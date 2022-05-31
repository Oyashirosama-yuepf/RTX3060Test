/*!
 *  \brief
 *  \author liwenjun (liwenjun@holomatic.ai)
 *  \date Jul 14, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _SPLINE_AFFINE_CONSTRAINT_H_
#define _SPLINE_AFFINE_CONSTRAINT_H_

#include <Eigen/Core>
#include <holo/core/types.h>

namespace holo {
namespace planning {

class AffineConstraint {
 public:
  AffineConstraint();
  ~AffineConstraint();
  explicit AffineConstraint(const bool is_equality);
  explicit AffineConstraint(const Eigen::MatrixXd& constraint_matrix,
                            const Eigen::MatrixXd& constraint_boundary,
                            const bool is_equality);

  void SetIsEquality(const float64_t is_equality);

  const Eigen::MatrixXd& constraint_matrix() const;
  const Eigen::MatrixXd& constraint_boundary() const;
  bool AddConstraint(const Eigen::MatrixXd& constraint_matrix,
                     const Eigen::MatrixXd& constraint_boundary);

 private:
  Eigen::MatrixXd constraint_matrix_;
  Eigen::MatrixXd constraint_boundary_;
  bool is_equality_ = true;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_AFFINE_CONSTRAINT_H_
