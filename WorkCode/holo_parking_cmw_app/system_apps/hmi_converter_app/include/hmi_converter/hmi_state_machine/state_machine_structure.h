/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_converter_app.h
 * @brief This header file defines hmi converter app class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#ifndef HOLO_PARKING_HMI_STATE_STRUCTURE_H_
#define HOLO_PARKING_HMI_STATE_STRUCTURE_H_

// apa event request 中间件通信变量需求, using ApaEventRequest
#include <holo/parking/system/apa_event_request.h>     
// remote contrl signal 中间件通信变量需求, using RemoteControlSignal, using TboxSignal, using SbmSignal
#include <holo/parking/system/remote_control_signal.h>  
// HmiCommand 中间件通信变量需求, using HmiCommand
#include <holo/parking/system/hmi_command.h>  
// odometry<f> 中间件通信变量需求, using Odometryf
#include <holo/common/odometry.h>

#include <array>
#include <memory>
#include <string>


namespace holo
{

namespace parking_cmw_app
{

namespace hmi_converter
{


using ApaEventRequest      = holo::parking::system::ApaEventRequest;
using RemoteControlSignal  = holo::parking::system::RemoteControlSignal;
using TboxSignal           = holo::parking::system::TboxSignal;
using SbmSignal            = holo::parking::system::SbmSignal;
using HmiCommand           = holo::parking::system::HmiCommand;
using Odometryf            = holo::common::Odometryf;

struct InterfaceConfig {
    bool_t enable_dds_interface;
    bool_t enable_cloud_interface;
    bool_t enable_bluetooth_interface;
};

struct HmiInput {
    ApaEventRequest apa_event_request_;
    RemoteControlSignal remote_control_signal_;
    Odometryf odometry_f_park;
    Odometryf odometry_f_map;
};

struct HmiOutput {
    HmiCommand hmi_command_;
};


}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo

#endif   /// HOLO_PARKING_HMI_STATE_STRUCTURE_H_