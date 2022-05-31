/*!
 * \brief Unit test for graph builder in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-17-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LinearContainerFactor.h>

#include <holo/localization/vision/vslam/graph_builder.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(FactorMeasurements, Constructor)
{
    PreintegratedImuMeasurements pim = PreintegratedImuMeasurements();
    MapProjectionMeasurements    mpm{};
    Vector3                      velocity(1.0, 1.0, 1.0);
    VelocityMeasurement          vm;
    vm.velocity = velocity;

    Values predicted_values{};
    Pose3  gt_pose = Pose3::Identity();

    // create FactorMeasurements
    FactorMeasurements fm(pim, mpm, vm, predicted_values, gt_pose);

    /// @brief check result
    ASSERT_EQ(velocity, fm.vm.velocity);
    ASSERT_TRUE(fm.predicted_values.empty());
    ASSERT_EQ(gt_pose, fm.gt_pose);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GraphBuilderParameters, Constructor)
{
    const PriorVehicleStateNoise prior_noise = PriorVehicleStateNoise::Example();
    Vector6                      bias_between_sigma(0.1, -0.2, 0.3, -0.4, 0.5, -0.6);
    const Vector3                velocity_factor_sigma(-0.1, 0.2, -0.3);
    const Vector3                velocity_factor_sigma_when_turns(0.1, -0.2, 0.4);
    const Vector3                low_precision_velocity_factor_sigma(0.1, -0.3, 0.7);
    const Vector2                pose_only_unit3_factor_sigma(0.1, 0.1);
    Vector6                      zero_velocity_between_pose_sigma(0.1, -0.2, 0.3, -0.4, 0.5, -0.6);
    Vector6                      gt_pose_sigma(0.1, -0.2, 0.3, -0.4, 0.5, -0.6);
    const Scalar                 pose_only_huber_loss = 0.01;

    // construct parameters
    const GraphBuilder::Parameters parameters(
        prior_noise, bias_between_sigma, velocity_factor_sigma, velocity_factor_sigma_when_turns,
        low_precision_velocity_factor_sigma, pose_only_unit3_factor_sigma, zero_velocity_between_pose_sigma,
        gt_pose_sigma, pose_only_huber_loss, true, true, false, false, false, false);

    /// @brief check result
    ASSERT_EQ(prior_noise.pose_sigma, parameters.prior_noise.pose_sigma);
    ASSERT_EQ(prior_noise.velocity_sigma, parameters.prior_noise.velocity_sigma);
    ASSERT_EQ(prior_noise.bias_sigma, parameters.prior_noise.bias_sigma);
    ASSERT_EQ(bias_between_sigma, parameters.bias_between_sigma);
    ASSERT_EQ(velocity_factor_sigma, parameters.velocity_factor_sigma);
    ASSERT_EQ(velocity_factor_sigma_when_turns, parameters.velocity_factor_sigma_when_turns);
    ASSERT_EQ(low_precision_velocity_factor_sigma, parameters.low_precision_velocity_factor_sigma);
    ASSERT_EQ(pose_only_unit3_factor_sigma, parameters.pose_only_unit3_factor_sigma);
    ASSERT_EQ(zero_velocity_between_pose_sigma, parameters.zero_velocity_between_pose_sigma);
    ASSERT_EQ(gt_pose_sigma, parameters.gt_pose_sigma);
    ASSERT_EQ(pose_only_huber_loss, parameters.pose_only_huber_loss);
    ASSERT_TRUE(parameters.enable_velocity_factor);
    ASSERT_TRUE(parameters.enable_zero_velocity_factor);
    ASSERT_FALSE(parameters.enable_prior_factor);
    ASSERT_FALSE(parameters.enable_pose_only_unit3_factor);
    ASSERT_FALSE(parameters.enable_unit3_factor);
    ASSERT_FALSE(parameters.enable_gt_pose_factor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GraphBuilderParameters, Example)
{
    const PriorVehicleStateNoise prior_noise = PriorVehicleStateNoise::Example();
    Vector6                      bias_between_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    const Vector3                velocity_factor_sigma(0.1, 0.1, 0.1);
    const Vector3                velocity_factor_sigma_when_turns(0.1, 0.1, 0.1);
    const Vector2                pose_only_unit3_factor_sigma(0.1, 0.1);
    Vector6                      zero_velocity_between_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    Vector6                      gt_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    const Scalar                 pose_only_huber_loss(0.5);

    // construct parameters
    const GraphBuilder::Parameters parameters = GraphBuilder::Parameters::Example();

    /// @brief check result
    ASSERT_EQ(prior_noise.pose_sigma, parameters.prior_noise.pose_sigma);
    ASSERT_EQ(prior_noise.velocity_sigma, parameters.prior_noise.velocity_sigma);
    ASSERT_EQ(prior_noise.bias_sigma, parameters.prior_noise.bias_sigma);
    ASSERT_EQ(bias_between_sigma, parameters.bias_between_sigma);
    ASSERT_EQ(velocity_factor_sigma, parameters.velocity_factor_sigma);
    ASSERT_EQ(velocity_factor_sigma_when_turns, parameters.velocity_factor_sigma_when_turns);
    ASSERT_EQ(pose_only_unit3_factor_sigma, parameters.pose_only_unit3_factor_sigma);
    ASSERT_EQ(zero_velocity_between_pose_sigma, parameters.zero_velocity_between_pose_sigma);
    ASSERT_EQ(gt_pose_sigma, parameters.gt_pose_sigma);
    ASSERT_EQ(pose_only_huber_loss, parameters.pose_only_huber_loss);
    ASSERT_TRUE(parameters.enable_velocity_factor);
    ASSERT_TRUE(parameters.enable_zero_velocity_factor);
    ASSERT_TRUE(parameters.enable_prior_factor);
    ASSERT_TRUE(parameters.enable_pose_only_unit3_factor);
    ASSERT_TRUE(parameters.enable_unit3_factor);
    ASSERT_FALSE(parameters.enable_gt_pose_factor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GraphBuilder, Problem)
{
    FactorGraph factor_graph = FactorGraph();
    Values      values       = Values();

    // construct parameters
    const GraphBuilder::Problem problem(factor_graph, values);

    /// @brief check result
    ASSERT_TRUE(problem.factor_graph.empty());
    ASSERT_TRUE(problem.values.empty());
    ASSERT_TRUE(problem.Empty());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GraphBuilder, Constructor)
{
    const PriorVehicleStateNoise prior_noise = PriorVehicleStateNoise::Example();
    Vector6                      bias_between_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    const Vector3                velocity_factor_sigma(0.1, 0.1, 0.1);
    const Vector3                velocity_factor_sigma_when_turns(0.1, 0.1, 0.1);
    const Vector2                pose_only_unit3_factor_sigma(0.1, 0.1);
    Vector6                      zero_velocity_between_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    Vector6                      gt_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    const Scalar                 pose_only_huber_loss(0.5);

    // construct parameters
    const GraphBuilder::Parameters parameters = GraphBuilder::Parameters::Example();

    // camera parameters
    CameraParameters::Ptr camera_params = CameraParameters::Example();

    // create builder
    const GraphBuilder builder(parameters, camera_params);

    /// @brief check result
    ASSERT_EQ(prior_noise.pose_sigma, builder.Params().prior_noise.pose_sigma);
    ASSERT_EQ(prior_noise.velocity_sigma, builder.Params().prior_noise.velocity_sigma);
    ASSERT_EQ(prior_noise.bias_sigma, builder.Params().prior_noise.bias_sigma);
    ASSERT_EQ(bias_between_sigma, builder.Params().bias_between_sigma);
    ASSERT_EQ(velocity_factor_sigma, builder.Params().velocity_factor_sigma);
    ASSERT_EQ(velocity_factor_sigma_when_turns, builder.Params().velocity_factor_sigma_when_turns);
    ASSERT_EQ(pose_only_unit3_factor_sigma, builder.Params().pose_only_unit3_factor_sigma);
    ASSERT_EQ(zero_velocity_between_pose_sigma, builder.Params().zero_velocity_between_pose_sigma);
    ASSERT_EQ(gt_pose_sigma, builder.Params().gt_pose_sigma);
    ASSERT_EQ(pose_only_huber_loss, builder.Params().pose_only_huber_loss);
    ASSERT_TRUE(builder.Params().enable_velocity_factor);
    ASSERT_TRUE(builder.Params().enable_zero_velocity_factor);
    ASSERT_TRUE(builder.Params().enable_prior_factor);
    ASSERT_TRUE(builder.Params().enable_pose_only_unit3_factor);
    ASSERT_TRUE(builder.Params().enable_unit3_factor);
    ASSERT_FALSE(builder.Params().enable_gt_pose_factor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GraphBuilder, Initialize)
{
    // create builder
    GraphBuilder builder(GraphBuilder::Parameters::Example(), CameraParameters::Example());

    // create initial vehicle state and initial velocity measurement
    const VehicleState  initial_vehicle_state(Point3(1.1, -1.2, 1.3), Rot3::Rz(0.5), Vector3(2.1, -2.2, 2.3),
                                             Vector3(0.03, -0.04, 0.05), Vector3(-0.06, 0.07, -0.08));
    const Vector3       initial_velocity(0.1, -0.2, 0.3);
    VelocityMeasurement vm;
    vm.velocity    = initial_velocity;
    vm.reliability = VelocityMeasurementReliability::HIGH;

    // call initialize
    FactorMeasurements fm;
    fm.vm                                    = vm;
    const uint64_t       initial_frame_index = 0;
    const gtsam::Pose3   prior_pose          = holo::localization::HoloGtsam::Convert(initial_vehicle_state.Pose());
    const gtsam::Vector3 prior_velocity      = holo::localization::HoloGtsam::Convert(initial_vehicle_state.Velocity());
    const gtsam::imuBias::ConstantBias prior_bias(
        holo::localization::HoloGtsam::Convert(initial_vehicle_state.AccBias()),
        holo::localization::HoloGtsam::Convert(initial_vehicle_state.GyroBias()));
    fm.predicted_values.insert(X(initial_frame_index), prior_pose);
    fm.predicted_values.insert(V(initial_frame_index), prior_velocity);
    fm.predicted_values.insert(B(initial_frame_index), prior_bias);
    const auto graph = builder.Initialize(fm, initial_frame_index);

    // check result
    ASSERT_EQ(graph.factor_graph.size(), 4u);
    ASSERT_EQ(graph.values.size(), 3u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GraphBuilder, Run)
{
    uint16_t camera_index = 0;

    gtsam::Values value;
    value.insert(X(2), gtsam::Pose3::identity());
    gtsam::imuBias::ConstantBias dummy_bias;
    value.insert(B(2), dummy_bias);
    value.insert(V(2), gtsam::Vector3(1, 2, 3));

    gtsam::PreintegratedImuMeasurements pim(gtsam::PreintegrationParams::MakeSharedU());

    for (size_t i = 0; i < 10u; i++)
    {
        const Scalar dt = i == 0 ? 0 : 0.01;
        pim.integrateMeasurement(holo::localization::HoloGtsam::Convert(Vector3(0, 1, 2)),
                                 holo::localization::HoloGtsam::Convert(Vector3(1, 2, 3)), dt);
    }

    Vector3             velocity(1.1, 2.1, 3.1);
    VelocityMeasurement vm;
    vm.velocity    = velocity;
    vm.reliability = VelocityMeasurementReliability::HIGH;

    MapProjectionMeasurements mpm;

    for (int i = 0; i < 3; i++)
    {
        uint64_t frame_id = 2;
        Vector3  bearing(i + 1, i + 2, i + 3);
        MapPoint point;
        point.position   = Point3(i + 10, i + 11, i + 12);
        point.direction  = Vector3(0, 0, 0);
        point.covariance = Matrix3::Identity();
        point.descriptor = cv::Mat::eye(1, 256, CV_32F);
        MapProjectionMeasurement measurement(frame_id, camera_index, std::make_shared<MapPoint>(point), bearing);
        mpm.push_back(measurement);
    }

    std::vector<FeatureTrack::Measurement> measurements;

    for (size_t i = 0; i <= 2; i++)
    {
        const Feature feature(cv::Point2f(i, i + 1), boost::none, Point3(i, i + 1, 1.0), camera_index);
        measurements.emplace_back(i, FeatureTrack::CameraIndexedFeature{{camera_index, feature}});
    }

    FeatureTrack track(std::make_shared<FeatureTrack::Parameters>(FeatureTrack::Parameters::Example()),  // parameters
                       CameraParameters::Example(), 2,           // camera parameters, track_id
                       measurements,                             // measuremets
                       FeatureTrack::State::LIVE,                // state
                       Landmark(2, gtsam::Point3(10, 11, 12)));  // use track id as landmark id

    std::vector<FeatureTrack> tracks;
    tracks.push_back(track);
    SlidingWindowState::static_tracker_state = Tracker::State(2, holo::Timestamp(), tracks);

    GraphBuilder builder(GraphBuilder::Parameters::Example(), CameraParameters::Example());

    FactorMeasurements factor_measurement(pim, mpm, vm, value, boost::none);

    const auto new_problem = builder.Run(factor_measurement, tracks, 2);
    ASSERT_EQ(new_problem.factor_graph.size(), 7u);
    ASSERT_EQ(new_problem.values.size(), 3u);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
