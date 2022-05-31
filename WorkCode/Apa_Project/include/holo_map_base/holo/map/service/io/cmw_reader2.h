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

#ifndef HOLO_MAP_SERVICE_IO_CMW_READER2_H_
#define HOLO_MAP_SERVICE_IO_CMW_READER2_H_

#include <memory>
#include <queue>
#include <sstream>

#include <holo/log/hololog.h>

#include <holo/map/common/classes/auto_spin_mutex.h>
#include <holo/map/service/io/reader.h>

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
 * @brief Concrete session reader, read session data from CMW message queue.
 * 
 * @detail This object is thread-safe, we can receive data from MQ and read
 *         data from it at the same time.
 * 
 * @note If in map local client, the token id must be set(ReaderBase::SetToken()).
 */
class CMWReader2 : public ReaderBase
{
public:
    /// Redefine inner type for data buffer.
    using DataValueType             = RawBufferValueType;
    using DataBufferType            = RawBufferType;
    using DataBufferConstType       = RawBufferConstType;
    using DataBufferSizeType        = RawBufferSizeType;

    /// Redefine message type for MQ.
    using BusType           = cmw_wrapper::CmwBus;
    using BusReaderType     = cmw_wrapper::CmwBus::ReaderType<DataBufferType>;

    /**
     * @brief Constructor.
     * 
     * @param[in] cmw An initialized CMW handle.
     * @param[in] topic Topic name.
     */
    CMWReader2(BusType& bus, std::string const& topic) :
        bus_(bus)
    {
        static_assert(sizeof(holo::uint8_t) == sizeof(DataValueType),
            "In class CMWReader2: DataBufferType only support types with 8 bits(1 byte)");

        this->sub_session_ = bus.AddReader<DataBufferType>(topic);
        this->sub_session_.SetOnDataAvailableCallback(std::bind(&CMWReader2::CallbackMessage, this,
            std::placeholders::_1, std::placeholders::_2));
    }

    /**
     * @brief Desconstructor.
     */
    virtual ~CMWReader2()
    {
    }

    /**
     * @brief Callback function will be called by CMW.
     * 
     * @param[in] msg Middle data type in CMW.
     */
    void CallbackMessage(DataBufferConstType buffer, DataBufferSizeType const size)
    {
        if (nullptr == buffer || 0 == size)
        {
            LOG_FIRST_N(ERROR, 1) << "CMWReader2::CallbackMessage fail, invalid parameter, size=" << size;
            return;
        }

        if (size > this->max_protocol_capacity_)
        {
            LOG(ERROR) << "CMWReader2::CallbackMessage fail, un-expected package, size=" << size
                       << " capacity=" << this->max_protocol_capacity_;
            return;
        }

        if (this->verbose_)
        {
            this->debugByteStream("CMWReader2::RawBuffer", buffer, size);
        }

        ++this->raw_reader_counter_;

        if (!this->GetMqdtFlag())
        {
            this->CallbackDataPackage(this->buffer_, size);
            return;
        }

        RawBufferSizeType package_size = 0;
        ErrorCodeType const ec = this->Exchange(buffer, size, this->buffer_,
            this->buffer_capacity_, package_size);
        if (ErrorCodeType::ERROR_CODE_NONE == ec || ErrorCodeType::ERROR_CODE_AGAIN == ec)
        {
            return;
        }

        if (ErrorCodeType::ERROR_CODE_OK != ec)
        {
            LOG(ERROR) <<"CallbackMessage fail, ec=" << static_cast<int>(ec) << " size=" << size
                       << " package_size=" << package_size << " package_capacity=" << this->buffer_capacity_;
            return;
        }

        this->CallbackDataPackage(this->buffer_, package_size);
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
}; ///< End of class CMWReader.

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_CMW_READER2_H_ */
