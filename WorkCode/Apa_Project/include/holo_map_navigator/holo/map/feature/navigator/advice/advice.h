/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file advice.h
 * @brief New advice
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2021-10-08"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_H_

#include <vector>

#include <holo/common/road_type.h>
#include <holo/common/timestamp.h>

#include <holo/map/common/marshal.h>

#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/state_region_harder.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Advice message
 *
 */
class Advice2
{
public:
    struct DistanceAttribute
    {
        static holo::float64_t constexpr DEFAULT_INVALID_DISTANCE_VALUE = -999999.999999;

        holo::float64_t distance_to_available_hd_area_entry_ = DEFAULT_INVALID_DISTANCE_VALUE;
        holo::float64_t distance_to_available_hd_area_exit_  = DEFAULT_INVALID_DISTANCE_VALUE;
        holo::float64_t distance_to_hd_area_entry_           = DEFAULT_INVALID_DISTANCE_VALUE;
        holo::float64_t distance_to_hd_area_exit_            = DEFAULT_INVALID_DISTANCE_VALUE;
        holo::float64_t distance_to_sd_destination_          = DEFAULT_INVALID_DISTANCE_VALUE;
        holo::float64_t distance_to_hd_destination_          = DEFAULT_INVALID_DISTANCE_VALUE;
    };
    
public:
    using Ptr = std::shared_ptr<Advice2>;
    using LanePathSPtrType = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType = std::vector<LanePathSPtrType>;

public:
    /**
     * @brief Format to JSON String
     *
     * @param advice Advice2
     * @return std::string JOSN string
     */
    static std::string FormatToString(Advice2 const& advice)
    {
        std::stringstream ss;
        ss << "{";
        ss << "\"ts_str\": "<< advice.GetTimestamp().ToSec();
        ss << ", \"on_route_state\": " << static_cast<int>(advice.GetOnRouteState());
        ss << ", \"on_hdmap\": " << advice.IsOnHDMap();
        ss << ", \"dist_to_dest\": " << advice.GetDistanceToDestination();
        ss << ", \"dist_out_hdmap\": " << advice.GetDistanceOutHDMap();
        ss << ", \"position_state\": " << static_cast<int>(advice.GetPositionState());
        ss << ", \"expect_lane_seqs\": " << marshal::FormatToString(advice.GetExpectLaneSeqs());
        ss << ", \"expect_lane_paths\": " << marshal::FormatToString(advice.GetExpectedLanePaths());
        ss << "}";
        return ss.str();
    }

public:
    /**
     * @brief State about whether or not on route
     *
     * @note On SD Route using SD navigation but lacks HD map information
     */
    enum OnRouteState : holo::uint8_t
    {
        UNDIFINED = 0U,  ///> Undifined state so not tu use
        ON_HD_ROUTE,     ///> On High Decidion route
        ON_SD_ROUTE,     ///> ON SD route
        OUT_ROUTE        ///> Out route
    };
    /**
     * @brief State for positioning
     * @details LOW, HIGH and Medium represents different level of
     *          positioning precision. And the TRANSERSE_HIGH_PRECISION
     *          just guarantees the yaw angle and heading angle
     *
     */
    enum PositionState : holo::uint8_t
    {
        INVALID                  = 0U,  ///> Postion state invalid
        LOW_PRECISION            = 1U,  ///> Position precision is low
        MEDIUM_PRECISION         = 2U,  ///> Position precision is medium
        TRANSERSE_HIGH_PRECISION = 3U,  ///> Position precision is high along transerse direction
        HIGH_PRECISION           = 4U   ///> Position precision is high
    };

    Advice2()             = default;
    Advice2(Advice2 const&) = default;
    Advice2(Advice2&&)      = default;
    Advice2& operator=(Advice2 const&) = delete;
    Advice2& operator=(Advice2&&) = delete;
    ~Advice2()                    = default;

    /**
     * @brief Set the Timestamp
     * 
     * @param timestamp 
     */
    void SetTimestamp(holo::common::Timestamp const& timestamp)
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get the Timestamp
     * 
     * @return holo::common::Timestamp const 
     */
    holo::common::Timestamp const GetTimestamp() const
    {
        return this->timestamp_;
    }

    /**
     * @brief Set the On Route State
     *
     * @param state OnRouteState
     */
    void SetOnRouteState(OnRouteState const& state)
    {
        this->on_route_state_ = state;
    }
    
    /**
     * @brief Get the state of whether or not on route 
     * 
     * @return OnRouteState 
     */
    OnRouteState GetOnRouteState() const
    {
        return this->on_route_state_;
    }

    /**
     * @brief Set state of whether or not on HD map
     * 
     * @param on_map Whether or not on HD map
     */
    void SetIsOnHDMap(holo::bool_t on_map)
    {
        this->on_hdmap_ = on_map;
    }

    /**
     * @brief Whether or not on HD map
     *
     * @return holo::bool_t Whether or not on HD map
     */
    holo::bool_t IsOnHDMap() const
    {
        return this->on_hdmap_;
    }

    /**
     * @brief Add lane path
     *
     * @param lane_path Lane path details described in LanePath
     */
    void AddLanePath(LanePathSPtrType const& lane_path)
    {
        this->lane_paths_.push_back(lane_path);
    }

