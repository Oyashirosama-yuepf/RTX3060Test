/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file const_absolute_jerk_planner.h
 * @brief the header of the const absolute-jerk planner
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef MODULES_PLANNING_PLANNER_LONGITUDINAL_CONST_ABSOLUTE_JERK_PLANNER_H_
#define MODULES_PLANNING_PLANNER_LONGITUDINAL_CONST_ABSOLUTE_JERK_PLANNER_H_

#include <array>
#include <vector>

#include <holo/core/types.h>

namespace holo
{
namespace planning
{
/**
 * @brief a longitudinal planner which has a const absolute-jerk.
 */
class ConstAbsoluteJerkPlanner
{
public:
    /**
     * @brief the constarint of the ConstAbsoluteJerkPlanner
     */
    struct ConstraintParam
    {
        float32_t min_velocity;      ///< the minimum velocity during the whole process, it should be set by user
        float32_t max_velocity;      ///< the maximum velocity during the whole process, it should be set by user
        float32_t default_abs_jerk;  ///< the default value of abs_jerk
        float32_t abs_jerk_step;     ///< the abs_jerk's step value
        float32_t max_abs_jerk;      ///< the maximum value of abs_jerk, it's the vehicle's parameter
        float32_t max_acc;           ///< the maximum value of accerlation, it's the vehicle's parameter
        float32_t min_acc;           ///< the minimum value of accerlation, it's the vehicle's parameter
        float32_t max_distance;      ///< the maximum value of distance, it should be set by user
        float32_t min_distance;      ///< the minimum value of distance, it should be set by user
    };

public:
    /**
     * @brief solve the problem
     *
     * @param a0 The start-state's acceleration.
     * @param v0 The start-state's velocity.
     * @param a1 The end-state's acceleration.
     * @param v1 The end-state's velocity.
     * @param param The the constarint of the ConstAbsoluteJerkPlanner
     *
     * @return true if planner work successfully, false otherwise
     */
    bool_t Solve(float32_t a0, float32_t v0, float32_t a1, float32_t v1, const ConstraintParam& param);

    /**
     * @brief generate the whole process from (a0, v0) to (a1, v1)
     *
     * @param[in] time_step The time-margin between two point
     * @param[out] target_point_series The vector of the dynamic state which is made up by (a, v, s).
     */
    void GenerateWholeProcessByTimeStep(float32_t                              time_step,
                                        std::vector<std::array<float64_t, 3>>& target_point_series) const;

    /**
     * @brief calculate acceleration during the whole process at time t
     *
     * @param t The time is going to be used to calculate acceleration.
     *
     * @return The acceleration at time t.
     */
    float32_t CalcAcc(float32_t t) const noexcept;

    /**
     * @brief calculate velocity during the whole process at time t
     *
     * @param t The time is going to be used to calculate velocity.
     *
     * @return The velocity at time t.
     */
    float32_t CalcVel(float32_t t) const noexcept;

    /**
     * @brief calculate distance during the whole process at time t
     *
     * @param t The time is going to be used to calculate distance.
     *
     * @return The distance at time t.
     */
    float32_t CalcDist(float32_t t) const noexcept;

    /**
     * @brief Get the whole process's time length
     *
     * @return The whole process's time length.
     */
    float32_t GetProsessTime() const noexcept
    {
        return section_3_end_time_;
    }

    /**
     * @brief Get the whole process's distance
     *
     * @return The whole process's distance.
     */
    float32_t GetProsessDist() const noexcept
    {
        return CalcDist(section_3_end_time_);
    }

    /**
     * @brief Get the section1's jerk
     *
     * @return the section1's jerk
     */
    float32_t GetSection1Jerk() const noexcept
    {
        return alpha_;
    }

public:
    /**
     * @brief Get the start-state's acc
     *
     * @return the start-state's acc
     */
    float32_t GetStartStateAcc() const noexcept
    {
        return start_state_acc_;
    }

    /**
     * @brief Get the start-state's vel
     *
     * @return the start-state's vel
     */
    float32_t GetStartStateVel() const noexcept
    {
        return start_state_vel_;
    }

    /**
     * @brief Get the end-state's acc
     *
     * @return the end-state's acc
     */
    float32_t GetEndStateAcc() const noexcept
    {
        return end_state_acc_;
    }

    /**
     * @brief Get the end-state's vel
     *
     * @return the end-state's vel
     */
    float32_t GetEndStateVel() const noexcept
    {
        return end_state_vel_;
    }

    /**
     * @brief Get the constraint parameters
     *
     * @return the constraint parameters
     */
    const ConstraintParam& GetConstraintParam() const noexcept
    {
        return constraint_param_;
    }

private:
    /**
     * @brief check the solution can satisfied with the given constraints in 2Sections' form
     *
     * @param t1 The time of section 1, it describes part of the solution.
     * @param is_1st_section_positive_jerk The flag which shows whether section 1's jerk is positive or negative.
     * @param abs_jerk The absolute-jerk, it describes part of the solution.
     *
     * @return true if the solution can be satisfied with all constraints, false otherwise.
     */
    bool_t CheckAllConstraintInForm2Section(float32_t t1, bool_t is_1st_section_positive_jerk, float32_t abs_jerk) const
        noexcept;

