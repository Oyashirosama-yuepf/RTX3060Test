/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file io_rw.h
 * @brief Base interface for mqdt.
 * @author wanghaiyang@holomatic.com
 * @date "2021-11-13"
 */

#ifndef HOLO_MAP_SERVICE_IO_IO_MQDT_H_
#define HOLO_MAP_SERVICE_IO_IO_MQDT_H_

#include "./details/mqdt.h"

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
 * @brief Base interface for MQDT.
 */
class IORW : public IOBase
{
public:
    /// Define type for MQDT.
    using MQDataTransferType     =  details::MQDataTransfer;
    using MQDataTransferUPtrType = std::unique_ptr<MQDataTransferType>;

    /**
     * @brief Default Constructor.
    */
    IORW()
    {
        this->max_package_capacity_     = IOBase::CAPACITY;
        this->max_protocol_capacity_    = IOBase::CAPACITY + MQDataTransferType::GetHeaderSize();

        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            this->handle_ = std::unique_ptr<MQDataTransferType>(new 
                MQDataTransferType(this, this->max_protocol_capacity_));
        }
    }

    /**
     * @brief Default Destructor.
     */
    virtual ~IORW()
    { 
        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            this->handle_ = nullptr;
        }
        
        this->max_package_capacity_ = 0;
        this->max_protocol_capacity_ = 0;
    }

    /**
     * @brief Access MQDT status.
     * 
     * @return Status info.
     */
    virtual std::string Status() override
    {
        return "IORW::RawRead Status, un-implementation";
    }

    /**
     * @brief Access MQDT flag.
     * 
     * @return MQDT flag.
     */
    virtual holo::bool_t GetMqdtFlag() const noexcept
    {
        return this->handle_flag_;
    }

    /**
     * @brief Assign MQDT flag.
     * 
     * @param[in] f If true: publish and subscribe data by MQDT protocol;
     *              If false: publish and subscribe data by raw message queue.
     */
    virtual void SetMqdtFlag(holo::bool_t const f) noexcept
    {
        this->handle_flag_ = f;
    }

    /**
     * @brief Update MQDT status, real flush data to message queue from sending buffer.
     * 
     * @param[in] v Timestamp with unit millisecond.
     */
    virtual void Update(TimestampValueType const v) override
    {
        if (this->handle_flag_)
        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            this->handle_->Update(v);
        }
    }

    /**
     * @brief Re-create MQDT protocol environment, because the Raw MQDT protocol(KCP)
     *        not support re-connection, if a server or client breakdown, they will not
     *        connect automatically.
     * 
     * @note If we detect a server or client loss of communication by timer and heartbeat,
     *       we should reset the MQDT protocol environment.
     */
    virtual void Reset() override
    {
        if (this->handle_flag_)
        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            this->handle_->Reset();
        }
    }

protected:
    /**
     * @brief Read data from raw message queue interface.
     * 
     * @note This function only used in MQDT as callback.
     * @param[in] buffer Data buffer for caching reading data.
     * @param[in] capacity Max capacity of data buffer.
     * @param[in] size Real size of cached data in buffer.
     */
    virtual void RawRead(RawBufferType buffer, RawBufferSizeType const capacity, RawBufferSizeType& size) override
    {
        (void)buffer;
        (void)capacity;
        (void)size;
        LOG(FATAL) << "IORW::RawRead fatal, un-implementation";
    }

    /**
     * @brief Write data to raw message queue interface.
     * 
     * @param[in] buffer Data need to write to message queue.
     * @param[in] size Data size in buffer.
     */
    virtual void RawWrite(RawBufferConstType buffer, RawBufferSizeType const size) override
    {
        (void)buffer;
        (void)size;
        LOG(FATAL) << "IORW::RawWrite fatal, un-implementation";
    }

    /**
     * @brief Write raw message to MQDT and read package buffer from MQDT.
     * 
     * @param[in] raw_buffer Message data buffer from message queue.
     * @param[in] raw_size Data size of Message data buffer.
     * @param[out] real_buffer Package data buffer from MQDT.
     * @param[in] real_capacity Max capacity of package data buffer.
     * @param[out] real_size Data size in package data buffer.
     * @return ERROR_CODE_OK: read a data package from MQDT.
     *         ERROR_CODE_NONE and ERROR_CODE_AGAIN: data is not ready in MQDT.
     *         ERROR_CODE_FAILED: an error occurs in this function.
     */
    ErrorCodeType Exchange(RawBufferConstType raw_buffer, RawBufferSizeType const raw_size,
        RawBufferType real_buffer, RawBufferSizeType const real_capacity, RawBufferSizeType& real_size)
    {
        if (!this->handle_flag_)
        {
            return ErrorCodeType::ERROR_CODE_FAILED;
        }

        ErrorCodeType ec = ErrorCodeType::ERROR_CODE_OK;
        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            ec = this->handle_->Exchange(raw_buffer, raw_size, real_buffer,
                real_capacity, real_size);
        }
        
        return ec;
    }

    /**
     * @brief Read data package buffer from MQDT.
     *
     * @param[out] buffer Package data buffer from MQDT.
     * @param[in] capacity Max capacity of package data buffer.
     * @param[out] size Data size in package data buffer.
     * @return ERROR_CODE_OK: read a data package from MQDT.
     *         ERROR_CODE_NONE and ERROR_CODE_AGAIN: data is not ready in MQDT.
     *         ERROR_CODE_FAILED: an error occurs in this function.
     */
    ErrorCodeType TryRead(RawBufferType buffer, RawBufferSizeType const capacity, RawBufferSizeType& size)
    {
        ErrorCodeType ec = ErrorCodeType::ERROR_CODE_NONE;
        if (this->handle_flag_)
        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            ec = this->handle_->Read(buffer, capacity, size);
        }
        return ec;
    }

    /**
     * @brief Write raw message to MQDT.
     * 
     * @param[in] buffer Message data buffer.
     * @param[in] size Data size of Message data buffer.
     */
    void TryWrite(RawBufferConstType buffer, RawBufferSizeType const size)
    {
        if (this->handle_flag_)
        {
            holo::map::AutoSpinMutex guard(this->handle_mutex_);
            this->handle_->Write(buffer, size);
        }
    }

protected:
    /// If true, transmite data message by MQDT protocol;
    /// If false, transmite data message by raw message queue.
    holo::bool_t                handle_flag_            = true;
    /// Mutex for protecting MQDT handle;
    holo::map::SpinMutex        handle_mutex_;
    /// MQDT handle.
    MQDataTransferUPtrType      handle_                 = nullptr;

    /// Map package data size. 
    RawBufferSizeType           max_package_capacity_   = 0;
    /// Map protocol data buffer size.
    RawBufferSizeType           max_protocol_capacity_  = 0;
}; ///< End of class IORW

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_IO_MQDT_H_ */
