
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <exception>
#include <functional>
#include <memory>

extern "C" {
#include <TI/tivx.h>
#include <app_init.h>
#include <app_sensor_module.h>
#include <app_stream.h>
}

#include <cmw_wrapper/cmw_bus.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

#include <holo/log/hololog.h>
#include <holo/core/types.h>
#include <holo/os/time.h>
#include <holo/sensors/camera/image_ipc.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/camera/image_utils.h>
#include <holo/utils/buffer.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/serialization.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>

static int32_t appInit()
{
    int32_t status = 0;

    status = appCommonInit();

    if (status == 0)
    {
        tivxInit();
        tivxHostInit();
    }
    return status;
}

static int32_t appDeInit()
{
    int32_t status = 0;

    tivxHostDeInit();
    tivxDeInit();
    appCommonDeInit();

    return status;
}

static constexpr uint32_t camera_sid_list[NUM_CAPT_CHANNELS] = {
#if (NUM_CAPT_CHANNELS == 1)
    51381647,
#elif (NUM_CAPT_CHANNELS == 4)
    51577487, 51577231, 51578056, 51577672
#else
#error "invalid NUM_CAPT_CHANNELS value"
#endif
};
static const std::string image_counter_topics[NUM_CAPT_CHANNELS] = {
#if (NUM_CAPT_CHANNELS == 1)
    "/holo/sensors/camera/front_center_counter",
#elif (NUM_CAPT_CHANNELS == 4)
    "/holo/sensors/camera/rear_center_counter",
    "/holo/sensors/camera/front_center_gs_counter",
    "/holo/sensors/camera/front_right_counter",
    "/holo/sensors/camera/front_left_counter",
#else
#error "invalid NUM_CAPT_CHANNELS value"
#endif
};
static const std::string image_info_topics[NUM_CAPT_CHANNELS] = {
#if (NUM_CAPT_CHANNELS == 1)
    "/holo/sensors/camera/front_center_info",
#elif (NUM_CAPT_CHANNELS == 4)
    "/holo/sensors/camera/rear_center_info",
    "/holo/sensors/camera/front_center_gs_info",
    "/holo/sensors/camera/front_right_info",
    "/holo/sensors/camera/front_left_info",
#else
#error "invalid NUM_CAPT_CHANNELS value"
#endif
};

static const uint32_t    IMAGE_ENCODE_SIZE_MAX                    = CAP_IMAGE_WIDTH * CAP_IMAGE_HEIGHT * 2u + 256u;
static const std::string image_encoder_topics[NUM_ENCODE_CHANNEL] = {
#if (NUM_ENCODE_CHANNEL == 1)
    "/holo/sensors/camera/front_center_encoder",
#elif (NUM_ENCODE_CHANNEL == 4)
    "/holo/sensors/camera/rear_center_encoder",
    "/holo/sensors/camera/front_center_gs_encoder",
    "/holo/sensors/camera/front_right_encoder",
    "/holo/sensors/camera/front_left_encoder",
#else
#error "invalid NUM_ENCODE_CHANNEL value"
#endif
};

static std::shared_ptr<cmw_wrapper::BusType>            bus;
static std::shared_ptr<holo::sensors::camera::ImageIpc> image_ipc_list[NUM_CAPT_CHANNELS];
static uint32_t                                         image_counter_data[NUM_CAPT_CHANNELS];
static cmw_wrapper::BusType::WriterType<uint32_t>       image_counter_publishers[NUM_CAPT_CHANNELS];
static cmw_wrapper::BusType::WriterType<uint64_t>       image_info_publishers[NUM_CAPT_CHANNELS];
static Nv12OutBuf                                       nv12out_buf[NUM_CAPT_CHANNELS];

