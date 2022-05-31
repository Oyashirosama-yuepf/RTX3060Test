/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_boundary.cpp
 * @brief This src file implements LaneBoundary .
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-06
 */

#include <assert.h>
#include <holo/common/lane_boundary.h>
#include <holo/geometry/polynomial_curve2d.h>

namespace holo
{
LaneBoundary::LaneBoundary() noexcept
  : lane_boundary_id_(LaneBoundaryId::INVALID)
  , lane_boundary_type_(LaneBoundaryType::INVALID)
  , lane_mark_color_(LaneMarkColor::INVALID)
  , lane_boundary_params_(nullptr)
  , num_lane_boundary_points_(0U)
  , lane_mark_width_(0.0f)
  , confidence_(0.0f)
  , predicted_(true)
{
}

LaneBoundary::LaneBoundary(const LaneBoundaryId lane_boundary_id, const LaneBoundaryType lane_boundary_type,
                           const LaneMarkColor                                     lane_mark_color,
                           const std::shared_ptr<CurveDescriptorT<float32_t>>&     lane_boundary_params,
                           const uint32_t                                          num_lane_boundary_points,
                           const std::array<Point3f, LANE_BOUNDARY_MAX_POINT_NUM>& lane_boundary_points,
                           const float32_t lane_mark_width, const float32_t confidence, const bool_t predicted) noexcept
  : lane_boundary_id_(lane_boundary_id)
  , lane_boundary_type_(lane_boundary_type)
  , lane_mark_color_(lane_mark_color)
  , lane_boundary_params_(lane_boundary_params)
  , num_lane_boundary_points_(num_lane_boundary_points)
  , lane_boundary_points_(lane_boundary_points)
  , lane_mark_width_(lane_mark_width)
  , confidence_(confidence)
  , predicted_(predicted)
{
}

LaneBoundary::LaneBoundary(const LaneBoundary& other) noexcept
  : lane_boundary_id_(other.lane_boundary_id_)
  , lane_boundary_type_(other.lane_boundary_type_)
  , lane_mark_color_(other.lane_mark_color_)
  , lane_boundary_params_(other.lane_boundary_params_)
  , num_lane_boundary_points_(other.num_lane_boundary_points_)
  , lane_boundary_points_(other.lane_boundary_points_)
  , lane_mark_width_(other.lane_mark_width_)
  , confidence_(other.confidence_)
  , predicted_(other.predicted_)
{
}

LaneBoundary::LaneBoundary(LaneBoundary&& other) noexcept
  : lane_boundary_id_(other.lane_boundary_id_)
  , lane_boundary_type_(other.lane_boundary_type_)
  , lane_mark_color_(other.lane_mark_color_)
  , lane_boundary_params_(std::move(other.lane_boundary_params_))
  , num_lane_boundary_points_(other.num_lane_boundary_points_)
  , lane_boundary_points_(std::move(other.lane_boundary_points_))
  , lane_mark_width_(other.lane_mark_width_)
  , confidence_(other.confidence_)
  , predicted_(other.predicted_)
{
}

LaneBoundary& LaneBoundary::operator=(const LaneBoundary& other) noexcept
{
    this->lane_boundary_id_         = other.lane_boundary_id_;
    this->lane_boundary_type_       = other.lane_boundary_type_;
    this->lane_mark_color_          = other.lane_mark_color_;
    this->lane_boundary_params_     = other.lane_boundary_params_;
    this->num_lane_boundary_points_ = other.num_lane_boundary_points_;
    this->lane_boundary_points_     = other.lane_boundary_points_;
    this->lane_mark_width_          = other.lane_mark_width_;
    this->confidence_               = other.confidence_;
    this->predicted_                = other.predicted_;

    return *this;
}

LaneBoundary& LaneBoundary::operator=(LaneBoundary&& other) noexcept
{
    // avoid self = std::move(self)
    if (this == &other)
    {
        return *this;
    }

    this->lane_boundary_id_         = other.lane_boundary_id_;
    this->lane_boundary_type_       = other.lane_boundary_type_;
    this->lane_mark_color_          = other.lane_mark_color_;
    this->lane_boundary_params_     = std::move(other.lane_boundary_params_);
    this->num_lane_boundary_points_ = other.num_lane_boundary_points_;
    this->lane_mark_width_          = other.lane_mark_width_;
    this->confidence_               = other.confidence_;
    this->predicted_                = other.predicted_;
    this->lane_boundary_points_     = std::move(other.lane_boundary_points_);

    return *this;
}

bool_t LaneBoundary::GetStartPoint(Point3f& point) const noexcept
{
    if (num_lane_boundary_points_ > 0U)
    {
        point = lane_boundary_points_[0U];
        return true;
    }
    return false;
}

bool_t LaneBoundary::GetEndPoint(Point3f& point) const noexcept
{
    if (num_lane_boundary_points_ > 0U)
    {
        point = lane_boundary_points_[num_lane_boundary_points_ - 1U];
        return true;
    }
    return false;
}

std::string LaneBoundary::ToString() const noexcept
{
    std::stringstream ss;
    ss << "LaneBoundary: ("
       << ", lane_boundary_id_: " << static_cast<int32_t>(lane_boundary_id_)
       << ", lane_boundary_type_: " << static_cast<uint32_t>(lane_boundary_type_)
       << ", lane_mark_color_: " << static_cast<uint32_t>(lane_mark_color_)
       << ", lane_boundary_params_: " << lane_boundary_params_->ToString()
       << ", num_lane_boundary_points_: " << num_lane_boundary_points_ << ", lane_mark_width_: " << lane_mark_width_
       << ", confidence_: " << confidence_ << ", predicted_: " << predicted_;
    ss << "lane_boundary_points_: ";
    for (uint32_t i = 0U; i < num_lane_boundary_points_; ++i)
    {
        ss << lane_boundary_points_[i] << ", ";
    }
    ss << ")" << std::endl;

    return ss.str();
}


}  // namespace holo
