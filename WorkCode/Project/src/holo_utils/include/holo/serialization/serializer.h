/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file serializer.h
 * @brief This header file defines Serializer class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2021-3-23
 */

#ifndef HOLO_SERIALIZATION_SERIALIZER_H_
#define HOLO_SERIALIZATION_SERIALIZER_H_

#include <holo/core/endian.h>
#include <holo/core/types.h>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include "utility.h"

namespace holo
{
namespace serialization
{
template <bool_t IsNetworkByteOrder = true, size_t Alignment = 4U>
class Serializer;

class SerializationBufferOverflowException : public std::exception
{
};

template <size_t Alignment>
class Serializer<true, Alignment>
{
public:
    static bool const   NETWORK_BYTE_ORDER = true;
    static size_t const ALIGNMENT_VALUE    = Alignment;

    Serializer(void* buffer, size_t capacity, size_t offset = 0U)
      : buffer_(buffer), capacity_(capacity), offset_(offset)
    {
        (void)std::memset(reinterpret_cast<uint8_t*>(buffer) + offset, 0, capacity - offset);
    }

    Serializer& operator<<(bool value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<uint8_t*>(buffer_)[offset_] = value;
        offset_ += sizeof(bool);
        return *this;
    }

    Serializer& operator<<(char value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<char*>(buffer_)[offset_] = value;
        offset_ += sizeof(char);
        return *this;
    }

    Serializer& operator<<(int8_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<uint8_t*>(buffer_)[offset_] = value;
        offset_ += sizeof(int8_t);
        return *this;
    }

    Serializer& operator<<(uint8_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<uint8_t*>(buffer_)[offset_] = value;
        offset_ += sizeof(uint8_t);
        return *this;
    }

    Serializer& operator<<(int16_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(int16_t)>();
        *aligned_cast_address<uint16_t>() = holo::core::hton16(value);
        offset_ += sizeof(int16_t);
        return *this;
    }

    Serializer& operator<<(uint16_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(uint16_t)>();
        *aligned_cast_address<uint16_t>() = holo::core::hton16(value);
        offset_ += sizeof(uint16_t);
        return *this;
    }

    Serializer& operator<<(int32_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(int32_t)>();
        *aligned_cast_address<uint32_t>() = holo::core::hton32(value);
        offset_ += sizeof(int32_t);
        return *this;
    }

    Serializer& operator<<(uint32_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(uint32_t)>();
        *aligned_cast_address<uint32_t>() = holo::core::hton32(value);
        offset_ += sizeof(uint32_t);
        return *this;
    }

    Serializer& operator<<(int64_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(int64_t)>();
        *aligned_cast_address<uint64_t>() = holo::core::hton64(value);
        offset_ += sizeof(int64_t);
        return *this;
    }

    Serializer& operator<<(uint64_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(uint64_t)>();
        *aligned_cast_address<uint64_t>() = holo::core::hton64(value);
        offset_ += sizeof(uint64_t);
        return *this;
    }

    Serializer& operator<<(float value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }

        align<sizeof(float)>();
        uint32_t tmp;
        (void)std::memcpy(&tmp, &value, sizeof(float));
        tmp = holo::core::hton32(tmp);
        (void)std::memcpy(aligned_cast_address<uint32_t>(), &tmp, sizeof(float));
        offset_ += sizeof(float);
        return *this;
    }

    Serializer& operator<<(double value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }

        align<sizeof(double)>();
        uint64_t tmp;
        (void)std::memcpy(&tmp, &value, sizeof(double));
        tmp = holo::core::hton64(tmp);
        (void)std::memcpy(aligned_cast_address<uint64_t>(), &tmp, sizeof(double));
        offset_ += sizeof(double);
        return *this;
    }

    Serializer& operator<<(std::string const& value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        (void)std::memcpy(aligned_cast_address<char>(), value.c_str(), value.size() + 1U);
        offset_ += value.size() + 1U;
        return *this;
    }

