/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file perception_ability.h
 * @brief This header file defines .
 * @author sunzhenqiang(sunzhenqiang@holomaitc.com)
 * @date "2020-04-21"
 */

#ifndef HOLO_COMMON_PERCEPTION_ABILITY_H_
#define HOLO_COMMON_PERCEPTION_ABILITY_H_

#include <holo/log/hololog.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>

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
 * @brief This class defines the perception ability of different zone.
 *
 * @details Perception ability is consist of eight zone, and each zone has four level capabilities: HIGH, MIDDLE, LOW
 * and NONE.
 * @verbatim
 * * Perception ability zone:
 * |               |  Z5  |     Z2         |    |
 * |      Z7       |-----|-----------------|    |
 * |---------------| CAR>|Z9|   Z3         | Z1 |
 * |      Z8       |-----|-----------------|    |
 * |               |  Z6  |     Z4         |    |
 *
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +----------------------------------+--+--+--+--+--+--+--+--+--+
 * |                  RSV             |Z9|Z8|Z7|Z6|Z5|Z4|Z3|Z2|Z1|
 * +-------------------------------------------------------------+
 * @endverbatim
 *
 * RSV: Reserved.
 *
 * Z9: Zone9 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z8: Zone8 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z7: Zone7 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z6: Zone6 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z5: Zone5 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z4: Zone4 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z3: Zone3 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z2: Zone2 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 *
 * Z1: Zone1 perception ability, has four levels. 00-NONE, 01-LOW, 10-MIDDLE, 11-HIGH.
 */

class PerceptionAbility
{
public:
    /**
     * @brief Enumerate Perception Ability Level.
     *
     * @note Perception Ability Level is only 2-bit long, value range is [0, 4].
     */
    enum class PerceptionAbilityLevel : uint8_t
    {
        NONE   = 0x0,  ///< None perception ability
        LOW    = 0x1,  ///< Low level perception ability
        MIDDLE = 0x2,  ///< Middle level perception ability
        HIGH   = 0x3,  ///< High level perception ability
    };

    /**
     * @brief Construct a new Perception Ability object
     *
     */
    PerceptionAbility() noexcept
      : level_z1_(0U)
      , level_z2_(0U)
      , level_z3_(0U)
      , level_z4_(0U)
      , level_z5_(0U)
      , level_z6_(0U)
      , level_z7_(0U)
      , level_z8_(0U)
      , level_z9_(0U)
      , reserved_(0U)
    {
    }

    PerceptionAbility(uint32_t pa_z1, uint32_t pa_z2, uint32_t pa_z3, uint32_t pa_z4, uint32_t pa_z5, uint32_t pa_z6,
                      uint32_t pa_z7, uint32_t pa_z8, uint32_t pa_z9) noexcept
      : level_z1_(pa_z1)
      , level_z2_(pa_z2)
      , level_z3_(pa_z3)
      , level_z4_(pa_z4)
      , level_z5_(pa_z5)
      , level_z6_(pa_z6)
      , level_z7_(pa_z7)
      , level_z8_(pa_z8)
      , level_z9_(pa_z9)
      , reserved_(0U)
    {
    }

    /**
     * @brief Construct a new Perception Ability object
     *
     * @param value Value to initialize PerceptionAbility.
     */
    PerceptionAbility(uint32_t value) noexcept
      : level_z1_(value & 0x3)
      , level_z2_((value >> 2U) & 0x3)
      , level_z3_((value >> 4U) & 0x3)
      , level_z4_((value >> 6U) & 0x3)
      , level_z5_((value >> 8U) & 0x3)
      , level_z6_((value >> 10U) & 0x3)
      , level_z7_((value >> 12U) & 0x3)
      , level_z8_((value >> 14U) & 0x3)
      , level_z9_((value >> 16U) & 0x3)
      , reserved_(0U)
    {
    }

    /**
     * @brief Assign operator. Enable initialize from uint32_t.
     *
     * @param value Value to initialize PerceptionAbility.
     * @return Reference to PerceptionAbility object.
     */
    PerceptionAbility& operator=(uint32_t value) noexcept
    {
        level_z1_ = value & 0x3;
        level_z2_ = (value >> 2U) & 0x3;
        level_z3_ = (value >> 4U) & 0x3;
        level_z4_ = (value >> 6U) & 0x3;
        level_z5_ = (value >> 8U) & 0x3;
        level_z6_ = (value >> 10U) & 0x3;
        level_z7_ = (value >> 12U) & 0x3;
        level_z8_ = (value >> 14U) & 0x3;
        level_z9_ = (value >> 16U) & 0x3;
        reserved_ = 0U;
        return *this;
    }

