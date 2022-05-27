/*!
 * \brief holo cmw wrapper of visual based slam
 * \author Yanwei Du, duyanwei@holomatic.com
 * \date April-01-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <localization/deep/feature_detector_cmw.h>

#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
static const char* APP_NAME = "FeatureDetectorCmw";
///////////////////////////////////////////////////////////////////////////////
FeatureDetectorCmw::FeatureDetectorCmw(const std::string& config_file, const uint32_t domain_id, const std::string& ns)
  : bus_(domain_id, ns)
  , deepslam_base_(nullptr)
  , visualizer_(nullptr)
  , input_image_callback_counter(0)
  , output_features_callback_counter(0)
  , camera_params_(nullptr)
{
    signal(SIGINT, BusType::SignalHandler);
    SetUp(config_file);
}

///////////////////////////////////////////////////////////////////////////////
FeatureDetectorCmw::~FeatureDetectorCmw()
{
}

///////////////////////////////////////////////////////////////////////////////
void FeatureDetectorCmw::Spin(holo::uint16_t const num_threads)
{
    // start feature_detector node
    {
        if (visualizer_)
        {
            visualizer_->Spin();
        }
        deepslam_base_->Spin();
    }
    bus_.Spin(num_threads);
}

///////////////////////////////////////////////////////////////////////////////
void FeatureDetectorCmw::Stop()
{
    if (deepslam_base_)
    {
        deepslam_base_->Stop();
    }

    if (visualizer_)
    {
        visualizer_->Stop();
    }
}

///////////////////////////////////////////////////////////////////////////////
void FeatureDetectorCmw::SetUp(const std::string& config_file)
{
    LOG(INFO) << "FeatureDetectorCmw --- set up ... ";

    // initialize yaml node
    const holo::yaml::Node& deepslam_base_node = holo::yaml::LoadFile(config_file);

    LOG(INFO) << "FeatureDetectorCmw --- initialize subscribers and publichers ...";
    // initialize subscribers and publichers
    {
        // Step 1: loading topics
        const holo::yaml::Node& topics_node = deepslam_base_node["topics"];
        const Topics            topics      = Topics::LoadFromYaml(topics_node);
        LOG(INFO) << topics;

        // Step 2: initialize subs and pubs
        if (topics.input_images.empty())
        {
            throw std::runtime_error(
                "FeatureDetectorCmw -- init image subscriber failed. input image topics is empty.\n");
        }

        cmw_readers_writers_.images_reader.reserve(topics.input_images.size());

        for (size_t i = 0; i < topics.input_images.size(); i++)
        {
            cmw_readers_writers_.images_reader.emplace_back(bus_.AddReader<holo::uint32_t>(topics.input_images.at(i)));
            cmw_readers_writers_.images_reader[i].SetOnDataAvailableCallback(
                std::bind(&FeatureDetectorCmw::InputImageCallback, this, std::placeholders::_1, i));
        }

        cmw_readers_writers_.point_feature_writer =
            bus_.AddWriter<holo::parking::vision::PointFeaturePtrListf,
                           BusType::DefaultConversionTraitsType<holo::parking::vision::PointFeaturePtrListf> >(
                topics.output_features);
    }

    LOG(INFO) << "FeatureDetectorCmw --- initialize feature detector ...";
    //  initialize deepslam base
    {
        const auto deepslam_base_parameters = DeepSLAMBase::Parameters::LoadFromYaml(deepslam_base_node["deepslam"]);
        LOG(INFO) << deepslam_base_parameters;
        deepslam_base_ = std::make_shared<DeepSLAMBase>(deepslam_base_parameters);
        camera_params_ = deepslam_base_parameters.camera_params;

        deepslam_base_->SetFeaturesCallback(
            std::bind(&FeatureDetectorCmw::OutputFeatureLists, this, std::placeholders::_1, std::placeholders::_2));
    }

    LOG(INFO) << "FeatureDetectorCmw --- initialize image_ipc for image data retrieving ...";
    // initialize image_ipc for image data retrieving
    {
        const holo::yaml::Node& camera_node = deepslam_base_node["deepslam"]["camera_params"];
        camera_parameters_                  = CameraParameters::LoadFromYaml(camera_node);

        if (camera_parameters_->camera_coords.empty())
        {
            throw std::runtime_error("FeatureDetectorCmw --- init image_ipc failed. no camera intrinsic.\n");
        }

        // initialize image_ipc for image data retrieving
        for (uint16_t i = 0; i < camera_parameters_->camera_number; i++)
        {
            const deep::IntrinsicPtr& intrinsic = camera_parameters_->intrinsics.at(i);

#ifdef USE_NV12
            image_ipcs_.emplace_back(std::make_shared<holo::sensors::camera::ImageIpc>(
                intrinsic->GetSensorId(), static_cast<uint32_t>(intrinsic->GetHeight()),
                static_cast<uint32_t>(intrinsic->GetWidth()), holo::Image::Encoding::NV12));
#else
            image_ipcs_.emplace_back(std::make_shared<holo::sensors::camera::ImageIpc>(
                intrinsic->GetSensorId(), static_cast<uint32_t>(intrinsic->GetHeight()),
                static_cast<uint32_t>(intrinsic->GetWidth()), holo::Image::Encoding::RGB));
#endif
        }
    }

    // initialize visulizer
    const holo::yaml::Node& vis_node = deepslam_base_node["vis"];

    if (vis_node["enable_visualizer"].as<bool>(false))
    {
        LOG(INFO) << "FeatureDetectorCmw --- initialize visulizer ...";
        const auto& vis_parameters = Visualizer::Parameters::LoadFromYaml(vis_node);
        LOG(INFO) << vis_parameters;
        visualizer_ = std::make_shared<Visualizer>(vis_parameters, camera_parameters_);
        deepslam_base_->SetVisualizationCallback(
            std::bind(&Visualizer::ProcessNodeState, visualizer_, std::placeholders::_1));

        LOG(INFO) << "FeatureDetectorCmw --- launched viusualizer!!";
    }
}

///////////////////////////////////////////////////////////////////////////////
void FeatureDetectorCmw::InputImageCallback(holo::uint32_t msg, uint16_t camera_index)
{
    (void)msg;

    if (image_ipcs_.empty() || camera_index > image_ipcs_.size() - 1)
    {
        return;
    }

    Image image;

    if (!image_ipcs_.at(camera_index)->GetImageData(image))
    {
        LOG(ERROR) << "FeatureDetectorCmw --- could not get image from camera"
                   << camera_parameters_->camera_coords.at(camera_index);
        throw std::runtime_error("FeatureDetectorCmw --- unknown error happens for multi camera driver system.");
    }

    auto mat = image.GetCvType();
    deepslam_base_->ProcessImage(image, camera_index);

    LOG(INFO) << "FeatureDetectorCmw --- Obtain " << input_image_callback_counter++ << " images.";
}

///////////////////////////////////////////////////////////////////////////////
holo::int32_t FeatureDetectorCmw::OutputFeatureLists(const Features& input_features, const Timestamp& input_timestamp)
{
    if (input_features.empty())
    {
        return false;
    }

    const auto camera_id = input_features.at(0).camera_id;

    PointFeaturePtrList output_feature_lists;
    output_feature_lists.SetTimestamp(input_timestamp);
    output_feature_lists.SetSensorId(camera_params_->intrinsics.at(camera_id)->GetSensorId());

    // point feature list
    auto& output_point_feature_list = output_feature_lists.GetPointFeatureList();
    for (uint16_t i = 0; i < input_features.size(); i++)
    {
        auto& input_feature = input_features.at(i);

        Point2f        output_point(input_feature.image_point.x, input_feature.image_point.y);
        float32_t      ouput_confidence(input_feature.score);
        DescriptorType output_descriptor(input_feature.optional_descriptor->reshape(1, 1));

        PointFeature output_point_feature(output_point, output_descriptor, ouput_confidence);
        output_point_feature_list.emplace_back(std::make_shared<PointFeature>(output_point_feature));
    }
    cmw_readers_writers_.point_feature_writer.Write(output_feature_lists);

    LOG(INFO) << "FeatureDetectorCmw--- Publish " << output_features_callback_counter++ << " messages. ";

    return 1;
}
}  // namespace holo_cmw

///////////////////////////////////////////////////////////////////////////////
holo::int32_t main(holo::int32_t argc, char** argv)
{
    // set options
    cxxopts::Options options(holo_cmw::APP_NAME, "FeatureDetector Node");

    options.add_options()("h,help", "help message")(
        "c,config_file", "Configuration file path",
        cxxopts::value<std::string>()->default_value(
            ""))("d,domain_id", "domain id",
                 cxxopts::value<uint32_t>()->default_value(
                     "5"))("n,namespace", "Namespace",
                           cxxopts::value<std::string>()->default_value(
                               ""))("l,log_to_console", "if also outputs glog to console", cxxopts::value<uint8_t>(),
                                    "0")("m,min_log_level",
                                         "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)",
                                         cxxopts::value<holo::uint8_t>()->default_value("1"));

    options.parse(argc, argv);

    if (options.count("help"))
    {
        LOG(INFO) << options.help();
        return 1;
    }

    // creat log file
    std::string log_file = "/tmp/mlc_feature_detector.log";
    if (holo::CreateHoloLogSubdirectory("holo_localization_deep"))
    {
        log_file = holo::GetLogFileAbsolutePath("holo_localization_deep/"
                                                "mlc_feature_detector.log");
    }

    // set google logging
    // google::InitGoogleLogging(argv[0]);
    // google::SetLogDestination(google::FATAL, "");
    // google::SetLogDestination(google::ERROR, "");
    // google::SetLogDestination(google::WARNING, "");
    // google::SetLogDestination(google::INFO, log_file.c_str());
    // FLAGS_alsologtostderr = options["log_to_console"].as<uint8_t>();
    // FLAGS_minloglevel     = options["min_log_level"].as<holo::uint8_t>();

    const uint32_t    domain_id = options["domain_id"].as<uint32_t>();
    const std::string ns        = options["namespace"].as<std::string>();
    LOG(INFO) << "FeatureDetectorCmw --- the domain id is: " << domain_id << ", namespace is: " << ns << "\n";

    // set feature_detector app
    holo_cmw::FeatureDetectorCmw::BusType::Initialize(argc, argv, holo_cmw::APP_NAME);
    holo_cmw::FeatureDetectorCmw app(options["config_file"].as<std::string>(), domain_id, ns);

    app.Spin();

    app.Stop();

    // google::ShutdownGoogleLogging();

    return 0;
}
