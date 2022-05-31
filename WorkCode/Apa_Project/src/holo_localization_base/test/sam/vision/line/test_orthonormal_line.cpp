/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_orthonormal_line.cpp
 * @brief This file defines unit test of orthonormal line.
 * @author MaYufei(mayufei@holomatic.com)
 * @date "2021-12-15"
 */
#include <gtest/gtest.h>
#include <holo/localization/sam/sam.h>
#include <holo/localization/sam/vision/line/orthonormal_line.h>
#include <holo/log/hololog.h>

using namespace holo;
using namespace holo::localization;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, ConstructFromUAndWRotationMatrix)
{
    GTRot3 const                  expected_U = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                phi        = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W = OrthonormalLine::GTRot2(phi);

    GTOrthonormalLine orthonormal_line(expected_U, expected_W);
    ASSERT_EQ(orthonormal_line.getU().matrix(), expected_U.matrix());
    ASSERT_EQ(orthonormal_line.getW().matrix(), expected_W.matrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, ConstructFromUAndWRotationVector)
{
    GTVector3 const   u = GTVector3(1.0, 0.0, 0.0);
    GTScalar const    w = M_PI / 3;
    GTOrthonormalLine orthonormal_line(u, w);
    ASSERT_EQ(orthonormal_line.getU().matrix(), GTRot3::Expmap(u).matrix());
    ASSERT_EQ(orthonormal_line.getW().matrix(), OrthonormalLine::GTRot2::Expmap(gtsam::Vector1(w)).matrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, ConstructFrom4DimensionVector)
{
    GTVector4 const   orthonormal_line_vector = GTVector4(1.0, 0.0, 0.0, M_PI / 3);
    GTOrthonormalLine orthonormal_line(orthonormal_line_vector);
    ASSERT_EQ(
        orthonormal_line.getU().matrix(),
        GTRot3::Expmap(GTVector3(orthonormal_line_vector(0u), orthonormal_line_vector(1u), orthonormal_line_vector(2u)))
            .matrix());
    ASSERT_EQ(orthonormal_line.getW().matrix(),
              OrthonormalLine::GTRot2::Expmap(gtsam::Vector1(orthonormal_line_vector(3u))).matrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, ConstructFromPluckerLine)
{
    GTVector6 plucker_line_vector;
    plucker_line_vector << -1.0, -1.0, 1.0, 1.0, 2.0, 3.0;
    GTPluckerLine const plucker_line(plucker_line_vector);
    GTOrthonormalLine   orthonormal_line(plucker_line);

    GTPoint3 const colm1(-1 / sqrt(3), -1 / sqrt(3), 1 / sqrt(3));
    GTPoint3 const colm2(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14));
    GTPoint3 const colm3(-5 / sqrt(42), 4 / sqrt(42), -1 / sqrt(42));

    GTRot3                  expected_U(colm1, colm2, colm3);
    OrthonormalLine::GTRot2 expected_W(GTScalar(acos((sqrt(3) / sqrt(17)))));
    GTOrthonormalLine       expected_orthonormal_line(expected_U, expected_W);

    ASSERT_EQ(orthonormal_line.equals(expected_orthonormal_line), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, convertToPlukerLine)
{
    GTRot3 const                  expected_U = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                phi        = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W = OrthonormalLine::GTRot2(phi);

    GTOrthonormalLine orthonormal_line(expected_U, expected_W);
    GTPluckerLine     plucker_line = orthonormal_line.convertToPluckerLine();

    ASSERT_NEAR(plucker_line.getNormalVector()(0u), std::cos(M_PI / 3) * 1.0, 1e-10);
    ASSERT_NEAR(plucker_line.getNormalVector()(1u), std::cos(M_PI / 3) * 0.0, 1e-10);
    ASSERT_NEAR(plucker_line.getNormalVector()(2u), std::cos(M_PI / 3) * 0.0, 1e-10);
    ASSERT_NEAR(plucker_line.getDirectionVector()(0u), std::sin(M_PI / 3) * 0.0, 1e-10);
    ASSERT_NEAR(plucker_line.getDirectionVector()(1u), std::sin(M_PI / 3) * 0.0, 1e-10);
    ASSERT_NEAR(plucker_line.getDirectionVector()(2u), std::sin(M_PI / 3) * 1.0, 1e-10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, print)
{
    GTVector3 const   u = GTVector3(1.0, 0.0, 0.0);
    GTScalar const    w = M_PI / 3;
    GTOrthonormalLine orthonormal_line(u, w);

    std::string s;
    orthonormal_line.print(s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, equals)
{
    GTVector3 const   u_left = GTVector3(1.0, 0.0, 0.0);
    GTScalar const    w_left = M_PI / 3;
    GTOrthonormalLine orthonormal_line_left(u_left, w_left);
    GTOrthonormalLine orthonormal_line_right_test1(u_left, w_left);

    GTVector3 const   u = GTVector3(1.0, 1.0, 0.0);
    GTScalar const    w = M_PI / 3;
    GTOrthonormalLine orthonormal_line_right_test2(u, w);

    ASSERT_EQ(orthonormal_line_left.equals(orthonormal_line_right_test1), true);
    ASSERT_EQ(orthonormal_line_left.equals(orthonormal_line_right_test2), false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, inverse)
{
    GTRot3 const                  expected_U   = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                expected_phi = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W   = OrthonormalLine::GTRot2(expected_phi);
    GTOrthonormalLine             orthonormal_line(expected_U, expected_W);

    GTRot3 const      expected_U_inverse = expected_U.inverse();
    gtsam::Rot2 const expected_W_inverse = expected_W.inverse();

    ASSERT_EQ(orthonormal_line.inverse().getU().matrix(), expected_U_inverse.matrix());
    ASSERT_EQ(orthonormal_line.inverse().getW().matrix(), expected_W_inverse.matrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GTOrthonormalLine, operator_product)
{
    GTRot3 const                  expected_U_left   = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                expected_phi_left = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W_left   = OrthonormalLine::GTRot2(expected_phi_left);
    GTOrthonormalLine             orthonormal_line_left(expected_U_left, expected_W_left);

    GTRot3 const                  expected_U_right   = GTRot3::RzRyRx(M_PI / 3, 0.0, 0.0);
    GTScalar const                expected_phi_right = M_PI / 6;
    OrthonormalLine::GTRot2 const expected_W_right   = OrthonormalLine::GTRot2(expected_phi_right);
    GTOrthonormalLine             orthonormal_line_right(expected_U_right, expected_W_right);

    ASSERT_EQ((orthonormal_line_left * orthonormal_line_right).getU().matrix(),
              (orthonormal_line_left.getU() * orthonormal_line_right.getU()).matrix());
    ASSERT_EQ((orthonormal_line_left * orthonormal_line_right).getW().matrix(),
              (orthonormal_line_left.getW() * orthonormal_line_right.getW()).matrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OrthonormalLine, Expmap)
{
    GTRot3 const                  expected_U   = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                expected_phi = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W   = OrthonormalLine::GTRot2(expected_phi);
    GTOrthonormalLine             orthonormal_line(expected_U, expected_W);
    GTRot3                        expected_expmap = GTRot3(gtsam::traits<gtsam::SO3>::Expmap(GTVector3(1.0, 0.0, 0.0)));
    ASSERT_EQ(orthonormal_line.Expmap(GTVector4(1.0, 0.0, 0.0, 0.0)).getU().matrix(), expected_expmap.matrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OrthonormalLine, Logmap)
{
    GTRot3 const                  U   = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                phi = M_PI / 3;
    OrthonormalLine::GTRot2 const W   = OrthonormalLine::GTRot2(phi);
    GTOrthonormalLine             orthonormal_line(U, W);

    GTVector3                     expected_algebra = GTVector3(1.0, 0.0, 0.0);
    GTRot3 const                  expected_U       = GTRot3(gtsam::traits<gtsam::SO3>::Expmap(expected_algebra));
    GTScalar const                expected_phi     = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W       = OrthonormalLine::GTRot2(expected_phi);
    GTOrthonormalLine             expected_orthonormal_line(expected_U, expected_W);
    GTVector4                     logmap_result = orthonormal_line.Logmap(expected_orthonormal_line);
    ASSERT_EQ(GTVector3(logmap_result(0u), logmap_result(1u), logmap_result(2u)), expected_algebra);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OrthonormalLine, AdjointMap)
{
    GTRot3 const                  expected_U   = GTRot3::RzRyRx(M_PI / 2, 0.0, 0.0);
    GTScalar const                expected_phi = M_PI / 3;
    OrthonormalLine::GTRot2 const expected_W   = OrthonormalLine::GTRot2(expected_phi);
    GTOrthonormalLine             orthonormal_line(expected_U, expected_W);

    GTMatrix3 matrix_on_left_corner  = orthonormal_line.AdjointMap().block<3u, 3u>(0u, 0u);
    GTMatrix  matrix_on_right_corner = orthonormal_line.AdjointMap().block<1u, 1u>(3u, 3u);
    ASSERT_EQ(matrix_on_left_corner, orthonormal_line.getU().matrix());
    ASSERT_EQ(matrix_on_right_corner, gtsam::I_1x1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(OrthonormalLine, OptimizationFunction)
{
    // add values
    GTRot3 const                  U1   = GTRot3::RzRyRx(M_PI / 2 + 0.1, 0.0, 0.0);
    GTScalar const                phi1 = M_PI / 3 + 0.1;
    OrthonormalLine::GTRot2 const W1   = OrthonormalLine::GTRot2(phi1);
    GTOrthonormalLine             orthonormal_line1(U1, W1);
    orthonormal_line1.print("value1");

    GTRot3 const                  U2   = GTRot3::RzRyRx(M_PI / 2 - 0.1, 0.0, 0.0);
    GTScalar const                phi2 = M_PI / 3 + 0.2;
    OrthonormalLine::GTRot2 const W2   = OrthonormalLine::GTRot2(phi2);
    GTOrthonormalLine             orthonormal_line2(U2, W2);
    orthonormal_line2.print("value2");

    GTValues values;
    values.insert<GTOrthonormalLine>(symbol_shorthand::X(1), orthonormal_line1);
    values.insert<GTOrthonormalLine>(symbol_shorthand::X(2), orthonormal_line2);

    // construct prior measurement
    GTRot3 const                  U_initial   = GTRot3::identity();
    GTScalar const                phi_initial = M_PI / 3 + 0.0;
    OrthonormalLine::GTRot2 const W_initial   = OrthonormalLine::GTRot2(phi_initial);
    GTOrthonormalLine             orthonormal_line_measurement_initial(U_initial, W_initial);
    orthonormal_line_measurement_initial.print("prior measure");

    // construct between measurement
    GTRot3 const                  U   = GTRot3::identity();
    GTScalar const                phi = 0.0;
    OrthonormalLine::GTRot2 const W   = OrthonormalLine::GTRot2(phi);
    GTOrthonormalLine             orthonormal_line_measurement(U, W);
    orthonormal_line_measurement.print("between measure");

    // add factors
    gtsam::PriorFactor<OrthonormalLine> prior_factor =
        gtsam::PriorFactor<GTOrthonormalLine>(symbol_shorthand::X(1), orthonormal_line_measurement_initial);

    gtsam::BetweenFactor<OrthonormalLine> between_factor = gtsam::BetweenFactor<OrthonormalLine>(
        symbol_shorthand::X(1), symbol_shorthand::X(2), orthonormal_line_measurement);

    GTNonlinearFactorGraph factor_graph;
    factor_graph.add(prior_factor);
    factor_graph.add(between_factor);

    // start smooth
    GTIncrementalFixedLagSmoother smoother;
    smoother.update(factor_graph, values);
    GTValues result = smoother.calculateEstimate();
    result.print();

    // compare X1、X2 and measure
    OrthonormalLine optimized_line1 = result.at<GTOrthonormalLine>(symbol_shorthand::X(1));
    OrthonormalLine optimized_line2 = result.at<GTOrthonormalLine>(symbol_shorthand::X(2));

    ASSERT_EQ(optimized_line1.equals(orthonormal_line_measurement_initial), true);
    ASSERT_EQ(optimized_line2.equals(orthonormal_line_measurement_initial), true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}