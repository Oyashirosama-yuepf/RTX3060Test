/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_item_generator_manager.h
 * @brief Manager lane item generator
 * @author chanqiliang (chanqiliang@holomatic.com)
 * @date 2022-4-13
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_GENERATOR_MANAGER_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_GENERATOR_MANAGER_H_
#include <holo/map/feature/navigator/advice/lane_navigator/lane_item.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_path.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_item_generator/lane_item_generator_base.h>
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
class LaneItemGeneratorManager
{
public:
    using LaneItemSPtrType             = std::shared_ptr<LaneItem>;
    using LaneItemSPtrVecType          = std::vector<LaneItemSPtrType>;
    using LanePathSPtrType             = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType          = std::vector<LanePathSPtrType>;
    using SceneSketchType              = holo::map::navigator::advice::scene::SceneSketch;
    using SceneCategoryType            = SceneSketchType::SceneCategory;
    using SceneSketchSPtrType          = std::shared_ptr<SceneSketchType>;
    using SceneSketchSPtrVecType       = std::vector<SceneSketchSPtrType>;
    using LaneItemGeneratorBaseType    = holo::map::navigator::advice::lanepath::LaneItemGeneratorBase;
    using LaneItemGeneratorSPtrType    = std::shared_ptr<LaneItemGeneratorBaseType>;
    using LaneItemGeneratorSPtrVecType = std::vector<LaneItemGeneratorSPtrType>;
    using SeedType                     = holo::map::navigator::advice::lanepath::LaneItemGeneratorBase::Seed;
    using NewbornType                  = holo::map::navigator::advice::lanepath::LaneItemGeneratorBase::NewBorn;
    using NewbornVecType               = std::vector<NewbornType>;

public:
    LaneItemGeneratorManager()  = default;
    ~LaneItemGeneratorManager() = default;

    /**
     * @brief Add a new generator
     *
     * @param lane_item_generator new added generator
     * @return
     */
    void Add(LaneItemGeneratorSPtrType const& lane_item_generator);

    /**
     * @brief Delete a generators by given mode
     *
     * @param mode generator mode
     * @return
     */
    void Remove(LaneItemGeneratorBaseType::GeneratorMode const& mode);

    /**
     * @brief Delete all generators
     *
     * @param
     * @return
     */
    void Clear();

    /**
     * @brief Update route info
     *
     * @param route_info
     * @return holo::bool_t
     */
    holo::bool_t Update(RouteInfo2::Ptr route_info);

    /**
     * @brief Update scenes
     *
     * @param scenes Scenes in route
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t Update(SceneSketchSPtrVecType const& scenes);


    /**
     * @brief Generate lane item by all owned generators
     *
     * @param
     * @return
     */
    bool GeneratorLaneItem(SeedType const& seed, NewbornVecType& new_born);

private:
    LaneItemGeneratorSPtrVecType lane_item_generators_;
};

}  // namespace lanepath
}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_NAVIGATOR_ADVICE_LANE_NAVIGATOR_V2_LANE_PATH_ANALYSIS_LANE_ITEM_GENERATOR_MANAGER_H_