/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_id_tracking_pipeline.h
 * @brief This header file defines tracking pipeline using sensor id and obstacle id to associate.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-07-06"
 */

#ifndef HOLO_PERCEPTION_UTILS_OBSTACLE_ID_TRACKING_PIPELINE_H_
#define HOLO_PERCEPTION_UTILS_OBSTACLE_ID_TRACKING_PIPELINE_H_

#include <holo/perception/utils/sensor_obstacle_track.h>
#include <holo/perception/fusion/impl/tracking_pipeline.hpp>

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
 * @brief a tracking pipeline using obstacle's sensor id and obstacle id to associate
 *
 * @tparam _Track track
 */
template <typename _Track>
class ObstacleIdTrackingPipeline : public TrackingPipeline<SensorMeasurementKey, _Track, SensorMeasurementKeyHash>
{
public:
    using Base           = TrackingPipeline<SensorMeasurementKey, _Track, SensorMeasurementKeyHash>;
    using MeasurementMap = typename Base::MeasurementMap;
    using Cluster        = typename Base::Cluster;
    using ClusterPtr     = typename Base::ClusterPtr;
    using Track          = typename Base::Track;
    using TrackPtr       = typename Base::TrackPtr;
    using Measurement    = typename Base::Measurement;
    using MeasurementPtr = typename Track::MeasurementPtr;

    /**
     * @brief Construct a new Obstacle Id Tracking Pipeline object
     *
     */
    ObstacleIdTrackingPipeline();

protected:
    /**
     * @brief associate measurement and track using <sensor_id, obstacle_id> as key
     *
     * @param measurement_map measurements
     */
    virtual void associate(MeasurementMap const& measurement_map) override;

    /**
     * @brief Create a New Track
     *
     * @param cluster cluster
     */
    virtual void createNewTrack(ClusterPtr const cluster) override;

    /**
     * @brief remove old track
     *
     */
    virtual void removeOldTrack() override;

    /**
     * @brief determine if the track and measurement are matched
     *
     * @param track track
     * @param measurement measurement
     * @return bool_t true if they match
     */
    virtual bool_t match(TrackPtr const track, MeasurementPtr const measurement);

protected:
    uint32_t cluster_id_;
};

using GeneralObstacleIdTracker = ObstacleIdTrackingPipeline<GeneralObstacleTrack>;
using LidarObstacleIdTracker   = ObstacleIdTrackingPipeline<LidarObstacleTrack>;
using RadarObstacleIdTracker   = ObstacleIdTrackingPipeline<RadarObstacleTrack>;
using VisionObstacleIdTracker  = ObstacleIdTrackingPipeline<VisionObstacleTrack>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
