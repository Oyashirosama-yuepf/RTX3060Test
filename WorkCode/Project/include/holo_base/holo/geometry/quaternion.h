/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file quaternion.h
 * @brief This header file defines quaternion.
 * @author duyanwei@holomatic.com
 * @date Oct-10-2020
 */

#ifndef HOLO_GEOMETRY_QUATERNION_H_
#define HOLO_GEOMETRY_QUATERNION_H_

#include "./details/quaternion.h"

namespace holo
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 *
 */

template <typename T>
using QuaternionT = details::QuaternionT<T>;

using Quaternionf = details::QuaternionT<float32_t>;
using Quaterniond = details::QuaternionT<float64_t>;
using Quaternion  = details::QuaternionT<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::QuaternionT<T>
 *
 * @tparam T
 */
template <typename T>
using QuaternionT [[deprecated]] = geometry::QuaternionT<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Quaternionf
 *
 */
using Quaternionf [[deprecated]] = geometry::Quaternionf;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Quaterniond
 *
 */
using Quaterniond [[deprecated]] = geometry::Quaterniond;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Quaternion
 *
 */
using Quaternion [[deprecated]] = geometry::Quaternion;

}  // namespace holo

#endif  // HOLO_GEOMETRY_QUATERNION_H_