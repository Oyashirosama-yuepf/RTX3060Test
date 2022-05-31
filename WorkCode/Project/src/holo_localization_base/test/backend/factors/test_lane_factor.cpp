/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_lane_factor.cpp
 * @brief test lane factor class
 * @author Zhang Yelin (zhangyelin@holomatic.com)
 * @date Dec 26, 2019
 */

#include <gtest/gtest.h>
#include <gtsam/base/numericalDerivative.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/PriorFactor.h>
#include <holo/localization/backend/factors/lane_factor.h>
#include <holo/localization/sam/factors/internal/lane_factor_inl.h>
#include <holo/log/hololog.h>
#include <holo/numerics/vector.h>

using namespace holo;
using namespace holo::localization;
using gtsam::symbol_shorthand::X;
using LaneCorrespondenceType = holo::localization::LaneCorrespondences::Type;

TEST(TestLaneFactor, Jacobian)
{
    holo::geometry::Pose3  gt_holo_pose(holo::geometry::Rot3::RzRyRx(0.05, 0.15, 0.1), holo::geometry::Point3(1, 0, 1));
    gtsam::Pose3           gt_gtsam_pose(gtsam::Rot3::RzRyRx(0.05, 0.15, 0.1), gtsam::Point3(1, 0, 1));
    holo::geometry::Line2d detected_line(Vector3(1, 1, 1));
    holo::geometry::Point3 p(1.0, -2.0, 0.0);
    holo::geometry::Point3 pt              = gt_holo_pose.TransformFrom(p);
    holo::geometry::Point3 map_point_world = holo::geometry::Point3(pt.GetX(), pt.GetY(), pt.GetZ());
    Scalar                 sigma           = 0.1;

    const uint64_t                  pose_key = 1;
    holo::localization::Lane2Factor lane2_factor(pose_key, map_point_world, detected_line, sigma,
                                                 LaneCorrespondenceType::PROJECT_TO_BODY, false);

    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(lane2_factor.GetFactor()));

    gtsam::Key    key(X(pose_key));
    gtsam::Values values;
    values.insert(key, gt_gtsam_pose);
    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("LaneFactorJacobian", *factor, values, 1e-5, 1e-8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * The factor graph is composed of a pose variable and two factors :
 * prior factor and lane factor. The optimization result provide the
 * poses.
 */
TEST(TestLaneFactor, Optimize)
{
    /* groundtruth */
    /// rotation of body frame in world frame
    const gtsam::Rot3 wRb = gtsam::Rot3::Rz(85 * M_PI / 180);

    /// roll pitch yaw of rotation
    const gtsam::Vector3 car_rotation = gtsam::Vector3(0, 0, 85 * M_PI / 180);

    /// translation of body frame in world frame
    const gtsam::Point3 wtb = gtsam::Point3(5, 0, 0);

    /// body pose in world frame
    const gtsam::Pose3 wTb = gtsam::Pose3(wRb, wtb);

    /// pose  index
    const holo::uint64_t pose_index = 1u;

    /// create factor graph and symbols
    gtsam::NonlinearFactorGraph graph;
    const gtsam::Key            x1 = gtsam::symbol_shorthand::X(pose_index);

    /// noise model
    gtsam::SharedNoiseModel prior_pose_model = gtsam::noiseModel::Isotropic::Sigma(6, 1e-9);

    /// create prior pose factor
    graph.emplace_shared<gtsam::PriorFactor<gtsam::Pose3>>(x1, wTb, prior_pose_model);

    /// detected_line defines in body frame
    const holo::geometry::Line2d detected_line(holo::numerics::Vector3(0, 1, -3));
    const holo::geometry::Point3 map_point_world(8, 0, 0);
    const Scalar                 sigma = 0.1;

    /// create lane factor
    holo::localization::Lane2Factor     lane2_factor(pose_index, map_point_world, detected_line, sigma,
                                                 LaneCorrespondenceType::PROJECT_TO_BODY, false);
    gtsam::NoiseModelFactor::shared_ptr factor;
    factor.reset(static_cast<gtsam::NoiseModelFactor*>(lane2_factor.GetFactor()));
    graph.add(factor);

    /// initial values
    gtsam::Values initials;
    initials.insert(x1, wTb);

    /// optimize
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);
    gtsam::Values                      results = optimizer.optimize();

    /// display results
    graph.print("Factor Graph:\n");
    results.print("Final Result:\n");

    const gtsam::Pose3 est_pose = results.at<gtsam::Pose3>(x1);
    LOG(INFO) << " est_pose.GetRotation().RPY(): " << est_pose.rotation().rpy() << "\n";
    ASSERT_TRUE(assert_equal(gtsam::Point3(est_pose.translation()), wtb, 1e-3));
    ASSERT_TRUE(assert_equal(gtsam::Point3(est_pose.rotation().rpy()), gtsam::Point3(car_rotation), 1e-2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(TestLane2Factor, DefaultConstructor)
{
    holo::localization::internal::Lane2Factor();
}

/*****************************************************************************/
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
