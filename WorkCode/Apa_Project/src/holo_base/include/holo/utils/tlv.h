/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tlv.h
 * @brief This header file defines TlvT Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2020-06-21
 */

#ifndef HOLO_UTILS_TLV_H_
#define HOLO_UTILS_TLV_H_

#include <cassert>
#include <cstring>
#include <type_traits>

#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/os/endian.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace utils
{
/**
 * @addtogroup utils
 * {
 */

template <typename Tlv, typename Tlv::TypeType END = 0U>
class TlvSequence;

/**
 * @brief TlvT class defines a Type-Length-Value tuple.
 *
 * @details TlvT is a Type-Length-Value tuple. This data structure can be used to represent dynamic data types. @n
 * TlvT consist of three parts: Type, Length and Value. @n
 * Type: Type of data. @n
 * Length: Length of tlv value. (Not the whole Tlv block) @n
 * Value: Value of data. @n
 *
 * @tparam T Type of TlvT type.
 * @tparam L Type of TlvT length.
 * @tparam IsNetworkByteOrder Tlv data byte order
 * @tparam Alignment Alignment of tlv data.
 */
template <typename T, typename L, bool_t IsNetworkByteOrder = true, size_t Alignment = 4U,
          typename std::enable_if<std::is_integral<T>::value && std::is_integral<L>::value>::type* = nullptr>
class TlvT
{
public:
    using TypeType   = T;
    using LengthType = L;

public:
    static size_t const ALIGNMENT_VALUE = Alignment;

    static size_t const LENGTH_OFFSET = holo::serialization::AlignedSize < (sizeof(L) < ALIGNMENT_VALUE) ?
                                            sizeof(L) :
                                            ALIGNMENT_VALUE > (sizeof(T));
    static size_t const VALUE_OFFSET = holo::serialization::AlignedSize<ALIGNMENT_VALUE>(LENGTH_OFFSET + sizeof(L));

    /**
     * @brief Default construct
     *
     * @exceptsafe No throw
     */
    TlvT(uint8_t* p, size_t size) noexcept : value_(p), size_(size)
    {
    }

    bool_t operator==(TlvT const& other) const noexcept
    {
        return other.value_ == value_;
    }

    bool_t operator!=(TlvT const& other) const noexcept
    {
        return !(*this == other);
    }

    /**
     * @brief Get type of TlvT.
     *
     * @return Type of Tlv.
     *
     * @exceptsafe No throw
     */
    TypeType GetType() const noexcept
    {
        TypeType v;
        read(value_, v);
        return v;
    }

    /**
     * @brief Set Tlv Type
     *
     * @param type Type value
     */
    void SetType(TypeType type) noexcept
    {
        write(value_, type);
        write(value_ + LENGTH_OFFSET, static_cast<LengthType>(0U));
    }

    /**
     * @brief Get length of Tlv value part.
     *
     * @return Length of Tlv value part.
     *
     * @exceptsafe No throw
     */
    LengthType GetLength() const noexcept
    {
        LengthType v;
        read(value_ + LENGTH_OFFSET, v);
        return v;
    }

    /**
     * @brief Get tlv value as V type
     *
     * @tparam V Value type
     *
     * @return Value type
     *
     * @throws holo::exception::OutOfRangeException if Tlv length < sizeof V.
     */
    template <typename V>
    V GetValue() const
    {
        V      v;
        size_t actual_size = extractValues(VALUE_OFFSET, v);
        if (actual_size > GetLength())
        {
            throw holo::exception::OutOfRangeException("");
        }
        return v;
    }

    /**
     * @brief Set Tlv value and tlv length
     *
     * @tparam V Value type
     * @param value Value
     */
    template <typename V>
    void SetValue(V value)
    {
        SetValues(value);
    }

    /**
     * @brief Set tlv
     *
     * @tparam Args value types.
     * @param type Type of tlv
     * @param args Values of tlv.
     */
    template <typename... Args>
    void Set(TypeType type, Args&&... args)
    {
        size_t expected_size = getValueSize(VALUE_OFFSET, std::forward<Args>(args)...);
        if (expected_size > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        write(value_, type);
        write(value_ + LENGTH_OFFSET, static_cast<LengthType>(assignValues(VALUE_OFFSET, std::forward<Args>(args)...)));
        assert(GetLength() == expected_size);
    }

    /**
     * @brief Set tlv values
     *
     * @tparam Args Value types
     * @param[in] args values
     */
    template <typename... Args>
    void SetValues(Args&&... args)
    {
        size_t expected_size = getValueSize(VALUE_OFFSET, std::forward<Args>(args)...);
        if (expected_size > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        write(value_ + LENGTH_OFFSET, static_cast<LengthType>(assignValues(VALUE_OFFSET, std::forward<Args>(args)...)));
        assert(GetLength() == expected_size);
    }

    /**
     * @brief Get tlv values
     *
     * @tparam Args Value types
     * @param[out] args values
     */
    template <typename... Args>
    void GetValues(Args&&... args) const
    {
        size_t actual_size = extractValues(VALUE_OFFSET, std::forward<Args>(args)...);
        if (actual_size > GetLength())
        {
            throw holo::exception::OutOfRangeException("");
        }
    }

    /**
     * @brief Check if Tlv block is valid
     *
     * @return True if tlv block is a valid block otherwise false
     */
    bool_t IsValid() const noexcept
    {
        return size_ >= VALUE_OFFSET;
    }

    template <typename Tlv, typename Tlv::TypeType END>
    friend class TlvSequence<Tlv, END>::iterator;

    template <typename Tlv, typename Tlv::TypeType END>
    friend class TlvSequence<Tlv, END>::const_iterator;

protected:
    /**
     * @brief Write value to buffer
     *
     * @tparam V Value type
     * @param p pointer to buffer
     * @param value value
     */
    template <typename V, typename std::enable_if<sizeof(V) == 1U>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        *p = static_cast<uint8_t>(value);
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 2U) && IsNetworkByteOrder>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        value = holo::os::hton16(value);
        std::memcpy(p, &value, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 4U) && IsNetworkByteOrder &&
                                                  std::is_integral<V>::value>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        value = holo::os::hton32(value);
        std::memcpy(p, &value, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 8U) && IsNetworkByteOrder &&
                                                  std::is_integral<V>::value>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        value = holo::os::hton64(value);
        std::memcpy(p, &value, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 4U) && IsNetworkByteOrder &&
                                                  std::is_floating_point<V>::value>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        uint32_t tmp = 0U;
        std::memcpy(&tmp, &value, sizeof(V));
        tmp = holo::os::hton32(tmp);
        std::memcpy(p, &tmp, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 8U) && IsNetworkByteOrder &&
                                                  std::is_floating_point<V>::value>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        uint64_t tmp = 0U;
        std::memcpy(&tmp, &value, sizeof(V));
        tmp = holo::os::hton64(tmp);
        std::memcpy(p, &tmp, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 2U) && !IsNetworkByteOrder>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        std::memcpy(p, &value, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 4U) && !IsNetworkByteOrder>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        std::memcpy(p, &value, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 8U) && !IsNetworkByteOrder>::type* = nullptr>
    void write(uint8_t* p, V value) noexcept
    {
        std::memcpy(p, &value, sizeof(V));
    }

    /**
     * @brief Read value from buffer
     *
     * @tparam V Value type
     * @param p pointer to buffer
     * @param value value
     */
    template <typename V, typename std::enable_if<sizeof(V) == 1U>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        value = static_cast<V>(*p);
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 2U) && IsNetworkByteOrder>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        std::memcpy(&value, p, sizeof(V));
        value = holo::os::ntoh16(value);
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 4U) && IsNetworkByteOrder &&
                                                  std::is_integral<V>::value>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        std::memcpy(&value, p, sizeof(V));
        value = holo::os::ntoh32(value);
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 8U) && IsNetworkByteOrder &&
                                                  std::is_integral<V>::value>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        std::memcpy(&value, p, sizeof(V));
        value = holo::os::ntoh64(value);
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 4U) && IsNetworkByteOrder &&
                                                  std::is_floating_point<V>::value>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        uint32_t tmp = 0U;
        std::memcpy(&tmp, p, sizeof(V));
        tmp = holo::os::ntoh32(tmp);
        std::memcpy(&value, &tmp, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 8U) && IsNetworkByteOrder &&
                                                  std::is_floating_point<V>::value>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        uint64_t tmp = 0U;
        std::memcpy(&tmp, p, sizeof(V));
        tmp = holo::os::ntoh64(tmp);
        std::memcpy(&value, &tmp, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 2U) && !IsNetworkByteOrder>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        std::memcpy(&value, p, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 4U) && !IsNetworkByteOrder>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        std::memcpy(&value, p, sizeof(V));
    }

    template <typename V, typename std::enable_if<(sizeof(V) == 8U) && !IsNetworkByteOrder>::type* = nullptr>
    void read(uint8_t* p, V& value) const noexcept
    {
        std::memcpy(&value, p, sizeof(V));
    }

    /**
     * @brief Assign scalar type
     *
     * @tparam T1 Scalar type
     * @tparam Args Rest of argument types
     * @param offset write offset
     * @param v1 value
     * @param args rest of args
     *
     * @return Bytes wrote to buffer of v1 and args
     */
    template <
        typename T1, typename... Args,
        typename std::enable_if<std::is_arithmetic<typename std::remove_reference<T1>::type>::value>::type* = nullptr>
    size_t assignValues(size_t offset, T1&& v1, Args&&... args) noexcept
    {
        size_t const align_size = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        write(value_ + holo::serialization::AlignedSize<align_size>(offset), v1);
        return assignValues(holo::serialization::AlignedSize<align_size>(offset) + sizeof(T1), std::forward<Args>(args)...);
    }

    /**
     * @brief Assign array of scalar type
     *
     * @tparam T1 Scalar type
     * @tparam T2 size type
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param v1 Scalar array
     * @param v2 Size of array
     * @param args Rest of args
     *
     * @return Bytes wrote to buffer of v1 v2 and args
     */
    template <
        typename T1, typename T2, typename... Args,
        typename std::enable_if<std::is_arithmetic<typename std::remove_reference<T1>::type>::value &&
                                std::is_integral<typename std::remove_reference<T2>::type>::value>::type* = nullptr>
    size_t assignValues(size_t offset, T1* v1, T2&& v2, Args&&... args) noexcept
    {
        size_t const align_size  = sizeof(LengthType) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(LengthType);
        size_t const align_size2 = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        offset                   = holo::serialization::AlignedSize<align_size>(offset);
        write(value_ + offset, static_cast<LengthType>(v2));
        offset = holo::serialization::AlignedSize<align_size2>(offset + sizeof(LengthType));
        for (size_t i = 0U; i < static_cast<LengthType>(v2); ++i)
        {
            write(value_ + offset, v1[i]);
            offset += sizeof(T1);
        }
        return assignValues(offset, std::forward<Args>(args)...);
    }

    /**
     * @brief Assign string type
     *
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param v1 String value
     * @param args Rest of args
     *
     * @return Bytes wrote to buffer of v1 and args
     */
    template <typename... Args>
    size_t assignValues(size_t offset, std::string const& v1, Args&&... args) noexcept
    {
        std::copy(v1.cbegin(), v1.cend(), value_ + holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset));
        value_[holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) + v1.size()] = 0U;
        return assignValues(holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) + v1.size() + 1U,
                            std::forward<Args>(args)...);
    }

    /**
     * @brief Assign raw string type
     *
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param v1 Pointer to raw string
     * @param args Rest of args
     *
     * @return Bytes wrote to buffer of v1 and args
     */
    template <typename... Args>
    size_t assignValues(size_t offset, char* const& v1, Args&&... args) noexcept
    {
        offset   = holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset);
        size_t i = 0U;
        while (v1[i] != '\0')
        {
            ++i;
        }
        std::memcpy(value_ + offset, v1, i + 1U);
        return assignValues(holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) + i + 1U, std::forward<Args>(args)...);
    }

    /**
     * @brief Assign empty value
     *
     * @param offset Write offset
     *
     * @return Bytes wrote to buffer
     */
    size_t assignValues(size_t offset) noexcept
    {
        return holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) - VALUE_OFFSET;
    }

    /**
     * @brief Extract scalar type from buffer
     *
     * @tparam T1 Scalar type
     * @tparam Args Rest of argument types
     * @param offset Read offset
     * @param v1 Value
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer of v1 and args
     */
    template <
        typename T1, typename... Args,
        typename std::enable_if<std::is_lvalue_reference<T1&&>::value &&
                                std::is_arithmetic<typename std::remove_reference<T1>::type>::value>::type* = nullptr>
    constexpr size_t extractValues(size_t offset, T1&& v1, Args&&... args) const noexcept
    {
        size_t const align_size = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        read(value_ + holo::serialization::AlignedSize<align_size>(offset), v1);
        return extractValues(holo::serialization::AlignedSize<align_size>(offset) + sizeof(T1), std::forward<Args>(args)...);
    }

    /**
     * @brief Extract array of scalar from buffer
     *
     * @tparam T1 Scalar type
     * @tparam T2 size type
     * @tparam Args Rest of argument types
     * @param offset Read offset
     * @param v1 Pointer to array
     * @param v2 Size of array
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer of v1 v2 and args
     */
    template <
        typename T1, typename T2, typename... Args,
        typename std::enable_if<std::is_lvalue_reference<T2&&>::value &&
                                std::is_arithmetic<typename std::remove_reference<T1>::type>::value &&
                                std::is_integral<typename std::remove_reference<T2>::type>::value>::type* = nullptr>
    constexpr size_t extractValues(size_t offset, T1* v1, T2&& v2, Args&&... args) const noexcept
    {
        size_t const align_size  = sizeof(LengthType) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(LengthType);
        size_t const align_size2 = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        offset                   = holo::serialization::AlignedSize<align_size>(offset);
        LengthType size          = 0U;
        read(value_ + offset, size);
        v2     = size;
        offset = holo::serialization::AlignedSize<align_size2>(offset + sizeof(LengthType));
        for (size_t i = 0U; i < size; ++i)
        {
            read(value_ + offset, v1[i]);
            offset += sizeof(T1);
        }
        return extractValues(holo::serialization::AlignedSize<align_size>(offset), std::forward<Args>(args)...);
    }

    /**
     * @brief Extract string type from buffer
     *
     * @tparam Args Rest of argument types
     * @param offset Read offset
     * @param v1 String value
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer of v1 and args
     */
    template <typename... Args>
    constexpr size_t extractValues(size_t offset, std::string& v1, Args&&... args) const noexcept
    {
        size_t const start = holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset);
        size_t       size  = 0U;
        while (value_[start + size] != 0)
        {
            ++size;
        }
        v1.resize(size);
        std::copy(value_ + start, value_ + start + size, v1.begin());
        return extractValues(start + size + 1U, std::forward<Args>(args)...);
    }

    /**
     * @brief Extract raw string from buffer
     *
     * @tparam Args Rest of argument types
     * @param offset Read offset
     * @param v1 Value
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer of v1 and args
     */
    template <typename... Args>
    constexpr size_t extractValues(size_t offset, char* v1, Args&&... args) const noexcept
    {
        size_t const start = holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset);
        size_t       size  = 0U;
        while (value_[start + size] != 0)
        {
            ++size;
        }
        std::memcpy(v1, value_ + start, size + 1U);
        return extractValues(start + size + 1U, std::forward<Args>(args)...);
    }

    /**
     * @brief Skip scalar type from buffer
     *
     * @tparam T1 Scalar type
     * @tparam Args Rest of argument types
     * @param offset Read offset
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer
     */
    template <
        typename T1, typename... Args,
        typename std::enable_if<std::is_rvalue_reference<T1&&>::value &&
                                std::is_arithmetic<typename std::remove_reference<T1>::type>::value>::type* = nullptr>
    constexpr size_t extractValues(size_t offset, T1&&, Args&&... args) const noexcept
    {
        size_t const align_size = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        return extractValues(holo::serialization::AlignedSize<align_size>(offset) + sizeof(T1), std::forward<Args>(args)...);
    }

    /**
     * @brief Skip array of scalar from buffer
     *
     * @tparam T1 Scalar type
     * @tparam T2 size type
     * @tparam Args Rest of argument types
     * @param offset Read offset
     * @param v1 Pointer to array
     * @param v2 Size of array
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer
     */
    template <
        typename T1, typename T2, typename... Args,
        typename std::enable_if<std::is_rvalue_reference<T2&&>::value &&
                                std::is_arithmetic<typename std::remove_reference<T1>::type>::value &&
                                std::is_integral<typename std::remove_reference<T2>::type>::value>::type* = nullptr>
    constexpr size_t extractValues(size_t offset, T1*, T2&&, Args&&... args) const noexcept
    {
        size_t const align_size  = sizeof(LengthType) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(LengthType);
        size_t const align_size2 = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        offset                   = holo::serialization::AlignedSize<align_size>(offset);
        LengthType size          = 0U;
        read(value_ + offset, size);
        offset = holo::serialization::AlignedSize<align_size2>(offset + sizeof(LengthType));
        offset += sizeof(T1) * size;
        return extractValues(holo::serialization::AlignedSize<align_size>(offset), std::forward<Args>(args)...);
    }

    /**
     * @brief Skip string type from buffer
     *
     * @tparam Args Rest of argument types
     * @param v1 String value
     * @param args Rest of arguments
     *
     * @return Bytes read from buffer
     */
    template <typename... Args>
    constexpr size_t extractValues(size_t offset, std::string&&, Args&&... args) const noexcept
    {
        size_t const start = holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset);
        size_t       size  = 0U;
        while (value_[start + size] != 0)
        {
            ++size;
        }
        return extractValues(holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) + size + 1U,
                             std::forward<Args>(args)...);
    }

    /**
     * @brief Extract empty values from buffer
     *
     * @param offset Read offset
     *
     * @return Bytes read from buffer
     */
    constexpr size_t extractValues(size_t offset) const noexcept
    {
        return holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) - VALUE_OFFSET;
    }

    /**
     * @brief Get size of buffer needed to assign values
     *
     * @tparam T1 Type of current value
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param args Rest of arguments
     *
     * @return Required buffer size
     */
    template <
        typename T1, typename... Args,
        typename std::enable_if<std::is_arithmetic<typename std::remove_reference<T1&&>::type>::value>::type* = nullptr>
    constexpr size_t getValueSize(size_t offset, T1&&, Args&&... args) const noexcept
    {
        size_t const align_size = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        return getValueSize(holo::serialization::AlignedSize<align_size>(offset) + sizeof(T1), std::forward<Args>(args)...);
    }

    /**
     * @brief Get size of buffer need to assign values
     *
     * @tparam T1 Pointer to array
     * @tparam T2 Array size type
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param v2 Size value
     * @param args Rest of arguments
     *
     * @return Required buffer size
     */
    template <
        typename T1, typename T2, typename... Args,
        typename std::enable_if<std::is_arithmetic<typename std::remove_reference<T1>::type>::value &&
                                std::is_integral<typename std::remove_reference<T2>::type>::value>::type* = nullptr>
    constexpr size_t getValueSize(size_t offset, T1*, T2&& v2, Args&&... args) const noexcept
    {
        size_t const align_size  = sizeof(LengthType) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(LengthType);
        size_t const align_size2 = sizeof(T1) > ALIGNMENT_VALUE ? ALIGNMENT_VALUE : sizeof(T1);
        offset                   = holo::serialization::AlignedSize<align_size>(offset);
        offset                   = holo::serialization::AlignedSize<align_size2>(offset + sizeof(LengthType));
        offset += sizeof(T1) * static_cast<LengthType>(v2);
        return getValueSize(offset, std::forward<Args>(args)...);
    }

    /**
     * @brief Get size of buffer need to assign values
     *
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param v1 String value
     * @param args Rest of arguments
     *
     * @return Required buffer size
     */
    template <typename... Args>
    constexpr size_t getValueSize(size_t offset, std::string const& v1, Args&&... args) const noexcept
    {
        return getValueSize(holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) + v1.size() + 1U,
                            std::forward<Args>(args)...);
    }

    /**
     * @brief Get size of buffer need to assign values
     *
     * @tparam Args Rest of argument types
     * @param offset Write offset
     * @param v1 Pointer to char buffer
     * @param args Rest of arguments
     *
     * @return Required buffer size
     */
    template <typename... Args>
    constexpr size_t getValueSize(size_t offset, char* v1, Args&&... args) const noexcept
    {
        return getValueSize(holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) + std::strlen(v1) + 1U,
                            std::forward<Args>(args)...);
    }

    /**
     * @brief Get size of buffer need to assign values
     *
     * @param offset Write offset
     *
     * @return Required buffer size
     */
    constexpr size_t getValueSize(size_t offset) const noexcept
    {
        return holo::serialization::AlignedSize<ALIGNMENT_VALUE>(offset) - VALUE_OFFSET;
    }

