/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_holo_can_obstacle.hpp
 * @brief To receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/24
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
void BoschMpcDriverT<HoloCanPacket>::ConstructObjectPartA(const HoloCanPacket& msg, ObjectType& object)
{
    /* parse and store */
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_BV_Obj_01_A_BV1_Obj_01_LongitudinalDist(msg.GetData());
    if (u32val != BV_Obj_01_A_BV1_Obj_01_LongitudinalDist_Init)
    {
        f32val = CALC_BV_Obj_01_A_BV1_Obj_01_LongitudinalDist(u32val, 1.0);
    }
    else
    {
        f32val = 1.0f; /* default value */
    }
    object.SetLongDist(f32val);
    u32val = GET_BV_Obj_01_A_BV1_Obj_01_WnklMitte(msg.GetData());
    if (u32val != BV_Obj_01_A_BV1_Obj_01_WnklMitte_Init)
    {
        f32val = CALC_BV_Obj_01_A_BV1_Obj_01_WnklMitte(u32val, 1.0);
    }
    else
    {
        f32val = 0; /* default value */
    }
    object.SetAngleCenter(f32val);
    u32val = GET_BV_Obj_01_A_BV1_Obj_01_Klasse(msg.GetData());
    u32val = CALC_BV_Obj_01_A_BV1_Obj_01_Klasse(u32val, 1);
    object.SetClassification(u32val);
    object.SetPartAValid(true);
}

void BoschMpcDriverT<HoloCanPacket>::ConstructObjectPartB(const HoloCanPacket& msg, ObjectType& object)
{
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_BV_Obj_01_B_BV1_Obj_01_WnklBreite(msg.GetData());
    f32val = CALC_BV_Obj_01_B_BV1_Obj_01_WnklBreite(u32val, 1.0);
    object.SetAngleWidth(f32val);
    u32val = GET_BV_Obj_01_B_BV1_Obj_01_ExistenzMass(msg.GetData());
    if (u32val != BV_Obj_01_B_BV1_Obj_01_ExistenzMass_Init)
    {
        f32val = CALC_BV_Obj_01_B_BV1_Obj_01_ExistenzMass(u32val, 1.0);
    }
    else
    {
        f32val = 0.0f;
    }
    object.SetConfidence(f32val);
    u32val = GET_BV_Obj_01_B_BV1_Obj_01_WnklGeschw(msg.GetData());
    if (u32val < (BV_Obj_01_B_BV1_Obj_01_WnklGeschw_Init - 1))
    {
        f32val = CALC_BV_Obj_01_B_BV1_Obj_01_WnklGeschw(u32val, 1.0);
    }
    else
    {
        f32val = 0.0f;
    }
    object.SetAngleSpeed(f32val);
    object.SetPartBValid(true);
}

void BoschMpcDriverT<HoloCanPacket>::ConstructObjectPartC(const HoloCanPacket& msg, ObjectType& object)
{
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_BV_Obj_01_C_BV1_Obj_01_InvTTCBildeb(msg.GetData());
    f32val = CALC_BV_Obj_01_C_BV1_Obj_01_InvTTCBildeb(u32val, 1.0);
    object.SetInvTTC(f32val);
    u32val = GET_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurR(msg.GetData());
    f32val = CALC_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurR(u32val, 1.0);
    object.SetAngleOverlapEgolaneRight(f32val);
    u32val = GET_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurL(msg.GetData());
    f32val = CALC_BV_Obj_01_C_BV1_Obj_01_UeberdWnklEgoSpurL(u32val, 1.0);
    object.SetAngleOverlapEgolaneLeft(f32val);
    u32val = GET_BV_Obj_01_C_BV1_Obj_01_Alter(msg.GetData());
    u32val = CALC_BV_Obj_01_C_BV1_Obj_01_Alter(u32val, 1);
    object.SetAge(u32val);
    object.SetPartCValid(true);
}

void BoschMpcDriverT<HoloCanPacket>::ConstructObjectPartD(const HoloCanPacket& msg, ObjectType& object)
{
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_BV_Obj_01_D_BV_Objekt_01_phi_right(msg.GetData());
    f32val = CALC_BV_Obj_01_D_BV_Objekt_01_phi_right(u32val, 1.0);
    object.SetAngleEdgeRight(f32val);
    u32val = GET_BV_Obj_01_D_BV_Objekt_01_phi_left(msg.GetData());
    f32val = CALC_BV_Obj_01_D_BV_Objekt_01_phi_left(u32val, 1.0);
    object.SetAngleEdgeLeft(f32val);
    u32val = GET_BV_Obj_01_D_BV1_Obj_01_ID(msg.GetData());
    u32val = CALC_BV_Obj_01_D_BV1_Obj_01_ID(u32val, 1);
    object.SetId(u32val);
    object.SetPartDValid(true);
}

void BoschMpcDriverT<HoloCanPacket>::ConstructObjectPartE(const HoloCanPacket& msg, ObjectType& object)
{
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_BV_Obj_01_E_BV1_Obj_01_RadialGeschw(msg.GetData());
    if (u32val != BV_Obj_01_E_BV1_Obj_01_RadialGeschw_Init)
    {
        f32val = CALC_BV_Obj_01_E_BV1_Obj_01_RadialGeschw(u32val, 1.0);
    }
    else
    {
        f32val = 0.0f;
    }
    object.SetLongVelocity(f32val);
    object.SetPartEValid(true);
    /* timestamp */
    object.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConvertToObstaclePtrListWithTransform(const std::array<ObjectType, 16>& input,
                                                                           ObstaclePtrListType& output) const
{
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (auto in = input.cbegin(); in != input.cend() && out != output.GetObstacleList().end(); in++)
    {
        if (!in->IsValid())
        {
            continue;
        }
        if (!(in->GetConfidence() > 0.0f))
        {
            continue;
        }
        *out = std::make_shared<ObstacleType>();
        in->ConvertToHoloObstacleWithTransform(**out++, extrinsic_);
        objnum++;
    }
    output.SetSize(objnum);
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
