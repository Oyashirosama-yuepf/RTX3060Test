/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file utility.hpp
 * @brief utility functions in numerics
 * @author jiaxing.zhao, duyanwei
 * @date 2019-09-04
 */

#ifndef HOLO_NUMERICS_UTILITY_HPP_
#define HOLO_NUMERICS_UTILITY_HPP_

#include <algorithm>
#include <cmath>
#include <numeric>

#include <holo/log/hololog.h>
#include <Eigen/Dense>

#include <holo/core/epsilon.h>
#include <holo/numerics/utility.h>

namespace holo
{
namespace numerics
{
template <typename Scalar>
void ComputeMeanAndStdev(const std::vector<Scalar>& v, Scalar& mean, Scalar& stdev) noexcept
{
    if (v.empty())
    {
        return;
    }

    mean = std::accumulate(v.begin(), v.end(), static_cast<Scalar>(0.0)) / static_cast<Scalar>(v.size());

    std::vector<Scalar> diff(v.size());
    (void)std::transform(v.begin(), v.end(), diff.begin(), [mean](const Scalar x) { return x - mean; });

    const Scalar sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), static_cast<Scalar>(0.0));
    stdev               = std::sqrt(sq_sum / static_cast<Scalar>(v.size()));
}

template <typename Scalar>
void ComputeMaxAndMinValue(const std::vector<Scalar>& data, Scalar& max_value, Scalar& min_value) noexcept
{
    if (data.empty())
    {
        return;
    }

    max_value = *std::max_element(data.begin(), data.end());
    min_value = *std::min_element(data.begin(), data.end());
}

template <typename Scalar>
Scalar ComputeRMS(const std::vector<Scalar>& data) noexcept
{
    if (data.empty())
    {
        return static_cast<Scalar>(0.0);
    }

    const Scalar sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), static_cast<Scalar>(0.0));
    return std::sqrt(sq_sum / static_cast<Scalar>(data.size()));
}

template <typename Scalar>
void ComputeCovarianceMatrix(const MatrixXT<Scalar>& samples, VectorXT<Scalar>& mean,
                             MatrixXT<Scalar>& covariance) noexcept
{
    // sanity check
    const uint16_t sample_size = samples.GetRows();
    const uint16_t sample_dim  = samples.GetCols();
    if ((sample_size == 0u) || (sample_dim == 0u))
    {
        return;
    }

    // compute mean
    mean.Resize(static_cast<uint32_t>(sample_dim));
    mean.SetZero();
    for (uint16_t i = 0u; i < sample_dim; i++)
    {
        for (uint16_t j = 0u; j < sample_size; j++)
        {
            mean(i) += samples(j, i);
        }
    }
    mean /= static_cast<Scalar>(sample_size);

    // compute variance
    covariance.Resize(sample_dim, sample_dim);
    covariance.SetZero();
    for (uint16_t i = 0u; i < sample_size; i++)
    {
        VectorXT<Scalar> vec(sample_dim);
        for (uint16_t j = 0u; j < sample_dim; j++)
        {
            vec(j) = samples(i, j) - mean(j);
        }

        covariance += vec * vec.Transpose();
    }
    return;
}

template <typename Scalar>
void ComputePolynomialRoots(const VectorXT<Scalar>& coeffs, std::set<std::pair<Scalar, Scalar> >& roots) noexcept
{
    if (coeffs.GetSize() <= 1u)
    {
        LOG(INFO) << "function is constant!";
        return;
    }

    // find the first coefficient that is not zero, equivalent to extract x,
    // e.g. x + x^2 = x( 1 + x), here 0 is root
    if (ScalarEqualT<Scalar>()(coeffs(0), static_cast<Scalar>(0.0)))
    {
        (void)roots.emplace(static_cast<Scalar>(0.0), static_cast<Scalar>(0.0));
        const VectorXT<Scalar> sub_coeffs = coeffs.GetSegment(1u, coeffs.GetSize() - 1u);
        ComputePolynomialRoots(sub_coeffs, roots);
    }
    else
    {
        int32_t index_of_nonzero_from_right = coeffs.GetSize() - 1u;
        for (; index_of_nonzero_from_right >= 0; --index_of_nonzero_from_right)
        {
            if (!ScalarEqualT<Scalar>()(coeffs(index_of_nonzero_from_right), static_cast<Scalar>(0.0)))
            {
                break;
            }
        }

        const VectorXT<Scalar> coeffcients = coeffs.GetSegment(0u, index_of_nonzero_from_right + 1u);

        const uint32_t size = coeffcients.GetSize();
        const Scalar   a0   = coeffcients(0u);

        Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> mat_root_correlation;
        mat_root_correlation.resize(size, size);
        mat_root_correlation.fill(static_cast<Scalar>(0.0));

        // if i < size coeffcients out of bound
        for (uint32_t i = 0u; i < size - 1u; ++i)
        {
            mat_root_correlation(0u, i) = -coeffcients(i + 1u) / a0;
        }

        for (uint32_t i = 0u; i < size - 1u; ++i)
        {
            mat_root_correlation(i + 1u, i) = static_cast<Scalar>(1.0);
        }

        Eigen::EigenSolver<Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> > es(mat_root_correlation);

        const Eigen::Matrix<Scalar, Eigen::Dynamic, 1> imag_values = es.eigenvalues().imag();
        const Eigen::Matrix<Scalar, Eigen::Dynamic, 1> real_values = es.eigenvalues().real();

        for (uint32_t i = 0u; i < (uint32_t)real_values.size(); ++i)
        {
            const Scalar den = real_values(i) * real_values(i) + imag_values(i) * imag_values(i);

            if (den > ScalarEqualT<Scalar>().GetEpsilonValue())
            {
                (void)roots.emplace(real_values(i) / den, -imag_values(i) / den);
            }
        }
    }

    return;
}

}  // namespace numerics
}  // namespace holo

#endif  // HOLO_NUMERICS_UTILITY_HPP_