static cmw_wrapper::BusType::WriterType<uint8_t*>         image_publishers[NUM_ENCODE_CHANNEL];
static uint8_t                                            image_buffer[NUM_ENCODE_CHANNEL][IMAGE_ENCODE_SIZE_MAX];
static std::shared_ptr<holo::utils::Serializer<false, 4>> image_serializers[NUM_ENCODE_CHANNEL];
static uint32_t                                           image_skip_counters[NUM_ENCODE_CHANNEL];
static EncodeStreamInfo                                   stream_buf[NUM_ENCODE_CHANNEL];

static holo::common::Timestamp getTimestamp()
{
    uint32_t sec = 0, n_sec = 0;
    holo::os::GetSystemTime(sec, n_sec);
    return holo::common::Timestamp(sec, n_sec);
}

enum SaveMode : uint32_t
{
    NONE = 0,
    SINGLE = 1,
    ALL = 2
};

static void publish_rawdata(uint8_t channel, const Nv12OutBuf* data, const holo::common::Timestamp& stamp, SaveMode save_mode)
{
    LOG(INFO) << "publish_rawdata: ch = " << static_cast<uint32_t>(channel) << ", stamp = " << stamp.ToSec();
#if (NUM_ENCODE_CHANNEL == 1)
    if (image_skip_counters[channel] == 1)
    {
        return;
    }
#endif
    static holo::Image image(CAP_IMAGE_WIDTH, CAP_IMAGE_HEIGHT, holo::Image::Encoding::NV12);
    image.SetReceivedStamp(stamp);
    image.SetTriggerStamp(stamp);
    std::memcpy(image.GetData(), data->Luma_ptr, data->Luma_size);
    std::memcpy(image.GetData() + data->Luma_size, data->Cbcr_ptr, data->Cbcr_size);
    image_ipc_list[channel]->SetImageData(image);
    if (save_mode != SaveMode::NONE)
    {
        cv::Mat img;
        cv::cvtColor(holo::sensors::camera::Image2Mat(image), img, CV_YUV2BGR_NV12);
        std::string name = std::to_string(camera_sid_list[channel]);
        if (save_mode == SaveMode::ALL)
        {
            name += "." + std::to_string(image.GetTimestamp().ToSec());
        }
        name += ".jpg";
        cv::imwrite(name.c_str(), img);
    }
    image_counter_publishers[channel].Write(image_counter_data[channel]);
    uint64_t info = (static_cast<uint64_t>(camera_sid_list[channel]) << 32) + image_counter_data[channel];
    image_info_publishers[channel].Write(info);
    image_counter_data[channel]++;
}

static void publish_encoded(uint8_t channel, const EncodeStreamInfo* data, const holo::common::Timestamp& stamp)
{
    LOG(INFO) << "publish_encoded: ch = " << static_cast<uint32_t>(channel) << ", stamp = " << stamp.ToSec();
#if (NUM_ENCODE_CHANNEL == 1)
    if (image_skip_counters[channel] == 1)
    {
        image_skip_counters[channel] = 0;
        return;
    }
    image_skip_counters[channel]++;
#endif
    holo::sensors::camera::ImagePacket packet;
    packet.image_type     = holo::sensors::camera::ImageType::H264;
    packet.frame_type     = holo::sensors::camera::FrameType::UNKNOWN;
    packet.cols           = CAP_IMAGE_WIDTH;
    packet.rows           = CAP_IMAGE_HEIGHT;
    packet.seq            = 0;
    packet.received_stamp = stamp;
    packet.trigger_stamp  = stamp;
    packet.size           = data->datalen;
    packet.data           = const_cast<uint8_t*>(data->mem);
    uint32_t offset       = 0;
    memcpy(&image_buffer[channel][offset], &packet.seq, 4);
    offset += 4;
    uint32_t u32 = packet.received_stamp.GetSec();
    memcpy(&image_buffer[channel][offset], &u32, 4);
    offset += 4;
    u32 = packet.received_stamp.GetNsec();
    memcpy(&image_buffer[channel][offset], &u32, 4);
    offset += 4;
    u32 = packet.trigger_stamp.GetSec();
    memcpy(&image_buffer[channel][offset], &u32, 4);
    offset += 4;
    u32 = packet.trigger_stamp.GetNsec();
    memcpy(&image_buffer[channel][offset], &u32, 4);
    offset += 4;
    memcpy(&image_buffer[channel][offset], &packet.frame_type, 1);
    offset += 4;
    memcpy(&image_buffer[channel][offset], &packet.cols, 4);
    offset += 4;
    memcpy(&image_buffer[channel][offset], &packet.rows, 4);
    offset += 4;
    memcpy(&image_buffer[channel][offset], &packet.image_type, 1);
    offset += 4;
    memcpy(&image_buffer[channel][offset], &packet.size, 4);
    offset += 4;
    memcpy(&image_buffer[channel][offset], packet.data, packet.size);
    offset += packet.size;
    image_publishers[channel].Write(&image_buffer[channel][0], offset);
    // if (packet.Serialize(*image_serializers[channel]))
    //{
    //    image_publishers[channel].Write(&image_buffer[channel][0], image_serializers[channel]->Tellp());
    //}
    // image_serializers[channel]->SetSize(0);
    // image_serializers[channel]->Seekp(0);
}

