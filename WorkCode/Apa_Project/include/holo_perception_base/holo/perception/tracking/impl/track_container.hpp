/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track_container.hpp
 * @brief the implementation of template class TrackContainerT
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-10"
 */

#ifndef HOLO_PERCEPTION_TRACKING_TRACK_CONTAINER_HPP_
#define HOLO_PERCEPTION_TRACKING_TRACK_CONTAINER_HPP_

#include <holo/log/hololog.h>

#include <holo/perception/tracking/track_container.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::AddTrack(const TrackPtr track_ptr)
{
    auto sensor_id  = static_cast<uint32_t>(track_ptr->GetSensorId());
    auto iter_track = all_tracks_.find(sensor_id);

    // if not have correspond sensor id in all_tracks_
    if (iter_track == all_tracks_.end())
    {
        Tracks tracks;
        tracks[track_ptr->GetId()] = track_ptr;
        all_tracks_[sensor_id]     = tracks;
    }
    // pls make sure different track has different track id
    else
    {
        (*iter_track).second[track_ptr->GetId()] = track_ptr;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
const typename TrackContainerT<T>::TrackPtr TrackContainerT<T>::GetTrackById(const TrackId track_id)
{
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        auto iter_track = iter_sensor->second.find(track_id);
        if (iter_track != iter_sensor->second.end())
        {
            return iter_track->second;
        }
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
const typename TrackContainerT<T>::TrackPtr TrackContainerT<T>::GetTrackById(SensorId const sensor_id,
                                                                             TrackId const  track_id)
{
    auto iter_sensor = all_tracks_.find(static_cast<uint32_t>(sensor_id));
    if (iter_sensor == all_tracks_.end())
    {
        LOG(WARNING) << "not supported sensor type: " << sensor_id;
        return nullptr;
    }
    else
    {
        auto iter_track = iter_sensor->second.find(track_id);
        if (iter_track == iter_sensor->second.end())
        {
            LOG(WARNING) << "not supported track id: " << track_id;
            return nullptr;
        }
        else
        {
            return iter_track->second;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::RemoveTrackById(const TrackId track_id)
{
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        auto iter_track = iter_sensor->second.find(track_id);
        if (iter_track != iter_sensor->second.end())
        {
            iter_sensor->second.erase(iter_track->first);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::RemoveTerminatedTrack() noexcept
{
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end();)
        {
            if (iter_track->second->GetStage() == TrackT<T>::Stage::TERMINATED)
            {
                iter_track = iter_sensor->second.erase(iter_track);
            }
            else
            {
                ++iter_track;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::GetTracks(const SensorId sensor_id, std::vector<TrackPtr>& results) const
{
    results.clear();
    auto iter_sensor = all_tracks_.find(static_cast<uint32_t>(sensor_id));
    if (iter_sensor == all_tracks_.end())
    {
        LOG(WARNING) << "not supported sensor type: " << sensor_id;
    }
    else
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end(); iter_track++)
        {
            results.emplace_back(iter_track->second);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::GetTracks(std::vector<TrackPtr>& results) const
{
    results.clear();
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end(); iter_track++)
        {
            results.emplace_back(iter_track->second);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::GetConfirmedTracks(const SensorId sensor_id, std::vector<TrackPtr>& results) const
{
    results.clear();
    auto iter_sensor = all_tracks_.find((uint32_t)sensor_id);
    if (iter_sensor == all_tracks_.end())
    {
        LOG(WARNING) << "not supported sensor type: " << sensor_id;
    }
    else
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end(); iter_track++)
        {
            if (iter_track->second->GetStage() == TrackT<T>::Stage::CONFIRMED)
            {
                results.emplace_back(iter_track->second);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::GetConfirmedTracks(std::vector<TrackPtr>& results) const
{
    results.clear();
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end(); iter_track++)
        {
            if (iter_track->second->GetStage() == TrackT<T>::Stage::CONFIRMED)
            {
                results.emplace_back(iter_track->second);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackContainerT<T>::GetUnConfirmedTracks(std::vector<TrackPtr>& results) const
{
    results.clear();
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end(); iter_track++)
        {
            if (iter_track->second->GetStage() != TrackT<T>::Stage::CONFIRMED &&
                iter_track->second->GetStage() != TrackT<T>::Stage::TERMINATED)
            {
                results.emplace_back(iter_track->second);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t TrackContainerT<T>::IsEmpty() const noexcept
{
    for (auto iter_sensor = all_tracks_.begin(); iter_sensor != all_tracks_.end(); iter_sensor++)
    {
        for (auto iter_track = iter_sensor->second.begin(); iter_track != iter_sensor->second.end(); iter_track++)
        {
            if (!iter_track->second->IsEmpty())
            {
                return false;
            }
        }
    }
    return true;
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_TRACK_CONTAINER_HPP_
