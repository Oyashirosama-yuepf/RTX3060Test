/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */


#ifndef MODULES_PLANNING_SMOOTHING_SPLINE_2D_KERNEL_H_
#define MODULES_PLANNING_SMOOTHING_SPLINE_2D_KERNEL_H_

#include <vector>
#include <Eigen/Core>

#include <holo/geometry/point2.h>

#include <holo/planning/qp/spline/spline_2d.h>

namespace holo {
namespace planning {

class Spline2dKernel {
 public:
  Spline2dKernel(const std::vector<float64_t>& t_knots,
                 const uint32_t spline_order);

  // customized input output
  void AddRegularization(const float64_t regularization_param);
  bool AddKernel(const Eigen::MatrixXd& kernel, const Eigen::MatrixXd& offset,
                 const float64_t weight);
  bool AddKernel(const Eigen::MatrixXd& kernel, const float64_t weight);

  Eigen::MatrixXd* mutable_kernel_matrix();
  Eigen::MatrixXd* mutable_offset();

  const Eigen::MatrixXd kernel_matrix() const;
  const Eigen::MatrixXd offset() const;

  // build-in kernel methods
  void AddDerivativeKernelMatrix(const float64_t weight);
  void AddSecondOrderDerivativeMatrix(const float64_t weight);
  void AddThirdOrderDerivativeMatrix(const float64_t weight);

  // reference line kernel, x_coord in strictly increasing order
  bool AddReferenceLineKernelMatrix(
      const std::vector<float64_t>& t_coord,
      const std::vector<geometry::Point2>& ref_points, const float64_t weight);

 private:
  void AddNthDerivativeKernelMatrix(const uint32_t n, const float64_t weight);
  uint32_t find_index(const float64_t x) const;

 private:
  Eigen::MatrixXd kernel_matrix_;
  Eigen::MatrixXd offset_;
  std::vector<float64_t> t_knots_;
  uint32_t spline_order_;
  uint32_t total_params_;
};

}  // namespace planning
}  // namespace apollo
#endif  // MODULES_PLANNING_SMOOTHING_SPLINE_2D_KERNEL_H_
