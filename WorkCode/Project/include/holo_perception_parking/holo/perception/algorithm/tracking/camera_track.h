/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_track.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomaitc.com)
 * @date "2019-12-31"
 */

#ifndef HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_H_
#define HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_H_

#include <holo/perception/algorithm/tracking/sort_kalman_filter.h>
#include <holo/perception/common/box_object.h>
#include <holo/perception/common/keypoint.h>
#include <holo/perception/math/adaptive_window_filter.h>
#include <holo/perception/math/first_order_adaptive_windowing.h>
#include <holo/perception/math/recursive_least_square_filter.h>
#include <holo/perception/space_convertor/velocity_estimator.h>
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
 * @brief Camera detected object track
 *
 * @tparam T data type
 * @todo add kalman filter
 */
template <typename T>
class CameraTrackT : public TrackT<BoxObjectT<T, 8U>>
{
public:
    using AgeType                  = uint32_t;
    using CameraDetectedObjectType = BoxObjectT<T, 8U>;
    using CameraDetectedObjectPtr  = std::shared_ptr<CameraDetectedObjectType>;
    using Box2Type                 = Box2DT<T>;
    using TrackType                = TrackT<CameraDetectedObjectType>;
    using Stage                    = typename TrackType::Stage;
    using TrackId                  = typename TrackType::TrackId;
    using RLSFilterType            = RecursiveLeastSquareFilterT<T>;
    using RLSFilterPtr             = std::shared_ptr<RLSFilterType>;
    using AWFType                  = AdaptiveWindowFilterT<T>;
    using AWFPtr                   = std::shared_ptr<AWFType>;
    using AWFVector                = std::vector<AWFPtr>;
    using FOAWType                 = FirstOrderAdaptiveWindowingT<T>;
    using FOAWPtr                  = std::shared_ptr<FOAWType>;
    using SORTKalmanFilterType     = SORTKalmanFilterT<T>;
    using SORTKalmanFilterPtr      = std::shared_ptr<SORTKalmanFilterType>;
    using KeyPointType             = typename CameraDetectedObjectType::KeyPointType;
    using KeyPointVector           = typename CameraDetectedObjectType::KeyPoint2DVector;
    using Timestamp                = holo::common::Timestamp;
    using SensorId                 = holo::common::SensorId;

    /**
     * @brief Construct a new Camera Track T object
     *
     * @param id track id
     * @param stage track stage
     * @param sensor_id track sensor id
     * @param timestamp track start time
     * @param object_ptr track's measured object pointer
     * @param x_forget_factor forget factor of RLS filter for x direction
     * @param x_init_variance init variance of RLS filter for x direction
     * @param x_poly_degree degree of polynomial of RLS filter for x direction
     * @param y_forget_factor forget factor of RLS filter for y direction
     * @param y_init_variance init variance of RLS filter for y direction
     * @param y_poly_degree degree of polynomial of RLS filter for y direction
     */
    CameraTrackT(const TrackId id, const Stage stage, const SensorId sensor_id, const Timestamp& timestamp,
                 const CameraDetectedObjectPtr object_ptr, size_t const max_window_size, T const max_delta,
                 T const min_forget_factor);

    /**
     * @brief Update the track
     * @details Check the timestamp of the detected object
     * if the timestamp is newer, save the object to history
     *
     * @param det_obj_ptr camera detected object pointer
     * @param use_kf whether use kalman filter in update
     * @return bool_t true if the object has newer timestamp else false
     *
     * @todo add Kalman filter
     */
    bool_t Update(const CameraDetectedObjectPtr det_obj_ptr, bool_t use_kf = true);

    /**
     * @brief Predict the next time bounding box of this track
     *
     * @param use_kf whether use kalman filter in predict
     * @return Box2Type predicted bbox
     *
     * @todo add Kalman filter
     */
    Box2Type Predict(bool_t use_kf = true);

    /**
     * @brief Increase hit num by one
     *
     * @return AgeType increased hit num
     */
    AgeType IncreaseHitNum()
    {
        ++hit_num_;
        return hit_num_;
    }

    /**
     * @brief Reset hit num to zero
     *
     */
    void ResetHitNum()
    {
        hit_num_ = 0;
    }

    /**
     * @brief Increase time since update by one
     *
     * @return AgeType increased time since update
     */
    AgeType IncreaseTimeSinceUpdate()
    {
        ++time_since_update_;
        return time_since_update_;
    }

    /**
     * @brief Increase age in predict by one
     *
     * @return AgeType, increased age after predict
     */
    AgeType IncreaseAge()
    {
        ++age_;
        return age_;
    }

    /**
     * @brief Get the Age num
     *
     * @return AgeType, object age
     */
    AgeType GetAge()
    {
        return age_;
    }

    /**
     * @brief Reset time since update to zero
     *
     */
    void ResetTimeSinceUpdate()
    {
        time_since_update_ = 0;
    }

    /**
     * @brief Get hit num
     *
     * @return const AgeType hit num
     */
    AgeType GetHitNum()
    {
        return hit_num_;
    }

    /**
     * @brief Get the Time Since Update
     *
     * @return const AgeType time since update
     */
    AgeType GetTimeSinceUpdate()
    {
        return time_since_update_;
    }

    /**
     * @brief Smooth keypoint and height of box2, box3
     */
    void SmoothKeypointAndHeight();

    /**
     * @brief Smooth position and velocity of the newest object in track history
     */
    void SmoothPositionVelocity();

private:
    AgeType             hit_num_;                ///< time steps the object was continuously detected
    AgeType             time_since_update_;      ///< time steps the object was continuously lost
    AgeType             age_;                    ///< time steps the object was predicted
    AWFVector           keypoint_u_awf_vector_;  ///< smoothing keypoint x
    AWFVector           keypoint_v_awf_vector_;  ///< smoothing keypoint y
    AWFPtr              position_x_awf_ptr_;     ///< smoothing x position
    AWFPtr              position_y_awf_ptr_;     ///< smoothing y position
    FOAWPtr             velocity_x_foaw_ptr_;    ///< estimate velocity x
    FOAWPtr             velocity_y_foaw_ptr_;    ///< estimate velocity y
    AWFPtr              box_height_awf_ptr_;
    RLSFilterPtr        vehicle_height_rls_ptr_;
    SORTKalmanFilterPtr sort_kalman_filter_ptr_;

    static const size_t keypoint_num_;  ///< keypoint number used for 2d to 3d
};

/**
 * @}
 *
 */
}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_TRACKING_CAMERA_TRACK_H_
