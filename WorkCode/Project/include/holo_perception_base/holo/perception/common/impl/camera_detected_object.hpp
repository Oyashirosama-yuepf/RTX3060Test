/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_detected_object.hpp
 * @brief This file implements a camera detected object.
 * @author tanghui(tanghui@holomaitc.com)
 * @date 2019-12-16
 */

#ifndef HOLO_PERCEPTION_COMMON_CAMERA_DETECTED_OBJECT_HPP_
#define HOLO_PERCEPTION_COMMON_CAMERA_DETECTED_OBJECT_HPP_

#include <holo/perception/common/camera_detected_object.h>
namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraDetectedObjectT<T>::CameraDetectedObjectT(const Scalar confidence, const Classification& classification,
                                                const IdType id, const Point3Type& position,
                                                const Vector3Type& velocity, const Timestamp& timestamp,
                                                const Box2Type& box2, const Box3Type& box3,
                                                const KeypointVector& keypoint_vector)
  : DetectedObjectT<T>(confidence, classification, id, position, velocity, timestamp)
  , box2_(box2)
  , box3_(box3)
  , keypoint_vector_(keypoint_vector)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraDetectedObjectT<T>::CameraDetectedObjectT(const CameraDetectedObjectT& camera_detected_object) noexcept
  : DetectedObjectT<Scalar>(camera_detected_object.GetConfidence(), camera_detected_object.GetClassification(),
                            camera_detected_object.GetObjectId(), camera_detected_object.GetPosition(),
                            camera_detected_object.GetVelocity(), camera_detected_object.GetTimestamp())
  , box2_(camera_detected_object.box2_)
  , box3_(camera_detected_object.box3_)
  , keypoint_vector_(camera_detected_object.keypoint_vector_)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraDetectedObjectT<T>::CameraDetectedObjectT(CameraDetectedObjectT&& camera_detected_object) noexcept
  : DetectedObjectT<Scalar>(camera_detected_object.GetConfidence(), camera_detected_object.GetClassification(),
                            camera_detected_object.GetObjectId(), std::move(camera_detected_object.GetPosition()),
                            std::move(camera_detected_object.GetVelocity()),
                            std::move(camera_detected_object.GetTimestamp()))
  , box2_(std::move(camera_detected_object.box2_))
  , box3_(std::move(camera_detected_object.box3_))
  , keypoint_vector_(std::move(camera_detected_object.keypoint_vector_))
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraDetectedObjectT<T>::~CameraDetectedObjectT()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraDetectedObjectT<T>& CameraDetectedObjectT<T>::operator=(const CameraDetectedObjectT<Scalar>& other)
{
    DetectedObjectT<T>::operator=(other);
    box2_                       = other.box2_;
    box3_                       = other.box3_;
    keypoint_vector_            = other.keypoint_vector_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraDetectedObjectT<T>& CameraDetectedObjectT<T>::operator=(CameraDetectedObjectT<Scalar>&& other) noexcept
{
    if (this != &other)
    {
        DetectedObjectT<T>::operator=(other);
        box2_                       = other.box2_;
        box3_                       = other.box3_;
        keypoint_vector_            = std::move(other.keypoint_vector_);
    }
    return *this;
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_CAMERA_DETECTED_OBJECT_HPP_