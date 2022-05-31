/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file deserializer.h
 * @brief This header file defines Deserializer class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2021-3-23
 */

#ifndef HOLO_SERIALIZATION_DESERIALIZER_H_
#define HOLO_SERIALIZATION_DESERIALIZER_H_

#include <holo/core/endian.h>
#include <holo/core/types.h>
#include <cstring>
#include <exception>
#include <string>
#include <type_traits>
#include <vector>
#include "utility.h"

namespace holo
{
namespace serialization
{
template <bool_t IsNetworkByteOrder = true, size_t Alignment = 4U>
class Deserializer;

class DeserializationBufferUnderflowException : public std::exception
{
};

template <size_t Alignment>
class Deserializer<true, Alignment>
{
public:
    static bool const   NETWORK_BYTE_ORDER = true;
    static size_t const ALIGNMENT_VALUE    = Alignment;

    Deserializer(void const* buffer, size_t size, size_t offset = 0) : buffer_(buffer), size_(size), offset_(offset)
    {
    }

    Deserializer& operator>>(bool& value)
    {
        if (!check_size<bool>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<bool const*>(buffer_)[offset_];
        offset_ += sizeof(bool);
        return *this;
    }

    Deserializer& operator>>(char& value)
    {
        if (!check_size<char>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<char const*>(buffer_)[offset_];
        offset_ += sizeof(char);
        return *this;
    }

    Deserializer& operator>>(int8_t& value)
    {
        if (!check_size<int8_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<int8_t const*>(buffer_)[offset_];
        offset_ += sizeof(int8_t);
        return *this;
    }

    Deserializer& operator>>(uint8_t& value)
    {
        if (!check_size<uint8_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<uint8_t const*>(buffer_)[offset_];
        offset_ += sizeof(uint8_t);
        return *this;
    }

    Deserializer& operator>>(int16_t& value)
    {
        if (!check_size<int16_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(int16_t)>();
        value = holo::core::ntoh16(*aligned_cast_address<uint16_t>());
        offset_ += sizeof(int16_t);
        return *this;
    }

    Deserializer& operator>>(uint16_t& value)
    {
        if (!check_size<uint16_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(uint16_t)>();
        value = holo::core::ntoh16(*aligned_cast_address<uint16_t>());
        offset_ += sizeof(uint16_t);
        return *this;
    }

    Deserializer& operator>>(int32_t& value)
    {
        if (!check_size<int32_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(int32_t)>();
        value = holo::core::ntoh32(*aligned_cast_address<uint32_t>());
        offset_ += sizeof(int32_t);
        return *this;
    }

    Deserializer& operator>>(uint32_t& value)
    {
        if (!check_size<uint32_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(uint32_t)>();
        value = holo::core::ntoh32(*aligned_cast_address<uint32_t>());
        offset_ += sizeof(uint32_t);
        return *this;
    }

    Deserializer& operator>>(int64_t& value)
    {
        if (!check_size<int64_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(int64_t)>();
        value = holo::core::ntoh64(*aligned_cast_address<uint64_t>());
        offset_ += sizeof(int64_t);
        return *this;
    }

    Deserializer& operator>>(uint64_t& value)
    {
        if (!check_size<uint64_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(uint64_t)>();
        value = holo::core::ntoh64(*aligned_cast_address<uint64_t>());
        offset_ += sizeof(uint64_t);
        return *this;
    }

    Deserializer& operator>>(float& value)
    {
        if (!check_size<float>())
        {
            throw DeserializationBufferUnderflowException();
        }

        align<sizeof(float)>();
        uint32_t tmp;
        (void)std::memcpy(&tmp, aligned_cast_address<uint32_t>(), sizeof(float));
        tmp = holo::core::ntoh32(tmp);
        (void)std::memcpy(&value, &tmp, sizeof(float));
        offset_ += sizeof(float);
        return *this;
    }

    Deserializer& operator>>(double& value)
    {
        if (!check_size<double>())
        {
            throw DeserializationBufferUnderflowException();
        }

        align<sizeof(double)>();
        uint64_t tmp;
        (void)std::memcpy(&tmp, aligned_cast_address<uint64_t>(), sizeof(double));
        tmp = holo::core::ntoh64(tmp);
        (void)std::memcpy(&value, &tmp, sizeof(double));
        offset_ += sizeof(double);
        return *this;
    }

    Deserializer& operator>>(std::string& value)
    {
        if (std::strlen(aligned_cast_address<char>()) >= size_ - offset_)
        {
            throw DeserializationBufferUnderflowException();
        }
        value = aligned_cast_address<char>();
        offset_ += value.size() + 1U;
        return *this;
    }

    template <typename T, typename Allocator>
    Deserializer& operator>>(std::vector<T, Allocator>& value)
    {
        uint32_t size = 0U;
        (*this) >> size >> holo::serialization::align;
        value.resize(size);
        for (size_t i = 0U; i < size; ++i)
        {
            (*this) >> value[i];
        }
        (*this) >> holo::serialization::align;
    }

    template <typename T>
    Deserializer& operator>>(T& value)
    {
        align();
        value.Deserialize(*this);
        return *this;
    }

    Deserializer& operator>>(manipulator::Align)
    {
        align();
        return *this;
    }

    Deserializer& Read(void* p, size_t size)
    {
        if (offset_ + size > size_)
        {
            throw DeserializationBufferUnderflowException();
        }
        (void)std::memcpy(p, reinterpret_cast<uint8_t const*>(buffer_) + offset_, size);
        offset_ += size;
        return *this;
    }

    Deserializer& Skip(size_t size)
    {
        if (offset_ + size > size_)
        {
            throw DeserializationBufferUnderflowException();
        }
        offset_ += size;
        return *this;
    }

    uint8_t const* GetData() const noexcept
    {
        return reinterpret_cast<uint8_t const*>(buffer_);
    }

    size_t GetSize() const noexcept
    {
        return size_;
    }

    size_t GetOffset() const noexcept
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
    T const* aligned_cast_address()
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return reinterpret_cast<T const*>(reinterpret_cast<uint8_t const*>(buffer_) + AlignedSize<ALIGN>(offset_));
    }

    template <typename T,
              typename = typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type>
    bool check_size()
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return AlignedSize<ALIGN>(AlignedSize<ALIGN>(offset_) + sizeof(T)) <= size_;
    }

    void const* buffer_;
    size_t      size_;
    size_t      offset_;
};
template <size_t Alignment>
class Deserializer<false, Alignment>
{
public:
    static bool const   NETWORK_BYTE_ORDER = true;
    static size_t const ALIGNMENT_VALUE    = Alignment;

    Deserializer(void const* buffer, size_t size, size_t offset = 0) : buffer_(buffer), size_(size), offset_(offset)
    {
    }

    Deserializer& operator>>(bool& value)
    {
        if (!check_size<bool>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<bool const*>(buffer_)[offset_];
        offset_ += sizeof(bool);
        return *this;
    }

    Deserializer& operator>>(char& value)
    {
        if (!check_size<char>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<char const*>(buffer_)[offset_];
        offset_ += sizeof(char);
        return *this;
    }

    Deserializer& operator>>(int8_t& value)
    {
        if (!check_size<int8_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<int8_t const*>(buffer_)[offset_];
        offset_ += sizeof(int8_t);
        return *this;
    }

    Deserializer& operator>>(uint8_t& value)
    {
        if (!check_size<uint8_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        value = reinterpret_cast<uint8_t const*>(buffer_)[offset_];
        offset_ += sizeof(uint8_t);
        return *this;
    }

    Deserializer& operator>>(int16_t& value)
    {
        if (!check_size<int16_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(int16_t)>();
        value = *aligned_cast_address<uint16_t>();
        offset_ += sizeof(int16_t);
        return *this;
    }

    Deserializer& operator>>(uint16_t& value)
    {
        if (!check_size<uint16_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(uint16_t)>();
        value = *aligned_cast_address<uint16_t>();
        offset_ += sizeof(uint16_t);
        return *this;
    }

    Deserializer& operator>>(int32_t& value)
    {
        if (!check_size<int32_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(int32_t)>();
        value = *aligned_cast_address<uint32_t>();
        offset_ += sizeof(int32_t);
        return *this;
    }

    Deserializer& operator>>(uint32_t& value)
    {
        if (!check_size<uint32_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(uint32_t)>();
        value = *aligned_cast_address<uint32_t>();
        offset_ += sizeof(uint32_t);
        return *this;
    }

    Deserializer& operator>>(int64_t& value)
    {
        if (!check_size<int64_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(int64_t)>();
        value = *aligned_cast_address<uint64_t>();
        offset_ += sizeof(int64_t);
        return *this;
    }

    Deserializer& operator>>(uint64_t& value)
    {
        if (!check_size<uint64_t>())
        {
            throw DeserializationBufferUnderflowException();
        }
        align<sizeof(uint64_t)>();
        value = *aligned_cast_address<uint64_t>();
        offset_ += sizeof(uint64_t);
        return *this;
    }

    Deserializer& operator>>(float& value)
    {
        if (!check_size<float>())
        {
            throw DeserializationBufferUnderflowException();
        }

        align<sizeof(float)>();
        (void)std::memcpy(&value, aligned_cast_address<uint32_t>(), sizeof(float));
        offset_ += sizeof(float);
        return *this;
    }

    Deserializer& operator>>(double& value)
    {
        if (!check_size<double>())
        {
            throw DeserializationBufferUnderflowException();
        }

        align<sizeof(double)>();
        (void)std::memcpy(&value, aligned_cast_address<uint64_t>(), sizeof(double));
        offset_ += sizeof(double);
        return *this;
    }

    Deserializer& operator>>(std::string& value)
    {
        if (std::strlen(aligned_cast_address<char>()) >= size_ - offset_)
        {
            throw DeserializationBufferUnderflowException();
        }
        value = aligned_cast_address<char>();
        offset_ += value.size() + 1U;
        return *this;
    }

    template <typename T, typename Allocator>
    Deserializer& operator>>(std::vector<T, Allocator>& value)
    {
        uint32_t size = 0U;
        (*this) >> size >> holo::serialization::align;
        value.resize(size);
        for (size_t i = 0U; i < size; ++i)
        {
            (*this) >> value[i];
        }
        (*this) >> holo::serialization::align;
    }

    template <typename T>
    Deserializer& operator>>(T& value)
    {
        align();
        value.Deserialize(*this);
        return *this;
    }

    Deserializer& operator>>(manipulator::Align)
    {
        align();
        return *this;
    }

    Deserializer& Read(void* p, size_t size)
    {
        if (offset_ + size > size_)
        {
            throw DeserializationBufferUnderflowException();
        }
        (void)std::memcpy(p, reinterpret_cast<uint8_t const*>(buffer_) + offset_, size);
        offset_ += size;
        return *this;
    }

    Deserializer& Skip(size_t size)
    {
        if (offset_ + size > size_)
        {
            throw DeserializationBufferUnderflowException();
        }
        offset_ += size;
        return *this;
    }

    uint8_t const* GetData() const noexcept
    {
        return reinterpret_cast<uint8_t const*>(buffer_);
    }

    size_t GetSize() const noexcept
    {
        return size_;
    }

    size_t GetOffset() const noexcept
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
    T const* aligned_cast_address()
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return reinterpret_cast<T const*>(reinterpret_cast<uint8_t const*>(buffer_) + AlignedSize<ALIGN>(offset_));
    }

    template <typename T,
              typename = typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type>
    bool check_size()
    {
        size_t constexpr ALIGN = sizeof(T) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T);
        return AlignedSize<ALIGN>(AlignedSize<ALIGN>(offset_) + sizeof(T)) <= size_;
    }

    void const* buffer_;
    size_t      size_;
    size_t      offset_;
};

}  // namespace serialization
}  // namespace holo

#endif
