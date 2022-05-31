/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pow_int.h
 * @brief compile time pow functions
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-06-01
 */

#ifndef HOLO_MATH_MATH_DETAILS_POW_INT_H_
#define HOLO_MATH_MATH_DETAILS_POW_INT_H_

#include <type_traits>
#include <cstddef>

namespace holo
{
namespace math
{
template <size_t N, typename T, typename std::enable_if<(N == 3)>::type* = nullptr>
constexpr T Pow(T base) noexcept
{
    return base * base * base;
}

template <size_t N, typename T, typename std::enable_if<(N == 2)>::type* = nullptr>
constexpr T Pow(T base) noexcept
{
    return base * base;
}

template <size_t N, typename T, typename std::enable_if<(N == 1)>::type* = nullptr>
constexpr T Pow(T base) noexcept
{
    return base;
}

template <size_t N, typename T, typename std::enable_if<(N == 0)>::type* = nullptr>
constexpr T Pow(T) noexcept
{
    return static_cast<T>(1);
}

template <size_t N, typename T, typename std::enable_if<(N > 3) && (N % 2)>::type* = nullptr>
constexpr T Pow(T base) noexcept
{
    return Pow<N / 2>(base * base) * base;
}

template <size_t N, typename T, typename std::enable_if<(N > 3) && !(N % 2)>::type* = nullptr>
constexpr T Pow(T base) noexcept
{
    return Pow<N / 2>(base * base);
}

}  // namespace math
}  // namespace holo

#endif
