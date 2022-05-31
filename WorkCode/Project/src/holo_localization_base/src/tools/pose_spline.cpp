/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_spline.cpp
 * @brief spline class implementation
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date April 08, 2020
 */

#include <holo/localization/tools/pose_spline.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::PoseSpline(const std::vector<Timestamp>& timestamps, const std::vector<Pose3d>& poses,
                       const Vector3d& offset, float64_t lambda, uint32_t num_of_time_segments)
  : offset_(offset), spline_(convertTimestamp(timestamps), convertPose(poses), lambda, num_of_time_segments)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::~PoseSpline() noexcept
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Timestamp PoseSpline::GetStartTime() const
{
    return Timestamp(spline_.GetParamRange().first);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Timestamp PoseSpline::GetEndTime() const
{
    return Timestamp(spline_.GetParamRange().second);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Pose3d PoseSpline::GetPose(const Timestamp& t, bool_t local) const
{
    // interpolation
    const Vector6d m = spline_.GetValue(t.ToSec());

    // translation
    Point3d p(m(0u), m(1u), m(2u));

    if (!local)
    {
        p += Point3d(offset_(0u), offset_(1u), offset_(2u));
    }

    // rotation
    Rot3d r;  // default identity
    {
        const Vector3d v(m(3u), m(4u), m(5u));
        if (v.GetNorm() > 1e-5)
        {
            r = Rot3d(AngleAxisd(v.GetNorm(), v).ToRotationMatrix());
        }
    }

    return Pose3d(r, p);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Vector3d PoseSpline::GetLinearVelocity(const Timestamp& t) const
{
    // take first order derivative
    const Vector6d v = spline_.GetDerivation<1u>(t.ToSec());
    return Vector3d(v(0u), v(1u), v(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Vector3d PoseSpline::GetLinearAcceleration(const Timestamp& t) const
{
    // take second order derivative
    const Vector6d a = spline_.GetDerivation<2u>(t.ToSec());
    return Vector3d(a(0u), a(1u), a(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Vector3d PoseSpline::GetAngularVelocityBodyFrame(const Timestamp& t) const
{
    const Vector6d m = spline_.GetValue(t.ToSec());
    const Vector6d v = spline_.GetDerivation<1u>(t.ToSec());

    const Vector3d omega = constructSMatrix(Vector3d(m(3u), m(4u), m(5u))) * Vector3d(v(3u), v(4u), v(5u));
    return omega;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Vector3d const& PoseSpline::GetOffset() const
{
    return offset_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<float64_t> PoseSpline::convertTimestamp(const std::vector<Timestamp>& timestamps) const
{
    std::vector<float64_t> times;
    (void)std::transform(timestamps.begin(), timestamps.end(), std::back_inserter(times),
                   [](const Timestamp& t) { return t.ToSec(); });
    return times;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<PoseSpline::Vector6d> PoseSpline::convertPose(const std::vector<Pose3d>& poses) const
{
    std::vector<Vector6d> result;
    result.reserve(poses.size());

    for (uint32_t i = 0u; i < poses.size(); i++)
    {
        // consider offset in translation
        const Vector3d p = poses.at(i).GetTranslation().As<Vector3d>() - offset_;

        // smoothing rotation
        Vector3d r = Rot3d::Logmap(poses.at(i).GetRotation());
        if (i != 0u)
        {
            r = findNearestRotation(Vector3d(result.back()(3u), result.back()(4u), result.back()(5u)), r);
        }
        result.emplace_back(p(0u), p(1u), p(2u), r(0u), r(1u), r(2u));
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Vector3d PoseSpline::findNearestRotation(const Vector3d& last_rotation,
                                                     const Vector3d& current_rotation) const
{
    const float64_t zero = 1e-8;
    if ((last_rotation.GetNorm() < zero) && (current_rotation.GetNorm() < zero))
    {
        return current_rotation;
    }

    float64_t angle = current_rotation.GetNorm();
    Vector3d  axis;
    if (angle < zero)
    {
        axis = last_rotation / last_rotation.GetNorm();
    }
    else
    {
        axis = current_rotation / angle;
    }

    // s1. check direction
    if (axis.Dot(last_rotation) < 0.0)
    {
        axis  = axis * -1.0;
        angle = 2.0 * M_PI - angle;
    }

    // s2. compensate angle
    {
        const float64_t pi2   = 2.0 * M_PI;
        const float64_t ratio = std::round((last_rotation.GetNorm() - angle) / pi2);
        angle += ratio * pi2;
    }

    return angle * axis;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PoseSpline::Matrix3d PoseSpline::constructSMatrix(const Vector3d& rotation) const
{
    const float64_t angle = rotation.GetNorm();

    if (angle < 1e-15)
    {
        return Matrix3d::Identity();
    }

    const float64_t sin_angle      = std::sin(angle);
    const float64_t sin_half_angle = std::sin(angle / 2.0);
    const float64_t inv_angle      = 1.0 / angle;
    const float64_t c1             = -2.0 * sin_half_angle * sin_half_angle * inv_angle;
    const float64_t c2             = (angle - sin_angle) * inv_angle;
    const Vector3d  axis           = rotation / angle;
    const Matrix3d  axis_mat       = axis.ToSkewSymmetric();

    return Matrix3d::Identity() + c1 * axis_mat + c2 * axis_mat * axis_mat;
}

}  // namespace localization
}  // namespace holo
