/**
 * @file serialization.h
 * @brief This header file defines utility functions for serialization and deserialization.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-10-25
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_UTILS_SERIALIZATION_H_
#define HOLO_UTILS_SERIALIZATION_H_

#include <holo/core/types.h>
#include <holo/utils/serialization.h>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace holo
{
namespace utils
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

template <size_t ALIGN, typename... Args>
constexpr static size_t SerializedSize(Args&&... args) noexcept
{
    return AlignedSize<ALIGN>(SerializedSizeInternal<ALIGN>(0U, std::forward<Args>(args)...));
}

} /* namespace utils */

} /* namespace holo */

#endif

