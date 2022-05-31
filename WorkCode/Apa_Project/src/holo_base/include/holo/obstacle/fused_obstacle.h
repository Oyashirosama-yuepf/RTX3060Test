/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fused_obstacle.h
 * @brief This header file defines FusedObstacleT.
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date 2021-10-22
 */

#ifndef HOLO_OBSTACLE_FUSED_OBSTACLE_H_
#define HOLO_OBSTACLE_FUSED_OBSTACLE_H_

#include <holo/obstacle/details/fused_obstacle.h>

namespace holo
{
namespace gh02
{  
namespace obstacle
{
template <typename T, size_t SIZE = 256U>
using FusedObstacleT = details::FusedObstacleT<T, SIZE>;

}  // namespace obstacle
}  // namespace gh02
}  // namespace holo

#endif
