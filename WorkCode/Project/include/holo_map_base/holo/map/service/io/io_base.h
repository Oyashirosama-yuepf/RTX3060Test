/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file cmw_io.h
 * @brief Base interface for reader and writer.
 * @author wanghaiyang@holomatic.com
 * @date "2021-01-13"
 */

#ifndef HOLO_MAP_SERVICE_IO_IO_BASE_H_
#define HOLO_MAP_SERVICE_IO_IO_BASE_H_

#include <iomanip>
#include <string>
#include <sstream>

#include <holo/log/hololog.h>
#include <holo/map/service/io/types.h>

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
 * @brief Base interface for IO.
 */
class IOBase
{
public:
    /// Redefine inner types for members.
    using RawBufferValueType    = holo::uint8_t;
    using RawBufferType         = RawBufferValueType*;
    using RawBufferConstType    = RawBufferValueType const*;
    using RawBufferSizeType     = std::size_t;

    /// Redefine data package types for inner members.
    using DataPackageType   = holo::map::service::io::FixDataPackageType;
    using PatternType       = DataPackageType::PatternType;
    using TokenIdType       = DataPackageType::TokenIdType;

    /// Redefine timestamp value type.
    using TimestampValueType = holo::uint64_t;

    /// Define the max data package size.
    static RawBufferSizeType constexpr CAPACITY = holo::map::service::io::FIX_SIZE_VALUE;

    /**
     * @brief Define error code for IO interface.
     */
    enum ErrorCode : holo::uint8_t
    {
        ///< No error.
        ERROR_CODE_OK   = 0,
        ///< Nothing to do or there is no target data.
        ERROR_CODE_NONE,
        ///< Inner interface is busy now, wait a moment, retry to read or write again.
        ERROR_CODE_AGAIN,
        ///< An error occurs in current function.
        ERROR_CODE_FAILED,
    };

    /// Redefine error code type for inner members.
    using ErrorCodeType = ErrorCode;
    /**
     * @brief Default Constructor.
     */
    IOBase()
    {
    }

    /**
     * @brief Default Destructor.
     */
    virtual ~IOBase()
    {
    }

    IOBase(IOBase const&) = delete;
    IOBase(IOBase&&) = delete;

    IOBase& operator = (IOBase const&) = delete;
    IOBase& operator = (IOBase&&) = delete;

    /**
     * @brief Whether or not current reader has been exited.
     * 
     * @return true: Main channel has been exited, we will never receive message from this reader.
     *         false: Current handle is valid.
     */
    virtual holo::bool_t IsExit() const = 0;

    /**
     * @brief Access the reader status info.
     * 
     * @return Status info with json format.
     */
    virtual std::string Status() = 0;

    /**
     * @brief Access token id.
     * 
     * @return Token id.
     */
    virtual TokenIdType GetTokenId() const noexcept
    {
        return this->token_id_;
    }

    /**
     * @brief Assign token id.
     * 
     * @param[in] id Token id.
     */
    virtual void SetTokenId(TokenIdType const id) noexcept
    {
        this->token_id_ = id;
    }

    /**
     * @brief Access pattern value.
     * 
     * @return Pattern value.
     */
    virtual PatternType GetPattern() const noexcept
    {
        return this->pattern_;
    }

    /**
     * @brief Assign pattern value.
     * 
     * @param[in] p Pattern value.
     */
    virtual void SetPattern(PatternType const p) noexcept
    {
        this->pattern_ = p;
    }

    /**
     * @brief Assign verbose flag.
     *  
     * @param[in] v If true, reader object will print debug message to log.
     */
    virtual void SetVerbose(holo::bool_t const v) noexcept
    {
        this->verbose_ = v;
    }

    /**
     * @brief Access verbose flag.
     * 
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const
    {
        return this->verbose_;
    }

    /**
     * @brief Access MQDT flag.
     * 
     * @return MQDT flag.
     */
    virtual holo::bool_t GetMqdtFlag() const noexcept = 0;

    /**
     * @brief Assign MQDT flag.
     * 
     * @param[in] f If true: publish and subscribe data by MQDT protocol;
     *              If false: publish and subscribe data by raw message queue.
     */
    virtual void SetMqdtFlag(holo::bool_t const f) noexcept = 0;

    /**
     * @brief Read data from raw message queue interface.
     * 
     * @note This function only used in MQDT as callback.
     * @param[in] buffer Data buffer for caching reading data.
     * @param[in] capacity Max capacity of data buffer.
     * @param[in] size Real size of cached data in buffer.
     */
    virtual void RawRead(RawBufferType buffer, RawBufferSizeType const capacity, RawBufferSizeType& size) = 0;

    /**
     * @brief Write data to raw message queue interface.
     * 
     * @param[in] buffer Data need to write to message queue.
     * @param[in] size Data size in buffer.
     */
    virtual void RawWrite(RawBufferConstType buffer, RawBufferSizeType const size) = 0;

    /**
     * @brief Update MQDT status, real flush data to message queue from sending buffer.
     * 
     * @param[in] v Timestamp with unit millisecond.
     */
    virtual void Update(TimestampValueType const v) = 0;

    /**
     * @brief Re-create IO environment, because the communication protocol maybe
     *        not support re-connection, if server or client breakdown, they will
     *        not connect automatically.
     * 
     * @note If we detect a server or client loss of communication by timer and
     *       heartbeat, we should reset the IO environment.
     */
    virtual void Reset() = 0;

protected:
    /**
     * @brief Print raw data buffer to log for debuging.
     * 
     * @param[in] buffer Data buffer form MQ callback.
     * @param[in] size Data buffer size.
     */
    void debugByteStream(std::string const& title, holo::uint8_t const* buffer, std::size_t const size)
    {
        if (!this->detail_)
        {
            return;
        }

        LOG(INFO) << title << "::debugByteStream, size=" << size;
        for (std::size_t i = 0; i < size; i += 20)
        {
            std::stringstream stream;
            for (std::size_t j = 0; j < 20 && i+j < size; ++j)
            {
                stream << std::uppercase << std::setfill('0') << std::setw(2) << std::hex
                       << static_cast<int>(buffer[i+j]) << " ";
            }
            LOG(INFO) << title << "::debugByteStream, i=" << i << " " << stream.str();
        }
    }

protected:
    ///< If true, print detail message data to log.
    holo::bool_t    detail_     = false;
    ///< If true, print debug message to log.
    holo::bool_t    verbose_    = false;
    ///< Counter of all the valid  message received from MQ or sent to MQ.
    std::size_t     counter_    = 0;

    /// Token id, this value must be set in map service client.
    TokenIdType     token_id_ = 0;
    /// Pattern value, this value should be udpate in routing applications.
    PatternType     pattern_  = PatternType::PATTERN_REGION;
}; ///< End of class IOBase

/**
 * @}
 *
 */

} ///< namespace io
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_IO_IO_BASE_H_ */
