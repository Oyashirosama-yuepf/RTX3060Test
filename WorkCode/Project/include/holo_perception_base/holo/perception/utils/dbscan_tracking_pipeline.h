/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dbscan_tracking_pipeline.h
 * @brief This header file defines tracking pipeline using a DBSCAN-like association algorithm.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-07-02"
 */

#ifndef HOLO_PERCEPTION_UTILS_DBSCAN_TRACKING_PIPELINE_
#define HOLO_PERCEPTION_UTILS_DBSCAN_TRACKING_PIPELINE_

#include <deque>
#include <list>

#include <holo/perception/fusion/tracking_pipeline.h>

namespace holo
{
namespace perception
{
/**
 * @brief A Tracking Pipeline interface using DBSCAN-like association algorithm
 *
 * @tparam _TrackKey track key
 * @tparam _Track track
 * @tparam _Hash hash
 */
template <typename _TrackKey, typename _Track, typename _Hash>
class DBSCANTrackingPipeline : public TrackingPipeline<_TrackKey, _Track, _Hash>
{
public:
    using Base           = TrackingPipeline<_TrackKey, _Track, _Hash>;
    using TrackPtr       = typename Base::TrackPtr;
    using MeasurementPtr = typename Base::Track::MeasurementPtr;
    using TrackMap       = typename Base::TrackMap;
    using MeasurementMap = typename Base::MeasurementMap;
    using Cluster        = typename Base::Cluster;
    using ClusterPtr     = typename Base::ClusterPtr;

    /**
     * @brief point of a track, used by clustering algorithm
     *
     */
    struct TrackPoint
    {
        /**
         * @brief Construct a new Track Point object
         *
         * @param _track track pointer
         */
        TrackPoint(TrackPtr const _track);
        uint32_t cluster_id;  ///< cluster id
        TrackPtr track;       ///< track pointer
    };
    using TrackPointPtr   = std::shared_ptr<TrackPoint>;
    using TrackPointDeque = std::deque<TrackPointPtr>;

    /**
     * @brief point of a measurement, used by clustering algorithm
     *
     */
    struct MeasurementPoint
    {
        /**
         * @brief Construct a new Measurement Point object
         *
         * @param _measurement measurement pointer
         */
        MeasurementPoint(MeasurementPtr const _measurement);
        uint32_t       cluster_id;   ///< cluster id
        MeasurementPtr measurement;  ///< measurement pointer
    };
    using MeasurementPointPtr   = std::shared_ptr<MeasurementPoint>;
    using MeasurementPointDeque = std::deque<MeasurementPointPtr>;

protected:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // derived methods

    /**
     * @brief associate tracks and measurement using a DBSCAN-like scheme
     *
     * @param measurement_map measurements
     */
    void associate(MeasurementMap const& measurement_map) override;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // native methods

    /**
     * @brief collect track points and measurment points
     *
     * @param measurement_map measurements
     */
    void collectPoints(MeasurementMap const& measurement_map);

    /**
     * @brief find all other points in the cluster contains input_points
     * @details using non-recursive implementation
     *
     * @param track_point seed track point, ignore nullptr
     * @param measurement_point seed measurement point, ignore nullptr
     * @param cluster cluster
     */
    void expand(TrackPointPtr const track_point, MeasurementPointPtr const measurement_point, ClusterPtr cluster);

    /**
     * @brief expand a track point
     *
     * @param query_point the query track point (eg. we need find its neighbors)
     * @param track_point_deque track point deque, contains point to expand
     * @param measurement_point_deque measurement point deque, contains point to expand
     * @param cluster cluster
     */
    void expandTrackPoint(TrackPointPtr const query_point, TrackPointDeque& track_point_deque,
                          MeasurementPointDeque& measurement_point_deque, ClusterPtr cluster);

    /**
     * @brief expand a measurement point
     *
     * @param query_point the query measurement point (eg. we need find its neighbors)
     * @param track_point_deque track point deque, contains point to expand
     * @param measurement_point_deque measurement point deque, contains point to expand
     * @param cluster cluster
     */
    void expandMeasurementPoint(MeasurementPointPtr const query_point, TrackPointDeque& track_point_deque,
                                MeasurementPointDeque& measurement_point_deque, ClusterPtr cluster);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // virtual methods

    /**
     * @brief add track to cluster
     *
     * @param track the track
     * @param cluster the cluster
     */
    virtual void addTrackToCluster(TrackPtr const track, ClusterPtr cluster) = 0;

    /**
     * @brief add measurement to cluster
     *
     * @param measurement the measurement
     * @param cluster the cluster
     */
    virtual void addMeasurementToCluster(MeasurementPtr const measurement, ClusterPtr cluster) = 0;

    /**
     * @brief determine whether the track point can create a new cluster
     *
     * @param track_point track point
     * @return bool_t ture if it can create a new cluster else false
     */
    virtual bool_t canCreateCluster(TrackPointPtr const track_point) = 0;

    /**
     * @brief determine whether the measurement point can create a new cluster
     *
     * @param measurement_point measurement point
     * @return bool_t true if it can create a new cluster else false
     */
    virtual bool_t canCreateCluster(MeasurementPointPtr const measurement_point) = 0;

    /**
     * @brief determine whethter the track point can expand
     *
     * @param track_point track point
     * @return bool_t true if it can expand else false
     */
    virtual bool_t canExpand(TrackPointPtr const track_point) = 0;

    /**
     * @brief determine whether the measurement point can expand
     *
     * @param measurement_point measurement point
     * @return bool_t true if it can expand else false
     */
    virtual bool_t canExpand(MeasurementPointPtr const measurement_point) = 0;

    /**
     * @brief determine whether lhs and rhs are matched (they belongs to the same cluster)
     *
     * @param lhs a track
     * @param rhs another track
     * @return bool_t true if they match else false
     */
    virtual bool_t match(TrackPtr const lhs, TrackPtr const rhs) = 0;

    /**
     * @brief determine whether lhs and rhs are matched (they belongs to the same cluster)
     *
     * @param lhs a track
     * @param rhs a measurement
     * @return bool_t true if they match else false
     */
    virtual bool_t match(TrackPtr const lhs, MeasurementPtr const rhs) = 0;

    /**
     * @brief determine whether lhs and rhs are matched (they belongs to the same cluster)
     *
     * @param lhs a measurement
     * @param rhs a track
     * @return bool_t true if they match else false
     */
    virtual bool_t match(MeasurementPtr const lhs, TrackPtr const rhs) = 0;

    /**
     * @brief determine whether lhs and rhs are matched (they belongs to the same cluster)
     *
     * @param lhs a measurement
     * @param rhs another measurement
     * @return bool_t true if they match else false
     */
    virtual bool_t match(MeasurementPtr const lhs, MeasurementPtr const rhs) = 0;

protected:
    uint32_t                       cluster_id_;
    std::list<MeasurementPointPtr> measurement_point_list_;
    std::list<TrackPointPtr>       track_point_list_;
};

}  // namespace perception
}  // namespace holo

#endif
