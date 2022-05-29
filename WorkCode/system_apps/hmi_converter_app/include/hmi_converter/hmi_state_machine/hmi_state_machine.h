/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_state_machine.h
 * @brief This header file defines state management class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#ifndef HOLO_PARKING_STATE_MANAGEMENT_H_
#define HOLO_PARKING_STATE_MANAGEMENT_H_

#include <hmi_converter/hmi_state_machine/hmi_fsm_state.h>

namespace holo
{

namespace parking_cmw_app
{

namespace hmi_converter
{

class HmiStateMachineManager {
public:
    HmiStateMachineManager() { 
        HmiTinyFsm::HmiFsm::start();   // 状态机启动
    };
    ~HmiStateMachineManager() = default;
    void Manage(HmiInput const& hmi_input);

private:  // 状态机输出信息
    HmiCommand hmi_command_output_;
    uint32_t route_id_;

private:  // 状态机切换时间
    HmiTinyFsm::SwitchToPowerOff switch_to_power_off;
    HmiTinyFsm::SwitchToStandby switch_to_stand_by;
    HmiTinyFsm::SwitchToStartApa switch_to_start_apa;
    HmiTinyFsm::SwitchToStopApa switch_to_stop_apa;

private:  // 状态事件判断
    void EnterStandbyStatusCondition(HmiInput const& hmi_input);
    void EnterStartApaStatusCondition(HmiInput const& hmi_input);
    
public:
    void SetHmiCommand(HmiCommand hmi_command) {
        hmi_command_output_.SetTimestamp(hmi_command.GetTimestamp());
        hmi_command_output_.SetHmiParkType(hmi_command.GetHmiParkType());
        hmi_command_output_.SetHmiCommand(hmi_command.GetHmiCommand());
    }

    HmiCommand GetHmiCommandOutput() {
        return hmi_command_output_;
    }

    uint32_t GetRouteId() {
        return route_id_;
    }
};

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo

#endif  // HOLO_PARKING_STATE_MANAGEMENT_H_
