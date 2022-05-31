/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lidar_converter_app.cpp
 * @brief A converter to convert lidar scan messages to pcd
 * @author wujie<wujie@holomatic.com>
 * @date 2022/01/24
 */

#include <lidar/lidar_converter_app.h>
#include <csignal>

namespace holo_cmw
{
void LidarConverterApp::Setup(const std::string& config_file)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "lidar converter app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    /* create ldiar scan and ipc */
    try
    {
        std::function<void(const uint8_t*, size_t)> h0 = nullptr;
#if defined(CMW_WRAPPER_ENABLE_MDC_CM)
        scan_sub_ = bus_.AddReader<uint8_t*, mdc_cm_wrapper::BuiltinBufferSITraits<uint8_t*>>(scan_topic_);
        pcd_pub_  = bus_.AddWriter<uint64_t, mdc_cm_wrapper::UInt64SITraits<uint64_t>>(pcd_topic_);
#else
        scan_sub_ = bus_.AddReader<uint8_t*>(scan_topic_);
        pcd_pub_  = bus_.AddWriter<uint64_t>(pcd_topic_);
#endif
        if (extrinsic_path_ == "")
        {
            h0 = std::bind(&LidarConverterApp::DataCallbackDefaultExtrinsic, this, std::placeholders::_1,
                           std::placeholders::_2);
        }
        else
        {
            /* load extrinsic */
            if (!holo::IsAbsolutePath(extrinsic_path_))
            {
                extrinsic_path_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_path_;
            }
            LOG(INFO) << "loading extrinsics from " << extrinsic_path_;
            extrinsic_ = holo::common::Extrinsicf::LoadYaml(extrinsic_path_);
            sensor_id_ = extrinsic_.GetSensorId();
            pcd_ipc_   = std::make_shared<PointCloudIpc>(sensor_id_);

            h0 = std::bind(&LidarConverterApp::DataCallbackUserExtrinsic, this, std::placeholders::_1,
                           std::placeholders::_2);
        }
        scan_sub_.SetOnDataAvailableCallback(h0);

        /* lidar scan */
        lidar_scan_ = std::make_shared<LidarScan>();
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "failed to create LidarScan or Ipc";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }

    LOG(INFO) << "start work";
    cmw_wrapper::BusType::AsyncSpin(1);

    uint32_t frames_last = 0;
    while (cmw_wrapper::BusType::IsRunning())
    {
        uint32_t frames_this = frames_;
        LOG(INFO) << "data hz = " << frames_this - frames_last;
        frames_last = frames_this;
        holo::os::Sleep(1);
    }
}

void LidarConverterApp::SetPcdToShm(const PointCloudType& pcd)
{
    /* set data to shm */
    if (true != pcd_ipc_->SetPointCloudData(pcd))
    {
        LOG(ERROR) << "Save Pcd To Shm Error !";
        return;
    }
    frames_++;
    // (void)holo::sensors::PlyConverter<PointCloudType>::Save(pcd, "test.ply");
    uint64_t info = (static_cast<uint64_t>(sensor_id_) << 32) + frames_;
    pcd_pub_.Write(info);
}

void LidarConverterApp::DataCallbackDefaultExtrinsic(const uint8_t* data, size_t size)
{
    PointCloudType   pcd;
    DeserializerType deserializer(data, size);

    if (!lidar_scan_->ConvertToPcd(deserializer, pcd))
    {
        LOG(ERROR) << "LidarScan ConvertToPcd Error!";
        return;
    }

    /* open shm */
    if (pcd_ipc_ == nullptr)
    {
        sensor_id_ = lidar_scan_->GetExtrinsic().GetSensorId();
        pcd_ipc_   = std::make_shared<PointCloudIpc>(sensor_id_);
    }

    SetPcdToShm(pcd);
}

void LidarConverterApp::DataCallbackUserExtrinsic(const uint8_t* data, size_t size)
{
    PointCloudType   pcd;
    DeserializerType deserializer(data, size);

    if (!lidar_scan_->ConvertToPcd(deserializer, pcd, extrinsic_))
    {
        LOG(ERROR) << "LidarScan ConvertToPcd Error!";
        return;
    }
    SetPcdToShm(pcd);
}

bool LidarConverterApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        extrinsic_path_       = node["extrinsic"].as<std::string>("");

        LOG(INFO) << "scan_topic                  = " << scan_topic_;
        LOG(INFO) << "pcd_topic                   = " << pcd_topic_;
        LOG(INFO) << "extrinsic                   = " << extrinsic_path_;
        LOG(INFO) << "loading parameters successfully";
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load convert parameters: " << e.what();
        return false;
    }
    return true;
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
    cxxopts::Options options(argv[0], "Lidar-converter");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("LidarConverter"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/Lidar_converter_" + node_name + ".log");
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
        holo_cmw::LidarConverterApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit : " << e.what();
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}