/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file eigen_solver.h
 * @brief holo eigen solver
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-09-05
 */

#ifndef HOLO_NUMERICS_EIGEN_SOLVER_H_
#define HOLO_NUMERICS_EIGEN_SOLVER_H_

#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace eigen_solver
{
/**
 * @addtogroup numerics
 * @{
 */

template <typename Scalar>
using MatrixXT [[deprecated]] = holo::numerics::MatrixXT<Scalar>;
template <typename Scalar>
using VectorXT [[deprecated]] = holo::numerics::VectorXT<Scalar>;

template <typename Scalar>
using MatrixXType = holo::numerics::MatrixXT<Scalar>;

template <typename Scalar>
using VectorXType = holo::numerics::VectorXT<Scalar>;

/**
 * @brief compute eigen values and eigen vectors (A * v = lambda * v)
 *
 * @tparam Scalar
 * @note it now only supports self-adjoint matrix (for real matrix, it means symmetric)
 * @param matrix input matrix
 * @param values eigen values in a vector form
 * @param vectors eigen vectors in a matrix form
 * @return bool_t success or not
 */
template <typename Scalar>
bool_t ComputeEigenValuesAndVectors(const MatrixXType<Scalar>& matrix, VectorXType<Scalar>& values,
                                    MatrixXType<Scalar>& vectors) noexcept;

/**
 * @brief singular value decomposition (A = U * diag(S) * V')
 *
 * @tparam Scalar
 * @param matrix input matrix
 * @param U decomposed U matrix
 * @param S decomposed singular values
 * @param V decomposed V  matrix
 * @param options ComputeFullU(0x04), ComputeFullV(0x10), ComputeThinU(0x08), ComputeThinV(0x20)
 * @return bool_t success or not
 */
template <typename Scalar>
bool_t SVD(const MatrixXType<Scalar>& matrix, MatrixXType<Scalar>& U, VectorXType<Scalar>& S, MatrixXType<Scalar>& V,
           const uint32_t options = 0x08 | 0x20) noexcept;

/**
 * @brief define linear system solver type
 *
 */
enum class Type
{
    FULL_PIV_LU,
    COL_PIV_HOUSEHOLDER_QR,
    LLT,
    LDLT,
    BDC_SVD,
    JACOBI_SVD,
};  // Type

/**
 * @brief Linear System Solver (A * x = b)
 *
 * @tparam Scalar
 * @param A coefficients matrix
 * @param b b value
 * @param type solver type
 * @return VectorXType<Scalar> results
 */
template <typename Scalar>
VectorXType<Scalar> SolveLinearSystem(const MatrixXType<Scalar>& A, const VectorXType<Scalar>& b,
                                   const Type type = Type::COL_PIV_HOUSEHOLDER_QR) noexcept;

/**
 * @}
 *
 */

}  // namespace eigen_solver
}  // namespace holo

#endif  // HOLO_NUMERICS_EIGEN_SOLVER_H_
