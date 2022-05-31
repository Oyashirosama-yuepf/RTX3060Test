/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_list.h
 * @brief This header file defines ObstaclePtrListT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-11-27
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_PTR_LIST_H_
#define HOLO_OBSTACLE_OBSTACLE_PTR_LIST_H_

#include <holo/obstacle/details/obstacle_list.h>

namespace holo
{
namespace obstacle
{
template <typename T, std::size_t CAPACITY>
using ObstaclePtrListT = details::ObstaclePtrListT<T, CAPACITY>;

using ObstacleGeneralPtrList =
    ObstaclePtrListT<ObstacleGeneralT<holo::float32_t>, GENERAL_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleLidarPtrList = ObstaclePtrListT<ObstacleLidarT<holo::float32_t>, LIDAR_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleRadarPtrList = ObstaclePtrListT<ObstacleRadarT<holo::float32_t>, RADAR_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleUssPtrList   = ObstaclePtrListT<ObstacleUssT<holo::float32_t>, USS_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleVisionPtrList =
    ObstaclePtrListT<ObstacleVisionT<holo::float32_t, 8U>, VISION_OBSTACLE_LIST_COMMON_CAPACITY>;

}  // namespace obstacle

template <typename T, std::size_t CAPACITY>
using ObstaclePtrListT[[deprecated]] = obstacle::ObstaclePtrListT<T, CAPACITY>;

using ObstacleGeneralPtrList[[deprecated]] = obstacle::ObstacleGeneralPtrList;
using ObstacleLidarPtrList[[deprecated]]   = obstacle::ObstacleLidarPtrList;
using ObstacleRadarPtrList[[deprecated]]   = obstacle::ObstacleRadarPtrList;
using ObstacleUssPtrList[[deprecated]]     = obstacle::ObstacleUssPtrList;
using ObstacleVisionPtrList[[deprecated]]  = obstacle::ObstacleVisionPtrList;
}  // namespace holo

#endif
