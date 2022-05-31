/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline.hpp
 * @brief holo spline implementation
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-12-06
 */

#include <vector>

#include <Eigen/Sparse>
#include <unsupported/Eigen/Splines>

#include <holo/numerics/spline.h>

namespace holo
{
template <int32_t DIM>
class SplineT<DIM>::Implementation
{
public:
    using EigenMatrixXType = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using EigenVectorXType = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
    using EigenSplineType  = Eigen::Spline<Scalar, DIM, Eigen::Dynamic>;

    using KnotVectorType         = typename EigenSplineType::KnotVectorType;
    using ControlPointVectorType = typename EigenSplineType::ControlPointVectorType;
    using ParameterVectorType    = typename EigenSplineType::ParameterVectorType;

    using TripletType      = Eigen::Triplet<Scalar>;
    using TripletsType     = std::vector<TripletType>;
    using MatrixType       = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using SparseMatrixType = Eigen::SparseMatrix<Scalar, Eigen::ColMajor, long int>;
    using SparseIndex      = typename SparseMatrixType::Index;
    using DenseIndex       = Eigen::DenseIndex;

    /**
     * @brief Construct a new Implementation object
     *
     * @param data data
     * @param degree degree
     * @param knots knots
     */
    Implementation(const MatrixXType& data, const uint8_t degree, const VectorXType& knots)
    {
        Eigen::Map<const EigenMatrixXType> temp(data.GetData(), data.GetRows(), data.GetCols());
        const EigenMatrixXType             eigen_data(temp.transpose());
        Eigen::Map<const EigenVectorXType> eigen_knots(knots.GetData(), knots.GetSize());
        spline_ = FittingSpline(eigen_data, degree, eigen_knots);
    }

    /**
     * @brief interpolation
     *
     * @param t interpolated position
     * @return VectorXType
     */
    VectorXType Interpolate(const Scalar t) const
    {
        const EigenVectorXType value = spline_(t);
        VectorXType            result(value.size());
        for (uint8_t i = 0u; i < value.size(); i++)
        {
            result(i) = value(i);
        }
        return result;
    }

    /**
     * @brief get derivatives
     *
     * @param t  interpolated position
     * @param order derivative order
     * @return MatrixXType derivatives up-to given order
     */
    MatrixXType Derivatives(const Scalar t, const uint8_t order) const
    {
        const EigenMatrixXType value = spline_.derivatives(t, order);
        MatrixXType            result(value.rows(), value.cols());
        for (uint8_t i = 0u; i < value.rows(); i++)
        {
            for (uint8_t j = 0u; j < value.cols(); j++)
            {
                result(i, j) = value(i, j);
            }
        }
        return result;
    }

private:
    /**
     * @brief fitting spline with given data
     *
     * @tparam PointArrayType
     * @param data
     * @param knots
     * @param degree
     */
    template <typename PointArrayType>
    EigenSplineType FittingSpline(const PointArrayType& pts, Eigen::DenseIndex degree,
                                  const ParameterVectorType& parameters) const
    {
        KnotVectorType knots;
        KnotAveraging(parameters, degree, knots);

        SparseIndex              n = pts.cols();
        SparseMatrixType         A(n, n);
        std::vector<TripletType> triplets;
        triplets.reserve(n * (degree + 1));

        for (SparseIndex i = 1; i < n - 1; ++i)
        {
            const SparseIndex span = EigenSplineType::Span(parameters[i], degree, knots);
            MatrixType        bf   = EigenSplineType::BasisFunctions(parameters[i], degree, knots);

            for (SparseIndex j = span - degree; j < span + 1; ++j)
            {
                const Scalar val = bf(j - (span - degree));
                triplets.push_back(TripletType(i, j, val));
            }
        }

        triplets.push_back(TripletType(0, 0, 1.0));
        triplets.push_back(TripletType(n - 1, n - 1, 1.0));
        A.setFromTriplets(triplets.begin(), triplets.end());

        Eigen::SparseLU<SparseMatrixType> solver;
        solver.analyzePattern(A);
        solver.factorize(A);

        ControlPointVectorType ctrls = solver.solve(MatrixType(pts.transpose())).transpose();

        return EigenSplineType(knots, ctrls);
    }

    /**
     * @brief knot averaging
     *
     * @details please refer to The NURBS book (2nd ed.) 9.2.1 Global Curve Interpolation to Point Data equation (9.8)
     *          for details
     * @param parameters
     * @param degree
     * @param knots
     */
    void KnotAveraging(const ParameterVectorType& parameters, Eigen::DenseIndex degree, KnotVectorType& knots) const
    {
        Eigen::DenseIndex num_knots = parameters.size() + degree + 1;
        knots.resize(num_knots);

        for (Eigen::DenseIndex j = 1; j < parameters.size() - degree; ++j)
        {
            knots(j + degree) = parameters.segment(j, degree).mean();
        }

        knots.segment(0, degree + 1).setConstant(parameters(0));
        knots.segment(knots.size() - degree - 1, degree + 1).setConstant(parameters(parameters.size() - 1));
    }

private:
    /**
     * @brief spline declaration
     *
     */
    EigenSplineType spline_;

};  // class Implementation

template <int32_t DIM>
SplineT<DIM>::SplineT(const MatrixXType& data, const uint8_t degree, const VectorXType& knots)
{
    if (data.GetRows() == 0u)
    {
        throw std::runtime_error("empty data");
    }
    else if (static_cast<int32_t>(data.GetCols()) != DIM)
    {
        throw std::runtime_error("inconsistent matrix and spline dimension");
    }
    else if (data.GetRows() != knots.GetRows())
    {
        throw std::runtime_error("inconsistent data and knots number");
    }

    boundary_min_ = knots(0u);
    boundary_max_ = knots(knots.GetSize() - 1u);
    impl_.reset(new Implementation(data, degree, knots));
}

template <int32_t DIM>
SplineT<DIM>::~SplineT() noexcept
{
}

template <int32_t DIM>
typename SplineT<DIM>::VectorXType SplineT<DIM>::Interpolate(const Scalar t) const
{
    if (t < boundary_min_ || t > boundary_max_)
    {
        throw std::runtime_error("!!!interpolation out of boundary!!!");
    }
    return impl_->Interpolate(t);
}

template <int32_t DIM>
typename SplineT<DIM>::MatrixXType SplineT<DIM>::Derivatives(const Scalar t, const uint8_t order) const
{
    if (t < boundary_min_ || t > boundary_max_)
    {
        throw std::runtime_error("!!!interpolation out of boundary!!!");
    }
    return impl_->Derivatives(t, order);
}

}  // namespace holo
