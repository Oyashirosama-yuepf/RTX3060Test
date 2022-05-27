/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_interface.cpp
 * @brief This cpp file defines parking manager common interface management
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#include <hmi_converter/interface_manager/common_interface.h>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{

CommonInterface::CommonInterface()
{
}

bool_t CommonInterface::ReceiveApaEventRequest(const ApaEventRequest& apa_event_request)
{
    std::lock_guard<std::mutex> guard(mutex_apa_event_request_);
    apa_event_request_ = apa_event_request;

    return true;
}

bool_t CommonInterface::ReceiveRemoteControlSignal(const RemoteControlSignal& remote_control_signal)
{
    std::lock_guard<std::mutex> guard(mutex_remote_control_signal_);
    remote_control_signal_ = remote_control_signal;
    sbm_signal_ = remote_control_signal.GetSbmSignal();
    tbox_signal_ = remote_control_signal.GetTboxSignal();

    return true;
}

bool_t CommonInterface::ReceiveParkingOdodmetry(const Odometryf& parking_odometry)
{
    std::lock_guard<std::mutex> guard(mutex_parking_odometry_);
    parking_odometry_ = parking_odometry;

    return true;
}

bool_t CommonInterface::ReceiveMappingOdometry(const Odometryf & mapping_odometry)
{
    std::lock_guard<std::mutex> guard(mutex_mapping_odometry_);
    mapping_odometry_ = mapping_odometry;

    return true;
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
