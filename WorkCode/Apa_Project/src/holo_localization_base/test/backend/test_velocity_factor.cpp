/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_velocity_factor.cpp
 * @brief test velocity factor class
 * @author Yetong. Zhang, zhangyetong@holomatic.com
 * @author Shuaijie Li(lishuaijie@holomaitc.com)
 * @date "2019-06-05"
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
#include <holo/localization/backend/velocity_factor.h>
#include <holo/localization/sam/factors/internal/velocity_factor_inl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * The factor graph is composed of a pose variable, a velocity variable and two
 * factors. One prior factor specifies the pose of the vehicle; one velocity
 * factor specifies the velocity measured in body frame. The optimization
 * result should provide the velocity measured in the world frame.
 */
TEST(VelocityFactorTest, Optimize)
{
    /* groundtruth */
    /// @brief velocity in body frame
    const gtsam::Vector3                  velocity_b(5.0, 0.0, 0.0);
    const holo::localization::Vector3Type velocity_measurement(5.0, 0.0, 0.0);

    /// @brief rotation of body frame in world frame
    const gtsam::Rot3 wRb = gtsam::Rot3::Ry(M_PI_2);

    /// @brief translation of body frame in world frame
    const gtsam::Point3 wtb = gtsam::Point3(2, 0, 0);

    /// @brief body pose in world frame
    const gtsam::Pose3 wTb = gtsam::Pose3(wRb, wtb);

    /// @brief velocity in world frame
    const gtsam::Vector3 velocity_w = wRb.rotate(velocity_b);

    /// @brief pose and velocity index
    const holo::uint64_t pose_index     = 1u;
    const holo::uint64_t velocity_index = 1u;

    /// @brief create factor graph and symbols
    gtsam::NonlinearFactorGraph graph;
    const gtsam::Key            x1 = gtsam::symbol_shorthand::X(pose_index);
    const gtsam::Key            v1 = gtsam::symbol_shorthand::V(velocity_index);

    /// @brief noise model
    gtsam::SharedNoiseModel         prior_pose_model = gtsam::noiseModel::Isotropic::Sigma(6, 1e-9);
    holo::localization::Vector3Type velocity_sigmas(1e-9, 1e-9, 1e-9);

    /// @brief create prior pose factor
    graph.emplace_shared<gtsam::PriorFactor<gtsam::Pose3>>(x1, wTb, prior_pose_model);

    /// @brief create velocity factor
    holo::localization::VelocityFactor  velocity_factor(pose_index, velocity_index, velocity_measurement,
                                                       velocity_sigmas);
    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(velocity_factor.GetFactor()));
    graph.add(factor);

    /// @brief initial values
    gtsam::Values initials;
    initials.insert(x1, wTb);
    initials.insert(v1, gtsam::Vector3(1.0, -1.0, -4.0));

    /// @brief optimize
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);
    gtsam::Values                      results = optimizer.optimize();

    /// @brief display results
    graph.print("Factor Graph:\n");
    results.print("Final Result:\n");
    LOG(INFO) << "True velocity: " << velocity_w << "\n";

    const gtsam::Vector3 est_v = results.at<gtsam::Vector3>(v1);
    ASSERT_TRUE(assert_equal(gtsam::Point3(est_v), gtsam::Point3(velocity_w), 1e-3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VelocityFactorTest, Jacobian)
{
    // ground truth
    const gtsam::Rot3                     wRb = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3                   wtb = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3                    wTb(wRb, wtb);
    const gtsam::Vector3                  velocity_b(5.0, 0.0, 0.0);
    const holo::localization::Vector3Type velocity_measurement(5.0, 0.0, 0.0);
    const gtsam::Vector3                  velocity_w     = wRb.rotate(velocity_b);
    const holo::uint64_t                  pose_index     = 1u;
    const holo::uint64_t                  velocity_index = 1u;

    // define key
    const gtsam::Key x1 = gtsam::symbol_shorthand::X(pose_index);
    const gtsam::Key v1 = gtsam::symbol_shorthand::V(velocity_index);

    // noise model
    holo::localization::Vector3Type velocity_sigmas(1.0, 1.0, 1.0);

    // create velocity factor
    holo::localization::VelocityFactor  velocity_factor(pose_index, velocity_index, velocity_measurement,
                                                       velocity_sigmas);
    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(velocity_factor.GetFactor()));

    // add initial values
    gtsam::Values values;
    values.insert(x1, wTb);
    values.insert(v1, velocity_w);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("VelocityFactorJacobian", *factor, values, 1e-5, 1e-8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VelocityFactorTest, THROW)
{
    // velocity measurement
    const holo::localization::Vector3Type velocity_measurement(5.0, 0.0, 0.0);

    // pose_index != velocity_index, throw exception
    const holo::uint64_t pose_index     = 1u;
    const holo::uint64_t velocity_index = 2u;

    // noise model
    holo::localization::Vector3Type velocity_sigmas(1.0, 1.0, 1.0);

    // create velocity factor
    holo::localization::VelocityFactor velocity_factor(pose_index, velocity_index, velocity_measurement,
                                                       velocity_sigmas);

    // check results
    ASSERT_THROW(velocity_factor.GetFactor(), std::exception);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VelocityFactorTest, NormalFunction)
{
    const gtsam::Key                             pose_key     = gtsam::symbol_shorthand::X(1u);
    const gtsam::Key                             velocity_key = gtsam::symbol_shorthand::V(1u);
    const gtsam::Vector3                         velocity_measurement(5.0, 0.0, 0.0);
    const gtsam::Vector3                         sigmas_value(1.0, 1.0, 1.0);
    const gtsam::SharedNoiseModel                noise_model = gtsam::noiseModel::Diagonal::Sigmas(sigmas_value);
    holo::localization::internal::VelocityFactor velocity_factor(pose_key, velocity_key, velocity_measurement,
                                                                 noise_model);

    /* check normal function */
    ASSERT_EQ(velocity_factor.GetVelocityMeasurement(), velocity_measurement);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VelocityFactorTest, InternalDefaultConstructor)
{
    holo::localization::VelocityFactor::TestDefaultConstructorOfInternalFactor();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
