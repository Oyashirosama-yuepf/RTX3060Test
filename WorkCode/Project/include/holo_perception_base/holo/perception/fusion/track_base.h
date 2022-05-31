/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file track_base.h
 * @brief This header file defines track base class.
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-06-21"
 */

#ifndef HOLO_PERCEPTION_FUSION_TRACK_BASE_H_
#define HOLO_PERCEPTION_FUSION_TRACK_BASE_H_

#include <memory>

#include <holo/common/sensor_id.h>
#include <holo/core/types.h>
#include <holo/perception/utils/obstacle_property.h>

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
 * @brief Track type
 *
 */
enum class TrackType : uint8_t
{
    UNKNOWN,
    FUSED,
    GENERAL,
    LIDAR,
    RADAR,
    USS,
    VISION,
};

/**
 * @brief Sensor measurement key, pair meaning <SensorId, ObstacleId>
 *
 */
using SensorMeasurementKey = std::pair<holo::common::SensorId, uint32_t>;

/**
 * @brief Track base class, all other track should derive from this class
 *
 */
class TrackBase
{
public:
    using SensorId             = holo::common::SensorId;
    using ObstaclePropertyType = ObstacleProperty<float32_t>;

    /**
     * @brief Construct a new Track Base object
     *
     * @param track_type track type
     */
    TrackBase(TrackType const track_type) noexcept : track_type_(track_type), obstacle_id_(0U)
    {
    }

    /**
     * @brief Destroy the Track Base object
     *
     */
    virtual ~TrackBase() noexcept
    {
    }

    /**
     * @brief Set the Track Type
     *
     * @param track_type track type
     */
    void SetTrackType(TrackType const track_type) noexcept
    {
        track_type_ = track_type;
    }

    /**
     * @brief Get the Track Type
     *
     * @return TrackType track type of this track
     */
    TrackType GetTrackType() const noexcept
    {
        return track_type_;
    }

    /**
     * @brief Get the Sensor Id object
     *
     * @return SensorId sensor id
     */
    SensorId GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief Get the Obstacle Id object
     *
     * @return uint32_t obstacle id
     */
    uint32_t GetObstacleId() const noexcept
    {
        return obstacle_id_;
    }

    /**
     * @brief Get the Sensor Measurement Key object
     *
     * @return SensorMeasurementKey sensor measurement key
     */
    SensorMeasurementKey GetSensorMeasurementKey() const noexcept
    {
        return SensorMeasurementKey(sensor_id_, obstacle_id_);
    }

    /**
     * @brief Get the Obstacle Property
     *
     * @return ObstaclePropertyType const& obstacle property
     */
    ObstaclePropertyType const& GetObstacleProperty() const noexcept
    {
        return obstacle_property_;
    }

protected:
    TrackType            track_type_;
    SensorId             sensor_id_;
    uint32_t             obstacle_id_;
    ObstaclePropertyType obstacle_property_;
};

using TrackBasePtr = std::shared_ptr<TrackBase>;

template <typename DerivedTrackType>
std::shared_ptr<DerivedTrackType> GetDerivedTrack(TrackBasePtr const base_track)
{
    return std::dynamic_pointer_cast<DerivedTrackType>(base_track);
}

/**
 * @}
 */
}  // namespace perception
}  // namespace holo

#endif
