/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane_factor_inl.cpp
 * @brief This header file defines plane factor implementation
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-31
 */

#include <holo/localization/sam/factors/internal/point2plane_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2PlaneFactor::Point2PlaneFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt,
                                     gtsam::Point3 const& target_pt, gtsam::Vector3 const& target_normal,
                                     gtsam::SharedNoiseModel const& noise_model)
  : Base(noise_model, pose_key), source_pt_(source_pt), target_pt_(target_pt), target_normal_(target_normal)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2PlaneFactor::~Point2PlaneFactor()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector Point2PlaneFactor::evaluateError(gtsam::Pose3 const& pose, boost::optional<gtsam::Matrix&> H) const
{
    // error =  normal.transpose() * (pose * source_pt - target_pt)
    // Jacobian:
    // e_H_pose = D(error) / D(pose)
    //        = (D(error) / D(pose * p)) * (D(pose * p) / D(pose))
    //        = normal.transpose() * (D(pose * p) / D(pose))
    //
    gtsam::Matrix36 Hx1_pose;

    gtsam::Point3 x1 = pose.transform_from(source_pt_, Hx1_pose);

    if (H)
    {
        *H = target_normal_.transpose() * Hx1_pose;
    }

    double error = target_normal_.transpose() * (x1 - target_pt_);

    return gtsam::Vector1(error);
}
}  // namespace internal
}  // namespace localization
}  // namespace holo
