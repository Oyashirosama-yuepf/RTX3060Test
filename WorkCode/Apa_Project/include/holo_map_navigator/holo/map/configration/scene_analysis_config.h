/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_analysis_config.h
 * @brief Configuration for scene analysis
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_CONFIGURATION_SCENE_ANALYSIS_CONFIG_H_
#define HOLO_MAP_CONFIGURATION_SCENE_ANALYSIS_CONFIG_H_

#include <holo/map/configration/configuration.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/common/yaml_helper.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace config
{
/**
 * @brief The configuration for scene analysis
 * 
 */
class SceneAnalysisConfig : public ConfigurationBase
{
public:
    using ConfigurationSPtrType = std::shared_ptr<ConfigurationBase>;
    enum class SceneCategory : holo::uint8_t
    {
        UNDEFINED                    = 0x00,  ///> Undefiend scene category
        SPLIT_TWO_MAIN_BRANCH        = 0x11,  ///> Split-flow to two ramp branches
        SPLIT_MAIN_DOWN_RAMP         = 0x12,  ///> Split-flow and drive along main road
        SPLIT_ALONG_MAIN_ROAD        = 0x13,  ///> Split-flow and drive along either branch
        SPLIT_TWO_RAMP_BRANCH        = 0x14,  ///> Split-flow to two main-road braches
        SPLIT_MULTI_BRANCH           = 0x15,  ///> More than two split-flow branches
        MERGE_MAIN                   = 0x21,  ///> Two main road merging
        MERGE_RAMP_UP_MAIN           = 0x22,  ///> Merging and drive from ramp to main road
        MERGE_ALONG_MAIN_ROAD        = 0x23,  ///> Mergint and drive along main road
        MERGE_RAMP                   = 0x24,  ///> Two ramp merging
        MERGE_MULTI_ROAD             = 0x25,  ///> More than two merging branches
        INNER_LANE_SPLIT             = 0x31,  ///> Inner lane spliting
        INNER_LANE_MERGE             = 0x32,  ///> Inner lane merging
        INNER_LANE_BREAKING          = 0x33,  ///> Inner lane breaking
        INNER_TOLL_AREA              = 0x34,  ///> Toll area
        INNER_NO_MARK                = 0x35,  ///> No mark area
        INNER_CHANGE_HIGHWAY_URBAN   = 0x36,  ///> Change between highway and urban
        INTERSECTION_CROSSROADS      = 0x41,  ///> Crossroads 
        INTERSECTION_T_JUNCTION      = 0x42,  ///> T-junction
        INTERSECTION_ROUNDABOUT      = 0x43,  ///> Roundabout
        COMPOSITE_JCT                = 0x51,  ///> From main road to ramp and going through jct, finally driving up to main road
        COMPOSITE_MULTI_INTERSECTION = 0x52,  ///> Two or more nearby intersections                 = 0x65,  ///> Fifth reserved enum value 
        OTHERS                       = 0xFF   ///> Others
    };
    struct SceneSetting
    {
        holo::float64_t distance = -1.0f;
        SceneCategory   category;
        holo::bool_t    actived = false;
    };

    ConfigCategory GetCategory() override;

    holo::bool_t Load(holo::yaml::Node const& node) override;

    holo::float64_t GetMaximumSearchDistance() const;

    std::vector<SceneSetting>const& GetSceneSettings() const;

private:
    holo::bool_t loadSplitTwoMainBranchConfig(holo::yaml::Node const& node);

    holo::bool_t loadSplitMainDownRamp(holo::yaml::Node const& node);

    holo::bool_t loadSplitAlongMainRoad(holo::yaml::Node const& node);

    holo::bool_t loadSplitTwoRampBranch(holo::yaml::Node const& node);

    holo::bool_t loadSplitMultiBranch(holo::yaml::Node const& node);

    holo::bool_t loadMergeMain(holo::yaml::Node const& node);

    holo::bool_t loadMergeRampUpMain(holo::yaml::Node const& node);

    holo::bool_t loadMergeAlongMainRoad(holo::yaml::Node const& node);

    holo::bool_t loadMergeRamp(holo::yaml::Node const& node);

    holo::bool_t loadMergeMultiRoad(holo::yaml::Node const& node);

    holo::bool_t loadInnerLaneSplit(holo::yaml::Node const& node);

    holo::bool_t loadInnerLaneMerge(holo::yaml::Node const& node);

    holo::bool_t loadInnerLaneBreaking(holo::yaml::Node const& node);

    holo::bool_t loadInnerTollArea(holo::yaml::Node const& node);

    holo::bool_t loadInnerNoMark(holo::yaml::Node const& node);

    holo::bool_t loadInnerChangeHighwayUrban(holo::yaml::Node const& node);

    holo::bool_t loadIntersectionCrossroads(holo::yaml::Node const& node);

    holo::bool_t loadIntersectionTJunction(holo::yaml::Node const& node);

    holo::bool_t loadIntersectionRoundabout(holo::yaml::Node const& node);

    holo::bool_t checkSceneSettingUnique() const;

private:
    std::vector<SceneSetting> scene_settings_;
    holo::float64_t           maximum_search_distance_ = 0.0f;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_SCENE_ANALYSIS_CONFIG_H_ */