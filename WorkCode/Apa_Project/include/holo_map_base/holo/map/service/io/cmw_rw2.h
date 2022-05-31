/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_rw2.h
 * @brief Concrete message reader and writer for common cmw message queue.
 * @author wanghaiyang@holomatic.com
 * @date "2021-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_RW2_H_
#define HOLO_MAP_SERVICE_IO_CMW_RW2_H_

#include <memory>
#include <queue>
#include <sstream>

#include <holo/log/hololog.h>
#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo/map/service/io/reader.h>
#include <holo/map/service/io/writer.h>

#include <cmw_wrapper/cmw_bus.h>

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
 * @brief Concrete reader and writer, read and write message data by CMW message queue.
 * 
 * @detail This object is thread-safe, we can receive data from MQ and read
 *         data from it at the same time.
 * 
 * @note If in map local client, the token id must be set(ReaderBase::SetToken()).
 */
class CmwRW2 : public ReaderBase, public WriterBase
{
public:
    /// Refine inner data type for message.
    using DataValueType             = RawBufferValueType;
    using DataBufferType            = RawBufferType;
    using DataBufferConstType       = RawBufferConstType;
    using DataBufferSizeType        = RawBufferSizeType;
    
    /// Redefine message io type for MQ.
    using BusType           = cmw_wrapper::CmwBus;
    using BusReaderType     = cmw_wrapper::CmwBus::ReaderType<DataBufferType>;
    using BusWriterType     = cmw_wrapper::CmwBus::WriterType<DataBufferType>;

    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Reader topic name.
     * @param[in] topic Writer topic name.
     */
    CmwRW2(BusType& bus, std::string const& reader_topic, std::string const& writer_topic) :
        bus_(bus)
    {
        static_assert(sizeof(holo::uint8_t) == sizeof(DataValueType),
            "In class CmwRW2: DataBufferType only support types with 8 bits(1 byte)");

        this->sub_session_ = bus.AddReader<DataBufferType>(reader_topic);
        this->sub_session_.SetOnDataAvailableCallback(std::bind(&CmwRW2::CallbackMessage,
            this, std::placeholders::_1, std::placeholders::_2));

        this->pub_session_ = this->bus_.AddWriter<DataBufferType>(writer_topic);
    }

    /**
     * @brief Desconstructor.
     */
    virtual ~CmwRW2()
    {
    }

    /**
     * @brief Access the RW3 status info.
     * 
     * @return Status info with json format.
     */
    virtual std::string Status() override
    {
        std::size_t busy_package_queue_size = 0;
        std::size_t free_package_queue_size = 0;

        {
            holo::map::AutoSpinMutex lock(this->package_queue_mutex_);
            busy_package_queue_size = this->busy_package_queue_.size();
            free_package_queue_size = this->free_package_queue_.size();
        }

        std::stringstream stream;
        {
            stream << "{\"busy_package_queue_size\":" << busy_package_queue_size
                   << ", \"free_package_queue_size\":" << free_package_queue_size
                   << ", \"raw_reader_counter\":" << this->raw_reader_counter_
                   << ", \"real_reader_counter\":" << this->real_reader_counter_
                   << ", \"raw_write_counter\"" << this->raw_write_counter_
                   << ", \"real_write_counter\"" << this->real_write_counter_
                   << ", \"token_id\":" << this->token_id_
                   << "}";
        }
        return stream.str();
    }

    /**
     * @brief Callback function will be called by CMW thread.
     * 
     * @param[in] msg Middle data type in CMW.
     * @param[size] size Data size.
     */
    void CallbackMessage(DataBufferConstType buffer, DataBufferSizeType const size)
    {
        if (nullptr == buffer || 0 == size)
        {
            LOG_FIRST_N(ERROR, 1) << "CmwRW2::CallbackMessage fail, invalid parameter, size=" << size;
            return;
        }

        if (size > this->max_protocol_capacity_)
        {
            LOG(ERROR) << "CmwRW2::CallbackMessage fail, un-expected package, size=" << size
                       << " capacity=" << this->max_protocol_capacity_;
            return;
        }

        if (IOBase::GetVerbose())
        {
            this->debugByteStream("CmwRW2::Read::RawBuffer", buffer, size);
            LOG(INFO) << "CmwRW2::CallbackMessage debug, mqdt=" << this->GetMqdtFlag() 
                      << " raw_size=" << size;
        }

        ++this->raw_reader_counter_;

        if (!this->GetMqdtFlag())
        {
            ReaderBase::CallbackDataPackage(buffer, size);
            return;
        }

        RawBufferSizeType package_size = 0;
        ErrorCodeType const ec = this->Exchange(buffer, size, this->buffer_, this->buffer_capacity_,
            package_size);
        if (ErrorCodeType::ERROR_CODE_NONE == ec || ErrorCodeType::ERROR_CODE_AGAIN == ec)
        {
            return;
        }

        if (ErrorCodeType::ERROR_CODE_OK != ec)
        {
            LOG(ERROR) <<"CmwRW2::CallbackMessage fail, ec=" << static_cast<int>(ec) << " raw_size=" << size
                       << " package_size=" << package_size << " package_capacity=" << this->buffer_capacity_;
            return;
        }

        ReaderBase::CallbackDataPackage(this->buffer_, package_size);
    }

    /**
     * @brief Whether or not current io has been exited.
     * 
     * @return true: Main channel has been exited, we will never receive message from this reader.
     *         false: Current handle is valid.
     */
    virtual holo::bool_t IsExit() const override
    {
        return !BusType::IsRunning();
    }

protected:
    /**
     * @brief Real write data to message queue.
     * 
     * @param[in] buffer Data stream.
     * @param[in] size Data size in buffer.
     */
    virtual void RawWrite(DataBufferConstType buffer, DataBufferSizeType const size) override
    {
        if (size > this->max_protocol_capacity_ || size <= 0)
        {
            LOG(ERROR) << "CmwRW2::RawWrite fail, size=" << size << " capacity=" << this->max_protocol_capacity_;
            return;
        }

        if (IOBase::GetVerbose())
        {
            this->debugByteStream("CmwRW2::Write::RawBuffer", buffer, size);
        }

        {
            holo::map::AutoSpinMutex guard(pub_mutex_);

            ++this->real_write_counter_;
            this->pub_session_.Write(buffer, size);

            if (IOBase::GetVerbose())
            {
                LOG(INFO) << "CmwRW2::RawWrite debug, mqdt=" << this->GetMqdtFlag() << "real_size=" << size
                          << " token_id=" << this->GetTokenId()
                          << " raw_write_counter=" << this->raw_write_counter_
                          << " real_write_counter=" << this->real_write_counter_
                          << " topic=" << this->pub_session_.GetTopicName();
            }
        }
    }

private:
    /// Message queue handle, it must be initialized outside.
    BusType&                    bus_;
    /// Subscriber(reader) handle.
    BusReaderType               sub_session_;
    /// Publisher(writer) handle.
    BusWriterType               pub_session_;
    /// Mutex for publisher handle.
    holo::map::SpinMutex        pub_mutex_;
}; ///< End of class CmwRW2.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_RW2_H_ */