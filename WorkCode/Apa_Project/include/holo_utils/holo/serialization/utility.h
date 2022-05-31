/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file utility.h
 * @brief This header file defines serialization utility functions
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2021-3-23
 */

#ifndef HOLO_SERIALIZATION_UTILITY_H_
#define HOLO_SERIALIZATION_UTILITY_H_

#include <holo/core/types.h>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>

namespace holo
{
namespace serialization
{
/**
 * @brief Calculate minimum @b ALIGN aligned size for data of size @b size.
 *
 * @detail Get minimum aligned size for data of size @b size.
 * For example.
 * If size == 3 and ALIGN == 4, will return 4. @n
 * If size == 3 and ALIGN == 8, will return 8. @n
 * If size == 5 and ALIGN == 4, will return 8. @n
 * If size == 8 and ALIGN == 4, will return 8. @n
 *
 * @tparam ALIGN ALIGN, Must be power of 2.
 * @param size Data size.
 *
 * @return Minimum aligned data size.
 */
template <size_t ALIGN>
constexpr static size_t AlignedSize(size_t size) noexcept
{
    return ((size + ALIGN - 1U) & (-ALIGN));
}

template <typename T>
constexpr size_t AlignOf() noexcept
{
    return alignof(T);
}

template <size_t ALIGN>
constexpr static size_t SerializedSizeInternal(size_t s, std::string const& value) noexcept
{
    return s + value.size() + 1U;
}

template <size_t ALIGN, typename... Args>
constexpr static size_t SerializedSizeInternal(size_t s, std::string const& value, Args&&... args) noexcept
{
    return SerializedSizeInternal<ALIGN>(s + value.size() + 1U, std::forward<Args>(args)...);
}

template <size_t ALIGN, typename T,
          typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type* = nullptr>
constexpr static size_t SerializedSizeInternal(size_t s, T) noexcept
{
    return sizeof(T) > ALIGN ? AlignedSize<ALIGN>(s) + sizeof(T) : AlignedSize<sizeof(T)>(s) + sizeof(T);
}

template <size_t ALIGN, typename T, typename... Args,
          typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type* = nullptr>
constexpr static size_t SerializedSizeInternal(size_t s, T, Args&&... args) noexcept
{
    return sizeof(T) > ALIGN ?
               SerializedSizeInternal<ALIGN>(AlignedSize<ALIGN>(s) + sizeof(T), std::forward<Args>(args)...) :
               SerializedSizeInternal<ALIGN>(AlignedSize<sizeof(T)>(s) + sizeof(T), std::forward<Args>(args)...);
}

template <size_t ALIGN, typename T, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
constexpr static size_t SerializedSizeInternal(size_t s, T const& value) noexcept
{
    return AlignOf<T>() == 0U ? (AlignedSize<ALIGN>(s) + value.template GetSerializedSize<ALIGN>()) :
                                (AlignedSize<AlignOf<T>()>(s) + value.template GetSerializedSize<AlignOf<T>()>());
}

template <size_t ALIGN, typename T, typename... Args, typename std::enable_if<std::is_class<T>::value>::type* = nullptr>
constexpr static size_t SerializedSizeInternal(size_t s, T const& value, Args&&... args) noexcept
{
    return AlignOf<T>() == 0U ?
               SerializedSizeInternal<ALIGN>(AlignedSize<ALIGN>(s) + value.template GetSerializedSize<ALIGN>(),
                                             std::forward<Args>(args)...) :
               SerializedSizeInternal<ALIGN>(AlignedSize<AlignOf<T>()>(s) +
                                                 value.template GetSerializedSize<AlignOf<T>()>(),
                                             std::forward<Args>(args)...);
}

template <size_t ALIGN, typename... Args>
constexpr static size_t SerializedSize(Args&&... args) noexcept
{
    return AlignedSize<ALIGN>(SerializedSizeInternal<ALIGN>(0U, std::forward<Args>(args)...));
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(std::string const& value)
{
    return value.size() + 1U;
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(bool value)
{
    return sizeof(bool);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(char value)
{
    return sizeof(char);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(int8_t value)
{
    return sizeof(int8_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(uint8_t value)
{
    return sizeof(uint8_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(int16_t value)
{
    return sizeof(int16_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(uint16_t value)
{
    return sizeof(uint16_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(int32_t value)
{
    return sizeof(int32_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(uint32_t value)
{
    return sizeof(uint32_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(int64_t value)
{
    return sizeof(int64_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(uint64_t value)
{
    return sizeof(uint64_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(float32_t value)
{
    return sizeof(float32_t);
}

template <size_t ALIGN = 4U>
size_t GetSerializedSize(float64_t value)
{
    return sizeof(float64_t);
}

template <typename T, typename ARCHIVE>
void Serialize(T const& value, ARCHIVE& archive)
{
    archive << value;
}

template <typename T, typename ARCHIVE>
void Deserialize(ARCHIVE& archive, T& value)
{
    archive >> value;
}

namespace manipulator
{
struct Align
{
};
}  // namespace manipulator

extern holo::serialization::manipulator::Align align;

}  // namespace serialization

} /* namespace holo */

#endif
