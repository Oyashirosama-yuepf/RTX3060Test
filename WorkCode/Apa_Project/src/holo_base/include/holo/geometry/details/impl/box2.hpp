/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box2.hpp
 * @brief box in 2D space
 * @author duyanwei@holomatic.com
 * @date Sep-25-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_BOX2_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_BOX2_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Box2T<T>::Box2T() noexcept : Box2T(Point2Type::Zero(), Point2Type::One())
{
}

template <typename T>
Box2T<T>::Box2T(Point2Type const& p1, Point2Type const& p2)
  : Box2T((p1.GetX() >= p2.GetX()) ? (p1.GetX() - p2.GetX()) : (p2.GetX() - p1.GetX()),
          (p1.GetY() >= p2.GetY()) ? (p1.GetY() - p2.GetY()) : (p2.GetY() - p1.GetY()),
          Pose2Type(Rot2Type(), Point2Type(std::min(p1.GetX(), p2.GetX()), std::min(p1.GetY(), p2.GetY()))))
{
}

template <typename T>
Box2T<T>::Box2T(Point2Type const& center, ScalarType const width, ScalarType const height, ScalarType const theta)
  : Box2T(width, height,
          Pose2Type(Rot2Type(theta), Point2Type(center.GetX() - (width * std::cos(theta) - height * std::sin(theta)) /
                                                                    static_cast<ScalarType>(2.0),
                                                center.GetY() - (height * std::cos(theta) + width * std::sin(theta)) /
                                                                    static_cast<ScalarType>(2.0))))
{
}

template <typename T>
Box2T<T>::Box2T(ScalarType const width, ScalarType const height, const Pose2Type& pose)
  : width_(width), height_(height), pose_(pose)
{
    assert(IsValid());
}

template <typename T>
Box2T<T>::Box2T(Box2T const& box) noexcept : width_(box.width_), height_(box.height_), pose_(box.pose_)
{
}

template <typename T>
Box2T<T>::~Box2T() noexcept
{
}

template <typename T>
Box2T<T>& Box2T<T>::operator=(Box2T const& box) noexcept
{
    width_  = box.width_;
    height_ = box.height_;
    pose_   = box.pose_;

    return *this;
}

template <typename T>
bool_t Box2T<T>::operator==(Box2T const& box) const noexcept
{
    return IsEqual(box);
}

template <typename T>
bool_t Box2T<T>::Contains(Point2Type const& pt, ScalarType const tol) const noexcept
{
    Point2Type q = pose_.TransformTo(pt);
    return (q.GetX() >= -tol && q.GetX() <= width_ + tol && q.GetY() >= -tol && q.GetY() <= height_ + tol);
}

template <typename T>
bool_t Box2T<T>::Contains(LineSegment2Type const& ls, ScalarType const tol) const noexcept
{
    return Contains(ls.GetStartPoint(), tol) && Contains(ls.GetEndPoint(), tol);
}

template <typename T>
bool_t Box2T<T>::IsEqual(Box2T const& box, ScalarType const tol) const noexcept
{
    ScalarType err_w = (width_ > box.GetWidth()) ? (width_ - box.GetWidth()) : (box.GetWidth() - width_);

    ScalarType err_h = (height_ > box.GetHeight()) ? (height_ - box.GetHeight()) : (box.GetHeight() - height_);

    return (err_w <= tol && err_h <= tol && pose_.IsEqual(box.GetPose(), tol));
}

template <typename T>
bool_t Box2T<T>::IsValid() const noexcept
{
    return (width_ > ScalarEqualT<T>().GetEpsilonValue()) && (height_ > ScalarEqualT<T>().GetEpsilonValue()) &&
           (pose_.IsValid());
}

template <typename T>
uint8_t Box2T<T>::Intersect(LineSegment2Type const& ls, Point2Type& pt1, Point2Type& pt2) const noexcept
{
    // get four boundaries of a box
    LineSegment2Type lss[4u] = {LineSegment2Type(), LineSegment2Type(), LineSegment2Type(), LineSegment2Type()};

    GetEdges(lss[0u], lss[1u], lss[2u], lss[3u]);

    // find the intersections of line segment with four boundaries
    Point2Type pt;
    uint8_t    num = 0u;
    for (uint8_t i = 0u; i < 4u; i++)
    {
        if (ls.Intersect(lss[i], pt))
        {
            if (num == 0u)
            {
                // first point
                pt1 = pt;
                num++;
            }
            else if (num > 0u)
            {
                // second point
                if (!pt1.IsEqual(pt))
                {
                    pt2 = pt;
                    num++;
                    break;
                }
            }
        }
    }
    return num;
}

