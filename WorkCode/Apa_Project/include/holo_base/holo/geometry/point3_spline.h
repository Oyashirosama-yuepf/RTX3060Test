/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point3_spline.h
 * @brief holo spline class
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-09-28
 */

#ifndef HOLO_GEOMETRY_POINT3_SPLINE_H_
#define HOLO_GEOMETRY_POINT3_SPLINE_H_

#include <holo/geometry/point3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
/**
 * @addtogroup geometry
 * @{
 *
 */

/**
 * @brief spline fitting of point
 *
 */
class Point3Spline
{
public:
    /**
     * @brief typedefs
     *
     */
    using Scalar      = holo::float64_t;
    using Point3Type  = holo::geometry::Point3T<Scalar>;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;
    using Vector3Type = holo::numerics::Vector3T<Scalar>;

    /**
     * @brief smart pointer wrapper
     *
     */
    using Ptr      = std::shared_ptr<Point3Spline>;
    using ConstPtr = std::shared_ptr<const Point3Spline>;

    /**
     * @brief Construct a new Point 3 Spline object
     *
     * @param data data to be fitted, each element pair in vector is a data sample (knot + point)
     * @param offset data offset, if unset, no offset will be used
     */
    Point3Spline(const std::vector<std::pair<Scalar, Point3Type> >& data,
                 const Point3Type&                                  offset = Point3Type::Zero());

    /**
     * @brief Construct a new Point 3 Spline object
     *
     * @param data data to be fitted, each element pair in vector is a data sample (knot + point)
     * @param offset data offset
     * @param lambda smoothing factor
     */
    Point3Spline(const std::vector<std::pair<Scalar, Point3Type> >& data, const Point3Type& offset,
                 const Scalar lambda);

    /**
     * @brief brief destructor
     *
     */
    ~Point3Spline() noexcept;

    /**
     * @brief interpolate point at specific position
     *
     * @param t input position
     * @param local the offset is considered when local is false, otherwise not
     * @throws throw exception if out of boundary
     * @note Exception safety
     *
     * @return point3
     */
    Point3Type Interpolate(const Scalar t, const bool_t local = true) const;

    /**
     * @brief interpolate point at specific position
     *
     * @param t input position
     * @param local the offset is considered when local is false, otherwise not
     * @throws throw exception if out of boundary
     * @note Exception safety
     *
     * @return point3
     */
    Point3Type operator()(const Scalar t, const bool_t local = true) const;

    /**
     * @brief return timestamp of left boundary
     *
     * @return
     */
    inline Scalar GetBoundaryMin() const noexcept
    {
        return boundary_min_;
    }

    /**
     * @brief return timestamp of the right boundary
     *
     * @return
     */
    inline Scalar GetBoundaryMax() const noexcept
    {
        return boundary_max_;
    }

    /**
     * @brief return offset of spline
     *
     * @return offset
     */
    inline const Point3Type& GetOffset() const noexcept
    {
        return offset_;
    }

protected:
    /**
     * @brief degree, default 3
     *
     */
    const uint32_t degree_ = 3u;

    /**
     * @brief offset for point spline
     */
    const Point3Type offset_;

    /**
     * @brief boundary
     *
     */
    Scalar boundary_min_;
    Scalar boundary_max_;

    /**
     * @brief pointer of implemenation
     *
     */
    class Implementation;
    std::unique_ptr<Implementation> impl_;

};  // class Point3Spline

/**
 * @}
 *
 */

}  // namespace holo

#endif  // HOLO_GEOMETRY_POINT3_SPLINE_H_
