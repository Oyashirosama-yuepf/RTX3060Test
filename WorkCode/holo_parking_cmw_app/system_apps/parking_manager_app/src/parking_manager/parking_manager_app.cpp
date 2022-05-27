/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_manager_app.cpp
 * @brief This cpp file defines parking manager app class
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#include <parking_manager/parking_manager_app.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{
    
ParkingManagerApp::ParkingManagerApp(int32_t id, std::string const& ns) : bus_{id, ns} {
    running_ = true;
}

void ParkingManagerApp::Setup(const std::string& config_file)
{
    if (!GetParameters(config_file))
    {
        LOG(WARNING) << "parking manager app could not get the parameters.";
        return;
    }

    // hmi_command_topic
    LOG(INFO) << "subscribe init";
    sub_hmi_command_topic_ = bus_.AddReader<HmiCommand>(hmi_command_topic_);
    sub_hmi_command_topic_.SetOnDataAvailableCallback(
        std::bind(&ParkingManagerApp::CallbackHmiCommand, this, std::placeholders::_1));
    // psd_state_topic
    sub_psd_status_ = bus_.AddReader<PsdStatus>(psd_state_topic_);
    sub_psd_status_.SetOnDataAvailableCallback(
    std::bind(&ParkingManagerApp::CallbackPsdState, this, std::placeholders::_1));
    // hand_shake_topic
    sub_hand_shake_ = bus_.AddReader<uint32_t>(hand_shake_topic_);
    sub_hand_shake_.SetOnDataAvailableCallback(
    std::bind(&ParkingManagerApp::CallbackHandShake, this, std::placeholders::_1)); 
    // planning_state_topic
    sub_planning_state_ = bus_.AddReader<uint32_t>(planning_state_topic_);
    sub_planning_state_.SetOnDataAvailableCallback(
        std::bind(&ParkingManagerApp::CallbackPlanningState, this, std::placeholders::_1));

    // subscriber chassis_state_topic
    sub_chassis_status_ = bus_.AddReader<ChassisState>(chassis_state_topic_);
    sub_chassis_status_.SetOnDataAvailableCallback(
        std::bind(&ParkingManagerApp::CallbackChassisStatus, this, std::placeholders::_1));
    // user_operation_topic
    sub_user_operation_ = bus_.AddReader<UserOperation>(user_operation_topic_);
    sub_user_operation_.SetOnDataAvailableCallback(
        std::bind(&ParkingManagerApp::CallbackUserOperation, this, std::placeholders::_1));
    // vehicle_body_state_topic
    sub_vehicle_body_status_ = bus_.AddReader<VehicleBodyState>(vehicle_body_state_topic_);
    sub_vehicle_body_status_.SetOnDataAvailableCallback(
        std::bind(&ParkingManagerApp::CallbackVehicleBodyStatus, this, std::placeholders::_1));

    // odometry_topic
    sub_odometry_ = bus_.AddReader<Odometryd>(odometry_topic_);
    sub_odometry_.SetOnDataAvailableCallback(
        std::bind(&ParkingManagerApp::CallbackOdometry, this, std::placeholders::_1));
    LOG(INFO) << "subscribe init success";

    // publisher
    LOG(INFO) << "publisher init";
    pub_Heartbeat_bag_ = bus_.AddWriter<uint32_t>(apa_heartbeat_bag_topic_);
    pub_route_id_ = bus_.AddWriter<uint32_t>(apa_route_id_topic_);
    pub_apa_ctrl_req_ = bus_.AddWriter<bool_t>(apa_ctrl_req_topic_);
    pub_apa_parking_state_ = bus_.AddWriter<APAParkingState>(apa_parking_state_topic_);
    pub_apa_parking_command_ = bus_.AddWriter<APAParkingManagerCommand>(apa_parking_manager_command_topic_);
    LOG(INFO) << "publisher init success";

    // init pipeline
    LOG(INFO) << "class init";
    parking_manager_ = std::make_shared<holo::parking_cmw_app::parking_manager::ParkingManager>(interface_config_);
    LOG(INFO) << "class init success";
    // init thread
    parking_manager_thread_ = 
        std::make_shared<std::thread>(std::bind(&ParkingManagerApp::ParkingManagerThread, this));

    while (BusType::IsRunning())
    {
        LOG(INFO) << "receive infoinfo" << parking_manager_->GetCommonInterface()->GetHmiCommand().GetHmiCommand() << "value";
        BusType::Spin(1);
    }
}

