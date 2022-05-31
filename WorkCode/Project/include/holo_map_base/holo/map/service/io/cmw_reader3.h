/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_reader3.h
 * @brief Concrete session reader based on cmw message channel for MDC CM.
 * @author wanghaiyang@holomatic.com
 * @date "2021-10-15"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_READER3_H_
#define HOLO_MAP_SERVICE_IO_CMW_READER3_H_

#include <cassert>
#include <memory>
#include <queue>
#include <sstream>

#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo/map/service/io/reader.h>

#include <cmw_wrapper/cmw_bus.h>
#include <gh02_msg/traits.h>

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
class CMWReader3 : public ReaderBase
{
public:
    /// Refine inner type for session.
    using FixBufferType     = holo_base_msg::core::BuiltinBuffer;
    using BusType           = cmw_wrapper::CmwBus;
    
    using BusReaderType     = cmw_wrapper::CmwBus::ReaderType<FixBufferType,
        mdc_cm_wrapper::BuiltinBufferSITraits<FixBufferType>>;

    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Topic name.
     */
    CMWReader3(BusType& bus, std::string const& topic) :
        bus_(bus)
    {
        static_assert(sizeof(holo::uint8_t) == sizeof(FixBufferType::value_type),
            "FixBufferType only support types with 8 bits(1 byte)");
        this->sub_session_ = bus.AddReader<FixBufferType,
            mdc_cm_wrapper::BuiltinBufferSITraits<FixBufferType>>(topic);
        this->sub_session_.SetOnDataAvailableCallback(std::bind(&CMWReader3::CallbackSession, this,
            std::placeholders::_1));
    }

    /**
     * @brief Desconstructor.
     */
    virtual ~CMWReader3()
    {
    }

    /**
     * @brief Callback function will be called by CMW.
     * 
     * @param[in] msg Middle data type in CMW.
     */
    void CallbackSession(FixBufferType const& buffer)
    {
        if (buffer.empty())
        {
            LOG_FIRST_N(ERROR, 1) << "CMWReader3::CallbackSession fail, invalid parameter";
            return;
        }

        if (this->verbose_)
        {
            this->debugByteStream("CMWReader3", buffer.data(), buffer.size());
        }

        ++this->counter_;
        DataPackagePtrType ptr = nullptr;
        {
            holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
            if (this->free_package_queue_.empty())
            {
                ptr = new DataPackageType();
            }
            else
            {
                ptr = this->free_package_queue_.front();
                this->free_package_queue_.pop();
            }
        }

        // Clear dirty data and status for the session object.
        ptr->Clear();
        
        std::size_t s = buffer.size();

        holo::serialization::Deserializer<true, 1> deserializer(const_cast<holo::uint8_t*>(buffer.data()), s);
        ptr->Deserialize(deserializer);

        {
            holo::map::AutoSpinMutex lock(this->package_queue_mutex_);

            if (this->verbose_)
            {
                LOG(INFO) << "CMWReader3::CallbackSession debug, token=" << ptr->GetTokenId()
                          << " sequence_id=" << ptr->GetSequenceId() << " item_count=" << ptr->GetCount()
                          << " data_size=" << ptr->GetDataSize() << " free_queue_size=" << this->free_package_queue_.size()
                          << " busy_queue_size=" << this->busy_package_queue_.size() << " callback_counter=" << this->counter_
                          << " topic=" << this->sub_session_.GetTopicName();
            }

            // 0 is an invalid token id, if we receive a package with 0 token id, we will discard it.            
            if (0 == ptr->GetTokenId())
            {
                LOG_FIRST_N(ERROR, 1) << "CMWReader3::CallbackSession error, token=" << ptr->GetTokenId()
                    << " sequence_id=" << ptr->GetSequenceId();
                this->free_package_queue_.push(ptr);
            }
            else
            {
                // TODO: wanghaiyang 2021-11-09 RoutingMode is not ready, close it temporary.
                //if (ptr->GetPattern() != this->pattern_)
                //{
                //    LOG(ERROR) << "CMWReader3::CallbackSession fail, invalid pattern,"
                //               << "bus_pattern=" << static_cast<int>(this->pattern_)
                //               << " session_pattern=" << static_cast<int>(ptr->GetPattern());
                //    this->free_package_queue_.push(ptr);
                //}
                //else
                {
                    this->busy_package_queue_.push(ptr);
                }
            }
        }
    }

    /**
     * @brief Whether or not current reader has been exited.
     * 
     * @return true: Main channel has been exited, we will never receive message from this reader.
     *         false: Current handle is valid.
     */
    virtual holo::bool_t IsExit() const override
    {
        return !BusType::IsRunning();
    }

private:
    BusType&                    bus_;                   ///< Message queue handle, must be initialized outside.
    BusReaderType               sub_session_;           ///< Subscriber handle.
}; ///< End of class CMWReader3.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_READER3_H_ */