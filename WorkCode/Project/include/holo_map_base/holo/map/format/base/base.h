/* 
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file base.h
 * @brief Head file of internal base format
 * @author Yuchao Hu(huyuchao@holomaitc.com)
 * @date 2017-04-03
 */

#ifndef HOLO_MAP_FORMAT_BASE_BASE_H_
#define HOLO_MAP_FORMAT_BASE_BASE_H_

#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <holo/map/common/map_version_parser.h>
#include <holo/map/map_format_version_config.h>

namespace holo
{
namespace map
{
namespace format
{

/**
 * @addtogroup format
 * @{
 *
 */

class Base
{
public:

    /**
     * @brief Definition of concrete map feature types.
     */
    enum class FeatureType : uint8_t
    {
        UNKNOWN = 0,
        OBJECT_PARKING_SPACE,
        OBJECT_PARKING_FLOOR,
        OBJECT_PARKING_LOT,
        OBJECT_PARKING_POI,
        OBJECT_PARKING_BACKGROUND,
        MULTI_POSITION,
        INTERVAL_TYPE,
        CONNECTION_V2,
        GEO_CIRCLE,
        GEO_BOX4,
        CONDITION,
        GEO_LINE,
        ID_INTERVAL_FLOAT64,
        INTERVAL_UINT64,
        COORDINATE,
        GEO_POINT,
        GEO_BOX,
        INTERVAL_FLOAT64,
        POSITION,
        GEO_MULTI_POINT,
        GEO_POLYGON,
        DATE_TIME_CYCLE,
        GEO_MULTI_LINE,
        GEO_MULTI_POLYGON,
        GEO_COLLECTION,
        QUASI_DYNAMIC_LANE_GROUP,
        QUASI_DYNAMIC_LANE,
        WEATHER_CONDITION,
        SPEED_LIMIT_CONDITION,
        MAP_REASON,
        TRAFFIC_CONDITION,
        QUASI_DYNAMIC_REGION,
        MAP_CONDITION,
        PAVEMENT_CONDITION,
        TILE,
        LANE_GROUP_ATTRIBUTE,
        LANE_BOUNDARY_INFO,
        SD_ROAD,
        OBJECT_TRAFFIC_SIGN,
        OBJECT_REGIONAL_INFO,
        OBJECT_SAFE_ISLAND,
        OBJECT_INFO,
        OBJECT_LINEAR_INFO,
        OBJECT_TRAFFIC_LIGHT_GROUP,
        LANE_WIDTH_INFO,
        OBJECT_STOP_LINE,
        JUNCTION,
        ROAD_ATTRIBUTE,
        GEOFENCE,
        LANE_BOUNDARY_ELEMENT,
        SPEED_LIMIT_INFO,
        HEADER,
        ROAD,
        LANE_GROUP,
        LANE_BOUNDARY,
        GEOFENCE_FEATURE_INFO,
        LANE,
        OBJECT_TRAFFIC_LIGHT,
        OBJECT_PEDESTRIAN_CROSSING,
        SD_NODE,
        INTERSECTION,
        ROUTING_PATH,
        ROUTING_GRAPH,
        ROUTING_PATH_ELEMENT,
        ROUTING_POSITION,
        ROUTING_REQUEST,
        ROUTING_EDGE,
        CONNECTION,
        ROUTING_NODE,
    };

