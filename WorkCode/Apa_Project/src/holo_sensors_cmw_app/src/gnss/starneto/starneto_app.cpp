/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file starneto_app.cpp
 * @brief A app for starneto messages output
 * @author wangzhaobing<wangzhaobing@holomatic.com>
 * @date 2022/1/28
 */

#include <gnss/starneto/starneto_app.h>
#include <holo/log/hololog.h>
#include <csignal>

namespace holo_cmw
{
using holo::sensors::format::HoloCanPacket;
using holo::sensors::starneto::StarnetoDriver;

template <typename Td, typename Ti>
void StarnetoAppT<Td, Ti>::Setup(const std::string& config_file, bool_t blocking_mode)
{
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "Starneto driver app conld not load file!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

#if defined(CMW_WRAPPER_ENABLE_ROS)
    pub_odometry_ = bus_->AddWriter<Odometryd, ros_wrapper::DefaultConversionTraits<Odometryd>>(odometry_topic_);
    pub_translation_odometry_ =
        bus_->AddWriter<Odometryd, ros_wrapper::DefaultConversionTraits<Odometryd>>(odometry_translation_topic_);
    pub_imu_      = bus_->AddWriter<Imud, ros_wrapper::DefaultConversionTraits<Imud>>(imu_topic_);
    pub_gnss_pvt_ = bus_->AddWriter<GnssPvt, ros_wrapper::DefaultConversionTraits<GnssPvt>>(gnss_pvt_topic_);
#else
    pub_odometry_             = bus_->AddWriter<Odometryd>(odometry_topic_);
    pub_translation_odometry_ = bus_->AddWriter<Odometryd>(odometry_translation_topic_);
    pub_imu_                  = bus_->AddWriter<Imud>(imu_topic_);
    pub_gnss_pvt_             = bus_->AddWriter<GnssPvt>(gnss_pvt_topic_);
#endif

    if (!holo::IsAbsolutePath(extrinsic_file_))
    {
        extrinsic_file_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_file_;
    }
    LOG(INFO) << "loading extrinsics from" << extrinsic_file_;
    auto extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_file_);
    LOG(INFO) << "done";
    try
    {
        driver_ = std::make_shared<Td>(extrinsic);
    }
    catch (const std::exception& e)
    {
        std::string s = "failed to create driver: ";
        s += e.what();
        LOG(ERROR) << s;
        throw std::runtime_error(s);
    }

    std::function<void(const Odometryd&)> odo_handler =
        std::bind(&StarnetoAppT<Td, Ti>::OdometryCallbackStarneto, this, std::placeholders::_1, std::ref(pub_odometry_));
    driver_->SetOdometryCallback(odo_handler);
    std::function<void(const Odometryd&)> odot_handler = std::bind(
        &StarnetoAppT<Td, Ti>::OdometryCallbackStarneto, this, std::placeholders::_1, std::ref(pub_translation_odometry_));
    driver_->SetOdometryTranslationCallback(odot_handler);
    std::function<void(const Imud&)> imu_handler =
        std::bind(&StarnetoAppT<Td, Ti>::ImuCallbackStarneto, this, std::placeholders::_1, std::ref(pub_imu_));
    driver_->SetImuCallback(imu_handler);
    std::function<void(const GnssPvt&)> pos_handler =
        std::bind(&StarnetoAppT<Td, Ti>::PositionCallbackStarneto, this, std::placeholders::_1, std::ref(pub_gnss_pvt_));
    driver_->SetPositionCallback(pos_handler);

    std::function<void(const holo::sensors::format::HoloCanPacket&)> h =
        std::bind(&StarnetoDriver::ParseData, driver_.get(), std::placeholders::_1);
    interface_->InstallCallback(h);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif

    thread_ = std::make_shared<std::thread>(&StarnetoAppT<Td, Ti>::Background, this);

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename Td, typename Ti>
void StarnetoAppT<Td, Ti>::Background()
{
    holo::Timer timer(1.0f);
    uint32_t    frames_odometry_last   = 0;
    uint32_t    frames_odometry_t_last = 0;
    uint32_t    frames_imu_last        = 0;
    uint32_t    frames_gnss_pvt_last   = 0;

    while (cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();

        uint32_t frames_odometry_this   = frames_odometry_;
        uint32_t frames_odometry_t_this = frames_odometry_t_;
        uint32_t frames_imu_this        = frames_imu_;
        uint32_t frames_gnss_pvt_this   = frames_gnss_pvt_;

        if (live_callback_)
        {
            live_callback_(static_cast<uint32_t>(StarnetoMsgType::ODOMETRY), frames_odometry_this - frames_odometry_last);
            live_callback_(static_cast<uint32_t>(StarnetoMsgType::ODOMETRY_T),
                           frames_odometry_t_this - frames_odometry_t_last);
            live_callback_(static_cast<uint32_t>(StarnetoMsgType::IMU), frames_imu_this - frames_imu_last);
            live_callback_(static_cast<uint32_t>(StarnetoMsgType::GNSS_PVT), frames_gnss_pvt_this - frames_gnss_pvt_last);
        }
        frames_odometry_last   = frames_odometry_this;
        frames_odometry_t_last = frames_odometry_t_this;
        frames_imu_last        = frames_imu_this;
        frames_gnss_pvt_last   = frames_gnss_pvt_this;

        timer.Stop();
    }
}

template <typename Td, typename Ti>
bool_t StarnetoAppT<Td, Ti>::GetParameters(const std::string& config_file)
{
    LOG(INFO) << "loading paramters from: " << config_file;

    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);

