/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gateway_hpp.h
 * @brief the header of hpp gateway
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#ifndef _HOLO_PLANNING_GATEWAY_HPP_H_
#define _HOLO_PLANNING_GATEWAY_HPP_H_

#include <holo/parking/map/navigation_road_builder.h>
#include <holo/parking/map/parking_navigation.h>

#include <holo/hpp/hpp_car_road_state.h>
#include <holo/planning/framework/gateway_base.h>
namespace holo
{
namespace planning
{
using MapNavigation = holo::map::ParkingNavigation;
/**
 * @brief Data Receiver and Keeper.
 * @details A very important class, which receive and keep all the data sent
 *          by other modules, like sensors, map, etc. It also has the ability
 *          to classify the obstacles according to relative area to ego car.
 */
class GatewayHpp : public GatewayBase
{
public:
    using ObstacleGeneralPtrList =
        holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>;

public:
    typedef std::vector<std::shared_ptr<holo::common::AutoFreespace<geometry::Point3f>>> FreeSpaceLList;
    typedef std::vector<std::shared_ptr<ObstacleGeneralPtrList>>                         ObstacleLList;
    typedef std::vector<std::shared_ptr<holo::parking::system::ControlOutput>>           ControlOutLList;
    typedef std::vector<std::shared_ptr<MapNavigation>>                                  NavigationPointList;
    typedef std::vector<std::shared_ptr<holo::common::ParkingSlotFrame>>                 ParkingSlotLList;

public:
    /**
     * @brief Constructor.
     */
    GatewayHpp();

    /**
     * @brief Destroys the object.
     */
    virtual ~GatewayHpp();

    /**
     * @brief      Gets the car road state.
     *
     * @param      hpp_car_road_state The car road state
     *
     * @return     True if no errors happened, False otherwise.
     */
    virtual bool GetHppCarRoadState(HppCarRoadState& hpp_car_road_state);

    std::shared_ptr<MapNavigation> GetHppNavigationPoint();

    /**
     * @brief Receive Parking Slot
     *
     * @param parking_slot  The parking slot
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveParkingSlot(std::shared_ptr<holo::common::ParkingSlotFrame> const& parking_slot);

    /**
     * @brief Receive Free space
     *
     * @param free_space  The free space
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveFreeSpace(std::shared_ptr<holo::common::AutoFreespace<geometry::Point3f>> const& free_space);

    /**
     * @brief Receive Avm Free space
     *
     * @param free_space  The avm free space
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveAvmFreeSpace(std::shared_ptr<holo::common::AutoFreespace<geometry::Point3f>> const& free_space_avm);

    bool ReceiveNavigationPoint(std::shared_ptr<MapNavigation> const& navigation_point);

    /**
     * @brief Receive parking map state
     *
     * @param parking_map_state The route id
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveMapState(uint32_t const parking_map_state);

    /**
     * @brief Receive Detection
     *
     * @param detection  The detection obstacle
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveDetection(std::shared_ptr<ObstacleGeneralPtrList> const& detection);

    /**
     * @brief Receive Control output
     *
     * @param control_output  The control output state
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveControlOutput(std::shared_ptr<holo::parking::system::ControlOutput> const& control_output);

    /**
     * @brief Receive parking route command id
     *
     * @param hpp_parking_command The route id
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveHppParkingCommand(uint32_t const hpp_parking_command);

    /**
     * @brief Receive recovery cmd.
     *
     * @param recovery_status The recovery signal
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveRecoveryStatus(uint32_t const recovery_status);

    /**
     * @brief Receive heartbeat.
     *
     * @param heartbeat The heartbeat signal
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveHeartbeat(uint32_t const heartbeat);

    /**
     * @brief Receive hpa command.
     *
     * @param hpa_command The hpa command signal
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceiveHpaCommand(uint32_t const hpa_command);

    /**
     * @brief Receive path handle command.
     *
     * @param path_handle_command The path handle command signal
     *
     * @return True if no errors happened, False otherwise.
     */
    bool ReceivePathHandleCommand(uint32_t const path_handle_command);

protected:
    ParkingSlotLList parking_slot_llist_;
    std::mutex       mutex_parking_slot_;

    FreeSpaceLList free_space_llist_;
    std::mutex     mutex_free_space_;

    FreeSpaceLList free_space_avm_llist_;
    std::mutex     mutex_free_space_avm_;

    ObstacleLList detection_llist_;
    std::mutex    mutex_detection_;

    ControlOutLList control_output_llist_;
    std::mutex      mutex_control_output_;

    NavigationPointList navigation_point_list_;
    std::mutex          mutex_navigation_point_;

    uint32_t   parking_map_state_ = 0;
    std::mutex mutex_parking_map_state_;

    uint32_t   hpp_parking_command_ = 1000;
    std::mutex mutex_hpp_parking_command_;

    uint32_t   recovery_status_ = 0;
    std::mutex mutex_recovery_status_;

    uint32_t   heartbeat_ = 1000;
    std::mutex mutex_heartbeat_;

    uint32_t   hpa_command_ = 0;
    std::mutex mutex_hpa_command_;
    size_t     hpa_command_counter_ = 0;

    uint32_t   path_handle_command_ = 0;
    std::mutex mutex_path_handle_command_;

    std::shared_ptr<common::details::ChassisState> chassis_state_;
    std::shared_ptr<holo::common::Odometryd>       odometry_;

    float64_t freespace_diff_;
    float64_t freespace_avm_diff_;
    float64_t detection_diff_;
    float64_t chassis_state_diff_;
    float64_t odometry_diff_;

    float32_t high_limit_speed_;
    float32_t low_limit_speed_;

    common::Timestamp last_receiving_freespace_timestamp_;
    common::Timestamp last_receiving_freespace_avm_timestamp_;
    common::Timestamp last_receiving_detection_timestamp_;
    common::Timestamp last_receiving_chassis_state_timestamp_;
    common::Timestamp last_receiving_odometry_timestamp_;
    common::Timestamp last_receiving_navigation_timestamp_;

    bool monitor_freespace_     = false;
    bool monitor_freespace_avm_ = false;
    bool monitor_detection_     = false;
    bool monitor_chassis_state_ = false;
    bool monitor_odometry_      = false;
    bool monitor_navigation_    = false;
    bool hpa_command_is_active_ = false;
};

}  // namespace planning
}  // namespace holo

#endif
