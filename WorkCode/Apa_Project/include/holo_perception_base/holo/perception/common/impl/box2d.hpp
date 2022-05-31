/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box2.hpp
 * @brief This src file implements the api of box2d.h.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-15"
 */

#ifndef HOLO_PERCEPTION_COMMON_BOX2D_HPP_
#define HOLO_PERCEPTION_COMMON_BOX2D_HPP_

#include <holo/perception/common/box2d.h>

namespace holo
{
namespace perception
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box2DT<T>::Box2DT(Point2Type const& left_up_point, Point2Type const& right_bottom_point)
{
    T width  = right_bottom_point.GetX() - left_up_point.GetX();
    T height = right_bottom_point.GetY() - left_up_point.GetY();
    if (width <= static_cast<Scalar>(0.0) || height <= static_cast<Scalar>(0.0))
    {
        throw std::out_of_range("the second point should be in lower right corner of the first point");
    }
    x_        = left_up_point.GetX();
    y_        = left_up_point.GetY();
    width_    = width;
    height_   = height;
    rotation_ = static_cast<T>(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box2DT<T>& Box2DT<T>::operator=(Box2Type const& box) noexcept
{
    x_        = box.x_;
    y_        = box.y_;
    width_    = box.width_;
    height_   = box.height_;
    rotation_ = box.rotation_;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
bool_t Box2DT<T>::operator==(Box2Type const& box) const noexcept
{
    Scalar err_x = std::abs(x_ - box.GetX());
    Scalar err_y = std::abs(y_ - box.GetY());
    Scalar err_w = std::abs(width_ - box.GetWidth());
    Scalar err_h = std::abs(height_ - box.GetHeight());
    Scalar err_r = std::abs(rotation_ - box.GetRotation());
    return (err_x <= tol && err_y <= tol && err_w <= tol && err_h <= tol && err_r <= tol);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
holo::geometry::details::Point2T<T> const Box2DT<T>::GetCenterPoint() const noexcept
{
    Scalar tr_x = x_ + width_ * std::cos(rotation_);
    Scalar tr_y = y_ + width_ * std::sin(rotation_);
    Scalar bl_x = x_ - height_ * std::sin(rotation_);
    Scalar bl_y = y_ + height_ * std::cos(rotation_);

    Scalar center_p_x = (tr_x + bl_x) * static_cast<Scalar>(0.5);
    Scalar center_p_y = (tr_y + bl_y) * static_cast<Scalar>(0.5);
    return Point2Type(center_p_x, center_p_y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box2DT<T> const Box2DT<T>::GetIntersectionBox(Box2Type const& box) const
{
    if (std::abs(rotation_ - box.GetRotation()) > tol)
    {
        throw std::range_error("only support boxes' rotations are same now!");
    }

    /**
     *     w o---------------------------> x
     *       |          box1
     *       |   T1 o**********----------> x1
     *       |      *         *  box2
     *       |      *  T2 o---*----------> x2
     *       |      *     |   *   |
     *       |      ***********   |
     *       |      |     |_______|
     *       |      |     |
     *     y v   y1 v  y1 v
     */

    // step1: get the top left coordinates in the "world" frame
    Point2Type tl1_w = Point2Type(this->GetX(), this->GetY());
    Point2Type tl2_w = Point2Type(box.GetX(), box.GetY());

    // step2: transform T2 box's tl and br points to T1 box's frame
    Pose2Type  Tw1(rotation_, tl1_w);
    Pose2Type  Tw2(box.GetRotation(), tl2_w);
    Pose2Type  T12 = Tw1.Inverse() * Tw2;
    Point2Type tl1_T1(static_cast<Scalar>(0), static_cast<Scalar>(0));
    Point2Type br1_T1(width_, height_);
    Point2Type tl2_T2(static_cast<Scalar>(0.0), static_cast<Scalar>(0.0));
    Point2Type br2_T2(box.GetWidth(), box.GetHeight());
    Point2Type tl2_T1 = T12 * tl2_T2;
    Point2Type br2_T1 = T12 * br2_T2;

    // step3: compute the intersection box in T1 frame
    Scalar pt1_x_T1 = std::max(tl1_T1.GetX(), tl2_T1.GetX());
    Scalar pt1_y_T1 = std::max(tl1_T1.GetY(), tl2_T1.GetY());
    Scalar pt2_x_T1 = std::min(br1_T1.GetX(), br2_T1.GetX());
    Scalar pt2_y_T1 = std::min(br1_T1.GetY(), br2_T1.GetY());
    Scalar width    = pt2_x_T1 - pt1_x_T1;
    Scalar height   = pt2_y_T1 - pt1_y_T1;

    if (width <= static_cast<Scalar>(0.0) || height <= static_cast<Scalar>(0.0))
    {
        return Box2Type();
    }

    // step4: transform inter_box's top left point from T1 frame to "world" frame
    Point2Type pt1 = Tw1 * Point2Type(pt1_x_T1, pt1_y_T1);
    return Box2Type(pt1.GetX(), pt1.GetY(), width, height, rotation_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
Box2DT<T> const Box2DT<T>::GetMinConvexBox(Box2Type const& box) const
{
    if (std::abs(rotation_ - box.GetRotation()) > tol)
    {
        throw std::range_error("only support boxes' rotations are same now!");
    }

    // step1: get the top left coordinates in the "world" frame
    Point2Type tl1_w = Point2Type(this->GetX(), this->GetY());
    Point2Type tl2_w = Point2Type(box.GetX(), box.GetY());

    // step2: transform T2 box's tl and br points to T1 box's frame
    Pose2Type  Tw1(rotation_, tl1_w);
    Pose2Type  Tw2(box.GetRotation(), tl2_w);
    Pose2Type  T12 = Tw1.Inverse() * Tw2;
    Point2Type tl1_T1(static_cast<Scalar>(0), static_cast<Scalar>(0));
    Point2Type br1_T1(width_, height_);
    Point2Type tl2_T2(static_cast<Scalar>(0.0), static_cast<Scalar>(0.0));
    Point2Type br2_T2(box.GetWidth(), box.GetHeight());
    Point2Type tl2_T1 = T12 * tl2_T2;
    Point2Type br2_T1 = T12 * br2_T2;

    // step3: compute the min convex box in T1 frame
    Scalar pt1_x_T1 = std::min(tl1_T1.GetX(), tl2_T1.GetX());
    Scalar pt1_y_T1 = std::min(tl1_T1.GetY(), tl2_T1.GetY());
    Scalar pt2_x_T1 = std::max(br1_T1.GetX(), br2_T1.GetX());
    Scalar pt2_y_T1 = std::max(br1_T1.GetY(), br2_T1.GetY());
    Scalar width    = pt2_x_T1 - pt1_x_T1;
    Scalar height   = pt2_y_T1 - pt1_y_T1;

    // step4: transform convex_box's top left point from T1 frame to "world" frame
    Point2Type pt1 = Tw1 * Point2Type(pt1_x_T1, pt1_y_T1);
    return Box2Type(pt1.GetX(), pt1.GetY(), width, height, rotation_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T Box2DT<T>::GetIntersectionArea(Box2Type const& box) const
{
    return this->GetIntersectionBox(box).GetArea();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T Box2DT<T>::GetUnionArea(Box2Type const& box) const
{
    return this->GetArea() + box.GetArea() - this->GetIntersectionArea(box);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
T Box2DT<T>::ComputeIoU(Box2Type const& box2_in) const
{
    return this->GetIntersectionArea(box2_in) / this->GetUnionArea(box2_in);
}

template <typename T>
T Box2DT<T>::ComputeGIoU(Box2Type const& box2_in) const
{
    Scalar inter_area = this->GetIntersectionArea(box2_in);
    Scalar Ac         = this->GetMinConvexBox(box2_in).GetArea();
    Scalar unionS     = this->GetUnionArea(box2_in);
    Scalar iou        = inter_area / unionS;
    return iou - (Ac - unionS) / Ac;
}

template <typename T>
bool_t Box2DT<T>::IsValid() const noexcept
{
    if (std::isnan(x_) || std::isnan(y_) || std::isnan(width_) || std::isnan(height_) || std::isnan(rotation_) ||
        width_ <= tol || height_ <= tol)
    {
        return false;
    }
    return true;
}

template <typename T>
void Box2DT<T>::ConvertToBaseBox2(BaseBox2Type& box2_out) const noexcept
{
    box2_out = BaseBox2Type(width_, height_, Pose2Type(Rot2Type(rotation_), Point2Type(x_, y_)));
}

template <typename T>
void Box2DT<T>::ConvertFromBaseBox2(BaseBox2Type const& box2_in) noexcept
{
    Pose2Type pose = box2_in.GetPose();
    this->SetX(pose.GetX());
    this->SetY(pose.GetY());
    this->SetWidth(box2_in.GetWidth());
    this->SetHeight(box2_in.GetHeight());
    this->SetRotation(pose.GetRotation().GetTheta());
}

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_BOX2D_HPP_
