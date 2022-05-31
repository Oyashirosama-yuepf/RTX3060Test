/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file minimum_spanning_tree_cluster_algorithm.h
 * @brief This header file defines mst clustering algorithm.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-05"
 */

#ifndef HOLO_PERCEPTION_FUSION_MINIMUM_SPANNING_TREE_CLUSTER_ALGORITHM_H_
#define HOLO_PERCEPTION_FUSION_MINIMUM_SPANNING_TREE_CLUSTER_ALGORITHM_H_

#include <list>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <holo/core/types.h>

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
 * @brief MST clustering algorithm
 * @details TrackType and MeasurementType can NOT be SAME
 *
 * @tparam TrackType track type
 * @tparam MeasurementType measurement type
 */
template <typename _TrackType, typename _MeasurementType>
class MinimumSpanningTreeClusterAlgorithm
{
public:
    using Scalar         = float32_t;
    using TrackPtr       = std::shared_ptr<_TrackType>;
    using MeasurementPtr = std::shared_ptr<_MeasurementType>;
    using EdgeType       = std::tuple<uint32_t, uint32_t, Scalar>;

    /**
     * @brief point for clustering
     *
     */
    struct Point
    {
        /**
         * @brief Construct a new Point using track
         *
         * @param index index in point list
         * @param track track ptr
         */
        Point(uint32_t index, TrackPtr track);

        /**
         * @brief Construct a new Point using measurement
         *
         * @param index index in point list
         * @param measurement measurement ptr
         */
        Point(uint32_t index, MeasurementPtr measurement);

        uint32_t       id;
        TrackPtr       track;
        MeasurementPtr measurement;
    };
    using Cluster    = std::list<Point>;
    using ClusterMap = std::unordered_map<uint32_t, Cluster>;

    /**
     * @brief define constraints for clustering
     *
     */
    struct Constraints
    {
        /**
         * @brief point to point constraints
         * @details default is true
         *
         * @param lhs point
         * @param rhs point
         * @return bool_t true if they satisfy constraints else false
         */
        virtual bool_t operator()(Point const& lhs, Point const& rhs) const;

        /**
         * @brief point to cluster constraints
         * @details default is true
         *
         * @param lhs point
         * @param rhs cluster
         * @return bool_t true if they satisfy constraints else false
         */
        virtual bool_t operator()(Point const& lhs, Cluster const& rhs) const;

        /**
         * @brief cluster to cluster constraints
         * @details default is true
         *
         * @param lhs cluster
         * @param rhs cluster
         * @return bool_t true if they satisfy constraints else false
         */
        virtual bool_t operator()(Cluster const& lhs, Cluster const& rhs) const;

        /**
         * @brief distance constraints, eg. iou > thresh
         * @details default is true
         *
         * @param dist distance
         * @return bool_t true if constraints are satisfied
         */
        virtual bool_t operator()(Scalar dist) const;
    };

    /**
     * @brief define distance of points
     *
     */
    struct Distance
    {
        /**
         * @brief compute distance of points
         *
         * @param lhs point
         * @param rhs point
         * @return Scalar distance between points
         */
        virtual Scalar operator()(Point const& lhs, Point const& rhs) const;
    };

public:
    /**
     * @brief do clustering
     *
     * @param track_list track pointer list
     * @param measurement_list measurement pointer list
     * @param constraints constraints
     * @param distance distance
     * @param cluster_map cluster map
     * @param revserse true: distance sort in descent order, false: distance sort in ascent order
     */
    void Compute(std::list<TrackPtr> const& track_list, std::list<MeasurementPtr> const& measurement_list,
                 Constraints const& constraints, Distance const& distance, ClusterMap& cluster_map,
                 bool_t revserse = false);

    /**
     * @brief Get the Debug Info string list
     *
     * @return std::list<std::string> const& debug info string list
     */
    std::list<std::string> const& GetDebugInfoStr()
    {
        return debug_info_str_;
    }

private:
    /**
     * @brief collect points
     *
     * @param track_list track pointer list
     * @param measurement_list measurement pointer list
     * @param point_list point list
     */
    void collectPointList(std::list<TrackPtr> const& track_list, std::list<MeasurementPtr> const& measurement_list,
                          std::vector<Point>& point_list);

    /**
     * @brief compute distance for all valid edges
     *
     * @param point_list point list
     * @param constraints constraints
     * @param distance distance
     * @param edge_list edge list
     */
    void computeDistance(std::vector<Point> const& point_list, Constraints const& constraints, Distance const& distance,
                         std::list<EdgeType>& edge_list);

    /**
     * @brief merge cluster of cluster id i & j
     *
     * @param i cluster id
     * @param j cluster id
     * @param cluster_map cluster map
     * @param id2cluster point index to cluster id map
     */
    void mergeCluster(uint32_t i, uint32_t j, ClusterMap& cluster_map,
                      std::unordered_map<uint32_t, uint32_t>& id2cluster);

    /**
     * @brief Create a New Cluster with point i & j
     *
     * @param point_list point list
     * @param i point index i
     * @param j point index j
     * @param cluster_id cluster id
     * @param id2cluster point index to cluster id map
     * @param cluster_map cluster map
     */
    void createNewCluster(std::vector<Point> const& point_list, uint32_t i, uint32_t j, uint32_t& cluster_id,
                          std::unordered_map<uint32_t, uint32_t>& id2cluster, ClusterMap& cluster_map);

    /**
     * @brief Create a New Cluster object
     *
     * @param point_list point list
     * @param i point index
     * @param cluster_id cluster id
     * @param id2cluster point index to cluster id map
     * @param cluster_map cluster map
     */
    void createNewCluster(std::vector<Point> const& point_list, uint32_t i, uint32_t& cluster_id,
                          std::unordered_map<uint32_t, uint32_t>& id2cluster, ClusterMap& cluster_map);

    /**
     * @brief generate cluster map using edge list
     *
     * @param point_list point list
     * @param edge_list edge list
     * @param constraints constraints
     * @param cluster_map cluster map
     */
    void generateClusterMap(std::vector<Point> const& point_list, std::list<EdgeType> const& edge_list,
                            Constraints const& constraints, ClusterMap& cluster_map);

private:
    std::string getClusterStr(ClusterMap const& cluster_map)
    {
        std::stringstream ss;
        for (auto const& c : cluster_map)
        {
            ss << "{";
            for (auto const& p : c.second)
            {
                ss << p.id << " ";
            }
            ss << "}";
        }
        return ss.str();
    }

    std::list<std::string> debug_info_str_;
};
/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
