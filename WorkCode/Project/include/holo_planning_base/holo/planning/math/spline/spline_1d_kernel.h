/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _SPLINE_SPLINE_1D_KERNEL_H_
#define _SPLINE_SPLINE_1D_KERNEL_H_

#include <vector>

#include <holo/planning/math/spline/spline_1d.h>

namespace holo
{
namespace planning
{
class Spline1dKernel
{
public:
    explicit Spline1dKernel(const Spline1d& spline1d);
    Spline1dKernel(const std::vector<float64_t>& x_knots, const uint32_t spline_order);

    // customized input / output method
    void   AddRegularization(const float64_t regularized_param);
    bool_t AddKernel(const numerics::MatrixXd& kernel, const numerics::MatrixXd& offset, const float64_t weight);
    bool_t AddKernel(const numerics::MatrixXd& kernel, const float64_t weight);

    numerics::MatrixXd* mutable_kernel_matrix();
    numerics::MatrixXd* mutable_offset();

    const numerics::MatrixXd kernel_matrix() const;
    const numerics::MatrixXd offset() const;

    // build-in kernel methods
    bool_t AddDerivativeKernelMatrix(const float64_t weight);
    bool_t AddSecondOrderDerivativeMatrix(const float64_t weight);
    bool_t AddThirdOrderDerivativeMatrix(const float64_t weight);
    bool_t AddDerivativeKernelMatrixForSplineK(const uint32_t k, const float64_t weight);
    bool_t AddSecondOrderDerivativeMatrixForSplineK(const uint32_t k, const float64_t weight);
    bool_t AddThirdOrderDerivativeMatrixForSplineK(const uint32_t k, const float64_t weight);

    // reference line kernel, x_coord in strictly increasing order (for path
    // optimizer)
    bool_t AddReferenceLineKernelMatrix(const std::vector<float64_t>& x_coord,
                                        const std::vector<float64_t>& ref_fx,
                                        const float64_t               weight);

private:
    bool_t   AddNthDerivativekernelMatrix(const uint32_t n, const float64_t weight);
    bool_t   AddNthDerivativekernelMatrixForSplineK(const uint32_t n, const uint32_t k, const float64_t weight);
    uint32_t FindIndex(const float64_t x) const;

private:
    numerics::MatrixXd     kernel_matrix_;
    numerics::MatrixXd     offset_;
    std::vector<float64_t> x_knots_;
    uint32_t               spline_order_;
    uint32_t               total_params_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_1D_KERNEL_H_
