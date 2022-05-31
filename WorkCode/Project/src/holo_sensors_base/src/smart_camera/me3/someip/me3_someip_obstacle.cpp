/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_someip_obstacle.hpp
 * @brief A class to receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me3/me3_someip.h>
#include <holo_c/sensors/mobileye/mobileye_dbc_output.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace mobileye
{
void MobileyeDriverT<SomeipPacketType>::Convert(const MobileyeObjectRawData&   input,
                                                std::shared_ptr<ObstacleType>& output) const
{
    bool_t     boolval;
    uint8_t    u8val;
    uint16_t   u16val;
    float32_t  f32val;
    ObjectType object;
    object.SetTimestamp(holo::common::Timestamp(input.timestamp.sec, input.timestamp.nsec));
    f32val = CALC_Objects0_Signals_Message_Part0_Objects_Longitudial_Dist_Obj0(input.longitudial_dist, 1.0f);
    object.SetLongitudinalDist(f32val);
    f32val = CALC_Objects0_Signals_Message_Part2_Objects_Lateral_Distance_Obj0(input.lateral_distance, 1.0f);
    object.SetLateralDist(f32val);
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Relative_Velocity_Obj0(input.relative_velocity, 1.0f);
    object.SetLongitudinalVelocity(f32val);
    f32val = CALC_Objects0_Signals_Message_Part3_Objects_Lateral_Velocity_Obj0(input.lateral_velocity, 1.0f);
    object.SetLateralVelocity(f32val);
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Acceleration_Abs_Obj0(input.acceleration_abs, 1.0f);
    object.SetAcceleration(f32val);
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Width_Obj0(input.width, 1.0f);
    object.SetWidth(f32val);
    f32val = CALC_Objects0_Signals_Message_Part0_Objects_Angle_Left_Obj0(input.angle_left, 1.0f);
    object.SetAngleLeft(f32val);
    f32val = CALC_Objects0_Signals_Message_Part1_Objects_Angle_Right_Obj0(input.angle_right, 1.0f);
    object.SetAngleRight(f32val);
    f32val = CALC_Objects0_Signals_Message_Part2_Objects_Angle_Rate_Mean_Obj0(input.angle_rate_mean, 1.0f);
    object.SetAngleRateMean(f32val);
    u16val = CALC_Objects0_Signals_Message_Part3_Objects_Object_Age_Obj0(input.object_age, 1);
    object.SetObjectAge(u16val);
    u8val = CALC_Objects0_Signals_Message_Part0_Objects_ID_Obj0(input.id, 1);
    object.SetId(u8val);
    u8val = CALC_Objects0_Signals_Message_Part0_Objects_Object_Class_Obj0(input.object_class, 1);
    object.SetObjectClass(u8val);
    u8val = CALC_Objects0_Signals_Message_Part0_Objects_Motion_Status_Obj0(input.motion_status, 1);
    object.SetMotionStatus(u8val);
    u8val = CALC_Objects0_Signals_Message_Part2_Objects_Cut_In_Cut_Out_Obj0(input.cut_in_cut_out, 1);
    object.SetCutInOut(u8val);
    boolval = CALC_Objects0_Signals_Message_Part3_Objects_ObstacleReplaced_Obj0(input.obstacle_replaced, 1);
    object.SetReplaced(boolval);
    boolval = CALC_Objects0_Signals_Message_Part3_Objects_CIPVFlag_Obj0(input.cipv_flag, 1);
    object.SetCipvFlag(boolval);
    object.SetPart0Valid(true);
    object.SetPart1Valid(true);
    object.SetPart2Valid(true);
    object.SetPart3Valid(true);
    /* convert */
    object.ConvertToHoloObstacleWithTransform(*output, extrinsic_);
}

void MobileyeDriverT<SomeipPacketType>::Convert(const MobileyeObjectListRawData& input,
                                                ObstaclePtrListType&             output) const
{
    uint32_t                                                                                        objnum = 0;
    std::map<uint8_t, uint8_t>                                                                      object_map;
    std::array<std::shared_ptr<ObstacleType>, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>::iterator out =
        output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.num && out != output.GetObstacleList().end(); i++)
    {
        if (input.object[i].id < 1) /* MIN_Objects0_Signals_Message_Part0_Objects_ID_Obj0 */
        {
            continue;
        }
        if (object_map.count(input.object[i].id))
        {
            LOG(WARNING) << "ignore object with duplicated id: " << input.object[i].id;
            continue;
        }
        object_map.insert(std::make_pair(input.object[i].id, 0));
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        Convert(input.object[i], *out++);
        objnum++;
    }
    output.SetSize(objnum);
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
