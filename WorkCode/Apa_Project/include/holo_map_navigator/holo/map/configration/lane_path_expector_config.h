/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file scene_analysis_config.cpp
 * @brief Scene analysis configuration
 * @author zhengshulei (zhengshulei@holomatic.com)
 * @date 2022-04-26
 */

#ifndef HOLO_MAP_CONFIGURATION_EXPECTOR_CONFIG_H_
#define HOLO_MAP_CONFIGURATION_EXPECTOR_CONFIG_H_

#include <holo/map/common/yaml_helper.h>
#include <holo/map/configration/configuration.h>
#include <holo/map/service/client/engine/helper.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace config
{
/**
 * @brief The configuration for Lane path expector
 *
 */
class LanePathExpectorConfig : public ConfigurationBase
{
public:
    using ConfigurationSPtrType    = std::shared_ptr<ConfigurationBase>;
    using DistanceTypeV0           = holo::map::service::client::engine::helper::raw::DistanceTypeV0;
    using RawFeatureIdTypeV0       = holo::map::service::client::engine::helper::raw::RawFeatureIdTypeV0;
    using RawFeatureIdVectorTypeV0 = holo::map::service::client::engine::helper::raw::RawFeatureIdVectorTypeV0;

public:
    LanePathExpectorConfig()          = default;
    virtual ~LanePathExpectorConfig() = default;

public:
    struct StepExpectorParams
    {
        StepExpectorParams() : basic_expector_distance(1500.0), step_factor_distance(500.0){};
        // basic expector distance. unit: meter
        DistanceTypeV0 basic_expector_distance;
        // step factor distance. unit: meter
        DistanceTypeV0 step_factor_distance;
    };
    struct DownRampExpectorSetting
    {
        DistanceTypeV0 max_expected_distance  = 2500.0f;
        DistanceTypeV0 best_expected_distance = 1500.0f;
    };
    struct LanePathExpectorSettings
    {
        StepExpectorParams      step_expector_setting;
        DownRampExpectorSetting dowm_ramp_setting;
    };

public:
    ConfigCategory                  GetCategory() override;
    holo::bool_t                    Load(holo::yaml::Node const& node) override;
    LanePathExpectorSettings const& GetAllSettings() const;

private:
    holo::bool_t loadStepExpector(holo::yaml::Node const& node);
    holo::bool_t loadDownRampExpectorConfig(holo::yaml::Node const& node);

private:
    LanePathExpectorSettings settings_;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_LANE_PATH_EXPECTOR_CONFIG_H_ */
