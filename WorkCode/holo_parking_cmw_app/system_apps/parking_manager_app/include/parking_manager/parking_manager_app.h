/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_manager_app.h
 * @brief This header file defines parking manager app class
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#ifndef HOLO_CMW_APPS_PARKING_MANAGER_APP_H_
#define HOLO_CMW_APPS_PARKING_MANAGER_APP_H_

#include <chrono>
#include <exception>
#include <iostream>
#include <memory>
#include <mutex>
#include <signal.h>
#include <string>
#include <thread>

#include <holo_base_msg/traits.h>
#include <holo/common/chassis_state.h>
#include <holo/common/odometry.h>
#include <holo/os/time.h> 
#include <holo/os/timer.h>
#include <holo/utils/yaml.h>

#include <cmw_wrapper/cmw_bus.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

#include <parking_manager/parking_manager.h>


namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

using BusType = cmw_wrapper::BusType;

using HmiCommand = holo::parking::system::HmiCommand;
using ChassisState = holo::common::ChassisState;
using VehicleBodyState = holo::common::VehicleBodyState;
using UserOperation = holo::common::UserOperation;
using Odometryd = holo::common::Odometryd;

using APAParkingManagerCommand = holo::parking::parking_manager::APAParkingManagerCommand;
using APAParkingState = holo::parking::parking_manager::APAParkingState;


class ParkingManagerApp
{
public:  // 构造函数
	ParkingManagerApp(int32_t id, std::string const& ns);
public:  // 析构函数
    ~ParkingManagerApp() = default;
public:
    // 初始化
    void   Setup(const std::string& config_file);
    void   ParkingManagerThread();

private:
    // 获取config
    bool_t GetParameters(const std::string& config_file);
    // 进程间通信，接收回调函数
    void   CallbackPlanningState(const uint32_t& msg);
    void   CallbackChassisStatus(const ChassisState& msg);
    void   CallbackVehicleBodyStatus(const VehicleBodyState& msg);
    void   CallbackHmiCommand(const HmiCommand& msg);
    void   CallbackOdometry(const Odometryd& msg);
    void   CallbackPsdState(const PsdStatus& msg);
    void   CallbackHandShake(const uint32_t &msg);
    void   CallbackVehicleInfoChassisStatus(const ChassisState& msg);
    void   CallbackUserOperation(const UserOperation& msg);
    // 进程间通信，发送消息
    bool_t PublisherHeartBeat();
    void   PubApaState(const APAParkingState apa_state);
    void   PubParkingCommand(const APAParkingManagerCommand apa_park_manager_command);
    void   PubCtrlReq(const bool_t ctrl_req);
    void   PubRouteId(const uint32_t route_id);

private:  //进程间通信相关
    // bus
    BusType bus_;
    // Reader
    BusType::ReaderType<uint32_t> sub_planning_state_;
    BusType::ReaderType<ChassisState> sub_chassis_status_;
    BusType::ReaderType<VehicleBodyState> sub_vehicle_body_status_;
    BusType::ReaderType<UserOperation> sub_user_operation_;
    BusType::ReaderType<HmiCommand> sub_hmi_command_topic_;
    BusType::ReaderType<uint32_t> sub_hand_shake_;
    BusType::ReaderType<Odometryd> sub_odometry_;
    BusType::ReaderType<PsdStatus> sub_psd_status_;
    // Writer
    BusType::WriterType<uint32_t> pub_parking_command_;
    BusType::WriterType<uint32_t> pub_Heartbeat_bag_;
    BusType::WriterType<uint32_t>  pub_route_id_;
    BusType::WriterType<APAParkingManagerCommand> pub_apa_parking_command_;
    BusType::WriterType<APAParkingState> pub_apa_parking_state_;
    BusType::WriterType<bool_t> pub_apa_ctrl_req_;
    // 配置文件
    std::string yaml_file_; 
    // 接收topic
    std::string chassis_state_topic_;
    std::string vehicle_body_state_topic_;
    std::string user_operation_topic_;
    std::string planning_state_topic_;
    std::string hmi_command_topic_;
    std::string odometry_topic_;
    std::string psd_state_topic_;
    std::string hand_shake_topic_;
    // 发送topic
    std::string apa_parking_manager_command_topic_;
    std::string apa_parking_state_topic_;
    std::string apa_ctrl_req_topic_;
    std::string apa_route_id_topic_;
    std::string apa_heartbeat_bag_topic_;
private:  // 子线程
    // class
    std::shared_ptr<holo::parking_cmw_app::parking_manager::ParkingManager> parking_manager_;
    // thread
    std::shared_ptr<std::thread> parking_manager_thread_;
private: 
    bool_t running_;
    InterfaceConfig interface_config_;
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif //HOLO_CMW_APPS_PARKING_MANAGER_APP_H_
