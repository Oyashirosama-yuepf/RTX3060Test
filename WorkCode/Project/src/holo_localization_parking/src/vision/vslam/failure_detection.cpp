/*!
 * \brief failure detection class source file in vslam
 * \author shuaijie.li @ lishuaijie@holomatic.com
 * \date Oct-24-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/failure_detection.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FailureDetection::Parameters FailureDetection::Parameters::LoadFromYaml(const holo::yaml::Node& node)
{
    const Scalar x_translation_threshold = node["x_translation_threshold"].as<Scalar>(3.3);
    const Scalar y_translation_threshold = node["y_translation_threshold"].as<Scalar>(0.44);
    const Scalar yaw_threshold           = node["yaw_threshold"].as<Scalar>(0.55);
    const Scalar vehicle_speed_threshold = node["vehicle_speed_threshold"].as<Scalar>(33.0);
    return Parameters(x_translation_threshold, y_translation_threshold, yaw_threshold, vehicle_speed_threshold);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FailureDetection::Parameters FailureDetection::Parameters::Example()
{
    return Parameters();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FailureDetection::Run(const SlidingWindowState& state, const Timestamp& old_timestamp,
                           const Scalar frequency) const
{
    // if old_timestamp is invalid[TimeStamp(0,0)], do nothing
    if (old_timestamp.IsZero())
    {
        return false;
    }

    // get relative pose between the newest pose and the second newest pose
    gtsam::Pose3 T_01 = state.NewestRelativePose();

    // compute frame num between newest estimated SlidingWindowState and
    // last SlidingWindowState
    const Scalar frame_num = ((state.GetTimestamp() - old_timestamp).ToSec()) * frequency;

    // @todo(Feng. Li 2020-01-10) checking if the frame_num is resonable

    // check translation
    if (std::fabs(T_01.x()) > frame_num * parameters_.x_translation_threshold ||
        std::fabs(T_01.y()) > frame_num * parameters_.y_translation_threshold)
    {
        LOG(WARNING) << "FailureDetection --- Translation[m] checking: \n"
                     << "1. translation along x axis is: " << T_01.x()
                     << ", the threshold along x axis is: " << parameters_.x_translation_threshold * frame_num
                     << "\n 2. translation along y axis is: " << T_01.y()
                     << ", the threshold along y axis is: " << parameters_.y_translation_threshold * frame_num;
        return true;
    }

    // check yaw angle in previous vehicle body frame
    const Scalar yaw = T_01.rotation().yaw();

    if (std::fabs(yaw) > parameters_.yaw_threshold)
    {
        LOG(WARNING) << "FailureDetection --- Yaw[rad] checking: "
                     << "yaw angle is: " << yaw << ", the threshold of yaw angle is:" << parameters_.yaw_threshold;
        return true;
    }

    // check velocity norm
    const Scalar current_speed_norm = state.NewestVehicleState().Velocity().GetNorm();

    if (current_speed_norm > parameters_.vehicle_speed_threshold)
    {
        LOG(WARNING) << "FailureDetection --- Vehicle speed[m/s] checking: "
                     << "vehicle speed norm is: " << current_speed_norm
                     << ", vehicle speed norm threshold is: " << parameters_.vehicle_speed_threshold;
        return true;
    }

    return false;
}

}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
