/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geofence_common.h
 * @brief This header file defines common functions for geofence related code.
 * @author lisong@holomatic.com
 * @date 2020-05-06
 */

#ifndef HOLO_MAP_GEOFENCE_GEOFENCE_COMMON_H_
#define HOLO_MAP_GEOFENCE_GEOFENCE_COMMON_H_

#include <chrono>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <ratio>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <holo/log/hololog.h>

#include <holo/core/types.h>
#include <holo/map/common_def.h>
#include <holo/map/common/common_type_define.h>
#include <holo/serialization/deserializer.h>
#include <holo/serialization/serializer.h>

#include <holo/map/geofence/map_geofence.h>

#define FIX_BUFFER_SIZE 8192UL
#define ALIGNMENT_SIZE 4UL

#define DURATION_YEAR_RATIO 31536000 ///< 365*24*60*60 seconds
#define DURATION_MONTH_RATIO 2592000 ///< 30*24*60*60  seconds
#define DURATION_DAY_RATIO 86400     ///< 24*60*60     seconds

namespace holo
{
/**
 * @addtogroup holo
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup map
 *
 * @{
 */

namespace geofence
{
/**
 * @addtogroup geofence
 *
 * @{
 */

/// Common use time duration types
using YearDurationType  = std::chrono::duration<holo::int64_t, std::ratio<DURATION_YEAR_RATIO>>;
using MonthDurationType = std::chrono::duration<holo::int64_t, std::ratio<DURATION_MONTH_RATIO>>;
using DayDurationType   = std::chrono::duration<holo::int64_t, std::ratio<DURATION_DAY_RATIO>>;

/**
 * @brief Format values to json string.
 *
 * @tparam T Type of object that need to format to string
 * @param [in] values Value.
 * @return Json string.
 */
template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
std::string FormatToString(T const& obj)
{
    std::stringstream stream;
    stream << std::setprecision(16);
    stream << obj;
    return stream.str();
}

/**
 * @brief Format values to json string.
 *
 * @tparam T Type of object that need to format to string
 * @param [in] values Value.
 * @return Json string.
 */
template <typename T, typename std::enable_if<std::is_same<T, int8_t>::value || std::is_same<T, uint8_t>::value>::type* = nullptr>
std::string FormatToString(T const& obj)
{
    std::stringstream stream;
    stream << static_cast<int>(obj);
    return stream.str();
}

/**
 * @brief Format values to json string.
 *
 * @tparam T Type of object that need to format to string
 * @param [in] values Value.
 * @return Json string.
 */
template <typename T, typename std::enable_if<!std::is_same<T, int8_t>::value && !std::is_same<T, uint8_t>::value && !std::is_floating_point<T>::value>::type* = nullptr>
std::string FormatToString(T const& obj)
{
    std::stringstream stream;
    stream << obj;
    return stream.str();
}

/**
 * @brief Format a object of MapGeofence::Function to json string
 *
 * @param[in] obj Object of MapGeofence::Function
 * @return Result string.
 */
std::string FormatToString(MapGeofence::Function const obj);

/**
 * @brief Format a object of MapGeofence::GeofenceType to json string
 *
 * @param[in] obj Object of MapGeofence::GeofenceType
 * @return Result string.
 */
std::string FormatToString(MapGeofence::GeofenceType const obj);

/**
 * @brief Format a object of MapGeofence::GeoType to json string
 *
 * @param[in] obj Object of MapGeofence::GeoType
 * @return Result string.
 */
std::string FormatToString(MapGeofence::GeoType const obj);

/**
 * @brief Format a object of MapGeofence::FeatureType to json string
 *
 * @param[in] obj Object of MapGeofence::FeatureType
 * @return Result string.
 */
std::string FormatToString(MapGeofence::FeatureType const obj);

/**
 * @brief Format a object of MapGeofence::ValidType to json string
 *
 * @param[in] obj Object of MapGeofence::ValidType
 * @return Result string.
 */
std::string FormatToString(MapGeofence::ValidType const obj);

/**
 * @brief Format a uint64_t value to json string
 *
 * @param[in] val uint64_t value
 * @param[in] for_time_point If true interpret val as time point,
 *                           If false interpret val as time duration
 * @return Result string.
 */
std::string FormatToString(holo::uint64_t const val, holo::bool_t const for_time_point);

/**
 * @brief Convert a string to a uint64_t value
 *
 * @param[in] str Source string
 * @param[in] for_time_point If true interpret str as time point,
 *                           If false interpret str as time duration
 * @return Result uint64_t value.
 */
holo::uint64_t ReadFromString(std::string const& str, holo::bool_t const for_time_point);

/**
 * @brief Format a object of MapGeofence::ValidTime to json string
 *
 * @param[in] obj Object of MapGeofence::ValidTime
 * @return Result string.
 */
std::string FormatToString(MapGeofence::ValidTime const& obj);

/**
 * @brief Format a object of LocalGepfence to json string
 *
 * @param[in] obj Result object of MapGeofence
 * @return Result string.
 */
std::string FormatToString(MapGeofence const& obj);

/**
 * @brief Format a object of MapGeofenceIndex to json string
 *
 * @param[in] obj Result object of MapGeofenceIndex
 * @return Result string.
 */
std::string FormatToString(MapGeofenceIndex const& obj);

/**
 * @brief Format values to json string.
 *
 * @tparam T Type of object from vector that need to format to string
 * @param [in] values Value in array.
 * @return Json string.
 */
template <typename T>
std::string FormatToString(std::vector<T> const& values)
{
    std::stringstream stream;
    stream << "[";
    std::size_t const count = values.size();
    for (std::size_t i = 0; i < count; ++i)
    {
        std::string const end = (i + 1) < count ? ", " : "";
        stream << FormatToString(values[i]) << end;
    }
    stream << "]";
    return stream.str();
}

/**
 * @brief Serialize object of type T to string.
 *
 * @tparam T Type of object to serialize
 * @param[in] obj Object of T
 * @return Result string.
 */
template <typename T>
std::string SerializeToString(T const& obj)
{
    holo::uint8_t buffer[FIX_BUFFER_SIZE];
    holo::serialization::Serializer<> serializer(buffer, FIX_BUFFER_SIZE);
    serializer << obj;
    serializer << holo::serialization::align;

    return std::string(reinterpret_cast<char const*>(serializer.GetData()), serializer.GetSize());
}

/**
 * @brief Specialization for MapGeofence::ValidTime
 */
template<>
std::string SerializeToString(MapGeofence::ValidTime const& obj);

/**
 * @brief Serialize
 *
 * @tparam T Type of object serialize from
 * @param[in] serializer Reference to serializer object
 * @param[in] obj Object serialize from
 * @return Reference to serializer object
 */
template <typename T>
void Serialize(holo::serialization::Serializer<>& serializer, T const& obj)
{
    serializer << obj;
}

/**
 * @brief Serialize string to vector object of type T.
 *
 * @tparam T Type of object vector to serialize from
 * @param[in] obj Result object vector of T
 * @return Result string.
 */
template <typename T>
std::string SerializeToString(std::vector<T> const& obj_vec)
{
    holo::uint8_t buffer[FIX_BUFFER_SIZE];
    holo::serialization::Serializer<> serializer(buffer, FIX_BUFFER_SIZE);
    std::size_t const count = obj_vec.size();
    serializer << count;
    for (std::size_t i = 0; i < count; ++i)
    {
        Serialize(serializer, obj_vec.at(i));
    }
    serializer << holo::serialization::align;

    return std::string(reinterpret_cast<char const*>(serializer.GetData()), serializer.GetSize());
}

/**
 * @brief Specialization for MapGeofence
 */
template<>
std::string SerializeToString(MapGeofence const& obj);

/**
 * @brief Specialization for MapGeofenceIndex
 */
template<>
std::string SerializeToString(MapGeofenceIndex const& obj);

/**
 * @brief Deserialize string to object of type T.
 *
 * @tparam T Type of result object deserialize to
 * @param[in] str Given str
 * @param[out] obj Result object of T
 * @return True if successful,
 *         False if failed.
 */
template <typename T>
holo::bool_t DeserializeFromString(std::string const& str, T& obj)
{
    if (str.data() == nullptr)
    {
        LOG(ERROR) << "DeserializeFromString failed, underlying data of given string is null.";
        return false;
    }
    char* raw_data_pointer = const_cast<char*>(str.data());
    holo::uint8_t buffer[FIX_BUFFER_SIZE];
    std::memcpy(static_cast<void*>(buffer), static_cast<void*>(raw_data_pointer), str.size());
    holo::serialization::Deserializer<> deserializer(buffer, str.size());
    deserializer >> obj >> holo::serialization::align;

    return true;
}

/**
 * @brief Specialization for MapGeofence::ValidTime
 */
template<>
holo::bool_t DeserializeFromString(std::string const& str, MapGeofence::ValidTime& obj);

/**
 * @brief Deserialize
 *
 * @tparam T Type of result object deserialize to
 * @param[in] deserializer Deserializer object
 * @param[out] obj Result object of T
 * @return Reference to Deserializer object
 */
template <typename T>
void Deserialize(holo::serialization::Deserializer<>& deserializer, T& obj)
{
    deserializer >> obj;
}

/**
 * @brief Deserialize string to object vector of type T.
 *
 * @tparam T Type of result object
 * @param[in] str Given str
 * @param[out] obj_vec Result object vector of T
 * @return True if successful,
 *         False if failed.
 */
template <typename T>
holo::bool_t DeserializeFromString(std::string const& str, std::vector<T>& obj_vec)
{
    obj_vec.clear();
    if (str.data() == nullptr)
    {
        LOG(ERROR) << "DeserializeFromString failed, underlying data of given string is null.";
        return false;
    }
    char* raw_data_pointer = const_cast<char*>(str.data());
    holo::uint8_t buffer[FIX_BUFFER_SIZE];
    std::memcpy(static_cast<void*>(buffer), static_cast<void*>(raw_data_pointer), str.size());
    holo::serialization::Deserializer<> deserializer(buffer, str.size());

    std::size_t count = 0UL;
    deserializer >> count;
    obj_vec.resize(count);
    for (std::size_t idx = 0UL; idx < count; ++idx)
    {
        Deserialize(deserializer, obj_vec[idx]);
    }
    deserializer >> holo::serialization::align;

    return true;
}

/**
 * @brief Specialization for MapGeofence
 */
template<>
holo::bool_t DeserializeFromString(std::string const& str, MapGeofence& obj);

/**
 * @brief Specialization for MapGeofenceIndex
 */
template<>
holo::bool_t DeserializeFromString(std::string const& str, MapGeofenceIndex& obj);

/**
 * @brief Check if given ID is valid.
 * @details Only check IDs of MapGeofence\MapGeofenceIndex\Link|Tile for now.
 *
 * @param[in] id Given ID.
 * @return True if given ID is valid,
 *         False if not.
 */
holo::bool_t IsIDValid(MapFeatureIdType const id);

/**
 * @brief Check if given Function(MapGeofence::Function) is valid.
 * @details Following Function is valid:
 *          MapGeofence::Function::UNKNOWN
 *          MapGeofence::Function::FUNCTION_MAX
 *
 * @param[in] function Given Function.
 * @return True if given Function is valid,
 *         False if not.
 */
holo::bool_t IsFunctionValid(MapGeofence::Function const function);

/**
 * @}
 */
}  // namespace geofence
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo

#endif /* HOLO_MAP_GEOFENCE_GEOFENCE_COMMON_H_ */
