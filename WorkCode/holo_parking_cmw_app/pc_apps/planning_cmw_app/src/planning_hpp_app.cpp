/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file planning_hpp.cpp
 * @brief the implementation of planning hpp
 * @author zhangchun(zhangchun@holomatic.com)
 * @date 2019-09-20
 */

#include <holo/utils/holo_root.h>
#include <cmw_wrapper/utils/cxxopts.hpp>
#include <holo/log/hololog.h>

#include <planning_hpp_app.h>

static const char* APP_NAME        = "planning_hpp";
static const char* APP_DESCRIPTION = "planning hpp node";

namespace holo_cmw
{
PlanningHppApp::PlanningHppApp(int argc, char** argv, const std::string& config_file, uint32_t domain_id) : hz_(20)
{
    InitConfig(config_file);

    hpp_ = holo::planning::HppBuilder::CreateHpp(file_name_, hz_);
    hpp_->SetListener(this);

    BusType::Initialize(argc, argv, APP_NAME);
    signal(SIGINT, BusType::SignalHandler);
    bus_ = std::make_shared<BusType>(domain_id, "");

    if (!path_topic_.empty())
    {
        path_writer_ = bus_->AddWriter<holo::Pathd>(path_topic_);
    }

    if (!pridict_path_topic_.empty())
    {
        pridict_path_writer_ = bus_->AddWriter<holo::Pathd>(pridict_path_topic_);
    }

    if (!planning_command_topic_.empty())
    {
        planning_command_writer_ = bus_->AddWriter<holo::uint32_t>(planning_command_topic_);
    }

    if (!path_attribute_topic_.empty())
    {
        path_attribute_writer_ = bus_->AddWriter<PathAttribute>(path_attribute_topic_);
    }

    if (!planning_state_topic_.empty())
    {
        planning_state_writer_ = bus_->AddWriter<holo::uint32_t>(planning_state_topic_);
    }

    if (!fault_state_topic_.empty())
    {
        fault_state_writer_ = bus_->AddWriter<holo::uint32_t>(fault_state_topic_);
    }

    if (!chassis_state_topic_.empty())
    {
        chassis_state_reader_ = bus_->AddReader<holo::ChassisState>(chassis_state_topic_);
        chassis_state_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackChassisState, this, std::placeholders::_1));
    }

    if (!free_space_topic_.empty())
    {
        free_space_reader_ = bus_->AddReader<holo::common::AutoFreespace<holo::geometry::Point3f>>(free_space_topic_);
        free_space_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackFreeSpace, this, std::placeholders::_1));
    }

    /// TODO: uss reader
    /*
    if (!obstacle_list_topic_.empty())
    {
        sub_obstacle_list_state_ = cmw_.AddSubscriber<CMW::ObstacleGeneralListTopicType>(
            obstacle_list_topic_, 1,
            std::bind(&PlanningHppApp::CallbackObstacleListState, this, std::placeholders::_1));
    }
    */

    if (!detection_topic_.empty())
    {
        detection_reader_ = bus_->AddReader<ObstacleGeneralPtrList>(detection_topic_);
        detection_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackDetection, this, std::placeholders::_1));
    }

    if (!odometry_topic_.empty())
    {
        odometry_reader_ = bus_->AddReader<holo::common::Odometryd>(odometry_topic_);
        odometry_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackOdometry, this, std::placeholders::_1));
    }

    if (!recovery_topic_.empty())
    {
        recovery_status_reader_ = bus_->AddReader<holo::uint32_t>(recovery_topic_);
        recovery_status_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackRecovery, this, std::placeholders::_1));
    }

    if (!hpp_parking_command_topic_.empty())
    {
        hpp_parking_command_reader_ = bus_->AddReader<holo::uint32_t>(hpp_parking_command_topic_);
        hpp_parking_command_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackHppParkingCommand, this, std::placeholders::_1));
    }

    if (!heartbeat_topic_.empty())
    {
        heartbeat_reader_ = bus_->AddReader<holo::uint32_t>(heartbeat_topic_);
        heartbeat_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackHeartbeat, this, std::placeholders::_1));
    }

    if (!hpa_command_topic_.empty())
    {
        hpa_command_reader_ = bus_->AddReader<holo::uint32_t>(hpa_command_topic_);
        hpa_command_reader_.SetOnDataAvailableCallback(
            std::bind(&PlanningHppApp::CallbackHpaCommand, this, std::placeholders::_1));
    }

    hpp_->Run();
}

void PlanningHppApp::Run()
{
    bus_->Spin(1);
    hpp_->Terminate();
}

