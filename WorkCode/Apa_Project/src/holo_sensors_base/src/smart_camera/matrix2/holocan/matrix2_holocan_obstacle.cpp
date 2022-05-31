/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_holocan_obstacle.hpp
 * @brief A class to receive and construct horizon matrix2 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/09
 */

#include <holo/log/hololog.h>
#include <holo_c/sensors/dbc/matrix2_laneboundary_dbc.h>
#include <holo_c/sensors/dbc/matrix2_obstacle_dbc.h>
#include <holo/sensors/smart_camera/matrix2/matrix2_holocan.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace horizon_matrix2
{
void HorizonMatrix2DriverT<HoloCanPacket>::ConstructObjectPartA(const HoloCanPacket& msg, ObjectType& object)
{
    int16_t   rawval;
    float32_t f32val;
    rawval = GET_ObstacleDataA1_ObstacleID(msg.GetData());
    rawval = CALC_ObstacleDataA1_ObstacleID(rawval, 1);
    object.SetId(static_cast<uint8_t>(rawval));
    rawval = GET_ObstacleDataA1_ObstaclePosX(msg.GetData());
    f32val = CALC_ObstacleDataA1_ObstaclePosX(rawval, 1.0f);
    object.SetPosX(f32val);
    rawval = GET_ObstacleDataA1_ObstaclePosY(msg.GetData());
    f32val = CALC_ObstacleDataA1_ObstaclePosY(rawval, 1.0f);
    object.SetPosY(f32val);
    rawval = GET_ObstacleDataA1_Move_in_and_Out(msg.GetData());
    rawval = CALC_ObstacleDataA1_Move_in_and_Out(rawval, 1);
    object.SetMoveInOut(static_cast<uint8_t>(rawval));
    rawval = GET_ObstacleDataA1_ObstacleVelX(msg.GetData());
    f32val = CALC_ObstacleDataA1_ObstacleVelX(rawval, 1.0f);
    object.SetVelX(f32val);
    rawval = GET_ObstacleDataA1_ObstacleType(msg.GetData());
    rawval = CALC_ObstacleDataA1_ObstacleType(rawval, 1);
    object.SetType(static_cast<uint8_t>(rawval));
    rawval = GET_ObstacleDataA1_VehicleSubType(msg.GetData());
    rawval = CALC_ObstacleDataA1_VehicleSubType(rawval, 1);
    object.SetVehicleSubtype(static_cast<uint8_t>(rawval));
    rawval = GET_ObstacleDataA1_ObstacleStatus(msg.GetData());
    rawval = CALC_ObstacleDataA1_ObstacleStatus(rawval, 1);
    object.SetStatus(static_cast<uint8_t>(rawval));
    rawval = GET_ObstacleDataA1_ObstacleValid(msg.GetData());
    rawval = CALC_ObstacleDataA1_ObstacleValid(rawval, 1);
    object.SetValid(static_cast<uint8_t>(rawval));
    object.SetPartAValid(true);
}

void HorizonMatrix2DriverT<HoloCanPacket>::ConstructObjectPartB(const HoloCanPacket& msg, ObjectType& object)
{
    int16_t   rawval;
    float32_t f32val;
    rawval = GET_ObstacleDataB1_ObstacleLength(msg.GetData());
    f32val = CALC_ObstacleDataB1_ObstacleLength(rawval, 1.0f);
    object.SetLength(f32val);
    rawval = GET_ObstacleDataB1_ObstacleWidth(msg.GetData());
    f32val = CALC_ObstacleDataB1_ObstacleWidth(rawval, 1.0f);
    object.SetWidth(f32val);
    rawval = GET_ObstacleDataB1_PedSubType(msg.GetData());
    rawval = CALC_ObstacleDataB1_PedSubType(rawval, 1);
    object.SetPedSubtype(static_cast<uint8_t>(rawval));
    object.SetPartBValid(true);
}

void HorizonMatrix2DriverT<HoloCanPacket>::ConstructObjectPartC(const HoloCanPacket& msg, ObjectType& object)
{
    int16_t   rawval;
    float32_t f32val;
    rawval = GET_ObstacleDataC1_ObstacleAngleRate(msg.GetData());
    f32val = CALC_ObstacleDataC1_ObstacleAngleRate(rawval, 1.0f);
    object.SetAngleRate(f32val);
    rawval = GET_ObstacleDataC1_ObstacleVelY(msg.GetData());
    f32val = CALC_ObstacleDataC1_ObstacleVelY(rawval, 1.0f);
    object.SetVelY(f32val);
    rawval = GET_ObstacleDataC1_Object_Accel_X(msg.GetData());
    f32val = CALC_ObstacleDataC1_Object_Accel_X(rawval, 1.0f);
    object.SetAccelX(f32val);
    rawval = GET_ObstacleDataC1_VehicleAngle(msg.GetData());
    f32val = CALC_ObstacleDataC1_VehicleAngle(rawval, 1.0f);
    object.SetVehicleAngle(f32val);
    object.SetPartCValid(true);
}

void HorizonMatrix2DriverT<HoloCanPacket>::ConvertToObstaclePtrListWithTransform(const ObjectListType& input,
                                                                                 ObstaclePtrListType&  output) const
{
    uint32_t                                                                                        objnum = 0;
    std::array<std::shared_ptr<ObstacleType>, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>::iterator out =
        output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.size() && out != output.GetObstacleList().end(); i++)
    {
        if (!input[i].IsAllPartsValid())
        {
            continue;
        }
        if (!input[i].GetValid())
        {
            continue;
        }
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        input[i].ConvertToHoloObstacleWithTransform(**out++, extrinsic_);
        objnum++;
    }
    output.SetSize(objnum);
}

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
