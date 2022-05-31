/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gnss_position_velocity_factor.cpp
 * @brief test GNSS position velocity factor class
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Aug 24, 2020
 */

#include <gtest/gtest.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/ImuBias.h>
#include <gtsam/navigation/ImuFactor.h>
#include <gtsam/navigation/PreintegratedRotation.h>
#include <gtsam/navigation/PreintegrationParams.h>
#include <gtsam/navigation/Scenario.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

#include <holo/localization/backend/factors/gnss_position_velocity_factor.h>
#include <holo/localization/backend/velocity_factor.h>
#include <holo/log/hololog.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssPositionVelocityFactorTest, TestJacobian)
{
    /// Step 1: Prepare the input variables
    gtsam::Rot3 const    wRb = gtsam::Rot3::RzRyRx(0.1, 0.2, -0.3);
    gtsam::Point3 const  wtb = gtsam::Point3(1.0, -1.0, 2.0);
    gtsam::Pose3 const   wTb(wRb, wtb);
    gtsam::Vector3 const velocity(1.0, 2.0, 0.5);

    holo::localization::Vector6Type const gnss_measurement(1.1, -1.1, 2.1, 1.1, 2.1, 0.6);
    holo::localization::Vector6Type const noise_sigma(1.0, 1.1, 1.2, 0.1, 0.2, 0.3);

    /// Construct the key
    holo::uint64_t const pose_index = 1u;
    holo::uint64_t const vel_index  = 1u;

    gtsam::Key const x1 = gtsam::symbol_shorthand::X(pose_index);
    gtsam::Key const v1 = gtsam::symbol_shorthand::V(vel_index);

    /// Step 2: Create the Gnss position velocity factor
    holo::localization::GnssPositionVelocityFactor factor(pose_index, vel_index, gnss_measurement, noise_sigma);
    gtsam::NoiseModelFactor::shared_ptr gtsam_factor(static_cast<gtsam::NoiseModelFactor*>(factor.GetFactor()));

    /// Step 3: Create the values
    gtsam::Values values;
    values.insert(x1, wTb);
    values.insert(v1, velocity);

    /// Step 4: Check the jacobian
    ASSERT_TRUE(
        gtsam::internal::testFactorJacobians("GnssPositionVelocityFactorJacobian", *gtsam_factor, values, 1e-4, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssPositionVelocityFactorTest, TestJacobian_PIM)
{
    using namespace holo::localization;

    /**
     * @brief scenario
     *
     * 1. The vehicle is moving with a constant acceleration of (ax = 1.5, ay = 0.1, az = 0.0)
     * 2. The first state is estimated at time t_k (0.0), next state is estimated at time t_(k+1) (1.0)
     * 3. GPS is measured at time t_j (0.1)
     * 4. PIM is created between time [t_k, t_j] ([0.0, 0.1]) at a frequency of 100hz, i.e. 10 Imus
     */

    /// Step 1: Prepare the input variables

    // first state
    Rot3Type const    wRbk = Rot3Type::RzRyRx(0.1, 0.2, -0.3);
    Point3Type const  wtbk(1.0, -1.0, 2.0);
    Pose3Type const   wTbk(wRbk, wtbk);
    Vector3Type const wVbk(1.0, 2.0, 0.5);

    // define exactly the same state to save conversion space
    gtsam::Rot3 const    gtsam_wRbk = gtsam::Rot3::RzRyRx(0.1, 0.2, -0.3);
    gtsam::Point3 const  gtsam_wtbk(1.0, -1.0, 2.0);
    gtsam::Pose3 const   gtsam_wTbk(gtsam_wRbk, gtsam_wtbk);
    gtsam::Vector3 const gtsam_wVbk(1.0, 2.0, 0.5);

    // define vehicle dynamics
    Vector3Type const acc(1.5, 0.1, 0.0);   // m/s^2
    Vector3Type const gyro(0.0, 0.0, 0.0);  // rad/s
    Scalar const      dt = 0.1;             // s

    // define state when sampled gps measurement
    Vector3Type const w_acc = wRbk * acc;  // no rotation happens
    Rot3Type const    wRbj  = wRbk;        // no rotation happens
    Point3Type const  wtbj  = wtbk + Point3Type(wVbk * dt + w_acc * (0.5 * dt * dt));
    Vector3Type const wVbj  = wVbk + w_acc * dt;

    // define real gnss measurement
    Vector6Type const gnss_measurement(wtbj.GetX() + 0.1, wtbj.GetY() - 0.1, wtbj.GetZ() - 0.2, wVbj(0u) + 0.3,
                                       wVbj(1u) - 0.1, wVbj(2u) + 0.2);
    Vector6Type const noise_sigma(1.0, 1.1, 1.2, 0.1, 0.2, 0.3);

    // define PIM
    ImuPreintegrationMeasurement pim;  // default parameters

    int32_t const     num = int32_t(dt * 100.0);  // hardcode imu frequency
    Vector3Type const g(0.0, 0.0, pim.GetParameters().GetGravity());
    Vector3Type const acc_m = acc + wRbk.Unrotate(g);  // consider gravity
    for (int32_t i = 0; i < num; i++)
    {
        pim.IntegrateMeasurement(acc_m, gyro, 0.01);  // hardcode imu interval
    }

    /// Construct the key
    holo::uint64_t const pose_index = 1u;
    holo::uint64_t const vel_index  = 1u;

    gtsam::Key const x1 = gtsam::symbol_shorthand::X(pose_index);
    gtsam::Key const v1 = gtsam::symbol_shorthand::V(vel_index);

    /// Step 2: Create the Gnss position velocity factor
    GnssPositionVelocityFactor          factor(pose_index, vel_index, gnss_measurement, noise_sigma, pim, wRbk);
    gtsam::NoiseModelFactor::shared_ptr gtsam_factor(static_cast<gtsam::NoiseModelFactor*>(factor.GetFactor()));

    /// Step 3: Create the values
    gtsam::Values values;
    values.insert(x1, gtsam_wTbk);
    values.insert(v1, gtsam_wVbk);

    /// Step 4: Check the jacobian
    ASSERT_TRUE(
        gtsam::internal::testFactorJacobians("GnssPositionVelocityFactorJacobian", *gtsam_factor, values, 1e-4, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssPositionVelocityFactorTest, TestOptimize)
{
    /// Step 1: Create the ground truth
    gtsam::Point3 const  ground_truth_position(1.0, 1.0, 1.0);
    gtsam::Vector3 const ground_truth_velocity(20.0, 1.0, 0.5);
    gtsam::Rot3 const    ground_truth_rotation = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.1);
    gtsam::Pose3 const   ground_truth_pose(ground_truth_rotation, ground_truth_position);

    /// Step 2: Create the GNSS measurement
    holo::localization::Vector6Type const gnss_measurement(ground_truth_position.x(), ground_truth_position.y(),
                                                           ground_truth_position.z(), ground_truth_velocity(0u),
                                                           ground_truth_velocity(1u), ground_truth_velocity(2u));
    holo::localization::Vector6Type const gnss_sigma = holo::localization::Vector6Type::Constant(1e-9);

    /// Step 3: Create the factor
    holo::uint64_t const pose_index     = 1u;
    holo::uint64_t const velocity_index = 1u;

    gtsam::Key const x1 = gtsam::symbol_shorthand::X(pose_index);
    gtsam::Key const v1 = gtsam::symbol_shorthand::V(velocity_index);

    holo::localization::GnssPositionVelocityFactor gnss_pos_vel_factor(pose_index, velocity_index, gnss_measurement,
                                                                       gnss_sigma);

    /// Step 4: Create the factor graph
    gtsam::NonlinearFactorGraph         graph;
    gtsam::NoiseModelFactor::shared_ptr gnss_factor;
    gnss_factor.reset(static_cast<gtsam::NoiseModelFactor*>(gnss_pos_vel_factor.GetFactor()));
    graph.add(gnss_factor);

    /// Step 5: Create the initial value
    gtsam::Values        values;
    gtsam::Point3 const  initial_position(1.2, 1.1, 1.4);
    gtsam::Vector3 const initial_velocity(20.5, 1.1, 0.7);
    gtsam::Rot3 const    initial_rotation;  // identity
    gtsam::Pose3 const   initial_pose(initial_rotation, initial_position);
    values.insert<gtsam::Pose3>(x1, initial_pose);
    values.insert<gtsam::Vector3>(v1, initial_velocity);

    /// Step 6: Call the optimization
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values /*default paramters*/);
    gtsam::Values                      result = optimizer.optimize();

    // check results
    gtsam::Point3 const  estimated_position = result.at<gtsam::Pose3>(x1).translation();
    gtsam::Rot3 const    estimated_rotation = result.at<gtsam::Pose3>(x1).rotation();
    gtsam::Vector3 const estimated_velocity = result.at<gtsam::Vector3>(v1);

    ASSERT_EQ(ground_truth_position, estimated_position);
    ASSERT_EQ(ground_truth_velocity, estimated_velocity);

    // make sure rotation does NOT change (because we are not optimizing it)
    ASSERT_TRUE(initial_rotation.equals(estimated_rotation));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssPositionVelocityFactorTest, TestOptimize_PIM)
{
    using namespace holo::localization;

    /**
     * @brief scenario
     *
     * 1. The vehicle is moving with a constant acceleration of (ax = 1.5, ay = 0.1, az = 0.0)
     * 2. The first state is estimated at time t_k (0.0), next state is estimated at time t_(k+1) (1.0)
     * 3. GPS is measured at time t_j (0.1)
     * 4. PIM is created between time [t_k, t_j] ([0.0, 0.1]) at a frequency of 100hz, i.e. 10 Imus
     */

    /// Step 1: Prepare the input variables

    // first state
    Rot3Type const    wRbk = Rot3Type::RzRyRx(0.1, 0.2, -0.3);
    Point3Type const  wtbk(1.0, 1.0, 1.0);
    Pose3Type const   wTbk(wRbk, wtbk);
    Vector3Type const wVbk(20.0, 1.0, 0.5);

    // define exactly the same state to save conversion space
    gtsam::Rot3 const    ground_truth_rotation = gtsam::Rot3::RzRyRx(0.1, 0.2, -0.3);
    gtsam::Point3 const  ground_truth_position(1.0, 1.0, 1.0);
    gtsam::Pose3 const   ground_truth_pose(ground_truth_rotation, ground_truth_position);
    gtsam::Vector3 const ground_truth_velocity(20.0, 1.0, 0.5);

    // define vehicle dynamics
    Vector3Type const acc(0.5, 0.1, 0.0);   // m/s^2
    Vector3Type const gyro(0.0, 0.0, 0.0);  // rad/s
    Scalar const      dt = 0.1;             // s

    // define state when sampled gps measurement at time t_j
    Vector3Type const w_acc = wRbk * acc;  // no rotation happens
    Rot3Type const    wRbj  = wRbk;        // no rotation happens
    Point3Type const  wtbj  = wtbk + Point3Type(wVbk * dt + w_acc * (0.5 * dt * dt));
    Vector3Type const wVbj  = wVbk + w_acc * dt;

    // define real gnss measurement
    Vector6Type const gnss_measurement(wtbj.GetX(), wtbj.GetY(), wtbj.GetZ(), wVbj(0u), wVbj(1u), wVbj(2u));
    Vector6Type const noise_sigma(1.0, 1.1, 1.2, 0.1, 0.2, 0.3);

    // define PIM
    ImuPreintegrationMeasurement pim;  // default parameters

    int32_t const     num = int32_t(dt * 100.0);  // hardcode imu frequency
    Vector3Type const g(0.0, 0.0, pim.GetParameters().GetGravity());
    Vector3Type const acc_m = acc + wRbk.Unrotate(g);  // consider gravity
    for (int32_t i = 0; i < num; i++)
    {
        pim.IntegrateMeasurement(acc_m, gyro, 0.01);  // hardcode imu interval
    }

    /// Construct the key
    holo::uint64_t const pose_index = 1u;
    holo::uint64_t const vel_index  = 1u;

    gtsam::Key const x1 = gtsam::symbol_shorthand::X(pose_index);
    gtsam::Key const v1 = gtsam::symbol_shorthand::V(vel_index);

    /// Step 2: Create the Gnss position velocity factor
    GnssPositionVelocityFactor          factor(pose_index, vel_index, gnss_measurement, noise_sigma, pim, wRbk);
    gtsam::NoiseModelFactor::shared_ptr gtsam_factor(static_cast<gtsam::NoiseModelFactor*>(factor.GetFactor()));

    /// Step 3: Create the factor graph
    gtsam::NonlinearFactorGraph graph;
    graph.add(gtsam_factor);

    /// Step 4: Create the initial value
    gtsam::Values        values;
    gtsam::Point3 const  initial_position(1.2, 1.1, 1.4);
    gtsam::Vector3 const initial_velocity(20.5, 1.1, 0.7);
    gtsam::Rot3 const    initial_rotation;  // identity
    gtsam::Pose3 const   initial_pose(initial_rotation, initial_position);
    values.insert<gtsam::Pose3>(x1, initial_pose);
    values.insert<gtsam::Vector3>(v1, initial_velocity);

    /// Step 5: Call the optimization
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values /*default paramters*/);
    gtsam::Values                      result = optimizer.optimize();

    // check results
    gtsam::Point3 const  estimated_position = result.at<gtsam::Pose3>(x1).translation();
    gtsam::Rot3 const    estimated_rotation = result.at<gtsam::Pose3>(x1).rotation();
    gtsam::Vector3 const estimated_velocity = result.at<gtsam::Vector3>(v1);

    ASSERT_TRUE(estimated_position.isApprox(ground_truth_position, 1e-6));
    ASSERT_TRUE(estimated_velocity.isApprox(ground_truth_velocity, 1e-6));

    // make sure rotation does NOT change (because we are not optimizing it)
    ASSERT_TRUE(initial_rotation.equals(estimated_rotation));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssPositionVelocityFactorTest, InvalidIndexCheck)
{
    /// Prepare the input variables
    gtsam::Rot3 const    wRb = gtsam::Rot3::RzRyRx(0.1, 0.2, -0.3);
    gtsam::Point3 const  wtb = gtsam::Point3(1.0, -1.0, 2.0);
    gtsam::Pose3 const   wTb(wRb, wtb);
    gtsam::Vector3 const velocity(1.0, 2.0, 0.5);

    holo::localization::Vector6Type const gnss_measurement(1.1, -1.1, 2.1, 1.1, 2.1, 0.6);
    holo::localization::Vector6Type const noise_sigma(1.0, 1.1, 1.2, 0.1, 0.2, 0.3);

    holo::uint64_t const pose_index = 1u;
    holo::uint64_t const vel_index  = 2u;

    // check result
    ASSERT_THROW(
        holo::localization::GnssPositionVelocityFactor factor(pose_index, vel_index, gnss_measurement, noise_sigma),
        std::runtime_error);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
