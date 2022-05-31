/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_fused_obstacle_track.h
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-08-17"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_FUSED_OBSTACLE_TRACK_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_FUSED_OBSTACLE_TRACK_H_

#include <holo/common/odometry.h>
#include <holo/perception/fusion/track.h>
#include <holo/perception/math/first_order_adaptive_windowing.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_motion_estimator.h>
#include <holo/perception/obstacle_fusion/parking_ukf.h>
#include <holo/perception/utils/constant_velocity_kalman_filter.h>
#include <holo/perception/utils/sensor_obstacle_track.h>

#include <unordered_set>

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
 * @brief Fused obstacle track derived from track
 */
class ParkingFusedObstacleTrack : public Track<SensorMeasurementKey, TrackBase, SensorMeasurementKeyHash>
{
public:
    using Scalar              = float32_t;
    using String              = std::string;
    using Bool                = bool_t;
    using Vector              = std::vector<Scalar>;
    using Map                 = std::unordered_map<String, Vector>;
    using Base                = Track<SensorMeasurementKey, TrackBase, SensorMeasurementKeyHash>;
    using PropertyType        = ObstacleProperty<Scalar>;
    using Classification      = holo::common::Classification;
    using FOAW                = FirstOrderAdaptiveWindowingT<Scalar>;
    using FOAWPtr             = std::shared_ptr<FOAW>;
    using KF                  = ConstantVelocityKalmanFilter;
    using KFPtr               = std::shared_ptr<KF>;
    using Vector3f            = holo::numerics::Vector3f;
    using MS                  = MotionStatusEstimator;
    using MSPtr               = std::shared_ptr<MS>;
    using MotionStatus        = holo::obstacle::details::MotionStatus;
    using MotionStatusHistory = std::deque<MotionStatus>;
    using OdometryType        = holo::common::Odometryf;

    using HistoryType = std::deque<std::pair<PropertyType, Timestamp>>;

    /**
     * @brief Construct a new Fused Obstacle Track object
     *
     * @param track_id track id to create track
     * @param measurement_map measurement
     * @param current_timestamp current timestamp
     */
    ParkingFusedObstacleTrack(uint32_t track_id, MeasurementMap const& measurement_map, Vector3f const& vel_body,
                              Scalar const& angular_velocity, Pose3f const& current_pose, Map track_params,
                              Timestamp const& current_timestamp, std::vector<Scalar> const& sensor_field_of_view);

    /**
     * @brief predict Fused obstacle position/velocity at current timestamp
     *
     * @param current_timestamp current timestamp
     */
    void Predict(Timestamp const& current_timestamp) override;

    /**
     * @brief store the new incoming data
     * @details the measurement have one obstacle at most,
     * because it tracks a individual sensor obstacle
     *
     * @param measurement_map measurement
     */
    void Update(MeasurementMap const& measurement_map) override;

    /**
     * @brief Get the motion status object
     *
     * @return motion status
     */
    MotionStatus GetMotionStats() const
    {
        return motion_status_estimator_->GetCurrentMotionStatus();
    }

    /**
     * @brief Get the Timestamp object
     *
     * @return Timestamp
     */
    Timestamp GetCurrentTimestamp() const
    {
        return this->current_timestamp_;
    }

    /**
     * @brief Get estimated y Position
     *
     * @return estimated y position
     */
    Vector3f GetRevisedVelocity() const
    {
        return Vector3f(revised_props_.vx, revised_props_.vy, 0.0f);
    }

    /**
     * @brief Get the Classification
     *
     * @return Object's Classification
     */
    Classification GetClassification() const
    {
        return revised_props_.cls;
    }

    /**
     * @brief Get the lost count object
     *
     * @return lost count of track
     */
    uint32_t GetLostCount() const
    {
        return lost_count_;
    }

    /**
     * @brief get age of sensor obstacle
     *
     * @return uint32_t
     */
    uint32_t GetAge() const
    {
        return age_;
    }

    /**
     * @brief get measurement memory size
     *
     * @return uint32_t
     */
    size_t GetMeasurementHistorySize()
    {
        return history_measurements_.size();
    }

    /**
     * @brief get last measurement in measurement map
     *
     * @return measurement
     */
    MeasurementMap const& GetLastMeasurementMap()
    {
        return last_measurement_map_;
    }

    /**
     * @brief get last updated timestamp
     *
     * @return timestamp
     */
    Timestamp GetLastUpdateTimeStamp() const
    {
        return last_updated_timestamp_;
    }

    /**
     * @brief get the pose object
     *
     * @return pose3f
     */
    Pose3f GetPose()
    {
        return this->current_pose_;
    }

