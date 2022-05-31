/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file box3d.h
 * @brief This header file defines box3d used for perception.
 * @author lanshayun(lanshayun@holomatic.com)
 * @date "2020-09-16"
 */

#ifndef HOLO_PERCEPTION_COMMON_BOX3D_H_
#define HOLO_PERCEPTION_COMMON_BOX3D_H_

#include <holo/core/epsilon.h>
#include <holo/core/types.h>
#include <holo/geometry/box3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/rot3.h>

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
 * @brief define box3d
 *
 * @tparam T data type, only support float32_t and float64_t now
 * @ref https://wiki.holomatic.cn/pages/viewpage.action?pageId=56765408
 * @note in right-handed coordinate frame
 *
 *        top-down view              front-view                   side-view
 *                  x                         z                   z
 *                  ^                         ^                   ^
 *          y_dim   |                  y_dim  |                   |   x_dim
 *         *******  |                 ******* |                   |  *******
 *   x_dim *  o  *  | depth     z_dim *  o  * | height     height |  *  o  * z_dim
 *         *******  |                 ******* |                   |  *******
 *   y <------------O         y <-------------O                   O------------->x
 *        width                       width                          depth
 *
 */
template <typename T>
class Box3DT
{
public:
    using Scalar       = T;
    using Box3Type     = Box3DT<Scalar>;
    using BaseBox3Type = holo::geometry::Box3T<Scalar>;
    using Rot3Type     = holo::geometry::Rot3T<Scalar>;
    using Pose3Type    = holo::geometry::Pose3T<Scalar>;
    using Point3Type   = holo::geometry::Point3T<Scalar>;
    using Vector3Type  = holo::numerics::Vector3T<Scalar>;
    Scalar const tol   = holo::EpsilonT<Scalar>::value;

    /**
     * @brief Default constructor
     *
     */
    Box3DT() noexcept
      : center_point_(Point3Type::Zero())
      , x_dim_(static_cast<Scalar>(0.0))
      , y_dim_(static_cast<Scalar>(0.0))
      , z_dim_(static_cast<Scalar>(0.0))
      , rx_(static_cast<Scalar>(0.0))
      , ry_(static_cast<Scalar>(0.0))
      , rz_(static_cast<Scalar>(0.0))
    {
    }

    /**
     * @brief Construct a new Box3D with params
     *
     * @param center_point, center point of the box3d
     * @param x_dim, box's dimension aligns x axis
     * @param y_dim, box's dimension aligns y axis
     * @param z_dim, box's dimension aligns z axis
     * @param rx, rotate around x axis, in radian
     * @param ry, rotate around y axis, in radian
     * @param rz, rotate around z axis, in radian
     * @throw std::range_error throw, if x_dim or y_dim or z_dim is negative
     */
    Box3DT(Point3Type const& center_point, Scalar x_dim, Scalar y_dim, Scalar z_dim,
           Scalar rx = static_cast<Scalar>(0.0), Scalar ry = static_cast<Scalar>(0.0),
           Scalar rz = static_cast<Scalar>(0.0));

    /**
     * @brief Construct a new Box3DT with params
     *
     * @param x, x value of center point
     * @param y, y value of center point
     * @param z, z value of center point
     * @param x_dim, box's dimension aligns x axis
     * @param y_dim, box's dimension aligns y axis
     * @param z_dim, box's dimension aligns z axis
     * @param rx, rotate around x axis, in radian
     * @param ry, rotate around y axis, in radian
     * @param rz, rotate around z axis, in radian
     */
    Box3DT(Scalar x, Scalar y, Scalar z, Scalar x_dim, Scalar y_dim, Scalar z_dim, Scalar rx = static_cast<Scalar>(0.0),
           Scalar ry = static_cast<Scalar>(0.0), Scalar rz = static_cast<Scalar>(0.0)) noexcept;

    /**
     * @brief Copy constructor
     *
     * @param box3, another box3d object
     */
    Box3DT(Box3Type const& box3) noexcept;

    /**
     * @brief deconstructor
     *
     */
    ~Box3DT() noexcept
    {
    }

    /**
     * @brief assignment operator
     *
     * @param box3, another box3d object
     * @return Box3Type&
     */
    Box3Type& operator=(Box3Type const& box3) noexcept;

    /**
     * @brief equal operator
     *
     * @param box3, another box3d object
     * @return bool_t, true for same, false for different
     */
    bool_t operator==(Box3Type const& box3) const noexcept;

    /**
     * @brief Set the center point for box3d
     *
     * @param center_point, [x, y, z]
     */
    void SetCenterPoint(Point3Type const& center_point) noexcept
    {
        center_point_ = center_point;
    }

    /**
     * @brief Set box's dimension aligns x axis
     *
     * @param x_dim, dimension on x axis, should be greater than 0
     * @throw std::range_error throw if x_dim is negative
     */
    void SetXDim(Scalar x_dim)
    {
        if (x_dim < static_cast<Scalar>(0.0))
        {
            throw std::range_error("x_dim should be a non-negative value!");
        }
        x_dim_ = x_dim;
    }

