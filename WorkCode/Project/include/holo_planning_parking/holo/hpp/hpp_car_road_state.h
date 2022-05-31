/**
 * @file hpp_car_road_state.h
 * @brief the header of car road state for hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2020-11-18
 */

#ifndef _HOLO_PLANNING_HPP_CAR_ROAD_STATE_H_
#define _HOLO_PLANNING_HPP_CAR_ROAD_STATE_H_

#include <holo/common/freespace.h>
#include <holo/common/parking_slot.h>
#include <holo/parking/map/navigation_road_builder.h>
#include <holo/parking/system/hpa_control_output_command.h>
#include <holo/planning/common/car_road_state.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Class for hpp car road state. This class keeps all the information
 *             used by the following path caculation from gateway.
 */
struct HppCarRoadState
{
    HppCarRoadState()
      : car_road_state(new CarRoadState), free_space(nullptr), hpp_parking_command(1000), recovery_status(0)
    {
    }
    std::shared_ptr<CarRoadState>                                   car_road_state;  ///< chassis, odometry, obstacle
    std::shared_ptr<holo::common::ParkingSlotFrame>                 parking_slot;    ///< parking slot
    std::shared_ptr<holo::common::AutoFreespace<geometry::Point3f>> free_space;      ///< free spaces, ranges, and holls
    std::shared_ptr<holo::common::AutoFreespace<geometry::Point3f>> free_space_avm;  ///< free spaces
    std::shared_ptr<holo::obstacle::ObstaclePtrListT<holo::obstacle::ObstacleGeneralT<holo::float32_t>, 128UL>>
                                                          detection;       ///< camera detection
    std::shared_ptr<holo::parking::system::ControlOutput> control_output;  ///< control output
    uint32_t hpp_parking_command;  ///< 0: reset, 1 - 999: start for route number, 1000: no command
    uint32_t hpp_parking_command_last;
    uint32_t recovery_status;      ///< 1: recovery command
    uint32_t heartbeat;            ///< 0: start, 3: running, 4: stop, 1000: no heartbeat, hz: about 4
    uint32_t hpa_command;          ///< 0: standby, 1 : active, 2 : suspend, 3 : exit
    uint32_t map_state;            ///< 0: standby, 1 : active, 2 : exit, 3 : complete
    uint32_t path_handle_command;  ///< 0: standby, 1 : active, 2 : exit

    bool is_chassis_valid    = false;
    bool is_odometry_valid   = false;
    bool is_navigation_valid = true;
    bool rcv_freespace_over_time;
    bool rcv_freespace_avm_over_time;
    bool rcv_detection_over_time;

    bool speed_under_low_limit  = true;
    bool speed_under_high_limit = true;
};

}  // namespace planning
}  // namespace holo
#endif
