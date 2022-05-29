/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file state_machine_structure.h
 * @brief the structure of state machine
 * @author yangzhongtao(yangzhongtao@holomatic.com)
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_STATE_MACHINE_STRUCTURE_H
#define HOLO_PARKING_STATE_MACHINE_STRUCTURE_H

#include <holo/common/chassis_state.h>
#include <holo/core/types.h>
#include <holo/parking/system/hmi_command.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/common/vehicle_state.h>
#include <holo/common/odometry.h>
#include <holo/parking/system/psd_status.h>
#include <holo/parking/parking_manager/apa_parking_status.h>
#include <holo/parking/parking_manager/apa_parking_manager_command.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

using HmiCommand = holo::parking::system::HmiCommand;
using ChassisState = holo::common::ChassisState;
using VehicleBodyState = holo::common::VehicleBodyState;
using UserOperation = holo::common::UserOperation;
using Odometryd = holo::common::Odometryd;
using PsdStatus = holo::parking::system::PsdStatus;
using APAParkingState = holo::parking::parking_manager::APAParkingState;
using APAParkingManagerCommand = holo::parking::parking_manager::APAParkingManagerCommand;

struct InterfaceConfig
{
    bool_t enable_dds_interface;
    bool_t enable_cloud_interface;
    bool_t enable_bluetooth_interface;
};

enum class PlanningState : uint8_t
{
    STANDBY           = 0U,
    ACTIVE            = 1U,
    INTERRUPT         = 2U,
    SUCCESS           = 3U,
    FAILED            = 4U,
    COMPLETED         = 5U,
    OBSTACLE_STOPPING = 6U,
    OBSTACLE_AVOID    = 7U,
};

struct CloudCommand
{
    uint64_t route_id;
    uint64_t heart_id;
    uint64_t takeover_recovery_command;
    uint64_t start_stop_command;
    uint64_t mapping_path_command;
};

struct ParkingInput
{
    HmiCommand        hmi_command;    // 1. Apa开关
    PsdStatus         psd_status;     // 2. 是否搜索到车位，apa是否ready
    uint32_t          hand_shake;     // 3. 是否获取到控制权
    PlanningState     planning_state; // 4. 是否泊车成功
    // 用户其他操作影响和异常状态判断
    ChassisState      chassis_state;
    UserOperation     user_operation;
    VehicleBodyState  vehicle_body_state;
};

struct SwitchOffCondition
{
    bool_t stop_wait_time_exceeded;
};

struct PathAttribute
{
    uint8_t path_index;
    uint8_t park_mode;
    uint8_t path_slot;
    uint8_t path_state;
    uint16_t path_length;
    std::string path_name;
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif //HOLO_PARKING_STATE_MACHINE_STRUCTURE_H