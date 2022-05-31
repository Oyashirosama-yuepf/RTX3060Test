/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pullingoutbase.h
 * @brief the base of vertical & parallel pullingout
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-16
 */

#ifndef _PULLINGBASE_H_
#define _PULLINGBASE_H_

#include <holo/hpp/parkingplan/commonfunction.h>
#include <holo/hpp/parkingplan/parkingpath.h>
#include <holo/hpp/parkingplan/samplingpathplan.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
/**
 * @brief  main class of pullingout path plan
 *
 * @details a important class, which includes pullingout state decision
 * and pullingout path plan
 */
class PullingOutBase
{
public:
    /**
     * @brief constructor
     */
    PullingOutBase()
    {
    }

    /**
     * @brief destroys the object
     */
    ~PullingOutBase() = default;

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
     */
    void Init(std::vector<std::vector<geometry::Point2>> const* tm_freespace_,
              common::ChassisState const*                       tm_chassis_state_,
              bool_t const&                                     tm_replan_recommended_,
              float64_t                                         tm_desiredspeed,
              OperateState*                                     tm_parking_operatestate_,
              PathData*                                         tm_current_path_,
              SingleParkingLot*                                 tm_current_parkinglot_,
              std::vector<CurvePoint> const*                    tm_reference_line_,
              int8_t const&                                     tm_pullout_dir_,
              std::shared_ptr<std::vector<CurvePoint>>          tm_global_plan_path_);

    /**
     * @brief cycle run pullingout process management
     *
     * @details pullingout process management including decision making and path planning
     */
    virtual void RunOnce() = 0;

protected:
    std::vector<std::vector<geometry::Point2>> const* freespace_               = nullptr;
    common::ChassisState const*                       chassis_state_           = nullptr;
    bool_t                                            replan_recommended_      = false;
    OperateState*                                     parking_operatestate_    = nullptr;
    PathData*                                         current_path_            = nullptr;
    SingleParkingLot*                                 current_parkinglot_      = nullptr;
    int32_t                                           pullout_dir_             = 0;
    float64_t                                         desiredspeed_            = 0.0;
    float64_t                                         path_interval_threshold_ = 0.2;
    std::vector<CurvePoint>                           reference_line_;
    CollisionChecker                                  collision_checker_;
    std::shared_ptr<std::vector<CurvePoint>>          global_plan_path_ = std::make_shared<std::vector<CurvePoint>>();
    ParkingPath      parking_path_;        ///< parking and pulling out path planning method class
    SamplingPathPlan sampling_path_plan_;  ///< class provides sampling method
    /**
     * @brief what to do when complete pullingout
     */
    virtual void CompletePullOut() = 0;

    /**
     * @brief  set path data
     *
     * @param[in] gpath PathData struct to be assigned
     * @param[in] path  path used for assignment
     */
    void SetPathData(PathData* gpath, std::vector<CurvePoint>& path);

    /**
     * @brief  stop car order
     */
    void StopCar();
};

}  // namespace planning
}  // namespace holo

#endif