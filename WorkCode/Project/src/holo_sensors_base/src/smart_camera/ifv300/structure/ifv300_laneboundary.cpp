/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ifv300_laneboundary.c
 * @brief A class to describe ifv300 laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/24
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/ifv300/structure/ifv300_laneboundary.h>

namespace holo
{
namespace sensors
{
namespace ifv300
{
const holo::common::BoundaryStyle Ifv300LaneBoundary::ktype_remap_table_[16] = {
    holo::common::BoundaryStyle::UNKNOWN,       //  0 "none"
    holo::common::BoundaryStyle::SOLID,         //  1 "solid"
    holo::common::BoundaryStyle::DASHED,        //  2 "dashed"
    holo::common::BoundaryStyle::UNKNOWN,       //  3 "reserved"
    holo::common::BoundaryStyle::BOTTS_DOT,     //  4 "botts dots"
    holo::common::BoundaryStyle::UNKNOWN,       //  5 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //  6 "invalid (no classification)"
    holo::common::BoundaryStyle::UNKNOWN,       //  7 "undecided"
    holo::common::BoundaryStyle::DOUBLE_SOLID,  //  8 "double lane mark"
    holo::common::BoundaryStyle::UNKNOWN,       //  9 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       // 10 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       // 11 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       // 12 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       // 13 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       // 14 "reserved"
    holo::common::BoundaryStyle::UNKNOWN        // 15 "reserved"
};
const holo::common::BoundaryColor Ifv300LaneBoundary::kcolor_remap_table_[4] = {
    holo::common::BoundaryColor::UNKNOWN,  // 0 "unknown"
    holo::common::BoundaryColor::YELLOW,   // 1 "yellow"
    holo::common::BoundaryColor::WHITE,    // 2 "white"
    holo::common::BoundaryColor::YELLOW    // 3 "blue" -> assigned to YELLOW
};

const float32_t Ifv300LaneBoundary::kquality_remap_table_[4] = {0.25f, 0.5f, 0.75f, 1.0f};

const float32_t Ifv300LaneBoundary::kboundary_width_ = 0.15f;

void Ifv300LaneBoundary::ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                                   const holo::common::Extrinsicf&        extrinsic) const
{
    bool_t range_invalid = range_ < IFV300_LANEBOUNDARY_LENGTH_MIN;
    if (range_invalid)
    {
        output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
        return;
    }
    float32_t c0      = -a0_;
    float32_t c1      = -a1_;
    float32_t c2      = -a2_;
    float32_t c3      = -a3_;
    float32_t x_start = 0;
    float32_t x_end   = range_;
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
    output->SetStyle(ktype_remap_table_[type_]);
    output->SetColor(kcolor_remap_table_[color_]);
    output->SetWidth(kboundary_width_ * 100);
    output->SetConfidence(kquality_remap_table_[quality_] * 100);
}

}  // namespace ifv300
}  // namespace sensors
}  // namespace holo
