/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file eigen_solver.hpp
 * @brief holo eigen solver
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-09-05
 */

#ifndef HOLO_NUMERICS_EIGEN_SOLVER_HPP_
#define HOLO_NUMERICS_EIGEN_SOLVER_HPP_

#include <Eigen/Eigenvalues>
#include <Eigen/QR>
#include <Eigen/SVD>

#include <holo/numerics/eigen_solver.h>

namespace holo
{
namespace eigen_solver
{
template <typename Scalar>
using EigenMatrixT = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
template <typename Scalar>
using EigenVectorT = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;

/**
 * @brief convert to eigen matrix
 *
 * @tparam Scalar
 * @param in holo matrix
 * @return eigen matrix
 */
template <typename Scalar>
EigenMatrixT<Scalar> ConvertMatrix(const MatrixXT<Scalar>& in) noexcept
{
    // convert holo matrix to eigen type
    EigenMatrixT<Scalar> out(in.GetRows(), in.GetCols());
    for (uint16_t i = 0u; i < in.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < in.GetCols(); j++)
        {
            out(i, j) = in.At(i, j);
        }
    }
    return out;
}

/**
 * @brief convert to holo matrix
 *
 * @tparam Scalar
 * @param in eigen matrix
 * @return holo matrix
 */
template <typename Scalar>
MatrixXT<Scalar> ConvertMatrix(const EigenMatrixT<Scalar>& in) noexcept
{
    // convert holo matrix to eigen type
    MatrixXT<Scalar> out(in.rows(), in.cols());
    for (uint16_t i = 0u; i < out.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < out.GetCols(); j++)
        {
            out.At(i, j) = in(i, j);
        }
    }
    return out;
}

/**
 * @brief convert to eigen vector
 *
 * @tparam Scalar
 * @param in holo vector
 * @return eigen vector
 */
template <typename Scalar>
EigenVectorT<Scalar> ConvertVector(const VectorXT<Scalar>& in) noexcept
{
    // convert holo vector to eigen type
    EigenVectorT<Scalar> out(in.GetSize());
    for (uint32_t i = 0u; i < in.GetSize(); i++)
    {
        out(i) = in(i);
    }
    return out;
}

/**
 * @brief convert to holo vector
 *
 * @tparam Scalar
 * @param in eigen vector
 * @return holo vector
 */
template <typename Scalar>
VectorXT<Scalar> ConvertVector(const EigenVectorT<Scalar>& in) noexcept
{
    // convert holo vector to eigen type
    VectorXT<Scalar> out(in.size());
    for (uint32_t i = 0u; i < out.GetSize(); i++)
    {
        out(i) = in(i);
    }
    return out;
}

template <typename Scalar>
bool_t ComputeEigenValuesAndVectors(const MatrixXT<Scalar>& matrix, VectorXT<Scalar>& values,
                                    MatrixXT<Scalar>& vectors) noexcept
{
    if (!matrix.IsSymmetric())
    {
        return false;
    }

    // convert to eigen matrix
    const EigenMatrixT<Scalar> mat = ConvertMatrix<Scalar>(matrix);

    // solve eigen vectors and eigen values
    typename Eigen::SelfAdjointEigenSolver<EigenMatrixT<Scalar> > solver(mat, Eigen::ComputeEigenvectors);
    {
        values  = ConvertVector(solver.eigenvalues());
        vectors = ConvertMatrix(solver.eigenvectors());
    }
    return true;
}

template <typename Scalar>
bool_t SVD(const MatrixXT<Scalar>& matrix, MatrixXT<Scalar>& U, VectorXT<Scalar>& S, MatrixXT<Scalar>& V,
           const uint32_t options) noexcept
{
    // convert holo matrix to eigen type
    const EigenMatrixT<Scalar> mat = ConvertMatrix<Scalar>(matrix);

    // run svd
    typename Eigen::JacobiSVD<EigenMatrixT<Scalar> > svd(mat, options);
    {
        S = ConvertVector(svd.singularValues());
        if ((options & Eigen::ComputeFullU) || (options & Eigen::ComputeThinU))
        {
            U = ConvertMatrix(svd.matrixU());
        }
        if ((options & Eigen::ComputeFullV) || (options & Eigen::ComputeThinV))
        {
            V = ConvertMatrix(svd.matrixV());
        }
    }
    return true;
}

template <typename Scalar>
VectorXT<Scalar> SolveLinearSystem(const MatrixXT<Scalar>& A, const VectorXT<Scalar>& b, const Type type) noexcept
{
    // convert to eigen type
    const EigenMatrixT<Scalar> mat_A = ConvertMatrix<Scalar>(A);
    const EigenVectorT<Scalar> mat_b = ConvertVector<Scalar>(b);
    EigenVectorT<Scalar>       mat_solution;
    switch (type)
    {
        case Type::FULL_PIV_LU:
        {
            mat_solution = mat_A.fullPivLu().solve(mat_b);
            break;
        }
        case Type::COL_PIV_HOUSEHOLDER_QR:
        {
            mat_solution = mat_A.colPivHouseholderQr().solve(mat_b);
            break;
        }
        case Type::LLT:
        {
            mat_solution = mat_A.llt().solve(mat_b);
            break;
        }
        case Type::LDLT:
        {
            mat_solution = mat_A.ldlt().solve(mat_b);
            break;
        }
        case Type::BDC_SVD:
        {
            mat_solution = mat_A.bdcSvd().solve(mat_b);
            break;
        }
        case Type::JACOBI_SVD:
        {
            mat_solution = mat_A.jacobiSvd().solve(mat_b);
            break;
        }
        default:
        {
            break;
        }
    }

    return ConvertVector(mat_solution);
}

}  // namespace eigen_solver
}  // namespace holo

#endif  // HOLO_NUMERICS_EIGEN_SOLVER_HPP_