    /**
     * @brief check the solution can be satisfied with the velocity constraints in 2Sections' form
     *
     * @param t1 The time of section 1, it describes part of the solution.
     * @param is_1st_section_positive_jerk The flag which shows whether section 1's jerk is positive or negative.
     * @param abs_jerk The absolute-jerk, it describes part of the solution.
     *
     * @return true if the solution can be satisfied with the velocity constraints, false otherwise.
     */
    bool_t CheckVelConstraint(float32_t t1, bool_t is_1st_section_positive_jerk, float32_t abs_jerk) const noexcept;

    /**
     * @brief check the solution can be satisfied with the distance constraints in 2Sections' form
     *
     * @param t1 The time of section 1, it describes part of the solution.
     * @param is_1st_section_positive_jerk The flag which shows whether section 1's jerk is positive or negative.
     * @param abs_jerk The absolute-jerk, it describes part of the solution.
     *
     * @return true if the solution can be satisfied with the distance constraints, false otherwise.
     */
    bool_t CheckDistConstraint(float32_t t1, bool_t is_1st_section_positive_jerk, float32_t abs_jerk) const noexcept;

    /**
     * @brief check the solution can be satisfied with the accerlation constraints in 2Sections' form
     *
     * @return true if the solution can be satisfied with the distance constraints, false otherwise.
     */
    bool_t CheckAccConstraint() const noexcept;

private:
    /**
     * @brief solve the problem with abs_jerk
     *
     * @param abs_jerk The input jerk's absolute value.
     *
     * @return true if the problem can be solved with abs_jerk, false otherwise.
     */
    bool_t SolveWithInputAbsJerk(float32_t abs_jerk);

    /**
     * @brief calculate the time length of section 1&2 by using alpha and t1 in 2Sections' form
     *
     * @param alpha The jerk of section 1.
     * @param t1 The time length of section 1.
     *
     * @return the time length of section 1&2
     */
    float32_t CalcT2Root(float32_t alpha, float32_t t1) const noexcept;

    /**
     * @brief calculate the accerlation of section 1 at time t in 2Sections' form
     *
     * @param alpha The jerk of section 1.
     * @param t1 The time length of section 1.
     * @param t The input time.
     *
     * @return the accerlation of section 1 at time t
     */
    float32_t CalcAccSection1(float32_t alpha, float32_t t1, float32_t t) const noexcept;

    /**
     * @brief calculate the velocity of section 1 at time t in 2Sections' form
     *
     * @param alpha The jerk of section 1.
     * @param t1 The time length of section 1.
     * @param t The input time.
     *
     * @return the velocity of section 1 at time t
     */
    float32_t CalcVelSection1(float32_t alpha, float32_t t1, float32_t t) const noexcept;

    /**
     * @brief calculate the distance of section 1 at time t in 2Sections' form
     *
     * @param alpha The jerk of section 1.
     * @param t1 The time length of section 1.
     * @param t The input time.
     *
     * @return the distance of section 1 at time t
     */
    float32_t CalcDistSection1(float32_t alpha, float32_t t1, float32_t t) const noexcept;

    /**
     * @brief calculate the velocity of section 2 at time t in 2Sections' form
     *
     * @param alpha The jerk of section 2.
     * @param t1 The time length of section 1.
     * @param t The input time.
     *
     * @return the velocity of section 2 at time t
     */
    float32_t CalcVelSection2(float32_t alpha, float32_t t1, float32_t t) const noexcept;

    /**
     * @brief calculate the distance of section 2 at time t in 2Sections' form
     *
     * @param alpha The jerk of section 2.
     * @param t1 The time length of section 2.
     * @param t The input time.
     *
     * @return the distance of section 2 at time t
     */
    float32_t CalcDistSection2(float32_t alpha, float32_t t1, float32_t t) const noexcept;

    /**
     * @brief change the solution's form into 3Sections form
     *
     * @param alpha The jerk of section 2.
     * @param t1 The time length of section 1 in form of 2Sections.
     *
     * @return the solution in 3Sections' form can satisfied with the constants, false otherwise
     */
    bool_t ChangeFormInto3Sections(float32_t alpha, float32_t t1);

private:
    /**
     * @brief The parameter of constraint.
     */
    ConstraintParam constraint_param_;

    /**
     * @brief The end time of Section1.
     */
    float32_t section_1_end_time_;

    /**
     * @brief The end time of Section2.
     */
    float32_t section_2_end_time_;

    /**
     * @brief The end time of Section3.
     */
    float32_t section_3_end_time_;

    /**
     * @brief The jerk of curve_1_.
     */
    float32_t alpha_;

    /**
     * @brief The start-state's acceleration
     */
    float32_t start_state_acc_;

    /**
     * @brief The start-state's velocity
     */
    float32_t start_state_vel_;

    /**
     * @brief The end-state's acceleration
     */
    float32_t end_state_acc_;

    /**
     * @brief The end-state's velocity
     */
    float32_t end_state_vel_;
};

}  // namespace planning
}  // namespace holo

#endif  // MODULES_PLANNING_PLANNER_LONGITUDINAL_CONST_ABSOLUTE_JERK_PLANNER_H_
