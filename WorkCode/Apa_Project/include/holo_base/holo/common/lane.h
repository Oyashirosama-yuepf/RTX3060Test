/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane.h
 * @brief This header file defines Lane.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-11
 */

#ifndef HOLO_COMMON_LANE_H_
#define HOLO_COMMON_LANE_H_

#include <array>

#include <holo/common/lane_boundary.h>
#include <holo/serialization/serialization.h>

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief This class is used to describe the lane
 * @deprecated Use holo::common::Lane instead. Will be removed in v0.5.0
 *
 * @details A lane is comprised of two lane boundaries, one left and one right. If there doesn't have left/right lane
 * boundary then the container of left/right lane boundary in lane is null. The lane struct also describe lane merge and
 * lane split scenario in real world.
 *
 * @note Please reference https://wiki.holomatic.cn/display/HOLO/RoadFrame+Usage for lane merge and split scenario
 * defination.
 */
class [[deprecated]] Lane
{
public:
    /**
     * @brief This enum class is used to describe id of lane
     */
    enum class LaneId : int8_t
    {
        LEFT_2ND_LANE  = -4,
        LEFT_1ST_LANE  = -2,
        CURRENT_LANE   = 0,
        RIGHT_1ST_LANE = 2,
        RIGHT_2ND_LANE = 4,
        INVALID        = 15,
    };

    /**
     * @brief This enum class is used to describe the type of lane
     */
    enum class LaneType : uint8_t
    {
        UNDECIDED      = 0,
        REAL_LANE      = 1,
        VIRTUAL_LANE   = 2,
        EMERGENCY_LANE = 3,
        INVALID        = 15,
    };

public:
    /**
     * @brief Default constructor
     */
    Lane() noexcept;

    /**
     * @brief Constructor with parameters
     *
     * @param lane_id lane id
     * @param lane_type lane type
     * @param max_limit_speed max limit speed for lane
     * @param min_limit_speed min limit speed for lane
     * @param lane_width lane width
     */
    Lane(const LaneId lane_id, const LaneType lane_type, const float32_t max_limit_speed,
         const float32_t min_limit_speed, const float32_t lane_width) noexcept;

    /**
     * @brief Constructor with parameters
     *
     * @param lane_id lane id
     * @param lane_type lane type
     * @param max_limit_speed max limit speed for lane
     * @param min_limit_speed min limit speed for lane
     * @param lane_width lane width
     * @param left_lane_boundary left lane boundary
     * @param right_lane_boundary right lane boundary
     * @param target_merged_lane target merged lane when merge lane scenario happened
     * @param merge_lanes array of merge lanes when merge lane scenario happened
     * @param split_lanes array of split lanes when split lane scenario happened
     */
    Lane(const LaneId lane_id, const LaneType lane_type, const float32_t max_limit_speed,
         const float32_t min_limit_speed, const float32_t lane_width,
         const std::shared_ptr<LaneBoundary>& left_lane_boundary,
         const std::shared_ptr<LaneBoundary>& right_lane_boundary) noexcept;

    /**
     * @brief Copy constructor
     *
     * @param other other lane
     */
    Lane(const Lane& other) noexcept;

    /**
     * @brief Move constructor
     *
     * @param other other lane
     */
    Lane(Lane&& other) noexcept;

    /**
     * @brief Copy assignment
     *
     * @param other lane to assign
     * @return new lane
     */
    Lane& operator=(const Lane& other) noexcept;

    /**
     * @brief Move assignment
     *
     * @param other other lane
     * @return new lane
     */
    Lane& operator=(Lane&& other) noexcept;

    /**
     * @brief Get lane id
     *
     * @return lane id
     */
    LaneId GetLaneId() const noexcept
    {
        return lane_id_;
    }

    /**
     * @brief Set lane id
     *
     * @param lane_id lane id
     */
    void SetLaneId(const LaneId lane_id) noexcept
    {
        this->lane_id_ = lane_id;
    }

