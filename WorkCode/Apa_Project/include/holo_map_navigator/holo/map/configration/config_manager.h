/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file config_manager.h
 * @brief Manager for configuration
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-04-13
 */

#ifndef HOLO_MAP_CONFIGURATION_CONFIG_MANAGER_H_
#define HOLO_MAP_CONFIGURATION_CONFIG_MANAGER_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/yaml_helper.h>
#include <holo/map/configration/configuration.h>
#include <holo/map/configration/global_config.h>
#include <holo/map/configration/lane_path_analysis_config.h>
#include <holo/map/configration/lane_path_expector_config.h>
#include <holo/map/configration/scene_analysis_config.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace config
{
class ConfigManager
{
public:
    using ConfigManagerSPtrType = std::shared_ptr<ConfigManager>;
    using ConfigurationSPtrType = std::shared_ptr<ConfigurationBase>;

public:
    /**
     * @brief Get instance of configuration manager
     *
     * @return Instance of configuration manager
     */
    static ConfigManagerSPtrType Instance();

    /**
     * @brief Get the Config by configuration category
     *
     * @param category Configuration category
     * @return Configuration
     */
    ConfigurationSPtrType GetConfig(ConfigurationBase::ConfigCategory const category);

    /**
     * @brief Load from file path
     *
     * @param path Yaml file path
     * @return holo::bool_t True, succeed, false, otherwise
     */
    holo::bool_t Load(std::string const path);

private:
    /**
     * @brief Load from yaml Node
     *
     * @param node Yaml Node
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t load(holo::yaml::Node const& node);

private:
    /// The instance of configuraiton manager
    static ConfigManagerSPtrType instance_;

private:
    /// The root configuration
    ConfigurationSPtrType root_ = nullptr;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_CONFIG_MANAGER_H_ */