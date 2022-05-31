/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_fitting.h
 * @brief spline_fitting class
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date April 08, 2020
 */

#ifndef HOLO_LOCALIZATION_TOOLS_SPLINE_FITTING_H_
#define HOLO_LOCALIZATION_TOOLS_SPLINE_FITTING_H_

#include <holo/log/hololog.h>
#include <holo/numerics/bspline.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace localization
{
/**
 * @brief define spline fitting class
 *
 */
template <size_t Dimension, size_t Degree = 3u, bool_t Uniform = false>
class SplineFittingT
  : public numerics::BSpline<float64_t, holo::numerics::VectorT<float64_t, Dimension>, Degree, Uniform>
{
public:
    using Base = numerics::BSpline<float64_t, holo::numerics::VectorT<float64_t, Dimension>, Degree, Uniform>;

    using Base::DegreeValue;
    using Base::OrderValue;
    static uint32_t const DimensionValue = Dimension;

    using typename Base::PointType;
    using typename Base::ScalarType;

    using BasisVectorType = holo::numerics::VectorT<float64_t, Base::OrderValue>;
    using typename Base::BasisMatrixType;
    using MatrixXd = holo::numerics::MatrixXT<float64_t>;
    using VectorXd = holo::numerics::VectorXT<float64_t>;

    /**
     * @brief Construct a new SplineFittingT object
     *
     * @param times times
     * @param data data
     * @param lambda smoothing coefficient when computing control points
     * @param num_of_time_segments num_of_time_segments to average the times range
     * @throw std::out_of_range exception if the size of times and data are not the same
     */
    SplineFittingT(const std::vector<float64_t>& times, const std::vector<PointType>& data, float64_t lambda = 0.0,
                   uint32_t num_of_time_segments = 0u);

    /**
     * @brief Destroy the SplineFittingT object
     *
     */
    virtual ~SplineFittingT() noexcept;

private:
    /**
     * @brief init spline
     *
     * @param times
     * @param data
     * @param lambda
     * @param num_of_time_segments
     */
    void initialize(const std::vector<float64_t>& times, const std::vector<PointType>& data, const float64_t lambda,
                    const uint32_t num_of_time_segments);

    /**
     * @brief compute knots
     *
     * @param times
     * @param num_of_time_segments
     * @return std::vector<float64_t>
     */
    std::vector<float64_t> computeKnots(const std::vector<float64_t>& times, const uint32_t num_of_time_segments) const;

    /**
     * @brief average knots
     *
     * @param times
     * @param num_of_time_segments
     * @return std::vector<float64_t>
     */
    std::vector<float64_t> averageKnots(const std::vector<float64_t>& times, const uint32_t num_of_time_segments) const;

    /**
     * @brief Get the Knots Number object
     *
     * @param num_of_time_segments
     * @return uint32_t
     */
    uint32_t getKnotsNumber(const uint32_t num_of_time_segments) const;

    /**
     * @brief Get the Control Points Number object
     *
     * @param num_of_time_segments
     * @return uint32_t
     */
    uint32_t getControlPointsNumber(const uint32_t num_of_time_segments) const;

    /**
     * @brief compute control points
     *
     * @param times
     * @param data
     * @param lambda
     * @return std::vector<PointType>
     */
    std::vector<PointType> computeControlPointsSparse(const std::vector<float64_t>& times,
                                                      const std::vector<PointType>& data, const float64_t lambda) const;

    /**
     * @brief compute control points start index
     *
     * @param t
     * @return uint32_t
     */
    uint32_t computeControlPointStartIndex(const float64_t t) const;

    /**
     * @brief compute jacobian
     *
     * @param t
     * @return MatrixXd
     */
    MatrixXd computeJacobian(const float64_t t) const;

    /**
     * @brief segment quadratic integral
     *
     * @param W
     * @param index
     * @param derivative_order
     * @return MatrixXd
     */
    MatrixXd segmentQuadraticIntegral(const MatrixXd& W, const uint32_t index, const uint32_t derivative_order) const;

    /**
     * @brief compute Dii
     *
     * @param index
     * @return MatrixXd
     */
    MatrixXd computeDii(const uint32_t index) const;

    /**
     * @brief compute Vi
     *
     * @param index
     * @return MatrixXd
     */
    MatrixXd computeVi(const uint32_t index) const;

    /**
     * @brief compute Mi
     *
     * @param index
     * @return MatrixXd
     */
    MatrixXd computeMi(const uint32_t index) const;

    /**
     * @brief compute Bij
     *
     * @param index
     * @param col
     * @return MatrixXd
     */
    MatrixXd computeBij(const uint32_t index, const uint32_t col) const;

    /**
     * @brief Get the Time Interval object
     *
     * @param index
     * @return std::pair<float64_t, float64_t>
     */
    std::pair<float64_t, float64_t> getTimeInterval(const uint32_t index) const;

};  // class SplineFittingT

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TOOLS_SPLINE_FITTING_H_
