/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane.cpp
 * @brief This src file defines Lane.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-11
 */

#include <assert.h>
#include <holo/common/lane.h>

namespace holo
{
Lane::Lane() noexcept
  : lane_id_(LaneId(LaneId::INVALID))
  , lane_type_(LaneType(LaneType::INVALID))
  , max_speed_limit_(0.0f)
  , min_speed_limit_(0.0f)
  , lane_width_(0.0f)
  , left_lane_boundary_(nullptr)
  , right_lane_boundary_(nullptr)
  , target_merged_lane_(nullptr)
  , merge_lanes_()
  , split_lanes_()
{
}

Lane::Lane(const LaneId lane_id, const LaneType lane_type, const float32_t max_speed_limit,
           const float32_t min_speed_limit, const float32_t lane_width) noexcept
  : lane_id_(lane_id)
  , lane_type_(lane_type)
  , max_speed_limit_(max_speed_limit)
  , min_speed_limit_(min_speed_limit)
  , lane_width_(lane_width)
  , left_lane_boundary_(nullptr)
  , right_lane_boundary_(nullptr)
  , target_merged_lane_(nullptr)
  , merge_lanes_()
  , split_lanes_()
{
}

Lane::Lane(const LaneId lane_id, const LaneType lane_type, const float32_t max_speed_limit,
           const float32_t min_speed_limit, const float32_t lane_width,
           const std::shared_ptr<LaneBoundary>& left_lane_boundary,
           const std::shared_ptr<LaneBoundary>& right_lane_boundary) noexcept
  : lane_id_(lane_id)
  , lane_type_(lane_type)
  , max_speed_limit_(max_speed_limit)
  , min_speed_limit_(min_speed_limit)
  , lane_width_(lane_width)
  , left_lane_boundary_(left_lane_boundary)
  , right_lane_boundary_(right_lane_boundary)
  , target_merged_lane_(nullptr)
  , merge_lanes_()
  , split_lanes_()
{
}

Lane::Lane(const Lane& other) noexcept
  : lane_id_(other.lane_id_)
  , lane_type_(other.lane_type_)
  , max_speed_limit_(other.max_speed_limit_)
  , min_speed_limit_(other.min_speed_limit_)
  , lane_width_(other.lane_width_)
  , left_lane_boundary_(other.left_lane_boundary_)
  , right_lane_boundary_(other.right_lane_boundary_)
  , target_merged_lane_(other.target_merged_lane_)
  , merge_lanes_(other.merge_lanes_)
  , split_lanes_(other.split_lanes_)
{
}

Lane::Lane(Lane&& other) noexcept
  : lane_id_(other.lane_id_)
  , lane_type_(other.lane_type_)
  , max_speed_limit_(other.max_speed_limit_)
  , min_speed_limit_(other.min_speed_limit_)
  , lane_width_(other.lane_width_)
  , left_lane_boundary_(std::move(other.left_lane_boundary_))
  , right_lane_boundary_(std::move(other.right_lane_boundary_))
  , target_merged_lane_(std::move(other.target_merged_lane_))
  , merge_lanes_(std::move(other.merge_lanes_))
  , split_lanes_(std::move(other.split_lanes_))
{
}

Lane& Lane::operator=(const Lane& other) noexcept
{
    this->lane_id_             = other.lane_id_;
    this->lane_type_           = other.lane_type_;
    this->max_speed_limit_     = other.max_speed_limit_;
    this->min_speed_limit_     = other.min_speed_limit_;
    this->lane_width_          = other.lane_width_;
    this->left_lane_boundary_  = other.left_lane_boundary_;
    this->right_lane_boundary_ = other.right_lane_boundary_;
    this->target_merged_lane_  = other.target_merged_lane_;
    this->merge_lanes_         = other.merge_lanes_;
    this->split_lanes_         = other.split_lanes_;

    return *this;
}

Lane& Lane::operator=(Lane&& other) noexcept
{
    // avoid self = std::move(self)
    if (this == &other)
    {
        return *this;
    }

    this->lane_id_             = other.lane_id_;
    this->lane_type_           = other.lane_type_;
    this->max_speed_limit_     = other.max_speed_limit_;
    this->min_speed_limit_     = other.min_speed_limit_;
    this->lane_width_          = other.lane_width_;
    this->left_lane_boundary_  = std::move(other.left_lane_boundary_);
    this->right_lane_boundary_ = std::move(other.right_lane_boundary_);
    this->target_merged_lane_  = std::move(other.target_merged_lane_);
    this->merge_lanes_         = std::move(other.merge_lanes_);
    this->split_lanes_         = std::move(other.split_lanes_);

    return *this;
}

bool_t Lane::HasMergeLanes() const noexcept
{
    if (merge_lanes_.empty() == false)
    {
        return true;
    }
    return false;
}

bool_t Lane::HasSplitLanes() const noexcept
{
    if (split_lanes_.empty() == false)
    {
        return true;
    }
    return false;
}

void Lane::AppendMergeLane(const std::shared_ptr<Lane>& merge_lane) noexcept
{
    merge_lanes_.push_back(merge_lane);
}

void Lane::AppendSplitLane(const std::shared_ptr<Lane>& split_lane) noexcept
{
    split_lanes_.push_back(split_lane);
}

std::string Lane::ToString() const noexcept
{
    std::stringstream ss;
    ss << "Lane: ("
       << "lane_id_: " << static_cast<int32_t>(lane_id_) << ", lane_type_: " << static_cast<uint32_t>(lane_type_)
       << ", max_speed_limit_: " << max_speed_limit_ << ", min_speed_limit_: " << min_speed_limit_
       << ", lane_width_: " << lane_width_;

    if (left_lane_boundary_ != nullptr)
    {
        ss << ", left_lane_boundary_: " << left_lane_boundary_->ToString();
    }
    else
    {
        ss << ", left_lane_boundary_ is empty";
    }

    if (right_lane_boundary_ != nullptr)
    {
        ss << ", right_lane_boundary_: " << right_lane_boundary_->ToString();
    }
    else
    {
        ss << ", right_lane_boundary_ is empty ";
    }

    if (target_merged_lane_ != nullptr)
    {
        ss << ", target_merged_lane_: " << target_merged_lane_->ToString();
    }

    for (uint32_t i = 0U; i < merge_lanes_.size(); ++i)
    {
        if (merge_lanes_[i] != nullptr)
        {
            ss << ", merge_lanes_[" << i << "]: " << merge_lanes_[i]->ToString();
        }
    }

    for (uint32_t i = 0U; i < split_lanes_.size(); ++i)
    {
        if (split_lanes_[i] != nullptr)
        {
            ss << ", split_lanes_[" << i << "]: " << split_lanes_[i]->ToString();
        }
    }

    ss << ")" << std::endl;

    return ss.str();
}

}  // namespace holo
