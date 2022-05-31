/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_writer.h
 * @brief Concrete session writer based on cmw message channel.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_WRITER2_H_
#define HOLO_MAP_SERVICE_IO_CMW_WRITER2_H_

#include <memory>
#include <queue>

#include <holo/map/service/io/writer.h>
#include <holo/map/common/classes/auto_spin_mutex.h>

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
 * @brief Concrete writer based on CMW message queue, write session data to CME message queue.
 */
class CMWWriter2 : public WriterBase
{
public:
    /// Redefine inner type for data buffer.
    using DataValueType           = RawBufferValueType;
    using DataBufferType          = RawBufferType;
    using DataBufferConstType     = RawBufferConstType;
    using DataBufferSizeType      = RawBufferSizeType;

    /// Redefine message type for MQ.
    using BusType           = cmw_wrapper::CmwBus;
    using BusWriterType     = cmw_wrapper::CmwBus::WriterType<DataBufferType>;

    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Topic name.
     */
    CMWWriter2(BusType& bus, std::string const& topic) : bus_(bus)
    {
        static_assert(sizeof(holo::uint8_t) == sizeof(DataValueType),
            "In class CMWWriter2: DataBufferType only support types with 8 bits(1 byte)");
        this->pub_session_ = this->bus_.AddWriter<DataBufferType>(topic);
    }

    /**
     * @brief Descontructor.
     */
    virtual ~CMWWriter2()
    {
    }

    /**
     * @brief Whether or not current writer has been exited.
     * 
     * @return true: Main channel has been exited, we will never sent message by this writer.
     *         false: Current handle is valid.
     */
    virtual holo::bool_t IsExit() const override
    {
        return !BusType::IsRunning();
    }

protected:
    virtual void RawWrite(DataBufferConstType buffer, DataBufferSizeType const size) override
    {
        if (size > this->max_protocol_capacity_ || size <= 0)
        {
            LOG(ERROR) << "CMWWriter2::RawWrite fail, size=" << size
                       << " capacity=" << this->max_protocol_capacity_;
            return;
        }

        if (this->verbose_)
        {
            this->debugByteStream("CMWWriter2::RawBuffer", buffer, size);
        }

        {
            holo::map::AutoSpinMutex guard(this->pub_mutex_);

            ++this->raw_write_counter_;
            this->pub_session_.Write(buffer, size);

            if (this->verbose_)
            {
                LOG(INFO) << "CMWWriter2::RawWrite debug, size=" << size
                          << " token_id=" << this->GetTokenId()
                          << " raw_write_counter=" << this->raw_write_counter_
                          << " real_write_counter=" << this->real_write_counter_
                          << " topic=" << this->pub_session_.GetTopicName();
            }
        }
    }

private:
    /// Message queue handle, must be initialized outside.
    BusType&                 bus_;              
    /// Publisher handle.
    BusWriterType            pub_session_;
    /// Mutex for free and busy session buffer.
    holo::map::SpinMutex     pub_mutex_;
}; ///< End of class CMWWriter2.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_WRITER2_H_ */
