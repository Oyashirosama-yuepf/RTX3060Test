/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file factorial.h
 * @brief compile time factorial functions
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-06-01
 */

#ifndef HOLO_MATH_MATH_DETAILS_FACTORIAL_H_
#define HOLO_MATH_MATH_DETAILS_FACTORIAL_H_

#include <cstddef>
#include <type_traits>

namespace holo
{
namespace math
{
template <size_t N>
constexpr size_t Factorial()
{
    return N * Factorial<N - 1>();
}

template <>
constexpr size_t Factorial<0>()
{
    return 1U;
}

}  // namespace math
}  // namespace holo

#endif
