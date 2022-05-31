/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensors_proxy_app.cpp
 * @brief A driver for several sensors startup
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021/10/27
 */

#include <sensors_proxy/sensors_proxy_app.h>
#include <csignal>

namespace holo_cmw
{
/* need algin with enum class SensorType */
std::vector<std::string> sensor_type{"NOVATEL", "LIVOX",    "PANDAR40",  "PANDAR128", "RSBPERAL", "RSRUBY",
                                     "HAP",     "GEN_CAM",  "SMART_CAM", "OUSTER",    "STARNETO", "RADAR"};

SensorsProxy::SensorsProxy(const std::string& config_file, uint32_t domain_id)
{
    back_ground_th_running_ = true;
    rcev_app_broadcast_     = false;
    sensors_switch_         = false;
    app_live_counter_       = 0;
    LOG(INFO) << "loading configs from " << config_file;
    holo::yaml::Node node         = holo::yaml::LoadFile(config_file);
    holo::yaml::Node sensors_node = node["sensors"];
    sensors_num_                  = sensors_node.size();

    std::string boradcast_ip      = node["broadcast"]["ip"].as<std::string>();
    uint32_t    boradcast_port    = node["broadcast"]["port"].as<uint32_t>();
    start_ins_cmd_                = node["commands"]["start_ins"].as<std::string>("");
    stop_ins_cmd_                 = node["commands"]["stop_ins"].as<std::string>("");
    start_holobag_cmd_            = node["commands"]["start_holobag"].as<std::string>();
    stop_holobag_cmd_             = node["commands"]["stop_holobag"].as<std::string>();
    mount_ext_storage_dev_cmd_    = node["commands"]["mount_ext_storage_dev_cmd"].as<std::string>("");
    ext_storage_dev_check_cmd_    = node["commands"]["ext_storage_dev_check_cmd"].as<std::string>("");
    ext_storage_dev_name_         = node["commands"]["ext_storage_dev_name"].as<std::string>("");
    mkdir_cmd_                    = node["commands"]["make_data_dir"].as<std::string>("");

    LOG(INFO) << "sensors_num                     = " << sensors_num_;
    LOG(INFO) << "boradcast_ip                    = " << boradcast_ip;
    LOG(INFO) << "boradcast_port                  = " << boradcast_port;
    LOG(INFO) << "start_ins_cmd_                  = " << start_ins_cmd_;
    LOG(INFO) << "start_holobag_cmd_              = " << start_holobag_cmd_;
    LOG(INFO) << "stop_holobag_cmd_               = " << stop_holobag_cmd_;
    LOG(INFO) << "mount_ext_storage_dev_cmd_      = " << mount_ext_storage_dev_cmd_;
    LOG(INFO) << "ext_storage_dev_check_cmd_      = " << ext_storage_dev_check_cmd_;
    LOG(INFO) << "mkdir_cmd_                      = " << mkdir_cmd_;
    LOG(INFO) << "ext_storage_dev_name_           = " << ext_storage_dev_name_;

    SensorStatistics sensors_sta;
    for (uint32_t i = 0; i < sensors_num_; i++)
    {
        /* statistics */
        sensors_sta.id      = sensors_node[i]["id"].as<uint32_t>();
        sensors_sta.name    = sensors_node[i]["sensor_name"].as<std::string>();
        sensors_sta.cpuload = 27;
        sensors_sta.type    = SensorType::UNKNOWN;
        for (uint32_t j = 0; j < sensor_type.size(); j++)
        {
            if (0 == sensors_sta.name.find(sensor_type[j]))  // finded type
            {
                sensors_sta.type = static_cast<SensorType>(j);
                // LOG(INFO) << "sensor_type[j] = " << sensor_type[j];
                if (SensorType::NOVATEL == sensors_sta.type)
                {
                    // LOG(INFO) << "novatel type";
                    sensors_sta.hz.resize(4);
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::ODOMETRY)].min =
                        sensors_node[i]["data_odometry_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::ODOMETRY)].max =
                        sensors_node[i]["data_odometry_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::ODOMETRY)].current = 0;
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::ODOMETRY_T)].min =
                        sensors_node[i]["data_odometry_t_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::ODOMETRY_T)].max =
                        sensors_node[i]["data_odometry_t_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::ODOMETRY_T)].current = 0;
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::IMU)].min =
                        sensors_node[i]["data_imu_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::IMU)].max =
                        sensors_node[i]["data_imu_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::IMU)].current = 0;
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::GNSS_PVT)].min =
                        sensors_node[i]["data_gnss_pvt_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::GNSS_PVT)].max =
                        sensors_node[i]["data_gnss_pvt_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(NovatelMsgType::GNSS_PVT)].current = 0;
                }
                else if (SensorType::SMART_CAMERA == sensors_sta.type)
                {
                    // LOG(INFO) << "smart camera type";
                    sensors_sta.hz.resize(3);
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::OBSTACLES)].min =
                        sensors_node[i]["data_obstacles_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::OBSTACLES)].max =
                        sensors_node[i]["data_obstacles_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::OBSTACLES)].current = 0;
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::ROADFRAME)].min =
                        sensors_node[i]["data_roadframe_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::ROADFRAME)].max =
                        sensors_node[i]["data_roadframe_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::ROADFRAME)].current = 0;
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::SPD_LIMIT_SIGN)].min =
                        sensors_node[i]["data_spd_limit_sign_hz_min"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::SPD_LIMIT_SIGN)].max =
                        sensors_node[i]["data_spd_limit_sign_hz_max"].as<uint32_t>();
                    sensors_sta.hz[static_cast<uint32_t>(SmtCameraMsgType::SPD_LIMIT_SIGN)].current = 0;
                }
                else
                {
                    // LOG(INFO) << "other type";
                    sensors_sta.hz.resize(1);
                    sensors_sta.hz[0].min     = sensors_node[i]["data_hz_min"].as<uint32_t>();
                    sensors_sta.hz[0].max     = sensors_node[i]["data_hz_max"].as<uint32_t>();
                    sensors_sta.hz[0].current = 0;
                }
                break;
            }
        }
        sensors_.push_back(sensors_sta);

        config_file_.push_back(sensors_node[i]["config_file"].as<std::string>());

        if (!holo::IsAbsolutePath(config_file_[i]))
        {
            /*give yaml abs path*/
            config_file_[i] = holo::GetHoloConfigRootDirectory() + "/holo_sensors/app_config/" + config_file_[i];
        }

        LOG(INFO) << "config_file_[" << i << "] = " << config_file_[i];
    }

    /* broadcast addr */
    live_addr_.sin_addr.s_addr = inet_addr(boradcast_ip.c_str());
    live_addr_.sin_port        = holo::os::hton16(boradcast_port);
    live_addr_.sin_family      = AF_INET;

    std::memset(&user_addr_, 0, sizeof(user_addr_));

    LOG(INFO) << "Create interface";
    /* udp */
    status_interface_ = std::make_shared<UdpInterface<RawbufferType>>(node["status_interface"]);
    std::function<void(const RawbufferType&, void*)> h0 =
        std::bind(&SensorsProxy::Callback, this, std::placeholders::_1, std::placeholders::_2, &user_addr_);
    status_interface_->InstallCallback(h0);

    LOG(INFO) << "install call back";

    /* background thread */
    thread_ = std::make_shared<std::thread>(&SensorsProxy::Bg, this, std::ref(live_addr_), std::ref(user_addr_));
    LOG(INFO) << "create thread";
    bus_ = std::make_shared<cmw_wrapper::BusType>(domain_id, "");

    /* execute bash commands */
    std::vector<std::string> rstring_list;
    ShellExec(start_ins_cmd_.c_str(), rstring_list, true);

    if (!(mount_ext_storage_dev_cmd_ == std::string("")))
    {
        bool_t storage_mounted = false;
        while (!storage_mounted)
        {
            LOG(INFO) << "Try to mount external storage device ...";
            ShellExec(mount_ext_storage_dev_cmd_.c_str(), rstring_list, true);
            ShellExec(ext_storage_dev_check_cmd_.c_str(), rstring_list, false);
            for (uint32_t i = 0; i < rstring_list.size(); i++)
            {
                if (std::string::npos != rstring_list[i].find(ext_storage_dev_name_.c_str()))
                {
                    LOG(INFO) << "External storage device mount success!!!";
                    storage_mounted = true;
                    break;
                }
            }
            holo::os::Sleep(1);
        }
    }
    else
    {
        LOG(WARNING) << "No nas mount command, start up sensors directly!";
    }

    cmw_wrapper::BusType::AsyncSpin(1);
    StartUpAllSensors();
    /* timestamp_compensation */
    TimediffGetterParam timediff_param(node["time_compensation"]);
    timediff_getter_ = std::make_shared<TimediffGetter>(timediff_param);
    std::function<void(int64_t)> timediff_callback =
        std::bind(&SensorsProxy::SetTimediffValue, this, std::placeholders::_1);
    timediff_getter_->InstallCallback(timediff_callback);


    holo::yaml::Node node2 = holo::yaml::LoadFile(config_file)["image_sync"];
    sync_interface_        = std::make_shared<UdpInterface<HoloSyncDiffPacket>>(node2);
    std::function<void(const HoloSyncDiffPacket&)> h2 =
        std::bind(&SensorsProxy::SetImageTimesyncData, this, std::placeholders::_1);
    sync_interface_->InstallCallback(h2);
}

