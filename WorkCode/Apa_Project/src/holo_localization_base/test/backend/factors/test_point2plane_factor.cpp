/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_plane_factor.cpp
 * @brief This header file defines test for plane factor class
 * @author mengzhili(mengzhili@holomaitc.com)
 * @date 2021-03-31
 */

#include <gtest/gtest.h>
#include <gtsam/base/Vector.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/navigation/Scenario.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

#include <holo/localization/sam/factors/point2plane_factor.h>
#include <holo/log/hololog.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Point2PlaneFactorTest, TestJacobian)
{
    /// Step 1: Prepare the input variables
    gtsam::Rot3 const   wRb = gtsam::Rot3::RzRyRx(0.1, 0.2, -0.3);
    gtsam::Point3 const wtb = gtsam::Point3(1.0, -1.0, 2.0);
    gtsam::Pose3 const  wTb(wRb, wtb);

    gtsam::Point3 const  pt_w(0.5, 0.5, 0.0);
    gtsam::Vector3 const pt_w_normal(0.0, 0.0, 1.0);

    gtsam::Point3 pt_src = wTb.transform_to(pt_w);

    /// Construct the key
    uint64_t const   pose_index = 1u;
    gtsam::Key const x1         = gtsam::symbol_shorthand::X(pose_index);

    /// Step 2: Create the Plane factor
    auto                                    noise = gtsam::noiseModel::Isotropic::Sigma(1, 1e-3);
    holo::localization::GTPoint2PlaneFactor factor(x1, pt_src, pt_w, pt_w_normal, noise);

    /// Step 3: Create the values
    gtsam::Values values;
    values.insert(x1, wTb);

    /// Step 4: Check the jacobian
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("Point2PlaneFactorJacobian", factor, values, 1e-4, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Point2PlaneFactorTest, TestOptimize)
{
    using Point2PlaneFactor = holo::localization::GTPoint2PlaneFactor;

    /// Step 1: Create the ground truth
    gtsam::Point3 const gt_position(0.5, 0.25, -0.35);
    gtsam::Rot3 const   gt_rotation = gtsam::Rot3::RzRyRx(0.2, -0.1, 0.3);
    gtsam::Pose3 const  gt_pose(gt_rotation, gt_position);

    /// Step 2: Create the measurements
    std::vector<gtsam::Point3>  target_pts;
    std::vector<gtsam::Vector3> target_normals;
    std::vector<gtsam::Point3>  source_pts;

    // create three perpendicular plane points
    size_t const   resolution = 50;
    double         step       = 1.0 / static_cast<double>(resolution);
    gtsam::Vector3 normal_z   = gtsam::Vector3(0.0, 0.0, 1.0);
    gtsam::Vector3 normal_x   = gtsam::Vector3(1.0, 0.0, 0.0);
    gtsam::Vector3 normal_y   = gtsam::Vector3(0.0, 1.0, 0.0);

    // fill xy plane
    for (size_t i = 0; i < resolution; ++i)
    {
        for (size_t j = 0; j < resolution; ++j)
        {
            target_pts.emplace_back(gtsam::Point3(i * step, j * step, 0.0));
            target_normals.emplace_back(normal_z);
        }
    }

    // fill yz plane
    for (size_t i = 1; i < resolution; ++i)
    {
        for (size_t j = 1; j < resolution; ++j)
        {
            target_pts.emplace_back(gtsam::Point3(0, i * step, j * step));
            target_normals.emplace_back(normal_x);
        }
    }

    // fill xz plane
    for (size_t i = 1; i < resolution; ++i)
    {
        for (size_t j = 1; j < resolution; ++j)
        {
            target_pts.emplace_back(gtsam::Point3(i * step, 0.0, j * step));
            target_normals.emplace_back(normal_y);
        }
    }

    for (size_t i = 0; i < target_pts.size(); ++i)
    {
        source_pts.emplace_back(gt_pose.transform_to(target_pts[i]));
    }

    /// Step 3: Create the factor
    uint64_t const   pose_index = 1u;
    gtsam::Key const x1         = gtsam::symbol_shorthand::X(pose_index);

    auto plane_noise = gtsam::noiseModel::Isotropic::Sigma(1, 1e-3);

    std::vector<gtsam::NoiseModelFactor::shared_ptr> factors;

    for (size_t i = 0; i < target_pts.size(); ++i)
    {
        gtsam::NoiseModelFactor::shared_ptr factor(
            new Point2PlaneFactor(x1, source_pts[i], target_pts[i], target_normals[i], plane_noise));
        factors.emplace_back(factor);
    }

    /// Step 4: Create the factor graph
    gtsam::NonlinearFactorGraph graph;
    graph.add(factors);

    /// Step 5: Create the initial value
    gtsam::Values values;
    values.insert<gtsam::Pose3>(x1, gtsam::Pose3::identity());

    /// Step 6: Call the optimization
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, values /*default paramters*/);
    gtsam::Values                      result = optimizer.optimize();

    // check results
    gtsam::Pose3 es_x1 = result.at<gtsam::Pose3>(x1);
    ASSERT_TRUE(es_x1.equals(gt_pose, 1e-3));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
