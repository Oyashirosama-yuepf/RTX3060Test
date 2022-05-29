/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_state_machine.cpp
 * @brief This cpp file defines state management class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#include <hmi_converter/hmi_state_machine/hmi_state_machine.h>

#ifndef INITIAL_HMI_FSM_
#define INITIAL_HMI_FSM_
FSM_INITIAL_STATE(HmiTinyFsm::HmiFsm, HmiTinyFsm::StartApa)
#endif  /// INITIAL_HMI_FSM_

namespace holo
{

namespace parking_cmw_app
{

namespace hmi_converter
{

void HmiStateMachineManager::Manage(HmiInput const& hmi_input) {
    EnterStandbyStatusCondition(hmi_input);
    EnterStartApaStatusCondition(hmi_input);
}

void HmiStateMachineManager::EnterStandbyStatusCondition(HmiInput const& hmi_input) {
    if(!hmi_input.apa_event_request_.GetEnableApaStatus()) {
        HmiTinyFsm::send_event(switch_to_stop_apa);
    }
}

void HmiStateMachineManager::EnterStartApaStatusCondition(HmiInput const& hmi_input) {
    if(hmi_input.apa_event_request_.GetEnableApaStatus()) {
        HmiTinyFsm::send_event(switch_to_start_apa);
    }
}

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo
