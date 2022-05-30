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

#ifndef HOLO_PARKING_HMI_CONVERTER_APP_H_
#define HOLO_PARKING_HMI_CONVERTER_APP_H_

#include <cmw_wrapper/cmw_bus.h>
#include <holo/map/map_navigation_request.h>
#include <holo/os/time.h>
#include <holo/os/timer.h> 

#include <hmi_converter/interface_manager/common_interface.h>
#include <hmi_converter/hmi_manager.h>

#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>
#include <holo_base_msg/traits.h>

#include <signal.h>
#include <chrono>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <exception>
#include <iostream>
#include <mutex>
#include <thread>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{

using BusType = cmw_wrapper::BusType;

class HmiConverterApp
{

public:   // 构造函数
    HmiConverterApp(const uint32_t id);
public:   // 析构函数
    ~HmiConverterApp() = default;
public:   
    //  初始化
    void Setup(const std::string& config_file);

private:  
    bool_t GetParameters(const std::string& config_file);
    void   HmiManagementThread();
    // 进程间通信,接收回调函数
    void   CallbackApaEventRequest(const ApaEventRequest& msg);
    void   CallbackRemoteControlSignal(const RemoteControlSignal& msg);
    void   CallbackParkingOdometry(const Odometryf& msg);
    void   CallbackMappingOdometry(const Odometryf& msg);
    // 进程间通信，发送函数
    void   PubHmiCommand(const HmiCommand& hmi_command);

private:  
    // bus
    BusType bus_;
    // 进程间通信，获取Reader
    BusType::ReaderType<ApaEventRequest> sub_apa_event_request_;
    BusType::ReaderType<RemoteControlSignal> sub_remote_control_signal_;
    BusType::ReaderType<Odometryf> sub_parking_odometry_;
    BusType::ReaderType<Odometryf> sub_mapping_odometry_;
    // 进程间通信，发送Writer
    BusType::WriterType<HmiCommand> pub_hmi_command_;
    // topic
    std::string apa_event_request_topic_;
    std::string remote_control_signal_topic_;
    std::string hmi_parking_state_topic_;
    std::string parking_odometry_topic_;
    std::string mapping_odometry_topic_;
    std::string hpa_event_response_topic_;
    std::string hpa_info_topic_;
    std::string hmi_command_topic_;
    std::string hmi_state_topic_;
    std::string PASRemoteParkingMode_topic_;
    std::string PASRemoteParkingEnable_topic_;
    std::string APADrvReq_topic_;
    std::string APAActFuncInd_topic_;
    std::string APAAuthst_topic_;
    std::string PASCommandDoorsUnlock_topic_;
    std::string PASAPASt_topic_;
    std::string FAPARPAReady_topic_;
    std::string FAPA_RPAChallenge2SBM_topic_;
    std::string FAPA_RPAChallenge1SBM_topic_;
    std::string tbox_command_topic_;
    std::string cloud_path_info_topic_;
    std::string tbox_signal_topic_;
    std::string hmi_routing_request_topic_;
    std::string geographical_location_topic_;
    std::string chassis_state_topic_;
    std::string universal_can_tx_topic_;
    std::string download_shared_route_topic_;
    std::string shared_route_req_topic_;
private:
    // class
    std::shared_ptr<HmiManager> hmi_manager_;
    // thread
    std::shared_ptr<std::thread> main_thread_;
private:
    std::string yaml_file_;
    bool_t running_;
};

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo

#endif  // HOLO_PARKING_HMI_CONVERTER_APP_H_
