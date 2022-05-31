/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_essential_matrix_factor.cpp
 * @brief test EssentialMatrixFactor class
 * @author Lifeng(lifeng@holomaitc.com)
 * @date "Jan-03-2022"
 */

#include <random>

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <holo/localization/vision/vslam/essential_matrix_factor.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(EssentialMatrixFactor, ErrorAndJacobian)
{
    // generate pose ground truth
    const gtsam::Rot3   R = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3 t = gtsam::Point3(0.4, 0.5, 1.0);
    const gtsam::Pose3  wTb2(R, t);
    const gtsam::Pose3  wTb1 = gtsam::Pose3::identity();

    // use identity extrinsic parameter
    const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

    // generate feature point on noramlized coordinate
    const holo::float64_t depth = 10.0;
    const gtsam::Point3   p1(0.3, -0.2, 1.0);
    const gtsam::Point3   landmark = p1 * depth;

    // generate feature point in camera2 coordinate
    const gtsam::Point3 pc2 = (wTb2 * T_bc).transformTo(landmark);
    const gtsam::Point3 p2  = pc2 / pc2.z();

    // define pose key
    const gtsam::Symbol pose1_key = gtsam::symbol_shorthand::X(0u);
    const gtsam::Symbol pose2_key = gtsam::symbol_shorthand::X(1u);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(1, 1.0);  // dim, sigma

    // create factor
    const auto factor =
        holo::localization::vision::vslam::EssentialMatrixFactor(p1, p2, pose1_key, pose2_key, model, T_bc);

    // compute error
    gtsam::Vector3 errorActual = factor.evaluateError(wTb1, wTb2);

    // Expected error
    gtsam::Vector3 errorExpected(3);
    errorExpected << 0, 0, 0;
    ASSERT_NEAR(errorExpected[0], errorActual[0], 1e-6);

    // set initial values
    gtsam::Values values;
    values.insert(pose1_key, wTb1);
    values.insert(pose2_key, wTb2);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("EssentialMatrixFactorJacobian", factor, values, 1e-7, 1e-7));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(EssentialMatrixFactor2, ErrorAndJacobian)
{
    // generate pose ground truth
    const gtsam::Rot3            R = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3          t = gtsam::Point3(0.4, 0.5, 1.0);
    const gtsam::Pose3           wTb2(R, t);
    const gtsam::Pose3           wTb1 = gtsam::Pose3::identity();
    const gtsam::EssentialMatrix E    = gtsam::EssentialMatrix::FromPose3(wTb1.inverse() * wTb2);

    // use identity extrinsic parameter
    const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

    gtsam::SharedNoiseModel model = gtsam::noiseModel::Isotropic::Sigma(5, 0.25);

    // define pose key
    const gtsam::Symbol pose1_key = gtsam::symbol_shorthand::X(0u);
    const gtsam::Symbol pose2_key = gtsam::symbol_shorthand::X(1u);

    // create factor
    const auto factor = holo::localization::vision::vslam::EssentialMatrixFactor2(E, pose1_key, pose2_key, model, T_bc);

    gtsam::Vector3 errorActual = factor.evaluateError(wTb1, wTb2);
    // compute error

    // Expected error
    gtsam::Vector3 errorExpected(5);
    errorExpected << 0, 0, 0, 0, 0;
    ASSERT_NEAR(errorExpected[0], errorActual[0], 1e-6);
    ASSERT_NEAR(errorExpected[1], errorActual[1], 1e-6);
    ASSERT_NEAR(errorExpected[2], errorActual[2], 1e-6);
    ASSERT_NEAR(errorExpected[3], errorActual[3], 1e-6);
    ASSERT_NEAR(errorExpected[4], errorActual[4], 1e-6);

    // set initial values
    gtsam::Values values;
    values.insert(pose1_key, wTb1);
    values.insert(pose2_key, wTb2);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("EssentialMatrixFactor2Jacobian", factor, values, 1e-7, 1e-7));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}