void ParkingManagerApp::ParkingManagerThread() {
    holo::Timer timer(10);

    while (running_) {
        // 待pub内容
        APAParkingState apa_state;
        APAParkingManagerCommand apa_park_command;
        bool apa_ctrl_req;
        uint32_t route_id;
    
        timer.Start();
        uint8_t outputvalue = parking_manager_->GetCommonInterface()->GetHmiCommand().GetHmiCommand();
        LOG(INFO) << "receive info :" << outputvalue;
        // 状态机刷新pub内容
        parking_manager_->Pipeline(apa_state, apa_park_command, apa_ctrl_req, route_id);
        // 消息pub
        PubApaState(apa_state);
        PubParkingCommand(apa_park_command);
        PubCtrlReq(apa_ctrl_req);
        PubRouteId(route_id);
        timer.Stop();
    }
}

bool_t ParkingManagerApp::GetParameters(const std::string& config_file) {
    try {
        holo::yaml::Node node                        = holo::yaml::LoadFile(config_file);
        interface_config_.enable_dds_interface       = node["enable_dds_interface"].as<bool_t>();
        interface_config_.enable_cloud_interface     = node["enable_cloud_interface"].as<bool_t>();
        interface_config_.enable_bluetooth_interface = node["enable_bluetooth_interface"].as<bool_t>();

        chassis_state_topic_                         = node["chassis_state_topic"].as<std::string>();
        vehicle_body_state_topic_                    = node["vehicle_body_state_topic"].as<std::string>();
        user_operation_topic_                        = node["user_operation_topic"].as<std::string>();
        planning_state_topic_                        = node["planning_state_topic"].as<std::string>();
        hmi_command_topic_                           = node["hmi_command_topic"].as<std::string>();
        odometry_topic_                              = node["odometry_topic"].as<std::string>();
        psd_state_topic_                             = node["psd_state_topic"].as<std::string>();
        hand_shake_topic_                            = node["hand_shake_topic"].as<std::string>();

        apa_parking_manager_command_topic_           = node["apa_parking_manager_command_topic"].as<std::string>();
        apa_parking_state_topic_                     = node["apa_parking_state_topic"].as<std::string>();
        apa_ctrl_req_topic_                          = node["apa_ctrl_req_topic"].as<std::string>();
        apa_route_id_topic_                          = node["apa_route_id_topic"].as<std::string>();
        apa_heartbeat_bag_topic_                     = node["apa_heartbeat_bag_topic"].as<std::string>();
        
        yaml_file_                                   = node["cloud_yaml_file"].as<std::string>();
    }
    catch (std::exception& e)
    {
        return false;
    }
    return true;
}

bool_t ParkingManagerApp::PublisherHeartBeat() {
    static uint32_t heart_beat = 0;
    pub_Heartbeat_bag_.Write(heart_beat++);

    return true;
}

void ParkingManagerApp::CallbackPlanningState(const uint32_t& msg) {
    if (!parking_manager_->GetCommonInterface()->ReceivePlanningState(msg))
    {
        LOG(ERROR) << "Could not push the planning state to queue";
        return;
    }
}

void ParkingManagerApp::CallbackHmiCommand(const HmiCommand& msg) {
    LOG(INFO) << "push into hmi command";
    if(!parking_manager_->GetCommonInterface()->ReceiveHmiCommand(msg))
    {
        LOG(ERROR) << "Could not push the Hmi Command to queue";
        return;
    }
}

