/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_weather.h
 * @brief Define weather infomation which from third-party service.
 * @author wanghaiyang@holomatic.com
 * @date "2020-02-28"
 */

#ifndef HOLO_MAP_MAP_WEATHER_H_
#define HOLO_MAP_MAP_WEATHER_H_

#include <vector>

#include <holo/common/timestamp.h>
#include <holo/common/weather.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief Third-party weather information.
 * 
 * @note Reference to: https://wiki.holomatic.cn/pages/viewpage.action?pageId=56757088.
 */
class MapWeather
{
public:
    /**
     * @brief Redefine type for inner data.
     */
    using PressureType      = holo::int32_t;
    using TemperatureType   = holo::int32_t;
    using WindPowerType     = holo::uint32_t;
    using HumidityType      = holo::uint32_t;

    /**
     * @brief Constructor.
     * 
     * @return Nothing.
     */
    MapWeather() : 
        timestamp_(0.0f),
        report_time_(0.0f),
        data_{0, 0, 0, 0, 0, 0}
    {}

    /**
     * @brief Access timestamp.
     * 
     * @return A reference of Timestamp.
     */
    Timestamp& GetTimestamp() noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Access timestamp.
     * 
     * @return A const reference of Timestamp.
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return this->timestamp_;
    }

    /**
     * @brief Assign a new timestamp.
     * 
     * @param[in] t A timestamp value.
     * @return Nothing.
     */
    void SetTimestamp(Timestamp const& t)
    {
        this->timestamp_ = t;
    }

    /**
     * @brief Access weather report time.
     * 
     * @return A reference of Timestamp.
     */
    Timestamp& GetReportTime() noexcept
    {
        return this->report_time_;
    }

    /**
     * @brief Access weather report time.
     * 
     * @return A const reference of Timestamp.
     */
    Timestamp const& GetReportTime() const noexcept
    {
        return this->report_time_;
    }

    /**
     * @brief Assign a new weather report time.
     * 
     * @param[in] t A timestamp value.
     * @return Nothing.
     */
    void SetReportTime(Timestamp const& t)
    {
        this->report_time_ = t;
    }

    /**
     * @brief Access common weather information.
     * 
     * @return A reference of Weather.
     */
    common::Weather& GetWeather() noexcept
    {
        return this->weather_;
    }

    /**
     * @brief Access common weather information.
     * 
     * @return A const reference of Weather.
     */
    common::Weather const& GetWeather() const noexcept
    {
        return this->weather_;
    }

    /**
     * @brief Assign a new common weather information.
     * 
     * @param[in] t A weather value.
     * @return Nothing.
     */
    void SetWeather(common::Weather const& w)
    {
        this->weather_ = w;
    }

    /**
     * @brief Access atmospheric pressure.
     * 
     * @return Atmospheric pressure(Unit: Pa).
     */
    PressureType GetAtmosphericPressure() const noexcept
    {
        return this->data_.pressure;
    }

    /**
     * @brief Assign a new atmospheric pressure.
     * 
     * @param[in] p Atmospheric pressure(Unit: Pa).
     * @return Nothing.
     */
    void SetAtmosphericPressure(PressureType const p) noexcept
    {
        this->data_.pressure = p;
    }

    /**
     * @brief Access atmospheric temperature.
     * 
     * @return Atmospheric temperature(Unit: celcius).
     */
    TemperatureType GetAtmosphericTemperature() const noexcept
    {
        return this->data_.temperature;
    }

    /**
     * @brief Assign a new atmospheric temperature value.
     * 
     * @param[in] t Atmospheric temperature(Unit: celcius).
     * @return Nothing.
     */
    void SetAtmosphericTemperature(TemperatureType const t) noexcept
    {
        this->data_.temperature = t;
    }

    /**
     * @brief Access atmospheric humidity.
     * 
     * @return Atmospheric humidity(Unit: %RH).
     */
    HumidityType GetAtmosphericHumidity() const noexcept
    {
        return this->data_.humidity;
    }

    /**
     * @brief Assign a new atmospheric humidity value.
     * 
     * @param[in] h Atmospheric humidity(Unit: %RH).
     * @return Nothing.
     */
    void SetAtmosphericHumidity(HumidityType const h)  noexcept
    {
        this->data_.humidity = h;
    }

    /**
     * @brief Access wind power.
     * 
     * @return Wind power(Range: [0, 12]).
     */
    WindPowerType GetWindPower() const noexcept
    {
        return this->data_.wind_power;
    }

    /**
     * @brief Assign a new wind power value.
     * 
     * @param[in] v Wind power(Range: [0, 12]).
     * @return Nothing.
     */
    void SetWindPower(WindPowerType const v) noexcept
    {
        this->data_.wind_power = v;
    }

    /**
     * @brief Whether or not is north wind direction.
     * 
     * @return true: North wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsNorthWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::NORTH;
    }

    /**
     * @brief Assign wind direction with type of north.
     * 
     * @param[in] w true: Set NORTH to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetNorthWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::NORTH) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is northeast wind direction.
     * 
     * @return true: Northeast wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsNortheastWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::NORTH_EAST;
    }

    /**
     * @brief Assign wind direction with type of northeast.
     * 
     * @param[in] w true: Set NORTH_EAST to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetNortheastWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::NORTH_EAST) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is east wind direction.
     * 
     * @return true: East wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsEastWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::EAST;
    }

    /**
     * @brief Assign wind direction with type of east.
     * 
     * @param[in] w true: Set EAST to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetEastWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::EAST) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is southeast wind direction.
     * 
     * @return true: Southeast wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsSoutheastWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::SOUTH_EAST;
    }

    /**
     * @brief Assign wind direction with type of southeast.
     * 
     * @param[in] w true: Set SOUTH_EAST to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetSoutheastWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::SOUTH_EAST) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is south wind direction.
     * 
     * @return true: South wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsSouthWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::SOUTH;
    }

    /**
     * @brief Assign wind direction with type of south.
     * 
     * @param[in] w true: Set SOUTH to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetSouthWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::SOUTH) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is southwest wind direction.
     * 
     * @return true: Southwest wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsSouthwestWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::SOUTH_WEST;
    }

    /**
     * @brief Assign wind direction with type of southwest.
     * 
     * @param[in] w true: Set SOUTH_WEST to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetSouthwest(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::SOUTH_WEST) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is west wind direction.
     * 
     * @return true: West wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsWestWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::WEST;
    }

    /**
     * @brief Assign wind direction with type of west.
     * 
     * @param[in] w true: Set WEST to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetWestWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::WEST) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is northwest wind direction.
     * 
     * @return true: Northwest wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsNorthwestWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::NORTH_WEST;
    }

    /**
     * @brief Assign wind direction with type of northwest.
     * 
     * @param[in] w true: Set NORTH_WEST to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetNorthwestWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::NORTH_WEST) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is uncertain wind direction.
     * 
     * @return true: Uncertain wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsUncertainWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::UNCERTAIN;
    }

    /**
     * @brief Assign wind direction with type of uncertain.
     * 
     * @param[in] w true: Set UNCERTAIN to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetUncertainWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::UNCERTAIN) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is no wind.
     * 
     * @return true: No wind;
     *         false: Otherwise.
     */
    holo::bool_t IsNoWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::NONE;
    }

    /**
     * @brief Assign wind direction with type of no wind.
     * 
     * @param[in] w true: Set NONE to wind direction;
     *              false: Set UNKNOWN to wind direction.
     * @return Nothing.
     */
    void SetNoWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::NONE) :
                                         static_cast<holo::uint32_t>(WindDirection::UNKNOWN);
    }

    /**
     * @brief Whether or not is unknown wind direction.
     * 
     * @return true: Unknown wind direction;
     *         false: Otherwise.
     */
    holo::bool_t IsUnknownWind() const noexcept
    {
        return static_cast<WindDirection>(this->data_.wind_direction) == WindDirection::UNKNOWN;
    }

    /**
     * @brief Assign wind direction with type of unknown.
     * 
     * @param[in] w true: Set UNKNOWN to wind direction;
     *              false: Do nothing.
     * @return Nothing.
     */
    void SetUnknownWind(holo::bool_t const w = true) noexcept
    {
        this->data_.wind_direction = w ? static_cast<holo::uint32_t>(WindDirection::UNKNOWN) :
                                         this->data_.wind_direction;
    }

