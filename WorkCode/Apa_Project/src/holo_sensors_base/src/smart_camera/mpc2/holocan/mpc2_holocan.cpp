/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_holocan.hpp
 * @brief A class to receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/08/24
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
void BoschMpcDriverT<HoloCanPacket>::ParseData(const HoloCanPacket& msg)
{
    switch (msg.GetId())
    {
        case ID_BV1_Lin_01_A:
            /* start a new cycle */
            for (uint32_t i = 0; i < lane_boundary_list_.size(); i++)
            {
                /* clear valid flag */
                lane_boundary_list_[i].SetPartAValid(false);
                lane_boundary_list_[i].SetPartBValid(false);
            }
            /* fetch lane head */
            ConstructLaneBoundaryPartA(msg, lane_boundary_list_[0]);
            break;
        case ID_BV1_Lin_01_B:
            ConstructLaneBoundaryPartB(msg, lane_boundary_list_[0]);
            break;
        case ID_BV1_Lin_02_A:
            ConstructLaneBoundaryPartA(msg, lane_boundary_list_[1]);
            break;
        case ID_BV1_Lin_02_B:
            ConstructLaneBoundaryPartB(msg, lane_boundary_list_[1]);
            break;
        case ID_BV1_Lin_03_A:
            ConstructLaneBoundaryPartA(msg, lane_boundary_list_[2]);
            break;
        case ID_BV1_Lin_03_B:
            ConstructLaneBoundaryPartB(msg, lane_boundary_list_[2]);
            break;
        case ID_BV1_Lin_04_A:
            ConstructLaneBoundaryPartA(msg, lane_boundary_list_[3]);
            break;
        case ID_BV1_Lin_04_B:
            ConstructLaneBoundaryPartB(msg, lane_boundary_list_[3]);
            /* end of this cycle */
            if (roadframe_callback_)
            {
                /* call service callback */
                RoadFrameType road_frame;
                ConvertToRoadFrameWithTransform(lane_boundary_list_, road_frame);
                roadframe_callback_(road_frame);
            }
            /* clear valid flag */
            for (uint32_t i = 0; i < lane_boundary_list_.size(); i++)
            {
                /* clear valid flag */
                lane_boundary_list_[i].SetPartAValid(false);
                lane_boundary_list_[i].SetPartBValid(false);
            }
            break;
        case ID_BV_Obj_01_A:
            /* start of cycle, clear valid flag */
            for (uint32_t i = 0; i < 16; i++)
            {
                object_list_[i].SetPartAValid(false);
                object_list_[i].SetPartBValid(false);
                object_list_[i].SetPartCValid(false);
                object_list_[i].SetPartDValid(false);
                object_list_[i].SetPartEValid(false);
            }
            ConstructObjectPartA(msg, object_list_[0]);
            break;
        case ID_BV_Obj_01_B:
            ConstructObjectPartB(msg, object_list_[0]);
            break;
        case ID_BV_Obj_01_C:
            ConstructObjectPartC(msg, object_list_[0]);
            break;
        case ID_BV_Obj_01_D:
            ConstructObjectPartD(msg, object_list_[0]);
            break;
        case ID_BV_Obj_01_E:
            ConstructObjectPartE(msg, object_list_[0]);
            break;
        case ID_BV_Obj_02_A:
            ConstructObjectPartA(msg, object_list_[1]);
            break;
        case ID_BV_Obj_02_B:
            ConstructObjectPartB(msg, object_list_[1]);
            break;
        case ID_BV_Obj_02_C:
            ConstructObjectPartC(msg, object_list_[1]);
            break;
        case ID_BV_Obj_02_D:
            ConstructObjectPartD(msg, object_list_[1]);
            break;
        case ID_BV_Obj_02_E:
            ConstructObjectPartE(msg, object_list_[1]);
            break;
        case ID_BV_Obj_03_A:
            ConstructObjectPartA(msg, object_list_[2]);
            break;
        case ID_BV_Obj_03_B:
            ConstructObjectPartB(msg, object_list_[2]);
            break;
        case ID_BV_Obj_03_C:
            ConstructObjectPartC(msg, object_list_[2]);
            break;
        case ID_BV_Obj_03_D:
            ConstructObjectPartD(msg, object_list_[2]);
            break;
        case ID_BV_Obj_03_E:
            ConstructObjectPartE(msg, object_list_[2]);
            break;
        case ID_BV_Obj_04_A:
            ConstructObjectPartA(msg, object_list_[3]);
            break;
        case ID_BV_Obj_04_B:
            ConstructObjectPartB(msg, object_list_[3]);
            break;
        case ID_BV_Obj_04_C:
            ConstructObjectPartC(msg, object_list_[3]);
            break;
        case ID_BV_Obj_04_D:
            ConstructObjectPartD(msg, object_list_[3]);
            break;
        case ID_BV_Obj_04_E:
            ConstructObjectPartE(msg, object_list_[3]);
            break;
        case ID_BV_Obj_05_A:
            ConstructObjectPartA(msg, object_list_[4]);
            break;
        case ID_BV_Obj_05_B:
            ConstructObjectPartB(msg, object_list_[4]);
            break;
        case ID_BV_Obj_05_C:
            ConstructObjectPartC(msg, object_list_[4]);
            break;
        case ID_BV_Obj_05_D:
            ConstructObjectPartD(msg, object_list_[4]);
            break;
        case ID_BV_Obj_05_E:
            ConstructObjectPartE(msg, object_list_[4]);
            break;
        case ID_BV_Obj_06_A:
            ConstructObjectPartA(msg, object_list_[5]);
            break;
        case ID_BV_Obj_06_B:
            ConstructObjectPartB(msg, object_list_[5]);
            break;
        case ID_BV_Obj_06_C:
            ConstructObjectPartC(msg, object_list_[5]);
            break;
        case ID_BV_Obj_06_D:
            ConstructObjectPartD(msg, object_list_[5]);
            break;
        case ID_BV_Obj_06_E:
            ConstructObjectPartE(msg, object_list_[5]);
            break;
        case ID_BV_Obj_07_A:
            ConstructObjectPartA(msg, object_list_[6]);
            break;
        case ID_BV_Obj_07_B:
            ConstructObjectPartB(msg, object_list_[6]);
            break;
        case ID_BV_Obj_07_C:
            ConstructObjectPartC(msg, object_list_[6]);
            break;
        case ID_BV_Obj_07_D:
            ConstructObjectPartD(msg, object_list_[6]);
            break;
        case ID_BV_Obj_07_E:
            ConstructObjectPartE(msg, object_list_[6]);
            break;
        case ID_BV_Obj_08_A:
            ConstructObjectPartA(msg, object_list_[7]);
            break;
        case ID_BV_Obj_08_B:
            ConstructObjectPartB(msg, object_list_[7]);
            break;
        case ID_BV_Obj_08_C:
            ConstructObjectPartC(msg, object_list_[7]);
            break;
        case ID_BV_Obj_08_D:
            ConstructObjectPartD(msg, object_list_[7]);
            break;
        case ID_BV_Obj_08_E:
            ConstructObjectPartE(msg, object_list_[7]);
            break;
        case ID_BV_Obj_09_A:
            ConstructObjectPartA(msg, object_list_[8]);
            break;
        case ID_BV_Obj_09_B:
            ConstructObjectPartB(msg, object_list_[8]);
            break;
        case ID_BV_Obj_09_C:
            ConstructObjectPartC(msg, object_list_[8]);
            break;
        case ID_BV_Obj_09_D:
            ConstructObjectPartD(msg, object_list_[8]);
            break;
        case ID_BV_Obj_09_E:
            ConstructObjectPartE(msg, object_list_[8]);
            break;
        case ID_BV_Obj_10_A:
            ConstructObjectPartA(msg, object_list_[9]);
            break;
        case ID_BV_Obj_10_B:
            ConstructObjectPartB(msg, object_list_[9]);
            break;
        case ID_BV_Obj_10_C:
            ConstructObjectPartC(msg, object_list_[9]);
            break;
        case ID_BV_Obj_10_D:
            ConstructObjectPartD(msg, object_list_[9]);
            break;
        case ID_BV_Obj_10_E:
            ConstructObjectPartE(msg, object_list_[9]);
            break;
        case ID_BV_Obj_11_A:
            ConstructObjectPartA(msg, object_list_[10]);
            break;
        case ID_BV_Obj_11_B:
            ConstructObjectPartB(msg, object_list_[10]);
            break;
        case ID_BV_Obj_11_C:
            ConstructObjectPartC(msg, object_list_[10]);
            break;
        case ID_BV_Obj_11_D:
            ConstructObjectPartD(msg, object_list_[10]);
            break;
        case ID_BV_Obj_11_E:
            ConstructObjectPartE(msg, object_list_[10]);
            break;
        case ID_BV_Obj_12_A:
            ConstructObjectPartA(msg, object_list_[11]);
            break;
        case ID_BV_Obj_12_B:
            ConstructObjectPartB(msg, object_list_[11]);
            break;
        case ID_BV_Obj_12_C:
            ConstructObjectPartC(msg, object_list_[11]);
            break;
        case ID_BV_Obj_12_D:
            ConstructObjectPartD(msg, object_list_[11]);
            break;
        case ID_BV_Obj_12_E:
            ConstructObjectPartE(msg, object_list_[11]);
            break;
        case ID_BV_Obj_13_A:
            ConstructObjectPartA(msg, object_list_[12]);
            break;
        case ID_BV_Obj_13_B:
            ConstructObjectPartB(msg, object_list_[12]);
            break;
        case ID_BV_Obj_13_C:
            ConstructObjectPartC(msg, object_list_[12]);
            break;
        case ID_BV_Obj_13_D:
            ConstructObjectPartD(msg, object_list_[12]);
            break;
        case ID_BV_Obj_13_E:
            ConstructObjectPartE(msg, object_list_[12]);
            break;
        case ID_BV_Obj_14_A:
            ConstructObjectPartA(msg, object_list_[13]);
            break;
        case ID_BV_Obj_14_B:
            ConstructObjectPartB(msg, object_list_[13]);
            break;
        case ID_BV_Obj_14_C:
            ConstructObjectPartC(msg, object_list_[13]);
            break;
        case ID_BV_Obj_14_D:
            ConstructObjectPartD(msg, object_list_[13]);
            break;
        case ID_BV_Obj_14_E:
            ConstructObjectPartE(msg, object_list_[13]);
            break;
        case ID_BV_Obj_15_A:
            ConstructObjectPartA(msg, object_list_[14]);
            break;
        case ID_BV_Obj_15_B:
            ConstructObjectPartB(msg, object_list_[14]);
            break;
        case ID_BV_Obj_15_C:
            ConstructObjectPartC(msg, object_list_[14]);
            break;
        case ID_BV_Obj_15_D:
            ConstructObjectPartD(msg, object_list_[14]);
            break;
        case ID_BV_Obj_15_E:
            ConstructObjectPartE(msg, object_list_[14]);
            break;
        case ID_BV_Obj_16_A:
            ConstructObjectPartA(msg, object_list_[15]);
            break;
        case ID_BV_Obj_16_B:
            ConstructObjectPartB(msg, object_list_[15]);
            break;
        case ID_BV_Obj_16_C:
            ConstructObjectPartC(msg, object_list_[15]);
            break;
        case ID_BV_Obj_16_D:
            ConstructObjectPartD(msg, object_list_[15]);
            break;
        case ID_BV_Obj_16_E:
            ConstructObjectPartE(msg, object_list_[15]);
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
            for (uint32_t i = 0; i < 16; i++)
            {
                object_list_[i].SetPartAValid(false);
                object_list_[i].SetPartBValid(false);
                object_list_[i].SetPartCValid(false);
                object_list_[i].SetPartDValid(false);
                object_list_[i].SetPartEValid(false);
            }
            break;
        case ID_RSR_Objects01_A:
            ConstructSpdLimitSign1PartA(msg, spd_limit_sign_list_[0]);
            break;
        case ID_RSR_Objects02_A:
            ConstructSpdLimitSign2PartA(msg, spd_limit_sign_list_[1]);
            break;
        case ID_RSR_Objects03_A:
            ConstructSpdLimitSign3PartA(msg, spd_limit_sign_list_[2]);
            break;
        case ID_RSR_Objects04_A:
            ConstructSpdLimitSign4PartA(msg, spd_limit_sign_list_[3]);
            break;
        case ID_RSR_Objects05_A:
            ConstructSpdLimitSign5PartA(msg, spd_limit_sign_list_[4]);
            break;
        case ID_RSR_Objects07_A:
            ConstructSpdLimitSign7PartA(msg, spd_limit_sign_list_[5]);
            break;
        case ID_RSR_Objects08_A:
            ConstructSpdLimitSign8PartA(msg, spd_limit_sign_list_[6]);
            if (spd_limit_sign_callback_)
            {
                SpdLimitSignListType sls;

                for (uint32_t i=0; i<sls.size(); i++)
                {
                    spd_limit_sign_list_[i].ConvertToHoloSpdLimtSign(sls[i]);
                }
                spd_limit_sign_callback_(sls);
            }
            break;
        default:
            break;
    }
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