void ParkingManagerApp::CallbackChassisStatus(const ChassisState& msg) {
    if (!parking_manager_->GetCommonInterface()->ReceiveChassisState(msg))
    {
        LOG(ERROR) << "Could not push the chassis state to queue";
        return;
    }
}

void ParkingManagerApp::CallbackVehicleBodyStatus(const VehicleBodyState& msg) {
    if(!parking_manager_->GetCommonInterface()->ReceiveVehicleBodyStatus(msg))
    {
        LOG(ERROR) << "Could not push the vehicle state to queue";
        return;
    }
}

void ParkingManagerApp::CallbackPsdState(const PsdStatus& msg) {
    if(!parking_manager_->GetCommonInterface()->ReceivePsdState(msg))
    {
        LOG(ERROR) << "Could not push the psd status to queue";
        return;
    }
}

void ParkingManagerApp::CallbackHandShake(const uint32_t& msg) {
    if(!parking_manager_->GetCommonInterface()->ReceiveHandShake(msg))
    {
        LOG(ERROR) << "Could not push the hand shake to queue";
        return;
    }
}

void ParkingManagerApp::CallbackUserOperation(const UserOperation& msg) {
    if(!parking_manager_->GetCommonInterface()->ReceiveUserOperation(msg))
    {
        LOG(ERROR) << "Could not push the vehicle state to queue";
        return;
    }
}

void ParkingManagerApp::CallbackOdometry(const Odometryd& msg) {
    if (!parking_manager_->GetCommonInterface()->ReceiveOdometry(msg))
    {
        LOG(ERROR) << "Could not push the odometry to queue";
        return;
    }
}

void ParkingManagerApp::PubApaState(const APAParkingState apa_state) {
    APAParkingState output = apa_state;
    LOG(INFO) << "apa_state: " << static_cast<uint8_t>(output.GetCurrentState());
    pub_apa_parking_state_.Write(output);
}

void ParkingManagerApp::PubParkingCommand(const APAParkingManagerCommand apa_park_command) {
    APAParkingManagerCommand output = apa_park_command;
    LOG(INFO) << "apa park command: " << output.GetEnableApaStatus();
    pub_apa_parking_command_.Write(output);
}

void ParkingManagerApp::PubCtrlReq(const bool_t ctrl_req) {
    bool_t output = ctrl_req;
    LOG(INFO) << "ctrl req: " << output;
    pub_apa_ctrl_req_.Write(output);
}

void ParkingManagerApp::PubRouteId(const uint32_t route_id) {
    uint32_t output = route_id;
    LOG(INFO) << "route_id: " << output;
    pub_route_id_.Write(output);
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

int main(int argc, char** argv) {
    cxxopts::Options options("ParkingManager", "parking_manager node");
    options.add_options()("h,help", "help message")("c,config_file", "Configuration file path",
                                                    cxxopts::value<std::string>()->default_value(""))(
        "d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("5"))(
        "v,verbose", "if also outputs glog to console", cxxopts::value<holo::bool_t>()->default_value("false"))(
        "n,node_name", "holo parking manager node name",
        cxxopts::value<std::string>()->default_value("ParkingManager"))(
        "m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)",
        cxxopts::value<holo::uint8_t>()->default_value("1"));

    options.parse(argc, argv);
    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 1;
    }

    holo::CreateHoloLogSubdirectory("holo_parking_cmw_app");
    std::string log_file =
        holo::GetLogFileAbsolutePath("holo_parking_cmw_app/" + options["node_name"].as<std::string>() + ".log");

    holo::log::HoloLogger::Initialize(argv[0]);

    std::string node_name = options["node_name"].as<std::string>();
    cmw_wrapper::BusType::Initialize(argc, argv, node_name);
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);
    uint32_t domain_id = options["domain_id"].as<uint32_t>();

    holo::parking_cmw_app::parking_manager::ParkingManagerApp app(domain_id, "");
    app.Setup(options["config_file"].as<std::string>());

    holo::log::HoloLogger::Shutdown();
    return 0;
};
