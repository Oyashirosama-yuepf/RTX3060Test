/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_cloud.h
 * @brief This header file defines point types used by point cloud.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2020-10-29
 */

#ifndef HOLO_POINT_CLOUD_POINT_CLOUD_H_
#define HOLO_POINT_CLOUD_POINT_CLOUD_H_

#include "details/point_cloud.h"

namespace holo
{
namespace point_cloud
{
/**
 * @addtogroup point_cloud
 * @{
 */

/**
 * @brief Organized point cloud type tag
 */
using details::OrganizedLayoutTag;

/**
 * @brief Unorganized point cloud type tag
 */
using details::UnorganizedLayoutTag;

/**
 * @brief Point cloud type
 *
 * @tparam Point Point type of point cloud
 * @tparam SIZE Size of point cloud. 0 for dynamic size. Default value = 0U
 * @tparam STRIDE Stride of each element. Default value = sizeof(Point)
 * @tparam LayoutTag Point cloud type tag
 */
template <typename Point, size_t SIZE, size_t STRIDE = sizeof(Point), typename LayoutTag = UnorganizedLayoutTag>
using PointCloudT = details::PointCloudT<Point, SIZE, STRIDE, LayoutTag>;

/**
 * @}
 */

}  // namespace point_cloud
}  // namespace holo

#endif
