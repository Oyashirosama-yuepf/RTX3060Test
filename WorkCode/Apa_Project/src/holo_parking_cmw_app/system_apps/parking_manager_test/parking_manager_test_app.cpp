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

#include <csignal>
#include <thread>
#include <unistd.h>

//#include <glog/logging.h>

#include <holo/common/chassis_state.h>
#include <holo/common/vehicle_body_state.h>
#include <holo/core/types.h>
#include <holo_base_msg/traits.h>

#include <cmw_wrapper/cmw_bus.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

class ParkingManagerTestApp
{
public:
    using BusType = cmw_wrapper::BusType;

    ParkingManagerTestApp(int32_t id, std::string const& ns) : bus_{id, ns}
    {
        route_id_reader_ = bus_.AddReader<uint32_t>("/holo/parking_manager/route_id");
        route_id_reader_.SetOnDataAvailableCallback(
            std::bind(&ParkingManagerTestApp::RouIdCallback, this, std::placeholders::_1));

        while (cmw_wrapper::BusType::IsRunning())
        {
            cmw_wrapper::BusType::Spin(1);
        }
    }

    void RouIdCallback(uint32_t const& input)
    {
        LOG(ERROR) << input;
    }

private:
    BusType                       bus_;
    BusType::ReaderType<uint32_t> route_id_reader_;
};

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "parking_manager_test");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("5"))
        ;
    // clang-format on
    options.parse(argc, argv);

    if (options.count("help"))
    {
        std::cout << options.help();
        return 0;
    }
    holo::log::HoloLogger::Initialize(argv[0]);
    // google::InitGoogleLogging(argv[0]);
    //    google::SetLogDestination(google::FATAL, "");
    //    google::SetLogDestination(google::ERROR, "");
    //    google::SetLogDestination(google::WARNING, "");
    //    google::SetLogDestination(google::INFO, "");
    //    FLAGS_alsologtostderr = true;
    cmw_wrapper::BusType::Initialize(argc, argv, "parking_manager_test");
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);
    uint32_t domain_id = options["domain_id"].as<uint32_t>();
    ParkingManagerTestApp(domain_id, "");
    holo::log::HoloLogger::Shutdown();
    // google::ShutdownGoogleLogging();
    return 0;
}
