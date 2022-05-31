/*!
 *  \brief
 *  \author zhangyuchen (zhangyuchen@holomatic.ai)
 *  \date Jul 25, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_QP_SOLVER_H_
#define _HOLO_PLANNING_QP_SOLVER_H_

#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <qpOASES.hpp>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{

/**
 * @brief class for qp solver
 */
class QpSolver
{
public:

    /**
     * @brief constructor
     *
     * @param[in] matrix_h             the matrix H in object function
     * @param[in] matrix_g             the matrix g in object function
     * @param[in] inequality_matrix    inequality constraint matrix
     * @param[in] inequality_boundary  inequality boundary vector
     * @param[in] equality_matrix      equality constraint matrix
     * @param[in] equality_boundary    equality boundary vector
     */
    QpSolver(const Eigen::MatrixXd& matrix_h,
             const Eigen::MatrixXd& matrix_g,
             const Eigen::MatrixXd& inequality_matrix,
             const Eigen::MatrixXd& inequality_boundary,
             const Eigen::MatrixXd& equality_matrix,
             const Eigen::MatrixXd& equality_boundary);

    /**
     * @brief destructor
     */
    virtual ~QpSolver() = default;

    /**
     * @brief function for solve qp problem
     *
     * @return true if succefully solve, false otherwise
     */
    virtual bool Solve() = 0;

    /**
     * @brief return the computing result
     */
    const Eigen::MatrixXd Result() const;

protected:

    /**
     * @brief computing result
     */
    Eigen::MatrixXd result_;

    /**
     * @brief the matrix H in object function
     */
    Eigen::MatrixXd matrix_h_;

    /**
     * @brief the matrix g in object function
     */
    Eigen::MatrixXd matrix_g_;

    /**
     * @brief inequality constraint matrix
     */
    Eigen::MatrixXd inequality_matrix_;

    /**
     * @brief inequality boundary vector
     */
    Eigen::MatrixXd inequality_boundary_;

    /**
     * @brief equality constraint matrix
     */
    Eigen::MatrixXd equality_matrix_;

    /**
     * @brief equality boundary vector
     */
    Eigen::MatrixXd equality_boundary_;

};//class QpSolver

}//namespace planning
}//namespace holo

#endif//_HOLO_PLANNING_QP_SOLVER_H_