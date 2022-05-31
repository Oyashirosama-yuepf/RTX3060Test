/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsm1_app.cpp
 * @brief A driver for rsm1 scan messages output
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/18
 */

#include <holo/common/extrinsic.h>
#include <lidar/rsm1/rsm1_app.h>
#include <csignal>

namespace holo_cmw
{
void Rsm1DriverApp::Setup(const std::string& config_file)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "rsm1 driver app failed to load config file";
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
    driver_ = std::make_shared<Rsm1Driver>(coord_, packet_rate_, scan_rate_);

#if defined(MDC_PRODUCTION_MDC610)
    driver_->SetDatalayerTimestamp(use_datalayer_timestamp_);
#endif

    /* install callback */
    std::function<void(const Rsm1ScanType&)> h;
    if (publish_scan_)
    {
        try
        {
            lidar_scan_ =
                std::make_shared<LidarScan>(LidarScan::LidarType::RSM1, use_compress_, extrinsic, !use_lidarscan_);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create LidarScan";
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
        scan_pub_ = bus_.AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(scan_topic_);
#else
        scan_pub_ = bus_.AddWriter<uint8_t*>(scan_topic_);
#endif
        h = std::bind(&Rsm1DriverApp::ScanDataCallback, this, std::placeholders::_1);
    }
    else
    {
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
        pcd_pub_ = bus_.AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(pcd_topic_);
#else
        pcd_pub_  = bus_.AddWriter<uint64_t>(pcd_topic_);
#endif

        /* create converter */
        try
        {
            converter_ = std::make_shared<Rsm1Converter>(extrinsic);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create rsm1 converter";
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

        h = std::bind(&Rsm1DriverApp::AddTask, this, std::placeholders::_1);
    }
    driver_->InstallScanCallback(h);

    /* load device info interface param*/
    /*
    holo::yaml::Node         node0 = holo::yaml::LoadFile(config_file)["device_info_interface"];
    UdpInterfaceParam        device_info_if_param(node0);
    UdpInterface<Rsm1DeviceInfoPacket> device_info_interface(device_info_if_param);
    std::function<void(const Rsm1DeviceInfoPacket&)> h0 = std::bind(&Rsm1Driver::PushDeviceInfoPacket, driver_.get(),
    std::placeholders::_1); device_info_interface.InstallCallback(h0);
    */
    /* load data interface param */
    holo::yaml::Node                       node1 = holo::yaml::LoadFile(config_file)["data_interface"];
    UdpInterface<Rsm1Packet>               data_interface(node1, true, 5000);
    std::function<void(const Rsm1Packet&)> h1 =
        std::bind(&Rsm1Driver::PushPacket, driver_.get(), std::placeholders::_1);
    data_interface.InstallCallback(h1);
    LOG(INFO) << "created data interface";
    LOG(INFO) << "start to receive data";

    cmw_wrapper::BusType::AsyncSpin(1);
    uint32_t    frames_last = 0;
    holo::Timer timer(1.0f);
    while (cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();
        uint32_t frames_this = frames_;
        LOG(INFO) << "data hz = " << frames_this - frames_last;
        frames_last = frames_this;
        timer.Stop();
    }
    thread_pool_ptr_->WaitAndDestroy();
}

bool Rsm1DriverApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node    = holo::yaml::LoadFile(config_file);
        coord_                   = node["coord"].as<uint32_t>();
        scan_topic_              = node["scan_topic"].as<std::string>();
        pcd_topic_               = node["pcd_topic"].as<std::string>();
        publish_scan_            = node["publish_scan"].as<holo::bool_t>();
        use_lidarscan_           = node["use_lidarscan"].as<holo::bool_t>(true);
        use_compress_            = node["use_compress"].as<holo::bool_t>();
        time_check_              = node["time_check"].as<holo::bool_t>();
        scan_rate_               = node["scan_rate"].as<uint32_t>();
        packet_rate_             = node["packet_rate"].as<uint32_t>();
        extrinsic_               = node["extrinsic"].as<std::string>(); /* for converter usage */
        max_thr_num_             = node["max_thr_num"].as<uint32_t>();
        use_datalayer_timestamp_ = node["use_datalayer_timestamp"].as<holo::bool_t>("true");

        LOG(INFO) << "coord                   = " << coord_;
        LOG(INFO) << "scan_topic              = " << scan_topic_;
        LOG(INFO) << "pcd_topic               = " << pcd_topic_;
        LOG(INFO) << "publish_scan            = " << publish_scan_;
        LOG(INFO) << "use_lidarscan           = " << use_lidarscan_;
        LOG(INFO) << "use_compress_           = " << use_compress_;
        LOG(INFO) << "time_check_             = " << time_check_;
        LOG(INFO) << "scan_rate_              = " << scan_rate_;
        LOG(INFO) << "packet_rate_            = " << packet_rate_;
        LOG(INFO) << "extrinsic               = " << extrinsic_;
        LOG(INFO) << "max_thr_num             = " << max_thr_num_;
        LOG(INFO) << "use_datalayer_timestamp = " << use_datalayer_timestamp_;
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load parameters: " << e.what();
        return false;
    }
    return true;
}

/*
    @brief scan to pcd and set to shm
*/
void Rsm1DriverApp::SavePcdToShm(const Rsm1ScanType& scan)
{
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].GetHeaderTimestamp(), scan_rate_)))
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
        LOG(ERROR) << "save pcd to shm error !";
        return;
    }
    frames_++;
    uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + frames_;
    pcd_pub_.Write(info);
}

void Rsm1DriverApp::AddTask(const Rsm1ScanType& scan)
{
    thread_pool_ptr_->AddTask(&Rsm1DriverApp::SavePcdToShm, this, scan);
}

void Rsm1DriverApp::ScanDataCallback(const Rsm1ScanType& scan)
{
    /* Is time check */
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].GetHeaderTimestamp(), scan_rate_)))
    {
        return;
    }

    if (lidar_scan_->SetScanData(scan))
    {
        SerializerType serializer(scan_data_.get(), CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
            frames_++;
        }
    }
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
    cxxopts::Options options(argv[0], "rsm1-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("Rsm1Driver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/rsm1_driver_" + node_name + ".log");
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
        holo_cmw::Rsm1DriverApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}