/*!
 * \brief visual relocalization class implementation
 * \author Feng.Li lifeng@holomatic.com
 * \date Aug-26-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/localization/relocalization.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
/**
 * @brief initalize static value
 *
 */
std::shared_ptr<DBoW3::Vocabulary> Relocalization::bow_vocabulary_ = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Relocalization::Parameters Relocalization::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // frequency
    Scalar frequency = 1.0;

    // queue size
    uint64_t measurements_queue_size = 1;

    // parameters to query candidate keyframes
    Scalar      distance_threshold   = 15.0;
    Scalar      angle_threshold      = 30.0;
    uint16_t    maximum_keyframe_num = 6;
    std::string bow_vocabulary_path;
    uint16_t    query_type_uint16 = 0u;

    // enable_pose_only_ba
    bool enable_pose_only_ba = true;

    // visualize matches
    bool visualize_matches = false;

    // ransac pnp solver parameters
    uint16_t iteration              = 100;
    Scalar   projection_threshold   = 0.005;
    Scalar   confidence             = 0.99;
    uint16_t minimum_correspondence = 10;
    uint16_t minimum_inliers        = 8;

    if (!node.IsNull())
    {
        frequency               = node["frequency"].as<Scalar>(1.0);
        measurements_queue_size = node["measurements_queue_size"].as<uint64_t>(5);
        distance_threshold      = node["distance_threshold"].as<Scalar>(10.0);
        angle_threshold         = node["angle_threshold"].as<Scalar>(15.0);
        maximum_keyframe_num    = node["maximum_keyframe_num"].as<uint16_t>(6);
        enable_pose_only_ba     = node["enable_pose_only_ba"].as<bool>(true);
        visualize_matches       = node["visualize_matches"].as<bool>(false);
        bow_vocabulary_path =
            holo::GetHoloConfigRootDirectory() + "/" + node["bow_vocabulary_path"].as<std::string>("");
        query_type_uint16      = node["query_type_uint16"].as<uint16_t>(0u);
        iteration              = node["iteration"].as<uint16_t>(100);
        projection_threshold   = node["projection_threshold"].as<Scalar>(0.005);
        confidence             = node["confidence"].as<Scalar>(0.99);
        minimum_correspondence = node["minimum_correspondence"].as<uint16_t>(10);
        minimum_inliers        = node["minimum_inliers"].as<uint16_t>(8);
    }

    RansacPnPParameters ransac_pnp_params(iteration, projection_threshold, confidence, minimum_correspondence,
                                          minimum_inliers);

    return Parameters(frequency, measurements_queue_size, distance_threshold, angle_threshold, maximum_keyframe_num,
                      enable_pose_only_ba, visualize_matches, ransac_pnp_params, bow_vocabulary_path,
                      query_type_uint16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Relocalization::Parameters Relocalization::Parameters::Example()
{
    return Parameters();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Relocalization::Relocalization(const Parameters& parameters, const CameraParameters::Ptr& camera_parameters)
  : parameters_(parameters)
  , camera_parameters_(camera_parameters)
  , measurements_queue_(parameters_.measurements_queue_size)
  , lastest_relocalization_msg_(boost::none)
  , query_type_(static_cast<QueryType>(parameters.query_type_uint16))
{
    // start main thread
    relocalization_thread_ = std::make_shared<std::thread>(
        std::bind(&Relocalization::threadFunc, this, std::placeholders::_1), parameters_.frequency);
    pthread_setname_np(relocalization_thread_->native_handle(), "VslamRelocalizationThread");

    // toggle state to ready
    state_ = Base::State::READY;
    Spin();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<Pose3, std::vector<uint16_t>> Relocalization::RansacPnpRun(const std::vector<cv::Point3d>& point3d,
                                                                     const std::vector<cv::Point2d>& point2d,
                                                                     const cv::Mat&                  K) const
{
    // check minimum correspondence
    if (point3d.size() < parameters_.ransac_pnp_params.minimum_correspondence)
    {
        LOG(ERROR) << "Relocalization --- correspondence for solve pnp is few. correspondence num: " << point3d.size()
                   << "\n";
        return {};
    }

    cv::Mat               R, r, t;
    std::vector<uint16_t> inliers;

    if (!cv::solvePnPRansac(point3d, point2d, K, cv::Mat(), r, t, false, parameters_.ransac_pnp_params.iteration,
                            parameters_.ransac_pnp_params.projection_threshold,
                            parameters_.ransac_pnp_params.confidence, inliers, cv::SOLVEPNP_EPNP))
    {
        LOG(ERROR) << "Relocalization --- Solve pnp failed.\n";
        return {};
    }

    // check inliers num
    if (inliers.size() < parameters_.ransac_pnp_params.minimum_inliers)
    {
        LOG(ERROR) << "Relocalization --- inliers after solve pnp is few. inliers num: " << inliers.size()
                   << ", correspondence num" << point3d.size() << "\n";
        return {};
    }

    cv::Rodrigues(r, R);
    gtsam::Matrix3 rotation;
    cv::cv2eigen(R, rotation);
    const Pose3 T_cw(Rot3(HoloGtsam::Convert(rotation)),
                     Point3(t.at<float64_t>(0), t.at<float64_t>(1), t.at<float64_t>(2)));
    const Pose3 T_wc = T_cw.Inverse();

    return std::make_pair(T_wc, inliers);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::pair<uint64_t, uint16_t>> Relocalization::QueryCandidateFramesByPose(
    KeyFramesDatabase const& train_frames, Pose3 const& prior_camera_pose, uint16_t const n_best_candidates,
    Scalar const dist_threshold, Scalar const angle_threshold) const
{
    if (train_frames.size() < n_best_candidates)
    {
        LOG(ERROR) << "ERROR: at least " << n_best_candidates << " need by relocation, "
                   << "But current keyframe database size = " << train_frames.size();

        return {};
    }

    /**
     * @brief Step-1: compute pose difference between query_frame and train_frame
     *
     * @details in tuple, uint64_t -> frame_id. uint16_t -> camera_index, Scalar -> delta_dist
     * @note only keyframe which within the range of differences(orientation, position) will be stored
     */
    std::vector<std::tuple<uint64_t, uint16_t, Scalar>> candidate_frames_index;

    for (const auto& frame : train_frames)
    {
        for (auto const& single_camera : frame.second.multi_camera_data)
        {
            uint16_t const camera_id   = single_camera.features.front().camera_id;
            auto const     delta_T     = prior_camera_pose.Inverse() * single_camera.pose;
            auto const     delta_dist  = delta_T.GetTranslation().ToVector().GetNorm();
            auto const     delta_angle = delta_T.GetRotation().ComputeAngle();

            if (delta_dist > dist_threshold || delta_angle > angle_threshold)
            {
                continue;
            }

            candidate_frames_index.emplace_back(frame.first, camera_id, delta_dist);
        }
    }

    /**
     * @brief Step-2: sort keyframe by distance, we just choose N-best keyframe do geometry-consistency-check
     */
    std::sort(candidate_frames_index.begin(), candidate_frames_index.end(),
              [](std::tuple<uint64_t, uint16_t, Scalar> const& c0, std::tuple<uint64_t, uint16_t, Scalar> const& c1) {
                  return std::get<2>(c0) < std::get<2>(c1);
              });

    /**
     * @brief Step-3: return the N-best candidate keyframes
     */
    std::vector<std::pair<uint64_t, uint16_t>> candidate_results;
    candidate_results.reserve(n_best_candidates);

    for (const auto& candidate : candidate_frames_index)
    {
        // 0 -> frame_id, 1 -> camera_id
        candidate_results.emplace_back(std::get<0>(candidate), std::get<1>(candidate));

        if (candidate_results.size() > n_best_candidates)
        {
            break;
        }
    }

    return candidate_results;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::pair<uint64_t, uint16_t>>
Relocalization::QueryCandidateFramesByBOW(Features const& query_features, FrameIndexedBows const& keyframes_bow_vectors,
                                          uint16_t const n_best_candidates) const
{
    if (keyframes_bow_vectors.size() < n_best_candidates)
    {
        LOG(ERROR) << "ERROR: at least " << n_best_candidates << " need by relocation"
                   << "But current keyframe database size = " << keyframes_bow_vectors.size();

        return {};
    }

    /// Step-1: Compute query_image's bag-of-words vector using their keypoint descriptors
    std::vector<cv::Mat> query_img_descriptors;
    query_img_descriptors.reserve(query_features.size());

    // gets all the descriptors of the query frame
    for (auto const& query_feature : query_features)
    {
        if (query_feature.optional_descriptor == boost::none)
        {
            LOG(WARNING) << "Relocalization call BOW method, but there have keypoints which descriptors is none!";
            continue;
        }

        query_img_descriptors.emplace_back(*query_feature.optional_descriptor);
    }

    DBoW3::BowVector query_img_bow;
    bow_vocabulary_->transform(query_img_descriptors, query_img_bow);

    /**
     * @brief Step-2: Compute key-frame's bag-of-words vector
     *
     * @details one key-frame will have muti-camera's image data, because of the different orientation of the vehicle
     * when running, there may be covisible between a front camera and a rear camera, same with other camera; To ensure
     * the accuracy of the query, we will check all images in one keyframe
     */
    std::vector<std::tuple<uint64_t, uint16_t, Scalar>> frameID_cameraID_score;

    for (auto const& single_frame_bow : keyframes_bow_vectors)
    {
        // get the ID about keyframe
        uint64_t frame_id = single_frame_bow.first;

        for (auto const& single_camera_bow : single_frame_bow.second)
        {
            /**
             * @brief get the ID/descrptors about camera
             *
             * @details compute the BOW vector similarity score between \b query_frame and \b train_frame
             */
            uint16_t         camera_id     = single_camera_bow.first;
            DBoW3::BowVector train_img_bow = single_camera_bow.second;
            Scalar           score         = bow_vocabulary_->score(query_img_bow, train_img_bow);

            frameID_cameraID_score.emplace_back(frame_id, camera_id, score);
        }
    }

    /**
     * @details Step-3: sort by BOW's score (similarity)
     */
    std::sort(frameID_cameraID_score.begin(), frameID_cameraID_score.end(),
              [](std::tuple<uint64_t, uint16_t, Scalar> const& c0, std::tuple<uint64_t, uint16_t, Scalar> const& c1) {
                  return std::get<2>(c0) < std::get<2>(c1);
              });

    /// @brief Step-4: obtain top N similar candidate keyframes
    std::vector<std::pair<uint64_t, uint16_t>> candidate_results;
    candidate_results.reserve(n_best_candidates);

    for (auto const& candidate : frameID_cameraID_score)
    {
        // 0 -> frame_id, 1 -> camera_id
        candidate_results.emplace_back(std::get<0>(candidate), std::get<1>(candidate));

        if (candidate_results.size() >= n_best_candidates)
        {
            break;
        }
    }

    return candidate_results;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Relocalization::FrameToFrameCheckingResult Relocalization::GeometricConsistencyChecking(
    const KeyFrame& train_frame, const uint16_t train_camera_index, const Features& query_features,
    const boost::optional<Pose3>& prior_Twc) const
{
    const auto& single_camera_data = train_frame.multi_camera_data.at(train_camera_index);

    // check the view direction between train camera and query camera
    if (prior_Twc)
    {
        Scalar const kAngleThreshold = 30.0;  // degree
        if ((single_camera_data.pose.Inverse() * (*prior_Twc)).GetRotation().ComputeAngle() > kAngleThreshold)
        {
            return FrameToFrameCheckingResult();
        }
    }

    const Scalar minimum_feature_num = 20;
    if (single_camera_data.features.size() < minimum_feature_num || query_features.size() < minimum_feature_num)
    {
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
    const Scalar dist_th       = 1.0;
    const Scalar ratio_test_th = 1.0;
    TicTocTimer  timer;
    timer.Tic();
    const auto match_pairs =
        DescriptorMatcher::BruteForceMatching(last_descriptors, curr_descriptors, dist_th, ratio_test_th);
    LOG(INFO) << "BruteForceMatching tacks " << 1000.0 * timer.Elapsed() << " ms.\n";

    // solve pnp
    if (match_pairs.size() < parameters_.ransac_pnp_params.minimum_correspondence)
    {
        LOG(ERROR) << "Relocalization --- matched feature is too few. matched feature num: " << match_pairs.size()
                   << "\n";
        return FrameToFrameCheckingResult();
    }

    // retrieve 3d-2d correspondence for pnp solver
    std::vector<cv::Point3d> pts3;
    pts3.reserve(match_pairs.size());
    std::vector<cv::Point2d> pts2;
    pts2.reserve(match_pairs.size());

    // retrieve 3d2dcorrespondences
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
    cv::eigen2cv(HoloGtsam::Convert(K), cv_K);
    const auto  rasanc_pnp_result = RansacPnpRun(pts3, pts2, cv_K);
    const auto& T_wc              = rasanc_pnp_result.first;
    const auto& inliers           = rasanc_pnp_result.second;

    LOG(INFO) << "query frame id: " << current_measurement_.query_frame_id
              << ", train features: " << single_camera_data.features.size()
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

    return FrameToFrameCheckingResult(std::make_pair(train_frame.frame_id, train_camera_index), match_pairs,
                                      inliers_pair, T_wc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t Relocalization::BoundaryClamp(const int32_t value, const int32_t min, const int32_t max) const
{
    int32_t result = value < min ? min : value;
    result         = result > max ? max : result;

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MapProjectionMeasurements Relocalization::CreatePoseOnlyProjectionFactorMeasurements(
    const KeyFramesDatabase& train_frames, const Features& query_features,
    const std::vector<FrameToFrameCheckingResult>& associated_results) const
{
    // check input
    if (train_frames.empty() || query_features.empty() || associated_results.empty())
    {
        LOG(ERROR) << "Relocalization --- CreatePoseOnlyProjectionFactorMeasurements, nothing should be processed.\n";
        return {};
    }

    MapProjectionMeasurements mpm;
    const auto&               query_camera_index = query_features.at(0).camera_id;
    const auto&               intrinsic          = camera_parameters_->intrinsics.at(query_camera_index);
    const auto                undistorter        = Utility::CreateImageUndistorter(intrinsic);

    // create mask arount exist associated features in query frame
    const auto&          image_width  = intrinsic->GetWidth();
    const auto&          image_height = intrinsic->GetHeight();
    cv::Mat              mask(image_height, image_width, CV_8UC1, cv::Scalar(0));
    static const int32_t minimum_feature_distance = 4.0;

    // traversal all associated results
    for (const auto& associated_result : associated_results)
    {
        const auto& train_frame_id     = associated_result.train_frame_id_and_camera_index.first;
        const auto& train_camera_index = associated_result.train_frame_id_and_camera_index.second;
        const auto& mappoints = train_frames.at(train_frame_id).multi_camera_data.at(train_camera_index).mappoints;
        const auto& inliers   = associated_result.inliers;
        mpm.reserve(mpm.size() + associated_result.inliers.size());

        // traversal all inliers
        for (const auto& inlier_index : inliers)
        {
            // retrieve associated train mappoints
            const auto& train_landmark_index = inlier_index.first;
            const auto& ptw                  = mappoints.at(train_landmark_index);

            // retrieve associated query feature
            const auto& query_feature_index = inlier_index.second;
            const auto& query_feature       = query_features.at(query_feature_index);
            Point2      undistorted_point(query_feature.image_point.x, query_feature.image_point.y);
            Point2      distorted_point = undistorted_point;

            if (intrinsic->GetModel() == Model::PINHOLE)
            {
                PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());

                if (!pinhole)
                {
                    LOG(ERROR) << "Relocalization --- failed to cast source intrinsic to pinhole type";
                    throw std::runtime_error("Relocalization --- failed to cast source intrinsic to pinhole type");
                }
                std::vector<Point2> undistorted_points{undistorted_point}, distorted_points;
                pinhole->DistortPoints(undistorted_points, distorted_points);
                distorted_point = distorted_points.front();
            }
            else if (intrinsic->GetModel() == Model::FISHEYE)
            {
                FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());

                if (!fisheye)
                {
                    LOG(ERROR) << "Relocalization --- failed to cast source intrinsic to fisheye type";
                    throw std::runtime_error("Relocalization --- failed to cast source intrinsic to fisheye type");
                }
                std::vector<Point2> undistorted_points{undistorted_point}, distorted_points;
                fisheye->DistortPoints(undistorted_points, distorted_points);
                distorted_point = distorted_points.front();
            }

            // check if this feature was already associated to any landmarks
            if (mask.at<uchar>(cv::Point2f(distorted_point.GetX(), distorted_point.GetY())) == 250)
            {
                continue;
            }

            // create new pose only projection factor for this correspondence
            MapPoint mp;
            mp.position = ptw;

            /// @todo(Feng.Li lifeng@holomatic.com 2020-09-01) set other attribute of a MapPoint.

            mpm.emplace_back(current_measurement_.query_frame_id, query_camera_index, std::make_shared<MapPoint>(mp),
                             query_feature.normalized_point.ToVector());

            // mask this area
            const int32_t x    = static_cast<int32_t>(distorted_point.GetX());
            const int32_t y    = static_cast<int32_t>(distorted_point.GetY());
            int32_t       xmin = BoundaryClamp(x - minimum_feature_distance, 0, image_width - 1);
            int32_t       xmax = BoundaryClamp(x + minimum_feature_distance, 0, image_width - 1);
            int32_t       ymin = BoundaryClamp(y - minimum_feature_distance, 0, image_height - 1);
            int32_t       ymax = BoundaryClamp(y + minimum_feature_distance, 0, image_height - 1);
            cv::Range     row_range(ymin, ymax);
            cv::Range     col_range(xmin, xmax);
            mask(row_range, col_range) = 250;
        }
    }

    return mpm;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<Pose3, MapProjectionMeasurements> Relocalization::PoseOnlyBundleAdjustment(
    const MapProjectionMeasurements& mpms, const Pose3& prior_Twc, const IntrinsicBaseTypePtr& intrinsic) const
{
    // check factor number
    static const uint16_t minimum_correspondence_number = 10;
    if (mpms.size() < minimum_correspondence_number)
    {
        LOG(ERROR) << "Relocalization::PoseOnlyBundleAdjustment --- correspondence number is too few: " << mpms.size()
                   << "\n";
        return {};
    }

    // build factor graph
    FactorGraph factor_graph;
    Values      values;
    values.insert(X(0), HoloGtsam::Convert(prior_Twc));

    for (const auto& mpm : mpms)
    {
        const Point3&       point   = mpm.map_point->position;
        const Vector3&      feature = mpm.bearing;
        const gtsam::Point3 gtsam_point(point.GetX(), point.GetY(), point.GetZ());
        const gtsam::Point3 gtsam_feature(feature(0), feature(1), feature(2));

        // convert sigma_uv and loss from pixel error to unit3 error
        Scalar sigma_uv = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(intrinsic, 3.0);
        Scalar loss     = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(intrinsic, 2.5) / sigma_uv;

        // create noise model and huber loss
        /// @todo(Feng.Li 2020-06-03) we should also consider the covariance of the mappoints for this
        /// PoseOnlyUnit3Factor
        const gtsam::SharedNoiseModel noise_sigma =
            gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector2(sigma_uv, sigma_uv));
        const auto huber =
            gtsam::noiseModel::Robust::Create(gtsam::noiseModel::mEstimator::Huber::Create(loss), noise_sigma);

        // add PoseOnlyUnit3Factor
        factor_graph.add(
            boost::make_shared<PoseOnlyUnit3Factor>(gtsam_point, gtsam_feature, huber, X(0), gtsam::Pose3::identity()));
    }

    // optimization
    gtsam::LevenbergMarquardtOptimizer optimizer(factor_graph, values);
    Values                             optimized_values = optimizer.optimize();
    Pose3 optimized_Twc = HoloGtsam::Convert(optimized_values.at(X(0)).cast<gtsam::Pose3>());

    // check inliers
    const auto   Tcw                        = optimized_Twc.Inverse();
    const Scalar projection_error_threshold = 3.5;  // pixel
    const Scalar unit3_error_threshold =
        CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(intrinsic, projection_error_threshold);
    MapProjectionMeasurements inliers_mpms;
    inliers_mpms.reserve(mpms.size());

    for (const auto& mpm : mpms)
    {
        // re-project landmarks by optimized pose
        const auto& ptw      = mpm.map_point->position;
        Point3      proj_ptn = Tcw * ptw;

        // create two vectors
        const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(proj_ptn));
        const gtsam::Unit3 q = gtsam::Unit3(HoloGtsam::Convert(mpm.bearing));

        // compute error
        if (p.errorVector(q).norm() > unit3_error_threshold)
        {
            continue;
        }

        inliers_mpms.emplace_back(mpm);
    }

    LOG(INFO) << "Relocalization --- BA inliers: " << mpms.size() << " " << inliers_mpms.size() << "\n";
    static const uint16_t minimum_inlier_correspondence_number = 8;

    if (inliers_mpms.size() < minimum_inlier_correspondence_number)
    {
        LOG(ERROR) << "Relocalization --- inliers after optimization is too few. inliers num: " << inliers_mpms.size()
                   << "\n";
        return {};
    }

    return std::make_pair(optimized_Twc, inliers_mpms);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat Relocalization::MergeTwoImages(const cv::Mat& image0, const cv::Mat& image1) const
{
    int16_t row = std::max<int16_t>(image0.rows, image1.rows);
    int16_t col = image0.cols + image1.cols;
    cv::Mat mosaic_image(row, col, image0.type());
    image0.copyTo(mosaic_image.rowRange(0, image0.rows).colRange(0, image0.cols));
    image1.copyTo(mosaic_image.rowRange(0, image1.rows).colRange(image0.cols, col));
    return mosaic_image;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Relocalization::DrawMacthedInfo(const KeyFramesDatabase& train_frames, const Features& query_features,
                                     const cv::Mat&                                 query_image,
                                     const std::vector<FrameToFrameCheckingResult>& associated_results) const
{
    if (query_image.empty() || associated_results.empty())
    {
        return;
    }

    static const std::string image_dir          = "/opt/holo/hpp/route_1/images/";
    const auto&              best_result        = associated_results.front();
    const auto&              train_frame_id     = best_result.train_frame_id_and_camera_index.first;
    const auto&              train_camera_index = best_result.train_frame_id_and_camera_index.second;

    std::string train_image_name =
        image_dir + std::to_string(train_frame_id) + "-" + std::to_string(train_camera_index) + ".png";

    // check if train frame is exist in disk
    if (!boost::filesystem::exists(train_image_name))
    {
        LOG(INFO) << "Relocalization::DrawMacthedInfo --- image does nor exist: " << train_image_name << "\n";
        return;
    }

    // read train image from disk
    cv::Mat train_image = cv::imread(train_image_name, cv::IMREAD_COLOR);

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

    for (const auto& pair : matche_pairs)
    {
        const auto& train_index = pair.first;
        const auto& query_index = pair.second;
        const auto& confidence  = pair.second;

        const auto& train_pt = train_kpts.at(train_index);
        const auto& query_pt = query_kpts.at(query_index);
        const auto  color    = cv::Scalar(128, 128, confidence * 255);
        cv::line(image_with_matches, train_pt, query_pt + shift_pt, color, 2, cv::LineTypes::LINE_AA);
    }

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
    }

    std::stringstream ss;
    ss << "train features num: " << train_kpts.size() << ", query features num: " << query_kpts.size()
       << ", matched num: " << matche_pairs.size() << ", inliers num: " << inliers.size();

    cv::putText(image_with_matches, ss.str(), cv::Point2f(10, 950), cv::FONT_HERSHEY_DUPLEX, 1.5,
                cv::Scalar(0, 0, 255));

    cv::namedWindow("matches", 0);
    cv::imshow("matches", image_with_matches);
    cv::waitKey(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<Relocalization::FrameToFrameCheckingResult> Relocalization::SolvePoseByFrameToFrameMatching(
    const KeyFramesDatabase& train_frames, const Features& query_features,
    const boost::optional<Pose3>& prior_vehicle_pose, const cv::Mat& query_image) const
{
    /// @brief Step-0: soucre data check
    if (query_features.empty() || train_frames.empty())
    {
        LOG(ERROR) << "Relocalization --- Empty query features or train keyframes!";
        return {};
    }

    // get camera's prior pose if prior vehicle pose exist
    boost::optional<Pose3> prior_camera_pose;

    if (prior_vehicle_pose)
    {
        const auto& query_camera_index = query_features.front().camera_id;
        const auto& T_bc               = camera_parameters_->extrinsics.at(query_camera_index);
        prior_camera_pose              = (*prior_vehicle_pose) * T_bc;

        LOG(INFO) << "SolvePoseByFrameToFrameMatching: Compute prior camera pose using prior vehicle pose";
    }

    /// @brief Step-1: get candiate frames using specify query type
    std::vector<std::pair<uint64_t, uint16_t>> candidate_frames_ids;

    if (query_type_ == QueryType::PRIOR_POSE && prior_camera_pose)
    {
        LOG(INFO) << "Query candidate keyframes using initial camera pose!";
        candidate_frames_ids =
            QueryCandidateFramesByPose(train_frames, *prior_camera_pose, parameters_.maximum_keyframe_num,
                                       parameters_.distance_threshold, parameters_.angle_threshold);
    }
    else if (query_type_ == QueryType::BOW)
    {
        LOG(INFO) << "Query candidate keyframes using bag of words method!";
        candidate_frames_ids =
            QueryCandidateFramesByBOW(query_features, keyframes_bow_vectors_, parameters_.maximum_keyframe_num);
    }
    else
    {
        LOG(ERROR) << "Relocalization --- UNKNOWN query candidate keyframe's method!";
        return {};
    }

    LOG(INFO) << "Relocalization --- candidate_frames: " << candidate_frames_ids.size() << "\n";

    /// @brief Step-2: obtain associate results from geometry consistency Checking
    std::vector<FrameToFrameCheckingResult> associated_results;

    for (const auto& train_frame_id : candidate_frames_ids)
    {
        LOG(ERROR) << "Search result about train frame ID: " << train_frame_id.first;
        auto const&    train_frame  = train_frames.at(train_frame_id.first);
        uint16_t const camera_index = train_frame_id.second;
        auto const result = GeometricConsistencyChecking(train_frame, camera_index, query_features, prior_camera_pose);

        if (result.inliers.empty())
        {
            continue;
        }

        associated_results.emplace_back(result);
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
    if (parameters_.visualize_matches)
    {
        DrawMacthedInfo(train_frames, query_features, query_image, associated_results);
    }

    return associated_results;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Pose3> Relocalization::RunSynchronously(const std::vector<Features>&  multi_camera_features,
                                                        const boost::optional<Pose3>& prior_vehicle_pose) const
{
    // trying to relocaization by each camera data
    for (uint16_t camera_index = 0; camera_index < multi_camera_features.size(); camera_index++)
    {
        const auto& query_features = multi_camera_features.at(camera_index);
        const auto& intrinsic      = camera_parameters_->intrinsics.at(camera_index);
        const auto& T_bc           = camera_parameters_->extrinsics.at(camera_index);

        const auto associated_results =
            SolvePoseByFrameToFrameMatching(key_frames_database_, query_features, prior_vehicle_pose);

        // check if solved pose successfully
        if (associated_results.empty())
        {
            continue;
        }

        // retrieve best camera pose
        auto best_Twc = associated_results.front().T_wc;

        // create new pose only projection factor measurements
        auto inliers_mpms =
            CreatePoseOnlyProjectionFactorMeasurements(key_frames_database_, query_features, associated_results);

        // optimize camera pose
        if (parameters_.enable_pose_only_ba)
        {
            const auto ba_result = PoseOnlyBundleAdjustment(inliers_mpms, associated_results.front().T_wc, intrinsic);
            best_Twc             = ba_result.first;
            inliers_mpms         = ba_result.second;
        }

        // check if optimization failed
        if (inliers_mpms.empty())
        {
            continue;
        }

        return best_Twc * T_bc.Inverse();
    }

    return boost::none;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Relocalization::run()
{
    TicTocTimer reloc_timer;
    reloc_timer.Tic();
    {
        std::unique_lock<std::mutex> lock(relocalization_mutex_);
        current_measurement_ = measurements_queue_.front();
        measurements_queue_.pop_front();
    }

    LOG(INFO) << "Relocalization --- EstimationCore is running ...\n";
    const auto&                    prior_vehicle_pose = current_measurement_.prior_Twb;
    std::vector<RelocalizationMsg> relocalization_msg;
    relocalization_msg.reserve(current_measurement_.multi_camera_features.size());

    // trying to relocaization by each camera data
    for (uint16_t camera_index = 0; camera_index < camera_parameters_->camera_number; camera_index++)
    {
        const auto& query_features = current_measurement_.multi_camera_features.at(camera_index);
        const auto& query_image    = current_measurement_.multi_camera_grayscale.at(camera_index);
        const auto& intrinsic      = camera_parameters_->intrinsics.at(camera_index);
        const auto& T_bc           = camera_parameters_->extrinsics.at(camera_index);

        const auto associated_results =
            SolvePoseByFrameToFrameMatching(key_frames_database_, query_features, prior_vehicle_pose, query_image);

        if (associated_results.empty())
        {
            continue;
        }

        // retrieve best camera pose
        auto best_Twc = associated_results.front().T_wc;

        // create new pose only projection factor measurements
        auto inliers_mpms =
            CreatePoseOnlyProjectionFactorMeasurements(key_frames_database_, query_features, associated_results);

        // optimize camera pose
        if (parameters_.enable_pose_only_ba)
        {
            const auto ba_result = PoseOnlyBundleAdjustment(inliers_mpms, associated_results.front().T_wc, intrinsic);
            best_Twc             = ba_result.first;
            inliers_mpms         = ba_result.second;
        }

        // check if optimization failed
        if (inliers_mpms.empty())
        {
            continue;
        }

        relocalization_msg.emplace_back(current_measurement_.query_frame_id, best_Twc * T_bc.Inverse(), inliers_mpms);
    }

    if (!relocalization_msg.empty())
    {
        // put all result together
        std::sort(relocalization_msg.begin(), relocalization_msg.end(),
                  [](const RelocalizationMsg& msg1, const RelocalizationMsg& msg2) {
                      return msg1.mpm.size() > msg2.mpm.size();
                  });

        MapProjectionMeasurements final_mpms;
        for (const auto& msg : relocalization_msg)
        {
            const auto& mpms = msg.mpm;
            final_mpms.reserve(final_mpms.size() + mpms.size());
            std::copy(mpms.begin(), mpms.end(), std::back_inserter(final_mpms));
        }

        {
            // update place_recognition_msg for other module
            std::unique_lock<std::mutex> lock(relocalization_mutex_);
            lastest_relocalization_msg_ = RelocalizationMsg(current_measurement_.query_frame_id,
                                                            relocalization_msg.front().query_T_wb, final_mpms);
        }
    }

    // record timer
    LOG(INFO) << "Relocalization --- EstimationCore takes " << 1e3 * reloc_timer.Elapsed() << " ms";
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
