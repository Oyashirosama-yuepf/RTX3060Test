/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_interface.cpp
 * @brief This cpp file defines parking manager common interface management
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#include <parking_manager/interface_manager/common_interface.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

CommonInterface::CommonInterface()
{
}

bool_t CommonInterface::ReceiveChassisState(const ChassisState& chassis_state)
{
    std::lock_guard<std::mutex> guard(mutex_chassis_state_);
    chassis_state_ = chassis_state;

    return true;
}

bool_t CommonInterface::ReceiveVehicleBodyStatus(const VehicleBodyState& vehicle_body_state)
{
    std::lock_guard<std::mutex> guard(mutex_vehicle_body_state_);
    vehicle_body_state_ = vehicle_body_state;

    return true;
}

bool_t CommonInterface::ReceivePsdState(const PsdStatus& psd_state)
{
    std::lock_guard<std::mutex> guard(mutex_psd_state_);
    psd_state_ = psd_state;

    return true;
}

bool_t CommonInterface::ReceiveHandShake(const uint32_t & hand_shake)
{
    std::lock_guard<std::mutex> guard(mutex_hand_shake_);
    hand_shake_ = hand_shake;

    return true;
}

bool_t CommonInterface::ReceiveUserOperation(const UserOperation& user_operation)
{
    std::lock_guard<std::mutex> guard(mutex_user_operation_); 
    user_operation_ = user_operation;

    return true;
}

bool_t CommonInterface::ReceivePlanningState(const uint32_t & planning_state)
{
    std::lock_guard<std::mutex> guard(mutex_planning_state_);
    planning_state_ = planning_state;

    return true;
}

bool_t CommonInterface::ReceiveHmiCommand(const HmiCommand & hmi_command)
{
    std::lock_guard<std::mutex> guard(mutex_hmi_command_);
    hmi_command_ = hmi_command;
    return true;
}

bool_t CommonInterface::ReceiveOdometry(const Odometryd& odometry)
{
    std::lock_guard<std::mutex> guard(mutex_odometry_d_);
    odometry_d_ = odometry;
    return true;
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
