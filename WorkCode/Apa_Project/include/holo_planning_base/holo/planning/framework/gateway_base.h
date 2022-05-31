/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.ai)
 *  \date Aug 11, 2017
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_GATEWAY_BASE_H_
#define _HOLO_PLANNING_GATEWAY_BASE_H_

#include <mutex>
#include <vector>

#include <holo/common/timestamp.h>
#include <holo/core/types.h>
#include <holo/map/advice.h>

#include <holo/planning/common/car_road_state.h>
#include <holo/planning/common/command.h>
#include <holo/planning/common/plan_route.h>

namespace holo
{
namespace planning
{
/**
 * @brief      Data Receiver and Keeper.
 * @details    A very important class, which receive and keep all the data sent
 *             by other modules, like sensors, map, etc. It also has the ability
 *             to classify the obstacles according to relative area to ego car.
 */
class GatewayBase
{
public:
    typedef std::vector<std::shared_ptr<obstacle::ObstacleGeneralPtrList>> ObstacleLList;

public:
    /**
     * @brief      Constructor.
     */
    GatewayBase();

    /**
     * @brief      Destroys the object.
     */
    virtual ~GatewayBase();

    /**
     * @brief      Gets the car road state.
     *
     * @param      car_road_state  The car road state
     *
     * @return     True if no errors happened, False otherwise.
     */
    virtual bool_t GetCarRoadState(CarRoadState& car_road_state);

    /**
     * @brief      Gets the command.
     *
     * @param      cmd  The command
     *
     * @return     True if no errors happened, False otherwise.
     */
    virtual bool_t GetCommand(Command& cmd);

    /**
     * @brief      Receive chassis state.
     *
     * @param[in]  chassis_state  The chassis state
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveChassisState(std::shared_ptr<common::details::ChassisState> chassis_state);

    /**
     * @brief      Receive vehicle body state.
     *
     * @param[in]  state  The vehicle body state
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveVehicleBodyState(std::shared_ptr<common::VehicleBodyState> state);

    /**
     * @brief      Receive obstacles.
     *
     * @param[in]  obstacle_state  The obstacle state
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveObstacleState(const std::shared_ptr<obstacle::ObstacleGeneralPtrList>& obstacles);

    /**
     * @brief      Receive odometry.
     *
     * @param[in]  odometry  The odometry
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveOdometry(const std::shared_ptr<holo::common::Odometryd>& odometry);

    /**
     * @brief      Receive IntentionList.
     *
     * @param[in]  intention_list  The intention_list
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveIntentionList(const std::shared_ptr<holo::prediction::Intentions>& intention_list);

    /**
     * @brief      Receive control active command
     *
     * @param[in]  control active command
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveActivateCommand(const uint32_t cmd);

    /**
     * @brief      Receive road frame2.
     *
     * @param[in]  road_frame2  The road_frame2
     *
     * @return     True if no errors happened, False otherwise.
     */
    bool_t ReceiveRoadFrame2(const RoadFramePtr& road_frame2);

protected:
    std::vector<std::shared_ptr<common::details::ChassisState>> chassis_state_list_;
    std::mutex                                                  mutex_chassis_state_;

    std::vector<std::shared_ptr<common::VehicleBodyState>> vehicle_body_state_list_;
    std::mutex                                             mutex_vehicle_body_state_;

    ObstacleLList obstacles_llist_;
    std::mutex    mutex_obstacles_;

    std::vector<std::shared_ptr<holo::common::Odometryd>> odometry_list_;
    std::mutex                                            mutex_odometry_;

    std::vector<std::shared_ptr<holo::prediction::Intentions>> intention_list_list_;
    std::mutex                                                 mutex_intention_list_;

    std::vector<RoadFramePtr> road_frame2_list_;
    std::mutex                mutex_road_frame2_;

    std::vector<uint32_t> activate_cmd_list_;
    std::mutex            mutex_activate_cmd_;
};

}  // namespace planning
}  // namespace holo

#endif
