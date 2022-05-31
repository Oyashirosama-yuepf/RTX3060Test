/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box2d.h
 * @brief This header file defines box2 used for perception in Deep Learning.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-15"
 */

#ifndef HOLO_PERCEPTION_COMMON_BOX2D_H_
#define HOLO_PERCEPTION_COMMON_BOX2D_H_

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/pose2.h>
#include <holo/geometry/rot2.h>
#include <iomanip>

namespace holo
{
namespace perception
{
/**
 * @addtogroup common
 *
 * @{
 */

/**
 * @brief define box2d
 *
 * @note the width of box is aligned with x-axis(u-axis) and
 *       height is aligned with y-axis(v-axis) in box local frame
 *       O----------------> x(u)
 *       | (x,y)
 *       |   *******
 *       |   *     * h
 *       |   *******
 *       |     w
 *   y(v)v
 * @tparam T data type
 */
template <typename T>
class Box2DT
{
public:
    using Scalar       = T;
    using Box2Type     = Box2DT<Scalar>;
    using BaseBox2Type = holo::geometry::Box2T<Scalar>;
    using Rot2Type     = holo::geometry::Rot2T<Scalar>;
    using Point2Type   = holo::geometry::Point2T<Scalar>;
    using Pose2Type    = holo::geometry::Pose2T<Scalar>;
    Scalar const tol   = holo::EpsilonT<Scalar>::value;

    /**
     * @brief Default Constructor
     *
     */
    Box2DT() noexcept
      : x_(static_cast<Scalar>(0.0))
      , y_(static_cast<Scalar>(0.0))
      , width_(static_cast<Scalar>(0.0))
      , height_(static_cast<Scalar>(0.0))
      , rotation_(static_cast<Scalar>(0.0))
    {
    }

    /**
     * @brief Construct a new Box2D
     *
     * @param x
     * @param y
     * @param width, box width
     * @param height, box height
     * @param rotation, yaw in radian, positive when rotates from axis_x to axis_y
     * @throw std::out_of_range, if width or height is negative
     */
    Box2DT(Scalar x, Scalar y, Scalar width, Scalar height, Scalar rotation = static_cast<Scalar>(0.0))
      : x_(x), y_(y), width_(width), height_(height), rotation_(rotation)
    {
        if (width_ < static_cast<Scalar>(0.0) || height_ < static_cast<Scalar>(0.0))
        {
            throw std::out_of_range("width and height should be greater than 0");
        }
    }

    /**
     * @brief Construct a new Box2D object with left up point and right bottom point
     *
     * @param left_up_point
     * @param right_bottom_point
     * @throw std::out_of_range, if right_bottom_point isn't in lower right corner of left_up_point
     */
    Box2DT(Point2Type const& left_up_point, Point2Type const& right_bottom_point);

    /**
     * @brief Destructor
     *
     */
    ~Box2DT()
    {
    }

    /**
     * @brief assignment operator
     *
     * @param box
     * @return Box2Type&
     */
    Box2Type& operator=(Box2Type const& box) noexcept;

    /**
     * @brief operator ==, check if two boxes are equal
     *
     * @param box
     * @return bool_t, true is same, false is different
     */
    bool_t operator==(Box2Type const& box) const noexcept;

    /**
     * @brief Get the center point of the box
     *
     * @return Point2Type
     */
    Point2Type const GetCenterPoint() const noexcept;

    /**
     * @brief get the intersection box of two boxes
     *
     * @param box
     * @return Box2Type, the intersection box
     * @note only compute the intersection of two boxes with identify rotation now
     * @throw std::range_error throw, if the two boxes' roatation are different
     */
    Box2Type const GetIntersectionBox(Box2Type const& box) const;

    /**
     * @brief get the min convex box that encloses two boxes
     *
     * @param box
     * @return Box2Type
     * @note only compute the min convex box of two boxes with identify rotation now
     * @throw std::range_error throw, if the two boxes' roatation are different
     */
    Box2Type const GetMinConvexBox(Box2Type const& box) const;

    /**
     * @brief get the intersection area with another box
     *
     * @param box, another box
     * @return Scalar
     * @note you can customize this function when the two boxes' rotations are different
     */
    virtual Scalar GetIntersectionArea(Box2Type const& box) const;

    /**
     * @brief get the union area with another box
     *
     * @param box, another box
     * @return Scalar
     * @note you can customize this function when the two boxes' rotations are different
     */
    virtual Scalar GetUnionArea(Box2Type const& box) const;

    /**
     * @brief Set the left top point x
     *
     * @param x
     */
    void SetX(Scalar const x) noexcept
    {
        x_ = x;
    }

