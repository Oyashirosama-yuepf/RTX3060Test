/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file wheel_preintegration.h
 * @brief define wheel preintegration
 * @author Binbin.Wang wangbinbin@holomatic.com
 * @date 2020-08-29
 */

#include <gtest/gtest.h>

#include <holo/localization/common/wheel_preintegration.h>

using namespace holo::localization;
using WheelPreintegrationMeasurement = holo::localization::WheelPreintegrationMeasurement;
using WheelPreintegrationParams      = WheelPreintegrationMeasurement::WheelPreintegrationParams;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelPreintegrationMeasurementParamsTest, NormalCase)
{
    WheelPreintegrationParams pwm_params;
    Matrix3Type               velocity_covariance    = (Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal();
    Matrix3Type               integration_covariance = (Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal();
    ASSERT_TRUE(velocity_covariance == pwm_params.velocity_covariance);
    ASSERT_TRUE(integration_covariance == pwm_params.integration_covariance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelPreintegrationMeasurementTest, NormalCase)
{
    WheelPreintegrationMeasurement pwm;
    Matrix3Type                    velocity_covariance    = (Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal();
    Matrix3Type                    integration_covariance = (Vector3Type(1e-4, 1e-4, 1e-4)).AsDiagonal();

    ASSERT_TRUE(velocity_covariance == pwm.GetParams().velocity_covariance);
    ASSERT_TRUE(integration_covariance == pwm.GetParams().integration_covariance);
    ASSERT_TRUE(Pose3Type::Identity() == pwm.GetEibHat());
    ASSERT_TRUE(Vector3Type(0.0, 0.0, 0.0) == pwm.GetPreintegrated());
    ASSERT_TRUE(Matrix3Type::Zero() == pwm.GetPreintegratedHRib());
    ASSERT_TRUE(Matrix3Type::Zero() == pwm.GetPreintegratedMeasurementCovariance());
    ASSERT_TRUE(0.0 == pwm.GetDeltaTij());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelPreintegrationMeasurement, SetGetTimestamp)
{
    WheelPreintegrationMeasurement pwm;

    /** check GetTimestamp **/
    ASSERT_EQ(holo::Timestamp(0u, 0u), pwm.GetStartTime());
    ASSERT_EQ(holo::Timestamp(0u, 0u), pwm.GetEndTime());

    holo::Timestamp start_time(10.0);
    holo::Timestamp end_time(10.1);
    pwm.SetStartTime(start_time);
    pwm.SetEndTime(end_time);

    /** check SetTimestamp **/
    ASSERT_EQ(start_time, pwm.GetStartTime());
    ASSERT_EQ(end_time, pwm.GetEndTime());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(WheelPreintegrationMeasurementTest, IntegrateMeasurement)
{
    WheelPreintegrationMeasurement pwm;

    const Vector3Type velocity  = Vector3Type(10, 0, 0);
    const Rot3Type    delta_Ril = Rot3Type::Identity();
    const Scalar      dt        = 0.1;

    pwm.IntegrateMeasurement(velocity, delta_Ril, dt);

    const Scalar delta_Tij = dt;

    // update preintegrate
    Vector3Type preintegrated = delta_Ril.ToMatrix() * pwm.GetEibHat().GetRotation().ToMatrix() * velocity * dt;

    const Vector3Type vel = pwm.GetEibHat().GetRotation().ToMatrix() * velocity;
    const Matrix3Type A   = -((delta_Ril.ToMatrix()) * vel.ToSkewSymmetric() * dt);
    const Matrix3Type B   = -(delta_Ril.ToMatrix() * pwm.GetEibHat().GetRotation().ToMatrix() * dt);

    // update jacobian preintegrated_H_Rib
    Matrix3Type preintegrated_H_Rib =
        -(delta_Ril.ToMatrix() * pwm.GetEibHat().GetRotation().ToMatrix() * velocity.ToSkewSymmetric() * dt);

    const Matrix3Type& v_cov   = pwm.GetParams().velocity_covariance;
    const Matrix3Type& int_cov = pwm.GetParams().integration_covariance;

    // update covariance
    // (1/dt) allows to pass from continuous time noise to discrete time noise
    Matrix3Type preintegratedmeascov = A * (int_cov / dt) * A.Transpose();
    //@todo get imu gyroscope preintegrate covariance from pim
    preintegratedmeascov += B * (v_cov / dt) * B.Transpose();

    ASSERT_TRUE(Pose3Type::Identity() == pwm.GetEibHat());
    ASSERT_TRUE(preintegrated == pwm.GetPreintegrated());
    ASSERT_TRUE(preintegrated_H_Rib == pwm.GetPreintegratedHRib());
    ASSERT_TRUE(preintegratedmeascov == pwm.GetPreintegratedMeasurementCovariance());
    ASSERT_TRUE(delta_Tij == pwm.GetDeltaTij());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
