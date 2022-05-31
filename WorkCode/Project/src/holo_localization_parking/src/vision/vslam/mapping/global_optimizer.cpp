/*!
 * \brief global optimizer class implementation file in vslam
 * \author Feng. Li, lifeng@holomatic.com
 * \date Mar-02-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtsam/nonlinear/ISAM2.h>
#include <holo/localization/vision/vslam/mapping/global_optimizer.h>
#include <holo/localization/vision/vslam/rotation_only_imu_factor.h>

#include <eigen3/Eigen/Dense>
#include <opencv2/core/eigen.hpp>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalOptimizer::Parameters GlobalOptimizer::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    // loop detector parameters
    const holo::yaml::Node loop_detector_node   = node["loop_detector"];
    const auto             loop_detector_params = LoopDetector::Parameters::LoadFromYaml(loop_detector_node);

    // loop triangulator parameters
    const holo::yaml::Node triangulation_node  = node["triangulation"];
    const auto             triangulator_params = Triangulator::Parameters::LoadFromYaml(triangulation_node);

    // sigmas
    const holo::yaml::Node sigmas_nodes = node["sigmas"];

    Vector6 bias_between_sigma;
    {
        const holo::yaml::Node sigma_node = sigmas_nodes["bias_between_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        bias_between_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        bias_between_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        bias_between_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
        bias_between_sigma(3) = sigma_node.IsNull() ? 5e-6 : sigma_node[3].as<Scalar>();
        bias_between_sigma(4) = sigma_node.IsNull() ? 5e-6 : sigma_node[4].as<Scalar>();
        bias_between_sigma(5) = sigma_node.IsNull() ? 2e-6 : sigma_node[5].as<Scalar>();
    }

    Vector3 velocity_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["velocity_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        velocity_factor_sigma(0) = sigma_node.IsNull() ? 0.034 : sigma_node[0].as<Scalar>();
        velocity_factor_sigma(1) = sigma_node.IsNull() ? 0.034 : sigma_node[1].as<Scalar>();
        velocity_factor_sigma(2) = sigma_node.IsNull() ? 0.034 : sigma_node[2].as<Scalar>();
    }

    Vector3 velocity_factor_sigma_when_turns;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["velocity_factor_sigma_when_turns"].as<holo::yaml::Node>(holo::yaml::Node());

        velocity_factor_sigma_when_turns(0) = sigma_node.IsNull() ? 0.034 : sigma_node[0].as<Scalar>();
        velocity_factor_sigma_when_turns(1) = sigma_node.IsNull() ? 0.1 : sigma_node[1].as<Scalar>();
        velocity_factor_sigma_when_turns(2) = sigma_node.IsNull() ? 0.034 : sigma_node[2].as<Scalar>();
    }

    Vector6 wheel_integration_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["wheel_integration_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        wheel_integration_factor_sigma(0) = sigma_node.IsNull() ? 100.0 : sigma_node[0].as<Scalar>();
        wheel_integration_factor_sigma(1) = sigma_node.IsNull() ? 100.0 : sigma_node[1].as<Scalar>();
        wheel_integration_factor_sigma(2) = sigma_node.IsNull() ? 1e-2 : sigma_node[2].as<Scalar>();
        wheel_integration_factor_sigma(3) = sigma_node.IsNull() ? 1e-2 : sigma_node[3].as<Scalar>();
        wheel_integration_factor_sigma(4) = sigma_node.IsNull() ? 1e-2 : sigma_node[4].as<Scalar>();
        wheel_integration_factor_sigma(5) = sigma_node.IsNull() ? 100.0 : sigma_node[5].as<Scalar>();
    }

    Vector6 zero_velocity_between_pose_sigma;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["zero_velocity_between_pose_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        zero_velocity_between_pose_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        zero_velocity_between_pose_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        zero_velocity_between_pose_sigma(2) = sigma_node.IsNull() ? 1e-3 : sigma_node[2].as<Scalar>();
        zero_velocity_between_pose_sigma(3) = sigma_node.IsNull() ? 0.00175 : sigma_node[3].as<Scalar>();
        zero_velocity_between_pose_sigma(4) = sigma_node.IsNull() ? 0.00175 : sigma_node[4].as<Scalar>();
        zero_velocity_between_pose_sigma(5) = sigma_node.IsNull() ? 0.00175 : sigma_node[5].as<Scalar>();
    }

    Vector6 loop_closing_between_pose_sigma;
    {
        loop_closing_between_pose_sigma(0) = sigmas_nodes["loop_closing_between_pose_sigma"][0].as<Scalar>(0.1);
        loop_closing_between_pose_sigma(1) = sigmas_nodes["loop_closing_between_pose_sigma"][1].as<Scalar>(0.1);
        loop_closing_between_pose_sigma(2) = sigmas_nodes["loop_closing_between_pose_sigma"][2].as<Scalar>(0.1);
        loop_closing_between_pose_sigma(3) = sigmas_nodes["loop_closing_between_pose_sigma"][3].as<Scalar>(0.1);
        loop_closing_between_pose_sigma(4) = sigmas_nodes["loop_closing_between_pose_sigma"][4].as<Scalar>(0.1);
        loop_closing_between_pose_sigma(5) = sigmas_nodes["loop_closing_between_pose_sigma"][5].as<Scalar>(0.1);
    }

    Vector6 prior_pose_sigma;
    {
        prior_pose_sigma(0) = sigmas_nodes["prior_pose_sigma"][0].as<Scalar>(0.1);
        prior_pose_sigma(1) = sigmas_nodes["prior_pose_sigma"][1].as<Scalar>(0.1);
        prior_pose_sigma(2) = sigmas_nodes["prior_pose_sigma"][2].as<Scalar>(0.1);
        prior_pose_sigma(3) = sigmas_nodes["prior_pose_sigma"][3].as<Scalar>(0.1);
        prior_pose_sigma(4) = sigmas_nodes["prior_pose_sigma"][4].as<Scalar>(0.1);
        prior_pose_sigma(5) = sigmas_nodes["prior_pose_sigma"][5].as<Scalar>(0.1);
    }

    Vector3 prior_velocity_sigma;
    {
        prior_velocity_sigma(0) = sigmas_nodes["prior_velocity_sigma"][0].as<Scalar>(0.1);
        prior_velocity_sigma(1) = sigmas_nodes["prior_velocity_sigma"][1].as<Scalar>(0.1);
        prior_velocity_sigma(2) = sigmas_nodes["prior_velocity_sigma"][2].as<Scalar>(0.1);
    }

    Vector6 prior_bias_sigma;
    {
        prior_bias_sigma(0) = sigmas_nodes["prior_bias_sigma"][0].as<Scalar>(0.1);
        prior_bias_sigma(1) = sigmas_nodes["prior_bias_sigma"][1].as<Scalar>(0.1);
        prior_bias_sigma(2) = sigmas_nodes["prior_bias_sigma"][2].as<Scalar>(0.1);
        prior_bias_sigma(3) = sigmas_nodes["prior_bias_sigma"][3].as<Scalar>(0.1);
        prior_bias_sigma(4) = sigmas_nodes["prior_bias_sigma"][4].as<Scalar>(0.1);
        prior_bias_sigma(5) = sigmas_nodes["prior_bias_sigma"][5].as<Scalar>(0.1);
    }

    Vector6 gt_pose_sigma;
    {
        const holo::yaml::Node sigma_node = node["gt_pose_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        // order is roll, pitch, yaw，x, y, z
        gt_pose_sigma(0) = sigma_node.IsNull() ? 0.0017 : sigma_node[0].as<Scalar>(0.0017);
        gt_pose_sigma(1) = sigma_node.IsNull() ? 0.0017 : sigma_node[1].as<Scalar>(0.0017);
        gt_pose_sigma(2) = sigma_node.IsNull() ? 0.0017 : sigma_node[2].as<Scalar>(0.0017);
        gt_pose_sigma(3) = sigma_node.IsNull() ? 0.005 : sigma_node[3].as<Scalar>(0.005);
        gt_pose_sigma(4) = sigma_node.IsNull() ? 0.005 : sigma_node[4].as<Scalar>(0.005);
        gt_pose_sigma(5) = sigma_node.IsNull() ? 0.005 : sigma_node[5].as<Scalar>(0.005);
    }

    /// sigma for vertex factor
    Vector3 vertex_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["vertex_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        vertex_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        vertex_factor_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        vertex_factor_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
    }

    /// sigma for plane factor
    Vector3 plane_factor_sigma;
    {
        const holo::yaml::Node sigma_node = sigmas_nodes["plane_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        plane_factor_sigma(0)             = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        plane_factor_sigma(1)             = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        plane_factor_sigma(2)             = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
    }

    /// sigma for point plane factor
    Vector1 point_plane_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["point_plane_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        point_plane_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
    }

    /// sigma for parallel factor
    Vector3 parallel_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            sigmas_nodes["parallel_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        parallel_factor_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        parallel_factor_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        parallel_factor_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
    }

    const Sigmas sigmas(bias_between_sigma, velocity_factor_sigma, velocity_factor_sigma_when_turns,
                        wheel_integration_factor_sigma, zero_velocity_between_pose_sigma,
                        loop_closing_between_pose_sigma, prior_pose_sigma, prior_velocity_sigma, prior_bias_sigma,
                        gt_pose_sigma, vertex_factor_sigma, plane_factor_sigma, point_plane_factor_sigma,
                        parallel_factor_sigma);

    // imu pre-integration parameters
    PreintegrationParamsPtr pim_params;
    const holo::yaml::Node  pim_node = node["pim_params"];
    {
        const Scalar   gravity = pim_node["gravity"].as<Scalar>(9.81);
        gtsam::Vector3 gyro_noise_sigma;
        {
            gyro_noise_sigma(0) = pim_node["gyro_noise_sigma"][0].as<Scalar>(1e-3);
            gyro_noise_sigma(1) = pim_node["gyro_noise_sigma"][1].as<Scalar>(1e-3);
            gyro_noise_sigma(2) = pim_node["gyro_noise_sigma"][2].as<Scalar>(1e-3);
        }

        gtsam::Vector3 acc_noise_sigma;
        {
            acc_noise_sigma(0) = pim_node["acc_noise_sigma"][0].as<Scalar>(1e-3);
            acc_noise_sigma(1) = pim_node["acc_noise_sigma"][1].as<Scalar>(1e-3);
            acc_noise_sigma(2) = pim_node["acc_noise_sigma"][2].as<Scalar>(1e-3);
        }

        gtsam::Vector3 gyro_noise_sigma_square;
        gtsam::Vector3 acc_noise_sigma_square;

        for (auto i = 0; i < 3; i++)
        {
            gyro_noise_sigma_square(i) = std::pow(gyro_noise_sigma(i), 2);
            acc_noise_sigma_square(i)  = std::pow(acc_noise_sigma(i), 2);
        }

        // create pim params
        pim_params = gtsam::PreintegrationParams::MakeSharedU(gravity);

        // construct pim covariance
        const gtsam::Matrix3 gyro_cov = gyro_noise_sigma_square.asDiagonal();
        const gtsam::Matrix3 acc_cov  = acc_noise_sigma_square.asDiagonal();
        const gtsam::Matrix3 int_cov  = gtsam::Matrix3::Identity() * 1e-8;

        // set pim covariance
        pim_params->setGyroscopeCovariance(gyro_cov);
        pim_params->setAccelerometerCovariance(acc_cov);
        pim_params->setIntegrationCovariance(int_cov);
    }

    // frame to frame checking parameters
    const holo::yaml::Node f2fc_node = node["f2fc_params"].as<holo::yaml::Node>(holo::yaml::Node());
    const auto             minimum_frame_interval =
        f2fc_node.IsNull() ? 100 : f2fc_node["minimum_frame_interval"].as<uint64_t>(100);
    const auto descriptor_distance_th = f2fc_node.IsNull() ? 1.2 : f2fc_node["descriptor_distance_th"].as<Scalar>(1.2);
    const auto ratio_test_th          = f2fc_node.IsNull() ? 1.0 : f2fc_node["ratio_test_th"].as<Scalar>(0.85);
    const auto matches_threshold      = f2fc_node.IsNull() ? 10 : f2fc_node["matches_threshold"].as<uint16_t>(10);
    const auto ransanc_iterations_number =
        f2fc_node.IsNull() ? 100 : f2fc_node["ransanc_iterations_number"].as<uint16_t>(100);
    const auto projection_error_threshold =
        f2fc_node.IsNull() ? 8e-3 : f2fc_node["projection_error_threshold"].as<Scalar>(8e-3);
    const auto confidence             = f2fc_node.IsNull() ? 0.99 : f2fc_node["confidence"].as<Scalar>(0.99);
    const auto minimum_inliers_number = f2fc_node.IsNull() ? 8 : f2fc_node["minimum_inliers_number"].as<uint16_t>(8);
    const FrameToFrameCheckingParameters f2fc_params(minimum_frame_interval, descriptor_distance_th, ratio_test_th,
                                                     matches_threshold, ransanc_iterations_number,
                                                     projection_error_threshold, confidence, minimum_inliers_number);

    // frame to covisibility map checking parameters
    const holo::yaml::Node f2cmc_node = node["f2cmc_params"].as<holo::yaml::Node>(holo::yaml::Node());
    const auto             max_covisibility_intensity =
        f2cmc_node.IsNull() ? 60 : f2cmc_node["max_covisibility_intensity"].as<uint16_t>(60);
    const auto min_covisibility_intensity =
        f2cmc_node.IsNull() ? 3 : f2cmc_node["min_covisibility_intensity"].as<uint16_t>(5);
    const auto window_size              = f2cmc_node.IsNull() ? 80.0 : f2cmc_node["window_size"].as<Scalar>(80.0);
    const auto f2cmc_descriptor_dist_th = f2cmc_node.IsNull() ? 1.0 : f2cmc_node["descriptor_dist_th"].as<Scalar>(1.0);
    const auto f2cmc_ratio_test_th      = f2cmc_node.IsNull() ? 1.0 : f2cmc_node["ratio_test_th"].as<Scalar>(0.95);
    const auto view_distance_th        = f2cmc_node.IsNull() ? 100.0 : f2cmc_node["view_distance_th"].as<Scalar>(100.0);
    const auto view_direction_th       = f2cmc_node.IsNull() ? 45.0 : f2cmc_node["view_direction_th"].as<Scalar>(45.0);
    const auto f2cmc_matches_threshold = f2cmc_node.IsNull() ? 80 : f2cmc_node["matches_threshold"].as<uint16_t>(60);
    const Vector2 pose_only_unit3_factor_sigma(
        f2cmc_node.IsNull() ? 0.05 : f2cmc_node["pose_only_unit3_factor_sigma"][0].as<Scalar>(0.05),
        f2cmc_node.IsNull() ? 0.05 : f2cmc_node["pose_only_unit3_factor_sigma"][1].as<Scalar>(0.05));
    const auto pose_only_unit3_factor_huber_loss =
        f2cmc_node.IsNull() ? 0.5 : f2cmc_node["pose_only_unit3_factor_huber_loss"].as<Scalar>(0.5);
    const auto f2cmc_projection_error_threshold =
        f2cmc_node.IsNull() ? 5e-3 : f2cmc_node["projection_error_threshold"].as<Scalar>(5e-3);
    const auto f2cmc_minimum_inliers_number =
        f2cmc_node.IsNull() ? 45 : f2cmc_node["minimum_inliers_number"].as<uint16_t>(50);
    const FrameToCovisibilityMapCheckingParameters f2cmc_params(
        max_covisibility_intensity, min_covisibility_intensity, window_size, f2cmc_descriptor_dist_th,
        f2cmc_ratio_test_th, view_distance_th, view_direction_th, f2cmc_matches_threshold, pose_only_unit3_factor_sigma,
        pose_only_unit3_factor_huber_loss, f2cmc_projection_error_threshold, f2cmc_minimum_inliers_number);

    // inliers projection error after global BA
    const auto projection_error_after_gba = node["projection_error_after_gba"].as<Scalar>(3e-3);

    // max landmark distance
    const auto max_landmark_distance = node["max_landmark_distance"].as<Scalar>(150.0);

    // enable_gt_pose_factor
    const auto enable_gt_pose_factor = node["enable_gt_pose_factor"].as<bool>(false);

    // enable_position_factor
    const auto enable_position_factor = node["enable_position_factor"].as<bool>(false);

    // enable_visualizer
    const auto enable_visualizer = node["enable_visualizer"].as<bool>(false);

    // working mode
    const auto mode = node["mode"].as<std::string>("single_map_optimization");

    const bool verbose = node["verbose"].as<bool>(false);

    const auto minimum_keyframe_travel_distance = node["minimum_keyframe_travel_distance"].as<Scalar>(0.5);

    const auto minimum_keyframe_angle = node["minimum_keyframe_angle"].as<Scalar>(3.0);

    const auto enable_loop_detection = node["enable_loop_detection"].as<bool>(false);

    const auto factor_number_in_one_frame = node["factor_number_in_one_frame"].as<uint64_t>(20);

    const auto minimum_valid_track_length = node["minimum_valid_track_length"].as<uint64_t>(3);

    const auto frame_num_selected_for_epipolar_matching =
        node["frame_num_selected_for_epipolar_matching"].as<uint32_t>(10);

    return Parameters(loop_detector_params, triangulator_params, sigmas, pim_params, f2fc_params, f2cmc_params,
                      projection_error_after_gba, max_landmark_distance, enable_gt_pose_factor, enable_position_factor,
                      enable_visualizer, mode, verbose, minimum_keyframe_travel_distance, minimum_keyframe_angle,
                      enable_loop_detection, factor_number_in_one_frame, minimum_valid_track_length,
                      frame_num_selected_for_epipolar_matching);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalOptimizer::Parameters GlobalOptimizer::Parameters::Example()
{
    // create loop_detector_params
    const auto loop_detector_params = LoopDetector::Parameters::Example();

    Vector6 bias_between_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);

    Vector3 velocity_factor_sigma(0.1, 0.1, 0.1);

    Vector3 velocity_factor_sigma_when_turns(0.1, 0.1, 0.1);

    Vector6 wheel_integration_factor_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);

    Vector6 zero_velocity_between_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);

    Vector6 loop_closing_between_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);

    Vector6 prior_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);

    Vector3 prior_velocity_sigma(0.1, 0.1, 0.1);

    Vector6 prior_bias_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);

    Vector6 gt_pose_sigma(0.0017, 0.0017, 0.0017, 0.005, 0.005, 0.005);

    Vector3 vertex_factor_sigma(0.1, 0.1, 0.1);

    Vector3 plane_factor_sigma(0.1, 0.1, 0.1);

    Vector1 point_plane_factor_sigma(0.1);

    Vector3 parallel_factor_sigma(0.1, 0.1, 0.1);

    const Sigmas sigmas(bias_between_sigma, velocity_factor_sigma, velocity_factor_sigma_when_turns,
                        wheel_integration_factor_sigma, zero_velocity_between_pose_sigma,
                        loop_closing_between_pose_sigma, prior_pose_sigma, prior_velocity_sigma, prior_bias_sigma,
                        gt_pose_sigma, vertex_factor_sigma, plane_factor_sigma, point_plane_factor_sigma,
                        parallel_factor_sigma);

    // create imu preintegration parameters
    const Scalar gravity(9.81);
    auto         pim_params_example = gtsam::PreintegrationParams::MakeSharedU(gravity);
    {
        const gtsam::Matrix3 cov = 1e-8 * gtsam::Matrix3::Identity();
        pim_params_example->setGyroscopeCovariance(cov);
        pim_params_example->setAccelerometerCovariance(cov);
        pim_params_example->setIntegrationCovariance(cov);
    }

    return Parameters(loop_detector_params, Triangulator::Parameters::Example(), sigmas, pim_params_example);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalOptimizer::GlobalOptimizer(const Parameters& parameters)
  : parameters_(parameters), offline_mapping_progress_(0U), map_quality_(255U)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalOptimizer::OptimizedResults GlobalOptimizer::SingleMapOptimization(const MappingDatabase& mapping_database)
{
    // load values, tracks and sensor measurements from offline database
    const auto old_values          = mapping_database.xvb_values;
    auto       old_tracks_database = mapping_database.tracks_database;

    // triangulate candidate tracks
    old_tracks_database = TriangulateTracks(old_tracks_database, old_values);

    // create frame from tracks and values
    TicTocTimer timer_step;
    timer_step.Tic();
    const auto old_frames_database = CreateFramesDatabase(mapping_database);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- CreateFramesDatabase takes " << timer_step.Elapsed()
                                      << " s";
    offline_mapping_progress_ = 1U;

    // local map association
    FramesDatabase new_frames_database;
    TracksDatabase new_tracks_database;
    timer_step.Tic();
    std::tie(new_frames_database, new_tracks_database) = LocalMapAssociation(old_frames_database, old_tracks_database);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- LocalMapAssociation takes " << timer_step.Elapsed()
                                      << " s";
    offline_mapping_progress_ = 2U;

    // create loop detector
    LoopDetector loop_detector(parameters_.loop_detector_parames, new_frames_database);

    // loop detection and geometric consistency checking
    timer_step.Tic();
    LoopClosingResults loop_detection_result;

    if (parameters_.enable_loop_detection)
    {
        loop_detection_result =
            LoopDetectionAndGeometricChecking(loop_detector, new_frames_database, new_tracks_database);
    }
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- LoopDetectionAndGeometricChecking takes "
                                      << timer_step.Elapsed() << " s";
    offline_mapping_progress_ = 3U;

    // merge tracks according to the loop closing association result
    timer_step.Tic();
    new_tracks_database = FeatureTracksMerging(new_frames_database, new_tracks_database, loop_detection_result);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- FeatureTracksMerging takes " << timer_step.Elapsed()
                                      << " s";
    offline_mapping_progress_ = 4U;

    // build factor graph from sensor measurement. this factor graph does not contain visual factor.
    timer_step.Tic();
    FactorGraph new_factor_graph;
    new_factor_graph.reserve(100000);
    BuildSequentialFactorGraphFromMappingDatabase(mapping_database, new_factor_graph);

    // add prior factors to factor graph
    AddPriorFactor(mapping_database, new_factor_graph);

    // add loop constraint and visual factors to factor graph
    std::set<holo::uint64_t> landmark_ids = AddVisualFactorAndLoopConstraintsToGraph(
        new_factor_graph, old_values, new_frames_database, new_tracks_database, loop_detection_result);

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- Landmark number to be optimization : "
                                      << landmark_ids.size() << ", all tracks number : " << new_tracks_database.Size();

    // add landmarks' position to values
    auto new_values = AddLandmarksToValues(landmark_ids, old_values, new_tracks_database);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- FactorGraphBuilding takes " << timer_step.Elapsed()
                                      << " s";
    offline_mapping_progress_ = 5U;

    // global bundle adjustment
    timer_step.Tic();
    new_values = GlobalBundleAdjustment(new_factor_graph, new_values);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- GlobalBundleAdjustment takes " << timer_step.Elapsed()
                                      << " s";
    // check inliers
    timer_step.Tic();
    new_values = RemoveOutlierLandmarksFromValue(new_values, new_tracks_database);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- RemoveOutlierLandmarksFromValue takes "
                                      << timer_step.Elapsed() << " s";

    offline_mapping_progress_ = 6U;

    timer_step.Tic();
    new_tracks_database = TriangulateTracks(new_tracks_database, new_values, false);
    new_values          = UpdateLandmarksValues(new_values, new_tracks_database);
    new_frames_database = CreateFramesDatabaseFromTracks(new_values, new_tracks_database);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- Post process takes  " << timer_step.Elapsed() << " s";

    timer_step.Tic();
    const auto parking_slot_values = ParkingSlotOptimization(new_values, mapping_database);
    new_values.insert(parking_slot_values);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- Parking slot map optimization takes "
                                      << timer_step.Elapsed() << " s";

    offline_mapping_progress_ = 7U;

    /// sfm again with EpipolarLineMatching after optimization process is done
    timer_step.Tic();
    new_tracks_database =
        FindMoreMappointsInFrame(old_frames_database, new_frames_database, new_values, new_tracks_database);
    new_values          = UpdateLandmarksValues(new_values, new_tracks_database);
    new_frames_database = CreateFramesDatabaseFromTracks(new_values, new_tracks_database);
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- FindMoreMappointsInFrame takes " << timer_step.Elapsed()
                                      << " s";

    return OptimizedResults(new_frames_database, new_tracks_database, new_values, loop_detection_result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GlobalOptimizer::ParkingSlotOptimization(const Values& new_values, const MappingDatabase& mapping_database)
{
    // construct pose spline
    const auto pose_spline = ConstructPoseSpline(mapping_database, new_values);

    std::pair<FactorGraph, Values> semantic_problem =
        AddSemanticFactor(pose_spline, mapping_database.parking_slot_tracks_database);

    // parking slot global bundle adjustment
    semantic_problem.second = GlobalBundleAdjustment(semantic_problem.first, semantic_problem.second);

    return semantic_problem.second;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline GlobalOptimizer::ConstructPoseSpline(const MappingDatabase& mapping_database, const Values& new_values) const
{
    std::vector<Timestamp> timestamps;
    std::vector<Pose3>     poses;
    for (const auto& timestamp_to_frame_id : mapping_database.timestamp_to_frame_id)
    {
        timestamps.push_back(timestamp_to_frame_id.first);
        const auto pose = new_values.at(X(timestamp_to_frame_id.second)).cast<gtsam::Pose3>();
        poses.push_back(HoloGtsam::Convert(pose));
    }

    return PoseSpline(timestamps, poses);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalOptimizer::MultiMapMerging(const MapDatabaseManager& map_database_manager) const
{
    const auto& mapping_databases = map_database_manager.GetMappingDatabases();

    // hashing each mapping_databases' frame id and landmark id, get new_mapping_databases
    std::vector<MappingDatabase> hashed_mapping_databases;
    std::vector<FramesDatabase>  hashed_frames_databases;
    std::vector<TracksDatabase>  hashed_tracks_databases;

    Values          new_values;
    FactorGraph     global_factor_graph;
    MappingDatabase global_mapping_database;

    for (auto it = mapping_databases.begin(); it != mapping_databases.end(); it++)
    {
        const auto& mapping_database = it->second;
        LOG(INFO) << "map id: " << mapping_database.map_id;

        // hash local mapping  database for merging
        const auto hashed_mapping_database = HashMappingDatabaseForMerge(mapping_database, global_mapping_database);
        const auto old_tracks_database     = hashed_mapping_database.tracks_database;

        // create frame from tracks and values
        const auto old_frames_database = CreateFramesDatabase(hashed_mapping_database);

        // local map association
        FramesDatabase new_frames_database;
        TracksDatabase new_tracks_database;
        std::tie(new_frames_database, new_tracks_database) =
            LocalMapAssociation(old_frames_database, old_tracks_database);

        hashed_tracks_databases.push_back(new_tracks_database);
        hashed_frames_databases.push_back(new_frames_database);

        // build sequential factors for each new_mapping_database.(imu factor, velocity factor, between pose factor,
        // bias factor, etc. no prior factor, visual projection factor and loop closing between pose factor)
        FactorGraph local_factor_graph;
        BuildSequentialFactorGraphFromMappingDatabase(hashed_mapping_database, local_factor_graph);

        // add prior factor for first frame
        if (mapping_database.map_id == 0)
        {
            AddPriorFactor(hashed_mapping_database, local_factor_graph);
        }

        global_factor_graph.add(local_factor_graph);
    }

    global_mapping_database.map_id            = mapping_databases.size();
    global_mapping_database.camera_parameters = mapping_databases.begin()->second.camera_parameters;

    // create global frame and track database from multi frame and track databases
    FramesDatabase global_frames_database(hashed_frames_databases);
    TracksDatabase global_tracks_database(hashed_tracks_databases);

    // create loop detector
    LoopDetector loop_detector(parameters_.loop_detector_parames, global_frames_database);

    // loop detection and geometric consistency checking
    const auto loop_detection_result =
        LoopDetectionAndGeometricChecking(loop_detector, global_frames_database, global_tracks_database);

    const auto unmerged_tracks_database = global_tracks_database;
    const auto unmerged_frames_database = global_frames_database;

    // merge tracks according to the loop closing association result
    global_tracks_database =
        FeatureTracksMerging(global_frames_database, global_tracks_database, loop_detection_result);

    if (loop_detection_result.size() > 0 && mapping_databases.size() > 1)
    {
        QueryMapToTrainMapTransformPairs transforms =
            FindTheBestTransformBetweenTwoMaps(global_frames_database, loop_detection_result);

        const auto loop_map_ids_of_each_map = FindLoopCandidatesForEachMap(transforms);

        global_tracks_database =
            TransformAllLandmarksToTargetCoordinate(global_tracks_database, transforms, loop_map_ids_of_each_map);

        std::tie(new_values, global_frames_database) = TransformAllFramePoseToTargetCoordinate(
            global_mapping_database.xvb_values, global_frames_database, transforms, loop_map_ids_of_each_map);

        if (parameters_.enable_visualizer)
        {
            DrawMappingMergeLoop(loop_detection_result, global_tracks_database, unmerged_tracks_database,
                                 global_frames_database, unmerged_frames_database, mapping_databases.size());
        }
    }

    // add loop constraint and visual factors to factor graph
    AddVisualFactorAndLoopConstraintsToGraph(global_factor_graph, global_mapping_database.xvb_values,
                                             global_frames_database, global_tracks_database, loop_detection_result);

    // add landmarks' position to values
    new_values = AddLandmarksToValues(new_values, global_tracks_database);

    // global bundle adjustment
    new_values = GlobalBundleAdjustment(global_factor_graph, new_values);

    // check inliers
    new_values = RemoveOutlierLandmarksFromValue(new_values, global_tracks_database);

    // save the optimized result
    map_database_manager.SaveTheMergedMapAfterOptimizing(new_values, global_frames_database, global_mapping_database,
                                                         global_tracks_database, "multi_map_merging");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalOptimizer::Run(const MapDatabaseManager& map_database_manager)
{
    const auto& mapping_databases = map_database_manager.GetMappingDatabases();
    LOG(INFO) << "GlobalOptimizer --- start process mapping database, database number: " << mapping_databases.size();

    if (parameters_.mode == "single_map_optimization")
    {
        // process map data one by one
        for (const auto& item : mapping_databases)
        {
            TicTocTimer timer;
            timer.Tic();
            const auto& map_name         = item.first;
            const auto& mapping_database = item.second;

            // optimize this map
            LOG(INFO) << "GlobalOptimizer --- start process: " << map_name;
            const auto optimized_result = SingleMapOptimization(mapping_database);
            LOG(INFO) << "GlobalOptimizer --- optimize " << map_name << " done.\n";

            // save the optimized result and evaluate map quality
            LOG(INFO) << "GlobalOptimizer --- start save and evaluate the quality of the optimized map ...\n";
            const auto quality = map_database_manager.SaveAndEvaluateQualityOfTheOptimizedMap(
                optimized_result.optimized_values, optimized_result.frames_database, map_name,
                optimized_result.tracks_database);
            LOG(INFO) << "GlobalOptimizer --- save and evaluate quality of the optimized map done. the quality is: "
                      << static_cast<uint16_t>(quality) << "\n";
            map_quality_ = static_cast<uint8_t>(quality);

            LOG(INFO) << "GlobalOptimizer --- process " << map_name << " done.\n";
            LOG(INFO) << "GlobalOptimizer --- process " << map_name << " takes " << timer.Elapsed() << " s.\n";
            offline_mapping_progress_ = 8U;
        }
    }
    else if (parameters_.mode == "multi_map_merging")
    {
        // optimize this map
        LOG(INFO) << "GlobalOptimizer --- start multi map merging ...\n";
        MultiMapMerging(map_database_manager);
        LOG(INFO) << "GlobalOptimizer --- optimize multi map merging done.\n";
    }
    else
    {
        LOG(ERROR) << "GlobalOptimizer --- unsupported mode: " << parameters_.mode << "\n";
        throw std::runtime_error("GlobalOptimizer --- unsupported mode.");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::uint8_t GlobalOptimizer::GetMappingProgress() const
{
    return offline_mapping_progress_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::uint8_t GlobalOptimizer::GetMappingResultQuality() const
{
    return map_quality_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FramesDatabase GlobalOptimizer::CreateFramesDatabaseFromTracks(const Values&         values,
                                                               const TracksDatabase& track_database) const
{
    std::unordered_map<uint64_t, Frame> indexed_frames;

    // loop all tracks
    for (const auto& indexed_track : track_database.GetAllTracks())
    {
        const auto& lm_id = indexed_track.first;
        const auto& track = indexed_track.second;

        const auto& camera_parameters = track.CameraParams();

        // loop all measurement of this track
        for (const auto& m : track.Measurements())
        {
            // get associated frame id
            const auto& frame_id = m.first;

            // check if this frame exist in values
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "CreateFramesDatabase --- frame " << frame_id << " does NOT exist in values.";
                throw std::runtime_error("frame which associated to this track does NOT exist in values\n");
            }

            // check if this is a new frame
            if (!indexed_frames.count(frame_id))
            {
                indexed_frames.emplace(frame_id, Frame(frame_id, camera_parameters));

                // get vehicle pose of this new frame
                const auto T_wb = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());

                // get pose and image for all camera.
                for (size_t camera_index = 0; camera_index < camera_parameters->camera_number; camera_index++)
                {
                    // add camera pose for this camera
                    const auto& T_bc = camera_parameters->extrinsics.at(camera_index);
                    indexed_frames[frame_id].multi_camera_data[camera_index].pose = T_wb * T_bc;
                }
            }

            // loop all camera
            for (size_t camera_index = 0; camera_index < camera_parameters->camera_number; camera_index++)
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
    FramesDatabase frame_database;

    for (const auto& indexed_frame : indexed_frames)
    {
        frame_database.AddFrame(indexed_frame.second);
    }

    return frame_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FramesDatabase GlobalOptimizer::CreateFramesDatabase(const MappingDatabase& mapping_database) const
{
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- CreateFramesDatabase is running ...\n";
    const auto&                         values = mapping_database.xvb_values;
    const auto&                         images = mapping_database.images;
    std::unordered_map<uint64_t, Frame> indexed_frames;

    // select keyframe
    std::set<uint64_t> keyframe_ids;

    for (const auto& frame_id_to_timestamp : mapping_database.frame_id_to_timestamp)
    {
        const auto& frame_id = frame_id_to_timestamp.first;

        // retrieve pose and velocity from values.
        if (!values.exists(X(frame_id)))
        {
            continue;
        }

        if (!mapping_database.frame_indexed_features.count(frame_id))
        {
            continue;
        }

        keyframe_ids.insert(frame_id);
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- Total frame number = "
                                      << mapping_database.frame_id_to_timestamp.size()
                                      << ", keyframe number = " << keyframe_ids.size();

    // loop all tracks
    for (const auto& indexed_track : mapping_database.tracks_database.GetAllTracks())
    {
        const auto& lm_id = indexed_track.first;
        const auto& track = indexed_track.second;

        // loop all measurement of this track
        for (const auto& m : track.Measurements())
        {
            // get associated frame id
            const auto& frame_id = m.first;

            // check if this frame exist in values
            if (!values.exists(X(frame_id)))
            {
                LOG(ERROR) << "CreateFramesDatabase --- frame " << frame_id << " does NOT exist in values.";
                throw std::runtime_error("frame which associated to this track does NOT exist in values\n");
            }

            // check if this is a new frame
            if (!indexed_frames.count(frame_id))
            {
                indexed_frames.emplace(frame_id, Frame(frame_id, mapping_database.camera_parameters));

                // get vehicle pose of this new frame
                const auto T_wb = HoloGtsam::Convert(values.at(X(frame_id)).cast<gtsam::Pose3>());

                // get pose and image for all camera.
                for (size_t camera_index = 0; camera_index < mapping_database.camera_parameters->camera_number;
                     camera_index++)
                {
                    // add camera pose for this camera
                    const auto& T_bc = mapping_database.camera_parameters->extrinsics.at(camera_index);
                    indexed_frames[frame_id].multi_camera_data[camera_index].pose = T_wb * T_bc;

                    // get image name for reading image from disk.
                    if (images.empty() || !images.count(frame_id) || !images.at(frame_id).count(camera_index))
                    {
                        continue;
                    }

                    indexed_frames[frame_id].multi_camera_data[camera_index].image_name =
                        images.at(frame_id).at(camera_index);
                }
            }

            // loop all camera
            for (size_t camera_index = 0; camera_index < mapping_database.camera_parameters->camera_number;
                 camera_index++)
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

    // add more features for each frame
    std::vector<Frame> frames;
    frames.reserve(indexed_frames.size());

    for (const auto& indexed_frame : indexed_frames)
    {
        if (!keyframe_ids.count(indexed_frame.first))
        {
            continue;
        }

        frames.emplace_back(indexed_frame.second);
    }

    FramesDatabase database = AddUntrackedFeaturesToEachFrame(frames, mapping_database.frame_indexed_features);

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- CreateFramesDatabase done. total frames number: "
                                      << database.Size() << ".";

    return database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t GlobalOptimizer::BoundaryClamp(const int32_t value, const int32_t min, const int32_t max) const
{
    int32_t result = value < min ? min : value;
    result         = result > max ? max : result;

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FramesDatabase GlobalOptimizer::AddUntrackedFeaturesToEachFrame(
    const std::vector<Frame>& frames, const FrameIndexedFeatures& frame_indexed_features) const
{
    FramesDatabase database;
    uint64_t       processed_frame = 0;

    if (frames.empty())
    {
        LOG(WARNING) << "AddUntrackedFeaturesToEachFrame --- given frames is empty.\n";
        return database;
    }

    // create undistorters to distort / undistort points
    auto undistorters = Utility::CreateImageUndistorters(frames.front().camera_parameters->intrinsics);

    for (Frame frame : frames)
    {
        if (!frame_indexed_features.count(frame.frame_id))
        {
            continue;
        }
        auto& multi_camera_data = frame.multi_camera_data;

        // process all camera data
        for (size_t camera_index = 0; camera_index < multi_camera_data.size(); camera_index++)
        {
            const auto& intrinsic    = frame.camera_parameters->intrinsics.at(camera_index);
            const auto& image_width  = frame.camera_parameters->intrinsics.at(camera_index)->GetWidth();
            const auto& image_height = frame.camera_parameters->intrinsics.at(camera_index)->GetHeight();
            cv::Mat     roi(image_height, image_width, CV_8UC1, cv::Scalar(0));

            auto& features             = multi_camera_data.at(camera_index).features;
            auto& associated_landmarks = multi_camera_data.at(camera_index).associated_landmarks;

            // create mask arount exist features for feature extraction
            for (const auto& ft : features)
            {
                Point2 distorted_point(ft.image_point.x, ft.image_point.y);

                // distorte this point to create mask in original image
                if (intrinsic->GetModel() == Model::PINHOLE)
                {
                    PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());

                    if (!pinhole)
                    {
                        LOG(ERROR)
                            << "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to pinhole type";
                        throw std::runtime_error(
                            "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to pinhole type");
                    }
                    std::vector<Point2> undistorted_points{distorted_point}, distorted_points;
                    pinhole->DistortPoints(undistorted_points, distorted_points);
                    distorted_point = distorted_points.front();
                }
                else if (intrinsic->GetModel() == Model::FISHEYE)
                {
                    FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());

                    if (!fisheye)
                    {
                        LOG(ERROR)
                            << "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to fisheye type";
                        throw std::runtime_error(
                            "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to fisheye type");
                    }
                    std::vector<Point2> undistorted_points{distorted_point}, distorted_points;
                    fisheye->DistortPoints(undistorted_points, distorted_points);
                    distorted_point = distorted_points.front();
                }

                const int32_t x = static_cast<int32_t>(distorted_point.GetX());
                const int32_t y = static_cast<int32_t>(distorted_point.GetY());

                const int32_t minimum_feature_distance = 30.0;

                int32_t xmin = BoundaryClamp(x - minimum_feature_distance, 0, image_width - 1);
                int32_t xmax = BoundaryClamp(x + minimum_feature_distance, 0, image_width - 1);
                int32_t ymin = BoundaryClamp(y - minimum_feature_distance, 0, image_height - 1);
                int32_t ymax = BoundaryClamp(y + minimum_feature_distance, 0, image_height - 1);

                cv::Range row_range(ymin, ymax);
                cv::Range col_range(xmin, xmax);
                roi(row_range, col_range) = 250;
            }

            // retrieve untracked features
            const auto untracked_features = frame_indexed_features.at(frame.frame_id).at(camera_index);

            // record new features
            features.reserve(features.size() + untracked_features.size());
            associated_landmarks.reserve(associated_landmarks.size() + untracked_features.size());

            for (const auto& ft : untracked_features)
            {
                Point2 distorted_point(ft.image_point.x, ft.image_point.y);

                // distorte this point to create mask in original image
                if (intrinsic->GetModel() == Model::PINHOLE)
                {
                    PinholeIntrinsicType const* pinhole = dynamic_cast<PinholeIntrinsicType const*>(intrinsic.get());

                    if (!pinhole)
                    {
                        LOG(ERROR)
                            << "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to pinhole type";
                        throw std::runtime_error(
                            "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to pinhole type");
                    }
                    std::vector<Point2> undistorted_points{distorted_point}, distorted_points;
                    pinhole->DistortPoints(undistorted_points, distorted_points);
                    distorted_point = distorted_points.front();
                }
                else if (intrinsic->GetModel() == Model::FISHEYE)
                {
                    FisheyeIntrinsicType const* fisheye = dynamic_cast<FisheyeIntrinsicType const*>(intrinsic.get());

                    if (!fisheye)
                    {
                        LOG(ERROR)
                            << "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to fisheye type";
                        throw std::runtime_error(
                            "AddUntrackedFeaturesToEachFrame --- failed to cast source intrinsic to fisheye type");
                    }
                    std::vector<Point2> undistorted_points{distorted_point}, distorted_points;
                    fisheye->DistortPoints(undistorted_points, distorted_points);
                    distorted_point = distorted_points.front();
                }

                if (roi.at<uchar>(cv::Point2f(distorted_point.GetX(), distorted_point.GetY())) == 250)
                {
                    continue;
                }

                features.emplace_back(ft);
                associated_landmarks.emplace_back(-1);
            }
        }

        processed_frame++;
        database.AddFrame(frame);

        if (parameters_.verbose)
        {
            LOG_EVERY_N(INFO, 50) << "GlobalOptimizer --- feature extraction is running, processed frames:"
                                  << processed_frame << ", total frames: " << frames.size()
                                  << ", Progress: " << 100.0 * processed_frame / frames.size() << " %.\n";
        }
    }

    return database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::tuple<FramesDatabase, TracksDatabase, GlobalOptimizer::LandmarkIdPairs>
GlobalOptimizer::LocalMapMatchingAndTracksExtending(const FramesDatabase& frames_database,
                                                    const TracksDatabase& tracks_database) const
{
    LandmarkIdPairs associated_landmark_id_pairs;
    FramesDatabase  new_frames_database;
    TracksDatabase  new_tracks_database;
    uint64_t        processed_frame = 0;

    // traversal all frames
    for (const auto& indexed_frame : frames_database.GetAllFrames())
    {
        const auto& query_frame             = indexed_frame.second;
        const auto& query_multi_camera_data = query_frame.multi_camera_data;
        const auto& query_frame_id          = query_frame.frame_id;
        const auto& camera_parameters       = query_frame.camera_parameters;

        // create new frame
        Frame new_frame = query_frame;

        // traversal all camera
        for (uint16_t query_camera_index = 0; query_camera_index < camera_parameters->camera_number;
             query_camera_index++)
        {
            // query covisibility frames
            std::unordered_map<uint64_t, uint16_t> covisibility_frames =
                QueryCovisibilityFrames(frames_database, tracks_database, query_frame_id, query_camera_index);

            // remove query_frame from covisibility frames if it present
            if (covisibility_frames.count(query_frame_id))
            {
                covisibility_frames.erase(query_frame_id);
            }

            // query covisibility map
            const auto covisibility_map =
                QueryCovisibilityMap(frames_database, tracks_database, covisibility_frames, query_camera_index,
                                     parameters_.f2cmc_params.min_covisibility_intensity);

            // feature association with covisibility map
            std::vector<uint64_t> train_landmark_ids;
            train_landmark_ids.reserve(covisibility_map.size());
            Map map;
            map.reserve(covisibility_map.size());
            for (const auto& data : covisibility_map)
            {
                train_landmark_ids.emplace_back(data.first);
                map.emplace_back(std::make_shared<MapPoint>(data.second));
            }

            /**
             * @details Since the pose and landmark position is almost locally consistent after the online
             * estimation. we match the local map by project all mappoint to frames with the online estimated pose
             * and position. then search candidate features at a relatively near window.
             */
            const auto&  intrinsic      = camera_parameters->intrinsics.at(query_camera_index);
            const auto&  query_features = query_multi_camera_data.at(query_camera_index).features;
            const auto&  query_pose     = query_multi_camera_data.at(query_camera_index).pose;
            const Scalar window_size = 5.0, descriptor_dist_th = 1.0, ratio_test_th = 1.0, view_distance_th = 25.0,
                         view_direction_th = 20.0;
            const auto match_pair          = DescriptorMatcher::MappointsToFeaturesMatching(
                std::make_shared<const Map>(map), query_features, intrinsic, query_pose, window_size,
                descriptor_dist_th, ratio_test_th, view_distance_th, view_direction_th);

            auto query_landmark_ids = query_multi_camera_data.at(query_camera_index).associated_landmarks;

            // record matched result
            for (const auto& pair : match_pair)
            {
                const uint64_t train_lm_id = train_landmark_ids.at(pair.first);
                const uint64_t query_lm_id = query_landmark_ids.at(pair.second);

                if (query_lm_id > 0 && tracks_database.Exists(query_lm_id))
                {
                    associated_landmark_id_pairs.push_back(std::make_pair(train_lm_id, query_lm_id));
                    continue;
                }

                // update tracks measurement
                auto track = tracks_database.GetTrack(train_lm_id);
                track.AddNewestMeasurement(query_frame_id, query_features.at(pair.second));

                if (new_tracks_database.Exists(train_lm_id))
                {
                    new_tracks_database.UpdateFeatureTrack(train_lm_id, query_frame_id, query_features.at(pair.second));
                }
                else
                {
                    new_tracks_database.AddFeatureTrack(track);
                }

                query_landmark_ids[pair.second] = train_lm_id;
            }

            // update the associated_landmarks of query frame
            new_frame.multi_camera_data[query_camera_index].associated_landmarks = query_landmark_ids;
        }

        processed_frame++;

        if (parameters_.verbose)
        {
            LOG_EVERY_N(INFO, 50)
                << "GlobalOptimizer --- local map matching and tracks extending running, processed frames:"
                << processed_frame << ", total frames: " << frames_database.Size()
                << ", Progress: " << 100.0 * processed_frame / frames_database.Size() << " %.\n";
        }

        // add new frame to new frames database
        new_frames_database.AddFrame(new_frame);
    }

    // move other tracks from old tracks database to new tracks database
    for (const auto& indexed_track : tracks_database.GetAllTracks())
    {
        const auto& lm_id = indexed_track.first;
        if (new_tracks_database.Exists(lm_id))
        {
            continue;
        }

        new_tracks_database.AddFeatureTrack(indexed_track.second);
    }

    return std::tuple<FramesDatabase, TracksDatabase, LandmarkIdPairs>(new_frames_database, new_tracks_database,
                                                                       associated_landmark_id_pairs);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<FramesDatabase, TracksDatabase>
