/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_line_triangulation.cpp
 * @brief This file defines unit test of line triangulation.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-16"
 */
#include <gtest/gtest.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/sam/vision/line/line_triangulation.h>
#include <holo/log/hololog.h>

using namespace holo;
using namespace holo::localization;

// case1
// construct two point on line in world coordinate
GTVector4 const case_1_endpoint_a(5.0, 0.5, 1.2, 1.0);
GTVector4 const case_1_endpoint_b(5.0, 1.0, 1.2, 1.0);

// case2
// construct two point on line in world coordinate
GTVector4 const case_2_endpoint_a(0.0, 0.5, -0.5, 1.0);
GTVector4 const case_2_endpoint_b(0.0, 0.5, -1.0, 1.0);

class LineTriangulationTest : public LineTriangulation
{
public:
    LineTriangulationTest(LineTriangulation::Parameters const& parameters) : LineTriangulation(parameters)
    {
    }

    GTScalar TestComputeAngleBetweenTwoPlanes(GTVector4 const& plane1, GTVector4 const& plane2)
    {
        return computeAngleBetweenTwoPlanes(plane1, plane2);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, runwithCameraInfoWithLineCoefficient1_TriangulateSuccess)
{
    // construct actual space line landmark
    GTMatrix4 const plucker_matrix =
        case_1_endpoint_a * case_1_endpoint_b.transpose() - case_1_endpoint_b * case_1_endpoint_a.transpose();
    GTVector3 const expected_normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const expected_direction_vector   = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   expected_space_plucker_line = GTPluckerLine(expected_normal_vector, expected_direction_vector);

    // prepair left data
    GTRot3 const   left_rotation    = GTRot3::RzRyRx(-M_PI / 2, 0.0, -M_PI / 2);
    GTPoint3 const left_translation = GTPoint3(0.0, 0.0, 1.0);
    GTPose3 const  left_wTc         = GTPose3(left_rotation, left_translation);
    GTMatrix3      left_K;
    left_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to left image plane
    GTPluckerLine const expected_left_camera_plucker_line =
        expected_space_plucker_line.transformFrom(left_wTc.inverse());

    GTMatrix3 left_line_intrinsic_matrix = GTMatrix3::Zero();
    left_line_intrinsic_matrix(0, 0)     = left_K(1, 1);
    left_line_intrinsic_matrix(1, 1)     = left_K(0, 0);
    left_line_intrinsic_matrix(2, 0)     = -left_K(1, 1) * left_K(0, 2);
    left_line_intrinsic_matrix(2, 1)     = -left_K(0, 0) * left_K(1, 2);
    left_line_intrinsic_matrix(2, 2)     = left_K(0, 0) * left_K(1, 1);

    GTVector3 const left_line_coefficient_on_image_plane =
        left_line_intrinsic_matrix * expected_left_camera_plucker_line.getNormalVector();

    GTPose3 const right_wTc = left_wTc * GTPose3(GTRot3(), GTPoint3(1.2, 1.2, 1.0));
    GTMatrix3     right_K;
    right_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to right image plane
    GTPluckerLine const expected_right_camera_plucker_line =
        expected_space_plucker_line.transformFrom(right_wTc.inverse());
    GTMatrix3 right_line_intrinsic_matrix = GTMatrix3::Zero();
    right_line_intrinsic_matrix(0, 0)     = right_K(1, 1);
    right_line_intrinsic_matrix(1, 1)     = right_K(0, 0);
    right_line_intrinsic_matrix(2, 0)     = -right_K(1, 1) * right_K(0, 2);
    right_line_intrinsic_matrix(2, 1)     = -right_K(0, 0) * right_K(1, 2);
    right_line_intrinsic_matrix(2, 2)     = right_K(0, 0) * right_K(1, 1);

    GTVector3 const right_line_coefficient_on_image_plane =
        right_line_intrinsic_matrix * expected_right_camera_plucker_line.getNormalVector();

    // construct LineTriangulation object
    GTLineTriangulation::Parameters const parameters = GTLineTriangulation::Parameters::GenerateExample();
    GTLineTriangulation                   line_triangulation(parameters);

    // run triangulate
    GTLineTriangulation::CameraInfoWithLineCoefficient left_camera_info_with_line_coefficient(
        left_wTc, left_K, left_line_coefficient_on_image_plane);

    GTLineTriangulation::CameraInfoWithLineCoefficient right_camera_info_with_line_coefficient(
        right_wTc, right_K, right_line_coefficient_on_image_plane);

    std::pair<bool, GTPluckerLine> result =
        line_triangulation.run(left_camera_info_with_line_coefficient, right_camera_info_with_line_coefficient);

    // check if the computed plucker line and expected plucker line are different by a scale(positive or negtive).
    // if so, they are the same space line actually.
    GTVector6 normalized_expected_plucker_line;
    normalized_expected_plucker_line << expected_space_plucker_line.getNormalVector().normalized(),
        expected_space_plucker_line.getDirectionVector().normalized();

    GTVector6 normalized_result_plucker_line;
    normalized_result_plucker_line << result.second.getNormalVector().normalized(),
        result.second.getDirectionVector().normalized();

    for (int i = 0; i < 6; i++)
    {
        if ((normalized_expected_plucker_line(i) != 0) && (normalized_result_plucker_line(i) != 0) &&
            (normalized_expected_plucker_line(i) * normalized_result_plucker_line(i) < 0))
        {
            normalized_expected_plucker_line = -normalized_expected_plucker_line;
        }
    }

    ASSERT_EQ(result.first, true);
    ASSERT_NEAR(normalized_result_plucker_line(0u), normalized_expected_plucker_line(0u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(1u), normalized_expected_plucker_line(1u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(2u), normalized_expected_plucker_line(2u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(3u), normalized_expected_plucker_line(3u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(4u), normalized_expected_plucker_line(4u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(5u), normalized_expected_plucker_line(5u), 1e-4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, runwithCameraInfoWithLineCoefficient2_TriangulateSuccess)
{
    // construct actual space line landmark
    GTMatrix4 const plucker_matrix =
        case_2_endpoint_a * case_2_endpoint_b.transpose() - case_2_endpoint_b * case_2_endpoint_a.transpose();
    GTVector3 const expected_normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const expected_direction_vector   = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   expected_space_plucker_line = GTPluckerLine(expected_normal_vector, expected_direction_vector);

    // left camera to world coordinate
    GTRot3 const   left_rotation    = GTRot3::Ypr(0.0, M_PI / 2, M_PI / 2);
    GTPoint3 const left_translation = GTPoint3(1.0, 0.5, 0.5);
    GTPose3 const  left_wTc         = GTPose3(left_rotation.inverse(), left_translation);
    GTMatrix3      left_K;
    left_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to left image plane
    GTPluckerLine const expected_left_camera_plucker_line =
        expected_space_plucker_line.transformFrom(left_wTc.inverse());
    GTMatrix3 left_line_intrinsic_matrix = GTMatrix3::Zero();
    left_line_intrinsic_matrix(0, 0)     = left_K(1, 1);
    left_line_intrinsic_matrix(1, 1)     = left_K(0, 0);
    left_line_intrinsic_matrix(2, 0)     = -left_K(1, 1) * left_K(0, 2);
    left_line_intrinsic_matrix(2, 1)     = -left_K(0, 0) * left_K(1, 2);
    left_line_intrinsic_matrix(2, 2)     = left_K(0, 0) * left_K(1, 1);

    GTVector3 const left_line_coefficient_on_image_plane =
        left_line_intrinsic_matrix * expected_left_camera_plucker_line.getNormalVector();

    // right camera to world coordinate
    GTRot3 const   right_rotation    = GTRot3::Ypr(0.0, M_PI, M_PI / 2);
    GTPoint3 const right_translation = GTPoint3(0.0, 1.0, 0.5);
    GTPose3 const  right_wTc         = GTPose3(right_rotation.inverse(), right_translation);
    GTMatrix3      right_K;
    right_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to right image plane
    GTPluckerLine const actual_right_camera_plucker_line =
        expected_space_plucker_line.transformFrom(right_wTc.inverse());
    GTMatrix3 right_line_intrinsic_matrix = GTMatrix3::Zero();
    right_line_intrinsic_matrix(0, 0)     = right_K(1, 1);
    right_line_intrinsic_matrix(1, 1)     = right_K(0, 0);
    right_line_intrinsic_matrix(2, 0)     = -right_K(1, 1) * right_K(0, 2);
    right_line_intrinsic_matrix(2, 1)     = -right_K(0, 0) * right_K(1, 2);
    right_line_intrinsic_matrix(2, 2)     = right_K(0, 0) * right_K(1, 1);

    GTVector3 const right_line_coefficient_on_image_plane =
        right_line_intrinsic_matrix * actual_right_camera_plucker_line.getNormalVector();

    // construct LineTriangulation object
    GTLineTriangulation::Parameters const parameters = GTLineTriangulation::Parameters::GenerateExample();
    GTLineTriangulation                   line_triangulation(parameters);

    // run triangulate
    GTLineTriangulation::CameraInfoWithLineCoefficient const left_camera_info_with_line_coefficient(
        left_wTc, left_K, left_line_coefficient_on_image_plane);

    GTLineTriangulation::CameraInfoWithLineCoefficient const right_camera_info_with_line_coefficient(
        right_wTc, right_K, right_line_coefficient_on_image_plane);

    std::pair<bool, GTPluckerLine> result =
        line_triangulation.run(left_camera_info_with_line_coefficient, right_camera_info_with_line_coefficient);

    // check if the computed plucker line and expected plucker line are different by a scale(positive or negtive).
    // if so, they are the same space line actually.
    GTVector6 normalized_expected_plucker_line;
    normalized_expected_plucker_line << expected_space_plucker_line.getNormalVector().normalized(),
        expected_space_plucker_line.getDirectionVector().normalized();

    GTVector6 normalized_result_plucker_line;
    normalized_result_plucker_line << result.second.getNormalVector().normalized(),
        result.second.getDirectionVector().normalized();

    for (int i = 0; i < 6; i++)
    {
        if ((normalized_expected_plucker_line(i) != 0) && (normalized_result_plucker_line(i) != 0) &&
            (normalized_expected_plucker_line(i) * normalized_result_plucker_line(i) < 0))
        {
            normalized_expected_plucker_line = -normalized_expected_plucker_line;
        }
    }

    ASSERT_EQ(result.first, true);
    ASSERT_NEAR(normalized_result_plucker_line(0u), normalized_expected_plucker_line(0u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(1u), normalized_expected_plucker_line(1u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(2u), normalized_expected_plucker_line(2u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(3u), normalized_expected_plucker_line(3u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(4u), normalized_expected_plucker_line(4u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(5u), normalized_expected_plucker_line(5u), 1e-4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, runwithCameraInfoWithLineCoefficient3_TriangulateFailed_DistanceTooSmall)
{
    // construct actual space line landmark
    GTMatrix4 const plucker_matrix =
        case_2_endpoint_a * case_2_endpoint_b.transpose() - case_2_endpoint_b * case_2_endpoint_a.transpose();
    GTVector3 const expected_normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const expected_direction_vector   = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   expected_space_plucker_line = GTPluckerLine(expected_normal_vector, expected_direction_vector);

    // left camera to world coordinate
    GTRot3 const   left_rotation    = GTRot3::Ypr(0.0, M_PI / 2, M_PI / 2);
    GTPoint3 const left_translation = GTPoint3(1.0, 0.5, 0.5);
    GTPose3 const  left_wTc         = GTPose3(left_rotation.inverse(), left_translation);
    GTMatrix3      left_K;
    left_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to left image plane
    GTPluckerLine const expected_left_camera_plucker_line =
        expected_space_plucker_line.transformFrom(left_wTc.inverse());
    GTMatrix3 left_line_intrinsic_matrix = GTMatrix3::Zero();
    left_line_intrinsic_matrix(0, 0)     = left_K(1, 1);
    left_line_intrinsic_matrix(1, 1)     = left_K(0, 0);
    left_line_intrinsic_matrix(2, 0)     = -left_K(1, 1) * left_K(0, 2);
    left_line_intrinsic_matrix(2, 1)     = -left_K(0, 0) * left_K(1, 2);
    left_line_intrinsic_matrix(2, 2)     = left_K(0, 0) * left_K(1, 1);

    GTVector3 const left_line_coefficient_on_image_plane =
        left_line_intrinsic_matrix * expected_left_camera_plucker_line.getNormalVector();

    // right camera to world coordinate
    GTRot3 const   right_rotation    = GTRot3::Ypr(0.0, M_PI, M_PI / 2);
    GTPoint3 const right_translation = GTPoint3(1.0, 0.2, 0.5);
    GTPose3 const  right_wTc         = GTPose3(right_rotation.inverse(), right_translation);
    GTMatrix3      right_K;
    right_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to right image plane
    GTPluckerLine const actual_right_camera_plucker_line =
        expected_space_plucker_line.transformFrom(right_wTc.inverse());
    GTMatrix3 right_line_intrinsic_matrix = GTMatrix3::Zero();
    right_line_intrinsic_matrix(0, 0)     = right_K(1, 1);
    right_line_intrinsic_matrix(1, 1)     = right_K(0, 0);
    right_line_intrinsic_matrix(2, 0)     = -right_K(1, 1) * right_K(0, 2);
    right_line_intrinsic_matrix(2, 1)     = -right_K(0, 0) * right_K(1, 2);
    right_line_intrinsic_matrix(2, 2)     = right_K(0, 0) * right_K(1, 1);

    GTVector3 const right_line_coefficient_on_image_plane =
        right_line_intrinsic_matrix * actual_right_camera_plucker_line.getNormalVector();

    // construct LineTriangulation object
    GTLineTriangulation::Parameters const parameters = GTLineTriangulation::Parameters::GenerateExample();
    GTLineTriangulation                   line_triangulation(parameters);

    // run triangulate
    GTLineTriangulation::CameraInfoWithLineCoefficient const left_camera_info_with_line_coefficient(
        left_wTc, left_K, left_line_coefficient_on_image_plane);

    GTLineTriangulation::CameraInfoWithLineCoefficient const right_camera_info_with_line_coefficient(
        right_wTc, right_K, right_line_coefficient_on_image_plane);

    std::pair<bool, GTPluckerLine> result =
        line_triangulation.run(left_camera_info_with_line_coefficient, right_camera_info_with_line_coefficient);

    ASSERT_EQ(result.first, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, runwithCameraInfoWithLineCoefficient3_TriangulateFailed_AngleTooSmall)
{
    // construct actual space line landmark
    GTMatrix4 const plucker_matrix =
        case_1_endpoint_a * case_1_endpoint_b.transpose() - case_1_endpoint_b * case_1_endpoint_a.transpose();
    GTVector3 const expected_normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const expected_direction_vector   = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   expected_space_plucker_line = GTPluckerLine(expected_normal_vector, expected_direction_vector);

    // prepair left data
    GTRot3 const   left_rotation    = GTRot3::RzRyRx(-M_PI / 2, 0.0, -M_PI / 2);
    GTPoint3 const left_translation = GTPoint3(0.0, 0.0, 1.0);
    GTPose3 const  left_wTc         = GTPose3(left_rotation, left_translation);
    GTMatrix3      left_K;
    left_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to left image plane
    GTPluckerLine const expected_left_camera_plucker_line =
        expected_space_plucker_line.transformFrom(left_wTc.inverse());

    GTMatrix3 left_line_intrinsic_matrix = GTMatrix3::Zero();
    left_line_intrinsic_matrix(0, 0)     = left_K(1, 1);
    left_line_intrinsic_matrix(1, 1)     = left_K(0, 0);
    left_line_intrinsic_matrix(2, 0)     = -left_K(1, 1) * left_K(0, 2);
    left_line_intrinsic_matrix(2, 1)     = -left_K(0, 0) * left_K(1, 2);
    left_line_intrinsic_matrix(2, 2)     = left_K(0, 0) * left_K(1, 1);

    GTVector3 const left_line_coefficient_on_image_plane =
        left_line_intrinsic_matrix * expected_left_camera_plucker_line.getNormalVector();

    GTPose3 const right_wTc = left_wTc * GTPose3(GTRot3(), GTPoint3(0.2, 0.2, 1.0));
    GTMatrix3     right_K;
    right_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project space line to right image plane
    GTPluckerLine const expected_right_camera_plucker_line =
        expected_space_plucker_line.transformFrom(right_wTc.inverse());
    GTMatrix3 right_line_intrinsic_matrix = GTMatrix3::Zero();
    right_line_intrinsic_matrix(0, 0)     = right_K(1, 1);
    right_line_intrinsic_matrix(1, 1)     = right_K(0, 0);
    right_line_intrinsic_matrix(2, 0)     = -right_K(1, 1) * right_K(0, 2);
    right_line_intrinsic_matrix(2, 1)     = -right_K(0, 0) * right_K(1, 2);
    right_line_intrinsic_matrix(2, 2)     = right_K(0, 0) * right_K(1, 1);

    GTVector3 const right_line_coefficient_on_image_plane =
        right_line_intrinsic_matrix * expected_right_camera_plucker_line.getNormalVector();

    // construct LineTriangulation object
    GTLineTriangulation::Parameters const parameters = GTLineTriangulation::Parameters::GenerateExample();
    GTLineTriangulation                   line_triangulation(parameters);

    // run triangulate
    GTLineTriangulation::CameraInfoWithLineCoefficient left_camera_info_with_line_coefficient(
        left_wTc, left_K, left_line_coefficient_on_image_plane);

    GTLineTriangulation::CameraInfoWithLineCoefficient right_camera_info_with_line_coefficient(
        right_wTc, right_K, right_line_coefficient_on_image_plane);

    std::pair<bool, GTPluckerLine> result =
        line_triangulation.run(left_camera_info_with_line_coefficient, right_camera_info_with_line_coefficient);

    ASSERT_EQ(result.first, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, runwithCameraInfoWithLineEndpoints1_TriangulateSuccess)
{
    // prepair left data
    GTRot3 const   left_rotation    = GTRot3::RzRyRx(-M_PI / 2, 0.0, -M_PI / 2);
    GTPoint3 const left_translation = GTPoint3(0.0, 0.0, 1.0);
    GTPose3 const  left_wTc         = GTPose3(left_rotation, left_translation);

    GTMatrix3 left_K;
    left_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    GTPose3 const right_wTc = left_wTc * GTPose3(GTRot3(), GTPoint3(1.2, 1.2, 1.0));
    GTMatrix3     right_K;
    right_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project two space points to left plane

    GTPoint3 const endpoint_a_in_left_camera =
        left_wTc.inverse().transform_from(GTPoint3(case_1_endpoint_a(0), case_1_endpoint_a(1), case_1_endpoint_a(2)));
    GTPoint3 const endpoint_b_in_left_camera =
        left_wTc.inverse().transform_from(GTPoint3(case_1_endpoint_b(0), case_1_endpoint_b(1), case_1_endpoint_b(2)));

    GTVector3 const endpoint_a_on_left_image_with_z = left_K * endpoint_a_in_left_camera;
    GTPoint2 const  endpoint_a_on_left_image(endpoint_a_on_left_image_with_z(0u) / endpoint_a_on_left_image_with_z(2u),
                                            endpoint_a_on_left_image_with_z(1u) / endpoint_a_on_left_image_with_z(2u));

    GTVector3 const endpoint_b_on_left_image_with_z = left_K * endpoint_b_in_left_camera;
    GTPoint2 const  endpoint_b_on_left_image(endpoint_b_on_left_image_with_z(0u) / endpoint_b_on_left_image_with_z(2u),
                                            endpoint_b_on_left_image_with_z(1u) / endpoint_b_on_left_image_with_z(2u));

    // project two space points to right plane
    GTPoint3 const endpoint_a_in_right_camera =
        right_wTc.inverse().transform_from(GTPoint3(case_1_endpoint_a(0), case_1_endpoint_a(1), case_1_endpoint_a(2)));
    GTPoint3 const endpoint_b_in_right_camera =
        right_wTc.inverse().transform_from(GTPoint3(case_1_endpoint_b(0), case_1_endpoint_b(1), case_1_endpoint_b(2)));

    GTVector3 const endpoint_a_on_right_image_with_z = right_K * endpoint_a_in_right_camera;
    GTPoint2 const  endpoint_a_on_right_image(
        endpoint_a_on_right_image_with_z(0u) / endpoint_a_on_right_image_with_z(2u),
        endpoint_a_on_right_image_with_z(1u) / endpoint_a_on_right_image_with_z(2u));

    GTVector3 const endpoint_b_on_right_image_with_z = right_K * endpoint_b_in_right_camera;
    GTPoint2 const  endpoint_b_on_right_image(
        endpoint_b_on_right_image_with_z(0u) / endpoint_b_on_right_image_with_z(2u),
        endpoint_b_on_right_image_with_z(1u) / endpoint_b_on_right_image_with_z(2u));

    // construct LineTriangulation object
    GTLineTriangulation::Parameters const parameters = GTLineTriangulation::Parameters::GenerateExample();
    GTLineTriangulation                   line_triangulation(parameters);

    // run triangulate
    GTLineTriangulation::CameraInfoWithLineEndpoints left_camera_info_with_line_coefficient(
        left_wTc, left_K, endpoint_a_on_left_image, endpoint_b_on_left_image);
    GTLineTriangulation::CameraInfoWithLineEndpoints right_camera_info_with_line_coefficient(
        right_wTc, right_K, endpoint_a_on_right_image, endpoint_b_on_right_image);

    std::pair<bool, GTPluckerLine> result =
        line_triangulation.run(left_camera_info_with_line_coefficient, right_camera_info_with_line_coefficient);

    // construct actual space line landmark
    GTMatrix4 const plucker_matrix =
        case_1_endpoint_a * case_1_endpoint_b.transpose() - case_1_endpoint_b * case_1_endpoint_a.transpose();
    GTVector3 const expected_normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const expected_direction_vector   = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   expected_space_plucker_line = GTPluckerLine(expected_normal_vector, expected_direction_vector);

    // check if the computed plucker line and expected plucker line are different by a scale(positive or negtive).
    // if so, they are the same space line actually.
    GTVector6 normalized_expected_plucker_line;
    normalized_expected_plucker_line << expected_space_plucker_line.getNormalVector().normalized(),
        expected_space_plucker_line.getDirectionVector().normalized();

    GTVector6 normalized_result_plucker_line;
    normalized_result_plucker_line << result.second.getNormalVector().normalized(),
        result.second.getDirectionVector().normalized();

    for (int i = 0; i < 6; i++)
    {
        if ((normalized_expected_plucker_line(i) != 0) && (normalized_result_plucker_line(i) != 0) &&
            (normalized_expected_plucker_line(i) * normalized_result_plucker_line(i) < 0))
        {
            normalized_expected_plucker_line = -normalized_expected_plucker_line;
        }
    }

    ASSERT_EQ(result.first, true);
    ASSERT_NEAR(normalized_result_plucker_line(0u), normalized_expected_plucker_line(0u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(1u), normalized_expected_plucker_line(1u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(2u), normalized_expected_plucker_line(2u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(3u), normalized_expected_plucker_line(3u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(4u), normalized_expected_plucker_line(4u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(5u), normalized_expected_plucker_line(5u), 1e-4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, runwithCameraInfoWithLineEndpoints2_TriangulateSuccess)
{
    // left camera to world coordinate
    GTRot3 const   left_rotation    = GTRot3::Ypr(0.0, M_PI / 2, M_PI / 2);
    GTPoint3 const left_translation = GTPoint3(1.0, 0.5, 0.5);
    GTPose3 const  left_wTc         = GTPose3(left_rotation.inverse(), left_translation);

    GTMatrix3 left_K;
    left_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // right camera to world coordinate
    GTRot3 const   right_rotation    = GTRot3::Ypr(0.0, M_PI, M_PI / 2);
    GTPoint3 const right_translation = GTPoint3(0.0, 1.0, 0.5);
    GTPose3 const  right_wTc         = GTPose3(right_rotation.inverse(), right_translation);

    GTMatrix3 right_K;
    right_K << 1200.0, 0.0, 960.0, 0.0, 1200.0, 540.0, 0.0, 0.0, 1.0;

    // project two space points to left plane
    GTPoint3 const endpoint_a_in_left_camera =
        left_wTc.inverse().transform_from(GTPoint3(case_2_endpoint_a(0), case_2_endpoint_a(1), case_2_endpoint_a(2)));
    GTPoint3 const endpoint_b_in_left_camera =
        left_wTc.inverse().transform_from(GTPoint3(case_2_endpoint_b(0), case_2_endpoint_b(1), case_2_endpoint_b(2)));

    GTVector3 const endpoint_a_on_left_image_with_z = left_K * endpoint_a_in_left_camera;
    GTPoint2 const  endpoint_a_on_left_image(endpoint_a_on_left_image_with_z(0u) / endpoint_a_on_left_image_with_z(2u),
                                            endpoint_a_on_left_image_with_z(1u) / endpoint_a_on_left_image_with_z(2u));

    GTVector3 const endpoint_b_on_left_image_with_z = left_K * endpoint_b_in_left_camera;
    GTPoint2 const  endpoint_b_on_left_image(endpoint_b_on_left_image_with_z(0u) / endpoint_b_on_left_image_with_z(2u),
                                            endpoint_b_on_left_image_with_z(1u) / endpoint_b_on_left_image_with_z(2u));

    // project two space points to right plane
    GTPoint3 const endpoint_a_in_right_camera =
        right_wTc.inverse().transform_from(GTPoint3(case_2_endpoint_a(0), case_2_endpoint_a(1), case_2_endpoint_a(2)));
    GTPoint3 const endpoint_b_in_right_camera =
        right_wTc.inverse().transform_from(GTPoint3(case_2_endpoint_b(0), case_2_endpoint_b(1), case_2_endpoint_b(2)));

    GTVector3 const endpoint_a_on_right_image_with_z = right_K * endpoint_a_in_right_camera;
    GTPoint2 const  endpoint_a_on_right_image(
        endpoint_a_on_right_image_with_z(0u) / endpoint_a_on_right_image_with_z(2u),
        endpoint_a_on_right_image_with_z(1u) / endpoint_a_on_right_image_with_z(2u));

    GTVector3 const endpoint_b_on_right_image_with_z = right_K * endpoint_b_in_right_camera;
    GTPoint2 const  endpoint_b_on_right_image(
        endpoint_b_on_right_image_with_z(0u) / endpoint_b_on_right_image_with_z(2u),
        endpoint_b_on_right_image_with_z(1u) / endpoint_b_on_right_image_with_z(2u));

    // construct LineTriangulation object
    GTLineTriangulation::Parameters const parameters = GTLineTriangulation::Parameters::GenerateExample();
    GTLineTriangulation                   line_triangulation(parameters);

    // run triangulate
    GTLineTriangulation::CameraInfoWithLineEndpoints const left_camera_info_with_line_endpoints(
        left_wTc, left_K, endpoint_a_on_left_image, endpoint_b_on_left_image);

    GTLineTriangulation::CameraInfoWithLineEndpoints const right_camera_info_with_line_endpoints(
        right_wTc, right_K, endpoint_a_on_right_image, endpoint_b_on_right_image);

    std::pair<bool, GTPluckerLine> result =
        line_triangulation.run(left_camera_info_with_line_endpoints, right_camera_info_with_line_endpoints);

    // construct actual space line landmark
    GTMatrix4 const plucker_matrix =
        case_2_endpoint_a * case_2_endpoint_b.transpose() - case_2_endpoint_b * case_2_endpoint_a.transpose();
    GTVector3 const expected_normal_vector(-plucker_matrix(1u, 2u), plucker_matrix(0u, 2u), -plucker_matrix(0u, 1u));
    GTVector3 const expected_direction_vector   = GTVector3(plucker_matrix.block<3u, 1u>(0u, 3u));
    GTPluckerLine   expected_space_plucker_line = GTPluckerLine(expected_normal_vector, expected_direction_vector);

    // check if the computed plucker line and expected plucker line are different by a scale(positive or negtive).
    // if so, they are the same space line actually.
    GTVector6 normalized_expected_plucker_line;
    normalized_expected_plucker_line << expected_space_plucker_line.getNormalVector().normalized(),
        expected_space_plucker_line.getDirectionVector().normalized();

    GTVector6 normalized_result_plucker_line;
    normalized_result_plucker_line << result.second.getNormalVector().normalized(),
        result.second.getDirectionVector().normalized();

    for (int i = 0; i < 6; i++)
    {
        if ((normalized_expected_plucker_line(i) != 0) && (normalized_result_plucker_line(i) != 0) &&
            (normalized_expected_plucker_line(i) * normalized_result_plucker_line(i) < 0))
        {
            normalized_expected_plucker_line = -normalized_expected_plucker_line;
        }
    }

    ASSERT_EQ(result.first, true);
    ASSERT_NEAR(normalized_result_plucker_line(0u), normalized_expected_plucker_line(0u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(1u), normalized_expected_plucker_line(1u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(2u), normalized_expected_plucker_line(2u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(3u), normalized_expected_plucker_line(3u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(4u), normalized_expected_plucker_line(4u), 1e-4);
    ASSERT_NEAR(normalized_result_plucker_line(5u), normalized_expected_plucker_line(5u), 1e-4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTLineTriangulation, computeAngleBetweenTwoPlanes)
{
    GTVector4 plane1(0.6, 0, -2.5, 5.0);
    GTVector4 plane2(0, -0.5, 0, 2.0);

    GTLineTriangulation::Parameters parameters = GTLineTriangulation::Parameters::GenerateExample();
    LineTriangulationTest           line_triangulation(parameters);
    GTScalar                        actual_angle = line_triangulation.TestComputeAngleBetweenTwoPlanes(plane1, plane2);
    ASSERT_EQ(actual_angle, M_PI / 2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}