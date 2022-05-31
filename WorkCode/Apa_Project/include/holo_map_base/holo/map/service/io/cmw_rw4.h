/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_rw4.h
 * @brief Concrete message reader and writer for baidu-ehp which's based on gh02 cmw message queue.
 * @author zhengshulei@holomatic.com
 * @date "2021-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_RW4_H_
#define HOLO_MAP_SERVICE_IO_CMW_RW4_H_

#include <memory>
#include <queue>
#include <sstream>

#include <holo/log/hololog.h>
#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo/map/service/io/reader.h>
#include <holo/map/service/io/writer.h>

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
 * @brief Concrete reader and writer, read and write message data by CMW message queue.
 *        Specify for EHP/EHP receive and test broadcast.
 * 
 * @detail This object is thread-safe, we can receive data from MQ and read
 *         data from it at the same time.
 * 
 * @note If in map local client, the token id must be set(ReaderBase::SetToken()).
 */
class CmwRW4 : public ReaderBase, public WriterBase
{
public:
     /// Refine inner data type for message.
    using MsgBufferType     = holo_base_msg::core::BuiltinBuffer;
    using MsgBufferSizeType = MsgBufferType::size_type;

    /// Redefine message io type for MQ.
    using BusType           = cmw_wrapper::CmwBus;
    using BusReaderType     = cmw_wrapper::CmwBus::ReaderType<MsgBufferType,
        mdc_cm_wrapper::BuiltinBufferSITraits<MsgBufferType>>;
    using BusWriterType     = cmw_wrapper::CmwBus::WriterType<MsgBufferType,
        mdc_cm_wrapper::BuiltinBufferSITraits<MsgBufferType>>;

    /**
     * @brief Constructor.
     * 
     * @param[in] bus An initialized bus handle.
     * @param[in] reader_topic Reader topic name(/holo/map/adasis_data).
     * @param[in] writer_topic Writer topic name(/holo/map/adasis_data).
     * @param[in] read_mode read or write mode(true for reader).
     * @param[in] reader_buff_size Reader buffer size(1~50).
     */
    CmwRW4(BusType& bus, 
           std::string const& reader_topic, 
           std::string const& writer_topic, 
           holo::bool_t read_mode = true,
           const size_t reader_buff_size = 50) :
        ReaderBase(), WriterBase(), bus_(bus)
    {
        static_assert(sizeof(holo::uint8_t) == sizeof(MsgBufferType::value_type),
            "In class CmwRW4: MsgBufferType only support types with 8 bits(1 byte)");
        if(read_mode)
        {
            this->sub_session_ = bus.AddReader<MsgBufferType,
                mdc_cm_wrapper::BuiltinBufferSITraits<MsgBufferType>>(reader_topic, reader_buff_size);
            this->sub_session_.SetOnDataAvailableCallback(std::bind(&CmwRW4::CallbackMessage, this,
                std::placeholders::_1));
        }
        else
        {
            this->pub_session_ = this->bus_.AddWriter<MsgBufferType,
                mdc_cm_wrapper::BuiltinBufferSITraits<MsgBufferType>>(writer_topic);
        }
        
        {
            holo::map::AutoSpinMutex guard(this->pub_mutex_);
            this->msg_buffer_capacity_ = EHP_RAW_PACKAGE_MAXSIZE;
            this->msg_buffer_.resize(this->msg_buffer_capacity_);
        }
    }

    /**
     * @brief Desconstructor.
     */
    virtual ~CmwRW4()
    {
        {
            holo::map::AutoSpinMutex guard(this->pub_mutex_);
            this->msg_buffer_.clear();
        }
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
                   << ", \"real_reader_counter\":" << this->real_reader_counter_
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
     */
    void CallbackMessage(MsgBufferType const& buffer)
    {
        if (buffer.empty())
        {
            LOG_FIRST_N(ERROR, 1) << "CmwRW4::CallbackMessage fail, invalid parameter";
            return;
        }

        MsgBufferSizeType const size = buffer.size();
        if (size > this->EHP_RAW_PACKAGE_MAXSIZE)
        {
            LOG(ERROR) << "CmwRW4::CallbackMessage fail, un-expected package, size=" << size
                       << " capacity=" << this->EHP_RAW_PACKAGE_MAXSIZE;
        }

        if (IOBase::GetVerbose())
        {
            this->debugByteStream("CmwRW4::Read::RawBuffer", buffer.data(), size);
        }

        ReaderBase::CallbackRawBufferDirectToDataPackage(buffer.data(), size);

        ++this->real_reader_counter_;

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

    /**
     * @brief Write data package to message queue.
     * 
     * @param[in] package Data package object.
     */
    virtual void Write(DataPackageType const& package)
    {
        RawBufferConstType buffer = package.GetData();
        RawBufferSizeType const size = package.GetDataSize();

        if (IOBase::GetVerbose())
        {
            this->debugByteStream("CmwRW4::Write::RawBuffer", buffer, size);
        }

        {
            holo::map::AutoSpinMutex guard(this->pub_mutex_);

            ++this->real_write_counter_;

            this->msg_buffer_.clear();
            this->msg_buffer_.resize(size);
            std::memcpy(&(this->msg_buffer_[0]), buffer, size);
            this->pub_session_.Write(this->msg_buffer_);

            if (IOBase::GetVerbose())
            {
                LOG(INFO) << "CmwRW4::Write debug, real_size=" << size
                          << " real_write_counter=" << this->real_write_counter_
                          << " topic=" << this->pub_session_.GetTopicName();
            }
        }
    }

private:
    /// max ehp datapackage size
    const holo::uint32_t EHP_RAW_PACKAGE_MAXSIZE = 1500;
    /// Message queue handle, must be initialized outside.
    BusType&                    bus_;
    /// Subscriber(reader) handle.
    BusReaderType               sub_session_;
    /// Publisher(writer) handle.
    BusWriterType               pub_session_;
    /// Mutex for publisher handle.
    holo::map::SpinMutex        pub_mutex_;
    /// A buffer as a bridge for converting user data type to message type.
    MsgBufferType               msg_buffer_;
    /// Max buffer capacity.
    MsgBufferSizeType           msg_buffer_capacity_ = 0;
}; ///< End of class CmwRW4.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_RW4_H_ */
