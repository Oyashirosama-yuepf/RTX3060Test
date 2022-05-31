/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_holocan.hpp
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
void HorizonMatrix2DriverT<HoloCanPacket>::ParseData(const HoloCanPacket& msg)
{
    switch (msg.GetId())
    {
        case ID_ObstacleStatusA:
            for (ObjectListType::iterator it = object_list_.begin(); it != object_list_.end(); ++it)
            {
                it->SetPartAValid(false);
                it->SetPartBValid(false);
                it->SetPartCValid(false);
            }
            break;
        case ID_ObstacleDataA1:
            ConstructObjectPartA(msg, object_list_[0]);
            break;
        case ID_ObstacleDataB1:
            ConstructObjectPartB(msg, object_list_[0]);
            break;
        case ID_ObstacleDataC1:
            ConstructObjectPartC(msg, object_list_[0]);
            break;
        case ID_ObstacleDataA2:
            ConstructObjectPartA(msg, object_list_[1]);
            break;
        case ID_ObstacleDataB2:
            ConstructObjectPartB(msg, object_list_[1]);
            break;
        case ID_ObstacleDataC2:
            ConstructObjectPartC(msg, object_list_[1]);
            break;
        case ID_ObstacleDataA3:
            ConstructObjectPartA(msg, object_list_[2]);
            break;
        case ID_ObstacleDataB3:
            ConstructObjectPartB(msg, object_list_[2]);
            break;
        case ID_ObstacleDataC3:
            ConstructObjectPartC(msg, object_list_[2]);
            break;
        case ID_ObstacleDataA4:
            ConstructObjectPartA(msg, object_list_[3]);
            break;
        case ID_ObstacleDataB4:
            ConstructObjectPartB(msg, object_list_[3]);
            break;
        case ID_ObstacleDataC4:
            ConstructObjectPartC(msg, object_list_[3]);
            break;
        case ID_ObstacleDataA5:
            ConstructObjectPartA(msg, object_list_[4]);
            break;
        case ID_ObstacleDataB5:
            ConstructObjectPartB(msg, object_list_[4]);
            break;
        case ID_ObstacleDataC5:
            ConstructObjectPartC(msg, object_list_[4]);
            break;
        case ID_ObstacleDataA6:
            ConstructObjectPartA(msg, object_list_[5]);
            break;
        case ID_ObstacleDataB6:
            ConstructObjectPartB(msg, object_list_[5]);
            break;
        case ID_ObstacleDataC6:
            ConstructObjectPartC(msg, object_list_[5]);
            break;
        case ID_ObstacleDataA7:
            ConstructObjectPartA(msg, object_list_[6]);
            break;
        case ID_ObstacleDataB7:
            ConstructObjectPartB(msg, object_list_[6]);
            break;
        case ID_ObstacleDataC7:
            ConstructObjectPartC(msg, object_list_[6]);
            break;
        case ID_ObstacleDataA8:
            ConstructObjectPartA(msg, object_list_[7]);
            break;
        case ID_ObstacleDataB8:
            ConstructObjectPartB(msg, object_list_[7]);
            break;
        case ID_ObstacleDataC8:
            ConstructObjectPartC(msg, object_list_[7]);
            break;
        case ID_ObstacleDataA9:
            ConstructObjectPartA(msg, object_list_[8]);
            break;
        case ID_ObstacleDataB9:
            ConstructObjectPartB(msg, object_list_[8]);
            break;
        case ID_ObstacleDataC9:
            ConstructObjectPartC(msg, object_list_[8]);
            break;
        case ID_ObstacleDataA10:
            ConstructObjectPartA(msg, object_list_[9]);
            break;
        case ID_ObstacleDataB10:
            ConstructObjectPartB(msg, object_list_[9]);
            break;
        case ID_ObstacleDataC10:
            ConstructObjectPartC(msg, object_list_[9]);
            /* end of cycle */
            if (obstacles_callback_)
            {
                ObstaclePtrListType obstacles;
                obstacles.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
                obstacles.SetCoordinate(extrinsic_.GetParentCoordinate());
                obstacles.SetSensorId(this->GetSensorId());
                ConvertToObstaclePtrListWithTransform(object_list_, obstacles);
                obstacles_callback_(obstacles);
            }
            /* clear valid flag */
            for (ObjectListType::iterator it = object_list_.begin(); it != object_list_.end(); ++it)
            {
                it->SetPartAValid(false);
                it->SetPartBValid(false);
                it->SetPartCValid(false);
            }
            break;
        case ID_LKA_Left_Lane_A:
            /* start a new cycle */
            for (LineListType::iterator it = lane_boundary_list_.begin(); it != lane_boundary_list_.end(); ++it)
            {
                it->SetPartAValid(false);
                it->SetPartBValid(false);
            }
            ConstructLaneboundaryPartA(msg, lane_boundary_list_[LKA_LEFT_INDEX]);
            break;
        case ID_LKA_Left_Lane_B:
            ConstructLaneboundaryPartB(msg, lane_boundary_list_[LKA_LEFT_INDEX]);
            break;
        case ID_LKA_Right_Lane_A:
            ConstructLaneboundaryPartA(msg, lane_boundary_list_[LKA_RIGHT_INDEX]);
            break;
        case ID_LKA_Right_Lane_B:
            ConstructLaneboundaryPartB(msg, lane_boundary_list_[LKA_RIGHT_INDEX]);
            break;
        case ID_Next_Left_Lane_A:
            ConstructLaneboundaryPartA(msg, lane_boundary_list_[NEXT_LEFT_INDEX]);
            break;
        case ID_Next_Left_Lane_B:
            ConstructLaneboundaryPartB(msg, lane_boundary_list_[NEXT_LEFT_INDEX]);
            break;
        case ID_Next_Right_Lane_A:
            ConstructLaneboundaryPartA(msg, lane_boundary_list_[NEXT_RIGHT_INDEX]);
            break;
        case ID_Next_Right_Lane_B:
            ConstructLaneboundaryPartB(msg, lane_boundary_list_[NEXT_RIGHT_INDEX]);
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
                it->SetPartAValid(false);
                it->SetPartBValid(false);
            }
            break;
        default:
            break;
    }
}

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
