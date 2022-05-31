/*!
 * \brief avp mapping class header file in vslam
 * \author Peikai. Guo guopeikai@holomatic.com
 * \date Jun-02-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/mapping/avp_mapping.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat MergeTwoImages(const cv::Mat& image0, const cv::Mat& image1)
{
    int16_t row = std::max<int16_t>(image0.rows, image1.rows);
    int16_t col = image0.cols + image1.cols;
    cv::Mat mosaic_image(row, col, image0.type());
    image0.copyTo(mosaic_image.rowRange(0, image0.rows).colRange(0, image0.cols));
    image1.copyTo(mosaic_image.rowRange(0, image1.rows).colRange(image0.cols, col));
    return mosaic_image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void swapYUV_I420toNV12(unsigned char* i420bytes, unsigned char* nv12bytes, int width, int height)
{
    int nLenY = width * height;
    int nLenU = nLenY / 4;

    memcpy(nv12bytes, i420bytes, width * height);

    for (int i = 0; i < nLenU; i++)
    {
        nv12bytes[nLenY + 2 * i]     = i420bytes[nLenY + i];          // U
        nv12bytes[nLenY + 2 * i + 1] = i420bytes[nLenY + nLenU + i];  // V
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BGR2YUV_nv12(cv::Mat src, cv::Mat& dst)
{
    int width  = src.cols;
    int height = src.rows;
    dst        = cv::Mat(height * 1.5, width, CV_8UC1, Scalar(0));
    cv::Mat src_YUV_I420(height * 1.5, width, CV_8UC1, Scalar(0));  // YUV_I420
    cv::cvtColor(src, src_YUV_I420, CV_BGR2YUV_I420);
    swapYUV_I420toNV12(src_YUV_I420.data, dst.data, width, height);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveDetectFeatures(std::vector<deep::Features> features, uint64_t frame_id)
{
    std::ofstream features_bin(holo::GetHoloConfigRootDirectory() + "/frame_" + std::to_string(frame_id) + ".bin");
    uint16_t      camere_num = features.size();
    features_bin.write((const char*)&camere_num, sizeof(uint16_t));

    for (size_t i = 0; i < features.size(); i++)
    {
        uint16_t single_camera_feature_num = features.at(i).size();
        features_bin.write((const char*)&single_camera_feature_num, sizeof(uint16_t));
    }

    uint16_t des_dim = features.front().front().optional_descriptor->cols;
    features_bin.write((const char*)&des_dim, sizeof(int16_t));

    for (size_t i = 0; i < features.size(); i++)
    {
        for (size_t j = 0; j < features.at(i).size(); j++)
        {
            const cv::Point2f& pt       = features.at(i).at(j).image_point;
            const Scalar       img_pt_x = pt.x;
            const Scalar       img_pt_y = pt.y;
            features_bin.write((const char*)&(img_pt_x), sizeof(Scalar));
            features_bin.write((const char*)&(img_pt_y), sizeof(Scalar));

            const cv::Mat desc = *(features.at(i).at(j).optional_descriptor);
            for (uint16_t k = 0; k < des_dim; k++)
            {
                features_bin.write((const char*)&desc.at<float32_t>(0, k), sizeof(float32_t));
            }

            const Scalar score = features.at(i).at(j).score;
            features_bin.write((const char*)&(score), sizeof(Scalar));
        }
    }
    features_bin.close();
    LOG(INFO) << "Save features done !!!";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::localization::Mat AvpMapping::UndistortedImage(const cv::Mat& cv_img) const
{
    const uint64_t width       = cv_img.cols;
    const uint64_t height      = cv_img.rows;
    const uint32_t buffer_size = width * height;
    holo::Image    holo_image;
    holo_image.SetData(static_cast<uint8_t*>(cv_img.data), buffer_size, width, height,
                       holo::Image::Encoding::GRAYSCALE);
    holo::localization::Mat undistorted_img;
    undistorters_.at(0)->Undistort(holo::localization::Mat(holo_image), undistorted_img);
    return undistorted_img;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::DrawMacthedInfo(const std::vector<std::pair<FeatureTrack, vslam::Feature>>& associated_results,
                                 const cv::Mat& query_image, const cv::Mat& train_image,
                                 const uint64_t camera_index) const
{
    if (query_image.empty() || train_image.empty() || associated_results.empty())
    {
        return;
    }
    cv::namedWindow("matches", 0);
    const uint64_t width       = query_image.cols;
    const uint64_t height      = query_image.rows;
    const uint32_t buffer_size = width * height;
    holo::Image    holo_query_image, holo_train_image;
    holo_query_image.SetData(static_cast<uint8_t*>(query_image.data), buffer_size, width, height,
                             holo::Image::Encoding::GRAYSCALE);

    holo_train_image.SetData(static_cast<uint8_t*>(train_image.data), buffer_size, width, height,
                             holo::Image::Encoding::GRAYSCALE);

    holo::localization::Mat undistorted_query_img, undistorted_train_img;
    undistorters_.at(0)->Undistort(holo::localization::Mat(holo_query_image), undistorted_query_img);
    cv::Mat cv_query_image;
    cv::cvtColor(undistorted_query_img.GetCvType().clone(), cv_query_image, CV_GRAY2BGR);

    undistorters_.at(0)->Undistort(holo::localization::Mat(holo_train_image), undistorted_train_img);
    cv::Mat cv_train_image;
    cv::cvtColor(undistorted_train_img.GetCvType().clone(), cv_train_image, CV_GRAY2BGR);

    // merge two image
    auto image_with_matches = MergeTwoImages(cv_train_image, cv_query_image);

    // draw keypoint
    static const auto  white = cv::Scalar(255, 255, 255);
    static const auto  black = cv::Scalar(0, 0, 0);
    static cv::Point2f shift_pt(train_image.cols, 0);

    std::vector<cv::Point2f> train_kpts;
    std::vector<cv::Point2f> query_kpts;

    for (const auto& item : associated_results)
    {
        // draw train tracks kpts
        const auto& train_kp = item.first.NewestMeasurement().second.at(camera_index).image_point;
        cv::circle(image_with_matches, train_kp, 6, black, -1, cv::LineTypes::LINE_AA);
        cv::circle(image_with_matches, train_kp, 3, white, -1, cv::LineTypes::LINE_AA);
        train_kpts.push_back(train_kp);

        // draw query feature kpts
        const auto& query_kp = item.second.image_point + shift_pt;
        cv::circle(image_with_matches, query_kp, 6, black, -1, cv::LineTypes::LINE_AA);
        cv::circle(image_with_matches, query_kp, 3, white, -1, cv::LineTypes::LINE_AA);
        query_kpts.push_back(query_kp);

        // draw matches
        const auto color = cv::Scalar(128, 128, 255);
        cv::line(image_with_matches, train_kp, query_kp, color, 2, cv::LineTypes::LINE_AA);
    }

    cv::imshow("matches", image_with_matches);
    cv::waitKey(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AvpMapping::Parameters AvpMapping::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    /**
    // save camera yaml
    Intrinsic pinhole_intrinsic;
    pinhole_intrinsic.SetSensorId(51381647);
    pinhole_intrinsic.SetPrinciplePoint(972.007672, 609.011356);
    pinhole_intrinsic.SetFocalLength(1192.872656, 1189.513383);
    pinhole_intrinsic.SetDimension(1920, 1200);
    pinhole_intrinsic.SetDistortionParameter(-0.34255609, 0.13805731, -0.000040426, 0.0000663034, -0.02910199);

    // save intrinsic
    YAML::Node intrinsic_node;
    intrinsic_node                      = pinhole_intrinsic;
    std::string   intrinsic_file_string = "/home/holo/avp_camera.yaml";
    std::ofstream intrinsic_file(intrinsic_file_string);
    intrinsic_file << intrinsic_node;
    intrinsic_file.close();
    */

    // avp map file
    const std::string map_file = node["map_file"].as<std::string>("");
    std::cout << "map file: " << map_file << std::endl;

    const std::string images_path = node["images_path"].as<std::string>("");

    // camera parameters
    const holo::yaml::Node camera_node = node["vslam_camera_params"].as<holo::yaml::Node>(holo::yaml::Node());
    if (camera_node.IsNull())
    {
        std::cout << "the node is null !!!" << std::endl;
    }
    const auto camera_params = CameraParameters::LoadFromYaml(camera_node);
    LOG(INFO) << "vslam camera params: " << camera_params;

    LOG(INFO) << "loading deep camera params ...";
    // camera parameters
    const holo::yaml::Node deep_camera_node   = node["deep_camera_params"];
    const auto             deep_camera_params = deep::CameraParameters::LoadFromYaml(deep_camera_node);

    // raw measurement preprocessor parameters
    const holo::yaml::Node                             rmpp_node = node["rmpp_params"];
    const deep::RawMeasurementPreprocessor::Parameters rmpp_params =
        deep::RawMeasurementPreprocessor::Parameters::LoadFromYaml(rmpp_node);

    // map database manager parameters
    const holo::yaml::Node               mdm_node   = node["mdm_params"];
    const MapDatabaseManager::Parameters mdm_params = MapDatabaseManager::Parameters::LoadFromYaml(mdm_node);

    // max tracking lost frame
    const uint64_t elm_max_tracking_lost_frame = node["elm_max_tracking_lost_frame"].as<uint64_t>(3);

    // epipolar dist threshold
    const Scalar elm_epipolar_dist_th = node["elm_epipolar_dist_th"].as<Scalar>(4e-3);

    // descriptor dist threshold
    const Scalar elm_descriptor_dist_th = node["elm_descriptor_dist_th"].as<Scalar>(0.8);

    // ratio test threshold
    const Scalar elm_ratio_test_th = node["elm_ratio_test_th"].as<Scalar>(0.75);

    // triangulator parameters
    const Triangulator::Parameters triangulator_params =
        Triangulator::Parameters::LoadFromYaml(node["triangulator_params"]);

    // visualize flag
    const auto enable_vis = node["enable_visualizer"].as<bool>(false);

    // load start frame id
    const auto start_frame_id = node["start_frame_id"].as<uint64_t>(0);

    // load end frame id
    const auto end_frame_id = node["end_frame_id"].as<uint64_t>(0);

    return Parameters(map_file, images_path, camera_params, deep_camera_params, rmpp_params, mdm_params,
                      elm_max_tracking_lost_frame, elm_epipolar_dist_th, elm_descriptor_dist_th, elm_ratio_test_th,
                      triangulator_params, enable_vis, start_frame_id, end_frame_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AvpMapping::AvpMapping(const Parameters& parameters)
  : parameters_(parameters)
  , camera_parameters_(parameters_.camera_params)
  , deep_camera_parameters_(parameters_.deep_camera_params)
  , preprocessor_(parameters_.rmpp_params, parameters_.deep_camera_params)
  , triangulator_(parameters_.triangulator_params, parameters_.camera_params)
  , map_database_manager_(parameters_.mdm_params)
  , undistorters_(Utility::CreateImageUndistorters(camera_parameters_->intrinsics))
{
    const auto Tic                       = camera_parameters_->extrinsics.at(0);
    camera_parameters_->extrinsics.at(0) = Pose3(Rot3::RzRyRx(M_PI, 0.0, M_PI / 2.0), Point3(0, 0, 0)) * Tic;

    if (boost::filesystem::exists(holo::GetHoloConfigRootDirectory() + "/avp_path_pose.ply"))
    {
        boost::filesystem::remove(holo::GetHoloConfigRootDirectory() + "/avp_path_pose.ply");
    }

    if (boost::filesystem::exists(holo::GetHoloConfigRootDirectory() + "/avp_optimized.ply"))
    {
        boost::filesystem::remove(holo::GetHoloConfigRootDirectory() + "/avp_optimized.ply");
    }
    avp_map_database_ = LoadAvpMapDatabase(holo::GetHoloConfigRootDirectory() + "/" + parameters_.map_file);

    // load holo avp map database
    /*
    avp_map_database_ = LoadAvpMapDatabase(
        holo::GetHoloConfigRootDirectory() + "/" +
        "holo_localization_parking/vslam/route_1/timestamp_and_frame_id.txt", holo::GetHoloConfigRootDirectory() +
        "/" + "holo_localization_parking/vslam/route_1/values_xvb.txt");
    */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AvpMapping::~AvpMapping()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vslam::Features AvpMapping::ConvertDeepToVslamFeatures(const deep::Features& features)
{
    vslam::Features new_features;
    for (const auto& feature : features)
    {
        if (std::fabs(cv::norm(*feature.optional_descriptor) - 1.0) > 1e-5)
        {
            LOG(ERROR) << "The descriptor is not normed !!!";
        }
        vslam::Feature      new_feature;
        std::vector<Point2> undistorted_point;
        undistorters_.at(feature.camera_id)
            ->UndistortPoints({Point2(feature.image_point.x, feature.image_point.y)}, undistorted_point);
        new_feature.image_point = cv::Point2f(undistorted_point.front().GetX(), undistorted_point.front().GetY());
        camera_parameters_->intrinsics.at(0)->Unproject(undistorted_point.front(), new_feature.normalized_point);
        new_feature.optional_descriptor = feature.optional_descriptor;
        new_feature.score               = feature.score;
        new_feature.camera_id           = feature.camera_id;

        new_features.push_back(new_feature);
    }
    return new_features;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AvpMapping::AvpMapDatabase AvpMapping::LoadAvpMapDatabase(const std::string& img_file_name,
                                                          const std::string& values_file_name)
{
    if (!boost::filesystem::exists(img_file_name))
    {
        LOG(ERROR) << "AvpMapping --- avp map file: " << img_file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    if (!boost::filesystem::exists(values_file_name))
    {
        LOG(ERROR) << "AvpMapping --- avp map file: " << values_file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    AvpMapDatabase avp_database;
    LOG(INFO) << "AvpMapping --- trying to load mp from " << img_file_name << "\n";
    std::ifstream            img_ifs(img_file_name, std::fstream::in);
    std::vector<std::string> image_names;

    // read image name
    while (img_ifs.good())
    {
        uint64_t image_name, frame_id;
        img_ifs >> image_name >> frame_id;
        std::cout << "frame id in image txt: " << frame_id << std::endl;

        // construct avp map database
        if (avp_database.frame_id_to_images.count(frame_id))
        {
            avp_database.frame_id_to_images.at(frame_id).emplace(0, std::to_string(image_name) + ".png");
        }
        CameraIndexedImage new_index_image_map;
        new_index_image_map.emplace((uint64_t)0, std::to_string(image_name) + ".png");
        avp_database.frame_id_to_images[frame_id] = new_index_image_map;
        if (img_ifs.fail())
        {
            break;
        }
    }

    FactorGraph factor_graph;
    // read xvb values
    LOG(INFO) << "AvpMapping --- trying to load mp from " << values_file_name << "\n";
    std::ifstream values_ifs(values_file_name, std::fstream::in);
    while (values_ifs.good())
    {
        // frame_id tx ty tz qw qx qy qz vx vy vz bias_acc_x bias_acc_y bias_acc_z bias_gyro_x bias_gyro_y bias_gyro_z
        uint64_t frame_id = 0;
        Scalar   tx = 0.0, ty = 0.0, tz = 0.0;
        Scalar   qw = 0.0, qx = 0.0, qy = 0.0, qz = 0.0;
        Scalar   vx = 0.0, vy = 0.0, vz = 0.0;
        Scalar   bias_acc_x = 0.0, bias_acc_y = 0.0, bias_acc_z = 0.0;
        Scalar   bias_gyro_x = 0.0, bias_gyro_y = 0.0, bias_gyro_z = 0.0;

        values_ifs >> frame_id >> tx >> ty >> tz >> qw >> qx >> qy >> qz >> vx >> vy >> vz >> bias_acc_x >>
            bias_acc_y >> bias_acc_z >> bias_gyro_x >> bias_gyro_y >> bias_gyro_z;
        if (values_ifs.fail())
        {
            break;
        }

        // construct pose
        static Point3 init_t(tx, ty, tz);

        Point3     t(tx, ty, tz);
        Rot3       r(Quaternion(qw, qx, qy, qz).ToRotationMatrix());
        const auto pose = holo::localization::HoloGtsam::Convert(Pose3(r, t - init_t));

        // insert to values
        if (avp_database.values.exists(X(frame_id)))
        {
            LOG(ERROR) << "AvpMapping --- LoadXVBValues. frame id: " << frame_id << " already exist in values.\n";
            throw std::runtime_error("AvpMapping --- LoadXVBValues. frame id already exist in values.");
        }
        avp_database.values.insert(X(frame_id), pose);

        // add prior factor of pose
        factor_graph.add(gtsam::PriorFactor<gtsam::Pose3>(X(frame_id), pose,
                                                          gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(
                                                              Vector6(0.0349, 0.0349, 0.00349, 1e-3, 1e-3, 1e-3)))));
        DrawCamera(HoloGtsam::Convert(pose) * camera_parameters_->extrinsics.at(0));
        DrawTrajectory(HoloGtsam::Convert(pose));
    }
    current_ba_problem_.pose_graph.add_factors(factor_graph);
    // LOG(INFO) << "saving ply file ... " << pose_and_trajectory_msg_.size() << std::endl;
    // holo::pointcloud::SavePly("/home/holo/avp.ply", pose_and_trajectory_msg_);
    // LOG(INFO) << "Save ply done.";
    current_ba_problem_.values = avp_database.values;
    LOG(INFO) << "AvpMapping --- load avp map database done. total images: " << avp_database.frame_id_to_images.size()
              << "\n";
    return avp_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AvpMapping::AvpMapDatabase AvpMapping::LoadAvpMapDatabase(const std::string& file_name)
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "AvpMapping --- avp map file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "AvpMapping --- trying to load mp from " << file_name << "\n";
    std::ifstream ifs(file_name, std::fstream::in);

    // GNSS 3 degree frame to UTM frame
    Rot3                  R_gnss_to_utm = Rot3::RzRyRx(M_PI, 0.0, M_PI / 2.0);
    AvpMapDatabase        result;
    FactorGraph           factor_graph;
    std::vector<Odometry> trajectory;

    static uint64_t counter = 0;
    // read imus
    while (ifs.good())
    {
        counter++;
        uint64_t    frame_id = 0, camera_id = 0, data = 0;
        std::string image_name = "";
        Scalar      gps_time = 0.0, bj_time = 0.0;
        Scalar      easting = 0.0, northing = 0.0, hell = 0.0;
        Scalar      latitude = 0.0, longitude = 0.0;
        Scalar      roll = 0.0, pitch = 0.0, yaw = 0.0;
        ifs >> frame_id >> image_name >> data >> gps_time >> bj_time >> easting >> northing >> hell >> latitude >>
            longitude >> roll >> pitch >> yaw;
        image_name = image_name.substr(0, image_name.rfind("."));

        if (ifs.fail())
        {
            break;
        }

        if (frame_id < parameters_.start_frame_id || frame_id > parameters_.end_frame_id)
        {
            continue;
        }

        // construct avp map database
        if (result.frame_id_to_images.count(frame_id))
        {
            result.frame_id_to_images.at(frame_id).emplace(camera_id, image_name);
        }
        CameraIndexedImage new_index_image_map;
        new_index_image_map.emplace((uint64_t)camera_id, image_name);
        result.frame_id_to_images[frame_id] = new_index_image_map;

        //---------------- convert longitude and latitude to utm frame---------------------
        holo::uint8_t      zone_id    = holo::utils::LonLatGetUtmZoneId(longitude, latitude);
        holo::bool_t const south_flag = latitude >= 0.0 ? false : true;

        holo::float64_t x_utm = 0.0;
        holo::float64_t y_utm = 0.0;
        holo::utils::LonLatToUtm(longitude, latitude, zone_id, south_flag, x_utm, y_utm);

        std::ofstream utm_txt(holo::GetHoloConfigRootDirectory() + "/utm.txt", std::ofstream::app);
        utm_txt << std::fixed << x_utm << " " << std::fixed << y_utm << "\n";
        utm_txt.close();

        // construct pose
        static Point3 init_t(x_utm, y_utm, hell);
        static Scalar init_yaw   = yaw;
        static Scalar init_roll  = roll;
        static Scalar init_pitch = pitch;
        pose_compensation_       = Pose3(Rot3(), init_t).Inverse();

        Point3     t(x_utm, y_utm, hell);
        Rot3       r    = Rot3::RzRyRx(holo::Radian(roll), holo::Radian(pitch), holo::Radian(yaw));
        const auto pose = holo::localization::HoloGtsam::Convert(Pose3(R_gnss_to_utm.Inverse() * r, t));
        result.values.insert(X(frame_id), pose);

        // add prior factor of pose
        factor_graph.add(gtsam::PriorFactor<gtsam::Pose3>(X(frame_id), pose,
                                                          gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(
                                                              Vector6(0.0349, 0.0349, 0.00349, 1e-3, 1e-3, 1e-3)))));
        (void)init_roll;
        (void)init_yaw;
        (void)init_pitch;

        DrawCamera(HoloGtsam::Convert(pose) * camera_parameters_->extrinsics.at(0));
        DrawTrajectory(HoloGtsam::Convert(pose));

        // create odometry.
        Odometry odom;
        odom.SetTimestamp(holo::Timestamp(0.0));
        odom.SetChildCoordinate(holo::Coordinate());
        odom.SetStatus(Odometry::Status::ALLGOOD);
        odom.SetSource(Odometry::Source::VISION);
        odom.SetPose(holo::localization::HoloGtsam::Convert(pose));
        odom.SetVelocity(Vector6(0.0, 0.0, 0.0, 0.0, 0.0, 0.0));

        trajectory.push_back(odom);
    }
    // save trajectory
    holo_io::Save(trajectory, holo::GetHoloConfigRootDirectory() + "/vehicle_odometry.txt");

    LOG(INFO) << "saving raw avp data ply file ... " << pose_and_trajectory_msg_.size() << std::endl;
    holo::pointcloud::SavePly(holo::GetHoloConfigRootDirectory() + "/avp_path_pose.ply", pose_and_trajectory_msg_);
    LOG(INFO) << "Save ply done.";
    current_ba_problem_.pose_graph.add_factors(factor_graph);
    current_ba_problem_.values = result.values;
    LOG(INFO) << "AvpMapping --- load avp map database done. total images: " << result.frame_id_to_images.size()
              << "\n";
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::run()
{
    // save test image feature
    {
        // std::ifstream ifs(holo::GetHoloConfigRootDirectory() + "/images_name.txt", std::fstream::in);
        // std::string   image_name = "";
        // while (ifs.good())
        // {
        //     ifs >> image_name;
        //     LOG(INFO) << "The test image name is: " << image_name;
        //     if (ifs.fail())
        //     {
        //         break;
        //     }

        //     deep::Image image;
        //     cv::Mat     input_image =
        //         cv::imread(holo::GetHoloConfigRootDirectory() + "/images/" + image_name, cv::IMREAD_GRAYSCALE);

        //     // cv::imshow("front image", input_image);
        //     // cv::waitKey(50);

        //     const uint64_t width       = input_image.cols;
        //     const uint64_t height      = input_image.rows;
        //     const uint32_t buffer_size = width * height;

        //     image.SetData(static_cast<uint8_t*>(input_image.data), buffer_size, width, height,
        //                   Image::Encoding::GRAYSCALE);
        //     const auto deep_features = preprocessor_.ExtractSuperpointFeatures(deep::RawMeasurement({image}));

        //     cv::Mat vis_image;
        //     cv::cvtColor(image.GetCvType(), vis_image, CV_GRAY2RGB);

        //     // visilize super point extract result in original image
        //     for (size_t i = 0; i < deep_features.front().size(); i++)
        //     {
        //         const cv::Point2f& keypoint = deep_features.front().at(i).image_point;
        //         cv::circle(vis_image, cv::Point(keypoint.x, keypoint.y), 5, cv::Scalar(0, 255, 0));
        //     }
        //     cv::imwrite(holo::GetHoloConfigRootDirectory() + "/test_images_sp_result/" + image_name, vis_image);
        //     // SaveDetectFeatures(deep_features, 1);
        // }
    }

    if (parameters_.enable_visualizer)
    {
        cv::namedWindow("tracking result", 0);
    }

    LOG(INFO) << "AvpMapping --- EstimationCore is running ...\n";
    // load map data directory
    std::string map_data_dir = parameters_.images_path;

    if (!IsAbsolutePath(map_data_dir))
    {
        map_data_dir = holo::GetHoloConfigRootDirectory() + "/" + map_data_dir;
    }
    for (const auto item : avp_map_database_.frame_id_to_images)
    {
        TicTocTimer timer;
        timer.Tic();
        CameraIndexedFeatures    camera_index_features;
        std::vector<deep::Image> input_images;
        const auto               frame_id = item.first;
        for (const auto& camera_index_to_image : item.second)
        {
            const auto& image_name = camera_index_to_image.second;
            std::cout << "image name: " << map_data_dir + "/" + image_name + ".jpg" << std::endl;

            deep::Image image;
            cv::Mat     input_image = cv::imread(map_data_dir + "/" + image_name + ".jpg", cv::IMREAD_GRAYSCALE);

            const uint64_t width       = input_image.cols;
            const uint64_t height      = input_image.rows;
            const uint32_t buffer_size = width * height;

            image.SetData(static_cast<uint8_t*>(input_image.data), buffer_size, width, height,
                          Image::Encoding::GRAYSCALE);
            input_images.push_back(image);
        }

        const auto deep_features = preprocessor_.ExtractSuperpointFeatures(deep::RawMeasurement(input_images));
        LOG(INFO) << "deep_feature size: " << deep_features.at(0).size();
        for (size_t i = 0; i < deep_features.size(); i++)
        {
            camera_index_features.emplace(i, ConvertDeepToVslamFeatures(deep_features.at(i)));
        }

        cv::Mat vis_image;
        cv::cvtColor(input_images.front().GetCvType(), vis_image, CV_GRAY2RGB);

        // visilize super point extract result in original image
        // for (size_t i = 0; i < deep_features.front().size(); i++)
        // {
        //     const cv::Point2f& keypoint = deep_features.front().at(i).image_point;
        //     cv::circle(vis_image, cv::Point(keypoint.x, keypoint.y), 5, cv::Scalar(0, 255, 0));
        // }
        // cv::imshow("front_center_camera", vis_image);
        // cv::waitKey(10);

        FeatureMatching(current_ba_problem_.tracks, camera_index_features, current_ba_problem_.values, frame_id);
        LOG(INFO) << "AvpMapping --- EstimationCore runs " << frame_id << " done. Takes: " << 1e3 * timer.Elapsed()
                  << " ms\n ";

        if (parameters_.enable_visualizer)
        {
            // visualize the matching result
            holo::localization::Mat undistort_img;
            undistorters_.front()->Undistort(holo::localization::Mat(input_images.front()), undistort_img);
            cv::cvtColor(undistort_img.GetCvType(), vis_image, CV_GRAY2RGB);

            // draw the tracking result
            const auto vis_img = VisualizeTracks(vis_image, frame_id, current_ba_problem_.tracks);
            cv::imwrite(holo::GetHoloConfigRootDirectory() + "/tracking_result/" + std::to_string(frame_id) + ".png",
                        vis_img);

            cv::imshow("tracking result", vis_img);
            cv::waitKey(10);
        }
    }

    const auto tracks_and_values   = Optimization(current_ba_problem_);
    Map        new_map             = ConvertTracksToMap(tracks_and_values.first, tracks_and_values.second);
    const auto new_frames_database = CreateFramesDatabase(tracks_and_values.first, tracks_and_values.second);
    LOG(INFO) << "Avp Mapping --- optimize avp map done.\n"
              << " create new map num: " << new_map.size()
              << "\n create new key frames num: " << new_frames_database.Size() << "\n";

    map_database_manager_.SaveTheAvpMapAfterOptimizing(tracks_and_values.second, new_frames_database, new_map,
                                                       map_database_manager_.GetParameters().map_names.at(0),
                                                       pose_compensation_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<std::vector<FeatureTrack>, Values> AvpMapping::Optimization(const BundleAdjustmentProblem& ba_problem)
{
    auto        old_tracks       = ba_problem.tracks;
    const auto& old_values       = ba_problem.values;
    const auto& old_factor_graph = ba_problem.pose_graph;
    std::cout << "old factor graph size: " << old_factor_graph.size() << std::endl;

    // the feature association is finished, next we will do these things below:
    // 1. triangulate the featuretracks
    TriangulateNewTracks(old_tracks, old_values);
    LOG(INFO) << "The total tracks num is: " << old_tracks.size();

    // 2. filtered old tracks
    const auto filtered_old_tracks = SelectTracksWithTriangulationResult(old_tracks);
    LOG(INFO) << "The filtered tracks num is: " << filtered_old_tracks.size();

    // 3. add visual factor graph
    const auto new_factor_graph = AddVisualFactorGraph(old_values, old_factor_graph, filtered_old_tracks);
    LOG(INFO) << "new graph size: " << new_factor_graph.size();

    // 4. add landmarks' position to values
    auto new_values = AddLandmarksToValues(old_values, filtered_old_tracks);

    // save ply file for debug
    LOG(INFO) << "saving optimized ply file ... " << pose_and_trajectory_msg_.size() << std::endl;
    holo::pointcloud::SavePly(holo::GetHoloConfigRootDirectory() + "/avp_optimized.ply", pose_and_trajectory_msg_);
    LOG(INFO) << "Save optimized ply done.";

    // 5. optimize the sub map
    const auto optimized_values = GlobalBundleAdjustment(new_factor_graph, new_values);

    // 6. remove the outliers
    new_values = RemoveOutlierLandmarksFromValue(optimized_values, filtered_old_tracks);

    return std::make_pair(filtered_old_tracks, new_values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<FeatureTrack> AvpMapping::CreateNewTracks(const CameraIndexedFeatures& features,
                                                      const uint64_t               frame_id) const
{
    std::vector<FeatureTrack> tracks;
    for (const auto& item : features)
    {
        for (const auto& feature : item.second)
        {
            FeatureTrack::CameraIndexedFeature camera_indexed_feature;
            camera_indexed_feature.emplace(item.first, feature);
            tracks.emplace_back(
                FeatureTrack::CreateNewTrack(parameters_.track_params, camera_parameters_,
                                             FeatureTrack::Measurement(frame_id, camera_indexed_feature)));
        }
    }
    return tracks;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::FeatureMatching(std::vector<FeatureTrack>& tracks, const CameraIndexedFeatures& features,
                                 const Values& values, const uint64_t new_frame_id) const
{
    if (!tracks.size())
    {
        LOG(INFO) << "AvpMapping --- there are no tracks in sliding matching window, Initalizing...\n";
        tracks = CreateNewTracks(features, new_frame_id);
        return;
    }
    if (!values.exists(X(new_frame_id)))
    {
        LOG(ERROR) << "AvpMapping --- there are no frame id: " << new_frame_id << " in values.\n";
    }

    // loop all camras
    for (auto camera_index_feature : features)
    {
        // match old tracks with landmarks
        const uint64_t camera_index = camera_index_feature.first;

        // the features in roi area
        vslam::Features new_features = camera_index_feature.second;

        // compute camera pose in vslam map frame
        const auto prior_Twc = HoloGtsam::Convert(values.at(X(new_frame_id)).cast<gtsam::Pose3>()) *
                               camera_parameters_->extrinsics.at(camera_index);

        // match filtered old tracks by epipolar line matching method
        MatchOldTracksByEpipolarLineMatching(tracks, values, new_frame_id - 1, new_features, new_frame_id, camera_index,
                                             prior_Twc);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::MatchOldTracksByEpipolarLineMatching(std::vector<FeatureTrack>& old_tracks, const Values& old_values,
                                                      const uint64_t old_frame_id, const vslam::Features& new_features,
                                                      const uint64_t new_frame_id, const uint64_t camera_index,
                                                      const Pose3& prior_Twc) const
{
    // filtered_old_tracks contains tracks do not matched success with new_features
    // candidate_old_tracks will be used to match with new features
    std::vector<uint64_t> old_tracks_index;  // old feature's index in window tracks

    // construct features with its observed poses for EpipolarLineMatching
    DescriptorMatcher::FeaturesWithObservedPoses features_with_observed_poses_1, features_with_observed_poses_2;
    features_with_observed_poses_1.reserve(old_tracks.size());
    features_with_observed_poses_2.reserve(new_features.size());

    for (size_t i = 0; i < old_tracks.size(); i++)
    {
        const auto& reference_measurement = old_tracks.at(i).NewestMeasurement();
        const auto& reference_frame_id    = reference_measurement.first;
        if (!reference_measurement.second.count(camera_index))
        {
            continue;
        }
        const auto& reference_feature = reference_measurement.second.at(camera_index);

        // check tracking lost times and the max matching times
        if (reference_frame_id + 3 /* parameters_.dm.elm.max_tracking_lost_frame*/ < old_frame_id ||
            old_tracks.at(i).GetState() == FeatureTrack::State::DEAD ||
            new_frame_id - old_tracks.at(i).NewestMeasurement().first > 1)
        {
            continue;
        }

        // get optimized pose from old values
        if (!old_values.exists(X(reference_frame_id)))
        {
            throw std::runtime_error(
                "AvpMapping --- required frame id dose not exist in values, something must be wrong.\n");
        }
        const Pose3 reference_pose = HoloGtsam::Convert(old_values.at(X(reference_frame_id)).cast<gtsam::Pose3>()) *
                                     camera_parameters_->extrinsics.at(camera_index);
        features_with_observed_poses_1.emplace_back(reference_feature, reference_pose);
        old_tracks_index.push_back(i);
    }

    for (size_t i = 0; i < new_features.size(); i++)
    {
        features_with_observed_poses_2.emplace_back(new_features.at(i), prior_Twc);
    }

    // call EpipolarLineMatching
    TicTocTimer matching_timer;
    matching_timer.Tic();
    const auto match_pairs = DescriptorMatcher::EpipolarLineMatching(
        features_with_observed_poses_1, features_with_observed_poses_2, parameters_.elm_epipolar_dist_th,
        parameters_.elm_descriptor_dist_th, parameters_.elm_ratio_test_th);
    LOG(INFO) << "The feature matching takes " << 1e3 * matching_timer.Elapsed() << " ms\n";

    // visualize matching result
    std::map<uint64_t, std::vector<std::pair<FeatureTrack, vslam::Feature>>> frame_to_tracks_features_matching_pairs;
    for (size_t i = 0; i < match_pairs.size(); i++)
    {
        const auto filtered_tracks_index = match_pairs.at(i).first;
        const auto old_track             = old_tracks.at(old_tracks_index.at(filtered_tracks_index));
        if (!frame_to_tracks_features_matching_pairs.count(old_track.NewestMeasurement().first))
        {
            frame_to_tracks_features_matching_pairs[old_track.NewestMeasurement().first] = {
                std::make_pair(old_track, new_features.at(match_pairs.at(i).second))};
        }
        else
        {
            frame_to_tracks_features_matching_pairs[old_track.NewestMeasurement().first].push_back(
                std::make_pair(old_track, new_features.at(match_pairs.at(i).second)));
        }
    }
    LOG(INFO) << "The new frame id is: " << new_frame_id;
    std::string map_data_dir = parameters_.images_path;

    if (!IsAbsolutePath(map_data_dir))
    {
        map_data_dir = holo::GetHoloConfigRootDirectory() + "/" + map_data_dir;
    }
    const auto query_image_name =
        map_data_dir + "/" + avp_map_database_.frame_id_to_images.at(new_frame_id).at(0) + ".jpg";

    LOG(INFO) << "query image name: " << query_image_name;
    cv::Mat query_image = cv::imread(query_image_name, cv::IMREAD_GRAYSCALE);

    std::vector<cv::Mat> train_images;
    for (const auto& item : frame_to_tracks_features_matching_pairs)
    {
        LOG(INFO) << "The candidate frame to match is: " << item.first << " the tracks size is: " << item.second.size();
        const auto train_iamge_name =
            map_data_dir + "/" + avp_map_database_.frame_id_to_images.at(item.first).at(0) + ".jpg";
        cv::Mat train_image = cv::imread(train_iamge_name, cv::IMREAD_GRAYSCALE);
        train_images.push_back(train_image);
    }

    if (parameters_.enable_visualizer)
    {
        uint64_t image_index = 0;
        for (const auto& item : frame_to_tracks_features_matching_pairs)
        {
            // draw matching result
            DrawMacthedInfo(item.second, query_image, train_images.at(image_index), camera_index);

            // draw epipolar matching
            DrawEpipolarLineMatching(features_with_observed_poses_2, features_with_observed_poses_1, query_image,
                                     train_images.at(image_index), parameters_.elm_epipolar_dist_th,
                                     parameters_.elm_descriptor_dist_th, parameters_.elm_ratio_test_th);
            image_index++;
        }
    }

    // update tracks with new features
    UpdateTracksWithNewFeatures(old_tracks, old_tracks_index, new_features, new_frame_id, camera_index, match_pairs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FramesDatabase AvpMapping::CreateFramesDatabase(const std::vector<FeatureTrack>& feature_tracks,
                                                const Values&                    xvb_values) const
{
    LOG(INFO) << "AvpMapping --- CreateFramesDatabase is running ...\n";
    const auto                          values = xvb_values;
    std::unordered_map<uint64_t, Frame> indexed_frames;

    // loop all tracks
    for (const auto& track : feature_tracks)
    {
        const auto& lm_id = track.GetLandmark()->Id();

        // loop all measurement of this track
        for (const auto& m : track.Measurements())
        {
            // get associated frame id
            const auto& frame_id = m.first;

            // check if this frame exist in values
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "AvpMapping --- frame " << frame_id << " does NOT exist in values.";
                throw std::runtime_error("frame which associated to this track does NOT exist in values\n");
            }

            // check if this is a new frame
            if (!indexed_frames.count(frame_id))
            {
                indexed_frames.emplace(frame_id, Frame(frame_id, camera_parameters_));

                // get vehicle pose of this new frame
                const auto T_wb = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());

                // get pose and image for all camera.
                for (size_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
                {
                    // add camera pose for this camera
                    const auto& T_bc = camera_parameters_->extrinsics.at(camera_index);
                    indexed_frames[frame_id].multi_camera_data[camera_index].pose       = T_wb * T_bc;
                    indexed_frames[frame_id].multi_camera_data[camera_index].image_name = "";
                }
            }

            // loop all camera
            for (size_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
            {
                if (!m.second.count(camera_index))
                {
                    continue;
                }

                // add features to this frame
                const auto& feature = m.second.at(camera_index);
                indexed_frames[frame_id].multi_camera_data[camera_index].features.push_back(feature);
                indexed_frames[frame_id].multi_camera_data[camera_index].associated_landmarks.push_back(lm_id);
            }
        }
    }

    FramesDatabase database;

    for (const auto& indexed_frame : indexed_frames)
    {
        database.AddFrame(indexed_frame.second);
    }

    LOG(INFO) << "AvpMapping --- CreateFramesDatabase done. total frames number: " << indexed_frames.size() << ".";

    return database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values AvpMapping::GlobalBundleAdjustment(const FactorGraph& new_factor_graph, const Values& new_values) const
{
    // optimize by gtsam
    LOG(INFO) << "AvpMapping --- start to do avp map bundle adjustment ...\n";
    gtsam::LevenbergMarquardtParams params;
    params.setVerbosity(
        gtsam::LevenbergMarquardtParams::verbosityLMTranslator(gtsam::LevenbergMarquardtParams::VerbosityLM::LAMBDA));
    gtsam::LevenbergMarquardtOptimizer optimizer(new_factor_graph, new_values, params);
    const Values                       optimized_value = optimizer.optimize();
    LOG(INFO) << "AvpMapping --- sub avp bundle adjustment done.\n";
    return optimized_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values AvpMapping::RemoveOutlierLandmarksFromValue(const Values&                    values,
                                                   const std::vector<FeatureTrack>& feature_tracks) const
{
    LOG(INFO) << "AvpMapping --- start remove outlier landmarks after optimization ...\n";
    Values   new_value   = values;
    uint64_t outiers_num = 0;

    // check inliers
    for (const auto& track : feature_tracks)
    {
        const auto lm_id = track.GetLandmark()->Id();

        for (size_t measurement_index = 0; measurement_index < track.Length(); measurement_index++)
        {
            for (size_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
            {
                // convert error threshold from pixel error to unit3 error
                Scalar threshold = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                    camera_parameters_->intrinsics.at(camera_index),
                    parameters_.triangulator_params.max_acceptable_reproject_error);
                if (track.ComputeReprojectionError(values, measurement_index, camera_index) < threshold)
                {
                    continue;
                }
                else if (new_value.exists(L(lm_id)))
                {
                    new_value.erase(L(lm_id));
                    outiers_num++;
                }
            }
        }
    }

    LOG(INFO) << "AvpMapping --- remove outlier done. total outliers num: " << outiers_num << "\n";
    return new_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::TriangulateNewTracks(std::vector<FeatureTrack>& tracks, const Values& values) const
{
    for (auto& track : tracks)
    {
        const FeatureTrack::State track_state = track.GetState();
        if (track_state == FeatureTrack::State::CANDIDATE)
        {
            auto result = triangulator_.Run(track, values);
            if (result)
            {
                track.UpdatingState(FeatureTrack::State::FRESH, HoloGtsam::Convert(*result));
            }
            else
            {
                // transit track state to BAD after triangulation failures
                track.UpdatingState(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Map AvpMapping::ConvertTracksToMap(const std::vector<FeatureTrack>& feature_tracks, const Values& values) const
{
    // create map
    Map map;

    for (const auto& track : feature_tracks)
    {
        const auto landmark = track.GetLandmark();

        if (!landmark)
        {
            continue;
        }
        const auto& lm_id = landmark->Id();

        if (!values.exists(L(lm_id)))
        {
            continue;
        }

        // get position
        const Point3 position = HoloGtsam::Convert(values.at(L(lm_id)).cast<gtsam::Point3>());

        // get reference measurement
        // set the oldest measurement as this mappoint's reference measurement
        FeatureTrack::Measurement reference_measurement;

        for (size_t i = 0; i < track.Length(); i++)
        {
            reference_measurement = track.Measurements(i);

            if (values.exists(X(reference_measurement.first)))
            {
                break;
            }
        }

        // check validity of reference_measurement
        if (reference_measurement.second.empty())
        {
            throw std::runtime_error("AvpMapping --- CreateMapAndPath, reference_measurement is "
                                     "invalid. something must be wrong.\n");
        }

        const auto& reference_frame_id                  = reference_measurement.first;
        const auto& reference_feature_with_camera_index = reference_measurement.second;

        // create a new mappoint
        /// @todo we need to init new mappoint's remember rate and confidence
        MapPoint mp;

        /// @todo(Feng. Li 2020-02-13) in multi-camera vslam system, if a feature track can be tracked by
        /// different camera. then how can we select the direction for the mappoint? since by now we just track
        /// features at the same camera, here we just select the first one, there shouldn't be much problem. if
        /// we enbale tracking feature at different camera, we should come back to fix this issue.
        const auto& camera_index      = reference_feature_with_camera_index.begin()->first;
        const auto& reference_feature = reference_feature_with_camera_index.begin()->second;
        const Pose3 T_wc              = HoloGtsam::Convert(values.at(X(reference_frame_id)).cast<gtsam::Pose3>()) *
                           camera_parameters_->extrinsics.at(camera_index);
        const auto direction = T_wc.GetRotation().Rotate(reference_feature.normalized_point.ToVector());

        // select the best category of this track
        const auto semantic_label = track.GetLabel();

        // assign the category to mappoint which satisfies the conditions
        // we only add the static and vehicle mappoint to map for localization
        if ((semantic_label == SemanticLabel::STATIC || semantic_label == SemanticLabel::VEHICLE))
        {
            mp.semantic_label = semantic_label;
        }

        // compute reprojection errors in whole track of the mappoint
        // and the mean reprojection error of this mappoint
        std::vector<Scalar> measurement_errors;
        for (uint64_t measurement_index = 0; measurement_index < track.Length(); measurement_index++)
        {
            // check if the measurement has data
            if (track.Measurements(measurement_index).second.empty())
            {
                continue;
            }
            boost::optional<Scalar> reprojection_error = track.ComputePiexlReprojectionError(values, measurement_index);
            if (!reprojection_error)
            {
                continue;
            }
            mp.reprojection_errors.emplace_back(*reprojection_error);
            measurement_errors.emplace_back(*reprojection_error);
        }

        mp.mean_reprojection_error =
            std::accumulate(measurement_errors.begin(), measurement_errors.end(), 0.0) / measurement_errors.size();

        mp.reference_pose     = T_wc;
        mp.reference_frame_id = reference_frame_id;
        mp.direction          = direction / direction.GetNorm();
        mp.score              = reference_feature.score;

        mp.position = position;
        /// @todo(Feng. Li) select best descriptor of this track
        mp.descriptor = *(reference_feature.optional_descriptor);
        mp.life_long_states.push_back(MapPointState::MATCHED);
        mp.remember_rate = std::exp(-(1.0 / 19));

        /// @todo compute covariance of this mappoint
        if (mp.position.Dist(mp.reference_pose.GetTranslation()) > 60.0)
        {
            LOG(INFO) << "The optimized map point dis is larger than 60: "
                      << mp.position.Dist(mp.reference_pose.GetTranslation());
            continue;
        }

        map.push_back(std::make_shared<MapPoint>(mp));
    }

    return map;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<FeatureTrack>
AvpMapping::SelectTracksWithTriangulationResult(const std::vector<FeatureTrack>& feature_tracks) const
{
    std::vector<FeatureTrack> new_feature_tracks;
    for (const auto& track : feature_tracks)
    {
        if (track.GetState() == FeatureTrack::State::FRESH)
        {
            new_feature_tracks.push_back(track);
        }
    }
    return new_feature_tracks;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactorGraph AvpMapping::AddVisualFactorGraph(const Values& values, const FactorGraph& old_graph,
                                             const std::vector<FeatureTrack>& feature_tracks) const
{
    LOG(INFO) << "Begin to add visual factor graph...";
    (void)values;
    FactorGraph new_graph = old_graph;

    // loop all tracks to add Unit3Factors
    for (const auto& track : feature_tracks)
    {
        const auto& factors = track.Unit3Factors();

        if (factors.empty())
        {
            continue;
        }
        new_graph.add(factors);
    }
    return new_graph;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values AvpMapping::AddLandmarksToValues(const Values& old_values, const std::vector<FeatureTrack>& feature_tracks)
{
    PointCloudXYZIRRgbSt pcd_msg(1);
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<::holo::float32_t>());
    Values new_values = old_values;

    for (const auto& track : feature_tracks)
    {
        const auto& landmark = track.GetLandmark();

        if (!landmark)
        {
            throw std::runtime_error(
                "AvpMapping --- AddLandmarksToValues. given tracks without landmark. something must be wrong.\n");
        }
        new_values.insert(L(landmark->Id()), landmark->Point());
        pcd_msg[0].Set(HoloGtsam::Convert(landmark->Point()));
        pose_and_trajectory_msg_.insert(pose_and_trajectory_msg_.end(), pcd_msg.begin(), pcd_msg.end());
    }

    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::UpdateTracksWithNewFeatures(std::vector<FeatureTrack>&   old_tracks,
                                             const std::vector<uint64_t>& old_tracks_index,
                                             const vslam::Features& new_features, const uint64_t new_frame_id,
                                             const uint64_t                       camera_index,
                                             const DescriptorMatcher::MatchPairs& match_pairs) const
{
    IndexedFeatures new_tracked_features;
    vslam::Features new_detected_features;

    if (match_pairs.empty())
    {
        // match_pairs is empty, all features will used to create new track
        return;
    }
    else
    {
        // sort original match_pairs.
        // first element in a match_pair is a feature_track's index in the whole sliding window feature tracks, we
        // can use it to retrieve a specific feature track. second element in a match_pair is the new feature's
        // index in input features. we sort the match_pairs in an incremental way according to feature's index, to
        // facilitate classification later.
        DescriptorMatcher::MatchPairs sorted_match_pairs = match_pairs;
        std::sort(sorted_match_pairs.begin(), sorted_match_pairs.end(),
                  [](std::pair<uint64_t, uint64_t> a, std::pair<uint64_t, uint64_t> b) { return a.second < b.second; });

        // mark the first match pair index
        uint64_t match_pair_index      = 0;
        uint64_t old_track_index       = sorted_match_pairs[match_pair_index].first;
        uint64_t matched_feature_index = sorted_match_pairs[match_pair_index].second;

        // loop all input features
        for (uint64_t i = 0; i < new_features.size(); i++)
        {
            // current feature index is equals to matched_feature_index, this means it belongs to an old track, we
            // mark it associated track index.
            if (i == matched_feature_index)
            {
                // belongs to an old track
                new_tracked_features.emplace(old_track_index, new_features.at(i));

                // move match_pair_index to next one if not out of sorted_match_pairs's boundary
                if (match_pair_index < sorted_match_pairs.size() - 1)
                {
                    match_pair_index++;
                    old_track_index       = sorted_match_pairs[match_pair_index].first;
                    matched_feature_index = sorted_match_pairs[match_pair_index].second;
                }
            }
            else
            {
                // belongs to a new track
                new_detected_features.emplace_back(new_features.at(i));
            }
        }

        // update tracks with tracked features, meanwhile mark tracks which can NOT match with new features
        for (size_t i = 0; i < old_tracks_index.size(); i++)
        {
            if (new_tracked_features.count(i))
            {
                auto const& new_feature = new_tracked_features.at(i);
                auto&       old_track   = old_tracks.at(old_tracks_index.at(i));
                old_track.AddNewestMeasurement(new_frame_id, new_feature);
                // LOG(INFO) << "Old track add new measurement:  " << old_track.NewestMeasurement().first;
            }
        }

        // create new tracks
        old_tracks.reserve(old_tracks.size() + new_detected_features.size());

        // create new feature track for each new_features which does NOT matching any old_tracks
        for (size_t i = 0; i < new_detected_features.size(); i++)
        {
            FeatureTrack::CameraIndexedFeature camera_indexed_feature;
            camera_indexed_feature.emplace(camera_index, new_detected_features.at(i));
            old_tracks.emplace_back(
                FeatureTrack::CreateNewTrack(parameters_.track_params, camera_parameters_,
                                             FeatureTrack::Measurement(new_frame_id, camera_indexed_feature)));
        }
        (void)camera_index;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
KeyFramesDatabase AvpMapping::SelectKeyFrames(const FramesDatabase& new_frames_database, const Values& xvb_values) const
{
    KeyFramesDatabase new_keyframes_database;
    //  select key frames
    const auto gridding_frame_ids = map_database_manager_.AssignFramesToVoxelGrid(xvb_values, new_frames_database);
    const auto keyframe_ids =
        map_database_manager_.SelectKeyFrames(xvb_values, new_frames_database, gridding_frame_ids);

    for (auto& keyframe_id : keyframe_ids)
    {
        auto           frame             = new_frames_database.GetFrame(keyframe_id);
        const uint64_t camera_number     = frame.multi_camera_data.size();
        auto&          multi_camera_data = frame.multi_camera_data;
        KeyFrame       keyframe(frame.frame_id, HoloGtsam::Convert(xvb_values.at(X(keyframe_id)).cast<gtsam::Pose3>()),
                                camera_number);

        // process all camera data
        for (uint64_t camera_index = 0; camera_index < camera_number; camera_index++)
        {
            // save camera pose
            const auto T_wc = HoloGtsam::Convert(xvb_values.at(X(keyframe_id)).cast<gtsam::Pose3>()) *
                              frame.camera_parameters->extrinsics.at(camera_index);

            // save features and associated landmark ids
            const auto& features             = multi_camera_data.at(camera_index).features;
            const auto& associated_landmarks = multi_camera_data.at(camera_index).associated_landmarks;

            // select features observed landmark
            Features             selected_features;
            std::vector<Point3>  landmarks;
            std::vector<int64_t> ids;

            for (uint64_t i = 0; i < features.size(); i++)
            {
                const auto& lm_id = associated_landmarks.at(i);
                if (lm_id < 0 || !xvb_values.exists(L(lm_id)))
                {
                    continue;
                }

                selected_features.push_back(features.at(i));
                ids.push_back(lm_id);
                const auto point = HoloGtsam::Convert(xvb_values.at(L(lm_id)).cast<gtsam::Point3>());
                landmarks.push_back(point);
            }

            keyframe.multi_camera_data[camera_index].pose                 = T_wc;
            keyframe.multi_camera_data[camera_index].features             = selected_features;
            keyframe.multi_camera_data[camera_index].associated_landmarks = associated_landmarks;
            keyframe.multi_camera_data[camera_index].mappoints            = landmarks;
        }
        new_keyframes_database.emplace(keyframe.frame_id, keyframe);
    }
    return new_keyframes_database;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat AvpMapping::VisualizeTracks(const cv::Mat& img, const uint64_t frame_id,
                                    const std::vector<FeatureTrack>& tracks) const
{
    cv::Mat new_image = img.clone();
    // draw all features extracted on this image
    for (size_t i = 0; i < tracks.size(); i++)
    {
        if (tracks.at(i).NewestMeasurement().first != frame_id)
        {
            continue;
        }

        // draw track path if any
        if (tracks.at(i).Length() > 1u)
        {
            auto measurements = tracks.at(i).Measurements();
            std::sort(measurements.begin(), measurements.end(),
                      [](const FeatureTrack::Measurement& m0, const FeatureTrack::Measurement& m1) {
                          return m0.first < m1.first;
                      });

            cv::circle(new_image, measurements.back().second.at(0).image_point, 5, cv::Scalar(0, 255, 0));

            for (uint64_t j = 0; j < tracks.at(i).Length() - 1u; j++)
            {
                // LOG(INFO) << "Line: " << measurements.at(j).second.at(0).image_point << "  "
                //           << measurements.at(j + 1).second.at(0).image_point;
                if (measurements.at(j).first >= frame_id)
                {
                    break;
                }

                cv::line(new_image, measurements.at(j).second.at(0).image_point,
                         measurements.at(j + 1).second.at(0).image_point, cv::Scalar(0, 255, 255));  // yellow
            }
        }
    }

    // draw statistics info
    std::stringstream ss;
    ss << "frame_id = " << frame_id;
    cv::putText(new_image, ss.str(), cv::Point2f(10, 30), 1, 1, cv::Scalar(0, 0, 255));  // red

    return new_image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::DrawLine(const Point3& start, const Point3& end)
{
    PointCloudXYZIRRgbSt pcd_msg(200);
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<::holo::float32_t>());
    float64_t start_x = start.GetX();
    float64_t start_y = start.GetY();
    float64_t start_z = start.GetZ();

    float64_t end_x = end.GetX();
    float64_t end_y = end.GetY();
    float64_t end_z = end.GetZ();

    float64_t inc_x = (end_x - start_x) / 200.0f;
    float64_t inc_y = (end_y - start_y) / 200.0f;
    float64_t inc_z = (end_z - start_z) / 200.0f;

    for (float64_t i = 0; i < 200; i += 1)
    {
        float64_t x = start_x + i * inc_x;
        float64_t y = start_y + i * inc_y;
        float64_t z = start_z + i * inc_z;
        // std::cout << "pcd x: " << x << std::endl;
        // std::cout << "pcd y: " << y << std::endl;
        // std::cout << "pcd z: " << z << std::endl;
        pcd_msg[i].Set(x, y, z);
    }
    pose_and_trajectory_msg_.insert(pose_and_trajectory_msg_.end(), pcd_msg.begin(), pcd_msg.end());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::DrawCamera(const Pose3& pose)
{
    Pose3  global_pose(pose.GetRotation(), Point3(pose.GetX(), pose.GetY(), pose.GetZ()));
    Point3 inner_vertex0 = global_pose * Point3(0.2, 0.2, 0);
    Point3 inner_vertex1 = global_pose * Point3(-0.2, 0.2, 0);
    Point3 inner_vertex2 = global_pose * Point3(0.2, -0.2, 0);
    Point3 inner_vertex3 = global_pose * Point3(-0.2, -0.2, 0);

    Point3 outer_vertex0 = global_pose * Point3(0.4, 0.4, 0.2);
    Point3 outer_vertex1 = global_pose * Point3(-0.4, 0.4, 0.2);
    Point3 outer_vertex2 = global_pose * Point3(0.4, -0.4, 0.2);
    Point3 outer_vertex3 = global_pose * Point3(-0.4, -0.4, 0.2);

    DrawLine(inner_vertex0, inner_vertex1);
    DrawLine(inner_vertex0, inner_vertex2);
    DrawLine(inner_vertex1, inner_vertex3);
    DrawLine(inner_vertex2, inner_vertex3);

    DrawLine(outer_vertex0, outer_vertex1);
    DrawLine(outer_vertex0, outer_vertex2);
    DrawLine(outer_vertex1, outer_vertex3);
    DrawLine(outer_vertex2, outer_vertex3);

    DrawLine(inner_vertex0, outer_vertex0);
    DrawLine(inner_vertex1, outer_vertex1);
    DrawLine(inner_vertex2, outer_vertex2);
    DrawLine(inner_vertex3, outer_vertex3);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::DrawTrajectory(const Pose3& pose)
{
    PointCloudXYZIRRgbSt pcd_msg(1);
    pcd_msg.SetTimestamp(holo::Timestamp());
    pcd_msg.SetCoordinate(holo::Coordinate());
    pcd_msg.SetPose(Pose3::Identity().Cast<::holo::float32_t>());
    const auto x = pose.GetTranslation().GetX();
    const auto y = pose.GetTranslation().GetY();
    const auto z = pose.GetTranslation().GetZ();
    pcd_msg[0].Set(x, y, z);

    pose_and_trajectory_msg_.insert(pose_and_trajectory_msg_.end(), pcd_msg.begin(), pcd_msg.end());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AvpMapping::DrawEpipolarLineMatching(const DescriptorMatcher::FeaturesWithObservedPoses& query_data,
                                          const DescriptorMatcher::FeaturesWithObservedPoses& train_data,
                                          const cv::Mat& query_image, const cv::Mat& train_image,
                                          Scalar epipolar_dist_th, Scalar descriptor_dist_th,
                                          Scalar ratio_test_th) const
{
    // cv::namedWindow("epipolar line", 0);
    static uint64_t epipolar_counter = 0;

    std::map<std::pair<Pose3, Pose3>, Matrix3, ComparePose3Pair> pose_pair_to_essential_matrix;
    const uint64_t                                               width       = query_image.cols;
    const uint64_t                                               height      = query_image.rows;
    const uint32_t                                               buffer_size = width * height;
    holo::Image                                                  holo_query_image, holo_train_image;
    holo_query_image.SetData(static_cast<uint8_t*>(query_image.data), buffer_size, width, height,
                             holo::Image::Encoding::GRAYSCALE);

    holo_train_image.SetData(static_cast<uint8_t*>(train_image.data), buffer_size, width, height,
                             holo::Image::Encoding::GRAYSCALE);

    holo::localization::Mat undistorted_query_img, undistorted_train_img;
    undistorters_.at(0)->Undistort(holo::localization::Mat(holo_query_image), undistorted_query_img);
    cv::Mat cv_query_image;
    cv::cvtColor(undistorted_query_img.GetCvType().clone(), cv_query_image, CV_GRAY2BGR);

    undistorters_.at(0)->Undistort(holo::localization::Mat(holo_train_image), undistorted_train_img);
    cv::Mat cv_train_image;
    cv::cvtColor(undistorted_train_img.GetCvType().clone(), cv_train_image, CV_GRAY2BGR);

    // merge two image
    auto image_with_matches = MergeTwoImages(cv_query_image, cv_train_image);

    // draw keypoint
    static const auto  white = cv::Scalar(255, 255, 255);
    static const auto  black = cv::Scalar(0, 0, 0);
    static const auto  blue  = cv::Scalar(255, 0, 0);
    static const auto  red   = cv::Scalar(0, 0, 255);
    static cv::Point2f shift_pt(train_image.cols, 0);

    std::vector<cv::Point2f> train_kpts;
    std::vector<cv::Point2f> query_kpts;

    for (const auto& item : train_data)
    {
        // draw train tracks kpts
        const auto& train_kp = item.first.image_point;
        cv::circle(image_with_matches, train_kp + shift_pt, 6, black, -1, cv::LineTypes::LINE_AA);
        cv::circle(image_with_matches, train_kp + shift_pt, 3, white, -1, cv::LineTypes::LINE_AA);
        train_kpts.push_back(train_kp);
    }

    // cv::imshow("epipolar line", image_with_matches);
    // cv::waitKey(0);
    // return;

    auto image_with_matches_bk = image_with_matches;

    // define temporary match result.(many to one)
    DescriptorMatcher::MatchPairsWithDistance many_to_one_match_result;

    // loop all features in first_data
    for (size_t i = 0; i < query_data.size(); i++)
    {
        const auto  desc_i = query_data.at(i).first.optional_descriptor;
        const auto  pti_i  = query_data.at(i).first.image_point;
        const auto  ptn_i  = query_data.at(i).first.normalized_point;
        const Pose3 Twc_i  = query_data.at(i).second;

        if (!desc_i)
        {
            throw std::runtime_error("AvpMapping --- calling EpipolarLineMatching while input first_data "
                                     "without descriptor.\n");
        }

        // define matching message
        MatchingMessage matching_message(*desc_i, i);

        image_with_matches = image_with_matches_bk.clone();
        // loop all features in second_data
        for (size_t j = 0; j < train_data.size(); j++)
        {
            // get desc_j and nomarlized point j
            const auto  desc_j = train_data.at(j).first.optional_descriptor;
            const auto  pti_j  = train_data.at(j).first.image_point;
            const auto  ptn_j  = train_data.at(j).first.normalized_point;
            const Pose3 Twc_j  = train_data.at(j).second;

            // check valid of descriptor
            if (!desc_j)
            {
                throw std::runtime_error("AvpMapping --- calling EpipolarLineMatching while input second_data "
                                         "without descriptor.\n");
            }

            // calculate F matrix
            Matrix3    fundamental_matrix;
            const auto intrinsic = camera_parameters_->intrinsics.at(0);
            if (intrinsic->GetModel() == Model::PINHOLE)
            {
                PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());
                if (!pinhole)
                {
                    LOG(ERROR) << "AvpMapping --- DrawEpipolarLineMatching, failed to cast source intrinsic to "
                                  "pinhole type";
                    throw std::runtime_error(
                        "AvpMapping --- DrawEpipolarLineMatching, failed to cast source intrinsic to pinhole type");
                }
                fundamental_matrix =
                    pinhole->GetK().Inverse().Transpose() *
                    holo::localization::vision::vslam::Utility::EssentialMatrixFromPoses(Twc_i, Twc_j) *
                    pinhole->GetK().Inverse();
            }
            else if (intrinsic->GetModel() == Model::FISHEYE)
            {
                FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());
                if (!fisheye)
                {
                    LOG(ERROR) << "AvpMapping --- DrawEpipolarLineMatching, failed to cast source intrinsic to "
                                  "fisheye type";
                    throw std::runtime_error(
                        "AvpMapping --- DrawEpipolarLineMatching, failed to cast source intrinsic to fisheye type");
                }
                fundamental_matrix =
                    fisheye->GetK().Inverse().Transpose() *
                    holo::localization::vision::vslam::Utility::EssentialMatrixFromPoses(Twc_i, Twc_j) *
                    fisheye->GetK().Inverse();
            }
            else if (intrinsic->GetModel() == Model::OMNIDIRECTIONAL)
            {
                LOG(ERROR) << "AvpMapping --- DrawEpipolarLineMatching, do not support ocam model !!!";
                return;
            }
            else
            {
                LOG(ERROR) << "AvpMapping --- DrawEpipolarLineMatching, the input source intrinsic is invalid! model: "
                           << (intrinsic ? static_cast<uint16_t>(intrinsic->GetModel()) :
                                           static_cast<uint16_t>(Model::UNKNOWN));
                throw std::runtime_error("AvpMapping --- DrawEpipolarLineMatching, invalid intrinsic");
            }

            const auto  epipolar_line = fundamental_matrix * Point3d(pti_i.x, pti_i.y, 1).ToVector();
            const auto  color         = cv::Scalar(128, 128, 255);
            cv::Point2f line_point_1  = cv::Point2f(0, -epipolar_line(2) / epipolar_line(1));
            cv::Point2f line_point_2  = cv::Point2d(
                 train_image.cols, -(epipolar_line(2) + epipolar_line(0) * train_image.cols) / epipolar_line(1));

            cv::circle(image_with_matches, pti_i, 10, black, -1, cv::LineTypes::LINE_AA);
            cv::circle(image_with_matches, pti_i, 5, white, -1, cv::LineTypes::LINE_AA);
            cv::line(image_with_matches, line_point_1 + shift_pt, line_point_2 + shift_pt, color, 2,
                     cv::LineTypes::LINE_AA);

            // check if can serve as candidate correspondence
            if (Twc_j.Dist(Twc_i) < 1e-3)
            {
                // pure rotation, degenerated case
                // rotate two camera view direction to world frame
                const Vector3 view_direction_i = Twc_i.GetRotation().Rotate(ptn_i.ToVector());
                const Vector3 view_direction_j = Twc_j.GetRotation().Rotate(ptn_j.ToVector());

                // compute angle between view_direction_i and view_direction_j
                const Scalar cos_theta =
                    view_direction_i.Dot(view_direction_j) / (view_direction_i.GetNorm() * view_direction_j.GetNorm());

                // check angle
                const Scalar angle_th = 1.0;  // degree.

                if (cos_theta < std::cos(holo::Radian(angle_th)))
                {
                    continue;
                }
            }
            else
            {
                Vector3 epipolar_line;
                if (!pose_pair_to_essential_matrix.count(std::pair<Pose3, Pose3>{Twc_i, Twc_j}))
                {
                    const std::pair<Pose3, Pose3> pose_pair = std::make_pair(Twc_i, Twc_j);
                    pose_pair_to_essential_matrix[pose_pair] =
                        holo::localization::vision::vslam::Utility::EssentialMatrixFromPoses(Twc_i, Twc_j);
                }
                epipolar_line =
                    pose_pair_to_essential_matrix.at(std::pair<Pose3, Pose3>{Twc_i, Twc_j}) * ptn_i.ToVector();

                // compute distance between ptn_j and epipolar_line
                // l: Ax + By + C = 0; p: (x0, y0); distance = |A * x0 + B * y0 + C| / sqrt(A^2 + B^2);
                const Scalar epipolar_distance =
                    std::fabs(ptn_j.ToVector().Dot(epipolar_line)) / epipolar_line.GetBlock(0, 0, 2, 1).GetNorm();

                // reject if epipolar_distance large than threshold
                if (epipolar_distance > epipolar_dist_th)
                {
                    continue;
                }
            }

            // update matching message
            matching_message = matching_message.UpdateMessage(matching_message, *desc_j, j);
            cv::circle(image_with_matches, pti_j + shift_pt, 10, blue, -1, cv::LineTypes::LINE_AA);
            cv::circle(image_with_matches, pti_j + shift_pt, 5, white, -1, cv::LineTypes::LINE_AA);
        }

        // check if acceptable
        if (matching_message.IsMatchingAcceptable(descriptor_dist_th, ratio_test_th))
        {
            cv::circle(image_with_matches,
                       train_data.at(matching_message.best_query_index).first.image_point + shift_pt, 10, red, -1,
                       cv::LineTypes::LINE_AA);
            cv::imwrite(holo::GetHoloConfigRootDirectory() + "/epipolar_result/" + std::to_string(epipolar_counter) +
                            ".png",
                        image_with_matches);
            epipolar_counter++;
            // cv::imshow("epipolar line", image_with_matches);
            // cv::waitKey(0);
            many_to_one_match_result.emplace(
                matching_message.train_index,
                std::make_pair(matching_message.best_query_index, matching_message.minimum_distance));
        }
        else
        {
            // cv::imshow("epipolar line", image_with_matches);
            // cv::waitKey(0);

            cv::imwrite(holo::GetHoloConfigRootDirectory() + "/epipolar_result/" + std::to_string(epipolar_counter) +
                            ".png",
                        image_with_matches);
            epipolar_counter++;
        }
    }

    return;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
