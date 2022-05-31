/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensor_obstacle_track.hpp
 * @brief This header file defines sensor obstacle track implementation.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-24"
 */

#ifndef HOLO_PERCEPTION_UTILS_SENSOR_OBSTACLE_TRACK_HPP_
#define HOLO_PERCEPTION_UTILS_SENSOR_OBSTACLE_TRACK_HPP_

#include <holo/perception/utils/sensor_obstacle_track.h>

namespace holo
{
namespace perception
{
template <typename ObstacleType, TrackType track_type>
SensorObstacleTrack<ObstacleType, track_type>::SensorObstacleTrack(ObstaclePtr obs, uint32_t max_history)
  : Track<SensorMeasurementKey, ObstacleType, SensorMeasurementKeyHash>(track_type)
  , timestamp_(obs->GetTimestamp())
  , max_history_(max_history)
  , lost_count_(0U)
  , age_(1U)
{
    TrackBase::sensor_id_   = obs->GetSensorId();
    TrackBase::obstacle_id_ = obs->GetObstacleId();
    setObstacleProperty(obs);
    history_.push_back(obs);
}

template <typename ObstacleType, TrackType track_type>
void SensorObstacleTrack<ObstacleType, track_type>::Predict(Timestamp const& current_timestamp)
{
    ++lost_count_;
    auto last_obs                   = history_.back();
    auto dt                         = (current_timestamp - timestamp_).ToSec();
    TrackBase::obstacle_property_.x = last_obs->GetPosition().GetX() + last_obs->GetRelativeVelocity()[0U] * dt;
    TrackBase::obstacle_property_.y = last_obs->GetPosition().GetY() + last_obs->GetRelativeVelocity()[1U] * dt;
    timestamp_                      = current_timestamp;
}

template <typename ObstacleType, TrackType track_type>
void SensorObstacleTrack<ObstacleType, track_type>::Update(MeasurementMap const& measurement_map)
{
    if (measurement_map.size() > 0U)
    {
        lost_count_ = 0U;
        ++age_;
        auto obs = measurement_map.begin()->second;
        setObstacleProperty(obs);
        history_.push_back(obs);
        if (history_.size() > max_history_)
        {
            history_.pop_front();
        }
    }
}

template <typename ObstacleType, TrackType track_type>
void SensorObstacleTrack<ObstacleType, track_type>::setObstacleProperty(ObstaclePtr const obs)
{
    TrackBase::obstacle_property_.t  = obs->GetTimestamp();
    TrackBase::obstacle_property_.x  = obs->GetPosition().GetX();
    TrackBase::obstacle_property_.y  = obs->GetPosition().GetY();
    TrackBase::obstacle_property_.z  = obs->GetPosition().GetZ();
    TrackBase::obstacle_property_.vx = obs->GetRelativeVelocity()[0U];
    TrackBase::obstacle_property_.vy = obs->GetRelativeVelocity()[1U];
    TrackBase::obstacle_property_.ax = obs->GetAcceleration()[0U];
    TrackBase::obstacle_property_.ay = obs->GetAcceleration()[1U];
}

template <>
void SensorObstacleTrack<obstacle::ObstacleGeneralT<float32_t>, TrackType::GENERAL>::setObstacleProperty(
    ObstaclePtr const obs);

template <>
void SensorObstacleTrack<obstacle::ObstacleLidarT<float32_t>, TrackType::LIDAR>::setObstacleProperty(
    ObstaclePtr const obs);

template <>
void SensorObstacleTrack<obstacle::ObstacleRadarT<float32_t>, TrackType::RADAR>::setObstacleProperty(
    ObstaclePtr const obs);

template <>
void SensorObstacleTrack<obstacle::ObstacleVisionT<float32_t>, TrackType::VISION>::setObstacleProperty(
    ObstaclePtr const obs);
}  // namespace perception
}  // namespace holo

#endif
