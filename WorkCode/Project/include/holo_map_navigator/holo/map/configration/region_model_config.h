/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file region_model_config.h
 * @brief Configuration for region model
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-5-7
 */

#ifndef HOLO_MAP_CONFIGURATION_REGION_MODEL_CONFIG_H_
#define HOLO_MAP_CONFIGURATION_REGION_MODEL_CONFIG_H_

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
 * @brief The configuration for scene analysis
 *
 */
class RegionModelConfig : public ConfigurationBase
{
public:
    struct MainRoadSetting
    {
        holo::float64_t change_region_interval_length = 200.0f;
        holo::float64_t distance_ready_to_risk        = 1000.0f;
    };
    struct DownRampSetting
    {
        holo::float64_t max_search_joint_length = 200.0f;
        holo::float64_t max_region_length       = 200.0f;
        holo::float64_t rate_risk_to_ultimate = 0.3f;
    };

    struct RampSplitSetting
    {
        holo::float64_t max_search_joint_length = 200.0f;
        holo::float64_t max_region_length       = 200.0f;
        holo::float64_t rate_risk_to_ultimate = 0.3f;
    };

    struct MergeToRoadSetting
    {
        holo::float64_t max_search_joint_length = 200.0f;
        holo::float64_t max_region_length       = 200.0f;
        holo::float64_t rate_risk_to_ultimate = 0.3f;
    };

public:
    ConfigCategory GetCategory() override;

    holo::bool_t Load(holo::yaml::Node const& node) override;

    MainRoadSetting const GetMainRoadSetting() const;

    DownRampSetting const GetDownRampSetting() const;

    RampSplitSetting const GetRampSplitSetting() const;

    MergeToRoadSetting const GetMergeToRoadSetting() const;

private:
    holo::bool_t loadMainRoadSetting(holo::yaml::Node const&);
    holo::bool_t loadDownRampSetting(holo::yaml::Node const&);
    holo::bool_t loadRampSplitRoadSetting(holo::yaml::Node const&);
    holo::bool_t loadMergeToRoadSetting(holo::yaml::Node const&);

private:
    MainRoadSetting main_road_setting_;
    DownRampSetting down_ramp_setting_;
    RampSplitSetting ramp_split_setting_;
    MergeToRoadSetting merge_to_road_setting_;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_SCENE_ANALYSIS_CONFIG_H_ */