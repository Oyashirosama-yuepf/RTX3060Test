/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_pipeline.h
 * @brief This header file defines tight coupling fusion pipeline using radar,vision and lidar.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_PIPELINE_H_
#define HOLO_PERCEPTION_OBSATCLE_FUSION_TIGHT_FUSION_PIPELINE_H_

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
#include <holo/obstacle/fused_obstacle.h>
#endif

#include <holo/common/odometry.h>
//#include <holo/perception/obstacle_fusion/obstacle_fusion_json_format.h>
#include <holo/perception/obstacle_fusion/tight_fusion_obstacle_filter.h>
#include <holo/perception/obstacle_fusion/tight_fusion_obstacle_tracker.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <holo/perception/utils/impl/camera_group.hpp>

namespace holo
{
namespace perception
{
/**
 * @brief tight fusion pipeline
 *
 */
class TightFusionPipeline
{
public:
    using Scalar    = float32_t;
    using AppStatus = holo::uint32_t;

    using FusedObstaclePtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;

    using FusedObstaclePtr = std::shared_ptr<obstacle::ObstacleGeneralT<Scalar>>;
    using Timestamp        = common::Timestamp;
    using OdometryType     = common::Odometryf;
    using OdometryMessage  = std::shared_ptr<OdometryType>;
    // using LidarObsPtr        = std::shared_ptr<obstacle::ObstacleLidarT<Scalar>>;
    // using LidarMessage       = std::shared_ptr<obstacle::ObstacleLidarPtrList>;
    // using LidarMessageMap    = std::unordered_map<uint32_t, LidarMessage>;
    // using RadarObsPtr        = std::shared_ptr<obstacle::ObstacleRadarT<Scalar>>;
    // using RadarMessage       = std::shared_ptr<obstacle::ObstacleRadarPtrList>;
    // using RadarMessageMap    = std::unordered_map<uint32_t, RadarMessage>;

    using UssObsPtr     = std::shared_ptr<obstacle::ObstacleUssT<Scalar>>;
    using UssMessage    = std::shared_ptr<obstacle::ObstacleUssPtrList>;
    using UssMessageMap = std::unordered_map<uint32_t, UssMessage>;

    using VisionObsPtr     = std::shared_ptr<obstacle::ObstacleVisionT<Scalar>>;
    using VisionMessage    = std::shared_ptr<obstacle::ObstacleVisionPtrList>;
    using VisionMessageMap = std::unordered_map<uint32_t, VisionMessage>;

    using Vector3f           = numerics::Vector3f;
    using Matrix4f           = numerics::Matrix4f;
    using ObstacleFilterPtr  = std::shared_ptr<TightFusionObstacleFilter>;
    using ObstacleTrackerPtr = std::shared_ptr<TightFusionObstacleTracker>;
    using FusedTrackPtr      = TightFusionObstacleTracker::FusedTrackPtr;
    using CameraGroupPtr     = std::shared_ptr<CameraGroup>;
    using Classification     = common::Classification;
    using ClusterMap         = TightFusionObstacleTracker::ClusterMap;

public:
    /**
     * @brief Construct a new Tight Fusion Pipeline object
     *
     */
    TightFusionPipeline();

    /**
     * @brief setup
     *
     * @param config_file config file
     */
    void Setup();

    /**
     * @brief compute pipeline
     *
     * @param odometry odometry
     * @param uss_msg_map uss message map
     * @param vision_msg_map vision message map
     * @param output_msg output message
     */
    void Compute(OdometryMessage const odometry, UssMessageMap const& uss_msg_map,
                 VisionMessageMap const& vision_msg_map, FusedObstaclePtrList& output_msg, AppStatus& app_status);

    // /**
    //  * @brief Set the Debug Info object
    //  *
    //  * @param debug_info debug info for interactive app
    //  */
    // void SetDebugInfo(Json::Value& debug_info);

private:
    /**
     * @brief Get the Current Time And Velocity
     *
     * @param odometry odometry
     * @return bool_t true if get a new odometry message
     */
    bool_t getCurrentTimeAndVelocity(OdometryMessage const odometry);

    /**
     * @brief Get the Fused Obstacle Ptr object
     *
     * @param track track
     * @return FusedObstaclePtr fused obstacle pointer
     */
    FusedObstaclePtr getFusedObstaclePtr(FusedTrackPtr const track);

    /**
     * @brief convert ouput message
     *
     * @param track track
     * @param app_status app safety code
     * @return FusedObstaclePtr fused obstacle pointer
     */
    FusedObstaclePtr convertToOutput(FusedTrackPtr const& track, AppStatus& app_status);

    /**
     * @brief generate output message
     *
     * @param output_msg output message
     */
    void generateOutputMessage(FusedObstaclePtrList& output_msg, AppStatus& app_status);

    /**
     * @brief Get the Box2 object
     *
     * @param info
     * @return geometry::Box2f
     */
    geometry::Box2f getBox2(std::array<Scalar, 4U> const& info);

    /**
     * @brief print cluster map, debug use
     *
     * @param cluster_map cluster map
     */
    void printCluster(const ClusterMap& cluster_map);

    /**
     * @brief update app status code according to the position, velocity, score
     *
     * @param x position x
     * @param y position y
     * @param vx abs velocity along x
     * @param vy abs velocity along y
     * @param score obsatcle existing score
     * @return GeneralObsPtr type of track's obstacle property
     */
    void AppStatusChecker(Scalar const& x, Scalar const& y, Scalar const& vx, Scalar const& vy, Scalar const& score,
                          AppStatus& app_status);

private:
    Timestamp          current_timestamp_;          /* current timestamp */
    Vector3f           vel_body_;                   /* body linear velocity */
    Scalar             angular_velocity_   = 0.0f;  /* body yaw velocity */
    bool_t             last_odometry_flag_ = false; /* whether receive odometry */
    Matrix4f           body_transformation_;        /* last body to current body pose */
    Matrix4f           last_odometry_pose_;         /* last body pose */
    CameraGroupPtr     camera_group_;
    ObstacleFilterPtr  obstacle_filter_;
    ObstacleTrackerPtr obstacle_tracker_;

    uint8_t odometry_lost_count_;
    Pose3f  odometry_pose_;
};

}  // namespace perception
}  // namespace holo

#endif
