/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hmi_converter_app.cpp
 * @brief This cpp file defines hmi converter app class
 * @author yuepengfei(yuepengfei@holomaitc.com)
 * @date 2022/05/23
 */

#include <hmi_converter/hmi_converter_app.h>

namespace holo
{
namespace parking_cmw_app
{
namespace hmi_converter
{
HmiConverterApp::HmiConverterApp(const uint32_t id) : bus_(id, "")
{
    LOG(INFO) << "domain id: " << id;
    running_                    = true;
}

void HmiConverterApp::Setup(const std::string& config_file)
{
    if (!GetParameters(config_file))
    {
        LOG(WARNING) << "hmi converter app could not get the parameters.";
        return;
    }

    // subscriber
    LOG(INFO) << "subscribe init";
    // ApaEventRequest, 从操作屏幕获取Apa任务的设置内容
    sub_apa_event_request_ = bus_.AddReader<ApaEventRequest>(apa_event_request_topic_);
    sub_apa_event_request_.SetOnDataAvailableCallback(
        std::bind(&HmiConverterApp::CallbackApaEventRequest, this, std::placeholders::_1));
    // RemoteControlSignal, 原创遥控内容获取
    sub_remote_control_signal_ = bus_.AddReader<RemoteControlSignal>(remote_control_signal_topic_);
    sub_remote_control_signal_.SetOnDataAvailableCallback(
        std::bind(&HmiConverterApp::CallbackRemoteControlSignal, this, std::placeholders::_1));

    sub_parking_odometry_ = bus_.AddReader<Odometryf>(parking_odometry_topic_);
    sub_parking_odometry_.SetOnDataAvailableCallback(
        std::bind(&HmiConverterApp::CallbackParkingOdometry, this, std::placeholders::_1));
        
    sub_mapping_odometry_ = bus_.AddReader<Odometryf>(mapping_odometry_topic_);
    sub_mapping_odometry_.SetOnDataAvailableCallback(
        std::bind(&HmiConverterApp::CallbackMappingOdometry, this, std::placeholders::_1));
    LOG(INFO) << "subscribe init success";

    // publisher
    LOG(INFO) << "publisher init";
    // HmiCommand, 向泊车状态机发布泊车命令
    pub_hmi_command_ = bus_.AddWriter<HmiCommand>(hmi_command_topic_);
    LOG(INFO) << "publisher init success";
    
    LOG(INFO) << "opendds bus init";
    bus_.Enable();
    LOG(INFO) << "opendds bus init success";

    // Init class
    LOG(INFO) << "class init";
    hmi_manager_ = std::make_shared<HmiManager>();
    LOG(INFO) << "class init success";
    main_thread_ = std::make_shared<std::thread>(std::bind(&HmiConverterApp::HmiManagementThread, this));

    while (BusType::IsRunning())
    {
        BusType::Spin(1);       
    }
    running_ = false;
    LOG(INFO) << "HmiConverterApp: start join thread...";
    main_thread_->join();
}

void HmiConverterApp::HmiManagementThread()
{
    // LOG(INFO) << "Enter main thread.";
    holo::Timer timer(10);

    HmiInput hmi_input;
    memset(&hmi_input, 0 , sizeof(hmi_input));
    
    while (running_)
    {
        timer.Start();
        // 待pub内容
        HmiCommand hmi_command;
        uint32_t route_id;
        // 状态机运转，刷新待pub内容
        hmi_manager_->Pipeline(hmi_command, route_id);
        // 刷新Hmi输出
        PubHmiCommand(hmi_command);
        
        timer.Stop();
    }
}

bool_t HmiConverterApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node         = holo::yaml::LoadFile(config_file);
        hmi_state_topic_              = node["hmi_state_topic"].as<std::string>();
        apa_event_request_topic_      = node["hpa_event_request_topic"].as<std::string>();
        remote_control_signal_topic_  = node["remote_control_signal_topic"].as<std::string>();
        hmi_parking_state_topic_      = node["hmi_parking_state_topic"].as<std::string>();
        parking_odometry_topic_       = node["parking_odometry_topic"].as<std::string>();
        hpa_event_response_topic_     = node["hpa_event_response_topic"].as<std::string>();
        hpa_info_topic_               = node["hpa_info_topic"].as<std::string>();
        hmi_command_topic_            = node["hmi_command_topic"].as<std::string>();
        PASRemoteParkingMode_topic_   = node["PASRemoteParkingMode_topic"].as<std::string>();
        PASRemoteParkingEnable_topic_ = node["PASRemoteParkingEnable_topic"].as<std::string>();
        APADrvReq_topic_              = node["APADrvReq_topic"].as<std::string>();
        APAActFuncInd_topic_          = node["APAActFuncInd_topic"].as<std::string>();
        APAAuthst_topic_              = node["APAAuthst_topic"].as<std::string>();
        PASCommandDoorsUnlock_topic_  = node["PASCommandDoorsUnlock_topic"].as<std::string>();
        PASAPASt_topic_               = node["PASAPASt_topic"].as<std::string>();
        FAPARPAReady_topic_           = node["FAPARPAReady_topic"].as<std::string>();
        FAPA_RPAChallenge2SBM_topic_  = node["FAPA_RPAChallenge2SBM_topic"].as<std::string>();
        FAPA_RPAChallenge1SBM_topic_  = node["FAPA_RPAChallenge1SBM_topic"].as<std::string>();
        tbox_command_topic_           = node["tbox_command_topic"].as<std::string>();
        cloud_path_info_topic_        = node["cloud_path_info_topic"].as<std::string>();
        tbox_signal_topic_            = node["tbox_signal_topic"].as<std::string>();
        hmi_routing_request_topic_    = node["hmi_routing_request_topic"].as<std::string>();
        mapping_odometry_topic_       = node["mapping_odometry_topic"].as<std::string>();
        download_shared_route_topic_  = node["download_shared_route_topic"].as<std::string>();
        shared_route_req_topic_       = node["shared_route_req_topic"].as<std::string>();
        //geographical_location_topic_  = node["geographical_location_topic"].as<std::string>();
        chassis_state_topic_          = node["chassis_state"].as<std::string>();
        universal_can_tx_topic_       = node["univeral_can_tx"].as<std::string>();
    }
    catch (std::exception& e)
    {
        return false;
    }
    return true;
}

void HmiConverterApp::CallbackApaEventRequest(const ApaEventRequest& msg)
{
    if(!hmi_manager_->GetCommonInterface()->ReceiveApaEventRequest(msg)) {
        LOG(ERROR) << "Could not receive apa event requset";
    }
}

void HmiConverterApp::CallbackRemoteControlSignal(const RemoteControlSignal& msg)
{
    static uint32_t count = 0;
    if (++count % 3000 == 0) {
        LOG(INFO) << "CallbackRemoteControlSignal(" << count << " / 3000).";
    }
    if(!hmi_manager_->GetCommonInterface()->ReceiveRemoteControlSignal(msg)) {
        LOG(ERROR) << "Could not receive remote control signal";
    }
}

void HmiConverterApp::CallbackParkingOdometry(const Odometryf& msg)
{
    static uint32_t count = 0;
    if (++count % 600 == 0) {
        LOG(INFO) << "CallbackParkingOdometry(" << count << " / 600).";
    }
    if(!hmi_manager_->GetCommonInterface()->ReceiveParkingOdodmetry(msg)) {
        LOG(ERROR) << "Could not receive parking odometry";
    }
}

void HmiConverterApp::CallbackMappingOdometry(const Odometryf& msg)
{
    static uint32_t count = 0;
    if (++count % 300 == 0) {
        LOG(INFO) << "CallbackMappingOdometry(" << count << " / 300).";
    }
    if(!hmi_manager_->GetCommonInterface()->ReceiveMappingOdometry(msg)) {
        LOG(ERROR) << "Could not receive mapping odometry";
    }
}

void HmiConverterApp::PubHmiCommand(const HmiCommand& hmi_command) {
    pub_hmi_command_.Write(hmi_command);
}

}  // namespace hmi_converter
}  // namespace parking_cmw_app
}  // namespace holo

