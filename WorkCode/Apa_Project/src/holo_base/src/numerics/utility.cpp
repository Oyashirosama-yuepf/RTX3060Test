/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file utility.cpp
 * @brief holo numerics utility cpp file
 * @author Yanwei. Du, duyanwei@holomatic.com
 * @date 2019-07-09
 */

#include <holo/numerics/utility.h>
#include <holo/numerics/impl/utility.hpp>

#define INSTANTIATE(Scalar)                                                                                            \
    template void   ComputeMeanAndStdev<Scalar>(const std::vector<Scalar>& v, Scalar& mean, Scalar& stdev) noexcept;   \
    template void   ComputeMaxAndMinValue<Scalar>(const std::vector<Scalar>& data, Scalar& max_value,                  \
                                                Scalar& min_value) noexcept;                                         \
    template Scalar ComputeRMS<Scalar>(const std::vector<Scalar>& data) noexcept;                                      \
    template void   ComputeCovarianceMatrix<Scalar>(const MatrixXT<Scalar>& samples, VectorXT<Scalar>& mean,           \
                                                  MatrixXT<Scalar>& covariance) noexcept;                            \
    template void   ComputePolynomialRoots<Scalar>(const VectorXT<Scalar>&               coeffs,                       \
                                                 std::set<std::pair<Scalar, Scalar> >& roots) noexcept;

namespace holo
{
namespace numerics
{
INSTANTIATE(float32_t);
INSTANTIATE(float64_t);
}  // namespace numerics
}  // namespace holo
