/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_type.h
 * @brief Common definitions for road.
 * @author lisong@holomatic.com
 * @date "2020-08-13"
 */

#ifndef HOLO_COMMON_ROAD_TYPE_H_
#define HOLO_COMMON_ROAD_TYPE_H_

#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 */

/**
 * @brief Types and tags of road.
 *
 * @deprecated Use holo::common::RoadCategory instead
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnxymWmsPSdPBdcnEQfe362b
 *
 * @details A road type value is consist of two parts.
 * @verbatim
 * |-------------------------4 Bytes/32 Bits--------------------------|
 * |            8 Bits           |              24 Bits               |
 * |          Road type          |             Road tags              |
 * @endverbatim
 *
 * Road type: road type is exclusive, numbers for each type as follow:
 *     UNKNOWN: 0
 *     MAINROAD: 1
 *     RAMP: 2
 *
 * Road tags: road tags can coexist, each bit as flag for each tag:
 * |----------------------------24 Bits----------------------------|
 * |···················································1     1     |
 * |                                                  TOLL TUNNEL  |
 *
 */
class [[deprecated]] RoadType
{
public:
    /**
     * @brief Default constructer
     */
    RoadType() : tags_(0U), type_(0U)
    {
    }

    /**
     * @brief Constructer with parameters
     *
     * @param[in] value A holo::uint32_t value
     */
    explicit RoadType(holo::uint32_t const value) : tags_(value), type_(value >> TAGS_OCCUPIED_)
    {
    }

    /**
     * @brief Check if road type is UNKNOWN.
     *
     * @return True if is UNKNOWN.
     * @return False if is not.
     */
    holo::bool_t IsTypeUnknown() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::UNKNOWN);
    }

    /**
     * @brief Set road type to UNKNOWN.
     *
     * @return Nothing.
     */
    void SetTypeUnknown() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::UNKNOWN);
    }

    /**
     * @brief Check if road type is MAINROAD.
     *
     * @return True if is MAINROAD.
     * @return False if is not.
     */
    holo::bool_t IsTypeMainRoad() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::MAINROAD);
    }

    /**
     * @brief Set road type to MAINROAD.
     *
     * @return Nothing.
     */
    void SetTypeMainRoad() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::MAINROAD);
    }

    /**
     * @brief Check if road type is RAMP.
     *
     * @return True if is RAMP.
     * @return False if is not.
     */
    holo::bool_t IsTypeRamp() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::RAMP);
    }

    /**
     * @brief Set road type to RAMP.
     *
     * @return Nothing.
     */
    void SetTypeRamp() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::RAMP);
    }

    /**
     * @brief Check if has TUNNEL tag.
     *
     * @return True if has.
     * @return False if not.
     */
    holo::bool_t HasTagTunnel() const noexcept
    {
        return (tags_ & static_cast<holo::uint32_t>(Tag::TUNNEL)) == static_cast<holo::uint32_t>(Tag::TUNNEL);
    }

    /**
     * @brief Set TUNNEL tag.
     *
     * @return Nothing.
     */
    void SetTagTunnel() noexcept
    {
        tags_ |= static_cast<holo::uint32_t>(Tag::TUNNEL);
    }

    /**
     * @brief Reset TUNNEL tag.
     *
     * @return Nothing.
     */
    void ResetTagTunnel() noexcept
    {
        tags_ = static_cast<holo::uint32_t>(tags_) & ~static_cast<holo::uint32_t>(Tag::TUNNEL);
    }

    /**
     * @brief Check if has TOLL tag.
     *
     * @return True if has.
     * @return False if not.
     */
    holo::bool_t HasTagToll() const noexcept
    {
        return (tags_ & static_cast<holo::uint32_t>(Tag::TOLL)) == static_cast<holo::uint32_t>(Tag::TOLL);
    }

    /**
     * @brief Set TOLL tag.
     *
     * @return Nothing.
     */
    void SetTagToll() noexcept
    {
        tags_ |= static_cast<holo::uint32_t>(Tag::TOLL);
    }

    /**
     * @brief Reset TOLL tag to false
     *
     * @return Nothing.
     */
    void ResetTagToll() noexcept
    {
        tags_ = static_cast<holo::uint32_t>(tags_) & ~static_cast<holo::uint32_t>(Tag::TOLL);
    }

    /**
     * @brief Get holo::uint32_t value of road type.
     *
     * @return A holo::uint32_t value.
     */
    holo::uint32_t GetValue() const noexcept
    {
        return static_cast<holo::uint32_t>(tags_ | ((holo::uint32_t)type_ << TAGS_OCCUPIED_));
    }

    /**
     * @brief Set road type value.
     *
     * @param[in] value A holo::uint32_t value.
     * @return Nothing.
     */
    void SetValue(holo::uint32_t const value) noexcept
    {
        tags_ = value;
        type_ = (value >> (TAGS_OCCUPIED_));
    }

    /**
     * @brief == operator.
     *
     * @param [in] other A RoadType object
     * @return True if equal.
     * @return False if not equal.
     */
    holo::bool_t operator==(RoadType const& other) const noexcept
    {
        return (this->tags_ == other.tags_) && (this->type_ == other.type_);
    }

    /**
     * @brief RoadType object to uint32 value cast operator overloading.
     *
     * @return A holo::uint32_t value stores the meta data of RoadType object.
     */
    explicit operator holo::uint32_t() const noexcept
    {
        return GetValue();
    }

    /**
     * @brief Get required buffer size to serialize this object
     *
     * @tparam ALIGNMENT Byte alignment
     *
     * @return Required buffer size
     */
    template <size_t ALIGNMENT = 4U>
    std::size_t GetSerializedSize() const noexcept
    {
        return sizeof(RoadType);
    }

    template <typename S>
    void Serialize(S & serializer) const
    {
        serializer << this->GetValue();
    }

    template <typename D>
    void Deserialize(D & deserializer)
    {
        holo::uint32_t value = 0U;
        deserializer >> value;
        this->SetValue(value);
    }

