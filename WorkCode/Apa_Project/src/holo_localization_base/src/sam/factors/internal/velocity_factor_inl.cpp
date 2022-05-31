/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file velocity_factor_inl.cpp
 * @brief source file of velocity factor used to constraint a pose and velocity
 * @author Yetong. Zhang, zhangyetong@holomatic.com
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-06-02"
 */

#include <holo/localization/sam/factors/internal/velocity_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityFactor::VelocityFactor()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VelocityFactor::VelocityFactor(const gtsam::Key& pose_key, const gtsam::Key& velocity_key,
                               const gtsam::Vector3& measurement, const gtsam::SharedNoiseModel& model)
  : Base(model, pose_key, velocity_key), measurement_(measurement)
{
    const gtsam::Symbol pose_symbol(pose_key);
    const gtsam::Symbol velocity_symbol(velocity_key);
    if (pose_symbol.index() != velocity_symbol.index())
    {
        std::stringstream ss;
        ss << "VelocityFactor --- pose_key must be equal to velocity_key: "
           << "pose_symbol_index = " << pose_symbol.index() << ", velocity_symbol_index = " << velocity_symbol.index();

        std::cout << ss.str() << std::endl;
        std::string s = ss.str();
        throw std::runtime_error(s);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const gtsam::Vector3& VelocityFactor::GetVelocityMeasurement() const
{
    return measurement_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector VelocityFactor::evaluateError(const gtsam::Pose3& wTb, const gtsam::Vector3& Vw,
                                            boost::optional<gtsam::Matrix&> H1,
                                            boost::optional<gtsam::Matrix&> H2) const
{
    const gtsam::Rot3&   wRb        = wTb.rotation();
    const gtsam::Vector3 prediction = wRb.unrotate(Vw);
    const double         wx         = prediction.x();
    const double         wy         = prediction.y();
    const double         wz         = prediction.z();

    if (H1)
    {
        *H1 = (gtsam::Matrix36() << 0.0, -wz, +wy, 0.0, 0.0, 0.0, +wz, 0.0, -wx, 0.0, 0.0, 0.0, -wy, +wx, 0.0, 0.0, 0.0,
               0.0)
                  .finished();
    }

    if (H2)
    {
        *H2 = wRb.transpose();
    }

    // @brief return error vector
    return (prediction - measurement_);
}

}  // namespace internal
}  // namespace localization
}  // namespace holo
