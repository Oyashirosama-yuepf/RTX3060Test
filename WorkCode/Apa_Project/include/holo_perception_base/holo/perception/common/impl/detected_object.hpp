/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file detected_object.hpp
 * @brief This file implements a detected object.
 * @author tanghui(tanghui@holomaitc.com)
 * @date 2019-12-16
 */

#ifndef HOLO_PERCEPTION_COMMON_DETECTED_OBJECT_HPP_
#define HOLO_PERCEPTION_COMMON_DETECTED_OBJECT_HPP_

#include <holo/perception/common/detected_object.h>
namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
DetectedObjectT<T>::DetectedObjectT(const Scalar confidence, const Classification& classification, const IdType id,
                                    const Point3Type& position, const Vector3Type& velocity, const Timestamp& timestamp)
  : confidence_(confidence)
  , classification_(classification)
  , object_id_(id)
  , position_(position)
  , velocity_(velocity)
  , timestamp_(timestamp)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
DetectedObjectT<T>::DetectedObjectT(const DetectedObjectT& detected_object) noexcept
  : confidence_(detected_object.confidence_)
  , classification_(detected_object.classification_)
  , object_id_(detected_object.object_id_)
  , position_(detected_object.position_)
  , velocity_(detected_object.velocity_)
  , timestamp_(detected_object.timestamp_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
DetectedObjectT<T>::DetectedObjectT(DetectedObjectT&& detected_object) noexcept
  : confidence_(detected_object.confidence_)
  , classification_(detected_object.classification_)
  , object_id_(detected_object.object_id_)
  , position_(std::move(detected_object.position_))
  , velocity_(std::move(detected_object.velocity_))
  , timestamp_(std::move(detected_object.timestamp_))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
DetectedObjectT<T>::~DetectedObjectT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
DetectedObjectT<T>& DetectedObjectT<T>::operator=(const DetectedObjectT<Scalar>& other)
{
    confidence_     = other.confidence_;
    classification_ = other.classification_;
    object_id_      = other.object_id_;
    position_       = other.position_;
    velocity_       = other.velocity_;
    timestamp_      = other.timestamp_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
DetectedObjectT<T>& DetectedObjectT<T>::operator=(DetectedObjectT<Scalar>&& other) noexcept
{
    if (this != &other)
    {
        confidence_     = other.confidence_;
        classification_ = other.classification_;
        object_id_      = other.object_id_;
        position_       = std::move(other.position_);
        velocity_       = std::move(other.velocity_);
        timestamp_      = (std::move(other.timestamp_));
    }

    return *this;
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_DETECTED_OBJECT_HPP__