    static const ::std::map<::std::string, FeatureType>& ENUMSTR_FEATURETYPE() 
    { 
        static const ::std::map<::std::string, FeatureType> data{
            {"OBJECT_PARKING_SPACE", FeatureType::OBJECT_PARKING_SPACE},
            {"OBJECT_PARKING_FLOOR", FeatureType::OBJECT_PARKING_FLOOR},
            {"OBJECT_PARKING_LOT", FeatureType::OBJECT_PARKING_LOT},
            {"OBJECT_PARKING_POI", FeatureType::OBJECT_PARKING_POI},
            {"OBJECT_PARKING_BACKGROUND", FeatureType::OBJECT_PARKING_BACKGROUND},
            {"MULTI_POSITION", FeatureType::MULTI_POSITION},
            {"INTERVAL_TYPE", FeatureType::INTERVAL_TYPE},
            {"CONNECTION_V2", FeatureType::CONNECTION_V2},
            {"GEO_CIRCLE", FeatureType::GEO_CIRCLE},
            {"GEO_BOX4", FeatureType::GEO_BOX4},
            {"CONDITION", FeatureType::CONDITION},
            {"GEO_LINE", FeatureType::GEO_LINE},
            {"ID_INTERVAL_FLOAT64", FeatureType::ID_INTERVAL_FLOAT64},
            {"INTERVAL_UINT64", FeatureType::INTERVAL_UINT64},
            {"COORDINATE", FeatureType::COORDINATE},
            {"GEO_POINT", FeatureType::GEO_POINT},
            {"GEO_BOX", FeatureType::GEO_BOX},
            {"INTERVAL_FLOAT64", FeatureType::INTERVAL_FLOAT64},
            {"POSITION", FeatureType::POSITION},
            {"GEO_MULTI_POINT", FeatureType::GEO_MULTI_POINT},
            {"GEO_POLYGON", FeatureType::GEO_POLYGON},
            {"DATE_TIME_CYCLE", FeatureType::DATE_TIME_CYCLE},
            {"GEO_MULTI_LINE", FeatureType::GEO_MULTI_LINE},
            {"GEO_MULTI_POLYGON", FeatureType::GEO_MULTI_POLYGON},
            {"GEO_COLLECTION", FeatureType::GEO_COLLECTION},
            {"QUASI_DYNAMIC_LANE_GROUP", FeatureType::QUASI_DYNAMIC_LANE_GROUP},
            {"QUASI_DYNAMIC_LANE", FeatureType::QUASI_DYNAMIC_LANE},
            {"WEATHER_CONDITION", FeatureType::WEATHER_CONDITION},
            {"SPEED_LIMIT_CONDITION", FeatureType::SPEED_LIMIT_CONDITION},
            {"MAP_REASON", FeatureType::MAP_REASON},
            {"TRAFFIC_CONDITION", FeatureType::TRAFFIC_CONDITION},
            {"QUASI_DYNAMIC_REGION", FeatureType::QUASI_DYNAMIC_REGION},
            {"MAP_CONDITION", FeatureType::MAP_CONDITION},
            {"PAVEMENT_CONDITION", FeatureType::PAVEMENT_CONDITION},
            {"TILE", FeatureType::TILE},
            {"LANE_GROUP_ATTRIBUTE", FeatureType::LANE_GROUP_ATTRIBUTE},
            {"LANE_BOUNDARY_INFO", FeatureType::LANE_BOUNDARY_INFO},
            {"SD_ROAD", FeatureType::SD_ROAD},
            {"OBJECT_TRAFFIC_SIGN", FeatureType::OBJECT_TRAFFIC_SIGN},
            {"OBJECT_REGIONAL_INFO", FeatureType::OBJECT_REGIONAL_INFO},
            {"OBJECT_SAFE_ISLAND", FeatureType::OBJECT_SAFE_ISLAND},
            {"OBJECT_INFO", FeatureType::OBJECT_INFO},
            {"OBJECT_LINEAR_INFO", FeatureType::OBJECT_LINEAR_INFO},
            {"OBJECT_TRAFFIC_LIGHT_GROUP", FeatureType::OBJECT_TRAFFIC_LIGHT_GROUP},
            {"LANE_WIDTH_INFO", FeatureType::LANE_WIDTH_INFO},
            {"OBJECT_STOP_LINE", FeatureType::OBJECT_STOP_LINE},
            {"JUNCTION", FeatureType::JUNCTION},
            {"ROAD_ATTRIBUTE", FeatureType::ROAD_ATTRIBUTE},
            {"GEOFENCE", FeatureType::GEOFENCE},
            {"LANE_BOUNDARY_ELEMENT", FeatureType::LANE_BOUNDARY_ELEMENT},
            {"SPEED_LIMIT_INFO", FeatureType::SPEED_LIMIT_INFO},
            {"HEADER", FeatureType::HEADER},
            {"ROAD", FeatureType::ROAD},
            {"LANE_GROUP", FeatureType::LANE_GROUP},
            {"LANE_BOUNDARY", FeatureType::LANE_BOUNDARY},
            {"GEOFENCE_FEATURE_INFO", FeatureType::GEOFENCE_FEATURE_INFO},
            {"LANE", FeatureType::LANE},
            {"OBJECT_TRAFFIC_LIGHT", FeatureType::OBJECT_TRAFFIC_LIGHT},
            {"OBJECT_PEDESTRIAN_CROSSING", FeatureType::OBJECT_PEDESTRIAN_CROSSING},
            {"SD_NODE", FeatureType::SD_NODE},
            {"INTERSECTION", FeatureType::INTERSECTION},
            {"ROUTING_PATH", FeatureType::ROUTING_PATH},
            {"ROUTING_GRAPH", FeatureType::ROUTING_GRAPH},
            {"ROUTING_PATH_ELEMENT", FeatureType::ROUTING_PATH_ELEMENT},
            {"ROUTING_POSITION", FeatureType::ROUTING_POSITION},
            {"ROUTING_REQUEST", FeatureType::ROUTING_REQUEST},
            {"ROUTING_EDGE", FeatureType::ROUTING_EDGE},
            {"CONNECTION", FeatureType::CONNECTION},
            {"ROUTING_NODE", FeatureType::ROUTING_NODE}, 
        };
        return data;
    }

