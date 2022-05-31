/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file road_category.h
 * @brief Common definitions for road.
 * @author lisong@holomatic.com
 * @date "2021-12-10"
 */

#ifndef HOLO_COMMON_ROAD_CATEGORY_H_
#define HOLO_COMMON_ROAD_CATEGORY_H_

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
 * @brief Category and tags of road.
 * @ref Reference to: https://holomatic.feishu.cn/docs/doccnxymWmsPSdPBdcnEQfe362b
 *
 * @details A road category value is consist of two parts.
 * @verbatim
 * |----------------------------4 Bytes/32 Bits---------------------------|
 * |              8 Bits             |              24 Bits               |
 * |          Road category          |             Road tags              |
 * @endverbatim
 *
 * Road category: road category is exclusive, numbers for each category as follow:
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
class RoadCategory
{
public:
    /**
     * @brief Default constructer
     */
    RoadCategory() : tags_(0U), category_(0U)
    {
    }

    /**
     * @brief Constructer with parameters
     *
     * @param[in] value A holo::uint32_t value
     */
    explicit RoadCategory(holo::uint32_t const value) : tags_(value), category_(value >> TAGS_OCCUPIED_)
    {
    }

    /**
     * @brief Check if road category is UNKNOWN.
     *
     * @return True if is UNKNOWN.
     * @return False if is not.
     */
    holo::bool_t IsCategoryUnknown() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::UNKNOWN);
    }

    /**
     * @brief Set road category to UNKNOWN.
     *
     * @return Nothing.
     */
    void SetCategoryUnknown() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::UNKNOWN);
    }

    /**
     * @brief Check if road category is MAINROAD.
     *
     * @return True if is MAINROAD.
     * @return False if is not.
     */
    holo::bool_t IsCategoryMainRoad() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::MAINROAD);
    }

    /**
     * @brief Set road category to MAINROAD.
     *
     * @return Nothing.
     */
    void SetCategoryMainRoad() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::MAINROAD);
    }

    /**
     * @brief Check if road category is RAMP.
     *
     * @return True if is RAMP.
     * @return False if is not.
     */
    holo::bool_t IsCategoryRamp() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::RAMP);
    }

    /**
     * @brief Set road category to RAMP.
     *
     * @return Nothing.
     */
    void SetCategoryRamp() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::RAMP);
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
     * @brief Get holo::uint32_t value of road category.
     *
     * @return A holo::uint32_t value.
     */
    holo::uint32_t GetValue() const noexcept
    {
        return static_cast<holo::uint32_t>(tags_ | ((holo::uint32_t)category_ << TAGS_OCCUPIED_));
    }

    /**
     * @brief Set road category value.
     *
     * @param[in] value A holo::uint32_t value.
     * @return Nothing.
     */
    void SetValue(holo::uint32_t const value) noexcept
    {
        tags_     = value;
        category_ = (value >> (TAGS_OCCUPIED_));
    }

    /**
     * @brief == operator.
     *
     * @param [in] other A RoadCategory object
     * @return True if equal.
     * @return False if not equal.
     */
    holo::bool_t operator==(RoadCategory const& other) const noexcept
    {
        return (this->tags_ == other.tags_) && (this->category_ == other.category_);
    }

    /**
     * @brief RoadCategory object to uint32 value cast operator overloading.
     *
     * @return A holo::uint32_t value stores the meta data of RoadCategory object.
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
        return sizeof(RoadCategory);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << this->GetValue();
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint32_t value = 0U;
        deserializer >> value;
        this->SetValue(value);
    }

private:
    /**
     * @brief Road category.
     */
    enum class Category : holo::uint8_t
    {
        UNKNOWN  = 0U,  ///< Unknown category
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
    static constexpr holo::uint8_t CATEGORY_OCCUPIED_ = 8U;  ///< Size of road category occupied in shared uint32 value.

    holo::uint32_t tags_ : TAGS_OCCUPIED_;          ///< Road tags.
    holo::uint32_t category_ : CATEGORY_OCCUPIED_;  ///< Road category.
};                                                  // end for RoadCategory

/**
 * @brief category of lane
 *
 * @details A lane category value is consist of two parts.
 * @verbatim
 * |---------------------------4 Bytes/32 Bits----------------------------|
 * |              8 Bits             |              24 Bits               |
 * |          Lane category          |             Lane tags              |
 * @endverbatim
 *
 * Lane category: lane category is exclusive, numbers for each category as follow:
 *     UNKNOWN: 0
 *     REGULAR: 1
 *     ACCELERATION: 2
 *     DECELERATION: 3
 */
class LaneCategory
{
public:
    /**
     * @brief Constructer
     */
    LaneCategory() : tags_(0U), category_(0U)
    {
    }

