/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file obstacle_list.h
 * @brief This header file defines ObstaclePtrListT.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-11-27
 */

#ifndef HOLO_OBSTACLE_DETAILS_OBSTACLE_PTR_LIST_H_
#define HOLO_OBSTACLE_DETAILS_OBSTACLE_PTR_LIST_H_

#include <array>
#include <memory>

#include <holo/common/classification.h>
#include <holo/common/perception_ability.h>
#include <holo/common/sensor_id.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_base.h>
#include <holo/obstacle/obstacle_general.h>
#include <holo/obstacle/obstacle_lidar.h>
#include <holo/obstacle/obstacle_radar.h>
#include <holo/obstacle/obstacle_uss.h>
#include <holo/obstacle/obstacle_vision.h>
#include <holo/serialization/serialization.h>

namespace holo
{
// Common capacity for different type obstacle list
[[deprecated]] const static uint32_t GENERAL_OBSTACLE_LIST_COMMON_CAPACITY =
    256U;  ///< Common capacity for general obstacle list
[[deprecated]] const static uint32_t LIDAR_OBSTACLE_LIST_COMMON_CAPACITY =
    512U;  ///< Common capacity for lidar obstacle list
[[deprecated]] const static uint32_t RADAR_OBSTACLE_LIST_COMMON_CAPACITY =
    512U;  ///< Common capacity for radar obstacle list
[[deprecated]] const static uint32_t USS_OBSTACLE_LIST_COMMON_CAPACITY =
    128U;  ///< Common capacity for uss obstacle list
[[deprecated]] const static uint32_t VISION_OBSTACLE_LIST_COMMON_CAPACITY =
    128U;  ///< Common capacity for vision obstacle list

namespace obstacle
{
// Common capacity for different type obstacle list
const static uint32_t GENERAL_OBSTACLE_LIST_COMMON_CAPACITY = 256U;  ///< Common capacity for general obstacle list
const static uint32_t LIDAR_OBSTACLE_LIST_COMMON_CAPACITY   = 512U;  ///< Common capacity for lidar obstacle list
const static uint32_t RADAR_OBSTACLE_LIST_COMMON_CAPACITY   = 512U;  ///< Common capacity for radar obstacle list
const static uint32_t USS_OBSTACLE_LIST_COMMON_CAPACITY     = 128U;  ///< Common capacity for uss obstacle list
const static uint32_t VISION_OBSTACLE_LIST_COMMON_CAPACITY  = 128U;  ///< Common capacity for vision obstacle list

namespace details
{
/**
 * @addtogroup obstacle
 *
 * @{
 */

/**
 * @brief This class holds list of obstacles and a message header.
 *
 * @tparam T Obstacle type
 * @tparam CAPACITY Capacity of array to store obstacles
 */
template <typename T, std::size_t CAPACITY>
class ObstaclePtrListT
{
public:
    using Coordinate        = holo::common::Coordinate;
    using Timestamp         = holo::common::Timestamp;
    using PerceptionAbility = holo::common::PerceptionAbility;
    using SensorId          = holo::common::SensorId;

    /**
     * @brief Default constructor
     */
    ObstaclePtrListT()
      : timestamp_{}
      , coordinate_{Coordinate(Coordinate::UNKNOWN)}
      , sensor_id_{}
      , size_{0U}
      , perception_ability_{0U}
      , obstacle_list_{}
    {
    }

    /**
     * @brief Constructor with params
     *
     * @param timestamp time stamp
     * @param coord coordinate
     * @param sensor_id from which sensor
     * @param size number of obstacles in array
     * @param perception_ability perception ability
     * @param obstacle_list obstacles ptr
     */
    ObstaclePtrListT(const Timestamp& timestamp, const Coordinate coord, const SensorId& sensor_id, const uint32_t size,
                     const PerceptionAbility&                        perception_ability,
                     const std::array<std::shared_ptr<T>, CAPACITY>& obstacle_list)
      : timestamp_(timestamp)
      , coordinate_(coord)
      , sensor_id_(sensor_id)
      , size_(size)
      , perception_ability_(perception_ability)
      , obstacle_list_(obstacle_list)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other ObstaclePtrListT
     */
    ObstaclePtrListT(const ObstaclePtrListT& other)
      : timestamp_(other.timestamp_)
      , coordinate_(other.coordinate_)
      , sensor_id_(other.sensor_id_)
      , size_(other.size_)
      , perception_ability_(other.perception_ability_)
      , obstacle_list_(other.obstacle_list_)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other ObstaclePtrListT
     */
    ObstaclePtrListT(ObstaclePtrListT&& other)
      : timestamp_(other.timestamp_)
      , coordinate_(other.coordinate_)
      , sensor_id_(other.sensor_id_)
      , size_(other.size_)
      , perception_ability_(other.perception_ability_)
      , obstacle_list_(std::move(other.obstacle_list_))
    {
    }

    /**
     * @brief Copy assignment
     *
     * @param other ObstaclePtrListT
     */
    ObstaclePtrListT& operator=(const ObstaclePtrListT& other)
    {
        if (&other != this)
        {
            this->timestamp_          = other.timestamp_;
            this->coordinate_         = other.coordinate_;
            this->sensor_id_          = other.sensor_id_;
            this->size_               = other.size_;
            this->perception_ability_ = other.perception_ability_;
            this->obstacle_list_      = other.obstacle_list_;
        }

        return *this;
    }