    struct DataBlock
    {
        const char* pointer;
        ::std::size_t size;
    };

public:
    Base() = default;
    explicit Base(const FeatureType t) : type_(t) {}
    virtual ~Base() = default;

    static ::std::string GetClassName()
    {
        return ::std::string("Base");
    }

    static ::std::uint64_t GetMapFormatVersion()
    {
        holo::map::MapVersionParser const holo_map_format_version(
            HOLO_MAP_FORMAT_DEFINITION_VERSION_MAJOR,
            HOLO_MAP_FORMAT_DEFINITION_VERSION_PATCH, 
            HOLO_MAP_FORMAT_DEFINITION_VERSION_YEAR,
            static_cast<holo::map::MapVersionParser::VersionMonth>(HOLO_MAP_FORMAT_DEFINITION_VERSION_MONTH),
            HOLO_MAP_FORMAT_DEFINITION_VERSION_DAY, 
            static_cast<holo::map::MapVersionParser::VersionCode>(HOLO_MAP_FORMAT_DEFINITION_VERSION_CODE));

        return holo_map_format_version.GetVersionValue();
    }

    /**
     * @brief Access the concrete map freature type.
     *
     * @return Map feature type.
     */
    FeatureType GetFeatureType() const noexcept
    {
        return type_;
    }

    virtual ::std::uint64_t GetPrimaryKey() const = 0;
    virtual const DataBlock GetDataBlock() = 0;
    virtual void SetDataBlock(const DataBlock& _data_blocks) = 0;

protected:
    template <typename T>
    static ::std::size_t SizeOfVector(const ::std::vector<T>& _v);

    template <typename T>
    static void UniqueAppend(::std::vector<T>& _vec1, const ::std::vector<T>& _vec2);

    template <typename T, typename ::std::enable_if<::std::is_floating_point<T>::value, T>::type* = nullptr>
    static bool EqualTo(const T _a, const T _b);

    template <typename T, typename ::std::enable_if<::std::is_integral<T>::value, T>::type* = nullptr>
    static bool EqualTo(const T _a, const T _b);

    template <typename T, typename ::std::enable_if<!::std::is_arithmetic<T>::value, T>::type* = nullptr>
    static bool EqualTo(const T& _a, const T& _b);

