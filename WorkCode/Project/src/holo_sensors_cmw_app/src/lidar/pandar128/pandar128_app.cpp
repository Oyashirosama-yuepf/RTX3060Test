/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar128_app.cpp
 * @brief A driver for pandar128 scan messages output
 * @author wujie<wujie@holomatic.com>
 * @date 2021/12/30
 */

#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <lidar/pandar128/pandar128_app.h>
#include <csignal>

namespace holo_cmw
{
void Pandar128DriverApp::Setup(const std::string& config_file, bool_t blocking_mode)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "pandar128 driver app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    /* load extrinsic */
    if (!holo::IsAbsolutePath(extrinsic_))
    {
        extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
    }
    LOG(INFO) << "loading extrinsics from " << extrinsic_;
    holo::common::Extrinsicf extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
    sensor_id_                         = extrinsic.GetSensorId();

    /* thread pool */
    thread_pool_ptr_ = std::make_shared<ThreadPool>(max_thr_num_);
    /* create device */
    driver_ = std::make_shared<Pandar128Driver>(packet_rate_, scan_rate_, rpm_, coord_, use_gps_);

    /* install callback */
    std::function<void(const Pandar128Scan&)> h0;
    if (publish_scan_)
    {
        /* parse converter params */
        static const uint32_t                           buffer_size = 4096;
        uint8_t                                         buffer[buffer_size];
        holo::sensors::pandar128::CorrectionParameter   correct_param(correct_node_);
        holo::sensors::pandar128::LuminousTimeParameter luminoustime_param(luminous_time_node_);
        SerializerType                                  serializer(buffer, buffer_size);

        if (correct_param.Serialize(serializer) && luminoustime_param.Serialize(serializer))
        {
            lidar_scan_ = std::make_shared<LidarScan>(LidarScan::LidarType::PANDAR128, use_compress_, extrinsic,
                                                      serializer.GetData(), serializer.GetSize());
        }
        else
        {
            LOG(ERROR) << "Converter Params Serialize Error!";
        }
        /* publisher */
        scan_pub_ = bus_->AddWriter<uint8_t*>(scan_topic_);
        h0        = std::bind(&Pandar128DriverApp::ScanDataCallback, this, std::placeholders::_1);
    }
    else
    {
        /* create converter */
        try
        {
            converter_ = std::make_shared<Pandar128PcdConverter>(luminous_time_node_, correct_node_, extrinsic);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create Pandar128 converter";
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
        /* open shm */
        try
        {
            LOG(INFO) << "sensor_id_ = " << sensor_id_;

            pcd_ipc_ = std::make_shared<PointCloudIpc>(sensor_id_);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create shm";
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
        pcd_pub_ = bus_->AddWriter<uint64_t>(pcd_topic_);
        h0       = std::bind(&Pandar128DriverApp::SavePcdToShmDataCallback, this, std::placeholders::_1);
    }
    driver_->InstallCallback(h0);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&Pandar128DriverApp::Background, this, config_file);

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

void Pandar128DriverApp::Background(const std::string& config_file)
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
    holo::yaml::Node                            node = holo::yaml::LoadFile(config_file)["data_interface"];
    UdpInterface<Pandar128Packet>               data_interface(node, true, 5000);
    std::function<void(const Pandar128Packet&)> h1 =
        std::bind(&Pandar128Driver::PushPacket, driver_.get(), std::placeholders::_1);
    data_interface.InstallCallback(h1);

    std::shared_ptr<UdpInterface<Pandar128GpsPacket>> sync_interface = nullptr;
    if (use_gps_)
    {
        holo::yaml::Node node2 = holo::yaml::LoadFile(config_file)["sync_interface"];
        sync_interface         = std::make_shared<UdpInterface<Pandar128GpsPacket>>(node2);
        std::function<void(const Pandar128GpsPacket&)> h2 =
            std::bind(&Pandar128Driver::PushGpsPacket, driver_.get(), std::placeholders::_1);
        sync_interface->InstallCallback(h2);
    }
    LOG(INFO) << "created data interface";
    LOG(INFO) << "start to receive data";

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

bool_t Pandar128DriverApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        rpm_                  = node["rpm"].as<uint32_t>();
        coord_                = node["coord"].as<uint32_t>();
        use_gps_              = node["use_gps"].as<bool>();
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        time_check_           = node["time_check"].as<holo::bool_t>();
        scan_rate_            = node["scan_rate"].as<uint32_t>();
        packet_rate_          = node["packet_rate"].as<uint32_t>();
        publish_scan_         = node["publish_scan"].as<bool_t>();
        extrinsic_            = node["extrinsic"].as<std::string>();
        use_compress_         = node["use_compress"].as<bool_t>();

        LOG(INFO) << "rpm                       = " << rpm_;
        LOG(INFO) << "coord                     = " << coord_;
        LOG(INFO) << "use_gps                   = " << use_gps_;
        LOG(INFO) << "scan_topic                = " << scan_topic_;
        LOG(INFO) << "pcd_topic                 = " << pcd_topic_;
        LOG(INFO) << "time_check                = " << time_check_;
        LOG(INFO) << "scan_rate                 = " << scan_rate_;
        LOG(INFO) << "packet_rate               = " << packet_rate_;
        LOG(INFO) << "publish_scan              = " << publish_scan_;
        LOG(INFO) << "extrinsic                 = " << extrinsic_;
        LOG(INFO) << "use_compress              = " << use_compress_;

        correct_node_       = node["correct"];
        luminous_time_node_ = node["luminous_time"];
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what();
        return false;
    }
    return true;
}

void Pandar128DriverApp::ScanDataCallback(const Pandar128Scan& scan)
{
    /* Is time check */
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].TimeStamp(), scan_rate_)))
    {
        return;
    }

    int64_t offset_value = 0;
    /* if use external time compensation */
    if (TimediffBase::IsEnabled())
    {
        offset_value = TimediffBase::GetValue();
        if (!TimediffBase::IsInitialized(offset_value))
        {
            LOG(ERROR) << "timestamp compensation is not initialized";
            return;
        }
    }

    if (lidar_scan_->SetScanData(scan))
    {
        lidar_scan_->SetTimeOffset0(offset_value);
        SerializerType serializer(scan_data_.get(), P128_DATA_CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
            frames_++;
        }
    }
}

/*
    @brief scan to pcd and set to shm
*/
void Pandar128DriverApp::SavePcdToShm(const Pandar128Scan& scan)
{
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].TimeStamp(), scan_rate_)))
    {
        LOG(ERROR) << "Time Check Error !";
        return;
    }

    /* scan converter to pcd */
    PointCloudType pcd;
    if (0 == converter_->ParseScan(scan, pcd))
    {
        LOG(ERROR) << static_cast<uint32_t>(pcd.GetCoordinate()) << "." << pcd.GetTimestamp().ToSec() << "is empty";
        return;
    }
    /* set data */
    if (true != pcd_ipc_->SetPointCloudData(pcd))
    {
        LOG(ERROR) << "Save Pcd To Shm Error !";
        return;
    }
    frames_++;
    uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + frames_;
    pcd_pub_.Write(info);
}

void Pandar128DriverApp::SavePcdToShmDataCallback(const Pandar128Scan& scan)
{
    thread_pool_ptr_->AddTask(&Pandar128DriverApp::SavePcdToShm, this, scan);
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
    cxxopts::Options options(argv[0], "pandar128-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("Pandar128Driver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/pandar128_driver_" + node_name + ".log");
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
        holo_cmw::Pandar128DriverApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit";
    }

    holo::log::HoloLogger::Shutdown();

    return 0;
}
#endif
