/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file end_condition_sampler.h
 * @brief the header of the end condition sampler in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_END_CONDITION_SAMPLER_H_
#define _HOLO_PLANNING_LATTICE_END_CONDITION_SAMPLER_H_

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/common/plan_route.h>
#include <holo/planning/planner/lattice/constraint_checker.h>
#include <holo/planning/planner/lattice/lattice_constant.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Class for sample lon and lat curve end conditions
 */
class EndConditionSampler
{
public:
    using ObstacleList                = std::vector<std::shared_ptr<ObstacleInfo>>;
    using State                       = std::array<float64_t, 3>;
    using Condition                   = std::pair<State, float64_t>;
    using PredictedBoxesTrajectoryPtr = std::shared_ptr<std::vector<std::vector<NormalBox>>>;
    using ConstraintPtr               = std::shared_ptr<LatticeConstraint>;
    /**
     * @brief Construct a new End Condition Sampler object
     *
     * @param init_s initial longitudinal frenet state
     * @param init_l initial lateral frenet state
     * @param boxes_trajectory_ptr pointer of predicted obstacles trajectory boxs
     * @param constraint_ptr pointer of constraint
     * @param enable_avoid_in_lane switch of avoid in lane
     */
    EndConditionSampler(const State&                       init_s,
                        const State&                       init_l,
                        const PredictedBoxesTrajectoryPtr& boxes_trajectory_ptr,
                        const ConstraintPtr&               constraint_ptr,
                        bool_t                             enable_avoid_in_lane);

    /**
     * @brief Destroy the End Condition Sampler object
     */
    ~EndConditionSampler() = default;

    /**
     * @brief sample longitudinal frenet end conditions for cruising
     *
     * @param ref_speed reference longitudinal speed
     * @param LonEndConditions vector to save longitudinal end conditions
     */
    void SampleLonEndConditionsForCruising(float64_t ref_speed, std::vector<Condition>& LonEndConditions) const;

    /**
     * @brief sample longitudinal frenet end conditions for stopping
     *
     * @param stop_s longitudinal distance to stop point, [0.0 - 500.0] is valid value, other values mean no certain
     *               stop point
     * @param LonEndConditions vector to save longitudinal end conditions
     */
    void SampleLonEndConditionsForStopping(float64_t stop_s, std::vector<Condition>& LonEndConditions) const;

    /**
     * @brief sample longitudinal frenet end conditions for following obstacle
     *
     * @param obs_list obstacle pointer list
     * @param ref_speed reference longitudinal speed
     * @param LonEndConditions vector to save longitudinal end conditions
     */
    void SampleLonEndConditionsForFollowing(const ObstacleList&     obs_list,
                                            float64_t               ref_speed,
                                            std::vector<Condition>& LonEndConditions) const;

    /**
     * @brief sample longitudinal frenet end conditions for following obstacle
     *
     * @param ref_speed reference longitudinal speed
     * @param LonEndConditions vector to save longitudinal end conditions
     * @param ego_box the ego car box
     * @param headway_time the headway time
     */
    void SampleLonEndConditionsForFollowing(float64_t               ref_speed,
                                            std::vector<Condition>& LonEndConditions,
                                            NormalBox const&        ego_box,
                                            float64_t               headway_time) const;

    /**
     * @brief sample lateral frenet end conditions
     *
     * @param LatEndConditions vector to save lateral end conditions
     * @param road_width road width
     * @param vehcile_width ego car width
     */
    void SampleLatEndConditions(std::vector<Condition>& LatEndConditions,
                                float64_t               road_width,
                                float64_t               vehicle_width) const;

private:
    /**
     * @brief calculate upper speed
     *
     * @param t the time
     *
     * @return float64_t upper speed according to time
     */
    inline float64_t CalVUpper(float64_t t) const noexcept
    {
        return init_s_[1] + constraint_ptr_->lon_acc_upper_bound * t;
    }

    /**
     * @brief calculate lower speed
     *
     * @param t the time
     *
     * @return float64_t lower speed according to time
     */
    inline float64_t CalVLower(float64_t t) const noexcept
    {
        const float64_t v_lower = init_s_[1] + constraint_ptr_->lon_acc_lower_bound * t;
        return v_lower > 0.0 ? v_lower : 0.0;
    }

    /**
     * @brief calculate upper distance
     *
     * @param t the time
     *
     * @return float64_t upper distance accordint to time
     */
    inline float64_t CalSUpper(float64_t t) const noexcept
    {
        return init_s_[0] + init_s_[1] * t + 0.5 * constraint_ptr_->lon_acc_upper_bound * t * t;
    }

    /**
     * @brief calculate lower distance
     *
     * @param t the time
     *
     * @return float64_t lower distance accordint to time
     */
    inline float64_t CalSLower(float64_t t) const noexcept
    {
        float64_t t_at_zero_speed = 0.0 - init_s_[1] / constraint_ptr_->lon_acc_lower_bound;
        if (t > t_at_zero_speed)
        {
            return init_s_[0] + init_s_[1] * init_s_[1] / (2.0 * constraint_ptr_->lon_acc_lower_bound);
        }
        else
        {
            return init_s_[0] + init_s_[1] * t + 0.5 * constraint_ptr_->lon_acc_lower_bound * t * t;
        }
    }

    /**
     * @brief initial longitudinal frenet state
     */
    State init_s_;

    /**
     * @brief initial lateral frenet state
     */
    State init_l_;

    /**
     * @brief pointer of predicted obstacles' trajectory
     */
    PredictedBoxesTrajectoryPtr boxes_trajectory_ptr_;

    /**
     * @brief pointer of constraint
     */
    ConstraintPtr constraint_ptr_;

    /**
     * @brief switch of avoid in lane
     */
    bool_t enable_avoid_in_lane_;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif