/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_imu_io.cpp
 * @brief unit test io utils for imu objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <yaml-cpp/yaml.h>

#include <gtest/gtest.h>
#include <holo/common/imu.h>
#include <holo/io/common/imu.h>
#include <string>

using Imuf = holo::common::Imuf;

TEST(ImuIO, EncodeAndDecodeImu)
{
    Imuf imu, imu_expected;
    imu.SetAngularVelocity(1.0f, 2.0f, 3.0f);
    imu.SetLinearAcceleration(5.0f, 6.0f, 7.0f);
    imu.SetTimestamp(holo::common::Timestamp(10, 20));
    imu.SetCoordinate(holo::common::Coordinate(30));
    imu.SetStatus(Imuf::Status::GYROXERROR);

    YAML::Node node;
    node["test"] = imu;
    imu_expected = node["test"].as<Imuf>();

    ASSERT_EQ(imu.GetAngularVelocity(), imu_expected.GetAngularVelocity());
    ASSERT_EQ(imu.GetLinearAcceleration(), imu_expected.GetLinearAcceleration());
    ASSERT_EQ(imu.GetTimestamp(), imu_expected.GetTimestamp());
    ASSERT_EQ(imu.GetCoordinate(), imu_expected.GetCoordinate());
    ASSERT_EQ(imu.GetStatus(), imu_expected.GetStatus());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
