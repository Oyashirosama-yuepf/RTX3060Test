/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_holocan.hpp
 * @brief A class to receive and construct ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/04
 */

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
void Ifv300DriverT<HoloCanPacket>::ParseData(const HoloCanPacket& msg)
{
    switch (msg.GetId())
    {
        case ID_Vehicle_State_Info_1:
        {
            int16_t raw_i16val = GET_Vehicle_State_Info_1_CAN_VEHICLE_SPEED(msg.GetData());
            vehicle_speed_     = CALC_Vehicle_State_Info_1_CAN_VEHICLE_SPEED(raw_i16val, 1.0);
        }
        break;
        case ID_VIS_OBS_MSG_1:
            ConstructObjectPartA(msg, object_list_);
            break;
        case ID_VIS_OBS_MSG_2:
            ConstructObjectPartB(msg, object_list_);
            break;
        case ID_VIS_OBS_MSG_3:
            ConstructObjectPartC(msg, object_list_);
            break;
        case ID_VIS_LANE_INFORMATION:
            /* start a new cycle */
            for (uint32_t i = 0; i < lane_boundary_list_.size(); i++)
            {
                lane_boundary_list_[i].SetValid(false);
            }
            /* fetch lane head */
            ConstructLaneboundaryHeader(msg, lane_boundary_header_);
            break;
        case ID_VIS_LANE_NEAR_LEFT_INDIVIDUAL:
            ConstructLaneboundaryBody(msg, lane_boundary_list_[1]);
            break;
        case ID_VIS_LANE_NEAR_RIGHT_INDIVIDUAL:
            ConstructLaneboundaryBody(msg, lane_boundary_list_[2]);
            break;
        case ID_VIS_LANE_NEIGHBOR_RIGHT:
            ConstructLaneboundaryBody(msg, lane_boundary_list_[3]);
            break;
        case ID_VIS_LANE_NEIGHBOR_LEFT:
            ConstructLaneboundaryBody(msg, lane_boundary_list_[0]);
            /* end of this cycle */
            lane_boundary_list_[0].SetType(lane_boundary_header_.left_left_type);
            lane_boundary_list_[0].SetQuality(lane_boundary_header_.left_left_lkaconf);
            lane_boundary_list_[1].SetType(lane_boundary_header_.left_type);
            lane_boundary_list_[1].SetQuality(lane_boundary_header_.left_lkaconf);
            lane_boundary_list_[2].SetType(lane_boundary_header_.right_type);
            lane_boundary_list_[2].SetQuality(lane_boundary_header_.right_lkaconf);
            lane_boundary_list_[3].SetType(lane_boundary_header_.right_right_type);
            lane_boundary_list_[3].SetQuality(lane_boundary_header_.right_right_lkaconf);
            if (roadframe_callback_)
            {
                RoadFrameType roadframe;
                roadframe.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
                ConvertToRoadFrameWithTransform(lane_boundary_list_, roadframe);
                roadframe_callback_(roadframe);
            }
            /* clear valid flag */
            for (uint32_t i = 0; i < lane_boundary_list_.size(); i++)
            {
                lane_boundary_list_[i].SetValid(false);
            }
            break;
        default:
            break;
    }
}

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
