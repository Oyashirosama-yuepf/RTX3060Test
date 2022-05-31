/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file eigen_solver.cpp
 * @brief holo eigen sovler cpp file
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-09-05
 */

#include <holo/numerics/eigen_solver.h>
#include <holo/numerics/impl/eigen_solver.hpp>

#define INSTANTIATE(Scalar)                                                                                            \
    template bool_t ComputeEigenValuesAndVectors(const MatrixXType<Scalar>& matrix, VectorXType<Scalar>& values,             \
                                                 MatrixXType<Scalar>& vectors) noexcept;                                  \
    template bool_t SVD(const MatrixXType<Scalar>& matrix, MatrixXType<Scalar>& U, VectorXType<Scalar>& S, MatrixXType<Scalar>& V, \
                        const uint32_t options) noexcept;                                                              \
    template VectorXType<Scalar> SolveLinearSystem(const MatrixXType<Scalar>& A, const VectorXType<Scalar>& b,                  \
                                                const Type type = Type::COL_PIV_HOUSEHOLDER_QR) noexcept;

namespace holo
{
namespace eigen_solver
{
INSTANTIATE(float32_t);
INSTANTIATE(float64_t);
}  // namespace eigen_solver
}  // namespace holo
