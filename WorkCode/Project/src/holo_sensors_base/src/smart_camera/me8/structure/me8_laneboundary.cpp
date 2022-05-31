/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file me8_laneboundary.cpp
 * @brief A class to describe me8 laneboundary
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/09
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me8/structure/me8_laneboundary.h>

namespace holo
{
namespace sensors
{
namespace me8
{
const holo::common::BoundaryStyle Me8LaneBoundaryHost::ktype_remap_table_[7] = {
    holo::common::BoundaryStyle::UNKNOWN,    //  0 - UNDECIDED
    holo::common::BoundaryStyle::SOLID,      //  1 - SOLID
    holo::common::BoundaryStyle::DASHED,     //  2 - DASHED
    holo::common::BoundaryStyle::UNKNOWN,    //  3 - DLM
    holo::common::BoundaryStyle::BOTTS_DOT,  //  4 - BOTTS
    holo::common::BoundaryStyle::UNKNOWN,    //  5 - DECELERATION
    holo::common::BoundaryStyle::UNKNOWN,    //  6 - HOV_LANE
};
const holo::common::BoundaryStyle Me8LaneBoundaryAdjacent::ktype_remap_table_[16] = {
    holo::common::BoundaryStyle::UNKNOWN,    //  0 - UNDECIDED
    holo::common::BoundaryStyle::SOLID,      //  1 - SOLID
    holo::common::BoundaryStyle::DASHED,     //  2 - DASHED
    holo::common::BoundaryStyle::UNKNOWN,    //  3 - DLM
    holo::common::BoundaryStyle::BOTTS_DOT,  //  4 - BOTTS
    holo::common::BoundaryStyle::UNKNOWN,    //  5 - HOV_LANE
    holo::common::BoundaryStyle::UNKNOWN,    //  6
    holo::common::BoundaryStyle::UNKNOWN,    //  7
    holo::common::BoundaryStyle::UNKNOWN,    //  8
    holo::common::BoundaryStyle::UNKNOWN,    //  9
    holo::common::BoundaryStyle::UNKNOWN,    //  10
    holo::common::BoundaryStyle::UNKNOWN,    //  11
    holo::common::BoundaryStyle::UNKNOWN,    //  12
    holo::common::BoundaryStyle::UNKNOWN,    //  13
    holo::common::BoundaryStyle::UNKNOWN,    //  14
    holo::common::BoundaryStyle::UNKNOWN,    //  15
};

const float32_t Me8LaneBoundaryHost::kboundary_width_ = 0.15f;

void Me8LaneBoundaryHost::ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                                    const holo::common::Extrinsicf&        extrinsic) const
{
    bool_t range_invalid = std::fabs(lh_vr_start_ - lh_vr_end_) < ME8_LANEBOUNDARY_LENGTH_MIN;
    if (range_invalid)
    {
        output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
        return;
    }
    // the definition of Y axis of me8 coordinate system and body coordinate system is opposite
    float32_t c0      = -lh_c0_;
    float32_t c1      = -lh_c1_;
    float32_t c2      = -lh_c2_;
    float32_t c3      = -lh_c3_;
    float32_t x_start = lh_vr_start_;
    float32_t x_end   = lh_vr_end_;
    //! conversions
    //! c0' = c0 + c1*dx + c2*dx^2 + c3*dx^3 - dy
    //! c1' = c1 + 2*c2*dx + 3*c3*dx^2
    //! c2' = c2 + 3*c3*dx
    //! c3' = c3
    //! x_start' = x start + dx;
    //! x_end' = x end + dx
    float32_t x = extrinsic.GetPose().GetX();
    float32_t y = extrinsic.GetPose().GetY();
    c0          = c0 + c1 * x + c2 * x * x + c3 * x * x * x - y;
    c1          = c1 + 2 * c2 * x + 3 * c3 * x * x;
    c2          = c2 + 3 * c3 * x;
    x_start += x;
    x_end += x;
    output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({c0, c1, c2, c3}),
                                                    x_start, x_end);
    output->SetStyle(ktype_remap_table_[lh_lanemark_type_]);
    output->SetColor(holo::common::BoundaryColor::UNKNOWN);
    output->SetWidth(kboundary_width_ * 100);
    /* raw data is flat32, range is [0..1], holodata is uint8_t, uint is %, so need to convert unit with " *100 " */
    output->SetConfidence(static_cast<uint8_t>(lh_confidence_*100));
}

const float32_t Me8LaneBoundaryAdjacent::kboundary_width_ = 0.15f;

void Me8LaneBoundaryAdjacent::ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                                        const holo::common::Extrinsicf&        extrinsic) const
{
    bool_t range_invalid =
        std::fabs(adjacent_view_range_start_ - adjacent_view_range_end_) < ME8_LANEBOUNDARY_LENGTH_MIN;
    if (range_invalid)
    {
        output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
        return;
    }
    // the definition of Y axis of me8 coordinate system and body coordinate system is opposite
    float32_t c0      = -adjacent_line_c0_;
    float32_t c1      = -adjacent_line_c1_;
    float32_t c2      = -adjacent_line_c2_;
    float32_t c3      = -adjacent_line_c3_;
    float32_t x_start = adjacent_view_range_start_;
    float32_t x_end   = adjacent_view_range_end_;
    //! conversions
    //! c0' = c0 + c1*dx + c2*dx^2 + c3*dx^3 - dy
    //! c1' = c1 + 2*c2*dx + 3*c3*dx^2
    //! c2' = c2 + 3*c3*dx
    //! c3' = c3
    //! x_start' = x start + dx;
    //! x_end' = x end + dx
    float32_t x = extrinsic.GetPose().GetX();
    float32_t y = extrinsic.GetPose().GetY();
    c0          = c0 + c1 * x + c2 * x * x + c3 * x * x * x - y;
    c1          = c1 + 2 * c2 * x + 3 * c3 * x * x;
    c2          = c2 + 3 * c3 * x;
    x_start += x;
    x_end += x;
    output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({c0, c1, c2, c3}),
                                                    x_start, x_end);
    output->SetStyle(ktype_remap_table_[adjacent_type_]);
    output->SetColor(holo::common::BoundaryColor::UNKNOWN);
    output->SetWidth(kboundary_width_ * 100);
    /* raw data is flat32, range is [0..1], holodata is uint8_t, uint is %, so need to convert unit with " *100 " */
    output->SetConfidence(static_cast<uint8_t>(adjacent_confidence_*100));
}

}  // namespace me8
}  // namespace sensors
}  // namespace holo
