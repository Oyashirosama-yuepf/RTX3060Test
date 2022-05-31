/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pandar_converter.cpp
 * @brief A converter to convert pandar scan messages to pcd
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/03/22
 */

#include <lidar/pandar/pandar_converter_app.h>
#include <csignal>

namespace holo_cmw
{
void PandarConverterApp::Setup(const std::string& config_file, const std::string& out_fmt)
{
    LOG(INFO) << "output file name format is " << out_fmt;
    lidar_utils_.SetPlyNameFormat(out_fmt);

    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "pandar converter app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }
    /* create converter */
    try
    {
        if (extrinsic_path_ != "")
        {
            if (!holo::IsAbsolutePath(extrinsic_path_))
            {
                extrinsic_path_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_path_;
            }

            extrinsic_ = holo::common::Extrinsicf::LoadYaml(extrinsic_path_);
            sensor_id_ = extrinsic_.GetSensorId();
            if (!publish_scan_)
            {
                pcd_client_ = std::make_shared<PointCloudIpc>(sensor_id_);
            }
            LOG(INFO) << "sensor_id_ = " << sensor_id_;
        }

        std::function<void(const uint8_t*, size_t)> h0 = nullptr;

        if (publish_scan_)
        {
            lidar_scan_ = std::make_shared<LidarScan>();

            /* subscriber & install callback */
            std::function<void(const uint8_t*, size_t)> h0 = nullptr;
            scan_sub_                                      = bus_.AddReader<uint8_t*>(scan_topic_);

            if (extrinsic_path_ == "")
            {
                h0 = std::bind(&PandarConverterApp::DataCallbackUseDefaultExtrinsic, this, std::placeholders::_1,
                               std::placeholders::_2);
                LOG(INFO) << "use default extrinsics from LidarScan";
            }
            else
            {
                h0 = std::bind(&PandarConverterApp::DataCallbackUseUserExtrinsic, this, std::placeholders::_1,
                               std::placeholders::_2);
                LOG(INFO) << "loading extrinsics from " << extrinsic_path_;
            }

            scan_sub_.SetOnDataAvailableCallback(h0);
        }
        else
        {
            pcd_sub_                         = bus_.AddReader<uint64_t>(pcd_topic_);
            std::function<void(uint64_t)> h0 = nullptr;
            h0 = std::bind(&PandarConverterApp::DataCallbackGetPcdShm, this, std::placeholders::_1);
            pcd_sub_.SetOnDataAvailableCallback(h0);
        }
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "pandar driver app failed to create converter";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

bool PandarConverterApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        extrinsic_path_       = node["extrinsic"].as<std::string>();
        use_compress_         = node["use_compress"].as<bool_t>();
        publish_scan_         = node["publish_scan"].as<bool_t>();
        LOG(INFO) << "scan_topic                   = " << scan_topic_;
        LOG(INFO) << "pcd_topic                    = " << pcd_topic_;
        LOG(INFO) << "extrinsic                    = " << extrinsic_path_;
        LOG(INFO) << "use_compress                 = " << use_compress_;
        LOG(INFO) << "publish_scan                 = " << publish_scan_;

        holo::yaml::Node cvt_node = node["convert"];
        convert_param_.LoadConvertParameters(cvt_node);
        holo::yaml::Node crr_node = node["correct"];
        correct_param_.LoadCorrectionParameters(crr_node);
        LOG(INFO) << "loading convert/correction parameters successfully";
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to load convert/correction parameters: " << e.what();
        return false;
    }
    return true;
}
void PandarConverterApp::DataCallbackUseDefaultExtrinsic(const uint8_t* data, size_t size)
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

void PandarConverterApp::DataCallbackUseUserExtrinsic(const uint8_t* data, size_t size)
{
    scan_count_++;

    PointCloudType pcd;

    DeserializerType deserializer(data, size);

    if (!lidar_scan_->ConvertToPcd(deserializer, pcd, extrinsic_))
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

void PandarConverterApp::DataCallbackGetPcdShm(const uint64_t info)
{
    /* open shm */
    if (pcd_client_ == nullptr)
    {
        sensor_id_  = lidar_scan_->GetExtrinsic().GetSensorId();
        pcd_client_ = std::make_shared<PointCloudIpc>(sensor_id_);
    }

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
    cxxopts::Options options(argv[0], "pandar-converter");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("PandarConverter"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/pandar_converter_" + node_name + ".log");
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
        holo_cmw::PandarConverterApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>(), options["output_name"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit : " << e.what();
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