    /**
     * @brief Get lane type
     *
     * @return lane type
     */
    LaneType GetLaneType() const noexcept
    {
        return lane_type_;
    }

    /**
     * @brief Set lane type
     *
     * @param lane_type lane type
     */
    void SetLaneType(const LaneType lane_type) noexcept
    {
        this->lane_type_ = lane_type;
    }

    /**
     * @brief Get max speed limit of this lane
     *
     * @return max speed limit
     */
    float32_t GetMaxSpeedLimit() const noexcept
    {
        return max_speed_limit_;
    }

    /**
     * @brief Set max speed limit of this lane
     *
     * @param max_speed_limit max speed limit
     */
    void SetMaxSpeedLimit(const float32_t max_speed_limit) noexcept
    {
        this->max_speed_limit_ = max_speed_limit;
    }

    /**
     * @brief Get min speed limit of this lane
     *
     * @return min limit speed
     */
    float32_t GetMinSpeedLimit() const noexcept
    {
        return min_speed_limit_;
    }

    /**
     * @brief Set min speed limit of this lane
     *
     * @param min_speed_limit min speed limit
     */
    void SetMinSpeedLimit(const float32_t min_speed_limit) noexcept
    {
        this->min_speed_limit_ = min_speed_limit;
    }

    /**
     * @brief Get lane width
     *
     * @return lane width
     */
    float32_t GetLaneWidth() const noexcept
    {
        return lane_width_;
    }

    /**
     * @brief Set lane width
     *
     * @param lane_width lane width
     */
    void SetLaneWidth(const float32_t lane_width) noexcept
    {
        this->lane_width_ = lane_width;
    }

    /**
     * @brief Whether current lane has lanes merged
     *
     * @details Merge lane has only one targe lane, if multi lanes merged, there must be one target merge lane
     *
     * @return return true if multi lanes merged with this lane, otherwise return false
     */
    bool_t HasMergeLanes() const noexcept;

    /**
     * @brief Get count of merge lanes
     *
     * @return number of  merge lanes
     */
    uint32_t GetNumMergeLanes() const noexcept
    {
        return merge_lanes_.size();
    }

    /**
     * @brief Judge whether has split lane
     *
     * @details Lane may split into several lanes, we store split lanes when this scenarioes happened
     *
     * @return return true if lane split into several lanes, otherwise false
     */
    bool_t HasSplitLanes() const noexcept;

    /**
     * @brief Get count of split lanes
     *
     * @return number of split lanes
     */
    uint32_t GetNumSplitLanes() const noexcept
    {
        return split_lanes_.size();
    }

    /**
     * @brief Get target merged lane when merge lane scenario happens
     *
     * @return target merged lane
     */
    const std::shared_ptr<const Lane> GetTargetMergedLane() const noexcept
    {
        std::shared_ptr<const Lane> ret = std::const_pointer_cast<const Lane>(target_merged_lane_);
        return ret;
    }

    /**
     * @brief Get target merged lane when merge lane scenario happens
     *
     * @return target merged lane
     */
    std::shared_ptr<Lane> GetTargetMergedLane() noexcept
    {
        return target_merged_lane_;
    }

    /**
     * @brief Set target merged lane when merge lane scenario happens
     *
     * @param target_merged_lane target merged lane
     *
     * @note If Target merged lane is self, set merge lane as nullptr
     */
    void SetTargetMergetLane(const std::shared_ptr<Lane>& target_merged_lane) noexcept
    {
        this->target_merged_lane_ = target_merged_lane;
    }

    /**
     * @brief Get merge lanes when merge lane scenario happens
     *
     * @return merge lanes
     */
    const std::vector<std::shared_ptr<const Lane>> GetMergeLanes() const noexcept
    {
        std::vector<std::shared_ptr<const Lane>> ret;
        for (size_t i = 0; i < merge_lanes_.size(); ++i)
        {
            ret.push_back(std::const_pointer_cast<const Lane>(merge_lanes_[i]));
        }
        return ret;
    }

