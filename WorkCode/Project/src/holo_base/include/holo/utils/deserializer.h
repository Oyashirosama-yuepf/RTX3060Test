/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file deserializer.h
 * @brief This header file defines Deserializer class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-7
 */

#ifndef HOLO_UTILS_DESERIALIZER_H_
#define HOLO_UTILS_DESERIALIZER_H_

#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo/utils/serialization_exception.h>
#include <holo/utils/internal/reference_buffer.h>

namespace holo
{
namespace utils
{
/**
 * @addtogroup utils
 * @{
 *
 */

using BasicInputBuffer = BasicDeserializer;

/**
 * @brief Deserializer 
 *
 * @tparam IsNetworkByteOrder
 * @tparam Alignment
 */
template<bool_t IsNetworkByteOrder = true, size_t Alignment = 4>
class Deserializer : public BasicDeserializer
{
public:
    using BasicDeserializer::BasicDeserializer;

    static size_t const ALIGNMENT_VALUE = Alignment;

    static size_t constexpr GetAlignment() noexcept
    {
        return ALIGNMENT_VALUE;
    }

    /**
     * @brief Sets the position of next character to be extracted from the input buffer to next aligned position.
     */
    void Align() noexcept final
    {
        get_offset_ = (get_offset_ + ALIGNMENT_VALUE - 1) & (-ALIGNMENT_VALUE);
    }

protected:
    /**
     * @brief Read bool_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(bool_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read char_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(char_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read int8_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(int8_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read uint8_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(uint8_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read int16_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(int16_t& value) const final
    {
        readAligned(value);

    }

    /**
     * @brief Read uint16_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(uint16_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read int32_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(int32_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read uint32_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(uint32_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read int64_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(int64_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read uint64_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(uint64_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read float32_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(float32_t& value) const final
    {
        readAligned(value);
    }

    /**
     * @brief Read float64_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::DeserializationBufferUnderflowException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    void read(float64_t& value) const final
    {
        readAligned(value);
    }

private:
    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 1), void>::type* = nullptr>
    void readAligned(T& value) const
    {
        if(computeAlignedSize(get_offset_ + sizeof(uint8_t)) > size_)
        {
            throw holo::exception::DeserializationBufferUnderflowException(get_offset_);
        }
        value        = static_cast<T>(data_[get_offset_++]);
    };

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 !(std::is_floating_point<T>::value) && 
                                                 (sizeof(T) > 1), void>::type* = nullptr>
    void readAligned(T& value) const
    {
        size_t expected_offset = computeAlignedOffset<T>();
        if(computeAlignedSize(expected_offset + sizeof(T)) > size_)
        {
            throw holo::exception::DeserializationBufferUnderflowException(get_offset_);
        }
        value          = ntoh(*reinterpret_cast<T*>(data_ + expected_offset));
        get_offset_    = expected_offset + sizeof(T);
    }

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value &&
                                                 std::is_floating_point<T>::value && 
                                                 (sizeof(T) == 4), void>::type* = nullptr>
    void readAligned(T& value) const
    {
        size_t expected_offset = computeAlignedOffset<T>();
        if(computeAlignedSize(expected_offset + sizeof(T)) > size_)
        {
            throw holo::exception::DeserializationBufferUnderflowException(get_offset_);
        }
        uint32_t  cur = (ntoh(*reinterpret_cast<uint32_t*>(data_ + expected_offset)));
        uint32_t* p   = reinterpret_cast<uint32_t*>(&value);
        *p            = cur;
        get_offset_   = expected_offset + sizeof(T);
    }

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 std::is_floating_point<T>::value && 
                                                 (sizeof(T) == 8), void>::type* = nullptr>
    void readAligned(T& value) const
    {
        size_t expected_offset = computeAlignedOffset<T>();
        if((expected_offset + sizeof(T)) > size_)
        {
            throw holo::exception::DeserializationBufferUnderflowException(get_offset_);
        }
        uint64_t  cur = (ntoh(*reinterpret_cast<uint64_t*>(data_ + expected_offset)));
        uint64_t* p   = reinterpret_cast<uint64_t*>(&value);
        *p            = cur;
        get_offset_   = expected_offset + sizeof(T);
    }

    template<typename T, typename std::enable_if<Alignment >= sizeof(T), void>::type* = nullptr>
    size_t computeAlignedOffset() const noexcept
    {
        return (get_offset_ + (sizeof(T) - 1U)) & (~(sizeof(T) - 1U));
    }

    template<typename T, typename std::enable_if<Alignment < sizeof(T), void>::type* = nullptr>
    size_t computeAlignedOffset() const noexcept
    {
        return (get_offset_ + (Alignment - 1U)) & (~(Alignment - 1U));
    }

    size_t computeAlignedSize(size_t value) const noexcept
    {
        return (value + (Alignment - 1U)) & (~(Alignment - 1U));
    }

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 sizeof(T) == 1, void>::type* = nullptr>
    T ntoh(T value) const noexcept
    {
        return value;
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 2), void>::type* = nullptr>
    T ntoh(T value) const noexcept
    {
        return static_cast<T>(holo::os::ntoh16(static_cast<uint16_t>(value)));
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 4), void>::type* = nullptr>
    T ntoh(T value) const noexcept
    {
        return static_cast<T>(holo::os::ntoh32(static_cast<uint32_t>(value)));
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 8), void>::type* = nullptr>
    T ntoh(T value) const noexcept
    {
        return static_cast<T>(holo::os::ntoh64(static_cast<uint64_t>(value)));
    };    

    template<typename T, typename std::enable_if<(!IsNetworkByteOrder) && 
                                                  std::is_arithmetic<T>::value, void>::type* = nullptr>
    T ntoh(T value) const noexcept
    {
        return value;
    };      
};

} //namespace utils
} //namespace holo

#endif
