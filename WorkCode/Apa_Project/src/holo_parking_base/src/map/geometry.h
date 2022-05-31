/**
 * @file geometry.h
 * @brief 
 * @author wangminghui@holomatic.com
 * @date "2021-08-28"
 */

#include <cmath>
#include <limits>
#include <vector>
#include <glog/logging.h>
#include <holo/common/coordinate.h>
#include <holo/geometry/convex_polygon2.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/polyfit2.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace map
{
namespace geometry
{
using ScalarType = holo::float64_t;
using PointType = holo::geometry::Point3T<ScalarType>;
typedef holo::geometry::LineSegment2d MapLineSegment;
typedef holo::geometry::Point2d MapPoint;
typedef float64_t  Distance;
typedef float64_t  FloatChar13;
typedef ::std::size_t Size;
const Size MAX_SIZE   =   std::numeric_limits<Size>::max();
const Distance MAX_DISTANCE =  std::numeric_limits<Distance>::max();
const float64_t MAX_FLOAT64 = std::numeric_limits<float64_t>::max();

/**
 * @brief Convert the format of target point from PointType to MapPoint
 * @param[in] _point Target point
 * @return Converted point
 */
inline MapPoint GetPointXY(const PointType& _point)
{
    return _point.GetPointXY();
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
    return MapPoint(_p1.GetX(), _p1.GetY()).Dist(MapPoint(_p2.GetX(), _p2.GetY())) < _max_span;
}


template <typename T>
Distance DistSqr2D(const T& _point1, const T& _point2)
{
    const holo::float64_t dist_x = _point1.GetX() - _point2.GetX();
    const holo::float64_t dist_y = _point1.GetY() - _point2.GetY();

    return dist_x * dist_x + dist_y * dist_y;
}


template <typename T>
Distance DistSqr3D(const T& point1, const T& point2)
{
    
    const holo::float64_t dist_x = point1.GetX() - point2.GetX();
    const holo::float64_t dist_y = point1.GetY() - point2.GetY();
    const holo::float64_t dist_z = point1.GetZ() - point2.GetZ();

    return dist_x * dist_x + dist_y * dist_y + dist_z * dist_z;
}

template <typename T>
Distance Dist3D(const T& _point1, const T& _point2)
{
    return ::std::sqrt(DistSqr3D(_point1, _point2));
}

template <typename T>
const T Polate(const T& _start_point, const T& _end_point, const FloatChar13 _polate_ratio)
{
    Distance polate_x = (_end_point.GetX() - _start_point.GetX()) * _polate_ratio;
    Distance polate_y = (_end_point.GetY() - _start_point.GetY()) * _polate_ratio;
    Distance polate_z = (_end_point.GetZ() - _start_point.GetZ()) * _polate_ratio;

    T polate_point;
    polate_point.SetX(_start_point.GetX() + polate_x );
    polate_point.SetY(_start_point.GetY() + polate_y);
    polate_point.SetZ(_start_point.GetZ() + polate_z);
    return polate_point;
}

template <typename T>
Distance CalculateDistanceFromPointToLineSegment2D(const T& _pos, const T& _head_line_segment,
                                                   const T& _end_line_segment, T& _project_point, bool& _is_outside)
{
    _project_point = T();
    _is_outside = false;
    // if head and end are same point.
    const MapPoint target_pos = GetPointXY(_pos);
    if (AreSamePointsIn2D(_head_line_segment, _end_line_segment))
    {
        _project_point = _head_line_segment;
        return Dist3D(_pos, _head_line_segment);
    }

    const MapLineSegment segment(GetPointXY(_head_line_segment), GetPointXY(_end_line_segment));
    // dot product
    const MapPoint   vector_target_start = target_pos - segment.GetStartPoint();
    const FloatChar13 dot_value  = vector_target_start.ToVector().Dot(segment.GetDirection());
    const FloatChar13 segment_length      = segment.GetLength();

    _project_point = Polate(_head_line_segment, _end_line_segment, dot_value / segment_length);

    if (dot_value - segment_length > 1e-6)
    {
        _is_outside = true;
        return Dist3D(_pos, _end_line_segment);
    }
    if (dot_value < 0)
    {
        _is_outside = true;
        return Dist3D(_pos, _head_line_segment);
    }
    return Dist3D(_pos, _project_point);
}



template <typename T>
bool GetClosestPoint2D(const T& _target, const std::vector<T>& _points, T& _closest_point, Size& _index,
                       Distance& _min_distance, const Size _start_id, const Size _check_num)
{
    _min_distance = MAX_FLOAT64;
    _index = MAX_SIZE;
    if (_points.empty())
    {
        LOG(ERROR) << "GetClosestPoint2D fail, invalid parameter";
        return false;
    }

    Size counter = 0;  // count for times when min_distance is not been updated

    Distance min_distance_sqr = MAX_DISTANCE;
    for (Size i = _start_id; i < _points.size(); ++i)
    {
        const Distance current_distance_sqr = DistSqr2D(_target, _points[i]);
        if (current_distance_sqr < min_distance_sqr)
        {
            min_distance_sqr = current_distance_sqr;
            _index           = i;
        }
        else if (++counter >= _check_num)
        {
            break;
        }
    }
    const bool got = min_distance_sqr != MAX_DISTANCE;
    if (got)
    {
        _closest_point = _points[_index];
        _min_distance  = ::std::sqrt(min_distance_sqr);
    }

    return got;
}

template <typename T>
bool CalculateDistanceToPoints2D(const T& _pos_target, const std::vector<T>& _points, Size& _first_id, Size& _second_id,
                                 T& _project_point, Distance& _min_distance, bool& _is_outside,
                                 const bool _local_check = false, const Size _start_idx = 0, const Size _check_num = 5)
{
    _first_id              = MAX_SIZE;
    _second_id             = MAX_SIZE;
    _min_distance          = MAX_DISTANCE;
    _is_outside            = false;
    _project_point = T();

    const Size size_points = _points.size();
    if (_start_idx + 2 > size_points)
    {
        LOG(ERROR) << "CalculateDistanceToPoints2D fail, invaid parameter, start_idx=" << _start_idx
                   << " points_size=" << size_points;
        return false;
    }

    // find out closest reference point to target point
    T closest_point;
    if (_local_check)
    {
        GetClosestPoint2D(_pos_target, _points, closest_point, _first_id, _min_distance, _start_idx, _check_num);
    }
    else
    {
        GetClosestPoint2D(_pos_target, _points, closest_point, _first_id, _min_distance, _start_idx, MAX_SIZE);
    }
    // get the closet "line segment" from the points
    // i.e. find another point that forms a line segment with closet point
    // and this line segment has the minimal distance to our target point
    if (_first_id == 0)
    {
        _second_id    = 1;
        _min_distance = CalculateDistanceFromPointToLineSegment2D(_pos_target, _points[_second_id], _points[_first_id],
                                                                  _project_point, _is_outside);
    }
    else if (_first_id + 1 == size_points)
    {
        // for first id < second id
        _second_id    = _first_id;
        _first_id     = _second_id - 1;
        _min_distance = CalculateDistanceFromPointToLineSegment2D(_pos_target, _points[_first_id], _points[_second_id],
                                                                  _project_point, _is_outside);
    }
    else
    {
        // if first_id is between first point and last point, but project point is outside of linesegment,
        // we regard the first point as project point
        bool           is_outside_last = false;
        bool           is_outside_next = false;

        T project_last;
        T project_next;

        const Distance dist_to_last    = CalculateDistanceFromPointToLineSegment2D(
            _pos_target, _points[_first_id - 1], _points[_first_id], project_last, is_outside_last);
        const Distance dist_to_next = CalculateDistanceFromPointToLineSegment2D(
            _pos_target, _points[_first_id + 1], _points[_first_id], project_next, is_outside_next);

        // Situation 1:
        //                     (K)
        //                (P)\  |  /(Q)
        //                    \ | /
        //                     \|/
        //                      ^(B)
        //                ^     |      ^
        //          ^           |           ^
        // (A)^                 |(T)             ^(C)
        //
        // Direction: from point A to point B to  point C(a boundary with point A and B and C).
        // A: _points[_first_id-1]
        // B: _points[_first_id]
        // C: _points[_first_id+1]
        // PB: is the normal vector of line segment AB;
        // BQ: is the normal vector of line segment BC;

        if (is_outside_last && is_outside_next)
        {
            // In situation 1: if a target point in angle PBQ(an acute angle).
            _project_point = _points[_first_id];
            // Q: why chose _first_id-1 and _first_id as the tareget segment?
            // A: Because the direction of boundary is A->B->C.
            _first_id      = _first_id - 1;
            _second_id     = _first_id + 1;
            _min_distance  = Dist3D(_pos_target, _project_point);
        }
        else if (!is_outside_last && is_outside_next)
        {
            // In situation 1: if a target point in angle ABP(a right angle).
            _project_point = project_last;
            _first_id      = _first_id - 1;
            _second_id     = _first_id + 1;
            _min_distance  = dist_to_last;
        }
        else if (is_outside_next && !is_outside_next)
        {
            // In situation 1: if a target point in angle QBC(a right angle).
            _project_point = project_next;
            _second_id     = _first_id + 1;
            _min_distance  = dist_to_next;
        }
        else // condition: !is_outside_last && !is_outside_next
        {
            if (dist_to_last <= dist_to_next)
            {
                // In situation1: if a target point in angle ABT and on line segment BT.
                _project_point = project_last;
                _first_id = _first_id - 1;
                _second_id = _first_id + 1;
                _min_distance = dist_to_last;
            }
            else
            {
                // In situation1: if a target point in angle TBC.
                _project_point = project_next;
                _second_id = _first_id + 1;
                _min_distance = dist_to_next;
            }
        }

        // If the closest point(Raw _first_id from GetClosestPoint2D()) is neither
        // the head nor the tail, the project point is regard as inside.
        _is_outside = false;
    }
    return true;
}


template <typename T>
holo::bool_t UpSampleRefPointsByIntervalconst(
    std::vector<T>&  _points,
    Distance const _intervalconst,
    std::vector<holo::float32_t>&  _distance,
    Distance const _tolerance)
{
    if(_tolerance < 0.0 || _points.size() < 2 || _intervalconst <= 0)
    {
        LOG(ERROR) << "UpSampleRefPointsByIntervalconst fail,"
                   << " _tolerance=" << _tolerance
                   << " _intervalconst=" << _intervalconst
                   << " _points_size=" <<  _points.size();
        return false;
    }
    std::vector<T> const points = _points;
    _points.clear();
    std::size_t const points_size = points.size();
    holo::float32_t total_distance = 0.0;
    for(std::size_t i = 1; i < points_size; ++i)
    {
        T const curr_point = points[i-1];
        T const next_point = points[i];
        Distance const curr_len = Dist3D(curr_point, next_point);
        if(curr_len < 1e-6)
        {
            LOG(ERROR) << "UpSampleRefPointsByIntervalconst error curr_len = "<<curr_len;
            continue;
        }
        _points.emplace_back(curr_point);
        _distance.push_back(total_distance);
        Distance curr_insert_len = _intervalconst;
        while ((curr_len - _tolerance - curr_insert_len) > 1e-6)
        {
            holo::float64_t const ratio = curr_insert_len / curr_len;
            T const insert_point = Polate(curr_point, next_point, ratio);
            _points.emplace_back(insert_point);
            _distance.push_back(total_distance + curr_insert_len);
            curr_insert_len = curr_insert_len + _intervalconst;
        }
        total_distance += curr_len;
    }
    _points.emplace_back(points[points_size -1]);
    _distance.push_back(total_distance);
    return true;
}

}  // namespace geometry
}  // namespace map
}  // namespace holo
