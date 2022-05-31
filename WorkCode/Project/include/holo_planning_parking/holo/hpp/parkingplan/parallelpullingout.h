/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parallelpullingout.h
 * @brief the class of parallel pullingout
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-07-12
 */

#ifndef _PARALLELPULLINGOUT_H_
#define _PARALLELPULLINGOUT_H_

#include <holo/hpp/parkingplan/pullingoutbase.h>
#include <holo/planning/planner/hybrid_astar/hybrid_a_star.h>
#include <array>
#include <functional>

namespace holo
{
namespace planning
{
/**
 * @brief  main class of parallellot pullingout path plan
 *
 * @details a class, which includes parallellot pullingout state decision
 * and parallellot pullingout path plan
 */
class ParallelPullingOut : public PullingOutBase
{
public:
    /**
     * @brief constructor.
     */
    ParallelPullingOut()
      : vehicle_cfg_(config::HppConfigHelper::GetHppCfg().vehicle_cfg)
      , hybrid_astar_cfg_(config::HppConfigHelper::GetHppCfg().hybrid_astar_cfg)
    {
    }

    /**
     * @brief destroys the object.
     */
    ~ParallelPullingOut() = default;

    /**
     * @brief init input
     *
     * @param[in] tm_freespace_ freespace
     * @param[in] tm_chassis_state_ parkinglot
     * @param[in] tm_replan_recommended_ replan recommended order according to collision distance warning
     * @param[in] tm_desiredspeed desired speed calculated by outer module
     * @param[in] tm_parkingoperatestate_ paring status
     * @param[in] tm_current_path_ current path from last cycle
     * @param[in] tm_current_parkinglot_ current parklot after handling
     * @param[in] tm_reference_line_ reference path for pulling out
     * @param[in] tm_pullout_dir pullingout direction
     * @param[in] tm_global_plan_path_ global plan path for pullingout
     * @param[in] tm_hybridastar_paths_ hybrid a star plan paths for pullingout
     */
    void Init(std::vector<std::vector<geometry::Point2>> const*     tm_freespace_,
              common::ChassisState const*                           tm_chassis_state_,
              bool_t const&                                         tm_replan_recommended_,
              float64_t                                             tm_desiredspeed,
              OperateState*                                         tm_parking_operatestate_,
              PathData*                                             tm_current_path_,
              SingleParkingLot*                                     tm_current_parkinglot_,
              std::vector<CurvePoint> const*                        tm_reference_line_,
              int8_t const&                                         tm_pullout_dir_,
              std::shared_ptr<std::vector<CurvePoint>>              tm_global_plan_path_,
              std::shared_ptr<std::vector<std::vector<CurvePoint>>> tm_hybridastar_paths_);
    /**
     * @brief cycle run
     *
     * @details parallellot pullingout process management
     */
    void RunOnce() override;

    /**
     * @brief get global path for parallellot pullingout
     *
     * @param[out] path global path for parallellot pullingout
     */
    void GetGlobalPlanPath(std::vector<CurvePoint>& path);

    /**
     * @brief get hybridastar path for parallellot pullingout
     *
     * @param[out] path hybridastar path for parallellot pullingout
     */
    void GetHybridAStarPath(std::vector<std::vector<CurvePoint>>& path);

    /**
     * @brief reset used variables
     */
    void Reset4Next();

private:
    /**
     * @brief generate global path for parallellot pullingout
     *
     * @param[in] reference_line reference path for pulling out
     * @param[out] pullout_path global path for parallellot pullingout
     */
    void GenerateGlobalPathForPullOut(std::vector<CurvePoint> const& reference_line,
                                      std::vector<CurvePoint>&       pullout_path);

    /**
     * @brief generate global path for parallellot pullingout
     *
     * @param[in] start start pose
     * @param[in] end end pose
     * @param[in] speed real speed
     * @param[out] ha_paths hybrid a star paths for parallellot pullingout
     * @param[out] ha_directions hybrid a star directions for parallellot pullingout
     */
    bool_t hybridAStar(geometry::Pose2 const&                start,
                       geometry::Pose2 const&                end,
                       float64_t                             speed,
                       std::vector<std::vector<CurvePoint>>& ha_paths,
                       std::vector<bool_t>&                  ha_directions);

    /**
     * @brief ready for pullout
     */
    void ExcuteReadyForPullOut()
    {
    }

    /**
     * @brief first backward adjustment for parallellot pullingout
     */
    void ExcuteFirstBackwardAdjust();

    /**
     * @brief forward adjustment for parallellot pullingout
     */
    void ExcuteForwardAdjust();

    /**
     * @brief backward adjustment for parallellot pullingout
     */
    void ExcuteBackwardAdjust();

    /**
     * @brief pull out failed
     */
    void PullOutFailed();

