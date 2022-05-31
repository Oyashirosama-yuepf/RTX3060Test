/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parkingplan.h
 * @brief the header of parkingplan
 * @author yansenwei(yansenwei@holomatic.com)
 * @date 2021-03-11
 */

#ifndef _PARKINGPLAN_H_
#define _PARKINGPLAN_H_

#include <holo/hpp/parkingplan/common_struct_type.h>
#include <holo/hpp/parkingplan/commonfunction.h>
#include <holo/hpp/parkingplan/parallelpullingout.h>
#include <holo/hpp/parkingplan/pullingoutbase.h>
#include <holo/hpp/parkingplan/verticalparking.h>
#include <holo/hpp/parkingplan/verticalpullingout.h>
#include <holo/planning/common/hpp_param.h>
#include <holo/planning/common/macro.h>
#include <holo/planning/util/collision_checker.h>

namespace holo
{
namespace planning
{
/**
 * @brief  main class of parking & pullingout
 *
 * @details a important class, which includes parkinglot type classication and handling，
 * parking process management, pullingout process management
 */
class ParkingPlanner
{
private:
    ParkinglotData                                    parkinglot_;
    std::vector<std::vector<geometry::Point2>> const* freespace_     = nullptr;
    common::ChassisState const*                       chassis_state_ = nullptr;
    std::vector<CurvePoint>                           reference_line_;
    int8_t                                            pullout_dir_;
    int8_t                                            parkinglot_type_;
    geometry::Pose2                                   pose_;
    geometry::Pose2                                   last_pose_;

    SingleParkingLot  current_parkinglot_;  ///< lot uesd for planning
    SingleParkingLot  previous_parkinglot_;
    SingleParkingLot  current_parkinglot_dr_;  ///< lot calculated by DR which used chassis info
    SingleParkingLot  previous_parkinglot_dr_;
    SingleParkingLot  current_parkinglot_sv_tracking_;  ///< lot sent by surround view
    SingleParkingLot  previous_parkinglot_sv_tracking_;
    PathData          current_path_;  ///< parking path struct
    PathData          previous_path_;
    PullingoutLotData pullingout_lot_;  ///< lot uesd for pullingout

    OperateState parking_operatestate_;  ///< paring status struct
    // SamplingPathPlan   sampling_path_plan_;    ///< class provides sampling method
    ParkingPath      parking_path_;       ///< class provides parking path planning method
    ReckonData       position_reckon_;    ///< class provides DR method
    CollisionChecker collision_checker_;  ///< class provides collision check method
    //     UpdateControlValue update_control_value_;  ///< class provides speedplan method and orher
    ExecuteTrajectory  trajectory_frame_;     ///< trajectory struct
    VerticalParking    vertical_parking_;     ///< class which manages vertical parking process
    // ParallelParking    parallel_parking_;     ///< class which manages parallel parking process
    VerticalPullingOut vertical_pullingout_;  ///< class which manages vertical pullingout process
    ParallelPullingOut parallel_pullingout_;  ///< class which manages parallel pullingout process

    float64_t x_limit_;                  ///< criteria along x axis
    float64_t y_limit_;                  ///< criteria along y axis
    float64_t angle_limit_;              ///< criteria for headingangle
    uint8_t   replan_times_limit_;       ///< criteria for maximum replan times
    uint32_t  stop_time_counter_;        ///< counter accumulated when vehicle stops
    uint8_t   parking_cmd_;              ///< parking or pullingout command
    bool_t    replan_recommended_;       ///< replan recommended order according to collision distance warning
    float64_t expected_speed_;           ///< expected speed from speed plan
    bool_t    stopped_by_obs;            ///< stop car because of obstacle by speed plan
    uint32_t  replan_obstacle_counter_;  ///< counter when replan recommended by obstacle
    std::shared_ptr<std::vector<CurvePoint>> global_plan_path_ =
        std::make_shared<std::vector<CurvePoint>>();  ///< global plan path used when pulling out
    std::shared_ptr<std::vector<std::vector<CurvePoint>>> hybridastar_paths_ =
        std::make_shared<std::vector<std::vector<CurvePoint>>>();  ///< hybridastar plan paths used when parallel
                                                                   ///< pulling out

    /**
     * @brief parking function entry
     */
    bool_t AutoParking();

    /**
     * @brief parkinglot handling function entry
     */
    bool_t ParkingSpaceHandle();

