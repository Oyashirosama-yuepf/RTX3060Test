/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file keypoint.hpp
 * @brief This file implements the keypoint.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-16"
 */

#ifndef HOLO_PERCEPTION_COMMON_KEYPOINT_HPP_
#define HOLO_PERCEPTION_COMMON_KEYPOINT_HPP_

#include <cmath>

#include <holo/perception/common/keypoint.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
KeyPointT<T>& KeyPointT<T>::operator=(KeyPointType const& keypoint) noexcept
{
    x_          = keypoint.x_;
    y_          = keypoint.y_;
    z_          = keypoint.z_;
    confidence_ = keypoint.confidence_;
    visibility_ = keypoint.visibility_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t KeyPointT<T>::operator==(KeyPointType const& keypoint) const noexcept
{
    Scalar    err_x          = std::abs(x_ - keypoint.x_);
    Scalar    err_y          = std::abs(y_ - keypoint.y_);
    Scalar    err_z          = std::abs(z_ - keypoint.z_);
    float32_t err_confidence = std::abs(confidence_ - keypoint.confidence_);
    return (err_x <= tol && err_y <= tol && err_z <= tol && err_confidence <= holo::EpsilonT<float32_t>::value &&
            visibility_ == keypoint.visibility_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T KeyPointT<T>::Dist(KeyPointType const& target) const noexcept
{
    Scalar dx = x_ - target.GetX();
    Scalar dy = y_ - target.GetY();
    Scalar dz = z_ - target.GetZ();
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void KeyPointT<T>::ConvertToBaseKeyPoint2(BaseKeyPoint2Type& keypoint2_out) const noexcept
{
    keypoint2_out = BaseKeyPoint2Type(x_, y_, confidence_, visibility_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void KeyPointT<T>::ConvertFromBaseKeyPoint2(BaseKeyPoint2Type const& keypoint2_in) noexcept
{
    x_          = keypoint2_in.GetX();
    y_          = keypoint2_in.GetY();
    z_          = keypoint2_in.GetZ();
    confidence_ = keypoint2_in.GetConfidence();
    visibility_ = keypoint2_in.IsVisible();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void KeyPointT<T>::ConvertToBaseKeyPoint3(BaseKeyPoint3Type& keypoint3_out) const noexcept
{
    keypoint3_out = BaseKeyPoint3Type(x_, y_, z_, confidence_, visibility_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void KeyPointT<T>::ConvertFromBaseKeyPoint3(BaseKeyPoint3Type const& keypoint3_in) noexcept
{
    x_          = keypoint3_in.GetX();
    y_          = keypoint3_in.GetY();
    z_          = keypoint3_in.GetZ();
    confidence_ = keypoint3_in.GetConfidence();
    visibility_ = keypoint3_in.IsVisible();
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_KEYPOINT_HPP_
