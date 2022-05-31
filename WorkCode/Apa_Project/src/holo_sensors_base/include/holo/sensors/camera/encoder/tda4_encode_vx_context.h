/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tda4_encode_vx_context.h
 * @brief TDA4 Encode VX Context
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-12
 */

#ifndef _HOLO_SENSORS_CAMERA_IMAGE_SYNC_ENCODE_H
#define _HOLO_SENSORS_CAMERA_IMAGE_SYNC_ENCODE_H

#include <holo/sensors/camera/image_structure.h>
#include <list>

#include <TI/j7.h>
#include <VX/vx.h>
#include <VX/vxu.h>

#include <mutex>

extern "C" {
#include <TI/tivx.h>
#include <app_init.h>
}

namespace holo
{
namespace sensors
{
namespace camera
{
class Tda4EncodeVxContext
{
public:
    Tda4EncodeVxContext(uint16_t refnum);
    vx_context GetContext() const noexcept;
    virtual ~Tda4EncodeVxContext();

private:
    static std::mutex mutex_;
    static int32_t    refnum_;
    static vx_context context_;
};

}  // namespace camera
}  // namespace sensors
}  // namespace holo

#endif  //_HOLO_SENSORS_CAMERA_IMAGE_SYNC_ENCODE_H