/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_hap_app.cpp
 * @brief A driver for livox hap scan messages output
 * @author wujie<wujie@holomatic.com>
 * @date 2020/08/19
 */

#include <holo/os/time.h>
#include <holo/sensors/utils/livox_crc.h>
#include <lidar/livox/livox_hap_app.h>
#include <lz4.h>
#include <signal.h>
#include <csignal>
#include <iostream>
#include <sstream>
#include <vector>

namespace holo_cmw
{
template <typename LivoxPacketType>
void LivoxHapDriverApp<LivoxPacketType>::Setup(const std::string& config_file, bool_t blocking_mode)
{
    /* parse configure file */
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "livox driver app failed to load config file";
        LOG(ERROR) << oss.str();
        throw std::invalid_argument(oss.str());
    }

    /* initial memory */
#if defined(MDC_PRODUCTION_MDC610)
    holo::mdc610::GetTimeDiffBlocked(timediff_);
#endif

    /* load extrinsic */
    if (!holo::IsAbsolutePath(extrinsic_))
    {
        extrinsic_ = holo::sensors::GetHoloSensorsExtrinsicsDirectory() + extrinsic_;
    }
    LOG(INFO) << "loading extrinsics from " << extrinsic_;
    holo::common::Extrinsicf extrinsic = holo::common::Extrinsicf::LoadYaml(extrinsic_);
    sensor_id_                         = extrinsic.GetSensorId();

    /* create device */
    driver_ = std::make_shared<LivoxDriverType>(coord_, packet_rate_, scan_rate_);

