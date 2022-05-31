/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file writer.h
 * @brief Writer interface.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_WRITER_H_
#define HOLO_MAP_SERVICE_IO_WRITER_H_

#include <string>

#include <holo/map/service/io/io_rw.h>

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
 * @brief Writer interface.
 */
class WriterBase : virtual public IORW
{
public:

    /**
     * @brief Constructor.
     */
    WriterBase() : IORW()
    {
        this->max_package_capacity_ = IOBase::CAPACITY;
        this->writer_buffer_capacity_ = 1400*10;// IOBase::CAPACITY + MQDataTransferType::GetHeaderSize();

        this->writer_buffer_ = new RawBufferValueType[this->writer_buffer_capacity_];

        if (this->writer_buffer_capacity_ < this->max_package_capacity_)
        {
            LOG(FATAL) << "WriterBase fatal, un-expected value, buffer_capacity=" << this->writer_buffer_capacity_
                       << " max_package_capacity=" << this->max_package_capacity_;
        }
    }

    /**
     * @brief Destructor.
     */
    virtual ~WriterBase()
    {
        delete [] this->writer_buffer_;
        this->writer_buffer_ = nullptr;

        this->writer_buffer_capacity_ = 0;
        this->max_package_capacity_ = 0;
    }

    WriterBase(WriterBase const&) = delete;
    WriterBase(WriterBase&&) = delete;
    WriterBase& operator = (WriterBase const&) = delete;
    WriterBase& operator = (WriterBase&&) = delete;

    /**
     * @brief Access the writer status info.
     * 
     * @return Status info with json format.
     */
    virtual std::string Status() override
    {
        std::stringstream stream;
        stream << "{\"token_id\":" << this->token_id_ 
               << ",\"raw_write_counter\":" << this->raw_write_counter_ 
               << ",\"real_write_counter\":" << this->real_write_counter_
                << "}";
        return stream.str();
    }

    /**
     * @brief Write data package to message queue.
     * 
     * @param[in] package Data package object.
     */
    virtual void Write(DataPackageType const& package)
    {
        // TODO: wanghaiyang 2021-11-09 RoutingMode is not ready, close it temporary.
        //if (session.GetPattern() != this->pattern_)
        //{
        //    LOG(ERROR) << "CMWWriter3::Write fail, invalid pattern, bus_pattern=" << static_cast<int>(this->pattern_)
        //               << " session_pattern=" << static_cast<int>(session.GetPattern());
        //    return;
        //}

        ++this->raw_write_counter_;

        RawBufferSizeType const size = package.GetSerializedSize();
        if (size > this->max_package_capacity_)
        {
            LOG(ERROR) << "WriterBase::Write fail, un-expected package, size=" << size
                       << " capacity=" << this->max_package_capacity_
                       << " sequence_id=" << package.GetSequenceId();
            return;
        }

        holo::serialization::Serializer<true, 1> serializer(this->writer_buffer_, this->max_package_capacity_);
        package.Serialize(serializer);

        if (this->verbose_)
        {
            this->debugByteStream("WriterBase::Write::RawBuffer", this->writer_buffer_, size);
        }
        
        if (this->GetMqdtFlag())
        {
            this->TryWrite(this->writer_buffer_, size);
        }
        else
        {
            this->RawWrite(this->writer_buffer_, size);
        }
        
        if (this->verbose_)
        {
            LOG(INFO) << "WriterBase::Write debug, mqdt=" << this->GetMqdtFlag() << " raw_size=" << size
                      << " token_id=" << package.GetTokenId() << " sequence_id=" << package.GetSequenceId()
                      << " item_count=" << package.GetCount() << " data_size=" << package.GetDataSize() 
                      << " raw_write_counter=" << this->raw_write_counter_
                      << " real_write_counter=" << this->real_write_counter_;
        }
    }

protected:
    /// Counter for writing messages to message queue.
    std::size_t raw_write_counter_  = 0;
    /// Counter for writing data packages to message queue.
    std::size_t real_write_counter_ = 0;

    /// Data buffer.
    RawBufferType            writer_buffer_;
    /// Max capacity of data buffer.
    RawBufferSizeType        writer_buffer_capacity_ = 0;
}; ///< End of class WriterBase.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_WRITER_H_ */
