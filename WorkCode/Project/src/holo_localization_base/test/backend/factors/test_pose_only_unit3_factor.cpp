/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_pose_only_unit3_factor.cpp
 * @brief This header file defines test for pose only unit3 factor class
 * @author duyanwei@holomatic.com (Yanwei Du)
 * @author cuijiashuo@holomatic.com (Jiashuo Cui)
 * @date 2021-12-06
 */

#include <random>

#include <gtest/gtest.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <holo/localization/sam/factors/pose_only_unit3_factor.h>

using namespace holo::localization;

TEST(PoseOnlyUnit3Factor, Constructor)
{
    gtsam::Point3 const landmark(10, 10, 10);
    gtsam::Point3 const feature(0.3, -0.2, 1.0);
    ///@brief noise model
    auto const model = gtsam::noiseModel::Isotropic::Sigma(2, 0.001);  // dim, sigma

    ///@brief define pose key
    gtsam::Symbol const key = gtsam::symbol_shorthand::X(0u);

    ///@brief use identity extrinsic parameter
    gtsam::Pose3 const bTc = gtsam::Pose3::identity();

    GTPoseOnlyUnit3Factor const pose_only_unit3_factor(landmark, feature, model, key, bTc);

    ///@brief check result
    ASSERT_EQ(landmark, pose_only_unit3_factor.GetLandmarkMeasurement());
    ASSERT_EQ(feature, pose_only_unit3_factor.GetFeatureMeasurement());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseOnlyUnit3Factor, Jacobian)
{
    // generate pose ground truth
    gtsam::Rot3 const   wRb  = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    gtsam::Point3 const t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    gtsam::Pose3 const  wTb(wRb, t_wb);

    ///@brief use identity extrinsic parameter
    gtsam::Pose3 const bTc = gtsam::Pose3::identity();

    ///@brief generate feature point on noramlized coordinate
    holo::float64_t const depth = 10.0;
    gtsam::Point3 const   feature(0.3, -0.2, 1.0);

    ////@brief generate landmark in world coordinate
    gtsam::Point3 const landmark = (wTb * bTc).transform_from(feature * depth);

    ////@brief define pose key
    gtsam::Symbol const key = gtsam::symbol_shorthand::X(0u);

    ////@brief noise model
    auto const model = gtsam::noiseModel::Isotropic::Sigma(2, 1.0);  // dim, sigma

    ////@brief create factor
    auto const factor = holo::localization::GTPoseOnlyUnit3Factor(landmark, feature, model, key, bTc);

    ///@brief set initial values
    gtsam::Values values;
    values.insert(key, wTb);

    ///@brief check result
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("PoseOnlyUnit3FactorJacobian", factor, values, 1e-7, 1e-7));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseOnlyUnit3Factor, Optimize)
{
    ///@brief generate pose ground truth
    gtsam::Rot3 const   wRb  = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    gtsam::Point3 const t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    gtsam::Pose3 const  wTb(wRb, t_wb);

    ///@brief define pose key
    gtsam::Symbol const key = gtsam::symbol_shorthand::X(0u);

    ////@brief create graph
    gtsam::NonlinearFactorGraph graph;

    ////@brief create factors from synthetic data
    {
        ////@brief use identity extrinsic parameter
        gtsam::Pose3 const bTc = gtsam::Pose3::identity();

        ///@brief create random generator
        std::default_random_engine generator;

        ///@brief create distributions
        std::uniform_real_distribution<holo::float64_t> distribution_xy(-0.2, 0.2);      // meter
        std::uniform_real_distribution<holo::float64_t> distribution_depth(1.0, 10.0);   // meter
        std::normal_distribution<holo::float64_t>       distribution_noise(0.0, 0.001);  // meter

        auto dice_xy    = std::bind(distribution_xy, generator);
        auto dice_depth = std::bind(distribution_depth, generator);
        auto dice_noise = std::bind(distribution_noise, generator);

        for (uint8_t i = 0u; i < 10u; i++)
        {
            ////@brief generate random normalized feature point
            gtsam::Point3 const feature(dice_xy(), dice_xy(), 1.0);

            ///@brief generate random depth
            holo::float64_t const depth = dice_depth();

            ///@brief generate landmark in world coordinate
            gtsam::Point3 const landmark =
                (wTb * bTc).transform_from(feature * depth) + gtsam::Point3(dice_noise(), dice_noise(), dice_noise());

            ///@brief noise model
            auto const model = gtsam::noiseModel::Isotropic::Sigma(2, 0.001);  // dim, sigma

            ///@brief create factor and add to graph
            graph.emplace_shared<holo::localization::GTPoseOnlyUnit3Factor>(landmark, feature, model, key, bTc);
        }
    }

    ///@brief insert initial values
    gtsam::Values initials;
    initials.insert(key, gtsam::Pose3::identity());

    ////@brief run lm optimizer
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);

    gtsam::Values const results = optimizer.optimize();
    gtsam::Pose3 const  actual  = results.at<gtsam::Pose3>(key);

    ///@brief check result
    LOG(INFO) << "ground truth pose:";
    wTb.print();
    LOG(INFO) << "actual pose:";
    actual.print();
    ASSERT_TRUE(assert_equal(wTb, actual, 1e-2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
