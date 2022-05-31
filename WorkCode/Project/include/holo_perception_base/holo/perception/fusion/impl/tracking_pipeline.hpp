/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tracking_pipeline.hpp
 * @brief This header file defines tracking pipeline implementation.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-25"
 */

#ifndef HOLO_PERCEPTION_FUSION_IMPL_TRACKING_PIPELINE_HPP_
#define HOLO_PERCEPTION_FUSION_IMPL_TRACKING_PIPELINE_HPP_

#include <holo/perception/fusion/tracking_pipeline.h>

namespace holo
{
namespace perception
{
template <typename _TrackKey, typename _Track, typename _Hash>
void TrackingPipeline<_TrackKey, _Track, _Hash>::Update(MeasurementMap const& measurement_map,
                                                        Timestamp const&      current_timestamp)
{
    current_timestamp_ = current_timestamp;
    predict(current_timestamp);
    associate(measurement_map);
    maintainTracks();
}

template <typename _TrackKey, typename _Track, typename _Hash>
void TrackingPipeline<_TrackKey, _Track, _Hash>::predict(Timestamp const& current_timestamp)
{
    for (auto iter = track_map_.begin(); iter != track_map_.end(); ++iter)
    {
        iter->second->Predict(current_timestamp);
    }
}

template <typename _TrackKey, typename _Track, typename _Hash>
void TrackingPipeline<_TrackKey, _Track, _Hash>::maintainTracks()
{
    for (auto iter = cluster_map_.begin(); iter != cluster_map_.end(); ++iter)
    {
        auto cluster = iter->second;
        if (cluster->measurement_map.size() > 0U)
        {
            if (cluster->track_map.size() > 0U)
            {
                update(cluster);
            }
            else
            {
                createNewTrack(cluster);
            }
        }
    }
    removeOldTrack();
}

template <typename _TrackKey, typename _Track, typename _Hash>
void TrackingPipeline<_TrackKey, _Track, _Hash>::update(ClusterPtr const cluster)
{
    auto& track_map = cluster->track_map;
    for (auto iter = track_map.begin(); iter != track_map.end(); ++iter)
    {
        iter->second->Update(cluster->measurement_map);
    }
}

}  // namespace perception
}  // namespace holo

#endif
