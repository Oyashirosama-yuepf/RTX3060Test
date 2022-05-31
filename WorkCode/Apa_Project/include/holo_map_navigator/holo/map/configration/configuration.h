/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file configuratiojn.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_CONFIGURATION_CONFIGURATION_H_
#define HOLO_MAP_CONFIGURATION_CONFIGURATION_H_

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
class ConfigurationBase : std::enable_shared_from_this<ConfigurationBase>
{
public:
    using ConfigurationSPtrType = std::shared_ptr<ConfigurationBase>;

    virtual ~ConfigurationBase() = default;

    enum class ConfigCategory : holo::uint8_t
    {
        UNDEFINED,
        GLOBAL,              ///> Global configuration including general section in YAML
        SCENE_ANALYSIS,      ///> The module configuration for scene analysis
        LANE_PATH_ANALYSIS,  ///> The module configuration for Lane Path Analysis
        LANE_PATH_EXPECTOR,  ///> The module configuration for Expector
        REGION_MODEL         ///> The module configuration for Region Model
    };

    /**
     * @brief Whether or not contains configuration of certain category
     *
     * @param category The target configuration category
     * @return  True, succeed; false, otherwise
     */
    holo::bool_t Contains(ConfigCategory const category);

    /**
     * @brief Whether or not belongs to certain category
     *
     * @param category The target configuration category
     * @return  True, succeed; false, otherwise
     */
    holo::bool_t Is(ConfigCategory const category);

    /**
     * @brief Get the Config via category
     *
     * @param category The target configuration category
     * @return Configuration
     */
    ConfigurationSPtrType GetConfig(ConfigCategory const category);

    /**
     * @brief Get the Category
     *
     * @return Configuration Category
     */
    virtual ConfigCategory GetCategory() = 0;

    /**
     * @brief Load from YAML Node
     *
     * @param node Yaml node
     * @return holo::bool_t True, succeed; false, otherwise
     */
    virtual holo::bool_t Load(holo::yaml::Node const& node) = 0;

protected:
    /// Sub-configurations for the current configuration,
    /// the configurations are stored as trees
    std::vector<ConfigurationSPtrType> configs_;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_CONFIGURATION_H_ */