    template <typename T, typename Allocator>
    Serializer& operator<<(std::vector<T, Allocator> const& value)
    {
        (*this) << static_cast<uint32_t>(value.size()) << holo::serialization::align;
        for (size_t i = 0U; i < value.size(); ++i)
        {
            (*this) << value[i];
        }
        (*this) << holo::serialization::align;
    }

    template <typename T>
    Serializer& operator<<(T const& value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align();
        value.Serialize(*this);
        return *this;
    }

    Serializer& operator<<(manipulator::Align)
    {
        align();
        return *this;
    }

    Serializer& Write(void const* p, size_t size)
    {
        if (offset_ + size > capacity_)
        {
            throw SerializationBufferOverflowException();
        }
        (void)std::memcpy(reinterpret_cast<uint8_t*>(buffer_) + offset_, p, size);
        offset_ += size;
        return *this;
    }

    uint8_t const* GetData() const noexcept
    {
        return reinterpret_cast<uint8_t const*>(buffer_);
    }

    size_t GetCapacity() const noexcept
    {
        return capacity_;
    }

    size_t GetSize() const noexcept
    {
        return offset_;
    }

private:
    template <size_t _ALIGN = ALIGNMENT_VALUE>
    void align() noexcept
    {
        constexpr size_t ALIGN = _ALIGN > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : _ALIGN;
        offset_                = (offset_ + ALIGN - 1U) & (-ALIGN);
    }

    template <typename T>
    T* aligned_cast_address()
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(buffer_) + AlignedSize<ALIGN>(offset_));
    }

    template <typename T,
              typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type* = nullptr>
    bool check_capacity(T)
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return AlignedSize<ALIGN>(AlignedSize<ALIGN>(offset_) + sizeof(T)) <= capacity_;
    }

    template <typename T, typename std::enable_if<std::is_class<T>::value || std::is_union<T>::value>::type* = nullptr>
    bool check_capacity(T const& value)
    {
        size_t constexpr ALIGN =
            AlignOf<T>() == 0U ? ALIGNMENT_VALUE : AlignOf<T>() > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : AlignOf<T>();
        return AlignedSize<ALIGN>(AlignedSize<ALIGN>(offset_) + value.template GetSerializedSize<ALIGN>()) <= capacity_;
    }

    bool check_capacity(std::string const& value)
    {
        return AlignedSize<ALIGNMENT_VALUE>(offset_ + value.size() + 1U) <= capacity_;
    }

    void*  buffer_;
    size_t capacity_;
    size_t offset_;
};

template <size_t Alignment>
class Serializer<false, Alignment>
{
public:
    static bool const   NETWORK_BYTE_ORDER = false;
    static size_t const ALIGNMENT_VALUE    = Alignment;

    Serializer(void* buffer, size_t capacity, size_t offset = 0U)
      : buffer_(buffer), capacity_(capacity), offset_(offset)
    {
        (void)std::memset(reinterpret_cast<uint8_t*>(buffer) + offset, 0, capacity - offset);
    }

    Serializer& operator<<(bool value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<uint8_t*>(buffer_)[offset_] = value;
        offset_ += sizeof(bool);
        return *this;
    }

    Serializer& operator<<(char value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<char*>(buffer_)[offset_] = value;
        offset_ += sizeof(char);
        return *this;
    }

    Serializer& operator<<(int8_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<uint8_t*>(buffer_)[offset_] = value;
        offset_ += sizeof(int8_t);
        return *this;
    }

    Serializer& operator<<(uint8_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        reinterpret_cast<uint8_t*>(buffer_)[offset_] = value;
        offset_ += sizeof(uint8_t);
        return *this;
    }

    Serializer& operator<<(int16_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(int16_t)>();
        *aligned_cast_address<uint16_t>() = value;
        offset_ += sizeof(int16_t);
        return *this;
    }

    Serializer& operator<<(uint16_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(uint16_t)>();
        *aligned_cast_address<uint16_t>() = value;
        offset_ += sizeof(uint16_t);
        return *this;
    }

    Serializer& operator<<(int32_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(int32_t)>();
        *aligned_cast_address<uint32_t>() = value;
        offset_ += sizeof(int32_t);
        return *this;
    }