    /**
     * @brief Get the lane paths
     *
     * @return std::vector<LanePath> const& A vector of lane paths
     */
    std::vector<LanePathSPtrType> const& GetLanePaths() const
    {
        return this->lane_paths_;
    }

    std::vector<LanePathSPtrType>& GetLanePaths()
    {
        return this->lane_paths_;
    }

    /**
     * @brief Set the distance to destination
     *
     * @param dist meters Distance to destination
     */
    void SetDistanceToDestination(holo::float64_t const dist)
    {
        this->distance_to_destination_ = dist;
    }

    /**
     * @brief Get the distance to destination
     *
     * @return holo::float64_t Distance to destination;Unit: meter
     */
    holo::float64_t GetDistanceToDestination() const
    {
        return this->distance_to_destination_;
    }

    /**
     * @brief Set the distance out HD Map
     *
     * @param dist Distance out HD Map; Unit: meter
     */
    void SetDistanceOutHDMap(holo::float64_t const dist)
    {
        this->distance_out_hdmap = dist;
    }

    /**
     * @brief Get the distanc out of HD map
     *
     * @return holo::float64_t Distance out HD Map; Unit: meter
     */
    holo::float64_t GetDistanceOutHDMap() const
    {
        return this->distance_out_hdmap;
    }

    /**
     * @brief Set the positioning state
     *
     * @param state PositionState
     */
    void SetPositionState(PositionState const& state)
    {
        this->position_state_ = state;
    }

    /**
     * @brief Get the positioning state
     * 
     * @return PositionState 
     */
    PositionState GetPositionState() const
    {
        return this->position_state_;
    }

    /**
     * @brief Get the current lane sequence numbers
     *
     * @return std::vector<int32_t> const& Current lane sequence numbers
     */
    std::vector<int32_t> const GetCurrentLaneSeqs() const
    {
        std::vector<int32_t> seqs;
        std::size_t const    size_lane_paths = this->lane_paths_.size();
        for (std::size_t i = 0U; i < size_lane_paths; ++i)
        {
            if (std::find(seqs.begin(), seqs.end(), (*this->lane_paths_[i]).GetSequnceNumber()) == seqs.end())
            {
                seqs.push_back((*this->lane_paths_[i]).GetSequnceNumber());
            }
        }
        std::sort(seqs.begin(), seqs.end());
        return seqs;
    }

    /**
     * @brief Set the expected lane sequence numbers
     * 
     * @param seqs Sequence Numbers
     */
    void SetExpectLaneSeqs(std::vector<int32_t> const& seqs)
    {
        this->expect_lane_seqs_ = seqs;
    }

    /**
     * @brief Get the expected lane sequence numbers 
     * 
     * @return std::vector<int32_t> const& Sequence numbers
     */
    std::vector<int32_t> const& GetExpectLaneSeqs() const
    {
        return this->expect_lane_seqs_;
    }

    /**
     * @brief Set the Expected Lane Paths
     * 
     * @param paths Exptected lane paths
     */
    void SetExpectedLanePaths(std::vector<uint64_t> const& paths)
    {
        this->expect_lane_paths_ = paths;
    }

    /**
     * @brief Get the Expected Lane Paths
     *
     * @return Exptected lane paths
     */
    std::vector<holo::uint64_t> const& GetExpectedLanePaths() const
    {
        return this->expect_lane_paths_;
    }

    /**
     * @brief Get the Expected Lane Paths
     *
     * @return Exptected lane paths
     */
    std::vector<holo::uint64_t>& GetExpectedLanePaths()
    {
        return this->expect_lane_paths_;
    }

    /**
     * @brief Set the Histroy Trace 
     * 
     * @param trace 
     */
    void SetHistroyTrace(VecLaneIdType const trace)
    {
        this->history_trace_ = trace;
    }

    /**
     * @brief Get the History Trace
     *
     * @return VecKeyValue
     */
    VecLaneIdType GetHistoryTrace() const
    {
        return this->history_trace_;
    }

    std::vector<LanePathSPtrType>& GetRepairedLanePaths()
    {
        return this->repaired_lane_paths_;
    }

    DistanceAttribute const& GetDistanceAttribute() const noexcept
    {
        return this->dist_attribute_;
    }

    void SetDistanceAttribute(DistanceAttribute const dist_attr)
    {
        this->dist_attribute_ = dist_attr;
    }

private:
    ///> Message Time stapme
    holo::common::Timestamp timestamp_;
    ///> State for whther or not on route
    OnRouteState on_route_state_ = OnRouteState::UNDIFINED;
    ///> State for whether or not on HD map
    holo::bool_t on_hdmap_ = false;
    ///> Vector of lane paths
    std::vector<LanePathSPtrType> lane_paths_;
    /// Distance to destination, unit: meter
    holo::float64_t distance_to_destination_ = std::numeric_limits<holo::float64_t>::max();
    ///  Distance out of HD map, unit: meter;
    holo::float64_t distance_out_hdmap = std::numeric_limits<holo::float64_t>::max();
    ///  State for positioning
    PositionState position_state_;
    ///  Expected lane sequence numbers、
    std::vector<int32_t> expect_lane_seqs_;
    ///  History trace
    VecLaneIdType history_trace_;
    ///  Expected lane paths
    std::vector<holo::uint64_t> expect_lane_paths_;
    /// Repaired lane paths
    std::vector<LanePathSPtrType> repaired_lane_paths_;
    /// 
    DistanceAttribute dist_attribute_;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_H_ */
