/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_track.hpp
 * @brief This header file defines camera detected object track.
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2020-01-02"
 */

#ifndef HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_HPP_
#define HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_HPP_

#include <holo/perception/algorithm/tracking/camera_track.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
const size_t CameraTrackT<T>::keypoint_num_ = 2U;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
CameraTrackT<T>::CameraTrackT(const TrackId id, const Stage stage, const SensorId sensor_id, const Timestamp& timestamp,
                              const CameraDetectedObjectPtr object_ptr, size_t const max_window_size, T const max_delta,
                              T const min_forget_factor)
  : hit_num_(1U), time_since_update_(0U), age_(0U)
{
    TrackType::id_         = id;
    TrackType::stage_      = stage;
    TrackType::sensor_id_  = sensor_id;
    TrackType::start_time_ = timestamp;
    TrackType::track_list_.push_front(object_ptr);

    T const       sigma  = static_cast<T>(1.0f);
    uint8_t const degree = static_cast<uint8_t>(1U);

    keypoint_u_awf_vector_.reserve(keypoint_num_);
    keypoint_v_awf_vector_.reserve(keypoint_num_);
    for (size_t i = 0U; i < keypoint_num_; ++i)
    {
        // keypoint_u_awf_vector_.push_back(
        //     std::make_shared<AWFType>(max_window_size, max_delta, min_forget_factor, sigma, degree));
        // keypoint_v_awf_vector_.push_back(
        //     std::make_shared<AWFType>(max_window_size, max_delta, min_forget_factor, sigma, degree));
        keypoint_u_awf_vector_.push_back(std::make_shared<AWFType>(max_window_size, max_delta, 1.0f, sigma, degree));
        keypoint_v_awf_vector_.push_back(std::make_shared<AWFType>(max_window_size, max_delta, 1.0f, sigma, degree));
    }
    position_x_awf_ptr_  = std::make_shared<AWFType>(max_window_size, max_delta, min_forget_factor, sigma, degree);
    position_y_awf_ptr_  = std::make_shared<AWFType>(max_window_size, max_delta, min_forget_factor, sigma, degree);
    velocity_x_foaw_ptr_ = std::make_shared<FOAWType>(max_window_size, max_delta);
    velocity_y_foaw_ptr_ = std::make_shared<FOAWType>(max_window_size, max_delta);
    box_height_awf_ptr_  = std::make_shared<AWFType>(max_window_size, max_delta, min_forget_factor, sigma, degree);
    vehicle_height_rls_ptr_ =
        std::make_shared<RLSFilterType>(static_cast<T>(1.0f), sigma, 0U);  // since vehicle height is a constant

    sort_kalman_filter_ptr_ = std::make_shared<SORTKalmanFilterType>(object_ptr->GetBox2());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo add kalman filter
template <typename T>
bool_t CameraTrackT<T>::Update(const CameraDetectedObjectPtr det_obj_ptr, bool_t use_kf)
{
    // check the timestamp
    CameraDetectedObjectPtr latest_obj_ptr = TrackType::track_list_.front();
    if (det_obj_ptr->GetTimestamp() > latest_obj_ptr->GetTimestamp())
    {
        if (use_kf)
        {
            sort_kalman_filter_ptr_->Update(det_obj_ptr->GetBox2());
        }
        ResetTimeSinceUpdate();
        IncreaseHitNum();
        TrackType::track_list_.push_front(det_obj_ptr);

        // if list is full, remove the oldest frame
        if (TrackType::track_list_.size() > TrackType::max_list_size_)
        {
            TrackType::track_list_.pop_back();
        }
        return true;
    }
    else
    {
        LOG(ERROR) << "Camera track receive a older timestamp: " << det_obj_ptr->GetTimestamp().ToString()
                   << ", latest is " << latest_obj_ptr->GetTimestamp().ToString() << std::endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// todo add kalman filter
template <typename T>
Box2DT<T> CameraTrackT<T>::Predict(bool_t use_kf)
{
    IncreaseAge();
    if (time_since_update_ > 0U)
    {
        ResetHitNum();
    }
    IncreaseTimeSinceUpdate();

    if (use_kf)
    {
        Box2Type predict_box;
        bool_t   flag = sort_kalman_filter_ptr_->Predict(predict_box);
        return flag ? predict_box : TrackType::track_list_.front()->GetBox2();
    }
    else
    {
        return TrackType::track_list_.front()->GetBox2();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackT<T>::SmoothKeypointAndHeight()
{
    auto             current_obj_iter = TrackType::track_list_.begin();
    const Timestamp& current_time     = (*current_obj_iter)->GetTimestamp();

    T time_delta = static_cast<T>((current_time - TrackType::start_time_).ToSec());

    CameraDetectedObjectPtr det_obj_ptr     = *current_obj_iter;
    KeyPointVector          keypoint_vector = det_obj_ptr->GetKeyPoint2DVector();
    KeyPointVector          smoothed_keypoint_vector;
    smoothed_keypoint_vector.reserve(keypoint_vector.size());

    for (size_t i = 0U; i < keypoint_num_; ++i)
    {
        KeyPointType kp            = keypoint_vector[i];
        T            smoothed_kp_u = keypoint_u_awf_vector_[i]->Update(time_delta, kp.GetX());
        T            smoothed_kp_v = keypoint_v_awf_vector_[i]->Update(time_delta, kp.GetY());
        smoothed_keypoint_vector.push_back(
            KeyPointType(smoothed_kp_u, smoothed_kp_v, 0U, kp.GetConfidence(), kp.IsVisible()));
    }
    for (size_t i = keypoint_num_; i < keypoint_vector.size(); ++i)
    {
        smoothed_keypoint_vector.push_back(keypoint_vector[i]);
    }

    auto current_box2         = det_obj_ptr->GetBox2();
    auto current_box3         = det_obj_ptr->GetBox3();
    T    smoothed_box2_height = box_height_awf_ptr_->Update(time_delta, det_obj_ptr->GetBox2().GetHeight());
    T    smoothed_box3_height = vehicle_height_rls_ptr_->Update(time_delta, det_obj_ptr->GetBox3().GetZDim());

    Box2DT<T> smoothed_box2(current_box2);
    Box3DT<T> smoothed_box3(current_box3);
    smoothed_box3.SetZDim(smoothed_box3_height);
    smoothed_box2.SetHeight(smoothed_box2_height);

    det_obj_ptr->SetKeyPoint2DVector(smoothed_keypoint_vector);
    det_obj_ptr->SetBox2(smoothed_box2);
    det_obj_ptr->SetBox3(smoothed_box3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CameraTrackT<T>::SmoothPositionVelocity()
{
    auto                              current_obj_iter = TrackType::track_list_.begin();
    const holo::geometry::Point3T<T>& current_position = (*current_obj_iter)->GetPosition();
    const holo::common::Timestamp&    current_time     = (*current_obj_iter)->GetTimestamp();

    T time_delta = static_cast<T>((current_time - TrackType::start_time_).ToSec());

    T smoothed_position_x  = position_x_awf_ptr_->Update(time_delta, current_position.GetX());
    T smoothed_position_y  = position_y_awf_ptr_->Update(time_delta, current_position.GetY());
    T estimated_velocity_x = velocity_x_foaw_ptr_->Update(time_delta, smoothed_position_x);
    T estimated_velocity_y = velocity_y_foaw_ptr_->Update(time_delta, smoothed_position_y);

    // set the smoothed position and velocity
    holo::geometry::Point3T<T>  smoothed_position(smoothed_position_x, smoothed_position_y, static_cast<T>(0.0));
    holo::numerics::Vector3T<T> estimated_velocity(estimated_velocity_x, estimated_velocity_y, static_cast<T>(0.0));
    (*current_obj_iter)->SetPosition(smoothed_position);
    (*current_obj_iter)->SetVelocity(estimated_velocity);
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_HPP_
