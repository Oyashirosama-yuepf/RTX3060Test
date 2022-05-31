/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_holocan_obstacle.hpp
 * @brief A class to receive and construct ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#ifndef _HOLO_SENSORS_IFV300_IFV300_HOLOCAN_OBSTACLE_HPP
#define _HOLO_SENSORS_IFV300_IFV300_HOLOCAN_OBSTACLE_HPP

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_holocan.h>
#include <holo_c/sensors/dbc/ifv300_output_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace ifv300
{
bool_t Ifv300DriverT<HoloCanPacket>::ConstructObjectPartA(const HoloCanPacket&                        msg,
                                                          std::array<ObjectType, IFV300_OBJECTS_NUM>& object_list)
{
    uint8_t id = GET_VIS_OBS_MSG_1_VIS_OBS_COUNT_MSG1(msg.GetData());  //! no need CALC_* for this signal
    if (id == 1)                                                       /* minimal value */
    {
        /* start of cycle */
        /* clear valid flag */
        for (uint32_t i = 0; i < object_list.size(); i++)
        {
            object_list[i].SetPartAValid(false);
            object_list[i].SetPartBValid(false);
            object_list[i].SetPartCValid(false);
        }
    }
    if (id > object_list.size()) /* maxval of id */
    {
        LOG(ERROR) << "invalid id in part a: " << static_cast<uint32_t>(id);
        return false;
    }
    uint32_t  u32val;
    float32_t f32val;
    object_list[id].SetObjectId(id);
    u32val = GET_VIS_OBS_MSG_1_VIS_OBS_CLASSIFICATION_01(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_1_VIS_OBS_CLASSIFICATION_01(u32val, 1);
    object_list[id].SetClassification(u32val);
    u32val = GET_VIS_OBS_MSG_1_VIS_OBS_PED_WAIST_UP_01(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_1_VIS_OBS_PED_WAIST_UP_01(u32val, 1);
    object_list[id].SetPedWaistUp(bool_t(u32val));
    u32val = GET_VIS_OBS_MSG_1_VIS_OBS_TURN_INDICATOR_01(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_1_VIS_OBS_TURN_INDICATOR_01(u32val, 1);
    object_list[id].SetTurnInd(u32val);
    u32val = GET_VIS_OBS_MSG_1_VIS_OBS_BRAKE_LIGHT_INDIC_01(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_1_VIS_OBS_BRAKE_LIGHT_INDIC_01(u32val, 1);
    object_list[id].SetBrakeLightInd(u32val);
    u32val = GET_VIS_OBS_MSG_1_VIS_OBS_MESSAGE_COUNTER_MSG1(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_1_VIS_OBS_MESSAGE_COUNTER_MSG1(u32val, 1);
    object_list[id].SetRollingCounter(u32val);
    u32val = GET_VIS_OBS_MSG_1_VIS_OBS_HEIGHT_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_1_VIS_OBS_HEIGHT_01(u32val, 1.0f);
    object_list[id].SetHeight(f32val);
    /* set part a valid */
    object_list[id].SetPartAValid(true);
    return true;
}

bool_t Ifv300DriverT<HoloCanPacket>::ConstructObjectPartB(const HoloCanPacket&                        msg,
                                                          std::array<ObjectType, IFV300_OBJECTS_NUM>& object_list)
{
    uint8_t id = GET_VIS_OBS_MSG_2_VIS_OBS_COUNT_MSG2(msg.GetData());  //! no need CALC_* for this signal
    if (id > object_list.size())                                       /* maxval of id */
    {
        LOG(ERROR) << "invalid id in part a: " << id;
        return false;
    }
    if (id != object_list[id].GetObjectId())
    {
        LOG(ERROR) << "mismatch id in part b: " << id
                   << ", want: " << static_cast<uint32_t>(object_list[id].GetObjectId());
        return false;
    }
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_VIS_OBS_MSG_2_VIS_OBS_MESSAGE_COUNTER_MSG2(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_2_VIS_OBS_MESSAGE_COUNTER_MSG2(u32val, 1);
    if (u32val != object_list[id].GetRollingCounter())
    {
        LOG(ERROR) << "mismatch rc in part b: " << u32val
                   << ", want: " << static_cast<uint32_t>(object_list[id].GetRollingCounter());
        return false;
    }
    u32val = GET_VIS_OBS_MSG_2_VIS_OBS_CUT_IN_OUT_01(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_2_VIS_OBS_CUT_IN_OUT_01(u32val, 1);
    object_list[id].SetCutInOut(u32val);
    u32val = GET_VIS_OBS_MSG_2_VIS_OBS_TTC_CONST_ACC_MODEL_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_2_VIS_OBS_TTC_CONST_ACC_MODEL_01(u32val, 1.0f);
    object_list[id].SetTtc(f32val);
    u32val = GET_VIS_OBS_MSG_2_VIS_OBS_LONG_ACCEL_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_2_VIS_OBS_LONG_ACCEL_01(u32val, 1.0f);
    object_list[id].SetLongAccel(f32val);
    /* set part b valid */
    object_list[id].SetPartBValid(true);
    return true;
}

bool_t Ifv300DriverT<HoloCanPacket>::ConstructObjectPartC(const HoloCanPacket&                        msg,
                                                          std::array<ObjectType, IFV300_OBJECTS_NUM>& object_list)
{
    uint8_t id = GET_VIS_OBS_MSG_3_VIS_OBS_COUNT_MSG3(msg.GetData());  //! no need CALC_* for this signal
    if (id > object_list.size())                                       /* maxval of id */
    {
        LOG(ERROR) << "invalid id in part a: " << static_cast<uint32_t>(id);
        return false;
    }
    if (id != object_list[id].GetObjectId())
    {
        LOG(ERROR) << "mismatch id in part c: " << id
                   << ", want: " << static_cast<uint32_t>(object_list[id].GetObjectId());
        return false;
    }
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_VIS_OBS_MSG_3_VIS_OBS_MESSAGE_COUNTER_MSG3(msg.GetData());
    u32val = CALC_VIS_OBS_MSG_3_VIS_OBS_MESSAGE_COUNTER_MSG3(u32val, 1);
    if (u32val != object_list[id].GetRollingCounter())
    {
        LOG(ERROR) << "mismatch rc in part c: " << u32val
                   << ", want: " << static_cast<uint32_t>(object_list[id].GetRollingCounter());
        return false;
    }
    u32val = GET_VIS_OBS_MSG_3_VIS_OBS_WIDTH_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_WIDTH_01(u32val, 1.0f);
    object_list[id].SetWidth(f32val);
    u32val = GET_VIS_OBS_MSG_3_VIS_OBS_LONG_VEL_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LONG_VEL_01(u32val, 1.0f);
    object_list[id].SetLongVel(f32val - vehicle_speed_);
    u32val = GET_VIS_OBS_MSG_3_VIS_OBS_LONG_POS_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LONG_POS_01(u32val, 1.0f);
    object_list[id].SetLongPos(f32val);
    u32val = GET_VIS_OBS_MSG_3_VIS_OBS_LAT_VEL_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LAT_VEL_01(u32val, 1.0f);
    object_list[id].SetLatVel(f32val);
    u32val = GET_VIS_OBS_MSG_3_VIS_OBS_LAT_POS_01(msg.GetData());
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LAT_POS_01(u32val, 1.0f);
    object_list[id].SetLatPos(f32val);
    /* set part c valid */
    object_list[id].SetPartCValid(true);
    /* check if reaches the end */
    if (id == IFV300_OBJECTS_NUM) /* max value when end of cycle */
    {
        if (obstacles_callback_)
        {
            ObstaclePtrListType obstalce_list;
            obstalce_list.SetCoordinate(extrinsic_.GetParentCoordinate());
            obstalce_list.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
            obstalce_list.SetSensorId(this->GetSensorId());
            ConvertToObstaclePtrListWithTransform(object_list_, obstalce_list);
            obstacles_callback_(obstalce_list);
        }
        /* clear valid flag */
        for (uint32_t i = 0; i < object_list_.size(); i++)
        {
            object_list_[i].SetPartAValid(false);
            object_list_[i].SetPartBValid(false);
            object_list_[i].SetPartCValid(false);
        }
    }
    return true;
}

void Ifv300DriverT<HoloCanPacket>::ConvertToObstaclePtrListWithTransform(
    const std::array<ObjectType, IFV300_OBJECTS_NUM>& input, ObstaclePtrListType& output) const
{
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.size() && out != output.GetObstacleList().end(); i++)
    {
        if (!input[i].IsValid())
        {
            continue;
        }
        if ((fabs(input[i].GetLatPos()) < 0.01) && (fabs(input[i].GetLongPos()) < 0.01))
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

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo

#endif