private:
    uint8_t* value_;  // base pointer to tlv block
    size_t   size_;   // buffer size
};

template <typename Tlv, typename Tlv::TypeType END>
class TlvSequence
{
public:
    using value_type      = Tlv;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;
    template <bool_t CONST = false>
    class Iterator;
    using iterator       = Iterator<false>;
    using const_iterator = Iterator<true>;

    using TypeType                        = typename Tlv::TypeType;
    using LengthType                      = typename Tlv::LengthType;
    static size_t const   ALIGNMENT_VALUE = Tlv::ALIGNMENT_VALUE;
    static TypeType const END_TYPE_VALUE  = END;

    /**
     * @brief Default constructor
     */
    TlvSequence() noexcept : base_(nullptr), size_(0U)
    {
    }

    /**
     * @brief Construct with buffer address and buffer size
     *
     * @param base buffer base address
     * @param size size of buffer
     */
    TlvSequence(uint8_t* base, size_t size) noexcept : base_(base), size_(size)
    {
    }

    /**
     * @brief Get length of tlv sequence.
     *
     * @return Tlv sequence length or 0U if tlv sequence is malformed.
     */
    size_t GetLength() const noexcept
    {
        size_t size = 0U;
        auto   iter = begin();
        while (iter->GetType() != END_TYPE_VALUE)
        {
            size += Tlv::VALUE_OFFSET;
            size += iter->GetLength();
            if (size > size_)
            {
                return 0U;
            }
            ++iter;
        }
        size += Tlv::VALUE_OFFSET;
        return size > size_ ? 0U : size;
    }

