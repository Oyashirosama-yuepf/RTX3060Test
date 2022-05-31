/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_unit3_factor.cpp
 * @brief test Unit3Factor class
 * @author Yanwei Du(duyanwei@holomaitc.com)
 * @date "Dec-11-2019"
 */

#include <random>

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <holo/localization/vision/vslam/unit3_factor.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Unit3Factor, Basic)
{
    // use identity extrinsic parameter
    const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

    // generate feature point on noramlized coordinate
    const gtsam::Point3 feature(0.3, -0.2, 1.0);

    // define pose key
    const gtsam::Symbol pose_key     = gtsam::symbol_shorthand::X(0u);
    const gtsam::Symbol landmark_key = gtsam::symbol_shorthand::L(0u);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(2, 1.0);  // dim, sigma

    // construct factor
    const auto factor = holo::localization::vision::vslam::Unit3Factor(feature, model, pose_key, landmark_key, T_bc);

    // check Getter functions
    const auto es_feature = factor.GetFeatureMeasurement();
    ASSERT_FLOAT_EQ(es_feature.x(), feature.x());
    ASSERT_FLOAT_EQ(es_feature.y(), feature.y());
    ASSERT_FLOAT_EQ(es_feature.z(), feature.z());

    // generate pose ground truths
    const gtsam::Rot3   R_wb = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3 t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3  T_wb(R_wb, t_wb);

    // generate landmark in world coordinate
    const holo::float64_t depth    = 10.0;
    const gtsam::Point3   landmark = (T_wb * T_bc).transform_from(feature * depth);

    // evaluateError
    boost::optional<gtsam::Matrix&> H_pose;
    boost::optional<gtsam::Matrix&> H_landmark;
    const auto                      error = factor.evaluateError(T_wb, landmark, H_pose, H_landmark);

    // check result
    ASSERT_NEAR(error.x(), 0.0, 1e-15);
    ASSERT_NEAR(error.y(), 0.0, 1e-15);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Unit3Factor, Jacobian)
{
    // generate pose ground truth
    const gtsam::Rot3   R_wb = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3 t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3  T_wb(R_wb, t_wb);

    // use identity extrinsic parameter
    const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

    // generate feature point on noramlized coordinate
    const holo::float64_t depth = 10.0;
    const gtsam::Point3   feature(0.3, -0.2, 1.0);

    // generate landmark in world coordinate
    const gtsam::Point3 landmark = (T_wb * T_bc).transform_from(feature * depth);

    // define pose key
    const gtsam::Symbol pose_key     = gtsam::symbol_shorthand::X(0u);
    const gtsam::Symbol landmark_key = gtsam::symbol_shorthand::L(0u);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(2, 1.0);  // dim, sigma

    // create factor
    const auto factor = holo::localization::vision::vslam::Unit3Factor(feature, model, pose_key, landmark_key, T_bc);

    // set initial values
    gtsam::Values values;
    values.insert(pose_key, T_wb);
    values.insert(landmark_key, landmark);

    // check results
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("Unit3FactorJacobian", factor, values, 1e-7, 1e-7));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Unit3Factor, Optimize)
{
    // use identity extrinsic parameter
    const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

    // generate pose ground truth
    std::vector<std::pair<gtsam::Symbol, gtsam::Pose3>> poses;
    poses.reserve(3u);
    {
        const gtsam::Symbol pose_key_0 = gtsam::symbol_shorthand::X(0u);
        const gtsam::Rot3   R_wb_0     = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
        const gtsam::Point3 t_wb_0     = gtsam::Point3(0.1, 0.2, -0.1);
        poses.emplace_back(pose_key_0, gtsam::Pose3(R_wb_0, t_wb_0));

        const gtsam::Symbol pose_key_1 = gtsam::symbol_shorthand::X(1u);
        const gtsam::Rot3   R_wb_1     = gtsam::Rot3::RzRyRx(0.15, 0.25, 0.35);
        const gtsam::Point3 t_wb_1     = gtsam::Point3(0.1, 0.3, 0.5);
        poses.emplace_back(pose_key_1, gtsam::Pose3(R_wb_1, t_wb_1));

        const gtsam::Symbol pose_key_2 = gtsam::symbol_shorthand::X(2u);
        const gtsam::Rot3   R_wb_2     = gtsam::Rot3::RzRyRx(0.05, 0.15, 0.25);
        const gtsam::Point3 t_wb_2     = gtsam::Point3(0.1, 0.1, 1.0);
        poses.emplace_back(pose_key_2, gtsam::Pose3(R_wb_2, t_wb_2));
    }

    // create factors from synthetic data
    const uint8_t landmark_num = 5u;

    std::vector<std::pair<gtsam::Symbol, gtsam::Point3>> landmarks;
    landmarks.reserve(landmark_num);

    // create random generator
    std::default_random_engine generator;

    // create graph
    gtsam::NonlinearFactorGraph graph;
    {
        // create distributions
        std::uniform_real_distribution<holo::float64_t> distribution_xy(-0.2, 0.2);     // meter
        std::uniform_real_distribution<holo::float64_t> distribution_depth(1.0, 10.0);  // meter

        auto dice_xy    = std::bind(distribution_xy, generator);
        auto dice_depth = std::bind(distribution_depth, generator);

        for (uint8_t i = 0u; i < landmark_num; i++)
        {
            // landmark key
            const gtsam::Symbol landmark_key = gtsam::symbol_shorthand::L(i);

            // generate landmark
            {
                // generate random normalized feature point
                const gtsam::Point3 feature(dice_xy(), dice_xy(), 1.0);

                // generate random depth
                const holo::float64_t depth = dice_depth();

                // generate landmark in world coordinate
                const gtsam::Point3 landmark = (poses.at(0).second * T_bc).transform_from(feature * depth);
                landmarks.emplace_back(landmark_key, landmark);
            }

            // noise model
            const auto model = gtsam::noiseModel::Isotropic::Sigma(2, 10.0);  // dim, sigma

            // project to other cameras
            for (uint8_t j = 0u; j < poses.size(); j++)
            {
                gtsam::Point3 feature = (poses.at(j).second * T_bc).transform_to(landmarks.at(i).second);
                feature /= feature.z();

                // create factor and add to graph
                graph.emplace_shared<holo::localization::vision::vslam::Unit3Factor>(feature, model, poses.at(j).first,
                                                                                     landmark_key, T_bc);
            }
        }
    }

    // add a prior factor to graph
    {
        const auto model = gtsam::noiseModel::Isotropic::Sigma(6, 0.001);  // dim, sigma
        graph.emplace_shared<gtsam::PriorFactor<gtsam::Pose3>>(poses.at(0).first, poses.at(0).second, model);
    }

    // insert initial values
    gtsam::Values initials;
    {
        for (uint8_t i = 0u; i < poses.size(); i++)
        {
            initials.insert(poses.at(i).first, gtsam::Pose3::identity());  // identity pose
        }

        std::normal_distribution<holo::float64_t> distribution_noise(0.0, 0.001);  // meter

        auto dice_noise = std::bind(distribution_noise, generator);

        for (uint8_t i = 0u; i < landmarks.size(); i++)
        {
            const gtsam::Point3 landmark =
                landmarks.at(i).second + gtsam::Point3(dice_noise(), dice_noise(), dice_noise());
            initials.insert(landmarks.at(i).first, landmark);
        }
    }

    // run lm optimizer
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);
    const gtsam::Values                results = optimizer.optimize();

    // check results
    // pose
    for (uint8_t i = 0u; i < poses.size(); i++)
    {
        const gtsam::Pose3 actual = results.at<gtsam::Pose3>(poses.at(i).first);
        ASSERT_TRUE(assert_equal(poses.at(i).second, actual, 0.01));
    }

    // landmarks
    for (uint8_t i = 0u; i < landmarks.size(); i++)
    {
        const gtsam::Point3 actual = results.at<gtsam::Point3>(landmarks.at(i).first);
        ASSERT_TRUE(assert_equal(landmarks.at(i).second, actual, 0.05));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}