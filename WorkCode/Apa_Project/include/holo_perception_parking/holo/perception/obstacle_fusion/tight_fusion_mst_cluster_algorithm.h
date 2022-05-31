/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tight_fusion_mst_cluster_algorithm.h
 * @brief This header file defines mst cluster constaints and distance.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_MST_CLUSTER_ALGORITHM_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_TIGHT_FUSION_MST_CLUSTER_ALGORITHM_H_

#include <holo/perception/obstacle_fusion/tight_fusion_extended_kalman_filter.h>
#include <holo/perception/obstacle_fusion/tight_fusion_parameter.h>
#include <holo/perception/obstacle_fusion/tight_fusion_uss_obstacle_track.h>
#include <holo/perception/obstacle_fusion/tight_fusion_vision_obstacle_track.h>

#include <holo/perception/fusion/impl/minimum_spanning_tree_cluster_algorithm.hpp>
#include <holo/perception/utils/impl/camera_group.hpp>

namespace holo
{
namespace perception
{
/**
 * @brief mst clustering algorithm
 *
 */
class TightFusionMSTClusterAlgorithm
  : public MinimumSpanningTreeClusterAlgorithm<TightFusionExtendedKalmanFilter, TrackBase>
{
public:
    using Base               = MinimumSpanningTreeClusterAlgorithm<TightFusionExtendedKalmanFilter, TrackBase>;
    using Scalar             = float32_t;
    using Scalar4            = std::array<Scalar, 4U>;
    using CameraGroupPtr     = std::shared_ptr<CameraGroup>;
    using TrackPtr           = Base::TrackPtr;
    using MeasurementPtr     = Base::MeasurementPtr;
    using Box2dMap           = std::unordered_map<uint32_t, std::array<Scalar, 4U>>;
    using PointPointRule     = std::function<bool_t(Point const&, Point const&)>;
    using PointClusterRule   = std::function<bool_t(Point const&, Cluster const&)>;
    using ClusterClusterRule = std::function<bool_t(Cluster const&, Cluster const&)>;

public:
    /**
     * @brief Set the Camera Group object
     *
     * @param camera_group camera group pointer
     */
    void SetCameraGroup(CameraGroupPtr const camera_group);

    /**
     * @brief compute pipeline
     *
     * @param current_timestamp current timestamp
     * @param track_list track list
     * @param measurement_list measurement list
     * @param cluster_map cluster map
     */
    void Compute(common::Timestamp const& current_timestamp, std::list<TrackPtr> const& track_list,
                 std::list<MeasurementPtr> const& measurement_list, ClusterMap& cluster_map);

public:
    /**
     * @brief cluster history
     *
     */
    struct ClusterHistory
    {
        /**
         * @brief Construct a new Cluster History object
         *
         */
        ClusterHistory();

        /**
         * @brief Construct a new Cluster History object
         *
         * @param current_timestamp current timestamp
         * @param cluster cluster
         */
        ClusterHistory(common::Timestamp const& current_timestamp, Cluster cluster);

        /**
         * @brief if the cluster is empty
         *
         * @return bool_t true if it is empty
         */
        bool_t IsEmpty()
        {
            return history.size() == 0U;
        }

        common::Timestamp  timestamp;
        std::list<Cluster> history;
    };

    /**
     * @brief sensor measurement key -> cluster history
     *
     */
    class ClusterHistoryMap
    {
    public:
        /**
         * @brief update the map
         *
         * @param cluster_map current cluster map
         * @param current_timestamp current timestamp
         */
        void Update(ClusterMap const& cluster_map, common::Timestamp const& current_timestamp);

        /**
         * @brief get cluster history
         *
         * @param key sensor measurement key
         * @return ClusterHistory& cluster history
         */
        ClusterHistory& Get(SensorMeasurementKey const& key);

    private:
        ClusterHistory                                                                     empty_history_;
        std::unordered_map<SensorMeasurementKey, ClusterHistory, SensorMeasurementKeyHash> cluster_history_map_;
    };

    /**
     * @brief association constraints
     *
     */
    struct Constraints : public Base::Constraints
    {
        /**
         * @brief Get the Debug Info object
         *
         * @param lhs point
         * @param rhs point
         * @return std::string debug info string
         */
        std::string GetDebugInfo(Point const& lhs, Point const& rhs) const;

        /**
         * @brief Set the Camera Group object
         *
         * @param camera_group camera group pointer
         */
        void SetCameraGroup(CameraGroupPtr const camera_group);

        /**
         * @brief Append rules
         *
         */
        void AppendRules()
        {
            appendPointPointInlierRules();
            appendPointPointOutlierRules();
            appendPointClusterInlierRules();
            appendPointClusterOutlierRules();
            appendClusterClusterInlierRules();
            appendClusterClusterOutlierRules();
        }

        /**
         * @brief Set the Cluster History Map object
         *
         * @param cluster_history_map cluster history map
         */
        void SetClusterHistoryMap(std::shared_ptr<ClusterHistoryMap> cluster_history_map)
        {
            cluster_history_map_ = cluster_history_map;
        }

        /**
         * @brief determine weather two points can match
         *
         * @param lhs point
         * @param rhs point
         * @return bool_t true if they can match
         */
        bool_t operator()(Point const& lhs, Point const& rhs) const override;

        /**
         * @brief determine if the point can join the cluster
         *
         * @param lhs point
         * @param rhs cluster
         * @return bool_t true if point can joint cluster
         */
        bool_t operator()(Point const& lhs, Cluster const& rhs) const override;

        /**
         * @brief determine if two clusters can merge
         *
         * @param lhs cluster
         * @param rhs cluster
         * @return bool_t true if they can merge
         */
        bool_t operator()(Cluster const& lhs, Cluster const& rhs) const override;

        /**
         * @brief determine if the iou of two box is big enough
         *
         * @param dist iou
         * @return bool_t true if it is big enough
         */
        bool_t operator()(Scalar dist) const override;

        /**
         * @brief Get the Box2d Map From Point object
         *
         * @param point point
         * @return Box2dMap camera sensor id -> box2d map
         */
        static Box2dMap GetBox2dMapFromPoint(Base::Point const& point);

    private:
        /**
         * @brief append point to point inlier rules
         *
         */
        void appendPointPointInlierRules();

        /**
         * @brief append point to point outlier rules
         *
         */
        void appendPointPointOutlierRules();

        /**
         * @brief append point to cluster inlier rules
         *
         */
        void appendPointClusterInlierRules();

        /**
         * @brief append point to cluster outlier rules
         *
         */
        void appendPointClusterOutlierRules();

        /**
         * @brief append cluster to cluster inlier rules
         *
         */
        void appendClusterClusterInlierRules();

        /**
         * @brief append cluster to cluster outlier rules
         *
         */
        void appendClusterClusterOutlierRules();

        /**
         * @brief determine if two box2d map are compatible (iou > 0)
         *
         * @param lhs_box2d_map box2d map
         * @param rhs_box2d_map box2d map
         * @param need_same_image need project to same image
         * @return bool_t true is they are compatible
         */
        bool_t isBox2dCompatible(Box2dMap const& lhs_box2d_map, Box2dMap const& rhs_box2d_map,
                                 bool_t need_same_image = false) const;

    private:
        CameraGroupPtr                   camera_group_;
        bool_t                           is_pp_constrain_flag_ = true;
        std::weak_ptr<ClusterHistoryMap> cluster_history_map_;
        std::list<PointPointRule>        pp_inlier_rule_list_;
        std::list<PointPointRule>        pp_outlier_rule_list_;
        std::list<PointClusterRule>      pc_inlier_rule_list_;
        std::list<PointClusterRule>      pc_outlier_rule_list_;
        std::list<ClusterClusterRule>    cc_inlier_rule_list_;
        std::list<ClusterClusterRule>    cc_outlier_rule_list_;
    };

    /**
     * @brief distance function
     *
     */
    struct Distance : public Base::Distance
    {
        using Box2f   = geometry::Box2f;
        using Pose2f  = geometry::Pose2f;
        using Point2f = geometry::Point2f;
        using Rot2f   = geometry::Rot2f;

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
         * @brief distance of two point
         *
         * @param lhs point
         * @param rhs point
         * @return Scalar distance
         */
        Scalar operator()(Point const& lhs, Point const& rhs) const override;

        /**
         * @brief compute iou
         *
         * @param lhs scalar4
         * @param rhs scalar4
         * @return Scalar iou
         */
        static Scalar ComputeIOU(Scalar4 const& lhs, Scalar4 const& rhs);

        /**
         * @brief compute dilated iou
         *
         * @param lhs box2 [left, top, right, bottom]
         * @param rhs box2
         * @param dilation_factor_u dilation factor of box2 width
         * @param dilation_factor_v dilation factor of box2 height
         * @return Scalar iou
         */
        static Scalar ComputeDilatedIOU(Scalar4 const& lhs, Scalar4 const& rhs, Scalar dilation_factor_u = 1.0f,
                                        Scalar dilation_factor_v = 1.0f);

    private:
        /**
         * @brief compute position and velocity similarity
         *
         * @param lhs obstacle property
         * @param rhs obstacle property
         * @return Scalar similarity
         */
        Scalar computeSimilarity(ObstacleProperty<Scalar> const& lhs, ObstacleProperty<Scalar> const& rhs) const;

        /**
         * @brief Get the Obstacle Property From Point object
         *
         * @param point point
         * @return ObstacleProperty<Scalar> obstacle property
         */
        ObstacleProperty<Scalar> getObstaclePropertyFromPoint(Base::Point const& point) const;

        /**
         * @brief utility to print distance of pints
         *
         * @param ret distance
         * @param lhs point
         * @param rhs point
         */
        void printDistance(Scalar ret, Point const& lhs, Point const& rhs) const;

    private:
        CameraGroupPtr camera_group_;
    };

private:
    TightFusionMSTClusterAlgorithm::Constraints constraints_;
    TightFusionMSTClusterAlgorithm::Distance    distance_;
    std::shared_ptr<ClusterHistoryMap>          cluster_history_map_;
};

}  // namespace perception
}  // namespace holo

#endif
