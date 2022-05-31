/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_fitting.hpp
 * @brief spline fitting class implementation
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date April 08, 2020
 */

#include <numeric>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>
#include <Eigen/Sparse>

#include <holo/localization/tools/spline_fitting.h>

namespace holo
{
namespace localization
{
namespace spline_internal
{
using EigenMatrixXd     = Eigen::Matrix<float64_t, Eigen::Dynamic, Eigen::Dynamic>;
using EigenVectorXd     = Eigen::Matrix<float64_t, Eigen::Dynamic, 1>;
using EigenSparseMatrix = Eigen::SparseMatrix<float64_t, Eigen::ColMajor, long int>;
using EigenSparseIndex  = typename EigenSparseMatrix::Index;
using EigenTriplet      = Eigen::Triplet<float64_t>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EigenMatrixXd Convert(const holo::numerics::MatrixXT<float64_t>& mat)
{
    EigenMatrixXd result(mat.GetRows(), mat.GetCols());
    for (uint32_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint32_t j = 0u; j < mat.GetCols(); j++)
        {
            result(i, j) = mat(i, j);
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
EigenVectorXd Convert(const T& vec)
{
    EigenVectorXd result(vec.GetSize());
    for (uint32_t i = 0u; i < vec.GetSize(); i++)
    {
        result(i) = vec(i);
    }
    return result;
}

}  // namespace spline_internal

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
SplineFittingT<Dimension, Degree, Uniform>::SplineFittingT(const std::vector<float64_t>& times,
                                                           const std::vector<PointType>& data, float64_t lambda,
                                                           uint32_t num_of_time_segments)
  : Base(std::vector<float64_t>(2u * (DegreeValue + 1u), 0.0), /* dummy knots*/
         std::vector<PointType>(DegreeValue + 1u, PointType()) /*dummy control points */)
{
    /**
     * @brief sanity check
     *
     */

    // c1. size consistency
    if (times.size() != data.size())
    {
        std::stringstream ss;
        ss << "SplineFittingT --- the size of timestamps is: " << times.size()
           << ", the size of data is: " << data.size() << ", they are not equal !!!";
        LOG(ERROR) << ss.str();
        std::string s = ss.str();
        throw std::out_of_range(s);
    }

    // c2. size value
    if (times.size() < 2u)
    {
        std::string s("SplineFittingT---the size of times is less than 2 !!!");
        LOG(ERROR) << s;
        throw std::out_of_range(s);
    }

    // c3. time segment validity
    if (num_of_time_segments < 1u || num_of_time_segments >= times.size())
    {
        LOG_IF(WARNING, num_of_time_segments >= times.size())
            << "SplineFittingT --- inappropriate num_of_time_segments setting, the algorithm will use default value!!!";
        num_of_time_segments = times.size() - DegreeValue;
    }

    // after checking, start initialization
    initialize(times, data, lambda, num_of_time_segments);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
SplineFittingT<Dimension, Degree, Uniform>::~SplineFittingT() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
void SplineFittingT<Dimension, Degree, Uniform>::initialize(const std::vector<float64_t>& times,
                                                            const std::vector<PointType>& data, const float64_t lambda,
                                                            const uint32_t num_of_time_segments)
{
    LOG(INFO) << "SplineFittingT --- start fitting ... ";
    // initialize knots and control points
    std::vector<float64_t> knots = computeKnots(times, num_of_time_segments);
    std::vector<PointType> control_points(getControlPointsNumber(num_of_time_segments));

    // update basis matrix with knots and control points size
    Base::SetKnotsControlPoints(knots, control_points);

    // compute real control points
    control_points = computeControlPointsSparse(times, data, lambda);

    // update control points
    Base::SetControlPoints(control_points);
    LOG(INFO) << "SplineFittingT --- Done!";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
std::vector<float64_t> SplineFittingT<Dimension, Degree, Uniform>::computeKnots(
    const std::vector<float64_t>& times, const uint32_t num_of_time_segments) const
{
    if (num_of_time_segments == times.size() - DegreeValue)
    {
        return averageKnots(times, num_of_time_segments);
    }

    // general way
    const uint32_t num_of_knots = getKnotsNumber(num_of_time_segments);

    const float64_t dt = (times.back() - times.front()) / num_of_time_segments;

    std::vector<float64_t> knots(num_of_knots);
    for (int64_t i = 0u; i < (int64_t)num_of_knots; i++)
    {
        knots[i] = (times.front() + (i - (int64_t)DegreeValue) * dt);
    }

    // avoid numeric issue
    knots.at(num_of_time_segments + DegreeValue) = times.back();

    return knots;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
std::vector<float64_t> SplineFittingT<Dimension, Degree, Uniform>::averageKnots(
    const std::vector<float64_t>& times, const uint32_t num_of_time_segments) const
{
    const uint32_t         num_of_knots = getKnotsNumber(num_of_time_segments);
    std::vector<float64_t> knots(num_of_knots);

    for (uint32_t i = 1u; i < times.size() - DegreeValue; i++)
    {
        float64_t sum = 0.0;
        for (uint32_t j = 0u; j < DegreeValue; j++)
        {
            sum += times.at(i + j);
        }
        sum /= DegreeValue;
        knots.at(i + DegreeValue) = sum;
    }

    for (uint32_t i = 0u; i < OrderValue; i++)
    {
        knots.at(i) = times.at(0u);
    }

    for (uint32_t i = knots.size() - OrderValue; i < knots.size(); i++)
    {
        knots.at(i) = times.back();
    }
    return knots;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
uint32_t SplineFittingT<Dimension, Degree, Uniform>::getKnotsNumber(const uint32_t num_of_time_segments) const
{
    return num_of_time_segments + 2u * OrderValue - 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
uint32_t SplineFittingT<Dimension, Degree, Uniform>::getControlPointsNumber(const uint32_t num_of_time_segments) const
{
    return num_of_time_segments + OrderValue - 1u;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
std::vector<typename SplineFittingT<Dimension, Degree, Uniform>::PointType>
SplineFittingT<Dimension, Degree, Uniform>::computeControlPointsSparse(const std::vector<float64_t>& times,
                                                                       const std::vector<PointType>& data,
                                                                       const float64_t               lambda) const
{
    const uint32_t num_of_control_points = Base::GetControlPoints().size();
    const uint32_t A_rows                = DimensionValue * data.size();
    const uint32_t A_cols                = DimensionValue * num_of_control_points;

    // create A, x, b
    spline_internal::EigenSparseMatrix A(A_rows, A_cols);
    spline_internal::EigenVectorXd     b(A_rows);
    spline_internal::EigenVectorXd     x(A_cols);

    // fill A and b
    {
        std::vector<spline_internal::EigenTriplet> triplets;
        triplets.reserve(DimensionValue * data.size() * OrderValue);
        uint32_t       row_index     = 0u;
        const uint32_t jacobian_rows = DimensionValue;
        const uint32_t jacobian_cols = DimensionValue * OrderValue;
        for (uint32_t i = 0u; i < times.size(); i++)
        {
            const uint32_t cpt_start_index = computeControlPointStartIndex(times.at(i));
            const MatrixXd jacobian        = computeJacobian(times.at(i));

            const spline_internal::EigenSparseIndex row_anchor = row_index;
            const spline_internal::EigenSparseIndex col_anchor = cpt_start_index * DimensionValue;

            for (uint32_t row = 0u; row < jacobian_rows; row++)
            {
                for (uint32_t col = 0u; col < jacobian_cols; col++)
                {
                    triplets.emplace_back(row_anchor + row, col_anchor + col, jacobian(row, col));
                }
            }

            b.segment(row_index, DimensionValue) = spline_internal::Convert(data.at(i));
            row_index += DimensionValue;
        }

        A.setFromTriplets(triplets.begin(), triplets.end());

        b = (A.transpose() * b).eval();
        A = (A.transpose() * A).eval();
    }

    // consider smoothing term
    {
        const MatrixXd W                    = MatrixXd::Identity(DimensionValue) * lambda;
        const uint32_t derivative_order     = OrderValue == 2u ? 1u : 2u;
        const uint32_t num_of_time_segments = Base::GetKnots().size() - 2u * Base::OrderValue + 1u;

        spline_internal::EigenSparseMatrix         Q(A.rows(), A.cols());
        std::vector<spline_internal::EigenTriplet> triplets;
        triplets.reserve(num_of_time_segments * DimensionValue * OrderValue);

        const uint32_t segment_rows = DimensionValue * OrderValue;
        const uint32_t segment_cols = segment_rows;
        for (uint32_t i = 0u; i < num_of_time_segments; i++)
        {
            const MatrixXd S = segmentQuadraticIntegral(W, i, derivative_order);

            const spline_internal::EigenSparseIndex row_anchor = i * DimensionValue;
            const spline_internal::EigenSparseIndex col_anchor = row_anchor;

            for (uint32_t row = 0u; row < segment_rows; row++)
            {
                for (uint32_t col = 0u; col < segment_cols; col++)
                {
                    triplets.emplace_back(row_anchor + row, col_anchor + col, S(row, col));
                }
            }
        }

        Q.setFromTriplets(triplets.begin(), triplets.end());

        // update A
        A = (A + Q).eval();
    }

    // solve x
    {
        Eigen::SparseLU<spline_internal::EigenSparseMatrix> solver;
        solver.analyzePattern(A);
        solver.factorize(A);
        x = solver.solve(b).transpose();
    }

    // convert
    std::vector<PointType> cpts;
    cpts.reserve(num_of_control_points);
    for (uint32_t i = 0u; i < num_of_control_points; i++)
    {
        const uint32_t index = i * DimensionValue;
        PointType      pt;
        for (uint32_t j = 0u; j < DimensionValue; j++)
        {
            pt(j) = x(index + j);
        }
        cpts.emplace_back(pt);
    }

    return cpts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
uint32_t SplineFittingT<Dimension, Degree, Uniform>::computeControlPointStartIndex(const float64_t t) const
{
    size_t    slot;
    float64_t U;
    Base::getSlotAndU(t, slot, U);

    return slot - Base::DegreeValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
typename SplineFittingT<Dimension, Degree, Uniform>::MatrixXd
SplineFittingT<Dimension, Degree, Uniform>::computeJacobian(const float64_t t) const
{
    MatrixXd       jacobian(DimensionValue, DimensionValue * OrderValue);  // default zero
    const MatrixXd identity = MatrixXd::Identity(DimensionValue);

    // compute weight vector
    float64_t weight[OrderValue] = {};
    {
        size_t    slot;
        float64_t U;
        Base::getSlotAndU(t, slot, U);
        Base::template computeCoefficientsToParam<0u>(U, slot, weight);
    }

    // update jacobian matrix
    for (uint32_t i = 0u; i < OrderValue; i++)
    {
        jacobian.SetBlock(0u, DimensionValue * i, identity * weight[i]);
    }

    return jacobian;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
typename SplineFittingT<Dimension, Degree, Uniform>::MatrixXd
SplineFittingT<Dimension, Degree, Uniform>::segmentQuadraticIntegral(const MatrixXd& W, const uint32_t index,
                                                                     const uint32_t derivative_order) const
{
    const MatrixXd D = computeDii(index);
    MatrixXd       V = computeVi(index);
    const MatrixXd M = computeMi(index);

    for (uint32_t i = 0u; i < derivative_order; i++)
    {
        V = D.Transpose() * V * D;
    }

    MatrixXd WV(OrderValue * DimensionValue, OrderValue * DimensionValue);  // default zero

    for (uint32_t row = 0u; row < DimensionValue; row++)
    {
        for (uint32_t col = 0u; col < DimensionValue; col++)
        {
            WV.SetBlock(row * OrderValue, col * OrderValue, W(row, col) * V);
        }
    }

    const MatrixXd S = M.Transpose() * WV * M;
    return S;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
typename SplineFittingT<Dimension, Degree, Uniform>::MatrixXd
SplineFittingT<Dimension, Degree, Uniform>::computeDii(const uint32_t index) const
{
    const std::pair<float64_t, float64_t> t_range = getTimeInterval(index);

    const float64_t dt     = t_range.second - t_range.first;
    const float64_t inv_dt = dt > 0.0 ? 1.0 / dt : 0.0;

    MatrixXd D(OrderValue, OrderValue);  // default zero

    for (uint32_t row = 0; row < OrderValue - 1u; row++)
    {
        D(row, row + 1u) = ((float64_t)row + 1.0) * inv_dt;
    }

    return D;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
typename SplineFittingT<Dimension, Degree, Uniform>::MatrixXd
SplineFittingT<Dimension, Degree, Uniform>::computeVi(const uint32_t index) const
{
    VectorXd vals(2u * OrderValue);

    for (uint32_t ind = 0u; ind < vals.GetSize(); ind++)
    {
        vals(ind) = 1.0 / ((float64_t)ind + 1.0);
    }

    const std::pair<float64_t, float64_t> t_range = getTimeInterval(index);
    const float64_t                       dt      = t_range.second - t_range.first;

    MatrixXd V(OrderValue, OrderValue);  // default zero

    for (uint32_t row = 0u; row < OrderValue; row++)
    {
        for (uint32_t col = 0u; col < OrderValue; col++)
        {
            V(row, col) = vals(row + col) * dt;
        }
    }

    return V;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
typename SplineFittingT<Dimension, Degree, Uniform>::MatrixXd
SplineFittingT<Dimension, Degree, Uniform>::computeMi(const uint32_t index) const
{
    MatrixXd M(DimensionValue * OrderValue, DimensionValue * OrderValue);  // default zero

    for (uint32_t i = 0u; i < OrderValue; i++)
    {
        M.SetBlock(0u, i * DimensionValue, computeBij(index, i));
    }

    return M;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
typename SplineFittingT<Dimension, Degree, Uniform>::MatrixXd
SplineFittingT<Dimension, Degree, Uniform>::computeBij(const uint32_t index, const uint32_t col) const
{
    MatrixXd B(OrderValue * DimensionValue, DimensionValue);

    const BasisMatrixType& basis = Base::getBasisMatrix(index + DegreeValue);

    for (uint32_t i = 0u; i < DimensionValue; i++)
    {
        B.SetBlock(i * OrderValue, i, basis.GetCol(col));
    }

    return B;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <size_t Dimension, size_t Degree, bool_t Uniform>
std::pair<float64_t, float64_t> SplineFittingT<Dimension, Degree, Uniform>::getTimeInterval(const uint32_t index) const
{
    return std::make_pair(Base::GetKnots().at(OrderValue - 1u + index), Base::GetKnots().at(OrderValue + index));
}

}  // namespace localization
}  // namespace holo
