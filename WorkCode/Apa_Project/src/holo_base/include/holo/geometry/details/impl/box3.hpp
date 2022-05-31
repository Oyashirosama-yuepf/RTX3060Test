/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box3.hpp
 * @brief the template implementation of a box in 3d.
 * @author jiaxing.zhao
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date Sep-27-2020
 */

#ifndef HOLO_GEOMETRY_DETAILS_IMPL_BOX3_HPP_
#define HOLO_GEOMETRY_DETAILS_IMPL_BOX3_HPP_

namespace holo
{
namespace geometry
{
namespace details
{
template <typename T>
Box3T<T>::Box3T() noexcept : Box3T(Point3Type::Zero(), Point3Type::One())
{
}

template <typename T>
Box3T<T>::Box3T(Point3Type const& p1, Point3Type const& p2)
  : Box3T((p1.GetY() >= p2.GetY() ? (p1.GetY() - p2.GetY()) : (p2.GetY() - p1.GetY())),
          (p1.GetZ() >= p2.GetZ() ? (p1.GetZ() - p2.GetZ()) : (p2.GetZ() - p1.GetZ())),
          (p1.GetX() >= p2.GetX() ? (p1.GetX() - p2.GetX()) : (p2.GetX() - p1.GetX())),
          Pose3Type(Rot3Type(), Point3Type(std::min(p1.GetX(), p2.GetX()), std::min(p1.GetY(), p2.GetY()),
                                           std::min(p1.GetZ(), p2.GetZ()))))
{
}

template <typename T>
Box3T<T>::Box3T(Vector3Type const& dim, Pose3Type const& pose) : Box3T(dim(0u), dim(1u), dim(2u), pose)
{
}

template <typename T>
Box3T<T>::Box3T(ScalarType const width, ScalarType const height, ScalarType const depth, Pose3Type const& pose)
  : width_(width), height_(height), depth_(depth), pose_(pose)
{
    assert(IsValid());
}

template <typename T>
Box3T<T>::Box3T(ScalarType const width, ScalarType const height, ScalarType const depth, Point3Type const& center,
                ScalarType const roll, ScalarType const pitch, ScalarType const yaw)
  : width_(width), height_(height), depth_(depth)
{
    const Rot3T<T>   R = Rot3T<T>::RzRyRx(roll, pitch, yaw);
    const Point3T<T> t =
        center - R * Point3T<T>(static_cast<T>(depth / 2.0), static_cast<T>(width / 2.0), static_cast<T>(height / 2.0));
    pose_.SetRotation(R);
    pose_.SetTranslation(t);

    assert(IsValid());
}

template <typename T>
Box3T<T>::Box3T(Box3T const& other) noexcept
  : width_(other.width_), height_(other.height_), depth_(other.depth_), pose_(other.pose_)
{
}

template <typename T>
Box3T<T>::~Box3T() noexcept
{
}

template <typename T>
Box3T<T>& Box3T<T>::operator=(Box3T const& other) noexcept
{
    width_  = other.width_;
    height_ = other.height_;
    depth_  = other.depth_;
    pose_   = other.pose_;

    return *this;
}

template <typename T>
bool_t Box3T<T>::operator==(Box3T const& other) const noexcept
{
    return IsEqual(other);
}

template <typename T>
bool Box3T<T>::Contains(Point3Type const& pt, ScalarType const tol) const noexcept
{
    const Point3Type q = pose_.TransformTo(pt);
    return (q.GetX() >= -tol && q.GetX() <= depth_ + tol && q.GetY() >= -tol && q.GetY() <= width_ + tol &&
            q.GetZ() >= -tol && q.GetZ() <= height_ + tol);
}

template <typename T>
bool_t Box3T<T>::IsEqual(Box3T const& other, ScalarType const tol) const noexcept
{
    ScalarType err_w = (width_ > other.GetWidth()) ? (width_ - other.GetWidth()) : (other.GetWidth() - width_);

    ScalarType err_h = (height_ > other.GetHeight()) ? (height_ - other.GetHeight()) : (other.GetHeight() - height_);

    ScalarType err_d = (depth_ > other.GetDepth()) ? (depth_ - other.GetDepth()) : (other.GetDepth() - depth_);

    return (err_w <= tol && err_h <= tol && err_d <= tol && pose_.IsEqual(other.GetPose(), tol));
}

template <typename T>
bool_t Box3T<T>::IsValid() const noexcept
{
    return (width_ >= ScalarEqualT<T>().GetEpsilonValue()) && (height_ >= ScalarEqualT<T>().GetEpsilonValue()) &&
           (depth_ >= ScalarEqualT<T>().GetEpsilonValue()) && (pose_.IsValid());
}

template <typename T>
void Box3T<T>::GetAxisAlignedExternalBox(Point3Type& min_pt, Point3Type& max_pt) const noexcept
{
    const std::vector<Point3Type> corners = GetCornerPoints();

    ScalarType minx = std::numeric_limits<ScalarType>::max();
    ScalarType miny = std::numeric_limits<ScalarType>::max();
    ScalarType minz = std::numeric_limits<ScalarType>::max();
    ScalarType maxx = std::numeric_limits<ScalarType>::min();
    ScalarType maxy = std::numeric_limits<ScalarType>::min();
    ScalarType maxz = std::numeric_limits<ScalarType>::min();

    for (uint8_t i = 0u; i < corners.size(); ++i)
    {
        Point3Type const& q = corners[i];
        ScalarType const  x = q.GetX();
        ScalarType const  y = q.GetY();
        ScalarType const  z = q.GetZ();

        if (x < minx)
        {
            minx = x;
        }

        if (x > maxx)
        {
            maxx = x;
        }

        if (y < miny)
        {
            miny = y;
        }

        if (y > maxy)
        {
            maxy = y;
        }

        if (z < minz)
        {
            minz = z;
        }

        if (z > maxz)
        {
            maxz = z;
        }
    }

    // setup output
    min_pt.Set(minx, miny, minz);
    max_pt.Set(maxx, maxy, maxz);
}

template <typename T>
std::vector<typename Box3T<T>::Point3Type> Box3T<T>::GetCornerPoints() const noexcept
{
    /**
     * @brief corner points in order
     *     {xmin, ymin, zmin}
     *     {xmax, ymin, zmin}
     *     {xmax, ymax, zmin}
     *     {xmin, ymax, zmin}
     *     {xmin, ymax, zmax}
     *     {xmin, ymin, zmax}
     *     {xmax, ymin, zmax}
     *     {xmax, ymax, zmax}
     */
    Point3Type corners[8u] = {Point3Type::Zero(),
                              Point3Type(depth_, static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0)),
                              Point3Type(depth_, width_, static_cast<ScalarType>(0.0)),
                              Point3Type(static_cast<ScalarType>(0.0), width_, static_cast<ScalarType>(0.0)),
                              Point3Type(static_cast<ScalarType>(0.0), width_, height_),
                              Point3Type(static_cast<ScalarType>(0.0), static_cast<ScalarType>(0.0), height_),
                              Point3Type(depth_, static_cast<ScalarType>(0.0), height_),
                              Point3Type(depth_, width_, height_)};

    std::vector<Point3Type> points;
    points.reserve(8u);
    for (uint8_t i = 0u; i < 8u; ++i)
    {
        points.emplace_back(pose_.TransformFrom(corners[i]));
    }
    return points;
}

template <typename T>
typename Box3T<T>::Point3Type Box3T<T>::GetCenter() const noexcept
{
    return pose_.TransformFrom(Point3Type(depth_ / static_cast<ScalarType>(2.0), width_ / static_cast<ScalarType>(2.0),
                                          height_ / static_cast<ScalarType>(2.0)));
}

}  // namespace details
}  // namespace geometry
}  // namespace holo

#endif  // HOLO_GEOMETRY_DETAILS_IMPL_BOX3_HPP_
