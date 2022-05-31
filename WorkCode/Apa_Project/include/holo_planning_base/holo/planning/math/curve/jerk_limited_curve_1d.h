/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file jerk_limited_curve_1d.h
 * @brief the header of the Jerk Limited Curve 1d
 * @author wangchantong(wangchantong@holomatic.com)
 * @date 2020-09-28
 */

#ifndef _HOLO_PLANNING_MATH_JERK_LIMITED_CURVE_1D_H_
#define _HOLO_PLANNING_MATH_JERK_LIMITED_CURVE_1D_H_

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
 * @brief  JerkLimitedCurve1d is second-order integral model with target velocity, limited jerk and unlimited pos.
 *         Solve Boundary Value Problem by given [v_initial, acc_initial] to [v_target, 0].
 *
 *         Main application:
 *         (1) Obtain sampling reasonable region when sampling based method is used;
 *         (2) Used as Task state switch condition of Hierarchical Model;
 *         (3) A normal feasible connection of two given state.
 */
class JerkLimitedCurve1d : public Curve1d
{
public:
    /**
     * @brief The default constructor of Jerk-Limited Curve1d.
     */
    JerkLimitedCurve1d() = default;

    /**
     * @brief The constructor of Jerk-Limited Curve1d.
     *
     * @param start The current state.
     * @param target_velocity The target velocity.
     * @param limited_jerk The maximum jerk.
     * @param max_velocity The maximum velocity.
     * @param min_velocity The minimum velocity.
     * @param max_acceleration The maximum acceleration.
     * @param min_acceleration The minimum acceleration.
     *
     */
    JerkLimitedCurve1d(std::array<float64_t, 3> const& start,
                       float64_t const                 target_velocity,
                       float64_t const                 limited_jerk,
                       float64_t const                 max_velocity,
                       float64_t const                 min_velocity,
                       float64_t const                 max_acceleration,
                       float64_t const                 min_acceleration);

    /**
     * @brief The constructor of Jerk-Limited Curve1d.
     *
     * @param p0 The current position.
     * @param v0 The current velocity.
     * @param a0 The current acceleration.
     * @param target_velocity The target velocity.
     * @param limited_jerk The maximum jerk.
     * @param max_velocity The maximum velocity.
     * @param min_velocity The minimum velocity.
     * @param max_acceleration The maximum acceleration.
     * @param min_acceleration The minimum acceleration.
     */
    JerkLimitedCurve1d(float64_t const p0,
                       float64_t const v0,
                       float64_t const a0,
                       float64_t const target_velocity,
                       float64_t const limited_jerk,
                       float64_t const max_velocity,
                       float64_t const min_velocity,
                       float64_t const max_acceleration,
                       float64_t const min_acceleration);
    /**
     * @brief Destroy the Jerk-Limited Curve1d object.
     */
    virtual ~JerkLimitedCurve1d() = default;

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
     * @return The totol time of three periods of time in JLC.
     */
    virtual float64_t ParamLength() const;

    /**
     * @brief Curve1d to string.
     *
     * @return string.
     */
    virtual std::string String() const;

    /**
     * @brief Get calculated three section time.
     */
    std::array<float64_t, 3> GetSectionTime() const
    {
        return sections_time_;
    }

    /**
     * @brief Reset calculated curve and flag.
     */
    void Reset()
    {
        solved_ = false;
        sections_time_.fill(0.0);
        jerk_limited_curve_.clear();
    }

protected:
    /**
     * @brief Tuning initial state according to velocity and acceleration boundary.
     */
    void tuningInitialState();

    /**
     * @brief Calculate the Jerk-Limited Curve.
     *
     * @param current_vel The current velocity.
     * @param current_acc The current acceleration.
     */
    void calculateTrajectory(float64_t const& current_vel, float64_t const& current_acc);

    /**
     * @brief Determine the jerk direction in section one.
     *
     * @param vel The velocity.
     * @param acc The acceleration.
     *
     * @return The direction of jerk. [-1] means negative, [+1] means positve.
     */
    float64_t computeJerkDirection(float64_t const& vel, float64_t const& acc) const;

