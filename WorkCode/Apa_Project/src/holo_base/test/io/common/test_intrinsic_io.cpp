/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_intrinsic_io.cpp
 * @brief unit test io utils for intrinsic objects
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-31
 */

#include <gtest/gtest.h>
#include <holo/common/intrinsic.h>
#include <holo/io/common/intrinsic.h>

using Model = typename holo::common::details::CameraIntrinsicBaseT<holo::float32_t>::Model;

TEST(IntrinsicIO, PinholeIntrinsicEncodeDecodeYaml)
{
    holo::common::PinholeIntrinsicf intrinsic1, intrinsic2;
    intrinsic1.SetSensorId(holo::common::SensorId(1));
    intrinsic1.SetDimension(100, 200);
    intrinsic1.SetFocalLength(1, 1);
    intrinsic1.SetPrinciplePoint(2, 2);
    intrinsic1.SetSkew(3);
    intrinsic1.SetDistortionParameter(1, 2, 3, 4);
    YAML::Node node;
    node["test"] = intrinsic1;
    intrinsic2   = node["test"].as<holo::common::PinholeIntrinsicf>();
    std::cout << node["test"] << std::endl;
    ASSERT_EQ(intrinsic2.GetModel(), intrinsic1.GetModel());
    ASSERT_EQ(intrinsic2.GetSensorId(), intrinsic1.GetSensorId());
    ASSERT_EQ(intrinsic2.GetWidth(), intrinsic1.GetWidth());
    ASSERT_EQ(intrinsic2.GetHeight(), intrinsic1.GetHeight());
    ASSERT_EQ(intrinsic2.GetK(), intrinsic1.GetK());
    ASSERT_EQ(intrinsic2.GetD(), intrinsic1.GetD());
}

TEST(IntrinsicIO, PinholeIntrinsicEncodeDecodeYaml_2)
{
    holo::common::PinholeIntrinsicf intrinsic1, intrinsic2;
    intrinsic1.SetSensorId(holo::common::SensorId(1));
    intrinsic1.SetDimension(100, 200);
    intrinsic1.SetFocalLength(1, 1);
    intrinsic1.SetPrinciplePoint(2, 2);
    intrinsic1.SetSkew(3);
    intrinsic1.SetDistortionParameter(1, 2, 3, 4);
    YAML::Node node;
    node["test"]          = intrinsic1;
    node["test"]["model"] = static_cast<uint32_t>(Model::FISHEYE);

    try
    {
        intrinsic2 = node["test"].as<holo::common::PinholeIntrinsicf>();
    }
    catch (...)
    {
    }
}

TEST(IntrinsicIO, PinholeIntrinsicDecodeException)
{
    holo::common::PinholeIntrinsicf intrinsic;
    YAML::Node                      node = YAML::Load("{'height':32,'width':100}");
    try
    {
        intrinsic = node.as<holo::common::PinholeIntrinsicf>();
    }
    catch (...)
    {
    }
}

TEST(IntrinsicIO, FishEyeIntrinsicEncodeDecodeYaml)
{
    holo::common::FisheyeIntrinsicf intrinsic1, intrinsic2;
    intrinsic1.SetSensorId(holo::common::SensorId(1));
    intrinsic1.SetDimension(100, 200);
    intrinsic1.SetFocalLength(1, 1);
    intrinsic1.SetPrinciplePoint(2, 2);
    intrinsic1.SetSkew(3);
    intrinsic1.SetDistortionParameter(1, 2, 3, 4);

    YAML::Node node;
    node["test"] = intrinsic1;
    intrinsic2   = node["test"].as<holo::common::FisheyeIntrinsicf>();
    std::cout << node["test"] << std::endl;

    ASSERT_EQ(intrinsic2.GetModel(), intrinsic1.GetModel());
    ASSERT_EQ(intrinsic2.GetSensorId(), intrinsic1.GetSensorId());
    ASSERT_EQ(intrinsic2.GetWidth(), intrinsic1.GetWidth());
    ASSERT_EQ(intrinsic2.GetHeight(), intrinsic1.GetHeight());
    ASSERT_EQ(intrinsic2.GetK(), intrinsic1.GetK());
    ASSERT_EQ(intrinsic2.GetD(), intrinsic1.GetD());
}

TEST(IntrinsicIO, FishEyeIntrinsicEncodeDecodeYaml_2)
{
    holo::common::FisheyeIntrinsicf intrinsic1, intrinsic2;
    intrinsic1.SetSensorId(holo::common::SensorId(1));
    intrinsic1.SetDimension(100, 200);
    intrinsic1.SetFocalLength(1, 1);
    intrinsic1.SetPrinciplePoint(2, 2);
    intrinsic1.SetSkew(3);
    intrinsic1.SetDistortionParameter(1, 2, 3, 4);

    YAML::Node node;
    node["test"]          = intrinsic1;
    node["test"]["model"] = static_cast<uint32_t>(Model::PINHOLE);
    try
    {
        intrinsic2 = node["test"].as<holo::common::FisheyeIntrinsicf>();
    }
    catch (...)
    {
    }
}

TEST(IntrinsicIO, FishEyeIntrinsicDecodeException)
{
    holo::common::FisheyeIntrinsicf intrinsic;
    YAML::Node                      node = YAML::Load("{'height':32,'width':100}");
    try
    {
        intrinsic = node.as<holo::common::FisheyeIntrinsicf>();
    }
    catch (...)
    {
    }
}

TEST(IntrinsicIO, OcamIntrinsicEncodeDecodeYaml)
{
    holo::common::OmnidirectionalIntrinsicf intrinsic1, intrinsic2;
    intrinsic1.SetSensorId(holo::common::SensorId(1));
    intrinsic1.SetDimension(100, 200);
    intrinsic1.SetAffineTransformation(3, 4, 5);
    intrinsic1.SetUnprojectPolynomial({6, 7, 8}, {9, 10, 11, 12});

    YAML::Node node;
    node["test"] = intrinsic1;
    intrinsic2   = node["test"].as<holo::common::OmnidirectionalIntrinsicf>();

    ASSERT_EQ(intrinsic2.GetModel(), intrinsic1.GetModel());
    ASSERT_EQ(intrinsic2.GetSensorId(), intrinsic1.GetSensorId());
    ASSERT_EQ(intrinsic2.GetWidth(), intrinsic1.GetWidth());
    ASSERT_EQ(intrinsic2.GetHeight(), intrinsic1.GetHeight());
}

TEST(IntrinsicIO, OcamIntrinsicEncodeDecodeYaml_2)
{
    holo::common::OmnidirectionalIntrinsicf intrinsic1, intrinsic2;
    intrinsic1.SetSensorId(holo::common::SensorId(1));
    intrinsic1.SetDimension(100, 200);
    intrinsic1.SetAffineTransformation(3, 4, 5);
    intrinsic1.SetUnprojectPolynomial({6, 7, 8}, {9, 10, 11, 12});

    YAML::Node node;
    node["test"]          = intrinsic1;
    node["test"]["model"] = static_cast<uint32_t>(Model::FISHEYE);
    try
    {
        intrinsic2 = node["test"].as<holo::common::OmnidirectionalIntrinsicf>();
    }
    catch (...)
    {
    }
}

TEST(IntrinsicIO, OcamIntrinsicDecodeException)
{
    holo::common::OmnidirectionalIntrinsicf intrinsic;
    YAML::Node                              node = YAML::Load("{'model':32,'width':100}");
    try
    {
        intrinsic = node.as<holo::common::OmnidirectionalIntrinsicf>();
    }
    catch (...)
    {
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
