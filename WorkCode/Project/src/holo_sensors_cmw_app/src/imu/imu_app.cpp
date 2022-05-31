/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna_app.cpp
 * @brief A driver for imu messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/09/17
 */

#include <imu/imu_app.h>
#include <csignal>

namespace holo_cmw
{
template <typename Td, typename Ti>
void ImuDriverApp<Td, Ti>::Setup(const std::string& config_file)
{
    LOG(INFO) << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "imu driver app could not load file!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    /* publisher */
    imu_pub_ = bus_.AddWriter<Imud>(imu_topic_);

    /* create device */
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
        oss << "app failed to create imu driver";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }

    /* install callback */
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&ImuDriverApp<Td, Ti>::ImuCallback, this, std::placeholders::_1);
    driver_->InstallCallback(imu_handler);
    /* interface */
    holo::yaml::Node node = holo::yaml::LoadFile(config_file)["interface"];
    interface_            = std::make_shared<Ti>(node);
    std::function<void(const typename Td::InType&)> h = std::bind(&Td::ParseData, driver_.get(), std::placeholders::_1);
    interface_->InstallCallback(h);

    while (cmw_wrapper::BusType::IsRunning())
    {
        cmw_wrapper::BusType::Spin(1);
    }
}

template <typename Td, typename Ti>
bool_t ImuDriverApp<Td, Ti>::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        extrinsic_            = node["extrinsic"].as<std::string>();
        imu_topic_            = node["imu_topic"].as<std::string>();
        use_gps_stamp_        = node["use_gps_stamp"].as<bool>();

        LOG(INFO) << "extrinsic     =" << extrinsic_;
        LOG(INFO) << "imu_topic     =" << imu_topic_;
        LOG(INFO) << "use_gps_stamp =" << use_gps_stamp_;
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what();
        return false;
    }

    return true;
}

template <typename Td, typename Ti>
void ImuDriverApp<Td, Ti>::ImuCallback(const holo::common::Imud& msg)
{
    Imud message = msg;
    if (!use_gps_stamp_)
    {
        uint32_t sec;
        uint32_t nsec;
        if (!holo::os::GetSystemTime(sec, nsec))
        {
            LOG(ERROR) << "Get system time error!";
            return;
        }
        message.SetTimestamp(holo::common::Timestamp(sec, nsec));
    }
    imu_pub_.Write(message);
}

}  // namespace holo_cmw

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "imu driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("ImuDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/imu_" + node_name + ".log");
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

    std::string      config_file = options["config_file"].as<std::string>();
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
    std::string      type        = node["type"].as<std::string>();
    std::string      interface   = node["interface"]["type"].as<std::string>();
    std::string      format      = node["format"].as<std::string>();
    LOG(INFO) << "type      = " << type;
    LOG(INFO) << "interface = " << interface;
    LOG(INFO) << "format    = " << format;
    std::string desc = type + ":" + interface + ":" + format;

    try
    {
        if (desc == "aceinna:udp:holocan")
        {
            using Tf = holo::sensors::format::HoloCanPacket;
            using Td = holo::sensors::aceinna::AceinnaDriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::ImuDriverApp<Td, Ti> driver(domain_id, "");
            driver.Setup(options["config_file"].as<std::string>());
        }
        else if (desc == "aceinna:udp:someip")
        {
            using Tf = holo::sensors::aceinna::SomeipPacketType;
            using Td = holo::sensors::aceinna::AceinnaDriverT<Tf>;
            using Ti = holo_cmw::UdpInterface<Tf>;
            holo_cmw::ImuDriverApp<Td, Ti> driver(domain_id, "");
            driver.Setup(options["config_file"].as<std::string>());
        }
#if defined(ENABLE_MDC300_CAN_INTERFACE)
        else if (desc == "aceinna:mdc:holocan")
        {
            using Tf = holo::sensors::format::HoloCanPacket;
            using Td = holo::sensors::aceinna::AceinnaDriverT<Tf>;
            using Ti = holo_cmw::MdcCanInterface<Tf>;
            holo_cmw::ImuDriverApp<Td, Ti> driver(domain_id, "");
            driver.Setup(options["config_file"].as<std::string>());
        }
#endif
        else
        {
            LOG(ERROR) << "unsupported type-interface-format configuration: " << desc;
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
