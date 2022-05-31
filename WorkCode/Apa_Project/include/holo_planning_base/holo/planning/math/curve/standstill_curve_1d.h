/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file standstill_curve_1d.h
 * @brief the header of the standstill Curve 1d
 * @author wangchantong(wangchantong@holomatic.com)
 * @date 2020-09-28
 */

#ifndef _HOLO_PLANNING_MATH_STANDSTILL_CURVE_1D_H_
#define _HOLO_PLANNING_MATH_STANDSTILL_CURVE_1D_H_

#include <holo/planning/common/headers.h>
#include <holo/planning/math/curve/curve_1d.h>

#include <math.h>
#include <algorithm>
#include <array>
#include <vector>

namespace holo
{
namespace planning
{
namespace math
{
/**
 * @brief  StandstillCurve1d used in stop&go
 */
class StandstillCurve1d : public Curve1d
{
public:
    /**
     * @brief The default constructor of Standstill Curve1d.
     */
    StandstillCurve1d() = default;

    /**
     * @brief The constructor of Standstill Curve1d.
     *
     * @param start The current state.
     * @param target_velocity The target velocity.
     * @param target_acceleration The target acceleration.
     * @param target_jerk The target jerk.
     *
     */
    StandstillCurve1d(std::array<float64_t, 3> const& start,
                      float64_t const                 target_velocity,
                      float64_t const                 target_acceleration,
                      float64_t const                 target_jerk);

    /**
     * @brief The constructor of Standstill Curve1d.
     *
     * @param p0 The current position.
     * @param v0 The current velocity.
     * @param a0 The current acceleration.
     * @param target_velocity The target velocity.
     * @param target_acceleration The target acceleration.
     * @param target_jerk The target jerk.
     */
    StandstillCurve1d(float64_t const p0,
                      float64_t const v0,
                      float64_t const a0,
                      float64_t const target_velocity,
                      float64_t const target_acceleration,
                      float64_t const target_jerk);
    /**
     * @brief Destroy the Standstill Curve1d object.
     */
    virtual ~StandstillCurve1d() = default;

    /**
     * @brief Calculate the value in specific parameter and order.
     *
     * @param order The order.
     * @param p The parameter.
     */
    virtual float64_t Evaluate(uint32_t const order, float64_t const p) const override;

    /**
     * @brief The total time.
     *
     * @return The totol time.
     */
    virtual float64_t ParamLength() const;

    /**
     * @brief Curve1d to string.
     *
     * @return string.
     */
    virtual std::string String() const;

    /**
     * @brief Reset calculated curve and flag.
     */
    void Reset()
    {
        solved_ = false;
        standstill_curve_.clear();
    }

protected:
    /**
     * @brief Generate whole trajectory according to jerk direction.
     */
    void generateTrajectory();

protected:
    bool_t solved_ = false;  // false : unsolved ; true : whole curve was obtained

    float64_t const position_initial_;      // initial position
    float64_t const velocity_initial_;      // initial velocity
    float64_t const acceleration_initial_;  // initial acceleration
    float64_t const velocity_target_;       // target velocity
    float64_t const acceleration_target_;   // target acceleration
    float64_t const jerk_target_;           // target jerk

    float64_t const time_interval_ = 0.5;   // record time interval
    float64_t const time_horizon_  = 10.0;  // the maximum time range

    // [0] timestamp; [1] position; [2] velocity; [3] acceleration; [4] jerk.
    std::vector<std::array<float64_t, 5>> standstill_curve_;
};
}  // namespace math
}  // namespace planning
}  // namespace holo

#endif