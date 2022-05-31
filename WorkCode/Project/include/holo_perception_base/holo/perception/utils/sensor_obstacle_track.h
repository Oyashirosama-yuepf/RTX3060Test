/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensor_obstacle_track.h
 * @brief This header file defines common sensor obstacle track.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-23"
 */

#ifndef HOLO_PERCEPTION_UTILS_SENSOR_TRACK_H_
#define HOLO_PERCEPTION_UTILS_SENSOR_TRACK_H_

#include <deque>

#include <holo/obstacle/obstacle_list.h>
#include <holo/perception/fusion/track.h>
#include <holo/perception/utils/obstacle_property.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup utils
 *
 * @{
 */

/**
 * @brief Sensor measurement key hash
 *
 */
struct SensorMeasurementKeyHash
{
    size_t operator()(SensorMeasurementKey const& key) const
    {
        return std::hash<uint32_t>{}((uint32_t)key.first) ^ std::hash<uint32_t>{}(key.second);
    }
};

/**
 * @brief sensor obstacle track template
 * @details
 * ObstacleType should be a derived class of holo::ObstacleBaseT
 * and must have these methods:
 *  GetSensorId
 *  GetObstacleId
 *  GetPosition
 *  GetVelocity
 *
 * @tparam ObstacleType obstacle type, should derive from holo::ObstacleBaseT
 * @tparam track_type track type
 */
template <typename _ObstacleType, TrackType track_type>
class SensorObstacleTrack : public Track<SensorMeasurementKey, _ObstacleType, SensorMeasurementKeyHash>
{
public:
    using Scalar         = float32_t;
    using ObstacleType   = _ObstacleType;
    using ObstaclePtr    = std::shared_ptr<ObstacleType>;
    using HistoryType    = std::deque<ObstaclePtr>;
    using Timestamp      = holo::common::details::Timestamp;
    using SensorId       = TrackBase::SensorId;
    using PropertyType   = TrackBase::ObstaclePropertyType;
    using Base           = Track<SensorMeasurementKey, ObstacleType, SensorMeasurementKeyHash>;
    using MeasurementMap = typename Base::MeasurementMap;

    /**
     * @brief Construct a new Sensor Obstacle Track object
     *
     * @param obs a sensor obstacle to create the track
     */
    SensorObstacleTrack(ObstaclePtr const obs, uint32_t max_history = 15U);

    /**
     * @brief predict obstacle position/velocity at current timestamp
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
     * @brief Get the Sensor Id object
     *
     * @return SensorId
     */
    SensorId GetSensorId() const
    {
        return TrackBase::sensor_id_;
    }

    /**
     * @brief Get the Obstacle Id object
     *
     * @return uint32_t
     */
    uint32_t GetObstacleId() const
    {
        return TrackBase::obstacle_id_;
    }

    /**
     * @brief Get the Property object
     *
     * @return PropertyType const&
     */
    PropertyType const& GetProperty() const
    {
        return TrackBase::obstacle_property_;
    }

    /**
     * @brief Get the History object
     *
     * @return HistoryType const&
     */
    HistoryType const& GetHistory() const
    {
        return history_;
    }

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

protected:
    /**
     * @brief Set the Obstacle Property using obs's property
     *
     * @param obs the obstacle
     */
    virtual void setObstacleProperty(ObstaclePtr const obs);

private:
    Timestamp   timestamp_;
    HistoryType history_;      ///< history
    uint32_t    max_history_;  ///< max history size
    uint32_t    lost_count_;
    uint32_t    age_;
};

using GeneralObstacleTrack = SensorObstacleTrack<obstacle::ObstacleGeneralT<float32_t>, TrackType::GENERAL>;
using LidarObstacleTrack   = SensorObstacleTrack<obstacle::ObstacleLidarT<float32_t>, TrackType::LIDAR>;
using RadarObstacleTrack   = SensorObstacleTrack<obstacle::ObstacleRadarT<float32_t>, TrackType::RADAR>;
using VisionObstacleTrack  = SensorObstacleTrack<obstacle::ObstacleVisionT<float32_t>, TrackType::VISION>;

using GeneralObstacleTrackPtr = std::shared_ptr<GeneralObstacleTrack>;
using LidarObstacleTrackPtr   = std::shared_ptr<LidarObstacleTrack>;
using RadarObstacleTrackPtr   = std::shared_ptr<RadarObstacleTrack>;
using VisionObstacleTrackPtr  = std::shared_ptr<VisionObstacleTrack>;

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
