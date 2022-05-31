/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_plucker_line.cpp
 * @brief This file defines unit test of plucker line.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-09"
 */
#include <gtest/gtest.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/sam/vision/line/plucker_line.h>

using namespace holo;
using namespace holo::localization;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PluckerLine, ConstructFromPluckerLine)
{
    GTVector6 plucker_line;
    plucker_line << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0;

    GTPluckerLine const construct_plucker_line = GTPluckerLine(plucker_line);
    ASSERT_EQ(construct_plucker_line.getNormalVector(),
              GTVector3(plucker_line(0u), plucker_line(1u), plucker_line(2u)));
    ASSERT_EQ(construct_plucker_line.getDirectionVector(),
              GTVector3(plucker_line(3u), plucker_line(4u), plucker_line(5u)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PluckerLine, ConstructFromNormalVectorAndDirectionVector)
{
    GTVector3 const normal_vector(1.0, 0.0, 0.0);
    GTVector3 const direction_vector(0.0, 1.0, 0.0);
    GTPluckerLine   plucker_line(normal_vector, direction_vector);

    ASSERT_EQ(plucker_line.getDirectionVector(), direction_vector);
    ASSERT_EQ(plucker_line.getNormalVector(), normal_vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PluckerLine, ConstructFromDualPluckerMatrix)
{
    GTVector3 const normal_vector(-1.0, -1.0, 1.0);
    GTVector3 const direction_vector(1.0, 2.0, 3.0);
    GTMatrix4       dual_plucker_matrix;
    GTMatrix3 const skew_symmetric_matrix_of_direction_vector =
        gtsam::skewSymmetric(direction_vector(0u), direction_vector(1u), direction_vector(2u));
    dual_plucker_matrix.block<3u, 3u>(0u, 0u) = skew_symmetric_matrix_of_direction_vector;
    dual_plucker_matrix.block<3u, 1u>(0u, 3u) = normal_vector;
    dual_plucker_matrix.block<1u, 3u>(3u, 0u) = -normal_vector.transpose();

    GTPluckerLine plucker_line(dual_plucker_matrix);
    ASSERT_EQ(plucker_line.getNormalVector(), normal_vector);
    ASSERT_EQ(plucker_line.getDirectionVector(), direction_vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PluckerLine, ConstructFromTwoPlanes)
{
    GTVector3 const normal_vector    = GTVector3(-1.0, -1.0, 1.0);
    GTVector3 const direction_vector = GTVector3(1.0, 2.0, 3.0);

    GTVector4 const plane1       = GTVector4(-1.0, -1.0, 1.0, 0.0);
    GTVector4 const plane2       = GTVector4(1.0, 4.0, -3.0, 1.0);
    GTPluckerLine   plucker_line = GTPluckerLine(plane1, plane2);

    ASSERT_EQ(plucker_line.getNormalVector(), normal_vector);
    ASSERT_EQ(plucker_line.getDirectionVector(), direction_vector);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PluckerLine, transformFrom)
{
    GTVector3 const normal_vector    = GTVector3(1.0, 0.0, 0.0);
    GTVector3 const direction_vector = GTVector3(0.0, 1.0, 0.0);
    GTVector6       plucker_line;
    plucker_line << normal_vector(0u), normal_vector(1u), normal_vector(2u), direction_vector(0u), direction_vector(1u),
        direction_vector(2u);

    GTRot3 const   rotation_matrix = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTPoint3 const translation     = GTVector3(0.0, 0.0, 0.0);
    GTPose3 const  tTs(rotation_matrix, translation);

    GTPluckerLine construct_plucker_line = GTPluckerLine(plucker_line);
    GTPluckerLine expect_plucker_line    = construct_plucker_line.transformFrom(tTs);

    ASSERT_NEAR(expect_plucker_line.getDirectionVector()(0u), 0.0, 1e-10);
    ASSERT_NEAR(expect_plucker_line.getDirectionVector()(1u), 0.0, 1e-10);
    ASSERT_NEAR(expect_plucker_line.getDirectionVector()(2u), 1.0, 1e-10);
    ASSERT_NEAR(expect_plucker_line.getNormalVector()(0u), 1.0, 1e-10);
    ASSERT_NEAR(expect_plucker_line.getNormalVector()(1u), 0.0, 1e-10);
    ASSERT_NEAR(expect_plucker_line.getNormalVector()(2u), 0.0, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}