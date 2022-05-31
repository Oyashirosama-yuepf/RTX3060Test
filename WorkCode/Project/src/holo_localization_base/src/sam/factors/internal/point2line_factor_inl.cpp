/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file point2line_factor_inl.cpp
 * @brief This header file defines point2line factor implementation
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-04-23
 */

#include <holo/localization/sam/factors/internal/point2line_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2LineFactor::Point2LineFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt,
                                   gtsam::Point3 const& target_pt1, gtsam::Point3 const& target_pt2,
                                   gtsam::SharedNoiseModel const& noise_model)
  : Base(noise_model, pose_key)
  , source_pt_(source_pt)
  , target_pt_(target_pt1)
  , direction_((target_pt2 - target_pt1).normalized())
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2LineFactor::Point2LineFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt,
                                   gtsam::Point3 const& target_pt, gtsam::Vector3 const& target_line_dir,
                                   gtsam::SharedNoiseModel const& noise_model)
  : Base(noise_model, pose_key), source_pt_(source_pt), target_pt_(target_pt), direction_(target_line_dir.normalized())
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2LineFactor::~Point2LineFactor()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector Point2LineFactor::evaluateError(gtsam::Pose3 const& pose, boost::optional<gtsam::Matrix&> e_H_pose) const
{
    // let l1 = target line direction, l2 = pose * source_pt - target_pt1
    // error = ||l2.cross(l1)|| / ||l1||

    gtsam::Matrix36 Hx1_pose;

    gtsam::Point3 x1 = pose.transform_from(source_pt_, Hx1_pose);

    // line direction
    gtsam::Point3 l1 = direction_;
    gtsam::Point3 l2 = x1 - target_pt_;

    gtsam::Matrix33 Hc_l2;

    gtsam::Point3   c = gtsam::cross(l2, l1, Hc_l2);
    gtsam::Matrix13 Ha_c;
    double          error = gtsam::norm3(c, Ha_c);

    if (e_H_pose)
    {
        *e_H_pose = Ha_c * Hc_l2 * Hx1_pose;
    }

    return gtsam::Vector1(error);
}
}  // namespace internal
}  // namespace localization
}  // namespace holo
