/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_someip_laneboundary.hpp
 * @brief To receive and construct bosch mpc outputs
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/11
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
void BoschMpcDriverT<SomeipPacketType>::ConvertToLaneboundaryWithTransform(const struct MpcLineRawData& input,
                                                                           LineType&                    output)
{
    uint16_t                u16val;
    float32_t               f32val;
    holo::common::Timestamp stamp(input.timestamp.sec, input.timestamp.nsec);
    output.SetTimestamp(stamp);
    /* part a */
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_dx_Beginn(input.dx_begin, 1.0);
    output.SetDxBegin(f32val);
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_dx_Vorausschau(input.dx_end, 1.0);
    output.SetDxEnd(f32val);
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_dy(input.dy, 1.0);
    output.SetDy(f32val);
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_Existenzmass(input.confidence, 1.0);
    output.SetConfidence(f32val);
    f32val = CALC_BV1_Lin_01_A_BV_Linie_01_Gierw_diff(input.angle_diff, 1.0);
    output.SetAngleDiff(f32val);
    output.SetPartAValid(true);
    /* part b */
    f32val = CALC_BV1_Lin_01_B_BV_Linie_01_hor_Kruemmung(input.horizon_curve, 1);
    output.SetHorizonCurvature(f32val);
    f32val = CALC_BV1_Lin_01_B_BV_Linie_01_Linienbreite(input.width, 1.0);
    output.SetLineWidth(f32val);
    u16val = CALC_BV1_Lin_01_B_BV_Linie_01_Liniennummer(input.id, 1);
    output.SetLineNumber(u16val);
    u16val = CALC_BV1_Lin_01_B_BV_Linie_01_Typ(input.type, 1);
    output.SetLineType(u16val);
    u16val = CALC_BV1_Lin_01_B_BV_Linie_01_Farbe(input.color, 1);
    output.SetLineColor(u16val);
    output.SetPartBValid(true);
}

void BoschMpcDriverT<SomeipPacketType>::ConvertToRoadFrameWithTransform(const struct MpcLinesRawData& input,
                                                                        RoadFrameType&                output)
{
    /* lines to laneboundaries */
    std::array<LineType, 4> lbd_array;
    ConvertToLaneboundaryWithTransform(input.left_left_line, lbd_array[0]);
    ConvertToLaneboundaryWithTransform(input.left_line, lbd_array[1]);
    ConvertToLaneboundaryWithTransform(input.right_line, lbd_array[2]);
    ConvertToLaneboundaryWithTransform(input.right_right_line, lbd_array[3]);
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
    for (uint32_t i = 0; i < lbd_array.size(); i++)
    {
        if (lbd_array[i].IsValid())
        {
            if (lbd_array[i].GetConfidence() > 0.0f)
            {
                if (lbd_array[i].GetDy() > divide_threshold)
                {
                    left_line_list.push_back(&lbd_array[i]);
                }
                else
                {
                    right_line_list.push_back(&lbd_array[i]);
                }
            }
        }
    }
    left_line_list.sort(BoschMpcDriverT<SomeipPacketType>::CompareLaneBoundaryLeft);
    right_line_list.sort(BoschMpcDriverT<SomeipPacketType>::CompareLaneBoundaryRight);
    /* assign left laneboundaries */
    static const LaneboundaryType     dummy_boundary(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
    std::shared_ptr<LaneboundaryType> laneboundary = nullptr;
    if (left_line_list.size() > 2)
    {
        left_line_list.resize(2);
    }
    auto left_line = left_line_list.crbegin();
    if (left_line_list.size() == 2)
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
    uint8_t   left_1_confidence = output.at(1).GetConfidence();
    float32_t left_1_c0         = 0.0f;
    if (left_1_confidence > 0)
    {
        left_1_c0 = output.at(1).GetSampleByCoordinate(0).GetY();
    }
    uint8_t   right_1_confidence = output.at(2).GetConfidence();
    float32_t right_1_c0         = 0.0f;
    if (right_1_confidence > 0)
    {
        right_1_c0 = output.at(2).GetSampleByCoordinate(0).GetY();
    }
    if ((left_1_confidence > 0 && !(left_1_c0 > -0.45f)) || (right_1_confidence > 0 && !(right_1_c0 < 0.45f)))
    {
        veh_moving_mode_ = KEEPING_IN_LANE;
    }
    else if (left_1_confidence > 0 && (left_1_c0 < 0.45f))
    {
        veh_moving_mode_ = CHANGING_TO_LEFT;
    }
    else if (right_1_confidence > 0 && (right_1_c0 > -0.45f))
    {
        veh_moving_mode_ = CHANGING_TO_RIGHT;
    }
    else if ((left_1_confidence > 0 && !(left_1_c0 < 0.45f)) || (right_1_confidence > 0 && !(right_1_c0 > -0.45f)))
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
