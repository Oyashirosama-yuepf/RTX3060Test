/*!
 *  \brief
 *  \author lizhijian (lizhijian@holomatic.com)
 *  \date 2020-12-07
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/perception/utils/worker.h>
#include <holo/utils/yaml.h>
#include <perception/vision_freespace/vision_freespace_app.h>
#ifdef TIDL_INFERENCE
#include <holo/perception/app/vision_freespace_tidl.h>
#endif
#ifdef HOLO_PERCEPTION_PARKING_WITH_CUDA
#include <holo/perception/app/vision_freespace.h>
#endif
#include <fstream>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
VisionFreespaceApp::VisionFreespaceApp(int argc, char** argv, const std::string config_file, uint32_t domain_id)
  : domain_id_(domain_id), config_file_name_(config_file), vision_freespace_(0)
{
    (void)argc;
    (void)argv;
    InitConfig();
    CreateSubscribersAndPunlishers();

    InitDetector();
}

void VisionFreespaceApp::InitConfig()
{
    try
    {
        debug_image_             = 0;
        holo::yaml::Node node    = holo::yaml::LoadFile(config_file_name_);
        hz_                      = node["hz"].as<holo::float32_t>(hz_);
        debug_image_             = node["debug_image"].as<int32_t>(0);
        debug_image_skip_frames_ = node["debug_image_skip_frames"].as<size_t>(0);
        debug_image_path_        = node["debug_image_path"].as<std::string>();
        detection_params_file_   = node["detection_params_file"].as<std::string>();

        camera_names_                     = node["camera_names"].as<std::vector<std::string>>();
        topic_vision_freespace_publisher_ = node["topic_vision_freespace_publisher"].as<std::string>();
        topic_debug_image_publisher_      = node["topic_debug_image_publisher"].as<std::string>();

        /*
    std::vector<std::vector<holo::int16_t>> camera_resolution_ =
        node["camera_resolution"].as<std::vector<std::vector<holo::int16_t>>>();
    */
        std::vector<std::string> tmp_topic_subscribers =
            node["topic_camera_image_subscribers"].as<std::vector<std::string>>();

        for (size_t i = 0; i < camera_names_.size(); ++i)
        {
            topic_camera_image_subscribers_[camera_names_[i]] = tmp_topic_subscribers[i];
            // camera_resolutions_[camera_names_[i]]             = camera_resolution_[i];
        }
    }
    catch (std::exception& e)
    {
        LOG(FATAL) << "InitConfig Failure : " << config_file_name_ << std::endl << e.what();
    }
}

void VisionFreespaceApp::Run()
{
    BusType::Spin(1);
}

void VisionFreespaceApp::Terminate()
{
}

void VisionFreespaceApp::InitDetector()
{
    // init VisionFreespace
    vision_freespace_ = std::make_shared<VISION_FREESPACE_LIB_TYPE>(detection_params_file_, hz_, debug_image_,
                                                                    debug_image_skip_frames_, debug_image_path_);
    vision_freespace_->DoWork();

    vision_freespace_->SetFreespaceCallback(
        std::bind(&VisionFreespaceApp::PublishFreespaceCallback, this, std::placeholders::_1));

    // init img ipc

#ifdef TIDL_INFERENCE
    for (auto name : camera_names_)
    {
        image_ipcs_[name] = std::make_shared<holo::sensors::camera::ImageIpc>(
            vision_freespace_->camera_configs_[name]->sensor_id_,
            vision_freespace_->camera_configs_[name]->input_size_.height,
            vision_freespace_->camera_configs_[name]->input_size_.width, holo::Image::Encoding::YU12);
    }
#endif

#ifdef HOLO_PERCEPTION_PARKING_WITH_CUDA
    for (auto name : camera_names_)
    {
        image_ipcs_[name] = std::make_shared<holo::sensors::camera::ImageIpc>(
            vision_freespace_->camera_configs_[name]->sensor_id_,
            vision_freespace_->camera_configs_[name]->input_size_.height,
            vision_freespace_->camera_configs_[name]->input_size_.width);
    }
#endif
}

void VisionFreespaceApp::CreateSubscribersAndPunlishers()
{
    bus_ptr_ = std::make_shared<BusType>(domain_id_, std::string("freespace"));
    for (auto name : camera_names_)
    {
        LOG(INFO) << topic_camera_image_subscribers_[name] << std::endl;
        auto reader = bus_ptr_->AddReader<holo::uint32_t>(topic_camera_image_subscribers_[name]);

        reader.SetOnDataAvailableCallback(
            std::bind(&VisionFreespaceApp::CameraSubscriberCallback, this, name, std::placeholders::_1));
        LOG(INFO) << "bind callback on : " << name << std::endl;
    }

    fs_writer_ = bus_ptr_->AddWriter<VISION_FREESPACE_LIB_TYPE::FreespaceType>(topic_vision_freespace_publisher_);
}

void VisionFreespaceApp::CameraSubscriberCallback(const std::string camera_name, holo::uint32_t msg)
{
    (void)msg;

    LOG(INFO) << "App recived : " << camera_name;
    if (!image_ipcs_[camera_name])
    {
        LOG(ERROR) << "Camera image ipc is not ready.";
        return;
    }
    if (!vision_freespace_)
    {
        LOG(ERROR) << "Freespace detector is not ready.";
        return;
    }

    holo::Image img;
    img.SetReceivedStamp(img.GetTriggerStamp());
    image_ipcs_[camera_name]->GetImageData(img);

    vision_freespace_->ReceiveImageFromCamera(img, camera_name);
}

void VisionFreespaceApp::PublishFreespaceCallback(VISION_FREESPACE_LIB_TYPE::FreespaceType& fs)
{
    LOG_EVERY_N(INFO, 10) << "Freespace to send, size : " << fs.size();
    fs_writer_.Write(fs);
}

}  // namespace holo_cmw

int main(int argc, char** argv)
{
    cxxopts::Options options(argv[0], "vision_freespace");

    options.add_options()

        ("h,help", "show this message")("c,config_file", "configuration file path",
                                        cxxopts::value<std::string>()->default_value(
                                            "/opt/holo/config/holo_perception/app_config/vision_freespace.yaml"))(
            "v,verbose", "if also outputs glog to console")(
            "n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("camera_detection"))(
            "m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)",
            cxxopts::value<holo::uint8_t>()->default_value("1"))("d,domain_id", "domain_id",
                                                                 cxxopts::value<uint32_t>()->default_value("5"));

    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 0;
    }

    // ros
    BusType::Initialize(argc, argv, std::string("vision_freespace"));
    signal(SIGINT, BusType::SignalHandler);

    // holo::CreateHoloLogSubdirectory("holo_perception");
    std::string log_file =
        "";  // holo::GetLogFileAbsolutePath("holo_perception/" + options["node_name"].as<std::string>()+ ".log");
    // google::InitGoogleLogging(argv[0]);
    // google::SetLogDestination(google::FATAL, "");
    // google::SetLogDestination(google::ERROR, "");
    // google::SetLogDestination(google::WARNING, "");
    // google::SetLogDestination(google::INFO, log_file.c_str());
    // FLAGS_alsologtostderr = bool(options.count("verbose") > 0);
    // FLAGS_minloglevel     = options["min_log_level"].as<holo::uint8_t>();
    // FLAGS_logtostderr     = true;
    uint32_t domain_id    = options["domain_id"].as<uint32_t>();

    holo_cmw::VisionFreespaceApp app(argc, argv, options["config_file"].as<std::string>(), domain_id);
    app.Run();
    app.Terminate();

    // google::ShutdownGoogleLogging();
    return 0;
}
