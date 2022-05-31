/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smart_camera.h
 * @brief A base class of smart camera
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/10
 */

#ifndef HOLO_SENSORS_SMART_CAMERA_SMART_CAMERA_H_
#define HOLO_SENSORS_SMART_CAMERA_SMART_CAMERA_H_

#include <holo/common/extrinsic.h>
#include <holo/common/road_frame2.h>
#include <holo/core/types.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/common/interface.h>
#include <holo/sensors/format/spd_limit_sign.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <functional>

namespace holo
{
namespace sensors
{
template <typename T>
class SmartCameraDriverT
{
public:
    using Intype = T;
    /* obstacle alias */
    using ObstacleType = holo::obstacle::ObstacleVisionT<float32_t>;
    using ObstaclePtrListType =
        holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
    using ObstacleListCallbackType = std::function<void(const ObstaclePtrListType&)>;
    /* road frame alias */
    using LaneboundaryType      = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
    using RoadFrameType         = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
    using RoadFrameCallbackType = std::function<void(const RoadFrameType&)>;
    /* speed limit sign */
    using SpdLimitSignType             = holo::sensors::format::SpdLimitSign;
    using SpdLimitSignListType         = std::array<SpdLimitSignType, 7>;
    using SpdLimitSignListCallbackType = std::function<void(const SpdLimitSignListType&)>;

    SmartCameraDriverT() : obstacles_callback_(nullptr), roadframe_callback_(nullptr), spd_limit_sign_callback_(nullptr)
    {
    }

    virtual ~SmartCameraDriverT() = default;

    void InstallCallback(const ObstacleListCallbackType& handler) noexcept
    {
        obstacles_callback_ = handler;
    }
    void InstallCallback(const RoadFrameCallbackType& handler) noexcept
    {
        roadframe_callback_ = handler;
    }
    void InstallCallback(const SpdLimitSignListCallbackType& handler) noexcept
    {
        spd_limit_sign_callback_ = handler;
    }
    virtual void ParseData(const T&) = 0;

protected:
    ObstacleListCallbackType     obstacles_callback_;
    RoadFrameCallbackType        roadframe_callback_;
    SpdLimitSignListCallbackType spd_limit_sign_callback_;
};

}  // namespace sensors
}  // namespace holo

#endif
