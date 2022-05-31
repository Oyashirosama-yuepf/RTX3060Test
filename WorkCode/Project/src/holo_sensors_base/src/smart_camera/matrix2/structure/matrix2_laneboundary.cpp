/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file horizon_matrix2_laneboundary.cpp
 * @brief A class to describe delphi horizon matrix2 laneboundary
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/05/21
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/matrix2/structure/matrix2_laneboundary.h>

namespace holo
{
namespace sensors
{
namespace horizon_matrix2
{
/*
    laneType
    0 "Undecided"
    1 "Solid"
    2 "Road Edge"
    3 "Dashed"
    4 "Double Lane(Left Dashed, Right Solid)"
    5 "Double Lane(Left Solid, Right Dashed)"
    6 "Double Lane(Double Dashed)"
    7 "Double Lane(Double Solid)"
    8 "Barrier"
    15 "Invalid"
*/
const holo::common::BoundaryStyle HorizonMatrix2LaneBoundary::type_remap_table_const_[16] = {
    holo::common::BoundaryStyle::UNKNOWN,               //!  0 "Unknown" ;
    holo::common::BoundaryStyle::SOLID,                 //!  1 "Solid"
    holo::common::BoundaryStyle::ROAD_EDGE,             //!  2 "Road Edge"
    holo::common::BoundaryStyle::DASHED,                //!  3 "Dashed"
    holo::common::BoundaryStyle::LEFT_DOT_RIGHT_SOLID,  //!  4 "Double Lane(Left Dashed, Right Solid)"
    holo::common::BoundaryStyle::LEFT_SOLID_RIGHT_DOT,  //!  5 "Double Lane(Left Solid, Right Dashed)"
    holo::common::BoundaryStyle::DASHED,                //!  6 "Double Lane(Double Dashed)"
    holo::common::BoundaryStyle::DOUBLE_SOLID,          //!  7 "Double Lane(Double Solid)"
    holo::common::BoundaryStyle::BARRIER,               //!  8 "Barrier"
    holo::common::BoundaryStyle::UNKNOWN,               //!  9 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,               //! 10 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,               //! 11 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,               //! 12 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,               //! 13 "reserved"
    holo::common::BoundaryStyle::UNKNOWN,               //! 14 "reserved"
    holo::common::BoundaryStyle::UNKNOWN                //! 15 "reserved"
};

/*
    laneMarkColor
    0 "white"
    1 "yellow"
    2 "blue"
    3 "invalid"
*/
const holo::common::BoundaryColor HorizonMatrix2LaneBoundary::color_remap_table_const_[4] = {
    holo::common::BoundaryColor::WHITE,    //! 0 "White"
    holo::common::BoundaryColor::YELLOW,   //! 1 "Yellow_Orange_Red"
    holo::common::BoundaryColor::YELLOW,   //! 2 "Blue_Green" -> yellow
    holo::common::BoundaryColor::UNKNOWN,  //! 3 "Unknown"
};

void HorizonMatrix2LaneBoundary::ConvertToHoloLaneBoundary(std::shared_ptr<HoloLaneBoundaryType>& output,
                                                           const holo::common::Extrinsicf&        extrinsic) const
{
    bool_t range_invalid = (view_range_end_ - view_range_start_) < HORIZON_MATRIX2_LANEBOUNDARY_LENGTH_MIN;
    if (range_invalid)
    {
        output = std::make_shared<HoloLaneBoundaryType>(holo::numerics::Polynomial<holo::float32_t, 3U>({0, 0, 0, 0}));
        return;
    }
    float32_t c0      = c0_;
    float32_t c1      = c1_;
    float32_t c2      = c2_;
    float32_t c3      = c3_;
    float32_t x_start = view_range_start_;
    float32_t x_end   = view_range_end_;
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
    output->SetStyle(type_remap_table_const_[type_class_]);
    output->SetColor(color_remap_table_const_[mark_color_]);
    output->SetWidth(width_marking_ * 100);
    output->SetConfidence(confidence_ * 100);
}

}  // namespace horizon_matrix2
}  // namespace sensors
}  // namespace holo