void SensorsProxy::SwitchAllSensors(bool_t on_off)
{
    // LOG(INFO) << "now switc is " << sensors_switch_ << ", target switch is " << on_off;
    if (sensors_switch_ != on_off)
    {
        LOG(INFO) << "switch is diff, changing, on_off = " << on_off;
        std::vector<std::string> rstring_list;
        if (on_off)
        {
            ShellExec(mkdir_cmd_.c_str(), rstring_list, true);
            ShellExec(start_holobag_cmd_.c_str(), rstring_list, true);
        }
        else
        {
            ShellExec(stop_holobag_cmd_.c_str(), rstring_list, true);
        }

        sensors_switch_ = on_off;
    }
}

bool SensorsProxy::SetHz(uint32_t sensor_code, uint32_t msg_code, uint32_t hz)
{
    if (sensor_code >= sensors_num_)
    {
        LOG(INFO) << "sensor_code out of range: " << sensor_code;
        return false;
    }
    if (msg_code >= sensors_[sensor_code].hz.size())
    {
        LOG(INFO) << "msg_code out of range: " << msg_code << " >= " << sensors_[sensor_code].hz.size();
        return false;
    }
    sensors_[sensor_code].hz[msg_code].current = hz;
    return true;
}

void SensorsProxy::Callback(const RawbufferType& data, void* args, struct sockaddr_in* dest)
{
    struct sockaddr_in* addr = static_cast<struct sockaddr_in*>(args);
    std::memcpy(dest, addr, sizeof(struct sockaddr_in));

    // LOG(INFO) << "received data from ip = " << inet_ntoa(addr->sin_addr)
    //            << ", port = " << holo::os::hton16(addr->sin_port) << ", data:";

    // for(int i=0; i<4; i++)
    // {
    //     printf("%02X ", data[i]);
    // }
    // LOG(INFO) << "end of callback";

    /* refresh counter */
    temp_live_counter_ = app_live_counter_;
    if ((data[0] == 0xAA) && (data[1] == 0x55) && (data[3] == 0x01))
    {
        rcev_app_broadcast_ = true;
    }
    else
    {
        rcev_app_broadcast_ = false;
        LOG(ERROR) << "Port " << holo::os::hton16(addr->sin_port) << " revceived data, but header not correct !";
    }
}

