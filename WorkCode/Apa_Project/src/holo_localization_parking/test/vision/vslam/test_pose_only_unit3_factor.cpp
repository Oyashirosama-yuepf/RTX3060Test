/*!
 * \brief pose only unit3 factor implementation file
 * \author duyanwei@holomatic.com
 * \date Dec-11-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <random>

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <holo/localization/vision/vslam/pose_only_unit3_factor.h>

using namespace holo::localization::vision::vslam;

TEST(PoseOnlyUnit3Factor, Constructor)
{
    const gtsam::Point3 landmark(10, 10, 10);
    const gtsam::Point3 feature(0.3, -0.2, 1.0);
    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(2, 0.001);  // dim, sigma

    // define pose key
    const gtsam::Symbol key = gtsam::symbol_shorthand::X(0u);

    // use identity extrinsic parameter
    const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

    const PoseOnlyUnit3Factor pose_only_unit3_factor(landmark, feature, model, key, T_bc);

    /// @brief check result
    ASSERT_EQ(landmark, pose_only_unit3_factor.GetLandmarkMeasurement());
    ASSERT_EQ(feature, pose_only_unit3_factor.GetFeatureMeasurement());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseOnlyUnit3Factor, Jacobian)
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
    const gtsam::Symbol key = gtsam::symbol_shorthand::X(0u);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(2, 1.0);  // dim, sigma

    // create factor
    const auto factor = holo::localization::vision::vslam::PoseOnlyUnit3Factor(landmark, feature, model, key, T_bc);

    // set initial values
    gtsam::Values values;
    values.insert(key, T_wb);

    /// @brief check result
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("PoseOnlyUnit3FactorJacobian", factor, values, 1e-7, 1e-7));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(PoseOnlyUnit3Factor, Optimize)
{
    // generate pose ground truth
    const gtsam::Rot3   R_wb = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const gtsam::Point3 t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3  T_wb(R_wb, t_wb);

    // define pose key
    const gtsam::Symbol key = gtsam::symbol_shorthand::X(0u);

    // create graph
    gtsam::NonlinearFactorGraph graph;

    // create factors from synthetic data
    {
        // use identity extrinsic parameter
        const gtsam::Pose3 T_bc = gtsam::Pose3::identity();

        // create random generator
        std::default_random_engine generator;

        // create distributions
        std::uniform_real_distribution<holo::float64_t> distribution_xy(-0.2, 0.2);      // meter
        std::uniform_real_distribution<holo::float64_t> distribution_depth(1.0, 10.0);   // meter
        std::normal_distribution<holo::float64_t>       distribution_noise(0.0, 0.001);  // meter

        auto dice_xy    = std::bind(distribution_xy, generator);
        auto dice_depth = std::bind(distribution_depth, generator);
        auto dice_noise = std::bind(distribution_noise, generator);

        for (uint8_t i = 0u; i < 10u; i++)
        {
            // generate random normalized feature point
            const gtsam::Point3 feature(dice_xy(), dice_xy(), 1.0);

            // generate random depth
            const holo::float64_t depth = dice_depth();

            // generate landmark in world coordinate
            const gtsam::Point3 landmark =
                (T_wb * T_bc).transform_from(feature * depth) + gtsam::Point3(dice_noise(), dice_noise(), dice_noise());

            // noise model
            const auto model = gtsam::noiseModel::Isotropic::Sigma(2, 0.001);  // dim, sigma

            // create factor and add to graph
            graph.emplace_shared<holo::localization::vision::vslam::PoseOnlyUnit3Factor>(landmark, feature, model, key,
                                                                                         T_bc);
        }
    }

    // insert initial values
    gtsam::Values initials;
    initials.insert(key, gtsam::Pose3::identity());

    // run lm optimizer
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);

    const gtsam::Values results = optimizer.optimize();
    const gtsam::Pose3  actual  = results.at<gtsam::Pose3>(key);

    /// @brief check result
    LOG(INFO) << "ground truth pose:";
    T_wb.print();
    LOG(INFO) << "actual pose:";
    actual.print();
    ASSERT_TRUE(assert_equal(T_wb, actual, 1e-2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
