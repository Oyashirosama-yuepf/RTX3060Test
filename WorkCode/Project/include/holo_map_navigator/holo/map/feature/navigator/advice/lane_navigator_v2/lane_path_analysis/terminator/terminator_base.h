/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file terminator_base.h
 * @brief Terminator is used to stop extending of lane path
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-23
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_TERMINATOR_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_TERMINATOR_BASE_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_sketch.h>
#include <holo/map/feature/navigator/router/route_info.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
namespace lanepath
{
class TerminatorBase
{
public:
    using LaneItemSPtrType       = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType    = std::vector<LaneItemSPtrType>;
    using LanePathSPtrType       = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;
    using SceneSketchType        = holo::map::navigator::advice::scene::SceneSketch;
    using SceneCategoryType      = SceneSketchType::SceneCategory;
    using SceneSketchSPtrType    = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;
    using TerminatorSPtrType         = std::shared_ptr<TerminatorBase>;

    /**
     * @brief Different category of lane path terminator
     * 
     * @note Each enumerated value corresponds to a Terminator
     */
    enum class TerminatorCategory : holo::uint8_t
    {
        UNDEFINED = 0,
        NO_SUCCEEDING,  /// Current lane item has no sccceeding lanes
        INTERSECTION,   /// Current lane item is in intersection
        JCT,            /// Current lane item is in JCT scene
        DOWN_RAMP,      /// Current lane item is down ramp
        DEFAULT_MERGE,  /// Default strategy for merge scene
        MERGE,          /// Current lane item is merging
        OTHERS = 255
    };

    /**
     * @brief The target that should be checked
     */ 
    struct TerminatorTarget
    {
        /// The target need to be checked
        LaneItemSPtrType item     = nullptr;
        /// If true, the target as end of lane path should be stopped to extend;
        /// If false, continue to extend lane path
        holo::bool_t terminated = false;
    };

    virtual ~TerminatorBase() = default;

    /**
     * @brief Whethor or not the terminator take effect
     *
     * @return holo::bool_t True, take effect; false, no effect
     */
    virtual holo::bool_t Enable() = 0;

    /**
     * @brief Compared with another terminator
     *
     * @param terminator Another terminator
     * @return holo::bool_t True, take priority over another; false, not prior, may equally
     */
    virtual holo::bool_t HavePriorityOver(TerminatorSPtrType terminator) = 0;

    /**
     * @brief Get the Category 
     * 
     * @return TerminatorCategory 
     */
    virtual TerminatorCategory GetCategory() = 0;

    /**
     * @brief Check the whether or not the target should be stop to extend
     *
     * @param target Terminator target need to be checked
     * @return holo::bool_t
     */
    holo::bool_t Check(TerminatorTarget& target);
    
    /**
     * @brief Update route info
     *
     * @param route
     * @return holo::bool_t
     */
    holo::bool_t Update(RouteInfo2::Ptr route);

    /**
     * @brief Update scenes
     *
     * @param scenes Scenes in route
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Update(SceneSketchSPtrVecType const& scenes);

    /**
     * @brief Set the max distance for terminate for the lane
     */
    void SetSearchDistance(holo::float64_t const dist);


protected:
    /**
     * @brief Check the whether or not the target should be stop to extend
     *
     * @param targets Targets that should be checked
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t doCheck(TerminatorTarget& target) = 0;

    /**
     * @brief Basic check whether or not to stop extending;
     *
     * @param target Checked target
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t basicCheck(TerminatorTarget& target);

protected:
    /// Max lane path length, Unit: meters
    holo::float64_t max_path_length_ = 2000.0;
    /// Route info
    RouteInfo2::Ptr route_info_ = nullptr;
    /// Scenes in route
    SceneSketchSPtrVecType scene_sketchs_;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_TERMINATOR_BASE_H_ */