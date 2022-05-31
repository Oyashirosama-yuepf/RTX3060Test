/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_holocan_laneboundary.hpp
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
void HorizonMatrix2DriverT<HoloCanPacket>::ConstructLaneboundaryPartA(const HoloCanPacket& msg, LineType& laneboundary)
{
    int16_t   rawval;
    float32_t f32val;
    rawval = GET_LKA_Left_Lane_A_laneType(msg.GetData());
    rawval = CALC_LKA_Left_Lane_A_laneType(rawval, 1);
    laneboundary.SetTypeClass(static_cast<uint8_t>(rawval));
    rawval = GET_LKA_Left_Lane_A_laneQuality(msg.GetData());
    rawval = CALC_LKA_Left_Lane_A_laneQuality(rawval, 1);
    laneboundary.SetQuality(static_cast<uint8_t>(rawval));
    rawval = GET_LKA_Left_Lane_A_laneModelC0(msg.GetData());
    f32val = CALC_LKA_Left_Lane_A_laneModelC0(rawval, 1.0f);
    laneboundary.SetC0(f32val);
    rawval = GET_LKA_Left_Lane_A_laneModelC2(msg.GetData());
    f32val = CALC_LKA_Left_Lane_A_laneModelC2(rawval, 1.0f);
    laneboundary.SetC2(f32val);
    rawval = GET_LKA_Left_Lane_A_laneModelC3(msg.GetData());
    f32val = CALC_LKA_Left_Lane_A_laneModelC3(rawval, 1.0f);
    laneboundary.SetC3(f32val);
    rawval = GET_LKA_Left_Lane_A_laneWidthMarking(msg.GetData());
    f32val = CALC_LKA_Left_Lane_A_laneWidthMarking(rawval, 1.0f);
    laneboundary.SetWidthMarking(f32val);
    rawval = GET_LKA_Left_Lane_A_laneConfidence(msg.GetData());
    f32val = CALC_LKA_Left_Lane_A_laneConfidence(rawval, 1.0f);
    laneboundary.SetConfidence(f32val);
    laneboundary.SetPartAValid(true);
}

void HorizonMatrix2DriverT<HoloCanPacket>::ConstructLaneboundaryPartB(const HoloCanPacket& msg, LineType& laneboundary)
{
    int16_t   rawval;
    float32_t f32val;
    rawval = GET_LKA_Left_Lane_B_laneModelC1(msg.GetData());
    f32val = CALC_LKA_Left_Lane_B_laneModelC1(rawval, 1.0f);
    laneboundary.SetC1(f32val);
    rawval = GET_LKA_Left_Lane_B_viewRangeStart(msg.GetData());
    f32val = CALC_LKA_Left_Lane_B_viewRangeStart(rawval, 1.0f);
    laneboundary.SetViewRangeStart(f32val);
    rawval = GET_LKA_Left_Lane_B_viewRangeEnd(msg.GetData());
    f32val = CALC_LKA_Left_Lane_B_viewRangeEnd(rawval, 1.0f);
    laneboundary.SetViewRangeEnd(f32val);
    rawval = GET_LKA_Left_Lane_B_laneCrossing(msg.GetData());
    rawval = CALC_LKA_Left_Lane_B_laneCrossing(rawval, 1);
    laneboundary.SetCrossing(bool_t(rawval));
    rawval = GET_LKA_Left_Lane_B_laneMarkColor(msg.GetData());
    rawval = CALC_LKA_Left_Lane_B_laneMarkColor(rawval, 1);
    laneboundary.SetMarkColor(static_cast<uint8_t>(rawval));
    rawval = GET_LKA_Left_Lane_B_ttlc(msg.GetData());
    f32val = CALC_LKA_Left_Lane_B_ttlc(rawval, 1.0f);
    laneboundary.SetTlc(f32val);
    laneboundary.SetPartBValid(true);
}

void HorizonMatrix2DriverT<HoloCanPacket>::ConvertToRoadFrameWithTransform(const LineListType& input,
                                                                           RoadFrameType&      output)
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

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
