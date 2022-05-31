/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file line_triangulation.cpp
 * @brief This file defines source of line triangulation.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-16"
 */

#include <holo/localization/sam/vision/line/line_triangulation.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineTriangulation::Parameters LineTriangulation::Parameters::GenerateExample()
{
    GTScalar const min_distance_between_two_frames = 0.5;
    GTScalar const min_angle_between_two_planes    = 0.1;

    return Parameters(min_distance_between_two_frames, min_angle_between_two_planes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineTriangulation::~LineTriangulation()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<bool, PluckerLine> LineTriangulation::run(CameraInfoWithLineEndpoints const& lhs,
                                                    CameraInfoWithLineEndpoints const& rhs) const
{
    // compute left line coefficient on image plane
    GTVector3 const left_line_coefficient_on_image_plane =
        GTVector3(lhs.start_point(0u), lhs.start_point(1u), 1.0)
            .cross(GTVector3(lhs.end_point(0u), lhs.end_point(1u), 1.0));
    CameraInfoWithLineCoefficient left_camera_info_with_line_coefficient(lhs.wTc, lhs.K,
                                                                         left_line_coefficient_on_image_plane);

    // compute right line coefficient on image plane
    GTVector3 const right_line_coefficient_on_image_plane =
        GTVector3(rhs.start_point(0u), rhs.start_point(1u), 1.0)
            .cross(GTVector3(rhs.end_point(0u), rhs.end_point(1u), 1.0));
    CameraInfoWithLineCoefficient right_camera_info_with_line_coefficient(rhs.wTc, rhs.K,
                                                                          right_line_coefficient_on_image_plane);

    return run(left_camera_info_with_line_coefficient, right_camera_info_with_line_coefficient);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<bool, PluckerLine> LineTriangulation::run(CameraInfoWithLineCoefficient const& lhs,
                                                    CameraInfoWithLineCoefficient const& rhs) const
{
    // compute distance between two frames
    GTScalar const distance_between_two_frames = lhs.wTc.translation().dist(rhs.wTc.translation());

    if (distance_between_two_frames <= parameters_.min_distance_between_two_frames)
    {
        LOG(WARNING) << "LineTriangulation --- Triangulate failed, distance between two frames is"
                     << distance_between_two_frames
                     << "which is too small than threshold:" << parameters_.min_distance_between_two_frames;
        return std::make_pair(false, GTPluckerLine(GTVector3(), GTVector3()));
    }

    // compute left plane in left camera coordinate
    GTVector3 const left_line_coefficient_on_normalized_plane = lhs.K.transpose() * lhs.line_coefficient;
    GTVector4 const left_plane = computePlaneFromLineCoefficient(left_line_coefficient_on_normalized_plane);

    // compute right plane in right camera coordinate
    GTVector3 const right_line_coefficient_on_normalized_plane = rhs.K.transpose() * rhs.line_coefficient;
    GTVector4 const right_plane = computePlaneFromLineCoefficient(right_line_coefficient_on_normalized_plane);

    // transform right plane to left camera coordinate
    GTPose3 const   rTl                       = rhs.wTc.inverse() * lhs.wTc;
    GTVector4 const right_plane_in_left_frame = rTl.matrix().transpose() * right_plane;

    // compute angle between two planes
    GTScalar const angle_between_two_planes = computeAngleBetweenTwoPlanes(left_plane, right_plane_in_left_frame);

    if (angle_between_two_planes <= parameters_.min_angle_between_two_planes)
    {
        LOG(WARNING) << "LineTriangulation --- Triangulation failed, angle between two planes is"
                     << angle_between_two_planes
                     << "which is too small than threshold:" << parameters_.min_angle_between_two_planes;
        return std::make_pair(false, GTPluckerLine(GTVector3(), GTVector3()));
    }

    // compute plucker line through solving intersection of two planes
    GTMatrix4 const left_plane_mul_right_plane_transpose = left_plane * right_plane_in_left_frame.transpose();
    GTMatrix4 const plucker_matrix =
        left_plane_mul_right_plane_transpose - left_plane_mul_right_plane_transpose.transpose();
    GTPluckerLine plucker_line_in_camera_frame = GTPluckerLine(plucker_matrix);

    // convert plucker line in camera frame to world frame
    GTPluckerLine const plucker_line_in_world_frame = plucker_line_in_camera_frame.transformFrom(lhs.wTc);

    LOG(INFO) << "LineTriangulation --- Triangulation success!";
    return std::make_pair(true, plucker_line_in_world_frame);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineTriangulation::GTVector4
LineTriangulation::computePlaneFromLineCoefficient(GTVector3 const& line_coefficient_on_normalized_plane) const
{
    return GTVector4(line_coefficient_on_normalized_plane(0u), line_coefficient_on_normalized_plane(1u),
                     line_coefficient_on_normalized_plane(2u), 0.0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineTriangulation::GTScalar LineTriangulation::computeAngleBetweenTwoPlanes(GTVector4 const& left_plane,
                                                                            GTVector4 const& right_plane) const
{
    // normalize vector
    GTVector3 const normalized_normal_vector_of_plane_1 =
        GTVector3(left_plane(0u), left_plane(1u), left_plane(2u)).normalized();
    GTVector3 const normalized_normal_vector_of_plane_2 =
        GTVector3(right_plane(0u), right_plane(1u), right_plane(2u)).normalized();

    if (normalized_normal_vector_of_plane_1.norm() <= 1e-10 || normalized_normal_vector_of_plane_2.norm() <= 1e-10)
    {
        return GTScalar(0.0);
    }

    return std::acos(normalized_normal_vector_of_plane_1.dot(normalized_normal_vector_of_plane_2));
}
}  // namespace localization
}  // namespace holo
