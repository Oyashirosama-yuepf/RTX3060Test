/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_cloud.h
 * @brief This header file defines point cloud type in 3d
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-02-18
 */

#ifndef HOLO_3D_COMMON_POINT_CLOUD_H_
#define HOLO_3D_COMMON_POINT_CLOUD_H_

#include <holo/point_cloud/details/point_cloud.h>

namespace holo
{
namespace pointcloud
{
/**
 * @addtogroup point_cloud
 * @{
 */

/**
 * @brief Organized point cloud type tag
 */
using point_cloud::details::OrganizedLayoutTag;

/**
 * @brief Unorganized point cloud type tag
 */
using point_cloud::details::UnorganizedLayoutTag;

/**
 * @brief Point cloud type
 *
 * @tparam Point Point type of point cloud
 * @tparam SIZE Size of point cloud. use dynamic size vector in 3d
 * @tparam STRIDE Stride of each element. Default value = sizeof(Point)
 * @tparam LayoutTag Point cloud type tag
 */
template <typename Point, size_t SIZE = std::numeric_limits<size_t>::max(), size_t STRIDE = sizeof(Point),
          typename LayoutTag = UnorganizedLayoutTag>
using PointCloudT = point_cloud::details::PointCloudT<Point, SIZE, STRIDE, LayoutTag>;

/**
 * @}
 */

}  // namespace pointcloud
}  // namespace holo

#endif
