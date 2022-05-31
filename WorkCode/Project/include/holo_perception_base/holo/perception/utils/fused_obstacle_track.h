/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file fused_obstacle_track.h
 * @brief This header file defines fused track.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-30"
 */

#ifndef HOLO_PERCEPTION_UTILS_FUSED_OBSTACLE_TRACK_H_
#define HOLO_PERCEPTION_UTILS_FUSED_OBSTACLE_TRACK_H_

#include <holo/perception/fusion/track.h>
#include <holo/perception/utils/constant_velocity_kalman_filter.h>
#include <holo/perception/utils/sensor_obstacle_track.h>

/**
 * @addtogroup utils
 *
 * @{
 */

namespace holo
{
namespace perception
{
/**
 * @brief fused obstacle track
 *
 */
class FusedObstacleTrack : public Track<SensorMeasurementKey, TrackBase, SensorMeasurementKeyHash>
{
public:
    using Base           = Track<SensorMeasurementKey, TrackBase, SensorMeasurementKeyHash>;
    using Scalar         = float32_t;
    using PropertyType   = ObstacleProperty<Scalar>;
    using CVKF           = ConstantVelocityKalmanFilter;
    using CVKFPtr        = std::shared_ptr<CVKF>;
    using MeasurementPtr = typename Base::MeasurementPtr;
    using MeasurementMap = typename Base::MeasurementMap;
    using Timestamp      = holo::common::details::Timestamp;

    /**
     * @brief Construct a new Fused Obstacle Track object
     *
     */
    FusedObstacleTrack(uint32_t id, MeasurementMap const& measurement_map, Timestamp const& timestamp);

    /**
     * @brief predict track state at current timestamp
     *
     * @param current_timestamp current timestamp
     */
    virtual void Predict(Timestamp const& current_timestamp) override;

    /**
     * @brief update track state using measurements
     *
     * @param measurement_map measurements
     */
    virtual void Update(MeasurementMap const& measurement_map) override;

    /**
     * @brief Get the Track Id
     *
     * @return uint32_t track id
     */
    uint32_t GetTrackId() const
    {
        return TrackBase::obstacle_id_;
    }

    /**
     * @brief Get the Age
     *
     * @return uint32_t track age
     */
    uint32_t GetAge() const
    {
        return age_;
    }

    /**
     * @brief Get the Lost Count
     *
     * @return uint32_t track lost count
     */
    uint32_t GetLostCount() const
    {
        return lost_count_;
    }

protected:
    /**
     * @brief compute mean obstacle property of measurements
     *
     * @param measurement_map measurements
     * @return PropertyType mean obstacle property
     */
    virtual PropertyType computeMeanObstacleProperty(MeasurementMap const& measurement_map);

    /**
     * @brief Set TrackBase::obstacle_property_ using kf_'s state
     *
     */
    virtual void setProperty();

protected:
    uint32_t age_;
    uint32_t lost_count_;
    CVKFPtr  kf_;
};

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