    /**
     * @brief Move assignment
     *
     * @param other ObstaclePtrListT
     */
    ObstaclePtrListT& operator=(ObstaclePtrListT&& other)
    {
        if (&other != this)
        {
            this->timestamp_          = other.timestamp_;
            this->coordinate_         = other.coordinate_;
            this->sensor_id_          = other.sensor_id_;
            this->size_               = other.size_;
            this->perception_ability_ = other.perception_ability_;
            this->obstacle_list_      = std::move(other.obstacle_list_);
        }

        return *this;
    }

    /**
     * @brief Get timestamp
     *
     * @return timestamp of obstacle list
     */
    const Timestamp& GetTimestamp() const
    {
        return timestamp_;
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp timestmap of obstacle list
     */
    void SetTimestamp(const Timestamp& timestamp)
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief Get coordinate of obstacles in list
     *
     * @return coordinate
     */
    Coordinate GetCoordinate() const
    {
        return coordinate_;
    }

    /**
     * @brief Set coordinate of obstacles in list
     *
     * @param coord coordinate
     */
    void SetCoordinate(const Coordinate coord)
    {
        this->coordinate_ = coord;
    }

    /**
     * @brief Get information of obstacle from which sensor
     *
     * @return sensor id
     */
    const SensorId& GetSensorId() const
    {
        return sensor_id_;
    }

    /**
     * @brief Set sensor id
     *
     * @param sensor_id sensor id
     */
    void SetSensorId(const SensorId& sensor_id)
    {
        this->sensor_id_ = sensor_id;
    }

    /**
     * @brief Get real number of obstacles in array
     *
     * @return size
     */
    uint32_t GetSize() const
    {
        return size_;
    }

    /**
     * @brief Set real number of obstacles in array
     *
     * @param size number of obstacles
     */
    void SetSize(const uint32_t size)
    {
        this->size_ = size;
    }

    /**
     * @brief Set perception ability
     *
     */
    void SetPerceptionAbility(const PerceptionAbility& perception_ability)
    {
        this->perception_ability_ = perception_ability;
    }

    /**
     * @brief Get perception ability
     *
     * @return perception ability
     */
    const PerceptionAbility GetPerceptionAbility() const
    {
        return perception_ability_;
    }

    /**
     * @brief Get obstacle ptr list
     *
     * @return obstacle ptr list
     */
    const std::array<std::shared_ptr<T>, CAPACITY>& GetObstacleList() const
    {
        return obstacle_list_;
    }

    // std::array<std::shared_ptr<T>, size>& GetObstacleListNonConstRef();

    /**
     * @brief Get obstacle ptr list non const reference
     *
     * @return obstacle ptr list
     */
    std::array<std::shared_ptr<T>, CAPACITY>& GetObstacleList()
    {
        return obstacle_list_;
    }

    /**
     * @brief Set obstacle ptr list
     *
     * @param obstacle_list obstacle ptr list
     */
    void SetObstacleList(const std::array<std::shared_ptr<T>, CAPACITY>& obstacle_list)
    {
        this->obstacle_list_ = obstacle_list;
    }

    /**
     * @brief Set obstacle ptr list with rvalue
     *
     * @param obstacle_list obstacle list
     */
    void SetObstacleList(std::array<std::shared_ptr<T>, CAPACITY>&& obstacle_list)
    {
        if (&this->obstacle_list_ != &obstacle_list)
        {
            this->obstacle_list_ = std::move(obstacle_list);
        }
    }

    /**
     * @brief Get the Capacity of obstacle ptr list
     *
     * @return capacity
     */
    std::size_t GetCapacity() const
    {
        return CAPACITY;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        size_t aligned_size = timestamp_.GetSerializedSize<ALIGN>() +
                              holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_),
                                                                         static_cast<uint32_t>(sensor_id_), size_,
                                                                         static_cast<uint32_t>(perception_ability_));
        for (size_t i = 0U; i < size_; ++i)
        {
            aligned_size += obstacle_list_[i]->template GetSerializedSize<ALIGN>();
        }
        return aligned_size;
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
        serializer << timestamp_ << static_cast<uint32_t>(coordinate_) << static_cast<uint32_t>(sensor_id_) << size_
                   << static_cast<uint32_t>(perception_ability_);
        for (uint32_t i = 0; i < size_; i++)
        {
            serializer << *(obstacle_list_[i]);
        }
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
        uint32_t                                 cur_coord          = 0U;
        uint32_t                                 sensor_id          = 0U;
        uint32_t                                 perception_ability = 0U;
        std::array<std::shared_ptr<T>, CAPACITY> cur_arr_obstacle;
        deserializer >> timestamp_ >> cur_coord >> sensor_id >> size_ >> perception_ability;
        for (uint32_t i = 0U; i < size_; ++i)
        {
            std::shared_ptr<T> ptr_obstacle = std::make_shared<T>();
            deserializer >> *(ptr_obstacle);
            cur_arr_obstacle[i] = ptr_obstacle;
        }
        deserializer >> holo::serialization::align;
        coordinate_         = static_cast<Coordinate>(cur_coord);
        sensor_id_          = static_cast<SensorId>(sensor_id);
        perception_ability_ = static_cast<PerceptionAbility>(perception_ability);
        SetObstacleList(std::move(cur_arr_obstacle));
    }

private:
    Timestamp                                timestamp_;
    Coordinate                               coordinate_;
    SensorId                                 sensor_id_;
    uint32_t                                 size_;
    PerceptionAbility                        perception_ability_;
    std::array<std::shared_ptr<T>, CAPACITY> obstacle_list_;
};

/**
 * @}
 */

}  // namespace details
}  // namespace obstacle
}  // namespace holo

#endif