void PlanningHppApp::InitConfig(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node      = holo::yaml::LoadFile(config_file);
        hz_                        = node["hz"].as<holo::float64_t>(hz_);
        file_name_                 = node["planner_yaml"].as<std::string>(file_name_);
        path_topic_                = node["path_topic"].as<std::string>(path_topic_);
        pridict_path_topic_        = node["pridict_path_topic"].as<std::string>(pridict_path_topic_);
        planning_command_topic_    = node["planning_command_topic"].as<std::string>(planning_command_topic_);
        path_attribute_topic_      = node["path_attribute_topic"].as<std::string>(path_attribute_topic_);
        chassis_state_topic_       = node["chassis_state_topic"].as<std::string>(chassis_state_topic_);
        obstacle_list_topic_       = node["obstacle_list_topic"].as<std::string>(obstacle_list_topic_);
        free_space_topic_          = node["free_space_topic"].as<std::string>(free_space_topic_);
        detection_topic_           = node["detection_topic"].as<std::string>(detection_topic_);
        odometry_topic_            = node["odometry_topic"].as<std::string>(odometry_topic_);
        recovery_topic_            = node["recovery_topic"].as<std::string>(recovery_topic_);
        hpp_parking_command_topic_ = node["hpp_parking_command_topic"].as<std::string>(hpp_parking_command_topic_);
        heartbeat_topic_           = node["heartbeat_topic"].as<std::string>(heartbeat_topic_);
        hpa_command_topic_         = node["hpa_command_topic"].as<std::string>(hpa_command_topic_);
        planning_state_topic_      = node["planning_state_topic"].as<std::string>(planning_state_topic_);
        fault_state_topic_               = node["fault_state_topic"].as<std::string>(fault_state_topic_);
    }
    catch (std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure : " << config_file << std::endl << e.what();
    }
}

void PlanningHppApp::PubPath(holo::Pathd& path)
{
    path_writer_.Write(path);
}

void PlanningHppApp::PubPridictPath(holo::Pathd& pridict_path)
{
    pridict_path_writer_.Write(pridict_path);
}

void PlanningHppApp::PubPlanningCommand(holo::planning::PlanningCommand planning_command)
{
    planning_command_writer_.Write(static_cast<uint32_t>(planning_command));
}

void PlanningHppApp::PubPathAttribute(PathAttribute& path_attribute)
{
    path_attribute_writer_.Write(path_attribute);
}

void PlanningHppApp::PubPlanningState(holo::planning::HPAPlanningState planning_state)
{
    planning_state_writer_.Write(static_cast<uint32_t>(planning_state));
}

void PlanningHppApp::PubFaultState(uint32_t fault_state)
{
    fault_state_writer_.Write(fault_state);
}


void PlanningHppApp::PubPlanningStateAVP(holo::planning::HPAPlanningState planning_state)
{
    UNREFERENCE_PARAM(planning_state);
}

/// TODO: dbg visualization
/*
void PlanningHppApp::DbgHandler(std::vector<std::vector<holo::Point3d>>& dbg_info)
{
    if (pub_dbg_.GetNumSubscribers() > 0)
    {
        CMW::MarkerArrayTopicType output;
        visualization_msgs::Marker delete_all;
        delete_all.action = visualization_msgs::Marker::DELETEALL;
        output.markers.push_back(delete_all);

        visualization_msgs::Marker line_strip;
        line_strip.header.frame_id = "WORLD";
        line_strip.action = visualization_msgs::Marker::ADD;
        line_strip.type = visualization_msgs::Marker::LINE_STRIP;
        line_strip.scale.x = 1.0;
        line_strip.scale.y = 1.0;
        line_strip.scale.z = 1.0;
        line_strip.pose.orientation.x = 0.0;
        line_strip.pose.orientation.y = 0.0;
        line_strip.pose.orientation.z = 0.0;
        line_strip.pose.orientation.w = 1.0;
        line_strip.lifetime = ros::Duration(200.0);

        geometry_msgs::Point point;

        //narrow obstacles
        for (size_t i = 0; i < dbg_info.size(); ++i)
        {
            line_strip.points.clear();
            for (size_t j = 0; j < dbg_info[i].size(); ++j)
            {
                point.x = dbg_info[i][j].x();
                point.y = dbg_info[i][j].y();
                point.z = 0;
                line_strip.points.push_back(point);
            }
            line_strip.ns = "dbg";
            line_strip.id = 100 + i;
            line_strip.color.b = 1.0;
            line_strip.color.a = 1.0;
            output.markers.push_back(line_strip);
        }

        pub_dbg_.Write(output);
    }
}
*/

