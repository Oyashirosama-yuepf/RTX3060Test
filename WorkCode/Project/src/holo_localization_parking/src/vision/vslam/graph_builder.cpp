/*!
 * \brief graph builder class in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/graph_builder.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GraphBuilder::Parameters GraphBuilder::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const auto prior_noise = PriorVehicleStateNoise::LoadFromYaml(node["prior_noise"]);

    Vector6 wheel_integration_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            node["wheel_integration_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        wheel_integration_factor_sigma(0) = sigma_node.IsNull() ? 100.0 : sigma_node[0].as<Scalar>();
        wheel_integration_factor_sigma(1) = sigma_node.IsNull() ? 100.0 : sigma_node[1].as<Scalar>();
        wheel_integration_factor_sigma(2) = sigma_node.IsNull() ? 1e-2 : sigma_node[2].as<Scalar>();
        wheel_integration_factor_sigma(3) = sigma_node.IsNull() ? 1e-2 : sigma_node[3].as<Scalar>();
        wheel_integration_factor_sigma(4) = sigma_node.IsNull() ? 1e-2 : sigma_node[4].as<Scalar>();
        wheel_integration_factor_sigma(5) = sigma_node.IsNull() ? 100.0 : sigma_node[5].as<Scalar>();
    }

    Vector6 bias_between_sigma;
    {
        const holo::yaml::Node sigma_node = node["bias_between_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        bias_between_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        bias_between_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        bias_between_sigma(2) = sigma_node.IsNull() ? 4e-4 : sigma_node[2].as<Scalar>();
        bias_between_sigma(3) = sigma_node.IsNull() ? 5e-6 : sigma_node[3].as<Scalar>();
        bias_between_sigma(4) = sigma_node.IsNull() ? 5e-6 : sigma_node[4].as<Scalar>();
        bias_between_sigma(5) = sigma_node.IsNull() ? 2e-6 : sigma_node[5].as<Scalar>();
    }

    Vector3 velocity_factor_sigma;
    {
        const holo::yaml::Node sigma_node = node["velocity_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        velocity_factor_sigma(0) = sigma_node.IsNull() ? 0.034 : sigma_node[0].as<Scalar>();
        velocity_factor_sigma(1) = sigma_node.IsNull() ? 0.034 : sigma_node[1].as<Scalar>();
        velocity_factor_sigma(2) = sigma_node.IsNull() ? 0.034 : sigma_node[2].as<Scalar>();
    }

    Vector3 velocity_factor_sigma_when_turns;
    {
        const holo::yaml::Node sigma_node =
            node["velocity_factor_sigma_when_turns"].as<holo::yaml::Node>(holo::yaml::Node());

        velocity_factor_sigma_when_turns(0) = sigma_node.IsNull() ? 0.034 : sigma_node[0].as<Scalar>();
        velocity_factor_sigma_when_turns(1) = sigma_node.IsNull() ? 0.1 : sigma_node[1].as<Scalar>();
        velocity_factor_sigma_when_turns(2) = sigma_node.IsNull() ? 0.034 : sigma_node[2].as<Scalar>();
    }

    Vector3 low_precision_velocity_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            node["low_precision_velocity_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        low_precision_velocity_factor_sigma(0) = sigma_node.IsNull() ? 0.1 : sigma_node[0].as<Scalar>();
        low_precision_velocity_factor_sigma(1) = sigma_node.IsNull() ? 0.034 : sigma_node[1].as<Scalar>();
        low_precision_velocity_factor_sigma(2) = sigma_node.IsNull() ? 0.034 : sigma_node[2].as<Scalar>();
    }

    Vector2 pose_only_unit3_factor_sigma;
    {
        const holo::yaml::Node sigma_node =
            node["pose_only_unit3_factor_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        pose_only_unit3_factor_sigma(0) = sigma_node.IsNull() ? 0.05 : sigma_node[0].as<Scalar>();
        pose_only_unit3_factor_sigma(1) = sigma_node.IsNull() ? 0.05 : sigma_node[1].as<Scalar>();
    }

    Vector6 zero_velocity_between_pose_sigma;
    {
        const holo::yaml::Node sigma_node =
            node["zero_velocity_between_pose_sigma"].as<holo::yaml::Node>(holo::yaml::Node());
        zero_velocity_between_pose_sigma(0) = sigma_node.IsNull() ? 1e-3 : sigma_node[0].as<Scalar>();
        zero_velocity_between_pose_sigma(1) = sigma_node.IsNull() ? 1e-3 : sigma_node[1].as<Scalar>();
        zero_velocity_between_pose_sigma(2) = sigma_node.IsNull() ? 1e-3 : sigma_node[2].as<Scalar>();
        zero_velocity_between_pose_sigma(3) = sigma_node.IsNull() ? 0.00175 : sigma_node[3].as<Scalar>();
        zero_velocity_between_pose_sigma(4) = sigma_node.IsNull() ? 0.00175 : sigma_node[4].as<Scalar>();
        zero_velocity_between_pose_sigma(5) = sigma_node.IsNull() ? 0.00175 : sigma_node[5].as<Scalar>();
    }

    Vector6 gt_pose_sigma;
    {
        const holo::yaml::Node sigma_node = node["gt_pose_sigma"].as<holo::yaml::Node>(holo::yaml::Node());

        // order is roll, pitch, yaw，x, y, z
        gt_pose_sigma(0) = sigma_node.IsNull() ? 0.034 : sigma_node[0].as<Scalar>(0.034);
        gt_pose_sigma(1) = sigma_node.IsNull() ? 0.034 : sigma_node[1].as<Scalar>(0.034);
        gt_pose_sigma(2) = sigma_node.IsNull() ? 0.034 : sigma_node[2].as<Scalar>(0.034);
        gt_pose_sigma(3) = sigma_node.IsNull() ? 0.1 : sigma_node[3].as<Scalar>(0.1);
        gt_pose_sigma(4) = sigma_node.IsNull() ? 0.1 : sigma_node[4].as<Scalar>(0.1);
        gt_pose_sigma(5) = sigma_node.IsNull() ? 0.1 : sigma_node[5].as<Scalar>(0.1);
    }

    Scalar pose_only_huber_loss = node["pose_only_huber_loss"].as<Scalar>(0.5);

    bool enable_wheel_integration_factor = node["enable_wheel_integration_factor"].as<bool>(true);
    bool enable_velocity_factor          = node["enable_velocity_factor"].as<bool>(true);
    bool enable_zero_velocity_factor     = node["enable_zero_velocity_factor"].as<bool>(true);
    bool enable_prior_factor             = node["enable_prior_factor"].as<bool>(true);
    bool enable_pose_only_unit3_factor   = node["enable_pose_only_unit3_factor"].as<bool>(true);
    bool enable_unit3_factor             = node["enable_unit3_factor"].as<bool>(true);
    bool enable_gt_pose_factor           = node["enable_gt_pose_factor"].as<bool>(false);
    bool enable_position_factor          = node["enable_position_factor"].as<bool>(false);

    return Parameters(prior_noise, wheel_integration_factor_sigma, bias_between_sigma, velocity_factor_sigma,
                      velocity_factor_sigma_when_turns, low_precision_velocity_factor_sigma,
                      pose_only_unit3_factor_sigma, zero_velocity_between_pose_sigma, gt_pose_sigma,
                      pose_only_huber_loss, enable_wheel_integration_factor, enable_velocity_factor,
                      enable_zero_velocity_factor, enable_prior_factor, enable_pose_only_unit3_factor,
                      enable_unit3_factor, enable_gt_pose_factor, enable_position_factor);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GraphBuilder::Parameters GraphBuilder::Parameters::Example()
{
    Vector6 bias_between_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    Vector6 wheel_integration_factor_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    Vector3 velocity_factor_sigma(0.1, 0.1, 0.1);
    Vector3 velocity_factor_sigma_when_turns(0.1, 0.1, 0.1);
    Vector3 low_precision_velocity_factor_sigma(0.34, 034, 0.1);
    Vector2 pose_only_unit3_factor_sigma(0.1, 0.1);
    Vector6 zero_velocity_between_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    Vector6 gt_pose_sigma(0.1, 0.1, 0.1, 0.1, 0.1, 0.1);
    Scalar  pose_only_huber_loss(0.5);

    return Parameters(PriorVehicleStateNoise::Example(), wheel_integration_factor_sigma, bias_between_sigma,
                      velocity_factor_sigma, velocity_factor_sigma_when_turns, low_precision_velocity_factor_sigma,
                      pose_only_unit3_factor_sigma, zero_velocity_between_pose_sigma, gt_pose_sigma,
                      pose_only_huber_loss, true, true, true, true, true, true, false, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GraphBuilder::Problem::Empty() const
{
    return factor_graph.empty() || values.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GraphBuilder::Problem::Add(const FactorGraph& new_factor_graph, const Values& new_values)
{
    factor_graph.add(new_factor_graph);
    values.insert(new_values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GraphBuilder::Problem::Add(const FactorGraph& new_factor_graph)
{
    factor_graph.add(new_factor_graph);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GraphBuilder::Problem GraphBuilder::Initialize(const FactorMeasurements& initial_factor_measurements,
                                               uint64_t                  initial_frame_index) const
{
    // create initial values
    Values values = initial_factor_measurements.predicted_values;

    // create initial factor graph
    FactorGraph graph;

    // 1. add initial velocity factor
    if (SlidingWindowState::enable_estimation_with_acc && parameters_.enable_velocity_factor)
    {
        graph.add(NewVelocityFactor(initial_factor_measurements.vm.velocity, initial_frame_index,
                                    parameters_.velocity_factor_sigma));
    }

    // 2. add prior factor
    graph.add(CreatePriorFactor(initial_frame_index, values));

    // 3. add semantic factor
    addSemanticFactors(SlidingWindowState::static_semantic_state,
                       initial_factor_measurements.predicted_values.at<gtsam::Pose3>(X(initial_frame_index)), graph,
                       values, initial_frame_index);

    // combine all into a problem
    return Problem(graph, values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GraphBuilder::Problem GraphBuilder::Run(const FactorMeasurements&        new_factor_measurements,
                                        const std::vector<FeatureTrack>& tracks, uint64_t frame_index) const
{
    // build new sub graph
    // const FactorGraph new_sub_factor_graph = NewFactorGraph(new_factor_measurements, tracks, frame_index);
    FactorGraph new_sub_factor_graph = NewFactorGraph(new_factor_measurements, tracks, frame_index);

    // add new landmark values and vehicle state
    Values new_sub_values = NewLandmarkValues(tracks);
    new_sub_values.insert(X(frame_index), new_factor_measurements.predicted_values.at(X(frame_index)));
    new_sub_values.insert(B(frame_index), new_factor_measurements.predicted_values.at(B(frame_index)));

    if (SlidingWindowState::enable_estimation_with_acc)
    {
        new_sub_values.insert(V(frame_index), new_factor_measurements.predicted_values.at(V(frame_index)));
    }
    // add semantic factor
    addSemanticFactors(SlidingWindowState::static_semantic_state,
                       new_factor_measurements.predicted_values.at<gtsam::Pose3>(X(frame_index)), new_sub_factor_graph,
                       new_sub_values, frame_index);

    return Problem(new_sub_factor_graph, new_sub_values);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint64_t GraphBuilder::GetOldestFrameIndex(const gtsam::VariableIndex& variable_index) const
{
    uint64_t oldest_frame_index = std::numeric_limits<uint64_t>::max();

    for (const auto& key_value : variable_index)
    {
        const Symbol symbol(key_value.first);

        if (symbol.chr() == 'v')
        {
            oldest_frame_index = oldest_frame_index > symbol.index() ? symbol.index() : oldest_frame_index;
        }
    }

    return oldest_frame_index;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const GraphBuilder::Parameters& GraphBuilder::Params() const
{
    return parameters_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactorGraph GraphBuilder::CreatePriorFactor(const uint64_t frame_index, const Values& values) const
{
    FactorGraph prior_factor_graph;

    // add prior pose factor
    const gtsam::Pose3                     prior_pose = values.at(X(frame_index)).cast<gtsam::Pose3>();
    const gtsam::PriorFactor<gtsam::Pose3> prior_pose_factor(
        X(frame_index), prior_pose,
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.prior_noise.pose_sigma)));
    prior_factor_graph.add(prior_pose_factor);

    // add prior velocity factor
    if (SlidingWindowState::enable_estimation_with_acc)
    {
        if (parameters_.enable_velocity_factor)
        {
            const gtsam::Vector3                     prior_velocity = values.at(V(frame_index)).cast<gtsam::Vector3>();
            const gtsam::PriorFactor<gtsam::Vector3> prior_velocity_factor(
                V(frame_index), prior_velocity,
                gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.prior_noise.velocity_sigma)));
            prior_factor_graph.add(prior_velocity_factor);
        }

        const gtsam::imuBias::ConstantBias prior_bias = values.at(B(frame_index)).cast<gtsam::imuBias::ConstantBias>();
        const gtsam::PriorFactor<gtsam::imuBias::ConstantBias> prior_bias_factor(
            B(frame_index), prior_bias,
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.prior_noise.bias_sigma)));
        prior_factor_graph.add(prior_bias_factor);
    }
    else
    {
        // add prior bias factor
        const auto prior_bias = values.at(B(frame_index)).cast<gtsam::Vector3>();

        const gtsam::PriorFactor<gtsam::Vector3> prior_bias_factor(
            B(frame_index), prior_bias, gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(1e-1, 1e-1, 1e-1)));
        prior_factor_graph.add(prior_bias_factor);
    }

    return prior_factor_graph;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactorGraph GraphBuilder::NewFactorGraph(const FactorMeasurements&        new_factor_measurements,
                                         const std::vector<FeatureTrack>& new_tracks, uint64_t new_frame_index) const
{
    const auto& new_pim      = new_factor_measurements.pim;
    const auto& new_vm       = new_factor_measurements.vm;
    const auto& new_mpm      = new_factor_measurements.mpm;
    const auto& new_position = new_factor_measurements.position;
    const auto& new_wim      = new_factor_measurements.wim;
    const auto& new_pam      = new_factor_measurements.pam;
    const auto& new_sfm      = new_factor_measurements.sfm;

    boost::optional<gtsam::Pose3> gt_pose = boost::none;

    if (new_factor_measurements.gt_pose)
    {
        gt_pose = HoloGtsam::Convert(*(new_factor_measurements.gt_pose));
    }

    FactorGraph new_factor_graph;

    // Step 1: add new projection factor
    if (parameters_.enable_unit3_factor)
    {
        for (const auto& track : new_tracks)
        {
            const auto unit3_factors = track.Unit3Factors();
            // check whether return an empty vector
            if (unit3_factors.size() == 0)
            {
                continue;
            }
            new_factor_graph.add(unit3_factors);
        }
    }

    // step 2:add pose only unit3 factor
    if (parameters_.enable_pose_only_unit3_factor)
    {
        for (const auto& map_project_measurement : new_mpm)
        {
            new_factor_graph.add(NewPoseOnlyUnit3Factor(map_project_measurement));
        }
    }

    if (!new_sfm.measurements.empty())
    {
        new_factor_graph.add(NewPoseOnlySlotVertexFactor(new_sfm));
    }

    // Step 3: add local dr factor
    if (SlidingWindowState::enable_estimation_with_acc)
    {
        // imu factor
        new_factor_graph.add(NewImuFactor(new_pim, new_frame_index));
        new_factor_graph.add(NewImuBiasFactor(new_frame_index));

        // add velocity factor
        // @todo when the vehicle is making a turn, the velocity_factor may not so much resonable, so we don't add
        // velocity_factor at this case.
        // we temporary use the result of new_pim to check whether the vehicle is turn.
        const Scalar rotation_threshold = 5e-3;  // rotation threshold to determine if turn

        if (parameters_.enable_velocity_factor && new_vm.reliability != VelocityMeasurementReliability::NOGOOD)
        {
            auto sigma = parameters_.velocity_factor_sigma;

            if (new_pim.deltaRij().rpy().norm() > rotation_threshold)
            {
                sigma = parameters_.velocity_factor_sigma_when_turns;
            }

            if (new_vm.reliability == VelocityMeasurementReliability::LOW)
            {
                sigma = parameters_.low_precision_velocity_factor_sigma;
            }

            new_factor_graph.add(NewVelocityFactor(new_vm.velocity, new_frame_index, sigma));
        }

        // add pose3 between factor when vehicle speed < 1e-3 [m/s]
        const Scalar zero_velocity_threshold = 1e-3;  // velocity threshold to determine if is zero velocity

        if (parameters_.enable_zero_velocity_factor && new_vm.velocity.GetNorm() < zero_velocity_threshold)
        {
            new_factor_graph.add(NewPose3BetweenFactor(new_frame_index));
        }
    }
    else
    {
        // rotation only imu factor
        new_factor_graph.add(NewRotationOnlyImuFactor(new_pam, new_frame_index));
        new_factor_graph.add(NewGyroBiasFactor(new_frame_index));

        // essential matrix factor
        new_factor_graph.add(NewEssentialMatrixFactors(new_factor_measurements.emms));
        LOG(INFO) << "GraphBuilder --- NewEssentialMatrixFactors num : " << new_factor_measurements.emms.size();
    }

    // add wheel integration factor
    if (parameters_.enable_wheel_integration_factor && new_frame_index >= 1)
    {
        new_factor_graph.add(NewWheelIntegrationFactor(new_wim, new_frame_index));
    }

    // Step 7: add gt pose factor when use Mapping mode
    if (parameters_.enable_gt_pose_factor && gt_pose)
    {
        new_factor_graph.add(NewGtPoseFactor(*gt_pose, new_frame_index));
    }

    // Step 8: add gps factor
    if (parameters_.enable_position_factor && new_position)
    {
        // create gps factor
        const gtsam::SharedNoiseModel position_noise =
            gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(new_position->position_std));
        new_factor_graph.add(boost::make_shared<GPSFactor>(X(new_frame_index),
                                                           HoloGtsam::Convert(new_position->position), position_noise));
    }

    // return new factor graph
    return new_factor_graph;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pose3BetweenFactorPtr GraphBuilder::NewWheelIntegrationFactor(const WheelIntegrationMeasurement& new_wim,
                                                              uint64_t                           new_frame_index) const
{
    const gtsam::Pose2 pose2(new_wim.delta_x, new_wim.delta_y, new_wim.delta_yaw);
    const auto         t                              = pose2.translation().norm();
    Vector6            wheel_integration_factor_sigma = parameters_.wheel_integration_factor_sigma;

    if (t < 1e-5)
    {
        wheel_integration_factor_sigma = parameters_.zero_velocity_between_pose_sigma;
    }
    // create pose3 between factor noise model
    const gtsam::SharedNoiseModel pose3_between_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(wheel_integration_factor_sigma));
    const uint64_t old_frame_index = new_frame_index - 1;
    return boost::make_shared<Pose3BetweenFactor>(
        X(old_frame_index), X(new_frame_index),
        gtsam::Pose3(gtsam::Pose2(new_wim.delta_x, new_wim.delta_y, new_wim.delta_yaw)), pose3_between_factor_noise);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuFactorPtr GraphBuilder::NewImuFactor(const PreintegratedImuMeasurements& new_pim,
                                        const uint64_t                      new_frame_index) const
{
    const uint64_t old_frame_index = new_frame_index - 1;
    return boost::make_shared<ImuFactor>(X(old_frame_index), V(old_frame_index), X(new_frame_index), V(new_frame_index),
                                         B(old_frame_index), new_pim);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RotationOnlyImuFactorPtr GraphBuilder::NewRotationOnlyImuFactor(const PreintegratedAhrsMeasurements& new_pam,
                                                                const uint64_t new_frame_index) const
{
    const uint64_t old_frame_index = new_frame_index - 1;
    return boost::make_shared<RotationOnlyImuFactor>(X(old_frame_index), X(new_frame_index), B(old_frame_index),
                                                     new_pam);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pose3BetweenFactorPtr GraphBuilder::NewPose3BetweenFactor(const uint64_t new_frame_index) const
{
    // create pose3 between factor noise model
    const gtsam::SharedNoiseModel pose3_between_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.zero_velocity_between_pose_sigma));
    const uint64_t old_frame_index = new_frame_index - 1;
    return boost::make_shared<Pose3BetweenFactor>(X(old_frame_index), X(new_frame_index), gtsam::Pose3(),
                                                  pose3_between_factor_noise);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactorGraph GraphBuilder::NewEssentialMatrixFactors(const EssentialMatrixMeasurements& emms) const
{
    FactorGraph    result;
    gtsam::Vector6 rotation_between_factor_sigma;
    rotation_between_factor_sigma << 0.0349, 0.0349, 0.0349, 100, 100, 100;
    const gtsam::SharedNoiseModel pose3_between_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(rotation_between_factor_sigma);

    for (const auto& emm : emms)
    {
        const uint64_t     old_frame_index = emm.train_frame_id;
        const uint64_t     new_frame_index = emm.query_frame_id;
        const gtsam::Pose3 pose(emm.r, gtsam::Point3(0, 0, 0));

        result.add(boost::make_shared<Pose3BetweenFactor>(X(old_frame_index), X(new_frame_index), pose,
                                                          pose3_between_factor_noise));

        // gtsam::Pose3            Tbc   = HoloGtsam::Convert(camera_parameters_->extrinsics.at(0));
        // gtsam::SharedNoiseModel model = gtsam::noiseModel::Isotropic::Sigma(5, 0.25);
        // result.add(boost::make_shared<EssentialMatrixFactor2>(emm.measured_E.at(0), X(old_frame_index),
        //                                                       X(new_frame_index), model, Tbc));
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ImuBiasFactorPtr GraphBuilder::NewImuBiasFactor(const uint64_t new_frame_index) const
{
    // create imu bias noise(@todo control which imu bias factor)
    const gtsam::SharedNoiseModel bias_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.bias_between_sigma));

    const uint64_t old_frame_index = new_frame_index - 1;
    return boost::make_shared<ImuBiasFactor>(B(old_frame_index), B(new_frame_index), gtsam::imuBias::ConstantBias(),
                                             bias_noise);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GyroBiasFactorPtr GraphBuilder::NewGyroBiasFactor(const uint64_t new_frame_index) const
{
    gtsam::Vector3                gyro_bias_sigma(parameters_.bias_between_sigma[3], parameters_.bias_between_sigma[4],
                                   parameters_.bias_between_sigma[5]);
    const gtsam::SharedNoiseModel bias_noise = gtsam::noiseModel::Diagonal::Sigmas(gyro_bias_sigma);

    const uint64_t old_frame_index = new_frame_index - 1;
    return boost::make_shared<Vector3BetweenFactor>(B(old_frame_index), B(new_frame_index), gtsam::Vector3(0, 0, 0),
                                                    bias_noise);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityFactorPtr GraphBuilder::NewVelocityFactor(const Vector3& new_velocity, const uint64_t new_frame_index,
                                                  const Vector3& sigma) const
{
    const gtsam::SharedNoiseModel velocity_noise = gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(sigma));

    return boost::make_shared<VelocityFactor>(X(new_frame_index), V(new_frame_index), HoloGtsam::Convert(new_velocity),
                                              velocity_noise);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseOnlyUnit3FactorPtr
GraphBuilder::NewPoseOnlyUnit3Factor(const MapProjectionMeasurement& new_map_projection_measurement) const
{
    // create pose only unit3 noise
    const gtsam::SharedNoiseModel noise_sigma =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.pose_only_unit3_factor_sigma));
    const auto huber = gtsam::noiseModel::Robust::Create(
        gtsam::noiseModel::mEstimator::Huber::Create(parameters_.pose_only_huber_loss), noise_sigma);

    const Point3        point   = new_map_projection_measurement.map_point->position;
    const Vector3       feature = new_map_projection_measurement.bearing;
    const gtsam::Point3 gtsam_point(point.GetX(), point.GetY(), point.GetZ());
    const gtsam::Point3 gtsam_feature(feature(0), feature(1), feature(2));

    // get extrinsic
    const auto& camera_index = new_map_projection_measurement.camera_index;
    const auto& T_bc         = camera_parameters_->extrinsics.at(camera_index);
    return boost::make_shared<PoseOnlyUnit3Factor>(gtsam_point, gtsam_feature, huber,
                                                   X(new_map_projection_measurement.frame_id),
                                                   holo::localization::HoloGtsam::Convert(T_bc));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FactorGraph GraphBuilder::NewPoseOnlySlotVertexFactor(const SlotMapFactorMeasurement& new_sfm) const
{
    FactorGraph result;
    // create pose only unit3 noise
    const gtsam::SharedNoiseModel noise_sigma = gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(1.0, 1.0, 1.0));

    for (const auto measurement : new_sfm.measurements)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            const auto factor = boost::make_shared<semantic::PoseOnlySlotVertexFactor>(
                X(new_sfm.frame_id), holo::localization::HoloGtsam::Convert(measurement.train_slot.vertices[i]),
                holo::localization::HoloGtsam::Convert(measurement.query_slot.vertices[i]), noise_sigma);
            result.add(factor);
        }
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PosePriorFactorPtr GraphBuilder::NewGtPoseFactor(const gtsam::Pose3& gt_pose, const uint64_t new_frame_index) const
{
    // create prior pose noise
    const gtsam::SharedNoiseModel gt_pose_noise =
        gtsam::noiseModel::Diagonal::Sigmas(HoloGtsam::Convert(parameters_.gt_pose_sigma));
    return boost::make_shared<PosePriorFactor>(X(new_frame_index), gt_pose, gt_pose_noise);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Values GraphBuilder::NewLandmarkValues(const std::vector<FeatureTrack>& new_tracks) const
{
    Values new_values;

    for (const auto& track : new_tracks)
    {
        if (track.GetState() == FeatureTrack::State::FRESH)
        {
            const auto& landmark = track.GetLandmark();
            new_values.insert(L(landmark->Id()), landmark->Point());
        }
    }

    return new_values;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GraphBuilder::addSemanticFactors(const semantic::DataAssociation::State& semantic_state, const gtsam::Pose3& wTb,
                                      FactorGraph& graph, Values& values, const int64_t& frame_index) const
{
    (void)semantic_state;
    (void)wTb;
    (void)graph;
    (void)values;
    (void)frame_index;
    /*
    // @todo define it in parameters
    const gtsam::SharedNoiseModel vertex_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(0.5, 0.5, 0.5));
    const gtsam::SharedGaussian plane_factor_noise = gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3::Constant(0.1));
    const gtsam::SharedNoiseModel point_plane_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector1::Constant(0.2));
    const gtsam::SharedNoiseModel parallel_factor_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3::Constant(0.1));

    // add plane factor
    if (semantic_state.optional_plane)
    {
        // LOG(INFO) << "plane = " << semantic_state.optional_plane->data.planeCoefficients().transpose();
        graph.emplace_shared<gtsam::OrientedPlane3Factor>(semantic_state.optional_plane->data.planeCoefficients(),
                                                          plane_factor_noise, X(semantic_state.tracks.front().frame_id),
                                                          P(semantic_state.optional_plane->id));
        values.insert(P(semantic_state.optional_plane->id), semantic_state.optional_plane->data);
    }

    // loop over the tracks
    for (const auto& track : semantic_state.tracks)
    {
        const auto& state = track.state;
        if (frame_index != track.frame_id || state == semantic::ParkingSlotTrack::State::CANDIDATE)
        {
            continue;
        }

        // add initial values for FRESH tracks
        if (state == semantic::ParkingSlotTrack::State::FRESH)
        {
            const auto vertices = track.GetIndexedVertices(0);
            for (const auto& vertex : vertices)
            {
                const gtsam::Point3 measured = HoloGtsam::Convert(vertex.point);
                values.insert(S(vertex.id), wTb * measured);
            }
        }

        // add factors
        for (size_t i = 0; i < track.measurements.size(); i++)
        {
            if (state == semantic::ParkingSlotTrack::State::LIVE && i != track.measurements.size() - 1)
            {
                continue;
            }

            const auto frame_id = track.measurements.at(i).first;
            const auto vertices = track.GetIndexedVertices(i);

            for (const auto& vertex : vertices)
            {
                const gtsam::Point3 measured = HoloGtsam::Convert(vertex.point);

                // add vertex factor
                graph.emplace_shared<semantic::ParkingSlotVertexFactor>(X(frame_id), S(vertex.id), measured,
                                                                        vertex_factor_noise);

                // add point to plane factor
                if (semantic_state.optional_plane)
                {
                    graph.emplace_shared<semantic::ParkingSlotPointPlaneFactor>(S(vertex.id), P(track.plane_id),
                                                                                point_plane_factor_noise);
                }
            }

            // add parallel factor
            if (vertices.size() >= 4u)  // @todo is it appropriate to put this judgement here ???
            {
                graph.emplace_shared<semantic::ParkingSlotParallelFactor>(
                    S(vertices[0].id), S(vertices[1].id), S(vertices[2].id), S(vertices[3].id), parallel_factor_noise);
                graph.emplace_shared<semantic::ParkingSlotParallelFactor>(
                    S(vertices[1].id), S(vertices[2].id), S(vertices[3].id), S(vertices[0].id), parallel_factor_noise);
            }
        }
    }
    */
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
