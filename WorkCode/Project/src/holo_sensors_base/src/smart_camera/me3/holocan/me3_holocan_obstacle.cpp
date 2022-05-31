/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_holocan_obstacle.hpp
 * @brief A class to receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me3/me3_holocan.h>
#include <holo_c/sensors/mobileye/mobileye_dbc_output.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace mobileye
{
void MobileyeDriverT<HoloCanPacket>::ConstructObjectHeader(const HoloCanPacket& msg, ObjectHeader& header)
{
    header.object_num = GET_Objects_Signals_Header_Number_Of_Video_Objects(msg.GetData());
}

void MobileyeDriverT<HoloCanPacket>::ConstructObjectPart0(const HoloCanPacket& msg, ObjectType& object)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Objects0_Signals_Message_Part0_Objects_Angle_Left_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part0_Objects_Angle_Left_Obj0(rawval, 1.0f);
    object.SetAngleLeft(f32val);
    rawval = GET_Objects0_Signals_Message_Part0_Objects_Motion_Status_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part0_Objects_Motion_Status_Obj0(rawval, 1);
    object.SetMotionStatus(rawval);
    rawval = GET_Objects0_Signals_Message_Part0_Objects_Longitudial_Dist_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part0_Objects_Longitudial_Dist_Obj0(rawval, 1.0f);
    object.SetLongitudinalDist(f32val);
    rawval = GET_Objects0_Signals_Message_Part0_Objects_ID_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part0_Objects_ID_Obj0(rawval, 1);
    object.SetId(rawval);
    rawval = GET_Objects0_Signals_Message_Part0_Objects_Object_Class_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part0_Objects_Object_Class_Obj0(rawval, 1);
    object.SetObjectClass(rawval);
    object.SetPart0Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConstructObjectPart1(const HoloCanPacket& msg, ObjectType& object)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Objects0_Signals_Message_Part1_Objects_Width_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Width_Obj0(rawval, 1.0f);
    object.SetWidth(f32val);
    rawval = GET_Objects0_Signals_Message_Part1_Objects_Relative_Velocity_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Relative_Velocity_Obj0(rawval, 1.0f);
    object.SetLongitudinalVelocity(f32val);
    rawval = GET_Objects0_Signals_Message_Part1_Objects_Acceleration_Abs_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Acceleration_Abs_Obj0(rawval, 1.0f);
    object.SetAcceleration(f32val);
    rawval = GET_Objects0_Signals_Message_Part1_Objects_Angle_Right_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Angle_Right_Obj0(rawval, 1.0f);
    object.SetAngleRight(f32val);
    object.SetPart1Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConstructObjectPart2(const HoloCanPacket& msg, ObjectType& object)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Objects0_Signals_Message_Part2_Objects_Lateral_Distance_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part2_Objects_Lateral_Distance_Obj0(rawval, 1.0f);
    object.SetLateralDist(f32val);
    rawval = GET_Objects0_Signals_Message_Part2_Objects_Angle_Rate_Mean_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part2_Objects_Angle_Rate_Mean_Obj0(rawval, 1.0f);
    object.SetAngleRateMean(f32val);
    rawval = GET_Objects0_Signals_Message_Part2_Objects_Cut_In_Cut_Out_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part2_Objects_Cut_In_Cut_Out_Obj0(rawval, 1);
    object.SetCutInOut(rawval);
    object.SetPart2Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConstructObjectPart3(const HoloCanPacket& msg, ObjectType& object)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Objects0_Signals_Message_Part3_Objects_Object_Age_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part3_Objects_Object_Age_Obj0(rawval, 1);
    object.SetObjectAge(rawval);
    rawval = GET_Objects0_Signals_Message_Part3_Objects_Lateral_Velocity_Obj0(msg.GetData());
    f32val = CALC_Objects0_Signals_Message_Part3_Objects_Lateral_Velocity_Obj0(rawval, 1.0f);
    object.SetLateralVelocity(f32val);
    rawval = GET_Objects0_Signals_Message_Part3_Objects_ObstacleReplaced_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part3_Objects_ObstacleReplaced_Obj0(rawval, 1);
    object.SetReplaced(bool_t(rawval));
    rawval = GET_Objects0_Signals_Message_Part3_Objects_CIPVFlag_Obj0(msg.GetData());
    rawval = CALC_Objects0_Signals_Message_Part3_Objects_CIPVFlag_Obj0(rawval, 1);
    object.SetCipvFlag(bool_t(rawval));
    object.SetPart3Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConvertToObstaclePtrListWithTransform(const ObjectHeader&   header,
                                                                           const ObjectListType& input,
                                                                           ObstaclePtrListType&  output) const
{
    uint32_t                   objnum = 0;
    std::map<uint8_t, uint8_t> object_map;
    object_map.clear();
    std::array<std::shared_ptr<ObstacleType>, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>::iterator out =
        output.GetObstacleList().begin();
    for (uint32_t i = 0; i < header.object_num && i < input.size() && out != output.GetObstacleList().end(); i++)
    {
        if (!input[i].IsAllPartsValid())
        {
            continue;
        }
        if (input[i].GetId() < MIN_Objects0_Signals_Message_Part0_Objects_ID_Obj0)
        {
            continue;
        }
        if (object_map.count(input[i].GetId()))
        {
            LOG(WARNING) << "ignore object with duplicated id: " << static_cast<uint32_t>(input[i].GetId());
            continue;
        }
        object_map.insert(std::make_pair(input[i].GetId(), 0));
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        input[i].ConvertToHoloObstacleWithTransform(**out++, extrinsic_);
        objnum++;
    }
    output.SetSize(objnum);
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
