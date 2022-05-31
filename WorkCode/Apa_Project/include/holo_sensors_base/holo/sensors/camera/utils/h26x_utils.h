/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file h26x_utils.h.
 * @brief H26X Utils.
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2022-4-18.
 */

#ifndef _HOLO_SENSORS_CAMERA_H26X_UTILS_H
#define _HOLO_SENSORS_CAMERA_H26X_UTILS_H

#include <holo/core/types.h>

namespace holo
{
namespace sensors
{
namespace camera
{
bool_t is_key_frame_h265(uint8_t* pbuf, int buf_size);
bool_t is_key_frame_h264(uint8_t* pbuf, int buf_size);
}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_H26X_UTILS_H