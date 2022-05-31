/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conti_radar.h
 * @brief A class to receive and construct conti radar outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/16
 */

#ifndef HOLO_SENSORS_CONTI_RADAR_CONTI_RADAR_H_
#define HOLO_SENSORS_CONTI_RADAR_CONTI_RADAR_H_

#include <holo/common/extrinsic.h>
#include <holo/core/types.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/obstacle/obstacle_radar.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/common/interface.h>
#include <holo/sensors/radar/ars408/structure/ars408_obstacle.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo_c/sensors/conti_radar/structure/conti_radar_object.h>
#include <functional>

namespace holo
{
namespace sensors
{
namespace conti_radar
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;

template <typename T>
class ContiRadarDriverBase : public Device
{
public:
    using InType               = T;
    using ObjectType           = holo::sensors::conti_radar::ContiRadarObstacle;
    using ObstacleType         = holo::obstacle::ObstacleRadarT<float32_t>;
    using ObstaclePtrListType  = holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::RADAR_OBSTACLE_LIST_COMMON_CAPACITY>;
    using ObstacleListCallback = std::function<void(const ObstaclePtrListType&)>;

    ContiRadarDriverBase(const Extrinsicf& extrinsic)
        : Device(extrinsic.GetSensorId()), extrinsic_(extrinsic), obstacles_callback_(nullptr)
    {
    }

    virtual ~ContiRadarDriverBase() = default;

    void InstallCallback(const ObstacleListCallback& handler) noexcept
    {
        obstacles_callback_ = handler;
    }

    virtual void ParseData(const T& data) = 0;

protected:
    const Extrinsicf     extrinsic_;
    ObstacleListCallback obstacles_callback_;
};

template <typename T>
class ContiRadarDriverT : public ContiRadarDriverBase<T>
{
public:
    ContiRadarDriverT(const Extrinsicf& extrinsic) : ContiRadarDriverBase<T>(extrinsic)
    {
    }
    void ParseData(const T&){};
};

}  // namespace conti_radar
}  // namespace sensors
}  // namespace holo

#endif
