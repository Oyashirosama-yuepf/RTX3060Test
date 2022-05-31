/*!
 * \brief visual localization initializer class header file
 * \author Quan.Chen chenquan@holomatic.com
 * \date Jan-2-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/initializer.h>
#include <holo/localization/vision/vslam/sliding_window_state.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Initializer::Parameters Initializer::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const std::string source_to_compute_initial_pose =
        node["source_to_compute_initial_pose"].as<std::string>("prebuilt_map");

    const bool checking_solved_pose_by_path_start_point =
        node["checking_solved_pose_by_path_start_point"].as<bool>(false);

    // load max acceptable difference between solved init vehicle pose and origin point of learned map if required to do
    // such checking.
    Vector3 maximum_acceptable_diff_ypr(0, 0, 0);
    Scalar  maximum_acceptable_diff_z    = 0.0;
    Scalar  maximum_acceptable_diff_dist = 0.0;

    if (checking_solved_pose_by_path_start_point)
    {
        maximum_acceptable_diff_ypr  = Vector3(node["maximum_acceptable_diff_ypr"][0].as<Scalar>(15.0),
                                               node["maximum_acceptable_diff_ypr"][1].as<Scalar>(2.0),
                                               node["maximum_acceptable_diff_ypr"][2].as<Scalar>(2.0));
        maximum_acceptable_diff_z    = node["maximum_acceptable_diff_z"].as<Scalar>(0.5);
        maximum_acceptable_diff_dist = node["maximum_acceptable_diff_dist"].as<Scalar>(2.0);
    }

    // initial imu bias
    ImuBias initial_bias;
    {
        Vector3 acc_bias_vec(node["initial_bias"][0].as<Scalar>(0.0), node["initial_bias"][1].as<Scalar>(0.0),
                             node["initial_bias"][2].as<Scalar>(0.0));
        Vector3 gyeo_bias_vec(node["initial_bias"][3].as<Scalar>(0.0), node["initial_bias"][4].as<Scalar>(0.0),
                              node["initial_bias"][5].as<Scalar>(0.0));
        initial_bias.SetLinearAccelerationBias(acc_bias_vec);
        initial_bias.SetAngularVelocityBias(gyeo_bias_vec);
    }

    return Parameters(source_to_compute_initial_pose, checking_solved_pose_by_path_start_point,
                      maximum_acceptable_diff_ypr, maximum_acceptable_diff_z, maximum_acceptable_diff_dist,
                      initial_bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Initializer::Parameters Initializer::Parameters::Example()
{
    std::string source_to_compute_initial_pose           = "prebuilt_map";
    bool        checking_solved_pose_by_path_start_point = true;
    Vector3     maximum_acceptable_diff_ypr(15.0, 2.0, 2.0);
    Scalar      maximum_acceptable_diff_z    = 0.5;
    Scalar      maximum_acceptable_diff_dist = 2.0;

    return Parameters(source_to_compute_initial_pose, checking_solved_pose_by_path_start_point,
                      maximum_acceptable_diff_ypr, maximum_acceptable_diff_z, maximum_acceptable_diff_dist, ImuBias());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Initializer::CheckingWithReferencePose(const Pose3& solved_pose, const Pose3& reference_pose) const
{
    // compute relative translation and rotation
    const auto delta_pose           = solved_pose.Inverse() * reference_pose;
    const auto relative_rotation    = delta_pose.GetRotation().YPR();
    const auto relative_translation = delta_pose.GetTranslation();

    if (std::fabs(holo::Degree(relative_rotation[0])) > parameters_.maximum_acceptable_diff_ypr[0] ||
        std::fabs(holo::Degree(relative_rotation[1])) > parameters_.maximum_acceptable_diff_ypr[1] ||
        std::fabs(holo::Degree(relative_rotation[2])) > parameters_.maximum_acceptable_diff_ypr[2])
    {
        LOG(WARNING) << "Initializer --- yaw-pitch-roll error between solved rotation and prior rotation: "
                     << std::fabs(holo::Degree(relative_rotation[0])) << " "
                     << std::fabs(holo::Degree(relative_rotation[1])) << " "
                     << std::fabs(holo::Degree(relative_rotation[2]));
        return false;
    }

    if (std::fabs(relative_translation.GetZ()) > parameters_.maximum_acceptable_diff_z)
    {
        LOG(WARNING) << "Initializer --- z error between solved pose and prior pose is: " << relative_translation.GetZ()
                     << "\n";
        return false;
    }

    if (relative_translation.ToVector().GetNorm() > parameters_.maximum_acceptable_diff_dist)
    {
        LOG(WARNING) << "Initializer --- distance between solved pose and prior pose is: "
                     << relative_translation.ToVector().GetNorm() << "\n";
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<Pose3>
Initializer::GetInitPriorPoseFromGravityAlignedOdometry(const Odometry& gravity_aligned_odometry) const
{
    //@TODO maybe we should check odometry's state future
    return gravity_aligned_odometry.GetPose();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<std::pair<Pose3, ImuBias>>
Initializer::ComputeInitPoseAndBiasFromStandstill(const RawMeasurement& raw_measurement) const
{
    if (!SlidingWindowState::enable_estimation_with_acc)
    {
        return std::make_pair(Pose3::Identity(), ImuBias());
    }

    const uint16_t          min_imu_measurements_number = 200;
    static std::vector<Imu> imu_msg_buffer;

    if (raw_measurement.imus.empty())
    {
        LOG(INFO) << "Initializer --- raw measurement imu buffer empty ";
        return boost::none;
    }
    std::copy(raw_measurement.imus.begin(), raw_measurement.imus.end(), std::back_inserter(imu_msg_buffer));

    // get initial velocity in body frame
    const Vector3 V_b(raw_measurement.chassis_states.back().GetVehicleSpeed(), 0.0, 0.0);

    // check if the vehicle is really stationary
    if (V_b.GetNorm() > 1e-3)
    {
        LOG(ERROR) << "Initializer --- Failed to initialize system. please keep the vehicle stationary.";
        imu_msg_buffer.clear();
        return boost::none;
    }

    if (imu_msg_buffer.size() < min_imu_measurements_number)
    {
        LOG(INFO) << "Initializer --- waiting for more imu measurements. current number of imu measurements is: "
                  << imu_msg_buffer.size();
        return boost::none;
    }

    // comput initial rotation and imu bias
    Vector3 sum_angular_vel(0.0, 0.0, 0.0);
    Vector3 sum_linear_acc(0.0, 0.0, 0.0);

    for (const auto& imu : imu_msg_buffer)
    {
        sum_angular_vel += imu.GetAngularVelocity();
        sum_linear_acc += imu.GetLinearAcceleration();
    }

    // initialize the gyro bias
    ImuBias bias;
    bias.SetAngularVelocityBias(sum_angular_vel / imu_msg_buffer.size());

    // initialize the initial orientation
    const Vector3 mean_linear_acc = sum_linear_acc / imu_msg_buffer.size();
    const Vector3 earth_gravity_direction(0.0, 0.0, 1.0);

    const auto q_bw = Eigen::Quaterniond::FromTwoVectors(HoloGtsam::Convert(mean_linear_acc),
                                                         HoloGtsam::Convert(earth_gravity_direction))
                          .coeffs();
    Rot3 r_wb(Quaternion(q_bw[3], q_bw[0], q_bw[1], q_bw[2]).ToRotationMatrix().Transpose());

    // clear this buffer after iniitial done
    LOG(INFO) << "Initializer --- initial rotation: " << r_wb.YPR();

    imu_msg_buffer.clear();

    return std::make_pair(Pose3(r_wb, Point3(0.0, 0.0, 0.0)), bias);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
boost::optional<VehicleState> Initializer::Run(const RawMeasurement&         raw_measurement,
                                               const std::vector<Features>&  multi_camera_features,
                                               const boost::optional<Pose3>& prior_T_wb) const
{
    LOG(INFO) << "\n\n==================\nInitializer --- START initialization ...\n";

    boost::optional<Pose3> T_wb = boost::none;
    ImuBias                bias = parameters_.initial_bias;

    if (parameters_.source_to_compute_initial_pose == "gravity_aligned_odometry")
    {
        LOG(INFO) << "Initializer --- trying to compute initial pose from the gravity aligned odometry ...";

        if (!raw_measurement.optional_odometry)
        {
            LOG(ERROR) << "Initializer --- wanna initialize pose from gravity aligned odometry while can not get "
                          "such a odometry";
            return boost::none;
        }

        T_wb = GetInitPriorPoseFromGravityAlignedOdometry(*raw_measurement.optional_odometry);
    }
    else if (parameters_.source_to_compute_initial_pose == "prebuilt_map")
    {
        LOG(INFO) << "Initializer --- trying to compute initial pose by matching the prebuilt feature map  ...";

        if (raw_measurement.visible_map->empty())
        {
            LOG(ERROR)
                << "Initializer --- wanna initialize pose by matching the prebuilt feature map while can not get "
                   "such a map";
            return boost::none;
        }

        if (relocalization_ == nullptr)
        {
            throw std::runtime_error("Initializer --- relocalization pointer is NULL.\n");
        }

        T_wb = relocalization_->RunSynchronously(multi_camera_features, prior_T_wb);

        // limit start point if required
        if (T_wb && parameters_.checking_solved_pose_by_path_start_point &&
            !CheckingWithReferencePose(*T_wb, *prior_T_wb))
        {
            LOG(ERROR) << "Initializer --- Please make sure the vehicle nearby the Origin Point of this map. "
                          "(15deg and 2m)";
            return boost::none;
        }
    }
    else if (parameters_.source_to_compute_initial_pose == "stationary")
    {
        LOG(INFO) << "Initializer --- trying to compute initial rotation from imu readings  ...";

        const auto pose_and_bias = ComputeInitPoseAndBiasFromStandstill(raw_measurement);

        if (!pose_and_bias)
        {
            return boost::none;
        }

        T_wb = pose_and_bias->first;
    }
    else if (parameters_.source_to_compute_initial_pose == "path_start_point")
    {
        LOG(INFO) << "Initializer --- use the start point of learned path as initial pose.";

        if (!prior_T_wb)
        {
            LOG(ERROR) << "Initializer --- wanna using the start point of learned path as initial pose while can not "
                          "get such a prior pose.";
            throw std::runtime_error("Initializer --- unknown error happened.");
        }

        T_wb = prior_T_wb;
    }
    else
    {
        LOG(ERROR) << "Initializer --- unknow source to compute initial pose: "
                   << parameters_.source_to_compute_initial_pose << "\n";
        throw std::runtime_error("Initializer --- unknow source to compute initial pose");
    }

    // check the validity of the result
    if (!T_wb)
    {
        LOG(ERROR) << "Initializer --- failed to compute initial pose.";
        return boost::none;
    }

    LOG(INFO) << "Initializer --- success to compute initial pose: \n" << *T_wb << "\n";

    // compute initial velocity in body frame
    const Vector3 V_b(raw_measurement.chassis_states.back().GetVehicleSpeed(), 0.0, 0.0);

    // compute initial velocity in vslam map frame
    const Vector3 V_wb = T_wb->TransformFrom(V_b);

    // return initial vehicle state
    return VehicleState(*T_wb, V_wb, bias);
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
