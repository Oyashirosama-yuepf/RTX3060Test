/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_vector_io.cpp
 * @brief unit test io utils for vector objects
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-31
 */

#include <gtest/gtest.h>
#include <holo/io/numerics/vector.h>
#include <holo/numerics/vector.h>

TEST(VectorIO, FixedSizeVectorEncodeDecodeYaml)
{
    holo::numerics::VectorT<holo::float32_t, 3>   vector1, vector2;
    holo::numerics::VectorT<holo::float32_t, -1> vector3;
    for (size_t i = 0; i < 3U; ++i)
    {
        vector1(i) = i * 2U;
    }

    YAML::Node node;
    node["test"] = vector1;
    vector2         = node["test"].as<holo::numerics::VectorT<holo::float32_t, 3>>();
    vector3         = node["test"].as<holo::numerics::VectorT<holo::float32_t, -1>>();

    ASSERT_EQ(vector1.GetSize(), vector3.GetSize());
    for (size_t i = 0; i < 3U; ++i)
    {
        EXPECT_EQ(vector1(i), vector2(i));
        EXPECT_EQ(vector1(i), vector3(i));
    }
}

TEST(VectorIO, FixedSizeVectorDecodeYaml)
{
    YAML::Node node = YAML::Load("size: 3\nvalue: [1, 2, 3]\n");
    holo::numerics::VectorT<holo::float32_t, 3> vector1;
    vector1 = node.as<holo::numerics::VectorT<holo::float32_t, 3>>();
    for (size_t i = 0U; i < 3U; ++i)
    {
        EXPECT_EQ(i + 1, vector1(i));
    }
}

TEST(VectorIO, DynamicSizeVectorDecodeYaml)
{
    YAML::Node node = YAML::Load("size: 3 \nvalue: [1, 2, 3]\n");
    holo::numerics::VectorT<holo::float32_t, -1> vector1;
    vector1 = node.as<holo::numerics::VectorT<holo::float32_t, -1>>();
    EXPECT_EQ(3U, vector1.GetSize());
    for (size_t i = 0U; i < 3U; ++i)
    {
        EXPECT_EQ(i + 1, vector1(i));
    }
}

TEST(VectorIO, VectorDecodeYamlBadFormat)
{
    YAML::Node node = YAML::Load("SIZE: 3\nvalue: [1, 2, 3]\n");
    holo::numerics::VectorT<holo::float32_t, 3> vector1;
    EXPECT_THROW((node.as<holo::numerics::VectorT<holo::float32_t, 3>>()), std::exception);
}

TEST(VectorIO, FixedSizeVectorEncodeDecodeYamlException_1)
{
    holo::numerics::VectorT<holo::float32_t, 3>  vector1;
    for (size_t i = 0; i < 3U; ++i)
    {
        vector1(i) = i * 2U;
    }

    YAML::Node node;
    node = vector1;
    node["size"] = 2;

    try
    {
        vector1 = node.as<holo::numerics::VectorT<holo::float32_t, 3>>();
    }
    catch(...)
    {
    }
}

TEST(VectorIO, FixedSizeVectorEncodeDecodeYamlException_2)
{
    YAML::Node node = YAML::Load("'value': [1, 2, 3]");
    holo::numerics::VectorT<holo::float32_t, 3> vector1;
    try
    {
        vector1 = node.as<holo::numerics::VectorT<holo::float32_t, 3>>();
    }
    catch(...)
    {
    }
}

TEST(VectorIO, DynamicSizeVectorEncodeDecodeYamlException_2)
{
    YAML::Node node = YAML::Load("'value': [1, 2, 3]");
    holo::numerics::VectorT<holo::float32_t, -1> vector1;
    try
    {
        vector1 = node.as<holo::numerics::VectorT<holo::float32_t, -1>>();
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
