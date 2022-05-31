/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_holocan.hpp
 * @brief A class to receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/04
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
void MobileyeDriverT<HoloCanPacket>::ParseData(const HoloCanPacket& msg)
{
    switch (msg.GetId())
    {
        case ID_Objects0_Signals_Message_Part0:
            for (ObjectListType::iterator it = object_list_.begin(); it != object_list_.end(); ++it)
            {
                it->SetPart0Valid(false);
                it->SetPart1Valid(false);
                it->SetPart2Valid(false);
                it->SetPart3Valid(false);
            }
            ConstructObjectPart0(msg, object_list_[0]);
            break;
        case ID_Objects0_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[0]);
            break;
        case ID_Objects0_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[0]);
            break;
        case ID_Objects0_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[0]);
            break;
        case ID_Objects1_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[1]);
            break;
        case ID_Objects1_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[1]);
            break;
        case ID_Objects1_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[1]);
            break;
        case ID_Objects1_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[1]);
            break;
        case ID_Objects2_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[2]);
            break;
        case ID_Objects2_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[2]);
            break;
        case ID_Objects2_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[2]);
            break;
        case ID_Objects2_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[2]);
            break;
        case ID_Objects3_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[3]);
            break;
        case ID_Objects3_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[3]);
            break;
        case ID_Objects3_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[3]);
            break;
        case ID_Objects3_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[3]);
            break;
        case ID_Objects4_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[4]);
            break;
        case ID_Objects4_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[4]);
            break;
        case ID_Objects4_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[4]);
            break;
        case ID_Objects4_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[4]);
            break;
        case ID_Objects5_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[5]);
            break;
        case ID_Objects5_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[5]);
            break;
        case ID_Objects5_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[5]);
            break;
        case ID_Objects5_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[5]);
            break;
        case ID_Objects6_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[6]);
            break;
        case ID_Objects6_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[6]);
            break;
        case ID_Objects6_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[6]);
            break;
        case ID_Objects6_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[6]);
            break;
        case ID_Objects7_Signals_Message_Part0:
            ConstructObjectPart0(msg, object_list_[7]);
            break;
        case ID_Objects7_Signals_Message_Part1:
            ConstructObjectPart1(msg, object_list_[7]);
            break;
        case ID_Objects7_Signals_Message_Part2:
            ConstructObjectPart2(msg, object_list_[7]);
            break;
        case ID_Objects7_Signals_Message_Part3:
            ConstructObjectPart3(msg, object_list_[7]);
            break;
        case ID_Objects_Signals_Header:
            ConstructObjectHeader(msg, object_header_);
            /* end of cycle */
            if (obstacles_callback_)
            {
                ObstaclePtrListType obstacles;
                obstacles.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
                obstacles.SetCoordinate(extrinsic_.GetParentCoordinate());
                obstacles.SetSensorId(this->GetSensorId());
                ConvertToObstaclePtrListWithTransform(object_header_, object_list_, obstacles);
                obstacles_callback_(obstacles);
            }
            /* clear valid flag */
            for (ObjectListType::iterator it = object_list_.begin(); it != object_list_.end(); ++it)
            {
                it->SetPart0Valid(false);
                it->SetPart1Valid(false);
                it->SetPart2Valid(false);
                it->SetPart3Valid(false);
            }
            break;
        case ID_Lane0_Signals_Message_Part0:
            /* start a new cycle */
            for (LineListType::iterator it = lane_boundary_list_.begin(); it != lane_boundary_list_.end(); ++it)
            {
                it->SetPart0Valid(false);
                it->SetPart1Valid(false);
                it->SetPart2Valid(false);
            }
            ConstructLaneboundaryPart0(msg, lane_boundary_list_[LKA_LEFT_INDEX]);
            break;
        case ID_Lane0_Signals_Message_Part1:
            ConstructLaneboundaryPart1(msg, lane_boundary_list_[LKA_LEFT_INDEX]);
            break;
        case ID_Lane0_Signals_Message_Part2:
            ConstructLaneboundaryPart2(msg, lane_boundary_list_[LKA_LEFT_INDEX]);
            break;
        case ID_Lane1_Signals_Message_Part0:
            ConstructLaneboundaryPart0(msg, lane_boundary_list_[LKA_RIGHT_INDEX]);
            break;
        case ID_Lane1_Signals_Message_Part1:
            ConstructLaneboundaryPart1(msg, lane_boundary_list_[LKA_RIGHT_INDEX]);
            break;
        case ID_Lane1_Signals_Message_Part2:
            ConstructLaneboundaryPart2(msg, lane_boundary_list_[LKA_RIGHT_INDEX]);
            break;
        case ID_Lane2_Signals_Message_Part0:
            ConstructLaneboundaryPart0(msg, lane_boundary_list_[NEXT_LEFT_INDEX]);
            break;
        case ID_Lane2_Signals_Message_Part1:
            ConstructLaneboundaryPart1(msg, lane_boundary_list_[NEXT_LEFT_INDEX]);
            break;
        case ID_Lane2_Signals_Message_Part2:
            ConstructLaneboundaryPart2(msg, lane_boundary_list_[NEXT_LEFT_INDEX]);
            break;
        case ID_Lane3_Signals_Message_Part0:
            ConstructLaneboundaryPart0(msg, lane_boundary_list_[NEXT_RIGHT_INDEX]);
            break;
        case ID_Lane3_Signals_Message_Part1:
            ConstructLaneboundaryPart1(msg, lane_boundary_list_[NEXT_RIGHT_INDEX]);
            break;
        case ID_Lane3_Signals_Message_Part2:
            ConstructLaneboundaryPart2(msg, lane_boundary_list_[NEXT_RIGHT_INDEX]);
            /* end of this cycle */
            if (roadframe_callback_)
            {
                RoadFrameType roadframe;
                roadframe.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
                ConvertToRoadFrameWithTransform(lane_boundary_list_, roadframe);
                roadframe_callback_(roadframe);
            }
            /* clear valid flag */
            for (LineListType::iterator it = lane_boundary_list_.begin(); it != lane_boundary_list_.end(); ++it)
            {
                it->SetPart0Valid(false);
                it->SetPart1Valid(false);
                it->SetPart2Valid(false);
            }
            break;
        default:
            break;
    }
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
