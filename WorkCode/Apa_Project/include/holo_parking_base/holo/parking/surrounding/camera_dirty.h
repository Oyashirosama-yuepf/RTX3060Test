/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_dirty.h
 * @brief This header file defines camera conver infomation.
 * @author chengxiang(chengxiang@holomaitc.com)
 * @date 2021-08-04
 */

#ifndef HOLO_PARKING_BASE_SURROUNDING_CAMERA_DIRTY_H_
#define HOLO_PARKING_BASE_SURROUNDING_CAMERA_DIRTY_H_

#include <holo/parking/surrounding/detail/camera_dirty.h>

namespace holo
{
namespace parking
{
namespace surroundings
{

/// < camera view split into (4 x 4) dimension, block width and height is (480 x 270)
using CameraDirty4x4  = CameraDirty< 4, 4, 480, 270>;

using CamerasDirtyContainer = CamerasDirtyVector<CameraDirty4x4>;

}  // namespace surroundings
}  // namespace parking
}  // namespace holo

#endif