void signalHandler(int sig)
{
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
    raise(sig);
}

int main(int argc, char** argv)
{
    std::string program_version = "V0.2.3.2";

    cxxopts::Options options("HmiConverter", "hmi converter node");
    options.add_options()("h,help", "help message")("c,config_file", "Configuration file path",
                                                    cxxopts::value<std::string>()->default_value(""))(
        "d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("0"))(
        "v,verbose", "if also outputs glog to console", cxxopts::value<holo::bool_t>()->default_value("true"))(
        "n,node_name", "holo parking hmi converter node name",
        cxxopts::value<std::string>()->default_value("HmiConverter"))(
        "m,min_log_level",
        "minimum log level, INFO(0), WARNING(1), ERROR(2), "
        "FATAL(3)",
        cxxopts::value<holo::uint8_t>()->default_value("0"))(
        "hololog_config", "hololog yaml",
        cxxopts::value<std::string>()->default_value("./config/holo_parking_cmw_app/app_config/hololog.yaml"));

    options.parse(argc, argv);
    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 1;
    }

    std::string hololog_config = options["hololog_config"].as<std::string>();
    YAML::Node  node           = YAML::LoadFile(hololog_config);
    holo::log::HoloLogger::Initialize(node["hololog"], argv[0]);
    signal(SIGSEGV, signalHandler);
    signal(SIGINT, signalHandler);

    std::string node_name = options["node_name"].as<std::string>();
    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);

    LOG(WARNING) << "Program version: " << program_version;
    LOG(WARNING) << "Program last modify time: " << __TIME__ << " " << __DATE__;
    LOG(WARNING) << "Program package root directory: " << holo::GetHoloRootDirectory();;

    uint32_t domain_id = options["domain_id"].as<uint32_t>();
    holo::parking_cmw_app::hmi_converter::HmiConverterApp app(domain_id);
    app.Setup(options["config_file"].as<std::string>());

    return 0;
};
