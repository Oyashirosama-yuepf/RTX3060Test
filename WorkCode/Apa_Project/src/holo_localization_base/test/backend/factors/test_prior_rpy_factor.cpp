/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_prior_rpy_factor.cpp
 * @brief test prior rpy factor
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-02-09"
 */

#include <gtest/gtest.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/PriorFactor.h>

#include <holo/localization/backend/factors/prior_rpy_factor.h>
#include <holo/log/hololog.h>

using namespace holo;
using namespace holo::localization;
using namespace holo::geometry;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PriorRPYFactor, Optimize)
{
    Vector3Type const           sigmas(1e-3, 1e-3, 1e-3);
    uint64_t const              pose_index = 1u;
    gtsam::NonlinearFactorGraph graph;

    /** roll, pitch factor which constrains roll and pitch **/
    Vector3Type const measurement1(0.1, 0.2, 0.3);
    PriorRPYFactor    prior_rpy_factor1(sigmas, pose_index, measurement1, false, false, true);  // fix yaw
    gtsam::NoiseModelFactor::shared_ptr factor1;
    factor1.reset(static_cast<gtsam::NoiseModelFactor*>(prior_rpy_factor1.GetFactor()));
    graph.add(factor1);

    /** yaw factor which constrains yaw **/
    Vector3Type const measurement2(0.7, 0.8, 0.9);
    PriorRPYFactor    prior_rpy_factor2(sigmas, pose_index, measurement2, true, true, false);  // fix roll, pitch
    gtsam::NoiseModelFactor::shared_ptr factor2;
    factor2.reset(static_cast<gtsam::NoiseModelFactor*>(prior_rpy_factor2.GetFactor()));
    graph.add(factor2);

    gtsam::Key const   pose_key = gtsam::symbol_shorthand::X(pose_index);
    gtsam::Pose3 const pose(
        gtsam::Rot3::RzRyRx(holo::geometry::Radian(0.0), holo::geometry::Radian(0.0), holo::geometry::Radian(0.0)),
        gtsam::Point3(0.4, 0.5, 0.6));
    gtsam::Values      values;
    values.insert(pose_key, pose);

    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values, parameters);
    gtsam::Values                      results = optimizer.optimize();

    /** check results **/
    const gtsam::Pose3   est_pose = results.at<gtsam::Pose3>(pose_key);
    const gtsam::Vector3 est_rpy  = est_pose.rotation().rpy();
    ASSERT_NEAR(est_rpy(0u), measurement1(0u), holo::geometry::Radian(0.001));
    ASSERT_NEAR(est_rpy(1u), measurement1(1u), holo::geometry::Radian(0.001));
    ASSERT_NEAR(est_rpy(2u), measurement2(2u), holo::geometry::Radian(0.001));
    ASSERT_TRUE(assert_equal(est_pose.translation(), pose.translation(), 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PriorRPYFactor, Jacobian)
{
    Vector3Type const sigmas(1.0, 1.0, 1.0);
    uint64_t const    pose_index = 1u;
    Vector3Type const measurement(0.0, 0.0, 0.0);
    bool_t const      fix_roll  = false;
    bool_t const      fix_pitch = false;
    bool_t const      fix_yaw   = false;
    PriorRPYFactor    prior_rpy_factor(sigmas, pose_index, measurement, fix_roll, fix_pitch, fix_yaw);

    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(prior_rpy_factor.GetFactor()));
    gtsam::Key const   pose_key = gtsam::symbol_shorthand::X(pose_index);
    gtsam::Pose3 const pose(
        gtsam::Rot3::RzRyRx(holo::geometry::Radian(0.1), holo::geometry::Radian(0.2), holo::geometry::Radian(0.3)),
        gtsam::Point3(0.4, 0.5, 0.6));
    gtsam::Values      values;
    values.insert(pose_key, pose);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("PriorRPYFactorJacobian", *factor, values, 1e-5, 1e-8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
