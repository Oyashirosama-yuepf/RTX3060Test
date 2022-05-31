/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file global_config.h
 * @brief Generate lane path for lane-level navigation
 * @author yuhongbo (yuhongbo@holomatic.com)
 * @date 2022-3-7
 */

#ifndef HOLO_MAP_CONFIGURATION_GLOBAL_CONFIG_H_
#define HOLO_MAP_CONFIGURATION_GLOBAL_CONFIG_H_

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
 * @brief Global configuration
 *
 * @note Global configuration contains two sections:
 *       one is the general configuration section in Yaml,
 *       another is the module configurations such as scene
 *       analysis, lanepath analysis
 *
 */
class GlobalConfig : public ConfigurationBase, public std::enable_shared_from_this<GlobalConfig>
{
public:
    using ConfigurationSPtrType = std::shared_ptr<ConfigurationBase>;

    ConfigCategory GetCategory() override;

    holo::bool_t Load(holo::yaml::Node const& node) override;

    std::string GetTopicOdometry() const;

    std::string GetTopicOdometrySim() const;

    std::string GetTopicNavigation() const;

    std::string GetTopicLocalMapGraph() const;

    std::string GetTopicLocalMapIntersection() const;

    std::string GetTopicLocalMapServiceWriter() const;
    std::string GetTopicLocalMapServiceReader() const;

    std::string GetTopicAdasisWriter() const;
    std::string GetTopicAdasisReader() const;

    holo::uint64_t GetTopicLocalMapServiceTokenId() const;

    std::string GetTopicGeofence() const;

    std::string GetTopicRoadAttribute() const;

    std::string GetTopicRoadInterval() const;

    std::string GetTopicAppStatus() const;

    holo::float64_t GetHzNavigation() const;

    holo::float64_t GetHzLocalMapGraph() const;

    holo::float64_t GetLMGFrontDistance() const;

    holo::float64_t GetLMGRearDistance() const;

    holo::bool_t IsLMGWithUTMCoordinateEnabled() const;

    holo::bool_t IsLMGWithBenchMark() const;

    holo::bool_t IsLMGWithTruncationModeEnabled() const;

    std::string GetNodeName() const;

    holo::uint8_t GetDomainId() const;

    holo::bool_t IsEnableDebug() const;

    holo::bool_t IsEnableSimulator() const;

    holo::bool_t IsEnableDataSourceWithBaiduEHP() const;

    holo::bool_t IsEnableReparing() const;

    holo::bool_t IsEnableBetaMode() const;


    void SetNodeName(std::string const name);

    void SetDomainId(holo::uint8_t const domain_id);

    void SetDebug(holo::bool_t const v);

    void SetEnableSimulator(holo::bool_t const sim);

    void SetEnableLMGWithUTMCoordinate(holo::bool_t const enable);

    void SetEnableLMGWithBenchmark(holo::bool_t const enable);

    void SetEnableLMGWithTruncationMode(holo::bool_t const enable);

    void SetEnableDataSourceWithBaiduEHP(holo::bool_t const enable);

    void SetEnableRepairing(holo::bool_t const enable);

    void SetBetaMode(holo::bool_t const beta);

private:
    holo::bool_t loadTopics(holo::yaml::Node const& node);

    holo::bool_t loadGlobalNavigation(holo::yaml::Node const& node);

    holo::bool_t loadGlobalLocalMapGraph(holo::yaml::Node const& node);

    holo::bool_t loadOtherCmdParams(holo::yaml::Node const& node);

    holo::bool_t loadSceneAnalysis(holo::yaml::Node const& node);

    holo::bool_t loadLanePathAnalysis(holo::yaml::Node const& node);

    holo::bool_t loadLanePathExpector(holo::yaml::Node const& node);

    holo::bool_t loadRegionModel(holo::yaml::Node const& node);

private:
    std::string topic_odometry_;
    std::string topic_odometry_sim_;
    std::string topic_navigation_;
    std::string topic_local_map_graph_;
    std::string topic_local_map_intersection_;
    std::string topic_local_map_service_writer_;
    std::string topic_local_map_service_reader_;
    std::string topic_local_map_service_token_id_;
    std::string topic_geofence_;
    std::string topic_road_attribute_;
    std::string topic_road_interval_;
    std::string topic_app_status_;
    std::string topic_adasis_ehp_writer_;
    std::string topic_adasis_ehp_reader_;

    holo::bool_t  log_verbose_ = false;
    holo::bool_t  log_sync_    = false;
    holo::bool_t  log_single_  = false;
    std::string   log_storage_;
    holo::uint8_t log_min_level_ = 0U;

    holo::float64_t hz_navigation_                   = 0.0f;
    holo::float64_t lmg_hz_                          = 0.0f;
    holo::float64_t lmg_front_distance_              = 0.0f;
    holo::float64_t lmg_rear_distance_               = 0.0f;
    holo::bool_t    lmg_enable_with_utm_coordinate_  = false;
    holo::bool_t    lmg_enable_with_benchmark_       = false;
    holo::bool_t    lmg_enable_with_truncation_mode_ = false;

    std::string   node_name_;
    holo::uint8_t domain_id_ = 0U;

    holo::bool_t enable_data_source_with_baidu_ehp_ = false;
    holo::bool_t enable_repairing_                  = false;
    holo::bool_t enable_beta_mode_                  = false;
};

}  // namespace config
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_CONFIGURATION_GLOBAL_CONFIG_H_ */