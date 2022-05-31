/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tracking_pipeline.h
 * @brief This header file defines tracking pipeline interface.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-25"
 */

#ifndef HOLO_PERCEPTION_FUSION_TRACKING_PIPELINE_H_
#define HOLO_PERCEPTION_FUSION_TRACKING_PIPELINE_H_

#include <unordered_map>

#include <holo/common/timestamp.h>

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
 * @brief tracking pipeline interface
 * @details define common tracking pipeline
 * @ref https://holomatic.feishu.cn/docs/doccnqgnRNY6w3KqnHtGn7VSNne#lVBw3f
 *
 * @tparam _TrackKey track key
 * @tparam _Track track
 * @tparam _Hash hash
 */
template <typename _TrackKey, typename _Track, typename _Hash>
class TrackingPipeline
{
public:
    using TrackKey       = _TrackKey;
    using Track          = _Track;
    using Hash           = _Hash;
    using TrackPtr       = std::shared_ptr<Track>;
    using TrackMap       = std::unordered_map<TrackKey, TrackPtr, Hash>;
    using Measurement    = typename Track::Measurement;
    using MeasurementPtr = typename Track::MeasurementPtr;
    using MeasurementMap = typename Track::MeasurementMap;
    using Timestamp      = holo::common::Timestamp;

    /**
     * @brief association result (alias cluster)
     *
     */
    struct Cluster
    {
        Cluster(uint32_t _id) : id(_id)
        {
        }
        uint32_t       id;
        MeasurementMap measurement_map;
        TrackMap       track_map;
    };
    using ClusterPtr = std::shared_ptr<Cluster>;
    using ClusterMap = std::unordered_map<uint32_t, ClusterPtr>;

public:
    /**
     * @brief update tracks state using new measurements
     *
     * @param measurement_map new measurements
     * @param current_timestamp current timestamp
     */
    virtual void Update(MeasurementMap const& measurement_map, Timestamp const& current_timestamp);

    /**
     * @brief Get the Track Map
     *
     * @return TrackMap const& track map
     */
    TrackMap const& GetTrackMap() const
    {
        return track_map_;
    }

protected:
    /**
     * @brief predict track state at current timestamp
     *
     * @param current_timestamp current timestamp
     */
    virtual void predict(Timestamp const& current_timestamp);

    /**
     * @brief associate tracks and measurements
     * @details association results should store in cluster_map_
     *
     * @param measurement_map measurements
     */
    virtual void associate(MeasurementMap const& measurement_map) = 0;

    /**
     * @brief maintain tracks
     * @details tracks store in track_map_
     *
     */
    virtual void maintainTracks();

    /**
     * @brief update the track using associated measurements
     *
     * @param cluster cluster contain associated tracks and measurements
     */
    virtual void update(ClusterPtr const cluster);

    /**
     * @brief create a new track from the cluster
     *
     * @param cluster cluster
     */
    virtual void createNewTrack(ClusterPtr const cluster) = 0;

    /**
     * @brief remove old tracks in track map
     *
     */
    virtual void removeOldTrack() = 0;

protected:
    Timestamp  current_timestamp_;  ///< current timestamp
    ClusterMap cluster_map_;        ///< container of association result
    TrackMap   track_map_;          ///< container of tracks
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
