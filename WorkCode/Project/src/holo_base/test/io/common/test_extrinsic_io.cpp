/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_extrinsic_io.cpp
 * @brief unit test io utils for extrinsic objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-02-01
 */

#include <gtest/gtest.h>
#include <holo/common/extrinsic.h>
#include <holo/io/common/extrinsic.h>

using Coordinate = holo::common::Coordinate;
using Extrinsicf = holo::common::Extrinsicf;

TEST(extrinsicIO, ExtrinsicSaveYaml)
{
    const Coordinate    expected_parent_coord = Coordinate(Coordinate::IMU_MAIN); 
    const Coordinate    expected_child_coord  = Coordinate(Coordinate::IMU_VEHICLE); 

    const Extrinsicf::Pose3Type expected_pose(holo::geometry::Rot3f::Rz(holo::geometry::Radian(36.0f)),
                                                holo::geometry::Point3f(1.0f, 2.0f, 3.0f));

    Extrinsicf extrinsic(expected_parent_coord, expected_child_coord, expected_pose);
    Extrinsicf extrinsic_expect;

    YAML::Node node;
    node["test"] = extrinsic;
    extrinsic_expect   = node["test"].as<Extrinsicf>();

    ASSERT_EQ(extrinsic.GetParentCoordinate(), extrinsic_expect.GetParentCoordinate());
    ASSERT_EQ(extrinsic.GetChildCoordinate(), extrinsic_expect.GetChildCoordinate());
    ASSERT_EQ(extrinsic.GetPose(), extrinsic_expect.GetPose());
}

TEST(coordinateIO, DecodeExtrinsicException)
{
    Extrinsicf extrinsic_expect;
    YAML::Node node = YAML::Load("{'x':3,'y':100}");

    try
    {
        extrinsic_expect = node.as<Extrinsicf>();
    }
    catch(...)
    {
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
