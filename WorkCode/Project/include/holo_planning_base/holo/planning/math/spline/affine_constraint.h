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
#include <holo/numerics/matrix.h>

namespace holo
{
namespace planning
{
class AffineConstraint
{
public:
    AffineConstraint();
    ~AffineConstraint();

    const Eigen::MatrixXd& constraint_matrix() const;
    const Eigen::MatrixXd& constraint_boundary() const;
    bool_t AddConstraint(const Eigen::MatrixXd& constraint_matrix, const Eigen::MatrixXd& constraint_boundary);

private:
    Eigen::MatrixXd constraint_matrix_;
    Eigen::MatrixXd constraint_boundary_;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_AFFINE_CONSTRAINT_H_
