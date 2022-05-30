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

#include <hmi_converter/hmi_manager.h>

namespace holo
{

namespace parking_cmw_app
{

namespace hmi_converter
{

HmiManager::HmiManager() {
    common_interface_ = std::make_shared<CommonInterface>();   // 公共接口初始化
    hmi_state_management_ = std::make_shared<HmiStateMachineManager>();   // 状态机管理
}

void HmiManager::Pipeline(HmiCommand& hmi_command, uint32_t& route_id) {
    memset(&hmi_input_, 0 , sizeof(hmi_input_));
    /* 1. 刷新状态机输入信息 */
    CollectHmiStateManagementInfo();   
    /* 2. 状态机运转 */
    hmi_state_management_->Manage(hmi_input_);
    /* 3. 状态机输出信息刷新 */
    hmi_command = hmi_state_management_->GetHmiCommand();
    route_id = hmi_state_management_->GetRouteId();
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
