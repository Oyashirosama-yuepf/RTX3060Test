/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velodyne_app.cpp
 * @brief A driver for velodyne scan messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/11/26
 */

#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <lidar/velodyne/velodyne_app.h>
#include <csignal>

namespace holo_cmw
{
template <size_t PACKET_RATE>
void VelodyneDriverApp<PACKET_RATE>::Setup(const std::string& config_file)
{
    LOG(INFO) << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "vlp driver app could not load file!";
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
    holo::yaml::Node convert_node      = holo::yaml::LoadFile(config_file)["convert"];

    /* create device */
    driver_ = std::make_shared<VelodyneDriver>(PACKET_RATE, scan_rate_, rpm_, coord_, use_gps_);

    /*install callback */
    std::function<void(const VelodyneScan&)> h0;
    if (publish_scan_)
    {
        static const uint32_t                        buffer_size = 1024;
        uint8_t                                      buffer[buffer_size];
        holo::sensors::velodyne::CorrectionParameter correct_param(correct_node);
        holo::sensors::velodyne::ConvertParameter    convert_param(convert_node);
        SerializerType                               serializer(buffer, buffer_size);
        if (correct_param.Serialize(serializer) && convert_param.Serialize(serializer))
        {
            lidar_scan_ = std::make_shared<LidarScan>(LidarScan::LidarType::VELODYNE, use_compress_, extrinsic,
                                                      serializer.GetData(), serializer.GetSize());
        }
        else
        {
            LOG(ERROR) << "Converter Params Serialize Error!";
        }

        scan_pub_ = bus_.AddWriter<uint8_t*>(scan_topic_);
        h0        = std::bind(&VelodyneDriverApp<PACKET_RATE>::VelodyneCallbackSendScan, this, std::placeholders::_1);
    }
    else
    {
        /* publisher */
        pcd_pub_ = bus_.AddWriter<uint64_t>(pcd_topic_);
        /* create converter */
        try
        {
            /* load yaml */
            if (!holo::IsAbsolutePath(extrinsic_))
            {
                extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
            }
            LOG(INFO) << "loading extrinsics from " << extrinsic_;
            auto extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
            converter_     = std::make_shared<VelodynePcdConverter>(cvt_node_, crr_node_, extrinsic);
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "create converter faild: " << e.what();
        }
        /* open shm */
        try
        {
            pcd_ipc_ = std::make_shared<PointCloudIpc>(sensor_id_);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create shm";
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
        h0 = std::bind(&VelodyneDriverApp<PACKET_RATE>::VelodyneCallbackSavePcdToShm, this, std::placeholders::_1);
    }
    driver_->InstallCallback(h0);
    /* interface */
    holo::yaml::Node node = holo::yaml::LoadFile(config_file)["data_interface"];
    data_interface_       = std::make_shared<UdpInterface<VelodynePacket>>(node);
    std::function<void(const VelodynePacket&)> h1 =
        std::bind(&VelodyneDriver::PushPacket, driver_.get(), std::placeholders::_1);
    data_interface_->InstallCallback(h1);
    if (use_gps_)
    {
        holo::yaml::Node node2 = holo::yaml::LoadFile(config_file)["sync_interface"];
        sync_interface_        = std::make_shared<UdpInterface<VelodyneGpsPacket>>(node2);
        std::function<void(const VelodyneGpsPacket&)> h2 =
            std::bind(&VelodyneDriver::PushGpsPacket, driver_.get(), std::placeholders::_1);
        sync_interface_->InstallCallback(h2);
    }
    /* timestamp_compensation */
    holo::yaml::Node    node3 = holo::yaml::LoadFile(config_file)["time_compensation"];
    TimediffGetterParam timediff_param(node3);
    TimediffBase::SetEnable(timediff_param.enable);
#if defined(APP_MAIN_FUNCTION)
    TimediffGetter               timediff_getter(timediff_param);
    std::function<void(int64_t)> timediff_callback = std::bind(&TimediffBase::SetValue, this, std::placeholders::_1);
    timediff_getter.InstallCallback(timediff_callback);
#endif

    while (cmw_wrapper::BusType::IsRunning())
    {
        cmw_wrapper::BusType::Spin(1);
    }
}

template <size_t PACKET_RATE>
bool_t VelodyneDriverApp<PACKET_RATE>::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        // model_                = node["model"].as<std::string>();
        rpm_          = node["rpm"].as<uint32_t>();
        coord_        = node["coord"].as<uint32_t>();
        use_gps_      = node["use_gps"].as<bool>();
        scan_topic_   = node["scan_topic"].as<std::string>();
        pcd_topic_    = node["pcd_topic"].as<std::string>();
        time_check_   = node["time_check"].as<holo::bool_t>();
        scan_rate_    = node["scan_rate"].as<uint32_t>();
        publish_scan_ = node["publish_scan"].as<bool_t>();
        extrinsic_    = node["extrinsic"].as<std::string>();
        use_compress_ = node["use_compress"].as<bool_t>();

        // LOG(INFO) << "model      = " << model_;
        LOG(INFO) << "rpm          = " << rpm_;
        LOG(INFO) << "coord        = " << coord_;
        LOG(INFO) << "use_gps      = " << use_gps_;
        LOG(INFO) << "scan_topic   = " << scan_topic_;
        LOG(INFO) << "pcd_topic    = " << pcd_topic_;
        LOG(INFO) << "time_check   = " << time_check_;
        LOG(INFO) << "scan_rate    = " << scan_rate_;
        LOG(INFO) << "publish_scan = " << publish_scan_;
        LOG(INFO) << "extrinsic    = " << extrinsic_;
        LOG(INFO) << "use_compress = " << scan_rate_;

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

template <size_t PACKET_RATE>
void VelodyneDriverApp<PACKET_RATE>::VelodyneCallbackSendScan(const VelodyneScan& scan)
{
    /* Is time check */
    holo::common::Timestamp timestamp(static_cast<uint64_t>(scan[0].Timestamp()));
    if (time_check_ && (!holo::sensors::TimeCheck(timestamp, scan_rate_)))
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
        SerializerType serializer(scan_data_.get(), CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
            frames_++;
        }
    }
}

template <size_t PACKET_RATE>
void VelodyneDriverApp<PACKET_RATE>::VelodyneCallbackSavePcdToShm(const VelodyneScan& scan)
{
    holo::common::Timestamp timestamp(static_cast<uint64_t>(scan[0].Timestamp()));
    if (time_check_ && (!holo::sensors::TimeCheck(timestamp, scan_rate_)))
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

}  // namespace holo_cmw

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "velodyne-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("VelodyneDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/velodyne_driver_" + node_name + ".log");
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
        holo::yaml::Node node  = holo::yaml::LoadFile(options["config_file"].as<std::string>());
        std::string      model = node["model"].as<std::string>();
        LOG(INFO) << "model = " << model;
        try
        {
            if (model == "VLP16")
            {
                holo_cmw::VelodyneDriverApp<760u> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
            else if (model == "VLP32A")
            {
                holo_cmw::VelodyneDriverApp<1520u> driver(domain_id, "");
                driver.Setup(options["config_file"].as<std::string>());
            }
            else
            {
                LOG(ERROR) << "unknown vlp model, exit";
            }
        }
        catch (const std::exception& e)
        {
            LOG(ERROR) << "appication failed, exit";
        }
    }
    catch (std::exception& e)
    {
        LOG(ERROR) << "failed to read vlp model, exit";
    }
    holo::log::HoloLogger::Shutdown();
    return 0;
}
