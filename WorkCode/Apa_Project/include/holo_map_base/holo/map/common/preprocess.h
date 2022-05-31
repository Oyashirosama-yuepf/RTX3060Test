/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file preprocess.h
 * @brief Preprocessing functions for holo::map::format::***
 * @author wanghaiyang@holomatic.com
 * @date "2021-05-20"
 */

#ifndef HOLO_MAP_COMMON_PREPROCESS_H_
#define HOLO_MAP_COMMON_PREPROCESS_H_

#include <holo/common/coordinate.h>
#include <holo/map/common/types.h>

namespace holo
{
namespace map
{
namespace format
{
namespace geometry
{
/**
 * @addtogroup geometry
 * @{
 *
 */

/**
 * @brief An enclosure for geographic feature with coordinate reference system.
 * 
 * @tparam T holo::map::format::GeoPoint/GeoBox.
 * @tparam C holo::common::Coordinate.
 */
template <typename T, typename C>
struct GeographicParameter
{
    /// Redefine geographic feature type for inner members.
    using ParameterType = T;
    /// Redefine coordinate reference system type for inner members.
    using CoordinateType = C;

    /**
     * @brief Default constructor.
     */
    GeographicParameter()
    {
    }

    /**
     * @brief Default constructor.
     * 
     * @param[in] p A geographic feature.
     * @param[in] c Coordinate reference system.
     */
    GeographicParameter(ParameterType p, CoordinateType c) : parameter(p), coordinate(c)
    {}

    /// Geographic feature with postion, like: holo::map::format::GeoBox/GeoPoint.
    ParameterType   parameter;
    /// Coordinate reference system for geographic feature(parameter).
    CoordinateType  coordinate;
};

/**
 * @brief Check if input GCS(longitude and latitude) point is valid.
 * @note Reference resources: holo_base_c::geographical_transformation.c
 * @tparam T GCSParameter with holo::map::format::GeoPoint/MapPoint/MapPoint3.
 * @param[in] p GCS point.
 *
 * @return true:  This point is valid for GCS.
 * @return false: This point is invalid.
 */
template <typename T>
holo::bool_t IsValidGCSPoint(T const& p);

/**
 * @brief Convert coordinate reference system of a geographic feature to WGS84.
 * 
 * @tparam T GeographicParameter with holo::map::format::GeoBox/GeoPoint.
 * @param[in] in Geographic feature with UTM coordinate reference system.
 * @param[out] out Geographic feature with WGS84 coordinate reference system.
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T>
holo::bool_t ConvertUTMToWGS84(T in, T out);

/**
 * @brief Convert coordinate reference system of a geographic feature to UTM.
 * 
 * @tparam T GeographicParameter with holo::map::format::GeoBox/GeoPoint.
 * @param[in] in Geographic feature with WGS84 coordinate reference system.
 * @param[out] out Geographic feature with UTM coordinate reference system.
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T>
holo::bool_t ConvertWGS84ToUTM(T in, T out);

/**
 * @brief Convert a geographic feature to UTM CRS(Coordinate reference system).
 *
 * @note CRS can be WGS84, UTM3, UTM6.
 * @tparam T GeographicParameter with MapPoint, MapPoint3, GeoPoint.
 * @param[in] in A geographic feature with CRS info.
 * @param[out] out A geographic feature with UMT CRS info.
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T>
holo::bool_t ConvertToUTM(T in, T out);

/**
 * @brief Convert a geographic feature to special UTM CRS(Coordinate reference system).
 *
 * @note CRS only support WGS84, UTM6.
 * @tparam T GeographicParameter with MapPoint, MapPoint3, GeoPoint.
 * @param[in] in A geographic feature with CRS info.
 * @param[in] c Target coordinate reference system, note: it must be UTM6 now.
 * @param[out] out A geographic feature with special UMT CRS info.
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T, typename C>
holo::bool_t ConvertToUTMV2(T in, C const& c, T out);

/**
 * @brief Convert a geographic feature to WGS84 CRS(Coordinate reference system).
 *
 * @note CRS can be WGS84, UTM6.
 * @tparam T GeographicParameter with MapPoint, MapPoint3, GeoPoint.
 * @param[in] in A geographic feature with CRS info.
 * @param[out] out A geographic feature with WGS84 CRS info.
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T>
holo::bool_t ConvertToWGS84(T in, T out);

/**
 * @brief Convert coordinate between holo::map::format::Coordinate and holo::common::Coordinate
 *
 * @tparam T holo::map::format::Coordinate/holo::common::Coordinate
 * @tparam C holo::common::Coordinate/holo::map::format::Coordinate
 * @param[in] in A holo::map::format::Coordinate/holo::common::Coordinate.
 * @param[out] out A holo::common::Coordinate/holo::map::format::Coordinate.
 */
template <typename T, typename C>
void CovertCoordinate(T const& in, C& out);

/**
 * @brief Calculate bounding box for map feature.
 * 
 * @tparam T holo::map::format::PtrRoad.
 *           holo::map::format::PtrLane.
 *           holo::map::format::PtrLaneGroup.
 *           holo::map::format::PtrLaneBoundary.
 *           holo::map::format::PtrObject***.
 * @tparam B holo::map::format::GeoBox.
 * @param[in] t A map feature shared pointer, like: holo::map::format::PtrRoad/Lane/etc...
 * @param[in] b A bounding box object, link: holo::map::format::Box;
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T, typename B>
holo::bool_t CalculateBoundingBox2D(T& t, B& b);

/**
 * @brief Calculate bounding box for map feature.
 * 
 * @tparam T holo::map::format::PtrRoad.
 *           holo::map::format::PtrLane.
 *           holo::map::format::PtrLaneGroup.
 *           holo::map::format::PtrLaneBoundary.
 *           holo::map::format::PtrObject***.
 * @tparam B holo::map::format::GeoBox.
 * @param[in] t A map feature shared pointer, like: holo::map::format::PtrRoad/Lane/etc...
 * @param[in] b A bounding box object, link: holo::map::format::Box;
 * @return true: No error;
 *         false: An error occurs in this function, please see logs for more details.
 */
template <typename T, typename B>
holo::bool_t CalculateBoundingBox2D(T const& t, B& b);

/**
 * @brief Check if two bounding boxes are overlapped.
 * 
 * @tparam T holo::map::format::Box;
 * @param[in] box1 A bounding box object.
 * @param[in] box2 Another bounding box object.
 * @return true: They are overlapped.
 *         false: otherwise.
 */
template <typename B>
holo::bool_t AreBoundingBoxesOverlapped2D(B const& box1, B const& box2);

/**
 * @}
 *
 */
} ///< namespace geometry
} ///< namespace format
} ///< namespace map
} ///< namespace holo

#include "details/preprocess.hpp"

#endif /* HOLO_MAP_COMMON_PREPROCESS_H_ */