    /**
     * @brief Merge two perception ability
     *
     * @param perception_ability
     * @return merged perception ability
     */
    PerceptionAbility& Merge(PerceptionAbility const& perception_ability)
    {
        uint32_t value = perception_ability.GetZoneAbility();
        level_z1_      = mergeLevel(level_z1_, (value & 0x3));
        level_z2_      = mergeLevel(level_z2_, ((value >> 2U) & 0x3));
        level_z3_      = mergeLevel(level_z3_, ((value >> 4U) & 0x3));
        level_z4_      = mergeLevel(level_z4_, ((value >> 6U) & 0x3));
        level_z5_      = mergeLevel(level_z5_, ((value >> 8U) & 0x3));
        level_z6_      = mergeLevel(level_z6_, ((value >> 10U) & 0x3));
        level_z7_      = mergeLevel(level_z7_, ((value >> 12U) & 0x3));
        level_z8_      = mergeLevel(level_z8_, ((value >> 14U) & 0x3));
        level_z9_      = mergeLevel(level_z9_, ((value >> 16U) & 0x3));
        return *this;
    }

    /**
     * @brief Cast operator. Enable cast to uint32_t type.
     *
     * @return uint32_t type value.
     */
    operator uint32_t() const noexcept
    {
        return static_cast<uint32_t>(level_z9_) << 16U | static_cast<uint32_t>(level_z8_) << 14U |
               static_cast<uint32_t>(level_z7_) << 12U | static_cast<uint32_t>(level_z6_) << 10U |
               static_cast<uint32_t>(level_z5_) << 8U | static_cast<uint32_t>(level_z4_) << 6U |
               static_cast<uint32_t>(level_z3_) << 4U | static_cast<uint32_t>(level_z2_) << 2U |
               static_cast<uint32_t>(level_z1_);
    }

    /**
     * @brief Get the Zone Ability object
     *
     * @return perception zone ability's uint32_t type.
     */
    uint32_t GetZoneAbility() const noexcept
    {
        uint32_t ret = *this;
        return ret;
    }

