/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mqdt.h
 * @brief Define interface for MQDataTransfer.
 * @author wanghaiyang@holomatic.com
 * @date "2021-11-12"
 */

#ifndef HOLO_MAP_SERVICE_IO_DETAILS_MQDT_H_
#define HOLO_MAP_SERVICE_IO_DETAILS_MQDT_H_

#include <holo/map/service/io/io_base.h>

namespace holo
{
namespace map
{
namespace service
{
namespace io
{
namespace details
{

/**
 * @addtogroup io
 * @{
 *
 */

/**
 * @brief A fast and reliable data transation interface based on KCP(A fast
 *        and reliable protocol).
 */
class MQDataTransfer
{
public:
    /// Redefine IOBase type for inner callback members.
    using IOBaseType        = holo::map::service::io::IOBase;
    using IOBasePtrType     = IOBaseType*;

    /// Redefine error code for MQDT.
    using ErrorCodeType     = IOBaseType::ErrorCode;

    /// Redefine inner type for class members.
    using TokenIdType           = IOBaseType::TokenIdType();
    using TimestampValueType    = IOBaseType::TimestampValueType;

    /// Redefine buffer type for inner members.
    using BufferType      = IOBaseType::RawBufferType;
    using BufferConstType = IOBaseType::RawBufferConstType;
    using BufferSizeType  = IOBaseType::RawBufferSizeType;

    /**
     * @brief Default Constructor.
     * 
     * @param[in] io IOBase pointer.
     */
    MQDataTransfer(IOBaseType* io, BufferSizeType const size);

    /**
     * @brief Default Destructor.
     */
    virtual ~MQDataTransfer();

    MQDataTransfer(MQDataTransfer&& t) = delete;
    MQDataTransfer(MQDataTransfer const& t) = delete;
    
    MQDataTransfer& operator = (MQDataTransfer&& t) = delete;
    MQDataTransfer& operator = (MQDataTransfer const& t) = delete;

    /**
     * @brief Access MQDT protocol header size.
     * 
     * @return MQDT protocol header size.
     */
    static BufferSizeType GetHeaderSize();

    /**
     * @brief Read data package buffer from MQDT.
     *
     * @param[out] buffer Data buffer for caching data package..
     * @param[in] capacity Max capacity of package data buffer.
     * @param[out] size Data size in package data buffer.
     * @return ERROR_CODE_OK: read a data package from MQDT.
     *         ERROR_CODE_NONE and ERROR_CODE_AGAIN: data is not ready in MQDT.
     *         ERROR_CODE_FAILED: an error occurs in this function.
     */
    ErrorCodeType Read(BufferType buffer, BufferSizeType const capacity, BufferSizeType& size);

    /**
     * @brief Write raw message to MQDT.
     * 
     * @param[in] buffer Message data buffer.
     * @param[in] size Data size of Message data buffer.
     */
    ErrorCodeType Write(BufferConstType buffer, BufferSizeType const size);

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
    ErrorCodeType Exchange(BufferConstType raw_buffer, BufferSizeType const raw_size,
        BufferType real_buffer, BufferSizeType const real_capacity, BufferSizeType& real_size);

    /**
     * @brief Update MQDT status, real flush data to message queue from MQDT sending buffer.
     * 
     * @param[in] v Timestamp with unit millisecond.
     */
    void Update(TimestampValueType const v);

    /**
     * @brief Re-create MQDT protocol environment, because the Raw MQDT protocol(KCP)
     *        not support re-connection, if server or client breakdown, they will not
     *        connect automatically.
     * 
     * @note If we detect a server or client loss of communication by timer and heartbeat,
     *       we should reset the MQDT protocol environment.
     */
    void Reset();

private:
    ///< Declaration the inner class.
    class MQDataTransferInner;
    ///< Inner data transfer pointer.
    MQDataTransferInner* inner_ = nullptr;
}; ///< End of class MQDataTransfer.

/**
 * @}
 *
 */

} ///< namespace details
} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_DETAILS_MQDT_H_ */