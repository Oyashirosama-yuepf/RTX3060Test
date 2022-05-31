/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file spline_1d_smooth.h
 * @brief the header of spline 1d smooth
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-12-09
 */

#ifndef _SPLINE_1D_SMOOTH_
#define _SPLINE_1D_SMOOTH_

#include <holo/geometry/pose2.h>
#include <holo/planning/common/curve_point.h>
#include <holo/planning/qp/spline/spline_1d_generator.h>

namespace holo
{
namespace planning
{
class Spline1DSmooth
{
public:
    /**
     * @brief Constructor
     */
    Spline1DSmooth();

    /**
     * @brief Smoother interface
     *
     * @param[in] advice_path Advice static path
     * @param[in] forward Move direction
     * @param[in] pose Current pose
     * @param[out] path Smoothed path
     *
     * @return True if smooth successfully
     */
    bool Smooth(const std::vector<CurvePoint>& advice_path,
                bool_t                         forward,
                const geometry::Pose2&         pose,
                std::vector<CurvePoint>&       path);

private:
    /**
     * @brief Init the spline_solver
     *
     * @param start_s Start s value
     * @param end_s End s value
     *
     * @return Ture if init successfully
     */
    bool InitSpline(const float64_t start_s, const float64_t end_s);

    /**
     * @brief Add the constraint for QP
     *
     * @param start_s Start s value
     * @param start_l Start l value
     * @param start_delta_l Start delta l value
     * @param end_s End s value
     *
     * @return True if the constraint was added successfully, false otherwise
     */
    bool AddConstraint(float64_t start_s, float64_t start_l, float64_t start_delta_l, float64_t end_s);

    /**
     * @brief Add the kernel for QP
     *
     * @param start_s Start s value
     * @param end_s End s value
     */
    void AddKernel(float64_t start_s, float64_t end_s);

    /**
     * @brief Solve QP
     *
     * @return True if solve successfully
     */
    bool Solve();

private:
    std::unique_ptr<Spline1dGenerator> spline_generator_ = nullptr;

    std::vector<float64_t> knots_;
    std::vector<float64_t> evaluated_s_;

    uint32_t  sl_spline_order_        = 4;
    float64_t sl_spline_length_       = 10;
    float64_t sl_constraint_interval_ = 0.5;
    float64_t sl_dl_constraint_       = 1;
    float64_t sl_ddl_constraint_      = 0.5;
    float64_t sl_dddl_constraint_     = 0.05;
    float64_t smooth_length_          = 15.0;
    float64_t smooth_step_            = 0.1;
};

}  // namespace planning
}  // namespace holo

#endif  // _SPLINE_1D_SMOOTH_
