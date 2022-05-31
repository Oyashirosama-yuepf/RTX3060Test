/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_interface.h
 * @brief This header file defines parking manager common interface management
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_COMMON_INTERFACE_H
#define HOLO_PARKING_COMMON_INTERFACE_H

#include <mutex>

#include <glog/logging.h>

#include <holo/common/chassis_state.h>
#include <holo/common/odometry.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/common/vehicle_state.h>
#include <parking_manager/parking_state_machine/parking_state_machine.h>
#include <holo/parking/system/hmi_command.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

using holo::common::ChassisState;
using holo::common::Odometryd;
using holo::common::VehicleBodyState;
using holo::common::UserOperation;
using holo::parking::system::HmiCommand;

class CommonInterface
{

public:
    explicit CommonInterface();
    ~CommonInterface() = default;

    bool_t ReceiveHmiCommand(const HmiCommand& hmi_command);
    bool_t ReceivePsdState(const PsdStatus& psd_state);
    bool_t ReceiveHandShake(const uint32_t& hand_shake);
    bool_t ReceivePlanningState(const uint32_t& planning_command);

    bool_t ReceiveChassisState(const ChassisState& chassis_state);
    bool_t ReceiveVehicleBodyStatus(const VehicleBodyState& vehicle_body_state);
    bool_t ReceiveUserOperation(const UserOperation& user_operation);
    bool_t ReceiveOdometry(const Odometryd& odometry);

    
    HmiCommand GetHmiCommand() const noexcept {
        return hmi_command_;
    }

    PsdStatus GetPsdStatus() const noexcept {
        return psd_state_;
    }

    uint32_t GetHandShakeStatus() const noexcept {
        return hand_shake_;
    }

    uint32_t GetPlanningState() const noexcept {
        return planning_state_;
    }

    ChassisState GetChassisState() const noexcept {
        return chassis_state_;
    }

    UserOperation GetUserOperation() const noexcept {
        return user_operation_;
    }

    VehicleBodyState GetVehicleBodyStatus() const noexcept {
        return vehicle_body_state_;
    }

private:
    /* subscriber messages */
    HmiCommand hmi_command_;
    PsdStatus  psd_state_;
    uint32_t   hand_shake_;
    uint32_t   planning_state_;
    
    ChassisState chassis_state_;
    UserOperation user_operation_;
    VehicleBodyState vehicle_body_state_;
    Odometryd odometry_d_;
    /* mutex*/
    std::mutex mutex_hmi_command_;
    std::mutex mutex_psd_state_;
    std::mutex mutex_hand_shake_;
    std::mutex mutex_planning_state_;
    std::mutex mutex_chassis_state_;
    std::mutex mutex_user_operation_;
    std::mutex mutex_vehicle_body_state_;
    std::mutex mutex_odometry_d_;

};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  //HOLO_PARKING_COMMON_INTERFACE_H