    /**
     * @brief Calculate velocity when acc reaches zero, according to initial jerk direction.
     *
     * @param vel The velocity.
     * @param acc The acceleration.
     *
     * @return The velocity when accleration reaches zero.
     */
    float64_t calculateVelocityWhenAccReachZero(float64_t const& vel, float64_t const& acc) const;

    /**
     * @brief Calculate Three Period of time in Jerk-Limited curve.
     *
     * @param direction The jerk direction in section one.
     * @param vel The velocity.
     * @param acc The acceleration.
     *
     * @return The velocity when accleration reaches zero.
     */
    std::array<float64_t, 3> calculateMinimumTotalTime(float64_t const& direction,
                                                       float64_t const& vel,
                                                       float64_t const& acc) const;

    /**
     * @brief Calculate Time of Section One in Jerk-Limited curve.
     *
     * @param vel The velocity.
     * @param acc The acceleration.
     * @param jerk The jerk with direction.
     *
     * @return The time of section one.
     */
    float64_t calculateSectionOneTime(float64_t const& vel, float64_t const& acc, float64_t const& jerk) const;

    /**
     * @brief Adjust Section One time according to maximum and minimum acceleration limits.
     *
     * @param acc The acceleration.
     * @param jerk The jerk with direction.
     * @param time_adjust The Section one time after adjusting.
     *
     * @return The velocity when accleration reaches zero.
     */
    void limitAmplitudeAcceleration(float64_t const& acc, float64_t const& jerk, float64_t& time_adjust) const;

    /**
     * @brief Calculate Time of Section Two in Jerk-Limited curve.
     *
     * @param vel The velocity.
     * @param acc The acceleration.
     * @param jerk The jerk with direction.
     * @param time_section_one The time of section one.
     * @param time_section_three The time of section three.
     *
     * @return The time of section two.
     */
    float64_t calculateSectionTwoTime(float64_t const& vel,
                                      float64_t const& acc,
                                      float64_t const& jerk,
                                      float64_t const& time_section_one,
                                      float64_t const& time_section_three) const;

    /**
     * @brief Calculate Time of Section Three in Jerk-Limited curve.
     *
     * @param acc The acceleration.
     * @param jerk The jerk with direction.
     * @param time_section_one The time of section one.
     *
     * @return The time of section three.
     */
    float64_t calculateSectionThreeTime(float64_t const& acc,
                                        float64_t const& jerk,
                                        float64_t const& time_section_one) const;

    /**
     * @brief Generate whole trajectory according to calculated section times and jerk direction.
     */
    void generateTrajectory();

    /**
     * @brief Calculate Time of Section Three in Jerk-Limited curve.
     *
     * @param state The state contains [0] timestamp; [1] position; [2] velocity; [3] acceleration; [4] jerk.
     * @param dt The derivate time.
     * @param direction The direction of jerk in Section One.
     */
    void evaluateIntegralModel(std::array<float64_t, 5>& state, float64_t const& dt, float64_t const& direction) const;

protected:
    bool_t solved_;  // false : BVP unsolved ; true : whole curve was obtained

    float64_t position_initial_;      // initial position
    float64_t velocity_initial_;      // initial velocity
    float64_t acceleration_initial_;  // initial acceleration
    float64_t velocity_target_;       // target velocity

    float64_t const max_jerk_;         // comfort or emergency;
    float64_t const max_velocity_;     // maximum velocity
    float64_t const min_velocity_;     // minimum velocity
    float64_t const max_accleration_;  // maximum acceleration
    float64_t const min_accleration_;  // minimum accleration

    float64_t const time_deriavte_ = 0.0025;  // dt used in integration
    float64_t const time_interval_ = 0.05;    // record time interval
    float64_t const time_horizon_  = 10.0;    // the maximum time range

    std::array<float64_t, 3> sections_time_{{0.0, 0.0, 0.0}};  // three period of time in Jerk-Limited Curve

    // [0] timestamp; [1] position; [2] velocity; [3] acceleration; [4] jerk.
    std::vector<std::array<float64_t, 5>> jerk_limited_curve_;
};
}  // namespace math
}  // namespace planning
}  // namespace holo

#endif