/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file angle.h
 * @brief angle header file
 * @author duyanwei@holomatic.com
 * @date 2019-09-04
 */

#ifndef HOLO_GEOMETRY_ANGLE_H_
#define HOLO_GEOMETRY_ANGLE_H_

#include <cmath>

namespace holo
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 */

/**
 * @brief Convert degree to radian
 *
 * @tparam T float32_t or float64_t
 * @param value angle value in degree
 * @return radian
 */
template <typename T>
T Radian(T value) noexcept
{
    return value / static_cast<T>(180.0) * static_cast<T>(M_PI);
}

/**
 * @brief Convert degree to radian
 *
 * @details the output value is constrained in the range of [0, 2 * PI]
 * @note naming style follows std library, such as std::atan and std::atan2
 * @tparam T float32_t or float64_t
 * @param value angle value in degree
 * @return radian
 */
template <typename T>
T Radian2(T value) noexcept
{
    value   = Radian(value);
    T ratio = static_cast<T>(2.0) * static_cast<T>(M_PI);
    return value - ratio * std::floor(value / ratio);
}

/**
 * @brief Convert radian to degree
 *
 * @tparam T float32_t or float64_t
 * @param value angle value in radian
 * @return degree
 */
template <typename T>
T Degree(T value) noexcept
{
    return value * static_cast<T>(180.0) / static_cast<T>(M_PI);
}

/**
 * @brief Convert radian to degree
 *
 * @details the output value is constrained in the range of [0, 360.0]
 * @note naming style follows std library, such as std::atan and std::atan2
 * @tparam T float32_t or float64_t
 * @param value angle value in radian
 * @return degree
 */
template <typename T>
T Degree2(T value) noexcept
{
    T ratio = static_cast<T>(2.0) * static_cast<T>(M_PI);
    value   = value - ratio * std::floor(value / ratio);
    return Degree(value);
}

/**
 * @}
 *
 */

}  // namespace geometry

// @brief deprecated methods

template <typename T>
[[deprecated]] T Radian(T value) noexcept
{
    return geometry::Radian(value);
}

template <typename T>
[[deprecated]] T Radian2(T value) noexcept
{
    return geometry::Radian2(value);
}

template <typename T>
[[deprecated]] T Degree(T value) noexcept
{
    return geometry::Degree(value);
}

template <typename T>
[[deprecated]] T Degree2(T value) noexcept
{
    return geometry::Degree2(value);
}

}  // namespace holo

#endif  // HOLO_GEOMETRY_ANGLE_H_
