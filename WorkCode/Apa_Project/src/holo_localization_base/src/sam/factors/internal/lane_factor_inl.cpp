/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_factor_inl.cpp
 * @brief source file of lane factor
 * @author Zhang Yelin (zhangyelin@holomatic.com)
 * @author Wenzhi Liu (liuwenzhi@holomatic.com)
 * @date Dec 13, 2019
 */

#include <holo/localization/sam/factors/internal/lane_factor_inl.h>
#include <holo/localization/sam/sam.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Lane2Factor::Lane2Factor()
{
    lane_correspondence_type_      = LaneCorrespondenceType::PROJECT_TO_BODY;
    disable_rotation_optimization_ = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Lane2Factor::Lane2Factor(const gtsam::Key& j, const gtsam::SharedNoiseModel& model, const Point3Type& point,
                         const Line2& line, const LaneCorrespondenceType& lane_correspondence_type,
                         const bool_t disable_rotation_optimization)
  : gtsam::NoiseModelFactor1<gtsam::Pose3>(model, j)
  , point_(point)
  , line_(line)
  , lane_correspondence_type_(lane_correspondence_type)
  , disable_rotation_optimization_(disable_rotation_optimization)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gtsam::Vector Lane2Factor::evaluateError(const gtsam::Pose3& wTb, boost::optional<gtsam::Matrix&> dist_H_pose) const
{
    gtsam::Matrix36 point_H_pose;
    gtsam::Point3   point_initial = gtsam::Point3(point_.GetX(), point_.GetY(), point_.GetZ());
    // transform point to reference coordinate frame according to lane correspondence type
    gtsam::Point3 point_in_reference_frame;

    if (lane_correspondence_type_ == LaneCorrespondenceType::PROJECT_TO_BODY)
    {
        point_in_reference_frame = wTb.transform_to(point_initial, point_H_pose);
    }
    else if (lane_correspondence_type_ == LaneCorrespondenceType::PROJECT_TO_WORLD)
    {
        point_in_reference_frame = wTb.transform_from(point_initial, point_H_pose);
    }

    if (disable_rotation_optimization_)
    {
        point_H_pose.block(0u, 0u, 3, 3u) = GTMatrix3::Zero();
    }

    gtsam::Vector1 result;
    Vector3        norm_vector = line_.GetCoeffs();
    norm_vector.GetHead(2).Normalize();
    norm_vector(2) = 0.0;

    // define the detected line is a*x + b*y + c = 0, the distance from point(x, y) to the line is (a*x + b*y +
    // c)/sqrt(a^2+b^2), a/sqrt(a^2+b^2) = norm_vector[0], b/sqrt(a^2+b^2) = norm_vector[1],
    // result = norm_vector[0]*x + norm_vector[1]*y + c/sqrt(a^2+b^2)
    result(0) = norm_vector(0) * point_in_reference_frame.x() + norm_vector(1) * point_in_reference_frame.y() +
                line_.GetCoeffs()[2] / line_.GetCoeffs().GetHead(2).GetNorm();

    if (dist_H_pose)
    {
        /* dist_H_pose = dist_H_point * point_H_pose */
        *dist_H_pose = gtsam::Vector3(norm_vector(0), norm_vector(1), 0).transpose() * point_H_pose;
    }

    return result;
}

}  // namespace internal
}  // namespace localization
}  // namespace holo
