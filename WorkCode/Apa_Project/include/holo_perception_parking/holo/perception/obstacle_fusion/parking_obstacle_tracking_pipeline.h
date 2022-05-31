/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_obstacle_tracking_pipeline.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-17"
 */
#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_TRACKING_PIPELINE_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_OBSTACLE_TRACKING_PIPELINE_H_

#include <holo/numerics/vector.h>
#include <holo/perception/fusion/tracking_pipeline.h>
#include <holo/perception/obstacle_fusion/parking_fused_obstacle_track.h>
#include <holo/perception/tracking/track_container.h>
#include <holo/perception/utils/dg_port.h>
#include <holo/probability/ransac/ransac_line2_fitting_problem.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <holo/probability/ransac/impl/ransac.hpp>
#include <holo/probability/ransac/impl/ransac_line2_fitting_problem.hpp>
#include <holo/probability/ransac/impl/ransac_problem.hpp>

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
 * @brief obstacle tracking pipeline interface for parking
 * @details following common tracking pipeline and define association machanism
 *
 */

class ParkingObstacleTrackingPipeline
  : public TrackingPipeline<SensorMeasurementKey, ParkingFusedObstacleTrack, SensorMeasurementKeyHash>
{
public:
    using Scalar       = float32_t;
    using String       = std::string;
    using Vector       = std::vector<Scalar>;
    using Map          = std::unordered_map<String, Vector>;
    using Base         = TrackingPipeline<SensorMeasurementKey, ParkingFusedObstacleTrack, SensorMeasurementKeyHash>;
    using Vector3f     = holo::numerics::Vector3f;
    using PropertyType = ObstacleProperty<Scalar>;

    /**
     * @brief Construct a tacking pipeline object
     * @details initialize with default track_id = 0U, and max_track_id
     *
     */
    ParkingObstacleTrackingPipeline();

    /**
     * @brief Setup configurationfile
     *
     * @param config_file configuration file address
     */
    void Setup(holo::yaml::Node const& node);

    /**
     * @brief tracking pipeline update
     *
     * @param timestamp cuurent time stamp
     * @param vel_body ego car's velocity computed from Odometry
     * @param measurement_map new measurement
     */
    void Update(Timestamp const& timestamp, Vector3f const& vel_body, Scalar const& angular_velocity,
                Pose3f const& odo_pose, MeasurementMap const& measurement_map);

    /**
     * @brief get position abnormal flag
     *
     * @return bool
     */
    bool_t GetPostionChecker()
    {
        return position_checker_;
    }

    /**
     * @brief crossing obstacles abnormal flag
     *
     */
    bool_t IsCrossingObstacle()
    {
        return this->crossing_obstacles_;
    }

    /**
     * @brief crossing obstacles abnormal flag
     *
     * @return Vector3f
     */
    Vector3f GetVelocityBody()
    {
        return vel_body_;
    }

    /**
     * @brief get angular velocity
     *
     * @return scalar
     */
    Scalar GetAngularVelocity()
    {
        return angular_velocity_;
    }

    /**
     * @brief get odometry pose
     *
     * @return Pose3f
     */
    Pose3f GetOdometryPose()
    {
        return odometry_pose_;
    }

private:
    /**
     * @brief tracking pipeline associate strategy
     * @details associate measurement_map_ and track_map_, store the results in cluster_map
     *
     * @param measurement_map new measurement map
     */
    void associate(MeasurementMap const& measurement_map) override;

    /**
     * @brief create new track machanism
     *
     * @param cluster current cluster
     */
    void createNewTrack(ClusterPtr const cluster) override;

    /**
     * @brief remove track
     * @details remove track if lost a mount of count
     */
    void removeOldTrack() override;

    /**
     * @brief  init velocity for a track
     * @details using position variance as velocity indicator
     * @param track_ptr shared pointer to a track object
     */
    void correctTrack(std::shared_ptr<ParkingFusedObstacleTrack>& track, bool_t& postion_check);

private:
    /**
     * @brief computer mean cluster property
     * @details get mean obstacle PropertyType from both track and measure in a certain cluster
     *
     * @param cluster a cluster contained associated measurementMap and trackMap
     * @return averaged obstacle property
     */
    PropertyType computeVisionMeanClusterProperty(ClusterPtr const& cluster);

    /**
     * @brief computer mean cluster property
     * @details get mean obstacle PropertyType from both track and measure in a certain cluster,
     * main change: use closest points on obstacle bbox instead of position.
     *
     * @param cluster a cluster contained associated measurementMap and trackMap
     * @return averaged obstacle property
     */
    PropertyType computeUssMeanClusterProperty(ClusterPtr const& cluster);

    /**
     * @brief  get distance from prop and current measurement
     * @param prop property from a certain cluster
     * @param measure measure
     * @return distance
     */
    void getDistance(PropertyType const& prop, MeasurementPtr const& measure, Scalar& azimuth_dist,
                     Scalar& euclean_dist);

    /**
     * @brief  compute the closest point to origin on vision bounding box
     * @details using yaw as the pose
     * @param prop property of a obstacle
     * @return the point close to origin as point3f
     */
    Point3f getNearestPositionOnVisionObstacle(PropertyType const& prop);

    /**
     * @brief correct track's cls and pos according to history measurement
     *
     * @param track fused track ptr
     */
    void correctTrackProps(std::shared_ptr<ParkingFusedObstacleTrack>& track);

    /**
     * @brief correct track's velocity according to history measurement
     *
     * @param track fused track ptr
     */
    void ransacFittingVelocity(std::shared_ptr<ParkingFusedObstacleTrack>& track);

    /**
     * @brief lock a track's if requirements satisfied
     *
     * @param track fused track ptr
     */
    void lockTrackSatisfied(std::shared_ptr<ParkingFusedObstacleTrack>& track);

private:
    Vector3f            vel_body_;
    Scalar              angular_velocity_;
    Pose3f              odometry_pose_;
    uint32_t            track_id_;
    uint32_t            max_track_id_;
    Scalar              gaussian_smooth_std_;
    Scalar              matching_dist_thres_;
    Scalar              matching_angle_thres_;
    Scalar              timing_lost_thres_;
    Map                 track_params_map_;
    bool_t              position_checker_;
    bool_t              crossing_obstacles_;
    std::vector<Scalar> sensor_field_of_view_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
