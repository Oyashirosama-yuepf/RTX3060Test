/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_manager.h
 * @brief This header file defines parking manager pipeline
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/28
 */

#ifndef HOLO_PARKING_PARKING_MANAGER_H
#define HOLO_PARKING_PARKING_MANAGER_H

#include <holo/common/vehicle_state.h>

#include <holo/core/types.h>

#include <holo/planning/state.h>

#include <hmi_converter/interface_manager/common_interface.h>
#include <hmi_converter/hmi_state_machine/hmi_state_machine.h>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{

class HmiManager
{

public:
    explicit HmiManager();
    ~HmiManager() = default;

    void Pipeline(HmiCommand& hmi_command, uint32_t& route_id);

    std::shared_ptr<CommonInterface> GetCommonInterface() {
        return common_interface_;
    }

    std::shared_ptr<HmiStateMachineManager> GetHmiStateMachineManager() {
        return hmi_state_management_;
    }

private:  // 通过interface获取的状态机输入信息汇总
    HmiInput hmi_input_;
private:  // 状态机运转输入信息汇总
    void CollectHmiStateManagementInfo() {
        hmi_input_.apa_event_request_ = common_interface_->GetApaEventRequest();
        hmi_input_.remote_control_signal_ = common_interface_->GetRemoteControlSignal();
        hmi_input_.odometry_f_park = common_interface_->GetParkingOdometry();
        hmi_input_.odometry_f_map = common_interface_->GetMappingOdometry();
    }

private:
    bool_t running_;
    // 通信接口class
    std::shared_ptr<CommonInterface> common_interface_;
    // 状态机class
    std::shared_ptr<HmiStateMachineManager> hmi_state_management_;
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  //HOLO_PARKING_PARKING_MANAGER_H
