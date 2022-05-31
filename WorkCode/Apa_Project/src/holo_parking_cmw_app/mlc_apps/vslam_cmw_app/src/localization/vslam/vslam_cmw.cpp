/*!
 * \brief holo cmw wrapper of visual based slam
 * \author Yanwei Du, duyanwei@holomatic.com
 * \date April-01-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/geometry/angle.h>
#include <holo/log/hololog.h>
#include <localization/vision/vslam/vslam_cmw.h>
#include <cmw_wrapper/utils/cxxopts.hpp>

namespace holo_cmw
{
static const char* APP_NAME = "VSLAMCmw";
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMCmw::VSLAMCmw(const std::string& config_file, const uint32_t domain_id, const std::string& ns)
  : bus_(domain_id, ns)
  , vslam_(nullptr)
  , visualizer_(nullptr)
  , E_bn_(Rot3::Rz(-M_PI / 2.0), Point3::Zero())
  , chassis_state_buffer_(1000)
  , ground_truth_buffer_(100)
{
    signal(SIGINT, BusType::SignalHandler);
    SetUp(config_file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VSLAMCmw::~VSLAMCmw()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::Spin(holo::uint16_t const num_threads)
{
    // start vslam
    {
        if (visualizer_)
        {
            visualizer_->Spin();
        }

        if (vslam_)
        {
            vslam_->Spin();
            LOG(INFO) << "VSLAMCmw --- everything is ready, start vslam ... ";
        }
    }

    if (debugging_parameters_.use_ground_trurh_as_estimated)
    {
        LOG(INFO) << "VSLAMCmw --- enable using ground trurh odometry as estimated result.\n";
    }

    bus_.Spin(num_threads);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::Stop()
{
    if (vslam_)
    {
        vslam_->Stop();
    }

    if (visualizer_)
    {
        visualizer_->Stop();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::SetUp(const std::string& config_file)
{
    LOG(INFO) << "VSLAMCmw --- set up ... ";

    // initialize yaml node
    using holo::yaml::Node;
    const Node node = holo::yaml::LoadFile(config_file);

    // create base parameters node
    const std::string base_params_file =
        holo::GetHoloConfigRootDirectory() + "/" + node["vslam_base_params_file"].as<std::string>("");
    if (!boost::filesystem::exists(base_params_file))
    {
        LOG(ERROR) << "Localization --- failed to load vslam base parameters, invalid base_params_file: \n"
                   << base_params_file << "\n";
        throw std::runtime_error("Localization --- failed to load vslam base parameters");
    }

    const holo::yaml::Node base_params_node = holo::yaml::LoadFile(base_params_file);

    // initialize debugging parameters
    {
        const Node debugging_parameters_node = base_params_node["debugging_parameters"];
        debugging_parameters_                = DebuggingParameters::LoadFromYaml(debugging_parameters_node);
        LOG_IF(INFO, debugging_parameters_.verbose) << debugging_parameters_;
    }

    // initialize subscribers and publishers
    {
        // Step 1: loading topics
        const Node   topics_node = base_params_node["topics"];
        const Topics topics      = Topics::LoadFromYaml(topics_node);
        LOG(INFO) << topics;

        // Step 2: initialize subs and pubs
        if (topics.input_images.empty())
        {
            throw std::runtime_error("VSLAMCmw --- init image subscriber failed. input image topics is empty.\n");
        }

        cmw_readers_writers_.images_reader.reserve(topics.input_images.size());
  
        for (size_t i = 0; i < topics.input_images.size(); i++)
        {
            cmw_readers_writers_.images_reader.emplace_back(bus_.AddReader<holo::uint32_t>(topics.input_images.at(i)));
            cmw_readers_writers_.images_reader[i].SetOnDataAvailableCallback(
                std::bind(&VSLAMCmw::InputImageCallback, this, std::placeholders::_1, i));
        }

        cmw_readers_writers_.obstacle_list_reader = bus_.AddReader<vslam::ObstaclePtrList>(topics.input_obstacle_list);
        cmw_readers_writers_.obstacle_list_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputObstacleGeneralListCallback, this, std::placeholders::_1));

        cmw_readers_writers_.point_feature_list_reader =
            bus_.AddReader<PointFeaturePtrList>(topics.input_point_feature_list);
        cmw_readers_writers_.point_feature_list_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputPointFeatureListCallback, this, std::placeholders::_1));

        cmw_readers_writers_.imu_reader = bus_.AddReader<vslam::Imu>(topics.input_imu);
        cmw_readers_writers_.imu_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputImuCallback, this, std::placeholders::_1));

        cmw_readers_writers_.chassis_state_reader = bus_.AddReader<vslam::ChassisState>(topics.input_chassis_state);
        cmw_readers_writers_.chassis_state_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputChassisStateCallback, this, std::placeholders::_1));

        cmw_readers_writers_.gps_position_reader = bus_.AddReader<vslam::GnssPosition>(topics.input_gps_position);
        cmw_readers_writers_.gps_position_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputGpsPositionCallback, this, std::placeholders::_1));

        cmw_readers_writers_.gravity_aligned_odometry_reader =
            bus_.AddReader<vslam::Odometry>(topics.input_gravity_aligned_odometry);
        cmw_readers_writers_.gravity_aligned_odometry_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputGravityAlignedOdometryCallback, this, std::placeholders::_1));

        cmw_readers_writers_.ground_truth_odometry_reader =
            bus_.AddReader<vslam::Odometry>(topics.input_ground_truth_odometry);
        cmw_readers_writers_.ground_truth_odometry_reader.SetOnDataAvailableCallback(
            std::bind(&VSLAMCmw::InputGroundTruthOdometryCallback, this, std::placeholders::_1));

        cmw_readers_writers_.vslam_odometry_writer = bus_.AddWriter<vslam::Odometry>(topics.output_vslam_odometry);

        cmw_readers_writers_.imu_prediction_odometry_writer =
            bus_.AddWriter<vslam::Odometry>(topics.output_imu_prediction_odometry);

        cmw_readers_writers_.vehicle_pose_2d_writer =
            bus_.AddWriter<VehiclePose>(topics.output_hpa_local);

        cmw_readers_writers_.local_feature_map_writer =
            bus_.AddWriter<PointCloudXYZIRRgbSt>(topics.output_local_feature_map);

        cmw_readers_writers_.global_feature_map_writer =
            bus_.AddWriter<PointCloudXYZIRRgbSt>(topics.output_global_feature_map);

        cmw_readers_writers_.global_correspondence_writer =
            bus_.AddWriter<PointCloudXYZIRRgbSt>(topics.output_global_correspondence);
    }

    // working mode
    mode_ = node["mode"].as<std::string>("localization");
    LOG(INFO) << "mode = " << mode_;

    // initialize vslam and visualizer
    if (debugging_parameters_.use_ground_trurh_as_estimated)
    {
        if (mode_ == "mapping")
        {
            const holo::yaml::Node mdm_node = node["mdm_params"];

            // load map data directory
            auto map_data_dir = mdm_node["map_data_dir"].as<std::string>("");

            if (!holo::IsAbsolutePath(map_data_dir))
            {
                map_data_dir = holo::GetHoloConfigRootDirectory() + "/" + map_data_dir;
            }

            // load map name
            const auto map_names = mdm_node["map_names"].as<std::vector<std::string>>(std::vector<std::string>{});

            // create
            directory_ = map_data_dir + "/" + map_names.front() + "/";

            // remove all old file if exist
            if (boost::filesystem::is_directory(directory_))
            {
                boost::filesystem::remove_all(directory_);
            }

            // create directory to save mapping data
            if (!boost::filesystem::create_directories(directory_))
            {
                std::stringstream ss;
                ss << "MapDatabaseManager --- Failed to create dir: " << directory_ << "\n";
                throw std::runtime_error(ss.str());
            }
        }
    }
    else
    {
        vslam::CameraParameters::Ptr camera_params = nullptr;

        if (mode_ == "mapping")
        {
            // loading vslam parameters
            const auto vslam_parameters = vslam::Mapping::Parameters::LoadFromYaml(node);
            LOG_IF(INFO, debugging_parameters_.verbose) << vslam_parameters;
            vslam_        = std::make_shared<vslam::Mapping>(vslam_parameters);
            camera_params = vslam_parameters.camera_params;
        }
        else if (mode_ == "localization")
        {
            // loading vslam parameters
            const auto vslam_parameters = vslam::Localization::Parameters::LoadFromYaml(node);
            LOG_IF(INFO, debugging_parameters_.verbose) << vslam_parameters;
            vslam_        = std::make_shared<vslam::Localization>(vslam_parameters);
            camera_params = vslam_parameters.camera_params;
        }
        else
        {
            throw std::runtime_error("VSLAMCmw --- unknown mode.\n");
        }

        const Node vis_node = base_params_node["vis"];
        LOG(INFO) << "\n enable_visualizer = " << vis_node["enable_visualizer"].as<bool>(false);

        if (vis_node["enable_visualizer"].as<bool>(false))
        {
            const auto& vis_parameters = vslam::Visualizer::Parameters::LoadFromYaml(vis_node);
            LOG(INFO) << vis_parameters;
            visualizer_ = std::make_shared<vslam::Visualizer>(vis_parameters, camera_params);
            vslam_->SetVisualizationCallback(
                std::bind(&Visualizer::ProcessSlidingWindowState, visualizer_, std::placeholders::_1));
            LOG(INFO) << "VSLAMCmw --- launched vslam viusualizer!!";

            // initialize image_ipc for image data retrieving
            for (uint16_t i = 0; i < camera_params->camera_number; i++)
            {
                const vslam::IntrinsicBaseTypePtr& intrinsic = camera_params->intrinsics.at(i);
                image_ipcs_.emplace_back(std::make_shared<holo::sensors::camera::ImageIpc>(
                    intrinsic->GetSensorId(), static_cast<uint32_t>(intrinsic->GetHeight()),
                    static_cast<uint32_t>(intrinsic->GetWidth()), holo::Image::Encoding::NV12));
            }

            LOG(INFO) << "VSLAMCmw --- initialize image_ipc done!!";
        }

        LOG(INFO) << "VSLAMCmw --- launched vslam ... ";
    }

    ///////////////////////////////////////////////////////////////////////////
    // hook up vslam with cmw subs and pubs
    ///////////////////////////////////////////////////////////////////////////
    if (vslam_)
    {
        if (debugging_parameters_.publish_vslam_result)
        {
            vslam_->SetVslamResultCallback(
                std::bind(&VSLAMCmw::OutputVSLAMResultCallback, this, std::placeholders::_1, std::placeholders::_2));
        }

        vslam_->SetImuPredictionResultCallback(
            std::bind(&VSLAMCmw::OutputImuPredictionResultCallback, this, std::placeholders::_1));

        // output local feature map
        vslam_->SetOutputLocalFeatureMapCallback(
            std::bind(&VSLAMCmw::OutputLocalFeatureMap, this, std::placeholders::_1));

        // output global feature map
        vslam_->SetOutputGlobalFeatureMapCallback(
            std::bind(&VSLAMCmw::OutputGlobalFeatureMap, this, std::placeholders::_1));

        // output global correspondence
        vslam_->SetOutputGlobalCorrespondenceCallback(
            std::bind(&VSLAMCmw::OutputGlobalCorrespondence, this, std::placeholders::_1));
    }

    // initialize extrinsic novatel in body frame
    {
        const Node  extrinsic_node           = base_params_node["vslam"]["camera_params"];
        std::string body_gnss_extrinsic_file = extrinsic_node["body_gnss_extrinsic_file"].as<std::string>("");

        if (body_gnss_extrinsic_file != "")
        {
            E_bn_ = vslam::Pose3(
                vslam::Extrinsic::LoadYaml(holo::GetConfigFileAbsolutePath(body_gnss_extrinsic_file)).GetPose());
        }
        else
        {
            LOG(WARNING) << "vslam --- use default extrinsic novatel "
                         << "in body frame(90 degree)";
        }
    }

    // initialize logging files
    {
        const std::string vslam_relative_dir = "holo_localization_parking/vslam";
        const std::string vslam_absolute_dir = holo::GetLogFileAbsolutePath(vslam_relative_dir);
        // remove old log files
        boost::filesystem::remove_all(vslam_absolute_dir);

        if (!holo::CreateHoloLogSubdirectory(vslam_relative_dir))
        {
            std::stringstream ss;
            ss << "VSLAMCmw --- failed to create logging file directory : " << vslam_absolute_dir;
            LOG(ERROR) << ss.str();
            throw std::runtime_error(ss.str());
        }
        else
        {
            logging_files_ = LoggingFiles(vslam_absolute_dir);
            LOG(INFO) << logging_files_;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputImageCallback(holo::uint32_t msg, uint16_t camera_index)
{
    if (!vslam_)
    {
        return;
    }

    (void)msg;  // msg might help for debugging in future

    if (image_ipcs_.empty() || camera_index > image_ipcs_.size() - 1)
    {
        return;
    }

    vslam::Image image;

    if (!image_ipcs_.at(camera_index)->GetImageData(image))
    {
        LOG(ERROR) << "VSLAMCmw --- could not get image for camera "
                   << vslam_->Params().camera_params->camera_coords.at(camera_index);
        throw std::runtime_error("VSLAMCmw --- unknown error happens for multi camera driver system.");
    }

    cv::Mat nv12 = image.GetCvType();
    cv::Mat gray;
    cv::cvtColor(nv12, gray, CV_YUV2GRAY_NV12);

    const uint16_t width       = gray.cols;
    const uint16_t height      = gray.rows;
    const uint32_t buffer_size = width * height;
    image.SetData(static_cast<uint8_t*>(gray.data), buffer_size, width, height, holo::Image::Encoding::GRAYSCALE);

    vslam_->ProcessImage(image, camera_index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputImuCallback(const vslam::Imu& msg)
{
    if (!vslam_)
    {
        return;
    }

    vslam_->ProcessImu(msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputPointFeatureListCallback(const PointFeaturePtrList& msg)
{
    if (!vslam_)
    {
        return;
    }
    PointFeaturePtrList tmpmsg = msg;
    memset(&tmpmsg, 0, sizeof(tmpmsg));

    // vslam_->ProcessPointFeaturePtrList(msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputChassisStateCallback(const vslam::ChassisState& msg)
{
    if (!vslam_)
    {
        if (debugging_parameters_.use_ground_trurh_as_estimated && mode_ == "mapping")
        {
            std::unique_lock<std::mutex> lock1(chassis_state_buffer_mutex_);
            chassis_state_buffer_.push_back(msg);
        }

        return;
    }

    vslam_->ProcessChassisState(msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputGpsPositionCallback(const vslam::GnssPosition& msg)
{
    if (!vslam_)
    {
        return;
    }

    vslam_->ProcessGnssPosition(msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputGravityAlignedOdometryCallback(const vslam::Odometry& msg)
{
    if (!vslam_)
    {
        return;
    }

    if (!debugging_parameters_.use_ground_trurh_as_gravity_aligned)
    {
        vslam_->ProcessGravityAlignedOdometry(msg);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputGroundTruthOdometryCallback(const vslam::Odometry& msg)
{
    auto odo = msg;

    if (debugging_parameters_.use_ground_trurh_as_estimated)
    {
        ground_truth_buffer_.push_back(odo);
        OutputVSLAMResultCallback(odo, vslam::ImuBias());
        OutputImuPredictionResultCallback(odo);

        if (mode_ == "mapping")
        {
            SaveGroundTruthTrajectoryAndFrontWheelAngle();
        }

        return;
    }

    // process ground truth odometry
    vslam_->ProcessGroundTruthOdometry(odo);

    if (debugging_parameters_.use_ground_trurh_as_gravity_aligned)
    {
        vslam_->ProcessGravityAlignedOdometry(odo);
    }

    if (debugging_parameters_.enable_result_logging)
    {
        // save novatel odometry to file
        holo_io::Save<vslam::Odometry>({odo}, logging_files_.gts);
    }
}

///////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::InputObstacleGeneralListCallback(const vslam::ObstaclePtrList& msg)
{
    if (!vslam_)
    {
        return;
    }

    vslam_->ProcessObstaclePtrList(msg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t VSLAMCmw::OutputVSLAMResultCallback(const vslam::Odometry& odo_m, const vslam::ImuBias& bias)
{
    // publish vslam result in vslam map frame
    cmw_readers_writers_.vslam_odometry_writer.Write(odo_m);

    if (debugging_parameters_.enable_result_logging)
    {
        // save to file
        holo_io::Save<vslam::Odometry>({odo_m}, logging_files_.ess);
        // vslam::Odometry::Append(logging_files_.ess, odo_m);

        // save bias
        {
            std::fstream mybias(logging_files_.bias, std::fstream::app);
            mybias << bias.GetLinearAccelerationBias()[0] << " " << bias.GetLinearAccelerationBias()[1] << " "
                   << bias.GetLinearAccelerationBias()[2] << " " << bias.GetAngularVelocityBias()[0] << " "
                   << bias.GetAngularVelocityBias()[1] << " " << bias.GetAngularVelocityBias()[2] << "\n";
            mybias.close();
        }
    }
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t VSLAMCmw::OutputImuPredictionResultCallback(const vslam::Odometry& odo_m)
{
    // publish imu prediction result in vslam map frame
    cmw_readers_writers_.imu_prediction_odometry_writer.Write(odo_m);

    // save to file if required
    if (debugging_parameters_.enable_result_logging)
    {
        // vslam::Odometry::Append(logging_files_.imu_ess, odo_m);
        holo_io::Save<vslam::Odometry>({odo_m}, logging_files_.imu_ess);
    }

    const auto& t   = odo_m.GetPose().GetTranslation();
    const auto& ypr = odo_m.GetPose().GetRotation().RPY();

    VehiclePose vehicle_pose;
    vehicle_pose.SetPose(VehiclePose::Vector3Type(t.GetX(), t.GetY(), ypr[2]));
    vehicle_pose.SetPredictedPose(VehiclePose::Vector3Type(t.GetX(), t.GetY(), ypr[2]));
    cmw_readers_writers_.vehicle_pose_2d_writer.Write(vehicle_pose);

    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VSLAMCmw::SaveGroundTruthTrajectoryAndFrontWheelAngle()
{
    holo::Timestamp start_chassis_state_time, end_chassis_state_time;

    {
        std::unique_lock<std::mutex> lock1(chassis_state_buffer_mutex_);

        if (chassis_state_buffer_.empty())
        {
            LOG(WARNING) << "VSLAMCmw --- empty chassis_state buffer.";
            return;
        }

        start_chassis_state_time = chassis_state_buffer_.front().GetTimestamp();
        end_chassis_state_time   = chassis_state_buffer_.back().GetTimestamp();
    }

    auto odo = ground_truth_buffer_.front();

    while (odo.GetTimestamp() < start_chassis_state_time && !ground_truth_buffer_.empty())
    {
        odo = ground_truth_buffer_.front();
        ground_truth_buffer_.pop_front();
    }

    if (ground_truth_buffer_.empty())
    {
        LOG(WARNING) << "VSLAMCmw --- empty ground truth buffer.";
        return;
    }

    if (odo.GetTimestamp() > end_chassis_state_time)
    {
        LOG(WARNING) << "VSLAMCmw --- waiting for chassis state.";
        return;
    }

    // get left and right chassis state measurement
    const auto&  odo_timestamp = odo.GetTimestamp();
    ChassisState left_m, right_m;

    {
        std::unique_lock<std::mutex> lock1(chassis_state_buffer_mutex_);
        while (!chassis_state_buffer_.empty())
        {
            auto chassis_state = chassis_state_buffer_.front();
            chassis_state_buffer_.pop_front();

            if (chassis_state.GetTimestamp() < odo_timestamp)
            {
                left_m = chassis_state;
                continue;
            }

            if (chassis_state.GetTimestamp() > odo_timestamp)
            {
                right_m = chassis_state;
                break;
            }
        }

        if (chassis_state_buffer_.empty())
        {
            LOG(WARNING) << "VSLAMCmw --- empty chassis_state buffer.";
            return;
        }
    }

    // interpolate
    const Scalar lt    = left_m.GetTimestamp().ToSec();
    const Scalar rt    = right_m.GetTimestamp().ToSec();
    const Scalar t     = odo_timestamp.ToSec();
    const Scalar ratio = (t - lt) / (rt - lt);
    const Scalar front_wheel_angle =
        left_m.GetFrontWheelAngle() + ratio * (right_m.GetFrontWheelAngle() - left_m.GetFrontWheelAngle());

    // save front wheel angle
    static const std::string front_wheel_angle_file = directory_ + "/front_wheel_angle.txt";
    std::fstream             file(front_wheel_angle_file, std::fstream::app);
    file << odo_timestamp.ToNsec() << " " << front_wheel_angle << "\n";
    file.close();

    // save trajectory
    static const std::string     trajectory_file = directory_ + "/vehicle_odometry.txt";
    std::vector<vslam::Odometry> trajectory{odo};
    holo_io::Save(trajectory, trajectory_file);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t VSLAMCmw::OutputLocalFeatureMap(const PointCloudXYZIRRgbSt& m)
{
    cmw_readers_writers_.local_feature_map_writer.Write(m);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t VSLAMCmw::OutputGlobalFeatureMap(const PointCloudXYZIRRgbSt& m)
{
    cmw_readers_writers_.global_feature_map_writer.Write(m);
    return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t VSLAMCmw::OutputGlobalCorrespondence(const PointCloudXYZIRRgbSt& m)
{
    cmw_readers_writers_.global_correspondence_writer.Write(m);
    return 1;
}
}  // namespace holo_cmw

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(holo::int32_t argc, char** argv)
{
    // set options
    cxxopts::Options options(holo_cmw::APP_NAME, "VSLAM CMW Node");

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
    std::string log_file = "/tmp/mlc_vslam.log";
    if (holo::CreateHoloLogSubdirectory("holo_localization_parking"))
    {
        log_file = holo::GetLogFileAbsolutePath("holo_localization_parking/"
                                                "mlc_vslam.log");
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
    LOG(INFO) << "VSLAMCmw --- the domain id is: " << domain_id << ", namespace is: " << ns << "\n";

    // set vslam localization app
    holo_cmw::VSLAMCmw::BusType::Initialize(argc, argv, holo_cmw::APP_NAME);
    holo_cmw::VSLAMCmw app(options["config_file"].as<std::string>(), domain_id, ns);

    app.Spin();

    app.Stop();

    // google::ShutdownGoogleLogging();

    return 0;
}
