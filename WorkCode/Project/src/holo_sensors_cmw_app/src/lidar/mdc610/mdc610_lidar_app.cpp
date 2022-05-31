/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_app.cpp
 * @brief A driver for mdc610 lidar scan messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/11/26
 */

#include <lidar/mdc610/mdc610_lidar_app.h>
#include <chrono>
#include <csignal>

namespace holo_cmw
{
void Mdc610LidarDriverApp::Setup(const std::string& config_file)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "mdc610 lidar driver app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    if (!holo::IsAbsolutePath(extrinsic_))
    {
        extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
    }
    LOG(INFO) << "loading extrinsics from " << extrinsic_;
    holo::common::Extrinsicf extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
    sensor_id_                         = extrinsic.GetSensorId();

    /* load data interface param */
    holo::sensors::interface::Mdc610LidarInterfaceParam    data_params(instance_);
    holo::sensors::interface::Mdc610LidarInterface         data_interface(data_params);
    std::function<void(std::shared_ptr<const LidarFrame>)> h2;

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
    pcd_pub_ = bus_.AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(pcd_topic_);
#else
    pcd_pub_ = bus_.AddWriter<uint64_t>(pcd_topic_);
#endif
    /* create converter */
    try
    {
        converter_ = std::make_shared<Mdc610PcdConverter>(extrinsic);
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "failed to create mdc610 lidar converter";
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

    if (publish_scan_)
    {
        /* lidar_scan */
        try
        {
            lidar_scan_ = std::make_shared<LidarScan>(LidarScan::LidarType::MDC610, use_compress_, extrinsic);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create LidarScan";
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }

        /* publisher */
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
        scan_pub_ = bus_.AddWriter<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(scan_topic_);
#else
        scan_pub_ = bus_.AddWriter<uint8_t*>(scan_topic_);
#endif
        h2 = std::bind(&Mdc610LidarDriverApp::ScanDataCallback, this, std::placeholders::_1);
    }
    else
    {
        h2 = std::bind(&Mdc610LidarDriverApp::SavePcdDataCallback, this, std::placeholders::_1);
    }
    data_interface.InstallCallback(h2);

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
}

bool Mdc610LidarDriverApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        coord_                = node["coord"].as<uint32_t>();
        instance_             = node["instance"].as<uint32_t>();
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        use_compress_         = node["use_compress"].as<holo::bool_t>();
        extrinsic_            = node["extrinsic"].as<std::string>();
        publish_scan_         = node["publish_scan"].as<holo::bool_t>();

        LOG(INFO) << "coord           = " << coord_;
        LOG(INFO) << "instance        = " << instance_;
        LOG(INFO) << "scan_topic      = " << scan_topic_;
        LOG(INFO) << "pcd_topic       = " << pcd_topic_;
        LOG(INFO) << "use_compress    = " << use_compress_;
        LOG(INFO) << "extrinsic       = " << extrinsic_;
        LOG(INFO) << "publish_scan    = " << publish_scan_;
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load parameters: " << e.what();
        return false;
    }
    return true;
}

void Mdc610LidarDriverApp::ScanDataCallback(std::shared_ptr<const LidarFrame> frame)
{
    Mdc610ScanType scan(coord_, frame);

    /* send scan */
    if (lidar_scan_->SetScanData(scan))
    {
        SerializerType serializer(scan_data_.get(), CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
        }
    }

    /* send pcd */
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

void Mdc610LidarDriverApp::SavePcdDataCallback(std::shared_ptr<const LidarFrame> frame)
{
    /* scan converter to pcd */
    Mdc610ScanType scan(coord_, frame);

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

}  // namespace holo_cmw

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "mdc610-lidar-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("Mdc610LidarDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/mdc610_lidar_" + node_name + ".log");
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

#if (MDC610_VERSION_NUM == 20210430)
    Adsfi::AdsfiLogger::GetInstance().InitLogging("mdc610_lidar_" + node_name, "desc", 4, 6, "./log/holo_sensors/");
    Adsfi::AdsfiLogger::GetInstance().CreateLogger("mdc610_lidar_" + node_name, "async", 4);
#else
    Adsfi::AdsfiLogger::GetInstance().InitLogging(
        "mdc610_lidar_" + node_name, "desc", Adsfi::HafLogLevelType::HAF_ERROR,
        Adsfi::HafLogModeType::HAF_REMOTE_CONSOLE_FILE, "./log/holo_sensors/");
    Adsfi::AdsfiLogger::GetInstance().CreateLogger("mdc610_lidar_" + node_name, "async",
                                                   Adsfi::HafLogLevelType::HAF_ERROR);
#endif

    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    try
    {
        holo_cmw::Mdc610LidarDriverApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit: " << e.what();
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
