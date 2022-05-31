/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_obstacle_id_tracker.h
 * @brief This header file defines obstacle id tracker.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-22"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_OBSTACLE_ID_TRACKER_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_OBSTACLE_ID_TRACKER_H_

#include <holo/perception/obstacle_fusion/tight_fusion_uss_id_tracker.h>
#include <holo/perception/obstacle_fusion/tight_fusion_uss_obstacle_track.h>
#include <holo/perception/obstacle_fusion/tight_fusion_vision_obstacle_track.h>

#include <holo/perception/utils/impl/camera_group.hpp>
#include <holo/perception/utils/impl/obstacle_id_tracking_pipeline.hpp>

namespace holo
{
namespace perception
{
/**
 * @brief obstacle id tracker
 *
 * @tparam _Track track type
 */
template <typename _Track>
class TightFusionObstacleIdTracker : public ObstacleIdTrackingPipeline<_Track>
{
public:
    using Base           = ObstacleIdTrackingPipeline<_Track>;
    using Base2          = typename Base::Base;
    using ClusterPtr     = typename Base::ClusterPtr;
    using Track          = typename Base::Track;
    using CameraGroupPtr = std::shared_ptr<CameraGroup>;

    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group pointer
     */
    void SetCameraGroup(CameraGroupPtr const camera_group)
    {
        camera_group_ = camera_group;
    }

private:
    /**
     * @brief Create a New Track object
     *
     * @param cluster cluster
     */
    void createNewTrack(ClusterPtr const cluster) override
    {
        if (cluster->measurement_map.size() > 0U)
        {
            auto iter        = cluster->measurement_map.begin();
            auto key         = iter->first;
            auto measurement = iter->second;
            auto new_track   = std::make_shared<Track>(measurement);
            new_track->SetCameraGroup(camera_group_);
            new_track->ProjectToCamera();
            Base2::track_map_[key] = new_track;
        }
    }

private:
    CameraGroupPtr camera_group_;
};

using TightFusionVisionObstacleIdTracker = TightFusionObstacleIdTracker<TightFusionVisionObstacleTrack>;

}  // namespace perception
}  // namespace holo

#endif