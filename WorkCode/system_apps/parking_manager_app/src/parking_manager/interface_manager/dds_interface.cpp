/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dds_manager.cpp
 * @brief This cpp file defines parking manager dds interface management
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <parking_manager/interface_manager/dds_interface.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

DdsInterface::DdsInterface()
{
    hmi_updated_ = false;
    test_timer_ = 0U;
    route_id_ = 0U;
    start_mapping_offline_ = false;
    mapping_offline_thread_ = std::make_shared<std::thread>(
                              std::bind(&DdsInterface::MappingOfflineThread, this));
}

void DdsInterface::MappingOfflineThread()
{
    while (true)
    {
        if (start_mapping_offline_)
        {
            start_mapping_offline_ = false;
            mapping_offline_result_ = StopMapping(route_id_);            
        }
        sleep(1);
    }
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
