/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_obstacle_tracker.h
 * @brief This header file defines fused obstacle tracker.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_OBSTACLE_TRACKER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_OBSTACLE_TRACKER_H_

#include <holo/perception/fusion/impl/tracking_pipeline.hpp>
//#include <holo/perception/urban_fusion/obstacle_fusion_json_format.h>
#include <holo/perception/obstacle_fusion/tight_fusion_extended_kalman_filter.h>
#include <holo/perception/obstacle_fusion/tight_fusion_mst_cluster_algorithm.h>
#include <holo/perception/obstacle_fusion/tight_fusion_parameter.h>

namespace holo
{
namespace perception
{
/**
 * @brief fused obstacle tracker
 *
 */
class TightFusionObstacleTracker
  : public TrackingPipeline<uint32_t, TightFusionExtendedKalmanFilter, std::hash<uint32_t>>
{
public:
    using Base                  = TrackingPipeline<uint32_t, TightFusionExtendedKalmanFilter, std::hash<uint32_t>>;
    using Scalar                = float32_t;
    using FusedTrackPtr         = std::shared_ptr<TightFusionExtendedKalmanFilter>;
    using MeasurementMap        = Base::MeasurementMap;
    using ClusterPtr            = Base::ClusterPtr;
    using ClusterMap            = Base::ClusterMap;
    using Matrix4f              = numerics::Matrix4f;
    using Vector3f              = numerics::Vector3f;
    using CameraGroupPtr        = std::shared_ptr<CameraGroup>;
    using ObstaclePropertyType  = ObstacleProperty<float32_t>;
    using TrackFilterRule       = std::function<bool_t(TrackPtr const)>;
    using MeasurementFilterRule = std::function<bool_t(MeasurementPtr const)>;
    using CreateTrackRule       = std::function<bool_t(ClusterPtr const)>;
    using InitTrackRule         = std::function<void(ClusterPtr const, ObstaclePropertyType&)>;
    using RemoveTrackRule       = std::function<bool_t(TrackPtr const)>;

public:
    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group pointer
     */
    void SetCameraGroup(CameraGroupPtr const camera_group);

    /**
     * @brief update the tracker
     *
     * @param measurement_map measurement map
     * @param current_timestamp current timestamp
     * @param body_transformation body transformation
     * @param vel_body body linear velocity
     * @param angular_velocity body yaw velocity
     */
    void Update(MeasurementMap const& measurement_map, Timestamp const& current_timestamp,
                Matrix4f const& body_transformation, Vector3f const& vel_body, Scalar angular_velocity);

    /**
     * @brief Get the Cluster Map object
     *
     * @return ClusterMap const& cluster map
     */
    ClusterMap const& GetClusterMap()
    {
        return Base::cluster_map_;
    }

    // /**
    //  * @brief Set the Debug Info object
    //  *
    //  * @param debug_info json value
    //  */
    // void SetDebugInfo(Json::Value& debug_info);

private:
    /**
     * @brief each track predict current 3d state & box2d
     *
     * @param current_timestamp
     */
    void predict(Timestamp const& current_timestamp) override;

    /**
     * @brief data association
     *
     * @param measurement_map measurement map
     */
    void associate(MeasurementMap const& measurement_map) override;

    /**
     * @brief update
     *
     * @param cluster cluster
     */
    void update(ClusterPtr const cluster) override;

    /**
     * @brief Create a New Track object
     *
     * @param cluster cluster contains measurements only
     */
    void createNewTrack(ClusterPtr const cluster) override;

    /**
     * @brief remove invalid track
     *
     */
    void removeOldTrack() override;

    /**
     * @brief update last measurement map, its a trick
     *
     */
    void updateLastMeasurementMap();

    /**
     * @brief Get the Track List object
     *
     * @param track_list filtered track list
     */
    void getTrackList(std::list<TrackPtr>& track_list);

    /**
     * @brief Get the Measurement List object
     *
     * @param measurement_map measurement map
     * @param measurement_list filtered measurement list
     */
    void getMeasurementList(MeasurementMap const& measurement_map, std::list<MeasurementPtr>& measurement_list);

    /**
     * @brief fill cluster map using mst cluster result
     *
     * @param result result
     */
    void fillClusterMap(TightFusionMSTClusterAlgorithm::ClusterMap const& result);

    /**
     * @brief a utility to log point id -> track(measurement) map
     *
     * @param track_list track list
     * @param measurement_list measurement list
     */
    void logPointIdMap(std::list<TrackPtr> const& track_list, std::list<MeasurementPtr> const& measurement_list);

    /**
     * @brief append track filter rule
     *
     */
    void appendTrackFilterRule();

    /**
     * @brief append measurement filter rule
     *
     */
    void appendMeasurementFilterRule();

    /**
     * @brief append create track rule
     *
     */
    void appendCreateTrackRule();

    /**
     * @brief append initialize track rule
     *
     */
    void appendInitTrackRule();

    /**
     * @brief append remove track rule
     *
     */
    void appendRemoveTrackRule();

private:
    CameraGroupPtr                   camera_group_;
    Matrix4f                         body_transformation_;
    Vector3f                         vel_body_;
    Scalar                           angular_velocity_;
    TightFusionMSTClusterAlgorithm   cluster_algo_;
    uint32_t                         current_track_id_ = 0U;
    std::list<std::string>           debug_info_str_;
    std::list<TrackFilterRule>       track_filter_rule_list_;
    std::list<MeasurementFilterRule> measurement_filter_rule_list_;
    std::list<CreateTrackRule>       create_track_rule_list_;
    std::list<InitTrackRule>         init_track_rule_list_;
    std::list<RemoveTrackRule>       remove_track_rule_list_;
};

}  // namespace perception
}  // namespace holo

#endif
