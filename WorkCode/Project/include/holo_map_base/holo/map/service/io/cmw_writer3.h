/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_writer3.h
 * @brief Concrete session writer based on cmw message channel for MDC CM.
 * @author wanghaiyang@holomatic.com
 * @date "2021-10-15"
 */

#ifndef HOLO_MAP_SERVICE_IO_CMW_WRITER3_H_
#define HOLO_MAP_SERVICE_IO_CMW_WRITER3_H_

#include <cassert>
#include <memory>
#include <queue>

#include <holo/log/hololog.h>
#include <holo/map/service/io/writer.h>
#include <holo/map/common/classes/auto_spin_mutex.h>

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
 * @brief Concrete writer based on CMW message queue, write session data to CME message queue.
 */
class CMWWriter3 : public WriterBase
{
public:
    using DataPackagePtrType    = ReaderBase::DataPackageType*;
    using FixBufferType         = holo_base_msg::core::BuiltinBuffer;

    using BusType           = cmw_wrapper::CmwBus;
    using BusWriterType     = cmw_wrapper::CmwBus::WriterType<FixBufferType,
        mdc_cm_wrapper::BuiltinBufferSITraits<FixBufferType>>;
    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Topic name.
     */
    CMWWriter3(BusType& bus, std::string const& topic) : bus_(bus)
    {
        static_assert(sizeof(holo::uint8_t) == sizeof(FixBufferType::value_type),
            "FixBufferType only support types with 8 bits(1 byte)");
        this->buffer_.reserve(CAPACITY);
        this->pub_session_ = this->bus_.AddWriter<holo_base_msg::core::BuiltinBuffer,
            mdc_cm_wrapper::BuiltinBufferSITraits<holo_base_msg::core::BuiltinBuffer>>(topic);
    }

    /**
     * @brief Descontructor.
     */
    virtual ~CMWWriter3()
    {
    }

    /**
     * @brief Write session data to message queue.
     * 
     * @param[in] session Session data.
     */
    void Write(DataPackageType const& session)
    {
        // TODO: wanghaiyang 2021-11-09 RoutingMode is not ready, close it temporary.
        //if (session.GetPattern() != this->pattern_)
        //{
        //    LOG(ERROR) << "CMWWriter3::Write fail, invalid pattern, bus_pattern=" << static_cast<int>(this->pattern_)
        //               << " session_pattern=" << static_cast<int>(session.GetPattern());
        //    return;
        //}

        ++this->counter_;

        std::size_t const size = session.GetSerializedSize();
        if (size > CAPACITY)
        {
            LOG(ERROR) << "CMWWriter3::Write fail, size=" << size << " capacity=" << CAPACITY
                       << " capacity2=" << this->buffer_.capacity();
            return;
        }

        this->buffer_.resize(CAPACITY);

        holo::uint8_t* data = static_cast<holo::uint8_t*>(&this->buffer_[0]);
        holo::serialization::Serializer<true, 1> serializer(data, CAPACITY);
        session.Serialize(serializer);

        if (this->verbose_)
        {
            this->debugByteStream("CMWWriter3", data, size);
        }

        this->buffer_.resize(size);
        
        this->pub_session_.Write(this->buffer_);
        if (this->verbose_)
        {
            LOG(INFO) << "CMWWriter3::Write debug, counter=" << this->counter_ << " token_id=" << session.GetTokenId()
                      << " sequence_id=" << session.GetSequenceId() << " item_count=" << session.GetCount()
                      << " data_size=" << session.GetDataSize() << " payload_size=" << size
                      << " topic=" << this->pub_session_.GetTopicName();
        }
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

private:
    /// Message queue handle, must be initialized outside.
    BusType&                 bus_;              
    /// Publisher handle.
    BusWriterType            pub_session_;
    /// Data buffer.
    FixBufferType            buffer_;        ///< Data buffer.
    /// Data buffer capacity;
    static std::size_t const CAPACITY   = holo::map::service::io::FIX_SIZE_VALUE;
}; ///< End of class CMWWriter3.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_WRITER4_H_ */