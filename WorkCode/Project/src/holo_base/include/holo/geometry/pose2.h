/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose2.h
 * @brief This header file defines pose in 2D.
 * @author duyanwei@holomatic.com
 * @date 2020-09-25
 */

#ifndef HOLO_GEOMETRY_POSE2_H_
#define HOLO_GEOMETRY_POSE2_H_

#include "./details/pose2.h"

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
using Pose2T = details::Pose2T<T>;

using Pose2f = details::Pose2T<float32_t>;
using Pose2d = details::Pose2T<float64_t>;
using Pose2  = details::Pose2T<float64_t>;

}  // namespace geometry

/**
 * @deprecated Deprecated soon, please use holo::geometry::Pose2T<T>
 *
 * @tparam T
 */
template <typename T>
using Pose2T [[deprecated]] = geometry::Pose2T<T>;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Pose2f
 *
 */
using Pose2f [[deprecated]] = geometry::Pose2f;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Pose2d
 *
 */
using Pose2d [[deprecated]] = geometry::Pose2d;

/**
 * @deprecated Deprecated soon, please use holo::geometry:::Pose2
 *
 */
using Pose2 [[deprecated]] = geometry::Pose2;

}  // namespace holo

#endif  // HOLO_GEOMETRY_POSE2_H_