    /**
     * @brief Constructer with parameters
     *
     * @param [in] value A holo::uint32_t value
     */
    explicit LaneCategory(holo::uint32_t const value) : tags_(value), category_(value >> TAGS_OCCUPIED_)
    {
    }

    /**
     * @brief Get holo::uint32_t value of lane category.
     *
     * @return A holo::uint32_t value.
     */
    holo::uint32_t GetValue() const noexcept
    {
        return static_cast<holo::uint32_t>(tags_ | ((holo::uint32_t)category_ << TAGS_OCCUPIED_));
    }

    /**
     * @brief Set lane category value.
     *
     * @param[in] value A holo::uint32_t value.
     * @return Nothing.
     */
    void SetValue(holo::uint32_t const value) noexcept
    {
        tags_     = value;
        category_ = (value >> (TAGS_OCCUPIED_));
    }

    /**
     * @brief == operator.
     *
     * @param [in] other A LaneCategory object
     *
     * @return True if equal.
     * @return False if not equal.
     */
    holo::bool_t operator==(LaneCategory const& other) const noexcept
    {
        return (this->tags_ == other.tags_) && (this->category_ == other.category_);
    }

    /**
     * @brief LaneCategory object to uint32_t value cast operator overloading.
     *
     * @return A holo::uint32_t value stores the meta data of LaneCategory object.
     */
    explicit operator holo::uint32_t() const noexcept
    {
        return GetValue();
    }

    /**
     * @brief Check if lane category is UNKNOWN.
     *
     * @return True if is UNKNOWN.
     * @return False if is not.
     */
    holo::bool_t IsCategoryUnknown() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::UNKNOWN);
    }

    /**
     * @brief Set lane category to UNKNOWN.
     *
     * @return Nothing.
     */
    void SetCategoryUnknown() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::UNKNOWN);
    }

    /**
     * @brief Check if lane category is REGULAR.
     *
     * @return True if is REGULAR.
     * @return False if is not.
     */
    holo::bool_t IsCategoryRegular() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::REGULAR);
    }

    /**
     * @brief Set lane category to REGULAR.
     *
     * @return Nothing.
     */
    void SetCategoryRegular() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::REGULAR);
    }

    /**
     * @brief Check if lane category is ACCELERATION.
     *
     * @return True if is ACCELERATION.
     * @return False if is not.
     */
    holo::bool_t IsCategoryAcceleration() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::ACCELERATION);
    }

    /**
     * @brief Set lane category to ACCELERATION.
     *
     * @return Nothing.
     */
    void SetCategoryAcceleration() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::ACCELERATION);
    }

    /**
     * @brief Check if lane category is DECELERATION.
     *
     * @return True if is DECELERATION.
     * @return False if is not.
     */
    holo::bool_t IsCategoryDeceleration() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::DECELERATION);
    }

    /**
     * @brief Set lane category to DECELERATION.
     *
     * @return Nothing.
     */
    void SetCategoryDeceleration() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::DECELERATION);
    }

    /**
     * @brief Check if lane category is EMERGENCY.
     *
     * @return True if is emergency lane.
     * @return False if is not.
     */
    holo::bool_t IsCategoryEmergency() const noexcept
    {
        return category_ == static_cast<holo::uint32_t>(Category::EMERGENCY);
    }

    /**
     * @brief Set lane category to EMERGENCY.
     */
    void SetCategoryEmergency() noexcept
    {
        category_ = static_cast<holo::uint32_t>(Category::EMERGENCY);
    }

    template <size_t ALIGN = 4U>
    std::size_t GetSerializedSize() const noexcept
    {
        return sizeof(LaneCategory);
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << GetValue();
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        holo::uint32_t value = 0U;
        deserializer >> value;
        this->SetValue(value);
    }

private:
    /**
     * @brief Category for Lane
     */
    enum class Category : holo::uint8_t
    {
        UNKNOWN      = 0U,  ///< Unknown category
        REGULAR      = 1U,  ///< Regular lane
        ACCELERATION = 2U,  ///< Acceleration lane
        DECELERATION = 3U,  ///< Deceleration lane
        EMERGENCY    = 4U,  ///< Emergency lane
    };

    static holo::uint8_t const TAGS_OCCUPIED_     = 24U;  ///< Size of lane tag flags occupied in shared uint32 value.
    static holo::uint8_t const CATEGORY_OCCUPIED_ = 8U;   ///< Size of lane category occupied in shared uint32 value.

    holo::uint32_t tags_ : TAGS_OCCUPIED_;          ///< Lane tags.
    holo::uint32_t category_ : CATEGORY_OCCUPIED_;  ///< Lane category.
};

/**
 * @}
 */

}  // namespace common
}  // namespace holo

#endif /* HOLO_COMMON_ROAD_CATEGORY_H_ */
