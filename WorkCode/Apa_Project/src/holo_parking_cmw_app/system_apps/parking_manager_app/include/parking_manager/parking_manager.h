/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_manager.h
 * @brief This header file defines parking manager pipeline
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_PARKING_MANAGER_H
#define HOLO_PARKING_PARKING_MANAGER_H

#include <holo/common/vehicle_state.h>

#include <holo/core/types.h>

#include <holo/planning/state.h>

#include <parking_manager/interface_manager/common_interface.h>
#include <parking_manager/interface_manager/dds_interface.h>
#include <parking_manager/utils/parking_utils.h>
#include <parking_manager/utils/mapping_utils.h>
#include <parking_manager/parking_state_machine/parking_state_machine.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

class ParkingManager
{

public:
    explicit ParkingManager(const InterfaceConfig& config);
    ~ParkingManager() = default;

    void   Pipeline(APAParkingState& apa_state, 
                    APAParkingManagerCommand& apa_park_command,
                    bool_t& apa_ctrl_req,
                    uint32_t& route_id);

    std::shared_ptr<CommonInterface> GetCommonInterface() {
        return common_interface_;
    }

private:   // 状态机通过interface获取的信息汇总
    ParkingInput parking_input_;

private:   // 汇总状态机运转所需要的输入信息
    void CollectStateManagementInfo() {
        parking_input_.hmi_command = common_interface_->GetHmiCommand();
        parking_input_.psd_status = common_interface_->GetPsdStatus();
        parking_input_.hand_shake = common_interface_->GetHandShakeStatus();
        parking_input_.planning_state = static_cast<PlanningState>(common_interface_->GetPlanningState());

        parking_input_.chassis_state = common_interface_->GetChassisState();
        parking_input_.user_operation = common_interface_->GetUserOperation();
        parking_input_.vehicle_body_state = common_interface_->GetVehicleBodyStatus();
    }

private:
    bool_t running_;
    bool_t enable_dds_;
    // 通信接口class
    std::shared_ptr<CommonInterface> common_interface_;
    std::shared_ptr<DdsInterface> dds_interface_;
    // 状态机class
    std::shared_ptr<ParkStateMachineManager> park_state_managment;
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  //HOLO_PARKING_PARKING_MANAGER_H