    /**
     * @brief get absolute position
     *
     * @return point3f
     */
    Point3f GetAbsolutePosition() const
    {
        return absolute_position_;
    }

    /**
     * @brief get the global yaw for locked track
     *
     * @return Scalar
     */
    Scalar GetYawByOdometry();

    /**
     * @brief get the global position for locked track
     *
     * @return Point3f
     */
    Point3f GetPositionByOdometry();

    /**
     * @brief update history measurement map
     * @details deque
     * @param measurement_map measurement map
     */
    void UpdateMeasurementHistory(MeasurementMap const& measurement_map);

    /**
     * @brief update ego odometry pose
     * @param current_pose pose from tracking pipeline
     */
    void UpdateEgoPose(Pose3f const& current_pose)
    {
        this->current_pose_ = current_pose;
    }

public:
    /**
     * @brief lock a track if satisfied
     */
    void LockTrack();

    /**
     * @brief unlock a track
     */
    inline void UnlockTrack()
    {
        this->is_locked = false;
    }

    /**
     * @brief is a lock track
     *
     * @return bool
     */
    inline bool_t isLocked()
    {
        return this->is_locked;
    }

public:
    struct RansacParams
    {
        static constexpr const uint32_t max_iteration       = 10;
        static constexpr const Scalar   distance_tolerance_ = 0.1f;
        static constexpr const Scalar   confidence          = 0.9f;
        static constexpr const Bool     enable_optimizer    = true;
    } ransac_params_;

public:
    struct YawParams
    {
        static constexpr const Scalar w_fully         = 1.0f;
        static constexpr const Scalar w_partialy      = 0.5f;
        static constexpr const Scalar w_rearly        = 0.25f;
        static constexpr const Scalar w_last          = 0.2f;
        static constexpr const Scalar yaw_angle_front = 60.0f;
        static constexpr const Scalar yaw_angle_rear  = 135.0f;
    } yaw_params_;

    /**
     * @brief update polar according to weight and yaw
     * @details  weighted yaw
     * @param weight measure weght
     * @param yaw yaw measure
     * @param x  x Descartes
     * @param y y Descartes
     */
    void yawWeighted(Scalar weight, Scalar const& yaw, Scalar& x, Scalar& y);

    /**
     * @brief estimate yaw according to sid, location
     * @param yaw_map yaw map
     * @return estimated yaw
     */
    Scalar estimateYaw(std::map<uint32_t, std::pair<double, Scalar>> const& yaw_map);

public:
    /**
     * @brief Set the Global Yaw object
     *
     * @param property
     */
    void SetAbsoluteAnchor(PropertyType const& property);

    /**
     * @brief Set the Absolute Position object
     *
     */
    void SetAbsolutePosition();

    /**
     * @brief Set the Yaw Obstacle Property object
     *
     * @param yaw yaw
     */
    void SetYaw(Scalar yaw)
    {
        this->obstacle_property_.yaw = yaw;
    }

    /**
     * @brief Set the Yaw Obstacle Property object
     *
     * @param yaw yaw
     */
    void SetPosition(Point3f const& position)
    {
        this->obstacle_property_.x = position.GetX();
        this->obstacle_property_.y = position.GetY();
        this->obstacle_property_.z = position.GetZ();
    }

private:
    /**
     * @brief compute mean measurement property
     * @details get mean measurement PropertyType from measurement_map
     *
     * @param measurement_map measurement map
     * @return averaged obstacle measurement property
     */
    PropertyType computeMeanObstacleProperty(MeasurementMap const& measurement_map);

    /**
     * @brief Set the Obstacle Property using a given obs's property
     *
     * @param props obstacle's property
     */
    void setProperty(ObstaclePropertyType const& props);

    /**
     * @brief Set the Obstacle Property
     */
    void setProperty();

private:
    Timestamp           start_timestamp_;
    Timestamp           current_timestamp_;
    Timestamp           last_updated_timestamp_;
    uint32_t            lost_count_;
    uint32_t            age_;
    KFPtr               kf_;
    MSPtr               motion_status_estimator_;
    Scalar              last_measured_yaw_;
    MeasurementMap      last_measurement_map_;
    size_t              max_history_size_;
    std::vector<Scalar> sensor_field_of_view_;

    Pose3f   current_pose_;
    Vector3f vel_body_;
    Scalar   angular_velocity_;

    Point3f absolute_position_;
    Point3f absolute_position_anchor_;

public:
    bool_t       is_locked;
    HistoryType  history_measurements_;
    PropertyType revised_props_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
