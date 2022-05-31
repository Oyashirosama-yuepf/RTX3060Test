/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file prior_rpy_factor_inl.cpp
 * @brief source file of prior rpy factor
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-08"
 */

#include <holo/localization/sam/factors/internal/prior_rpy_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriorRPYFactor::PriorRPYFactor(gtsam::SharedNoiseModel const& model, gtsam::Key const& pose_key,
                               gtsam::Vector3 const& measurement, bool const fix_roll, bool const fix_pitch,
                               bool const fix_yaw, double const delta)
  : Base(model, pose_key)
  , measurement_(measurement)
  , fix_roll_(fix_roll)
  , fix_pitch_(fix_pitch)
  , fix_yaw_(fix_yaw)
  , delta_(delta)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PriorRPYFactor::~PriorRPYFactor()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector PriorRPYFactor::evaluateError(gtsam::Pose3 const& pose, boost::optional<gtsam::Matrix&> H) const
{
    gtsam::Matrix36      rotation_H_pose;
    gtsam::Rot3 const&   rotation = pose.rotation(H ? &rotation_H_pose : NULL);
    gtsam::Vector3 const rpy      = rotation.rpy();
    gtsam::Matrix36      rotation_vector_H_pose;
    gtsam::Matrix33      rpy_H_rotation_vector;

    if (H)
    {
        gtsam::Matrix33      rotation_vector_H_rotation;
        gtsam::Vector3 const rotation_vector = gtsam::Rot3::Logmap(rotation, rotation_vector_H_rotation);
        rotation_vector_H_pose               = rotation_vector_H_rotation * rotation_H_pose;
        rpy_H_rotation_vector                = computeJacobianOfRPYwrtRotationVector(rotation_vector, delta_);
        *H                                   = gtsam::Matrix36::Zero();
    }

    gtsam::Vector3 error = gtsam::Vector3::Zero();

    if (!fix_roll_)
    {
        error(0u) = rpy(0u) - measurement_(0u);

        if (H)
        {
            H->row(0u) = rpy_H_rotation_vector.row(0u) * rotation_vector_H_pose;
        }
    }

    if (!fix_pitch_)
    {
        error(1u) = rpy(1u) - measurement_(1u);

        if (H)
        {
            H->row(1u) = rpy_H_rotation_vector.row(1u) * rotation_vector_H_pose;
        }
    }

    if (!fix_yaw_)
    {
        error(2u) = rpy(2u) - measurement_(2u);

        if (H)
        {
            H->row(2u) = rpy_H_rotation_vector.row(2u) * rotation_vector_H_pose;
        }
    }

    return error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Matrix33 PriorRPYFactor::computeJacobianOfRPYwrtRotationVector(gtsam::Vector3 const& rotation_vector,
                                                                      double const          delta) const
{
    gtsam::Matrix33 jacobian;
    double const    one_over_2delta = 1.0 / (2.0 * delta);

    for (size_t i = 0u; i < 3u; i++)
    {
        // apply perturbution to left of ith element
        gtsam::Vector3 left_rotation_vector = rotation_vector;
        left_rotation_vector[i] -= delta;
        gtsam::Vector3 const left_rpy = gtsam::Rot3::Expmap(left_rotation_vector).rpy();

        // apply perturbution to right of ith element
        gtsam::Vector3 right_rotation_vector = rotation_vector;
        right_rotation_vector[i] += delta;
        gtsam::Vector3 const right_rpy = gtsam::Rot3::Expmap(right_rotation_vector).rpy();

        // jacobian
        gtsam::Vector3 const delta_rpy = right_rpy - left_rpy;
        jacobian.block(0u, i, 3u, 1u)  = delta_rpy * one_over_2delta;
    }

    return jacobian;
}

}  // namespace internal
}  // namespace localization
}  // namespace holo
