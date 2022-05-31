/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_app.cpp
 * @brief A driver for ouster scan messages output
 * @author yinweigen<yinweigen@holomatic.com>
 * @date 2022/01/24
 */

#include <lidar/ouster/ouster_app.h>

namespace holo_cmw
{
template <size_t PACKET_RATE>
void OusterDriverApp<PACKET_RATE>::Setup(const std::string& config_file, bool_t blocking_mode)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParamters(config_file))
    {
        std::ostringstream oss;
        oss << "ouster driver app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    /* create device */
    driver_ = std::make_shared<OusterDriver>(PACKET_RATE, scan_rate_, coord_);
    /* install callback */
    std::function<void(const OusterScan&)> h0;

    /* publisher */
#ifdef CMW_WRAPPER_ENABLE_ROS
    scan_pub_ = bus_->AddWriter<OusterScan, ros_wrapper::DefaultConversionTraits<OusterScan>>(scan_topic_);
#else
    scan_pub_ = bus_->AddWriter<uint8_t*>(scan_topic_);
#endif
    h0 = std::bind(&OusterDriverApp<PACKET_RATE>::DataCallbackSendScan, this, std::placeholders::_1);

    driver_->InstallCallback(h0);
    {
        /* create data interface */
        holo::yaml::Node node = holo::yaml::LoadFile(config_file)["data_interface"];
        data_interface_       = std::make_shared<UdpInterface<OusterPacket>>(node);
        std::function<void(const OusterPacket&)> h1 =
            std::bind(&OusterDriver::PushPacket, driver_.get(), std::placeholders::_1);
        data_interface_->InstallCallback(h1);
        // cmw_wrapper::BusType::AsyncSpin(1);
    }

    /* create ctrl interface */
    // holo::yaml::Node            node1 =
    // holo::yaml::LoadFile(config_file)["ctrl_interface"]; ctrl_interface_ =
    // std::make_shared<TcpcliInterface<OusterDriver::RawbufferType>>(node1);

    /* ouster init */
    // while (true)
    // {
    //     if (!cmw_wrapper::BusType::IsRunning())
    //     {
    //         return;
    //     }
    //     if (ctrl_interface_->IsConnected())
    //     {
    //         break;
    //     }
    //     holo::os::Sleep(0.1f);
    // }
    holo::os::Sleep(0.1f);
    LOG(INFO) << "sending command to device \n";
    std::string cmd_set_lidar_mode     = "set_config_param lidar_mode";
    std::string cmd_set_udp_port_lidar = "set_config_param udp_port_lidar";
    std::string cmd_set_udp_port_imu   = "set_config_param udp_port_imu";
    std::string cmd_set_udp_ip         = "set_config_param udp_ip";
    std::string cmd_set_timestamp_mode = "set_config_param timestamp_mode TIME_FROM_SYNC_PULSE_IN";
    std::string cmd_set_nmea_mode      = "set_config_param multipurpose_io_mode INPUT_NMEA_UART\n";
    std::string cmd_set_nmea_polarity  = "set_config_param nmea_in_polarity ACTIVE_LOW\n";
    std::string cmd_set_nmea_baud_rate = "set_config_param nmea_baud_rate BAUD_9600\n";
    std::string cmd_set_start_flag     = "set_config_param auto_start_flag 1\n";
    std::string cmd_reinitialize       = "reinitialize\n";

    // std::string cmd = cmd_set_lidar_mode + " " + lidar_mode_ + "\n";
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_set_udp_port_lidar + " " + udp_port_lidar_ + "\n";
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_set_udp_port_imu + " " + udp_port_imu_ + "\n";
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_set_udp_ip + " " + udp_ip_ + "\n";
    // ctrl_interface_->Send(cmd);
    // cmd = cmd_set_timestamp_mode + "\n";
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_set_nmea_mode;
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_set_nmea_polarity;
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_set_nmea_baud_rate;
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
    // cmd = cmd_reinitialize;
    // ctrl_interface_->Send(cmd);
    // holo::os::Sleep(0.1f);
#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&OusterDriverApp<PACKET_RATE>::Background, this);

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <size_t PACKET_RATE>
void OusterDriverApp<PACKET_RATE>::Background()
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

template <size_t PACKET_RATE>
bool_t OusterDriverApp<PACKET_RATE>::GetParamters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        coord_                = node["coord"].as<uint32_t>();
        scan_topic_           = node["scan_topic"].as<std::string>();
        time_check_           = node["time_check"].as<holo::bool_t>();
        scan_rate_            = node["scan_rate"].as<uint32_t>();
        use_compress_         = node["use_compress"].as<bool_t>();
        lidar_mode_           = node["lidar_mode"].as<std::string>();
        udp_port_lidar_       = node["udp_port_lidar"].as<std::string>();
        udp_port_imu_         = node["udp_port_imu"].as<std::string>();
        udp_ip_               = node["udp_ip"].as<std::string>();
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what();
        return false;
    }
    LOG(INFO) << "coord         = " << coord_;
    LOG(INFO) << "scan_topic    = " << scan_topic_;
    LOG(INFO) << "time_check    = " << time_check_;
    LOG(INFO) << "scan_rate     = " << scan_rate_;
    LOG(INFO) << "use_compress  = " << use_compress_;

    return true;
}

