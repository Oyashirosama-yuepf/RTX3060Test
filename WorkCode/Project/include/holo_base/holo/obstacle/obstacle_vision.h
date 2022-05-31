/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_vision.h
 * @brief This header file defines ObstacleVisionT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_VISION_H_
#define HOLO_OBSTACLE_OBSTACLE_VISION_H_

#include <holo/obstacle/details/obstacle_vision.h>

namespace holo
{
namespace obstacle
{
template <typename T, size_t SIZE = 8U>
using ObstacleVisionT = details::ObstacleVisionT<T, SIZE>;

}  // namespace obstacle

template <typename T, size_t SIZE = 8U>
using ObstacleVisionT[[deprecated]] = obstacle::ObstacleVisionT<T, SIZE>;

}  // namespace holo

#endif