void PlanningHppApp::CallbackChassisState(holo::ChassisState const& chassis_state)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    std::shared_ptr<holo::ChassisState> chassis_state_ptr = std::make_shared<holo::ChassisState>(chassis_state);
    if (!hpp_->GetGateway()->ReceiveChassisState(chassis_state_ptr))
    {
        LOG(ERROR) << "Could not push the car state to queue";
    }
}

void PlanningHppApp::CallbackFreeSpace(holo::common::AutoFreespace<holo::geometry::Point3f> const& free_space)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    std::shared_ptr<holo::common::AutoFreespace<holo::geometry::Point3f>> free_space_ptr =
        std::make_shared<holo::common::AutoFreespace<holo::geometry::Point3f>>(free_space);
    if (!hpp_->GetGateway()->ReceiveFreeSpace(free_space_ptr))
    {
        LOG(ERROR) << "Could not push the freespace to queue";
    }
}

void PlanningHppApp::CallbackDetection(ObstacleGeneralPtrList const& detection)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    std::shared_ptr<ObstacleGeneralPtrList> detection_ptr =
        std::make_shared<ObstacleGeneralPtrList>(detection);
    if (!hpp_->GetGateway()->ReceiveDetection(detection_ptr))
    {
        LOG(ERROR) << "Could not push the detection to queue";
        return;
    }
}

/// TODO: uss readers
/*
void PlanningHppApp::CallbackObstacleListState(const CMW::ObstacleGeneralListTopicType& msg)
{
    std::shared_ptr<holo::ObstacleGeneralPtrList> obstacle_list = std::make_shared<holo::ObstacleGeneralPtrList>();
    holo_cmw::Convert(msg, *obstacle_list);

    if (!hpp_->GetGateway()->ReceiveObstacleState(obstacle_list))
    {
        LOG(ERROR) << "Could not push the obstacle list to queue";
        return;
    }
}
*/

void PlanningHppApp::CallbackOdometry(holo::common::Odometryd const& odometry)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    std::shared_ptr<holo::common::Odometryd> odometry_ptr = std::make_shared<holo::common::Odometryd>(odometry);
    if (!hpp_->GetGateway()->ReceiveOdometry(odometry_ptr))
    {
        LOG(ERROR) << "Could not push the odometry to queue.";
    }
}

void PlanningHppApp::CallbackRecovery(holo::uint32_t recovery_status)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    if (!hpp_->GetGateway()->ReceiveRecoveryStatus(recovery_status))
    {
        LOG(ERROR) << "Could not push the recovery to queue.";
    }
}

void PlanningHppApp::CallbackHppParkingCommand(holo::uint32_t hpp_parking_command)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    if (!hpp_->GetGateway()->ReceiveHppParkingCommand(hpp_parking_command))
    {
        LOG(ERROR) << "Could not push the park_cmd to queue.";
    }
}

void PlanningHppApp::CallbackHeartbeat(holo::uint32_t heartbeat)
{
    if (!hpp_ || !hpp_->GetGateway())
    {
        return;
    }

    if (!hpp_->GetGateway()->ReceiveHeartbeat(heartbeat))
    {
        LOG(ERROR) << "Could not push the heartbeat to queue.";
    }
}

void PlanningHppApp::CallbackHpaCommand(holo::uint32_t hpa_command)
{
    if (!hpp_->GetGateway()->ReceiveHpaCommand(hpa_command))
    {
        LOG(ERROR) << "Could not push the hpa command to queue.";
    }
}

}  // namespace holo_cmw

int main(int argc, char** argv)
{
    std::string config_filepath = holo::GetHoloConfigRootDirectory();
    config_filepath += "/holo_planning_parking_cmw_app/app_config/planning_hpp_app.yaml";

    cxxopts::Options options(APP_NAME, APP_DESCRIPTION);
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(config_filepath))
        ("v,verbose", "if also outputs glog to console", cxxopts::value<bool>()->default_value("false"))
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value(APP_NAME))
        ("m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)", cxxopts::value<holo::uint8_t>()->default_value("1"))
        ("d, domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("5"));
    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 1;
    }

    uint32_t    domain_id   = options["domain_id"].as<uint32_t>();
    std::string config_file = options["config_file"].as<std::string>();
    LOG(WARNING) << "domain id and config file: " << domain_id << ", " << config_file;

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

    holo_cmw::PlanningHppApp app(argc, argv, config_file, domain_id);
    app.Run();

    // google::ShutdownGoogleLogging();
    return 0;
}
