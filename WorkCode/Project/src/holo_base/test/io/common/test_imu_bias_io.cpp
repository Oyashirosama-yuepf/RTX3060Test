/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_imu_bias_bias_io.cpp
 * @brief unit test io utils for imu_bias_bias objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <yaml-cpp/yaml.h>
#include <gtest/gtest.h>
#include <holo/common/imu_bias.h>
#include <holo/io/common/imu_bias.h>

using ImuBiasf = holo::common::ImuBiasf;

TEST(imu_biasIO, EncodeAndDecodeimu_bias)
{
    ImuBiasf imu_bias, imu_bias_expected;
    imu_bias.SetTimestamp(holo::common::Timestamp(10, 20));
    imu_bias.SetCoordinate(holo::common::Coordinate(100));

    imu_bias.SetAngularVelocityBias(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBias(5.0f, 6.0f, 7.0f);
    imu_bias.SetAngularVelocityBiasCovariance(9.0f, 10.0f, 11.0f);
    imu_bias.SetLinearAccelerationBiasCovariance(13.0f, 14.0f, 15.0f);

    YAML::Node node;
    node["test"] = imu_bias;
    imu_bias_expected = node["test"].as<ImuBiasf>();

    ASSERT_EQ(imu_bias.GetTimestamp(), imu_bias_expected.GetTimestamp());
    ASSERT_EQ(imu_bias.GetCoordinate(), imu_bias_expected.GetCoordinate());
    ASSERT_EQ(imu_bias.GetAngularVelocityBias(), imu_bias_expected.GetAngularVelocityBias());
    ASSERT_EQ(imu_bias.GetLinearAccelerationBias(), imu_bias_expected.GetLinearAccelerationBias());
    ASSERT_EQ(imu_bias.GetAngularVelocityBiasCovariance(), imu_bias_expected.GetAngularVelocityBiasCovariance());
    ASSERT_EQ(imu_bias.GetLinearAccelerationBiasCovariance(), imu_bias_expected.GetLinearAccelerationBiasCovariance());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
