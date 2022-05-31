/*!
 * \brief Unit test for parking slot plane factor in vslam
 * \author Changsong. Yu, yuchangsong@holomatic.com
 * \date March-10-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_point_plane_factor.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlotPointPlaneFactor, Jacobian)
{
    // ground truth
    const gtsam::OrientedPlane3 plane_w(0.0, 5.0, 5.0, 0);
    const gtsam::Point3         parking_slot_vertex_w(5.0, 0.0, 0.0);

    // define key
    const gtsam::Symbol p1 = P(1);
    const gtsam::Symbol l1 = L(1);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(1, 1);

    // create parking slot factor
    const auto factor = semantic::ParkingSlotPointPlaneFactor(l1, p1, model);

    // add initial values
    Values values;
    values.insert(p1, plane_w);
    values.insert(l1, parking_slot_vertex_w);

    /// @brief check result
    ASSERT_TRUE(
        gtsam::internal::testFactorJacobians("ParkingSlotPointPlaneFactorJacobian", factor, values, 1e-5, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}