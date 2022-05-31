/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_wheel_speed_factor.cpp
 * @brief define test for wheel speed factor
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-29
 */

#include <gtest/gtest.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/PriorFactor.h>
#include <holo/log/hololog.h>

#include <holo/localization/backend/wheel_speed_factor.h>
#include <holo/localization/sam/factors/internal/wheel_speed_factor_inl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelSpeedFactorTest, Optimize)
{
    /* groundtruth */
    /// @brief wheel preintegrated measurement
    const holo::localization::Vector3Type preintegrated_dist(2.0, 0.0, 0.0);
    const gtsam::Point3                   pwm_m(2.0, 0.0, 0.0);
    // body pose in imu frame
    const holo::localization::Pose3Type iEb = holo::localization::Pose3Type::Identity();

    // create new pwm
    holo::localization::WheelPreintegrationMeasurement pwm = holo::localization::WheelPreintegrationMeasurement(
        holo::localization::WheelPreintegrationMeasurement::WheelPreintegrationParams(), iEb, preintegrated_dist,
        holo::localization::Matrix3Type::Zero(), (holo::localization::Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal(), 0.1);

    /// @brief rotation 1 of body frame in world frame
    const gtsam::Rot3 wRb1 = gtsam::Rot3::Ry(M_PI_2);
    /// @brief translation of body frame in world frame
    const gtsam::Point3 wtb1 = gtsam::Point3(2, 0, 0);
    /// @brief pose1 body pose in world frame
    const gtsam::Pose3 wTb1 = gtsam::Pose3(wRb1, wtb1);

    /// @brief pose2 body translation in world frame
    const gtsam::Point3 wtb2 = wRb1 * pwm_m + wtb1;

    /// @brief pose and velocity index
    const holo::uint64_t pose1_index = 1u;
    const holo::uint64_t pose2_index = 2u;

    /// @brief create factor graph and symbols
    gtsam::NonlinearFactorGraph graph;
    const gtsam::Key            x1 = gtsam::symbol_shorthand::X(pose1_index);
    const gtsam::Key            x2 = gtsam::symbol_shorthand::X(pose2_index);

    /// @brief noise model
    gtsam::SharedNoiseModel prior_pose_model = gtsam::noiseModel::Isotropic::Sigma(6, 1e-9);

    /// @brief create prior pose factor
    graph.emplace_shared<gtsam::PriorFactor<gtsam::Pose3>>(x1, wTb1, prior_pose_model);

    /// @brief create wheel speed factor
    holo::localization::WheelSpeedFactor wheel_speed_factor(pose1_index, pose2_index, iEb, pwm);
    gtsam::NoiseModelFactor::shared_ptr  factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(wheel_speed_factor.GetFactor()));
    graph.add(factor);

    /// @brief initial values
    gtsam::Values initials;
    initials.insert(x1, wTb1);
    initials.insert(x2, gtsam::Pose3::identity());

    /// @brief optimize
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);
    gtsam::Values                      results = optimizer.optimize();

    /// @brief display results
    graph.print("Factor Graph:\n");
    results.print("Final Result:\n");
    LOG(INFO) << "True wtb2: " << wtb2 << "\n";

    const gtsam::Pose3 wTb2 = results.at<gtsam::Pose3>(x2);
    ASSERT_TRUE(assert_equal(wTb2.translation(), wtb2, 1e-6));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelSpeedFactorTest, Jacobian)
{
    /* groundtruth */
    /// @brief wheel preintegrated measurement
    const holo::localization::Vector3Type preintegrated_dist(2.0, 0.0, 0.0);
    const gtsam::Point3                   pwm_m(2.0, 0.0, 0.0);
    // body pose in imu frame
    const holo::localization::Pose3Type iEb = holo::localization::Pose3Type::Identity();

    // create new pwm
    holo::localization::WheelPreintegrationMeasurement pwm = holo::localization::WheelPreintegrationMeasurement(
        holo::localization::WheelPreintegrationMeasurement::WheelPreintegrationParams(), iEb, preintegrated_dist,
        holo::localization::Matrix3Type::Zero(), (holo::localization::Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal(), 0.1);

    const gtsam::Rot3   wRb1 = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3 wtb1 = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3  wTb1(wRb1, wtb1);

    /// @brief pose2 body translation in world frame
    const gtsam::Point3 wtb2 = wRb1 * pwm_m + wtb1;
    const gtsam::Pose3  wTb2 = gtsam::Pose3(gtsam::Rot3::identity(), wtb2);

    const holo::uint64_t pose1_index = 1u;
    const holo::uint64_t pose2_index = 2u;

    // define key
    const gtsam::Key x1 = gtsam::symbol_shorthand::X(pose1_index);
    const gtsam::Key x2 = gtsam::symbol_shorthand::X(pose2_index);

    // create wheel speed factor
    holo::localization::WheelSpeedFactor wheel_speed_factor(pose1_index, pose2_index, iEb, pwm);

    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(wheel_speed_factor.GetFactor()));

    // add initial values
    gtsam::Values values;
    values.insert(x1, wTb1);
    values.insert(x2, wTb2);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("WheelSpeedFactorJacobian", *factor, values, 1e-5, 1e-8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelSpeedFactorTest, NormalFunction)
{
    gtsam::Key const                               pose1_key = gtsam::symbol_shorthand::X(1u);
    gtsam::Key const                               pose2_key = gtsam::symbol_shorthand::X(2u);
    gtsam::Pose3 const                             iEb       = gtsam::Pose3();
    gtsam::Matrix3 const                           pwm_cov   = gtsam::Matrix3::Identity();
    gtsam::Vector3 const                           pwm_dist(0.1, 0.1, 0.1);
    holo::localization::internal::WheelSpeedFactor wheel_speed_factor(pose1_key, pose2_key, iEb, pwm_cov, pwm_dist);

    /* check normal function */
    ASSERT_TRUE(wheel_speed_factor.GetEib().equals(iEb));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelSpeedFactorTest, InternalDefaultConstructor)
{
    holo::localization::WheelSpeedFactor::TestDefaultConstructorOfInternalFactor();
}

///////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