static bool Running()
{
    return cmw_wrapper::BusType::IsRunning();
}

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("ImageEncoder", "ImageEncoder node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("tda4_image_capture_encoder"))
        ("s,save_image", "Save image mode: new, all", cxxopts::value<std::string>()->default_value(""))
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
    std::string node_name = options["node_name"].as<std::string>() + "_" + std::to_string(NUM_ENCODE_CHANNEL);
    holo::CreateHoloLogSubdirectory("holo_sensors");
    std::string log_file_name = holo::GetLogFileAbsolutePath("holo_sensors/" + node_name + ".log");
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

    bus = std::make_shared<cmw_wrapper::BusType>(domain_id, "");
    for (uint32_t i = 0; i < NUM_CAPT_CHANNELS; ++i)
    {
        image_counter_data[i] = 0;
        image_ipc_list[i]     = std::make_shared<holo::sensors::camera::ImageIpc>(
            camera_sid_list[i], CAP_IMAGE_HEIGHT, CAP_IMAGE_WIDTH, holo::Image::Encoding::NV12);
        image_counter_publishers[i] = bus->AddWriter<uint32_t>(image_counter_topics[i]);
        image_info_publishers[i]    = bus->AddWriter<uint64_t>(image_info_topics[i]);
    }
    for (uint32_t i = 0; i < NUM_ENCODE_CHANNEL; ++i)
    {
        size_t capacity      = IMAGE_ENCODE_SIZE_MAX;
        size_t size          = 0;
        image_serializers[i] = std::make_shared<holo::utils::Serializer<false, 4>>(&image_buffer[i][0], capacity, size);
        image_publishers[i]  = bus->AddWriter<uint8_t*>(image_encoder_topics[i]);
        image_skip_counters[i] = 0;
    }

    if (appInit() == 0)
    {
        app_stream_init();

        while (Running())
        {
            app_stream_run();
            holo::common::Timestamp stamp = getTimestamp();
            for (uint32_t i = 0; i < NUM_CAPT_CHANNELS; ++i)
            {
                app_get_nv12buf(&nv12out_buf[i], i);
                if (options["save_image"].as<std::string>() == "all")
                {
                    publish_rawdata(i, &nv12out_buf[i], stamp, SaveMode::ALL);
                }
                else if (options["save_image"].as<std::string>() == "new")
                {
                    publish_rawdata(i, &nv12out_buf[i], stamp, SaveMode::SINGLE);
                }
                else
                {
                    publish_rawdata(i, &nv12out_buf[i], stamp, SaveMode::NONE);
                }
            }
            for (uint32_t i = 0; i < NUM_ENCODE_CHANNEL; ++i)
            {
                app_get_streambuf(&stream_buf[i], i);
                publish_encoded(i, &stream_buf[i], stamp);
            }
        }

        app_stream_stop();
        app_stream_deinit();
        appDeInit();
    }

    return 0;
}
