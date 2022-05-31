/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_path_analysis_config.h
 * @brief Configuration for lane-path analysis
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_CONFIGURATION_LANE_PATH_ANALYSIS_CONFIG_H_
#define HOLO_MAP_CONFIGURATION_LANE_PATH_ANALYSIS_CONFIG_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/yaml_helper.h>
#include <holo/map/configration/configuration.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace config
{
/**
 * @brief Get the configuraiton for lane path analysis
 *
 */
class LanePathAnalysisConfig : public ConfigurationBase
{
public:
    using ConfigurationSPtrType = std::shared_ptr<ConfigurationBase>;
    enum class LaneItemGeneratorCategory : holo::uint8_t
    {
        UNDEFINED,
        UNIQUE,
        SPLIT,
        INTERSECTION
    };
    enum class ConstraintCategory : holo::uint8_t
    {
        INNER_SPLIT_CONSTRAINT,
        INNER_MERGE_CONSTRAINT,
        ROAD_MERGE_CONSTRAINT,
        ROAD_SPLIT_CONSTRAINT,
        INNER_SPLIT_NO_CONSTRAINT
    };
    enum class TerminatorCategory : holo::uint8_t
    {
        DOWN_RAMP_TERMINATOR,
        INTERSECTION_TERMINATOR,
        JCT_TERMINATOR,
        MERGE_TERMINATOR,
        NO_SUCCEED_TERMINATOR
    };
    struct LaneItemGeneratorSetting
    {
        LaneItemGeneratorCategory category;
        holo::bool_t              actvied = false;
    };
    struct ConstraintSetting
    {
        ConstraintCategory category;
        holo::float64_t    distacne = 0.0f;
        holo::bool_t       actvied  = false;
    };
    struct TerminatorSetting
    {
        TerminatorCategory category;
        holo::float64_t    distance = 0.0f;
        holo::bool_t       actvied  = false;
    };
    struct LaneItemGeneratorConfig
    {
        std::vector<LaneItemGeneratorSetting> settings;
    };
    struct ConstraintConfig
    {
        std::vector<ConstraintSetting> settings;
        holo::float64_t                search_distance = 0.0f;
    };

    struct TerminatorConfig
    {
        std::vector<TerminatorSetting> settings;
        holo::float64_t                search_distance = 0.0f;
    };
    struct LanePathGeneratorConfig
    {
        std::string                          identifier            = "default";
        holo::bool_t                         is_pre_generator      = false;
        holo::float64_t                      pre_generate_distance = 0;
        std::vector<LaneItemGeneratorConfig> lane_item_generator_configs;
        std::vector<ConstraintConfig>        constraint_configs;
        std::vector<TerminatorConfig>        terminator_configs;
    };

    ConfigCategory GetCategory() override;

    holo::bool_t Load(holo::yaml::Node const& node) override;

    std::vector<LanePathGeneratorConfig> const& GetLanePathGeneratorConfigs() const;

private:
    holo::bool_t loadLanePathGeneratorSettings(holo::yaml::Node const& node);

private:
    std::vector<LanePathGeneratorConfig> lane_path_generator_configs_;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_LANE_PATH_ANALYSIS_CONFIG_H_ */