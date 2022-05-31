/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file livox_app.cpp
 * @brief A driver for livox scan messages output
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020/11/26
 */

#include <holo/sensors/utils/livox_crc.h>
#include <lidar/livox/livox_app.h>
#include <lz4.h>
#include <csignal>
#if defined(HOLO_PLATFORM_MDC610)
#include <holo/sensors/utils/mdc610_utils.h>
#endif

namespace holo_cmw
{
template <typename LivoxPacketType>
void LivoxDriverApp<LivoxPacketType>::Setup(const std::string& config_file, bool_t blocking_mode)
{
    LOG(INFO) << "loading configs from " << config_file;
    if (!GetParameters(config_file))
    {
        std::ostringstream oss;
        oss << "livox driver app failed to load config file";
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
        lidar_scan_ = std::make_shared<LidarScan>(LidarScan::LidarType::LIVOX, use_compress_, extrinsic,
                                                  serializer.GetData(), serializer.GetSize());
        /* publisher */
        scan_pub_ = bus_->AddWriter<uint8_t*>(scan_topic_);
        h         = std::bind(&LivoxDriverApp<LivoxPacketType>::ScanDataCallback, this, std::placeholders::_1);
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
        h        = std::bind(&LivoxDriverApp<LivoxPacketType>::SavePcdToShm, this, std::placeholders::_1);
    }
    driver_->InstallCallback(h);
#if defined(APP_MAIN_FUNCTION)
    cmw_wrapper::BusType::AsyncSpin(1);
#endif
    thread_ = std::make_shared<std::thread>(&LivoxDriverApp<LivoxPacketType>::Background, this, config_file);

    while (blocking_mode && cmw_wrapper::BusType::IsRunning())
    {
        holo::os::Sleep(1);
    }
}

template <typename LivoxPacketType>
void LivoxDriverApp<LivoxPacketType>::Background(const std::string& config_file)
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
    holo::yaml::Node                            node0 = holo::yaml::LoadFile(config_file)["data_interface"];
    UdpInterfaceParam                           data_if_param(node0);
    UdpInterface<LivoxPacketType>               data_interface(data_if_param);
    std::function<void(const LivoxPacketType&)> h2 =
        std::bind(&LivoxDriverType::PushPacket, driver_.get(), std::placeholders::_1);
    data_interface.InstallCallback(h2);
    LOG(INFO) << "created data interface";
    /* ctrl interface */
    struct sockaddr_in target_addr;
    std::memset(&target_addr, 0, sizeof(struct sockaddr_in));
    holo::yaml::Node                                  node1 = holo::yaml::LoadFile(config_file)["ctrl_interface"];
    UdpInterfaceParam                                 ctrl_if_param(node1);
    UdpInterface<LivoxCmdPacket>                      ctrl_interface(ctrl_if_param);
    std::function<void(const LivoxCmdPacket&, void*)> h0 =
        std::bind(&LivoxDriverApp<LivoxPacketType>::CmdCallback, this, std::placeholders::_1, std::placeholders::_2,
                  &target_addr);
    ctrl_interface.InstallCallback(h0);
    LOG(INFO) << "created control interface";
    /* tx buffer */
    uint16_t tx_seq = 0;
    uint8_t  tx_buffer[100];
    uint32_t tx_length = 0;
    /* monitor */
    {
        holo::yaml::Node             node2 = holo::yaml::LoadFile(config_file)["monitor_interface"];
        UdpInterfaceParam            mon_if_param(node2);
        UdpInterface<LivoxCmdPacket> monitor_interface(mon_if_param);
        LOG(INFO) << "created monitor interface";
        /* fetch device addr */
        struct sockaddr_in dev_addr;
        std::memset(&dev_addr, 0, sizeof(struct sockaddr_in));
        std::function<void(const LivoxCmdPacket&, void*)> h1 =
            std::bind(&LivoxDriverApp<LivoxPacketType>::MonCallback, this, std::placeholders::_1, std::placeholders::_2,
                      &dev_addr);
        monitor_interface.InstallCallback(h1);
        uint32_t ip = static_cast<uint32_t>(inet_addr(device_ip_.c_str()));
        while ((dev_addr.sin_addr.s_addr != ip) || (holo::os::ntoh16(dev_addr.sin_port) != broadcast_port_))
        {
            if (!cmw_wrapper::BusType::IsRunning())
            {
                return;
            }
            LOG(INFO) << "wait for broadcast message...";
            std::unique_lock<std::mutex> lck(broadcast_mtx_);
            broadcast_cv_.wait_for(lck, std::chrono::milliseconds(1000));
        }
        LOG(INFO) << "device identified successfully";
        /* handshake with device */
        {
            /* wait until handshake ok */
            holo::Timer timer(1.0f);
            while (!connected_)
            {
                timer.Start();
                if (!cmw_wrapper::BusType::IsRunning())
                {
                    return;
                }
                LOG(INFO) << "send handshake message to device";
                driver_->generateHandshakePacket(tx_seq++, tx_buffer, tx_length, data_if_param.addr.ip,
                                                 data_if_param.addr.port, ctrl_if_param.addr.port);
                monitor_interface.Send(tx_buffer, tx_length, &dev_addr);
                timer.Stop();
            }
        }
    }
    /* add start sampling */
    {
        /* wait until handshake ok */
        holo::Timer timer(1.0f);
        while (!start_sampling_)
        {
            timer.Start();
            if (!cmw_wrapper::BusType::IsRunning())
            {
                return;
            }
            LOG(INFO) << "send start sampling message to device";
            driver_->generateStartsamplingPacket(tx_seq++, tx_buffer, tx_length);
            ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
            timer.Stop();
        }
    }
    LOG(INFO) << "start to receive data";
    uint32_t frames_last = 0;
    if (sync_available_)
    {
        /* synchronization */
        holo::common::Timestamp      rstamp;
        holo::yaml::Node             node3 = holo::yaml::LoadFile(config_file)["synchronization"]["interface"];
        UdpInterfaceParam            sync_if_param(node3);
        UdpInterface<HoloSyncPacket> sync_interface(sync_if_param);
        std::function<void(const HoloSyncPacket&)> h3 =
            std::bind(&LivoxDriverApp<LivoxPacketType>::SyncCallback, this, std::placeholders::_1, std::ref(rstamp));
        sync_interface.InstallCallback(h3);
        LOG(INFO) << "created sync interface";
        while (cmw_wrapper::BusType::IsRunning())
        {
            driver_->generateHeartbeatPacket(tx_seq++, tx_buffer, tx_length);
            ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
            std::unique_lock<std::mutex> lck(synchronization_mtx_);
            if (std::cv_status::timeout == synchronization_cv_.wait_for(lck, std::chrono::milliseconds(1000)))
            {
                continue;
            }
            driver_->generateUpdateUtcPacket(tx_seq++, tx_buffer, tx_length, rstamp.GetSec(), 0);
            ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
            /* heartbeat */
            uint32_t frames_this = frames_;
            if (live_callback_)
            {
                live_callback_(0, frames_this - frames_last);
            }
            LOG(INFO) << "data hz = " << frames_this - frames_last << ", send heartbeat...";
            frames_last = frames_this;
        }
        return;
    }
    /* heartbeat */
    holo::Timer timer(10.0f);
    while (cmw_wrapper::BusType::IsRunning())
    {
        timer.Start();
        uint32_t sec, nsec;
#if defined(HOLO_PLATFORM_MDC610)
        holo::common::Timestamp ts;
        holo::mdc610::GetManagmentLevelTime(ts);
        sec  = ts.GetSec();
        nsec = ts.GetNsec();
#else
        holo::os::GetSystemTime(sec, nsec);
#endif
        if (nsec < 100000000 || nsec >= 200000000)
        {
            timer.Stop();
            continue;
        }
        driver_->generateUpdateUtcPacket(tx_seq++, tx_buffer, tx_length, sec, 0);  // us has to be set to 0
        ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
        uint32_t frames_this = frames_;
        if (live_callback_)
        {
            live_callback_(0, frames_this - frames_last);
        }
        LOG(INFO) << "data hz = " << frames_this - frames_last << ", send heartbeat...";
        frames_last = frames_this;
        driver_->generateHeartbeatPacket(tx_seq++, tx_buffer, tx_length);
        ctrl_interface.Send(tx_buffer, tx_length, &target_addr);
        timer.Stop();
    }
}

