/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track_container.h
 * @brief This header file defines a base class of track container.
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-04"
 */

#ifndef HOLO_PERCEPTION_TRACKING_TRACK_CONTAINER_H_
#define HOLO_PERCEPTION_TRACKING_TRACK_CONTAINER_H_

#include <unordered_map>
#include <vector>

#include <holo/perception/tracking/track.h>
#include <holo/perception/tracking/impl/track.hpp>

namespace holo
{
namespace perception
{
/**
 * @addtogroup tracking
 *
 * @{
 */

/**
 * @brief This class defines a base class of track container to manage tracks.
 *
 * @tparam T data type of measured object.
 */
template <typename T>
class TrackContainerT
{
public:
    /**
     * @brief Smart pointer
     *
     */
    using Ptr      = std::shared_ptr<TrackContainerT<T> >;
    using ConstPtr = std::shared_ptr<const TrackContainerT<T> >;
    using TrackId  = uint32_t;
    using TrackPtr = typename TrackT<T>::Ptr;
    using Tracks   = std::unordered_map<TrackId, typename TrackT<T>::Ptr>;
    using SensorId = holo::common::SensorId;

    /**
     * @brief Add new tracks into tracks deque
     *
     * @param track_ptr track pointer
     * @throw throw std::runtime_error if track_ptr is null pointer
     */
    void AddTrack(const TrackPtr track_ptr);

    /**
     * @brief Get track by track id
     *
     * @return const TrackPtr
     */
    const TrackPtr GetTrackById(const TrackId track_id);

    /**
     * @brief Get the Track object according to sensor id and track_id
     *
     * @param [in] sensor_id sensor id
     * @param [in] track_id track id
     * @return const TrackPtr
     */
    const TrackPtr GetTrackById(SensorId const sensor_id, TrackId const track_id);

    /**
     * @brief Remove track by track id
     *
     */
    void RemoveTrackById(const TrackId track_id);

    /**
     * @brief Remove terminated track
     *
     */
    void RemoveTerminatedTrack() noexcept;

    /**
     * @brief Get tracks from track container according to sensor id
     *
     * @param [in] sensor_id sensor id
     * @param [out] results result trtacks
     */
    void GetTracks(const SensorId sensor_id, std::vector<TrackPtr>& results) const;

    /**
     * @brief Get all tracks with all sensors
     *
     * @param [out] results result tracks
     */
    void GetTracks(std::vector<TrackPtr>& results) const;

    /**
     * @brief Get the confirmed tracks from track container according to sensor id
     *
     * @param [in] sensor_id sensor id
     * @param [out] results result trtacks
     */
    void GetConfirmedTracks(const SensorId sensor_id, std::vector<TrackPtr>& results) const;

    /**
     * @brief Get all confirmed tracks with all sensors
     *
     * @param [out] results result tracks
     */
    void GetConfirmedTracks(std::vector<TrackPtr>& results) const;

    /**
     * @brief Get all unconfirmed tracks with all sensors
     *
     * @param [out] results result tracks
     */
    void GetUnConfirmedTracks(std::vector<TrackPtr>& results) const;

    /**
     * @brief Whether all_tracks_ map is empty
     *
     * @return bool_t
     */
    bool_t IsEmpty() const noexcept;

private:
    std::unordered_map<uint32_t, Tracks> all_tracks_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_BASE_TRACK_CONTAINER_H_
