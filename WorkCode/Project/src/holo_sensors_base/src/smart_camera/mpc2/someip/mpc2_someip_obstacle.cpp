/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_someip_obstacle.hpp
 * @brief To receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/24
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
void BoschMpcDriverT<SomeipPacketType>::ConvertToHoloObstacleWithTransform(const struct MpcObjectRawData& input,
                                                                           std::shared_ptr<ObstacleType>& output) const
{
    uint16_t   u16val;
    uint8_t    u8val;
    float32_t  f32val;
    ObjectType object;
    /* timestamp */
    holo::common::Timestamp stamp(input.timestamp.sec, input.timestamp.nsec);
    object.SetTimestamp(stamp);
    /* part a */
    if (input.lon_dist != BV_Obj_01_A_BV1_Obj_01_LongitudinalDist_Init)
    {
        f32val = CALC_BV_Obj_01_A_BV1_Obj_01_LongitudinalDist(input.lon_dist, 1.0f);
    }
    else
    {
        f32val = 1.0f; /* default value */
    }
    object.SetLongDist(f32val);
    if (input.angle_center != BV_Obj_01_A_BV1_Obj_01_WnklMitte_Init)
    {
        f32val = CALC_BV_Obj_01_A_BV1_Obj_01_WnklMitte(input.angle_center, 1.0f);
    }
    else
    {
        f32val = 0.0f; /* default value */
    }
    object.SetAngleCenter(f32val);
    u8val = CALC_BV_Obj_01_A_BV1_Obj_01_Klasse(input.classification, 1);
    object.SetClassification(u8val);
    /* part b */
    f32val = CALC_BV_Obj_01_B_BV1_Obj_01_WnklBreite(input.angle_width, 1.0f);
    object.SetAngleWidth(f32val);
    if (input.confidence != BV_Obj_01_B_BV1_Obj_01_ExistenzMass_Init)
    {
        f32val = CALC_BV_Obj_01_B_BV1_Obj_01_ExistenzMass(input.confidence, 1.0f);
    }
    else
    {
        f32val = 0.0f;
    }
    object.SetConfidence(f32val);
    if (input.angle_speed < (BV_Obj_01_B_BV1_Obj_01_WnklGeschw_Init - 1))
    {
        f32val = CALC_BV_Obj_01_B_BV1_Obj_01_WnklGeschw(input.angle_speed, 1.0f);
    }
    else
    {
        f32val = 0.0f;
    }
    object.SetAngleSpeed(f32val);
    /* part c */
    f32val = CALC_BV_Obj_01_C_BV1_Obj_01_InvTTCBildeb(input.inv_ttc, 1.0f);
    object.SetInvTTC(f32val);
    f32val = CALC_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurR(input.angle_overlap_egolane_right, 1.0f);
    object.SetAngleOverlapEgolaneRight(f32val);
    f32val = CALC_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurL(input.angle_overlap_egolane_left, 1.0f);
    object.SetAngleOverlapEgolaneLeft(f32val);
    u16val = CALC_BV_Obj_01_C_BV1_Obj_01_Alter(input.age, 1);
    object.SetAge(u16val);
    /* part d */
    f32val = CALC_BV_Obj_01_D_BV_Objekt_01_phi_right(input.angle_edge_right, 1.0f);
    object.SetAngleEdgeRight(f32val);
    f32val = CALC_BV_Obj_01_D_BV_Objekt_01_phi_left(input.angle_edge_left, 1.0f);
    object.SetAngleEdgeLeft(f32val);
    u8val = CALC_BV_Obj_01_D_BV1_Obj_01_ID(input.id, 1);
    object.SetId(u8val);
    /* part e */
    if (input.lon_velocity != BV_Obj_01_E_BV1_Obj_01_RadialGeschw_Init)
    {
        f32val = CALC_BV_Obj_01_E_BV1_Obj_01_RadialGeschw(input.lon_velocity, 1.0f);
    }
    else
    {
        f32val = 0.0f;
    }
    object.SetLongVelocity(f32val);
    /* convert */
    object.ConvertToHoloObstacleWithTransform(*output, extrinsic_);
}

void BoschMpcDriverT<SomeipPacketType>::ConvertToObstaclePtrListWithTransform(const struct MpcObjectListRawData& input,
                                                                              ObstaclePtrListType& output) const
{
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.num && out != output.GetObstacleList().end(); i++)
    {
        if (input.object[i].confidence == BV_Obj_01_B_BV1_Obj_01_ExistenzMass_Init)
        {
            continue;
        }
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        ConvertToHoloObstacleWithTransform(input.object[i], *out++);
        objnum++;
    }
    output.SetSize(objnum);
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
