/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file novatel_common_app.cpp
 * @brief A app for novatel messages output
 * @author houyujian<houyujian@holomatic.com>
 * @date 2019/12/24
 */

#include <novatel/novatel_app.h>
#include <csignal>

namespace holo_cmw
{
void NovatelDriverApp::Setup(const std::string& config_file, bool_t blocking_mode)
{
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "Novatel driver app could not load file!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    // clang-format off
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pub_odometry_             = bus_->AddWriter<Odometryd, mdc_cm_wrapper::VSOdometryWgs84SITraits<Odometryd>>(odometry_topic_);
    pub_translation_odometry_ = bus_->AddWriter<Odometryd, mdc_cm_wrapper::VSOdometryWgs84SITraits<Odometryd>>(odometry_translation_topic_);
    pub_imu_                  = bus_->AddWriter<Imud, mdc_cm_wrapper::VSImuSITraits<Imud>>(imu_topic_);
    pub_gnss_pvt_             = bus_->AddWriter<GnssPvt, mdc_cm_wrapper::VSGnssPvtWgs84SITraits<GnssPvt>>(gnss_pvt_topic_);
#elif defined(CMW_WRAPPER_ENABLE_ROS)
    pub_odometry_             = bus_->AddWriter<Odometryd, ros_wrapper::DefaultConversionTraits<Odometryd>>(odometry_topic_);
    pub_translation_odometry_ = bus_->AddWriter<Odometryd, ros_wrapper::DefaultConversionTraits<Odometryd>>(odometry_translation_topic_);
    pub_imu_                  = bus_->AddWriter<Imud, ros_wrapper::DefaultConversionTraits<Imud>>(imu_topic_);
    pub_gnss_pvt_             = bus_->AddWriter<GnssPvt, ros_wrapper::DefaultConversionTraits<GnssPvt>>(gnss_pvt_topic_);
#else
    pub_odometry_             = bus_->AddWriter<Odometryd>(odometry_topic_);
    pub_translation_odometry_ = bus_->AddWriter<Odometryd>(odometry_translation_topic_);
    pub_imu_                  = bus_->AddWriter<Imud>(imu_topic_);
    pub_gnss_pvt_             = bus_->AddWriter<GnssPvt>(gnss_pvt_topic_);
#endif
    // clang-format on

    if (!holo::IsAbsolutePath(extrinsic_file_))
    {
        extrinsic_file_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_file_;
    }
    LOG(INFO) << "loading extrinsics from " << extrinsic_file_;
    extrinsic_ = holo::common::Extrinsicf::LoadYaml(extrinsic_file_);
    LOG(INFO) << "done";
    try
    {
        driver_ = std::make_shared<NovatelDriver>(extrinsic_);
    }
    catch (std::exception& e)
    {
        std::string s = "failed to create driver: ";
        s += e.what();
        LOG(ERROR) << s;
        throw std::runtime_error(s);
    }
    std::function<void(const Odometryd&)> odo_handler =
        std::bind(&NovatelDriverApp::OdometryCallback, this, std::placeholders::_1, std::ref(pub_odometry_),
                  std::ref(frames_odometry_));
    driver_->SetOdometryCallback(odo_handler);
    std::function<void(const Odometryd&)> odot_handler =
        std::bind(&NovatelDriverApp::OdometryCallback, this, std::placeholders::_1, std::ref(pub_translation_odometry_),
                  std::ref(frames_odometry_t_));
    driver_->SetOdometryTranslationCallback(odot_handler);
    std::function<void(const Imud&)> imu_handler =
        std::bind(&NovatelDriverApp::ImuCallback, this, std::placeholders::_1, std::ref(pub_imu_));
    driver_->SetImuCallback(imu_handler);
    std::function<void(const GnssPvt&)> pos_handler =
        std::bind(&NovatelDriverApp::PositionCallback, this, std::placeholders::_1, std::ref(pub_gnss_pvt_));
    driver_->SetPositionCallback(pos_handler);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif

    thread_ = std::make_shared<std::thread>(std::bind(&NovatelDriverApp::Background, this, config_file));

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

void NovatelDriverApp::Background(const std::string& config_file)
{
    /* timestamp_compensation */
    holo::yaml::Node    root = holo::yaml::LoadFile(config_file);
    TimediffGetterParam timediff_param(root["time_compensation"]);
    TimediffBase::SetEnable(timediff_param.enable);
#if defined(APP_MAIN_FUNCTION)
    TimediffGetter               timediff_getter(timediff_param);
    std::function<void(int64_t)> timediff_callback = std::bind(&TimediffBase::SetValue, this, std::placeholders::_1);
    timediff_getter.InstallCallback(timediff_callback);
#endif

    /* interface */
    holo::yaml::Node node = holo::yaml::LoadFile(config_file)["interface"];
    std::shared_ptr<TcpcliInterface<NovatelDriver::RawbufferType>> data_if =
        std::make_shared<TcpcliInterface<NovatelDriver::RawbufferType>>(node);
    while (true)
    {
        if (!cmw_wrapper::BusType::IsRunning())
        {
            return;
        }
        if (data_if->IsConnected())
        {
            break;
        }
        holo::os::Sleep(0.1f);
    }
    LOG(INFO) << "sending command to device: \n" << command_;
    if (data_if->Send(command_))
    {
        std::string s = "failed to send command to device";
        LOG(ERROR) << s;
        throw std::runtime_error(s);
    }
    /* important in mode use_gps_time=false: delay 2.5s to clear tcp cache data from novatel */
    holo::os::Sleep(2.5f);
    /* install callback */
    std::function<void(const NovatelDriver::RawbufferType&)> h =
        std::bind(&NovatelDriver::ParseData, driver_.get(), std::placeholders::_1);
    data_if->InstallCallback(h);
    std::function<std::pair<uint8_t*, uint32_t>(uint8_t*, uint32_t)> recv_data_callback =
        std::bind(&NovatelDriver::RecvData, driver_.get(), std::placeholders::_1, std::placeholders::_2);
    data_if->InstallRecvCallback(recv_data_callback);

    std::string command = "ICOMCONFIG ICOM1 tcp " + rtk_server_ip_ + ":" + std::to_string(rtk_server_port_);
    holo::Timer timer(1);
    uint32_t    counter                = 0;
    uint32_t    frames_odometry_last   = 0;
    uint32_t    frames_odometry_t_last = 0;
    uint32_t    frames_imu_last        = 0;
    uint32_t    frames_gnss_pvt_last   = 0;
    while (running_ && cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();
        counter++;
        if (use_holo_basestation_ && (counter % 120 == 0))
        {
            counter = 0;
            data_if->Send(command);
        }

        uint32_t frames_odometry_this   = frames_odometry_;
        uint32_t frames_odometry_t_this = frames_odometry_t_;
        uint32_t frames_imu_this        = frames_imu_;
        uint32_t frames_gnss_pvt_this   = frames_gnss_pvt_;
        if (live_callback_)
        {
            live_callback_(static_cast<uint32_t>(NovatelMsgType::ODOMETRY),
                           frames_odometry_this - frames_odometry_last);
            live_callback_(static_cast<uint32_t>(NovatelMsgType::ODOMETRY_T),
                           frames_odometry_t_this - frames_odometry_t_last);
            live_callback_(static_cast<uint32_t>(NovatelMsgType::IMU), frames_imu_this - frames_imu_last);
            live_callback_(static_cast<uint32_t>(NovatelMsgType::GNSS_PVT),
                           frames_gnss_pvt_this - frames_gnss_pvt_last);
        }
        frames_odometry_last   = frames_odometry_this;
        frames_odometry_t_last = frames_odometry_t_this;
        frames_imu_last        = frames_imu_this;
        frames_gnss_pvt_last   = frames_gnss_pvt_this;

        timer.Stop();
    }
}

bool_t NovatelDriverApp::GetParameters(const std::string& config_file)
{
    LOG(INFO) << "loading paramters from: " << config_file;
    uint16_t    freq_number = 0u;
    std::string msg_name    = "";
    float32_t   freq        = 0.0f;
    command_                = "";
    try
    {
        holo::yaml::Node node        = holo::yaml::LoadFile(config_file);
        holo::yaml::Node output_freq = node["msg_output_freq"];
        for (uint32_t i = 0; i < output_freq.size(); i++)
        {
            msg_name    = output_freq[i]["msg_name"].as<std::string>();
            freq_number = output_freq[i]["freq"].as<uint16_t>();
            if (freq_number != 0u)
            {
                freq = (float32_t)1 / (float32_t)freq_number;
                command_ += "log ";
                command_ += msg_name + " ontime ";
                command_ += std::to_string(freq) + "\r\n";
            }
        }
        rtk_server_ip_              = node["rtk_server_ip"].as<std::string>();
        rtk_server_port_            = node["rtk_server_port"].as<holo::uint16_t>(),
        use_holo_basestation_       = node["use_holo_basestation"].as<bool_t>();
        extrinsic_file_             = node["extrinsic_file"].as<std::string>();
        odometry_topic_             = node["odometry_topic"].as<std::string>();
        odometry_translation_topic_ = node["odometry_translation_topic"].as<std::string>();
        imu_topic_                  = node["imu_topic"].as<std::string>();
        gnss_pvt_topic_             = node["position_topic"].as<std::string>();
        use_gps_time_               = node["use_gps_time"].as<bool_t>();
        // imu_to_body_                = node["imu_to_body"].as<bool_t>(false);

        LOG(INFO) << "rtk_server_ip              = " << rtk_server_ip_;
        LOG(INFO) << "rtk_server_port            = " << rtk_server_port_;
        LOG(INFO) << "use_holo_basestation       = " << use_holo_basestation_;
        LOG(INFO) << "extrinsic_file             = " << extrinsic_file_;
        LOG(INFO) << "odometry_topic             = " << odometry_topic_;
        LOG(INFO) << "odometry_translation_topic = " << odometry_translation_topic_;
        LOG(INFO) << "imu_topic                  = " << imu_topic_;
        LOG(INFO) << "gnss_pvt_topic             = " << gnss_pvt_topic_;
        LOG(INFO) << "use_gps_time               = " << use_gps_time_;
        // LOG(INFO) << "imu_to_body                = " << imu_to_body_;
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "novatel driver failed to load yaml: " << e.what();
        return false;
    }
    return true;
}

void NovatelDriverApp::OdometryCallback(const Odometryd& data, OdometrydWriterType& publisher,
                                        std::atomic<uint32_t>& frames)
{
    Odometryd msg = data;
    if (AdjustTimestamp(msg) == false)
    {
        return;
    }
    frames++;
    publisher.Write(msg);
}

void NovatelDriverApp::ImuCallback(const Imud& data, ImudWriterType& publisher)
{
    Imud msg = data;

    // if (imu_to_body_)
    // {
    //     TransformToBody(msg, extrinsic_.GetPose().template Cast<float64_t>());
    // }

    if (AdjustTimestamp(msg) == false)
    {
        return;
    }
    frames_imu_++;
    publisher.Write(msg);
}

void NovatelDriverApp::PositionCallback(const GnssPvt& data, GnssPvtWriterType& publisher)
{
    GnssPvt msg = data;

    if (AdjustTimestamp(msg) == false)
    {
        return;
    }
    frames_gnss_pvt_++;
    publisher.Write(msg);
}

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
    cxxopts::Options options(argv[0], "Novatel driver node");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("NovatelDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/novatel_" + node_name + ".log");
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
        holo_cmw::NovatelDriverApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit";
    }
    LOG(ERROR) << "exit";
    holo::log::HoloLogger::Shutdown();
    return 0;
};
#endif
