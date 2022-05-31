/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point_type.h
 * @brief This header file defines point types used by point cloud.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2020-10-29
 */

#ifndef HOLO_POINT_CLOUD_POINT_TYPE_H_
#define HOLO_POINT_CLOUD_POINT_TYPE_H_

#include "details/point_type.h"

namespace holo
{
namespace point_cloud
{

/**
 * @addtogroup point_cloud
 * @{
 */

/**
 * @brief Point type with x, y, z, intensity, ring, timestamp
 *
 * @tparam T Scalar type of point
 */
template <typename T>
using PointXYZIRSt = details::PointXYZIRSt<T>;

/**
 * @brief Point type with x, y, z, intensity, ring, rgb, timestamp
 *
 * @tparam T Scalar type of point
 */
template <typename T>
using PointXYZIRRgbSt = details::PointXYZIRRgbSt<T>;

/**
 * @}
 */

}
}  // namespace holo

#endif
