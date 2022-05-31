/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common_interface.h
 * @brief This header file defines Hmi common interface management
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/28
 */

#ifndef HOLO_HMI_COMMON_INTERFACE_H
#define HOLO_HMI_COMMON_INTERFACE_H

#include <mutex>
#include <glog/logging.h>
#include <hmi_converter/hmi_state_machine/hmi_state_machine.h>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{

class CommonInterface
{

public:
    explicit CommonInterface();
    ~CommonInterface() = default;

    bool_t ReceiveApaEventRequest(const ApaEventRequest& apa_event_request);
    bool_t ReceiveRemoteControlSignal(const RemoteControlSignal& remote_control_signal);
    bool_t ReceiveParkingOdodmetry(const Odometryf& parking_odometry);
    bool_t ReceiveMappingOdometry(const Odometryf& mapping_odometry);
    
    ApaEventRequest GetApaEventRequest() const noexcept {
        return apa_event_request_;
    }

    RemoteControlSignal GetRemoteControlSignal() const noexcept {
        return remote_control_signal_;
    }

    Odometryf GetParkingOdometry() const noexcept {
        return parking_odometry_;
    }

    Odometryf GetMappingOdometry() const noexcept {
        return mapping_odometry_;
    }

private:
    /* subscriber messages */
    SbmSignal sbm_signal_;
    TboxSignal tbox_signal_;
    ApaEventRequest apa_event_request_;
    RemoteControlSignal remote_control_signal_;
    Odometryf parking_odometry_;
    Odometryf mapping_odometry_;
    
    /* mutex*/
    std::mutex mutex_apa_event_request_;
    std::mutex mutex_remote_control_signal_;
    std::mutex mutex_parking_odometry_;
    std::mutex mutex_mapping_odometry_;
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  // HOLO_HMI_COMMON_INTERFACE_H