    /**
     * @brief Set the left top point y
     *
     * @param y
     */
    void SetY(Scalar const y) noexcept
    {
        y_ = y;
    }

    /**
     * @brief Set the width of the Box2D
     *
     * @param width, should be a non-negative value
     * @throw std::out of range throw, if width is negative
     */
    void SetWidth(Scalar const width)
    {
        if (width < static_cast<Scalar>(0.0))
        {
            throw std::out_of_range("width should be greater than 0");
        }
        width_ = width;
    }

    /**
     * @brief Set the height of the Box2D
     *
     * @param height, should be a non-negative value
     * @throw std::out of range throw, if height is negative
     */
    void SetHeight(Scalar const height)
    {
        if (height < static_cast<Scalar>(0.0))
        {
            throw std::out_of_range("width should be greater than 0");
        }
        height_ = height;
    }

    /**
     * @brief Set the rotation of the Box2D
     *
     * @param rotation, yaw in radian
     */
    void SetRotation(Scalar const rotation) noexcept
    {
        rotation_ = rotation;
    }

    /**
     * @brief Get the x of top left point
     *
     * @return Scalar
     */
    Scalar GetX() const noexcept
    {
        return x_;
    }

    /**
     * @brief Get the y of top left point
     *
     * @return Scalar
     */
    Scalar GetY() const noexcept
    {
        return y_;
    }

    /**
     * @brief Get the width of the Box2D
     *
     * @return Scalar
     */
    Scalar GetWidth() const noexcept
    {
        return width_;
    }

    /**
     * @brief Get the height of the Box2D
     *
     * @return Scalar
     */
    Scalar GetHeight() const noexcept
    {
        return height_;
    }

    /**
     * @brief Get the rotation of the Box2D
     *
     * @return Scalar, yaw in radian
     */
    Scalar GetRotation() const noexcept
    {
        return rotation_;
    }

    /**
     * @brief Get the area of the Box2D
     *
     * @return Scalar
     */
    Scalar GetArea() const noexcept
    {
        return width_ * height_;
    }

    /**
     * @brief Compute intersection over union between two boxes, IoU = (A ∩ B) / (A ∪ B)
     *
     * @param box2_in, another box2
     * @return Scalar, overlap ratio, a non-negative value
     * @throw std::range_error throw, if the two boxes' roatations are different. You can also
     * customize the GetIntersectionArea and GetUnionArea for more general case
     */
    Scalar ComputeIoU(Box2Type const& box2_in) const;

    /**
     * @brief Compute generalized intersection over union between two boxes
     *
     * @param box2_in, another box2
     * @return Scalar, general overlap ratio
     * @ref https://giou.stanford.edu/
     * @note this function may return a negative value
     * @throw std::range_error throw, if the two boxes' roatations are different
     */
    Scalar ComputeGIoU(Box2Type const& box2_in) const;

    /**
     * @brief Check whether is box2D is valid.
     * @note valid box's width and height should be greater than zero
     * @return bool_t, true for valid, false for invalid.
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief Convert the Box2D type to Box2 in holo_base.
     *
     * @param box2_out, type is holo_base/Box2
     */
    void ConvertToBaseBox2(BaseBox2Type& box2_out) const noexcept;

    /**
     * @brief Convert holo_base/Box2 to Box2D
     *
     * @param box2_in, type is holo_base/Box2
     */
    void ConvertFromBaseBox2(BaseBox2Type const& box2_in) noexcept;

    /**
     * @brief output stream
     *
     * @param os std::ostream
     * @param in  box2D
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, Box2Type const& in)
    {
        os << in.ToString();
        return os;
    }

    /**
     * @brief Convert to string for readable
     *
     * @return std::string
     */
    virtual std::string ToString() const
    {
        std::stringstream ss;
        ss << "Box2d: x = " << std::setiosflags(std::ios_base::fixed) << std::setprecision(2) << x_ << ", y = " << y_
           << ", width = " << width_ << ", height = " << height_ << ", rotation = " << rotation_ << std::endl;
        return ss.str();
    }

private:
    Scalar x_;
    Scalar y_;
    Scalar width_;     ///< width of Box2D, should be a non-negative value
    Scalar height_;    ///< heigth of Box2D, should be a non-negative value
    Scalar rotation_;  ///< yaw of Box2D, in radian
};

/**
 * @brief handy typedefs
 *
 */
using Box2Df = Box2DT<float32_t>;
using Box2Dd = Box2DT<float64_t>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_BOX2D_H_