private:
    /**
     * @brief Definition of wind direction.
     */
    enum class WindDirection : uint8_t
    {
        UNKNOWN = 0,        ///< Placehold.
        NONE,               ///< No wind.
        UNCERTAIN,
        NORTH,
        NORTH_EAST,
        EAST,
        SOUTH_EAST,
        SOUTH,
        SOUTH_WEST,
        WEST,
        NORTH_WEST,
        WIND_DIRECTION_MAX   ///< Total count of types in WindDirection.
    };

    /**
     * @brief Detail information of live weather.
     */
    struct InnerData
    {
        int32_t  pressure;          ///< Atmospheric pressure, Unit: Pa.
        int32_t  temperature;       ///< Unit: Celcius.
        uint32_t wind_power:4;      ///< Range: [0~12].
        uint32_t wind_direction:4;  ///< Direction of wind.
        uint32_t humidity:7;        ///< Air relative humidity, Unit: %RH.
        uint32_t reserved:17;       ///< Reserved bits.
    };

    holo::Timestamp timestamp_;     ///< Timestamp of message.
    holo::Timestamp report_time_;   ///< Report timestamp.
    common::Weather weather_;       ///< Weather condition.
    InnerData       data_;          ///< Detail information.
}; ///< End of class MapWeather.

/**
 * @}
 *
 */

} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_MAP_WEATHER_H_ */
