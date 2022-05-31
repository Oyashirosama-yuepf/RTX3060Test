/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_uss_obstacle_tracking_pipeline.h
 * @brief This header file defines uss tracking pipeline.
 * @author wenxunzhe(wenxunzhe@holomatic.com)
 * @date "2021-11-29"
 */
#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_USS_OBSTACLE_TRACKING_PIPELINE_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_USS_OBSTACLE_TRACKING_PIPELINE_H_

#include <holo/numerics/vector.h>
#include <holo/perception/obstacle_fusion/parking_uss_obstacle_track.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <holo/perception/fusion/impl/tracking_pipeline.hpp>

namespace holo
{
namespace perception
{
/**
 * @addtogroup fusion
 *
 * @{
 */

/**
 * @brief a tracking pipeline for uss obsatcles
 * @details uss obsatcle pipeline is derived from a base tracking pipeline
 *
 */

class ParkingUssObstacleTrackingPipeline : public TrackingPipeline<uint32_t, UssObsTrack, std::hash<uint32_t>>
{
public:
    using Scalar         = float32_t;
    using Vector3f       = holo::numerics::Vector3f;
    using String         = std::string;
    using Vector         = std::vector<Scalar>;
    using Map            = std::unordered_map<String, Vector>;
    using Base           = TrackingPipeline<uint32_t, UssObsTrack, std::hash<uint32_t>>;
    using MeasurementMap = Base::MeasurementMap;
    using Cluster        = Base::Cluster;
    using ClusterPtr     = Base::ClusterPtr;
    using Track          = Base::Track;
    using TrackPtr       = Base::TrackPtr;
    using Measurement    = Base::Measurement;
    using MeasurementPtr = Track::MeasurementPtr;
    using PropertyType   = ObstacleProperty<Scalar>;

    /**
     * @brief uss tracking pipeline constructor
     */
    ParkingUssObstacleTrackingPipeline();

    /**
     * @brief update tracks state using new measurements
     *
     * @param current_timestamp current timestamp
     * @param vel_body ego car's velocity mass
     * @param angular_velocity ego car's angular velocity
     * @param measurement_map new uss measurements
     */
    void Update(Timestamp const& timestamp, Vector3f const& vel_body, Scalar const& angular_velocity,
                MeasurementMap const& measurement_map);

    /**
     * @brief return angular velocity
     *
     * @param angular_velocity_ angular verlocity of ego car
     */
    Scalar GetAngularVelocity()
    {
        return angular_velocity_;
    }

protected:
    /**
     * @brief associate tracks and measurements
     *
     * @details association results should store in cluster_map_
     *
     * @param measurement_map measurements
     */
    void associate(MeasurementMap const& measurement_map) override;

    /**
     * @brief create a new track from a cluster
     *
     * @param cluster cluster
     */
    void createNewTrack(ClusterPtr const cluster) override;

    /**
     * @brief remove old tracks in track map
     */
    void removeOldTrack() override;

    /**
     * @brief remove old tracks in track map
     *
     * @param cluster pointer to a cluster
     */
    PropertyType computeMeanClusterProperty(ClusterPtr const cluster);

private:
    uint32_t track_id_;
    uint32_t max_track_id_;
    Vector3f vel_body_;
    Scalar   angular_velocity_;

    // tracking pipeline params
    Scalar   matching_dist_thres_;
    uint32_t removal_lost_count_thres_;

    // track params
    Map track_params;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