    /**
     * @brief Get the Front Far Zone Ability Level
     * @details Front Far Zone: Z1, Z3
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetFrontFarZoneAbility() const noexcept
    {
        return PerceptionAbilityLevel(level_z1_ < level_z3_ ? level_z1_ : level_z3_);
    }

    /**
     * @brief Get the Front Near Zone Ability Level
     * @details Front Near Zone: Z3
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetFrontNearZoneAbility() const noexcept
    {
        return PerceptionAbilityLevel(level_z3_);
    }

    /**
     * @brief Get the Front Wide Far Zone Ability Level
     * @details Front Wide Far Zone: Z1, Z2, Z3, Z4
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetFrontWideFarZoneAbility() const noexcept
    {
        uint32_t min = level_z1_;
        if (level_z2_ < min)
        {
            min = level_z2_;
        }
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        if (level_z4_ < min)
        {
            min = level_z4_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Front Wide Near Zone Ability Level
     * @details Front Wide Near Zone: Z2, Z3, Z4
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetFrontWideNearZoneAbility() const noexcept
    {
        uint32_t min = level_z2_;
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        if (level_z4_ < min)
        {
            min = level_z4_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Front Left Zone Ability Level
     * @details Front Front Left Zone: Z1, Z2, Z3
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetFrontLeftZoneAbility() const noexcept
    {
        uint32_t min = level_z1_;
        if (level_z2_ < min)
        {
            min = level_z2_;
        }
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Front Right Zone Ability Level
     * @details Front Front Right Zone: Z1, Z3, Z4
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetFrontRightZoneAbility() const noexcept
    {
        uint32_t min = level_z1_;
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        if (level_z4_ < min)
        {
            min = level_z4_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Left Zone Ability Level
     * @details Front Left Zone: Z1, Z2, Z3, Z5, Z7
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetLeftZoneAbility() const noexcept
    {
        uint32_t min = level_z1_;
        if (level_z2_ < min)
        {
            min = level_z2_;
        }
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        if (level_z5_ < min)
        {
            min = level_z5_;
        }
        if (level_z7_ < min)
        {
            min = level_z7_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Right Zone Ability Level
     * @details Front Right Zone: Z1, Z3, Z4, Z6, Z8
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetRightZoneAbility() const noexcept
    {
        uint32_t min = level_z1_;
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        if (level_z4_ < min)
        {
            min = level_z4_;
        }
        if (level_z6_ < min)
        {
            min = level_z6_;
        }
        if (level_z8_ < min)
        {
            min = level_z8_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Left Near Zone Ability Level
     * @details Front Left Near Zone: Z2, Z3, Z5, Z7
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetLeftNearZoneAbility() const noexcept
    {
        uint32_t min = level_z2_;
        if (level_z3_ < min)
        {
            min = level_z3_;
        }
        if (level_z5_ < min)
        {
            min = level_z5_;
        }
        if (level_z7_ < min)
        {
            min = level_z7_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Right Near Zone Ability Level
     * @details Front Right Near Zone: Z3, Z4, Z6, Z8
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetRightNearZoneAbility() const noexcept
    {
        uint32_t min = level_z3_;
        if (level_z4_ < min)
        {
            min = level_z4_;
        }
        if (level_z6_ < min)
        {
            min = level_z6_;
        }
        if (level_z8_ < min)
        {
            min = level_z8_;
        }
        return PerceptionAbilityLevel(min);
    }

    /**
     * @brief Get the Perception Ability level by coordinate.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return PerceptionAbilityLevel
     */
    PerceptionAbilityLevel GetPerceptionAbility(const float32_t x, const float32_t y) const
    {
        if (X_MAX < x || x < X_MIN || Y_MAX < y || y < Y_MIN)
        {
            throw std::range_error("Invalid coordinate position!");
        }
        uint32_t perception_ability = 0U;
        if (isInZone1(x, y)) perception_ability = level_z1_;
        if (isInZone2(x, y)) perception_ability = level_z2_;
        if (isInZone3(x, y)) perception_ability = level_z3_;
        if (isInZone4(x, y)) perception_ability = level_z4_;
        if (isInZone5(x, y)) perception_ability = level_z5_;
        if (isInZone6(x, y)) perception_ability = level_z6_;
        if (isInZone7(x, y)) perception_ability = level_z7_;
        if (isInZone8(x, y)) perception_ability = level_z8_;
        if (isInZone9(x, y)) perception_ability = level_z9_;
        return PerceptionAbilityLevel(perception_ability);
    }

private:
    /**
     * @brief merge two zone level
     * @details
     * merge rule: NONE + ANY_LEVEL = ANY_LEVEL, HIGH + ANY_LEVEL = HIGH, LOW + LOW = MIDDLE, LOW + MIDDLE = HIGH,
     * MIDDLE + MIDDLE = HIGH.
     * @param l1 first zone level
     * @param l2 second zone level
     * @return merged zone level
     */
    uint32_t mergeLevel(const uint32_t l1, const uint32_t l2)
    {
        uint32_t value1 = l1;
        uint32_t value2 = l2;
        if ((value1 + value2) > 3U)
        {
            return 3U;
        }
        else
        {
            return value1 + value2;
        }
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone1(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY5 < x && x <= X_MAX && Y_MIN <= y && y <= Y_MAX)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone2(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY4 < x && x <= X_BOUNDARY5 && Y_BOUNDARY3 < y && y <= Y_MAX)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone3(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY3 < x && x <= X_BOUNDARY5 && Y_BOUNDARY1 < y && y <= Y_BOUNDARY3)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone4(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY4 < x && x <= X_BOUNDARY5 && Y_MIN <= y && y <= Y_BOUNDARY1)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone5(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY1 < x && x <= X_BOUNDARY4 && Y_BOUNDARY3 < y && y <= Y_MAX)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone6(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY1 < x && x <= X_BOUNDARY4 && Y_MIN <= y && y <= Y_BOUNDARY1)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone7(const float32_t x, const float32_t y) const
    {
        if (X_MIN <= x && x <= X_BOUNDARY1 && Y_BOUNDARY2 < y && y <= Y_MAX)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone8(const float32_t x, const float32_t y) const
    {
        if (X_MIN <= x && x <= X_BOUNDARY1 && Y_MIN <= y && y <= Y_BOUNDARY2)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief check a coordinate point belong to this zone or not.
     *
     * @param x coordinate x in body frame.
     * @param y coordinate y in body frame.
     * @return bool_t, true for yes, false for no.
     */
    bool_t isInZone9(const float32_t x, const float32_t y) const
    {
        if (X_BOUNDARY2 <= x && x <= X_BOUNDARY3 && Y_BOUNDARY1 < y && y <= Y_BOUNDARY3)
        {
            return true;
        }
        return false;
    }

private:
    uint32_t level_z1_ : 2;
    uint32_t level_z2_ : 2;
    uint32_t level_z3_ : 2;
    uint32_t level_z4_ : 2;
    uint32_t level_z5_ : 2;
    uint32_t level_z6_ : 2;
    uint32_t level_z7_ : 2;
    uint32_t level_z8_ : 2;
    uint32_t level_z9_ : 2;
    uint32_t reserved_ : 14;

    // Zone boundary.
    static constexpr float32_t X_MIN{-100.0f};
    static constexpr float32_t X_MAX{200.0f};
    static constexpr float32_t Y_MIN{-12.0f};
    static constexpr float32_t Y_MAX{12.0f};
    static constexpr float32_t X_BOUNDARY1{0.0f};
    static constexpr float32_t X_BOUNDARY2{4.0f};
    static constexpr float32_t X_BOUNDARY3{9.0f};
    static constexpr float32_t X_BOUNDARY4{10.0f};
    static constexpr float32_t X_BOUNDARY5{100.0f};
    static constexpr float32_t Y_BOUNDARY1{-2.0f};
    static constexpr float32_t Y_BOUNDARY2{0.0f};
    static constexpr float32_t Y_BOUNDARY3{2.0f};
};
}  // namespace common
/**
 *
 * @}
 */

}  // namespace holo

#endif  //  !HOLO_COMMON_PERCEPTION_ABILITY_H_
