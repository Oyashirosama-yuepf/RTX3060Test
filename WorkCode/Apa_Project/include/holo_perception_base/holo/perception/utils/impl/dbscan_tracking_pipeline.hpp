/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dbscan_tracking_pipeline.hpp
 * @brief This header file defines DBSCANTrackingPipeline implementation.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-07-02"
 */

#ifndef HOLO_PERCEPTION_UTILS_DBSCAN_TRACKING_PIPELINE_HPP_
#define HOLO_PERCEPTION_UTILS_DBSCAN_TRACKING_PIPELINE_HPP_

#include <holo/perception/utils/dbscan_tracking_pipeline.h>

namespace holo
{
namespace perception
{
template <typename _TrackKey, typename _Track, typename _Hash>
DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::TrackPoint::TrackPoint(TrackPtr const _track)
  : cluster_id(0U), track(_track)
{
}

template <typename _TrackKey, typename _Track, typename _Hash>
DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::MeasurementPoint::MeasurementPoint(MeasurementPtr const _measurement)
  : cluster_id(0U), measurement(_measurement)
{
}

template <typename _TrackKey, typename _Track, typename _Hash>
void DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::associate(MeasurementMap const& measurement_map)
{
    // reset context
    cluster_id_ = 0U;
    Base::cluster_map_.clear();
    // collect track points and measurement points
    collectPoints(measurement_map);
    // associate and generate cluster map
    for (auto point : track_point_list_)
    {
        if (0U == point->cluster_id && canCreateCluster(point))
        {
            auto new_cluster  = std::make_shared<Cluster>(++cluster_id_);
            point->cluster_id = new_cluster->id;
            addTrackToCluster(point->track, new_cluster);
            expand(point, nullptr, new_cluster);
            Base::cluster_map_[cluster_id_] = new_cluster;
        }
    }
    for (auto point : measurement_point_list_)
    {
        if (0U == point->cluster_id && canCreateCluster(point))
        {
            auto new_cluster  = std::make_shared<Cluster>(++cluster_id_);
            point->cluster_id = new_cluster->id;
            addMeasurementToCluster(point->measurement, new_cluster);
            expand(nullptr, point, new_cluster);
            Base::cluster_map_[cluster_id_] = new_cluster;
        }
    }
}

template <typename _TrackKey, typename _Track, typename _Hash>
void DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::collectPoints(MeasurementMap const& measurement_map)
{
    // reset
    track_point_list_.clear();
    measurement_point_list_.clear();
    // collect track points from track map
    for (auto iter = Base::track_map_.begin(); iter != Base::track_map_.end(); ++iter)
    {
        track_point_list_.push_back(std::make_shared<TrackPoint>(iter->second));
    }
    // collect measurement points from measurement map
    for (auto iter = measurement_map.begin(); iter != measurement_map.end(); ++iter)
    {
        measurement_point_list_.push_back(std::make_shared<MeasurementPoint>(iter->second));
    }
}

template <typename _TrackKey, typename _Track, typename _Hash>
void DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::expand(TrackPointPtr const       track_point,
                                                              MeasurementPointPtr const measurement_point,
                                                              ClusterPtr                cluster)
{
    TrackPointDeque       track_point_deque;
    MeasurementPointDeque measurement_point_deque;
    if (nullptr != track_point)
    {
        track_point_deque.push_back(track_point);
    }
    if (nullptr != measurement_point)
    {
        measurement_point_deque.push_back(measurement_point);
    }

    while (track_point_deque.size() > 0U || measurement_point_deque.size() > 0U)
    {
        if (track_point_deque.size() > 0U)
        {
            auto query_point = track_point_deque.front();
            track_point_deque.pop_front();
            expandTrackPoint(query_point, track_point_deque, measurement_point_deque, cluster);
        }
        if (measurement_point_deque.size() > 0U)
        {
            auto query_point = measurement_point_deque.front();
            measurement_point_deque.pop_front();
            expandMeasurementPoint(query_point, track_point_deque, measurement_point_deque, cluster);
        }
    }
}

template <typename _TrackKey, typename _Track, typename _Hash>
void DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::expandTrackPoint(TrackPointPtr const    query_point,
                                                                        TrackPointDeque&       track_point_deque,
                                                                        MeasurementPointDeque& measurement_point_deque,
                                                                        ClusterPtr             cluster)
{
    for (auto point : track_point_list_)
    {
        if (0U == point->cluster_id && match(query_point->track, point->track))
        {
            point->cluster_id = query_point->cluster_id;
            addTrackToCluster(point->track, cluster);
            if (canExpand(point))
            {
                track_point_deque.push_back(point);
            }
        }
    }
    for (auto point : measurement_point_list_)
    {
        if (0U == point->cluster_id && match(query_point->track, point->measurement))
        {
            point->cluster_id = query_point->cluster_id;
            addMeasurementToCluster(point->measurement, cluster);
            if (canExpand(point))
            {
                measurement_point_deque.push_back(point);
            }
        }
    }
}

template <typename _TrackKey, typename _Track, typename _Hash>
void DBSCANTrackingPipeline<_TrackKey, _Track, _Hash>::expandMeasurementPoint(
    MeasurementPointPtr const query_point, TrackPointDeque& track_point_deque,
    MeasurementPointDeque& measurement_point_deque, ClusterPtr cluster)
{
    for (auto point : track_point_list_)
    {
        if (0U == point->cluster_id && match(query_point->measurement, point->track))
        {
            point->cluster_id = query_point->cluster_id;
            addTrackToCluster(point->track, cluster);
            if (canExpand(point))
            {
                track_point_deque.push_back(point);
            }
        }
    }
    for (auto point : measurement_point_list_)
    {
        if (0U == point->cluster_id && match(query_point->measurement, point->measurement))
        {
            point->cluster_id = query_point->cluster_id;
            addMeasurementToCluster(point->measurement, cluster);
            if (canExpand(point))
            {
                measurement_point_deque.push_back(point);
            }
        }
    }
}

}  // namespace perception
}  // namespace holo

#endif
