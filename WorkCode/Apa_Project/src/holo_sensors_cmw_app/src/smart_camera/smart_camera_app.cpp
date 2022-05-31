/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smart_camera_app.cpp
 * @brief A driver for ifv300 messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/09
 */

#include <holo/log/hololog.h>
#include <smart_camera/smart_camera_app.h>
#include <csignal>

namespace holo_cmw
{
using holo::sensors::bosch_mpc::BoschMpcDriverT;
using holo::sensors::horizon_matrix2::HorizonMatrix2DriverT;
using holo::sensors::ifv300::Ifv300DriverT;
using holo::sensors::mobileye::MobileyeDriverT;

using holo::sensors::format::HoloCanPacket;
using holo::sensors::format::SomeipPacket;
template <typename Td, typename Ti>
void SmartCameraApp<Td, Ti>::Setup(const std::string& config_file, bool_t blocking_mode)
{
    if (!GetParameters(config_file))
    {
        std::string info = "app failed to load config parameters";
        LOG(ERROR) << info;
        throw std::invalid_argument(info);
    }
    roadframe_pub_ = bus_->AddWriter<RoadFrameType>(roadframe_topic_);
    obstacles_pub_ = bus_->AddWriter<ObstaclePtrListType>(obstacles_topic_);
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
        std::string info = "failed to create smart camera driver";
        LOG(ERROR) << info << ", exception: " << e.what();
        throw std::runtime_error(info);
    }
    const RoadFrameCallbackType roadframe_handler =
        std::bind(&SmartCameraApp<Td, Ti>::RoadFrameCallback, this, std::placeholders::_1);
    const ObstacleListCallbackType obstacles_handler =
        std::bind(&SmartCameraApp<Td, Ti>::ObstaclesCallback, this, std::placeholders::_1);
    driver_->InstallCallback(roadframe_handler);
    driver_->InstallCallback(obstacles_handler);
    if (spd_limit_sign_topic_ != "")
    {
        spd_limit_sign_pub_ = bus_->AddWriter<uint8_t*>(spd_limit_sign_topic_);
        const SpdLimitSignListCallbackType spd_limit_sign_handler =
            std::bind(&SmartCameraApp<Td, Ti>::SpdLimitSignCallback, this, std::placeholders::_1);
        driver_->InstallCallback(spd_limit_sign_handler);
    }
    /* interface */
    std::function<void(const typename Td::Intype&)> h = std::bind(&Td::ParseData, driver_.get(), std::placeholders::_1);
    interface_->InstallCallback(h);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif

