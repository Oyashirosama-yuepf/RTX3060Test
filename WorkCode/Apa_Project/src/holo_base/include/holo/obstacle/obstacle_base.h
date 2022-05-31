/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_base.h
 * @brief This header file defines ObstacleBaseT .
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_OBSTACLE_BASE_H_
#define HOLO_OBSTACLE_OBSTACLE_BASE_H_

#include <holo/obstacle/details/obstacle_base.h>

namespace holo
{
namespace obstacle
{

template <typename T>
using ObstacleBaseT = details::ObstacleBaseT<T>;

using CutInCutOut = details::CutInCutOut;
using MotionStatus = details::MotionStatus;

}  // namespace obstacle

template <typename T>
using ObstacleBaseT[[deprecated]] = obstacle::ObstacleBaseT<T>;

using CutInCutOut[[deprecated]] = obstacle::CutInCutOut;
using MotionStatus[[deprecated]] = obstacle::MotionStatus;

}  // namespace holo

#endif  
