/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file orthonormal_line_projection_factor.cpp
 * @brief This source file defines orthonormal line projection factor.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2022-01-11"
 */

#include <gtsam/base/OptionalJacobian.h>
#include <holo/localization/sam/factors/internal/line_projection_factor_inl.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
namespace internal
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::LineProjectionFactor(GTKey const& pose_key, GTKey const& orthonormal_line_key,
                                           GTNoiseModel const& noise_model, Measurement const& measured,
                                           GTPose3 const& bTc, GTCal3::shared_ptr const& K)
  : Base(noise_model, pose_key, orthonormal_line_key), measured_(measured), bTc_(bTc), K_(K)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::GTPose3 const& LineProjectionFactor::GetExtrinsic()
{
    return bTc_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::Measurement const& LineProjectionFactor::GetMeasurement()
{
    return measured_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::GTCal3 const& LineProjectionFactor::GetCameraMatrix()
{
    return *K_;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::GTVector LineProjectionFactor::evaluateError(GTPose3 const&                  wTb,
                                                                   GTOrthonormalLine const&        orthonormal_line,
                                                                   boost::optional<gtsam::Matrix&> H1,
                                                                   boost::optional<gtsam::Matrix&> H2) const
{
    if (K_)
    {
        return evaluatePointToLineError(wTb, orthonormal_line, H1, H2);
    }
    else
    {
        return evaluatePlaneError(wTb, orthonormal_line, H1, H2);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::GTVector LineProjectionFactor::evaluatePlaneError(GTPose3 const&           wTb,
                                                                        GTOrthonormalLine const& orthonormal_line,
                                                                        boost::optional<gtsam::Matrix&> H1,
                                                                        boost::optional<gtsam::Matrix&> H2) const
{
    // convert the orthonormal line in world frame to plucker line in camera frame
    gtsam::Matrix64 H_Lw_Orth;
    GTPluckerLine   Lw = orthonormal_line.convertToPluckerLine(H_Lw_Orth);

    gtsam::Matrix6 H_Lb_Lw;
    gtsam::Matrix6 H_Lb_wTb;
    GTPluckerLine  Lb = Lw.transformTo(wTb, H_Lb_wTb, H_Lb_Lw);

    // compte H_Lc_to_Lw
    gtsam::Matrix6 H_Lc_Lb;
    GTPluckerLine  Lc      = Lb.transformTo(bTc_, boost::none, H_Lc_Lb);
    gtsam::Matrix6 H_Lc_Lw = H_Lc_Lb * H_Lb_Lw;

    // construct predicted line plane
    GTVector3 predicted_line_plane = Lc.getNormalVector();

    // construct detected line plane
    GTVector3 detected_line_plane_normal_vector =
        measured_.rays[0u].unitVector().cross(measured_.rays[1u].unitVector());

    // compute angle error of two planes
    gtsam::Matrix23 H_unit_point;
    GTUnit3         normalized_predicted_plane_normal_vector = GTUnit3::FromPoint3(
        GTPoint3(predicted_line_plane(0u), predicted_line_plane(1u), predicted_line_plane(2u)), H_unit_point);

    GTUnit3 normalized_detected_plane_normal_vector =
        GTUnit3::FromPoint3(GTPoint3(detected_line_plane_normal_vector(0u), detected_line_plane_normal_vector(1u),
                                     detected_line_plane_normal_vector(2u)));

    // compute jacobian of predicted plane w.r.t. Lc
    gtsam::Matrix36 H_predicted_plane_Lc;
    H_predicted_plane_Lc << gtsam::Matrix3::Identity(), gtsam::Matrix3::Zero();

    // compute jacobian of angle error w.r.t. plane normal vector(normalized)
    gtsam::Matrix H_error_normalized_normal_vector;
    GTVector2     angle_error = normalized_detected_plane_normal_vector.error(normalized_predicted_plane_normal_vector,
                                                                          H_error_normalized_normal_vector);

    gtsam::Matrix6 H_Lc_to_wTb = H_Lc_Lb * H_Lb_wTb;

    if (H1)
    {
        *H1 = H_error_normalized_normal_vector * H_unit_point * H_predicted_plane_Lc * H_Lc_to_wTb;
    }

    if (H2)
    {
        *H2 = H_error_normalized_normal_vector * H_unit_point * H_predicted_plane_Lc * H_Lc_Lw * H_Lw_Orth;
    }

    return angle_error;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::GTVector LineProjectionFactor::evaluatePointToLineError(GTPose3 const&           wTb,
                                                                              GTOrthonormalLine const& orthonormal_line,
                                                                              boost::optional<gtsam::Matrix&> H1,
                                                                              boost::optional<gtsam::Matrix&> H2) const
{
    // convert the orthonormal line in world frame to plucker line in camera frame
    gtsam::Matrix64 H_Lw_Orth;
    GTPluckerLine   Lw = orthonormal_line.convertToPluckerLine(H_Lw_Orth);

    gtsam::Matrix6 H_Lb_Lw;
    gtsam::Matrix6 H_Lb_wTb;
    GTPluckerLine  Lb = Lw.transformTo(wTb, H_Lb_wTb, H_Lb_Lw);

    gtsam::Matrix6 H_Lc_Lb;
    GTPluckerLine  Lc      = Lb.transformTo(bTc_, boost::none, H_Lc_Lb);
    gtsam::Matrix6 H_Lc_Lw = H_Lc_Lb * H_Lb_Lw;

    // project the plucker line to image plane
    gtsam::Matrix36 H_line_coefficient_Lc;
    GTVector3 const projected_line_coefficient = projectPluckerLineToImagePlane((*K_).K(), Lc, H_line_coefficient_Lc);

    // compute intersection of measured rays and normalized plane
    GTVector3 const detected_endpoint1_on_normalized_plane(
        measured_.rays[0u].unitVector()[0u] / measured_.rays[0u].unitVector()[2u],
        measured_.rays[0u].unitVector()[1u] / measured_.rays[0u].unitVector()[2u], 1.0);

    GTVector3 const detected_endpoint2_on_normalized_plane(
        measured_.rays[1u].unitVector()[0u] / measured_.rays[1u].unitVector()[2u],
        measured_.rays[1u].unitVector()[1u] / measured_.rays[1u].unitVector()[2u], 1.0);

    GTVector3 const detected_endpoint1_on_image_plane = (*K_).K() * detected_endpoint1_on_normalized_plane;
    GTVector3 const detected_endpoint2_on_image_plane = (*K_).K() * detected_endpoint2_on_normalized_plane;

    // compute distance from detected line endpoint to projected line
    GTScalar const dot1 = detected_endpoint1_on_image_plane.dot(projected_line_coefficient);
    GTScalar const dot2 = detected_endpoint2_on_image_plane.dot(projected_line_coefficient);

    GTScalar const error1 = dot1 / GTVector2(projected_line_coefficient[0u], projected_line_coefficient[1u]).norm();
    GTScalar const error2 = dot2 / GTVector2(projected_line_coefficient[0u], projected_line_coefficient[1u]).norm();

    // compute jacobian of distance error w.r.t. line coefficient, ref: PL-VIO: Tightly-Coupled Monocular
    // Visual–Inertial Odometry Using Point and Line Features
    GTScalar const first_two_dim_of_line_coefficient_norm =
        projected_line_coefficient[0u] * projected_line_coefficient[0u] +
        projected_line_coefficient[1u] * projected_line_coefficient[1u];

    GTScalar const coefficient1 = std::pow(first_two_dim_of_line_coefficient_norm, 1.5);
    GTScalar const coefficient2 = std::pow(first_two_dim_of_line_coefficient_norm, 0.5);

    gtsam::Matrix23 H_error_line_coefficient;
    H_error_line_coefficient << -projected_line_coefficient[0u] * dot1 / coefficient1 +
                                    detected_endpoint1_on_image_plane[0u] / coefficient2,
        -projected_line_coefficient[1u] * dot1 / coefficient1 + detected_endpoint1_on_image_plane[1u] / coefficient2,
        1 / coefficient2,
        -projected_line_coefficient[0u] * dot2 / coefficient1 + detected_endpoint2_on_image_plane[0u] / coefficient2,
        -projected_line_coefficient[1u] * dot2 / coefficient1 + detected_endpoint2_on_image_plane[1u] / coefficient2,
        1 / coefficient2;

    gtsam::Matrix6 H_Lc_wTb = H_Lc_Lb * H_Lb_wTb;

    if (H1)
    {
        *H1 = H_error_line_coefficient * H_line_coefficient_Lc * H_Lc_wTb;
    }

    if (H2)
    {
        *H2 = H_error_line_coefficient * H_line_coefficient_Lc * H_Lc_Lw * H_Lw_Orth;
    }

    return GTVector2(error1, error2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineProjectionFactor::GTVector3 LineProjectionFactor::projectPluckerLineToImagePlane(
    GTMatrix3 const& K, GTPluckerLine const& Lc, gtsam::OptionalJacobian<3u, 6u> H) const
{
    GTMatrix3 line_project_matrix = GTMatrix3::Zero();
    line_project_matrix(0, 0)     = K(1, 1);
    line_project_matrix(1, 1)     = K(0, 0);
    line_project_matrix(2, 0)     = -K(1, 1) * K(0, 2);
    line_project_matrix(2, 1)     = -K(0, 0) * K(1, 2);
    line_project_matrix(2, 2)     = K(0, 0) * K(1, 1);

    if (H)
    {
        *H << line_project_matrix, GTMatrix3::Zero();
    }

    GTVector3 const projected_line = line_project_matrix * Lc.getNormalVector();
    return projected_line;
}
}  // namespace internal
}  // namespace localization
}  // namespace holo