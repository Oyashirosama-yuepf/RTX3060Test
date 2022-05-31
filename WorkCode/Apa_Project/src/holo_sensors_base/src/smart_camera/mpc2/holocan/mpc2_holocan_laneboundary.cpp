/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_holocan_laneboundary.hpp
 * @brief To receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/11
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
void BoschMpcDriverT<HoloCanPacket>::ConstructLaneBoundaryPartA(const HoloCanPacket& msg, LineType& lane_boundary)
{
    /* fetch phy signals and asign part->signals */
    uint32_t  u32val;
    float32_t f32val;
    u32val = GET_BV1_Lin_01_A_BV_Linie_01_dx_Beginn(msg.GetData());
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_dx_Beginn(u32val, 1.0);
    lane_boundary.SetDxBegin(f32val);
    u32val = GET_BV1_Lin_01_A_BV_Linie_01_dx_Vorausschau(msg.GetData());
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_dx_Vorausschau(u32val, 1.0);
    lane_boundary.SetDxEnd(f32val);
    u32val = GET_BV1_Lin_01_A_BV_Linie_01_dy(msg.GetData());
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_dy(u32val, 1.0);
    lane_boundary.SetDy(f32val);
    u32val = GET_BV1_Lin_01_A_BV_Linie_01_Existenzmass(msg.GetData());
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_Existenzmass(u32val, 1.0);
    lane_boundary.SetConfidence(f32val);
    u32val = GET_BV1_Lin_01_A_BV_Linie_01_Gierw_diff(msg.GetData());
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_Gierw_diff(u32val, 1.0);
    lane_boundary.SetAngleDiff(f32val);
    /* set part true */
    lane_boundary.SetPartAValid(true);
}

