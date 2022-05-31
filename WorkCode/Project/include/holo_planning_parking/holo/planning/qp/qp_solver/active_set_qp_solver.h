/*!
 *  \brief
 *  \author zhangyuchen (zhangyuchen@holomatic.ai)
 *  \date Jul 25, 2018
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_ACTIVE_SET_QP_SOLVER_H_
#define _HOLO_PLANNING_ACTIVE_SET_QP_SOLVER_H_

#include <holo/planning/qp/qp_solver/qp_solver.h>

namespace holo
{
namespace planning
{

/**
 * @brief class for qp solver
 */
class ActiveSetQpSolver : public QpSolver
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
    ActiveSetQpSolver(const Eigen::MatrixXd& matrix_h,
                      const Eigen::MatrixXd& matrix_g,
                      const Eigen::MatrixXd& inequality_matrix,
                      const Eigen::MatrixXd& inequality_boundary,
                      const Eigen::MatrixXd& equality_matrix,
                      const Eigen::MatrixXd& equality_boundary);

    /**
     * @brief destructor
     */
    virtual ~ActiveSetQpSolver() = default;

    /**
     * @brief function for solve qp problem
     *
     * @return true if succefully solve, false otherwise
     */
    bool Solve() override;

    /**
     * @brief set maximum iteration in qp solver
     *
     * @param[in] iteration          maximum iterations want to set
     */
    void Set_Max_Iteration(const uint32_t iteration);

    /**
     * @brief set hessian_type_ to positive definite matrix
     */
    void Set_Pos_Definite_Hessian();

    /**
     * @brief set hessian_type_ to positive semi-definite matrix
     */
    void Set_Pos_Semi_Definite_Hessian();

    /**
     * @brief set cholesky_refactorisation_freq_
     *
     * param[in] value want to set
     */
    void Set_Cholesky_Refactorisation_Freq(const uint32_t freq);

    /**
     * @brief set termination_tolerance_
     *
     * param[in] value want to set
     */
    void Set_Termination_Tolerance(const float64_t num);

    /**
     * @brief set debug_qp_
     *
     * param[in] true if print debug info, false if dont print debug info
     */
    void Set_Debug_Qp(const bool enable);

private:

    /**
     * @brief number of solving object
     */
    uint32_t num_param_ = 0;

    /**
     * @brief number of constraint
     */
    uint32_t num_constraint_ = 0;

    /**
     * @brief maximum iterations
     */
    uint32_t max_iter_ = 1000;

    /**
     * @brief type of matrix H
     */
    qpOASES::HessianType hessian_type_ = qpOASES::HST_UNKNOWN;

    /**
     * @brief result searching lower bound
     */
    float64_t lower_bound_ = -1e10;

    /**
     * @brief result searching upper bound
     */
    float64_t upper_bound_ = 1e10;

    /**
     * @brief Specifies the frequency of full factorisation refactorisations of the projected
     *        Hessian: 0 turns them off, 1 uses them at each iteration etc
     */
    uint32_t cholesky_refactorisation_freq_ = 0;

    /**
     * @brief Relative termination tolerance to stop homotopy
     */
    float64_t termination_tolerance_ = 1e-9;

    /**
     * @brief whether need to print qp debug infomation
     */
    bool debug_qp_ = false;


};//class ActiveSetQpSolver

}//namespace planning
}//namespace holo

#endif//_HOLO_PLANNING_ACTIVE_SET_QP_SOLVER_H_