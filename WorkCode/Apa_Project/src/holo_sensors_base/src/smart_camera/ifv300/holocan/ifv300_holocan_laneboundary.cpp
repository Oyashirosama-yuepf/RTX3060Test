/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_holocan_laneboundary.hpp
 * @brief A class to receive and construct ifv300 outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
 */

#ifndef _HOLO_SENSORS_IFV300_IFV300_HOLOCAN_LANEBOUNDARY_HPP
#define _HOLO_SENSORS_IFV300_IFV300_HOLOCAN_LANEBOUNDARY_HPP

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
void Ifv300DriverT<HoloCanPacket>::ConstructLaneboundaryHeader(const HoloCanPacket& msg, LaneboundaryHeader& header)
{
    /* fetch signals and asign part->signals */
    header.left_left_type      = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_NEIGHBOR_TYPE(msg.GetData());
    header.left_left_lkaconf   = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_NEIGHBOR_LKACONF(msg.GetData());
    header.left_type           = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_INDIVID_TYPE(msg.GetData());
    header.left_lkaconf        = GET_VIS_LANE_INFORMATION_VIS_LANE_LEFT_INDIVID_LKACONF(msg.GetData());
    header.right_type          = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_INDIVID_TYPE(msg.GetData());
    header.right_lkaconf       = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_INDIVID_LKACONF(msg.GetData());
    header.right_right_type    = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_NEIGHBOR_TYPE(msg.GetData());
    header.right_right_lkaconf = GET_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_NEIGHBOR_LKACONF(msg.GetData());
    header.valid               = true;
}

void Ifv300DriverT<HoloCanPacket>::ConstructLaneboundaryBody(const HoloCanPacket& msg, LineType& laneboundary)
{
    /* fetch phy signals and asign part->signals */
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_IN_MARKER_COLOR(msg.GetData());
    u32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_IN_MARKER_COLOR(u32val, 1);
    laneboundary.SetColor(u32val);
    u32val = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A0(msg.GetData());
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A0(u32val, 1.0f);
    laneboundary.SetA0(f32val);
    u32val = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A1(msg.GetData());
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A1(u32val, 1.0f);
    laneboundary.SetA1(f32val);
    u32val = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A2(msg.GetData());
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A2(u32val, 1.0f);
    laneboundary.SetA2(f32val);
    u32val = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A3(msg.GetData());
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A3(u32val, 1.0f);
    laneboundary.SetA3(f32val);
    u32val = GET_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_RANGE(msg.GetData());
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_RANGE(u32val, 1.0f);
    laneboundary.SetRange(f32val);
    /* set part true */
    laneboundary.SetValid(true);
}

void Ifv300DriverT<HoloCanPacket>::ConvertToRoadFrameWithTransform(const std::array<LineType, IFV300_LINES_NUM>& input,
                                                                   RoadFrameType&                                output)
{
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;
    input[0].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    input[1].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    input[2].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    input[3].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
}

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo

#endif