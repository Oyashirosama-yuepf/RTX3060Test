/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_reader.h
 * @brief Concrete session reader based on cmw message channel.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_READER_H_
#define HOLO_MAP_SERVICE_IO_CMW_READER_H_

#include <memory>
#include <queue>
#include <sstream>

#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo/map/service/io/reader.h>

#include <holo_cmw/CMW/CMW.h>
#include <holo_cmw/message/message.h>

namespace holo
{
namespace map
{
namespace service
{
namespace io
{

/**
 * @addtogroup io
 * @{
 *
 */

/**
 * @brief Concrete session reader, read session data from CMW message queue.
 * 
 * @detail This object is thread-safe, we can receive data from MQ and read
 *         data from it at the same time.
 * 
 * @note If in map local client, the token id must be set(ReaderBase::SetToken()).
 */
class CMWReader : public ReaderBase
{
public:
    /// Refine inner type for session.
    using DataPackagePtrType    = ReaderBase::DataPackageType*;

    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Topic name.
     */
    CMWReader(holo_cmw::CMW& cmw, std::string const& topic) :
        cmw_(cmw)
    {
        this->sub_session_ = this->cmw_.AddSubscriber<holo_cmw::CMW::DataPackageTopicType>(
            topic, 1, std::bind(&CMWReader::CallbackSession, this, std::placeholders::_1));
    }

    /**
     * @brief Desconstructor.
     */
    virtual ~CMWReader()
    {
        holo::map::AutoSpinMutex lock(this->mutex_);

        while (!this->busy_session_buffer_.empty())
        {
            DataPackagePtrType ptr = this->busy_session_buffer_.front();
            this->busy_session_buffer_.pop();
            delete ptr;
        }

        while (!this->free_session_buffer_.empty())
        {
            DataPackagePtrType ptr = this->free_session_buffer_.front();
            this->free_session_buffer_.pop();
            delete ptr;
        }
    }

    /**
     * @brief Callback function will be called by CMW.
     * 
     * @param[in] msg Middle data type in CMW.
     */
    void CallbackSession(holo_cmw::CMW::DataPackageTopicType const& msg)
    {
        // 0 is a general token, if inner token is 0, we can receive
        // every message even though it is not related to current job.
        if (0 != this->GetTokenId() && msg.token_id != this->GetTokenId())
        {
            return;
        }
    
        ++this->counter_;
        DataPackagePtrType ptr = nullptr;
        {
            holo::map::AutoSpinMutex lock(this->mutex_);
            if (this->free_session_buffer_.empty())
            {
                ptr = new DataPackageType();
            }
            else
            {
                ptr = this->free_session_buffer_.front();
                this->free_session_buffer_.pop();
            }
        }

        // Clear dirty data and status for the session object.
        ptr->Clear();
        holo_cmw::Convert(msg, *ptr);

        {
            holo::map::AutoSpinMutex lock(this->mutex_);
            this->busy_session_buffer_.push(ptr);
            if (this->verbose_)
            {
                LOG(INFO) << "CMWReader::CallbackSession debug, token=" << ptr->GetTokenId()
                          << " sequence_id=" << ptr->GetSequenceId() << " item_count=" << ptr->GetCount()
                          << " data_size=" << ptr->GetDataSize() << " free_queue_size=" << this->free_session_buffer_.size()
                          << " busy_queue_size=" << this->busy_session_buffer_.size() << " callback_counter=" << this->counter_;
            }
        }
    }

    /**
     * @brief Read session data from current cache, if no valid session, empty flag will true.
     * 
     * @note If the second output(empty) is true, we should stop calling this function, if it is
     *       false, the inner cache maybe have many ready sessions, we should try to call it again.
     *       
     * @param[out] session Session object, if the inner cache is not empty, it will be set valid data.
     * @param[out] empty A flag for the output session, if the session is valid, it will be false.
     */
    void Read(DataPackageType& session, holo::bool_t& empty)
    {
        session.Clear();
        empty = false;
        
        DataPackagePtrType ptr = nullptr;
        {
            holo::map::AutoSpinMutex lock(this->mutex_);
            if (this->busy_session_buffer_.empty())
            {
                empty = true;
                return;
            }

            ptr = this->busy_session_buffer_.front();
            this->busy_session_buffer_.pop();
        }

        session = *ptr;
        ptr->Clear();
        
        {
            holo::map::AutoSpinMutex lock(this->mutex_);
            this->free_session_buffer_.push(ptr);
            if (this->verbose_)
            {
                LOG(INFO) << "CMWReader::Read debug, free_queue_size=" << this->free_session_buffer_.size()
                          << " busy_queue_size=" << this->busy_session_buffer_.size();
            }
        }
    }

    /**
     * @brief Whether or not current reader has been exited.
     * 
     * @return Always return false, and this reader always valid.
     */
    virtual holo::bool_t IsExit() const override
    {
        return false;
    }

    /**
     * @brief Access the reader status info.
     * 
     * @return Status info with json format.
     */
    virtual std::string Status() override
    {
        std::stringstream stream;
        {
            holo::map::AutoSpinMutex lock(this->mutex_);
            stream << "{\"busy_session_buffer_size\":" << this->busy_session_buffer_.size()
                   << ", \"free_session_buffer_size\":" << this->free_session_buffer_.size()
                   << ", \"counter\":" << this->counter_
                   << ", \"token_id\":" << this->token_id_
                   << "}";
        }
        return stream.str();
    }

    /**
     * @brief Release free buffer by size.
     * 
     * @param[in] size A size for release free buffer.
     */
    virtual void ReleaseFreeBuffer(std::size_t const size) override
    {
        holo::map::AutoSpinMutex lock(this->mutex_);
        std::size_t count = 0;
        while (count < size && !this->free_session_buffer_.empty())
        {
            DataPackagePtrType ptr = this->free_session_buffer_.front();
            this->free_session_buffer_.pop();
            delete ptr;
            ++count;
        }
    }

    /**
     * @brief Get free buffer size.
     * 
     * @return Free buffer size.
     */
    virtual std::size_t GetFreeBufferSize() override
    {
        holo::map::AutoSpinMutex lock(this->mutex_);
        return this->free_session_buffer_.size();
    }

    /**
     * @brief Get busy buffer size.
     * 
     * @return Busy buffer size.
     */
    virtual std::size_t GetBusyBufferSize() override
    {
        holo::map::AutoSpinMutex lock(this->mutex_);
        return this->busy_session_buffer_.size();
    }

private:
    holo_cmw::CMW&                          cmw_;           ///< Message queue handle, must be initialized outside.
    holo_cmw::CMW::DataPackageSubscriber    sub_session_;   ///< Subscriber handle.

    holo::map::SpinMutex        mutex_;                 ///< Mutex for free and busy session buffer.
    std::queue<DataPackagePtrType>  busy_session_buffer_;   ///< All the new session data in this buffer.
    std::queue<DataPackagePtrType>  free_session_buffer_;   ///< All the dirty session data in this buffer.
}; ///< End of class CMWReader.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_READER_H_ */
