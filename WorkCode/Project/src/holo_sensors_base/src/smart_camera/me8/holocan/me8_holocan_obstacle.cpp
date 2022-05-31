/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_holocan_obstacle.cpp
 * @brief A class to receive and construct me8 obstacles in holocan format
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021-12-10
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me8/me8_holocan.h>

namespace holo
{
namespace sensors
{
namespace me8
{
void Me8Driver::ConstructObjHeader(const HoloCanPacket& msg)
{
    // reserve to do something
    (void)msg;
}

void Me8Driver::ConstructObject(const HoloCanPacket& msg, ObjectListType& object_list)
{
    int32_t obs_msg_cnt = msg.GetId() - ID_Objects_Signals_A1;
    if ((obs_msg_cnt < 0) || (obs_msg_cnt >= static_cast<int32_t>(object_list.size() * 3)))
    {
        LOG(ERROR) << "Input msg id is invalid! ID: " << static_cast<uint32_t>(msg.GetId());
        return;
    }

    uint32_t  u32val;
    float32_t f32val;
    switch (obs_msg_cnt % 3)
    {
        case 0: /* part A */
        {
            /* all obs use Id=1 function, because they're all the same */
            if (0 == obs_msg_cnt)
            {
                /* clear valid flag */
                for (uint32_t i = 0; i < object_list.size(); i++)
                {
                    object_list[i].SetPartAValid(false);
                    object_list[i].SetPartBValid(false);
                    object_list[i].SetPartCValid(false);
                }
            }

            u32val = GET_Objects_Signals_A1_Obj_ID_1(msg.GetData());
            u32val = CALC_Objects_Signals_A1_Obj_ID_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetObjectId(obs_msg_cnt);
            u32val = GET_Objects_Signals_A1_Object_Class_1(msg.GetData());
            u32val = CALC_Objects_Signals_A1_Object_Class_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetObjectClass(u32val);
            u32val = GET_Objects_Signals_A1_OBJ_Width_1(msg.GetData());
            f32val = CALC_Objects_Signals_A1_OBJ_Width_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetObjectWidth(f32val);
            u32val = GET_Objects_Signals_A1_OBJ_Length_1(msg.GetData());
            f32val = CALC_Objects_Signals_A1_OBJ_Length_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetObjectLength(f32val);
            u32val = GET_Objects_Signals_A1_Relative_Long_Velocity_1(msg.GetData());
            f32val = CALC_Objects_Signals_A1_Relative_Long_Velocity_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetRelativeLongVelocity(f32val);
            u32val = GET_Objects_Signals_A1_OBJ_Lane_Assignment_1(msg.GetData());
            u32val = CALC_Objects_Signals_A1_OBJ_Lane_Assignment_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetLaneAssignment(u32val);
            u32val = GET_Objects_Signals_A1_Relative_Lat_Velocity_1(msg.GetData());
            f32val = CALC_Objects_Signals_A1_Relative_Lat_Velocity_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetRelativeLatVelocity(f32val);
            object_list[obs_msg_cnt/3].SetPartAValid(true);
            break;
        }
        case 1: /* part B */
        {
            u32val = GET_Objects_Signals_B1_Absolute_Long_Acc_1(msg.GetData());
            f32val = CALC_Objects_Signals_B1_Absolute_Long_Acc_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetAbsoluteLongAcc(f32val);
            u32val = GET_Objects_Signals_B1_Long_Distance_1(msg.GetData());
            f32val = CALC_Objects_Signals_B1_Long_Distance_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetLongDistanceAcc(f32val);
            u32val = GET_Objects_Signals_B1_Lateral_Distance_1(msg.GetData());
            f32val = CALC_Objects_Signals_B1_Lateral_Distance_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetLateralDistance(f32val);
            object_list[obs_msg_cnt/3].SetPartBValid(true);
            break;
        }
        case 2: /* part C */
        {
            u32val = GET_Objects_Signals_C1_Absolute_Speed_1(msg.GetData());
            f32val = CALC_Objects_Signals_C1_Absolute_Speed_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetAbsoluteSpeed(f32val);
            u32val = GET_Objects_Signals_C1_OBJ_Motion_Status_1(msg.GetData());
            u32val = CALC_Objects_Signals_C1_OBJ_Motion_Status_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetObjectMotionStatus(u32val);
            u32val = GET_Objects_Signals_C1_OBJ_Motion_Category_1(msg.GetData());
            u32val = CALC_Objects_Signals_C1_OBJ_Motion_Category_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetObjectMotionCategory(u32val);
            u32val = GET_Objects_Signals_C1_Brake_Light_1(msg.GetData());
            u32val = CALC_Objects_Signals_C1_Brake_Light_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetBrakeLight(bool_t(u32val));
            u32val = GET_Objects_Signals_C1_Turn_Indicator_Right_1(msg.GetData());
            u32val = CALC_Objects_Signals_C1_Turn_Indicator_Right_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetTurnIndicatorRight(bool_t(u32val));
            u32val = GET_Objects_Signals_C1_Turn_Indicator_Left_1(msg.GetData());
            u32val = CALC_Objects_Signals_C1_Turn_Indicator_Left_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetTurnIndicatorLeft(bool_t(u32val));
            u32val = GET_Objects_Signals_C1_Light_indicator_validity_1(msg.GetData());
            u32val = CALC_Objects_Signals_C1_Light_indicator_validity_1(u32val, 1);
            object_list[obs_msg_cnt/3].SetLightIndicatorValidity(bool_t(u32val));
            u32val = GET_Objects_Signals_C1_OBJ_Angle_Mid_1(msg.GetData());
            f32val = CALC_Objects_Signals_C1_OBJ_Angle_Mid_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetObjectAngleMid(f32val);
            u32val = GET_Objects_Signals_C1_OBJ_Angle_Rate_1(msg.GetData());
            f32val = CALC_Objects_Signals_C1_OBJ_Angle_Rate_1(u32val, 1.0f);
            object_list[obs_msg_cnt/3].SetObjectAngleRate(f32val);
            object_list[obs_msg_cnt/3].SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
            object_list[obs_msg_cnt/3].SetPartCValid(true);

            /* check if reaches the end */
            if (obs_msg_cnt == (ME8_OBJECTS_NUM * 3 - 1))
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
            break;
        }
        default:

            break;
    }
}

void Me8Driver::ConvertToObstaclePtrListWithTransform(ObjectListType& input, ObstaclePtrListType& output) const
{
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.size() && out != output.GetObstacleList().end(); i++)
    {
        if (!input[i].IsValid())
        {
            continue;
        }
        if ((fabs(input[i].GetLateralDistance()) < 0.01) && (fabs(input[i].GetLongDistanceAcc()) < 0.01))
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

}  // namespace me8
}  // namespace sensors
}  // namespace holo