private:
    /**
     * @brief Road types.
     */
    enum class Type : holo::uint8_t
    {
        UNKNOWN  = 0U,  ///< Unknown type
        MAINROAD = 1U,  ///< Main road
        RAMP     = 2U   ///< Ramp
    };

    /**
     * @brief Road tags.
     */
    enum class Tag : holo::uint32_t
    {
        TUNNEL = 1 << 0U,  ///< Tunnel
        TOLL   = 1 << 1U   ///< Toll
    };

    static constexpr holo::uint8_t TAGS_OCCUPIED_ = 24U;  ///< Size of road tag flags occupied in shared uint32 value.
    static constexpr holo::uint8_t TYPE_OCCUPIED_ = 8U;   ///< Size of road type occupied in shared uint32 value.

    holo::uint32_t tags_ : TAGS_OCCUPIED_;  ///< Road tags.
    holo::uint32_t type_ : TYPE_OCCUPIED_;  ///< Road type.
};                                          // end for RoadType

/**
 * @brief Types of lane
 *
 * @deprecated Use holo::common::LaneCategory instead
 * @details A lane type value is consist of two parts.
 * @verbatim
 * |-------------------------4 Bytes/32 Bits--------------------------|
 * |            8 Bits           |              24 Bits               |
 * |          Lane type          |             Lane tags              |
 * @endverbatim
 *
 * Lane type: lane type is exclusive, numbers for each type as follow:
 *     UNKNOWN: 0
 *     REGULAR: 1
 *     ACCELERATION: 2
 *     DECELERATION: 3
 */
class [[deprecated]] LaneType
{
public:
    /**
     * @brief Constructer
     */
    LaneType() : tags_(0U), type_(0U)
    {
    }

    /**
     * @brief Constructer with parameters
     *
     * @param [in] value A holo::uint32_t value
     */
    explicit LaneType(holo::uint32_t const value) : tags_(value), type_(value >> TAGS_OCCUPIED_)
    {
    }

    /**
     * @brief Get holo::uint32_t value of lane type.
     *
     * @return A holo::uint32_t value.
     */
    holo::uint32_t GetValue() const noexcept
    {
        return static_cast<holo::uint32_t>(tags_ | ((holo::uint32_t)type_ << TAGS_OCCUPIED_));
    }

