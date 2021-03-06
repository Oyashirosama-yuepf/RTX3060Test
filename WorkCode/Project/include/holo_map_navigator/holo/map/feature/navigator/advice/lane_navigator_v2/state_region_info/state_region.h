/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file state_region.h
 * @brief State region on lane path
 * @author yuhongbo(yuhongbo@holomaitc.com)
 * @date "2022-01-18"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_H_

#include <memory>

#include <holo/common/road_type.h>
#include <holo/core/types.h>

#include <holo/map/common/common_define.h>

#include <holo/map/feature/navigator/advice/lane_navigator/target_region.h>
#include <holo/map/format/base/lane_group.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
using SceneCategory = holo::map::navigator::advice::TargetRegion::SceneType;
class StateRegion
{
public:
    enum class StateFunction : holo::uint8_t
    {
        NONE              = 0x00U,
        BASIC_SPLIT_RIGHT = 0x10,  // Basic semantics, split to right
        BASIC_SPLIT_LEFT  = 0x11,  // Basic semantics, split to left
        BASIC_MERGE_RIGHT = 0x12,  // Basic semantics, merge to right
        BASIC_MERGE_LEFT  = 0x13,  // Basic semantics, merge to left
        BASIC_BREAKUP = 0X14, // Basic semantics, break up
        BASIC_DECELERATION_SPLIT_RIGHT = 0x15,  // Basic semantics, decelerate split to right
        BASIC_DECELERATION_SPLIT_LEFT  = 0x16,  // Basic semantics, decelerate split to left
        BASIC_ACCELERATION_MERGE_RIGHT = 0x17,  // Basic semantics, accelerate merge to right
        BASIC_ACCELERATION_MERGE_LEFT  = 0x18,  // Basic semantics, accelerate merge to left
        BASIC_MERGE_PASS_BY_LEFT = 0x19, // Basic semantics, merge pass by left
        BASIC_MERGE_PASS_BY_RIGHT = 0x20, // Basic semantics, merge pass by right
        BASIC_SPLIT_PASS_BY_LEFT = 0x21, // Basic semantics, split pass by left
        BASIC_SPLIT_PASS_BY_RIGHT = 0x22, // Basic semantics, split pass by right
        BASIC_TURN_LEFT,
        BASIC_TURN_RIGHT,
        BASIC_TURN_AROUND_LEFT,
        BASIC_TURN_AROUND_RIGHT,
        BASIC_TURN_LEFT_AREA,
        BASIC_TURN_RIGHT_AREA,
        OTHERS            = 0xff
    };
    enum class StateAction : holo::uint8_t
    {
        NONE                       = 0x00U,
        SCENE_DOWN_RAMP_DIRECT     = 0x21,  // Scene semantics, direct to down ramp
        SCENE_DOWN_RAMP_PARALLEL   = 0x22,  // Scene semantics, parallel to down ramp
        SCENE_DOWN_RAMP_CORRESPOND = 0x23,  // Scene semantics, correspond to down ramp
        SCENE_UP_MAIN_DIRECT       = 0x24,  // Scene semantics, direct to up main road
        SCENE_UP_MAIN_PARALLEL     = 0x25,  // Scene semantics, parallel to up main road
        SCENE_UP_MAIN_CORRESPOND   = 0x26,   // Scene semantics, correspond to up main road
        OTHERS                     = 0xff
    };

    static std::string FormatToString(StateRegion const region);

    static std::string FormatSequenceToString(std::vector<StateRegion> const& regions);

public:
    /**
     * @brief Get the Related Lane Ids 
     * 
     * @return A vector of related lane ids 
     */
    std::vector<holo::uint64_t> const& GetRelatedLaneIds() const;

    /**
     * @brief Get the Related Lane Ids 
     * 
     * @return A vector of related lane ids 
     */
    std::vector<holo::uint64_t>& GetRelatedLaneIds();

    void SetLength(holo::float64_t length);
    holo::float64_t GetLength() const;

    void SetStateFunction(StateFunction const& function);
    StateFunction GetStateFunction() const;

    void SetStateAction(StateAction const& action);
    StateAction GetStateAction() const;

    void SetStartDistance(holo::float64_t dist);
    holo::float64_t GetStartDistance() const;

    void SetEndDistance(holo::float64_t dist);
    holo::float64_t GetEndDistance() const;


    void SetStateRegionId(holo::uint64_t id);
    holo::uint64_t GetStateRegionId() const;
    
private:
    /// Related lane ids for state region
    std::vector<holo::uint64_t> lane_ids_;
    /// The legnth of state region
    holo::float64_t length_ = 0.0f;
    /// State function
    StateFunction state_function_ = StateFunction::NONE;
    /// State action
    StateAction state_action_ = StateAction::NONE;
    /// Start distance to position
    holo::float64_t start_distance_ = 0.0f;
    /// End distnace to position
    holo::float64_t end_distance_ = 0.0f;
    /// state region id
    holo::uint64_t id_ = 0;
};
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_STATE_REGION_H_ */
