/*!
 *  \brief Marshal common object to json string.
 *  \author wanghaiyang(wanghaiyang@holomaitc.com)
 *  \date 2019-08-29
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_MARSHAL_H_
#define HOLO_MAP_COMMON_MARSHAL_H_

#include <vector>
#include <string>

#include <holo/common/app_status.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/odometry.h>
#include <holo/common/road_type.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/common/preprocess.h>
#include <holo/map/format/common/geo_point.h>
#include <holo/map/format/common/id_interval_float64.h>
#include <holo/map/map_navigation_request.h>
#include <holo/map/road_ref_point_attributes.h>

namespace holo
{
namespace map
{
namespace marshal
{

/**
 * @brief Format a sequence container to a json string.
 * @param [in] c A sequence container.
 * @param [in] f A function for format single element to String.
 * @return Json string.
 */
template <typename T, typename Function, typename Container = std::vector<T>>
std::string FormatSequenceToString(Container const& c, Function f, std::size_t const limit = 5)
{
    std::stringstream stream;
    stream << "[";

    std::size_t const count = c.size();
    for (std::size_t i = 0; i < count && i < limit; ++i)
    {
        std::string const end = (i+1) < count ? ", " : "";
        stream << f(c[i]) << end;
    }

    stream << "]";
    return stream.str();
}

/**
 * @brief Format Value to json string.
 * @param [in] _point Point in 3D.
 * @return Json string.
 */
template <typename T>
std::string FormatToString(T const& _value);

/**
 * @brief Format values to json string.
 * @param [in] _values Value in array.
 * @return Json string.
 */
template <typename T>
static std::string FormatToString(std::vector<T> const& _values)
{
    std::stringstream stream;
    stream << "[";

    const std::size_t count = _values.size();
    for (std::size_t i = 0; i < count; ++i)
    {
        const std::string end = (i+1) < count ? ", " : "";
        if (std::is_same<T, int8_t>::value || std::is_same<T, uint8_t>::value)
        {
            stream << static_cast<int>(_values[i]) << end;
        }
        else
        {
            stream << _values[i] << end;
        }
    }

    stream << "]";
    return stream.str();
}

/**
 * @brief Format a Coordinate object to json string.
 * @param [in] coord A Coordinate object.
 * @return A Json string.
 */
std::string FormatToString(holo::common::Coordinate const& coord);

/**
 * @brief Format a gnss object to json string.
 * @param [in] pvt A GnssPvt object.
 * @return A Json string.
 */
std::string FormatToString(holo::common::GnssPvt const& pvt);

/**
 * @brief Format an Odometryd object to json string.
 * @param [in] odo An Odometryd object.
 * @return A Json string.
 */
std::string FormatToString(holo::common::Odometryd const& odo);

/**
 * @brief Format an LocalMapOdometryd object to json string.
 * @param [in] odo An LocalMapOdometryd object.
 * @return A Json string.
 */
std::string FormatToString(holo::common::LocalMapOdometryd const& odo);

/**
 * @brief Format an LocalMapOdometryd result object to json string.
 * @param [in] odo An LocalMapOdometryd result object.
 * @return A Json string.
 */
std::string FormatMatchingResultToString(holo::common::LocalMapOdometryd::MatchingResult const& result);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] _point GeoPoint.
 * @return Json string.
 */
std::string FormatToString(format::GeoPoint const& _point);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] _point MapPoint3.
 * @return Json string.
 */
std::string FormatToString(MapPoint3 const& _point);

/**
 * @brief Format Position to json string.
 * @param [in] _position Position.
 * @return Json string.
 */
std::string FormatToString(map::format::Position const& _position);

/**
 * @brief Format vector of positions to json string.
 * @param [in] _positions vector of positions.
 * @return Json string.
 */
std::string FormatToString(std::vector<map::format::Position> const& _positions);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] _point MapPoint.
 * @return Json string.
 */
std::string FormatToString(MapPoint const& _point);

/**
 * @brief Format MapPoint to json string.
 * @param [in] p MapPoint with coordinate info.
 * @return Json string.
 */
std::string FormatToString(format::geometry::GeographicParameterType<MapPoint> const& p);

/**
 * @brief Format MapPoint3 to json string.
 * @param [in] p MapPoint3 with coordinate info.
 * @return Json string.
 */
std::string FormatToString(format::geometry::GeographicParameterType<MapPoint3> const& p);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] p GeoPoint with coordinate info.
 * @return Json string.
 */
std::string FormatToString(format::geometry::GeographicParameterType<format::GeoPoint> const& p);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] _points GeoPoint array.
 * @return Json string.
 */
std::string FormatToString(std::vector<format::GeoPoint> const& _points);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] _points MapPoint3 array.
 * @return Json string.
 */
std::string FormatToString(std::vector<MapPoint3> const& _points);

/**
 * @brief Format GeoPoint to json string.
 * @param [in] _points MapPoint array.
 * @return Json string.
 */
std::string FormatToString(std::vector<MapPoint> const& _points);

/**
 * @brief Format holo::common::RoadType to json string.
 * @param [in] road_type A holo::common::RoadType object.
 * @return Json string.
 */
std::string FormatToString(holo::common::RoadType const& road_type);

/**
 * @brief Format holo::map::RoadTypeInterval to json string.
 * @param [in] road_type_interval A holo::map::RoadTypeInterval object.
 * @return Json string.
 */
std::string FormatToString(holo::map::RoadTypeInterval const& road_type_interval);

/**
 * @brief Format holo::map::RoadTypeInterval array to json string.
 * @param [in] road_type_intervals holo::map::RoadTypeInterval object array.
 * @return Json string.
 */
std::string FormatToString(holo::map::RoadRefPointAttributes<holo::map::RoadTypeInterval> const& road_type_intervals);

/**
 * @brief Format holo::map::format::id_interval_float64 to json string.
 * @param [in] id A holo::map::format::id_interval_float64 object.
 * @return Json string.
 */
std::string FormatToString(holo::map::format::IdIntervalFloat64 const& id);

/**
 * @brief Format holo::map::format::id_interval_float64s to json string.
 * @param [in] ids A holo::map::format::id_interval_float64 object array.
 * @return Json string.
 */
std::string FormatToString(std::vector<holo::map::format::IdIntervalFloat64> const& ids);

/**
 * @brief Format holo::common::AppStatus to json string.
 * @param [in] app_status holo::common::AppStatus object.
 * @return Json string.
 */
std::string FormatToString(holo::common::AppStatus const& app_status);

/**
 * @brief Format holo::map::NavigationPoint to json string.
 * @param [in] navigation_point holo::map::NavigationPoint object.
 * @return Json string.
 */
std::string FormatToString(holo::map::NavigationPoint const& navigation_point);

} // namespace marshal
} // namespace map
} // namespace holo

#include "details/format_marshal.hpp"

#endif //HOLO_MAP_COMMON_MARSHAL_H_
