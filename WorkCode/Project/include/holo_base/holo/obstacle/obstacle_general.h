/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_general.h
 * @brief This header file defines ObstacleGeneralT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_GENERAL_H_
#define HOLO_OBSTACLE_OBSTACLE_GENERAL_H_

#include <holo/obstacle/details/obstacle_general.h>

namespace holo
{
namespace obstacle
{

template<typename T>
using ObstacleGeneralT = details::ObstacleGeneralT<T>;

}  // namespace obstacle

template<typename T>
using ObstacleGeneralT[[deprecated]] = obstacle::ObstacleGeneralT<T>;
}  // namespace holo

#endif  // !HOLO_OBSTACLE_OBSTACLE_GENERAL_H_
