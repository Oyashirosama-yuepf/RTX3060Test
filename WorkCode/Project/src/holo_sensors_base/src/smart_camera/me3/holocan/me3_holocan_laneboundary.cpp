/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_holocan_laneboundary.hpp
 * @brief A class to receive and construct mobileye outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/03
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
void MobileyeDriverT<HoloCanPacket>::ConstructLaneboundaryPart0(const HoloCanPacket& msg, LineType& laneboundary)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Lane0_Signals_Message_Part0_Lane0_Lane_View_Range_Start(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_View_Range_Start(rawval, 1.0f);
    laneboundary.SetRangeStart(f32val);
    rawval = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Width(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Width(rawval, 1.0f);
    laneboundary.SetMarkWidth(f32val);
    rawval = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Quality(msg.GetData());
    rawval = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Quality(rawval, 1);
    laneboundary.SetQuality(rawval);
    rawval = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Type(msg.GetData());
    rawval = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Mark_Type(rawval, 1);
    laneboundary.SetType(rawval);
    rawval = GET_Lane0_Signals_Message_Part0_Lane0_Lane_Location_Type(msg.GetData());
    rawval = CALC_Lane0_Signals_Message_Part0_Lane0_Lane_Location_Type(rawval, 1);
    laneboundary.SetLocation(rawval);
    laneboundary.SetPart0Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConstructLaneboundaryPart1(const HoloCanPacket& msg, LineType& laneboundary)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Lane0_Signals_Message_Part1_Lane0_C2_Lane_Curvature(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part1_Lane0_C2_Lane_Curvature(rawval, 1.0f);
    laneboundary.SetC2(f32val);
    rawval = GET_Lane0_Signals_Message_Part1_Lane0_Lane_View_Range_End(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part1_Lane0_Lane_View_Range_End(rawval, 1.0f);
    laneboundary.SetRangeEnd(f32val);
    rawval = GET_Lane0_Signals_Message_Part1_Lane0_C1_Heading_Angle(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part1_Lane0_C1_Heading_Angle(rawval, 1.0f);
    laneboundary.SetC1(f32val);
    rawval = GET_Lane0_Signals_Message_Part1_Lane0_C0_Lane_Position(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part1_Lane0_C0_Lane_Position(rawval, 1.0f);
    laneboundary.SetC0(f32val);
    laneboundary.SetPart1Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConstructLaneboundaryPart2(const HoloCanPacket& msg, LineType& laneboundary)
{
    uint16_t  rawval;
    float32_t f32val;
    rawval = GET_Lane0_Signals_Message_Part2_Lane0_Lane_Mark_Color(msg.GetData());
    rawval = CALC_Lane0_Signals_Message_Part2_Lane0_Lane_Mark_Color(rawval, 1);
    laneboundary.SetColor(rawval);
    rawval = GET_Lane0_Signals_Message_Part2_Lane0_C3_Lane_Curvature_Driv(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part2_Lane0_C3_Lane_Curvature_Driv(rawval, 1.0f);
    laneboundary.SetC3(f32val);
    rawval = GET_Lane0_Signals_Message_Part2_Lane0_Crossing(msg.GetData());
    rawval = CALC_Lane0_Signals_Message_Part2_Lane0_Crossing(rawval, 1);
    laneboundary.SetCrossing(rawval);
    rawval = GET_Lane0_Signals_Message_Part2_Lane0_TLC(msg.GetData());
    f32val = CALC_Lane0_Signals_Message_Part2_Lane0_TLC(rawval, 1.0f);
    laneboundary.SetTlc(f32val);
    laneboundary.SetPart2Valid(true);
}

void MobileyeDriverT<HoloCanPacket>::ConvertToRoadFrameWithTransform(const LineListType& input, RoadFrameType& output)
{
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;
    input[NEXT_LEFT_INDEX].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    input[LKA_LEFT_INDEX].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    input[LKA_RIGHT_INDEX].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
    input[NEXT_RIGHT_INDEX].ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
    output.emplace_back(*laneboundary);
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
