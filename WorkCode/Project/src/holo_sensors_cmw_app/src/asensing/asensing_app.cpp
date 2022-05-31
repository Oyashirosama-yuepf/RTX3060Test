/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file asensing_app.cpp
 * @brief A driver for asensing messages output
 * @author zhangtongyang@holomatic.com
 * @date 2021-5-12
 */

#include <asensing/asensing_app.h>
#include <csignal>

namespace holo_cmw
{
template <typename T>
void AsensingDriverApp<T>::Setup(const std::string& config_file)
{
    LOG(INFO) << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "asensing driver app could not load file!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    asen_pos_pub_             = bus_.AddWriter<GnssPvt>(gnss_pvt_topic_);
    asen_pos_translation_pub_ = bus_.AddWriter<GnssPvt>(gnss_pvt_translation_topic_);
    imu_pub_                  = bus_.AddWriter<Imud>(imu_topic_);

    /* Creat device */
    try
    {
        if (!holo::IsAbsolutePath(extrinsic_))
        {
            extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
        }
        LOG(INFO) << "loading extrinsics from " << extrinsic_;
        holo::common::Extrinsicf extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
        driver_                            = std::make_shared<holo::sensors::asensing::AsensingDriverT<T>>(extrinsic);
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "app failed to create asensing driver";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }

    std::function<void(const holo::common::GnssPvt&)> hpos =
        std::bind(&AsensingDriverApp<T>::PositionCallback0, this, std::placeholders::_1);
    std::function<void(const holo::common::GnssPvt&)> htpos =
        std::bind(&AsensingDriverApp<T>::PositionCallback1, this, std::placeholders::_1);
    std::function<void(const holo::common::Imud&)> imu_handler =
        std::bind(&AsensingDriverApp<T>::ImuCallback, this, std::placeholders::_1);

    driver_->InstallPositionCallback(hpos);
    driver_->InstallPositionTranslationCallback(htpos);
    driver_->InstallCallback(imu_handler);

    holo::yaml::Node node = holo::yaml::LoadFile(config_file)["interface"];
    interface_            = std::make_shared<UdpInterface<T>>(node);
    std::function<void(const holo::sensors::format::HoloCanPacket&)> handler =
        std::bind(&holo::sensors::asensing::AsensingDriverT<T>::ParseData, driver_.get(), std::placeholders::_1);
    interface_->InstallCallback(handler);

    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename T>
bool_t AsensingDriverApp<T>::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node       = holo::yaml::LoadFile(config_file);
        gnss_pvt_topic_             = node["gnss_pvt_topic"].as<std::string>();
        gnss_pvt_translation_topic_ = node["gnss_pvt_translation_topic"].as<std::string>();
        extrinsic_                  = node["extrinsic"].as<std::string>();
        imu_topic_                  = node["imu_topic"].as<std::string>();
        use_gps_stamp_              = node["use_gps_stamp"].as<bool>();

        LOG(INFO) << "gnss_pvt_topic             = " << gnss_pvt_topic_;
        LOG(INFO) << "gnss_pvt_translation_topic = " << gnss_pvt_translation_topic_;
        LOG(INFO) << "extrinsic                  = " << extrinsic_;
        LOG(INFO) << "imu_topic                  = " << imu_topic_;
        LOG(INFO) << "use_gps_stamp              = " << use_gps_stamp_;
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what();
        return false;
    }
    return true;
}

template <typename T>
void AsensingDriverApp<T>::PositionCallback0(const holo::common::GnssPvt& msg)
{
    asen_pos_pub_.Write(msg);
}

template <typename T>
void AsensingDriverApp<T>::PositionCallback1(const holo::common::GnssPvt& msg)
{
    asen_pos_translation_pub_.Write(msg);
}

template <typename T>
void AsensingDriverApp<T>::ImuCallback(const holo::common::Imud& msg)
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
    cxxopts::Options options("AsensingDriver", "Asensing driver node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("AsensingDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/asensing_" + node_name + ".log");
    uint32_t log_level = options["min_log_level"].as<holo::uint8_t>();
    log_level = std::min<uint32_t>(log_level, 6);
    log_level = ((log_level * 10000 + 9999) / 10000) * 10000;

    holo::log::RollingFileConfigure log_file("log_file", log_file_name);
    holo::log::HoloLogger::Add(log_file);
    holo::log::HoloLogger::SetLogLevel(static_cast<holo::log::LogLevel>(log_level));
    holo::log::HoloLogger::SetLogLevel(holo::log::ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME,
        options.count("verbose") ? (static_cast<holo::log::LogLevel>(log_level)) : (holo::log::LogLevel::OFF));
    holo::log::HoloLogger::SetLogLevel(holo::log::ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME,
        options.count("verbose") ? (static_cast<holo::log::LogLevel>(log_level)) : (holo::log::LogLevel::OFF));

    signal(SIGSEGV, signalSegHandler);
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);

    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    std::string      config_file = options["config_file"].as<std::string>();
    holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
    std::string      format      = node["format"].as<std::string>();
    LOG(INFO) << "format = " << format;

    try
    {
        if (format == "holocan")
        {
            using FormatType = holo::sensors::format::HoloCanPacket;
            holo_cmw::AsensingDriverApp<FormatType> driver(domain_id, "");
            driver.Setup(options["config_file"].as<std::string>());
        }
        else
        {
            LOG(ERROR) << "unsupported format configuration: " << format;
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << e.what();
    }

    holo::log::HoloLogger::Shutdown();
    return 0;
}