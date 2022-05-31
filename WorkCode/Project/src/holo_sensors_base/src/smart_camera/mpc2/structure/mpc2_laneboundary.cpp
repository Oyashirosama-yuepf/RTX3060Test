/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bosch_mpc_laneboundary.c
 * @brief A class to describe bosch mpc laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/10
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/structure/mpc2_laneboundary.h>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
const uint32_t                    BoschMpcLaneBoundary::klane_boundaries_number_   = 4;
const float64_t                   BoschMpcLaneBoundary::khorizon_curvature_factor_ = 1.0f / 64.0f / 1024.0f;
const holo::common::BoundaryStyle BoschMpcLaneBoundary::ktype_remap_table_[8]      = {
    holo::common::BoundaryStyle::UNKNOWN,    // 0 "no_line"
    holo::common::BoundaryStyle::SOLID,      // 1 "solid"
    holo::common::BoundaryStyle::DASHED,     // 2 "dashed"
    holo::common::BoundaryStyle::ROAD_EDGE,  // 3 "curb"
    holo::common::BoundaryStyle::BARRIER,    // 4 "turf"
    holo::common::BoundaryStyle::BOTTS_DOT,  // 5 "bot-dotts"
    holo::common::BoundaryStyle::UNKNOWN,    // 6 "other"
    holo::common::BoundaryStyle::UNKNOWN,    // 7 "not_defined"
};
const holo::common::BoundaryColor BoschMpcLaneBoundary::kcolor_remap_table_[8] = {
    holo::common::BoundaryColor::UNKNOWN,  // 0 non line
    holo::common::BoundaryColor::WHITE,    // 1 white
    holo::common::BoundaryColor::YELLOW,   // 2 yellow, actually RED for mpc
    holo::common::BoundaryColor::YELLOW,   // 3 yellow
    holo::common::BoundaryColor::UNKNOWN,  // 4 not used
    holo::common::BoundaryColor::UNKNOWN,  // 5 not used
    holo::common::BoundaryColor::UNKNOWN,  // 6 not used
    holo::common::BoundaryColor::UNKNOWN,  // 7 not used
};

void BoschMpcLaneBoundary::ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                                     const holo::common::Extrinsicf&        extrinsic) const
{
    bool_t range_invalid = (dx_end_ - dx_begin_) < BOSCH_MPC_LANEBOUNDARY_LENGTH_MIN;
    if (range_invalid)
    {
        output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
        return;
    }
    float32_t c0      = dy_;
    float32_t c1      = static_cast<float32_t>(tan(angle_diff_));
    float32_t c2      = static_cast<float32_t>(0.5f * horizon_curvature_ * khorizon_curvature_factor_);
    float32_t c3      = 0.0f;
    float32_t x_start = dx_begin_;
    float32_t x_end   = dx_end_;
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
    c3          = c3;
    x_start     = dx_begin_ + x;
    x_end       = dx_end_ + x;
    output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({c0, c1, c2, c3}),
                                                    x_start, x_end);
    output->SetStyle(ktype_remap_table_[line_type_]);
    output->SetColor(kcolor_remap_table_[line_color_]);
    output->SetWidth(fabs(line_width_) * 100);
    output->SetConfidence(confidence_ * 100);
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo
