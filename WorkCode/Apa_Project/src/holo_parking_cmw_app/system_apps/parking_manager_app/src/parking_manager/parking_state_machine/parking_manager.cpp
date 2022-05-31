/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_manager.cpp
 * @brief This cpp file defines parking manager pipeline
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/28
 */

#include <glog/logging.h>

#include <parking_manager/parking_manager.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

ParkingManager::ParkingManager(const InterfaceConfig& config)
{
    enable_dds_ = false; // 启用opendds通信
    common_interface_ = std::make_shared<CommonInterface>();   // 公共接口初始化
    park_state_managment = std::make_shared<ParkStateMachineManager>();   // 状态机管理

    if (config.enable_dds_interface) {
        dds_interface_ = std::make_shared<DdsInterface>();
        enable_dds_ = true;
    } else {
        LOG(ERROR) << "Interface is not specified or supported!!";
    }
};

void ParkingManager::Pipeline(APAParkingState& apa_state, 
                              APAParkingManagerCommand& apa_park_command,
                              bool_t& apa_ctrl_req,
                              uint32_t& route_id) {

    /* 1. 刷新状态机输入信息 */                              
    memset(&parking_input_, 0 , sizeof(parking_input_));
    CollectStateManagementInfo();
    /* 2. 状态机运转 */
    park_state_managment->Manage(parking_input_);
    /* 3. 刷新输出信息 */
    apa_state = park_state_managment->GetApaState();
    apa_park_command = park_state_managment->GetApaParkingManagerCommand();
    apa_ctrl_req = park_state_managment->GetApaCtrlReq();
    route_id = park_state_managment->GetRouteId();
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
