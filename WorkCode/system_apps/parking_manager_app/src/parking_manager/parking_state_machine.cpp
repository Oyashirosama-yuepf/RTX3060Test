/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_state_machine.cpp
 * @brief defines state machine transition process
 * @author yuepengfei(yuepengfei@holomatic.com)
 * @date 2022/05/25
 */

#include <parking_manager/parking_state_machine/parking_state_machine.h>


#ifndef FSM_INITIAL_PARK_FSM_
#define FSM_INITIAL_PARK_FSM_
FSM_INITIAL_STATE(ParkTinyFsm::ParkFsm, ParkTinyFsm::Poweroff)
#endif /// FSM_INITIAL_PARK_FSM_

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

void ParkStateMachineManager::Manage(ParkingInput const& parking_input) {
    EnterStandbyStatusCondition(parking_input);     // 待机状态判断
    EnterSearchingStatusCondition(parking_input);   // 车位搜索状态判断
    EnterApaReadyStatusCondition(parking_input);    // 车位搜索成功状态判断
    EnterParkingStatusCondition(parking_input);     // 开始泊车状态判断
    EnterParkingSuccessCondition(parking_input);    // 泊车成功状态判断
}

void ParkStateMachineManager::EnterStandbyStatusCondition(ParkingInput const& parking_input) {
    if(parking_input.planning_state == PlanningState::FAILED) {
        ParkTinyFsm::send_event<ParkTinyFsm::SwitchToStandby>(switch_to_standby);
    }
}    // 进入待机状态判断

void ParkStateMachineManager::EnterSearchingStatusCondition(ParkingInput const& parking_input) {
    if(static_cast<uint8_t>(parking_input.hmi_command.GetHmiCommand()) == 
       static_cast<uint8_t>(HmiCommand::HmiCommandType::ENABLE_APA)) {
        ParkTinyFsm::send_event<ParkTinyFsm::SwitchToSearch>(switch_to_search);
    }
}   // 进入车位搜索状态判断

void ParkStateMachineManager::EnterApaReadyStatusCondition(ParkingInput const& parking_input) {
    if(parking_input.psd_status.GetSlotNodeState() == 0x02) {
        ParkTinyFsm::send_event<ParkTinyFsm::SwitchToApaReady>(switch_to_apa_ready);
    }
}   // 车位搜索成功状态判断

void ParkStateMachineManager::EnterParkingStatusCondition(ParkingInput const& parking_input) {
    if(parking_input.hand_shake == 0x01) {
        ParkTinyFsm::send_event<ParkTinyFsm::SwitchToPark>(switch_to_park);
    }
}   // 开始泊车状态判断

void ParkStateMachineManager::EnterParkingSuccessCondition(ParkingInput const& parking_input) {
    if(parking_input.planning_state == PlanningState::SUCCESS) {
        ParkTinyFsm::send_event<ParkTinyFsm::SwitchToParkSuccess>(switch_to_park_success);
    }
}    // 泊车成功状态判断

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

