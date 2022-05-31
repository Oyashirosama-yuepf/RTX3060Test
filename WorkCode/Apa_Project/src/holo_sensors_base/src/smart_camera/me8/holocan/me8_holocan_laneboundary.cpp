/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_holocan_laneboundary.cpp
 * @brief A class to receive and construct me8 laneboundarys in holocan format
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021-12-16
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me8/me8_holocan.h>

namespace holo
{
namespace sensors
{
namespace me8
{
void Me8Driver::ConstructLaneboundaryHostPartA(const HoloCanPacket& msg, LineTypeHost& host_lane_boundary)
{
    if ((msg.GetId() != ID_Lanes_Host_0) && (msg.GetId() != ID_Lanes_Host_2))
    {
        LOG(ERROR) << "Construct laneboundary host part A faild, ID: " << static_cast<uint32_t>(msg.GetId());
        return;
    }
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_Lanes_Host_0_LH_Confidence(msg.GetData());
    f32val = CALC_Lanes_Host_0_LH_Confidence(u32val, 1.0f);
    host_lane_boundary.SetLHConfidence(f32val);
    u32val = GET_Lanes_Host_0_LH_Lanemark_Type(msg.GetData());
    u32val = CALC_Lanes_Host_0_LH_Lanemark_Type(u32val, 1);
    host_lane_boundary.SetLHLanemarkType(u32val);
    u32val = GET_Lanes_Host_0_LH_Side(msg.GetData());
    u32val = CALC_Lanes_Host_0_LH_Side(u32val, 1);
    host_lane_boundary.SetLHSide(u32val);
    u32val = GET_Lanes_Host_0_LH_VR_Start(msg.GetData());
    f32val = CALC_Lanes_Host_0_LH_VR_Start(u32val, 1.0f);
    host_lane_boundary.SetLHVrStart(f32val);
    u32val = GET_Lanes_Host_0_LH_VR_End(msg.GetData());
    f32val = CALC_Lanes_Host_0_LH_VR_End(u32val, 1.0f);
    host_lane_boundary.SetLHVrEnd(f32val);

    host_lane_boundary.SetPartAValid(true);
}

void Me8Driver::ConstructLaneboundaryHostPartB(const HoloCanPacket& msg, LineTypeHost& host_lane_boundary)
{
    if ((msg.GetId() != ID_Lanes_Host_1) && (msg.GetId() != ID_Lanes_Host_3))
    {
        LOG(ERROR) << "Construct laneboundary host part B faild, ID: " << static_cast<uint32_t>(msg.GetId());
        return;
    }
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_Lanes_Host_1_LH_C0(msg.GetData());
    f32val = CALC_Lanes_Host_1_LH_C0(u32val, 1.0f);
    host_lane_boundary.SetLHC0(f32val);
    u32val = GET_Lanes_Host_1_LH_C1(msg.GetData());
    f32val = CALC_Lanes_Host_1_LH_C1(u32val, 1.0f);
    host_lane_boundary.SetLHC1(f32val);
    u32val = GET_Lanes_Host_1_LH_C2(msg.GetData());
    f32val = CALC_Lanes_Host_1_LH_C2(u32val, 1.0f);
    host_lane_boundary.SetLHC2(f32val);
    u32val = GET_Lanes_Host_1_LH_C3(msg.GetData());
    f32val = CALC_Lanes_Host_1_LH_C3(u32val, 1.0f);
    host_lane_boundary.SetLHC3(f32val);

    host_lane_boundary.SetPartBValid(true);
}

void Me8Driver::ConstructLaneboundaryAdjacentPartA(const HoloCanPacket& msg, LineTypeAdjacent& adjacent_lane_boundary)
{
    if ((msg.GetId() != ID_Lanes_Adjacent_1A) && (msg.GetId() != ID_Lanes_Adjacent_2A) &&
        (msg.GetId() != ID_Lanes_Adjacent_3A) && (msg.GetId() != ID_Lanes_Adjacent_4A))
    {
        LOG(ERROR) << "Construct laneboundary adjacent part B faild, ID: " << static_cast<uint32_t>(msg.GetId());
        return;
    }
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_Lanes_Adjacent_1A_Adjacent_Type_1(msg.GetData());
    u32val = CALC_Lanes_Adjacent_1A_Adjacent_Type_1(u32val, 1);
    adjacent_lane_boundary.SetAdjacentType(u32val);
    u32val = GET_Lanes_Adjacent_1A_Adjacent_Confidence_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1A_Adjacent_Confidence_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentConfidence(f32val);
    u32val = GET_Lanes_Adjacent_1A_Adjacent_View_Range_Start_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1A_Adjacent_View_Range_Start_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentViewRangeStart(f32val);
    u32val = GET_Lanes_Adjacent_1A_Adjacent_View_Range_End_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1A_Adjacent_View_Range_End_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentViewRangeEnd(f32val);

    adjacent_lane_boundary.SetPartAValid(true);
}

void Me8Driver::ConstructLaneboundaryAdjacentPartB(const HoloCanPacket& msg, LineTypeAdjacent& adjacent_lane_boundary)
{
    if ((msg.GetId() != ID_Lanes_Adjacent_1B) && (msg.GetId() != ID_Lanes_Adjacent_2B) &&
        (msg.GetId() != ID_Lanes_Adjacent_3B) && (msg.GetId() != ID_Lanes_Adjacent_4B))
    {
        LOG(ERROR) << "Construct laneboundary adjacent part B faild, ID: " << static_cast<uint32_t>(msg.GetId());
        return;
    }
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_Lanes_Adjacent_1B_Adjacent_Line_C0_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1B_Adjacent_Line_C0_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentC0(f32val);
    u32val = GET_Lanes_Adjacent_1B_Adjacent_Line_C1_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1B_Adjacent_Line_C1_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentC1(f32val);
    u32val = GET_Lanes_Adjacent_1B_Adjacent_Line_C2_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1B_Adjacent_Line_C2_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentC2(f32val);
    u32val = GET_Lanes_Adjacent_1B_Adjacent_Line_C3_1(msg.GetData());
    f32val = CALC_Lanes_Adjacent_1B_Adjacent_Line_C3_1(u32val, 1.0f);
    adjacent_lane_boundary.SetAdjacentC3(f32val);

    adjacent_lane_boundary.SetPartBValid(true);
}

void Me8Driver::ConvertToRoadFrameWithTransform(RoadFrameType& output)
{
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;

    host_lane_boundary_list_[0].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    host_lane_boundary_list_[1].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);

    adjacent_lane_boundary_list_[0].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    adjacent_lane_boundary_list_[1].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    adjacent_lane_boundary_list_[2].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    adjacent_lane_boundary_list_[3].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
}

}  // namespace me8
}  // namespace sensors
}  // namespace holo