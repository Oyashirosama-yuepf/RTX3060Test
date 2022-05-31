/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300.h
 * @brief A class to receive and construct aptive ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/26
 */

#ifndef HOLO_SENSORS_IFV300_IFV300_H_
#define HOLO_SENSORS_IFV300_IFV300_H_

#include <holo/sensors/smart_camera/ifv300/structure/ifv300_laneboundary.h>
#include <holo/sensors/smart_camera/ifv300/structure/ifv300_obstacle.h>
#include <holo/sensors/smart_camera/smart_camera.h>

namespace holo
{
namespace sensors
{
namespace ifv300
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;

static const uint32_t IFV300_LINES_NUM   = 4u;
static const uint32_t IFV300_OBJECTS_NUM = 15u;

class Ifv300DriverBase : public Device
{
public:
    /* obstacle alias */
    using ObjectType     = holo::sensors::ifv300::Ifv300Obstacle;
    using ObjectListType = std::array<ObjectType, IFV300_OBJECTS_NUM>;
    /* roadframe alias */
    using LineType     = holo::sensors::ifv300::Ifv300LaneBoundary;
    using LineListType = std::array<LineType, IFV300_LINES_NUM>;

    Ifv300DriverBase(const Extrinsicf& extrinsic)
      : Device(extrinsic.GetSensorId()), extrinsic_(extrinsic), vehicle_speed_(0)
    {
    }

    virtual ~Ifv300DriverBase() = default;

protected:
    Extrinsicf     extrinsic_;
    LineListType   lane_boundary_list_;
    ObjectListType object_list_;
    float32_t      vehicle_speed_;
};

template <typename T>
class Ifv300DriverT
{
public:
    Ifv300DriverT() = 0;
};

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo

#endif
