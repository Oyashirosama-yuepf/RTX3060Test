/*!
 *  \brief Map parameters in CMW node
 *  \author Hao Wentian(haowentian@holomaitc.com)
 *  \date 2017-09-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */
#ifndef _HOLO_CMW_APPS_MAP_PARAM_H_
#define _HOLO_CMW_APPS_MAP_PARAM_H_
#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include <holo/map/retriever/retriever.h>
#include <holo/utils/yaml.h>

namespace holo_cmw
{
namespace map
{
class MapParams
{
public:
    /**
     * Constructor
     */
    MapParams() = default;
    /**
     * Destructor
     */
    ~MapParams() = default;
    /**
     * MapParams init function
     * @param[in] _config_file Path of config file.
     */
    void Init(const ::std::string& _config_file);

public:
    /// topic reader
    std::string topic_name_odometry_     = "";
    std::string topic_name_vio_odometry_ = "";
    std::string topic_name_imu_odometry_ = "";
    /// topic writer
    std::string topic_name_map_advice_                        = "";
    std::string topic_name_map_navigator_app_status_          = "";
    std::string topic_name_map_geofence_                      = "";
    std::string topic_name_map_road_ref_point_type_intervals_ = "";
    std::string topic_name_map_road_ref_point_sces_           = "";
    std::string topic_name_map_lane_advice_                   = "";
    /// router calculate mode
    holo::uint8_t route_choice_ = 0;
    // true: route_choice use configuration information
    holo::bool_t route_choice_use_config_ = false;
    // render
    holo::bool_t map_lane_boundaries_render_              = false;
    holo::bool_t map_advice_render_                       = false;
    holo::bool_t map_guide_line_render_                   = false;
    holo::bool_t map_road_info_render_                    = false;
    holo::bool_t map_match_result_render_                 = false;
    holo::bool_t map_local_map_free_space_render_         = false;
    holo::bool_t map_lane_boundaries_render_struct_       = false;
    holo::bool_t map_current_road_info_render_            = false;
    holo::bool_t map_current_road_line_render_            = false;
    holo::bool_t is_statistic_function_on_                = false;
    holo::bool_t message_publish_statistic_all_switch_on_ = false;
    // frequency of message, default 30, unit hz
    holo::uint8_t hz_map_advice_info_      = 30U;
    holo::uint8_t hz_map_road_info_        = 30U;
    holo::uint8_t hz_map_poi_info_         = 30U;
    holo::uint8_t hz_local_map_free_space_ = 30U;
    holo::uint8_t hz_current_road_info_    = 30U;
    holo::uint8_t hz_guide_line_info_      = 30U;
    holo::uint8_t hz_map_benchmark_        = 30U;
};

void MapParams::Init(const ::std::string& _config_file)
{
    const holo::yaml::Node config = holo::yaml::LoadFile(_config_file);
    LOG(INFO) << "MapParams::Init config_file: " << _config_file;

    topic_name_odometry_                 = config["topics"]["odometry"].as<std::string>();
    topic_name_vio_odometry_             = config["topics"]["vio_odometry"].as<std::string>();
    topic_name_imu_odometry_             = config["topics"]["imu_odometry"].as<std::string>();
    topic_name_map_advice_               = config["topics"]["map_advice"].as<std::string>();
    topic_name_map_navigator_app_status_ = config["topics"]["navigator_app_status"].as<std::string>();
    topic_name_map_geofence_             = config["topics"]["map_geofence"].as<std::string>();
    topic_name_map_road_ref_point_sces_  = config["topics"]["map_road_ref_point_sces"].as<std::string>();
    topic_name_map_lane_advice_          = config["topics"]["map_lane_advice"].as<std::string>();
    topic_name_map_road_ref_point_type_intervals_ =
        config["topics"]["map_road_ref_point_type_intervals"].as<std::string>();

    route_choice_ = config["router"]["route_choice"].as<holo::uint8_t>();

    route_choice_use_config_           = config["router"]["use_config"].as<holo::bool_t>();
    map_lane_boundaries_render_        = config["render"]["lane_boundaries"].as<holo::bool_t>();
    map_advice_render_                 = config["render"]["advice"].as<holo::bool_t>();
    map_guide_line_render_             = config["render"]["guide_line"].as<holo::bool_t>();
    map_road_info_render_              = config["render"]["road_info"].as<holo::bool_t>();
    map_match_result_render_           = config["render"]["match_result"].as<holo::bool_t>();
    map_local_map_free_space_render_   = config["render"]["local_map_free_space"].as<holo::bool_t>();
    map_lane_boundaries_render_struct_ = config["render"]["struct_lane_boundary"].as<holo::bool_t>();
    map_current_road_info_render_      = config["render"]["current_road_info"].as<holo::bool_t>();
    map_current_road_line_render_      = config["render"]["current_road_line"].as<holo::bool_t>();

    message_publish_statistic_all_switch_on_ = config["cmw_output_switch"]["is_output_all"].as<holo::bool_t>();
    is_statistic_function_on_                = config["cmw_output_switch"]["is_function_on"].as<holo::bool_t>();

    hz_map_advice_info_      = config["advisor"]["hz"].as<holo::uint32_t>();
    hz_map_road_info_        = config["map_info"]["hz"].as<holo::uint32_t>();
    hz_map_poi_info_         = config["poi"]["hz"].as<holo::uint32_t>();
    hz_local_map_free_space_ = config["local_map_free_space"]["hz"].as<holo::uint32_t>();
    hz_current_road_info_    = config["current_road_info"]["hz"].as<holo::uint32_t>();
    hz_guide_line_info_      = config["guide_line"]["hz"].as<holo::uint32_t>();
    hz_map_benchmark_        = config["benchmark"]["hz"].as<holo::uint32_t>();
}

}  // namespace map
}  // namespace holo_cmw

#endif
