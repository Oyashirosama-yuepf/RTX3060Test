/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_state_machine.h
 * @brief The header file which defines state machine transition process
 * @author yuepengfei(yuepengfei@holomatic.com)
 * @date 2022/05/25
 */

#ifndef HOLO_PARKING_STATE_MACHINE_MANAGER_H
#define HOLO_PARKING_STATE_MACHINE_MANAGER_H

#include <parking_manager/parking_state_machine/park_fsm_state.h>

namespace holo
{

namespace parking_cmw_app
{

namespace parking_manager
{

class ParkStateMachineManager
{

public:
    ParkStateMachineManager() {
        ParkTinyFsm::ParkFsm::start();   // 状态机启动
    }
    virtual ~ParkStateMachineManager() = default;
    void Manage(ParkingInput const& parking_input);

private:  // 状态机输出相关
    APAParkingState apa_state_;
    APAParkingManagerCommand apa_park_command_;
    bool_t apa_ctrl_req_;
    uint32_t route_id_;

private:  // 状态切换事件
    ParkTinyFsm::SwitchToPowerOff switch_to_poweroff;
    ParkTinyFsm::SwitchToStandby switch_to_standby;
    ParkTinyFsm::SwitchToSearch switch_to_search;
    ParkTinyFsm::SwitchToApaReady switch_to_apa_ready;
    ParkTinyFsm::SwitchToPark switch_to_park;
    ParkTinyFsm::SwitchToParkSuccess switch_to_park_success;

private:  // 状态切换事件判断
    void EnterStandbyStatusCondition(ParkingInput const& parking_input);     // 进入待机状态判断
    void EnterSearchingStatusCondition(ParkingInput const& parking_input);   // 进入车位搜索状态判断
    void EnterApaReadyStatusCondition(ParkingInput const& parking_input);    // 车位搜索成功状态判断
    void EnterParkingStatusCondition(ParkingInput const& parking_input);     // 开始泊车状态判断
    void EnterParkingSuccessCondition(ParkingInput const& parking_input);    // 泊车成功状态判断

public: 
    APAParkingState GetApaState() {
        return apa_state_;
    }

    APAParkingManagerCommand GetApaParkingManagerCommand() {
        return apa_park_command_;
    }

    bool_t GetApaCtrlReq() {
        return apa_ctrl_req_;
    }

    uint32_t GetRouteId() {
        return route_id_;
    }
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif //HOLO_PARKING_STATE_MACHINE_MANAGER_H