void SensorsProxy::Bg(const struct sockaddr_in& live_addr, const struct sockaddr_in& user_addr)
{
    /* data */
    uint8_t online_buffer[4];
    online_buffer[0] = 0xAA;
    online_buffer[1] = 0x56;
    online_buffer[2] = 0;
    online_buffer[3] = 1;
    uint8_t status_buffer[1024];
    status_buffer[0] = 0x23;
    status_buffer[1] = 0x23;
    status_buffer[2] = 0;
    status_buffer[3] = sensors_num_;

    /* loop */
    holo::Timer timer(2);
    while (back_ground_th_running_)
    {
        /* 3s time out*/
        if ((app_live_counter_ - temp_live_counter_) > 6)
        {
            rcev_app_broadcast_ = false;
        }
        else
        {
            app_live_counter_++;
        }

        for (uint32_t i = 0; i < sensors_num_; ++i)
        {
            // if want upload 1 sensor's multiple message, need to update communication protocol !!!
            memcpy(&status_buffer[i * 16 + 4], sensors_[i].name.c_str(), sensors_[i].name.size());
            status_buffer[i * 16 + 16] = sensors_[i].cpuload;
            status_buffer[i * 16 + 17] = sensors_[i].hz[0].current;
            status_buffer[i * 16 + 18] = sensors_[i].hz[0].min;
            status_buffer[i * 16 + 19] = sensors_[i].hz[0].max;
        }
        // LOG(INFO) << "Bg(),live_addr.IP = " << inet_ntoa(live_addr.sin_addr) << ", port = "
        //     << holo::os::hton16(live_addr.sin_port) << ", sin_family = " << live_addr.sin_family << ",sin_zero:";
        //     for(int i=0; i<8; i++)
        //     {
        //         printf("%2X ",live_addr.sin_zero[i]);
        //     }
        //     printf("\n");

        struct sockaddr_in status_target_addr;
        std::memcpy(&status_target_addr, &user_addr, sizeof(status_target_addr));
        status_target_addr.sin_port = live_addr_.sin_port;

        // LOG(INFO) << "Bg(),status_target_addr.IP = " << inet_ntoa(status_target_addr.sin_addr) << ", port = "
        //     << holo::os::hton16(status_target_addr.sin_port) << ", sin_family = " << status_target_addr.sin_family <<
        //     ",sin_zero:"; for(int i=0; i<8; i++)
        //     {
        //         printf("%2X ",status_target_addr.sin_zero[i]);
        //     }
        //     printf("\n");

        timer.Start();

        online_buffer[2]++;
        status_buffer[2]++;

        int32_t online_send_ret = status_interface_->Send(online_buffer, 4, &live_addr);
        if (online_send_ret < 0)
        {
            LOG(ERROR) << "Send online buffer faild! online_send_ret = " << online_send_ret;
        }

        if (rcev_app_broadcast_)
        {
            // LOG(INFO) << "sending status";

            // for(int i=0; i<8; i++)
            // {
            //     printf("%2X ",status_buffer[16 + 16 * i]);
            // }
            // printf("\n");
            SwitchAllSensors(true);
            int32_t sta_send_ret = status_interface_->Send(status_buffer, 4 + 16 * sensors_num_, &status_target_addr);
            if ((sta_send_ret < 0) && rcev_app_broadcast_)
            {
                LOG(ERROR) << "Send status buffer faild! sta_send_ret = " << sta_send_ret;
            }
        }
        else
        {
            SwitchAllSensors(false);
        }

        timer.Stop();
    }
}

