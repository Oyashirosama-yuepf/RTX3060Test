/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_uss_obstacle_track.h
 * @brief This header file defines uss track.
 * @author wenxunzhe(wenxunzhe@holomatic.com)
 * @date "2021-11-27"
 */

#ifndef HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_USS_OBSTACLE_TRACK_H_
#define HOLO_PERCEPTION_OBSTACLE_FUSION_PARKING_USS_OBSTACLE_TRACK_H_

#include <holo/perception/fusion/track.h>
#include <holo/perception/math/first_order_adaptive_windowing.h>
#include <holo/perception/obstacle_fusion/parking_obstacle_motion_estimator.h>
#include <holo/perception/utils/constant_velocity_kalman_filter.h>
#include <holo/perception/utils/sensor_obstacle_track.h>

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
 * @brief Uss obstacle track for tracking, and derived from track
 */
class UssObsTrack
  : public Track<SensorMeasurementKey, holo::obstacle::ObstacleUssT<float32_t>, SensorMeasurementKeyHash>
{
public:
    using Scalar       = float32_t;
    using String       = std::string;
    using Vector       = std::vector<Scalar>;
    using Map          = std::unordered_map<String, Vector>;
    using Timestamp    = holo::common::details::Timestamp;
    using Vector3f     = holo::numerics::Vector3f;
    using SensorId     = TrackBase::SensorId;
    using ObstacleType = holo::obstacle::ObstacleUssT<float32_t>;
    using ObstaclePtr  = std::shared_ptr<ObstacleType>;
    using Base         = Track<SensorMeasurementKey, ObstacleType, SensorMeasurementKeyHash>;  // Track is based on uss
                                                                                       // obstacle, not TrackBase
    using PropertyType        = TrackBase::ObstaclePropertyType;
    using FOAW                = FirstOrderAdaptiveWindowingT<Scalar>;
    using FOAWPtr             = std::shared_ptr<FOAW>;
    using KF                  = ConstantVelocityKalmanFilter;
    using KFPtr               = std::shared_ptr<KF>;
    using MS                  = MotionStatusEstimator;
    using MSPtr               = std::shared_ptr<MS>;
    using MotionStatus        = holo::obstacle::details::MotionStatus;
    using MotionStatusHistory = std::deque<MotionStatus>;
    using MeasurementMap      = Base::MeasurementMap;
    using HistoryType         = std::deque<ObstaclePtr>;

    /**
     * @brief Construct a new fused obstacle Track object
     *
     * @param track_id track id to create track
     * @param obstacle_ptr pointer to uss obstacle
     * @param vel_body ego car's velocity
     * @param angular_velocity ego car's angular velocity
     * @param current_timestamp current timestamp
     */
    UssObsTrack(uint32_t track_id, ObstaclePtr const obstacle_ptr, Vector3f const& vel_body,
                     Scalar const& angular_velocity, Map track_params, Timestamp const& current_timestamp);

    /**
     * @brief predict uss obstacle position/velocity at current timestamp
     *
     * @param current_timestamp current timestamp
     */
    void Predict(Timestamp const& current_timestamp) override;

    /**
     * @brief update uss track using kf
     *
     * @details the measurement have one obstacle at most, because it tracks a individual sensor obstacle
     *
     * @param measurement_map measurement
     */
    void Update(MeasurementMap const& measurement_map) override;

    /**
     * @brief Get the obstacle property object
     *
     * @return TrackBase obstacle property
     */
    PropertyType const& GetProperty() const
    {
        return TrackBase::obstacle_property_;
    }

    /**
     * @brief Get the a container with past obstacles
     *
     * @return Dequeue with obstacle pointer
     */
    HistoryType const& GetHistory() const
    {
        return history_;
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
     * @brief get last measurement in measurement map
     *
     * @return measurement
     */
    MeasurementMap const& GetLastMeasurementMap()
    {
        return last_measurement_map_;
    }

private:
    /**
     * @brief compute mean measurement property
     *
     * @details get mean measurement PropertyType from measurement_map
     *
     * @param measurement_map measurement map
     *
     * @return averaged obstacle measurement property
     */
    PropertyType computeMeanObstacleProperty(MeasurementMap const& measurement_map);

    /**
     * @brief set the Obstacle Property's yaw
     *
     * @details set yaw from estimated obstacle's velocity and motion status
     */
    void setObstacleYaw();

    /**
     * @brief set the Obstacle Property's shape
     *
     * @details set shape from obstacle's distance and sensor's fov
     *
     * @param measurement_map measurement map
     */
    void setObstacleShape(ObstaclePtr const& obs);

    /**
     * @brief set the Obstacle Property using a given obs
     *
     * @param props obstacle pointer
     */
    void setObstacleProperty(ObstaclePtr const& obs);

    /**
     * @brief Set the obstacle property
     */
    void setProperty();

private:
    Timestamp      start_timestamp_;
    Timestamp      current_timestamp_;
    Scalar         angular_velocity_;
    Vector3f       vel_body_;
    uint32_t       lost_count_;
    uint32_t       age_;
    uint32_t       max_history_;
    FOAWPtr        foaw_x_;
    FOAWPtr        foaw_y_;
    KFPtr          kf_;
    MSPtr          motion_status_estimator_;
    HistoryType    history_;
    MeasurementMap last_measurement_map_;
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif
