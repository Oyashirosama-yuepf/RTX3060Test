/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file qp_solver.h
 * @brief the header of qp_solver
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-12-12
 */

#ifndef MODULES_PLANNING_PLANNER_QP_SOLVER_H_
#define MODULES_PLANNING_PLANNER_QP_SOLVER_H_

#include <Eigen/Core>
#include <memory>
#include <vector>

#include <holo/log/hololog.h>
#include <qpOASES.hpp>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
/**
 * @brief the api of using QP library
 *
 * @details the QP library is QPOASES, if want to use other lib, please change this class
 */
class QpSolver
{
public:
    QpSolver(bool_t    enable_cholesky_refactorisation,
             float64_t eps_num,
             float64_t eps_den,
             float64_t eps_iter_ref,
             bool_t    enable_active_set_debug_info,
             uint32_t  max_iter) noexcept
      : enable_cholesky_refactorisation_(enable_cholesky_refactorisation)
      , eps_num_(eps_num)
      , eps_den_(eps_den)
      , eps_iter_ref_(eps_iter_ref)
      , enable_active_set_debug_info_(enable_active_set_debug_info)
      , max_iter_(max_iter)
      , last_num_constraint_(0)
      , last_num_param_(0)
      , last_problem_success_(false)
    {
    }

    bool_t Solve(const Eigen::MatrixXd& matrix_h,
                 const Eigen::MatrixXd& matrix_g,
                 const Eigen::MatrixXd& inequality_constraint_matrix,
                 const Eigen::MatrixXd& inequality_constraint_lower_boundary,
                 const Eigen::MatrixXd& inequality_constraint_upper_boundary,
                 const Eigen::MatrixXd& bound_lower_boundary,
                 const Eigen::MatrixXd& bound_upper_boundary);

    bool_t GetEnableCholeskyRefactorisation() const noexcept
    {
        return enable_cholesky_refactorisation_;
    }

    float64_t GetEpsNum() const noexcept
    {
        return eps_num_;
    }

    float64_t GetEpsDen() const noexcept
    {
        return eps_den_;
    }

    float64_t GetEpsIterRef() const noexcept
    {
        return eps_iter_ref_;
    }

    bool_t GetEnableActiveSetDebugInfo() const noexcept
    {
        return enable_active_set_debug_info_;
    }

    uint32_t GetMaxIter() const noexcept
    {
        return max_iter_;
    }

    uint32_t GetLastNumConstraint() const noexcept
    {
        return last_num_constraint_;
    }

    uint32_t GetLastNumParam() const noexcept
    {
        return last_num_param_;
    }

    bool_t GetLastProblemSuccess() const noexcept
    {
        return last_problem_success_;
    }

    const Eigen::MatrixXd& GetResult() const noexcept
    {
        return result_;
    }

private:
    bool_t    enable_cholesky_refactorisation_;
    float64_t eps_num_;
    float64_t eps_den_;
    float64_t eps_iter_ref_;
    bool_t    enable_active_set_debug_info_;
    uint32_t  max_iter_;

    uint32_t                              last_num_constraint_;
    uint32_t                              last_num_param_;
    bool_t                                last_problem_success_;
    Eigen::MatrixXd                       result_;
    std::unique_ptr<::qpOASES::SQProblem> sqp_solver_;
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_PLANNER_QP_SOLVER_H_
