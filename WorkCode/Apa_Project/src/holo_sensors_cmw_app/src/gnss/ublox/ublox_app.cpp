/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ublox_driver_app.cpp
 * @brief A driver for ublox messages output
 * @author houyujian<houyujian@holomatic.com>
 * @date 2019-12-16
 */

#include <csignal>
#include <gnss/ublox/ublox_app.h>

namespace holo_cmw
{
template <typename T>
void UbloxDriverApp<T>::Setup(const std::string& config_file)
{
    LOG(INFO) << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "ublox driver app could not load file!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    ubx_raw_pub_             = bus_.AddWriter<GnssRawMeasurement>(gnss_raw_measurement_topic_);
    ubx_pos_pub_             = bus_.AddWriter<GnssPvt>(gnss_pvt_topic_);
    ubx_pos_translation_pub_ = bus_.AddWriter<GnssPvt>(gnss_pvt_translation_topic_);

    driver_ = std::make_shared<holo::sensors::ublox::UbloxDriverT<T>>();

    /* install callback */
    std::function<void(const GnssRawMeasurement&)> hraw =
        std::bind(&UbloxDriverApp<T>::GnssRawMeasurementCallback, this, std::placeholders::_1);
    std::function<void(const GnssPvt&)> hpos =
        std::bind(&UbloxDriverApp<T>::PositionCallback0, this, std::placeholders::_1);
    std::function<void(const GnssPvt&)> htpos =
        std::bind(&UbloxDriverApp<T>::PositionCallback1, this, std::placeholders::_1);
    driver_->InstallGnssRawCallback(hraw);
    driver_->InstallPositionCallback(hpos);
    driver_->InstallPositionTranslationCallback(htpos);

    /* interface */
    holo::yaml::Node node = holo::yaml::LoadFile(config_file)["interface"];
    interface_            = std::make_shared<UdpInterface<T>>(node);
    std::function<void(const T&)> handler =
        std::bind(&holo::sensors::ublox::UbloxDriverT<T>::ParseData, driver_.get(), std::placeholders::_1);
    interface_->InstallCallback(handler);

    while (cmw_wrapper::BusType::IsRunning())
    {
        cmw_wrapper::BusType::Spin(1);
    }
}

template <typename T>
bool_t UbloxDriverApp<T>::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node       = holo::yaml::LoadFile(config_file);
        gnss_raw_measurement_topic_ = node["gnss_raw_measurement_topic"].as<std::string>();
        gnss_pvt_topic_             = node["gnss_pvt_topic"].as<std::string>();
        gnss_pvt_translation_topic_ = node["gnss_pvt_translation_topic"].as<std::string>();

        LOG(INFO) << "gnss_raw_measurement_topic = " << gnss_raw_measurement_topic_;
        LOG(INFO) << "gnss_pvt_topic             = " << gnss_pvt_topic_;
        LOG(INFO) << "gnss_pvt_translation_topic = " << gnss_pvt_translation_topic_;
    }
    catch (std::exception& e)
    {
        return false;
    }
    return true;
}

template <typename T>
void UbloxDriverApp<T>::GnssRawMeasurementCallback(const GnssRawMeasurement& msg)
{
    ubx_raw_pub_.Write(msg);
}

template <typename T>
void UbloxDriverApp<T>::PositionCallback0(const GnssPvt& msg)
{
    ubx_pos_pub_.Write(msg);
}

template <typename T>
void UbloxDriverApp<T>::PositionCallback1(const GnssPvt& msg)
{
    ubx_pos_translation_pub_.Write(msg);
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
    cxxopts::Options options("UbloxDriver", "Ublox driver node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("UbloxDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/ublox_" + node_name + ".log");
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
        std::string      format      = node["format"].as<std::string>();
        LOG(INFO) << "format = " << format;

        try
        {
            if (format == "rawbuf")
            {
                using FormatType = holo::sensors::ublox::RawbufferType;
                holo_cmw::UbloxDriverApp<FormatType> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
            else if (format == "someip")
            {
                using FormatType = holo::sensors::ublox::SomeipPacketType;
                holo_cmw::UbloxDriverApp<FormatType> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
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
