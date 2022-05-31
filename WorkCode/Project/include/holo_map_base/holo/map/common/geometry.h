/*!
 *  \brief Geometry
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_GEOMETRY_H_
#define HOLO_MAP_COMMON_GEOMETRY_H_

#include <utility>
#include <vector>

#include <holo/common/coordinate.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/convex_polygon2.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/geographical_transformation.h>

#include <holo/map/common/classes/latlon.h>
#include <holo/map/common/classes/latlonh.h>
#include <holo/map/common/classes/latlonxyh.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/common/math.h>
#include <holo/map/common/types.h>
#include <holo/map/common/utility.h>
#include <holo/map/common/preprocess.h>

#include <holo/map/format/common/position.h>
#include <holo/map/format/common/geo_box.h>
#include <holo/map/format/common/geo_circle.h>
#include <holo/map/format/common/geo_point.h>

/*
@TODO

GetPose has duplicates
Down and up sampling has duplicates
AreSameRingsIn2D() use reference instead of copy assignments?
GetUnClosedPolygon() ??? opened?
IsPolygonVectorContained?? reference??
IsPointInSimplePolyogn ??? typo
LineFitDP?? what is it doing ?

*/

/**
 * @addtogroup holo
 *
 * @{
 */
namespace holo
{
/**
 * @addtogroup map
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup geometry
 *
 * @{
 */
namespace geometry
{
/**
 *@brief Define a bounding box
 */
struct Envelope
{
    holo::float64_t min_x = 0.0;
    holo::float64_t min_y = 0.0;
    holo::float64_t max_x = 0.0;
    holo::float64_t max_y = 0.0;

    Envelope(holo::float64_t x_min, holo::float64_t y_min, holo::float64_t x_max, holo::float64_t y_max)
            :min_x(x_min), min_y(y_min), max_x(x_max), max_y(y_max){}

    Envelope() = default;
    Envelope(Envelope const& env) = default;
    Envelope& operator=(Envelope const& env) = default;
};

/**
 * @brief Merge two Envelope instances into one.
 * @param[in] left_box first instance to be merged
 * @param[in] right_box second instance to be merged
 * @param[out] mix_box Merged Envelope instance
 * @return
 */
void MergeEnvelope(holo::map::geometry::Envelope const& left_box,
                   holo::map::geometry::Envelope const& right_box,
                   holo::map::geometry::Envelope& mix_box);

/**
 * @brief Merge Envelope instances vector into one.
 * @param[in] boxes Envelope instances to be merged
 * @param[out] mix_box Merged Envelope instance
 * @return
 */
void MergeEnvelope(std::vector<holo::map::geometry::Envelope> const& boxes,
                   holo::map::geometry::Envelope& mix_box);

/**
 * @brief Judge whether the two boxes intersect
 * @param[in] right_box Envelope instance to be merged
 * @param[in] left_box Envelope instance to be merged
 * @return true or false
 */
holo::bool_t AreEnvelopesOverlaped(holo::map::geometry::Envelope const& right_box,
                                   holo::map::geometry::Envelope const& left_box);

/**
 *@brief Define a polygon composed of a exterior ring and multiple interior rings
 */
struct Polygon
{
    /// Exterior ring
    ::std::vector<format::GeoPoint> exterior_ring;
    /// Interior rings
    ::std::vector<::std::vector<format::GeoPoint>> interior_rings;