    uint8_t const* GetData() const noexcept
    {
        return base_;
    }

    /**
     * @brief Get iterator to first tlv
     *
     * @return iterator
     */
    iterator begin() noexcept
    {
        return iterator(base_, size_);
    }

    /**
     * @brief Get iterator to the end
     *
     * @return iterator to the end
     */
    iterator end() noexcept
    {
        return iterator(base_ + size_, 0);
    }

    /**
     * @brief Get iterator to first tlv
     *
     * @return iterator
     */
    const_iterator begin() const noexcept
    {
        return const_iterator(base_, size_);
    }

    /**
     * @brief Get iterator to the end
     *
     * @return iterator to the end
     */
    const_iterator end() const noexcept
    {
        return const_iterator(base_ + size_, 0);
    }

    /**
     * @brief Get iterator to first tlv
     *
     * @return iterator
     */
    const_iterator cbegin() const noexcept
    {
        return const_iterator(base_, size_);
    }

    /**
     * @brief Get iterator to the end
     *
     * @return iterator to the end
     */
    const_iterator cend() const noexcept
    {
        return const_iterator(base_ + size_, 0);
    }

    /**
     * @brief Forward iterator of TlvSequence
     *
     * @tparam CONST Whether it is a const iterator.
     */
    template <bool_t CONST>
    class Iterator
    {
    public:
        using difference_type = TlvSequence::difference_type;
        using value_type      = TlvSequence::value_type;
        using reference       = typename std::conditional<CONST, typename TlvSequence::const_reference,
                                                    typename TlvSequence::reference>::type;
        using pointer =
            typename std::conditional<CONST, typename TlvSequence::const_pointer, typename TlvSequence::pointer>::type;
        using iterator_category = std::forward_iterator_tag;

