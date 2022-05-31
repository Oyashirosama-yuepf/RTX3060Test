/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _SPLINE_SPLINE_SEG_KERNEL_H_
#define _SPLINE_SPLINE_SEG_KERNEL_H_

#include <Eigen/Core>
#include <string>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>

#include <holo/planning/common/macro.h>

namespace holo
{
namespace planning
{
class SplineSegKernel
{
public:
    // generating kernel matrix
    Eigen::MatrixXd Kernel(const uint32_t num_params, const float64_t accumulated_x);

    // only support N <= 3 cases
    Eigen::MatrixXd NthDerivativeKernel(const uint32_t n, const uint32_t num_params, const float64_t accumulated_x);

private:
    Eigen::MatrixXd DerivativeKernel(const uint32_t num_of_params, const float64_t accumulated_x);
    Eigen::MatrixXd SecondOrderDerivativeKernel(const uint32_t num_of_params, const float64_t accumulated_x);
    Eigen::MatrixXd ThirdOrderDerivativeKernel(const uint32_t num_of_params, const float64_t accumulated_x);

    void IntegratedTermMatrix(const uint32_t     num_of_params,
                              const float64_t    x,
                              const std::string& type,
                              Eigen::MatrixXd*   term_matrix) const;
    void CalculateFx(const uint32_t num_of_params);
    void CalculateDerivative(const uint32_t num_of_params);
    void CalculateSecondOrderDerivative(const uint32_t num_of_params);
    void CalculateThirdOrderDerivative(const uint32_t num_of_params);

    const uint32_t reserved_order_ = 5;

    // 1.0 / (r + c + 1.0)
    Eigen::MatrixXd kernel_fx_;

    // r * c / (r + c - 1.0)
    Eigen::MatrixXd kernel_derivative_;

    // (r * r - r) * (c * c - c) / (r + c - 3.0)
    Eigen::MatrixXd kernel_second_order_derivative_;

    // (r * r - r) * (r - 2) * (c * c - c) * (c - 2) / (r + c - 5.0)
    Eigen::MatrixXd kernel_third_order_derivative_;

    DECLARE_SINGLETON(SplineSegKernel);
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_SEG_KERNEL_H_
