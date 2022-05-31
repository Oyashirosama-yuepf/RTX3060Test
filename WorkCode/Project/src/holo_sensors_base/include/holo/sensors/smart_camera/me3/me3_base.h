/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye.h
 * @brief A class to receive and construct hirain mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/26
 */

#ifndef HOLO_SENSORS_MOBILEYE_MOBILEYE_H_
#define HOLO_SENSORS_MOBILEYE_MOBILEYE_H_

#include <holo/sensors/smart_camera/me3/structure/me3_laneboundary.h>
#include <holo/sensors/smart_camera/me3/structure/me3_obstacle.h>
#include <holo/sensors/smart_camera/smart_camera.h>

namespace holo
{
namespace sensors
{
namespace mobileye
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;

class MobileyeDriverBase : public Device
{
public:
    /* obstacle alias */
    using ObjectType     = holo::sensors::mobileye::MobileyeObstacle;
    using ObjectListType = std::array<ObjectType, 8>;
    /* lane boundary alias */
    using LineType     = holo::sensors::mobileye::MobileyeLaneBoundary;
    using LineListType = std::array<LineType, 4>;

    MobileyeDriverBase(const Extrinsicf& extrinsic)
      : Device(extrinsic.GetSensorId()), extrinsic_(extrinsic)
    {
    }

    virtual ~MobileyeDriverBase() = default;

protected:
    Extrinsicf     extrinsic_;
    LineListType   lane_boundary_list_;
    ObjectListType object_list_;
};

template <typename T>
class MobileyeDriverT
{
public:
    MobileyeDriverT() = 0;
};

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo

#endif
