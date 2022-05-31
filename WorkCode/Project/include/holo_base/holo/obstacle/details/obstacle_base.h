/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_base.h
 * @brief This header file defines ObstacleBaseT .
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-03
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_BASE_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_BASE_H_

#include <holo/common/classification.h>
#include <holo/common/coordinate.h>
#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/point3.h>
#include <holo/serialization/serialization.h>

using SensorId[[deprecated]] = holo::common::SensorId;

namespace holo
{
/**
 * @brief Obstacle contour points max number for array
 */
const static uint32_t OBSTACLE_MAX_NUM_CONTOUR_POINTS = 20;

namespace obstacle
{
namespace details
{
/**
 * @addtogroup obstacle
 *
 * @{
 */

/**
 * @brief Obstacle lane changing state.
 */
enum class CutInCutOut : uint8_t
{
    UNKNOWN = 0U,        //!< UNKNOWN
    HOST_CUT_IN_LEFT,    //!< Obstacle cut into host lane from left
    HOST_CUT_IN_RIGHT,   //!< Obstacle cut into host lane from right
    HOST_CUT_OUT_LEFT,   //!< Obstacle cut out of host lane from left
    HOST_CUT_OUT_RIGHT,  //!< Obstacle cut out of host lane from right
    NEXT_CUT_IN_LEFT,    //!< Obstacle cut into left lane from 2nd left lane.
    NEXT_CUT_IN_RIGHT,   //!< Obstacle cut into right lane from 2nd right lane.
    NEXT_CUT_OUT_LEFT,   //!< Obstacle cut out of 2nd left lane from left
    NEXT_CUT_OUT_RIGHT,  //!< Obstacle cut out of 2nd right lane from right
};

/**
 * @brief Obstacle motion status
 */
enum class MotionStatus : uint8_t
{
    UNKNOWN    = 0U,  //!< Obstacle that could not tell motion status
    MOVING     = 1U,  //!< Obstacle that is moving such as a moving vehicle
    STATIONARY = 2U,  //!< Obstacle that is not capable of moving such as cones
    ONCOMING   = 3U,  //!< Obstacle that is moving towards us such as a vehicle moving in opposite direction
    STOPPED    = 4U,  //!< Obstacle that is able to move but now is stopped such as vehicles stopped in bad traffic
    PARKED     = 5U,  //!< Obstacle that is able to move but now is stopped and would not move for long time
    CROSSING   = 6U,  //!< Obstalce that is moving cross us such as the vehicle at crossroad
};

/**
 * @brief Base class for all obstacles.
 *
 * @details Obstacle base class. Obstacle type from different sensor type must be derived from ObstacleBaseT.
 * ObstacleBaseT provide base property and interface for obstacles.
 *
 * @tparam Obstacle scalar. Now support float32_t or float64_t.
 *
 * @note The confidence of an obstacle must be scaled to 0~1.
 */
template <typename T>
class ObstacleBaseT
{
public:
    using Scalar         = T;
    using Point3Type     = holo::geometry::Point3T<Scalar>;
    using Coordinate     = holo::common::Coordinate;
    using Timestamp      = holo::common::Timestamp;
    using SensorId       = holo::common::SensorId;
    using Classification = holo::common::Classification;

    /**
     * @brief Constructor
     *
     * @details Constructor with no parameter. Will set obstacle message header to
     * default, track id to max uint32_t, sensor id to default.
     */
    ObstacleBaseT() noexcept
      : timestamp_{}
      , coordinate_{Coordinate::UNKNOWN}
      , obstacle_id_{0U}
      , sensor_id_{}
      , classification_{}
      , obstacle_exist_score_{0.0f}
      , position_{Point3Type::Zero()}
    {
    }

    /**
     * @brief Constructor with parameters
     *
     * @param timestamp obstacle time stamp
     * @param coord obstacle coordinate
     * @param obstacle_id obstacle uuid
     * @param sensor_id obstacle from which sensor
     * @param classification obstacle classification
     * @param obstacle_exist_score obstacle existence score
     * @param position obstacle position
     */
    ObstacleBaseT(const Timestamp& timestamp, const Coordinate coord, const uint32_t obstacle_id,
                  const SensorId& sensor_id, const Classification& classification, const float32_t obstacle_exist_score,
                  const Point3Type& position) noexcept
      : timestamp_(timestamp)
      , coordinate_(coord)
      , obstacle_id_(obstacle_id)
      , sensor_id_(sensor_id)
      , classification_(classification)
      , obstacle_exist_score_(obstacle_exist_score)
      , position_(position)
    {
    }