    /* install callback */
    std::function<void(const LivoxScanType&)> h;
    if (publish_scan_)
    {
        /* parse converter params */
        static const uint32_t buffer_size = 4;
        uint8_t               buffer[buffer_size];
        SerializerType        serializer(buffer, buffer_size);
        serializer << packet_rate_;
        lidar_scan_ = std::make_shared<LidarScan>(LidarScan::LidarType::LIVOXHAP, use_compress_, extrinsic,
                                                  serializer.GetData(), serializer.GetSize());
        /* publisher */
        scan_pub_ = bus_->AddWriter<uint8_t*>(scan_topic_);
        h         = std::bind(&LivoxHapDriverApp<LivoxPacketType>::ScanDataCallback, this, std::placeholders::_1);
    }
    else
    {
        /* create converter */
        try
        {
            converter_ = std::make_shared<LivoxPcdConverter>(extrinsic, packet_rate_);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "failed to create livox converter";
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
        h        = std::bind(&LivoxHapDriverApp<LivoxPacketType>::SavePcdToShm, this, std::placeholders::_1);
    }
    driver_->InstallCallback(h);

#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&LivoxHapDriverApp<LivoxPacketType>::Background, this, config_file);
    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename LivoxPacketType>
void LivoxHapDriverApp<LivoxPacketType>::Background(const std::string& config_file)
{
    /* tx buffer */
    uint16_t tx_seq = 0;
    uint8_t  tx_buffer[50];
    uint32_t tx_length = 50;

    /* device addr struct */
    struct sockaddr_in target_addr;
    std::memset(&target_addr, 0, sizeof(struct sockaddr_in));
    target_addr.sin_family      = AF_INET;                        // IPv4
    target_addr.sin_addr.s_addr = inet_addr(device_ip_.c_str());  // IP
    target_addr.sin_port        = htons(broadcast_port_);         // CTRL PORT

    /* timestamp_compensation */
    holo::yaml::Node    root = holo::yaml::LoadFile(config_file);
    TimediffGetterParam timediff_param(root["time_compensation"]);
    TimediffBase::SetEnable(timediff_param.enable);
    /* HAP create Timediff getter anaway, This branch only useing on data collection(pilot real data system) */
    // #if defined(APP_MAIN_FUNCTION)
    TimediffGetter               timediff_getter(timediff_param);
    std::function<void(int64_t)> timediff_callback = std::bind(&TimediffBase::SetValue, this, std::placeholders::_1);
    timediff_getter.InstallCallback(timediff_callback);
    // #endif

    /* udp interface */
    /* create data interface */
    holo::yaml::Node                            node0 = holo::yaml::LoadFile(config_file)["data_interface"];
    UdpInterfaceParam                           data_if_param(node0);
    UdpInterface<LivoxPacketType>               data_interface(data_if_param);
    std::function<void(const LivoxPacketType&)> h0 =
        std::bind(&LivoxDriverType::PushPacket, driver_.get(), std::placeholders::_1);
    data_interface.InstallCallback(h0);
    LOG(INFO) << "created data interface";
    /* create ctrl interface */
    holo::yaml::Node                              node1 = holo::yaml::LoadFile(config_file)["ctrl_interface"];
    UdpInterfaceParam                             ctrl_if_param(node1);
    UdpInterface<LivoxHapCmdPacket>               ctrl_interface(ctrl_if_param);
    std::function<void(const LivoxHapCmdPacket&)> h1 =
        std::bind(&LivoxHapDriverApp<LivoxPacketType>::CmdCallback, this, std::placeholders::_1);
    ctrl_interface.InstallCallback(h1);
    LOG(INFO) << "created control interface";

    /* Lidar work control */
    /* start sampling */
    {
        LivoxHapControlInfo info(holo::sensors::livox::NORMAL_MODE, 11, 30, 0xff);
        holo::Timer         timer(1.0f);
        while (!start_sampling_)
        {
            timer.Start();
            if (!cmw_wrapper::BusType::IsRunning())
            {
                return;
            }
            LOG(INFO) << "send start sampling message to device";
            driver_->generateWorkControlPacket(tx_seq++, tx_buffer, tx_length, info);
            if (tx_length > 0)
            {
                ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
            }
            else
            {
                LOG(INFO) << "generateWorkControlPacket Error!";
            }
            timer.Stop();
        }
    }
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

    /* stop sampling */
    {
        LivoxHapControlInfo info(holo::sensors::livox::WAKE_MODE, 11, 30, 0xff);
        holo::Timer         timer(1.0f);
        while (start_sampling_)
        {
            timer.Start();
            LOG(INFO) << "send stop sampling message to device";
            driver_->generateWorkControlPacket(tx_seq++, tx_buffer, tx_length, info);
            if (tx_length > 0)
            {
                ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
            }
            else
            {
                LOG(INFO) << "generateWorkControlPacket Error!";
            }
            timer.Stop();
        }
    }
    LOG(INFO) << "stop to receive data";
}

template <typename LivoxPacketType>
void LivoxHapDriverApp<LivoxPacketType>::CmdCallback(const LivoxHapCmdPacket& packet)
{
    /* judge of message type (ACK) */
    if (0x01 != packet.CmdType())
    {
        LOG(WARNING) << "packet contains command type invalid: " << static_cast<uint32_t>(packet.CmdType());
        return;
    }

    /* judge of cmd ID */
    if (0x00 == packet.CmdId()) /* Broadcast Descovery */
    {
        if (0x00 == packet.CmdData()[0]) /* ret code */
        {
            connected_ = true;
            LOG(WARNING) << "Broadcast successfully";
        }
        else
        {
            connected_ = false;
            LOG(WARNING) << "Broadcast failed, return code = " << static_cast<uint32_t>(packet.CmdData()[0]);
        }
        // std::memcpy(dest, args, sizeof(struct sockaddr_in));
    }
    else if (0x02 == packet.CmdId()) /* lidar work control */
    {
        if (0x00 == packet.CmdData()[0]) /* ret code */
        {
            if (!start_sampling_) /* stop status */
            {
                start_sampling_ = true;
                LOG(WARNING) << "start sampling successfully";
            }
            else /* start status */
            {
                start_sampling_ = false;
                LOG(WARNING) << "stop sampling successfully";
            }
        }
        else /* error */
        {
            start_sampling_ = false;
            LOG(WARNING) << "start sampling failed, return code = " << static_cast<uint32_t>(packet.CmdData()[0]);
        }
        // std::memcpy(dest, args, sizeof(struct sockaddr_in));
    }
    else
    {
        /* ignore now */
        LOG(WARNING) << "CmdId: " << packet.CmdId();
    }
}

template <typename LivoxPacketType>
bool_t LivoxHapDriverApp<LivoxPacketType>::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        device_ip_            = node["device"]["ip"].as<std::string>();
        broadcast_port_       = node["device"]["broadcast_port"].as<uint16_t>(56000u);
        packet_rate_          = node["device"]["packet_rate"].as<uint32_t>();
        coord_                = node["coord"].as<uint32_t>();
        scan_rate_            = node["scan_rate"].as<uint32_t>();
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        publish_scan_         = node["publish_scan"].as<holo::bool_t>();
        use_compress_         = node["use_compress"].as<bool_t>();
        time_check_           = node["time_check"].as<holo::bool_t>();
        extrinsic_            = node["extrinsic"].as<std::string>(); /* for converter usage */

        LOG(INFO) << "device.ip             = " << device_ip_;
        LOG(INFO) << "device.broadcast_port = " << broadcast_port_;
        LOG(INFO) << "device.packet_rate    = " << packet_rate_;
        LOG(INFO) << "coord                 = " << coord_;
        LOG(INFO) << "scan_rate             = " << scan_rate_;
        LOG(INFO) << "scan_topic            = " << scan_topic_;
        LOG(INFO) << "pcd_topic             = " << pcd_topic_;
        LOG(INFO) << "publish_scan          = " << publish_scan_;
        LOG(INFO) << "use_compress_         = " << use_compress_;
        LOG(INFO) << "time_check_           = " << time_check_;
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
template <typename LivoxPacketType>
void LivoxHapDriverApp<LivoxPacketType>::SavePcdToShm(const LivoxScanType& scan)
{
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].GetTimestamp(), scan_rate_)))
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

template <typename LivoxPacketType>
void LivoxHapDriverApp<LivoxPacketType>::ScanDataCallback(const LivoxScanType& scan)
{
    /* Is time check */
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].GetTimestamp(), scan_rate_)))
    {
        return;
    }

#if defined(MDC_PRODUCTION_MDC610)
    holo::mdc610::GetTimeDiff(timediff_);
    TimediffBase::SetValue(timediff_.ToNsec());
#endif

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
        SerializerType serializer(scan_data_.get(), HAP_DATA_CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
            frames_++;
        }
    }
}

template class LivoxHapDriverApp<holo::sensors::format::LivoxHapPacket<1440>>;

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
    cxxopts::Options options(argv[0], "livox-driver");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("LivoxHapDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/livox_" + node_name + ".log");
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
        holo_cmw::LivoxHapDriverApp<holo::sensors::format::LivoxHapPacket<1440>> driver(domain_id, "");
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