int32_t SensorsProxy::ShellExec(const char* cmd, std::vector<std::string>& rstring_list, bool nonblock)
{
    rstring_list.clear();
    FILE* pp = popen(cmd, "r");
    if (!pp)
    {
        return -1;
    }
    if (nonblock)
    {
        return 0;
    }
    char tmp[2048];
    while (fgets(tmp, sizeof(tmp), pp) != NULL)
    {
        if (tmp[strlen(tmp) - 1] == '\n')
        {
            tmp[strlen(tmp) - 1] = '\0';
        }
        rstring_list.push_back(tmp);
    }
    pclose(pp);
    return rstring_list.size();
}

void SensorsProxy::SetImageTimesyncData(const HoloSyncDiffPacket& data)
{
    for (auto& it : camera_h264_leopard_m021_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h264_leopard_ap020_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h264_leopard_ar0231_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h264_leopard_ov490_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h264_entron_f001r_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h264_entron_s001r_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h264_v4l2_general_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_leopard_m021_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_leopard_ap020_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_leopard_ar0231_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_leopard_ov490_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_entron_f001r_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_entron_s001r_vec_)
    {
        it->SetTimeSyncData(data);
    }
    for (auto& it : camera_h265_v4l2_general_vec_)
    {
        it->SetTimeSyncData(data);
    }
}


void SensorsProxy::SetTimediffValue(int64_t value) noexcept
{
    for (auto& it : novatel_vec_)
    {
        it->SetValue(value);
    }
    for (auto& it : livox_vec_)
    {
        it->SetValue(value);
    }
    for (auto& it : p128_vec_)
    {
        it->SetValue(value);
    }
    for (auto& it : rsbp_vec_)
    {
        it->SetValue(value);
    }
/* sensors-proxy do not set HAP Timediff value, This branch only useing on data collection(pilot real data system) */
    // for (auto& it : hap_vec_)
    // {
        // it->SetValue(value);
    // }
}

SensorsProxy::~SensorsProxy()
{
    std::vector<std::string> rstring_list;
    ShellExec(stop_ins_cmd_.c_str(), rstring_list, true);
    ShellExec(stop_holobag_cmd_.c_str(), rstring_list, true);

    back_ground_th_running_ = false;
    if (thread_ && thread_->joinable())
    {
        thread_->join();
    }
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
    cxxopts::Options options(argv[0], "sensors_proxy");
    // clang-format off
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("sensors_proxy"))
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
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/sensors_proxy_" + node_name + ".log");
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

    // clang-format off
#if defined(HOLO_PLATFORM_MDC610)
#if (MDC610_VERSION_NUM == 20210430)
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("sensors_proxy_") + node_name, std::string("desc"), 4, 6, std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("sensors_proxy_") + node_name,std::string("desc"), 4);
#else
    Adsfi::AdsfiLogger::GetInstance().InitLogging(std::string("sensors_proxy_") + node_name, std::string("desc"), static_cast<Adsfi::HafLogLevelType>(4), static_cast<Adsfi::HafLogModeType>(6), std::string("./log/holo_sensors/"));
    Adsfi::AdsfiLogger::GetInstance().CreateLogger(std::string("sensors_proxy_") + node_name,std::string("desc"), static_cast<Adsfi::HafLogLevelType>(4));
#endif
#endif
    // clang-format on

    cmw_wrapper::BusType::Initialize(argc, argv, node_name);

    try
    {
        /* proxy */
        holo_cmw::SensorsProxy proxy(options["config_file"].as<std::string>(), domain_id);

        /* loop */
        while (cmw_wrapper::BusType::IsRunning())
        {
            holo::os::Sleep(0.1f);
        }
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "appication failed, exception: " << e.what();
    }
    LOG(INFO) << "log shutdown";
    holo::log::HoloLogger::Shutdown();
    return 0;
}
