/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file weather.h
 * @brief This header file defines the weather category.
 * @author lanshayun(lanshayun@holomaitc.com)
 * @date "2020-04-03"
 */

#ifndef HOLO_COMMON_WEATHER_H_
#define HOLO_COMMON_WEATHER_H_

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
 * @brief This class defines the weather categories.
 *
 * @details Weather object has 5 categories.
 * @verbatim
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +---------------------+---------+---------+---------+---------+-+
 * |         RSV         |  Sandy  |  Foggy  |  Snowy  |  Rainy  |C|
 * +---------------------+---------+---------+---------+---------+-+
 * @endverbatim
 * RSV: Reserved.
 *
 * Sandy: Sandy visibility, range: [0, 1085], unit m, map parameter: 35m, range = sandy_vis_ * vis_mapped_param;
 *
 * Foggy: Foggy visibility, range: [0, 1085], unit m, map parameter: 35m, range = foggy_vis_ * vis_mapped_param;
 *
 * Snowy: snowfall, range: [0, 31], unit: mm/24h;
 *
 * Rainy: rainfall, range: [0, 279], unit: mm/24h, map parameter: 9mm/24h, range = rainfall_ * rainy_mapped_param;
 *
 * C: Cloudy category, has 2 levels. 0-sunny, 1-cloudy.
 */

class Weather
{
public:
    /**
     * @brief The basic data structure.
     *
     */
    struct Category
    {
        uint32_t cloudy_ : 1;
        uint32_t rainfall_ : 5;
        uint32_t snowfall_ : 5;
        uint32_t foggy_vis_ : 5;
        uint32_t sandy_vis_ : 5;
        uint32_t reserved_ : 11;
    };

    /**
     * @brief Construct a new Weather object.
     *
     */
    Weather() : timestamp_(0.0f), weather_category_{0u, 0u, 0u, 0x1f, 0x1f, 0u}
    {
    }

    /**
     * @brief Construct a new Weather object.
     *
     * @param value Value to initialize Weather.
     *
     * @note The high 11-bit of value will be ignored.
     */
    Weather(uint32_t value)
      : timestamp_(0.0f)
      , weather_category_{
            value & 1u, (value >> 1) & 0x1f, (value >> 6) & 0x1f, (value >> 11) & 0x1f, (value >> 16) & 0x1f, 0u,
        }
    {
    }

    /**
     * @brief Get all weather status in uint32_t.
     *
     * @return uint32_t type value.
     */
    uint32_t GetAllWeather() const noexcept
    {
        return static_cast<uint32_t>(weather_category_.sandy_vis_) << 16 |
               static_cast<uint32_t>(weather_category_.foggy_vis_) << 11 |
               static_cast<uint32_t>(weather_category_.snowfall_) << 6 |
               static_cast<uint32_t>(weather_category_.rainfall_) << 1 |
               static_cast<uint32_t>(weather_category_.cloudy_);
    }

    /**
     * @brief Set the All Weather object from uint32_t.
     *
     * @param value, uint32_t type.
     */
    void SetAllWeather(uint32_t value) noexcept
    {
        weather_category_.cloudy_    = value & 1u;
        weather_category_.rainfall_  = (value >> 1) & 0x1f;
        weather_category_.snowfall_  = (value >> 6) & 0x1f;
        weather_category_.foggy_vis_ = (value >> 11) & 0x1f;
        weather_category_.sandy_vis_ = (value >> 16) & 0x1f;
    }

    /**
     * @brief Assign operator. Enable initialize from uint32_t.
     *
     * @param value Value to initialize Weather.
     * @return Reference to Weather object.
     */
    Weather& operator=(uint32_t value) noexcept
    {
        SetAllWeather(value);
        return *this;
    }

    /**
     * @brief Cast operator. Enable cast to uint32_t type.
     *
     * @return uint32_t type value.
     */
    operator uint32_t() const noexcept
    {
        return GetAllWeather();
    }

    /**
     * @brief Set the Cloudy status.
     *
     * @param flag, 0/false for sunny(not cloudy), 1/true for cloudy.
     */
    void SetCloudy(bool_t flag) noexcept
    {
        weather_category_.cloudy_ = flag;
    }

    /**
     * @brief Set the RainFall value.
     *
     * @param value, rainfall in mm/24h.
     */
    void SetRainFall(const uint32_t value) noexcept
    {
        weather_category_.rainfall_ = (value / RAINY_MAPPED_PARAM) > 0x1f ? 0x1f : (value / RAINY_MAPPED_PARAM);
    }

