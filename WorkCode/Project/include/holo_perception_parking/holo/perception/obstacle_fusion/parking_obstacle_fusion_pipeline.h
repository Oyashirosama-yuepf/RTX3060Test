/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_obstacle_fusion_pipeline.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-17"
 */

#ifndef HOLO_PERCEPTION_PARKING_OBSTACLE_FUSION_PARKING_OBSTACLE_FUSION_PIPELINE_H_
#define HOLO_PERCEPTION_PARKING_OBSTACLE_FUSION_PARKING_OBSTACLE_FUSION_PIPELINE_H_

#include <holo/common/odometry.h>
#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_filter.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_tracking_pipeline.h>
#include <holo/utils/holo_root.h>

#include <unordered_map>

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
 * @brief fusion pipeline interface for parking
 * @details define common fusion pipeline
 */
class ParkingObstacleFusionPipeline
{
public:
    using Scalar       = float32_t;
    using Bool         = bool_t;
    using AppStatus    = holo::uint32_t;
    using Timestamp    = holo::common::Timestamp;
    using Vector3f     = holo::numerics::Vector3f;
    using OdometryType = holo::common::Odometryf;
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;
    using ObstacleUssPtrList    = holo::obstacle::ObstacleUssPtrList;
    using ObstacleVisionPtrList = holo::obstacle::ObstacleVisionPtrList;
    using OdometryMessage       = std::shared_ptr<OdometryType>;
    using OdometryCache         = std::deque<OdometryMessage>;
    using GeneralMessage        = std::shared_ptr<ObstacleGeneralPtrList>;
    using GeneralMessageMap     = std::unordered_map<uint32_t, GeneralMessage>;
    using UssMessage            = std::shared_ptr<ObstacleUssPtrList>;
    using UssMessageMap         = std::unordered_map<uint32_t, UssMessage>;
    using VisionMessage         = std::shared_ptr<ObstacleVisionPtrList>;
    using VisionMessageMap      = std::unordered_map<uint32_t, VisionMessage>;
    using GeneralObsPtr         = std::shared_ptr<obstacle::ObstacleGeneralT<Scalar>>;

    ParkingObstacleFusionPipeline();

    /**
     * @brief defined fusion pipeline;
     * @details fusion message from all sensors and previous nodes, to obstacle fusion results;
     *
     * @param odo_msg odometry message
     * @param general_msg_map general message map
     * @param uss_msg_map uss message map
     * @param vision_msg_map vision message map from front camera
     * @param vision_avm_msg_map vision message map from avm
     * @param output_msg output fused obstacle messsage
     */
    void Compute(OdometryMessage odo_msg, GeneralMessageMap const& general_msg_map, UssMessageMap const& uss_msg_map,
                 VisionMessageMap const& vision_msg_map, OdometryCache const& odo_cache,
                 ObstacleGeneralPtrList& output_msg, AppStatus& app_status);

    /**
     * @brief set working frequency
     *
     * @param hz frequency of fusion
     */
    void SetFrequency(Scalar const& hz)
    {
        hz_ = hz;
    }

private:
    /**
     * @brief calculate ego car's velocity
     * @details velocity info will be stored in vel_body_
     *
     * @param odometry odometry message
     * @return true if it's valid odo message, false if not
     */
    bool_t getCurrentTimeAndVelocity(OdometryMessage odometry);

    /**
     * @brief generate output message from tracking pipeline results
     * @details iterate trhough each track in TrackMap to reconstruct output_msg
     *
     * @param output_msg output obstacle fusion message
     */
    void generateOutputMessage(ObstacleGeneralPtrList& output_msg, AppStatus& app_status);

    /**
     * @brief convert obstacle property type
     * @details convert track's obstacle property type into a obstacle pointer type
     *
     * @param track a single track in TrackMap
     * @return GeneralObsPtr type of track's obstacle property
     */
    GeneralObsPtr convertToOutput(ParkingFusedObstacleTrack const& track, AppStatus& app_status);

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

    /**
     * @brief CrossingObstacle CrossingObstacle
     *
     * @return bool_t
     */
    bool_t IsCrossingObstacle()
    {
        return this->tracking_pipeline_->IsCrossingObstacle();
    }

private:
    Timestamp                                        current_timestamp_;
    uint8_t                                          odometry_lost_count_;
    uint32_t                                         obstacle_response_time_;
    Vector3f                                         vel_body_;
    Scalar                                           hz_;
    Scalar                                           angular_velocity_;
    Pose3f                                           odometry_pose_;
    std::shared_ptr<ParkingObstacleFilter>           obstacle_filter_;
    std::shared_ptr<ParkingObstacleTrackingPipeline> tracking_pipeline_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
