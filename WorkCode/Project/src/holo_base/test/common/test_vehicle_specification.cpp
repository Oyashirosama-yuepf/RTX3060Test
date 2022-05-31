/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for vehicle specification class
 * @author lichao@holomatic.com
 * @date Sep 18, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/vehicle_specification.h>
#include <holo/utils/holo_root.h>

using VehicleSpecification = holo::VehicleSpecification;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorTest, NormalInput)
{
    const VehicleSpecification spec(holo::GetCurrentExecDirectory() + "/../data/vehicle_specification.yaml");

    ASSERT_TRUE("magotan" == spec.GetModel());
    ASSERT_FALSE(2.87f == spec.GetWheelBase());
    ASSERT_FLOAT_EQ(2.871f, spec.GetWheelBase());
    ASSERT_FLOAT_EQ(1.584f, spec.GetFrontTrackGauge());
    ASSERT_FLOAT_EQ(1.568f, spec.GetRearTrackGauge());
    ASSERT_FLOAT_EQ(13.6f, spec.GetSteeringRatio());
    ASSERT_FLOAT_EQ(1550.0f, spec.GetMass());
    ASSERT_FLOAT_EQ(420.0f, spec.GetMassFrontLeftTire());
    ASSERT_FLOAT_EQ(420.0f, spec.GetMassFrontRightTire());
    ASSERT_FLOAT_EQ(420.0f, spec.GetMassRearLeftTire());
    ASSERT_FLOAT_EQ(420.0f, spec.GetMassRearRightTire());
    ASSERT_FLOAT_EQ(155494.663f, spec.GetFrontWheelStiffness());
    ASSERT_FLOAT_EQ(155494.663f, spec.GetRearWheelStiffness());
    ASSERT_FLOAT_EQ(36.0f, spec.GetMaxWheelAngle());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
