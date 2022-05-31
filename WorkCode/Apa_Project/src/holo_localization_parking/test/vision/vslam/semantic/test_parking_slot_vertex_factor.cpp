/*!
 * \brief Unit test for parking slot vertex factor in vslam
 * \author Changsong. Yu, yuchangsong@holomatic.com
 * \date March-09-2020
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/factorTesting.h>
#include <holo/localization/vision/vslam/semantic/parking_slot_vertex_factor.h>

using namespace holo::localization::vision::vslam;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlotVertexFactor, Constructor)
{
    const gtsam::Symbol x1 = X(1);
    const gtsam::Symbol l1 = L(1);
    const gtsam::Point3 parking_slot_vertex_b(5.0, 0.0, 0.0);
    const auto          parking_slot_model = gtsam::noiseModel::Isotropic::Sigma(3, 1e-9);

    const semantic::ParkingSlotVertexFactor parking_slot_factor(x1, l1, parking_slot_vertex_b, parking_slot_model);

    /// @brief check result
    ASSERT_EQ(parking_slot_vertex_b, parking_slot_factor.GetParkingSlotVertexMeasurement());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ParkingSlotVertexFactor, Jacobian)
{
    // ground truth
    const auto          R_wb = gtsam::Rot3::RzRyRx(0.1, 0.2, 0.3);
    const auto          t_wb = gtsam::Point3(0.4, 0.5, 0.6);
    const gtsam::Pose3  T_wb(R_wb, t_wb);
    const gtsam::Point3 parking_slot_vertex_b(5.0, 0.0, 0.0);
    const gtsam::Point3 parking_slot_vertex_w = T_wb.transform_from(parking_slot_vertex_b);

    // define key
    const gtsam::Symbol x1 = X(1);
    const gtsam::Symbol l1 = L(1);

    // noise model
    const auto model = gtsam::noiseModel::Isotropic::Sigma(3, 1);

    // create parking_slot factor
    const auto factor = semantic::ParkingSlotVertexFactor(x1, l1, parking_slot_vertex_b, model);

    // add initial values
    Values values;
    values.insert(x1, T_wb);
    values.insert(l1, parking_slot_vertex_w);

    /// @brief check result
    ASSERT_TRUE(gtsam::internal::testFactorJacobians("ParkingSlotFactorJacobian", factor, values, 1e-5, 1e-5));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}