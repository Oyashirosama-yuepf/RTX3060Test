/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parkingbase.h
 * @brief the base of vertical & parallel parking
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-12
 */

#ifndef _PARKINGBASE_H_
#define _PARKINGBASE_H_

#include <holo/hpp/parkingplan/common_struct_type.h>
#include <holo/hpp/parkingplan/parkingpath.h>
#include <holo/planning/common/hpp_param.h>

namespace holo
{
namespace planning
{
/**
 * @brief  main class of parking path plan
 *
 * @details a important class, which includes parking state decision
 * and parking path plan
 */
class ParkingBase
{
public:
    /**
     * @brief constructor
     */
    ParkingBase()
      : vehicle_cfg_(config::HppConfigHelper::GetHppCfg().vehicle_cfg)
      , hybrid_astar_cfg_(config::HppConfigHelper::GetHppCfg().hybrid_astar_cfg)
      , stop_exit_waiting_cycle_(HppParam::Instance().stop_exit_waiting_cycle)
    {
    }

    /**
     * @brief destroys the object
     */
    ~ParkingBase()
    {
    }

    /**
     * @brief init input
     *
     * @param[in] tm_freespace_ freespace
     * @param[in] tm_chassis_state_ chassis_state
     * @param[in] tm_replan_recommended_ replan recommended order according to collision distance warning
     * @param[in] tm_x_limit criteria along x axis
     * @param[in] tm_y_limit criteria along y axis
     * @param[in] tm_angle_limit criteria for headingangle
     * @param[in] tm_replan_times_limit criteria for maximum replan times
     * @param[in] tm_desiredspeed desired speed calculated by outer module
     * @param[in] tm_parkingoperatestate_ paring status
     * @param[in] tm_current_path_ current path from last cycle
     * @param[in] tm_current_parkinglot_ current parklot after handling
     * @param[in] tm_reference_line_ reference path from route or other sources
     */
    void Init(std::vector<std::vector<geometry::Point2>> const* tm_freespace_,
              common::ChassisState const*                       tm_chassis_state_,
              bool_t const&                                     tm_replan_recommended_,
              float64_t const&                                  tm_x_limit,
              float64_t const&                                  tm_y_limit,
              float64_t const&                                  tm_angle_limit,
              uint32_t const&                                   tm_replan_times_limit,
              float64_t const&                                  tm_desiredspeed,
              OperateState*                                     tm_parkingoperatestate_,
              PathData*                                         tm_current_path_,
              SingleParkingLot*                                 tm_current_parkinglot_,
              std::vector<CurvePoint> const*                    tm_reference_line_);

    /**
     * @brief cycle run parking process management
     *
     * @details parking process management including decision making and path planning
     */
    virtual void RunOnce() = 0;

protected:
    std::vector<std::vector<geometry::Point2>> const* freespace_           = nullptr;
    common::ChassisState const*                       chassis_state_       = nullptr;
    OperateState*                                     parkingoperatestate_ = nullptr;
    SingleParkingLot*                                 current_parkinglot_  = nullptr;
    PathData*                                         current_path_        = nullptr;
    bool_t                                            replan_recommended_  = false;
    float64_t                                         desiredspeed_        = 0.0;
    ParkingPath                                       parking_path_;  ///< parking planning method class

    config::VehicleConfig const&     vehicle_cfg_;
    config::HybridAstarConfig const& hybrid_astar_cfg_;

    uint32_t  drive_stop_waiting_counter_    = 0;    ///< counter when unable to drive  due to slope or similar reasons
    uint32_t  obstacle_stop_waiting_counter_ = 0;    ///< counter when unable to drive due to obstacle
    uint32_t  forward_obstacle_counter_      = 0;    ///< counter when the front is restricted by obstacle
    uint32_t  backward_obstacle_counter_     = 0;    ///< counter when the back is restricted by obstacle
    float64_t x_limit_                       = 0.0;  ///< criteria along x axis
    float64_t y_limit_                       = 0.0;  ///< criteria along y axis
    float64_t angle_limit_                   = 0.0;  ///< criteria for headingangle
    uint32_t  replan_times_limit_            = 0;    ///< criteria for maximum replan times
    uint32_t  num_replan_times_              = 0;    ///< actual replan times
    float64_t brake_distance_threshold_      = 0.1;  ///< brake distance threshold required
    uint32_t  stop_exit_waiting_cycle_       = 300;  ///< exit waiting cycle caused by obstacle caused stop
    std::vector<CurvePoint> reference_line_;         ///< reference line

    void         Reset4Next();                 ///< reset commen used variables such as counter
    virtual void ExcuteOutsideForward()  = 0;  ///< forward path plan outside parkinglot
    virtual void ExcuteOutsideBackward() = 0;  ///< backward path plan outside parkinglot
    virtual void ExcuteInsideForward()   = 0;  ///< forward path plan inside parkinglot
    virtual void ExcuteInsideBackward()  = 0;  ///< backward path plan inside parkinglot
    virtual void CompleteParking()       = 0;  ///< parking succeed
    virtual void ParkingFailed()         = 0;  ///< parking failed

    PointXY              VehicleLeftFrontCornerCoord();
    PointXY              VehicleRightFrontCornerCoord();
    PointXY              VehicleLeftRearCornerCoord();
    PointXY              VehicleRightRearCornerCoord();
    std::vector<PointXY> GetParkinglotPoint(const RectCorner single_lot);
    void                 StopCar();
    void                 GetGear(const bool status);
};

}  // namespace planning
}  // namespace holo

#endif