        rtk_server_ip_ = node["rtk_server_ip"].as<std::string>();
        LOG(ERROR) << "rtk_server_ip = " << rtk_server_ip_;
        rtk_server_port_ = node["rtk_server_port"].as<holo::uint16_t>(),
        LOG(ERROR) << "rtk_server_port = " << rtk_server_port_;
        use_holo_basestation_ = node["use_holo_basestation"].as<bool_t>();
        LOG(ERROR) << "use_holo_basestation = " << use_holo_basestation_;
        extrinsic_file_ = node["extrinsic_file"].as<std::string>();
        LOG(ERROR) << "extrinsic_file = " << extrinsic_file_;

        odometry_topic_ = node["odometry_topic"].as<std::string>();
        LOG(ERROR) << "odometry_topic = " << odometry_topic_;
        odometry_translation_topic_ = node["odometry_translation_topic"].as<std::string>();
        LOG(ERROR) << "odometry_translation_topic = " << odometry_translation_topic_;
        imu_topic_ = node["imu_topic"].as<std::string>();
        LOG(ERROR) << "imu_topic = " << imu_topic_;
        gnss_pvt_topic_ = node["position_topic"].as<std::string>();
        LOG(ERROR) << "gnss_pvt_topic = " << gnss_pvt_topic_;
        use_gps_time_ = node["use_gps_time"].as<bool_t>();
        LOG(ERROR) << "use_gps_time = " << use_gps_time_;

        holo::yaml::Node nodeif = node["interface"];
        interface_              = std::make_shared<Ti>(nodeif);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Starneto driver failed to load yaml: " << e.what();
        return false;
    }
    return true;
}

template <typename Td, typename Ti>
void StarnetoAppT<Td, Ti>::OdometryCallbackStarneto(const Odometryd& data, OdometrydWriterType& publisher)
{
    Odometryd msg = data;
    uint32_t  sec;
    uint32_t  nsec;

    if (!use_gps_time_)
    {
        if (!holo::os::GetSystemTime(sec, nsec))
        {
            LOG(ERROR) << "Get system time error!";
            return;
        }
        msg.SetTimestamp(holo::common::Timestamp(sec, nsec));
    }
    if (odometry_topic_ == publisher.GetTopicName())
    {
        frames_odometry_++;
    }
    else
    {
        frames_odometry_t_++;
    }
    publisher.Write(msg);
}

template <typename Td, typename Ti>
void StarnetoAppT<Td, Ti>::ImuCallbackStarneto(const Imud& data, ImudWriterType& publisher)
{
    Imud     msg = data;
    uint32_t sec;
    uint32_t nsec;
    if (!use_gps_time_)
    {
        if (!holo::os::GetSystemTime(sec, nsec))
        {
            LOG(ERROR) << "Get system time error!";
            return;
        }
        msg.SetTimestamp(holo::common::Timestamp(sec, nsec));
    }
    frames_imu_++;
    publisher.Write(msg);
}

template <typename Td, typename Ti>
void StarnetoAppT<Td, Ti>::PositionCallbackStarneto(const GnssPvt& data, GnssPvtWriterType& publisher)
{
    GnssPvt msg = data;

    uint32_t sec;
    uint32_t nsec;

    if (!use_gps_time_)
    {
        if (!holo::os::GetSystemTime(sec, nsec))
        {
            LOG(ERROR) << "Get system time error!";
            return;
        }
        msg.SetTimestamp(holo::common::Timestamp(sec, nsec));
    }

    frames_gnss_pvt_++;
    publisher.Write(msg);
}

template class StarnetoAppT<StarnetoDriver, UdpInterface<HoloCanPacket>>;

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
    cxxopts::Options options("StarnetoDriver", "Starneto driver node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("Starneto"))
        ("m,min_log_level", "minimum log level, ALL/TRACE/0, D/1, I/2, W/3, E/4, F/5, OFF/6", cxxopts::value<holo::uint8_t>()->default_value("0"))
        ("d,domain_id", "domain_id", cxxopts::value<uint32_t>()->default_value("0"));
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/starneto_" + node_name + ".log");
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
                using Td = holo::sensors::starneto::StarnetoDriver;
                using Ti = holo_cmw::UdpInterface<Tf>;
                holo_cmw::StarnetoAppT<Td, Ti> driver(domain_id, "");
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
    LOG(ERROR) << "exit";
    holo::log::HoloLogger::Shutdown();
    return 0;
}
#endif
