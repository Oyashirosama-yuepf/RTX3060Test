/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2.h
 * @brief A class to receive and construct aptive horizon matrix2 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/26
 */

#ifndef HOLO_SENSORS_HORIZON_MATRIX2_HORIZON_MATRIX2_H_
#define HOLO_SENSORS_HORIZON_MATRIX2_HORIZON_MATRIX2_H_

#include <holo/sensors/smart_camera/matrix2/structure/matrix2_laneboundary.h>
#include <holo/sensors/smart_camera/matrix2/structure/matrix2_obstacle.h>
#include <holo/sensors/smart_camera/smart_camera.h>

namespace holo
{
namespace sensors
{
namespace horizon_matrix2
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;

static const uint32_t HORIZON_MATRIX2_LINES_NUM   = 4u;
static const uint32_t HORIZON_MATRIX2_OBJECTS_NUM = 10u;

class HorizonMatrix2DriverBase : public Device
{
public:
    //! obstacle typedefs
    using ObjectType     = holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle;
    using ObjectListType = std::array<ObjectType, HORIZON_MATRIX2_OBJECTS_NUM>;
    //! road frame typedefs
    using LineType     = holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary;
    using LineListType = std::array<LineType, HORIZON_MATRIX2_LINES_NUM>;

    HorizonMatrix2DriverBase(const Extrinsicf& extrinsic)
      : Device(extrinsic.GetSensorId()), extrinsic_(extrinsic)
    {
    }

    virtual ~HorizonMatrix2DriverBase() = default;

protected:
    Extrinsicf     extrinsic_;
    LineListType   lane_boundary_list_;
    ObjectListType object_list_;
};

template <typename T>
class HorizonMatrix2DriverT
{
public:
    HorizonMatrix2DriverT() = 0;
};

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo

#endif
