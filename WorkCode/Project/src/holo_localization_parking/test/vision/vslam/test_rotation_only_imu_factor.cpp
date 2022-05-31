/*!
 * \brief rotation only imu factor implementation file
 * \author lifeng@holomatic.com
 * \date Jan-02-2022
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <random>

#include <gtest/gtest.h>
#include <gtsam/base/TestableAssertions.h>
#include <gtsam/base/numericalDerivative.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/factorTesting.h>

#include <holo/localization/vision/vslam/rotation_only_imu_factor.h>

using namespace holo::localization::vision::vslam;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(RotationOnlyImuFactor, ErrorAndJacobian)
{
    // Linearization point
    gtsam::Vector3 bias(0., 0., 0.);  // Bias
    gtsam::Rot3    R1(gtsam::Rot3::RzRyRx(M_PI / 12.0, M_PI / 6.0, M_PI / 4.0));
    gtsam::Rot3    R2(gtsam::Rot3::RzRyRx(M_PI / 12.0 + M_PI / 100.0, M_PI / 6.0, M_PI / 4.0));
    gtsam::Pose3   x1(R1, gtsam::Point3(0, 0, 0));
    gtsam::Pose3   x2(R2, gtsam::Point3(0, 0, 0));
    // construct pim covariance
    const gtsam::Matrix3                                     gyro_cov = gtsam::Vector3(1e-2, 1e-2, 3e-3).asDiagonal();
    boost::shared_ptr<PreintegratedAhrsMeasurements::Params> ahrs_params =
        boost::make_shared<PreintegratedAhrsMeasurements::Params>(gyro_cov, boost::none);

    // Measurements
    gtsam::Vector3 measuredOmega;
    measuredOmega << M_PI / 100, 0, 0;
    double                        deltaT = 1.0;
    PreintegratedAhrsMeasurements pim(ahrs_params, bias);
    pim.integrateMeasurement(measuredOmega, deltaT);

    // Create factor
    RotationOnlyImuFactor factor(gtsam::symbol_shorthand::X(1), gtsam::symbol_shorthand::X(2),
                                 gtsam::symbol_shorthand::B(1), pim);

    gtsam::Vector3 errorActual = factor.evaluateError(x1, x2, bias);

    // Expected error
    gtsam::Vector3 errorExpected(3);
    errorExpected << 0, 0, 0;
    ASSERT_NEAR(errorExpected[0], errorActual[0], 1e-6);
    ASSERT_NEAR(errorExpected[1], errorActual[1], 1e-6);
    ASSERT_NEAR(errorExpected[2], errorActual[2], 1e-6);
    // set initial values
    gtsam::Values values;
    values.insert(gtsam::symbol_shorthand::X(1), gtsam::Pose3());
    values.insert(gtsam::symbol_shorthand::X(2), gtsam::Pose3());
    values.insert(gtsam::symbol_shorthand::B(1), gtsam::Vector3());

    // check jacobian
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("RotationOnlyImuFactorJacbian", factor, values, 1e-7, 1e-7));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