    Serializer& operator<<(uint32_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(uint32_t)>();
        *aligned_cast_address<uint32_t>() = value;
        offset_ += sizeof(uint32_t);
        return *this;
    }

    Serializer& operator<<(int64_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(int64_t)>();
        *aligned_cast_address<uint64_t>() = value;
        offset_ += sizeof(int64_t);
        return *this;
    }

    Serializer& operator<<(uint64_t value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align<sizeof(uint64_t)>();
        *aligned_cast_address<uint64_t>() = value;
        offset_ += sizeof(uint64_t);
        return *this;
    }

    Serializer& operator<<(float value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }

        align<sizeof(float)>();
        (void)std::memcpy(aligned_cast_address<uint32_t>(), &value, sizeof(float));
        offset_ += sizeof(float);
        return *this;
    }

    Serializer& operator<<(double value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }

        align<sizeof(double)>();
        (void)std::memcpy(aligned_cast_address<uint64_t>(), &value, sizeof(double));
        offset_ += sizeof(double);
        return *this;
    }

    Serializer& operator<<(std::string const& value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        (void)std::memcpy(aligned_cast_address<char>(), value.c_str(), value.size() + 1U);
        offset_ += value.size() + 1U;
        return *this;
    }

    template <typename T, typename Allocator>
    Serializer& operator<<(std::vector<T, Allocator> const& value)
    {
        (*this) << static_cast<uint32_t>(value.size()) << holo::serialization::align;
        for (size_t i = 0U; i < value.size(); ++i)
        {
            (*this) << value[i];
        }
        (*this) << holo::serialization::align;
    }

    template <typename T>
    Serializer& operator<<(T const& value)
    {
        if (!check_capacity(value))
        {
            throw SerializationBufferOverflowException();
        }
        align();
        value.Serialize(*this);
        return *this;
    }

    Serializer& operator<<(manipulator::Align)
    {
        align();
        return *this;
    }

    Serializer& Write(void const* p, size_t size)
    {
        if (offset_ + size > capacity_)
        {
            throw SerializationBufferOverflowException();
        }
        (void)std::memcpy(reinterpret_cast<uint8_t*>(buffer_) + offset_, p, size);
        offset_ += size;
        return *this;
    }

    uint8_t const* GetData() const noexcept
    {
        return reinterpret_cast<uint8_t const*>(buffer_);
    }

    size_t GetCapacity() const noexcept
    {
        return capacity_;
    }

    size_t GetSize() const noexcept
    {
        return offset_;
    }

private:
    template <size_t _ALIGN = ALIGNMENT_VALUE>
    void align() noexcept
    {
        constexpr size_t ALIGN = _ALIGN > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : _ALIGN;
        offset_                = (offset_ + ALIGN - 1U) & (-ALIGN);
    }

    template <typename T>
    T* aligned_cast_address()
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(buffer_) + AlignedSize<ALIGN>(offset_));
    }

    template <typename T,
              typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type* = nullptr>
    bool check_capacity(T)
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return AlignedSize<ALIGN>(AlignedSize<ALIGN>(offset_) + sizeof(T)) <= capacity_;
    }

    template <typename T, typename std::enable_if<std::is_class<T>::value || std::is_union<T>::value>::type* = nullptr>
    bool check_capacity(T const& value)
    {
        size_t constexpr ALIGN =
            AlignOf<T>() == 0U ? ALIGNMENT_VALUE : AlignOf<T>() > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : AlignOf<T>();
        return AlignedSize<ALIGN>(AlignedSize<ALIGN>(offset_) + value.template GetSerializedSize<ALIGN>()) <= capacity_;
    }

    bool check_capacity(std::string const& value)
    {
        return AlignedSize<ALIGNMENT_VALUE>(offset_ + value.size() + 1U) <= capacity_;
    }

    void*  buffer_;
    size_t capacity_;
    size_t offset_;
};
}  // namespace serialization
}  // namespace holo

#endif
