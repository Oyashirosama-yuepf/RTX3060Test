/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file rsbpearl_app.cpp
 * @brief A driver for rsbpearl scan messages output
 * @author wujie<wujie@holomatic.com>
 * @date 2021/01/12
 */

#include <holo/common/extrinsic.h>
#include <lidar/rsbpearl/rsbpearl_app.h>
#include <csignal>

namespace holo_cmw
{
void RsbpearlDriverApp::Setup(const std::string& config_file, bool_t blocking_mode)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "rsbpearl driver app failed to load config file";
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
    holo::yaml::Node correct_node      = holo::yaml::LoadFile(config_file)["correct"];

    /* create device */
    driver_ = std::make_shared<RsbpearlDriver>(coord_, packet_rate_, scan_rate_);

    /* install callback */
    std::function<void(const RsbpearlScanType&)> h;
    if (publish_scan_)
    {
        /* parse converter params */
        static const uint32_t                        buffer_size = 300;
        uint8_t                                      buffer[buffer_size];
        holo::sensors::rsbpearl::CorrectionParameter correct_param(correct_node);
        SerializerType                               serializer(buffer, buffer_size);
        if (correct_param.Serialize(serializer))
        {
            lidar_scan_ = std::make_shared<LidarScan>(LidarScan::LidarType::RSBPEARL, use_compress_, extrinsic,
                                                      serializer.GetData(), serializer.GetSize());
        }
        else
        {
            LOG(ERROR) << "Converter Params Serialize Error!";
        }

        scan_pub_ = bus_->AddWriter<uint8_t*>(scan_topic_);
        h         = std::bind(&RsbpearlDriverApp::ScanDataCallback, this, std::placeholders::_1);
    }
    else
    {
        pcd_pub_ = bus_->AddWriter<uint64_t>(pcd_topic_);

        /* create converter */
        try
        {
            converter_ = std::make_shared<RsbpearlConverter>(extrinsic, correct_node);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create rsbpearl converter";
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

        h = std::bind(&RsbpearlDriverApp::SavePcdToShm, this, std::placeholders::_1);
    }
    driver_->InstallScanCallback(h);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_                 = std::make_shared<std::thread>(&RsbpearlDriverApp::Background, this, config_file);
    uint32_t    frames_last = 0;
    holo::Timer timer(1.0f);
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();
        uint32_t frames_this = frames_;
        LOG(INFO) << "data hz = " << frames_this - frames_last;
        frames_last = frames_this;
        timer.Stop();
    }
}

void RsbpearlDriverApp::Background(const std::string& config_file)
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

    /* load data interface param */
    holo::yaml::Node                           node1 = holo::yaml::LoadFile(config_file)["data_interface"];
    UdpInterfaceParam                          data_if_param(node1);
    UdpInterface<RsbpearlPacket>               data_interface(data_if_param);
    std::function<void(const RsbpearlPacket&)> h1 =
        std::bind(&RsbpearlDriver::PushPacket, driver_.get(), std::placeholders::_1);
    data_interface.InstallCallback(h1);
    LOG(INFO) << "created data interface";

    holo::yaml::Node                                node2 = holo::yaml::LoadFile(config_file)["device_info_interface"];
    UdpInterfaceParam                               device_info_if_param(node2);
    UdpInterface<RsbpearlPacketDIFOP>               device_info_interface(device_info_if_param);
    std::function<void(const RsbpearlPacketDIFOP&)> h2 =
        std::bind(&RsbpearlDriverApp::DeviceInfoCallback, this, std::placeholders::_1);
    device_info_interface.InstallCallback(h2);

    LOG(INFO) << "created device info interface";
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

bool RsbpearlDriverApp::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        coord_                = node["coord"].as<uint32_t>();
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        publish_scan_         = node["publish_scan"].as<holo::bool_t>();
        use_compress_         = node["use_compress"].as<holo::bool_t>();
        time_check_           = node["time_check"].as<holo::bool_t>();
        scan_rate_            = node["scan_rate"].as<uint32_t>();
        packet_rate_          = node["packet_rate"].as<uint32_t>();
        extrinsic_            = node["extrinsic"].as<std::string>(); /* for converter usage */

        LOG(INFO) << "coord                 = " << coord_;
        LOG(INFO) << "scan_topic            = " << scan_topic_;
        LOG(INFO) << "pcd_topic             = " << pcd_topic_;
        LOG(INFO) << "publish_scan          = " << publish_scan_;
        LOG(INFO) << "use_compress_         = " << use_compress_;
        LOG(INFO) << "time_check_           = " << time_check_;
        LOG(INFO) << "scan_rate_            = " << scan_rate_;
        LOG(INFO) << "packet_rate_          = " << packet_rate_;
        LOG(INFO) << "extrinsic             = " << extrinsic_;
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
void RsbpearlDriverApp::SavePcdToShm(const RsbpearlScanType& scan)
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

void RsbpearlDriverApp::ScanDataCallback(const RsbpearlScanType& scan)
{
    /* Is time check */
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].GetHeaderTimestamp(), scan_rate_)))
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
        SerializerType serializer(scan_data_.get(), RSBP_DATA_CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
            frames_++;
        }
    }
}

void RsbpearlDriverApp::DeviceInfoCallback(const RsbpearlPacketDIFOP& info_packet)
{
    if (!info_packet.IsValid())
    {
        LOG(ERROR) << "Device Info Header Error!";
    }
    uint32_t                                     buffer_size = 300;
    uint8_t                                      buffer[buffer_size];
    holo::sensors::rsbpearl::CorrectionParameter correct_param;
    info_packet.VerticalOffset(correct_param.vertical_angle);
    info_packet.HorizontalOffset(correct_param.azimuth_correction);
    SerializerType serializer(buffer, buffer_size);

    if (correct_param.Serialize(serializer))
    {
        lidar_scan_->SetConverterParams(serializer.GetData(), serializer.GetSize());
    }
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
    cxxopts::Options options(argv[0], "rsbpearl-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("RsbpearlDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/rsbpearl_driver_" + node_name + ".log");
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
        holo_cmw::RsbpearlDriverApp driver(domain_id, "");
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
