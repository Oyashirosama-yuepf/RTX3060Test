/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_id_tracking_pipeline.hpp
 * @brief This header file defines ObstacleIdTrackingPipeline implementation.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-07-07"
 */

#ifndef HOLO_PERCEPTION_UTILS_OBSTACLE_ID_TRACKING_PIPELINE_HPP_
#define HOLO_PERCEPTION_UTILS_OBSTACLE_ID_TRACKING_PIPELINE_HPP_

#include <holo/perception/utils/obstacle_id_tracking_pipeline.h>

namespace holo
{
namespace perception
{
template <typename _Track>
ObstacleIdTrackingPipeline<_Track>::ObstacleIdTrackingPipeline() : cluster_id_(0U)
{
}

template <typename _Track>
void ObstacleIdTrackingPipeline<_Track>::associate(MeasurementMap const& measurement_map)
{
    cluster_id_ = 0U;
    Base::cluster_map_.clear();
    for (auto iter = measurement_map.begin(); iter != measurement_map.end(); ++iter)
    {
        auto key        = iter->first;
        auto track_iter = Base::track_map_.find(key);
        if (track_iter == Base::track_map_.end())
        {
            auto new_cluster                    = std::make_shared<Cluster>(++cluster_id_);
            new_cluster->measurement_map[key]   = iter->second;
            Base::cluster_map_[new_cluster->id] = new_cluster;
        }
        else
        {
            if (match(track_iter->second, iter->second))
            {
                auto new_cluster                    = std::make_shared<Cluster>(++cluster_id_);
                new_cluster->measurement_map[key]   = iter->second;
                new_cluster->track_map[key]         = track_iter->second;
                Base::cluster_map_[new_cluster->id] = new_cluster;
            }
            else
            {
                auto new_cluster                    = std::make_shared<Cluster>(++cluster_id_);
                new_cluster->measurement_map[key]   = iter->second;
                Base::cluster_map_[new_cluster->id] = new_cluster;
            }
        }
    }
}

template <typename _Track>
void ObstacleIdTrackingPipeline<_Track>::createNewTrack(ClusterPtr const cluster)
{
    if (cluster->measurement_map.size() > 0U)
    {
        auto iter             = cluster->measurement_map.begin();
        auto key              = iter->first;
        auto measurement      = iter->second;
        auto new_track        = std::make_shared<Track>(measurement);
        Base::track_map_[key] = new_track;
    }
}

template <typename _Track>
void ObstacleIdTrackingPipeline<_Track>::removeOldTrack()
{
    for (auto iter = Base::track_map_.begin(); iter != Base::track_map_.end();)
    {
        auto track = iter->second;

        if (track->GetLostCount() > 0U)
        {
            iter = Base::track_map_.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

template <typename _Track>
bool_t ObstacleIdTrackingPipeline<_Track>::match(TrackPtr const track, MeasurementPtr const measurement)
{
    (void)track;
    (void)measurement;
    return true;
}

}  // namespace perception
}  // namespace holo

#endif