GlobalOptimizer::LocalMapAssociation(const FramesDatabase& frames_database, const TracksDatabase& tracks_database) const
{
    // local map matching and extend track's measurement
    FramesDatabase  new_frames_database;
    TracksDatabase  new_tracks_database;
    LandmarkIdPairs associated_landmark_id_pairs;
    std::tie(new_frames_database, new_tracks_database, associated_landmark_id_pairs) =
        LocalMapMatchingAndTracksExtending(frames_database, tracks_database);

    // clustering associated landmark pairs
    const auto landmark_sets = ClusteringAssociatedLandmarkIds(associated_landmark_id_pairs);

    // record removed landmarks id and its corresponding retained landmark ids
    // key: removed landmark id, value: matched landmark id which retained in database
    std::unordered_map<uint64_t, uint64_t> removed_landmark_ids;

    // merge associated ladnmark pairs
    for (const auto& lm_set : landmark_sets)
    {
        // retain tracks with smallest id
        const uint64_t retained_lm_id = *lm_set.begin();
        auto           retained_track = new_tracks_database.GetTrack(retained_lm_id);

        for (const auto& lm_id : lm_set)
        {
            if (lm_id == retained_lm_id)
            {
                continue;
            }

            auto removed_track = new_tracks_database.GetTrack(lm_id);

            // add all removed track's measurement to retained track
            for (const auto& m : removed_track.Measurements())
            {
                const auto& frame_id = m.first;

                for (const auto& camera_indexed_feature : m.second)
                {
                    const auto& feature = camera_indexed_feature.second;
                    retained_track.AddNewestMeasurement(frame_id, feature);
                }
            }

            removed_landmark_ids.emplace(lm_id, retained_lm_id);
            new_tracks_database.Erase(lm_id);
        }

        new_tracks_database.UpdateFeatureTrack(retained_lm_id, retained_track);
    }

    auto& new_indexed_frames = new_frames_database.GetAllFrames();

    // update associated landmarks in frame
    for (auto& indexed_frame : new_indexed_frames)
    {
        auto& multi_camera_data = indexed_frame.second.multi_camera_data;

        // traversal all camera
        for (uint16_t camera_index = 0; camera_index < multi_camera_data.size(); camera_index++)
        {
            auto& landmark_ids = multi_camera_data.at(camera_index).associated_landmarks;

            for (size_t i = 0; i < landmark_ids.size(); i++)
            {
                const auto& lm_id = landmark_ids.at(i);

                // check if this landmark be removed
                if (!removed_landmark_ids.count(lm_id))
                {
                    continue;
                }

                // this landmark id was removed. get the corresponding retained one and associated again.
                landmark_ids[i] = removed_landmark_ids.at(lm_id);
            }
        }
    }

    return std::make_pair(new_frames_database, new_tracks_database);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase GlobalOptimizer::TriangulateTracks(const TracksDatabase& tracks_database, const Values& values,
                                                  holo::bool_t only_candiate_track) const
{
    LOG(INFO) << "GlobalOptimizer --- start triangulate candidate tracks ...\n";
    LOG(INFO) << "GlobalOptimizer --- total track number = " << tracks_database.Size() << "\n";
    const auto&    all_tracks          = tracks_database.GetAllTracks();
    uint64_t       processed_track_num = 0;
    uint64_t       candidate_num = 0, success_num = 0;
    TracksDatabase new_track_database;

    // loop for all tracks
    for (const auto& iter : all_tracks)
    {
        const auto& track = iter.second;

        /// check if associated landmark is exists in values
        if (track.GetLandmark() && values.exists(L(track.GetLandmark()->Id())))
        {
            new_track_database.AddFeatureTrack(track);
            continue;
        }

        // check if its a CANDIDATE track
        if (only_candiate_track && track.GetState() != FeatureTrack::State::CANDIDATE)
        {
            new_track_database.AddFeatureTrack(track);
            continue;
        }

        // construct a triangulator
        candidate_num++;
        Triangulator triangulator(parameters_.triangulator_params, track.CameraParams());

        const auto optional_point = triangulator.Run(track, values);

        if (!optional_point)
        {
            continue;
        }

        success_num++;
        gtsam::Point3 gt_ptw(optional_point->GetX(), optional_point->GetY(), optional_point->GetZ());
        new_track_database.AddFeatureTrack(track.CreateNewTrackByUpdatingState(FeatureTrack::State::FRESH, gt_ptw));
        processed_track_num++;
    }

    LOG(INFO) << "GlobalOptimizer --- triangulation info, candidate_num = " << candidate_num
              << ", success_num = " << success_num << "\n";
    LOG(INFO) << "GlobalOptimizer --- triangulate candidate tracks done.\n";

    return new_track_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalOptimizer::PnpResult GlobalOptimizer::SolvePNP(const std::vector<cv::Point3d>& point3d,
                                                     const std::vector<cv::Point2d>& point2d, const cv::Mat& K) const
{
    cv::Mat               R, r, t;
    std::vector<uint16_t> inliers;

    if (!cv::solvePnPRansac(point3d, point2d, K, cv::Mat(), r, t, false,
                            parameters_.f2fc_params.ransanc_iterations_number,
                            parameters_.f2fc_params.projection_error_threshold, parameters_.f2fc_params.confidence,
                            inliers, cv::SOLVEPNP_EPNP))
    {
        return PnpResult(boost::none, std::vector<uint16_t>());
    }

    // check inliers num
    if (inliers.size() < parameters_.f2fc_params.minimum_inliers_number)
    {
        return PnpResult(boost::none, std::vector<uint16_t>());
    }

    cv::Rodrigues(r, R);
    gtsam::Matrix3 rotation;
    cv::cv2eigen(R, rotation);
    const Pose3 T_cw(Rot3(HoloGtsam::Convert(rotation)),
                     Point3(t.at<float64_t>(0), t.at<float64_t>(1), t.at<float64_t>(2)));
    const Pose3 T_wc = T_cw.Inverse();

    return PnpResult(T_wc, inliers);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<GlobalOptimizer::LoopClosingResult>
GlobalOptimizer::FrameToFrameChecking(const FramesDatabase& frames_database, const TracksDatabase& tracks_database,
                                      const CandidatesLoop& candidates) const
{
    LoopClosingResults results;
    // retrieve query frame's information from candidates
    const uint64_t       query_frame_id     = candidates.query_frame.first;
    const uint16_t       query_camera_index = candidates.query_frame.second;
    const auto&          query_frame        = frames_database.GetFrame(query_frame_id);
    const auto&          query_features     = query_frame.multi_camera_data.at(query_camera_index).features;
    const auto&          query_lm_ids       = query_frame.multi_camera_data.at(query_camera_index).associated_landmarks;
    std::vector<cv::Mat> query_descs;
    query_descs.reserve(query_features.size());
    std::pair<uint64_t, uint64_t> query_map_id_frame_id(0, query_frame_id);

    if (frames_database.IsFromMultiDatabaseMerging())
    {
        query_map_id_frame_id = Utility::UnHashId((uint64_t)query_frame_id);
    }

    // retrieve descriptor for feature matching
    for (size_t i = 0; i < query_features.size(); i++)
    {
        query_descs.emplace_back(*query_features.at(i).optional_descriptor);
    }

    // loop for all candidate train frame
    for (size_t i = 0; i < candidates.train_frames.size(); i++)
    {
        // const auto& score = candidates.scores.at(i);
        /// @todo(Feng. Li. 2020-03-04) set a reasonable threshold to check the similarity score.

        // retrieve train frame's information from candidates
        const uint64_t                train_frame_id = candidates.train_frames.at(i).first;
        std::pair<uint64_t, uint64_t> train_map_id_frame_id(0, train_frame_id);

        if (frames_database.IsFromMultiDatabaseMerging())
        {
            train_map_id_frame_id = Utility::UnHashId((uint64_t)train_frame_id);
        }

        // check if the time gap of these two frames in the same map are large enough.
        if (train_map_id_frame_id.first == query_map_id_frame_id.first &&
            (train_map_id_frame_id.second >= query_map_id_frame_id.second ||
             query_map_id_frame_id.second - train_map_id_frame_id.second <
                 (uint64_t)parameters_.f2fc_params.minimum_frame_interval))
        {
            continue;
        }

        const uint16_t train_camera_index = candidates.train_frames.at(i).second;
        const auto&    train_frame        = frames_database.GetFrame(train_frame_id);
        const auto&    train_features     = train_frame.multi_camera_data.at(train_camera_index).features;

        std::vector<cv::Mat>  train_descs;
        std::vector<uint64_t> train_lm_ids;
        train_descs.reserve(train_features.size());
        train_lm_ids.reserve(train_features.size());

        // retrieve descriptor for feature matching
        for (size_t j = 0; j < train_features.size(); j++)
        {
            const auto& lm_id = train_frame.multi_camera_data.at(train_camera_index).associated_landmarks.at(j);

            if (lm_id < 0 || !tracks_database.Exists(lm_id))
            {
                continue;
            }

            train_descs.emplace_back(*train_features.at(j).optional_descriptor);
            train_lm_ids.emplace_back(lm_id);
        }

        // feature matching
        const auto match_pairs = DescriptorMatcher::BruteForceMatching(train_descs, query_descs,
                                                                       parameters_.f2fc_params.descriptor_distance_th,
                                                                       parameters_.f2fc_params.ratio_test_th);

        // check num of matched feature
        if (match_pairs.size() < parameters_.f2fc_params.matches_threshold)
        {
            continue;
        }

        // retrieve 3d-2d correspondence
        std::vector<cv::Point3d> pts3;
        std::vector<cv::Point2d> pts2;

        for (const auto& pair : match_pairs)
        {
            const auto& train_index = pair.first;
            const auto& train_lm_id = train_lm_ids.at(train_index);
            const auto& point3      = tracks_database.GetTrack(train_lm_id).GetLandmark()->Point();
            pts3.push_back(cv::Point3d(point3.x(), point3.y(), point3.z()));

            const auto& query_index = pair.second;
            const auto& point2      = query_features.at(query_index).normalized_point;
            pts2.push_back(cv::Point2d(point2.GetX() / point2.GetZ(), point2.GetY() / point2.GetZ()));
        }

        // solve pnp
        cv::Mat        cv_K;
        gtsam::Matrix3 K = gtsam::Matrix3::Identity();
        cv::eigen2cv(K, cv_K);
        const auto pnp_result = SolvePNP(pts3, pts2, cv_K);

        if (!pnp_result.pose)
        {
            continue;
        }

        // get associated landmarks
        LandmarkIdPairs                            associated_landmarks;
        std::vector<std::pair<uint64_t, uint16_t>> train_lm_id_to_query_feature_index;
        associated_landmarks.reserve(pnp_result.inliers.size());
        train_lm_id_to_query_feature_index.reserve(pnp_result.inliers.size());

        for (size_t i = 0; i < pnp_result.inliers.size(); i++)
        {
            const uint16_t train_index = match_pairs.at(pnp_result.inliers[i]).first;
            const uint16_t query_index = match_pairs.at(pnp_result.inliers[i]).second;
            const uint64_t train_lm_id = train_lm_ids.at(train_index);
            const uint64_t query_lm_id = query_lm_ids.at(query_index);

            if (query_lm_id > 0 && tracks_database.Exists(query_lm_id))
            {
                associated_landmarks.emplace_back(train_lm_id, query_lm_id);
            }
            else
            {
                train_lm_id_to_query_feature_index.emplace_back(train_lm_id, query_index);
            }
        }

        LoopClosingResult result(std::make_pair(train_frame_id, train_camera_index),
                                 std::make_pair(query_frame_id, query_camera_index), *pnp_result.pose,
                                 associated_landmarks, train_lm_id_to_query_feature_index);
        results.push_back(result);
    }

    if (!results.empty())
    {
        // sort all result by inliers
        std::sort(results.begin(), results.end(), [](const LoopClosingResult& m0, const LoopClosingResult& m1) {
            return m0.associated_landmarks.size() + m0.train_lm_id_to_query_feature_index.size() <
                   m1.associated_landmarks.size() + m1.train_lm_id_to_query_feature_index.size();
        });

        return results.back();
    }

    return boost::none;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<uint64_t, uint16_t> GlobalOptimizer::QueryCovisibilityFrames(const FramesDatabase& frames_database,
                                                                                const TracksDatabase& tracks_database,
                                                                                const uint64_t        query_frame_id,
                                                                                const uint16_t query_camera_index) const
{
    std::unordered_map<uint64_t, uint16_t> covisibility_frames;

    const auto& query_frame  = frames_database.GetFrame(query_frame_id);
    const auto& landmark_ids = query_frame.multi_camera_data.at(query_camera_index).associated_landmarks;

    for (const auto& lm_id : landmark_ids)
    {
        if (lm_id < 0 || !tracks_database.Exists(lm_id))
        {
            continue;
        }

        const auto& track = tracks_database.GetTrack(lm_id);
        for (size_t i = 0; i < track.Length(); i++)
        {
            const auto frame_id = track.Measurements(i).first;
            if (!frames_database.Exists(frame_id))
            {
                continue;
            }
            if (covisibility_frames.count(frame_id))
            {
                covisibility_frames[frame_id]++;
            }
            else
            {
                covisibility_frames.emplace(frame_id, 1);
            }
        }
    }

    return covisibility_frames;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<uint64_t, MapPoint> GlobalOptimizer::QueryCovisibilityMap(
    const FramesDatabase& frames_database, const TracksDatabase& tracks_database,
    const std::unordered_map<uint64_t, uint16_t>& covisibility_frames, const uint16_t query_camera_index,
    const uint16_t min_covisibility_intensity) const
{
    // construct covisibility map
    std::unordered_map<uint64_t, MapPoint> covisibility_map;

    uint64_t cnt = 0;

    // loop all covisibility_frames
    for (const auto& indexed_frame : covisibility_frames)
    {
        const uint64_t covisibility_frame_id  = indexed_frame.first;
        const uint16_t covisibility_intensity = indexed_frame.second;

        // check if the min_covisibility_intensity is strong enough
        if (covisibility_intensity < min_covisibility_intensity)
        {
            continue;
        }

        const auto& covisibility_frame = frames_database.GetFrame(covisibility_frame_id);
        const auto& covisibility_lms = covisibility_frame.multi_camera_data.at(query_camera_index).associated_landmarks;

        for (const auto& lm_id : covisibility_lms)
        {
            if (lm_id < 0 || !tracks_database.Exists(lm_id))
            {
                continue;
            }

            if (covisibility_map.count(lm_id))
            {
                continue;
            }

            const auto& track              = tracks_database.GetTrack(lm_id);
            uint64_t    reference_frame_id = track.OldestMeasurement().first;
            size_t      i                  = 0;
            for (; i < track.Length(); ++i)
            {
                reference_frame_id = track.Measurements(i).first;
                if (frames_database.Exists(reference_frame_id))
                {
                    break;
                }
            }

            if (i == track.Length())
            {
                cnt++;
                continue;
            }

            const auto& reference_frame   = frames_database.GetFrame(reference_frame_id);
            const auto& reference_feature = track.Measurements(i).second.at(query_camera_index);
            const Pose3 T_wc              = reference_frame.multi_camera_data.at(query_camera_index).pose;
            const auto  direction         = T_wc.GetRotation().Rotate(reference_feature.normalized_point.ToVector());

            // create a new mappoint
            MapPoint mp;
            mp.position       = HoloGtsam::Convert(track.GetLandmark()->Point());
            mp.reference_pose = T_wc;
            mp.direction      = direction / direction.GetNorm();
            mp.descriptor     = *(reference_feature.optional_descriptor);
            covisibility_map.emplace(lm_id, mp);
        }
    }

    return covisibility_map;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<GlobalOptimizer::LoopClosingResult> GlobalOptimizer::FrameToCovisibilityMapChecking(
    const FramesDatabase& frames_database, const TracksDatabase& tracks_database,
    const LoopClosingResult& candidate_result) const
{
    const uint64_t train_frame_id     = candidate_result.train_frame.first;
    const uint16_t train_camera_index = candidate_result.train_frame.second;

    const uint64_t query_frame_id     = candidate_result.query_frame.first;
    const uint16_t query_camera_index = candidate_result.query_frame.second;
    const Frame&   query_frame        = frames_database.GetFrame(query_frame_id);

    // query train frame's covisibility frames
    std::unordered_map<uint64_t, uint16_t> covisibility_frames =
        QueryCovisibilityFrames(frames_database, tracks_database, train_frame_id, train_camera_index);

    // check if train_frame and query_frame already share enough landmarks
    if (covisibility_frames.count(query_frame_id))
    {
        const uint16_t covisibility_intensity = covisibility_frames.at(query_frame_id);
        if (covisibility_intensity > parameters_.f2cmc_params.max_covisibility_intensity)
        {
            return boost::none;
        }

        /// @todo(Feng. Li 2020-03-21) should we erase the query_frame from covisibility_frames?
        covisibility_frames.erase(query_frame_id);
    }

    // query train frame's covisibility map
    const auto covisibility_map =
        QueryCovisibilityMap(frames_database, tracks_database, covisibility_frames, train_camera_index,
                             parameters_.f2cmc_params.min_covisibility_intensity);

    // feature association with covisibility map
    std::vector<uint64_t> train_landmark_ids;
    Map                   map;
    for (const auto& data : covisibility_map)
    {
        train_landmark_ids.push_back(data.first);
        map.push_back(std::make_shared<MapPoint>(data.second));
    }

    const auto&  intrinsic      = query_frame.camera_parameters->intrinsics.at(query_camera_index);
    const auto&  query_features = query_frame.multi_camera_data.at(query_camera_index).features;
    const Pose3& query_pose     = candidate_result.T_wq;
    const auto   match_pair     = DescriptorMatcher::MappointsToFeaturesMatching(
        std::make_shared<const Map>(map), query_features, intrinsic, query_pose, parameters_.f2cmc_params.window_size,
        parameters_.f2cmc_params.descriptor_dist_th, parameters_.f2cmc_params.ratio_test_th,
        parameters_.f2cmc_params.view_distance_th, parameters_.f2cmc_params.view_direction_th);

    if (match_pair.size() < parameters_.f2cmc_params.matches_threshold)
    {
        return boost::none;
    }

    // create pose only unit3 noise
    const gtsam::SharedNoiseModel noise_sigma =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.f2cmc_params.pose_only_unit3_factor_sigma));
    const auto huber = gtsam::noiseModel::Robust::Create(
        gtsam::noiseModel::mEstimator::Huber::Create(parameters_.f2cmc_params.pose_only_unit3_factor_huber_loss),
        noise_sigma);

    FactorGraph graph;
    Values      values;
    values.insert(X(query_frame_id), HoloGtsam::Convert(query_pose));

    for (const auto& pair : match_pair)
    {
        const auto& point3           = map.at(pair.first)->position;
        const auto& normalized_point = query_features.at(pair.second).normalized_point;

        const gtsam::Point3 gtsam_point(point3.GetX(), point3.GetY(), point3.GetZ());
        const gtsam::Point3 gtsam_feature(normalized_point.GetX(), normalized_point.GetY(), normalized_point.GetZ());

        graph.add(boost::make_shared<PoseOnlyUnit3Factor>(gtsam_point, gtsam_feature, huber, X(query_frame_id),
                                                          gtsam::Pose3::identity()));
    }

    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values);
    values    = optimizer.optimize();
    Pose3 Twc = HoloGtsam::Convert(values.at(X(query_frame_id)).cast<gtsam::Pose3>());

    // check inliers
    const auto  Tcw                = Twc.Inverse();
    const auto& query_landmark_ids = query_frame.multi_camera_data.at(query_camera_index).associated_landmarks;

    LandmarkIdPairs                            landmark_pairs;
    std::vector<std::pair<uint64_t, uint16_t>> train_lm_id_to_query_feature_index;

    for (const auto& pair : match_pair)
    {
        const auto& ptw      = map.at(pair.first)->position;
        Point3      proj_ptn = Tcw * ptw;
        Point2      proj_pt(proj_ptn.GetX() / proj_ptn.GetZ(), proj_ptn.GetY() / proj_ptn.GetZ());

        const auto& ptn = query_features.at(pair.second).normalized_point;
        Point2      pt(ptn.GetX() / ptn.GetZ(), ptn.GetY() / ptn.GetZ());

        if (proj_pt.Dist(pt) > parameters_.f2cmc_params.projection_error_threshold)
        {
            continue;
        }

        const uint64_t train_lm_id = train_landmark_ids.at(pair.first);
        const uint64_t query_lm_id = query_landmark_ids.at(pair.second);

        if (query_lm_id > 0 && tracks_database.Exists(query_lm_id))
        {
            landmark_pairs.push_back(std::make_pair(train_lm_id, query_lm_id));
        }
        else
        {
            train_lm_id_to_query_feature_index.emplace_back(train_lm_id, pair.second);
        }
    }

    if (landmark_pairs.size() + train_lm_id_to_query_feature_index.size() <
        parameters_.f2cmc_params.minimum_inliers_number)
    {
        return boost::none;
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- checking with covisibility map passed. train frame id: "
                                      << candidate_result.train_frame.first
                                      << ", query frame id: " << candidate_result.query_frame.first << ", inliers: "
                                      << landmark_pairs.size() + train_lm_id_to_query_feature_index.size()
                                      << ", match pairs :" << match_pair.size() << ", the proportion of inliers: "
                                      << 100.0 * (landmark_pairs.size() + train_lm_id_to_query_feature_index.size()) /
                                             match_pair.size()
                                      << " %.\n";

    if (frames_database.IsFromMultiDatabaseMerging())
    {
        std::pair<uint64_t, uint64_t> train_map_id_frame_id = Utility::UnHashId((uint64_t)train_frame_id);
        std::pair<uint64_t, uint64_t> query_map_id_frame_id = Utility::UnHashId((uint64_t)query_frame_id);
        if (train_map_id_frame_id.first != query_map_id_frame_id.first)
        {
            LOG(INFO) << "Train  map id: " << train_map_id_frame_id.first << "    "
                      << "Train frame id: " << train_map_id_frame_id.second << "\n";
            LOG(INFO) << "Query map id: " << query_map_id_frame_id.first << "    "
                      << "Query frame id: " << query_map_id_frame_id.second << "\n";
        }
        else
        {
            LOG(INFO) << "Have loop in self !!!"
                      << "\n";
            LOG(INFO) << "Train  map id: " << train_map_id_frame_id.first << "    "
                      << "Train frame id: " << train_map_id_frame_id.second << "\n";
            LOG(INFO) << "Query map id: " << query_map_id_frame_id.first << "    "
                      << "Query frame id: " << query_map_id_frame_id.second << "\n";
        }
    }

    return LoopClosingResult(candidate_result.train_frame, candidate_result.query_frame, Twc, landmark_pairs,
                             train_lm_id_to_query_feature_index);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GlobalOptimizer::LoopClosingResults GlobalOptimizer::LoopDetectionAndGeometricChecking(
    const LoopDetector& loop_detector, const FramesDatabase& frames_database,
    const TracksDatabase& tracks_database) const
{
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- start LoopDetectionAndGeometricChecking ...\n";
    LoopClosingResults results;
    uint64_t           processed_frame = 0;

    // traversal all frame
    for (const auto& indexed_frame : frames_database.GetAllFrames())
    {
        // retrieve query frame
        const auto& query_frame       = indexed_frame.second;
        const auto& camera_parameters = query_frame.camera_parameters;

        // create opencv windows name
        if (parameters_.enable_visualizer)
        {
            for (size_t i = 0; i < camera_parameters->camera_coords.size(); i++)
            {
                cv::namedWindow(camera_parameters->camera_coords.at(i), CV_WINDOW_KEEPRATIO);
            }
        }

        // traversal all camera
        for (uint16_t camera_index = 0; camera_index < query_frame.multi_camera_data.size(); camera_index++)
        {
            // query candidate loop for this frame
            const auto candidate_loop = loop_detector.Run(query_frame, camera_index, 3);

            // do geometric consistency checking for each candidate loop
            auto tmp_results = FrameToFrameChecking(frames_database, tracks_database, candidate_loop);

            if (tmp_results)
            {
                // further verifycation by covisibility map of train frame
                tmp_results = FrameToCovisibilityMapChecking(frames_database, tracks_database, *tmp_results);
            }

            // record current result
            if (tmp_results)
            {
                results.push_back(*tmp_results);
            }

            // visualization
            if (!parameters_.enable_visualizer || frames_database.IsFromMultiDatabaseMerging())
            {
                continue;
            }

            // declare visualizer
            static mapping::Visualizer visualizer;

            // visualize feature tracks
            if (!query_frame.multi_camera_data.at(camera_index).image_name.empty() ||
                !query_frame.multi_camera_data.at(camera_index).image.empty())
            {
                const auto image = visualizer.VisualizeTracks(query_frame, camera_index,
                                                              camera_parameters->intrinsics.at(camera_index),
                                                              tracks_database.GetAllTracks());
                cv::imshow(camera_parameters->camera_coords.at(camera_index), image);
                cv::waitKey(10);
            }

#ifdef HOLO_VISUALIZE_WITH_PCL
            // visualize loop edge
            if (tmp_results)
            {
                visualizer.DrawLoop(tmp_results->T_wq, query_frame.multi_camera_data.at(camera_index).pose, 255, 0, 0);
            }

            // visualize landmarks and camera trajectory
            visualizer.DrawLandmarks(tracks_database.GetAllTracks(),
                                     query_frame.multi_camera_data.at(camera_index).associated_landmarks);
            visualizer.DrawTrajectory(query_frame.multi_camera_data.at(camera_index).pose, 0, 255, 0);
            visualizer.DrawCamera(query_frame.multi_camera_data.at(camera_index).pose, 0, 255, 0);
            visualizer.Update();
#endif
        }

        processed_frame++;

        if (parameters_.verbose)
        {
            LOG_EVERY_N(INFO, 50)
                << "GlobalOptimizer --- LoopDetectionAndGeometricChecking is running, processed frames:"
                << processed_frame << ", total frames: " << frames_database.Size()
                << ", Progress: " << 100.0 * processed_frame / frames_database.Size() << " %.\n";
        }
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- LoopDetectionAndGeometricChecking done. finally find "
                                      << results.size() << " loop edge.\n";

    return results;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<std::set<uint64_t>>
GlobalOptimizer::ClusteringAssociatedLandmarkIds(const LandmarkIdPairs& associated_landmarks) const
{
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- start clustering associated lamdmark ids ...\n";
    // define landmark_sets with their set id.
    // key: set id. increase from 0 to max value automatically when create a new set
    // value: landmark id set which belong to a same landmark
    std::unordered_map<uint64_t, std::set<uint64_t>> indexed_landmark_sets;
    uint64_t                                         next_set_id = 0;

    // loop all associated landmarks
    for (const auto& landmark_id_pair : associated_landmarks)
    {
        const auto& train_lm_id = landmark_id_pair.first;
        const auto& query_lm_id = landmark_id_pair.second;

        std::vector<uint64_t> old_set_ids;

        /**
         * @details searching in indexed_landmark_sets to check if this pair belongs to some old sets
         * EXAMPLE:
         *       index: 0   1   2   3  |  4   5   6   7  | 8
         *              100 101 102 103 | 104 105 106 108 |108
         *               4   1   2   3  |  1   2   3   5  | 4
         * for example shown above, index:{0,1,2,3,7} will retrain in indexed_landmark_sets,
         * dex:1 will be counted, so the set of index:1 is {101,1,104}; when traversing to
         * index:7 will be counted, so the set of index:0 is {100,4,108,5}
         */
        for (const auto& indexed_lm_set : indexed_landmark_sets)
        {
            const auto& lm_set_id = indexed_lm_set.first;
            const auto& lm_set    = indexed_lm_set.second;

            if (lm_set.count(train_lm_id) || lm_set.count(query_lm_id))
            {
                old_set_ids.push_back(lm_set_id);
            }
        }

        if (old_set_ids.empty())
        {
            // belongs to a new set
            indexed_landmark_sets.emplace(next_set_id++, std::set<uint64_t>{train_lm_id, query_lm_id});
        }
        else
        {
            // belongs to maybe more than one set, the indexes of these old set are record in ${old_set_ids}.
            // retrieve first set in ${old_set_ids}, it will be retained, other set in ${old_set_ids} will be
            // mergeed with the retained set then be removed from &{indexed_landmark_sets}
            auto& retained_set = indexed_landmark_sets.at(old_set_ids.at(0));

            // 1. merge all record set in old_set_indexes.
            for (size_t i = 1; i < old_set_ids.size(); i++)
            {
                const auto& removed_set_id = old_set_ids.at(i);
                const auto& removed_set    = indexed_landmark_sets.at(removed_set_id);

                // insert this set to retained_set
                retained_set.insert(removed_set.begin(), removed_set.end());

                // remove this set from indexed_landmark_sets
                indexed_landmark_sets.erase(removed_set_id);
            }

            // 2. add train_lm_id and query_lm_id to the merged set
            retained_set.insert(train_lm_id);
            retained_set.insert(query_lm_id);
        }
    }

    std::vector<std::set<uint64_t>> result;
    result.reserve(indexed_landmark_sets.size());

    // construct result
    for (const auto& indexed_set : indexed_landmark_sets)
    {
        result.emplace_back(indexed_set.second);
    }

    LOG_IF(INFO, parameters_.verbose)
        << "GlobalOptimizer --- clustering associated lamdmark ids done. set num to be merged: "
        << indexed_landmark_sets.size();
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase GlobalOptimizer::FeatureTracksMerging(const FramesDatabase&     frames_database,
                                                     const TracksDatabase&     tracks_database,
                                                     const LoopClosingResults& loop_results) const
{
    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- start feature tracks merging ...\n";
    IndexedTracks new_indexed_tracks = tracks_database.GetAllTracks();

    // add new matched feature to track's measurement
    for (size_t i = 0; i < loop_results.size(); i++)
    {
        const uint64_t query_frame_id     = loop_results.at(i).query_frame.first;
        const uint16_t query_camera_index = loop_results.at(i).query_frame.second;
        const auto&    query_features =
            frames_database.GetFrame(query_frame_id).multi_camera_data.at(query_camera_index).features;
        const auto& pairs = loop_results.at(i).train_lm_id_to_query_feature_index;

        for (const auto& pair : pairs)
        {
            const uint64_t lm_id         = pair.first;
            const uint16_t feature_index = pair.second;

            auto& track = new_indexed_tracks.at(lm_id);

            // add new measurement to track
            track = track.CreateNewTrackByAddingNewestMeasurement(query_frame_id, query_features.at(feature_index));
        }
    }

    LandmarkIdPairs associated_lamdmark_ids;

    // retrieve all associated lamdmark ids
    for (size_t i = 0; i < loop_results.size(); i++)
    {
        const auto& pairs = loop_results.at(i).associated_landmarks;
        std::copy(pairs.begin(), pairs.end(), std::back_inserter(associated_lamdmark_ids));
    }

    // clustering the associated landmark ids
    const auto landmark_sets = ClusteringAssociatedLandmarkIds(associated_lamdmark_ids);

    // tracks merging
    uint64_t merged_tracks_num = 0;

    // loop all landmark sets
    for (const auto& lm_set : landmark_sets)
    {
        // retain tracks with smallest id
        const uint64_t retained_lm_id = *lm_set.begin();
        auto&          retained_track = new_indexed_tracks.at(retained_lm_id);

        for (const auto& lm_id : lm_set)
        {
            if (lm_id == retained_lm_id)
            {
                continue;
            }

            const auto& removed_track = new_indexed_tracks.at(lm_id);

            // add all removed track's measurement to retained track
            for (const auto& m : removed_track.Measurements())
            {
                const auto& frame_id = m.first;

                for (const auto& camera_indexed_feature : m.second)
                {
                    const auto& feature = camera_indexed_feature.second;
                    retained_track      = retained_track.CreateNewTrackByAddingNewestMeasurement(frame_id, feature);
                }
            }

            merged_tracks_num++;
            new_indexed_tracks.erase(lm_id);
        }
    }

    TracksDatabase new_database;

    for (const auto& indexed_track : new_indexed_tracks)
    {
        new_database.AddFeatureTrack(indexed_track.second);
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- FeatureTracksMerging done. merged tracks num: "
                                      << merged_tracks_num;
    return new_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalOptimizer::BuildSequentialFactorGraphFromMappingDatabase(const MappingDatabase& mapping_database,
                                                                    FactorGraph&           factor_graph) const
{
    const auto& timestamp_to_frame_id_map = mapping_database.timestamp_to_frame_id;
    const auto& values                    = mapping_database.xvb_values;

    std::unordered_map<uint64_t, bool> is_turn;

    // build imu factors meanwhile record whether the vehicle is turn by pim.
    for (const auto& iter : mapping_database.imu_factors)
    {
        factor_graph.add(iter.second);
    }

    for (const auto& imus : mapping_database.imus)
    {
        if (imus.size() <= 2)
        {
            continue;
        }

        if (!timestamp_to_frame_id_map.count(imus.front().GetTimestamp()) ||
            !timestamp_to_frame_id_map.count(imus.back().GetTimestamp()))
        {
            continue;
        }

        // get frame id
        const auto& start_frame_id = timestamp_to_frame_id_map.at(imus.front().GetTimestamp());
        const auto& end_frame_id   = timestamp_to_frame_id_map.at(imus.back().GetTimestamp());

        // create pim
        if (mapping_database.enable_estimation_with_acc)
        {
            const gtsam::imuBias::ConstantBias bias = values.at(B(start_frame_id)).cast<gtsam::imuBias::ConstantBias>();
            PreintegratedImuMeasurements       new_pim(parameters_.pim_params, bias);

            // pre-integrate imu measurement
            for (uint16_t i = 0; i < (uint16_t)(imus.size() - 1); i++)
            {
                const Scalar dt = (imus.at(i + 1).GetTimestamp() - imus.at(i).GetTimestamp()).ToSec();

                // calculate average linear_acceleration and angular_velocity
                // @todo(Feng. Li 2020-01-10) should we rotate imus.at(i + 1) with Quatation(angular_velocity * dt) ?
                const auto linear_acceleration =
                    0.5 * imus.at(i).GetLinearAcceleration() + 0.5 * imus.at(i + 1).GetLinearAcceleration();

                const auto angular_velocity =
                    0.5 * imus.at(i).GetAngularVelocity() + 0.5 * imus.at(i + 1).GetAngularVelocity();

                new_pim.integrateMeasurement(HoloGtsam::Convert(linear_acceleration),
                                             HoloGtsam::Convert(angular_velocity), dt);
            }

            // create imu factor
            // judge whether the vehicle is turn
            const Scalar rotation_threshold = 5e-3;  // rotation threshold to determine if turn

            if (new_pim.deltaRij().rpy().norm() > rotation_threshold)
            {
                is_turn.emplace(end_frame_id, true);
            }
        }
        else
        {
            static boost::shared_ptr<PreintegratedAhrsMeasurements::Params> ahrs_params =
                boost::make_shared<PreintegratedAhrsMeasurements::Params>(
                    parameters_.pim_params->getGyroscopeCovariance(), parameters_.pim_params->getOmegaCoriolis());

            const auto old_bias = values.at(B(start_frame_id)).cast<gtsam::Vector3>();

            // create rotation only
            PreintegratedAhrsMeasurements pam(ahrs_params, old_bias);

            for (uint16_t i = 0; i < (uint16_t)(imus.size() - 1); i++)
            {
                const Scalar dt = (imus.at(i + 1).GetTimestamp() - imus.at(i).GetTimestamp()).ToSec();

                const auto angular_velocity =
                    0.5 * imus.at(i).GetAngularVelocity() + 0.5 * imus.at(i + 1).GetAngularVelocity();

                pam.integrateMeasurement(HoloGtsam::Convert(angular_velocity), dt);
            }
            factor_graph.add(
                boost::make_shared<RotationOnlyImuFactor>(X(start_frame_id), X(end_frame_id), B(end_frame_id), pam));
        }
    }

    // build wheel pulse integration factor
    const auto& wheel_integration_measurements = mapping_database.wheel_integrations;
    for (size_t wim_index = 1; wim_index < wheel_integration_measurements.size(); ++wim_index)
    {
        const auto& wim             = wheel_integration_measurements[wim_index];
        const auto  wim_end_point   = timestamp_to_frame_id_map.find(wim.end);
        const auto  wim_start_point = timestamp_to_frame_id_map.find(wim.start);
        if (wim_end_point != timestamp_to_frame_id_map.end() && wim_start_point != timestamp_to_frame_id_map.end())
        {
            const auto& frame_id     = wim_end_point->second;
            const auto& old_frame_id = wim_start_point->second;

            const gtsam::Pose2 pose2(wim.delta_x, wim.delta_y, wim.delta_yaw);
            const auto         t                              = pose2.translation().norm();
            Vector6            wheel_integration_factor_sigma = parameters_.sigmas.wheel_integration_factor_sigma;

            if (t < 1e-5)
            {
                wheel_integration_factor_sigma = parameters_.sigmas.zero_velocity_between_pose_sigma;
            }

            const gtsam::SharedNoiseModel pose3_between_factor_noise =
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(wheel_integration_factor_sigma));
            factor_graph.add(boost::make_shared<Pose3BetweenFactor>(
                X(old_frame_id), X(frame_id), gtsam::Pose3(gtsam::Pose2(wim.delta_x, wim.delta_y, wim.delta_yaw)),
                pose3_between_factor_noise));
        }
    }

    if (mapping_database.enable_estimation_with_acc)
    {
        const auto& velocity_measurement_vector = mapping_database.velocities;
        for (uint64_t frame_index = 0; frame_index < (uint64_t)velocity_measurement_vector.size(); frame_index++)
        {
            const auto& velocity_measurement = velocity_measurement_vector[frame_index];

            // get measurement
            const auto& velocity = velocity_measurement.velocity;
            const auto& frame_id = timestamp_to_frame_id_map.at(velocity_measurement.timestamp);

            // get sigmas
            auto sigma = parameters_.sigmas.velocity_factor_sigma;

            if (is_turn.count(frame_id) && is_turn.at(frame_id))
            {
                sigma = parameters_.sigmas.velocity_factor_sigma_when_turns;
            }

            const gtsam::SharedNoiseModel velocity_noise =
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(sigma));
            factor_graph.add(boost::make_shared<VelocityFactor>(X(frame_id), V(frame_id), HoloGtsam::Convert(velocity),
                                                                velocity_noise));
        }
    }

    // build position factor
    if (parameters_.enable_position_factor)
    {
        for (const auto& utm_position : mapping_database.positions)
        {
            const auto& timestamp = utm_position.timestamp;

            if (!timestamp_to_frame_id_map.count(timestamp))
            {
                continue;
            }

            const auto& frame_id = timestamp_to_frame_id_map.at(timestamp);

            // create gps factor
            const gtsam::SharedNoiseModel position_noise =
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(utm_position.position_std));
            factor_graph.add(
                boost::make_shared<GPSFactor>(X(frame_id), HoloGtsam::Convert(utm_position.position), position_noise));
        }
    }

    // build imu bias factor
    if (mapping_database.enable_estimation_with_acc)
    {
        // create imu bias noise
        const gtsam::SharedNoiseModel bias_noise =
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.bias_between_sigma));
        uint64_t old_frame_index = 0;
        for (auto it = timestamp_to_frame_id_map.begin(); it != timestamp_to_frame_id_map.end(); ++it)
        {
            const uint64_t new_frame_index = it->second;
            if (it == timestamp_to_frame_id_map.begin())
            {
                old_frame_index = new_frame_index;
                continue;
            }

            factor_graph.add(boost::make_shared<ImuBiasFactor>(B(old_frame_index), B(new_frame_index),
                                                               gtsam::imuBias::ConstantBias(), bias_noise));
            old_frame_index = new_frame_index;
        }
    }
    else
    {
        gtsam::Vector3                gyro_bias_sigma(parameters_.sigmas.bias_between_sigma[3],
                                       parameters_.sigmas.bias_between_sigma[4],
                                       parameters_.sigmas.bias_between_sigma[5]);
        const gtsam::SharedNoiseModel bias_noise      = gtsam::noiseModel::Diagonal::Sigmas(gyro_bias_sigma);
        uint64_t                      old_frame_index = 0;

        for (auto it = timestamp_to_frame_id_map.begin(); it != timestamp_to_frame_id_map.end(); ++it)
        {
            const uint64_t new_frame_index = it->second;
            if (it == timestamp_to_frame_id_map.begin())
            {
                old_frame_index = new_frame_index;
                continue;
            }

            factor_graph.add(boost::make_shared<Vector3BetweenFactor>(B(old_frame_index), B(new_frame_index),
                                                                      gtsam::Vector3(0, 0, 0), bias_noise));
            old_frame_index = new_frame_index;
        }
    }

    // build ground truth prior factor
    if (parameters_.enable_gt_pose_factor)
    {
        for (const auto& gt_odo : mapping_database.ground_truth_odometry)
        {
            const auto& timestamp = gt_odo.GetTimestamp();

            // check timestamp
            if (!timestamp_to_frame_id_map.count(timestamp))
            {
                LOG(WARNING) << "GlobalOptimizer --- ground truth's timestamp is error ";
                continue;
            }
            const auto& frame_id = timestamp_to_frame_id_map.at(timestamp);

            // create ground truth factor
            const gtsam::SharedNoiseModel gt_pose_noise =
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.gt_pose_sigma));

            factor_graph.add(
                boost::make_shared<PosePriorFactor>(X(frame_id), HoloGtsam::Convert(gt_odo.GetPose()), gt_pose_noise));
        }
    }

    LOG_IF(INFO, parameters_.verbose)
        << "GlobalOptimizer --- BuildSequentialFactorGraphFromMappingDatabase done. total factor number: "
        << factor_graph.size() << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalOptimizer::AddPriorFactor(const MappingDatabase& mapping_database, FactorGraph& factor_graph) const
{
    const auto& values = mapping_database.xvb_values;

    // build prior factor for first frame
    {
        const auto& first_frame_id = mapping_database.frame_id_to_timestamp.begin()->first;
        const auto& end_frame_id   = mapping_database.frame_id_to_timestamp.rbegin()->first;
        // add prior pose factor
        if (!parameters_.enable_gt_pose_factor)
        {
            const gtsam::Pose3 prior_pose = values.at(X(first_frame_id)).cast<gtsam::Pose3>();
            factor_graph.add(gtsam::PriorFactor<gtsam::Pose3>(
                X(first_frame_id), prior_pose,
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.prior_pose_sigma))));
        }

        if (mapping_database.enable_estimation_with_acc)
        {
            // add prior velocity factor
            const gtsam::Vector3 prior_velocity = values.at(V(first_frame_id)).cast<gtsam::Vector3>();
            factor_graph.add(gtsam::PriorFactor<gtsam::Vector3>(
                V(first_frame_id), prior_velocity,
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.prior_velocity_sigma))));

            // add prior bias factor
            const gtsam::imuBias::ConstantBias prior_bias =
                values.at(B(end_frame_id)).cast<gtsam::imuBias::ConstantBias>();
            factor_graph.add(gtsam::PriorFactor<gtsam::imuBias::ConstantBias>(
                B(first_frame_id), prior_bias,
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.prior_bias_sigma))));
        }
        else
        {
            // add prior bias factor
            const auto prior_bias = values.at(B(end_frame_id)).cast<gtsam::Vector3>();

            const gtsam::PriorFactor<gtsam::Vector3> prior_bias_factor(
                B(first_frame_id), prior_bias, gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(1e-1, 1e-1, 1e-1)));
            factor_graph.add(prior_bias_factor);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<FactorGraph, Values> GlobalOptimizer::AddSemanticFactor(
    const PoseSpline& pose_spline, const ParkingSlotTracksDatabase& parking_slot_track_database)
{
    // create imu bias noise
    const gtsam::SharedNoiseModel vertex_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.vertex_factor_sigma));
    const gtsam::SharedGaussian plane_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.plane_factor_sigma));
    const gtsam::SharedNoiseModel point_plane_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector1(parameters_.sigmas.point_plane_factor_sigma[0]));
    const gtsam::SharedNoiseModel parallel_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.parallel_factor_sigma));

    FactorGraph semantic_factor_graph;
    Values      semantic_values;

    const auto& pose_spline_start_time = pose_spline.GetStartTime();
    const auto& pose_spline_end_time   = pose_spline.GetEndTime();

    MappingDatabase mapping_database;

    const auto all_parking_slot_tracks = parking_slot_track_database.GetAllParkingSlotTracks();

    for (const auto& track : all_parking_slot_tracks)
    {
        const auto& track_timestamp = track.timestamp;
        if (track_timestamp < pose_spline_start_time || track_timestamp > pose_spline_end_time)
        {
            continue;
        }

        const auto& cur_pose = HoloGtsam::Convert(pose_spline.GetPose(track_timestamp));
        const auto& vertices = track.GetIndexedVertices(track.measurements.size() - 1);
        for (const auto& vertex : vertices)
        {
            const gtsam::Point3 measured = HoloGtsam::Convert(vertex.point);
            if (!semantic_values.exists(S(vertex.id)))
            {
                semantic_values.insert(S(vertex.id), cur_pose * measured);
            }
        }

        if (vertices.size() >= 4u)
        {
            semantic_factor_graph.emplace_shared<semantic::ParkingSlotParallelFactor>(
                S(vertices[0].id), S(vertices[1].id), S(vertices[2].id), S(vertices[3].id), parallel_factor_noise);
            semantic_factor_graph.emplace_shared<semantic::ParkingSlotParallelFactor>(
                S(vertices[1].id), S(vertices[2].id), S(vertices[3].id), S(vertices[0].id), parallel_factor_noise);
        }

        // add vertex factor
        for (size_t i = 0; i < track.measurements.size(); i++)
        {
            const auto m                     = track.measurements.at(i);
            const auto measurement_timestamp = m.second.first;
            if (measurement_timestamp < pose_spline_start_time || measurement_timestamp > pose_spline_end_time)
            {
                continue;
            }
            const auto measurement_pose = pose_spline.GetPose(measurement_timestamp);
            const auto vertices         = track.GetIndexedVertices(i);

            for (const auto& vertex : vertices)
            {
                const gtsam::Point3 measured = HoloGtsam::Convert(vertex.point);

                semantic_factor_graph.emplace_shared<semantic::PointOnlySlotVertexFactor>(
                    S(vertex.id), HoloGtsam::Convert(measurement_pose), measured, vertex_factor_noise);
            }
        }
    }

    return std::make_pair(semantic_factor_graph, semantic_values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::set<holo::uint64_t> GlobalOptimizer::AddVisualFactorAndLoopConstraintsToGraph(
    FactorGraph& factor_graph, const Values& old_values, const FramesDatabase& frames_database,
    const TracksDatabase& tracks_database, const LoopClosingResults& loop_results) const
{
    uint64_t visual_factor_num = 0;

    std::set<holo::uint64_t> landmark_id;
    (void)tracks_database;
    /// @todo(Feng.Li lifeng@holmatic.com 2022-05-01) we should add visual factor to global BA problem when we actually
    /// fix the offline optimization time consumption

    /*
    std::unordered_map<holo::uint64_t, holo::uint16_t> frame_id_to_factor_number;

    // loop all tracks to add Unit3Factors
    for (const auto& indexed_track : tracks_database.GetAllTracks())
    {
        const auto& track = indexed_track.second;

        for (size_t i = 0; i < track.Length(); ++i)
        {
            const auto& m = track.Measurements(i);

            if (frame_id_to_factor_number.count(m.first) &&
                frame_id_to_factor_number.at(m.first) > parameters_.factor_number_in_one_frame)
            {
                continue;
            }
            frame_id_to_factor_number[m.first]++;
            const auto factors = track.CreateUnit3Factor(i);
            factor_graph.add(factors);

            visual_factor_num += factors.size();
            landmark_id.insert(track.GetLandmark()->Id());
        }
    }
    */

    // loop new_loop_result to add Pose3BetweenFactor
    for (size_t i = 0; i < loop_results.size(); i++)
    {
        const auto& loop_result    = loop_results.at(i);
        const auto& train_frame_id = loop_result.train_frame.first;
        const auto& query_frame_id = loop_result.query_frame.first;

        if (!frames_database.Exists(query_frame_id))
        {
            throw std::runtime_error(
                "AddLoopConstraintsToGraphThenOptimize --- query frame does not exist in frame database.");
        }

        if (!old_values.exists(X(train_frame_id)))
        {
            throw std::runtime_error(
                "AddLoopConstraintsToGraphThenOptimize --- train frame does not exist in old value.");
        }

        const auto& query_camera_parameters = frames_database.GetFrame(query_frame_id).camera_parameters;

        // compute between pose
        const auto& train_pose = old_values.at(X(train_frame_id)).cast<gtsam::Pose3>();

        const auto& T_bc         = query_camera_parameters->extrinsics.at(loop_result.query_frame.second);
        const auto  query_pose   = HoloGtsam::Convert(loop_result.T_wq * T_bc.Inverse());
        const auto  between_pose = train_pose.inverse() * query_pose;

        // create pose3 between factor noise model
        const gtsam::SharedNoiseModel pose3_between_factor_noise =
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.sigmas.loop_closing_between_pose_sigma));

        // add prior_factor
        factor_graph.add(boost::make_shared<Pose3BetweenFactor>(X(train_frame_id), X(loop_result.query_frame.first),
                                                                between_pose, pose3_between_factor_noise));
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- AddVisualFactorsToGraph done. visual factor num: "
                                      << visual_factor_num << ", between pose3 factor num: " << loop_results.size()
                                      << ", total factor num: " << factor_graph.size() << " \n";
    return landmark_id;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GlobalOptimizer::AddLandmarksToValues(const std::set<holo::uint64_t>& landmark_ids, const Values& old_values,
                                             const TracksDatabase& tracks_database) const
{
    Values new_values = old_values;

    for (const auto& landmark_id : landmark_ids)
    {
        const auto& track    = tracks_database.GetTrack(landmark_id);
        const auto& landmark = track.GetLandmark();

        if (!landmark)
        {
            throw std::runtime_error(
                "GlobalOptimizer --- AddLandmarksToValues. given tracks without landmark. something must be wrong.\n");
        }

        new_values.insert(L(landmark->Id()), landmark->Point());
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- AddLandmarksToValues done. landmark num: "
                                      << tracks_database.Size() << "  landmark_ids num:" << landmark_ids.size() << "\n";

    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GlobalOptimizer::UpdateLandmarksValues(const Values& old_values, const TracksDatabase& tracks_database) const
{
    Values   new_values = old_values;
    uint64_t num_add    = 0;

    for (const auto& indexed_track : tracks_database.GetAllTracks())
    {
        const auto& track    = indexed_track.second;
        const auto& landmark = track.GetLandmark();

        if (!landmark)
        {
            throw std::runtime_error(
                "GlobalOptimizer --- AddLandmarksToValues. given tracks without landmark. something must be wrong.\n");
        }
        if (!new_values.exists(L(landmark->Id())))
        {
            new_values.insert(L(landmark->Id()), landmark->Point());
            num_add++;
        }
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- AddLandmarksToValues done. all tracks num: "
                                      << tracks_database.Size() << "  add landmark num: " << num_add << "\n";

    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GlobalOptimizer::AddLandmarksToValues(const Values& old_values, const TracksDatabase& tracks_database) const
{
    Values new_values = old_values;

    for (const auto& indexed_track : tracks_database.GetAllTracks())
    {
        const auto& track    = indexed_track.second;
        const auto& landmark = track.GetLandmark();

        if (!landmark)
        {
            throw std::runtime_error(
                "GlobalOptimizer --- AddLandmarksToValues. given tracks without landmark. something must be wrong.\n");
        }

        new_values.insert(L(landmark->Id()), landmark->Point());
    }

    LOG_IF(INFO, parameters_.verbose) << "GlobalOptimizer --- AddLandmarksToValues done. landmark num: "
                                      << tracks_database.Size() << "\n";
    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GlobalOptimizer::GlobalBundleAdjustment(const FactorGraph& new_factor_graph, const Values& new_values) const
{
    // optimize by gtsam
    LOG(INFO) << "GlobalOptimizer --- start global bundle adjustment ...\n";
    gtsam::LevenbergMarquardtParams params;
    params.setVerbosity(
        gtsam::LevenbergMarquardtParams::verbosityLMTranslator(gtsam::LevenbergMarquardtParams::VerbosityLM::LAMBDA));
    gtsam::LevenbergMarquardtOptimizer optimizer(new_factor_graph, new_values, params);
    const Values                       optimized_value = optimizer.optimize();
    LOG(INFO) << "GlobalOptimizer --- global bundle adjustment iterations = " << optimizer.iterations() << "\n";
    LOG(INFO) << "GlobalOptimizer --- global bundle adjustment done.\n";
    return optimized_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GlobalOptimizer::CheckReprojectionError(const FramesDatabase& frames_database, const FeatureTrack& track,
                                             const Values& values) const
{
    // loop all measurement
    for (const auto& m : track.Measurements())
    {
        // get newest frame id
        const uint64_t frame_id = m.first;

        // check if frame is exist in frames_database
        if (!frames_database.Exists(frame_id))
        {
            continue;
        }

        // get camera parameters of this frame
        const auto& camera_parameters = frames_database.GetFrame(frame_id).camera_parameters;

        // loop for all observed camera
        for (const auto& camera_indexed_feature : m.second)
        {
            // get camera index and corresponding extrinsic
            const auto& camera_index = camera_indexed_feature.first;
            const auto& T_bc         = camera_parameters->extrinsics.at(camera_index);
            const auto& feature      = camera_indexed_feature.second;

            // compute camera pose in world frame
            const gtsam::Pose3 T_wb = values.at(X(frame_id)).cast<gtsam::Pose3>();
            const gtsam::Pose3 T_wc = T_wb * holo::localization::HoloGtsam::Convert(T_bc);

            // compute landmark location
            gtsam::Point3 landmark = values.at(L((track.GetLandmark())->Id())).cast<gtsam::Point3>();

            // transform landmark to camera coordinate
            const auto ptc = HoloGtsam::Convert(T_wc.inverse() * landmark);

            // check max distance
            if (ptc.ToVector().GetNorm() > parameters_.max_landmark_distance)
            {
                return false;
            }

            // check if behind camera
            const auto&  ray                                        = feature.normalized_point.ToVector();
            const Scalar angle_between_feature_ray_and_optical_axis = holo::Degree(std::acos(ray[2] / ray.GetNorm()));

            if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
            {
                // behind camera
                return false;
            }

            // create two vectors
            const gtsam::Unit3 p = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(ptc));
            const gtsam::Unit3 q = gtsam::Unit3::FromPoint3(HoloGtsam::Convert(feature.normalized_point));

            // convert error threshold from pixel error to unit3 error
            Scalar threshold = CameraParameters::ComputeUnit3ErrorFromPixelErrorAtImageCenter(
                camera_parameters->intrinsics.at(camera_index), parameters_.projection_error_after_gba);

            // compute error
            if (p.errorVector(q).norm() > threshold)
            {
                return false;
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GlobalOptimizer::CheckPiexlReprojectionError(const FeatureTrack& track, const Values& values,
                                                  const FramesDatabase& frames_database) const
{
    (void)frames_database;
    std::vector<Scalar> measurement_errors;
    Scalar              threshold = 4.0;

    // loop all measurement
    for (const auto& m : track.Measurements())
    {
        // get newest frame id
        const uint64_t frame_id = m.first;

        // check if frame is exist in values
        if (!values.exists(X(frame_id)))
        {
            continue;
        }

        // get camera parameters of this frame
        const auto& camera_parameters = track.CameraParams();

        // loop for all observed camera
        for (const auto& camera_indexed_feature : m.second)
        {
            // get camera index and corresponding extrinsic
            const auto& camera_index     = camera_indexed_feature.first;
            const auto& T_bc             = camera_parameters->extrinsics.at(camera_index);
            const auto& camera_intrinsic = camera_parameters->intrinsics.at(camera_index);
            const auto& feature          = camera_indexed_feature.second;

            // compute camera pose in world frame
            const gtsam::Pose3 T_wb = values.at(X(frame_id)).cast<gtsam::Pose3>();
            const gtsam::Pose3 T_wc = T_wb * holo::localization::HoloGtsam::Convert(T_bc);

            // compute landmark location
            gtsam::Point3 landmark = values.at(L((track.GetLandmark())->Id())).cast<gtsam::Point3>();

            // transform landmark to camera coordinate
            const auto ptc = HoloGtsam::Convert(T_wc.inverse() * landmark);

            // check max distance
            if (ptc.ToVector().GetNorm() > parameters_.max_landmark_distance)
            {
                return false;
            }

            // check if behind camera
            const auto&  ray                                        = feature.normalized_point.ToVector();
            const Scalar angle_between_feature_ray_and_optical_axis = holo::Degree(std::acos(ray[2] / ray.GetNorm()));

            if (angle_between_feature_ray_and_optical_axis < 90.0 && ptc.GetZ() < 0)
            {
                // behind camera
                return false;
            }

            // compute reprojection error at image plane (in pixel)
            Point2d pt_projected;
            camera_intrinsic->Project(ptc, pt_projected);
            const auto& pt_measurment = feature.image_point;
            Vector2d    pt1           = pt_projected.ToVector();
            Vector2d    pt2(pt_measurment.x, pt_measurment.y);
            Vector2d    error(pt1 - pt2);

            // save this reprojection error for compute of mean later
            measurement_errors.emplace_back(error.GetNorm());
        }
    }

    // check if mean reprojection error exceed threshold
    if ((std::accumulate(measurement_errors.begin(), measurement_errors.end(), 0.0) / measurement_errors.size()) >
        threshold)
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GlobalOptimizer::RemoveOutlierLandmarksFromValue(const Values& values, const TracksDatabase& track_database,
                                                        const FramesDatabase& frames_database) const
{
    LOG(INFO) << "GlobalOptimizer --- start remove outlier landmarks after optimization ...\n";
    Values   new_value     = values;
    uint64_t outliers_num  = 0;
    uint64_t useful_tracks = 0;

    // check inliers
    for (const auto& indexed_track : track_database.GetAllTracks())
    {
        const auto  lm_id = indexed_track.first;
        const auto& track = indexed_track.second;
        if (!new_value.exists(L(lm_id)))
        {
            continue;
        }
        useful_tracks++;

        if (CheckPiexlReprojectionError(track, new_value, frames_database))
        {
            continue;
        }

        new_value.erase(L(lm_id));
        outliers_num++;
    }

    LOG(INFO) << "GlobalOptimizer --- remove outlier done. total tracks num: " << track_database.GetAllTracks().size()
              << "  useful tracks num: " << useful_tracks << "  outliers num: " << outliers_num << "\n";

    return new_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalOptimizer::VisualizeOptimizedResults(const OptimizedResults& optimize_results,
                                                mapping::Visualizer&    visualizer) const
{
#ifdef HOLO_VISUALIZE_WITH_PCL
    const auto& loop_results     = optimize_results.loop_closing_results;
    const auto& optimized_values = optimize_results.optimized_values;
    const auto& frames_database  = optimize_results.frames_database;
    const auto& tracks_database  = optimize_results.tracks_database;

    // draw loop closing edge
    for (const auto& loop_result : loop_results)
    {
        const uint64_t train_frame_id = loop_result.train_frame.first;
        const auto&    train_pose =
            holo::localization::HoloGtsam::Convert(optimized_values.at(X(train_frame_id)).cast<gtsam::Pose3>());

        const uint64_t query_frame_id = loop_result.query_frame.first;
        const auto&    query_pose =
            holo::localization::HoloGtsam::Convert(optimized_values.at(X(query_frame_id)).cast<gtsam::Pose3>());

        visualizer.DrawLoop(train_pose, query_pose, 255, 0, 0);
    }

    // draw landmarks
    IndexedTracks        new_tracks = tracks_database.GetAllTracks();
    std::vector<int64_t> lm_ids;

    for (auto& indexed_track : new_tracks)
    {
        auto&      track    = indexed_track.second;
        const auto landmark = track.GetLandmark();

        if (!landmark)
        {
            continue;
        }
        const auto& lm_id = landmark->Id();

        if (!optimized_values.exists(L(lm_id)))
        {
            continue;
        }

        // update track's position
        track = track.CreateNewTrackByUpdatingState(FeatureTrack::State::FINISHED,
                                                    optimized_values.at(L(lm_id)).cast<gtsam::Point3>());
        lm_ids.push_back(lm_id);
    }
    visualizer.DrawLandmarks(new_tracks, lm_ids);

    // draw trajectory
    for (const auto& indexed_frame : frames_database.GetAllFrames())
    {
        const auto& frame_id = indexed_frame.first;

        // retrieve pose and velocity from values.
        if (!optimized_values.exists(X(frame_id)))
        {
            continue;
        }

        const auto pose = HoloGtsam::Convert(optimized_values.at(X(frame_id)).cast<gtsam::Pose3>());
        visualizer.DrawTrajectory(pose, 0, 255, 0);
    }
#else
    (void)optimize_results;
    (void)visualizer;
    LOG(WARNING) << "GlobalOptimizer --- Disable visualization with pcl, nothing could be visualize!!!";
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
QueryMapToTrainMapTransformPairs GlobalOptimizer::FindTheBestTransformBetweenTwoMaps(
    const FramesDatabase& frames_database, const LoopClosingResults& loop_results) const
{
    QueryMapToTrainMapTransformPairs                                 results;
    std::unordered_map<PairHashedKey, LoopClosingResults, pair_hash> transforms_between_two_maps;

    for (const auto& result : loop_results)
    {
        const std::pair<uint64_t, uint64_t> query_map_id_frame_id = Utility::UnHashId(result.query_frame.first);
        const std::pair<uint64_t, uint64_t> train_map_id_frame_id = Utility::UnHashId(result.train_frame.first);
        const std::pair<uint64_t, uint64_t> query_map_id_train_map_id =
            std::make_pair(query_map_id_frame_id.first, train_map_id_frame_id.first);

        if (transforms_between_two_maps.count(query_map_id_train_map_id))
        {
            transforms_between_two_maps.at(query_map_id_train_map_id).push_back(result);
        }
        else
        {
            transforms_between_two_maps.emplace(query_map_id_train_map_id, std::vector<LoopClosingResult>{result});
        }
    }

    for (const auto& transform : transforms_between_two_maps)
    {
        std::vector<std::pair<float, uint64_t>> errors_loop_id;
        LOG(INFO) << "Query map id: " << transform.first.first << "    "
                  << "Train map id: " << transform.first.second << "   "
                  << "The loop number is: " << transform.second.size() << "\n";

        if (transform.first.first == transform.first.second)
        {
            LOG(INFO) << "Query map id is the same as the Train map id, continue ...\n";
            continue;
        }

        for (size_t i = 0; i < transform.second.size(); i++)
        {
            float    pose_error = 0.0;
            uint64_t first_loop_query_frame_id;
            uint64_t second_loop_query_frame_id;

            for (size_t j = 0; j < transform.second.size(); j++)
            {
                if (i == j)
                {
                    continue;
                }
                const auto first_loop  = transform.second[i];
                const auto second_loop = transform.second[j];

                const auto first_loop_pose  = first_loop.T_wq;
                const auto second_loop_pose = second_loop.T_wq;

                first_loop_query_frame_id  = first_loop.query_frame.first;
                second_loop_query_frame_id = second_loop.query_frame.first;

                const auto first_loop_quert_frame_pose =
                    frames_database.GetFrame(first_loop_query_frame_id).multi_camera_data.front().pose;

                const auto second_loop_quert_frame_pose =
                    frames_database.GetFrame(second_loop_query_frame_id).multi_camera_data.front().pose;

                const auto first_query_second_query_pose_1oop = second_loop_pose.Inverse() * first_loop_pose;
                const auto first_query_second_query_pose_self =
                    second_loop_quert_frame_pose.Inverse() * first_loop_quert_frame_pose;

                const auto pose_diff =
                    first_query_second_query_pose_1oop.Inverse() * first_query_second_query_pose_self;
                const auto rot_to_rpy = pose_diff.GetRotation().RPY();
                pose_error = pose_error + std::abs(rot_to_rpy(0)) + std::abs(rot_to_rpy(1)) + std::abs(rot_to_rpy(2)) +
                             std::abs(pose_diff.GetX()) + std::abs(pose_diff.GetY()) + std::abs(pose_diff.GetZ());
            }
            LOG(INFO) << "Compute the pose error of query frame: "
                      << Utility::UnHashId(first_loop_query_frame_id).second << "!  the total error is: " << pose_error
                      << " "
                      << "! the average error is: " << (pose_error / (transform.second.size() - 1)) << "\n";
            errors_loop_id.push_back(std::make_pair(pose_error, i));
        }
        std::sort(errors_loop_id.begin(), errors_loop_id.end());
        const auto best_query_frame_id = transform.second[errors_loop_id.front().second].query_frame.first;
        const auto best_query_frame_pose_to_self =
            frames_database.GetFrame(best_query_frame_id).multi_camera_data.front().pose;
        const auto best_query_frame_pose_to_train = transform.second[errors_loop_id.front().second].T_wq;
        results.emplace(std::make_pair(transform.first.first, transform.first.second),
                        best_query_frame_pose_to_train * best_query_frame_pose_to_self.Inverse());
    }

    // add pose map2->map1, when loop can find map1->map2, but can not find map2->map1
    auto new_result = results;
    for (const auto transform : results)
    {
        std::pair<uint64_t, uint64_t> exchange_pair = std::make_pair(transform.first.second, transform.first.first);
        if (!results.count(exchange_pair))
        {
            LOG(INFO) << "Loop detector failed to find reverse loop pair! But do not worry, we add it by hand!!!\n";
            new_result.emplace(exchange_pair, (transform.second).Inverse());
        }
    }
    return new_result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unordered_map<uint64_t, std::set<uint64_t>>
GlobalOptimizer::FindLoopCandidatesForEachMap(const QueryMapToTrainMapTransformPairs& transform_between_two_maps) const
{
    std::unordered_map<uint64_t, std::set<uint64_t>> loop_map_ids_of_each_map;

    for (const auto& transform : transform_between_two_maps)
    {
        if (loop_map_ids_of_each_map.count(transform.first.first))
        {
            loop_map_ids_of_each_map.at(transform.first.first).insert(transform.first.second);
        }
        else
        {
            loop_map_ids_of_each_map.emplace(transform.first.first, std::set<uint64_t>{transform.first.second});
        }
    }
    for (const auto loop_map_ids : loop_map_ids_of_each_map)
    {
        LOG(INFO) << "---------------------------------";
        LOG(INFO) << "Query map id: " << loop_map_ids.first << ".\n";
        LOG(INFO) << "Candidate loop map ids: "
                  << "\n";
        for (auto map_id_set = loop_map_ids.second.begin(); map_id_set != loop_map_ids.second.end(); ++map_id_set)
        {
            LOG(INFO) << "map id: " << *map_id_set << "\n";
        }
    }
    LOG(INFO) << "---------------------------------";
    return loop_map_ids_of_each_map;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GlobalOptimizer::TransformCurrentMapToMap0(
    uint64_t map_id, const std::unordered_map<uint64_t, std::set<uint64_t>>& loop_map_ids_of_each_map,
    std::vector<uint64_t>& map_ids) const
{
    auto       current_map_ids = map_ids;
    const auto loop_maps_set   = loop_map_ids_of_each_map.at(map_id);
    if (*loop_maps_set.begin() == 0)
    {
        map_ids.push_back(map_id);
        map_ids.push_back(0);
        return true;
    }

    for (std::set<uint64_t>::iterator it = loop_maps_set.begin(); it != loop_maps_set.end(); ++it)
    {
        LOG(INFO) << "In Transform Current Map to Map_0: " << *it << ".\n";
        bool map_id_existed = false;
        for (const auto path : map_ids)
        {
            if (path == *it)
            {
                map_id_existed = true;
                break;
            }
        }
        if (map_id_existed)
        {
            continue;
        }

        if (map_id != map_ids.back())
        {
            map_ids.push_back(map_id);
        }

        if (TransformCurrentMapToMap0(*it, loop_map_ids_of_each_map, map_ids))
            return true;
    }
    // if not find route, give the original value
    map_ids = current_map_ids;
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase GlobalOptimizer::TransformAllLandmarksToTargetCoordinate(
    const TracksDatabase& tracks_database, const QueryMapToTrainMapTransformPairs& transforms,
    const std::unordered_map<uint64_t, std::set<uint64_t>>& loop_map_ids_of_each_map) const
{
    TracksDatabase new_tracks_database = tracks_database;

    auto new_tracks = new_tracks_database.GetAllTracks();

    for (const auto indexed_track : new_tracks)
    {
        auto track = indexed_track.second;

        const auto landmark = track.GetLandmark();

        if (!landmark)
        {
            continue;
        }
        const std::pair<uint64_t, uint64_t> map_id_landmark_id = Utility::UnHashId((uint64_t)landmark->Id());
        std::vector<uint64_t>               path_current_to_map0;

        if (map_id_landmark_id.first == 0)
        {
            continue;
        }

        if (TransformCurrentMapToMap0(map_id_landmark_id.first, loop_map_ids_of_each_map, path_current_to_map0))
        {
            uint64_t current_map_id = map_id_landmark_id.first;
            Pose3    current_pose   = Pose3::Identity();
            for (const auto& path : path_current_to_map0)
            {
                if (path == current_map_id)
                {
                    continue;
                }

                std::pair<uint64_t, uint64_t> path_transform      = std::make_pair(current_map_id, path);
                auto                          pose_query_to_train = transforms.at(path_transform);
                current_pose                                      = pose_query_to_train * current_pose;
                current_map_id                                    = path;
            }
            auto new_landmark_pose = HoloGtsam::Convert(current_pose) * landmark->Point();
            track.UpdatingState(track.GetState(), new_landmark_pose);
            new_tracks_database.UpdateFeatureTrack(landmark->Id(), track);
        }
        else
        {
            LOG(ERROR) << "GlobalOptimizer TransformAllLandmarksToTargetCoordinate --- landmark map id "
                       << map_id_landmark_id.first << ", "
                       << "landmark index " << map_id_landmark_id.second << ", does not have loop route to target map.";
            throw std::runtime_error("the current landmark does not have loop route to target map\n");
        }
    }
    return new_tracks_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<Values, FramesDatabase> GlobalOptimizer::TransformAllFramePoseToTargetCoordinate(
    const Values& values, FramesDatabase& frames_database, const QueryMapToTrainMapTransformPairs& transforms,
    const std::unordered_map<uint64_t, std::set<uint64_t>>& loop_map_ids_of_each_map) const
{
    auto  new_values          = values;
    auto  new_frames_database = frames_database;
    auto& new_indexed_frames  = new_frames_database.GetAllFrames();

    // update associated landmarks in frame
    for (auto& indexed_frame : new_indexed_frames)
    {
        auto                                frame_id        = indexed_frame.second.frame_id;
        const std::pair<uint64_t, uint64_t> map_id_frame_id = Utility::UnHashId(frame_id);
        std::vector<uint64_t>               path_current_to_map0;
        if (map_id_frame_id.first == 0)
        {
            continue;
        }

        if (TransformCurrentMapToMap0(map_id_frame_id.first, loop_map_ids_of_each_map, path_current_to_map0))
        {
            uint64_t current_map_id = map_id_frame_id.first;
            Pose3    current_pose   = Pose3::Identity();
            for (const auto& path : path_current_to_map0)
            {
                if (path == current_map_id)
                {
                    continue;
                }

                std::pair<uint64_t, uint64_t> path_transform      = std::make_pair(current_map_id, path);
                auto                          pose_query_to_train = transforms.at(path_transform);
                current_pose                                      = pose_query_to_train * current_pose;
                current_map_id                                    = path;
            }
            for (uint16_t camera_index = 0; camera_index < indexed_frame.second.multi_camera_data.size();
                 camera_index++)
            {
                // get camera index and corresponding extrinsic
                auto& T_bc = indexed_frame.second.camera_parameters->extrinsics.at(camera_index);
                // the pose of frame in Values is Twb, but the pose of new_frame_pose is Twc, so need T_bc to transform
                auto new_frame_pose = current_pose * indexed_frame.second.multi_camera_data[camera_index].pose;
                indexed_frame.second.multi_camera_data[camera_index].pose = new_frame_pose;
                new_values.erase(X(frame_id));
                new_values.insert(X(frame_id), HoloGtsam::Convert(new_frame_pose * T_bc.Inverse()));
            }
        }
        else
        {
            LOG(ERROR) << "GlobalOptimizer TransformAllFramePoseToTargetCoordinate --- frame map id "
                       << map_id_frame_id.first << ", "
                       << "frame index " << map_id_frame_id.second << ", does not have loop route to target map.";
            throw std::runtime_error("The current frame does not have loop route to target map\n");
        }
    }
    return std::make_pair(new_values, new_frames_database);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase GlobalOptimizer::UpdateTrackState(const TracksDatabase& tracks_database, const Values& new_values) const
{
    TracksDatabase new_tracks_database = tracks_database;

    auto new_tracks = new_tracks_database.GetAllTracks();
    for (auto track_index : new_tracks)
    {
        auto       track    = track_index.second;
        const auto landmark = track.GetLandmark();

        // LOG(INFO) << "Come into updata track state !!! before change: " << (int)track.GetState() << "\n";
        if (track.GetState() == FeatureTrack::State::BAD_BEFORE_OPTIMIZATION ||
            track.GetState() == FeatureTrack::State::BAD_AFTER_OPTIMIZATION)
        {
            track.UpdatingState(FeatureTrack::State::DEAD);
            continue;
        }
        else
        {
            track.UpdatingState(FeatureTrack::State::FINISHED);
            if (!landmark)
            {
                new_tracks_database.UpdateFeatureTrack(track_index.first, track);
                continue;
            }
            const auto& lm_id = landmark->Id();

            if (!new_values.exists(L(lm_id)))
            {
                new_tracks_database.Erase(lm_id);
                // new_tracks_database.UpdateFeatureTrack(track_index.first, track);
                continue;
            }
            // get update position
            const auto new_landmark_pose = new_values.at(L(lm_id)).cast<gtsam::Point3>();

            track.UpdatingState(track.GetState(), new_landmark_pose);
        }
        new_tracks_database.UpdateFeatureTrack(track_index.first, track);
        // LOG(INFO) << "Come into updata track state !!! after change: " << (int)track.GetState() << "\n";
    }
    //(void)new_values;
    return new_tracks_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MappingDatabase GlobalOptimizer::HashMappingDatabaseForMerge(const MappingDatabase& mapping_database,
                                                             MappingDatabase&       multi_mapping_database) const
{
    auto& multi_images                = multi_mapping_database.images;
    auto& multi_features              = multi_mapping_database.frame_indexed_features;
    auto& multi_imus                  = multi_mapping_database.imus;
    auto& multi_volocities            = multi_mapping_database.velocities;
    auto& multi_positions             = multi_mapping_database.positions;
    auto& multi_tracksdatabase        = multi_mapping_database.tracks_database;
    auto& multi_xvb_values            = multi_mapping_database.xvb_values;
    auto& multi_timestamp_to_frame_id = multi_mapping_database.timestamp_to_frame_id;
    auto& multi_frame_id_to_timestamp = multi_mapping_database.frame_id_to_timestamp;

    MappingDatabase new_mapping_database;
    // do hash
    FrameIndexedImages               hashed_images;
    FrameIndexedFeatures             hashed_features;
    std::vector<std::vector<Imu>>    hashed_imus;
    std::vector<VelocityMeasurement> hashed_velocities;
    std::vector<UtmPosition>         hashed_positions;
    TracksDatabase                   hashed_tracks_database;
    Values                           hashed_xvb_values;
    std::map<Timestamp, uint64_t>    hashed_timestamp_to_frame_id;
    std::map<uint64_t, Timestamp>    hashed_frame_id_to_timestamp;

    // get map id
    const uint64_t map_id = mapping_database.map_id;
    // hash image id
    for (auto image : mapping_database.images)
    {
        auto frame_id                  = image.first;
        auto hashed_frame_id           = Utility::HashId(map_id, frame_id);
        hashed_images[hashed_frame_id] = image.second;
        multi_images[hashed_frame_id]  = image.second;
    }
    // hash feature id
    for (auto feature : mapping_database.frame_indexed_features)
    {
        auto frame_id                    = feature.first;
        auto hashed_frame_id             = Utility::HashId(map_id, frame_id);
        hashed_features[hashed_frame_id] = feature.second;
        multi_features[hashed_frame_id]  = feature.second;
    }
    // hash imus timestamp
    for (auto imus : mapping_database.imus)
    {
        std::vector<Imu> vector_imus;
        for (auto imu : imus)
        {
            // get imu original timestamp
            uint64_t timestamp = imu.GetTimestamp().ToNsec();
            // cal imu hashed timestamp
            timestamp = timestamp + (uint64_t)(map_id * 10e17);
            imu.SetTimestamp(Timestamp(timestamp));
            vector_imus.push_back(imu);
        }
        hashed_imus.push_back(vector_imus);
        multi_imus.push_back(vector_imus);
    }
    // hash velocity timestamp
    for (auto velocity : mapping_database.velocities)
    {
        // get velocity original timestamp
        auto timestamp = velocity.timestamp.ToNsec();
        // cal imu hashed timestamp
        timestamp          = timestamp + (int64_t)(map_id * 10e17);
        velocity.timestamp = Timestamp((uint64_t)timestamp);
        hashed_velocities.push_back(velocity);
        multi_volocities.push_back(velocity);
    }
    // hash UTM postion timestamp
    for (auto position : mapping_database.positions)
    {
        // get positon original timestamp
        auto timestamp     = position.timestamp.ToNsec();
        timestamp          = timestamp + (int64_t)(map_id * 10e17);
        position.timestamp = Timestamp((uint64_t)timestamp);
        hashed_positions.push_back(position);
        multi_positions.push_back(position);
    }
    // hash track database's landmark id and frame id
    auto old_tracks = mapping_database.tracks_database.GetAllTracks();
    for (auto track_index : old_tracks)
    {
        // get original landmark id and pose
        auto track          = track_index.second;
        auto landmark       = track.GetLandmark();
        auto landmark_id    = track.Id();
        auto landmark_point = landmark->Point();
        auto state          = track.GetState();
        auto measurements   = track.Measurements();
        // get camera parameters
        auto camera_parameters = track.CameraParams();
        // hash landmark id
        landmark_id = Utility::HashId(map_id, landmark_id);
        // creat new landmark
        Landmark new_landmark(landmark_id, landmark_point);
        // declear new measurements
        std::vector<FeatureTrack::Measurement> hashed_measurements;
        for (auto measurement : measurements)
        {
            // get original frame id
            auto frame_id = measurement.first;
            // hash frame id
            auto hashed_frame_id = Utility::HashId(map_id, frame_id);
            // creat new measurement
            FeatureTrack::Measurement hashed_measurement = std::make_pair(hashed_frame_id, measurement.second);
            hashed_measurements.push_back(hashed_measurement);
        }
        // create track parameters
        FeatureTrack::Parameters::ConstPtr track_params = std::make_shared<FeatureTrack::Parameters>(true, true);
        // creat new track
        FeatureTrack new_track(track_params, camera_parameters, landmark_id, hashed_measurements, state, new_landmark);
        hashed_tracks_database.AddFeatureTrack(new_track);
        multi_tracksdatabase.AddFeatureTrack(new_track);
    }
    // hash values frame id
    Values old_values = mapping_database.xvb_values;
    for (auto image : mapping_database.frame_id_to_timestamp)
    {
        auto frame_id = image.first;
        if (!old_values.exists(X(frame_id)))
        {
            LOG(ERROR) << "MapDatabaseManager --- LoadXVBValues. frame id: " << frame_id
                       << " not exist in unhash values.\n";
            throw std::runtime_error("MapDatabaseManager --- LoadXVBValues. frame id not exist in unhash values.");
        }
        auto hashed_frame_id = Utility::HashId(map_id, frame_id);

        // add new pose value
        hashed_xvb_values.insert(X(hashed_frame_id), old_values.at(X(frame_id)).cast<gtsam::Pose3>());
        multi_xvb_values.insert(X(hashed_frame_id), old_values.at(X(frame_id)).cast<gtsam::Pose3>());

        // add new velocity value
        hashed_xvb_values.insert(V(hashed_frame_id), old_values.at(V(frame_id)).cast<gtsam::Vector3>());
        multi_xvb_values.insert(V(hashed_frame_id), old_values.at(V(frame_id)).cast<gtsam::Vector3>());

        // add new bias value
        hashed_xvb_values.insert(B(hashed_frame_id), old_values.at(B(frame_id)).cast<gtsam::imuBias::ConstantBias>());
        multi_xvb_values.insert(B(hashed_frame_id), old_values.at(B(frame_id)).cast<gtsam::imuBias::ConstantBias>());
    }
    // hash frame id and timestamp
    for (auto time_frame : mapping_database.timestamp_to_frame_id)
    {
        // get original timestamp
        uint64_t timestamp = time_frame.first.ToNsec();
        timestamp          = timestamp + (uint64_t)(map_id * 10e17);
        // get original frame id
        uint64_t frame_id = time_frame.second;
        frame_id          = Utility::HashId(map_id, frame_id);
        // creat new timestamp to frame id
        hashed_timestamp_to_frame_id.emplace(Timestamp(timestamp), frame_id);
        hashed_frame_id_to_timestamp.emplace(frame_id, Timestamp(timestamp));
        multi_timestamp_to_frame_id.emplace(Timestamp(timestamp), frame_id);
        multi_frame_id_to_timestamp.emplace(frame_id, Timestamp(timestamp));
    }

    new_mapping_database.map_id                 = map_id;
    new_mapping_database.images                 = hashed_images;
    new_mapping_database.frame_indexed_features = hashed_features;
    new_mapping_database.imus                   = hashed_imus;
    new_mapping_database.velocities             = hashed_velocities;
    new_mapping_database.positions              = hashed_positions;
    new_mapping_database.tracks_database        = hashed_tracks_database;
    new_mapping_database.xvb_values             = hashed_xvb_values;
    new_mapping_database.timestamp_to_frame_id  = hashed_timestamp_to_frame_id;
    new_mapping_database.frame_id_to_timestamp  = hashed_frame_id_to_timestamp;
    new_mapping_database.camera_parameters      = mapping_database.camera_parameters;
    return new_mapping_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TracksDatabase GlobalOptimizer::FindMoreMappointsInFrame(const FramesDatabase& old_frame_database,
                                                         const FramesDatabase& new_frame_database,
                                                         const Values&         optimized_values,
                                                         const TracksDatabase& track_database) const
{
    if (old_frame_database.Size() < 10)
    {
        LOG(WARNING) << "GlobalOptimizer FindMoreMappointsInFrame --- old frame database size is less "
                        "than threshold, do not do EpipolarLineMatching";
        return {};
    }

    /// select 10 candidate frames to do epipolar matching
    std::vector<uint64_t> target_frames_ids;
    target_frames_ids.reserve(parameters_.frame_num_selected_for_epipolar_matching);
    uint16_t target_frames_count = 0;
    uint64_t selected_frame_id   = 0;

    while (target_frames_count < parameters_.frame_num_selected_for_epipolar_matching &&
           selected_frame_id < new_frame_database.Size())
    {
        if (old_frame_database.Exists(selected_frame_id))
        {
            target_frames_ids.emplace_back(selected_frame_id);
            ++target_frames_count;
        }
        ++selected_frame_id;
    }

    const auto source_frame      = old_frame_database.GetFrame(target_frames_ids.front());
    auto&      multi_camera_data = source_frame.multi_camera_data;

    std::vector<FeatureTrack> new_tracks;
    new_tracks.reserve(multi_camera_data.size() * multi_camera_data.at(0).features.size());

    for (uint16_t camera_index = 0; camera_index < multi_camera_data.size(); ++camera_index)
    {
        Features source_features = multi_camera_data.at(camera_index).features;

        for (const auto& feature : source_features)
        {
            /// For each feature construct one FeatureTrack, whose first measurement is this feature
            FeatureTrack::CameraIndexedFeature camera_indexed_feature;
            camera_indexed_feature.emplace(camera_index, feature);
            FeatureTrack track = FeatureTrack::CreateNewTrack(
                std::make_shared<FeatureTrack::Parameters>(false, false), source_frame.camera_parameters,
                FeatureTrack::Measurement(source_frame.frame_id, camera_indexed_feature));

            for (size_t i = 1; i < target_frames_ids.size(); ++i)
            {
                uint64_t target_frame_id = target_frames_ids.at(i);

                /// matching through epipolar constraint
                const auto& target_frame    = old_frame_database.GetFrame(target_frame_id);
                Features    target_features = target_frame.multi_camera_data.at(camera_index).features;
                DescriptorMatcher::FeaturesWithObservedPoses first_data;
                DescriptorMatcher::FeaturesWithObservedPoses second_data;
                second_data.reserve(target_features.size());

                uint64_t last_tracked_frame_id = track.NewestMeasurement().first;
                Feature  last_tracked_feature  = track.NewestMeasurement().second.at(camera_index);

                /// get frame pose from new frame database
                const auto& last_tracked_frame_pose =
                    new_frame_database.GetFrame(last_tracked_frame_id).multi_camera_data.at(camera_index).pose;
                first_data.emplace_back(last_tracked_feature, last_tracked_frame_pose);
                const Pose3 target_frame_pose =
                    new_frame_database.GetFrame(target_frame_id).multi_camera_data.at(camera_index).pose;

                /// get features from old frame database
                for (const auto& target_feature : target_features)
                {
                    second_data.emplace_back(target_feature, target_frame_pose);
                }

                const auto match_pairs =
                    DescriptorMatcher::EpipolarLineMatching(first_data, second_data, 4e-3, 0.8, 0.75);

                if (!match_pairs.empty() && match_pairs.size() == 1)
                {
                    track.AddNewestMeasurement(target_frame_id, target_features.at(match_pairs[0].second));
                }
            }

            new_tracks.emplace_back(track);
        }
    }

    /// triangulate new tracks
    auto     indexed_tracks  = track_database.GetAllTracks();
    uint64_t success_tri_num = 0;
    for (auto& track : new_tracks)
    {
        const FeatureTrack::State track_state = track.GetState();
        if (track_state == FeatureTrack::State::CANDIDATE)
        {
            Triangulator triangulator(parameters_.triangulator_params, track.CameraParams());
            auto         result = triangulator.Run(track, optimized_values);

            if (result)
            {
                track.UpdatingState(FeatureTrack::State::FRESH, HoloGtsam::Convert(*result));
                indexed_tracks.emplace(track.Id(), track);
                ++success_tri_num;
            }
            else
            {
                track.UpdatingState(FeatureTrack::State::BAD_BEFORE_OPTIMIZATION);
            }
        }
    }

    LOG(INFO) << "GlobalOptimizer FindMoreMappointsInFrame --- tracks size: " << new_tracks.size()
              << "\n landmark through epipolar matching in first frame:" << success_tri_num;

    /// remove original landmarks in first frame and add new landmarks;
    for (uint16_t camera_index = 0; camera_index < multi_camera_data.size(); ++camera_index)
    {
        auto original_first_frame_landmarks =
            new_frame_database.GetFrame(source_frame.frame_id).multi_camera_data.at(camera_index).associated_landmarks;

        for (const auto first_frame_landmark : original_first_frame_landmarks)
        {
            if (indexed_tracks.count(first_frame_landmark))
            {
                indexed_tracks.erase(first_frame_landmark);
            }
        }
    }

    TracksDatabase new_track_database;
    for (const auto& indexed_track : indexed_tracks)
    {
        new_track_database.AddFeatureTrack(indexed_track.second);
    }

    return new_track_database;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GlobalOptimizer::DrawMappingMergeLoop(const LoopClosingResults& loop_results,
                                           const TracksDatabase&     tracks_database,
                                           const TracksDatabase&     unmerged_tracks_database,
                                           const FramesDatabase&     frames_database,
                                           const FramesDatabase&     unmerged_frames_database,
                                           const uint64_t&           maps_number) const
{
    auto query_frames          = frames_database.GetAllFrames();
    auto unmerged_query_frames = unmerged_frames_database.GetAllFrames();

    std::unordered_map<uint64_t, std::set<uint64_t>> loop_pairs;

    for (auto loop : loop_results)
    {
        std::pair<uint64_t, uint64_t> loop_pair = std::make_pair(loop.query_frame.first, loop.train_frame.first);
        if (loop_pairs.count(loop_pair.first))
        {
            loop_pairs.at(loop_pair.first).insert(loop_pair.second);
        }
        else if (loop_pairs.count(loop_pair.second))
        {
            loop_pairs.at(loop_pair.second).insert(loop_pair.first);
        }

        else
        {
            loop_pairs.emplace(loop_pair.first, std::set<uint64_t>{loop_pair.second});
            loop_pairs.emplace(loop_pair.second, std::set<uint64_t>{loop_pair.first});
        }
    }

    // get camera parameters
    const auto camera_parameters_ptr = query_frames.begin()->second.camera_parameters;
    for (int i = 0; i < (int)(camera_parameters_ptr->camera_coords.size()); i++)
    {
        cv::namedWindow(camera_parameters_ptr->camera_coords.at(i), CV_WINDOW_KEEPRATIO);
    }
    cv::namedWindow("Left_query_frame_Right_train_frame", CV_WINDOW_KEEPRATIO);
    LOG(INFO) << "Come into to draw loop !!!\n";
#ifdef HOLO_VISUALIZE_WITH_PCL
    static mapping::Visualizer visualizer;
    for (uint64_t local_map_id = 0; local_map_id < maps_number; local_map_id++)
    {
        LOG(INFO) << "PCL IS OPEN !!!\n";
        // erase local map, but retain golbal map
        if (local_map_id > 0)
        {
            LOG(INFO) << "Come into erase local map !!!\n";
            visualizer.EraseLocalMap();
            LOG(INFO) << "Come into update map !!!\n";
            visualizer.Update();
            visualizer.ClearLocalMapRecord();
            LOG(INFO) << "Finished erase local map !!!\n";
        }

        for (auto query_frame_map : query_frames)
        {
            auto query_frame_id       = query_frame_map.first;
            auto query_frame          = query_frame_map.second;
            auto unmerged_query_frame = unmerged_query_frames.at(query_frame_id);

            if (Utility::UnHashId(query_frame_id).first == local_map_id)
            {
                static auto stop_frame_id = query_frame_id;

                for (uint16_t camera_index = 0; camera_index < query_frame_map.second.multi_camera_data.size();
                     camera_index++)
                {
                    // visualize loop edge
                    if (loop_pairs.count(query_frame_id))
                    {
                        for (auto train_frame_id : loop_pairs.at(query_frame_id))
                        {
                            if (Utility::UnHashId(train_frame_id).first <= local_map_id)
                            {
                                visualizer.DrawLoop(
                                    query_frames.at(train_frame_id).multi_camera_data.at(camera_index).pose,
                                    unmerged_query_frame.multi_camera_data.at(camera_index).pose, 255, 0, 0, true);

                                // draw match image
                                const auto& query_image_name =
                                    unmerged_query_frame.multi_camera_data.at(camera_index).image_name;
                                const auto& train_image_name =
                                    query_frames.at(train_frame_id).multi_camera_data.at(camera_index).image_name;

                                auto query_map_id        = Utility::UnHashId(query_frame_id).first;
                                auto query_frame_id_self = Utility::UnHashId(query_frame_id).second;
                                auto train_map_id        = Utility::UnHashId(train_frame_id).first;
                                auto train_frame_id_self = Utility::UnHashId(train_frame_id).second;

                                cv::Mat query_frame = cv::imread(query_image_name, cv::IMREAD_GRAYSCALE);
                                cv::Mat train_frame = cv::imread(train_image_name, cv::IMREAD_GRAYSCALE);

                                int height      = query_frame.rows;
                                int query_width = query_frame.cols;
                                int train_width = train_frame.cols;

                                // combine two images
                                cv::Mat loop_images;
                                loop_images.create(height, query_width + train_width, query_frame.type());
                                cv::Mat r1 = loop_images(cv::Rect(0, 0, query_width, height));
                                query_frame.copyTo(r1);
                                cv::Mat r2 = loop_images(cv::Rect(query_width, 0, train_width, height));
                                train_frame.copyTo(r2);
                                cv::imshow("Left_query_frame_Right_train_frame", loop_images);
                                std::string loop_images_name = "Query_MapId_" + std::to_string(query_map_id) +
                                                               "_Query_FrameId_" + std::to_string(query_frame_id_self) +
                                                               "_Train_MapId_" + std::to_string(train_map_id) +
                                                               "_Train_FrameId_" + std::to_string(train_frame_id_self) +
                                                               ".png";
                                const auto config_root_dir = holo::GetHoloConfigRootDirectory() + "/";
                                cv::imwrite(config_root_dir + "holo_localization_parking/vslam/loop_images/" +
                                                loop_images_name,
                                            loop_images);
                                cv::waitKey(50);
                            }
                        }
                    }

                    // visualize feature tracks
                    // get query frame camera parameters
                    const auto query_camera_parameters = query_frame.camera_parameters;
                    const auto image                   = visualizer.VisualizeTracks(query_frame, camera_index,
                                                                  query_camera_parameters->intrinsics.at(camera_index),
                                                                  tracks_database.GetAllTracks());
                    cv::imshow(query_camera_parameters->camera_coords.at(camera_index), image);
                    if (stop_frame_id == query_frame_id)
                    {
                        cv::waitKey(50);
                    }
                    else
                    {
                        cv::waitKey(50);
                    }

                    // visualize landmarks and camera trajectory
                    // draw golbal map
                    visualizer.DrawLandmarks(tracks_database.GetAllTracks(),
                                             query_frame.multi_camera_data.at(camera_index).associated_landmarks);
                    visualizer.DrawTrajectory(query_frame.multi_camera_data.at(camera_index).pose, 0, 255, 0);
                    // visualizer.DrawCamera(query_frame.multi_camera_data.at(camera_index).pose, 0, 255, 0);

                    // draw local map
                    visualizer.DrawLandmarks(
                        unmerged_tracks_database.GetAllTracks(),
                        unmerged_query_frame.multi_camera_data.at(camera_index).associated_landmarks, true);
                    visualizer.DrawTrajectory(unmerged_query_frame.multi_camera_data.at(camera_index).pose, 0, 255, 0,
                                              true);
                    visualizer.DrawCamera(unmerged_query_frame.multi_camera_data.at(camera_index).pose, 0, 255, 0,
                                          true);
                    visualizer.Update();
                }
            }
        }
    }
#else
    (void)tracks_database;
    (void)unmerged_tracks_database;
    (void)maps_number;
    LOG(INFO) << "PCL NOT OPEN !!!\n";
#endif
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
