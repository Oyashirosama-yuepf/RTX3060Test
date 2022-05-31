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
#include <Eigen/Core>
#include <holo/planning/qp/spline/spline_1d.h>


namespace holo
{
namespace planning
{

class Spline1dKernel {
 public:
  explicit Spline1dKernel(const Spline1d& spline1d);
  Spline1dKernel(const std::vector<float64_t>& x_knots,
                 const uint32_t spline_order);

  // customized input / output method
  void AddRegularization(const float64_t regularized_param);
  bool AddKernel(const Eigen::MatrixXd& kernel, const Eigen::MatrixXd& offset,
                 const float64_t weight);
  bool AddKernel(const Eigen::MatrixXd& kernel, const float64_t weight);

  Eigen::MatrixXd* mutable_kernel_matrix();
  Eigen::MatrixXd* mutable_offset();

  const Eigen::MatrixXd& kernel_matrix() const;
  const Eigen::MatrixXd& offset() const;

  // build-in kernel methods
  void AddDerivativeKernelMatrix(const float64_t weight);
  void AddSecondOrderDerivativeMatrix(const float64_t weight);
  void AddThirdOrderDerivativeMatrix(const float64_t weight);
  void AddDerivativeKernelMatrixForSplineK(const uint32_t k,
                                           const float64_t weight);
  void AddSecondOrderDerivativeMatrixForSplineK(const uint32_t k,
                                                const float64_t weight);
  void AddThirdOrderDerivativeMatrixForSplineK(const uint32_t k,
                                               const float64_t weight);

  // reference line kernel, x_coord in strictly increasing order (for path
  // optimizer)
  bool AddReferenceLineKernelMatrix(const std::vector<float64_t>& x_coord,
                                    const std::vector<float64_t>& ref_fx,
                                    const float64_t weight);

  // distance offset (for speed optimizer, given time optimize the distance can
  // go)
  void AddDistanceOffset(const float64_t weight);

 private:
  void AddNthDerivativekernelMatrix(const uint32_t n, const float64_t weight);
  void AddNthDerivativekernelMatrixForSplineK(const uint32_t n,
                                              const uint32_t k,
                                              const float64_t weight);
  uint32_t FindIndex(const float64_t x) const;

 private:
  Eigen::MatrixXd kernel_matrix_;
  Eigen::MatrixXd offset_;
  std::vector<float64_t> x_knots_;
  uint32_t spline_order_;
  uint32_t total_params_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_SPLINE_1D_KERNEL_H_