template <typename LivoxPacketType>
void LivoxDriverApp<LivoxPacketType>::CmdCallback(const LivoxCmdPacket& packet, void* args, struct sockaddr_in* dest)
{
    /* judge of message type */
    if (0x01 != packet.CmdType())
    {
        LOG(WARNING) << "packet contains command type invalid: ";
        LOG(INFO) << "cmd_type = " << static_cast<uint32_t>(packet.CmdType())
                  << ",length = " << static_cast<uint32_t>(packet.Length())
                  << ",cmd_set = " << static_cast<uint32_t>(packet.CmdSet())
                  << ",cmd_id = " << static_cast<uint32_t>(packet.CmdId())
                  << ",status_code = " << static_cast<uint32_t>(packet.RetCode());
        return;
    }
    /* judge of cmd set */
    if (0x00 == packet.CmdSet())  // general
    {
        /* judge of cmd id */
        if (0x01 == packet.CmdId())
        {
            if (0x00 == packet.RetCode())
            {
                connected_ = true;
                LOG(WARNING) << "handshake successfully";
            }
            else
            {
                connected_ = false;
                LOG(WARNING) << "handshake failed, return code = " << static_cast<uint32_t>(packet.RetCode());
            }
            std::memcpy(dest, args, sizeof(struct sockaddr_in));
        }
        else if (0x3 == packet.CmdId())
        {
            if (0x00 != packet.RetCode())
            {
                LOG(ERROR) << "heartbeat ack return bad code";
            }
        }
        else if (0x4 == packet.CmdId())
        {
            if (0x00 == packet.RetCode())
            {
                start_sampling_ = true;
                LOG(WARNING) << "start sampling successfully";
            }
            else
            {
                start_sampling_ = false;
                LOG(WARNING) << "start sampling failed, return code = " << static_cast<uint32_t>(packet.RetCode());
            }
            std::memcpy(dest, args, sizeof(struct sockaddr_in));
        }
        else
        {
            /* ignore now */
        }
    }
    else if (0x01 == packet.CmdSet())  // lidar
    {
        /* judge of cmd id */
        if (0x0A == packet.CmdId())
        {
            if (0x00 != packet.RetCode())
            {
                LOG(ERROR) << "update utc synchronization time ack return bad code";
            }
        }
    }
    else
    {
        /* ignore now */
    }
}

