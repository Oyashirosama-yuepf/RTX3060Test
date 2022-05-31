/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fixed_size_vector_operations.h
 * @brief Unit test for fixed size vector object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-15
 */

#ifndef TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_VECTOR3_OPERATIONS_H_
#define TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_VECTOR3_OPERATIONS_H_

#include <cmath>

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

TEST(SUITENAME, Cross)
{
    VectorType vec1(1, 2, 3);
    VectorType vec2(0, 0, 0);
    VectorType vec3(3, 2, 1);
    VectorType result;

    // Cross self
    result = vec1.Cross(vec1);
    ASSERT_EQ(static_cast<Scalar>(0), result(0));
    ASSERT_EQ(static_cast<Scalar>(0), result(1));
    ASSERT_EQ(static_cast<Scalar>(0), result(2));

    // Cross zero vector
    result = vec1.Cross(vec2);
    ASSERT_EQ(static_cast<Scalar>(0), result(0));
    ASSERT_EQ(static_cast<Scalar>(0), result(1));
    ASSERT_EQ(static_cast<Scalar>(0), result(2));
    ASSERT_EQ(vec1.Cross(vec2), -vec2.Cross(vec1));

    // Cross non-zero vector
    result = vec1.Cross(vec3);
    ASSERT_EQ(static_cast<Scalar>(-4), result(0));
    ASSERT_EQ(static_cast<Scalar>(8), result(1));
    ASSERT_EQ(static_cast<Scalar>(-4), result(2));
    ASSERT_EQ(vec1.Cross(vec3), -vec3.Cross(vec1));
}

TEST(SUITENAME, ToSkewSymmetric)
{
    VectorType vec1(1, 2, 3);
    SquareMatrixType mat = vec1.ToSkewSymmetric();
    ASSERT_EQ(-mat, mat.Transpose());
}

#endif