        /**
         * @brief Construct with tlv pointer
         *
         * @param p_tlv Pointer to base address of a Tlv.
         */
        Iterator(uint8_t* buffer, size_t size) noexcept : tlv_(buffer, size)
        {
        }

        /**
         * @brief  Check if two iterators are equal.
         *
         * @tparam InputConst Whether input iterator is a const iterator.
         * @param other The input iterator.
         *
         * @return Whether the two iterators are pointing to the same tlv.
         */
        template <bool_t InputConst>
        bool_t operator==(Iterator<InputConst> const& other) const noexcept
        {
            if (other->size_ < value_type::VALUE_OFFSET || other->GetType() == END_TYPE_VALUE)
            {
                if ((*this)->GetType() == END_TYPE_VALUE || tlv_.size_ < value_type::VALUE_OFFSET)
                {
                    return true;
                }
            }
            return tlv_ == other.tlv_;
        }

        /**
         * @brief  Check if two iterators are not equal.
         *
         * @tparam InputConst Whether input iterator is a const iterator.
         * @param other The input iterator.
         *
         * @return Whether the two iterators are pointing to different tlvs.
         */
        template <bool_t InputConst>
        bool_t operator!=(Iterator<InputConst> const& other) const noexcept
        {
            return !(*this == other);
        }

