/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file plane_factor_inl.cpp
 * @brief This header file defines plane factor implementation
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-04-30
 */

#include <holo/localization/sam/factors/internal/point2point_factor_inl.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2PointFactor::Point2PointFactor(gtsam::Key const& pose_key, gtsam::Point3 const& source_pt,
                                     gtsam::Point3 const& target_pt, gtsam::SharedNoiseModel const& noise_model)
  : Base(noise_model, pose_key), source_pt_(source_pt), target_pt_(target_pt)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point2PointFactor::~Point2PointFactor()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector Point2PointFactor::evaluateError(gtsam::Pose3 const& pose, boost::optional<gtsam::Matrix&> H) const
{
    // error =  ||(pose * source_pt - target_pt||

    gtsam::Matrix36 Hx1_pose;
    gtsam::Point3   x1 = pose.transform_from(source_pt_, Hx1_pose);

    gtsam::Matrix13 He_x1;
    double          error = gtsam::norm3(x1 - target_pt_, He_x1);

    if (H)
    {
        *H = He_x1 * Hx1_pose;
    }

    return gtsam::Vector1(error);
}
}  // namespace internal
}  // namespace localization
}  // namespace holo
