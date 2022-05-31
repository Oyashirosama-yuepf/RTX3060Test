/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file minimum_spanning_tree_cluster_algorithm.hpp
 * @brief This header file defines implementation of mst clustering.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-09"
 */

#ifndef HOLO_PERCEPTION_FUSION_MINIMUM_SPANNING_TREE_CLUSTER_ALGORITHM_HPP_
#define HOLO_PERCEPTION_FUSION_MINIMUM_SPANNING_TREE_CLUSTER_ALGORITHM_HPP_

#include <holo/perception/fusion/minimum_spanning_tree_cluster_algorithm.h>

namespace holo
{
namespace perception
{
template <typename TrackType, typename MeasurementType>
MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Point::Point(uint32_t i, TrackPtr t)
  : id(i), track(t), measurement(nullptr)
{
}

template <typename TrackType, typename MeasurementType>
MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Point::Point(uint32_t i, MeasurementPtr m)
  : id(i), track(nullptr), measurement(m)
{
}

template <typename TrackType, typename MeasurementType>
bool_t MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Constraints::operator()(Point const& lhs,
                                                                                                Point const& rhs) const
{
    (void)lhs;
    (void)rhs;
    return true;
}

template <typename TrackType, typename MeasurementType>
bool_t MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Constraints::operator()(
    Point const& lhs, Cluster const& rhs) const
{
    (void)lhs;
    (void)rhs;
    return true;
}

template <typename TrackType, typename MeasurementType>
bool_t MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Constraints::operator()(
    Cluster const& lhs, Cluster const& rhs) const
{
    (void)lhs;
    (void)rhs;
    return true;
}

template <typename TrackType, typename MeasurementType>
bool_t MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Constraints::operator()(Scalar dist) const
{
    (void)dist;
    return true;
}

template <typename TrackType, typename MeasurementType>
typename MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Scalar
MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Distance::operator()(Point const& lhs,
                                                                                      Point const& rhs) const
{
    (void)lhs;
    (void)rhs;
    return Scalar();
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::Compute(
    std::list<TrackPtr> const& track_list, std::list<MeasurementPtr> const& measurement_list,
    Constraints const& constraints, Distance const& distance, ClusterMap& cluster_map, bool_t revserse)
{
    // 0. clear debug info
    debug_info_str_.clear();
    // 1. collect data point
    std::vector<Point> point_list;
    collectPointList(track_list, measurement_list, point_list);
    // 2. compute distance
    std::list<EdgeType> edge_list;
    computeDistance(point_list, constraints, distance, edge_list);
    // 3. sort by distance
    if (revserse)
    {
        edge_list.sort([](EdgeType const& lhs, EdgeType const& rhs) { return std::get<2>(lhs) > std::get<2>(rhs); });
    }
    else
    {
        edge_list.sort([](EdgeType const& lhs, EdgeType const& rhs) { return std::get<2>(lhs) < std::get<2>(rhs); });
    }
    // 4. generate cluster
    generateClusterMap(point_list, edge_list, constraints, cluster_map);
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::collectPointList(
    std::list<TrackPtr> const& track_list, std::list<MeasurementPtr> const& measurement_list,
    std::vector<Point>& point_list)
{
    point_list.reserve(track_list.size() + measurement_list.size());
    uint32_t id = 0U;
    for (auto t : track_list)
    {
        point_list.push_back(Point(id++, t));
    }
    for (auto m : measurement_list)
    {
        point_list.push_back(Point(id++, m));
    }
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::computeDistance(
    std::vector<Point> const& point_list, Constraints const& constraints, Distance const& distance,
    std::list<EdgeType>& edge_list)
{
    for (size_t i = 0U; i < point_list.size(); ++i)
    {
        for (size_t j = i + 1U; j < point_list.size(); ++j)
        {
            auto const& pi = point_list[i];
            auto const& pj = point_list[j];
            if (constraints(pi, pj))
            {
                edge_list.push_back(EdgeType(i, j, distance(pi, pj)));
            }
        }
    }
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::mergeCluster(
    uint32_t i, uint32_t j, ClusterMap& cluster_map, std::unordered_map<uint32_t, uint32_t>& id2cluster)
{
    auto iter_i = cluster_map.find(i);
    auto iter_j = cluster_map.find(j);
    if (cluster_map.end() != iter_i && cluster_map.end() != iter_j)
    {
        for (auto const& p : iter_j->second)
        {
            iter_i->second.push_back(p);
            id2cluster[p.id] = i;
        }
        cluster_map.erase(iter_j);
    }
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::createNewCluster(
    std::vector<Point> const& point_list, uint32_t i, uint32_t j, uint32_t& cluster_id,
    std::unordered_map<uint32_t, uint32_t>& id2cluster, ClusterMap& cluster_map)
{
    ++cluster_id;
    id2cluster[i]           = cluster_id;
    id2cluster[j]           = cluster_id;
    auto new_cluster        = {point_list[i], point_list[j]};
    cluster_map[cluster_id] = new_cluster;
    std::stringstream ss;
    ss << i << " & " << j << " create new cluster: " << getClusterStr(cluster_map);
    debug_info_str_.push_back(ss.str());
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::createNewCluster(
    std::vector<Point> const& point_list, uint32_t i, uint32_t& cluster_id,
    std::unordered_map<uint32_t, uint32_t>& id2cluster, ClusterMap& cluster_map)
{
    ++cluster_id;
    id2cluster[i]           = cluster_id;
    auto new_cluster        = {point_list[i]};
    cluster_map[cluster_id] = new_cluster;
    std::stringstream ss;
    ss << i << " create new cluster: " << getClusterStr(cluster_map);
    debug_info_str_.push_back(ss.str());
}

template <typename TrackType, typename MeasurementType>
void MinimumSpanningTreeClusterAlgorithm<TrackType, MeasurementType>::generateClusterMap(
    std::vector<Point> const& point_list, std::list<EdgeType> const& edge_list, Constraints const& constraints,
    ClusterMap& cluster_map)
{
    std::unordered_map<uint32_t, uint32_t> id2cluster;
    uint32_t                               cluster_id = 0U;
    for (auto const& e : edge_list)
    {
        if (constraints(std::get<2>(e)))  // distance satisfy constraints, eg. iou > thresh
        {
            auto        i      = std::get<0>(e);
            auto        j      = std::get<1>(e);
            auto const& pi     = point_list[i];
            auto const& pj     = point_list[j];
            auto        iter_i = id2cluster.find(i);
            auto        iter_j = id2cluster.find(j);
            if (id2cluster.end() == iter_i)
            {
                if (id2cluster.end() == iter_j)  // create a new cluster
                {
                    createNewCluster(point_list, i, j, cluster_id, id2cluster, cluster_map);
                }
                else
                {
                    if (constraints(pi, cluster_map[iter_j->second]))  // add pi to pj's cluster
                    {
                        id2cluster[i] = iter_j->second;
                        cluster_map[iter_j->second].push_back(pi);
                        std::stringstream ss;
                        ss << "add " << i << " to " << j << "'s cluster: " << getClusterStr(cluster_map);
                        debug_info_str_.push_back(ss.str());
                    }
                    else  // create new cluster contains pi
                    {
                        createNewCluster(point_list, i, cluster_id, id2cluster, cluster_map);
                    }
                }
            }
            else
            {
                if (id2cluster.end() == iter_j)
                {
                    if (constraints(pj, cluster_map[iter_i->second]))  // add pj to pi's cluster
                    {
                        id2cluster[j] = iter_i->second;
                        cluster_map[iter_i->second].push_back(pj);
                        std::stringstream ss;
                        ss << "add " << j << " to " << i << "'s cluster: " << getClusterStr(cluster_map);
                        debug_info_str_.push_back(ss.str());
                    }
                    else  // create new cluster contains pj
                    {
                        createNewCluster(point_list, j, cluster_id, id2cluster, cluster_map);
                    }
                }
                else
                {
                    if (iter_i->second != iter_j->second &&
                        constraints(cluster_map[iter_i->second], cluster_map[iter_j->second]))
                    {
                        // merge pi & pj's cluster
                        mergeCluster(iter_i->second, iter_j->second, cluster_map, id2cluster);
                        std::stringstream ss;
                        ss << "merge " << i << " & " << j << " : " << getClusterStr(cluster_map);
                        debug_info_str_.push_back(ss.str());
                    }
                    // else pi & pj are in the same cluster, do nothing
                    // or the two clusters are not compatible, do nothing
                }
            }
        }
    }
    // generate cluster for single point
    for (uint32_t i = 0U; i < point_list.size(); ++i)
    {
        if (id2cluster.end() == id2cluster.find(i))
        {
            createNewCluster(point_list, i, cluster_id, id2cluster, cluster_map);
        }
    }
}

}  // namespace perception
}  // namespace holo

#endif