void BoschMpcDriverT<HoloCanPacket>::ConstructLaneBoundaryPartB(const HoloCanPacket& msg, LineType& lane_boundary)
{
    /* fetch phy signals and asign part->signals */
    uint32_t  u32val;
    int16_t   s16val;
    float32_t f32val;
    u32val = GET_BV1_Lin_01_B_BV_Linie_01_hor_Kruemmung(msg.GetData());
    s16val = CALC_BV1_Lin_01_B_BV_Linie_01_hor_Kruemmung(u32val, 1);
    lane_boundary.SetHorizonCurvature(s16val);
    u32val = GET_BV1_Lin_01_B_BV_Linie_01_Linienbreite(msg.GetData());
    f32val = CALC_BV1_Lin_01_B_BV_Linie_01_Linienbreite(u32val, 1.0);
    lane_boundary.SetLineWidth(f32val);
    u32val = GET_BV1_Lin_01_B_BV_Linie_01_Liniennummer(msg.GetData());
    u32val = CALC_BV1_Lin_01_B_BV_Linie_01_Liniennummer(u32val, 1);
    lane_boundary.SetLineNumber(u32val);
    u32val = GET_BV1_Lin_01_B_BV_Linie_01_Typ(msg.GetData());
    u32val = CALC_BV1_Lin_01_B_BV_Linie_01_Typ(u32val, 1);
    lane_boundary.SetLineType(u32val);
    u32val = GET_BV1_Lin_01_B_BV_Linie_01_Farbe(msg.GetData());
    u32val = CALC_BV1_Lin_01_B_BV_Linie_01_Farbe(u32val, 1);
    lane_boundary.SetLineColor(u32val);
    /* set part true */
    lane_boundary.SetPartBValid(true);
    /* set timestamp */
    lane_boundary.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConvertToRoadFrameWithTransform(const LineListType& input, RoadFrameType& output)
{
    /* header */
    output.SetTimestamp(input[input.size() - 1].GetTimestamp());
    /* sort lane boundaries */
    float32_t divide_threshold;
    float32_t divide_compensation1 = 0.0f;
    float32_t divide_compensation2 = 0.0f;
    if (veh_moving_mode_ == CHANGING_TO_LEFT) /* to left */
    {
        divide_threshold     = -LANE_CHANGE_THRESHOLD;
        divide_compensation1 = -(LANE_WIDTH_HIGHWAY * 0.5f - fabs(divide_threshold));
    }
    else if (veh_moving_mode_ == CHANGING_TO_RIGHT) /* to right */
    {
        divide_threshold     = LANE_CHANGE_THRESHOLD;
        divide_compensation1 = (LANE_WIDTH_HIGHWAY * 0.5f - fabs(divide_threshold));
    }
    else /* KEEPING_IN_LANE */
    {
        divide_threshold     = 0.0f;
        divide_compensation2 = -LANE_CHANGE_THRESHOLD * 0.5f;
    }
    std::list<const LineType*> left_line_list;
    std::list<const LineType*> right_line_list;
    for (uint32_t i = 0; i < input.size(); i++)
    {
        if (input[i].IsValid())
        {
            if (input[i].GetConfidence() > 0.0f)
            {
                if (input[i].GetDy() > divide_threshold)
                {
                    left_line_list.push_back(&input[i]);
                }
                else
                {
                    right_line_list.push_back(&input[i]);
                }
            }
        }
    }
    left_line_list.sort(BoschMpcDriverBase::CompareLaneBoundaryLeft);
    right_line_list.sort(BoschMpcDriverBase::CompareLaneBoundaryRight);
    /* assign left laneboundaries */
    static const LaneboundaryType     dummy_boundary(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;
    if (left_line_list.size() > 2)
    {
        left_line_list.resize(2);
    }
    auto left_line = left_line_list.crbegin();
    if (left_line_list.size() >= 2)
    {
        /* convert and put in */
        (*left_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
        output.emplace_back(*laneboundary);
        left_line++;
        (*left_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
        output.emplace_back(*laneboundary);
    }
    else if (left_line_list.size() == 1)
    {
        if ((*left_line)->GetDy() < (LANE_WIDTH_HIGHWAY + divide_compensation1 + divide_compensation2) * 1.25f)
        {
            /* convert */
            output.emplace_back(dummy_boundary);
            (*left_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
            output.emplace_back(*laneboundary);
        }
        else
        {
            /* convert */
            (*left_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
            output.emplace_back(*laneboundary);
            output.emplace_back(dummy_boundary);
        }
    }
    else
    {
        output.emplace_back(dummy_boundary);
        output.emplace_back(dummy_boundary);
    }
    /* assign right laneboundaries */
    if (right_line_list.size() > 2)
    {
        right_line_list.resize(2);
    }
    auto right_line = right_line_list.cbegin();
    if (right_line_list.size() >= 2)
    {
        /* convert and put in */
        (*right_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
        output.emplace_back(*laneboundary);
        right_line++;
        (*right_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
        output.emplace_back(*laneboundary);
    }
    else if (right_line_list.size() == 1)
    {
        if ((*right_line)->GetDy() > -(LANE_WIDTH_HIGHWAY - divide_compensation1 + divide_compensation2) * 1.25f)
        {
            /* convert */
            (*right_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
            output.emplace_back(*laneboundary);
            output.emplace_back(dummy_boundary);
        }
        else
        {
            /* convert */
            output.emplace_back(dummy_boundary);
            (*right_line)->ConvertToHoloLaneBoundary(laneboundary, extrinsic_);
            output.emplace_back(*laneboundary);
        }
    }
    else
    {
        output.emplace_back(dummy_boundary);
        output.emplace_back(dummy_boundary);
    }
    /* judge moving mode */
    float32_t left_1_confidence = output.at(1).GetConfidence();
    float32_t left_1_c0         = 0.0f;
    if (left_1_confidence > 0.0f)
    {
        left_1_c0 = output.at(1).GetSampleByCoordinate(0).GetY();
    }
    float32_t right_1_confidence = output.at(2).GetConfidence();
    float32_t right_1_c0         = 0.0f;
    if (right_1_confidence > 0.0f)
    {
        right_1_c0 = output.at(2).GetSampleByCoordinate(0).GetY();
    }
    if ((left_1_confidence > 0.0f && !(left_1_c0 > -0.45f)) || (right_1_confidence > 0.0f && !(right_1_c0 < 0.45f)))
    {
        veh_moving_mode_ = KEEPING_IN_LANE;
    }
    else if (left_1_confidence > 0.0f && (left_1_c0 < 0.45f))
    {
        veh_moving_mode_ = CHANGING_TO_LEFT;
    }
    else if (right_1_confidence > 0.0f && (right_1_c0 > -0.45f))
    {
        veh_moving_mode_ = CHANGING_TO_RIGHT;
    }
    else if ((left_1_confidence > 0.0f && !(left_1_c0 < 0.45f)) ||
             (right_1_confidence > 0.0f && !(right_1_c0 > -0.45f)))
    {
        veh_moving_mode_ = KEEPING_IN_LANE;
    }
    else
    {
        /* keep last mode */
    }
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
