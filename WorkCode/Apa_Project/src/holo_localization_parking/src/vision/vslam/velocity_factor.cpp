/*!
 * \brief velocity factor in vslam
 * \author Yetong. Zhang, zhangyetong@holomatic.com
 * \date June-02-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo/localization/vision/vslam/velocity_factor.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityFactor::VelocityFactor(const gtsam::Key& pose_key, const gtsam::Key& velocity_key,
                               const gtsam::Velocity3& measurement, const gtsam::SharedNoiseModel& model)
  : Base(model, pose_key, velocity_key), measurement_(measurement)
{
    const Symbol pose_symbol(pose_key);
    const Symbol velocity_symbol(velocity_key);

    if (pose_symbol.index() != velocity_symbol.index())
    {
        std::stringstream ss;
        ss << "VelocityFactor --- pose_key must be equal to velocity_key: "
           << "pose_symbol_index = " << pose_symbol.index() << ", velocity_symbol_index = " << velocity_symbol.index();

        LOG(ERROR) << ss.str();
        throw std::runtime_error("VelocityFactor --- pose_key must be equal to "
                                 "velocity_key");
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const gtsam::Velocity3& VelocityFactor::GetVelocityMeasurement() const
{
    return measurement_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector VelocityFactor::evaluateError(const gtsam::Pose3& T_wb, const gtsam::Velocity3& V_w,
                                            boost::optional<gtsam::Matrix&> H1,
                                            boost::optional<gtsam::Matrix&> H2) const
{
    const gtsam::Rot3&     R_wb       = T_wb.rotation();
    const gtsam::Velocity3 prediction = R_wb.unrotate(V_w);
    const vslam::Scalar    wx = prediction.x(), wy = prediction.y(), wz = prediction.z();

    if (H1)
    {
        *H1 = (gtsam::Matrix36() << 0.0, -wz, +wy, 0.0, 0.0, 0.0, +wz, 0.0, -wx, 0.0, 0.0, 0.0, -wy, +wx, 0.0, 0.0, 0.0,
               0.0)
                  .finished();
    }

    if (H2)
    {
        *H2 = R_wb.transpose();
    }

    // return error vector
    return (prediction - measurement_);
}
}  // namespace vslam
}  // namespace vision
}  // namespace localization
}  // namespace holo
