/*!
 * \brief Unit test for velocity factor in vslam
 * \author Yetong. Zhang, zhangyetong@holomatic.com
 * \date June-5-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>

#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <holo/localization/vision/vslam/factor_graph.h>
#include <holo/localization/vision/vslam/velocity_factor.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VelocityFactor, Constructor)
{
    const gtsam::Symbol    x1 = X(1);
    const gtsam::Symbol    v1 = V(1);
    const gtsam::Velocity3 velocity_b(5.0, 0.0, 0.0);
    const auto             velocity_model = gtsam::noiseModel::Isotropic::Sigma(3, 1e-9);

    const VelocityFactor velocityfactor(x1, v1, velocity_b, velocity_model);

    /// @brief check result
    ASSERT_EQ(velocity_b, velocityfactor.GetVelocityMeasurement());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * The factor graph is composed of a pose variable, a velocity variable and two
 * factors. One prior factor specifies the pose of the vehicle; one velocity
 * factor specifies the velocity measured in body frame. The optimization
 * result should provide the velocity measured in the world frame.
 */
TEST(VelocityFactor, Optimize)
{
    /* ground truth */
    // velocity in body frame
    const gtsam::Velocity3 velocity_b(5.0, 0.0, 0.0);
    // rotation of body frame in world frame
    const auto R_wb = gtsam::Rot3::Ry(M_PI_2);
    // translation of body frame in world frame
    const auto t_wb = gtsam::Point3(2, 0, 0);
    // body pose in world frame
    const auto T_wb = gtsam::Pose3(R_wb, t_wb);
    // velocity in world frame
    const auto velocity_w = R_wb.rotate(velocity_b);

    // create factor graph and symbols
    FactorGraph graph;
    const auto  x1 = X(1);
    const auto  v1 = V(1);

    // noise model
    auto velocity_model = gtsam::noiseModel::Isotropic::Sigma(3, 1e-9);
    auto prior_model    = gtsam::noiseModel::Isotropic::Sigma(6, 1e-9);

    // create factors
    graph.emplace_shared<gtsam::PriorFactor<gtsam::Pose3>>(x1, T_wb, prior_model);
    graph.emplace_shared<VelocityFactor>(x1, v1, velocity_b, velocity_model);

    // initial values
    gtsam::Values initials;
    initials.insert(x1, T_wb);
    initials.insert(v1, gtsam::Velocity3(1.0, -1.0, -4.0));

    // optimize
    gtsam::LevenbergMarquardtParams parameters;
    parameters.setVerbosity("ERROR");
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initials, parameters);
    gtsam::Values                      results = optimizer.optimize();

    // display results
    graph.print("Factor Graph:\n");
    results.print("Final Result:\n");
    LOG(INFO) << "True velocity: " << velocity_w << "\n";

    const gtsam::Velocity3 est_v = results.at<gtsam::Velocity3>(v1);

    /// @brief check result
    ASSERT_TRUE(assert_equal(gtsam::Point3(est_v), gtsam::Point3(velocity_w), 1e-3));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(VelocityFactor, Jacobian)
{
    // ground truth
    const auto             R_wb = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const auto             t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3     T_wb(R_wb, t_wb);
    const gtsam::Velocity3 velocity_b(5.0, 0.0, 0.0);
    const gtsam::Velocity3 velocity_w = R_wb.rotate(velocity_b);

    // define key
    const gtsam::Symbol x1 = X(1);
    const gtsam::Symbol v1 = V(1);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(3, 1);

    // create velocity factor
    const auto factor = VelocityFactor(x1, v1, velocity_b, model);

    // add initial values
    Values values;
    values.insert(x1, T_wb);
    values.insert(v1, velocity_w);

    /// @brief check result
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("VelocityFactorJacobian", factor, values, 1e-5, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
