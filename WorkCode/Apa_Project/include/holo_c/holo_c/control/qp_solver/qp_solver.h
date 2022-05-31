/**
 * @file qp_solver.h
 * @brief the header of qp solver
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-08-30
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_C_CONTROL_QP_SOLVER_H_
#define HOLO_C_CONTROL_QP_SOLVER_H_

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/numerics/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

#define QP_SOLVER_VARIABLES_DIMENSION 1  ///< dimension of variables
#define QP_SOLVER_VARIABLES_NUM 10       ///< number of variables

typedef enum
{
    QP_SOLVER_HT_ZERO,              ///< Hessian is zero matrix (i.e. LP formulation).
    QP_SOLVER_HT_IDENTITY,          ///< Hessian is identity matrix.
    QP_SOLVER_HT_POSDEF,            ///< Hessian is (strictly) positive definite.
    QP_SOLVER_HT_POSDEF_NULLSPACE,  ///< Hessian is positive definite on null space of active bounds/constraints.
    QP_SOLVER_HT_SEMIDEF,           ///< Hessian is positive semi-definite.
    QP_SOLVER_HT_INDEF,             ///< Hessian is indefinite.
    QP_SOLVER_HT_UNKNOWN            ///< Hessian type is unknown.
} QpSolverHessianType;

/**
 * @brief This structure represents a quadratic-planning problem solver.
 *
 * @detail Format of quadratic-planning problem:
 *              min_x  : q(x) = 0.5 * x^T * H * x  + x^T g
 *                    with respect to:    A * x = b (equality constraint)
 *                                        C * x >= d (inequality constraint)
 */
struct QpSolver
{
    struct Matrixf result;                                                           ///< computing result
    float32_t      result_buffer[MATRIXF_MIN_BUF_SIZE(QP_SOLVER_VARIABLES_NUM, 1)];  ///< computing result's buffer

    struct Matrixf* matrix_h;                             ///< the matrix H in object function
    struct Matrixf* matrix_g;                             ///< the matrix g in object function
    struct Matrixf* inequality_constrain_matrix;          ///< inequality-constraint matrix
    struct Matrixf* inequality_constrain_lower_boundary;  ///< inequality-constraint's lower-boundary vector
    struct Matrixf* inequality_constrain_upper_boundary;  ///< inequality-constraint's upper-boundary vector
    struct Matrixf* bound_lower_boundary;                 ///< bound's lower-boundary vector
    struct Matrixf* bound_upper_boundary;                 ///< bound's upper-boundary vector

    uint32_t            num_param;       ///< number of solving object
    uint32_t            num_constraint;  ///< number of constraint
    bool_t              has_bound;       ///< number of bound
    uint32_t            max_iter;        ///< maximum iterations
    QpSolverHessianType hessian_type;    ///< type of matrix H

    /** Specifies the frequency of full factorisation refactorisations of the projected.Hessian :
     *  0 turns them off, 1 uses them at each iteration etc
     */
    uint32_t cholesky_refactorisation_freq;

    float32_t termination_tolerance;  ///< Relative termination tolerance to stop homotopy
};

/**
 * @brief function for init qp problem
 *
 * @param solver Pointer to QpSolver structure.
 * @param matrix_h The matrix H in object function.
 * @param matrix_g The matrix g in object function.
 * @param inequality_constrain_matrix The matrix to describe inequality constrain.
 * @param inequality_constrain_lower_boundary The lower bound of inequality constrain.
 * @param inequality_constrain_upper_boundary The upper bound of inequality constrain.
 * @param bound_lower_boundary The lower bound of bound constrain.
 * @param bound_upper_boundary The upper bound of bound constrain.
 *
 * @return RC_SUCCESS init successfully
 * @return RC_QPSOLVER_NO_CONSTRAINT no constraint or bound of the qp problem
 */
retcode_t qp_solver_init(struct QpSolver* solver, struct Matrixf* matrix_h, struct Matrixf* matrix_g,
                         struct Matrixf* inequality_constrain_matrix,
                         struct Matrixf* inequality_constrain_lower_boundary,
                         struct Matrixf* inequality_constrain_upper_boundary, struct Matrixf* bound_lower_boundary,
                         struct Matrixf* bound_upper_boundary);

/**
 * @brief function for solve qp problem
 *
 * @param solver Pointer to QpSolver structure
 *
 * @return RC_SUCCESS init successfully
 * @return RC_QPOASES_MAX_NWSR_REACHED qpOASES solver failed due to reached max iteration
 * @return RC_QPOASES_INFEASIBILITY qpOASES solver failed due to infeasibility or other reasons
 * @return RC_QPSOLVER_NOT_SOLVED QProblem is not been solved
 */
retcode_t qp_solver_solve(struct QpSolver* solver);

/**
 * @brief get the result of qp problem
 *
 * @param solver Pointer to QpSolver structure.
 *
 * @return result of qp_solver.
 */
const struct Matrixf* qp_solver_get_result(const struct QpSolver* solver);

/**
 * @brief set maximum iteration in qp solver
 *
 * @param solver Pointer to QpSolver structure.
 * @param iteration Maximum iterations want to set.
 */
void qp_solver_set_max_iteration(struct QpSolver* solver, uint32_t iteration);

/**
 * @brief set hessian_type to positive definite matrix
 *
 * @param solver Pointer to QpSolver structure.
 */
void qp_solver_set_pos_definite_hessian(struct QpSolver* solver);

/**
 * @brief set hessian_type to positive semi-definite matrix
 *
 * @param solver Pointer to QpSolver structure.
 */
void qp_solver_set_pos_semi_definite_hessian(struct QpSolver* solver);

/**
 * @brief set cholesky_refactorisation_freq
 *
 * @param solver Pointer to QpSolver structure.
 * @param freq Value of frequency to be set.
 */
void qp_solver_set_cholesky_refactorisation_freq(struct QpSolver* solver, uint32_t freq);

/**
 * @brief set termination_tolerance
 *
 * @param solver Pointer to QpSolver structure.
 * @param num Value of num to be set.
 */
void qp_solver_set_termination_tolerance(struct QpSolver* solver, float32_t num);

#ifdef __cplusplus
}
#endif

#endif /* HOLO_C_CONTROL_QP_SOLVER_H_ */