    /**
     * @brief pull out complete
     */
    void CompletePullOut() override;

    /**
     * @brief excute hybrid a star search path
     */
    void ExcuteHybridAStarSearch();

    /**
     * @brief  reason ready for pullout
     */
    void ReasonReadyForPullOut();

    /**
     * @brief reason first backward adjustment for parallellot pullingout
     */
    void ReasonFirstBackwardAdjust();

    /**
     * @brief reason forward adjustment for parallellot pullingout
     */
    void ReasonForwardAdjust();

    /**
     * @brief reason backward adjustment for parallellot pullingout
     */
    void ReasonBackwardAdjust();

    /**
     * @brief reason pull out complete
     */
    void ReasonCompletePullOut()
    {
    }

    /**
     * @brief reason pull out failed
     */
    void ReasonPullOutFailed()
    {
    }

    /**
     * @brief reason hybrid a star search path
     */
    void ReasonHybridAStarSearch();

    /**
     * @brief whether forward limited
     */
    bool_t IsForwardLimited();

    /**
     * @brief whether backward limited
     */
    bool_t IsBackwardLimited();

private:
    bool_t  is_first_backward_adjust_  = true;  ///< whether first backward adjustment
    int32_t pull_out_backward_counter_ = 0;     ///< counter of the number of backward

    float64_t    distance_parallelpullout_  = 0;  ///< parallel pullout retreat distance
    unsigned int forward_obstacle_counter_  = 0;  ///< counter when there is forward obstacle
    unsigned int backward_obstacle_counter_ = 0;  ///< counter when there is backward obstacle

    bool_t using_hybridastarplan_ = true;
    bool_t using_fsm_             = true;

    /// hybrid a star
    bool_t is_first_cal_hybridastar_ = true;  ///< whether first calculate target point for hybrid a star path plan
    std::shared_ptr<std::vector<std::vector<CurvePoint>>> hybridastar_paths_ =
        std::make_shared<std::vector<std::vector<CurvePoint>>>();
    std::vector<bool_t>                  hybridastar_directions_;
    int32_t                              target_reference_index_ = -1;
    std::vector<std::vector<CurvePoint>> ha_paths_;
    std::vector<bool_t>                  ha_directions_;
    size_t                               ha_current_index_;

    config::VehicleConfig const&     vehicle_cfg_;
    config::HybridAstarConfig const& hybrid_astar_cfg_;

    /// planner param
    float64_t smooth_step_             = 0.025;
    float64_t max_speed_tolerance_     = 0.005;
    float64_t max_path_length_         = 20;  ///< original 5.0 because container has limited capacity like 256
    float64_t max_path_size_tolerance_ = 10;  ///< 10 * 0.025 = 0.25, max distance tolerance to the end of current phase

    enum class ParallelPullingOutState
    {
        READY_FOR_PULLOUT,
        FIRST_BACKWARD,
        FORWARD_SEARCH,
        BACKWARD_ADJUST,
        PULLOUT_COMPLETE,
        PULLOUT_FAILED,
        HYBRIDASTAR_SEARCH
    };
    ParallelPullingOutState current_status_ = ParallelPullingOutState::READY_FOR_PULLOUT;
    /// state function binding definition to eliminate switch-case operation
    using StatesExcuteFunc = std::array<std::function<void()>, 7>;

    StatesExcuteFunc ExcuteFunc = {{std::bind(&ParallelPullingOut::ExcuteReadyForPullOut, this),
                                    std::bind(&ParallelPullingOut::ExcuteFirstBackwardAdjust, this),
                                    std::bind(&ParallelPullingOut::ExcuteForwardAdjust, this),
                                    std::bind(&ParallelPullingOut::ExcuteBackwardAdjust, this),
                                    std::bind(&ParallelPullingOut::CompletePullOut, this),
                                    std::bind(&ParallelPullingOut::PullOutFailed, this),
                                    std::bind(&ParallelPullingOut::ExcuteHybridAStarSearch, this)}};

    using StatesReasonFunc = std::array<std::function<void()>, 7>;

    StatesReasonFunc ReasonFunc = {{std::bind(&ParallelPullingOut::ReasonReadyForPullOut, this),
                                    std::bind(&ParallelPullingOut::ReasonFirstBackwardAdjust, this),
                                    std::bind(&ParallelPullingOut::ReasonForwardAdjust, this),
                                    std::bind(&ParallelPullingOut::ReasonBackwardAdjust, this),
                                    std::bind(&ParallelPullingOut::ReasonCompletePullOut, this),
                                    std::bind(&ParallelPullingOut::ReasonPullOutFailed, this),
                                    std::bind(&ParallelPullingOut::ReasonHybridAStarSearch, this)}};
};

}  // namespace planning
}  // namespace holo

#endif
