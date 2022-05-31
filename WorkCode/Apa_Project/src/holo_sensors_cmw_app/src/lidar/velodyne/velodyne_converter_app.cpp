/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velodyne_converter_app.cpp
 * @brief A converter to convert velodyne scan messages to pcd
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/07/07
 */

#include <lidar/velodyne/velodyne_converter_app.h>
#include <csignal>

namespace holo_cmw
{
void VelodyneConverterApp::Setup(const std::string& config_file, const std::string& out_fmt)
{
    LOG(INFO) << "output file name format is " << out_fmt;
    lidar_utils_.SetPlyNameFormat(out_fmt);
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "vlp converter app could not load file!";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    try
    {
        if (!holo::IsAbsolutePath(extrinsic_))
        {
            extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
        }
        LOG(INFO) << "loading extrinsics from " << extrinsic_;
        auto extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
        sensor_id_ = extrinsic.GetSensorId();
        LOG(INFO) << "sensor_id_ = " << sensor_id_;
        std::function<void(const uint8_t*, size_t)> h0 = nullptr;
        if (publish_scan_)
        {
            converter_ = std::make_shared<VelodynePcdConverter>(cvt_node_, crr_node_, extrinsic);
            /* subscriber & install callback */
            scan_sub_                                      = bus_.AddReader<uint8_t*>(scan_topic_);
            if (use_compress_)
            {
                h0 = std::bind(&VelodyneConverterApp::DataCallbackGetScan, this, std::placeholders::_1, std::placeholders::_2,
                            holo::sensors::LidarCompressAlgorithm::LZ4);
            }
            else
            {
                h0 = std::bind(&VelodyneConverterApp::DataCallbackGetScan, this, std::placeholders::_1, std::placeholders::_2,
                            holo::sensors::LidarCompressAlgorithm::NONE);
            }
            scan_sub_.SetOnDataAvailableCallback(h0);
        }
        else
        {
            pcd_client_ = std::make_shared<PointCloudIpc>(sensor_id_);
            pcd_sub_   = bus_.AddReader<uint64_t>(pcd_topic_);
            std::function<void(uint64_t)> h0 = nullptr;
            h0 = std::bind(&VelodyneConverterApp::DataCallbackGetPcdShm, this, std::placeholders::_1);
            pcd_sub_.SetOnDataAvailableCallback(h0);
        }
        
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "create converter faild: " << e.what();
    }

    /* start work */
    LOG(INFO) << "start work ...";
    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

bool VelodyneConverterApp::GetParameters(const std::string& config_file)
{
    LOG(INFO) << config_file;
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        scan_topic_   = node["scan_topic"].as<std::string>();
        pcd_topic_    = node["pcd_topic"].as<std::string>();
        publish_scan_ = node["publish_scan"].as<bool_t>();
        extrinsic_    = node["extrinsic"].as<std::string>();
        use_compress_ = node["use_compress"].as<bool_t>();

        LOG(INFO) << "scan_topic   = " << scan_topic_;
        LOG(INFO) << "pcd_topic    = " << pcd_topic_;
        LOG(INFO) << "publish_scan = " << publish_scan_;
        LOG(INFO) << "extrinsic    = " << extrinsic_;
        
        cvt_node_ = node["convert"];
        crr_node_ = node["correct"];
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << e.what();
        return false;
    }
    return true;
}
void VelodyneConverterApp::DataCallbackGetScan(const uint8_t* data, size_t size, holo::sensors::LidarCompressAlgorithm alg)
{
    PointCloudType pcd;

    if (0 == converter_->ParseScan(data, size, pcd, alg))
    {
        LOG(ERROR) << static_cast<uint32_t>(pcd.GetCoordinate()) << "." << pcd.GetTimestamp().ToSec() << "is empty";
    }

    lidar_utils_.SavePlyFile(pcd);
}
void VelodyneConverterApp::DataCallbackGetPcdShm(const uint64_t info)
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
    cxxopts::Options options(argv[0], "velodyne-converter");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("VelodyneConverter"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/velodyne_converter_" + node_name + ".log");
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
        holo_cmw::VelodyneConverterApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>(), options["output_name"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "application faild, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}