        /**
         * @brief Prefix increament operator
         *
         * @return iterator pointing to the next tlv block.
         */
        Iterator& operator++() noexcept
        {
            size_t offset = value_type::VALUE_OFFSET + tlv_.GetLength();
            if (offset > tlv_.size_)
            {
                tlv_.value_ += tlv_.size_;
                tlv_.size_ = 0U;
            }
            else
            {
                tlv_.value_ += offset;
                tlv_.size_ -= offset;
            }
            return *this;
        }

        /**
         * @brief Surfix increament operator.
         *
         * @param int Parameter used for function polymorphism.
         *
         * @return iterator pointing to current tlv block.
         */
        Iterator operator++(int)
        {
            Iterator tmp(*this);
            size_t   offset = value_type::VALUE_OFFSET + tlv_.GetLength();
            if (offset > tlv_.size_)
            {
                tlv_.value_ += tlv_.size_;
                tlv_.size_ = 0U;
            }
            else
            {
                tlv_.value_ += offset;
                tlv_.size_ -= offset;
            }
            return tmp;
        }

        /**
         * @brief Dereferencing operator
         *
         * @return reference to the tlv pointed by this iterator.
         */
        reference operator*() noexcept
        {
            return tlv_;
        }

        /**
         * @brief Dereferencing operator
         *
         * @return reference to the tlv pointed by this iterator.
         */
        reference operator*() const noexcept
        {
            return tlv_;
        }

