/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_radar.h
 * @brief This header file defines ObstacleRadarT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_RADAR_H_
#define HOLO_OBSTACLE_OBSTACLE_RADAR_H_

#include <holo/obstacle/details/obstacle_radar.h>

namespace holo
{
namespace obstacle
{

template <typename T>
using ObstacleRadarT = details::ObstacleRadarT<T>;

}  // namespace obstacle

template <typename T>
using ObstacleRadarT[[deprecated]] = obstacle::ObstacleRadarT<T>;

}  // namespace holo

#endif