    thread_ = std::make_shared<std::thread>(&SmartCameraApp<Td, Ti>::Background, this);

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Td, typename Ti>
void SmartCameraApp<Td, Ti>::Background()
{
    uint32_t frames_obstacles_last      = 0;
    uint32_t frames_roadframe_last      = 0;
    uint32_t frames_spd_limit_sign_last = 0;
    holo::Timer timer(1.0f);
    while (cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();
        uint32_t frames_obstacles_this      = frames_obstacles_;
        uint32_t frames_roadframe_this      = frames_roadframe_;
        uint32_t frames_spd_limit_sign_this = frames_spd_limit_sign_;        
        if (live_callback_)
        {
            live_callback_(static_cast<uint32_t>(SmtCameraMsgType::OBSTACLES),      frames_obstacles_this      - frames_obstacles_last);
            live_callback_(static_cast<uint32_t>(SmtCameraMsgType::ROADFRAME),      frames_roadframe_this      - frames_roadframe_last);
            live_callback_(static_cast<uint32_t>(SmtCameraMsgType::SPD_LIMIT_SIGN), frames_spd_limit_sign_this - frames_spd_limit_sign_last);
        }
        frames_obstacles_last      = frames_obstacles_this;
        frames_roadframe_last      = frames_roadframe_this;
        frames_spd_limit_sign_last = frames_spd_limit_sign_this;
        timer.Stop();
    }
}

template <typename Td, typename Ti>
bool SmartCameraApp<Td, Ti>::GetParameters(const std::string& config_file)
{
    LOG(INFO) << "loading parameters from: " << config_file;
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        extrinsic_            = node["extrinsic"].as<std::string>();
        roadframe_topic_      = node["roadframe_topic"].as<std::string>();
        obstacles_topic_      = node["obstacles_topic"].as<std::string>();
        spd_limit_sign_topic_ = node["spd_limit_sign_topic"].as<std::string>("");
        /* show */
        LOG(INFO) << "extrinsic            = " << extrinsic_;
        LOG(INFO) << "roadframe_topic      = " << roadframe_topic_;
        LOG(INFO) << "obstacles_topic      = " << obstacles_topic_;
        LOG(INFO) << "spd_limit_sign_topic = " << spd_limit_sign_topic_;
        /* interface */
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
void SmartCameraApp<Td, Ti>::RoadFrameCallback(const RoadFrameType& road_frame)
{
    frames_roadframe_++;
    roadframe_pub_.Write(road_frame);
}

template <typename Td, typename Ti>
void SmartCameraApp<Td, Ti>::ObstaclesCallback(const ObstaclePtrListType& obstacle_list)
{
    frames_obstacles_++;
    obstacles_pub_.Write(obstacle_list);
}

template <typename Td, typename Ti>
void SmartCameraApp<Td, Ti>::SpdLimitSignCallback(const SpdLimitSignListType& spd_sign)
{
    memset(spd_sign_data_, 0, SPD_SIGN_DATA_CAPACITY);

    for (uint32_t i=0; i<spd_sign.size(); i++)
    {
        spd_sign[i].Serialize(spd_sign_data_ + i*spd_sign[i].GetSerializedSize(), spd_sign[i].GetSerializedSize());
    }
    frames_spd_limit_sign_++;
    spd_limit_sign_pub_.Write(spd_sign_data_, spd_sign.size() * spd_sign[0].GetSerializedSize());
}
template class SmartCameraApp<MobileyeDriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
template class SmartCameraApp<MobileyeDriverT<holo::sensors::mobileye::SomeipPacketType>, UdpInterface<holo::sensors::mobileye::SomeipPacketType>>;
template class SmartCameraApp<Ifv300DriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
template class SmartCameraApp<Ifv300DriverT<holo::sensors::ifv300::SomeipPacketType>, UdpInterface<holo::sensors::ifv300::SomeipPacketType>>;
template class SmartCameraApp<BoschMpcDriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
template class SmartCameraApp<BoschMpcDriverT<holo::sensors::bosch_mpc::SomeipPacketType>, UdpInterface<holo::sensors::bosch_mpc::SomeipPacketType>>;
template class SmartCameraApp<HorizonMatrix2DriverT<HoloCanPacket>, UdpInterface<HoloCanPacket>>;
#if defined(ENABLE_MDC300_CAN_INTERFACE)
template class SmartCameraApp<MobileyeDriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
template class SmartCameraApp<Ifv300DriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
template class SmartCameraApp<BoschMpcDriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
template class SmartCameraApp<HorizonMatrix2DriverT<HoloCanPacket>, MdcCanInterface<HoloCanPacket>>;
#endif
}  // namespace holo_cmw

#if defined (APP_MAIN_FUNCTION)
static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "smart_camera");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("SmartCameraDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/smart_camera_" + node_name + ".log");
    uint32_t    log_level     = options["min_log_level"].as<holo::uint8_t>();
    log_level                 = std::min<uint32_t>(log_level, 6);
    log_level                 = ((log_level * 10000 + 9999) / 10000) * 10000;

    holo::log::RollingFileConfigure log_file("log_file", log_file_name);
    holo::log::HoloLogger::Add(log_file);
    holo::log::HoloLogger::SetLogLevel(static_cast<holo::log::LogLevel>(log_level));
    holo::log::HoloLogger::SetLogLevel(holo::log::ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME,
                                       options.count("verbose") ? (static_cast<holo::log::LogLevel>(log_level)) :
                                                                  (holo::log::LogLevel::OFF));

    signal(SIGSEGV, signalSegHandler);
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);
    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    std::string      config_file = options["config_file"].as<std::string>();
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
    std::string      type        = node["type"].as<std::string>();
    std::string      interface   = node["interface"]["type"].as<std::string>();
    std::string      format      = node["format"].as<std::string>();
    LOG(INFO) << "type      = " << type;
    LOG(INFO) << "interface = " << interface;
    LOG(INFO) << "format    = " << format;
    std::string tif = type + ":" + interface + ":" + format;

    using holo::sensors::bosch_mpc::BoschMpcDriverT;
    using holo::sensors::horizon_matrix2::HorizonMatrix2DriverT;
    using holo::sensors::ifv300::Ifv300DriverT;
    using holo::sensors::mobileye::MobileyeDriverT;
    using holo::sensors::me8::Me8Driver;

    using holo::sensors::format::HoloCanPacket;
    using holo::sensors::format::SomeipPacket;

    try
    {
        if (tif == "me3:udp:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = MobileyeDriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "me3:udp:someip")
        {
            using Tf = holo::sensors::mobileye::SomeipPacketType;
            using Td = MobileyeDriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "ifv300:udp:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = Ifv300DriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "ifv300:udp:someip")
        {
            using Tf = holo::sensors::ifv300::SomeipPacketType;
            using Td = Ifv300DriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "mpc2:udp:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = BoschMpcDriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "mpc2:udp:someip")
        {
            using Tf = holo::sensors::bosch_mpc::SomeipPacketType;
            using Td = BoschMpcDriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "matrix2:udp:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = HorizonMatrix2DriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if ("me8:udp:holocan")
        {
            using Tf = HoloCanPacket;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::SmartCameraApp<Me8Driver, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
#if defined(ENABLE_MDC300_CAN_INTERFACE)
        else if (tif == "me3:mdc:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = MobileyeDriverT<Tf>;
            using Ti = holo_cmw::MdcCanInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "ifv300:mdc:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = Ifv300DriverT<Tf>;
            using Ti = holo_cmw::MdcCanInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "mpc2:mdc:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = BoschMpcDriverT<Tf>;
            using Ti = holo_cmw::MdcCanInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
        else if (tif == "matrix2:mdc:holocan")
        {
            using Tf = HoloCanPacket;
            using Td = HorizonMatrix2DriverT<Tf>;
            using Ti = holo_cmw::MdcCanInterface<Tf>;
            holo_cmw::SmartCameraApp<Td, Ti> driver(domain_id, "");
            driver.Setup(config_file);
        }
#endif
        else
        {
            LOG(ERROR) << "unsupported type-interface-format configuration: " << tif;
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit: " << e.what();
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
#endif
