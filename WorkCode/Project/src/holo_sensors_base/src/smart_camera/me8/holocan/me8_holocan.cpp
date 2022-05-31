/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_holocan.cpp
 * @brief A class to receive and construct me8 outputs in holocan format
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
void Me8Driver::ParseData(const HoloCanPacket& msg)
{
    /* objects signals */
    if ((msg.GetId() >= ID_Objects_Signals_A1) && (msg.GetId() <= ID_Objects_Signals_C12))
    {
        ConstructObject(msg, object_list_);
    }
    else
    {
        switch (msg.GetId())
        {
            case ID_Objects_Header:
            {
                ConstructObjHeader(msg);
                break;
            }
            case ID_Lanes_Host_0:
            {
                /* start a new cycle */
                for (uint32_t i = 0; i < host_lane_boundary_list_.size(); i++)
                {
                    host_lane_boundary_list_[i].SetPartAValid(false);
                    host_lane_boundary_list_[i].SetPartBValid(false);
                }
                for (uint32_t i = 0; i < adjacent_lane_boundary_list_.size(); i++)
                {
                    adjacent_lane_boundary_list_[i].SetPartAValid(false);
                    adjacent_lane_boundary_list_[i].SetPartBValid(false);
                }
                ConstructLaneboundaryHostPartA(msg, host_lane_boundary_list_[0]);
                break;
            }
            case ID_Lanes_Host_1:
            {
                ConstructLaneboundaryHostPartB(msg, host_lane_boundary_list_[0]);
                break;
            }
            case ID_Lanes_Host_2:
            {
                ConstructLaneboundaryHostPartA(msg, host_lane_boundary_list_[1]);
                break;
            }
            case ID_Lanes_Host_3:
            {
                ConstructLaneboundaryHostPartB(msg, host_lane_boundary_list_[1]);
                break;
            }
            case ID_Lanes_Adjacent_Header:
            {
                break;
            }
            case ID_Lanes_Adjacent_1A:
            {
                ConstructLaneboundaryAdjacentPartA(msg, adjacent_lane_boundary_list_[0]);
                break;
            }
            case ID_Lanes_Adjacent_1B:
            {
                ConstructLaneboundaryAdjacentPartB(msg, adjacent_lane_boundary_list_[0]);
                break;
            }
            case ID_Lanes_Adjacent_2A:
            {
                ConstructLaneboundaryAdjacentPartA(msg, adjacent_lane_boundary_list_[1]);
                break;
            }
            case ID_Lanes_Adjacent_2B:
            {
                ConstructLaneboundaryAdjacentPartB(msg, adjacent_lane_boundary_list_[1]);
                break;
            }
            case ID_Lanes_Adjacent_3A:
            {
                ConstructLaneboundaryAdjacentPartA(msg, adjacent_lane_boundary_list_[2]);
                break;
            }
            case ID_Lanes_Adjacent_3B:
            {
                ConstructLaneboundaryAdjacentPartB(msg, adjacent_lane_boundary_list_[2]);
                break;
            }
            case ID_Lanes_Adjacent_4A:
            {
                ConstructLaneboundaryAdjacentPartA(msg, adjacent_lane_boundary_list_[3]);
                break;
            }
            case ID_Lanes_Adjacent_4B:
            {
                ConstructLaneboundaryAdjacentPartB(msg, adjacent_lane_boundary_list_[3]);

                if (roadframe_callback_)
                {
                    RoadFrameType roadframe;
                    roadframe.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
                    ConvertToRoadFrameWithTransform(roadframe);
                    roadframe_callback_(roadframe);
                }
                /* clear valid flag */
                for (uint32_t i = 0; i < host_lane_boundary_list_.size(); i++)
                {
                    host_lane_boundary_list_[i].SetPartAValid(false);
                    host_lane_boundary_list_[i].SetPartBValid(false);
                }
                for (uint32_t i = 0; i < adjacent_lane_boundary_list_.size(); i++)
                {
                    adjacent_lane_boundary_list_[i].SetPartAValid(false);
                    adjacent_lane_boundary_list_[i].SetPartBValid(false);
                }
                break;
            }
            /* flowing can message not use now, do nothing */
            case ID_Hazards_Header:
            {
                break;
            }
            case ID_Hazards_UTC:
            {
                break;
            }
            case ID_Hazards_0A:
            {
                break;
            }
            case ID_Hazards_0B:
            {
                break;
            }
            case ID_Hazards_1A:
            {
                break;
            }
            case ID_Hazards_1B:
            {
                break;
            }
            case ID_Hazards_2A:
            {
                break;
            }
            case ID_Hazards_2B:
            {
                break;
            }
            case ID_Hazards_3A:
            {
                break;
            }
            case ID_Hazards_3B:
            {
                break;
            }
            default:
                break;
        }
    }
}

}  // namespace me8
}  // namespace sensors
}  // namespace holo
