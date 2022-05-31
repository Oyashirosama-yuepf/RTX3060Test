/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose3.h
 * @brief This header file defines pose in 3D.
 * @author duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_POSE3_H_
#define HOLO_GEOMETRY_POSE3_H_

#include "./details/pose3.h"

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
using Pose3T = details::Pose3T<T>;

using Pose3f = details::Pose3T<float32_t>;
using Pose3d = details::Pose3T<float64_t>;
using Pose3  = details::Pose3T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Pose3T<T>
 *
 * @tparam T
 */
template <typename T>
using Pose3T [[deprecated]] = geometry::Pose3T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Pose3f
 *
 */
using Pose3f [[deprecated]] = geometry::Pose3f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Pose3d
 *
 */
using Pose3d [[deprecated]] = geometry::Pose3d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Pose3
 *
 */
using Pose3 [[deprecated]] = geometry::Pose3;

}  // namespace holo

#endif  // HOLO_GEOMETRY_POSE3_H_