/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file generator_base.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_GENERATOR_BASE_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_GENERATOR_BASE_H_

#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/router/route_info.h>
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
class LaneItemGeneratorBase
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
    using GeneratorSPtrType      = std::shared_ptr<LaneItemGeneratorBase>;

    enum class GeneratorMode : holo::uint8_t
    {
        UNDEFINED = 0,
        UNIQUE,
        SPLIT,
        INTERSECTION
    };

    struct Seed
    {
        Seed(LaneItemSPtrType item)
        {
            from = item;
        }
        LaneItemSPtrType from = nullptr;
    };

    struct NewBorn
    {
        LaneItemSPtrType to;
        // If true, stop to extend
        holo::bool_t     is_finished = false;
    };

    using NewBornVecType = std::vector<NewBorn>;

    /**
     * @brief Generate Lane Item from one to another
     *
     * @details The 'to' item may be successive to 'from' or is not.
     *          They may be has the relation as followed:
     *
     *          Case 1: Just Succeessive to another item
     *                  Item1 -> Item2
     *                   (to)     (from)
     *
     *          Case 2: Multi-item exists,
     *                   Item1 -> Item2 -> Item3 -> Item4 -> Item5
     *                   (to)                              (from)
     *
     * @param from The start item to generate
     * @param to The end item that has been generated
     * @return holo::bool_t True, exists; false, not exists
     */
    virtual holo::bool_t Generate(Seed const& seed, NewBornVecType& newborns) = 0;

    /**
     * @brief Whether or not the Generator is exclusive
     *
     * @return holo::bool_t True, no other Generators need to be executed;
     *                      False, need to execute other Generators
     */
    virtual holo::bool_t Exclusive() = 0;

    /**
     * @brief Whether or not priority other generater
     *
     * @param other Another generator
     * @return holo::bool_t True, prior to another; false, no priority
     */
    virtual holo::bool_t Priority(GeneratorSPtrType other) = 0;

    /**
     * @brief Get the Mode 
     * 
     * @return Generator's Mode 
     */
    virtual GeneratorMode GetMode() const = 0;

    /**
     * @brief Update route info
     * 
     * @return holo::bool_t 
     */
    holo::bool_t Update(RouteInfo2::Ptr);

    /**
     * @brief Update scenes
     *
     * @param scenes Scenes in route
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Update(SceneSketchSPtrVecType const& scenes);

protected:
    /**
     * @brief Check whether or not the lane itme should be finshed
     *
     * @param item Lane item
     * @return holo::bool_t True, finished; false, not be finished
     */
    holo::bool_t CheckLaneItemFinished(LaneItem const& item);

protected:
    ///> Maximum lane path length
    holo::float64_t max_lane_path_length_ = 2200.0f;
    ///> Route info
    RouteInfo2::Ptr route_info_ = nullptr;
    /// Scenes in route
    SceneSketchSPtrVecType scene_sketchs_;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_GENERATOR_BASE_H_ */