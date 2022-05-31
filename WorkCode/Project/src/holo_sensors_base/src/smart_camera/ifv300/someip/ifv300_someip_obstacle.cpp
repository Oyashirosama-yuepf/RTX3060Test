/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_someip_obstacle.hpp
 * @brief A class to receive and construct aptive ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_someip.h>
#include <holo_c/sensors/dbc/ifv300_output_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace ifv300
{
void Ifv300DriverT<SomeipPacketType>::Convert(const IfvObjectRawData&        input,
                                              std::shared_ptr<ObstacleType>& output) const
{
    bool_t     boolval;
    uint8_t    u8val;
    float32_t  f32val;
    ObjectType object;
    /* timestamp */
    holo::common::Timestamp stamp(input.timestamp.sec, input.timestamp.nsec);
    object.SetTimestamp(stamp);
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LONG_POS_01(input.part_C.long_pos, 1.0);
    object.SetLongPos(f32val);
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LAT_POS_01(input.part_C.lat_pos, 1.0);
    object.SetLatPos(f32val);
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LONG_VEL_01(input.part_C.long_vel, 1.0);
    object.SetLongVel(f32val - vehicle_speed_);
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_LAT_VEL_01(input.part_C.lat_vel, 1.0);
    object.SetLatVel(f32val);
    f32val = CALC_VIS_OBS_MSG_2_VIS_OBS_LONG_ACCEL_01(input.part_B.long_accel, 1.0);
    object.SetLongAccel(f32val);
    f32val = CALC_VIS_OBS_MSG_3_VIS_OBS_WIDTH_01(input.part_C.width, 1.0);
    object.SetWidth(f32val);
    f32val = CALC_VIS_OBS_MSG_1_VIS_OBS_HEIGHT_01(input.part_A.height, 1.0);
    object.SetHeight(f32val);
    f32val = CALC_VIS_OBS_MSG_2_VIS_OBS_TTC_CONST_ACC_MODEL_01(input.part_B.ttc_const_acc_model, 1.0);
    object.SetTtc(f32val);
    u8val = CALC_VIS_OBS_MSG_1_VIS_OBS_COUNT_MSG1(input.part_A.count_msg1, 1);
    object.SetObjectId(u8val);
    u8val = CALC_VIS_OBS_MSG_1_VIS_OBS_CLASSIFICATION_01(input.part_A.classification, 1);
    object.SetClassification(u8val);
    u8val = CALC_VIS_OBS_MSG_1_VIS_OBS_BRAKE_LIGHT_INDIC_01(input.part_A.brake_light_indicator, 1);
    object.SetBrakeLightInd(u8val);
    u8val = CALC_VIS_OBS_MSG_1_VIS_OBS_TURN_INDICATOR_01(input.part_A.turn_indicator, 1);
    object.SetTurnInd(u8val);
    u8val = CALC_VIS_OBS_MSG_2_VIS_OBS_CUT_IN_OUT_01(input.part_B.cut_in_cut_out, 1);
    object.SetCutInOut(u8val);
    u8val = CALC_VIS_OBS_MSG_1_VIS_OBS_MESSAGE_COUNTER_MSG1(input.part_A.message_counter_msg1, 1);
    object.SetRollingCounter(u8val);
    boolval = CALC_VIS_OBS_MSG_1_VIS_OBS_PED_WAIST_UP_01(input.part_A.ped_waise_up, 1);
    object.SetPedWaistUp(boolval);
    object.SetPartAValid(true);
    object.SetPartBValid(true);
    object.SetPartCValid(true);
    /* convert */
    object.ConvertToHoloObstacleWithTransform(*output, extrinsic_);
}

void Ifv300DriverT<SomeipPacketType>::Convert(const IfvObjectListRawData& input, ObstaclePtrListType& output) const
{
    /* parse data */
    uint32_t objnum = 0;
    auto     out    = output.GetObstacleList().begin();
    for (uint32_t i = 0; i < input.num && out != output.GetObstacleList().end(); i++)
    {
        if (input.object[i].part_A.count_msg1 != input.object[i].part_B.count_msg2)
        {
            continue;
        }
        if (input.object[i].part_A.count_msg1 != input.object[i].part_C.count_msg3)
        {
            continue;
        }
        if (input.object[i].part_A.message_counter_msg1 != input.object[i].part_B.message_counter_msg2)
        {
            continue;
        }
        if (input.object[i].part_A.message_counter_msg1 != input.object[i].part_C.message_counter_msg3)
        {
            continue;
        }
        float32_t long_pos = CALC_VIS_OBS_MSG_3_VIS_OBS_LONG_POS_01(input.object[i].part_C.long_pos, 1.0);
        float32_t lat_pos  = CALC_VIS_OBS_MSG_3_VIS_OBS_LAT_POS_01(input.object[i].part_C.lat_pos, 1.0);
        if ((fabs(lat_pos) < 0.01) && (fabs(long_pos) < 0.01))
        {
            continue;
        }
        *out = std::make_shared<ObstacleType>();
        (*out)->SetSensorId(this->GetSensorId());
        Convert(input.object[i], *out++);
        objnum++;
    }
    output.SetSize(objnum);
}

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