    void operator=(const ::holo::map::geometry::Polygon& _other)
    {
        exterior_ring.clear();
        interior_rings.clear();
        exterior_ring = _other.exterior_ring;
        interior_rings.reserve(_other.interior_rings.size());
        for (std::size_t i = 0; i < _other.interior_rings.size(); i++)
        {
            interior_rings.emplace_back(_other.interior_rings[i]);
        }
    }
    void swap(::holo::map::geometry::Polygon& _other)
    {
        this->exterior_ring.swap(_other.exterior_ring);
        this->interior_rings.swap(_other.interior_rings);
    }
};

/**
 * @brief Get X coordinate of a point
 * @param[in] _point Point to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const MapPoint& _point)
{
    return _point.GetX();
}

/**
 * @brief Get X coordinate of a vector
 * @param[in] _vec Vector to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const MapVector2& _vec)
{
    return _vec.At(0);
}

/**
 * @brief Get X coordinate of a point
 * @param[in] _vec Vector to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const MapVector3& _vec)
{
    return _vec.At(0);
}

/**
 * @brief Get X coordinate of a point
 * @param[in] _point Point to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const MapPoint3& _point)
{
    return _point.GetX();
}

/**
 * @brief Get X coordinate of a point
 * @param[in] _point Point to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const format::GeoPoint& _point)
{
    return _point.GetX();
}

/**
 * @brief Get X coordinate of a point
 * @param[in] _point Point to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const LLXYH& _point)
{
    return _point.GetX();
}

/**
 * @brief Get X coordinate of a point
 * @param[in] _point Point to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const MapPose3& _point)
{
    return _point.GetX();
}

/**
 * @brief Get X coordinate of a point
 * @param[in] _point Point to be checked
 * @return X coordinate of point in units of meters
 */
inline Distance GetX(const format::Position& _point)
{
    return _point.GetX();
}

/**
 * @brief Get Y coordinate of a point
 * @param[in] _point Point to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const MapPoint& _point)
{
    return _point.GetY();
}

/**
 * @brief Get Y coordinate of a vector
 * @param[in] _vec Vector to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const MapVector2& _vec)
{
    return _vec.At(1);
}

/**
 * @brief Get Y coordinate of a vector
 * @param[in] _vec Vector to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const MapVector3& _vec)
{
    return _vec.At(1);
}

/**
 * @brief Get Y coordinate of a point
 * @param[in] _point Point to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const MapPoint3& _point)
{
    return _point.GetY();
}

/**
 * @brief Get Y coordinate of a point
 * @param[in] _point Point to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const format::GeoPoint& _point)
{
    return _point.GetY();
}

/**
 * @brief Get Y coordinate of a point
 * @param[in] _point Point to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const LLXYH& _point)
{
    return _point.GetY();
}

/**
 * @brief Get Y coordinate of a point
 * @param[in] _point Point to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const MapPose3& _point)
{
    return _point.GetY();
}

/**
 * @brief Get Y coordinate of a point
 * @param[in] _point Point to be checked
 * @return Y coordinate of point in units of meters
 */
inline Distance GetY(const format::Position& _point)
{
    return _point.GetY();
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _point Point to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const MapPoint& _point)
{
    (void)_point;
    return 0;
}

/**
 * @brief Get Z coordinate of a vector
 * @param[in] _vec Vector to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const MapVector2& _vec)
{
    (void)_vec;
    return 0;
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _vec Vector to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const MapVector3& _vec)
{
    return _vec.At(2);
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _point Point to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const MapPoint3& _point)
{
    return _point.GetZ();
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _point Point to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const format::Position& _point)
{
    // cm to m
    return _point.GetHeightCm() * 0.01;
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _point Point to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const format::GeoPoint& _point)
{
    // cm to m
    return static_cast<Distance>(_point.GetHeightCm()) / 100.0;
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _point Point to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const LLXYH& _point)
{
    return _point.GetZ();
}

/**
 * @brief Get Z coordinate of a point
 * @param[in] _point Point to be checked
 * @return Z coordinate of point in units of meters
 */
inline Distance GetZ(const MapPose3& _point)
{
    return _point.GetZ();
}

/**
 * @brief Check if two points are overlapped in 2D (XY)
 * @tparam T,Y  MapPoint, MapPoint3, GeoPoint
 * @param[in] _p1 Point 1 (in different forms)
 * @param[in] _p2 Point 2 (in different forms)
 * @param[in] _max_span Maximal allowed distance between both points
 * @return true Two points are overlapped
 * @return false Otherwise
 */
template <typename T, typename Y>
bool AreSamePointsIn2D(const T& _p1, const Y& _p2, const double _max_span = 0.001 /* 1 mm */)
{
    return MapPoint(geometry::GetX(_p1), geometry::GetY(_p1)).Dist(MapPoint(geometry::GetX(_p2), geometry::GetY(_p2))) <
           _max_span;
}

/**
 * @brief Check if two points are overlapped in 3D (XYZ)
 * @tparam T,Y MapPoint, MapPoint3, GeoPoint
 * @param[in] _p1 Point 1 (in different forms)
 * @param[in] _p2 Point 2 (in different forms)
 * @param[in] _max_span Maximal allowed distance between both points
 * @return true Two points are overlapped
 * @return false Otherwise
 */
template <typename T, typename Y>
bool AreSamePointsIn3D(const T& _p1, const Y& _p2, const double _max_span = 0.001 /* 1 mm */)
{
    return MapPoint3(geometry::GetX(_p1), geometry::GetY(_p1), geometry::GetZ(_p1))
               .Dist(MapPoint3(geometry::GetX(_p2), geometry::GetY(_p2), geometry::GetZ(_p2))) < _max_span;
}
/**
 * @brief Append a line to the end of another line (in different format)
 * @tparam T1 GeoPoint, MapPoint3, MapPoint
 * @tparam T2 GeoPoint, MapPoint3, MapPoint
 * @param[out] _line1 Line to be extended
 * @param[in] _line2 Line (or part of it) to append to the end of _vec1.
 * @param[in] _start_id Left boundary of _line2 in terms of point index, if only part of it to be specified. Default
 * value is 0, indicating from the beginning.
 * @param[in] _end_id Right boundary of _line2 in terms of point index, if only part of it to be specified. Default
 * value is 0, indicating to the end.
 * @return true If the operation is successfully completed.
 * @return false Otherwise
 */
template <typename T1, typename T2>
bool AppendLine(std::vector<T1>& _line1, const std::vector<T2>& _line2, const Size _start_id = 0, Size _end_id = 0);

/**
 * @brief Insert a point before specified position of a line
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in,out] _line Line to be modified
 * @param[in] _p Point to insert
 * @param[in] _position Position on the line where point _p is inserted.
 * @details For example, if you want to insert a point at the head of line, _position shall be 0; if you want to insert
 * a point before the 2nd point of line, _position shall be 1; if you want to push a point at the tail of line,
 * _position shall be line.size().
 * @return true If operation succeeded
 */
template <typename T>
bool InsertPoint(std::vector<T>& _line, const T& _p, const Size _position);

/**
 * @brief Add a value into vector if there is no duplicates inside
 * @param[in] _vec Vector to be extended
 * @param[in] _data The element to be pushed to the tail of vector
 */
inline void UniquePush(std::vector<format::GeoPoint>& _vec, const format::GeoPoint& _data)
{
    // make sure the element to be added is unique in the vector
    bool duplicated = false;
    for (const format::GeoPoint& p : _vec)
    {
        if (AreSamePointsIn3D(p, _data))
        {
            duplicated = true;
            break;
        }
    }
    if (!duplicated)
    {
        _vec.push_back(_data);
    }
}

/**
 * @brief Get target point between two points according to the scale in 2D distance
 * @param[in] _p1 Starting point
 * @param[in] _p2 End point
 * @param[in] _scale Percentage of target point to _p1 w.r.t the 2D distance between _p1 and _p2
 * @return Point in-between
 */
MapPoint GetRoughScaledPoint(const MapPoint& _p1, const MapPoint& _p2, const double _scale);

/**
 * @brief Get target point between two points according to the scale in 2D distance
 * @param[in] _p1 Starting point
 * @param[in] _p2 End point
 * @param[in] _scale Percentage of target point to _p1 w.r.t the 2D distance between _p1 and _p2
 * @return Point in-between
 */
LL GetRoughScaledPoint(const LL& _p1, const LL& _p2, const double _scale);

/**
 * @brief Get target point between two points according to the scale in 2D distance
 * @param[in] _p1 Starting point
 * @param[in] _p2 End point
 * @param[in] _scale Percentage of target point to _p1 w.r.t the 2D distance between _p1 and _p2
 * @return Point in-between
 */
MapPoint3 GetRoughScaledPoint(const MapPoint3& _p1, const MapPoint3& _p2, const double _scale);

/**
 * @brief Get target point between two points according to the scale in 2D distance
 * @param[in] _p1 Starting point
 * @param[in] _p2 End point
 * @param[in] _scale Percentage of target point to _p1 w.r.t the 2D distance between _p1 and _p2
 * @return Point in-between
 */
format::GeoPoint GetRoughScaledPoint(const format::GeoPoint& _p1, const format::GeoPoint& _p2, const double _scale);

/**
 * @brief Get target point between two points according to the scale in 2D distance
 * @param[in] _p1 Starting point
 * @param[in] _p2 End point
 * @param[in] _scale Percentage of target point to _p1 w.r.t the 2D distance between _p1 and _p2
 * @return Point in-between
 */
LLXYH GetRoughScaledPoint(const LLXYH& _p1, const LLXYH& _p2, const double _scale);

/**
 * @brief Calculate target point given bearing and distance w.r.t a reference point in 2D
 * @param[in] _lat_ori_deg Latitude of reference point in units of degrees
 * @param[in] _lon_ori_deg Longitude of reference point in units of degrees
 * @param[in] _distance_meter Expected distance from target point to reference point, given in meters
 * @param[in] _bearing_deg Expected bearing angle from target point to reference point, given in degrees
 * @param[out] _lat_dest_deg Latitude of target point in units of degrees
 * @param[out] _lon_dest_deg Longitude of target point in units of degrees
 */
void GetPointByDistanceAndBearing(const MapDegree _lat_ori_deg, const MapDegree _lon_ori_deg,
                                  const Distance _distance_meter, const MapDegree _bearing_deg,
                                  MapDegree& _lat_dest_deg, MapDegree& _lon_dest_deg);

/**
 * @brief Calculate target point given bearing and distance w.r.t a reference point in 2D
 * @param[in] _ref Reference point in types of LL(lat/lon)
 * @param[in] _distance_meter Expected distance from target point to reference point, given in meters
 * @param[in] _bearing_deg Expected bearing angle from target point to reference point, given in degrees
 * @return Target point in types of LL(lat/lon)
 */
LL GetPointByDistanceAndBearing(const LL& _ref, const Distance _distance_meter, const MapDegree _bearing_deg);

/**
 * @brief Calculate target point given bearing and distance w.r.t a reference point in 2D
 * @param[in] _ref Reference point in types of MapPoint
 * @param[in] _distance_meter Expected distance from target point to reference point, given in meters
 * @param[in] _bearing_deg Expected bearing angle from target point to reference point, given in degrees
 * @return Target point in types of MapPoint
 */
MapPoint GetPointByDistanceAndBearing(const MapPoint& _ref, const Distance _distance_meter,
                                      const MapDegree _bearing_deg);

/**
 * @brief Calculate the initial bearing (in degrees) from point 2 to point 1
 * @param[in] _lat1 Latitude of point1
 * @param[in] _lon1 Longitude of point1
 * @param[in] _lat2 Latitude of point2
 * @param[in] _lon2 Longitude of point2
 * @return Bearing angle in units of degrees
 */
MapDegree GetBearingBetweenPoints(const MapDegree _lat1, const MapDegree _lon1, const MapDegree _lat2,
                                  const MapDegree _lon2);

/**
 * @brief Calculate the initial bearing (in degrees) from point 2 to point 1
 * @param[in] _p1 Point 1 in terms of LL(lat/lon)
 * @param[in] _p2 Point 2 in terms of LL(lat/lon)
 * @return Bearing angle in units of degrees
 */
MapDegree GetBearingBetweenPoints(const LL& _p1, const LL& _p2);

/**
 * @brief Get closest point on a line w.r.t a reference point, considering only 2D distance
 * @param[in] _ref_point Reference point
 * @param[in] _line Line
 * @param[out] _result Closest point on the line w.r.t target point
 * @param[out] _index Index of the closest point on the line
 * @return true: Closest point is obtained successfully
 * @return false Otherwise
 */
template <typename T>
bool GetClosestPoint2D(const T& _ref_point, const std::vector<T>& _line, T& _result, Size& _index);

/**
 * @brief Get closest point of a line w.r.t target point by local search. This is faster than GetClosestPoint2D which
 * performs global search
 * @details Define the "in-between distance" as the distance from target to each points of reference line. "Local
 * search" means the search will stop if the "in-between distance" decreases and then increases. This means the local
 * optimal value is found. Global search means we will traverse all points of reference line.
 * @param[in] _target Target point
 * @param[in] _positions Reference line
 * @param[out] _closest_point Closest point calculated in this function
 * @param[out] _index Index of the closest point in reference line
 * @param[out] _min_distance Distance from target point to reference line
 * @param[in] _start_id Index of point of reference line where search begins
 * @param[in] _check_num Number of points used for local search
 * @return true: Closest point has been found successfully
 * @return false Otherwise
 */
template <typename T>
bool GetClosestPoint2D(const T& _target, const std::vector<T>& _positions, T& _closest_point, Size& _index,
                       Distance& _min_distance, const Size _start_id = 0, const Size _check_num = 5);

/**
 * @brief Down-sample a vector of points by indicating the minimal distance between points
 * @details This is not a precise sampling. It can only guarantee that the distance
 * between neighbouring points is larger than the specific distance. Some points will be deleted for this purpose. There
 * is no interpolation between points.
 * @tparam T GeoPoint, MapPoint3, MapPoint
 * @param[in] _points A vector of points that compose a line
 * @param[in] _step Minimal distance between points
 * @param[out] _sampled_points Sampled points
 * @param[out] _sampled_ids Associated ids in original points
 * @return true If the operation succeeded
 * @return true Otherwise
 */
template <typename T>
bool DownSampleRefPoints(const std::vector<T>& _points, const float64_t _step, std::vector<T>& _sampled_points,
                         std::vector<MapFeatureIdType>& _sampled_ids);

/**
 * @brief Calculate the projection of target point to a line formed by a vector of reference points.
 * @details A line can be thought as a sequence of small-sized line segments, termed as "sub-line" herein. This task can
 * be simplified to finding out a target sub-line with the minimal distance to target point.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _pos_target Target point
 * @param[in] _points Vector of points that form a line
 * @param[out] _first_id Index of the left point of target sub-line
 * @param[out] _second_id Index of the right point of target sub-line
 * @param[out] _project_point Projection of target point on target sub-line
 * @param[in] _min_distance Distance from target point to target sub-line
 * @param[in] _is_outside Indicates whether the target can be projected outside the line
 * @param[in] _local_check True for a (rapid) local search; False for global search.
 * @param[in] _start_idx Starting position of local search
 * @param[in] _check_num Number of points to be checked for local search
 * @return true if Operation succeeded.
 * @return false Otherwise.
 */
template <typename T>
bool CalculateDistanceToPoints2D(const T& _pos_target, const std::vector<T>& _points, Size& _first_id, Size& _second_id,
                                 T& _project_point, Distance& _min_distance, bool& _is_outside,
                                 const bool _local_check = false, const Size _start_idx = 0, const Size _check_num = 5);

/**
 * @brief Packaged result associated to CalculateDistanceToPoints2D()
 * @tparam T MapPoint, MapPoint3 or GeoPoint
 */
template <typename T>
struct ResultDistToLine
{
    /// Left idx of projected point on reference line
    Size first_id = 0;
    /// Right idx of projected point on reference line
    Size second_id = 0;
    /// Projected point on reference line
    T project_point;
    /// Distance to reference line
    Distance min_distance = 0.0;
    /// Indicator about whether target point can be projected outside reference line
    bool is_outside = false;
};

/**
 * @brief Another form of CalculateDistanceToPoints2D() with results given in a struct format
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _pos_target Target point
 * @param[in] _points Reference line
 * @param[out] _result Results for "projection". @see ResultDistToLine
 * @param[in] _local_check True for a (rapid) local search; False for global search.
 * @param[in] _start_idx Starting position of local search
 * @param[in] _check_num Number of points to be checked for local search
 * @return true If operation succeeded
 */
template <typename T>
bool CalculateDistanceToPoints2D(const T& _pos_target, const std::vector<T>& _points, ResultDistToLine<T>& _result,
                                 const bool _local_check = false, const Size _start_idx = 0, const Size _check_num = 5);

/**
 * @brief Result parameters from CalculateDistanceToPoints2DExt().
 * @tparam T MapPoint, MapPoint3 or GeoPoint
 */
template <typename T>
struct ResultDistanceToPointsExt
{
    /// Result form CalculateDistanceToPoints2D.
    ResultDistToLine<T> result;
    /// Distance between projection point and the first point(at the index of result.first_id).
    Distance projection_to_first_distance   = 0.0;
    /// Distance between projection point and the second point(at the index of result.second_id).
    Distance projection_to_second_distance  = 0.0;
    /// Distance between projection point and the head point(start point) of input points.
    Distance projection_to_start_distance   = 0.0;
    /// Distance between projection point and the tail point(end point) of input points.
    Distance projection_to_end_distance     = 0.0;
    /// If 'result.is_outside' is true, this parameter is effective, otherwise ineffective,
    /// if true, the projection point at the side of start point of input points,
    /// if false, the projection point at the side of end point of input points.
    holo::bool_t outsize_of_start_or_end    = false;
};

/**
 * @brief Calculate relationship between a target point and a line with multiple points.
 *
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _pos_target Target point.
 * @param[in] _points A line with multiple points.
 * @param[out] _result Results for "projection". @see ResultDistanceToPointsExt.
 * @param[in] _local_check True for a (rapid) local search; False for global search.
 * @param[in] _start_idx Starting position of local search
 * @param[in] _check_num Number of points to be checked for local search
 * @return true If operation succeeded
 */
template <typename T>
holo::bool_t CalculateDistanceToPoints2DExt(T const& target, std::vector<T> const& points, ResultDistanceToPointsExt<T>& result,
    const bool local_check = false, const Size start_idx = 0, const Size check_num = 5);

/**
 * @brief Given two lines, find out a sub-line for each. Both selected sub-lines shall be roughly parallel.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line1 Line 1
 * @param[in] _line2 Line 2
 * @param[out] _lane_fixed_1 Fixed line 1 after alignment
 * @param[out] _lane_fixed_2 Fixed line 2 after alignment
 * @param[out] _left_id_line1 Left boundary of fixed line 1 on original line 1
 * @param[out] _right_id_line1 Right boundary of fixed line 1 on original line 1
 * @param[out] _left_id_line2 Left boundary of fixed line 2 on original line 2
 * @param[out] _right_id_line2 Right boundary of fixed line 2 on original line 2
 * @return true If the operation succeeded
 */
template <typename T>
bool AlignTwoLanes(const std::vector<T>& _line1, const std::vector<T>& _line2, std::vector<T>& _line_fixed_1,
                   std::vector<T>& _line_fixed_2, Size& _left_id_line1, Size& _right_id_line1, Size& _left_id_line2,
                   Size& _right_id_line2);

/**
 * @brief Calculate (approximately) averaged distance between two lines
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line1 Line 1 composed of sampling points
 * @param[in] _line2 Line 2 composed of sampling points
 * @param[in] step Sampling distance for points
 * @param[in] trunctation_ratio Percentage of points at head to ignore in terms of integer lower than 100.
 * @return Distance in-between
 */
template <typename T>
double CalculateAverageDistance2D(const std::vector<T>& _lane1, const std::vector<T>& _lane2, ::std::uint32_t step = 1,
                                  float trunctation_ratio = 0);

/**
 * @brief Derive lane boundaries of given lanes
 * @note NOTICE!!!THIS FUNCTION HAS A BUG caused by extreme case such as on a
 * corner the closest point near by p is q rather p1 or p2.
 *
 * ****************************q
 *                                          *
 * **************************
 *                                              *
 *                             *
 * ***************************P                 *
 *
 * ***************p1                         *p2
 *
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _left_lane_ref_points Reference points of left lane
 * @param[in] _right_lane_ref_points Reference points of right lane
 * @param[out] _left_lane_boundary  Lane boundary left to the left lane
 * @param[out] _middle_lane_boundary Lane boundary between both lanes
 * @param[out] _right_lane_boundary Lane boundary right to the right lane
 * @return true If the operation succeeded
 */
template <typename T>
bool BuildLaneBoundaries2D(const std::vector<T>& _left_lane_ref_points, const std::vector<T>& _right_lane_ref_points,
                           std::vector<T>& _left_lane_boundary, std::vector<T>& _middle_lane_boundary,
                           std::vector<T>& _right_lane_boundary);

/**
 * @brief Derive lane boundaries from given lane middle line
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _left_lanemark_ref_points Reference points of left lane mark
 * @param[in] _right_lanemark_ref_points Reference points of right lane mark
 * @param[out] _lane Lane middle line
 * @return true If the operation succeeded
 */
template <typename T>
bool BuildLaneBoundaries2D(const std::vector<T>& _left_lanemark_ref_points,
                           const std::vector<T>& _right_lanemark_ref_points, std::vector<T>& _lane);

/**
 * @brief Derive lane boundaries from given lane middle line
 * @note Compare the percentage positions of two points on their
 *       respective lines to determine whether one point needs to be advanced.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _left_lanemark_ref_points Reference points of left lane mark
 * @param[in] _right_lanemark_ref_points Reference points of right lane mark
 * @param[out] _lane Lane middle line
 * @return true If the operation succeeded
 */
template <typename T>
bool BuildLaneBoundaries2DV2(const std::vector<T>& _left_lanemark_ref_points,
                             const std::vector<T>& _right_lanemark_ref_points, std::vector<T>& _lane);

/**
 * @brief Derive multiple lane marks by left and right lane center lines
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _left_lane_ref_points Center line of left lane
 * @param[in] _right_lane_ref_points Center line of right lane
 * @param[out] lines Vector containing lane marks and probably an additional lane.if size is 5, the elements are
 * ordered as Id 0 = middle lane reference points Id 1 = lane mark
 * @param[out] ids Indices of lines
 * @return true If operation succeeded
 */
template <typename T>
bool CalculateLaneMarks(const std::vector<T>& _left_lane_ref_points, const std::vector<T>& _right_lane_ref_points,
                        std::vector<std::vector<T>>& lines, std::vector<std::pair<T, T>>& ids);

/**
 * @brief Calculate lane marks by reference points on left, right and middle lanes
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _left_lane_ref_points Refpoints of left lane
 * @param[in] _middle_lane_ref_points Refpoints of middle lane
 * @param[in] _right_lane_ref_points Refpoints of right lane
 * @param[out] lines Lines in-between
 * @param[out] ids Indices of lines
 * @return true If operation succeeded
 * @return false Otherwise *
 */
template <typename T>
bool CalculateLaneMarks(const std::vector<T>& _left_lane_ref_points, const std::vector<T>& _middle_lane_ref_points,
                        const std::vector<T>& _right_lane_ref_points, std::vector<std::vector<T>>& lines,
                        std::vector<std::pair<T, T>>& ids);

/**
 * @brief Given a reference line segment and a reference point on it, calculate target point on the (extension)
 * reference line with specific distance to reference point
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _start_point Left point of reference line segment
 * @param[in] _end_point Right point of reference line segment
 * @param[in] _given_point Given point on the reference line
 * @param[in] _distance Expected distance between target point and reference point
 * @param[in] _side Expected direction of target point w.r.t reference point, either DIR_PRECEDING or DIR_SUCCEEDING
 * @param[out] _result_point Resulted point
 * @return true If target point is calculated
 * @return false Otherwise
 */
template <typename T>
bool GetPointInLineWithDistance(const T& _start_point, const T& _end_point, const T& _given_point,
                                const Distance _distance, const Direction _side, T& _result_point);

/**
 * @brief Create a parallel line w.r.t a reference line in 2D
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _input Sample points of reference line
 * @param[in] _width Expected space between two (parallel) lines
 * @param[in] _on_which_side Expected direction of target line w.r.t reference line, either left or right.
 * @param[out] _output Target line parallel to reference line
 * @return true If target line can be derived
 * @return false Otherwise
 */
template <typename T>
bool CreateParallelLine(const std::vector<T>& _input, const Distance _width, const Direction _on_which_side,
                        std::vector<T>& _output);

/**
 * @brief Create target line according to a vector of width w.r.t a reference line. As a difference to @see
 * CreateParallelLine(), the resulted line is not parallel to reference line
 * @param[in] _input Sampling points of reference line
 * @param[in] _width_vec Vector of width
 * @param[in] _on_which_side Expected direction of target line w.r.t reference line, either left or right.
 * @param[out] _output Target line composed of a vector of reference points
 * @return true If target line can be derived
 * @return false Otherwise
 */
template <typename T>
bool CreateCorrelatedLine2D(const std::vector<T>& _input, const std::vector<Distance>& _width_vec,
                            const Direction _on_which_side, std::vector<T>& _output);

/**
 * @brief Create parallel lines to the left and right sides w.r.t a reference line in 2D
 * @param[in] _input Sample points of reference line
 * @param[in] _width Space between derived line w.r.t reference line
 * @param[out] _output_left Sampling points of parallel line to the left
 * @param[out] _output_left Sampling points of parallel line to the right
 * @return true If target line can be derived
 * @return false Otherwise
 */
bool CreateParallelLine(const std::vector<MapPoint>& _input, const Distance _width, std::vector<MapPoint>& _output_left,
                        std::vector<MapPoint>& _output_right);

/**
 * @brief Create target line w.r.t a reference line given space in-between at start and end, respectively.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _input Sampling points of reference line
 * @param[in] _start_width Width between both lines at start
 * @param[in] _end_width Width between both lines at end
 * @param[in] _on_which_side Direction of target line w.r.t reference line, either left or right
 * @param[out] _output Sampling points of resulted line
 * @return true Success
 * @return false Failure
 */
template <typename T>
bool CreateLineFromRefLineByDistance(const std::vector<T>& _input, const Distance _start_width,
                                     const Distance _end_width, const Direction _on_which_side,
                                     std::vector<T>& _output);

/**
 * @brief Get a sub-line with specific length from the beginning of a reference line
 * @param[in] _ref_points Reference line
 * @param[in] _expected_length Length of sub-line
 * @param[out] _sub_line Sub-line obtained
 */
template <typename T>
void GetSubPathAtHead2D(const std::vector<T>& _ref_points, const Distance _expected_length, std::vector<T>& _sub_line);

/**
 * @brief Get a sub-line with specific length from the end of a reference line
 * @param[in,out] _ref_points Reference line
 * @param[in] _expected_length Length of sub-line
 */
template <typename T>
void GetSubPathAtTail2D(std::vector<T>& _ref_points, const Distance _expected_length);

/**
 * @brief Converted a pose from given coordinate frame to map frame
 * @param[in] _coordinate Coordinate system
 * @param[in] _raw_pose Pose in the given coordinate frame
 * @return Converted pose in map coordinate frame
 */
holo::geometry::Pose3d GetExpectedPose(const ::holo::common::Coordinate& _coordinate,
                                       const holo::geometry::Pose3d& _raw_pose);

/**
 * @brief Up-sample a vector of points by adding same number of points in-between for specific times
 * @param[in,out] _points Reference points
 * @param[in] _n up sampling time, when n = 1, append vector one time
 * @return true Up-sampling successful
 * @return false Otherwise
 */
template <typename T>
void UpSampleRefPoints(std::vector<T>& _points, const int _n = 1);

/**
 * @brief Up-sample a vector of points by pos of percent length.
 * @param[in,out] _points Reference points
 * @param[in] _percent_poses A pos of percent length vector, used for insert point, range(0,100),
 *                           if one or more percent pos out range, we will also insert the pos,
 *                           but not use the percent pos which out range.
 * @param[out] _percent_pos_to_index Record relationship for percent pos(0,100) to point index[0-N]
 * @param[in] _tolerance A buffer length value,if insert point to front or back point length
 *                       less than the buffer length, will not insert the point.
 * @return true Up-sampling successful
 * @return false Otherwise
 */
template <typename T>
holo::bool_t UpSampleRefPointsByPercentPos(
    std::vector<T>&                                          _points,
    const std::vector<holo::float64_t>&                      _percent_poses,
    std::vector<std::pair<holo::float64_t, holo::uint32_t>>& _percent_pos_to_index,
    const Distance                                           _tolerance = 0.0);

/**
 * @brief Up-sample a vector of points by pos of interval length.
 * @param[in,out] points Reference points
 * @param[in] interval insert two point interval Unit: m.
 * @param[out] distances the distance between the current point and the first point.Unit: m.
 * @param[in] tolerance the insertion point is not inserted if the distance from the insertion point
 *               to the front or back point is less than the tolerance Unit: m.
 *
 * @return true Up-sampling successful
 * @return false Otherwise
 */
template <typename T>
holo::bool_t UpSampleRefPointsByInterval(
    std::vector<T>&                 points,
    Distance const                  interval,
    std::vector<Distance>&          distances,
    Distance const                  tolerance = 0.0);

/**
 * @brief Cut off a part from the beginning of a specific line
 * @param[in,out] _ref_points Line to be cut
 * @param[in] _cut_length Length to be cut
 */
template <typename T>
bool CutPathAtHead2D(std::vector<T>& _ref_points, const Distance _cut_length);

/**
 * @brief Cut a line at tail for a specific length
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in,out] _ref_points Line to be cut
 * @param[in] _cut_length Length to cut at tail of line
 */
template <typename T>
bool CutPathAtTail2D(std::vector<T>& _ref_points, const Distance _cut_length);

/**
 * @brief Cut a line at head to a specific position. The position is the projection of a target point on that line.
 * @tparam T GeoPoint, MapPoint, MapPoint3.
 * @param[in,out] _points Line to be cut.
 * @param[in] _target Target point on or not on the line
 * @param[in] _append_project_point If we append the projection of target point to the line after cutting, even if the
 * projection is outside the line.
 * @return true Success;
 *         false Failure.
 */
template <typename T>
bool CutPathAtHead2D(std::vector<T>& _points, const T& _target, const bool _append_project_point = false);

/**
 * @brief Cut a line at tail to a specific position. The position is the projection of a target point on that line.
 * @tparam T GeoPoint, MapPoint, MapPoint3.
 * @param[in,out] _ref_points Line to be cut
 * @param[in]  _target A point on or not on the line
 * @param[in] _append_project_point If we append the projection of target point to the line after cutting, even if the
 * projection is outside the line.
 * @return true Success;
 *         false Failure.
 */
template <typename T>
bool CutPathAtTail2D(std::vector<T>& _points, const T& _target, const bool _append_project_point = false);

/**
 * @brief Cut a line by two points. The resulted line will start and end with the projection of both points. The other
 * points of the resulted line come from the original line.
 * @tparam MapPoint3
 * @param[in] _line Original line
 * @param[in] _p1 Point indicating the left border
 * @param[in] _p2 Point indicating the right border
 * @param[out] _resulted_line Resulted line after cutting
 */
template <typename T>
void CutLineByPoints(const std::vector<T>& _line, const T& _p1, const T& _p2, std::vector<T>& _resulted_line);

/**
 * @brief Cut a long line into a series of sub-lines as to the specified length. Note the first or last sub-line may not
 * be of that length.
 * @param[in] _ori_line Original line
 * @param[out] _lines resulted vector of sub-lines
 * @param[in] _dist expected length of sub-line
 * @return true If operation succeeded
 * @return true Otherwise
 */
template <typename T>
bool CutIntoSubLines(const std::vector<T>& _ori_line, std::vector<std::vector<T>>& _lines, const map::Distance _dist);

/**
 * @brief Clip the subpath in the original path.
 *
 * @param[in, out] path Original path as input paramter, subpath as output paramter,
 *                 original path should not be empty and the internal points should
 *                 at least two.
 * @param[in, out] length Original path length as input paramter, subpath path length
 *                 as output paramter, we can calculate the length by geometry::GetVecLenght()
 *                 for original path. Note: tt should be larger than 0.0 as input paramter.
 * @param[in] offset The offset of the starting position of the subpath in the original path,
 *                   it should be equal or larger than 0.0. If it larger than the length of the
 *                   origianl path, the original path will clipped at all, and the subpath will
 *                   be empty. Note: it should be > 0.0.
 * @param[in] reservation Sub path length, the final subpath length may less than the reservation
 *            value, note: it should be > 0.0.
 * @param[in] tolerance Tolerance, if the cutting position is less than the tolerance distance
 *            from the head, the cutting will not be performed at the beginning, and if the cutting
 *            position is less than the tolerance distance from the tail, the cutting will not be
 *            performed at the tail. Note: tolerance should be >= 0.0.
 * @return true: No error.
 *         false: An error occurs in this funciton, please refer to log for more details.
 */
template <typename T>
holo::bool_t CutSubPath2D(std::vector<T>& path, Distance& length, const Distance offset,
    const Distance reservation, const Distance tolerance = 0.0);

/**
 * @brief Connect a (target) line to the tail of the reference line.
 * @tparam T GeoPoint, MapPoint3, MapPoint.
 * @param[in] _target Target line.
 * @param[in,out] _ref_line Reference line to be extended.
 * @return true Success
 * @return false Failure.
 */
template <typename T>
bool JoinPathAtTail2D(const std::vector<T>& _target, std::vector<T>& _ref_line);

/**
 * @brief Transform a pose to local frame centered at reference point
 * @param[in] _ref_pose Reference pose served as the center of transformation
 * @param[in] _pos Original pose
 * @return Transformed position
 */
MapPoint3 TransformToLocal(const MapPose3& _ref_pose, const MapPoint3& _pos);

/**
 * @brief Transform a pose to local frame centered at reference point
 * @param[in] _ref_pose Reference pose served as the center of transformation
 * @param[in] _pos Original pose
 * @return Transformed position
 */
MapPoint TransformToLocal(const MapPose3& _ref_pose, const MapPoint& _pos);

/**
 * @brief Transform a vector of pose to local frame centered at reference point
 * @param[in] _ref_pose Reference pose served as the center of transformation
 * @param[in] _vec_pos Vector of pose to be transformed
 * @return Transformed position
 */
std::vector<MapPoint3> TransformToLocal(const MapPose3& _ref_pose, const std::vector<MapPoint3>& _vec_pos);

/**
 * @brief Transform a vector of pose to local frame centered at reference point
 * @param[in] _ref_pose Reference pose served as the center of transformation
 * @param[in] _vec_pos Vector of pose to be transformed
 * @return Transformed position
 */
std::vector<MapPoint> TransformToLocal(const MapPose3& _ref_pose, const std::vector<MapPoint>& _vec_pos);

/**
 * @brief Given a target point and a reference line, calculate the distance of target point' projection to the end of
 * reference line
 * @param[in] _ref_points Reference line
 * @param[in] _position Target position
 * @param[out] _distance Distance calculated
 * @return If operation succeeded
 * @return Otherwise
 */
bool CalcDistanceToEndNode2D(const std::vector<format::GeoPoint>& _ref_points, const format::GeoPoint& _position,
                             Distance& _distance);

/**
 * @brief Calculate a point on the reference line given a specific distance from the line beginning.
 * @param[in] _ref_points Reference line
 * @param[in] _cut_length Distance from the beginning of reference line
 * @param[out] _pos_head Point calculated
 * @param[out] _cut_index index of the calculated position in the reference line. Assume the calculated position is P
 * falling into the line section p1 to p2, p1......P.....p2, then this index indicates the index of p2, i.e. the one
 * after P.
 * @return true If we can find out this position
 * @return false Otherwise
 */
template <typename T>
bool GetSpecificPointAtHead2D(const std::vector<T>& _ref_points, const Distance _cut_length, T& _pos_head,
                              Size& _cut_index);

/**
 * @brief Calculate a point on the reference line given a specific distance to the line end.
 * @param[in] _ref_points line represented by a vector of points
 * @param[in] _cut_length distance to the end of line
 * @param[out] _pos Point calculated
 * @param[out] _cut_index index of t he calculated position in the reference line. Assume the calculated position is P
 * falling into the line section p1 to p2,   p1......P.....p2, then this index indicates the index of p2, i.e. the one
 * after P.
 * @return true If we can find out this position
 * @return false Otherwise
 */
template <typename T>
bool GetSpecificPointAtTail(const std::vector<T>& _ref_points, const Distance _cut_length, T& _pos, Size& _cut_index);

/**
 * @brief Get sub-line from a reference line given the distance to line beginning and expected length
 * @param[in] _cut_at_head Distance to the beginning of reference line
 * @param[in] _ref_points Reference line
 * @param[in] _distance Expected length of sub-line
 * @param[out] _remaining_distance Remaining distance to the sub-line if the sub-line cannot be totally fetched from
 * reference line
 * @param[out] _sub_line Sub-line obtained
 * @return true If this sub-line can be totally obtained
 * @return false Otherwise, including the case that only part of line can be obtained
 */
template <typename T>
bool GetSubPath2D(const Distance _cut_at_head_dis, const std::vector<T>& _ref_points, const Distance _distance,
                  Distance& _remaining_distance, std::vector<T>& _sub_line);

/**
 * @brief Calculate distance from the projection of a given position to the end of line
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _pos Target position. We will calculate its projection on this line first.
 * @param[in] _points Reference line
 * @param[out] _distance Calculated distance from projected position to line end
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool CalculateDistanceToLineEnd2D(const T& _pos, const std::vector<T>& _points, Distance& _distance);

/**
 * @brief Calculate the distance from a line head to the projection of a given position on this line
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _pos Target position. We will calculate its projection on this line first.
 * @param[in] _points Reference line
 * @param[out] _distance Calculated distance from line head to projected position
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool CalculateDistanceFromLineHead2D(const T& _pos, const std::vector<T>& _points, Distance& _distance);

/**
 * @brief Calculate the distance from target point to reference line segment
 * @details We create this function in order to prevent the line segment from being created from two identical points
 * (head = tail). In this case, a line segment can be taken as a point, so the distance is simplified to the distance
 * between two points
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _pos Target point
 * @param[in] _head_line_segment Head of reference line segment
 * @param[in] _end_line_segment End of reference line segment
 * @param[out] _project_point Projected point
 * @param[out] _is_outside If projected point is outside the line segment
 * @return Distance from target point to reference line segment
 */
template <typename T>
Distance CalculateDistanceFromPointToLineSegment2D(const T& _pos, const T& _head_line_segment,
                                                   const T& _end_line_segment, T& _project_point, bool& _is_outside);

/**
 * @brief Calculate the distance from target point to reference line segment
 * @details We create this function in order to prevent the line segment from being created from two identical points
 * (head = tail). In this case, a line segment can be taken as a point, so the distance is simplified to the distance
 * between two points
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _pos Target point
 * @param[in] _head_line_segment Head of reference line segment
 * @param[in] _end_line_segment End of reference line segment
 * @return Distance from target point to reference line segment
 */
template <typename T>
Distance CalculateDistanceFromPointToLineSegment2D(const T& _pos, const T& _head_line_segment,
                                                   const T& _end_line_segment);

/**
 * @brief Interpolate or extrapolate a line segment (2D or 3D)
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _start_point Start point of line segment
 * @param[in] _end_point End point of line segment
 * @param[in] _polate_ratio Ratio for interpolation (absolute value < 1) or extrapolation (absolute value >= 1). A
 * positive value indicates the direction is from the beginning to the end.
 * @return Calculated point after interpolation or extrapolation
 */
template <typename T>
const T Polate(const T& _start_point, const T& _end_point, const FloatChar13 _polate_ratio);

/**
 * @brief Check if a line is covered by or intersects with a polygon
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _ls Line segment composed of reference points
 * @param[in] _pg Polygon
 * @param[in] rough_search True if rough (fast) search needed
 * @return true If this line is covered by or intersects with the polygon
 * @return false Otherwise
 */
template <typename T>
bool IsLineAssociatedToPolygon(const std::vector<T>& _ls, const holo::geometry::ConvexPolygon2d& _pg,
                               const bool rough_search = true);

/**
 * @brief Get closest terminals of two line segments
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _line1 Line segment 1
 * @param[in] _line2 Line segment 2
 * @param[out] _get_line1_head True if closest point is at line1 head; false at tail
 * @param[out] _get_line2_head True if closest point is at line2 head; false at tail
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool GetClosestTerminalsOfTwoLines(const std::vector<T>& _line1, const std::vector<T>& _line2, bool& _get_line1_head,
                                   bool& _get_line2_head);

/**
 * @brief Check the connection of two lines. If gaps exist, calculate the line segment that can connect both lines.
 * @details The calculated line segment is composed of three points. The first and last element shall be the terminals
 * of reference lines, the middle element shall be the center point of line segment
 * @param T GeoPoint, MapPoint, MapPoint3
 * @param[in] _line1 Line 1 composed of sampling points
 * @param[in] _line2 Line 2 composed of sampling points
 * @param[out] _new_lines Connecting lines created(terminals and center points)
 * @return True if operation succeeded
 * @return False Otherwise
 */
template <typename T>
bool AddLinesByFilling(const std::vector<T>& _line1, const std::vector<T>& _line2, std::vector<T>& _new_lines);

/**
 * @brief Check if there are duplicates in a series of points
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] _ori Points to check duplicates
 * @return True  Duplicates exist
 * @return False No duplicates
 */
template <typename T>
bool HasDuplicates2D(const ::std::vector<T>& _ori);

/**
 * @brief Given two points as terminals, insert a series of points along a straight line formed by both terminals and
 * ensure that the distance between points is not greater than the given distance.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _p1 Terminal 1
 * @param[in] _p2 Terminal 2
 * @param[in] _step Maximal distance between points, in units of [m]
 * @param[out] _points Created points
 * @param[in] _include_terminals True if both terminals will also appear in the resulted vector of points
 */
template <typename T>
void InsertRefPoints(const T& _p1, const T& _p2, const double _step, std::vector<T>& _points,
                     const bool _include_terminals);

/**
 * @brief Up-sample a line by ensuring the span between adjacent points is limited to a specific distance
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _ori_points Reference line
 * @param[in] _step Maximal length between re-sampled points in units of meters
 * @param[out] _created_points New line after up-sampling
 */
template <typename T>
void UpSampleByStepLength2D(const std::vector<T>& _ori_points, const double _step, std::vector<T>& _created_points);

/**
 * @brief Up-sample a line by ensuring the span between adjacent points is limited to a specific distance
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in,out] _ori_points Reference line
 * @param[in] _step Maximal length between re-sampled points in units of meters
 */
template <typename T>
void UpSampleByStepLength2D(std::vector<T>& _points, const double _step);

/**
 * @brief Down-sample a line by ensuring the span between adjacent points is greater than a threshold
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in,out] _points Reference line which
 * @param[in] _step Minimal length between re-sampled points in units of [m]
 */
template <typename T>
void DownSampleRefPoints2D(std::vector<T>& _points, const double _step);

/**
 * @brief Clean very close (almost overlapped) sampling points.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in,out] _ori_points Original line composed of sampling points
 * @param[in] _only_sequential_check True if we only sequentially check a point with its previous one; false if we check
 * each point with respect to the others, and this would be VERY TIME-CONSUMING !!!!!!
 * @param[in] _tolerance maximal allowed span between points
 */
template <typename T>
void ClearDuplicates2D(std::vector<T>& _ori_points, const bool _only_sequential_check, const double _tolerance = 0.05);

/**
 * @brief Push a point to the end of line
 * @details The operation of "push" is made as along as the new point is not overlapped with the last point of the
 * line.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in, out] _ori_points Reference line composed of sampling points
 * @param[in] _p Point to be pushed to back of reference line
 */
template <typename T>
void PushPoint2D(std::vector<T>& _ori_points, const T& _p);

/**
 * @brief Project a short line onto a longer line.
 * @note Both lines are thought as roughly parallel.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _long_line Longer line taken as reference
 * @param[in] _short_line Short line to be projected on the longer line
 * @param[in] _left_border_short_line Left index of the shorter line. This allows you to pick a segment of this line
 * @param[in] _right_border_short_line Right index of the shorter line. This allows you to pick a segment of this line
 * @param[out] _resulted_line Projected line of shorter line on the longer line
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool CalculateProjectedLineSegment(const std::vector<T>& _long_line, const std::vector<T>& _short_line,
                                   const Size _left_border_short_line, const Size _right_border_short_line,
                                   std::vector<T>& _resulted_line);

/**
 * @brief Replace part of line1 with its projection onto line2
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in,out] _line1 Line 1
 * @param[in] _line2 Line 2
 * @param[in] _left_border_line1 Left border(index starting from 0) of line 1
 * @param[in] _right_border_line2 Right border(index) of line 1
 * @return True If operation succeeded
 * @return False Otherwise
 */
template <typename T>
bool ReplaceWithOtherLine(std::vector<T>& _line1, const std::vector<T>& _line2, const Size _left_border_line1,
                          const Size _right_border_line1);

/**
 * @brief Calculate the minimal rectangular convex hull
 * @tparam T GeoPoint
 * @param[in] _points Original points
 * @return Vertices by clockwise
 */
template <typename T>
::std::vector<T> MinAreaRect(const ::std::vector<T>& _points);

/**
 * @brief Calculate the minimal box covering all sampling points
 * @tparam T GeoPoint
 * @param[in] _points Sampling points in 3D
 * @return Vertices by clockwise
 */
::std::vector<::holo::geometry::Point3d> MinAreaRectInPlane3D(::std::vector<::holo::geometry::Point3d> _points);

/**
 * @brief Append a point to the end of a line with duplication checks
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in,out] _line Line to be appended
 * @param[in] _point Point to be appended to the line
 */
template <typename T>
void AppendPoint2D(std::vector<T>& _line, const T& _point);

/**
 * @brief Get pose (mainly heading) from a vector composed of two points p1 and p2
 * @details  Vehicle coordinate system as to rotation from p1 to p2 is defined as follows:
 * X is the vehicle's forward direction,Y is on the left of forward direction of X
 *  *
 *
 *                                   *X
 *                Y                 *
 *                *                *
 *                   *            *
 *                      *        *
 *                         *    *
 *                           *p2
 *
 *         Y*
 *
 *
 *             *                 *X
 *       Y*               *
 *        *       *p1
 *        *
 *        *
 *  *******v***********X
 *        *
 * @param[in] _start_point Starting point (P1)
 * @param[in] _end_point End point (P2)
 * @param[out] _pose Pose to be calculated
 * @param[in] _is_pose_at_start_point True if the pose to be calculated is at starting point; false if the pose is at
 end point.
 * @return true If operation succeeded.
 */
template <typename TIN>
bool GetPoseFromTwoPoints(const TIN& _start_point, const TIN& _end_point, MapPose3& _pose,
                          const bool _is_pose_at_start_point);

/**
 * @brief Get pose formed by line terminals (first and last element)
 * @param[in] _vec Line composed of a vector of points
 * @param[out] _pose Pose to be calculated
 * @param[in] _is_pose_front true if the pose to be calculated is at the beginning of line; false it the pose is at the
 * line end
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename TIN>
bool GetPoseOfLineSegmentTerminal(const std::vector<TIN>& _vec, MapPose3& _pose, const bool _is_pose_front);

/**
 * @brief Check if both lines almost overlap, i.e. the distance of each point of line 1 to the projected point on line 2
 * is small enough. Note
 * @note  Make sure that each point of line 1 can be projected onto line2. This function will not check it for the sake
 * of performance
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line1 (Shorter) line
 * @param[in] _line2 (Longer) line
 * @param[in] _max_span Maximal allowed span between each point of line 1 and its projection on line 2
 * @return true If both lines can be judged as overlapped
 * @return false Otherwise
 */
template <typename T>
bool AreLinesOverlapped(const std::vector<T>& _line1, const std::vector<T>& _line2, const double _max_span);

/**
 * @brief Check if line1 and line2 show significant deviation in-between
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line1 (Shorter) line
 * @param[in] _line2 (Longer) line
 * @param[in] _max_span Maximal allowed span between each point of line 1 and its projection on line 2
 * @param[in] _count Number of consecutive points that override the maximal span. Reaching this count means that both
 * lines are deviating
 * @return True If both lines can be judged as deviating
 * @return False Otherwise
 */
template <typename T>
bool AreLinesDeviating(const std::vector<T>& _line1, const std::vector<T>& _line2, const Distance _max_span,
                       const Size _count = 5);

/**
 * @brief Check if a line is getting closer to the other line.
 * @details "Getting closer" means the distance between both lines are decresing until overlapped.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line_short (Shorter) line
 * @param[in] _line_long (Longer) line
 * @param[in] _tolerance Threshold to check "getting closer". Note it is sometimes difficult to strictly check the
 * decresing trend of distance between points. If the distance of current point and its counterpart of last point only
 * represent a minor difference, we believe they are "not getting closer".
 * @return true if both lines are getting closer
 */
template <typename T>
bool AreLinesGettingCloser(const std::vector<T>& _line_short, const std::vector<T>& _line_long,
                           const double _tolerance);

/**
 * @brief Get pose of a specific position on a line given a specific distance of this position to line head
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _points Original line
 * @param[in] _dist Distance of the target point from the line head
 * @param[out] _pose Pose to be calculated
 * @return true if Pose has been calculated
 * @return false Otherwise
 */
template <typename T>
bool GetPoseAtLine(const std::vector<T>& _points, const Distance _dist, MapPose3& _pose);

/**
 * @brief Sort verticies of polygon by included angles with centroid
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _ori_points Original verticies
 * @param[out] _sorted_points Sorted verties
 * @attention right hand coordinate: _sorted_points is anticlockwise
 *            left hand coordinate: _sorted_points is clockwise
 * @return True If we successfully obtained the sorted verticies
 * @return False Otherwise
 */
template <typename T>
bool SortVerticies(const std::vector<T>& _ori_points, std::vector<T>& _sorted_points);

/**
 * @brief Calculate intersections of two lines
 * @note There might be multiple intersections
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line1 Line 1
 * @param[in] _line2 Line 2
 * @param[out] _intersections Vector of intersections
 * @return True If operation succeeded
 * @return False Otherwise
 */
template <typename T>
bool CalculateIntersections(const std::vector<T>& _line1, const std::vector<T>& _line2, std::vector<T>& _intersections);

/**
 * @brief Extend a (target) line to intersect with a (reference) line
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line_extend Target line to be extended
 * @param[in] _lineref Reference line that target line to be intersected with
 * @param[out] _resulted_line Resulted line (extended)
 * @param[in] true If we need to check intersections first; False if you can assure that both lines are not intersected
 * at all in order to save time.
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool ExtendLineToIntersect(const std::vector<T>& _line_extend, const std::vector<T>& _line_ref,
                           std::vector<T>& _resulted_line, const bool _calculate_intersection_first = true);

/**
 * @brief Calculate the shortest distance between two lines
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] _line1 Line 1
 * @param[in] _line2 Line 2
 * @param[out] _min_distance Shortest distance between line 1 and line 2
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool CalculateShortestDistanceOfTwoLines2D(const std::vector<T>& _line1, const std::vector<T>& _line2,
                                           map::Distance& _min_distance);

/**
 * @brief Re-Sampling points by adding points. Newly added points shall obey a pre-defined distance between points
 * @param[in] _ori_line Original line composed of multiple points
 * @param[in] _step Pre-defined distance between points
 * @param[out] _new_line Re-sampled line points
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool EqualResamplePoints(const std::vector<T>& _ori_line, const map::Distance _step, std::vector<T>& _new_line);

/**
 * @brief Convert NDS tile to NavInfo tile
 * @param[in] _nds_tile_id Nds tile id
 * @param[in] _navinfo_tile_id Navinfo tile id
 * @return true If operation succeeded
 * @return false Otherwise
 */
MapFeatureIdType Nds2NavinfoTile(const MapFeatureIdType _nds_tile_id, const int8_t _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Convert NavInfo tile to NDS tile
 * @param[in] _navinfo_tile_id Navinfo tile id
 * @param[in] _nds_tile_id Nds tile id
 * @return true If operation succeeded
 * @return false Otherwise
 */
MapFeatureIdType Navinfo2NdsTile(const MapFeatureIdType _navinfo_tile_id, const int8_t _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile id by a box given by xy
 * @param[in] _geo_box GeoBox in UTM 50N coordinate system.
 * @param[out] _tile_ids Tile id to be calculated
 * @param[in] _id_flag Indicats NavInfo tile for 1, NavInfo tile and NDS tile for 2
 * @param[in] _tile_level NDS level default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateTileByLatLon(format::GeoBox const& _geo_box, MapFeatureIdVectorType& _tile_ids,
                           holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate covered tile ids by a box given in coordinate of WGS84.
 * @param[in] _geo_box GeoBox in coordinate reference system of WGS84.
 * @param[out] _tile_ids Tile id to be calculated
 * @param[in] _id_flag Indicats NavInfo tile for 1, NavInfo tile and NDS tile for 2
 * @param[in] _tile_level NDS level default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateTileByLatLonV2(format::GeoBox const& _geo_box, MapFeatureIdVectorType& _tile_ids,
                             holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate covered tile id by a box given by UTM;
 * @param[in] _geo_box GeoBox in coordinate reference system of UTM.
 * @param[out] _tile_ids Tile id to be calculated
 * @param[in] _zone UTM zone id.
 * @param[in] _south True: in the southern hemispherr, False: in the northern hemispherr.
 * @param[in] _id_flag Indicats NavInfo tile for 1, NavInfo tile and NDS tile for 2
 * @param[in] _tile_level NDS level default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateTileByUTM(format::GeoBox const& _geo_box, MapFeatureIdVectorType& _tile_ids,
                        holo::uint8_t const _zone, holo::bool_t const _south  = false,
                        holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile id where a point falls in xy.
 * @param[in] _geo_point Point with UTM zone 50.
 * @param[out] _tile_ids Tile id to be calculated
 * @param[in] _id_flag Indicates NavInfo tile for 1 and NDS tile for 2
 * @param[in] _tile_level NDS level default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateTileByLatLon(format::GeoPoint const& _geo_point, MapFeatureIdVectorType& _tile_ids,
                           holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile ids where the target point fall in.
 *
 * @param[in] _geo_point A point with coordinate reference systtem of WGS84.
 * @param[out] _tile_ids Tile ids.
 * @param[in] _id_flag 1: the results are Navinfo tile ids, otherwise the results are NDS tile ids.
 * @param[in]  _tile_level NDS level default 13.
 *
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool CalculateTileByLatLonV2(format::GeoPoint const& _geo_point, MapFeatureIdVectorType& _tile_ids,
                             holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile ids where the target point fall in.
 *
 * @param[in] _geo_point A point with coordinate reference systtem of WGS84.
 * @param[out] _tile_ids Tile ids.
 * @param[in] _zone UTM zone id.
 * @param[in] _south true: in the southern hemispherr, false: in the northern hemispherr.
 * @param[in] _id_flag 1: the results are Navinfo tile ids, otherwise the results are NDS tile ids.
 * @param[in]  _tile_level NDS level default 13.
 *
 * @return true: No error.
 *         false: An error occurs in this function.
 */
bool CalculateTileByUTM(format::GeoPoint const& _geo_point, MapFeatureIdVectorType& _tile_ids,
                        holo::uint8_t const _zone, holo::bool_t const _south  = false,
                        holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile id by given a circle.
 * @param[in] _geo_circle A circle with coordinate reference system of WGS84-UTM Zone 50N.
 * @param[out] _tile_ids Tiles covered by the circle.
 * @param[in] _id_flag NavInfo tile for 1 and NDS tile for 2
 * @param[in] _tile_level NDS level, default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateTileByLatLon(format::GeoCircle const& _geo_circle, MapFeatureIdVectorType& _tile_ids,
                           holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile ids by a circle.
 * @param[in] _geo_circle A circle with coordinate reference system of WGS84.
 * @param[out] _tile_ids Tiles covered by the circle.
 * @param[in] _id_flag NavInfo tile for 1 and NDS tile for 2.
 * @param[in] _tile_level NDS level, default 13.
 * @return true No error.
 *         false An error occurs in this function.
 */
bool CalculateTileByLatLonV2(format::GeoCircle const& _geo_circle, MapFeatureIdVectorType& _tile_ids,
                             holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile ids by a circle.
 * @param[in] _geo_circle A circle with coordinate reference system of UTM.
 * @param[out] _tile_ids Tiles covered by the circle.
 * @param[in] _zone_id UTM zone id.
 * @param[in] _south_flag true: in the southern hemispherr, false: in the northern hemispherr.
 * @param[in] _id_flag NavInfo tile for 1 and NDS tile for 2.
 * @param[in] _tile_level NDS level, default 13.
 * @return true No error.
 *         false An error occurs in this function.
 */
bool CalculateTileByUTM(format::GeoCircle const& _geo_circle, MapFeatureIdVectorType& _tile_ids,
                        CoordinateUtmZoneType const _zone_id, holo::bool_t const _south_flag,
                        holo::int8_t const _id_flag = 1, holo::int8_t const _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate distance between point and tile id center in WGS84.
 * @param[in] point The point to be calculated.
 * @param[in] tile_id Tile to be calculated.
 * @param[out] distance Diatance between point and tile id center.
 * @param[in] id_flag NavInfo tile for 1 and NDS tile for 2.
 * @param[in] tile_level Default tilt level, 15.
 * @return true No error.
 *         false An error occurs in this function.
 */
holo::bool_t CalculateTileCenterDistanceByLatLonV2(format::GeoPoint const& point, MapFeatureIdType const tile_id,
    Distance& distance, holo::int8_t const id_flag = 1, holo::int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate distance between point and tile id center in UTM6.
 * @param[in] point The point to be calculated.
 * @param[in] tile_id Tile to be calculated.
 * @param[out] distance Diatance between point and tile id center.
 * @param[in] zone UTM zone id.
 * @param[in] south true: in the southern hemispherr, false: in the northern hemispherr.
 * @param[in] id_flag NavInfo tile for 1 and NDS tile for 2.
 * @param[in] tile_level Default tilt level, 15.
 * @return true No error.
 *         false An error occurs in this function.
 */
holo::bool_t CalculateTileCenterDistanceByUTM6(format::GeoPoint const& point, MapFeatureIdType const tile_id,
    Distance& distance, holo::uint8_t const zone, holo::bool_t const south  = false,
    holo::int8_t const id_flag = 1, holo::int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate distance between point and tile id border in WGS84.
 * @param[in] point The point to be calculated.
 * @param[in] tile_id The tile to be calculated.
 * @param[out] distance Diatance between point and tile id border.
 * @param[in] id_flag NavInfo tile for 1 and NDS tile for 2.
 * @param[in] tile_level Default tilt level, 15.
 * @return true No error.
 *         false An error occurs in this function.
 */
holo::bool_t CalculateTileBorderDistanceByLatLonV2(format::GeoPoint const& point, MapFeatureIdType const tile_id,
    Distance& distance, holo::int8_t const id_flag = 1, holo::int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate distance between point and tile id border in UTM6.
 * @param[in] point The point to be calculated.
 * @param[in] tile_id Tile to be calculated.
 * @param[out] distance Diatance between point and tile id border.
 * @param[in] zone UTM zone id.
 * @param[in] south true: in the southern hemispherr, false: in the northern hemispherr.
 * @param[in] id_flag NavInfo tile for 1 and NDS tile for 2.
 * @param[in] tile_level Default tilt level, 15.
 * @return true No error.
 *         false An error occurs in this function.
 */
holo::bool_t CalculateTileBorderDistanceByUTM6(format::GeoPoint const& point, MapFeatureIdType const tile_id,
    Distance& distance, holo::uint8_t const zone, holo::bool_t const south  = false,
    holo::int8_t const id_flag = 1, holo::int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate 8 surrounding tiles by a point given in lat/lon
 * @param[in] _geo_point Point
 * @param[out] _tile_id Center tile id
 * @param[out] _surrounding_ids Ids of 8 surrounding tiles
 * @param[in] _id_flag Indicates NavInfo tile for 1 and NDS tile for 2
 * @param[in] _tile_level NDS level, default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateSurroundingTileByLatLon(format::GeoPoint const& geo_point,
    MapFeatureIdType& _center_tile_id, std::vector<MapFeatureIdType>& surrounding_ids,
    int8_t const id_flag = 1, int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate 8 surrounding tiles by a point given in lat/lon
 * @param[in] _geo_point Point
 * @param[out] _tile_id Center tile id
 * @param[out] _surrounding_ids Ids of 8 surrounding tiles
 * @param[in] _id_flag Indicates NavInfo tile for 1 and NDS tile for 2
 * @param[in] _tile_level NDS level, default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateSurroundingTileByLatLonV2(format::GeoPoint const& geo_point,
    MapFeatureIdType& _center_tile_id, std::vector<MapFeatureIdType>& surrounding_ids,
    int8_t const id_flag = 1, int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate current and surrounding tiles around target point.
 *
 * @param[in] geo_point Target point with longitude and latitude.
 * @param[in] ratio If 0, only calculate current tile;
 *                  If 1, calculate 3X3 tiles, contains current(1) and surrounding(8) tiles.
 *                  If 2, calculate 5X5 tiles, contains current(1) and surrounding(24) tiles.
 *                  etc...
 * @param[out] center_tile_id Tile id where target point located.
 * @param[out] surrounding_ids Surronding tiles of current tile, depend on ratio.
 * @param[in] id_flag 1: Output Navinfo tile ids;
 *                    0: Output NDS tile ids.
 * @param[in] tile_level Tile level, default 13.
 * @return true  No error.
 *         false An error occurs in this function, please refer to error logs for details.
 */
holo::bool_t CalculateSurroundingTileByLatLonV2(format::GeoPoint const& geo_point, holo::uint8_t const ratio,
    MapFeatureIdType& center_tile_id, std::vector<MapFeatureIdType>& surrounding_ids,
    int8_t const id_flag = 1, int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate current and surrounding tiles around target point.
 *
 * @param[in] geo_point Target point with longitude and latitude.
 * @param[in] directions If empty, only calculate current tile;
 *                       If not empty, calculate current tile and surronding tiles of special directions.
 * @param[out] center_tile_id Tile id where target point located.
 * @param[out] surrounding_ids Surronding tiles of current tile, depend on 'directions'.
 * @param[in] id_flag 1: Output Navinfo tile ids;
 *                    0: Output NDS tile ids.
 * @param[in] tile_level Tile level, default 13.
 * @return true  No error.
 *         false An error occurs in this function, please refer to error logs for details.
 */
holo::bool_t CalculateSurroundingTileByLatLonV2(format::GeoPoint const& geo_point,
    std::vector<MapDirection> const& directions,
    MapFeatureIdType& _center_tile_id, std::vector<MapFeatureIdType>& surrounding_ids,
    int8_t const id_flag = 1, int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate 8 surrounding tiles by a point given in lat/lon
 * @param[in] _geo_point Point
 * @param[out] _tile_id Center tile id
 * @param[out] _surrounding_ids Ids of 8 surrounding tiles
 * @param[in] _id_flag Indicates NavInfo tile for 1 and NDS tile for 2
 * @param[in] _tile_level NDS level, default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateSurroundingTileByUTM(format::GeoPoint const& _geo_point,
    holo::uint8_t const zone_id, holo::bool_t const south_flag,
    MapFeatureIdType& _center_tile_id, std::vector<MapFeatureIdType>& _surrounding_ids,
    int8_t const id_flag = 1, int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate current and surrounding tiles around target point.
 *
 * @param[in] geo_point Target point with UTM Coordinate Reference System.
 * @param[in] zone_id Zone id, range: [1, 60]
 * @param[in] south_flag If true, target point on the Southern Hemisphere.
 * @param[in] ratio If 0, only calculate current tile;
 *                  If 1, calculate 3X3 tiles, contains current(1) and surrounding(8) tiles.
 *                  If 2, calculate 5X5 tiles, contains current(1) and surrounding(24) tiles.
 *                  etc...
 * @param[out] center_tile_id Tile id where target point located.
 * @param[out] surrounding_ids Surronding tiles of current tile, depend on ratio.
 * @param[in] id_flag 1: Output Navinfo tile ids;
 *                    0: Output NDS tile ids.
 * @param[in] tile_level Tile level, default 13.
 * @return true  No error.
 *         false An error occurs in this function, please refer to error logs for details.
 */
holo::bool_t CalculateSurroundingTileByUTM(format::GeoPoint const& _geo_point,
    holo::uint8_t const zone_id, holo::bool_t const south_flag, holo::uint8_t const ratio,
    MapFeatureIdType& _center_tile_id, std::vector<MapFeatureIdType>& _surrounding_ids,
    int8_t const id_flag = 1, int8_t const tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate tile id by a circle given in meters
 * @param[in] _geo_circle Circle given in meters
 * @param[out] _tile_ids Tile ids to be calculated
 * @param[in] _id_flag Indicates NavInfo tile for 1 and NDS tile for 2
 * @param[in] _tile_level NDS level, default 13
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateTileByMeters(const format::GeoCircle& _geo_circle, ::std::vector<MapFeatureIdType>& _tile_ids,
                           const int8_t _id_flag = 1, const int8_t _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate NDS-latitude(Y) by geographical latitude
 * @param[in] _latitue Latitude
 * @param[out] _y NDS latitude
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateNDSLat(const double _latitude, int32_t& _y);

/**
 * @brief calculate NDS_longitude(X) by geographical longitude *
 * @param[in] _longitude Longitude
 * @param[out] _x NDS longitude(X)
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateNDSLon(const double _longitude, int32_t& _x);

/**
 * @brief calculate geographical longitude by NDS-longitude(X)
 * @param[in] _x NDS longitude(X)
 * @param[out] _longitude geographical longitude
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateLongitude(const uint32_t _x, double& _longitude);

/**
 * @brief calculate geographical latitude by NDS-latitude(Y) *
 * @param[in] _y y NDS latitude(Y)
 * @param[out] _latitude geographical latitude
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateLatitude(const int32_t _y, double& _latitude);

/**
 * @brief Calculate morton code
 * @param[out] _morton_code Morton code
 * @param[in] _x NDS longitude(X)
 * @param[in] _y NDS latitude(Y)
 */
void CalculateMortonCode(int64_t& _morton_code, int32_t _x, int32_t _y);

/**
 * @brief Calculate NDS tile by morton code
 * @param[in] _morton_code Morton code
 * @param[in] _tile_level Level of tile, default is 13
 * @return NDS tile id
 */
MapFeatureIdType CalculateNDSTile(const int64_t _morton_code, const int8_t _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate NavInfo tile by morton code
 * @param[in] _morton_code morton
 * @param[in] _tile_level Level of tile, default is 13
 * @return Navinfo tile id
 */
MapFeatureIdType CalculateNavinfoTile(const int64_t _morton_code, const int8_t _tile_level = DEFAULT_TILE_LEVEL);

/**
 * @brief Calculate level by tile id
 * @param[in] _tile_id NDS tile id. Note the level cannot be calculated by NavInfo tile id
 * @param[out] _level Level of tile
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateLevel(MapFeatureIdType _tile_id, int8_t& _level);

/**
 * @brief Calculate south west position
 * @param[in] _tile_id NDS tile id. Note it will return false for NavInfo tiles
 * @param[out] _x NDS longitude
 * @param[out] _y NDS latitude
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateSWPosition(MapFeatureIdType _tile_id, uint32_t& _x, uint32_t& _y);

/**
 * @brief Calculate south west position
 * @param[in] _tile_id NDS tile id. Note it will return false for NavInfo tiles
 * @param[out] _longitude Longitude
 * @param[out] _latitude Latitude
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateSWPosition(MapFeatureIdType _tile_id, double& _longitude, double& _latitude);

/**
 * @brief Calculate the bounding box of specific tile
 * @param[in] _tile_id NDS tile id
 * @param[out] _longitude_min Minimal longitude
 * @param[out] _longitude_max Maximal longitude
 * @param[out] _latitude_min Minimal latitude
 * @param[out] _latitude_max Maximal latitude
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateSWExtend(MapFeatureIdType _tile_id, double& _longitude_min, double& _longitude_max, double& _latitude_min,
                       double& _latitude_max);

/**
 * @brief Get pose of a (target) point w.r.t to a (reference) point
 * @param[in] _start_point start point
 * @param[in] _end_point end point
 * @param[out] _pose pose calculated from both points
 * @param[in] _is_pose_at_start_point Indicates which point is target point. True for start point and false for end
 * point
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool GetPoseFromPosition(const MapPoint3& _start_point, const MapPoint3& _end_point, MapPose3& _pose,
                         const bool _is_pose_at_start_point);

/**
 * @brief Calculate the side of point P w.r.t line segment AB (direction is A to B!!!)
 * @param[in] _a point A
 * @param[in] _b point B
 * @param[in] _p point P
 * @return LEFT/RIGHT for valid direction; UNKNOWN = P is on AB or its extension
 */
template <typename T>
Direction CalculateDirectionOfPointToLineSegment(const T& _a, const T& _b, const T& _p);

/**
 * @brief Calculate the intersection point of two line segments
 * @param[in] _line1_a a terminal of line1
 * @param[in] _line1_b another terminal of line1
 * @param[in] _line2_a a terminal of line2
 * @param[in] _line2_b another terminal of line2
 * @param[out] _p intersection P if any
 * @return True If intersection point is calculated
 * @return False Otherwise
 */
template <typename T>
bool IntersectPointOfTwoLine(const T& _line1_a, const T& _line1_b, const T& _line2_a, const T& _line2_b, T& _p);

/**
 * @brief Get an enclosed polygon with vertices sorted in counter-clockwise.
 * @param[in] _polygon A given polygon
 * @return Expected polygon
 */
Polygon GetClosedAndCounterClockWisePolygon(const Polygon& _polygon);

/**
 * @brief Check if the target ring is same as a reference ring
 * @param[in] _ring_1 Target ring
 * @param[in] _ring_2 Reference ring
 * @return True If both ring are same
 * @return False Otherwise
 */
bool AreSameRingsIn2D(std::vector<format::GeoPoint> _ring_1, std::vector<format::GeoPoint> _ring_2);

/**
 * @brief Get a un-closed (opened) polygon
 * @param[in,out] _polygon A given polygon
 * @return True if we get a un-closed polygon
 * @return False Otherwise
 */
bool GetUnClosedPolygon(Polygon& _polygon);

/**
 * @brief Check if the target polygon inside a polyon vector
 * @param[in] _polygons Vector of polygons
 * @param[in] _polygon Target polygon
 * @return True If inside
 * @return False Otherwise
 */
bool IsPolygonVectorContained(std::vector<Polygon> _polygons, Polygon _polygon);

/**
 * @brief Calculate intersection points of two lines. If two line segments are of the same line, return the terminal
 * points.
 * @param[in] _line1 Line 1
 * @param[in] _line2 Line 2
 * @param[out] _intersections Intersection points
 * @param[out] _line1_intersections Line segment id and intersection points on line 1
 * @param[out] _line2_intersections Line segment id and intersection points on line 2
 * @return true If operation succeeded
 * @return false Otherwise
 */
bool CalculateIntersectionsWithTerminalPoints(
    const std::vector<format::GeoPoint>& _line1, const std::vector<format::GeoPoint>& _line2,
    std::vector<format::GeoPoint>&                        _intersections,
    std::map<std::size_t, std::vector<format::GeoPoint>>& _line1_intersections,
    std::map<std::size_t, std::vector<format::GeoPoint>>& _line2_intersections);

/**
 * @brief Check if a simple polygon is inside another simple polygon.
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon1 Simple polygon 1
 * @param[in] _simple_polygon2 Simple polygon 2
 * @return True If polygon 1 is inside polygon 2
 * @return False Otherwise
 */
bool IsRingInAnotherRing(const std::vector<format::GeoPoint>& _simple_polygon1,
                         const std::vector<format::GeoPoint>& _simple_polygon2);

/**
 * @brief Check if Point P falls into the line segment formed by AB
 * @param[in] _a Point A
 * @param[in] _b Point B
 * @param[in] _p Point P
 * @return A struct indicating whether P is inside/outside the line segment or overlapped with any terminal
 */
InOrOutEntity AreThreePointInLine(const format::GeoPoint& _a, const format::GeoPoint& _b, const format::GeoPoint& _p);

/**
 * @brief Check if two simple polygons are NOT intersected
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon1 Polygon 1
 * @param[in] _simple_polygon2 Polygon 2
 * @return True If both polygons are NOT intersected
 * @return False Otherwise
 */
bool TwoPolyognNotIntersect(const ::std::vector<format::GeoPoint>& _simple_polygon1,
                            const ::std::vector<format::GeoPoint>& _simple_polygon2);

/**
 * @brief Check if two line segments are NOT intersected
 * @tparam T GeoPoint, MapPoint.
 * @param[in] _line1_point1 Terminal 1 of line segment 1
 * @param[in] _line1_point2 Terminal 2 of line segment 1
 * @param[in] _line2_point1 Terminal 1 of line segment 2
 * @param[in] _line2_point2 Terminal 2 of line segment 2
 * @return True If two lines are NOT intersected
 * @return False Otherwise
 */
template <typename T>
bool AreTwoLineNotIntersect(const T& _line1_point1, const T& _line1_point2, const T& _line2_point1,
                            const T& _line2_point2);

/**
 * @brief Check if two points are on different sides of a (reference) line segment
 * @tparam T GeoPoint, MapPoint
 * @param[in] _line_point1 Terminal 1 of line segment
 * @param[in] _line_point2 Terminal 2 of line segment
 * @param[in] _p1 Point 1
 * @param[in] _p2 Point 2
 * @return True If two points are on different sides w.r.t the reference line
 * @return False Otherwise
 */
template <typename T>
bool AreTwoPointsOnDifferentSidesOfLine(const T& _line_point1, const T& _line_point2, const T& _p1, const T& _p2);

/**
 * @brief Check if a point is inside a simple polygon
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _point The given point
 * @param[in] _simple_polygon The given simple polygon
 * @return A struct indicating whether P is inside/outside the line segment or overlapped with any terminal
 */
InOrOutEntity IsPointInSimplePolyogn(const format::GeoPoint&              _point,
                                     const std::vector<format::GeoPoint>& _simple_polygon);

/**
 * @brief Calculate the difference of two (simple) polygons
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon1 Polygon 1
 * @param[in] _simple_polygon2 Polygon 2
 * @param[out] _output_simple_polygons Difference expressed by points
 * @return Type of difference. 0 for no result,1 for polygon1 not break,2 for polygon1 break
 */
int DiffOfTwoSimplePolygons(const ::std::vector<format::GeoPoint>&        _simple_polygon1,
                            const ::std::vector<format::GeoPoint>&        _simple_polygon2,
                            std::vector<::std::vector<format::GeoPoint>>& _output_simple_polygons);

/**
 * @brief Calculate intersection of two simple polygons
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon1 Simple polygon 1
 * @param[in] _simple_polygon2 Simple polygon 2
 * @param[out] _output_simple_polygons Intersections expressed by points
 */
void IntersectionOfTwoSimplePolygons(const ::std::vector<format::GeoPoint>&        _simple_polygon1,
                                     const ::std::vector<format::GeoPoint>&        _simple_polygon2,
                                     std::vector<::std::vector<format::GeoPoint>>& _output_simple_polygons);

/**
 * @brief Calculate intersectons of two polygons.
 * @param[in] _polygon1 Polygon 1
 * @param[in] _polygon2 Polygon 2
 * @param[out] _output_polygons Intersections expressed by points
 */
void IntersectionOfTwoPolygons(const Polygon& _polygon1, const Polygon& _polygon2,
                               std::vector<Polygon>& _output_polygons);

/**
 * @brief Calculate union of two simple polygons
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html *
 * @param[in] _simple_polygon1 Simple polygon 1
 * @param[in] _simple_polygon2 Simple polygon 2
 * @param[out] _output_simple_polygons Unions expressed by points
 */
void UnionOfTwoSimplePolygons(const ::std::vector<format::GeoPoint>&        _simple_polygon1,
                              const ::std::vector<format::GeoPoint>&        _simple_polygon2,
                              std::vector<::std::vector<format::GeoPoint>>& _output_simple_polygons);

/**
 * @brief Calculate union of two polygons
 * @param[in] _polygon1 Polygon 1
 * @param[in] _polygon2 Polygon 2
 * @param[out] _output_polygons Unions expressed by points
 */
void UnionOfTwoPolygons(const Polygon& _polygon1, const Polygon& _polygon2, std::vector<Polygon>& _output_polygons);

/**
 * @brief Sort points lying on a same line accroding to the distance a reference point
 * @param[in] _points Points lying on a same line
 * @param[in] _ps Reference point of the line
 * @param[out] _output_points Sorted points
 */
void SortPointsInLine(const std::vector<format::GeoPoint>& _points, const format::GeoPoint& _ps,
                      std::vector<format::GeoPoint>& _output_points);

/**
 * @brief Sort a simple polygon's intersection points and corner points.
 * @param[in] _points Selected corner points of polygon
 * @param[in] _simple_polygon The given polygon
 * @return Points composed by polygon's corner points and intersection points
 */
std::vector<std::vector<format::GeoPoint>> SortPointsInPolygon(const std::vector<format::GeoPoint>& _points,
                                                               const std::vector<format::GeoPoint>& _simple_polygon);

/**
 * @brief Get a new (simple) polygon from (original) simple polygon and intersection points.
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _polygon_intersections  Intersection points of polygon
 * @param[in] _simple_polygon Reference (simple) polygon
 * @param[out] _new_polygon New polygon calculated herein
 */
void PolygonUnionIntersectPoint(const std::map<std::size_t, std::vector<format::GeoPoint>>& _polygon_intersections,
                                const std::vector<format::GeoPoint>&                        _simple_polygon,
                                std::vector<format::GeoPoint>&                              _new_polygon);

/**
 * @brief Check if the target point is inside a vector of points.
 * @param[in] _point Target point
 * @param[in] _points Vector of points
 * @return True Target point is inside
 * @return False Otherwise
 */
bool IsPointContained(const format::GeoPoint& _point, const std::vector<format::GeoPoint>& _points);

/**
 * @brief Check if a point is inside a polygon
 * @param[in] _point Target point
 * @param[in] _polygon Polygon
 * @return True Target point is inside
 * @return False Otherwise
 */
bool IsPointInPolygon2D(const MapPoint& _point, const Polygon& _polygon);

/**
 * @brief Check if two lines are crossed
 * @param[in] _line_1 Line 1
 * @param[in] _line_2 Line 2
 * @return True If two lines are crossed
 * @return False Otherwise
 */
bool AreLinesCrossed(const ::std::vector<format::GeoPoint>& _line_1, const ::std::vector<format::GeoPoint>& _line_2);

/**
 * @brief Calculate intersection of polygons
 * @param[in] _polygons A vector of polygons
 * @return Results of intersection in terms of polygons
 */
::std::vector<geometry::Polygon> Intersection2DAsPolygons(const ::std::vector<Polygon>& _polygons);

/**
 * @brief Calculate union of polygons
 * @param[in] _polygons A vector of polygons
 * @return Results of union in terms of polygons
 */
::std::vector<geometry::Polygon> Union2DAsPolygons(const ::std::vector<Polygon>& _polygons);

/**
 * @brief Get the envelope of a simple polygon
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon A simple polygon
 * @param[out] _envelop An envelope of polygon @see Envelop
 */
void GetRingEnvelope(const ::std::vector<format::GeoPoint>& _simple_polygon, Envelope& _envelope);

/**
 * @brief Calculate the area of a (simple) polygon
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon A (simple) polygon whose area is to be calculated
 * @return Area of given simple polygon
 */
double GetRingArea(const ::std::vector<format::GeoPoint>& _simple_polygon);

/**
 * @brief Get circumference of a simple polygon
 * @details A simple polygon has no interior rings. @see https://wrf.ecse.rpi.edu//Research/Short_Notes/pnpoly.html
 * @param[in] _simple_polygon A simple polygon
 * @return Circumference of polygon
 */
double GetRingLength(const ::std::vector<format::GeoPoint>& _simple_polygon);

/**
 * @brief Simplify a line by Douglas–Peucker algorithm
 * @param[in] _input_point Input points
 * @param[in] _span The max distance from original line to the generated line
 * @param[out] _out_point Generated line.
 */
void LineFitDP(const std::vector<format::GeoPoint>& _input_point, double _span,
               std::vector<format::GeoPoint>& _out_point);

/**
 * @brief Translate a vector from type LL to LLXYH
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
::std::vector<LLXYH> ToVecLLXYH(const ::std::vector<LL>& _vec1);

/**
 * @brief Translate a vector from type LL to GeoPoint
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<format::GeoPoint> ToVecGeoPoint(const std::vector<LL>& _vec1);

/**
 * @brief Translate a vector from type LLXYH to LL
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
::std::vector<LL> ToVecLL(const ::std::vector<LLXYH>& _vec1);

/**
 * @brief Translate a vector from type LLXYH to XY
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
::std::vector<MapPoint> ToVecXY(const ::std::vector<LLXYH>& _vec1);

/**
 * @brief Translate a vector from type LLXYH Vec1 into XY Vec2
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<MapPoint> ToVecXY(const std::vector<LL>& _vec1);

/**
 * @brief Translate a vector from type GeoPoint to XY;
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<MapPoint> ToVecXY(const std::vector<format::GeoPoint>& _vec1);

/**
 * @brief Translate a vector from type XYH to XY
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<MapPoint> ToVecXY(const std::vector<MapPoint3>& _vec1);

/**
 * @brief Translate a vector from type LLH to LLXYH
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
::std::vector<LLXYH> ToVecLLXYH(const ::std::vector<LLH>& _vec1);

/**
 * @brief Translate a vector from type MapPoint3 into LLXYH
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<LLXYH> ToVecLLXYH(const std::vector<MapPoint3>& _vec1);

/**
 * @brief Translate a vector from type MapPoint3 into GeoPoint
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<format::GeoPoint> ToVecGeoPoint(const std::vector<MapPoint3>& _vec1);

/**
 * @brief Translate a vector from type Position into GeoPoint
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<format::GeoPoint> ToVecGeoPoint(const std::vector<format::Position>& _vec1);

/**
 * @brief Translate a vector from type LLXYH to MapPoint3
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<MapPoint3> ToVecXYH(const VecLLXYH& _vec1);

/**
 * @brief Translate a vector from type LLXYH to MapPoint3
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<MapPoint3> ToVecXYH(const std::vector<format::GeoPoint>& _vec1);

/**
 * @brief Translate a vector from type format::Position to MapPoint
 * @param[in] _vec1 original vector
 * @return Translated vector
 */
std::vector<MapPoint> ToVecXY(const std::vector<format::Position>& _vec1);

/**
 * @brief Convert the target point in types of lat/lon to Geopoint
 * @param[in] _longitude Longitude of target point
 * @param[in] _latitude Latitude of target point
 * @param[in] _h Height  of target point
 * @return Point in formats of GeoPoint
 */
inline format::GeoPoint LonLatHToGeoPoint(const float64_t _longitude, const float64_t _latitude, const float64_t _h)
{
    const LL       ll(_latitude, _longitude);
    const MapPoint tmpmpoint = ll.ToXY();
    return format::GeoPoint(_h, geometry::GetX(tmpmpoint), geometry::GetY(tmpmpoint));
}

/**
 * @brief Convert the format of target point from Point3 to GeoPoint
 * @param[in] _x X of target point
 * @param[in] _y Y of target point
 * @param[in] _h Z of target point
 * @param[in] multiple Multiplication of Z. Default is 100, i.e. from cm to m.
 * @return Point in formats of GeoPoint
 */
inline format::GeoPoint XYHToGeoPoint(const Distance _x, const Distance _y, const Distance _h, int multiple = 100)
{
    return format::GeoPoint(_h * multiple, _x, _y);  // m->cm
}

/**
 * @brief Convert the format of target point from Point3 to GeoPoint
 * @param[in] _point3 Point 3d whose Z in given in meters
 * @return Point in formats of GeoPoint
 */
inline format::GeoPoint XYHToGeoPoint(const MapPoint3& _p, int multiple = 100)
{
    return format::GeoPoint(geometry::GetZ(_p) * multiple, geometry::GetX(_p), geometry::GetY(_p));  // m->cm
}

/**
 * @brief Convert the format of target point from Position to GeoPoint
 * @param[in] _p Target point
 * @return Converted point
 */
inline format::GeoPoint PositionToGeoPoint(const format::Position& _p)
{
    return format::GeoPoint(_p.GetHeightCm(), GetX(_p), GetY(_p));
}

/**
 * @brief Convert the format of target point from MapPoint3 to MapPoint
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint GetPointXY(const MapPoint3& _point)
{
    return _point.GetPointXY();
}

/**
 * @brief Convert the format of target point from GeoPoint to MapPoint
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint GetPointXY(const format::GeoPoint& _point)
{
    return holo::geometry::Point2(_point.GetX(), _point.GetY());
}

/**
 * @brief Convert the format of target point from LLXYH to MapPoint
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint GetPointXY(const LLXYH& _point)
{
    return _point.GetPointXY();
}

/**
 * @brief Convert the format of target point from Position to MapPoint
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint GetPointXY(const format::Position& _point)
{
    return holo::geometry::Point2(_point.GetX(), _point.GetY());
}

/**
 * @brief Convert the format of target point from MapPoint3 to LatLon
 * @param[in] _point Target point
 * @return Converted point
 */
inline LL GetLL(const MapPoint3& _point)
{
    LL ll;
    ll.SetByXY(GetPointXY(_point));
    return ll;
}

/**
 * @brief Convert the format of target point from MapPoint to LatLon
 * @param[in] _point Target point
 * @return Converted point
 */
inline LL GetLL(const MapPoint& _point)
{
    LL ll;
    ll.SetByXY(_point);
    return ll;
}

/**
 * @brief Convert the format of target point from GeoPoint to LatLon
 * @param[in] _point Target point
 * @return Converted point
 */
inline LL GetLL(const format::GeoPoint& _point)
{
    LL ll;
    ll.SetByXY(GetPointXY(_point));
    return ll;
}

/**
 * @brief Convert the format of target point from GeoPoint to MapPoint3
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint3 GetPointXYH(const format::GeoPoint& _point)
{
    return holo::geometry::Point3(_point.GetX(), _point.GetY(), GetZ(_point));
}

/**
 * @brief Convert the format of target point from LLXYH to MapPoint3
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint3 GetPointXYH(const LLXYH& _point)
{
    return _point.GetPointXYH();
}

/**
 * @brief Convert the format of target point from Position to MapPoint3
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint3 GetPointXYH(const format::Position& _point)
{
    return holo::geometry::Point3(_point.GetX(), _point.GetY(), _point.GetHeightCm() * 0.01);
}

/**
 * @brief Set X coordinate of a point
 * @param[in] x value of associated coordinate
 * @param[out] _point Point whose x is to be set
 */
inline void SetX(const Distance _x, MapPoint& _point)
{
    _point.SetX(_x);
}

/**
 * @brief Set X coordinate of a point
 * @param[in] x value of associated coordinate
 * @param[out] _point Point whose x is to be set
 */
inline void SetX(const Distance _x, MapVector2& _vec)
{
    _vec.At(0) = _x;
}

/**
 * @brief Set X coordinate of a point
 * @param[in] x value of associated coordinate
 * @param[out] _point Point whose x is to be set
 */
inline void SetX(const Distance _x, MapVector3& _vec)
{
    _vec.At(0) = _x;
}

/**
 * @brief Set X coordinate of a point
 * @param[in] x value of associated coordinate
 * @param[out] _point Point whose x is to be set
 */
inline void SetX(const Distance _x, MapPoint3& _point)
{
    _point.SetX(_x);
}

/**
 * @brief Set X coordinate of a point
 * @param[in] x value of associated coordinate
 * @param[out] _point Point whose x is to be set
 */
inline void SetX(const Distance _x, format::GeoPoint& _point)
{
    _point.SetX(_x);
}

/**
 * @brief Set X coordinate of a point
 * @param[in] x value of associated coordinate
 * @param[out] _point Point whose x is to be set
 */
inline void SetX(const Distance _x, LLXYH& _point)
{
    _point.SetX(_x);
}

/**
 * @brief Set Y coordinate of a point
 * @param[in] y value of associated coordinate
 * @param[out] _point Point whose y is to be set
 */
inline void SetY(const Distance _y, MapPoint& _point)
{
    _point.SetY(_y);
}

/**
 * @brief Set Y coordinate of a point
 * @param[in] y value of associated coordinate
 * @param[out] _point Point whose y is to be set
 */
inline void SetY(const Distance _y, MapVector2& _vec)
{
    _vec.At(1) = _y;
}

/**
 * @brief Set Y coordinate of a point
 * @param[in] y value of associated coordinate
 * @param[out] _point Point whose y is to be set
 */
inline void SetY(const Distance _y, MapVector3& _vec)
{
    _vec.At(1) = _y;
}

/**
 * @brief Set Y coordinate of a point
 * @param[in] y value of associated coordinate
 * @param[out] _point Point whose y is to be set
 */
inline void SetY(const Distance _y, MapPoint3& _point)
{
    _point.SetY(_y);
}

/**
 * @brief Set Y coordinate of a point
 * @param[in] y value of associated coordinate
 * @param[out] _point Point whose y is to be set
 */
inline void SetY(const Distance _y, format::GeoPoint& _point)
{
    _point.SetY(_y);
}

/**
 * @brief Set Y coordinate of a point
 * @param[in] y value of associated coordinate
 * @param[out] _point Point whose y is to be set
 */
inline void SetY(const Distance _y, LLXYH& _point)
{
    _point.SetY(_y);
}

/**
 * @brief Set Z coordinate of a point
 * @param[in] z value of associated coordinate
 * @param[out] _point Point whose z is to be set
 */
inline void SetZ(const Distance _z, MapPoint3& _point)
{
    _point.SetZ(_z);
}

/**
 * @brief Set Z coordinate of a point
 * @param[in] z value of associated coordinate
 * @param[out] _point Point whose z is to be set
 */
inline void SetZ(const Distance, MapVector2&)
{
    // vec2d does not have Z
}

/**
 * @brief Set Z coordinate of a point
 * @param[in] z value of associated coordinate
 * @param[out] _point Point whose z is to be set
 */
inline void SetZ(const Distance _z, MapVector3& _vec)
{
    _vec.At(2) = _z;
}

/**
 * @brief Set Z coordinate of a point
 * @param[in] z value of associated coordinate
 * @param[out] _point Point whose z is to be set
 */
inline void SetZ(const Distance _z, format::GeoPoint& _point)
{
    // m to cm
    _point.SetHeightCm(_z * 100.0);
}

/**
 * @brief Set Z coordinate of a point
 * @param[in] z value of associated coordinate
 * @param[out] _point Point whose z is to be set
 */
inline void SetZ(const Distance _z, LLXYH& _point)
{
    _point.SetZ(_z);
}

/**
 * @brief Set Z coordinate of a point
 * @param[in] z value of associated coordinate
 * @param[out] _point Point whose z is to be set
 */
inline void SetZ(const Distance, MapPoint&)
{
    // point2d does not have Z
}

/**
 * @brief Calculate distance from point1 and point2 in 2D
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] point1 Point 1
 * @param[in] point2 Point 2
 * @return 2D Distance between both points
 */
template <typename T>
Distance Dist2D(const T& point1, const T& point2);

/**
 * @brief Calculate distance from point1 and point2 in 3D
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] point1 Point 1
 * @param[in] point2 Point 2
 * @return 3D Distance between both points
 */
template <typename T>
Distance Dist3D(const T& point1, const T& point2);

/**
 * @brief Calculate squared distance on point1 and point2 in 2D
 * @details This function works faster than Dist2D if we intend to compare two distance values, as the operation of sqrt
 * is not needed.
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] point1 Point 1
 * @param[in] point2 Point 2
 * @return Squared distance in 2D
 */
template <typename T>
Distance DistSqr2D(const T& point1, const T& point2);

/**
 * @brief Calculate Euclidean distance between two geographic points.
 *
 * @tparam T MapPoint, MapPoint3, GeoPoint.
 * @details Convert two geographic points to same UTM coordinate and calculate
 *          Euclidean distance. The final UTM coordinate base on p1. Only support
 *          WGS84 and UTM6 now.
 * @param[in] p1 A geographic point with valid coordinate info.
 * @param[in] p2 A geographic point with valid coordinate info.
 * @return Euclidean Distance. If return std::numeric_limits<Distance>::max(),
 *          an error occurs in this function.
 */
template <typename T>
Distance DistSqr2D(const holo::map::format::geometry::GeographicParameterType<T>& p1,
                   const holo::map::format::geometry::GeographicParameterType<T>& p2);

/**
 * @brief Calculate squared distance on point1 and point2 in 3D
 * @details This function works faster than Dist2D if we intend to compare two distance values, as the operation of sqrt
 * is not needed.
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] point1 Point 1
 * @param[in] point2 Point 2
 * @return Squared distance in 3D
 */
template <typename T>
Distance DistSqr3D(const T& point1, const T& point2);

/**
 * @brief Rotating Calipers
 * @tparam T GeoPoint
 * @param[in] _points Convex hull
 * @return Minimal rectangular area
 */
template <typename T>
::std::vector<T> RotatingCalipers(const ::std::vector<T>& _points);

/**
 * @brief Get 2D normal vector with specific direction
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] _vec Coordinate vector
 * @param[in] _direction Direction of normal vector w.r.t input vector, can be either Direction::DIR_LEFT,
 * Direction::DIR_RIGHT the right side of the input vector's direction.
 * @param[out] _normal Coordinate of normal vector
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool Normal2D(const T& _vec, const Direction _direction, T& _normal);

/**
 * @brief Calculate the total length of line composed of sampling points in 2D
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] _vec Points
 * @return Total length in units of meters
 */
template <typename T>
holo::float64_t GetVecLength(const std::vector<T>& _vec);

/**
 * @brief Calculate the total length of line composed of sampling points in 2D
 * @tparam T GeoPoint, MapPoint, MapPoint3
 * @param[in] _vec Points
 * @param[out] _length Total length in units of meters
 * @param[in] _start_idx Index of starting point if we only care about part of the line
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool GetVecLength(const std::vector<T>& _vec, Distance& _length, const Size _start_idx = 0);

/**
 * @brief Calculate sub path length between start index and end index.
 * @tparam T GeoPoint, MapPoint, MapPoint3.
 * @param[in] points A path with multiple points(must more than 2 points).
 * @param[out] length Sub path length from start index to end index.
 * @param[in] start_idx Start point index, 0 <= start_idx < end_idx.
 * @param[in] end_idx End point index of sub path, start_idx < end_idx <= count(size of points).
 * @return true: No error.
 *         false: An error occurs in this function, please check the log for details.
 */
template <typename T>
holo::bool_t GetVecLength(std::vector<T> const& points, Distance& length, std::size_t const start_idx, std::size_t const end_idx);

/**
 * @brief Fitting a straight line with form @f$y = k * x + b@f$
 * @param[in] _point1 Start point
 * @param[in] _point2 End point
 * @param[out] _k Coefficient
 * @param[out] _b Coefficient
 */
void FittingStraightLine(const MapPoint& _point1, const MapPoint& _point2, Distance& _k, Distance& _b);

/**
 * @brief Determine whether target point is between two lines.
 * @param[in] ref_point1 Start point of line 1
 * @param[in] ref_point2 End point of line 1
 * @param[in] ref_point3 Start point of line 2
 * @param[in] ref_point4 End point of line 2
 * @return true If target point locates in-between
 * @return false Otherwise
 */
bool IsBetweenTwoLines(const MapPoint& _target, const MapPoint& _point1, const MapPoint& _point2,
                       const MapPoint& _point3, const MapPoint& _point4);

/**
 * @brief Calculate angle between vector (p2 - ori) and vector (p1 - ori)
 * @details If angle > 0, vector destination is anti-clockwise rotation in relative with origin; if angle < 0, vector
 * destination is clockwise rotation in relative with origin
 * @param[in] _vec_ori Vector of origin, i.e. from p1 to origin
 * @param[in] _vec_dest Vector of destination, i.e. from p2 to origin
 * @return Rotation angle in rad
 */
MapRadian CalcRotationAngle(const MapPoint& _vec_ori, const MapPoint& _vec_dest);

/**
 * @brief Calculate angle between two vectors
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _vec_ori Vector of origin
 * @param[in] _vec_dest Vector of destination
 * @param[in] index Position to cut the vectors, if the angle is calculated from part of both vectors. For vector of
 * origin, we take the points from 0 to index for preceeding direction; For vector of destination, we take the points
 * until last element - index
 * @param[in] preceding Direction of index taken
 * @return Rotation angle in rad
 */
template <typename T>
MapRadian CalcRotationAngle(const ::std::vector<T>& _vec_ori, const ::std::vector<T>& _vec_dest, size_t index = 2,
                            const bool preceding = true);

/**
 * @brief Find out and modify the exceptional Z-values
 * @param[in,out] _vec Vector of points
 * @param[in] _replace True: repair this z value; false: delete this point
 * @param[in] _mean_diff_threshold Maximal allowed difference of each Z w.r.t the mean value
 * @param[in] _jump_diff_threshold maximal allowed difference jumps. A jump is defined as the difference between current
 * and its preceeding and succeeding values.
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool SmoothZ(std::vector<T>& _vec, const bool _replace = true, const holo::float64_t _mean_diff_threshold = 1.5,
             const holo::float64_t _jump_diff_threshold = 0.3);

/**
 * @brief Check if vector 2 is on which side of vector 1.
 * @details This function will simplify a line string by a line segment with the same start and end point of original
 * line 1) If on right side, return Direction::DIR_RIGHT; 2) If on left side, return Direction::DIR_LEFT; 3) If they
 * have intersection, return Direction::UNKNOWN 4) Invalid input arguments, return Direction::ERROR
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _vec1 Vector 1
 * @param[in] _vec2 Vector 2
 * @param[out] _dir Direction
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool OnWhichSide(const std::vector<T>& _vec1, const std::vector<T>& _vec2, Direction& _dir);

/**
 * @brief Fitting a range of values according to a line.
 * @details Say we have a list of elements defined by first and last elements, and we have a line composed of
 * points p0, p1,....pn. We need to derive the elements in the range so that each element compared to first element is
 * equal to the distance from associated point to line head.
 * @tparam MapPoint, MapPoint3, GeoPoint
 * @param[in] _vec1 Line composed of vector of points
 * @param[in] _start_value First element of range
 * @param[in] _end_value Last element of range
 * @param[out] values Generated elements in range
 * @return true If operation succeeded.
 */
template <typename T>
bool CalculateIntermediateValuesByDistance2D(const std::vector<T>& _vec1, const holo::float64_t _start_value,
                                             const holo::float64_t _end_value, std::vector<holo::float64_t>& values);

/**
 * @brief Calculate union of polygon vector (called by Union2DAsPolygons)
 * @param[in] _polygons Vector of polygons
 * @return Union
 */
::std::vector<geometry::Polygon> Union2DAsPolygons_r(const ::std::vector<Polygon>& _polygons);

/**
 * @brief Calculate convex hull *
 * @param[in] _points Points
 * @return Convex hull
 */
::std::vector<::holo::geometry::Point2d> ConvexHull(::std::vector<::holo::geometry::Point2d> _points);

/**
 * @brief Convert the format of target point from MapPoint3 to MapPoint3
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint3& _p0, MapPoint3& _p1)
{
    _p1 = _p0;
}

/**
 * @brief Convert the format of target point from MapPoint3 to MapPoint
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint3& _p0, MapPoint& _p1)
{
    _p1 = _p0.GetPointXY();
}

/**
 * @brief Convert the format of target point from MapPoint3 to GeoPoint
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint3& _p0, format::GeoPoint& _p1)
{
    _p1 = geometry::XYHToGeoPoint(_p0);
}

/**
 * @brief Convert the format of target point from MapPoint to MapPoint3
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint& _p0, MapPoint3& _p1)
{
    _p1.Set(geometry::GetX(_p0), geometry::GetY(_p0), 0.0);
}

/**
 * @brief Convert the format of target point from MapPoint to MapPoint
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint& _p0, MapPoint& _p1)
{
    _p1 = _p0;
}

/**
 * @brief Convert the format of target point from MapPoint to GeoPoint
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint& _p0, format::GeoPoint& _p1)
{
    _p1 = geometry::XYHToGeoPoint(geometry::GetX(_p0), geometry::GetY(_p0), 0.0);
}

/**
 * @brief Convert the format of target point from MapPoint to Position
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint& _p0, format::Position& _p1)
{
    _p1.SetX(GetX(_p0));
    _p1.SetY(GetY(_p0));
    _p1.SetHeightCm(0);
}

/**
 * @brief Convert the format of target point from MapPoint3 to Position
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPoint3& _p0, format::Position& _p1)
{
    _p1.SetX(GetX(_p0));
    _p1.SetY(GetY(_p0));
    _p1.SetHeightCm(GetZ(_p0) * 100);
}

/**
 * @brief Convert the format of target point from GeoPoint to GeoPoint
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const format::GeoPoint& _p0, format::GeoPoint& _p1)
{
    _p1 = _p0;
}

/**
 * @brief Convert the format of target point from GeoPoint to MapPoint3
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const format::GeoPoint& _p0, MapPoint3& _p1)
{
    _p1 = geometry::GetPointXYH(_p0);
}

/**
 * @brief Convert the format of target point from GeoPoint to MapPoint
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const format::GeoPoint& _p0, MapPoint& _p1)
{
    _p1 = geometry::GetPointXY(_p0);
}

/**
 * @brief Convert the format of target point from MapPose3 to MapPoint3
 * @param[in] _p0 Target point
 * @param[out] _p1 Converted point
 */
inline void ConvertPoint(const MapPose3& _p0, MapPoint3& _p1)
{
    _p1.Set(geometry::GetX(_p0), geometry::GetY(_p0), geometry::GetZ(_p0));
}

/**
 * @brief Convert the format of a vector of target points from MapPoint3 to MapPoint3
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<MapPoint3>& _line0, std::vector<MapPoint3>& _line1)
{
    _line1 = _line0;
}

/**
 * @brief Convert the format of a vector of target points from MapPoint to MapPoint3
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<MapPoint3>& _line0, std::vector<MapPoint>& _line1)
{
    _line1.clear();
    _line1.reserve(_line0.size());
    for (const auto& p : _line0)
    {
        _line1.emplace_back(p.GetPointXY());
    }
}

/**
 * @brief Convert the format of a vector of target points from MapPoint3 to GeoPoint
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<MapPoint3>& _line0, std::vector<format::GeoPoint>& _line1)
{
    _line1.clear();
    _line1.reserve(_line0.size());
    for (const auto& p : _line0)
    {
        _line1.emplace_back(geometry::XYHToGeoPoint(p));
    }
}

/**
 * @brief Convert the format of a vector of target points from MapPoint to MapPoint3
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<MapPoint>& _line0, std::vector<MapPoint3>& _line1)
{
    _line1.clear();
    _line1.reserve(_line0.size());
    for (const auto& p : _line0)
    {
        _line1.emplace_back(geometry::GetX(p), geometry::GetY(p), 0.0);
    }
}

/**
 * @brief Convert the format of c from MapPoint to MapPoint
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<MapPoint>& _line0, std::vector<MapPoint>& _line1)
{
    _line1 = _line0;
}

/**
 * @brief Convert the format of a vector of target points from MapPoint to GeoPoint
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<MapPoint>& _line0, std::vector<format::GeoPoint>& _line1)
{
    _line1.clear();
    _line1.reserve(_line0.size());
    for (const auto& p : _line0)
    {
        _line1.emplace_back(geometry::XYHToGeoPoint(geometry::GetX(p), geometry::GetY(p), 0.0));
    }
}

/**
 * @brief Convert the format of a vector of target points from GeoPoint to MapPoint3
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<format::GeoPoint>& _line0, std::vector<MapPoint3>& _line1)
{
    _line1.clear();
    _line1.reserve(_line0.size());
    for (const auto& p : _line0)
    {
        _line1.emplace_back(geometry::GetPointXYH(p));
    }
}

/**
 * @brief Convert the format of a vector of target points from GeoPoint to GeoPoint
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<format::GeoPoint>& _line0, std::vector<format::GeoPoint>& _line1)
{
    _line1 = _line0;
}

/**
 * @brief Convert the format of a vector of target points from GeoPoint to MapPoint
 * @param[in] _line0 Target vector of points
 * @param[out] _line1 Converted vector of points
 */
inline void ConvertPoints(const std::vector<format::GeoPoint>& _line0, std::vector<MapPoint>& _line1)
{
    _line1.clear();
    _line1.reserve(_line0.size());
    for (const auto& p : _line0)
    {
        _line1.emplace_back(geometry::GetPointXY(p));
    }
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<MapPoint3>& _l, const MapPoint3& _p)
{
    _l.emplace_back(_p);
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<MapPoint3>& _l, const MapPoint& _p)
{
    _l.emplace_back(geometry::GetX(_p), geometry::GetY(_p), 0.0);
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<MapPoint3>& _l, const format::GeoPoint& _p)
{
    _l.emplace_back(geometry::GetPointXYH(_p));
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<MapPoint>& _l, const MapPoint3& _p)
{
    _l.emplace_back(_p.GetPointXY());
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<MapPoint>& _l, const MapPoint& _p)
{
    _l.emplace_back(_p);
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<MapPoint>& _l, const format::GeoPoint& _p)
{
    _l.emplace_back(geometry::GetX(_p), geometry::GetY(_p));
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<format::GeoPoint>& _l, const MapPoint3& _p)
{
    _l.emplace_back(geometry::XYHToGeoPoint(_p));
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<format::GeoPoint>& _l, const MapPoint& _p)
{
    _l.emplace_back(geometry::XYHToGeoPoint(geometry::GetX(_p), geometry::GetY(_p), 0.0));
}

/**
 * @brief Add a point to the end of a line.
 * @note There is no check of duplicates
 * @param[out] _l A line to be extended
 * @param[in] _p Point to add
 */
inline void AddPoint(std::vector<format::GeoPoint>& _l, const format::GeoPoint& _p)
{
    _l.emplace_back(_p);
}

/**
 * @brief Polyfit a 2D line and generated a smoother one.
 * @param[in] _line A line in terms of (X,Y)
 * @param[out] _new_line Smoothed line
 * @param[in] _ref_x If not empty, use this vector as reference indices, otherwise use original x
 * @return true If operation succeeded
 */
bool PolyfitLine2D(const std::vector<MapPoint>& _line, std::vector<MapPoint>& _new_line,
                   const std::vector<double>& _ref_x = std::vector<double>());

/**
 * @brief Polyfit a 3D line and generated a smoother one.
 * @note Note both Y and Z will be smoothed separately w.r.t X
 * @tparam T GeoPoint, MapPoint3D
 * @param[in] _line A line either in 2D or 3D
 * @param[out] _new_line Smoothed line
 * @param[in] _ref_x If not empty, use this vector as reference indices, otherwise use original x
 * @return true If operation succeeded
 */
template <typename T>
bool PolyfitLine3D(const std::vector<T>& _line, std::vector<T>& _new_line,
                   const std::vector<double>& _ref_x = std::vector<double>());

/**
 * @brief Create two lines composed pf equally distributed points
 * @details Given two parallel lines with (probably) different number of reference points, calculate two lines with same
 * length but same number of reference points with (almost) equal distribution
 * @tparam T GeoPoint, MapPoint3D
 * @param[in] _line1 Original line 1
 * @param[in] _line2 Original line 2
 * @param[out] _new_line1 New line associated to line 1
 * @param[out] _new_line2 New line associated to line 2
 * @param[in] _num_points Number of points that line 1 and 2 shall have. Default value is 0, meaning we do not specify
 * this value and leave it to be done automatically inside function. In this case, we choose the greater number of size
 * of both lines.
 * @return true If operation succeeded
 */
template <typename T>
bool CreateTwoLinesWithEquallyDistributedPoints(const std::vector<T>& _line1, const std::vector<T>& _line2,
                                                std::vector<T>& _new_line1, std::vector<T>& _new_line2,
                                                const Size _num_points = 0);

/**
 * @brief Restore Y-value of a re-sampled lines from its original counterpart
 * @tparam T GeoPoint,Point2, Point3
 * @param[in] _ori_line Original line (before re-sampling)
 * @param[in] _sampled_line Re-sampled line (in X-dimension)
 * @param[out] _new_line New line that follows the same re-sampling in X-dimension but its Y-value follows the original
 * counterpart
 * @return true If operation succeeded
 * @return false Otherwise
 */
template <typename T>
bool ResetYFromReferenceLine(const std::vector<T>& _ori_line, const std::vector<T>& _sampled_line,
                             std::vector<T>& _new_line);

/**
 * @brief Reset Z value of original line based on a reference line
 * @tparam T GeoPoint,Point2, Point3
 * @param[in, out] _ori_line original line whose Z value is to be reset
 * @param[in] _ref_line reference line
 * @return true: if operation succeeded; false: otherwise
 */
template <typename T>
bool ResetZFromReferenceLine(std::vector<T>& _ori_line, const std::vector<T>& _ref_line);

/**
 * @brief Cut a line into segments with X or Y equally distributed
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] _line1 Original line
 * @param[in] _num_section Number of sections that the line shall be cut to
 * @param[out] _cut_line Line after cutting
 * @return true If operation succeeded
 */
template <typename T>
bool CutLineEquallyByXY(const std::vector<T>& _line1, const map::Size _num_section, std::vector<T>& _cut_line);

/**
 * @brief Check if there is any outlier in given line
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] points Line to be checked
 * @param[in] max_delta Threshold to check the jump
 * @return True If this line has outlier in Z
 * @return False Otherwise
 */
template <typename T>
bool HasZOutlier(const std::vector<T>& points, const ::holo::float64_t max_delta = 0.5);

/**
 * @brief Get a part of line by start/end position.
 * @tparam T MapPoint, MapPoint3, GeoPoint
 * @param[in] line       Line
 * @param[in] start_pos  Start position [0, 100]
 * @param[in] end_pos    End position [0, 100]
 * @param[out] part_line A part of inputing line
 * @return True Operation successful.
 * @return False Otherwise
 */
template <typename T>
bool GetLineByStartAndEndPosition(const std::vector<T>& line, const holo::map::Distance start_pos,
                                  const holo::map::Distance end_pos, std::vector<T>& part_line);
}  // namespace geometry
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo
/**
 * @}
 */

#endif /* HOLO_MAP_COMMON_GEOMETRY_H_ */