    /**
     * @brief pullingout function entry
     *
     * @param[in] parkinglot_type  parkinglot type
     * @param[in] pullout_dir  selected pullout direction
     */
    bool_t PullOutFromParkinglot(int8_t parkinglot_type, int8_t pullout_dir);

    /**
     * @brief pullingout lot_type clasification & global path generation
     *
     * @param[in] parkinglot_type  parkinglot type
     * @param[in] pullout_dir  selected pullout direction
     */
    void GetReady4Pullout(int8_t parkinglot_type, int8_t pullout_dir);

    /**
     * @brief collision detection
     */
    void CollisionDetection();

    /**
     * @brief the coordinate of the lot is longitudinally compensated
     * because of the speed of the vehicle.
     */
    void ParkingLotAdjust();

    /**
     * @brief calculate the time difference between the location timestamp sent by the perception and the planned
     * processing moment
     */
    float64_t GetTimeInterval() const;

    /**
     * @brief determine the lot type
     *
     * @param[out] tmp_parkinglot   lot after judgment
     * @param[out] parkinglot_counter  the number of valid lot that have been judged
     */
    void JudgeParkingLotType(std::vector<SingleParkingLot>& tmp_parkinglot, int32_t& parkinglot_counter);

    /**
     * @brief select the nearest lot and set parking criteria
     *
     * @param[in] parkinglot_counter  the number of valid lot that have been judged
     * @param[in] tmp_parkinglot lot after judgment
     */
    void SelectLotAndSetCriterion(int32_t parkinglot_counter, std::vector<SingleParkingLot> tmp_parkinglot);

    /**
     * @brief set parking criteria
     */
    void SetStopCriterion();

    DECLARE_SINGLETON(ParkingPlanner);

public:
    //    /**
    //     * @brief constructor.
    //     */
    //    ParkingPlanner();

    /**
     * @brief destroys the object.
     */
    ~ParkingPlanner();

    /**
     * @brief init input
     *
     * @param[in] tm_parkinglot_ parkinglot
     * @param[in] tm_freespace_ freespace
     * @param[in] tm_chassis_state_ chassis state
     * @param[in] tm_parking_cmd parking or pullingout command
     * @param[in] tm_reference_line_ reference line used when pulling out
     * @param[in] tm_pullout_dir_ pullout direction
     * @param[in] tm_parkinglot_type_  parkinglot type uesd for pulling out
     * @param[in] tm_pose_  vehicle pose
     * @param[in] tm_last_pose_  last vehicle pose
     * @param[in] tm_expected_speed_  expected speed from speed plan
     * @param[in] stopped_by_obs  stop car because of obstacle by speed plan
     */
    void Init(ParkinglotData const&                             tm_parkinglot_,
              std::vector<std::vector<geometry::Point2>> const* tm_freespace_,
              common::ChassisState const*                       tm_chassis_state_,
              uint8_t const                                     tm_parking_cmd,
              std::vector<CurvePoint> const*                    tm_reference_line_,
              int8_t const                                      tm_pullout_dir_,
              int8_t const                                      tm_parkinglot_type_,
              geometry::Pose2                                   tm_pose_,
              geometry::Pose2                                   tm_last_pose_,
              float64_t                                         tm_expected_speed_,
              bool_t                                            tm_stopped_by_obs);

    /**
     * @brief main function of parking & pullingout
     *
     * @details including parkinglot type classication and handling，
     * parking process management, pullingout process management
     */
    bool_t ParkingPlan();

    /**
     * @brief return the output of parking or pullingout
     *
     * @return PathData is the reult of parking path planning
     */
    PathData ReturnParkingPath();

    /**
     * @brief return the output of parking or pullingout
     *
     * @return ExecuteTrajectory includes needed infomation by control
     */
    ExecuteTrajectory ReturnParkingTrajectory();

    void UpdateParkinglotDataForTimeGap();

    /**
     * @brief dead reckon for one point
     *
     * @param[in] point: target point before DR
     * @param[in] time_diff: one period
     * @param[in] real_speed: real car speed
     * @param[in] frontwheelangle: frontwheelangle, unit:rad
     *
     * @return PointXY: target point after DR
     *
     * @note: DR accuracy may be improved by using IMU
     */
    PointXY DR4Point(PointXY point, float64_t time_diff, float64_t real_speed, float64_t frontwheelangle);
};

}  // namespace planning
}  // namespace holo

#endif