    /**
     * @brief Set the SnowFall value.
     *
     * @param value, snowfall in mm/24h.
     */
    void SetSnowFall(const uint32_t value) noexcept
    {
        weather_category_.snowfall_ = value > 0x1f ? 0x1f : value;
    }

    /**
     * @brief Set the Foggy visibility.
     *
     * @param value, visibility in meter.
     */
    void SetFoggyVisibility(const uint32_t value) noexcept
    {
        weather_category_.foggy_vis_ = (value / VIS_MAPPED_PARAM) > 0x1f ? 0x1f : (value / VIS_MAPPED_PARAM);
    }

    /**
     * @brief Set the Sandy visibility.
     *
     * @param value, visibility in meter.
     */
    void SetSandyVisibility(const uint32_t value) noexcept
    {
        weather_category_.sandy_vis_ = (value / VIS_MAPPED_PARAM) > 0x1f ? 0x1f : (value / VIS_MAPPED_PARAM);
    }

    /**
     * @brief Check if the weather is cloudy.
     *
     * @return bool_t, true for yes, false for no(sunny).
     */
    bool_t IsCloudy() const noexcept
    {
        return weather_category_.cloudy_;
    }

    /**
     * @brief Check if the weather is rainy.
     *
     * @return bool_t, true for yes, false for no.
     */
    bool_t IsRainy() const noexcept
    {
        return weather_category_.rainfall_ > 0u;
    }

    /**
     * @brief Check if the weather is snowy.
     *
     * @return bool_t, true for yes, false for no.
     */
    bool_t IsSnowy() const noexcept
    {
        return weather_category_.snowfall_ > 0u;
    }

    /**
     * @brief Check if the weather is foggy.
     *
     * @return bool_t, true for yes, false for no.
     */
    bool_t IsFoggy() const noexcept
    {
        return weather_category_.foggy_vis_ * VIS_MAPPED_PARAM < VISBILITY_THRESHOLD;
    }

    /**
     * @brief Check if the weather is sandy.
     *
     * @return bool_t, true for yes, false for no.
     */
    bool_t IsSandy() const noexcept
    {
        return weather_category_.sandy_vis_ * VIS_MAPPED_PARAM < VISBILITY_THRESHOLD;
    }

    /**
     * @brief Get the RainFall value.
     *
     * @return uint32_t, rainfall in mm/24h.
     */
    uint32_t GetRainFall() const noexcept
    {
        return weather_category_.rainfall_ * RAINY_MAPPED_PARAM;
    }

    /**
     * @brief Get the SnowFall value.
     *
     * @return uint32_t, snowfall in mm/24h.
     */
    uint32_t GetSnowFall() const noexcept
    {
        return weather_category_.snowfall_;
    }

    /**
     * @brief Get the Foggy Visibility.
     *
     * @return uint32_t, visibility in meter.
     */
    uint32_t GetFoggyVisibility() const noexcept
    {
        return weather_category_.foggy_vis_ * VIS_MAPPED_PARAM;
    }

    /**
     * @brief Get the Sandy Visibility.
     *
     * @return uint32_t, visibilty in meter.
     */
    uint32_t GetSandyVisibility() const noexcept
    {
        return weather_category_.sandy_vis_ * VIS_MAPPED_PARAM;
    }

    /**
     * @brief Get const reference of Timestamp
     *
     * @return const reference of Timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set Timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(const Timestamp& timestamp)
    {
        timestamp_ = timestamp;
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
        uint32_t weather_category = 0;
        return timestamp_.GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(weather_category);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t all_weather = GetAllWeather();
        serializer << timestamp_ << all_weather << holo::serialization::align;
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
        uint32_t all_weather;
        deserializer >> timestamp_ >> all_weather >> holo::serialization::align;
        SetAllWeather(all_weather);
    }

private:
    Timestamp timestamp_;
    Category  weather_category_;

public:
    static uint32_t const RAINY_MAPPED_PARAM  = 9u;     ///< rainy value's uint is 9mm/24h.
    static uint32_t const VIS_MAPPED_PARAM    = 35u;    ///< foggy or sandy value's unit is 35m.
    static uint32_t const VISBILITY_THRESHOLD = 1000u;  ///< visibilty>1000m means no foggy or sandy.

};  // namespace Weather

}  // namespace common
/**
 *
 * @}
 */

}  // namespace holo

#endif  // !HOLO_COMMON_WEATHER_H_