    /**
     * @brief Destructor
     */
    virtual ~ObstacleBaseT() noexcept
    {
    }

    /**
     * @brief Get timestamp of obstacle
     *
     * @return timestamp of obstacle
     */
    virtual const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp for obstacle
     *
     * @param timestamp timestamp of obstacle
     */
    virtual void SetTimestamp(const Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get obstacle coordinate
     *
     * @return coordinate of obstacle
     */
    virtual Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Set obstacle coordinate
     *
     * @param coord obstacle coordinate
     */
    virtual void SetCoordinate(const Coordinate coord) noexcept
    {
        this->coordinate_ = coord;
    }

    /**
     * @brief Get obstacle id
     *
     * @return obstacle id
     */
    virtual uint32_t GetObstacleId() const noexcept
    {
        return obstacle_id_;
    }

    /**
     * @brief Set obstacle id
     *
     * @param obstacle_id obstacle id
     */
    virtual void SetObstacleId(const uint32_t obstacle_id) noexcept
    {
        this->obstacle_id_ = obstacle_id;
    }

    /**
     * @brief Get which sensor obstacle come from
     *
     * @return sensor id of obstacle
     */
    virtual const SensorId& GetSensorId() const noexcept
    {
        return sensor_id_;
    }

    /**
     * @brief Set obstacle sensor id
     *
     * @param sensor_id obstacle sensor id
     */
    virtual void SetSensorId(const SensorId& sensor_id) noexcept
    {
        this->sensor_id_ = sensor_id;
    }

    /**
     * @brief Get obstacle classification
     *
     * @return classification of obstacle
     */
    virtual const Classification& GetClassification() const noexcept
    {
        return classification_;
    }

    /**
     * @brief Set obstacle classfication
     *
     * @param classification classification of obstacle
     */
    virtual void SetClassification(const Classification& classification) noexcept
    {
        this->classification_ = classification;
    }

    /**
     * @brief Get obstacle exist score
     *
     * @return obstacle exist score
     */
    virtual float32_t GetObstacleExistScore() const noexcept
    {
        return obstacle_exist_score_;
    }

    /**
     * @brief Set obstacle exist score
     *
     * @param obstacle_exist_score - obstacle existence score
     */
    virtual void SetObstacleExistScore(const float32_t obstacle_exist_score) noexcept
    {
        this->obstacle_exist_score_ = obstacle_exist_score;
    }

    /**
     * @brief Get position of obstacle.
     *
     * @return position.
     */
    virtual const Point3Type& GetPosition() const noexcept
    {
        return position_;
    }

    /**
     * @brief Set obstacle position
     *
     * @param position obstacle position
     */
    virtual void SetPosition(const Point3Type& position) noexcept
    {
        this->position_ = position;
    }

    /**
     * @brief serialize content to string
     *
     * @return serialized string
     */
    virtual std::string ToString() const noexcept
    {
        std::stringstream ss;
        ss << "ObstacleBaseT: ("
           << "timestamp_: " << this->timestamp_.ToString()
           << ", coordinate_: " << static_cast<uint32_t>(this->coordinate_) << ", obstacle_id_: " << this->obstacle_id_
           << ", sensor_id_: " << static_cast<uint32_t>(this->sensor_id_)
           << ", classification_: " << this->classification_.ToString()
           << ", obstacle_exist_score_: " << this->obstacle_exist_score_ << ", position_: " << this->position_ << ")"
           << std::endl;

        return ss.str();
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   static_cast<uint32_t>(coordinate_), obstacle_id_, static_cast<uint32_t>(sensor_id_),
                   static_cast<uint32_t>(classification_), obstacle_exist_score_) +
               position_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << static_cast<uint32_t>(coordinate_) << obstacle_id_
                   << static_cast<uint32_t>(sensor_id_) << static_cast<uint32_t>(classification_)
                   << obstacle_exist_score_ << position_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t cur_coord      = 0;
        uint32_t sensor_id      = 0;
        uint32_t classification = 0;
        deserializer >> timestamp_ >> cur_coord >> obstacle_id_ >> sensor_id >> classification >>
            obstacle_exist_score_ >> position_;
        coordinate_     = static_cast<Coordinate>(cur_coord);
        sensor_id_      = sensor_id;
        classification_ = classification;
    }

protected:
    Timestamp      timestamp_;
    Coordinate     coordinate_;
    uint32_t       obstacle_id_;
    SensorId       sensor_id_;
    Classification classification_;
    float32_t      obstacle_exist_score_;
    Point3Type     position_;
};

/**
 * @}
 */
}  // namespace details
}  // namespace obstacle
}  // namespace holo

#endif
