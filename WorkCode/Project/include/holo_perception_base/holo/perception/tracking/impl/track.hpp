/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track.hpp
 * @brief The implementation of template class TrackT
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2019-12-10"
 */

#ifndef HOLO_PERCEPTION_TRACKING_TRACK_HPP_
#define HOLO_PERCEPTION_TRACKING_TRACK_HPP_

#include <holo/log/hololog.h>
#include <holo/perception/tracking/track.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
std::array<std::string, TrackT<T>::STAGE_NUM> const TrackT<T>::STAGE_STRING = {"UNCONFIRMED", "CONFIRMED", "LOST",
                                                                               "TERMINATED", "RESERVED"};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
TrackT<T>::TrackT() noexcept
  : id_(0U), stage_(Stage::UNCONFIRMED), sensor_id_(0U), start_time_(holo::Timestamp(0U, 0U)), max_list_size_(20U)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
TrackT<T>::TrackT(TrackId id, const Stage stage, const SensorId sensor_id, const Timestamp& timestamp, const T& object,
                  const uint32_t max_list_size) noexcept
  : id_(id), stage_(stage), sensor_id_(sensor_id), start_time_(timestamp), max_list_size_(max_list_size)
{
    track_list_.push_front(std::make_shared<T>(object));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void TrackT<T>::Update(const T& object)
{
    (void)object;
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_TRACK_HPP_
