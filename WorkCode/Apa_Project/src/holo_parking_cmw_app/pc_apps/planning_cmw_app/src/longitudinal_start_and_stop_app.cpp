/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file longitudinal_start_and_stop_app.cpp
 * @brief the implementation of longitudinal_start_and_stop_app
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-11-11
 */

#include <holo/utils/holo_root.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <holo/log/hololog.h>

#include <longitudinal_start_and_stop_app.h>

static const char* APP_NAME        = "longitudinal_start_and_stop_app";
static const char* APP_DESCRIPTION = "longitudinal_start_and_stop_app";

namespace holo_cmw
{
LongitudinalStartAndStopApp::LongitudinalStartAndStopApp(int argc, char** argv, const std::string& config_file, uint32_t domain_id)
  : hz_(10)
{
    InitConfig(config_file);

    BusType::Initialize(argc, argv, APP_NAME);
    signal(SIGINT, BusType::SignalHandler);
    bus_ = std::make_shared<BusType>(domain_id, "");

    longitudinal_start_and_stop_ = std::make_shared<LongitudinalStartAndStop>(hz_, lib_config_name_);
    longitudinal_start_and_stop_->Suspend();
    longitudinal_start_and_stop_->SetListener(this);

    if (!path_topic_.empty())
    {
        path_writer_ = bus_->AddWriter<holo::Pathd>(path_topic_);
    }

    if (!planning_command_topic_.empty())
    {
        planning_command_writer_ = bus_->AddWriter<holo::uint32_t>(planning_command_topic_);
    }

    if (!chassis_state_topic_.empty())
    {
        chassis_state_reader_ = bus_->AddReader<holo::ChassisState>(chassis_state_topic_);
        chassis_state_reader_.SetOnDataAvailableCallback(
            std::bind(&LongitudinalStartAndStopApp::CallbackChassisState, this, std::placeholders::_1));
    }

    if (!odometry_topic_.empty())
    {
        odometry_reader_ = bus_->AddReader<holo::common::Odometryd>(odometry_topic_);
        odometry_reader_.SetOnDataAvailableCallback(
            std::bind(&LongitudinalStartAndStopApp::CallbackOdometry, this, std::placeholders::_1));
    }

    longitudinal_start_and_stop_->Run();
}

void LongitudinalStartAndStopApp::Run()
{
    bus_->Spin(1);
    longitudinal_start_and_stop_->Terminate();
}

void LongitudinalStartAndStopApp::InitConfig(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node   = holo::yaml::LoadFile(config_file);
        hz_                     = node["hz"].as<holo::float64_t>(hz_);
        lib_config_name_        = node["lib_config_name"].as<std::string>(lib_config_name_);
        path_topic_             = node["path_topic"].as<std::string>(path_topic_);
        planning_command_topic_ = node["planning_command_topic"].as<std::string>(planning_command_topic_);
        chassis_state_topic_    = node["chassis_state_topic"].as<std::string>(chassis_state_topic_);
        odometry_topic_         = node["odometry_topic"].as<std::string>(odometry_topic_);
    }
    catch (std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure : " << config_file << std::endl << e.what();
    }
}

void LongitudinalStartAndStopApp::PubPath(holo::Path& path)
{
    path_writer_.Write(path);
}

void LongitudinalStartAndStopApp::PubPlanningCommand(holo::planning::PlanningCommand planning_command)
{
    planning_command_writer_.Write(static_cast<uint32_t>(planning_command));
}

void LongitudinalStartAndStopApp::CallbackChassisState(holo::ChassisState const& chassis_state)
{
    std::shared_ptr<holo::ChassisState> chassis_state_ptr = std::make_shared<holo::ChassisState>(chassis_state);
    if (!longitudinal_start_and_stop_->GetGateway()->ReceiveChassisState(chassis_state_ptr))
    {
        LOG(ERROR) << "Could not push the car state to queue";
    }
}

void LongitudinalStartAndStopApp::CallbackOdometry(holo::common::Odometryd const& odometry)
{
    std::shared_ptr<holo::common::Odometryd> odometry_ptr = std::make_shared<holo::common::Odometryd>(odometry);
    if (!longitudinal_start_and_stop_->GetGateway()->ReceiveOdometry(odometry_ptr))
    {
        LOG(ERROR) << "Could not push the odometry to queue.";
    }
}

}  // namespace holo_cmw

int main(int argc, char** argv)
{
    std::string config_filepath = holo::GetHoloConfigRootDirectory();
    config_filepath += "/holo_planning_parking_cmw_app/app_config/longitudinal_start_and_stop_app.yaml";

    cxxopts::Options options(APP_NAME, APP_DESCRIPTION);
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(config_filepath))
        ("v,verbose", "if also outputs glog to console", cxxopts::value<bool>()->default_value("false"))
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value(APP_NAME))
        ("m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)", cxxopts::value<holo::uint8_t>()->default_value("1"))
        ("d, domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("5"));
    options.parse(argc, argv);

    uint32_t domain_id = options["domain_id"].as<uint32_t>();
    std::string config_file = options["config_file"].as<std::string>();
    if (config_file.empty())
    {
        LOG(INFO) << "missed argument: --config_file";
        return 1;
    }

    holo::CreateHoloLogSubdirectory("holo_planning_parking");
    std::string log_filepath =
        holo::GetLogFileAbsolutePath("holo_planning_parking/planning_" + options["node_name"].as<std::string>());

    // google::InitGoogleLogging(argv[0]);
    // google::SetLogDestination(google::FATAL, "");
    // google::SetLogDestination(google::ERROR, "");
    // google::SetLogDestination(google::WARNING, "");
    // google::SetLogDestination(google::INFO, log_filepath.c_str());
    // FLAGS_alsologtostderr = options["verbose"].as<bool>();
    // FLAGS_minloglevel     = options["min_log_level"].as<holo::uint8_t>();

    holo_cmw::LongitudinalStartAndStopApp app(argc, argv, config_file, domain_id);
    app.Run();

    // google::ShutdownGoogleLogging();
    return 0;
}