    ::std::string str_data_;
    FeatureType type_ = FeatureType::UNKNOWN; ///< Indicate the concrete map feature type.

};  // class Base

template <typename T>
inline ::std::size_t Base::SizeOfVector(const ::std::vector<T>& _v)
{
    return _v.size() * sizeof(T);
}

template <typename T>
inline void Base::UniqueAppend(::std::vector<T>& _vec1,
                               const ::std::vector<T>& _vec2)
{
    _vec1.reserve(_vec1.size() + _vec2.size());
    for (::std::size_t i = 0; i < _vec2.size(); ++i)
    {
        if (::std::find(_vec1.begin(), _vec1.end(), _vec2[i]) == _vec1.end())
        {
            _vec1.push_back(_vec2[i]);
        }
    }
}

template <typename T, typename ::std::enable_if<::std::is_floating_point<T>::value, T>::type*>
inline bool Base::EqualTo(const T _a, const T _b)
{
    return (memcmp(&_a, &_b, sizeof(T)) == 0);
}

template <typename T, typename ::std::enable_if<::std::is_integral<T>::value, T>::type*>
inline bool Base::EqualTo(const T _a, const T _b)
{
    return (_a == _b);
}

template <typename T, typename ::std::enable_if<!::std::is_arithmetic<T>::value, T>::type*>
inline bool Base::EqualTo(const T& _a, const T& _b)
{
    return (_a == _b);
}

namespace helper
{

/**
 * @addtogroup helper
 * @{
 *
 */

/// Define feature id type for holo::map::format::xxx;
using FeatureIdType         = std::uint64_t;

/// Define feature id vector type for holo::map::format::xxx;
using FeatureIdVectorType   = std::vector<FeatureIdType>;

/// Define feature type for holo::map::format::helper.
using FeatureType           = holo::map::format::Base::FeatureType;

/// Define feature vector type for holo::map::format::helper.
using FeatureVectorType     = std::vector<FeatureType>;

/// Define shared pointer type for holo::map::format::Base.
using FeatureBaseSPtrType   = std::shared_ptr<holo::map::format::Base>;

/**
 * @brief Traits feature types from holo::map::format::xxx.
 */
template <class T>
struct FeatureTraits
{
    using RawType               = T;                            ///< Define self type for T.
    using PtrType               = T*;                           ///< Define pointer type for T.
    using SPtrType              = std::shared_ptr<T>;           ///< Define shared smart pointer type for T.
    using CSPtrType             = std::shared_ptr<T const>;     ///< Define shared smart pointer type for const T.
    using UPtrType              = std::unique_ptr<T>;           ///< Define unique smart pointer type for T.
    using CUPtrType             = std::unique_ptr<T const>;     ///< Define unique smart pointer type for const T.
}; ///< End of struct FeatureTraits

/**
 * @brief Traits feature types from holo::map::format::xxx*;
 */
template <class T>
struct FeatureTraits<T*>
{
    using RawType               = T;                            ///< Define self type for T.
    using PtrType               = T*;                           ///< Define pointer type for T.
    using SPtrType              = std::shared_ptr<T>;           ///< Define shared smart pointer type for T.
    using CSPtrType             = std::shared_ptr<T const>;     ///< Define shared smart pointer type for const T.
    using UPtrType              = std::unique_ptr<T>;           ///< Define unique smart pointer type for T.
    using CUPtrType             = std::unique_ptr<T const>;     ///< Define unique smart pointer type for const T.
}; ///< End of struct FeatureTraits

/**
 * @brief Traits feature types from holo::map::format::Ptrxxx*;
 */
template <class T>
struct FeatureTraits<std::shared_ptr<T>>
{
    using RawType               = T;                            ///< Define self type for T.
    using PtrType               = T*;                           ///< Define pointer type for T.
    using SPtrType              = std::shared_ptr<T>;           ///< Define shared smart pointer type for T.
    using CSPtrType             = std::shared_ptr<T const>;     ///< Define shared smart pointer type for const T.
    using UPtrType              = std::unique_ptr<T>;           ///< Define unique smart pointer type for T.
    using CUPtrType             = std::unique_ptr<T const>;     ///< Define unique smart pointer type for const T.
}; ///< End of struct FeatureTraits

/**
 * @brief Fetch all the feature types that defined in holo::map::format::Base.
 *
 * @return All the feature types.
 */
FeatureVectorType const& GetAllFeatureTypes();

/**
 * @brief Fetch all the available feature types.
 *
 * @note GetAllFeatureTypes() returns all the feature types, but some types has been deprecated in
 *       some projects, so GetAllAvailableFeatureTypes() can return all the available feature types.
 * @return  All the available feature types.
 */
FeatureVectorType const& GetAllAvailableFeatureTypes();

/**
 * @}
 *
 */

} ///< namespace helper

/**
 * @}
 *
 */

} ///< namespace format
} ///< namespace map
} ///< namespace holo

#endif  // HOLO_MAP_FORMAT_BASE_BASE_H_