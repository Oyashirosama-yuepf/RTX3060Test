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
#ifndef HOLO_PERCEPTION_TIGHT_FUSION_USS_OBSTACLE_ID_TRACKER_H_
#define HOLO_PERCEPTION_TIGHT_FUSION_USS_OBSTACLE_ID_TRACKER_H_

#include <holo/numerics/vector.h>
#include <holo/perception/obstacle_fusion/tight_fusion_uss_obstacle_track.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

#include <holo/perception/fusion/impl/tracking_pipeline.hpp>
#include <holo/perception/utils/impl/camera_group.hpp>

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

class TightFusionUssObstacleTracker
  : public TrackingPipeline<uint32_t, TightFusionUssObstacleTrack, std::hash<uint32_t>>
{
public:
    using Scalar         = float32_t;
    using Vector3f       = holo::numerics::Vector3f;
    using String         = std::string;
    using Vector         = std::vector<Scalar>;
    using Map            = std::unordered_map<String, Vector>;
    using Base           = TrackingPipeline<uint32_t, TightFusionUssObstacleTrack, std::hash<uint32_t>>;
    using MeasurementMap = Base::MeasurementMap;
    using Cluster        = Base::Cluster;
    using ClusterPtr     = Base::ClusterPtr;
    using Track          = Base::Track;
    using TrackPtr       = Base::TrackPtr;
    using Measurement    = Base::Measurement;
    using MeasurementPtr = Track::MeasurementPtr;
    using PropertyType   = ObstacleProperty<Scalar>;
    using CameraGroupPtr = std::shared_ptr<CameraGroup>;

    /**
     * @brief uss tracker constructor
     */
    TightFusionUssObstacleTracker()
    {
        track_id_     = 0U;
        max_track_id_ = 100000000U;

        try
        {
            holo::yaml::Node node = holo::yaml::LoadFile(GetConfigFileAbsolutePath(
                "holo_perception_parking/lib_config/obstacle_fusion/parking_obstacle_fusion.yaml"));

            matching_dist_thres_      = node["uss_track_matching_dist_thres"].as<Scalar>();
            removal_lost_count_thres_ = node["uss_track_lost_count_thres"].as<holo::uint32_t>();

            track_params["FOAW"] = node["uss_track_foaw_params"].as<Vector>();
            track_params["MS"]   = node["uss_track_motion_status_params"].as<std::vector<float32_t>>();
            track_params["KF"]   = node["uss_track_kalman_filter_Q_params"].as<Vector>();
        }
        catch (std::exception& e)
        {
            LOG(ERROR) << e.what() << " @ FUSION YAML.";
            throw;
        }
    }

    /**
     * @brief update tracks state using new measurements
     *
     * @param current_timestamp current timestamp
     * @param vel_body ego car's velocity mass
     * @param angular_velocity ego car's angular velocity
     * @param measurement_map new uss measurements
     */
    void Update(Timestamp const& timestamp, Vector3f const& vel_body, Scalar const& angular_velocity,
                MeasurementMap const& measurement_map)
    {
        vel_body_         = vel_body;
        angular_velocity_ = angular_velocity;

        Base::Update(measurement_map, timestamp);
    }

    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group pointer
     */
    void SetCameraGroup(CameraGroupPtr const camera_group)
    {
        camera_group_ = camera_group;
    }

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
    void associate(MeasurementMap const& measurement_map)
    {
        uint32_t cluster_id = 0U;
        Base::cluster_map_.clear();

        for (auto p : Base::track_map_)
        {
            auto track                                     = p.second;
            auto new_cluster                               = std::make_shared<Cluster>(cluster_id++);
            new_cluster->track_map[track->GetObstacleId()] = track;
            cluster_map_[new_cluster->id]                  = new_cluster;
        }

        for (auto pm : measurement_map)
        {
            auto measure = pm.second;

            ClusterPtr matched_cluster = nullptr;
            Scalar     match_distance  = 20.0f;

            for (auto pc : cluster_map_)
            {
                auto cluster = pc.second;

                auto props = computeMeanClusterProperty(cluster);

                auto dx = props.x - measure->GetPosition().GetX();
                auto dy = props.y - measure->GetPosition().GetY();

                Scalar diff = std::sqrt(pow(dx, 2.0) + pow(dy, 2.0));

                if (diff < matching_dist_thres_ && diff < match_distance)
                {
                    match_distance  = diff;
                    matched_cluster = cluster;
                }
            }

            if (nullptr == matched_cluster)
            {
                auto                                        new_cluster = std::make_shared<Cluster>(cluster_id++);
                std::pair<holo::common::SensorId, uint32_t> key(measure->GetSensorId(), measure->GetObstacleId());
                new_cluster->measurement_map[key] = measure;
                cluster_map_[new_cluster->id]     = new_cluster;
            }
            else
            {
                std::pair<holo::common::SensorId, uint32_t> key(measure->GetSensorId(), measure->GetObstacleId());
                matched_cluster->measurement_map[key] = measure;
            }
        }
    }

    /**
     * @brief create a new track from a cluster
     *
     * @param cluster cluster
     */
    void createNewTrack(ClusterPtr const cluster)
    {
        if (cluster->measurement_map.size() > 0U)
        {
            track_id_        = (track_id_ + 1U) % max_track_id_;
            auto iter        = cluster->measurement_map.begin();
            auto key         = iter->first;
            auto measurement = iter->second;
            auto new_track   = std::make_shared<TightFusionUssObstacleTrack>(measurement, 15U);
            new_track->SetCameraGroup(camera_group_);
            new_track->ProjectToCamera();
            Base::track_map_[track_id_] = new_track;

            LOG(ERROR) << "create c: " << cluster->id << " -> t: " << new_track->GetObstacleId();
        }
    }

    /**
     * @brief remove old tracks in track map
     */
    void removeOldTrack()
    {
        for (auto iter = Base::track_map_.begin(); iter != Base::track_map_.end();)
        {
            auto track = iter->second;
            if (track->GetLostCount() > removal_lost_count_thres_)
            {
                iter = Base::track_map_.erase(iter);

                LOG(ERROR) << "remove t: " << track->GetObstacleId();
            }
            else
            {
                ++iter;
            }
        }
    }

    /**
     * @brief remove old tracks in track map
     *
     * @param cluster pointer to a cluster
     */
    PropertyType computeMeanClusterProperty(ClusterPtr const cluster)
    {
        PropertyType ret;
        Scalar       cnt = 0.0f;
        for (auto p : cluster->track_map)
        {
            auto track = p.second;
            ret.x += track->GetObstacleProperty().x;
            ret.y += track->GetObstacleProperty().y;
            cnt += 1.0f;
        }

        for (auto p : cluster->measurement_map)
        {
            auto measure = p.second;
            ret.x += measure->GetPosition().GetX();
            ret.y += measure->GetPosition().GetY();
            cnt += 1.0f;
        }

        if (cnt > 0.0f)
        {
            ret.x /= cnt;
            ret.y /= cnt;
        }

        return ret;
    }

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

    CameraGroupPtr camera_group_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif