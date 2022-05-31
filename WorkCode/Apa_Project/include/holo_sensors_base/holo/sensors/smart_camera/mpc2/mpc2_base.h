/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc.h
 * @brief A class to receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/07
 */

#ifndef HOLO_SENSORS_BOSCH_MPC_BOSCH_MPC_H_
#define HOLO_SENSORS_BOSCH_MPC_BOSCH_MPC_H_

#include <holo/sensors/smart_camera/mpc2/structure/mpc2_laneboundary.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_obstacle.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_spd_limit_sign.h>
#include <holo/sensors/smart_camera/smart_camera.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;

static const float32_t LANE_WIDTH_HIGHWAY    = 3.75f;
static const float32_t LANE_CHANGE_THRESHOLD = 0.5f;

/* driver base */
class BoschMpcDriverBase : public Device
{
public:
    /* obstacle alias */
    using ObjectType     = BoschMpcObstacle;
    using ObjectListType = std::array<ObjectType, 16>;
    /* road frame alias */
    using LineType     = BoschMpcLaneBoundary;
    using LineListType = std::array<LineType, 4>;
    /* speed limit sign alias */
    using SpdSignType     = BoschMpcSpdLimitSign;
    using SpdSignListType = std::array<SpdSignType, 7>;

    BoschMpcDriverBase(const Extrinsicf& extrinsic)
      : Device(extrinsic.GetSensorId()), extrinsic_(extrinsic), veh_moving_mode_(KEEPING_IN_LANE)
    {
    }

    virtual ~BoschMpcDriverBase() = default;

    static bool_t CompareLaneBoundaryLeft(const LineType* lbd1, const LineType* lbd2)
    {
        return bool_t(lbd1->GetDy() < lbd2->GetDy());
    }

    static bool_t CompareLaneBoundaryRight(const LineType* lbd1, const LineType* lbd2)
    {
        return bool_t(lbd1->GetDy() > lbd2->GetDy());
    }

protected:
    /* moving mode */
    enum : uint32_t
    {
        KEEPING_IN_LANE   = 0,
        CHANGING_TO_LEFT  = 1,
        CHANGING_TO_RIGHT = 2
    };

protected:
    Extrinsicf      extrinsic_;
    LineListType    lane_boundary_list_;
    ObjectListType  object_list_;
    SpdSignListType spd_limit_sign_list_;
    uint32_t        veh_moving_mode_;
};

/* driver template */
template <typename T>
class BoschMpcDriverT
{
public:
    BoschMpcDriverT() = 0;
};

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo

#endif