        /**
         * @brief Access member via iterator.
         *
         * @return Pointer to tlv.
         */
        pointer operator->() noexcept
        {
            return &tlv_;
        }

        /**
         * @brief Access member via iterator.
         *
         * @return Pointer to tlv.
         */
        pointer operator->() const noexcept
        {
            return &tlv_;
        }

        friend class Iterator<!CONST>;

    private:
        Tlv tlv_;
    };

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const
    {
        size_t size = GetLength();
        return size == 0 ? holo::serialization::AlignedSize<ALIGN>(sizeof(TypeType) + sizeof(LengthType)) : size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        size_t size = GetLength();
        if (size == 0)
        {
            serializer << TypeType(END_TYPE_VALUE) << LengthType(0);
        }
        else
        {
            serializer.Write(base_, size);
        }
        serializer << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        TypeType type;
        LengthType length;
        deserializer >> type >> length;
        while(type != END_TYPE_VALUE)
        {
            deserializer.Skip(length);
            deserializer >> type >> length;
        }
        if(base_ == nullptr)
        {
            base_ = const_cast<uint8_t*>(deserializer.GetData());
            size_ = deserializer.GetOffset();
        }
        else
        {
            if(deserializer.GetOffset() > size_)
            {
                throw holo::exception::BadAllocException();
            }
            std::memcpy(base_, deserializer.GetData(), deserializer.GetOffset());
        }
        deserializer >> holo::serialization::align;
    }

private:
    uint8_t* base_;  // base pointer to tlv sequence
    size_t   size_;  // size of base buffer
};

/**
 * @}
 */

}  // namespace utils
}  // namespace holo

#endif