    /**
     * @brief Set lane type value.
     *
     * @param[in] value A holo::uint32_t value.
     * @return Nothing.
     */
    void SetValue(holo::uint32_t const value) noexcept
    {
        tags_ = value;
        type_ = (value >> (TAGS_OCCUPIED_));
    }

    /**
     * @brief == operator.
     *
     * @param [in] other A LaneType object
     *
     * @return True if equal.
     * @return False if not equal.
     */
    holo::bool_t operator==(LaneType const& other) const noexcept
    {
        return (this->tags_ == other.tags_) && (this->type_ == other.type_);
    }

    /**
     * @brief LaneType object to uint32_t value cast operator overloading.
     *
     * @return A holo::uint32_t value stores the meta data of LaneType object.
     */
    explicit operator holo::uint32_t() const noexcept
    {
        return GetValue();
    }

    /**
     * @brief Check if lane type is UNKNOWN.
     *
     * @return True if is UNKNOWN.
     * @return False if is not.
     */
    holo::bool_t IsTypeUnknown() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::UNKNOWN);
    }

    /**
     * @brief Set lane type to UNKNOWN.
     *
     * @return Nothing.
     */
    void SetTypeUnknown() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::UNKNOWN);
    }

    /**
     * @brief Check if lane type is REGULAR.
     *
     * @return True if is REGULAR.
     * @return False if is not.
     */
    holo::bool_t IsTypeRegular() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::REGULAR);
    }

    /**
     * @brief Set lane type to REGULAR.
     *
     * @return Nothing.
     */
    void SetTypeRegular() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::REGULAR);
    }

    /**
     * @brief Check if lane type is ACCELERATION.
     *
     * @return True if is ACCELERATION.
     * @return False if is not.
     */
    holo::bool_t IsTypeAcceleration() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::ACCELERATION);
    }

    /**
     * @brief Set lane type to ACCELERATION.
     *
     * @return Nothing.
     */
    void SetTypeAcceleration() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::ACCELERATION);
    }

    /**
     * @brief Check if lane type is DECELERATION.
     *
     * @return True if is DECELERATION.
     * @return False if is not.
     */
    holo::bool_t IsTypeDeceleration() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::DECELERATION);
    }

    /**
     * @brief Set lane type to DECELERATION.
     *
     * @return Nothing.
     */
    void SetTypeDeceleration() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::DECELERATION);
    }

    /**
     * @brief Check if lane type is EMERGENCY.
     *
     * @return True if is emergency lane.
     * @return False if is not.
     */
    holo::bool_t IsTypeEmergency() const noexcept
    {
        return type_ == static_cast<holo::uint32_t>(Type::EMERGENCY);
    }

    /**
     * @brief Set lane type to EMERGENCY.
     */
    void SetTypeEmergency() noexcept
    {
        type_ = static_cast<holo::uint32_t>(Type::EMERGENCY);
    }

    template <size_t ALIGN = 4U>
    std::size_t GetSerializedSize() const noexcept
    {
        return sizeof(LaneType);
    }

    template <typename S>
    void Serialize(S & serializer) const
    {
        serializer << GetValue();
    }

    template <typename D>
    void Deserialize(D & deserializer)
    {
        holo::uint32_t value = 0U;
        deserializer >> value;
        this->SetValue(value);
    }

private:
    /**
     * @brief Types for Lane
     */
    enum class Type : holo::uint8_t
    {
        UNKNOWN      = 0U,  ///< Unknown type
        REGULAR      = 1U,  ///< Regular lane
        ACCELERATION = 2U,  ///< Acceleration lane
        DECELERATION = 3U,  ///< Deceleration lane
        EMERGENCY    = 4U,  ///< Emergency lane
    };

    static holo::uint8_t const TAGS_OCCUPIED_ = 24U;  ///< Size of lane tag flags occupied in shared uint32 value.
    static holo::uint8_t const TYPE_OCCUPIED_ = 8U;   ///< Size of lane type occupied in shared uint32 value.

    holo::uint32_t tags_ : TAGS_OCCUPIED_;  ///< Lane tags.
    holo::uint32_t type_ : TYPE_OCCUPIED_;  ///< Lane type.
};

/**
 * @}
 */

}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_ROAD_TYPE_H_ */
