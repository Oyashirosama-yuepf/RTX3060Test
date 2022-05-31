/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_uss.h
 * @brief This header file defines ObstacleUssT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-05
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_USS_H_
#define HOLO_OBSTACLE_OBSTACLE_USS_H_

#include <holo/obstacle/details/obstacle_uss.h>

namespace holo
{
namespace obstacle
{
template <typename T>
using ObstacleUssT = details::ObstacleUssT<T>;

}  // namespace obstacle

template <typename T>
using ObstacleUssT[[deprecated]] = obstacle::ObstacleUssT<T>;
}  // namespace holo

#endif  // !HOLO_OBSTACLE_OBSTACLE_USS_H_
