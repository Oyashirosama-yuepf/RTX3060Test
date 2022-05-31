/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ouster_converter.cpp
 * @brief A converter to convert ouster scan messages to pcd
 * @author wangzhaobing<wangzhaobing@holomatic.com>
 * @date 2022/03/2
 */

#include <cmw_wrapper/cmw_bus.h>
#include <holo_base_msg/ros_msg/sensors/ouster_traits.h>
#include <holo_base_msg/traits.h>
#include <lidar/ouster/ouster_converter_app.h>
#include <csignal>

namespace holo_cmw
{
void OusterConverterApp::Setup(const std::string& config_file, const std::string& out_fmt)
{
    LOG(INFO) << "output file name format is " << out_fmt;
    lidar_utils_.SetPlyNameFormat(out_fmt);

    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "ouster converter app failed to load config file";
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
        sensor_id_     = extrinsic.GetSensorId();
        LOG(INFO) << "sensor_id_ = " << sensor_id_;
#ifdef CMW_WRAPPER_ENABLE_ROS
        std::function<void(const OusterScan&)> h0 = nullptr;
#else
        std::function<void(const uint8_t*, size_t)> h0 = nullptr;
#endif

        if (publish_scan_)
        {
            converter_ = std::make_shared<OusterPcdConverter>(convert_param_, correct_param_, extrinsic);

            /* subscriber & install callback */
#ifdef CMW_WRAPPER_ENABLE_ROS
            scan_sub_ = bus_.AddReader<OusterScan, ros_wrapper::DefaultConversionTraits<OusterScan>>(scan_topic_);
#else
            scan_sub_ = bus_.AddReader<uint8_t*>(scan_topic_);
#endif

#ifdef CMW_WRAPPER_ENABLE_ROS
            if (use_compress_)
            {
                LOG(ERROR) << "ouster donot support compress";
                h0 = std::bind(&OusterConverterApp::DataCallbackGetScan, this, std::placeholders::_1);
            }
            else
            {
                h0 = std::bind(&OusterConverterApp::DataCallbackGetScan, this, std::placeholders::_1);
            }
#else
            if (use_compress_)
            {
                LOG(ERROR) << "ouster donot support compress";
                h0 = std::bind(&OusterConverterApp::DataCallbackGetDDSScan, this, std::placeholders::_1, std::placeholders::_2);
            }
            else
            {
                h0 = std::bind(&OusterConverterApp::DataCallbackGetDDSScan, this, std::placeholders::_1, std::placeholders::_2);
            }
#endif
            scan_sub_.SetOnDataAvailableCallback(h0);
        }
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "ouster driver app failed to create converter";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    cmw_wrapper::BusType::AsyncSpin(1);
    while (cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

bool OusterConverterApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        scan_topic_           = node["scan_topic"].as<std::string>();
        extrinsic_            = node["extrinsic"].as<std::string>();
        use_compress_         = node["use_compress"].as<bool_t>();
        publish_scan_         = node["publish_scan"].as<bool_t>();
        LOG(INFO) << "scan_topic                   = " << scan_topic_;
        LOG(INFO) << "extrinsic                    = " << extrinsic_;
        LOG(INFO) << "use_compress                 = " << use_compress_;
        LOG(INFO) << "publish_scan                 = " << publish_scan_;

        holo::yaml::Node cvt_node                     = node["convert"];
        convert_param_.grid                           = cvt_node["grid"].as<bool>();
        convert_param_.min_dis                        = cvt_node["min_dis"].as<float32_t>();
        convert_param_.max_dis                        = cvt_node["max_dis"].as<float32_t>();
        convert_param_.start_azimuth                  = cvt_node["start_azimuth"].as<float32_t>();
        convert_param_.end_azimuth                    = cvt_node["end_azimuth"].as<float32_t>();
        convert_param_.start_azimuth                  = std::min<float32_t>(convert_param_.start_azimuth, 360.0f);
        convert_param_.start_azimuth                  = std::max<float32_t>(convert_param_.start_azimuth, 0.0f);
        convert_param_.end_azimuth                    = std::min<float32_t>(convert_param_.end_azimuth, 360.0f);
        convert_param_.end_azimuth                    = std::max<float32_t>(convert_param_.end_azimuth, 0.0f);
        convert_param_.lidar_origin_to_beam_origin_mm = cvt_node["lidartobeam_dis"].as<float32_t>();

        LOG(INFO) << "convert_param_.grid          = " << convert_param_.grid;
        LOG(INFO) << "convert_param_.min_dis       = " << convert_param_.min_dis;
        LOG(INFO) << "convert_param_.max_dis       = " << convert_param_.max_dis;
        LOG(INFO) << "convert_param_.start_azimuth = " << convert_param_.start_azimuth;
        LOG(INFO) << "convert_param_.end_azimuth   = " << convert_param_.end_azimuth;

        holo::yaml::Node crr_node = node["correct"];
        for (size_t i = 0; i != crr_node.size(); i++)
        {
            float32_t vertical_angle       = holo::geometry::Radian<float32_t>(crr_node[i]["Vertical"].as<float32_t>());
            float32_t azimuth_correction   = -holo::geometry::Radian<float32_t>(crr_node[i]["Azimuth"].as<float32_t>());
            correct_param_.data[i].cosines = std::cos(vertical_angle);
            correct_param_.data[i].sines   = std::sin(vertical_angle);
            correct_param_.data[i].azimuth_correction = azimuth_correction;
        }
        LOG(INFO) << "loading correction parameters successfully";
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "failed to load convert/correction parameters: " << e.what();
        return false;
    }
    return true;
}

void OusterConverterApp::DataCallbackGetScan(OusterScan const& scan)
{
    PointCloudType pcd;

    if (0 == converter_->ParseScan(scan, pcd))
    {
        LOG(ERROR) << static_cast<uint32_t>(pcd.GetCoordinate()) << "." << pcd.GetTimestamp().ToSec() << "is empty";
    }

    lidar_utils_.SavePlyFile(pcd);
}

void OusterConverterApp::DataCallbackGetDDSScan(const uint8_t* data, size_t size)
{
    PointCloudType pcd;

    if (0 == converter_->ParseScan(data, size, pcd))
    {
        LOG(ERROR) << static_cast<uint32_t>(pcd.GetCoordinate()) << "." << pcd.GetTimestamp().ToSec() << "is empty";
    }

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
    cxxopts::Options options(argv[0], "ouster-converter");
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/ouster_converter_" + node_name + ".log");
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
        holo_cmw::OusterConverterApp driver(domain_id, "");
        driver.Setup(options["config_file"].as<std::string>(), options["output_name"].as<std::string>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exit : " << e.what();
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
