/*!
 * \brief sliding window state in vslam
 * \author Yanwei. Du, duyanwei@holomatic.com
 * \date Jan-15-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

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
/**
 * @brief initialize static member variable
 */
gtsam::IncrementalFixedLagSmoother SlidingWindowState::static_smoother       = gtsam::IncrementalFixedLagSmoother();
Tracker::State                     SlidingWindowState::static_tracker_state  = Tracker::State();
semantic::DataAssociation::State   SlidingWindowState::static_semantic_state = semantic::DataAssociation::State();
bool                               SlidingWindowState::enable_estimation_with_acc = false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Timestamp SlidingWindowState::GetTimestamp() const noexcept
{
    return timestamp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SlidingWindowState::IsInitialized() const noexcept
{
    return !(static_smoother.getFactors().empty() || values.empty());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleState SlidingWindowState::NewestVehicleState() const
{
    return GetVehicleState(frame_id);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Pose3 SlidingWindowState::NewestRelativePose() const
{
    if (frame_id == 0)
    {
        return gtsam::Pose3();
    }

    if (!compensated_values.exists(X(frame_id)) || !compensated_values.exists(X(frame_id - 1)))
    {
        std::stringstream ss;
        ss << "SlidingWindowState --- frame_id: " << frame_id << ", or frame_id - 1: " << frame_id - 1
           << ", does not exist!!!";
        LOG(ERROR) << ss.str();
        throw std::runtime_error(ss.str());
    }

    const gtsam::Pose3 T_w0 = compensated_values.at(X(frame_id)).cast<gtsam::Pose3>();
    const gtsam::Pose3 T_w1 = compensated_values.at(X(frame_id - 1)).cast<gtsam::Pose3>();
    const gtsam::Pose3 T_01 = T_w0.inverse() * T_w1;

    return T_01;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VehicleState SlidingWindowState::GetVehicleState(const uint64_t index) const
{
    if (!compensated_values.exists(X(index)) || !compensated_values.exists(B(index)))
    {
        std::stringstream ss;
        ss << "VehicleState does NOT exist: query index = " << index;
        LOG(ERROR) << ss.str();
        throw std::runtime_error(ss.str());
    }

    if (enable_estimation_with_acc && !compensated_values.exists(V(index)))
    {
        std::stringstream ss;
        ss << "VehicleState does NOT exist: query index = " << index;
        LOG(ERROR) << ss.str();
        throw std::runtime_error(ss.str());
    }

    ImuBias imu_bias;

    ///@todo(chengchagnxi@holomatic.com) if no velocity value, create this by pose and t.
    gtsam::Vector3 velocity(0.0, 0.0, 0.0);

    if (enable_estimation_with_acc)
    {
        const gtsam::imuBias::ConstantBias bias(compensated_values.at(B(index)).cast<gtsam::imuBias::ConstantBias>());
        imu_bias.SetAngularVelocityBias(HoloGtsam::Convert(bias.gyroscope()));
        imu_bias.SetLinearAccelerationBias(HoloGtsam::Convert(bias.accelerometer()));
        velocity = compensated_values.at(V(index)).cast<gtsam::Vector3>();
    }
    else
    {
        gtsam::Vector3 gyro_bias = compensated_values.at(B(index)).cast<gtsam::Vector3>();
        imu_bias.SetAngularVelocityBias(HoloGtsam::Convert(gyro_bias));
    }

    const auto pose = HoloGtsam::Convert(compensated_values.at(X(index)).cast<gtsam::Pose3>());

    return VehicleState(pose, HoloGtsam::Convert(velocity), imu_bias);
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
