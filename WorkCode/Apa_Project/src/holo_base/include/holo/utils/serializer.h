/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file serializer.h
 * @brief This header file defines Serializer class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-7
 */

#ifndef HOLO_UTILS_SERIALIZER_H_
#define HOLO_UTILS_SERIALIZER_H_

#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo/utils/serialization.h>
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

using BasicOutputBuffer = BasicSerializer;

/**
 * @brief Serializer Template 
 *
 * @tparam IsNetworkByteOrder
 * @tparam Alignment
 */
template<bool_t IsNetworkByteOrder = true, size_t Alignment = 4>
class Serializer : public BasicSerializer
{
public:
    using BasicSerializer::BasicSerializer;

    static size_t const ALIGNMENT_VALUE = Alignment;

    static size_t constexpr GetAlignment() noexcept
    {
        return ALIGNMENT_VALUE;
    }

    /**
     * @brief Sets the position of next character to be put into buffer.
     */
    void Align() noexcept final
    {
        size_t new_offset = (put_offset_ + ALIGNMENT_VALUE - 1) & (-ALIGNMENT_VALUE);
        while(put_offset_ < new_offset)
        {
            data_[put_offset_++] = 0u;
        }
        size_ = put_offset_ > size_ ? put_offset_ : size_; 
    }


protected:
    /**
     * @brief Write bool_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(bool_t value) final
    {
        writeAligned(value);
    };
    
    /**
     * @brief Write char_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(char_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write int8_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(int8_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write uint8_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(uint8_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write int16_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(int16_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write uint16_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(uint16_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write int32_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(int32_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write uint32_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(uint32_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write int64_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(int64_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write uint64_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(uint64_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write float32_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(float32_t value) final
    {
        writeAligned(value);
    };

    /**
     * @brief Write float64_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::SerializationBufferOverflowException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    void write(float64_t value) final
    {
        writeAligned(value);
    };

private:

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 !(std::is_floating_point<T>::value) && 
                                                 (sizeof(T) == 1), void>::type* = nullptr>
    void writeAligned(T value)
    {
        if(computeAlignedSize(put_offset_ + sizeof(T)) > capacity_)
        {
            throw holo::exception::SerializationBufferOverflowException(size_);
        }
        data_[put_offset_]  = static_cast<uint8_t>(value);
        put_offset_        += sizeof(T);
        size_               = put_offset_ > size_ ? put_offset_ : size_;
    };

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 !(std::is_floating_point<T>::value) && 
                                                 (sizeof(T) > 1), void>::type* = nullptr>
    void writeAligned(T value)
    {
        if(computeAlignedSize(put_offset_ + sizeof(T)) > capacity_)
        {
            throw holo::exception::SerializationBufferOverflowException(size_);
        }
        align<T>();
        *(reinterpret_cast<T*>(data_ + put_offset_))  = hton(value);
        put_offset_                                  += sizeof(T);
        size_                                         = put_offset_ > size_ ? put_offset_ : size_;
    };

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 std::is_floating_point<T>::value && 
                                                 (sizeof(T) == 4), void>::type* = nullptr>
    void writeAligned(T value)
    {
        if(computeAlignedSize(put_offset_ + sizeof(T)) > capacity_)
        {
            throw holo::exception::SerializationBufferOverflowException(size_);
        }
        align<T>();
        uint32_t* p                                        = reinterpret_cast<uint32_t*>(&value);
        *reinterpret_cast<uint32_t*>(data_ + put_offset_)  = hton(*p);        
        put_offset_                                       += sizeof(T);
        size_                                              = put_offset_ > size_ ? put_offset_ : size_;
    }; 

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && 
                                                 std::is_floating_point<T>::value && 
                                                 (sizeof(T) == 8), void>::type* = nullptr>
    void writeAligned(T value)
    {
        if(computeAlignedSize(put_offset_ + sizeof(T)) > capacity_)
        {
            throw holo::exception::SerializationBufferOverflowException(size_);
        }
        align<T>();
        uint64_t* p                                        = reinterpret_cast<uint64_t*>(&value);
        *reinterpret_cast<uint64_t*>(data_ + put_offset_)  = hton(*p);
        put_offset_                                       += sizeof(T);
        size_                                              = put_offset_ > size_ ? put_offset_ : size_;
    };                

    template<typename T, typename std::enable_if<Alignment >= sizeof(T), void>::type* = nullptr>
    size_t computeAlignedOffset() const noexcept
    {
        return (put_offset_ + (sizeof(T) - 1U)) & (~(sizeof(T) - 1U));
    };

    template<typename T, typename std::enable_if<Alignment < sizeof(T), void>::type* = nullptr>
    size_t computeAlignedOffset() const noexcept
    {
        return (put_offset_ + (Alignment - 1U)) & (~(Alignment - 1U));
    };

    size_t computeAlignedSize(size_t value) const noexcept
    {
        return (value + (Alignment - 1U)) & (~(Alignment - 1U));
    };

    template<typename T, typename std::enable_if<sizeof(T) == 1u, void>::type* = nullptr>
    void align_internal()
    {};

    template<typename T, typename std::enable_if<sizeof(T) == 2u, void>::type* = nullptr>
    void align_internal() noexcept
    {
        if((size_ & 1U))
        {
            data_[put_offset_++] = 0u;
            size_ = put_offset_ > size_ ? put_offset_ : size_; 
        }
    };

    template<typename T, typename std::enable_if<sizeof(T) == 4u, void>::type* = nullptr>
    void align_internal() noexcept
    {
        if((put_offset_ & 3U))
        {
            uint8_t  PadSize        = 4U - (put_offset_ & 3U);
            size_t   offset_shrink  = (put_offset_ & (~0x03U));
            uint32_t value          = *(reinterpret_cast<volatile uint32_t*>(data_ + offset_shrink));
            value       &= (0xFFFFFFFFU >> (PadSize * 8U));
            *(reinterpret_cast<uint32_t*>(data_ + offset_shrink)) = value;
            put_offset_ += PadSize;
            size_        = put_offset_ > size_ ? put_offset_ : size_; 
        }
    };

    template<typename T, typename std::enable_if<sizeof(T) == 8u, void>::type* = nullptr>
    void align_internal() noexcept
    {
        if((put_offset_ & 7U))
        {
            uint8_t  PadSize        = 8U - (put_offset_ & 7U);
            size_t   offset_shrink  = (put_offset_ & (~0x07U));
            uint64_t value          = *(reinterpret_cast<volatile uint64_t*>(data_ + offset_shrink));
            value                  &= (0xFFFFFFFFFFFFFFFFU >> (PadSize * 8U));
            *(reinterpret_cast<uint64_t*>(data_ + offset_shrink)) = value;
            put_offset_    += PadSize;
            size_           = put_offset_ > size_ ? put_offset_ : size_; 
        }
    };

    template<typename T, typename std::enable_if<sizeof(T) <= Alignment, void>::type* = nullptr>
    void align()
    {
        align_internal<T>();
    };

    template <typename T, typename std::enable_if<(!(sizeof(T) <= Alignment)) && 
                                                   (sizeof(uint8_t) == Alignment), void>::type* = nullptr>
    void align()
    {
        align_internal<uint8_t>();
    };

    template <typename T, typename std::enable_if<(!(sizeof(T) <= Alignment)) && 
                                                   (sizeof(uint16_t) == Alignment), void>::type* = nullptr>
    void align()
    {
        align_internal<uint16_t>();
    };

    template <typename T, typename std::enable_if<(!(sizeof(T) <= Alignment)) && 
                                                   (sizeof(uint32_t) == Alignment), void>::type* = nullptr>
    void align()
    {
        align_internal<uint32_t>();
    };

    template <typename T, typename std::enable_if<(!(sizeof(T) <= Alignment)) && 
                                                   (sizeof(uint64_t) == Alignment), void>::type* = nullptr>
    void align()
    {
        align_internal<uint64_t>();
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 1) && 
                                                 std::is_integral<T>::value, void>::type* = nullptr>
    T hton(T value) const noexcept
    {
        return value;
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 2) && 
                                                 std::is_integral<T>::value, void>::type* = nullptr>
    T hton(T value) const noexcept
    {
        return static_cast<T>(holo::os::hton16(static_cast<uint16_t>(value)));
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 4) && 
                                                 std::is_integral<T>::value, void>::type* = nullptr>
    T hton(T value) const noexcept
    {
        return static_cast<T>(holo::os::hton32(static_cast<uint32_t>(value)));
    };

    template<typename T, typename std::enable_if<IsNetworkByteOrder && 
                                                 std::is_arithmetic<T>::value && 
                                                 (sizeof(T) == 8) && 
                                                 std::is_integral<T>::value, void>::type* = nullptr>
    T hton(T value) const noexcept
    {
        return static_cast<T>(holo::os::hton64(static_cast<uint64_t>(value)));
    };    

    template<typename T, typename std::enable_if<(!IsNetworkByteOrder) && 
                                                  std::is_arithmetic<T>::value, void>::type* = nullptr>
    T hton(T value) const noexcept
    {
        return value;
    };   
};

} //namespace utils
} //namespace holo

#endif
