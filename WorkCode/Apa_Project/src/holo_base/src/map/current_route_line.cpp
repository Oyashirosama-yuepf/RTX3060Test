/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file current_route_line.cpp
 * @brief current_route_line: provide route line.
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#include <holo/map/current_route_info.h>

#include <holo/log/hololog.h>
#include <algorithm>

#include <holo/geometry/line_segment2.h>

namespace holo
{
namespace map
{
/**
 * @brief Format Point3d to json string.
 * @param [in] point Point in 3D.
 * @return Json string.
 */
static std::string FormatPoint(const holo::geometry::Point3d& point) noexcept
{
    std::stringstream stream;
    stream << std::setprecision(16) << "{\"x\":" << point.GetX() << ", "
           << "\"y\":" << point.GetY() << ", "
           << "\"z\":" << point.GetZ() << "}";

    return stream.str();
}

/**
 * @brief Format Point3d to json string.
 * @param [in] points Point in array.
 * @return Json string.
 */
static std::string FormatPoints(const std::vector<holo::geometry::Point3d>& points) noexcept
{
    std::stringstream stream;
    stream << "[";
    const std::size_t count = points.size();
    for (std::size_t i = 0U; i < count; ++i)
    {
        std::string end = i < count - 1 ? ", " : "";
        stream << FormatPoint(points[i]) << end;
    }
    stream << "]";
    return stream.str();
}

static std::string FormatIDs(const std::vector<KeyValue>& ids) noexcept
{
    std::stringstream stream;
    stream << "[";
    const std::size_t count = ids.size();
    for (std::size_t i = 0U; i < count; ++i)
    {
        const std::string end = i < count - 1 ? ", " : "";
        stream << ids[i] << end;
    }
    stream << "]";
    return stream.str();
}

template <typename T>
static float64_t CalcPointsLengthIn2D(const std::vector<T>& points) noexcept
{
    float64_t         length = 0.0;
    const std::size_t count  = points.size();
    for (size_t i = 1; i < count; ++i)
    {
        const holo::geometry::Point2d p1 = points[i - 1].GetPointXY();
        const holo::geometry::Point2d p2 = points[i].GetPointXY();
        length += p2.Dist(p1);
    }
    return length;
}

template <typename T>
static bool AreSamePointsIn2D(const T& point1, const T& point2, const float64_t threshold = 0.1) noexcept
{
    const holo::geometry::Point2d p1 = point1.GetPointXY();
    const holo::geometry::Point2d p2 = point2.GetPointXY();
    return p1.Dist(p2) < threshold;
}

template <typename T>
static float64_t CalculateDistanceFromPointToLineSegment2D(const T& position, const T& head_line_segment,
                                                           const T& end_line_segment) noexcept
{
    if (AreSamePointsIn2D(head_line_segment, end_line_segment))
    {
        std::vector<T> points{position, head_line_segment};
        return CalcPointsLengthIn2D(points);
    }

    // if this is a valid line segment, calculate the distance in
    // the general way
    const holo::geometry::LineSegment2d segment(head_line_segment.GetPointXY(), end_line_segment.GetPointXY());
    const holo::geometry::Point2d       pos = position.GetPointXY();
    return segment.Dist(pos);
}

template <typename T>
static bool CalculateDistanceToPoints2D(const T& pos_target, const std::vector<T>& points, std::size_t& first_id,
                                        std::size_t& second_id, T& project_point, float64_t& min_distance,
                                        bool& is_outside, const bool local_check, const std::size_t start_idx,
                                        const size_t check_num) noexcept
{
    first_id     = std::numeric_limits<std::size_t>::max();
    second_id    = std::numeric_limits<std::size_t>::max();
    min_distance = std::numeric_limits<float64_t>::max();

    const std::size_t size_points = points.size();
    if (start_idx + 2 > size_points)
    {
        return false;
    }

    const holo::geometry::Point2d target = pos_target.GetPointXY();

    {
        // find out closest reference point to target point
        float64_t   mindis  = std::numeric_limits<float64_t>::max();
        std::size_t counter = 0U;
        for (std::size_t i = start_idx; i < size_points; ++i)
        {
            const holo::geometry::Point2d pos = points[i].GetPointXY();
            const float64_t               dis = target.Dist(pos);
            if (dis < mindis)
            {
                mindis   = dis;
                first_id = i;
                counter  = 0U;
            }
            if (local_check)
            {
                if (++counter >= check_num)
                {
                    break;
                }
            }
        }
    }

    // get the closet "line segment" from the points
    // i.e. find another point that forms a line segment with closet point
    // and this line segment has the minimal distance to our target point
    if (first_id == 0)
    {
        second_id    = 1;
        min_distance = CalculateDistanceFromPointToLineSegment2D(pos_target, points[first_id], points[second_id]);
    }
    else if (first_id == size_points - 1)
    {
        second_id    = first_id - 1;
        min_distance = CalculateDistanceFromPointToLineSegment2D(pos_target, points[first_id], points[second_id]);
    }
    else
    {
        const float64_t dist_to_last =
            CalculateDistanceFromPointToLineSegment2D(pos_target, points[first_id], points[first_id - 1]);
        const float64_t dist_to_next =
            CalculateDistanceFromPointToLineSegment2D(pos_target, points[first_id], points[first_id + 1]);

        if (dist_to_last < dist_to_next)
        {
            second_id    = first_id - 1;
            min_distance = dist_to_last;
        }
        else
        {
            second_id    = first_id + 1;
            min_distance = dist_to_next;
        }
    }

    const holo::geometry::Point2d first_point  = points[first_id].GetPointXY();
    const holo::geometry::Point2d second_point = points[second_id].GetPointXY();

    // Check if point is outside the range of points or not
    is_outside = false;
    if ((0 == first_id || size_points - 1 == first_id) && std::fabs(min_distance) > 0.000001)
    {
        holo::geometry::Point2d vec1(second_point.GetX() - first_point.GetX(),
                                     second_point.GetY() - first_point.GetY());
        holo::geometry::Point2d vec2(target.GetX() - first_point.GetX(), target.GetY() - first_point.GetY());
        // Normalize vec1 and vec2
        const float64_t norm_vec1 = std::sqrt(vec1.GetX() * vec1.GetX() + vec1.GetY() * vec1.GetY());
        const float64_t norm_vec2 = std::sqrt(vec2.GetX() * vec2.GetX() + vec2.GetY() * vec2.GetY());
        const float64_t vec1_x    = vec1.GetX() / norm_vec1;
        const float64_t vec1_y    = vec1.GetY() / norm_vec1;
        const float64_t vec2_x    = vec2.GetX() / norm_vec2;
        const float64_t vec2_y    = vec2.GetY() / norm_vec2;
        vec1.Set(vec1_x, vec1_y);
        vec2.Set(vec2_x, vec2_y);
        is_outside = (vec1.GetX() * vec2.GetX() + vec1.GetY() * vec2.GetY()) < 0.0;
    }

    {
        if (first_point == second_point)
        {
            project_point = points[first_id];
        }
        else
        {
            const holo::geometry::LineSegment2d ls(first_point, second_point);
            const holo::geometry::Point2d       projected_pos_2d = ls.Project(target);
            project_point                                        = projected_pos_2d;
        }
    }

    if (second_id < first_id)
    {
        std::swap(first_id, second_id);
    }

    return true;
}

template <typename T>
struct ResultDistToLine_In
{
    /// left idx of projected point
    std::size_t first_id = 0U;
    /// right idx of projected point
    std::size_t second_id = 0U;
    /// projected point on target line
    T project_point;
    /// distance to target line
    float64_t min_distance = 0.0;
    /// whether target out of range of line or not
    bool is_outside = false;
};

template <typename T>
static bool CalculateDistanceToPoints2D(const T& pos_target, const std::vector<T>& points,
                                        ResultDistToLine_In<T>& result, const bool local_check = false,
                                        const std::size_t start_idx = 0U, const std::size_t check_num = 5) noexcept
{
    return CalculateDistanceToPoints2D<T>(pos_target, points, result.first_id, result.second_id, result.project_point,
                                          result.min_distance, result.is_outside, local_check, start_idx, check_num);
}

template <typename T>
static bool JointPointsAtEnd2D(const std::vector<T>& src, std::vector<T>& des) noexcept
{
    if (des.empty())
    {
        des = src;
        return true;
    }
    des.reserve(src.size() + des.size());

    if (src.empty())
    {
        return true;
    }

    const std::size_t des_count = des.size();
    const std::size_t src_count = src.size();
    if (1 == des_count && 1 == src_count)
    {
        if (!AreSamePointsIn2D(des.front(), src.front()))
        {
            des.push_back(src.front());
        }
        return true;
    }

    if (1 == des_count)
    {
        ResultDistToLine_In<T> result;
        if (!CalculateDistanceToPoints2D(des.front(), src, result))
        {
            LOG(ERROR) << "JointPointsAtEnd2D fail, CalculateDistanceToPoints2D fail,"
                       << " target=" << FormatPoint(des.front()) << " points_size=" << src.size();
            return false;
        }

        if (result.is_outside)
        {
            if (0 == result.first_id && src_count - 1 == result.second_id)
            {
                const float64_t dist_first  = des.front().Dist(src.front());
                const float64_t dist_second = des.front().Dist(src.back());
                if (dist_first < dist_second)
                {
                    (void)des.insert(des.cend(), src.cbegin(), src.cend());
                }
                else
                {
                    return true;
                }
            }

            if (0 == result.first_id && src_count - 1 != result.second_id)
            {
                (void)des.insert(des.cend(), src.cbegin(), src.cend());
            }

            if (0 != result.first_id && src_count - 1 == result.second_id)
            {
                return true;
            }
        }
        else
        {
            const std::size_t index =
                AreSamePointsIn2D(des.front(), src[result.second_id]) ? result.second_id + 1 : result.second_id;
            (void)des.insert(des.cend(), src.cbegin() + index, src.cend());
        }
        return true;
    }

    for (std::size_t i = 0U; i < src_count; ++i)
    {
        ResultDistToLine_In<T> result;
        const bool             ok = CalculateDistanceToPoints2D(src[i], des, result, false, des_count - 2);
        if (!ok)
        {
            LOG(ERROR) << "JointPointsAtEnd2D fail, CalculateDistanceToPoints2D fail,"
                       << " target=" << FormatPoint(src[i]) << " points=" << FormatPoints(des);
            return false;
        }
        if (result.is_outside && des_count - 1 == result.second_id)
        {
            const std::size_t index = AreSamePointsIn2D(des[result.second_id], src[i]) ? i + 1 : i;
            (void)des.insert(des.cend(), src.cbegin() + index, src.cend());
            break;
        }
    }

    return true;
}

static holo::geometry::Point3d CalculateMiddlePoint3D(const holo::geometry::Point3d& first,
                                                      const holo::geometry::Point3d& second) noexcept
{
    return holo::geometry::Point3d((first.GetX() + second.GetX()) * 0.5, (first.GetY() + second.GetY()) * 0.5,
                                   (first.GetZ() + second.GetZ()) * 0.5);
}

typedef struct rotue_line_t
{
    typedef struct segment_t
    {
        const LinkInfo*     link_info;
        const LaneInfo*     lane_info;
        const LaneMarkInfo* mark_info;
    } Segment;

    typedef std::vector<Segment> SegmentArray;

    SegmentArray segments;
} RouteLine;

typedef std::vector<RouteLine> RouteLineArray;

static bool FindClosestLane(const LinkInfo& link, const std::vector<KeyValue>& lane_ids,
                            const RouteLineArray& left_old_lines, const RouteLineArray& right_old_lines,
                            KeyValue& lane_id) noexcept
{
    lane_id = 0U;
    if (lane_ids.empty())
    {
        LOG(ERROR) << "FindClosestLane fail, none of lane in next array, link_id=" << link.GetID();
        return false;
    }

    const std::size_t count = lane_ids.size();
    if (1 == count)
    {
        lane_id = lane_ids.front();
        return true;
    }

    if (left_old_lines.empty() || left_old_lines.back().segments.empty() ||
        left_old_lines.back().segments.back().mark_info == nullptr ||
        left_old_lines.back().segments.back().mark_info->GetRefPoints().empty())
    {
        LOG(ERROR) << "FindClosestLane fail, invalid param: left_old_correlator,"
                   << " link_id=" << link.GetID();
        return false;
    }

    if (right_old_lines.empty() || right_old_lines.back().segments.empty() ||
        right_old_lines.back().segments.back().mark_info == nullptr ||
        right_old_lines.back().segments.back().mark_info->GetRefPoints().empty())
    {
        LOG(ERROR) << "FindClosestLane fail, invalid param: right_old_correlator,"
                   << " link_id=" << link.GetID();
        return false;
    }

    const holo::geometry::Point3d& left_point = left_old_lines.back().segments.back().mark_info->GetRefPoints().back();
    const holo::geometry::Point3d& right_point =
        right_old_lines.back().segments.back().mark_info->GetRefPoints().back();

    const holo::geometry::Point3d middle_point = CalculateMiddlePoint3D(left_point, right_point);

    const std::vector<LaneInfo>& lanes = link.GetLaneInfos();
    if (lanes.empty())
    {
        LOG(ERROR) << "FindClosestLane fail, none of lane in link_id=" << link.GetID();
        return false;
    }

    float64_t min_distance = std::numeric_limits<float64_t>::max();
    for (const LaneInfo& lane : lanes)
    {
        const KeyValue id = lane.GetId();
        const auto     it = std::find(lane_ids.cbegin(), lane_ids.cend(), id);
        if (lane_ids.cend() == it)
        {
            continue;
        }

        const std::vector<holo::geometry::Point3d>& left_points  = lane.GetLeftMark().GetRefPoints();
        const std::vector<holo::geometry::Point3d>& right_points = lane.GetRightMark().GetRefPoints();

        if (left_points.empty() || right_points.empty())
        {
            LOG(ERROR) << "FindClosestLane fail, none of point in mark, link_id=" << link.GetID() << " lane_id=" << id
                       << " left_mark_count=" << left_points.size() << " right_mark_count=" << right_points.size();
            return false;
        }

        const float64_t dist =
            CalculateDistanceFromPointToLineSegment2D(middle_point, left_points.front(), right_points.front());
        if (dist < min_distance)
        {
            min_distance = dist;
            lane_id      = id;
        }
    }

    if (0 == lane_id)
    {
        LOG(ERROR) << "FindClosestLane fail, can't find lane_ids=" << FormatIDs(lane_ids)
                   << " in link_id=" << link.GetID();
        return false;
    }
    return true;
}

static bool JoinClosestRouteLine(const LinkInfo& link, const LaneInfo& lane, const bool is_left,
                                 const RouteLineArray& old_lines, RouteLineArray& new_lines) noexcept
{
    const LaneMarkInfo* mark = is_left ? &lane.GetLeftMark() : &lane.GetRightMark();
    if (mark->GetRefPoints().empty())
    {
        new_lines.shrink_to_fit();
        LOG(ERROR) << "JoinClosestRouteLine fail, none of point in mark,"
                   << " is_left=" << is_left << " link_id=" << link.GetID() << " lane_id=" << lane.GetId();
        return false;
    }

    bool              found = false;
    const KeyValue    id    = lane.GetId();
    const std::size_t count = old_lines.size();

    for (std::size_t i = 0U; i < count; ++i)
    {
        const RouteLine::Segment&    s   = old_lines[i].segments.back();
        const std::vector<KeyValue>& ids = s.lane_info->GetSuccLaneIds();
        const auto                   it  = std::find(ids.cbegin(), ids.cend(), id);
        if (ids.cend() == it)
        {
            continue;
        }

        RouteLine line;
        line.segments.reserve(old_lines[i].segments.size() + 1);
        (void)line.segments.insert(line.segments.end(), old_lines[i].segments.cbegin(), old_lines[i].segments.cend());
        line.segments.emplace_back(RouteLine::Segment{&link, &lane, mark});
        new_lines.emplace_back(std::move(line));
        found = true;
    }

    if (!found)
    {
        new_lines.emplace_back(RouteLine{RouteLine::SegmentArray{RouteLine::Segment{&link, &lane, mark}}});
    }

    return true;
}

static bool JoinLeftOrRightRouteLine(const LinkInfo& link, const std::vector<const LaneInfo*>& lanes,
                                     const std::size_t middle, const bool is_left, const RouteLineArray& old_lines,
                                     RouteLineArray& new_lines) noexcept
{
    const std::size_t count = lanes.size();
    const std::size_t start = is_left ? 0 : middle;
    const std::size_t end   = is_left ? middle + 1 : count;

    RouteLineArray lines;
    lines.reserve(count);

    for (std::size_t i = start; i < end; ++i)
    {
        const LaneInfo& lane = is_left ? *lanes[end - i - 1] : *lanes[i];
        const bool      ok   = JoinClosestRouteLine(link, lane, is_left, old_lines, lines);
        if (!ok)
        {
            LOG(ERROR) << "JoinLeftOrRightRouteLine fail, JoinClosestRouteLine fail,"
                       << " id=" << lane.GetId() << " is_left=" << is_left << " start=" << start << " end=" << end
                       << " count=" << count << " index=" << i;
            return false;
        }
    }

    const std::size_t count1 = old_lines.size();
    const std::size_t count2 = lines.size();
    new_lines.reserve(count1 + count2);

    std::size_t i = 0U;
    std::size_t j = 0U;
    while (i < count1 || j < count2)
    {
        if (i < count1 && j < count2)
        {
            const RouteLine& line1 = old_lines[i];
            if (line1.segments.empty() || nullptr == line1.segments.back().lane_info)
            {
                LOG(ERROR) << "JoinLeftOrRightRouteLine fail, invalid old_lines";
                return false;
            }

            const RouteLine& line2 = lines[j];
            if (line2.segments.empty() || nullptr == line2.segments.back().lane_info)
            {
                LOG(ERROR) << "JoinLeftOrRightRouteLine fail, invalid new_lines";
                return false;
            }

            const KeyValue               id         = line1.segments.back().lane_info->GetId();
            const std::vector<KeyValue>& precedings = line2.segments.back().lane_info->GetPreLaneIds();
            const auto                   it         = std::find(precedings.cbegin(), precedings.cend(), id);
            if (precedings.cend() != it)
            {
                new_lines.emplace_back(std::move(lines[j]));
                ++j;
            }
            else
            {
                new_lines.emplace_back(std::move(old_lines[i]));
            }
            ++i;
            continue;
        }

        while (i < count1)
        {
            new_lines.emplace_back(std::move(old_lines[i]));
            ++i;
        }

        while (j < count2)
        {
            new_lines.emplace_back(std::move(lines[j]));
            ++j;
        }
    }

    return true;
}

static bool JoinRouteLineByLanes(const LinkInfo& link, const std::vector<KeyValue>& target_lane_ids,
                                 const RouteLineArray& left_old_lines, const RouteLineArray& right_old_lines,
                                 RouteLineArray& left_new_lines, RouteLineArray& right_new_lines,
                                 std::vector<KeyValue>& next_lane_ids) noexcept
{
    next_lane_ids.clear();
    left_new_lines.shrink_to_fit();
    right_new_lines.shrink_to_fit();

    const KeyValue               link_id = link.GetID();
    const std::vector<LaneInfo>& lanes   = link.GetLaneInfos();
    if (lanes.empty())
    {
        LOG(ERROR) << "JoinRouteLineByLanes fail, none of lane in link_id=" << link_id;
        return false;
    }

    KeyValue lane_id = 0U;
    if (!FindClosestLane(link, target_lane_ids, left_old_lines, right_old_lines, lane_id))
    {
        LOG(ERROR) << "JoinRouteLineByLanes fail, FindClosestLane fail, link_id=" << link.GetID()
                   << " lane_ids=" << FormatIDs(target_lane_ids);
        return false;
    }

    const std::size_t            count = lanes.size();
    std::vector<const LaneInfo*> ptrs;
    ptrs.reserve(count);

    for (std::size_t i = 0U; i < count; ++i)
    {
        ptrs.push_back(&lanes[i]);
    }

    std::sort(ptrs.begin(), ptrs.end(), [](const LaneInfo* lane1, const LaneInfo* lane2) -> bool {
        return static_cast<int8_t>(lane1->GetSeq()) < static_cast<int8_t>(lane2->GetSeq());
    });

    std::size_t middle = std::numeric_limits<std::size_t>::max();
    for (std::size_t i = 0U; i < count; ++i)
    {
        if (ptrs[i]->GetId() == lane_id)
        {
            middle        = i;
            next_lane_ids = ptrs[i]->GetSuccLaneIds();
        }
    }

    if (std::numeric_limits<std::size_t>::max() == middle)
    {
        LOG(ERROR) << "JoinRouteLineByLanes fail, can't find target lane_id=" << lane_id << " in link_id=" << link_id;
        return false;
    }

    if (JoinLeftOrRightRouteLine(link, ptrs, middle, true, left_old_lines, left_new_lines))
    {
        return JoinLeftOrRightRouteLine(link, ptrs, middle, false, right_old_lines, right_new_lines);
    }
    else
    {
        LOG(ERROR) << "JoinRouteLineByLanes fail, JoinLeftOrRightRouteLine fail,"
                   << " link_id=" << link_id << " middle=" << middle << " lane_size=" << count;
        return false;
    }
}

static bool JoinRouteLineByLinks(const std::vector<LinkInfo>& links, const int8_t seq, RouteLineArray& left,
                                 RouteLineArray& right) noexcept
{
    left.clear();
    right.clear();
    if (links.empty())
    {
        LOG(ERROR) << "JoinRouteLineByLinks fail, none of link in array";
        return false;
    }

    RouteLineArray left_new;
    RouteLineArray right_new;

    std::vector<KeyValue> succeeds;
    for (const LinkInfo& link : links)
    {
        if (succeeds.empty())
        {
            const std::vector<LaneInfo>& lanes = link.GetLaneInfos();
            for (const LaneInfo& lane : lanes)
            {
                if (static_cast<int8_t>(lane.GetSeq()) == seq)
                {
                    succeeds.push_back(lane.GetId());
                    break;
                }
            }
        }

        if (succeeds.empty())
        {
            LOG(ERROR) << "JoinRouteLineByLinks fail, none of lane in succeeds,"
                       << " link_id=" << link.GetID() << " seq=" << seq;
            return false;
        }

        std::vector<KeyValue> nexts;
        if (!JoinRouteLineByLanes(link, succeeds, left, right, left_new, right_new, nexts))
        {
            LOG(ERROR) << "JoinRouteLineByLinks fail, JoinRouteLineByLanes fail,"
                       << " link_id=" << link.GetID() << " succeeds=" << FormatIDs(succeeds);
            return false;
        }

        succeeds.swap(nexts);

        left_new.swap(left);
        right_new.swap(right);
        left_new.clear();
        right_new.clear();
    }

    return true;
}

static bool JoinRouteLineByLinksV2(const std::vector<LinkInfo>& links, const KeyValue link_id, const KeyValue lane_id,
                                   RouteLineArray& left, RouteLineArray& right) noexcept
{
    left.clear();
    right.clear();
    if (links.empty())
    {
        LOG(ERROR) << "JoinRouteLineByLinksV2 fail, none of link in array";
        return false;
    }

    RouteLineArray left_new;
    RouteLineArray right_new;

    bool ready = false;

    std::vector<KeyValue> succeeds;
    for (const LinkInfo& link : links)
    {
        if (!ready)
        {
            if (link.GetID() != link_id)
            {
                continue;
            }
            ready = true;
        }

        if (succeeds.empty())
        {
            const std::vector<LaneInfo>& lanes = link.GetLaneInfos();
            for (const LaneInfo& lane : lanes)
            {
                if (lane.GetId() == lane_id)
                {
                    succeeds.push_back(lane.GetId());
                    break;
                }
            }
        }

        if (succeeds.empty())
        {
            LOG(ERROR) << "JoinRouteLineByLinksV2 fail, none of lane in succeeds,"
                       << " link_id=" << link.GetID() << " target_link_id=" << link_id << " target_lane_id=" << lane_id;
            return false;
        }

        std::vector<KeyValue> nexts;
        if (!JoinRouteLineByLanes(link, succeeds, left, right, left_new, right_new, nexts))
        {
            LOG(ERROR) << "JoinRouteLineByLinksV2 fail, JoinRouteLineByLanes fail,"
                       << " link_id=" << link.GetID() << " succeeds=" << FormatIDs(succeeds);
            return false;
        }

        succeeds.swap(nexts);

        left_new.swap(left);
        right_new.swap(right);
        left_new.clear();
        right_new.clear();
    }

    if (left.empty() && right.empty())
    {
        LOG(ERROR) << "JoinRouteLineByLinksV2 fail, can't find target link in array,"
                   << " links_size=" << links.size() << " links_first_id=" << links.front().GetID()
                   << " link_last_id=" << links.back().GetID() << " target_link_id=" << link_id
                   << " target_lane_id=" << lane_id;
        return false;
    }
    return true;
}

static bool MergeRouteLine(const RouteLineArray&                              routelines,
                           std::vector<std::vector<holo::geometry::Point3d>>& new_lines) noexcept
{
    if (routelines.empty())
    {
        LOG(ERROR) << "MergeRouteLine fail, none of route line in array";
        return false;
    }

    const std::size_t count = routelines.size();
    new_lines.clear();
    new_lines.reserve(count);

    for (std::size_t i = 0U; i < count; ++i)
    {
        const RouteLine& route = routelines[i];
        if (route.segments.empty())
        {
            LOG(ERROR) << "MergeRouteLine fail, none of segment in route_line=" << i;
            return false;
        }

        std::vector<holo::geometry::Point3d> points;

        const std::size_t size = route.segments.size();
        for (std::size_t j = 0U; j < size; ++j)
        {
            const RouteLine::Segment s = route.segments[j];
            if (NULL == s.link_info || NULL == s.lane_info || NULL == s.mark_info)
            {
                LOG(ERROR) << "MergeRouteLine fail, invalid segment, route_line=" << i << " segment=" << j;
                return false;
            }

            const std::vector<holo::geometry::Point3d>& mark_points = s.mark_info->GetRefPoints();
            if (mark_points.empty())
            {
                LOG(ERROR) << "MergeRouteLine fail, none of point in lane_mark,"
                           << " lane_id=" << s.lane_info->GetId() << " link_id=" << s.link_info->GetID() << " i=" << i
                           << " j=" << j;
                return false;
            }

            if (!JointPointsAtEnd2D(mark_points, points))
            {
                LOG(ERROR) << "GetCurrentRouteLine fail, JointPointsAtEnd2D fail,"
                           << " link_id=" << s.link_info->GetID() << " lane_id=" << s.lane_info->GetId()
                           << " source_size=" << mark_points.size() << " destination_size=" << points.size();
                return false;
            }
        }

        new_lines.emplace_back(std::move(points));
    }

    if (new_lines.empty())
    {
        LOG(ERROR) << "MergeRouteLine fail, none of point in route line,"
                   << " route_line_size=" << count;
    }

    return !new_lines.empty();
}

bool CurrentRouteInfo::GetCurrentRouteLine(const CurrentRouteInfo& info, const SeqValue lane_seq,
                                           ::std::vector<::std::vector<::holo::geometry::Point3d>>& left_route_lines,
                                           ::std::vector<::std::vector<::holo::geometry::Point3d>>& right_route_lines,
                                           const ::holo::float32_t distance, const bool forward)
{
    (void)distance;
    left_route_lines.clear();
    right_route_lines.clear();

    if (!forward)
    {
        LOG(ERROR) << "GetCurrentRouteLine fail, not support forward=" << forward;
        return false;
    }

    const std::vector<LinkInfo>& links = forward ? info.GetLinks() : info.GetRearLinks();
    if (links.empty())
    {
        LOG(ERROR) << "GetCurrentRouteLine fail, none of link in current route";
        return false;
    }

    LOG(INFO) << "GetCurrentRouteLine start, link_count=" << links.size() << " front_link_id=" << links.front().GetID();

    RouteLineArray temp_left_route_lines;
    RouteLineArray temp_right_route_lines;
    if (!JoinRouteLineByLinks(links, lane_seq, temp_left_route_lines, temp_right_route_lines))
    {
        LOG(ERROR) << "GetCurrentRouteLine fail, JoinRouteLineByLinks fail,"
                   << " link_count=" << links.size() << " lane_seq=" << lane_seq;
        return false;
    }

    if (!MergeRouteLine(temp_left_route_lines, left_route_lines))
    {
        LOG(ERROR) << "GetCurrentRouteLine fail, MergeRouteLine fail,"
                   << " left_route_lines_count=" << left_route_lines.size();
        return false;
    }

    if (!MergeRouteLine(temp_right_route_lines, right_route_lines))
    {
        LOG(ERROR) << "GetCurrentRouteLine fail, MergeRouteLine fail,"
                   << " right_route_lines_count=" << right_route_lines.size();
        return false;
    }

    if (left_route_lines.empty() && right_route_lines.empty())
    {
        LOG(ERROR) << "GetCurrentRouteLine fail, with empty result,"
                   << " link_size=" << info.GetLinks().size() << " rear_size=" << info.GetRearLinks().size()
                   << " left_route_line_array=" << left_route_lines.size()
                   << " right_route_line_array=" << right_route_lines.size();
    }

    return !left_route_lines.empty() || !right_route_lines.empty();
}

bool CurrentRouteInfo::GetCurrentRouteLineV2(CurrentRouteInfo const& info, KeyValue const link_id,
                                             KeyValue const                                           lane_id,
                                             ::std::vector<::std::vector<::holo::geometry::Point3d>>& left_route_lines,
                                             ::std::vector<::std::vector<::holo::geometry::Point3d>>& right_route_lines,
                                             bool const                                               forward)
{
    left_route_lines.clear();
    right_route_lines.clear();

    if (!forward)
    {
        LOG(ERROR) << "GetCurrentRouteLineV2 fail, not support forward=" << forward;
        return false;
    }

    const std::vector<LinkInfo>& links = forward ? info.GetLinks() : info.GetRearLinks();
    if (links.empty())
    {
        LOG(ERROR) << "GetCurrentRouteLineV2 fail, none of link in current route";
        return false;
    }

    LOG(INFO) << "GetCurrentRouteLineV2 start, link_count=" << links.size()
              << " front_link_id=" << links.front().GetID();

    RouteLineArray temp_left_route_lines;
    RouteLineArray temp_right_route_lines;
    if (!JoinRouteLineByLinksV2(links, link_id, lane_id, temp_left_route_lines, temp_right_route_lines))
    {
        LOG(ERROR) << "GetCurrentRouteLineV2 fail, JoinRouteLineByLinksV2 fail,"
                   << " link_count=" << links.size() << " target_link_id=" << link_id << " target_lane_id=" << lane_id;
        return false;
    }

    if (!MergeRouteLine(temp_left_route_lines, left_route_lines))
    {
        LOG(ERROR) << "GetCurrentRouteLineV2 fail, MergeRouteLine fail,"
                   << " left_route_lines_count=" << left_route_lines.size();
        return false;
    }

    if (!MergeRouteLine(temp_right_route_lines, right_route_lines))
    {
        LOG(ERROR) << "GetCurrentRouteLineV2 fail, MergeRouteLine fail,"
                   << " right_route_lines_count=" << right_route_lines.size();
        return false;
    }

    if (left_route_lines.empty() && right_route_lines.empty())
    {
        LOG(ERROR) << "GetCurrentRouteLineV2 fail, with empty result,"
                   << " link_size=" << info.GetLinks().size() << " rear_size=" << info.GetRearLinks().size()
                   << " left_route_line_array=" << left_route_lines.size()
                   << " right_route_line_array=" << right_route_lines.size();
    }

    return !left_route_lines.empty() || !right_route_lines.empty();
}

}  // namespace map
}  // namespace holo
