/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline.cpp
 * @brief holo spline class
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-09-28
 */

#include <vector>

#include <Eigen/Sparse>
#include <unsupported/Eigen/Splines>

#include <holo/geometry/point3_spline.h>

namespace holo
{
class Point3Spline::Implementation
{
public:
    using EigenMatrix3XType = Eigen::Matrix<Scalar, 3, Eigen::Dynamic>;
    using EigenVectorXType  = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
    using EigenVector3Type  = Eigen::Matrix<Scalar, 3, 1>;
    using EigenSpline3Type  = Eigen::Spline<Scalar, 3, Eigen::Dynamic>;

    using KnotVectorType         = typename EigenSpline3Type::KnotVectorType;
    using ControlPointVectorType = typename EigenSpline3Type::ControlPointVectorType;
    using ParameterVectorType    = typename EigenSpline3Type::ParameterVectorType;

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
     * @param offset offset
     * @param degree degree
     */
    Implementation(const std::vector<std::pair<Scalar, Point3Type> >& data, const Point3Type& offset,
                   const uint32_t degree = 3u)
    {
        EigenMatrix3XType points;
        EigenVectorXType  knots;
        CreatePointsAndKnots(data, offset, points, knots);
        spline_ = FittingSpline(points, degree, knots);
    }

    /**
     * @brief Construct a new Implementation object
     *
     * @param data data
     * @param offset offset
     * @param degree degree
     * @param lambda lambda
     */
    Implementation(const std::vector<std::pair<Scalar, Point3Type> >& data, const Point3Type& offset,
                   const uint32_t degree, const Scalar lambda)
    {
        EigenMatrix3XType points;
        EigenVectorXType  knots;
        CreatePointsAndKnots(data, offset, points, knots);
        spline_ = FittingSpline(points, degree, knots, lambda);
    }

    /**
     * @brief interpolation
     *
     * @param t interpolated value
     * @return Vector3Type
     */
    Point3Type Interpolate(const Scalar t) const
    {
        const EigenVector3Type value = spline_(t);
        return Point3Type(value(0), value(1), value(2));
    }

private:
    /**
     * @brief Create a Points And Knots object
     *
     * @param data
     * @param offset
     * @param points
     * @param knots
     */
    void CreatePointsAndKnots(const std::vector<std::pair<Scalar, Point3Type> >& data, const Point3Type& offset,
                              EigenMatrix3XType& points, EigenVectorXType& knots) const
    {
        points.resize(3u, data.size());
        knots.resize(data.size());
        for (uint64_t i = 0u; i < data.size(); i++)
        {
            knots(i)      = data.at(i).first;
            points(0u, i) = data.at(i).second.GetX() - offset.GetX();
            points(1u, i) = data.at(i).second.GetY() - offset.GetY();
            points(2u, i) = data.at(i).second.GetZ() - offset.GetZ();
        }
    }

    /**
     * @brief fitting spline with given data
     *
     * @tparam PointArrayType
     * @param data
     * @param knots
     * @param degree
     */
    template <typename PointArrayType>
    EigenSpline3Type FittingSpline(const PointArrayType& pts, Eigen::DenseIndex degree,
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
            const SparseIndex span = EigenSpline3Type::Span(parameters[i], degree, knots);
            MatrixType        bf   = EigenSpline3Type::BasisFunctions(parameters[i], degree, knots);

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

        return EigenSpline3Type(knots, ctrls);
    }

    /**
     * @brief fitting spline with given data
     *
     * @tparam PointArrayType
     * @param data
     * @param knots
     * @param degree
     * @param lambda
     */
    template <typename PointArrayType>
    EigenSpline3Type FittingSpline(const PointArrayType& points, DenseIndex degree,
                                   const ParameterVectorType& parameters, const Scalar lambda) const
    {
        KnotVectorType knots;
        KnotAveraging(parameters, degree, knots);

        SparseIndex       n     = points.cols();
        Eigen::DenseIndex order = 2;

        TripletsType basis_triplets;
        basis_triplets.reserve(n * (degree + 1));

        TripletsType derivative_triplets;
        derivative_triplets.reserve(n * (degree + 1));

        for (SparseIndex i = 0; i < n; i++)
        {
            if (i == 0 || i == n - 1)
            {
                basis_triplets.push_back(TripletType(i, i, 1.0));
                continue;
            }

            SparseIndex span = EigenSpline3Type::Span(parameters[i], degree, knots);

            MatrixType basis = EigenSpline3Type::BasisFunctions(parameters[i], degree, knots);

            MatrixType derivatives = EigenSpline3Type::BasisFunctionDerivatives(parameters[i], order, degree, knots);

            for (SparseIndex j = span - degree; j < span + 1; j++)
            {
                const Scalar base = basis(j - (span - degree));
                basis_triplets.push_back(TripletType(i, j, base));

                const Scalar derivative = derivatives(order, j - (span - degree));
                derivative_triplets.push_back(TripletType(i, j, derivative));
            }
        }

        SparseMatrixType basis_matrix(n, n);
        basis_matrix.setFromTriplets(basis_triplets.begin(), basis_triplets.end());

        SparseMatrixType derivative_matrix(n, n);
        derivative_matrix.setFromTriplets(derivative_triplets.begin(), derivative_triplets.end());

        SparseMatrixType A =
            basis_matrix.transpose() * basis_matrix + lambda * derivative_matrix.transpose() * derivative_matrix;

        MatrixType b(n, 1);
        b = basis_matrix.transpose() * points.transpose();

        Eigen::SparseLU<SparseMatrixType> solver;
        solver.analyzePattern(A);
        solver.factorize(A);

        ControlPointVectorType control_points = solver.solve(b).transpose();

        EigenSpline3Type smoothing_spline = EigenSpline3Type(knots, control_points);

        return smoothing_spline;
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
     * @brief spline3 declaration
     *
     */
    EigenSpline3Type spline_;

};  // class Implementation

Point3Spline::Point3Spline(const std::vector<std::pair<Scalar, Point3Type> >& data, const Point3Type& offset)
  : degree_(3u), offset_(offset)
{
    if (data.empty())
    {
        throw std::runtime_error("empty data");
    }

    boundary_min_ = data.front().first;
    boundary_max_ = data.back().first;
    impl_.reset(new Implementation(data, offset, degree_));
}

Point3Spline::Point3Spline(const std::vector<std::pair<Scalar, Point3Type> >& data, const Point3Type& offset,
                           const Scalar lambda)
  : degree_(3u), offset_(offset)
{
    if (data.empty())
    {
        throw std::runtime_error("empty data");
    }

    boundary_min_ = data.front().first;
    boundary_max_ = data.back().first;
    impl_.reset(new Implementation(data, offset, degree_, lambda));
}

Point3Spline::~Point3Spline()
{
}

Point3Spline::Point3Type Point3Spline::Interpolate(const Scalar t, const bool_t local) const
{
    if (t < boundary_min_ || t > boundary_max_)
    {
        throw std::runtime_error("!!!interpolation out of boundary!!!");
    }

    Point3Type value = impl_->Interpolate(t);

    if (!local)
    {
        value += offset_;
    }

    return value;
}

Point3Spline::Point3Type Point3Spline::operator()(const Scalar t, const bool_t local) const
{
    return Interpolate(t, local);
}

}  // namespace holo
