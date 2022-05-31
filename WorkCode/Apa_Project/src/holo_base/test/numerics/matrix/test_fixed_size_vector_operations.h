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

#ifndef TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_VECTOR_OPERATIONS_H_
#define TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_VECTOR_OPERATIONS_H_

#include <cmath>

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

TEST(SUITENAME, DefaultConstructor)
{
    VectorType v;
    ASSERT_EQ(RowValue, v.GetRows());
    ASSERT_EQ(ColValue, v.GetCols());
    ASSERT_EQ(SizeValue, v.GetSize());
    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(0), v(idx));
    }
}

TEST(SUITENAME, ConstructFromInitializerList)
{
    std::initializer_list<Scalar> sequence_initializer = {MATRIX_INIT_SEQUENCE};
    std::initializer_list<Scalar> short_sequence_initializer = {MATRIX_SHORT_INIT_SEQUENCE};
    std::initializer_list<Scalar> long_sequence_initializer = {MATRIX_LONG_INIT_SEQUENCE};

    VectorType v(sequence_initializer);
    ASSERT_EQ(RowValue, v.GetRows());
    ASSERT_EQ(ColValue, v.GetCols());
    ASSERT_EQ(SizeValue, v.GetSize());

    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v(idx));
    }

    VectorType v2(short_sequence_initializer);
    ASSERT_EQ(RowValue, v2.GetRows());
    ASSERT_EQ(ColValue, v2.GetCols());
    ASSERT_EQ(SizeValue, v2.GetSize());

    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        if(idx < short_sequence_initializer.size())
        {
            ASSERT_EQ(static_cast<Scalar>(idx), v2(idx));
        }
        else
        {
            ASSERT_EQ(static_cast<Scalar>(0), v2(idx));
        }
    }

    VectorType v3(long_sequence_initializer);
    ASSERT_EQ(RowValue, v3.GetRows());
    ASSERT_EQ(ColValue, v3.GetCols());
    ASSERT_EQ(SizeValue, v3.GetSize());

    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v3(idx));
    }
}

TEST(SUITENAME, ConstructFromElements)
{
    VectorType v(MATRIX_INIT_SEQUENCE);
    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v(idx));
    }

#if SizeValue > 1
    VectorType v2(MATRIX_SHORT_INIT_SEQUENCE);
    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v2(idx));
    }
#endif
}

TEST(SUITENAME, ConstructFromMatrixBase)
{
    holo::numerics::MatrixT<Scalar, RowValue, 1> matrix = {MATRIX_INIT_SEQUENCE};
    VectorType v(matrix);
    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v(idx));
    }
}

TEST(SUITENAME, ConstructFromDynamicVector)
{
    DynamicVectorType dyn_vector;
    dyn_vector.Resize(RowValue);
    for(size_t idx = 0; idx < RowValue; ++idx)
    {
        dyn_vector(idx) = static_cast<Scalar>(idx);
    }

    VectorType v(dyn_vector);
    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v(idx));
    }
}

TEST(SUITENAME, CopyConstructor)
{
    VectorType v1 = CreateSequenceMatrix();
    VectorType v2(v1);

    for(size_t idx = 0; idx < SizeValue; ++idx)
    {
        ASSERT_EQ(static_cast<Scalar>(idx), v2(idx));
    }
}

TEST(SUITENAME, AsDiagonal)
{
    VectorType mat = CreateSequenceMatrix();
    SquareMatrixType mat_s = mat.AsDiagonal();
    for(size_t i = 0; i < mat_s.GetRows(); ++i)
    {
        for(size_t j = 0; j < mat_s.GetCols(); ++j)
        {
            if(i == j)
            {
                ASSERT_EQ(static_cast<Scalar>(i), mat_s(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat_s(i, j));
            }
        }
    }
}

#endif

