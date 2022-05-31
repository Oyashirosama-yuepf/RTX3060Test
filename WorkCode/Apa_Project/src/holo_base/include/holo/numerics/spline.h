/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline.h
 * @brief holo spline class
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-12-06
 */

#ifndef HOLO_NUMERICS_SPLINE_H_
#define HOLO_NUMERICS_SPLINE_H_

#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
/**
 * @addtogroup numerics
 * @{
 *
 */

/**
 * @brief spline fitting
 *
 * @tparam T dimension of spline, e.g. 2 or 3
 */
template <int32_t DIM>
class SplineT
{
public:
    /**
     * @brief typedefs
     *
     */
    using Scalar      = holo::float64_t;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;
    using VectorXType = holo::numerics::VectorXT<Scalar>;

    /**
     * @brief smart pointer wrapper
     *
     */
    using Ptr      = std::shared_ptr<SplineT>;
    using ConstPtr = std::shared_ptr<const SplineT>;

    /**
     * @brief Construct a new Spline object
     *
     * @param data data to be fitted, each row in matrix corresponds to one sample
     * @param degree degree
     * @param knots spline knots
     */
    SplineT(const MatrixXType& data, const uint8_t degree, const VectorXType& knots);

    /**
     * @brief brief destructor
     *
     */
    ~SplineT() noexcept;

    /**
     * @brief interpolate data at specific position
     *
     * @param t input position
     * @note Exception safety
     *
     * @return interpolated data
     */
    VectorXType Interpolate(const Scalar t) const;

    /**
     * @brief get derivatives at specific position
     *
     * @details each column correpsonds to one order, starts from 0
     * @param t input position
     * @param order derivative order
     * @note Exception safety
     *
     * @return interpolated data
     */
    MatrixXType Derivatives(const Scalar t, const uint8_t order) const;

    /**
     * @brief return left boundary of knots
     *
     * @return left boundary
     */
    Scalar GetBoundaryMin() const noexcept
    {
        return boundary_min_;
    }

    /**
     * @brief return right boundary of knots
     *
     * @return right boundary
     */
    Scalar GetBoundaryMax() const noexcept
    {
        return boundary_max_;
    }

protected:
    /**
     * @brief boundary
     *
     */
    Scalar boundary_min_;
    Scalar boundary_max_;

    /**
     * @brief pointer of implementation
     *
     */
    class Implementation;
    std::unique_ptr<Implementation> impl_;

};  // class Spline

/**
 * @brief handy typedefs
 *
 */
using Spline2 = SplineT<2>;
using Spline3 = SplineT<3>;

/**
 * @}
 *
 */

}  // namespace holo

#endif  // HOLO_NUMERICS_SPLINE_H_
