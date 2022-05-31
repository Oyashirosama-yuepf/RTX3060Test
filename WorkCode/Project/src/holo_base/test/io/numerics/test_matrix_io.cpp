/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_matrix_io.cpp
 * @brief unit test io utils for matrix objects
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-31
 */

#include <gtest/gtest.h>
#include <holo/io/numerics/matrix.h>
#include <holo/numerics/matrix.h>

TEST(MatrixIO, FixedSizeMatrixEncodeDecodeYaml)
{
    holo::numerics::MatrixT<holo::float32_t, 3, 3> matrix, matrix_output;
    for (size_t i = 0; i < 9U; ++i)
    {
        matrix(i) = i * 2U;
    }

    YAML::Node node;
    node["test"] = matrix;

    matrix_output = node["test"].as<holo::numerics::MatrixT<holo::float32_t, 3, 3>>();

    ASSERT_EQ(matrix.GetRows(), matrix_output.GetRows());
    ASSERT_EQ(matrix.GetCols(), matrix_output.GetCols());
    for (size_t i = 0; i < 9U; ++i)
    {
        EXPECT_EQ(matrix(i), matrix_output(i));
    }
}

TEST(MatrixIO, FixedSizeMatrixEncodeDecodeYaml_2)
{
    holo::numerics::MatrixT<holo::float32_t, 3, 3>   matrix1, matrix2;
    holo::numerics::MatrixT<holo::float32_t, -1, -1> matrix3;
    for (size_t i = 0; i < 9U; ++i)
    {
        matrix1(i) = i * 2U;
    }

    YAML::Node node;
    node["test"] = matrix1;

    matrix2 = node["test"].as<holo::numerics::MatrixT<holo::float32_t, 3, 3>>();
    matrix3 = node["test"].as<holo::numerics::MatrixT<holo::float32_t, -1, -1>>();

    ASSERT_EQ(matrix1.GetRows(), matrix3.GetRows());
    ASSERT_EQ(matrix1.GetCols(), matrix3.GetCols());
    for (size_t i = 0; i < 9U; ++i)
    {
        EXPECT_EQ(matrix1(i), matrix2(i));
        EXPECT_EQ(matrix1(i), matrix3(i));
    }
}

TEST(MatrixIO, FixedSizeMatrixEncodeDecodeYaml_3)
{
    holo::numerics::MatrixT<holo::float32_t, 3, 3> matrix1;

    YAML::Node node;
    node["test"] = matrix1;
    node["test"]["row"] = 0;
    node["test"]["col"] = 0;

    try
    {
        matrix1 = node["test"].as<holo::numerics::MatrixT<holo::float32_t, 3, 3>>();
    }
    catch(...)
    {
    }
}

TEST(MatrixIO, FixedSizeMatrixEncodeDecodeYaml_4)
{
    holo::numerics::MatrixT<holo::float32_t, 3, 3> matrix1;
    YAML::Node node = YAML::Load("'row': 3");
    try
    {
        matrix1 = node.as<holo::numerics::MatrixT<holo::float32_t, 3, 3>>();
    }
    catch(...)
    {
    }
}

TEST(MatrixIO, DynamicSizeMatrixEncodeDecodeYaml)
{
    holo::numerics::MatrixT<holo::float32_t, -1, -1> matrix1;
    YAML::Node node = YAML::Load("'row': 3");
    try
    {
        matrix1 = node.as<holo::numerics::MatrixT<holo::float32_t, -1, -1>>();
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