    /**
     * @brief Set box's dimension aligns y axis
     *
     * @param y_dim, dimension on y axis, should be greater than 0
     * @throw std::range_error throw if y_dim is negative
     */
    void SetYDim(Scalar y_dim)
    {
        if (y_dim < static_cast<Scalar>(0.0))
        {
            throw std::range_error("y_dim should be a non-negative value!");
        }
        y_dim_ = y_dim;
    }

    /**
     * @brief Set box's dimension aligns z axis
     *
     * @param z_dimension, dimension on z axis, should be greater than 0
     * @throw std::range_error throw if z_dim is negative
     */
    void SetZDim(Scalar z_dim)
    {
        if (z_dim < static_cast<Scalar>(0.0))
        {
            throw std::range_error("z_dim should be a non-negative value!");
        }
        z_dim_ = z_dim;
    }

    /**
     * @brief Set the Rx of the box3
     *
     * @param rx, rotate around x axis, in radian
     */
    void SetRx(Scalar rx) noexcept
    {
        rx_ = rx;
    }

    /**
     * @brief Set the Ry of the box3
     *
     * @param ry, rotate around y axis, in radian
     */
    void SetRy(Scalar ry) noexcept
    {
        ry_ = ry;
    }

    /**
     * @brief Set the Rz of the box3
     *
     * @param rz, rotate around z axis, in radian
     */
    void SetRz(Scalar rz) noexcept
    {
        rz_ = rz;
    }

    /**
     * @brief Get the center point
     *
     * @return Point3Type const&
     */
    Point3Type const& GetCenterPoint() const noexcept
    {
        return center_point_;
    }

    /**
     * @brief Get box's dimension on x axis
     *
     * @return Scalar
     */
    Scalar GetXDim() const noexcept
    {
        return x_dim_;
    }

    /**
     * @brief Get box's dimension on y axis
     *
     * @return Scalar
     */
    Scalar GetYDim() const noexcept
    {
        return y_dim_;
    }

    /**
     * @brief Get box's dimension on z axis
     *
     * @return Scalar
     */
    Scalar GetZDim() const noexcept
    {
        return z_dim_;
    }

    /**
     * @brief Get the rx
     *
     * @return Scalar, rx in radian
     */
    Scalar GetRx() const noexcept
    {
        return rx_;
    }

    /**
     * @brief Get the ry
     *
     * @return Scalar, ry in radian
     */
    Scalar GetRy() const noexcept
    {
        return ry_;
    }

    /**
     * @brief Get the rz
     *
     * @return Scalar, rz in radian
     */
    Scalar GetRz() const noexcept
    {
        return rz_;
    }

    /**
     * @brief Get the volume of the box
     *
     * @return Scalar
     */
    Scalar GetVolume() const noexcept
    {
        return x_dim_ * y_dim_ * z_dim_;
    }

    /**
     * @brief Check whether the Box3D is valid.
     *
     * @return bool_t, true for valid, false for invalid.
     * @note valid box3d's dims should all be greater than zero
     */
    bool_t IsValid() const noexcept;

    /**
     * @brief Convert the Box3D type to holo_base/Box3
     *
     * @param box3_out, type is holo_base/Box3
     * @note you need transform the box3 to body frame (right-handed coordinate) before ConvertToBaseBox3
     * @details BaseBox3 ==> Box3D:
     *          1.transform the center point to the origin;
     *          2.rotate the box to the target orientation;
     *          3.translate the box to the target position.
     */
    void ConvertToBaseBox3(BaseBox3Type& box3_out) const noexcept;

    /**
     * @brief Convert holo_base/Box3 to Box3D
     *
     * @param box3_in, type is holo_base/Box3
     */
    void ConvertFromBaseBox3(BaseBox3Type const& box3_in) noexcept;

    friend std::ostream& operator<<(std::ostream& os, Box3Type const& in)
    {
        os << in.ToString();
        return os;
    }

    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Box3d: center_p " << center_point_.ToString() << ", x_dim = " << x_dim_ << ", y_dim = " << y_dim_
           << ", z_dim = " << z_dim_ << ", rx = " << rx_ << ", ry = " << ry_ << ", rz = " << rz_ << std::endl;
        return ss.str();
    }

private:
    Point3Type center_point_;
    Scalar     x_dim_;
    Scalar     y_dim_;
    Scalar     z_dim_;
    Scalar     rx_;  ///< rotates around x-axis, in radian
    Scalar     ry_;  ///< rotates around y-axis, in radian
    Scalar     rz_;  ///< rotates around z-axis, in radian
};

/**
 * @brief handy typedefs
 *
 */
using Box3Df = Box3DT<float32_t>;
using Box3Dd = Box3DT<float64_t>;

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_COMMON_BOX3D_H_
