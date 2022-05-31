/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file export_obstacle_fusion_message_app.cpp
 * @brief This header file defines .
 * @author yuanfeiyang(yuanfeiyang@holomatic.com)
 * @date "2022-04-14"
 */

#ifndef HOLO_PERCEPTION_APP_EXPORT_OBSTACLE_FUSION_MESSAGE_APP_H_
#define HOLO_PERCEPTION_APP_EXPORT_OBSTACLE_FUSION_MESSAGE_APP_H_

#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>

#include <holo/common/odometry.h>
#include <holo/perception/fusion/fusion_json_format.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{
/**
 * @brief export obstacle fusion input message
 *
 */
class ExportObstacleFusionMessageApp
{
public:
    using OdometryType = holo::common::Odometryf;
public:
    /**
     * @brief Destroy the Export Obstacle Fusion Message App object
     * @details write to file
     *
     */
    ~ExportObstacleFusionMessageApp();

    /**
     * @brief setup
     *
     * @param config_file config file
     */
    void Setup(std::string const& config_file);

    /**
     * @brief cache odometry message
     *
     * @param input odometry message
     */
    void CacheOdometry(OdometryType const& input);

    /**
     * @brief cache uss obstacle list
     *
     * @param id uss index
     * @param input uss obstacle list
     */
    void CacheUssObsList(uint32_t id, obstacle::ObstacleUssPtrList const& input);

    /**
     * @brief cache vision obstacle list
     *
     * @param id vision index
     * @param input vision obstacle lid
     */
    void CacheVisionObsList(uint32_t id, obstacle::ObstacleVisionPtrList const& input);

private:
    /**
     * @brief write to file
     *
     * @param root json value
     * @param output_file output file
     */
    void writeOutputFile(Json::Value const& root, std::string const& output_file);

private:
    /* mutex */
    std::mutex mutex_odometry_;
    std::mutex mutex_uss_;
    std::mutex mutex_vision_;
    std::mutex mutex_vision_srv_;
    /* json value */
    Json::Value json_odometry_;
    Json::Value json_uss_;
    Json::Value json_vision_;
    Json::Value json_vision_srv_;
    /* sensor id */
    common::SensorId sensor_id_uss_;
    common::SensorId sensor_id_vision_;
    common::SensorId sensor_id_vision_srv_;
    /* params from yaml */
    std::string bag_name_;
    std::string odometry_topic_;
    std::string uss_topic_;
    std::string vision_topic_;
    std::string vision_srv_topic_;
    std::string output_file_odometry_   = "odometry.json";
    std::string output_file_uss_        = "uss.json";
    std::string output_file_vision_     = "vision.json";
    std::string output_file_vision_srv_ = "vision_srv.json";
};

}  // namespace perception
}  // namespace holo

#endif
