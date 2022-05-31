/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_lidar.h
 * @brief This header file defines ObstacleLidarT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_LIDAR_H_
#define HOLO_OBSTACLE_OBSTACLE_LIDAR_H_

#include <holo/obstacle/details/obstacle_lidar.h>

namespace holo
{
namespace obstacle
{
template <typename T>
using ObstacleLidarT = details::ObstacleLidarT<T>;

}  // namespace obstacle

template <typename T>
using ObstacleLidarT[[deprecated]] = obstacle::ObstacleLidarT<T>;

}  // namespace holo

#endif  // !HOLO_OBSTACLE_OBSTACLE_LIDAR_H_