template <size_t PACKET_RATE>
void OusterDriverApp<PACKET_RATE>::DataCallbackSendScan(const OusterScan& scan)
{
    uint32_t sec, nsec;
    holo::os::GetSystemTime(sec, nsec);
    holo::common::Timestamp sys_time(sec, nsec);
    int64_t                 theoretical_time_ns = sys_time.ToNsec() - holo::sensors::NSEC_PER_SEC / scan_rate_;
    //    printf("DataCallbackSendScan is running\n");
    if (time_check_)
    {
        if (std::abs(theoretical_time_ns -
                     (scan.GetTimestamp() + holo::common::Duration(scan[0].GetBlockTimeStamp() / 1e6 + 1)).ToNsec()) <
            static_cast<int32_t>(holo::sensors::NSEC_PER_SEC / (2 * scan_rate_)))
        {
#ifdef CMW_WRAPPER_ENABLE_ROS
            if (scan.Size() > 0)
            {
                frames_++;
                scan_pub_.Write(scan);
            }
#else
            SerializerType serializer(scan_data_.get(), CAPACITY);
            if (scan.Serialize(serializer))
            {
                frames_++;
                scan_pub_.Write(serializer.GetData(), serializer.GetSize());
            }
#endif
        }
        else
        {
            // clang-format off
            LOG(ERROR) << "Not correct lidar time, lidar time =" << (scan.GetTimestamp() + holo::common::Duration(scan[0].GetBlockTimeStamp() / 1e6 + 1)).ToNsec()
                       << ", abs gap = " << std::abs(theoretical_time_ns - (scan.GetTimestamp() + holo::common::Duration(scan[0].GetBlockTimeStamp() / 1e6 + 1)).ToNsec());
            // clang-format on
        }
    }
    else
    {
#ifdef CMW_WRAPPER_ENABLE_ROS
        if (scan.Size() > 0)
        {
            frames_++;
            scan_pub_.Write(scan);
        }
#else
        SerializerType serializer(scan_data_.get(), CAPACITY);
        if (scan.Serialize(serializer))
        {
            frames_++;
            scan.GetTimestamp();
            //            printf("serializer.GetSize() = %d\n", serializer.GetSize());
            scan_pub_.Write(serializer.GetData(), serializer.GetSize());
        }
#endif
    }
}

template class OusterDriverApp<640>;

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
    cxxopts::Options options(argv[0], "ouster-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if alse outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("OusterDriver"))
        ("m,min_log_level", "minimum log level, ALL/TRACE/0, D/1, I/2, W/3, E/4, F/5, OFF/6", cxxopts::value<holo::uint8_t>()->default_value("0"))
        ("d,domain_id", "domain id", cxxopts::value<uint32_t>()->default_value("0"))
        ;
    // clang-format on
    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
    }

    signal(SIGSEGV, signalSegHandler);
    signal(SIGINT, cmw_wrapper::BusType::SignalHandler);

    uint32_t    domain_id = options["domain_id"].as<uint32_t>();
    std::string node_name = options["node_name"].as<std::string>();
    holo::CreateHoloLogSubdirectory("holo_sensors");
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/ouster_driver_" + node_name + ".log");
    uint32_t    log_level     = options["min_log_level"].as<holo::uint8_t>();
    log_level                 = std::min<uint32_t>(log_level, 6);
    log_level                 = ((log_level * 10000 + 9999) / 10000) * 10000;

    holo::log::RollingFileConfigure log_file("log_file", log_file_name);
    holo::log::HoloLogger::Add(log_file);
    holo::log::HoloLogger::SetLogLevel(static_cast<holo::log::LogLevel>(log_level));
    holo::log::HoloLogger::SetLogLevel(holo::log::ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME,
                                       options.count("verbose") ? (static_cast<holo::log::LogLevel>(log_level)) :
                                                                  (holo::log::LogLevel::OFF));

    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    try
    {
        holo::yaml::Node node  = holo::yaml::LoadFile(options["config_file"].as<std::string>());
        std::string      model = node["model"].as<std::string>("OUSTER");
        LOG(INFO) << "model = " << model;
        try
        {
            if (model == "OUSTER")
            {
                holo_cmw::OusterDriverApp<640> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
            else
            {
                LOG(ERROR) << "unknown device model, exit";
            }
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "application failed, exit";
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "failed to read device model, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
#endif
