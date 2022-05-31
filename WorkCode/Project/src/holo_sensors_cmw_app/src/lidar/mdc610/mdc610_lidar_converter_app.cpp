/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_lidar_converter_app.cpp
 * @brief A converter to convert mdc610_lidar scan messages to pcd
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/08/16
 */

#include <lidar/mdc610/mdc610_lidar_converter_app.h>
#include <csignal>

namespace holo_cmw
{
void Mdc610LidarConverterApp::Setup(const std::string& config_file, const std::string out_fmt)
{
    LOG(INFO) << "output file name format is " << out_fmt;
    lidar_utils_.SetPlyNameFormat(out_fmt);

    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "mdc610 lidar converter app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    if (!holo::IsAbsolutePath(extrinsic_))
    {
        extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
    }
    LOG(INFO) << "loading extrinsics from " << extrinsic_;

    auto extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
    sensor_id_     = extrinsic.GetSensorId();
    LOG(INFO) << "sensor_id_ = " << sensor_id_;

    if (publish_scan_)
    {
        lidar_scan_ = std::make_shared<LidarScan>();
        /* subscriber & install callback */
        std::function<void(const uint8_t*, size_t)> h0 = nullptr;
        h0 = std::bind(&Mdc610LidarConverterApp::DataCallbackGetLidarScan, this, std::placeholders::_1,
                       std::placeholders::_2);

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
        scan_sub_ = bus_.AddReader<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(scan_topic_);
#else
        scan_sub_ = bus_.AddReader<uint8_t*>(scan_topic_);
#endif
        scan_sub_.SetOnDataAvailableCallback(h0);
    }
    else
    {
        pcd_client_                      = std::make_shared<PointCloudIpc>(sensor_id_);
        std::function<void(uint64_t)> h0 = nullptr;
        h0 = std::bind(&Mdc610LidarConverterApp::DataCallbackGetPcdShm, this, std::placeholders::_1);

#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
        pcd_sub_ = bus_.AddReader<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(pcd_topic_);
#else
        pcd_sub_  = bus_.AddReader<uint64_t>(pcd_topic_);
#endif
        pcd_sub_.SetOnDataAvailableCallback(h0);
    }
    LOG(INFO) << "start work";

    cmw_wrapper::BusType::AsyncSpin(1);

    uint32_t last_ply_count = 0; /* count frame */
    while (cmw_wrapper::BusType::IsRunning())
    {
        LOG(INFO) << "ScanCount | ConvertedCount | PlyCount | PlyFrame: " << scan_count_ << " | " << converted_count_
                  << " | " << ply_count_ << " | " << ply_count_ - last_ply_count;
        last_ply_count = ply_count_;
        holo::os::Sleep(1);
    }
}

bool Mdc610LidarConverterApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        extrinsic_            = node["extrinsic"].as<std::string>();
        publish_scan_         = node["publish_scan"].as<bool_t>();

        LOG(INFO) << "scan_topic    = " << scan_topic_;
        LOG(INFO) << "pcd_topic     = " << pcd_topic_;
        LOG(INFO) << "publish_scan  = " << publish_scan_;
        LOG(INFO) << "loading parameters successfully";
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load convert parameters: " << e.what();
        return false;
    }
    return true;
}

void Mdc610LidarConverterApp::DataCallbackGetLidarScan(const uint8_t* data, size_t size)
{
    scan_count_++;

    PointCloudType pcd;

    DeserializerType deserializer(data, size);

    if (!lidar_scan_->ConvertToPcd(deserializer, pcd))
    {
        LOG(ERROR) << "LidarScan ConvertToPcd Error!";
    }
    else
    {
        converted_count_++;
        lidar_utils_.SavePlyFile(pcd);
        ply_count_++;
    }
}

void Mdc610LidarConverterApp::DataCallbackGetPcdShm(const uint64_t info)
{
    (void)info;
    PointCloudType pcd;
    pcd_client_->GetPointCloudData(pcd);
    lidar_utils_.SavePlyFile(pcd);
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
    cxxopts::Options options(argv[0], "mdc610-lidar-converter");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("Mdc610LidarConverter"))
        ("o,output_name", "output file name format, w8(8-bit width), ts(time stamp)",cxxopts::value<std::string>()->default_value("w8"))
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
    std::string log_file_name =
        holo::GetLogFileAbsolutePath("holo_sensors/mdc610_lidar_converter_" + node_name + ".log");
    uint32_t log_level = options["min_log_level"].as<holo::uint8_t>();
    log_level          = std::min<uint32_t>(log_level, 6);
    log_level          = ((log_level * 10000 + 9999) / 10000) * 10000;

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
        holo_cmw::Mdc610LidarConverterApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>(), options["output_name"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit: " << e.what();
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
