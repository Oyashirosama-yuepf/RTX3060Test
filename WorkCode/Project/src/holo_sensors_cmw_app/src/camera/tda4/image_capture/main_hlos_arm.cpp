
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
}

#include <cmw_wrapper/cmw_bus.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

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

typedef struct
{
    vx_uint8* Luma_ptr;
    vx_uint32 Luma_size;
    vx_uint8* Cbcr_ptr;
    vx_uint32 Cbcr_size;
} NV12OutImg;

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

static constexpr uint32_t IMAGE_WIDTH                        = CAP_IMG_WIDTH;
static constexpr uint32_t IMAGE_HEIGHT                       = CAP_IMG_HEIGHT;
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

static std::shared_ptr<holo::sensors::camera::ImageIpc> image_ipc_list[NUM_CAPT_CHANNELS];
static uint32_t                                         image_counter_data[NUM_CAPT_CHANNELS];
static std::shared_ptr<cmw_wrapper::BusType>            bus;
static cmw_wrapper::BusType::WriterType<uint32_t>       image_counter_publishers[NUM_CAPT_CHANNELS];
static cmw_wrapper::BusType::WriterType<uint64_t>       image_info_publishers[NUM_CAPT_CHANNELS];
#if (NUM_CAPT_CHANNELS == 1)
static uint32_t                                         image_skip_counters[NUM_CAPT_CHANNELS];
#endif

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

static void publish(uint8_t index, const NV12OutImg* data, SaveMode save_mode)
{
    LOG(INFO) << "publish: ch = " << static_cast<uint32_t>(index) << ", stamp = " << getTimestamp().ToSec();
#if (NUM_CAPT_CHANNELS == 1)
    if (image_skip_counters[index] == 1)
    {
        image_skip_counters[index] = 0;
        return;
    }
    image_skip_counters[index]++;
#endif
    static holo::Image image(IMAGE_WIDTH, IMAGE_HEIGHT, holo::Image::Encoding::NV12);
    holo::common::Timestamp stamp = getTimestamp();
    image.SetReceivedStamp(stamp);
    image.SetTriggerStamp(stamp);
    std::memcpy(image.GetData(), data->Luma_ptr, data->Luma_size);
    std::memcpy(image.GetData() + data->Luma_size, data->Cbcr_ptr, data->Cbcr_size);
    image_ipc_list[index]->SetImageData(image);
    if (save_mode != SaveMode::NONE)
    {
        cv::Mat img;
        cv::cvtColor(holo::sensors::camera::Image2Mat(image), img, CV_YUV2BGR_NV12);
        std::string name = std::to_string(camera_sid_list[index]);
        if (save_mode == SaveMode::ALL)
        {
            name += "." + std::to_string(image.GetTimestamp().ToSec());
        }
        name += ".jpg";
        cv::imwrite(name.c_str(), img);
    }
    image_counter_publishers[index].Write(image_counter_data[index]);
    uint64_t info = (static_cast<uint64_t>(camera_sid_list[index]) << 32) + image_counter_data[index];
    image_info_publishers[index].Write(info);
    image_counter_data[index]++;
    LOG(INFO) << "publish: exit";
}

static void publish_none(uint8_t index, const NV12OutImg* data)
{
    publish(index, data, SaveMode::NONE);
}

static void publish_single(uint8_t index, const NV12OutImg* data)
{
    publish(index, data, SaveMode::SINGLE);
}

static void publish_all(uint8_t index, const NV12OutImg* data)
{
    publish(index, data, SaveMode::ALL);
}

extern "C" {
extern void (*pcallback)(uint8_t, const NV12OutImg*);
extern int app_encode_main(int argc, char* argv[]);
uint32_t   Running()
{
    return cmw_wrapper::BusType::IsRunning();
}
}

static void signalSegHandler(int sig)
{
    cmw_wrapper::BusType::SignalHandler(sig);
    holo::log::HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
}


int main(int argc, char* argv[])
{
    cxxopts::Options options("ImageCapture", "ImageCapture node");
    // clang-format off
    options.add_options()
        ("h,help", "help message")
        ("c,config_file", "Configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "Node name for this app", cxxopts::value<std::string>()->default_value("tda4_image_capture"))
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
    std::string node_name = options["node_name"].as<std::string>() + "_" + std::to_string(NUM_CAPT_CHANNELS);
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
            camera_sid_list[i], IMAGE_HEIGHT, IMAGE_WIDTH, holo::Image::Encoding::NV12);
        printf("image counter topic[%u] = %s\r\n", i, image_counter_topics[i].c_str());
        image_counter_publishers[i] = bus->AddWriter<uint32_t>(image_counter_topics[i]);
        printf("image info topic[%u] = %s\r\n", i, image_info_topics[i].c_str());
        image_info_publishers[i] = bus->AddWriter<uint64_t>(image_info_topics[i]);
    }

    if (options["save_image"].as<std::string>() == "all")
    {
        pcallback = &publish_all;
    }
    else if (options["save_image"].as<std::string>() == "new")
    {
        pcallback = &publish_single;
    }
    else
    {
        pcallback = &publish_none;
    }

    if (appInit() == 0)
    {
        app_encode_main(argc, argv);
        appDeInit();
    }

    return 0;
}
