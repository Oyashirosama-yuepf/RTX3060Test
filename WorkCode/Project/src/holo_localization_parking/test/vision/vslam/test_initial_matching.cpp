/*!
 * \brief unit test for initial matching when localization
 * \author guopeikai@holomatic.com
 * \date Aug-30-2021
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <random>

#include <gtest/gtest.h>

#define protected public
#include <holo/localization/vision/vslam/mapping/map_database_manager.h>
#include <holo/localization/vision/vslam/localization/relocalization.h>
#include <holo/localization/vision/common/holo_gtsam.h>

using namespace holo::localization::vision::vslam;
std::string                                       raw_data_path = "";
std::string                                       test_scence   = "";
CameraParameters::Ptr                             camera_parameters_, avp_camera_parameters_;
holo::common::details::PinholeIntrinsicT<Scalar>  avp_intrinsic;
ImageUndistortionPtr                              init_camera_undistorter_;
std::vector<ImageUndistortionPtr>                 undistorters_;
std::vector<ImageUndistortionPtr>                 avp_undistorters_;
std::vector<std::pair<holo::Timestamp, uint64_t>> timestamp_frame_id_;
std::map<holo::Timestamp, uint64_t>               timestamp_to_frame_id;
std::map<uint64_t, holo::Timestamp>               frame_id_to_timestamp;
std::map<uint64_t, std::string>                   frame_id_to_image_name;
const auto                                        parameters_ = Relocalization::Parameters::Example();

struct FrameToFrameCheckingResult
{
    /// @brief train frame id and camera index
    std::pair<uint64_t, uint16_t> train_frame_id_and_camera_index;

    /// @brief matched index pairs
    DescriptorMatcher::MatchPairs matche_pairs;

    /// @brief inlier index pairs
    /// @details if solving failed, the inliers is empty. so one should checking the inliers first before use the
    /// solved T_wc.
    std::vector<std::pair<uint16_t, uint16_t>> inliers;

    /// @brief solved camera pose in world frame
    Pose3 T_wc;

    /**
     * @brief Constructor
     */
    FrameToFrameCheckingResult(const std::pair<uint64_t, uint16_t>               _train_frame_id_and_camera_index = {},
                               const DescriptorMatcher::MatchPairs&              _matche_pairs                    = {},
                               const std::vector<std::pair<uint16_t, uint16_t>>& _inliers                         = {},
                               const Pose3&                                      _T_wc = Pose3::Identity())
      : train_frame_id_and_camera_index(_train_frame_id_and_camera_index)
      , matche_pairs(_matche_pairs)
      , inliers(_inliers)
      , T_wc(_T_wc)
    {
    }
};

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
template <typename intrinsicT>
ImageUndistortionPtr CreateImageUndistorter(const intrinsicT& intrinsic)
{
    using Model = holo::common::details::CameraIntrinsicBase::Model;

    if (intrinsic.GetModel() != Model::FISHEYE && intrinsic.GetModel() != Model::PINHOLE)
    {
        return nullptr;
    }

    /// @todo(Feng. Li 2020-01-13) use ImageUndistortion with new Intrinsic which defined in holo::common::details
    // convert to old Intrinsic
    using OldIntrinicType = holo::IntrinsicT<Scalar>;
    using OldCameraModel  = holo::CameraModel;

    OldCameraModel           model;
    OldIntrinicType::Vector8 distortion_params;
    const auto&              d = intrinsic.GetD();

    if (intrinsic.GetModel() == Model::FISHEYE)
    {
        model             = OldCameraModel::FISHEYE;
        distortion_params = {d[0], d[1], 0.0, 0.0, d[2], d[3], 0.0, 0.0};
    }
    else
    {
        model             = OldCameraModel::PINHOLE;
        distortion_params = {d[0], d[1], d[2], d[3], d[4], 0.0, 0.0, 0.0};
    }

    OldIntrinicType old_intrinsic(holo::common::Coordinate(intrinsic.GetSensorId()), model,
                                  Vector2(intrinsic.GetWidth(), intrinsic.GetHeight()), intrinsic.GetK(),
                                  distortion_params);
    return std::make_shared<ImageUndistortion>(old_intrinsic);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawMacthedInfo(const KeyFramesDatabase& train_frames, const Features& query_features, const cv::Mat& query_image,
                     const std::vector<FrameToFrameCheckingResult>& associated_results,
                     const std::vector<ImageUndistortionPtr>&       train_image_undistorters)
{
    if (query_image.empty() || associated_results.empty())
    {
        return;
    }

    static const std::string image_dir          = "/opt/holo/hpp/route_1/" + raw_data_path + "/images/";
    const auto&              best_result        = associated_results.front();
    const auto&              train_frame_id     = best_result.train_frame_id_and_camera_index.first;
    const auto&              train_camera_index = best_result.train_frame_id_and_camera_index.second;

    std::string train_image_name = "";
    if (test_scence == "avp")
    {
        train_image_name = "/opt/holo/hpp/heduo/Camera0/" + frame_id_to_image_name.at(train_frame_id) + ".jpg";
    }
    else
    {
        train_image_name = image_dir + std::to_string(frame_id_to_timestamp.at(train_frame_id).ToNsec()) + ".png";
    }

    // check if train frame is exist in disk
    if (!boost::filesystem::exists(train_image_name))
    {
        LOG(INFO) << "DrawMacthedInfo --- image does nor exist: " << train_image_name << "\n";
        return;
    }

    // read train image from disk
    cv::Mat ori_train_image = cv::imread(train_image_name, cv::IMREAD_COLOR);

    const uint16_t width       = ori_train_image.cols;
    const uint16_t height      = ori_train_image.rows;
    const uint32_t buffer_size = width * height * 3;
    holo::Image    image;
    image.SetData(static_cast<uint8_t*>(ori_train_image.data), buffer_size, width, height, holo::Image::Encoding::BGR);

    holo::localization::Mat undistorted_img;
    train_image_undistorters.at(0)->Undistort(holo::localization::Mat(image), undistorted_img);
    cv::Mat train_image = undistorted_img.GetCvType().clone();
    // cv::imshow("reloc_img", train_image);
    // cv::waitKey(0);

    // draw keypoint
    static const auto white = cv::Scalar(255, 255, 255);
    static const auto black = cv::Scalar(0, 0, 0);

    std::vector<cv::Point2f> train_kpts;

    for (const auto& ft : train_frames.at(train_frame_id).multi_camera_data.at(train_camera_index).features)
    {
        const auto& kp = ft.image_point;
        cv::circle(train_image, kp, 6, black, -1, cv::LineTypes::LINE_AA);
        cv::circle(train_image, kp, 3, white, -1, cv::LineTypes::LINE_AA);
        train_kpts.push_back(kp);
    }

    cv::Mat query_image_bgr;
    cv::cvtColor(query_image, query_image_bgr, CV_GRAY2BGR);
    std::vector<cv::Point2f> query_kpts;

    for (const auto& ft : query_features)
    {
        const auto& kp = ft.image_point;
        cv::circle(query_image_bgr, kp, 6, black, -1, cv::LineTypes::LINE_AA);
        cv::circle(query_image_bgr, kp, 3, white, -1, cv::LineTypes::LINE_AA);
        query_kpts.push_back(kp);
    }

    // merge two image
    const auto image_with_matches = MergeTwoImages(train_image, query_image_bgr);

    // draw matches
    const auto&        matche_pairs = best_result.matche_pairs;
    static cv::Point2f shift_pt(train_image.cols, 0);

    // for (const auto& pair : matche_pairs)
    // {
    //     const auto& train_index = pair.first;
    //     const auto& query_index = pair.second;
    //     const auto& confidence  = pair.second;

    //     const auto& train_pt = train_kpts.at(train_index);
    //     const auto& query_pt = query_kpts.at(query_index);
    //     const auto  color    = cv::Scalar(128, 128, confidence * 255);
    //      cv::line(image_with_matches, train_pt, query_pt + shift_pt, color, 2, cv::LineTypes::LINE_AA);
    // }

    // mark inliers
    const auto& inliers = best_result.inliers;

    for (const auto& pair : inliers)
    {
        const auto& train_index = pair.first;
        const auto& query_index = pair.second;

        const auto& train_pt = train_kpts.at(train_index);
        const auto& query_pt = query_kpts.at(query_index) + shift_pt;
        cv::circle(image_with_matches, train_pt, 8, cv::Scalar(0, 255, 0), -1, cv::LineTypes::LINE_AA);
        cv::circle(image_with_matches, query_pt, 8, cv::Scalar(0, 255, 0), -1, cv::LineTypes::LINE_AA);
        const auto& confidence = pair.second;
        const auto  color      = cv::Scalar(128, 128, confidence * 255);
        cv::line(image_with_matches, train_pt, query_pt, color, 2, cv::LineTypes::LINE_AA);
    }

    std::stringstream ss;
    ss << "train features num: " << train_kpts.size() << ", query features num: " << query_kpts.size()
       << ", matched num: " << matche_pairs.size() << ", inliers num: " << inliers.size();

    cv::putText(image_with_matches, ss.str(), cv::Point2f(10, 950), cv::FONT_HERSHEY_DUPLEX, 1.5,
                cv::Scalar(0, 0, 255));

    cv::namedWindow("matches", 0);
    cv::imshow("matches", image_with_matches);
    cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<uint64_t> QueryCandidateFramesByPose(const KeyFramesDatabase& train_frames, const Pose3& prior_pose,
                                                 const Scalar dist_threshold, const Scalar angle_threshold)
{
    // get candiate frames
    std::vector<std::pair<uint64_t, Scalar>> candidate_frames_index;
    for (const auto& frame : train_frames)
    {
        const auto delta_T     = prior_pose.Inverse() * frame.second.pose;
        const auto delta_dist  = delta_T.GetTranslation().ToVector().GetNorm();
        const auto delta_angle = delta_T.GetRotation().ComputeAngle();
        if (delta_dist > dist_threshold || delta_angle > angle_threshold)
        {
            continue;
        }

        candidate_frames_index.push_back(std::make_pair(frame.first, delta_dist));
    }

    // sort by distance
    std::sort(candidate_frames_index.begin(), candidate_frames_index.end(),
              [](const std::pair<uint16_t, Scalar>& c0, const std::pair<uint16_t, Scalar>& c1) {
                  return c0.second < c1.second;
              });

    std::vector<uint64_t> result;
    result.reserve(candidate_frames_index.size());

    for (const auto& indexed_score : candidate_frames_index)
    {
        result.emplace_back(indexed_score.first);
        if (result.size() > parameters_.maximum_keyframe_num)
        {
            break;
        }
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<Pose3, std::vector<uint16_t>> RansacPnpRun(const std::vector<cv::Point3d>& point3d,
                                                     const std::vector<cv::Point2d>& point2d, const cv::Mat& K)
{
    // check minimum correspondence
    if (point3d.size() < parameters_.ransac_pnp_params.minimum_correspondence)
    {
        LOG(ERROR) << "RansacPnpRun --- correspondence for solve pnp is few. correspondence num: " << point3d.size()
                   << "\n";
        return {};
    }

    cv::Mat               R, r, t;
    std::vector<uint16_t> inliers;

    if (!cv::solvePnPRansac(point3d, point2d, K, cv::Mat(), r, t, false, parameters_.ransac_pnp_params.iteration,
                            parameters_.ransac_pnp_params.projection_threshold,
                            parameters_.ransac_pnp_params.confidence, inliers, cv::SOLVEPNP_EPNP))
    {
        LOG(ERROR) << "RansacPnpRun --- Solve pnp failed.\n";
        return {};
    }

    // check inliers num
    if (inliers.size() < parameters_.ransac_pnp_params.minimum_inliers)
    {
        LOG(ERROR) << "RansacPnpRun --- inliers after solve pnp is few. inliers num: " << inliers.size()
                   << ", correspondence num" << point3d.size() << "\n";
        return {};
    }

    cv::Rodrigues(r, R);
    gtsam::Matrix3 rotation;
    cv::cv2eigen(R, rotation);
    const Pose3 T_cw(Rot3(holo::localization::HoloGtsam::Convert(rotation)),
                     Point3(t.at<double>(0), t.at<double>(1), t.at<double>(2)));
    const Pose3 T_wc = T_cw.Inverse();

    return std::make_pair(T_wc, inliers);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FrameToFrameCheckingResult GeometricConsistencyChecking(const KeyFrame& train_frame, const uint16_t train_camera_index,
                                                        const Features& query_features, const Pose3& prior_Twc)
{
    const auto& single_camera_data = train_frame.multi_camera_data.at(train_camera_index);

    // check the view direction between train camera and query camera
    static const Scalar kAngleThreshold = 30.0;  // degree
    if ((single_camera_data.pose.Inverse() * prior_Twc).GetRotation().ComputeAngle() > kAngleThreshold)
    {
        LOG(INFO) << "The angle between train frame and prior pose is larger: "
                  << (single_camera_data.pose.Inverse() * prior_Twc).GetRotation().ComputeAngle();
        LOG(INFO) << "Train camera pose: " << single_camera_data.pose.GetRotation().RPY()
                  << "\n  prior pose: " << prior_Twc.GetRotation().RPY();
        return FrameToFrameCheckingResult();
    }

    const Scalar minimum_feature_num = 20;
    if (single_camera_data.features.size() < minimum_feature_num || query_features.size() < minimum_feature_num)
    {
        LOG(INFO) << "The train frame's feature is less: " << single_camera_data.features.size();
        return FrameToFrameCheckingResult();
    }

    // feature matching
    std::vector<cv::Mat> last_descriptors;
    last_descriptors.reserve(single_camera_data.features.size());
    for (const auto& feature : single_camera_data.features)
    {
        last_descriptors.emplace_back(*feature.optional_descriptor);
    }

    std::vector<cv::Mat> curr_descriptors;
    curr_descriptors.reserve(query_features.size());
    for (const auto& feature : query_features)
    {
        curr_descriptors.emplace_back(*feature.optional_descriptor);
    }

    // match old features with brute force matching
    const Scalar dist_th       = 1.5;
    const Scalar ratio_test_th = 1.0;

    const auto match_pairs =
        DescriptorMatcher::BruteForceMatching(last_descriptors, curr_descriptors, dist_th, ratio_test_th);

    // solve pnp
    if (match_pairs.size() < parameters_.ransac_pnp_params.minimum_correspondence)
    {
        LOG(ERROR) << "GeometricConsistencyChecking --- matched feature is too few. matched feature num: "
                   << match_pairs.size() << "\n";
        return FrameToFrameCheckingResult();
    }

    // retrieve 3d-2d correspondence for pnp solver
    std::vector<cv::Point3d> pts3;
    pts3.reserve(match_pairs.size());
    std::vector<cv::Point2d> pts2;
    pts2.reserve(match_pairs.size());

    // retrieve 3d-2dcorrespondences
    std::vector<std::pair<uint16_t, uint16_t>> matched_indexes;
    matched_indexes.reserve(match_pairs.size());

    for (const auto& pair : match_pairs)
    {
        const auto& position = single_camera_data.mappoints.at(pair.first);
        pts3.emplace_back(position.GetX(), position.GetY(), position.GetZ());

        const auto kpt = query_features.at(pair.second).normalized_point;
        pts2.emplace_back(kpt.GetX() / kpt.GetZ(), kpt.GetY() / kpt.GetZ());

        matched_indexes.push_back(std::make_pair(pair.first, pair.second));
    }

    // ransac PnP solver
    const Matrix3 K = Matrix3::Identity();
    cv::Mat       cv_K;
    cv::eigen2cv(holo::localization::HoloGtsam::Convert(K), cv_K);
    const auto  rasanc_pnp_result = RansacPnpRun(pts3, pts2, cv_K);
    const auto& T_wc              = rasanc_pnp_result.first;
    const auto& inliers           = rasanc_pnp_result.second;

    LOG(INFO) << ", train features: " << single_camera_data.features.size()
              << ", query features : " << query_features.size() << ", match_pairs: " << match_pairs.size()
              << ", inliers: " << inliers.size() << "\n";

    if (inliers.size() < parameters_.ransac_pnp_params.minimum_inliers)
    {
        return FrameToFrameCheckingResult();
    }

    std::vector<std::pair<uint16_t, uint16_t>> inliers_pair;
    inliers_pair.reserve(inliers.size());

    for (const auto& index : inliers)
    {
        inliers_pair.emplace_back(matched_indexes.at(index));
    }
    // std::vector<std::pair<uint16_t, uint16_t>> inliers_pair = match_pairs;
    return FrameToFrameCheckingResult(std::make_pair(train_frame.frame_id, train_camera_index), match_pairs,
                                      inliers_pair, T_wc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<FrameToFrameCheckingResult> SolvePoseByFrameToFrameMatching(
    const KeyFramesDatabase& train_frames, const Features& query_features, const Pose3& prior_vehicle_pose,
    const cv::Mat& query_image, const CameraParameters::Ptr& camera_parameters,
    const std::vector<ImageUndistortionPtr>& train_image_undistorters)
{
    // check input features
    if (query_features.empty())
    {
        return {};
    }

    // get intrinsic and extrinsic
    const auto& query_camera_index = query_features.front().camera_id;
    const auto& T_bc               = camera_parameters->extrinsics.at(query_camera_index);
    const Pose3 prior_camera_pose  = prior_vehicle_pose * T_bc;
    LOG(INFO) << "Prior vehicle pose: " << prior_vehicle_pose.GetRotation().RPY();
    LOG(INFO) << "Tbc: " << T_bc.GetRotation().RPY();

    // check valid of input frames
    if (train_frames.empty())
    {
        LOG(ERROR) << "SolvePoseByFrameToFrameMatching --- No keyframes.\n";
        return {};
    }

    // get candiate frames
    const auto candidate_frames_ids = QueryCandidateFramesByPose(
        train_frames, prior_vehicle_pose, parameters_.distance_threshold, parameters_.angle_threshold);
    LOG(INFO) << "SolvePoseByFrameToFrameMatching --- candidate_frames: " << candidate_frames_ids.size() << "\n";

    // match candidate frames one by one
    std::vector<FrameToFrameCheckingResult> associated_results;

    for (const auto& train_frame_id : candidate_frames_ids)
    {
        const auto& train_frame = train_frames.at(train_frame_id);
        LOG(INFO) << "Train frame id : " << train_frame_id;

        for (uint16_t camera_index = 0; camera_index < train_frame.multi_camera_data.size(); camera_index++)
        {
            const auto result =
                GeometricConsistencyChecking(train_frame, camera_index, query_features, prior_camera_pose);

            if (result.inliers.empty())
            {
                continue;
            }

            associated_results.emplace_back(result);
        }
    }

    if (associated_results.empty())
    {
        return {};
    }

    // sort result by each element's inliers number
    std::sort(associated_results.begin(), associated_results.end(),
              [](const FrameToFrameCheckingResult& result1, const FrameToFrameCheckingResult& result2) {
                  return result1.inliers.size() > result2.inliers.size();
              });

    // visualize matches
    DrawMacthedInfo(train_frames, query_features, query_image, associated_results, train_image_undistorters);
    return associated_results;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::pair<holo::Timestamp, Features>>
ConvertPointFeatures(const std::vector<PointFeaturePtrList>& multi_point_feature_list)
{
    std::vector<std::pair<holo::Timestamp, Features>> ret;
    ret.reserve(multi_point_feature_list.size());

    for (uint64_t index = 0; index < multi_point_feature_list.size(); index++)
    {
        const auto& all_point_features = multi_point_feature_list.at(index).GetPointFeatureList();
        const auto  camera_id          = camera_parameters_->sensor_id_to_camera_index_map_.at(
            static_cast<uint32_t>(multi_point_feature_list.at(index).GetSensorId()));
        Features features;
        features.reserve(all_point_features.size());

        for (const auto& point_feature : all_point_features)
        {
            Feature ft;
            ft.camera_id = camera_id;

            Point2 undistorted_point = point_feature->GetPointPosition().Cast<Scalar>();

            if (!undistorters_.at(camera_id))
            {
                LOG(ERROR) << "ConvertPointFeatures --- undistorter for camera " << camera_id << " is null!";
            }
            else
            {
                // TODO: add `UndistortPoint` interface
                std::vector<Point2> distorted_points = {undistorted_point.Cast<Scalar>()}, undistorted_points;
                undistorters_.at(camera_id)->UndistortPoints(distorted_points, undistorted_points);
                undistorted_point = undistorted_points.front();
            }

            ft.image_point = cv::Point2f(undistorted_point.GetX(), undistorted_point.GetY());
            camera_parameters_->intrinsics.at(camera_id).Unproject(undistorted_point, ft.normalized_point);
            ft.score = point_feature->GetConfidence();

            // convert descriptor
            cv::Mat desc_mat(cv::Size(point_feature->GetDescriptorDimension(), 1), CV_32FC1);

            for (size_t i = 0; i < point_feature->GetDescriptorDimension(); i++)
            {
                desc_mat.at<float_t>(0, i) = point_feature->GetDescriptor().at(i);
            }

            ft.optional_descriptor = desc_mat;

            features.emplace_back(ft);
        }
        ret.emplace_back(std::make_pair(multi_point_feature_list.at(index).GetTimestamp(), features));
    }
    return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Features ConvertLocStartImagePointFeatures(
    const holo::parking::vision::PointFeaturePtrListf::PointFeaturePtrListType& avp_point_feature_list)
{
    LOG(INFO) << "Convert localization init point features ..." << avp_point_feature_list.size();
    const auto& all_point_features = avp_point_feature_list;
    const auto  camera_id          = 0;
    Features    features;
    features.reserve(all_point_features.size());

    for (const auto& point_feature : all_point_features)
    {
        Feature ft;
        ft.camera_id = camera_id;

        Point2 undistorted_point = point_feature->GetPointPosition().Cast<Scalar>();

        if (!init_camera_undistorter_)
        {
            LOG(ERROR) << "ConvertPointFeatures --- undistorter for camera is null!";
        }
        else
        {
            // TODO: add `UndistortPoint` interface
            std::vector<Point2> distorted_points = {undistorted_point.Cast<Scalar>()}, undistorted_points;
            init_camera_undistorter_->UndistortPoints(distorted_points, undistorted_points);
            undistorted_point = undistorted_points.front();
        }

        ft.image_point = cv::Point2f(undistorted_point.GetX(), undistorted_point.GetY());
        avp_camera_parameters_->intrinsics.at(camera_id).Unproject(undistorted_point, ft.normalized_point);
        ft.score = point_feature->GetConfidence();

        // convert descriptor
        cv::Mat desc_mat(cv::Size(point_feature->GetDescriptorDimension(), 1), CV_32FC1);

        for (size_t i = 0; i < point_feature->GetDescriptorDimension(); i++)
        {
            desc_mat.at<float_t>(0, i) = point_feature->GetDescriptor().at(i);
        }

        ft.optional_descriptor = desc_mat;

        features.emplace_back(ft);
    }
    return features;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<PointFeaturePtrList> LoadFeatures(const std::string& input_data_dir)
{
    std::vector<PointFeaturePtrList> feature_ptr_lists_;
    std::string const                features_txt_name = input_data_dir + "/features.txt";
    std::ifstream                    features_txt(features_txt_name, std::fstream::in);
    LOG(INFO) << "LoadFeatures --- trying to load features from " << features_txt_name << "\n";

    if (features_txt.is_open())
    {
        std::string featues_base_name;
        while (getline(features_txt, featues_base_name))
        {
            std::string const features_bin_name = input_data_dir + "/features/" + featues_base_name + ".bin";
            std::ifstream     features_bin(features_bin_name);
            if (!features_bin)
            {
                LOG(ERROR) << "LoadFeatures --- PlayFeatures, could not open " << features_bin_name;
                throw std::runtime_error("LoadFeatures --- failed to play features.");
            }

            // timestamp
            uint64_t timestamp_nsec = 0;
            features_bin.read((char*)&timestamp_nsec, sizeof(uint64_t));

            // sensor id
            uint32_t sensor_id = 0;
            features_bin.read((char*)&sensor_id, sizeof(uint32_t));

            /// features number
            uint16_t features_num;
            features_bin.read((char*)&features_num, sizeof(uint16_t));

            std::vector<std::shared_ptr<PointFeature>> point_features(features_num);

            /// descriptor dimension
            uint16_t descriptor_dimension;
            features_bin.read((char*)&descriptor_dimension, sizeof(uint16_t));

            std::cout << "features info: " << timestamp_nsec << " " << sensor_id << " " << features_num << " "
                      << descriptor_dimension << "\n";

            // read each features info
            for (uint16_t i = 0; i < features_num; ++i)
            {
                /// read image point
                holo::float32_t pt_x;
                holo::float32_t pt_y;
                features_bin.read((char*)&pt_x, sizeof(holo::float32_t));
                features_bin.read((char*)&pt_y, sizeof(holo::float32_t));

                /// read descriptor
                std::vector<holo::float32_t> descriptor(descriptor_dimension);
                for (uint16_t j = 0; j < descriptor_dimension; ++j)
                {
                    features_bin.read((char*)&descriptor.at(j), sizeof(float));
                }
                /// read confidence
                holo::float32_t confidence;
                features_bin.read((char*)&confidence, sizeof(float));

                point_features.at(i) =
                    std::make_shared<PointFeature>(holo::Point2f(pt_x, pt_y), descriptor, confidence);
            }
            PointFeaturePtrList current_feature_ptr_list(holo::Timestamp(timestamp_nsec),
                                                         holo::common::SensorId(sensor_id), point_features);
            feature_ptr_lists_.emplace_back(current_feature_ptr_list);
        }
    }

    LOG(INFO) << "LoadFeatures --- load features done. features data num: " << feature_ptr_lists_.size() << "\n";
    return feature_ptr_lists_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::parking::vision::PointFeaturePtrListf::PointFeaturePtrListType LoadAvpFeatures(std::string file_name)
{
    std::ofstream point_feature_txt(holo::GetHoloConfigRootDirectory() + "/feature.txt");
    std::vector<holo::parking::vision::PointFeaturePtrListf::PointFeaturePtrListType> rets;
    std::cout << "MapDatabaseManager --- trying to load frames from: " << file_name << "\n";
    std::ifstream fin(file_name);

    if (!fin)
    {
        std::cout << "MapDatabaseManager --- LoadKeyFramesDatabase: could not open " << file_name << "\n";
        return {};
    }

    uint16_t camera_num;
    fin.read((char*)&camera_num, sizeof(uint16_t));
    std::cout << "camera num: " << camera_num << "\n";

    std::vector<uint16_t> single_camera_features;
    for (size_t i = 0; i < camera_num; i++)
    {
        uint16_t feature_num;
        fin.read((char*)&feature_num, sizeof(uint16_t));
        single_camera_features.push_back(feature_num);
        std::cout << "features num: " << feature_num << "\n";
    }

    uint16_t des_dim;
    fin.read((char*)&des_dim, sizeof(int16_t));
    std::cout << "des dim: " << des_dim << "\n";

    rets.resize(camera_num);

    for (size_t i = 0; i < camera_num; i++)
    {
        holo::parking::vision::PointFeaturePtrListf::PointFeaturePtrListType ret;
        ret.resize(single_camera_features.at(i));
        for (size_t j = 0; j < single_camera_features.at(i); j++)
        {
            Scalar pt_x, pt_y;
            fin.read((char*)&pt_x, sizeof(Scalar));
            fin.read((char*)&pt_y, sizeof(Scalar));
            point_feature_txt << "\n" << pt_x << " " << pt_y << "\n";

            holo::parking::vision::PointFeaturef::DescriptorType descriptors;
            descriptors.resize(des_dim);

            for (uint16_t k = 0; k < des_dim; k++)
            {
                fin.read((char*)&descriptors.at(k), sizeof(holo::float32_t));
                point_feature_txt << descriptors.at(k) << " ";
            }
            point_feature_txt << "\n";

            Scalar score;
            fin.read((char*)&score, sizeof(Scalar));
            point_feature_txt << score << "\n";

            holo::parking::vision::PointFeaturef::Point2Type point(pt_x, pt_y);
            holo::parking::vision::PointFeaturef             input_point_feature(point, descriptors, score);
            ret[j] = std::make_shared<holo::parking::vision::PointFeaturef>(input_point_feature);
        }
        rets[i] = ret;
    }
    std::cout << "point feature list size: " << rets.front().size();
    return rets.front();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::pair<holo::Timestamp, uint64_t>> LoadTimeStampAndFrameId(const std::string& file_name)
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "LoadTimeStampAndFrameId --- timestamp file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "LoadTimeStampAndFrameId --- trying to load timestamp and frame id from " << file_name << "\n";
    std::ifstream                                     ifs(file_name, std::fstream::in);
    std::vector<std::pair<holo::Timestamp, uint64_t>> result;

    // read imus
    while (ifs.good())
    {
        uint64_t timestamp = 0, frame_id = 0;
        ifs >> timestamp >> frame_id;

        if (ifs.fail())
        {
            break;
        }

        result.push_back(std::make_pair(holo::Timestamp(timestamp), frame_id));
    }

    LOG(INFO) << "LoadTimeStampAndFrameId --- load timestamp and frame id done. total frame num: " << result.size()
              << "\n";

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadAvpImageInfo(const std::string& file_name)
{
    if (!boost::filesystem::exists(file_name))
    {
        LOG(ERROR) << "AvpMapping --- avp map file: " << file_name << " does not exist ";
        throw std::runtime_error("No such file or directory!\n");
    }

    LOG(INFO) << "AvpMapping --- trying to load mp from " << file_name << "\n";
    std::ifstream ifs(file_name, std::fstream::in);

    // read avp image name
    while (ifs.good())
    {
        uint64_t    frame_id = 0, data = 0;
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
        frame_id_to_image_name[frame_id] = image_name;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    std::cout << "raw map data path is : " << argv[1] << std::endl;
    raw_data_path = argv[1];
    test_scence   = argv[2];  // avp or hpa
    if (test_scence != "avp" || test_scence != "hpa")
    {
        std::cout << "The test scence is not support: " << test_scence << "\n";
    }
    const std::string              map_data_dir = "/opt/holo/hpp/";
    const std::vector<std::string> map_names    = {"route_1"};
    const std::string              mode         = "localization";
    const bool                     save_image   = false;

    holo::common::details::FisheyeIntrinsicT<Scalar> init_camera_intrinsic =
        YAML::LoadFile("/opt/holo/hpp/heduo/camera_0.yaml").as<holo::common::details::FisheyeIntrinsicT<Scalar>>();
    init_camera_undistorter_ = CreateImageUndistorter(init_camera_intrinsic);
    MapDatabaseManager mdm(MapDatabaseManager::Parameters(map_data_dir, map_names, mode, save_image));
    if (test_scence == "avp")
    {
        // load avp parameters for load avp camera params
        LOG(INFO) << "Main --- loading parameters...\n";
        holo::yaml::Node node = holo::yaml::LoadFile(holo::GetHoloConfigRootDirectory() +
                                                     "/holo_localization_parking/lib_config/app/avp_mapping.yaml");

        // camera parameters
        const holo::yaml::Node camera_node = node["vslam_camera_params"].as<holo::yaml::Node>(holo::yaml::Node());
        if (camera_node.IsNull())
        {
            std::cout << "the avp camera node is null !!!" << std::endl;
        }
        avp_camera_parameters_                   = CameraParameters::LoadFromYaml(camera_node);
        const auto Tic                           = avp_camera_parameters_->extrinsics.at(0);
        avp_camera_parameters_->extrinsics.at(0) = Pose3(Rot3::RzRyRx(M_PI, 0.0, M_PI / 2.0), Point3(0, 0, 0)) * Tic;
        LOG(INFO) << "vslam camera params: " << avp_camera_parameters_;

        // load avp camera intrinsic which is used to mapping
        avp_undistorters_ = Utility::CreateImageUndistorters(avp_camera_parameters_->intrinsics);

        // when test avp, load avp image info
        LoadAvpImageInfo("/opt/holo/hpp/heduo/imgpost_part.txt");

        // the picture for testing localization initialization
        std::string image_path = "/opt/holo/hpp/heduo/image0__0000013691_1920x1080.jpg";

        // the feature is from init localiztion camera, so should use init camera undistorter
        const auto features =
            ConvertLocStartImagePointFeatures(LoadAvpFeatures("/opt/holo/hpp/heduo/frame_1_x86_int16_old.bin"));

        if (boost::filesystem::exists(image_path))
        {
            std::cout << image_path << std::endl;
            const auto     query_img   = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
            const uint16_t width       = query_img.cols;
            const uint16_t height      = query_img.rows;
            const uint32_t buffer_size = width * height;
            holo::Image    image;
            image.SetData(static_cast<uint8_t*>(query_img.data), buffer_size, width, height,
                          holo::Image::Encoding::GRAYSCALE);

            holo::localization::Mat undistorted_img;
            init_camera_undistorter_->Undistort(holo::localization::Mat(image), undistorted_img);
            // cv::imshow("ori_img", query_img);
            // cv::imshow("undistorted_img", undistorted_img.GetCvType());
            // cv::waitKey(0);

            cv::Mat vis_image;
            cv::cvtColor(undistorted_img.GetCvType(), vis_image, CV_GRAY2RGB);

            // visilize super point extract result in original image
            for (size_t i = 0; i < features.size(); i++)
            {
                const cv::Point2f& keypoint = features.at(i).image_point;
                cv::circle(vis_image, cv::Point(keypoint.x, keypoint.y), 5, cv::Scalar(0, 255, 0));
            }
            cv::imshow("load feature visual", vis_image);
            cv::waitKey(0);

            SolvePoseByFrameToFrameMatching(mdm.GetKeyframes(), features, mdm.GetLearnedPath().at(0).GetPose(),
                                            undistorted_img.GetCvType(), avp_camera_parameters_, avp_undistorters_);
            return 0;
        }
    }

    if (!boost::filesystem::exists(map_data_dir + map_names.at(0) + "/" + raw_data_path))
    {
        throw std::runtime_error("the raw data path: " + map_data_dir + map_names.at(0) + "/" + raw_data_path +
                                 " is not exist !!!");
    }

    camera_parameters_ = CameraParameters::LoadFromBin(map_data_dir + map_names.at(0) + "/camera_params.bin");
    LOG(INFO) << camera_parameters_;
    undistorters_       = Utility::CreateImageUndistorters(camera_parameters_->intrinsics);
    timestamp_frame_id_ = LoadTimeStampAndFrameId(map_data_dir + map_names.at(0) + "/timestamp_and_frame_id.txt");

    // create timestamp to frame id map and frame id to timestamp map
    for (const auto& time_frame_id : timestamp_frame_id_)
    {
        const auto& timestamp = time_frame_id.first;
        const auto& frame_id  = time_frame_id.second;
        timestamp_to_frame_id.emplace(timestamp, frame_id);
        frame_id_to_timestamp.emplace(frame_id, timestamp);
    }

    const auto keyframes = mdm.GetKeyframes();
    LOG(INFO) << "Load keyframe success, the total size is: " << keyframes.size();
    const auto learned_path = mdm.GetLearnedPath();
    LOG(INFO) << "Load learned path success, the total size is: " << learned_path.size();

    const auto  feature_lists      = LoadFeatures("/opt/holo/hpp/route_1/" + raw_data_path);
    const auto  timestamp_features = ConvertPointFeatures(feature_lists);
    const auto  prior_pose         = learned_path.at(0).GetPose();
    std::string image_path         = "";
    for (const auto& item : timestamp_features)
    {
        image_path = map_data_dir + map_names.at(0) + "/" + raw_data_path + "/images/" +
                     std::to_string(item.first.ToNsec()) + ".png";

        if (boost::filesystem::exists(image_path))
        {
            std::cout << image_path << std::endl;
            const auto     query_img   = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
            const uint16_t width       = query_img.cols;
            const uint16_t height      = query_img.rows;
            const uint32_t buffer_size = width * height;
            holo::Image    image;
            image.SetData(static_cast<uint8_t*>(query_img.data), buffer_size, width, height,
                          holo::Image::Encoding::GRAYSCALE);

            holo::localization::Mat undistorted_img;
            undistorters_.at(0)->Undistort(holo::localization::Mat(image), undistorted_img);
            // cv::imshow("ori_img", query_img);
            // cv::imshow("undistorted_img", undistorted_img.GetCvType());
            // cv::waitKey(0);
            SolvePoseByFrameToFrameMatching(keyframes, item.second, prior_pose, undistorted_img.GetCvType(),
                                            camera_parameters_, undistorters_);
            break;
        }
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
