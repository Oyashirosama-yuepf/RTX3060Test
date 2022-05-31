/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_someip_laneboundary.hpp
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
void Ifv300DriverT<SomeipPacketType>::Convert(const IfvLineInfoCurve& input, LineType& output)
{
    uint8_t   u8val;
    float32_t f32val;
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A0(input.a0, 1.0);
    output.SetA0(f32val);
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A1(input.a1, 1.0);
    output.SetA1(f32val);
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A2(input.a2, 1.0);
    output.SetA2(f32val);
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_A3(input.a3, 1.0);
    output.SetA3(f32val);
    f32val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_INDIVID_RANGE(input.range, 1.0);
    output.SetRange(f32val);
    u8val = CALC_VIS_LANE_NEAR_LEFT_INDIVIDUAL_VIS_LANE_LEFT_IN_MARKER_COLOR(input.mark_color, 1);
    output.SetColor(u8val);
    output.SetValid(true);
}

void Ifv300DriverT<SomeipPacketType>::Convert(const IfvLinesRawData& input, RoadFrameType& output)
{
    uint8_t u8val;
    /* lines to laneboundaries */
    LineType                          ifv300_laneboundary;
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;
    /* set timestamp */
    output.SetTimestamp(holo::common::Timestamp(input.timestamp.sec, input.timestamp.nsec));
    /* ll */
    Convert(input.left_left, ifv300_laneboundary);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_LEFT_NEIGHBOR_TYPE(input.line_head.left_left_type, 1);
    ifv300_laneboundary.SetType(u8val);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_LEFT_NEIGHBOR_LKACONF(input.line_head.left_left_lkaconf, 1);
    ifv300_laneboundary.SetQuality(u8val);
    ifv300_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    /* l */
    Convert(input.left, ifv300_laneboundary);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_LEFT_INDIVID_TYPE(input.line_head.left_type, 1);
    ifv300_laneboundary.SetType(u8val);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_LEFT_INDIVID_LKACONF(input.line_head.left_lkaconf, 1);
    ifv300_laneboundary.SetQuality(u8val);
    ifv300_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    /* r */
    Convert(input.right, ifv300_laneboundary);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_INDIVID_TYPE(input.line_head.right_type, 1);
    ifv300_laneboundary.SetType(u8val);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_INDIVID_LKACONF(input.line_head.right_lkaconf, 1);
    ifv300_laneboundary.SetQuality(u8val);
    ifv300_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    /* rr */
    Convert(input.right_right, ifv300_laneboundary);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_NEIGHBOR_TYPE(input.line_head.right_right_type, 1);
    ifv300_laneboundary.SetType(u8val);
    u8val = CALC_VIS_LANE_INFORMATION_VIS_LANE_RIGHT_NEIGHBOR_LKACONF(input.line_head.right_right_lkaconf, 1);
    ifv300_laneboundary.SetQuality(u8val);
    ifv300_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
}

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
