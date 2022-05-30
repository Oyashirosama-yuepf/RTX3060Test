/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file dds_interface.h
 * @brief This header file defines parking manager dds interface management
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_DDS_INTERFACE_H
#define HOLO_PARKING_DDS_INTERFACE_H

#include <deque>
#include <mutex>

#include <glog/logging.h>

#include <parking_manager/utils/mapping_utils.h>
#include <parking_manager/parking_state_machine/state_machine_structure.h>
#include <parking_manager/utils/parking_utils.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

class DdsInterface
{

public:
    explicit DdsInterface();
    ~DdsInterface() = default;

private:
	void MappingOfflineThread();
	std::mutex mutex_hmi_command_;
	bool_t hmi_updated_;
	//std::deque<HmiCommand> hmi_command_list_;

	uint32_t test_timer_;
	std::shared_ptr<std::thread> mapping_offline_thread_;
	uint32_t route_id_;
	bool_t start_mapping_offline_;
	std::string mapping_offline_result_;
	PathAttribute path_attribute_[10];
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  //HOLO_PARKING_DDS_INTERFACE_H
