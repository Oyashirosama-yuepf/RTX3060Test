/*!
 * \brief Unit test for parking slot vertex factor in vslam
 * \author Changsong. Yu, yuchangsong@holomatic.com
 * \date March-10-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_parallel_factor.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlotParallelFactor, Jacobian)
{
    // ground truth
    const gtsam::Point3 parking_slot_vertex_1(0.0, 0.0, 0.0);
    const gtsam::Point3 parking_slot_vertex_2(5.0, 0.0, 0.0);
    const gtsam::Point3 parking_slot_vertex_3(5.0, 5.0, 0.0);
    const gtsam::Point3 parking_slot_vertex_4(0.0, 5.0, 0.0);

    // define key
    const gtsam::Symbol l1 = L(1);
    const gtsam::Symbol l2 = L(2);
    const gtsam::Symbol l3 = L(3);
    const gtsam::Symbol l4 = L(4);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(3, 1);

    // create parkingspot factor
    const auto factor = semantic::ParkingSlotParallelFactor(l1, l2, l3, l4, model);

    // add initial values
    Values values;
    values.insert(l1, parking_slot_vertex_1);
    values.insert(l2, parking_slot_vertex_2);
    values.insert(l3, parking_slot_vertex_3);
    values.insert(l4, parking_slot_vertex_4);

    /// @brief check result
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("ParkingSlotFactorJacobian", factor, values, 1e-5, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}