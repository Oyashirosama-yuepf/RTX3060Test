/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_types.h
 * @brief This header file defines point types used by point cloud.
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2020-11-29
 */
#ifndef HOLO_3D_COMMON_POINT_TYPES_H_
#define HOLO_3D_COMMON_POINT_TYPES_H_

#include <holo/3d/common/details/point_types.h>
#include <holo/geometry/point3.h>
#include <holo/point_cloud/point_type.h>

namespace holo
{
namespace pointcloud
{
/**
 * @brief Point type with x, y, z, intensity, ring, timestamp
 *
 * @tparam T Scalar type of point
 */
template <typename T>
using PointXYZIRSt = point_cloud::details::PointXYZIRSt<T>;

/**
 * @brief Point type with x, y, z, intensity, ring, rgb, timestamp
 *
 * @tparam T Scalar type of point
 */
template <typename T>
using PointXYZIRRgbSt = point_cloud::details::PointXYZIRRgbSt<T>;

/**
 * @brief Point type with x, y, z, nx, ny, nz
 *
 * @tparam T Scalar type of point
 */
template <typename T>
using PointXYZNormalt = point_cloud::details::PointXYZNormalt<T>;

}  // namespace pointcloud
}  // namespace holo

#endif