    /**
     * @brief Set merge lane when merge lane scenario happens
     *
     * @param merge_lanes merge lanes
     */
    void SetMergeLanes(const std::vector<std::shared_ptr<Lane>>& merge_lanes) noexcept
    {
        this->merge_lanes_ = merge_lanes;
    }

    /**
     * @brief Set merge lane in efficient way
     *
     * @param merge_lanes merge lanes
     */
    void SetMergeLanes(std::vector<std::shared_ptr<Lane>>&& merge_lanes) noexcept
    {
        std::swap(this->merge_lanes_, merge_lanes);
    }

    /**
     * @brief Get split lanes when split lane scenario happens
     *
     * @return split lanes
     */
    const std::vector<std::shared_ptr<const Lane>> GetSplitLanes() const noexcept
    {
        std::vector<std::shared_ptr<const Lane>> ret;
        for (size_t i = 0; i < split_lanes_.size(); ++i)
        {
            ret.push_back(std::const_pointer_cast<const Lane>(split_lanes_[i]));
        }
        return ret;
    }

    /**
     * @brief Set split lane when split lane scenario happens
     *
     * @param split_lanes split lanes
     */
    void SetSplitLanes(const std::vector<std::shared_ptr<Lane>>& split_lanes) noexcept
    {
        this->split_lanes_ = split_lanes;
    }

    /**
     * @brief Set split lane in efficient way
     *
     * @param split_lanes split lanes
     */
    void SetSplitLanes(std::vector<std::shared_ptr<Lane>>&& split_lanes) noexcept
    {
        std::swap(this->split_lanes_, split_lanes);
    }

    /**
     * @brief Append a merge lane into merge lanes when merge lane scenario happens
     *
     * @param merge_lane merge lane to append
     */
    void AppendMergeLane(const std::shared_ptr<Lane>& merge_lane) noexcept;

    /**
     * @brief Append a split lane into split lanes when split lane scenario happens
     *
     * @param split_lane split lane to append
     */
    void AppendSplitLane(const std::shared_ptr<Lane>& split_lane) noexcept;

    /**
     * @brief Get left lane boundary ptr
     *
     * @return left lane boundary
     */
    const std::shared_ptr<const LaneBoundary> GetLeftLaneBoundary() const noexcept
    {
        std::shared_ptr<const LaneBoundary> ret = std::const_pointer_cast<const LaneBoundary>(left_lane_boundary_);
        return ret;
    }

    /**
     * @brief Set left lane boundary ptr
     *
     * @param lane_boundary left lane boundary ptr
     */
    void SetLeftLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary) noexcept
    {
        this->left_lane_boundary_ = lane_boundary;
    }

    /**
     * @brief Get right lane boundary ptr
     *
     * @return right lane bonudary
     */
    const std::shared_ptr<const LaneBoundary> GetRightLaneBoundary() const noexcept
    {
        std::shared_ptr<const LaneBoundary> ret = std::const_pointer_cast<const LaneBoundary>(right_lane_boundary_);
        return ret;
    }

    /**
     * @brief Set right lane bonudary ptr
     *
     * @param lane_boundary right lane boundary ptr
     */
    void SetRightLaneBoundary(const std::shared_ptr<LaneBoundary>& lane_boundary) noexcept
    {
        this->right_lane_boundary_ = lane_boundary;
    }

    /**
     * @brief Serialize content to string
     *
     * @return serialized string
     */
    std::string ToString() const noexcept;

private:
    LaneId                             lane_id_;
    LaneType                           lane_type_;
    float32_t                          max_speed_limit_;
    float32_t                          min_speed_limit_;
    float32_t                          lane_width_;
    std::shared_ptr<LaneBoundary>      left_lane_boundary_;
    std::shared_ptr<LaneBoundary>      right_lane_boundary_;
    std::shared_ptr<Lane>              target_merged_lane_;
    std::vector<std::shared_ptr<Lane>> merge_lanes_;
    std::vector<std::shared_ptr<Lane>> split_lanes_;
};  // Lane

/**
 * @}
 */

}  // namespace holo

#endif  // !HOLO_COMMON_LANE_H_