template <typename LivoxPacketType>
void LivoxDriverApp<LivoxPacketType>::MonCallback(const LivoxCmdPacket& packet, void* args, struct sockaddr_in* dest)
{
    struct sockaddr_in* addr = static_cast<struct sockaddr_in*>(args);
    /* check message contents */
    if (0x02 != packet.CmdType())
    {
        LOG(WARNING) << "packet contains command type invalid: " << static_cast<uint32_t>(packet.CmdType());
        return;
    }
    /* check source addr */
    uint32_t ip = static_cast<uint32_t>(inet_addr(device_ip_.c_str()));
    LOG(INFO) << "receive.ip = " << inet_ntoa(addr->sin_addr) << ", .port = " << holo::os::ntoh16(addr->sin_port);
    if ((addr->sin_addr.s_addr == ip) && (holo::os::ntoh16(addr->sin_port) == broadcast_port_))
    {
        std::unique_lock<std::mutex> lck(broadcast_mtx_);
        std::memcpy(dest, addr, sizeof(struct sockaddr_in));
        LOG(INFO) << "notify broadcast listener";
        broadcast_cv_.notify_one();
    }
}

template <typename LivoxPacketType>
void LivoxDriverApp<LivoxPacketType>::SyncCallback(const HoloSyncPacket& packet, holo::common::Timestamp& stamp)
{
    std::unique_lock<std::mutex> lck(synchronization_mtx_);
    stamp.SetSec(packet.GetSec());
    stamp.SetNsec(packet.GetNsec());
    synchronization_cv_.notify_one();
}

template <typename LivoxPacketType>
bool_t LivoxDriverApp<LivoxPacketType>::GetParameters(const std::string& config_file)
{
    try
    {
        holo::yaml::Node node = holo::yaml::LoadFile(config_file);
        device_ip_            = node["device"]["ip"].as<std::string>();
        broadcast_port_       = node["device"]["broadcast_port"].as<uint16_t>(65000u);
        packet_rate_          = node["device"]["packet_rate"].as<uint32_t>();
        sync_available_       = node["synchronization"]["available"].as<bool>(false);
        coord_                = node["coord"].as<uint32_t>();
        scan_rate_            = node["scan_rate"].as<uint32_t>();
        scan_topic_           = node["scan_topic"].as<std::string>();
        pcd_topic_            = node["pcd_topic"].as<std::string>();
        publish_scan_         = node["publish_scan"].as<holo::bool_t>();
        time_check_           = node["time_check"].as<holo::bool_t>();
        extrinsic_            = node["extrinsic"].as<std::string>(); /* for converter usage */
        use_compress_         = node["use_compress"].as<bool_t>();

        LOG(INFO) << "device.ip             = " << device_ip_;
        LOG(INFO) << "device.broadcast_port = " << broadcast_port_;
        LOG(INFO) << "device.packet_rate    = " << packet_rate_;
        LOG(INFO) << "sync_available        = " << sync_available_;
        LOG(INFO) << "coord                 = " << coord_;
        LOG(INFO) << "scan_rate             = " << scan_rate_;
        LOG(INFO) << "scan_topic            = " << scan_topic_;
        LOG(INFO) << "pcd_topic             = " << pcd_topic_;
        LOG(INFO) << "publish_scan          = " << publish_scan_;
        LOG(INFO) << "time_check            = " << time_check_;
        LOG(INFO) << "extrinsic             = " << extrinsic_;
        LOG(INFO) << "use_compress          = " << use_compress_;
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
void LivoxDriverApp<LivoxPacketType>::SavePcdToShm(const LivoxScanType& scan)
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
void LivoxDriverApp<LivoxPacketType>::ScanDataCallback(const LivoxScanType& scan)
{
    /* Is time check */
    if (time_check_ && (!holo::sensors::TimeCheck(scan[0].GetTimestamp(), scan_rate_)))
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
        SerializerType serializer(scan_data_.get(), LIVOX_DATA_CAPACITY);
        if (lidar_scan_->Serialize(serializer))
        {
            scan_pub_.Write(scan_data_.get(), serializer.GetSize());
            frames_++;
        }
    }
}

template class LivoxDriverApp<holo::sensors::format::LivoxPacket<96>>;
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
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("LivoxDriver"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/livox_driver_" + node_name + ".log");
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
        holo_cmw::LivoxDriverApp<holo::sensors::format::LivoxPacket<96>> driver(domain_id, "");
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
