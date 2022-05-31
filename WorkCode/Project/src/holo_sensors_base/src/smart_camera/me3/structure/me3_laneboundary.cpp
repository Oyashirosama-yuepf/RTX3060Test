/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mobileye_laneboundary.c
 * @brief A class to describe mobileye laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/01/14
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/me3/structure/me3_laneboundary.h>

namespace holo
{
namespace sensors
{
namespace mobileye
{
const holo::common::BoundaryStyle MobileyeLaneBoundary::ktype_remap_table_[16] = {
    holo::common::BoundaryStyle::UNKNOWN,       //!  0 "Undecided"
    holo::common::BoundaryStyle::SOLID,         //!  1 "Solid"
    holo::common::BoundaryStyle::ROAD_EDGE,     //!  2 "RoadEdge"
    holo::common::BoundaryStyle::DASHED,        //!  3 "Dashed"
    holo::common::BoundaryStyle::DOUBLE_SOLID,  //!  4 "DoubleLane"
    holo::common::BoundaryStyle::BOTTS_DOT,     //!  5 "Bott'sDots"
    holo::common::BoundaryStyle::BARRIER,       //!  6 "Barrier"
    holo::common::BoundaryStyle::UNKNOWN,       //!  7 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //!  8 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //!  9 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //! 10 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //! 11 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //! 12 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //! 13 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,       //! 14 "reserved"
    holo::common::BoundaryStyle::UNKNOWN        //! 15 "reserved"
};

const holo::common::BoundaryColor MobileyeLaneBoundary::kcolor_remap_table_[4] = {
    holo::common::BoundaryColor::UNKNOWN,  //! 0 "Unknown"
    holo::common::BoundaryColor::WHITE,    //! 1 "White"
    holo::common::BoundaryColor::YELLOW,   //! 2 "Yelow"
    holo::common::BoundaryColor::YELLOW    //! 3 "Blue" -> YELLOW
};

const float32_t MobileyeLaneBoundary::kquality_remap_table_[4] = {0.25f, 0.5f, 0.75f, 1.0f};

void MobileyeLaneBoundary::ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                                     const holo::common::Extrinsicf&        extrinsic) const
{
    bool_t range_invalid = (range_end_ - range_start_) < MOBILEYE_LANEBOUNDARY_LENGTH_MIN;
    if (range_invalid)
    {
        output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
        return;
    }
    float32_t c0      = -c0_;
    float32_t c1      = -c1_;
    float32_t c2      = -c2_;
    float32_t c3      = -c3_;
    float32_t x_start = range_start_;
    float32_t x_end   = range_end_;
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
    output->SetWidth(width_ * 100);
    output->SetConfidence(kquality_remap_table_[quality_] * 100);
}

}  // namespace mobileye
}  // namespace sensors
}  // namespace holo
