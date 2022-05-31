/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_scene.h
 * @brief This header file defines the lane_scene category.
 * @author tanghui(tanghui@holomaitc.com)
 * @date "2020-04-3"
 */

#ifndef HOLO_COMMON_LANE_SCENE_H_
#define HOLO_COMMON_LANE_SCENE_H_

#include <holo/common/timestamp.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
/**
 * @addtogroup common
 *
 * @{
 */
namespace common
{
/**
 * @brief This class defines the scene categories of lanes.
 *
 * @details lane scene object has 5 categories.
 * @verbatim
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +--------------------------------------------+-----+-----+----+
 * |RSV                                         |RIGHT|LEFT |LANE|
 * +--------------------------------------------+-----+-----+----+
 * @endverbatim
 *
 * RSV: Reserved.
 *
 * LANE: The lane in which ego car is.
 *
 * LEFT: The left lane of ego car.
 *
 * RIGHT: The right lane of ego car.
 */

class LaneScene
{
public:
    /**
     * @brief The basic categories of lane scene.
     *
     */
    enum class Type : uint8_t
    {
        UNKNOWN = 0X0,  ///< Unknown category
        FINE    = 0x1,  ///< Fine lane scene category
        WATER   = 0x2,  ///< Water lane scene category
        SNOW    = 0x3,  ///< Snow lane scene category
        ICED    = 0x4,  ///< Iced lane scene category
        MUD     = 0x5,  ///< Mud lane scene category

    };

    /**
     * @brief The basic data structure (three lanes).
     *
     */
    struct LaneGroup
    {
        uint32_t current : 3;
        uint32_t left : 3;
        uint32_t right : 3;
        uint32_t reserved : 23;
    };

    /**
     * @brief Construct a new LaneScene object.
     *
     */
    LaneScene() : timestamp_(0U, 0U), lane_group_{0u, 0u, 0u, 0u}
    {
    }

    /**
     * @brief Construct a new LaneScene object.
     *
     * @param timestamp Value to initialize LaneScene.
     * @param value Value to initialize LaneScene.
     *
     */
    LaneScene(const Timestamp& timestamp, uint32_t value) noexcept
    {
        timestamp_          = timestamp;
        lane_group_.current = value & 0x7;
        lane_group_.left    = (value >> 3) & 0x7;
        lane_group_.right   = (value >> 6) & 0x7;
    }

    /**
     * @brief Get timestamp of lane scene
     *
     * @return timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set time stamp of lane scene
     *
     * @param timestamp timestmap
     */
    void SetTimestamp(const Timestamp& timestamp) noexcept
    {
        this->timestamp_ = timestamp;
    }

    /**
     * @brief get all lane status in uint32.
     *
     * @return uint32_t type value.
     */
    holo::uint32_t GetValue() const noexcept
    {
        return static_cast<uint32_t>(lane_group_.right) << 6 | static_cast<uint32_t>(lane_group_.left) << 3 |
               static_cast<uint32_t>(lane_group_.current);
    }

    /**
     * @brief set all lane status from uint8.
     *
     * @param value uint32_t value.
     */
    void SetValue(uint32_t value) noexcept
    {
        lane_group_.current = value & 0x7;
        lane_group_.left    = (value >> 3) & 0x7;
        lane_group_.right   = (value >> 6) & 0x7;
    }

    /**
     * @brief Set the current status.
     *
     * @param value
     * UNKNOWN = 0X0,
     * FINE  = 0x1,
     * WATER = 0x2,
     * SNOW  = 0x3,
     * ICED  = 0x4,
     * MUD   = 0x5,
     */
    void SetCurrent(Type value) noexcept
    {
        lane_group_.current = static_cast<uint8_t>(value);
    }

    /**
     * @brief Set the left status.
     *
     * @param value
     * UNKNOWN = 0X0,
     * FINE  = 0x1,
     * WATER = 0x2,
     * SNOW  = 0x3,
     * ICED  = 0x4,
     * MUD   = 0x5,
     */
    void SetLeft(Type value) noexcept
    {
        lane_group_.left = static_cast<uint8_t>(value);
    }

    /**
     * @brief Set the right lane status.
     *
     * @param value
     * UNKNOWN = 0X0,
     * FINE  = 0x1,
     * WATER = 0x2,
     * SNOW  = 0x3,
     * ICED  = 0x4,
     * MUD   = 0x5,
     */
    void SetRight(Type value) noexcept
    {
        lane_group_.right = static_cast<uint8_t>(value);
    }

    /**
     * @brief Get the lane scene.
     *
     * @return Type
     * UNKNOWN = 0X0,
     * FINE  = 0x1,
     * WATER = 0x2,
     * SNOW  = 0x3,
     * ICED  = 0x4,
     * MUD   = 0x5,
     */
    Type GetCurrent() const noexcept
    {
        return static_cast<Type>(lane_group_.current);
    }

    /**
     * @brief Get the left lane scene.
     *
     * @return Type
     * UNKNOWN = 0X0,
     * FINE  = 0x1,
     * WATER = 0x2,
     * SNOW  = 0x3,
     * ICED  = 0x4,
     * MUD   = 0x5,
     */
    Type GetLeft() const noexcept
    {
        return static_cast<Type>(lane_group_.left);
    }

    /**
     * @brief Get the right lane scene.
     *
     * @return Type
     * UNKNOWN = 0X0,
     * FINE  = 0x1,
     * WATER = 0x2,
     * SNOW  = 0x3,
     * ICED  = 0x4,
     * MUD   = 0x5,
     */
    Type GetRight() const noexcept
    {
        return static_cast<Type>(lane_group_.right);
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
        uint32_t lane_group = 0;
        return timestamp_.GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(lane_group);
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
        /* serialize data */
        serializer << timestamp_ << GetValue() << holo::serialization::align;
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
        holo::uint32_t all_lane_scene;
        /* deserialize data */
        deserializer >> timestamp_ >> all_lane_scene >> holo::serialization::align;
        SetValue(all_lane_scene);
    }

private:
    Timestamp timestamp_;
    LaneGroup lane_group_;

};  // class LaneScene

}  // namespace common
/**
 *
 * @}
 */

}  // namespace holo

#endif  // !HOLO_COMMON_LANE_SCENE_H_