template <typename T>
void Box2T<T>::GetCornerPoints(Point2Type& bl, Point2Type& br, Point2Type& tr, Point2Type& tl) const noexcept
{
    // bottom left
    bl = pose_.TransformFrom(Point2Type::Zero());

    // bottom right
    br = pose_.TransformFrom(Point2Type(GetWidth(), static_cast<ScalarType>(0.0)));

    // top right
    tr = pose_.TransformFrom(Point2Type(GetWidth(), GetHeight()));

    // top left
    tl = pose_.TransformFrom(Point2Type(static_cast<ScalarType>(0.0), GetHeight()));
}

template <typename T>
void Box2T<T>::GetEdges(LineSegment2Type& bottom, LineSegment2Type& right, LineSegment2Type& top,
                        LineSegment2Type& left) const noexcept
{
    Point2Type pt1, pt2, pt3, pt4;
    GetCornerPoints(pt1, pt2, pt3, pt4);

    // bottom line segment
    bottom = LineSegment2Type(pt1, pt2);

    // right line segment
    right = LineSegment2Type(pt2, pt3);

    // top line segment
    top = LineSegment2Type(pt3, pt4);

    // left line segment
    left = LineSegment2Type(pt4, pt1);
}

template <typename T>
void Box2T<T>::GetAxisAlignedExternalBox(Point2Type& min_pt, Point2Type& max_pt) const noexcept
{
    // extract four corners
    Point2Type corners[4u];
    GetCornerPoints(corners[0u], corners[1u], corners[2u], corners[3u]);

    // loop over each corner to get the minimum and maximum value
    ScalarType min_x = corners[0u].GetX(), min_y = corners[0u].GetY();
    ScalarType max_x = min_x, max_y = min_y;

    for (uint8_t i = 1u; i < 4u; i++)
    {
        ScalarType const x = corners[i].GetX();
        ScalarType const y = corners[i].GetY();
        if (min_x > x)
        {
            min_x = x;
        }

        if (min_y > y)
        {
            min_y = y;
        }

        if (max_x < x)
        {
            max_x = x;
        }

        if (max_y < y)
        {
            max_y = y;
        }
    }

    // set the maximum and minimum point
    max_pt.Set(max_x, max_y);
    min_pt.Set(min_x, min_y);
}

template <typename T>
typename Box2T<T>::ScalarType Box2T<T>::ComputeIntersectionOverUnion(Box2T const& box) const noexcept
{
    // @note In current version we only compute the IOU of two boxes with
    //        identity rotation
    // @date Aug-24-2017
    if (pose_.GetTheta() != static_cast<ScalarType>(0.0) || box.GetPose().GetTheta() != static_cast<ScalarType>(0.0))
    {
        return static_cast<ScalarType>(0.0);
    }

    // axis-aligned coordinates
    Point2Type min_pt1, max_pt1, min_pt2, max_pt2;
    GetAxisAlignedExternalBox(min_pt1, max_pt1);
    box.GetAxisAlignedExternalBox(min_pt2, max_pt2);

    // compute corner points of intersection box
    Point2Type pt1(std::max(min_pt1.GetX(), min_pt2.GetX()), std::max(min_pt1.GetY(), min_pt2.GetY()));
    Point2Type pt2(std::min(max_pt1.GetX(), max_pt2.GetX()), std::min(max_pt1.GetY(), max_pt2.GetY()));

    // compute width and height of intersection box
    ScalarType width  = pt2.GetX() - pt1.GetX();
    ScalarType height = pt2.GetY() - pt1.GetY();

    // no intersection
    if (width <= ScalarEqualT<T>().GetEpsilonValue() || height <= ScalarEqualT<T>().GetEpsilonValue())
    {
        return static_cast<ScalarType>(0.0);
    }

    // compute area of intersection box
    ScalarType area = width * height;

    // compute ratio
    ScalarType ratio = area / (GetArea() + box.GetArea() - area);
    return ratio;
}

template <typename T>
void Box2T<T>::SetWidth(ScalarType const width) noexcept
{
    assert(width > static_cast<ScalarType>(0.0));
    width_ = width;
}

template <typename T>
void Box2T<T>::SetHeight(ScalarType const height) noexcept
{
    assert(height > static_cast<ScalarType>(0.0));
    height_ = height;
}

template <typename T>
void Box2T<T>::SetPose(const Pose2Type& pose) noexcept
{
    assert(pose.IsValid());
    pose_ = pose;
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_BOX2_HPP_
