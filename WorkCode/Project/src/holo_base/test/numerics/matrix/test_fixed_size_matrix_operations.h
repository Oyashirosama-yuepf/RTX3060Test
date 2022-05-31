/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_fixed_size_matrix_operations.h
 * @brief Unit test for fixed size matrix object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-5
 */

#ifndef TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_MATRIX_OPERATIONS_H_
#define TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_MATRIX_OPERATIONS_H_

#include <cmath>

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

TEST(SUITENAME, DefaultConstructor)
{
    MatrixType mat;
    ASSERT_EQ(RowValue, mat.GetRows());
    ASSERT_EQ(ColValue, mat.GetCols());
    for(int i = 0; i < RowValue; ++i)
    {
        for(int j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat(i, j));
        }
    }
}

TEST(SUITENAME, ConstructFromInitializerListU)
{
    std::initializer_list<Scalar> sequence_initializer = {MATRIX_INIT_SEQUENCE};
    std::initializer_list<Scalar> short_sequence_initializer = {MATRIX_SHORT_INIT_SEQUENCE};
    std::initializer_list<Scalar> long_sequence_initializer = {MATRIX_LONG_INIT_SEQUENCE};
    MatrixType mat(sequence_initializer);
    ASSERT_EQ(RowValue, mat.GetRows());
    ASSERT_EQ(ColValue, mat.GetCols());
    ASSERT_EQ(sequence_initializer.size(), mat.GetSize());

    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            size_t idx = i * ColValue + j;
            if(idx < sequence_initializer.size())
            {
                ASSERT_EQ(static_cast<Scalar>(idx), mat(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat(i, j));
            }
        }
    }

    MatrixType mat2(short_sequence_initializer);
    ASSERT_EQ(RowValue, mat2.GetRows());
    ASSERT_EQ(ColValue, mat2.GetCols());
    ASSERT_LT(short_sequence_initializer.size(), mat2.GetSize());

    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            size_t idx = i * ColValue + j;
            if(idx < short_sequence_initializer.size())
            {
                ASSERT_EQ(static_cast<Scalar>(idx), mat2(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
            }
        }
    }

    MatrixType mat3(long_sequence_initializer);
    ASSERT_EQ(RowValue, mat3.GetRows());
    ASSERT_EQ(ColValue, mat3.GetCols());
    ASSERT_GT(long_sequence_initializer.size(), mat3.GetSize());

    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            size_t idx = i * ColValue + j;
            if(idx < long_sequence_initializer.size())
            {
                ASSERT_EQ(static_cast<Scalar>(idx), mat3(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat3(i, j));
            }
        }
    }
}

TEST(SUITENAME, ConstructFromElements)
{
    MatrixType mat(MATRIX_INIT_SEQUENCE);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }

#if SizeValue > 1
    MatrixType mat2(MATRIX_SHORT_INIT_SEQUENCE);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            if((i * ColValue + j) >= ShortSizeValue)
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat2(i, j));
            }
        ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat2(i, j));
        }
    }
#endif
}

TEST(SUITENAME, CopyConstructor)
{
    MatrixType init = CreateSequenceMatrix();
    MatrixType mat(init);
    ASSERT_EQ(RowValue, mat.GetRows());
    ASSERT_EQ(ColValue, mat.GetCols());
    for(int i = 0; i < RowValue; ++i)
    {
        for(int j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
}

TEST(SUITENAME, ConstructFromDynamicMatrix)
{
    DynamicMatrixType dyn_mat;
    dyn_mat.Resize(RowValue, ColValue);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            dyn_mat(i, j) = static_cast<Scalar>(i * ColValue + j);
        }
    }

    MatrixType mat(dyn_mat);
    ASSERT_EQ(RowValue, mat.GetRows());
    ASSERT_EQ(ColValue, mat.GetCols());
    for(int i = 0; i < RowValue; ++i)
    {
        for(int j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
}

TEST(SUITENAME, AssignOperator)
{
    MatrixType init_mat = CreateSequenceMatrix();
    MatrixType mat;
    mat = init_mat;
    ASSERT_EQ(RowValue, mat.GetRows());
    ASSERT_EQ(ColValue, mat.GetCols());
    for(int i = 0; i < RowValue; ++i)
    {
        for(int j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
}

TEST(SUITENAME, AssignOperatorDynamicMatrix)
{
    DynamicMatrixType dyn_mat;
    dyn_mat.Resize(RowValue, ColValue);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            dyn_mat(i, j) = static_cast<Scalar>(i * ColValue + j);
        }
    }

    MatrixType mat = CreateZeroMatrix();
    mat = dyn_mat;
    for(int i = 0; i < RowValue; ++i)
    {
        for(int j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
}

TEST(SUITENAME, Zero)
{
    MatrixType mat = MatrixType::Zero();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
    }
}

TEST(SUITENAME, One)
{
    MatrixType mat = MatrixType::One();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(1), mat(i));
    }
}

TEST(SUITENAME, Constant)
{
    MatrixType mat = MatrixType::Constant(static_cast<Scalar>(0));
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
    }

    mat = MatrixType::Constant(static_cast<Scalar>(1));
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(1), mat(i));
    }

    mat = MatrixType::Constant(static_cast<Scalar>(2));
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(2), mat(i));
    }
}

TEST(SUITENAME, Identity)
{
    MatrixType mat = MatrixType::Identity();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            if(i == j)
            {
                ASSERT_EQ(static_cast<Scalar>(1), mat(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat(i, j));
            }
        }
    }
}

#endif

