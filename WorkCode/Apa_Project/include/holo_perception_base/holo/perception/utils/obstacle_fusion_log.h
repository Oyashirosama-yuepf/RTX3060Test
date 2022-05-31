/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_fusion_log.h
 * @brief This header file defines obstacle fusion log.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-26"
 */

#ifndef HOLO_PERCEPTION_UTILS_OBSTACLE_FUSION_LOG_
#define HOLO_PERCEPTION_UTILS_OBSTACLE_FUSION_LOG_

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>

#include <holo/common/timestamp.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/utils/holo_root.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup utils
 *
 * @{
 */

/**
 * @brief obstacle fusion log file
 *
 */
class ObstacleFusionLog
{
public:
    using Timestamp = holo::common::Timestamp;
    using SSPtr     = std::shared_ptr<std::stringstream>;

    /**
     * @brief Construct a new Obstacle Fusion Log object
     *
     * @param log_file log file name
     * @throw std::runtime_error if open file failed
     */
    ObstacleFusionLog(std::string const& log_file);

    /**
     * @brief Destroy the Obstacle Fusion Log object
     *
     */
    ~ObstacleFusionLog();
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // base function

    /**
     * @brief write a line under 'key' in the log file
     *
     * @param key key: input, filter, cluster or tracking
     * @param line line
     */
    void Write(std::string const& key, std::string const& line);
    /**
     * @brief write a frame
     * @details this should be called after every thing in this frame are written
     *
     * @param frame_index frame index
     * @param timestamp frame timestamp
     */
    void WriteFrame(uint32_t frame_index, Timestamp const& timestamp);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // utility function

    /**
     * @brief write sensor id and timestamp of the obstacle list
     *
     * @tparam ObstacleList obstacle list , eg. ObstacleVisionPtrList
     * @param obs_list obstacle list
     */
    template <typename ObstacleList>
    void WriteObstacleList(ObstacleList const& obs_list);

    /**
     * @brief write a filter result of measurement
     *
     * @param sensor_id sensor id of the measurement
     * @param obstacle_id obstacle id of the measurement
     * @param detail reason of filter the measurement, eg. low confidence
     */
    void WriteMeasurementFilterResult(uint32_t sensor_id, uint32_t obstacle_id, std::string const& detail);

    /**
     * @brief write a filter result of track
     *
     * @param track_id id of the track
     * @param detail reason of filter the track, eg. high lost count
     */
    void WriteTrackFilterResult(uint32_t track_id, std::string const& detail);

    /**
     * @brief write cluster result
     * @details
     * this function will call track->GetObstacleId()
     * and measure->GetSensorId(), measure->GetObstacleId()
     *
     * @tparam ClusterMap cluster map of a TrackingPipeline
     * @param cluster_map cluster map
     */
    template <typename ClusterMap>
    void WriteClusterResult(ClusterMap const& cluster_map);

    /**
     * @brief write a tracking operation
     * @details
     * format: operation + ' ' + detail
     * eg.
     * 'create C3 T100' , means using cluster 3 to create track 100
     * 'drop T5' , means remove track 5 from the track map
     *
     * @param detail detail of the tracking operation
     */
    void WriteTrackingResult(std::string const& detail);

private:
    std::ofstream                          ofs_;
    std::unordered_map<std::string, SSPtr> ss_map_;  // key -> stringstream pointer
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
