/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file conti_radar_app.cpp
 * @brief A driver for conti radar messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2019/12/12
 */

#include <conti_radar/conti_radar_app.h>
#include <csignal>
#include <holo/log/hololog.h>

namespace holo_cmw
{
using holo::sensors::format::HoloCanPacket;
using holo::sensors::conti_radar::ContiRadarDriverT;

template <typename Td, typename Ti>
void RadarAppT<Td, Ti>::Setup(const std::string& config_file, bool_t blocking_mode)
{
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "app failed to load config parameters";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }
    /* publisher */
    #ifdef CMW_WRAPPER_ENABLE_ROS
    obstacles_pub_ = bus_->AddWriter<ObstaclePtrList,ros_wrapper::DefaultConversionTraits<ObstaclePtrList>>(obstacles_topic_);
    #else
    obstacles_pub_ = bus_->AddWriter<ObstaclePtrList>(obstacles_topic_);
    #endif // ROS
    
    try
    {
        if (!holo::IsAbsolutePath(extrinsic_))
        {
            extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
        }
        LOG(INFO) << "loading extrinsics from " << extrinsic_;
        holo::common::Extrinsicf extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
        driver_                            = std::make_shared<Td>(extrinsic);
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "app failed to create conti radar driver";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    std::function<void(const ObstaclePtrList&)> h0 = std::bind(&RadarAppT<Td, Ti>::ObstaclesCallback, this,
        std::placeholders::_1);
    driver_->InstallCallback(h0);
    /* interface */
    std::function<void(const typename Td::InType&)> h = std::bind(&Td::ParseData, driver_.get(), std::placeholders::_1);
    interface_->InstallCallback(h);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&RadarAppT<Td, Ti>::Background, this);

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Td, typename Ti>
void RadarAppT<Td, Ti>::Background()
{
    uint32_t    frames_last = 0;
    holo::Timer timer(1.0f);
    while (cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();
        uint32_t frames_this = frames_;
        if (live_callback_)
        {
            live_callback_(0, frames_this - frames_last);
        }
        LOG(INFO) << "data hz = " << frames_this - frames_last;
        frames_last = frames_this;
        timer.Stop();
    }
}

template <typename Td, typename Ti>
bool RadarAppT<Td, Ti>::GetParameters(const std::string& config_file)
{
    LOG(INFO) << "loading parameters from: " << config_file;
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        extrinsic_            = node["extrinsic"].as<std::string>();
        obstacles_topic_      = node["obstacles_topic"].as<std::string>();
        /* show */
        LOG(INFO) << "extrinsic       = " << extrinsic_;
        LOG(INFO) << "obstacles_topic = " << obstacles_topic_;

        holo::yaml::Node nodeif = node["interface"];
        interface_              = std::make_shared<Ti>(nodeif);
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what();
        return false;
    }
    return true;
}

template <typename Td, typename Ti>
void RadarAppT<Td, Ti>::ObstaclesCallback(const ObstaclePtrList& obstacle_list)
{
    frames_++;
    obstacles_pub_.Write(obstacle_list);
}

template class RadarAppT<ContiRadarDriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
#if defined(ENABLE_MDC300_CAN_INTERFACE)
template class RadarAppT<ContiRadarDriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
#endif

}  // namespace holo_cmw

#if defined(APP_MAIN_FUNCTION)
static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "conti radar driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("ContiRadar"))
        ("m,min_log_level", "minimum log level, ALL/TRACE/0, D/1, I/2, W/3, E/4, F/5, OFF/6", cxxopts::value<holo::uint8_t>()->default_value("0"))
        ("d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("0"))
        ;
    // clang-format on
    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 0;
    }

    uint32_t    domain_id = options["domain_id"].as<uint32_t>();
    std::string node_name = options["node_name"].as<std::string>();
    holo::CreateHoloLogSubdirectory("holo_sensors");
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/conti_radar_" + node_name + ".log");
    uint32_t log_level = options["min_log_level"].as<holo::uint8_t>();
    log_level = std::min<uint32_t>(log_level, 6);
    log_level = ((log_level * 10000 + 9999) / 10000) * 10000;

    holo::log::RollingFileConfigure log_file("log_file", log_file_name);
    holo::log::HoloLogger::Add(log_file);
    holo::log::HoloLogger::SetLogLevel(static_cast<holo::log::LogLevel>(log_level));
    holo::log::HoloLogger::SetLogLevel(holo::log::ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME,
        options.count("verbose") ? (static_cast<holo::log::LogLevel>(log_level)) : (holo::log::LogLevel::OFF));

    signal(SIGSEGV, signalSegHandler);
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);

    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    try
    {
        std::string      config_file = options["config_file"].as<std::string>();
        holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
        std::string      interface   = node["interface"]["type"].as<std::string>("udp");
        std::string      format      = node["format"].as<std::string>("holocan");
        LOG(INFO) << "interface = " << interface;
        LOG(INFO) << "format    = " << format;

        std::string desc = interface + ":" + format;
        try
        {
            if (desc == "udp:holocan")
            {
                using Tf = holo::sensors::format::HoloCanPacket;
                using Td = holo::sensors::conti_radar::ContiRadarDriverT<Tf>;
                using Ti = holo_cmw::UdpInterface<Tf>;
                holo_cmw::RadarAppT<Td, Ti> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
            else if (desc == "udp:someip")
            {
                using Tf = holo::sensors::conti_radar::SomeipPacketType;
                using Td = holo::sensors::conti_radar::ContiRadarDriverT<Tf>;
                using Ti = holo_cmw::UdpInterface<Tf>;
                holo_cmw::RadarAppT<Td, Ti> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
#if defined(ENABLE_MDC300_CAN_INTERFACE)
            else if (desc == "mdc:holocan")
            {
                using Tf = holo::sensors::format::HoloCanPacket;
                using Td = holo::sensors::conti_radar::ContiRadarDriverT<Tf>;
                using Ti = holo_cmw::MdcCanInterface<Tf>;
                holo_cmw::RadarAppT<Td, Ti> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
#endif
            else
            {
                LOG(ERROR) << "unsupported format configuration: " << format;
            }
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "appication failed, exit";
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit";
    }

    holo::log::HoloLogger::Shutdown();
    return 0;
}
#endif
