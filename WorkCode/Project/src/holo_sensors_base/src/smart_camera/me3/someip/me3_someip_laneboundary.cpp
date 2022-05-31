/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_someip_laneboundary.hpp
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
void MobileyeDriverT<SomeipPacketType>::Convert(const MobileyeLaneRawData& input, LineType& output)
{
    output.SetTimestamp(holo::common::Timestamp(input.timestamp.sec, input.timestamp.nsec));
    float32_t c0 = CALC_Lane0_Signals_Message_Part1_Lane0_C0_Lane_Position(input.c0, 1.0f);
    output.SetC0(c0);
    float32_t c1 = CALC_Lane0_Signals_Message_Part1_Lane0_C1_Heading_Angle(input.c1, 1.0f);
    output.SetC1(c1);
    float32_t c2 = CALC_Lane0_Signals_Message_Part1_Lane0_C2_Lane_Curvature(input.c2, 1.0f);
    output.SetC2(c2);
    float32_t c3 = CALC_Lane0_Signals_Message_Part2_Lane0_C3_Lane_Curvature_Driv(input.c3, 1.0f);
    output.SetC3(c3);
    float32_t range_start = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_View_Range_Start(input.range_start, 1.0f);
    output.SetRangeStart(range_start);
    float32_t range_end = CALC_Lane0_Signals_Message_Part1_Lane0_Lane_View_Range_End(input.range_end, 1.0f);
    output.SetRangeEnd(range_end);
    float32_t width = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Width(input.mark_width, 1.0f);
    output.SetMarkWidth(width);
    float32_t tlc = CALC_Lane0_Signals_Message_Part2_Lane0_TLC(input.tlc, 1.0f);
    output.SetTlc(tlc);
    uint8_t location = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Location_Type(input.location_type, 1);
    output.SetLocation(location);
    uint8_t type = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Type(input.mark_type, 1);
    output.SetType(type);
    uint8_t color = CALC_Lane0_Signals_Message_Part2_Lane0_Lane_Mark_Color(input.mark_color, 1);
    output.SetColor(color);
    uint8_t quality = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Quality(input.mark_quality, 1);
    output.SetQuality(quality);
    bool_t crossing = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Quality(input.crossing, 1);
    output.SetCrossing(crossing);
    output.SetPart0Valid(true);
    output.SetPart1Valid(true);
    output.SetPart2Valid(true);
}

void MobileyeDriverT<SomeipPacketType>::Convert(const MobileyeLanesRawData& input, RoadFrameType& output)
{
    /* lines to laneboundaries */
    LineType                          mobileye_laneboundary;
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;
    /* ll */
    Convert(input.line0, mobileye_laneboundary);
    mobileye_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    /* l */
    Convert(input.line1, mobileye_laneboundary);
    mobileye_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    /* r */
    Convert(input.line2, mobileye_laneboundary);
    mobileye_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    /* rr */
    Convert(input.line3, mobileye_laneboundary);
    mobileye_laneboundary.ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
