/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_matrix_base_operations.h
 * @brief Unit test for matrix base object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-5
 */

#ifndef TEST_NUMERICS_MATRIX_TEST_MATRIX_BASE_OPERATIONS_H_
#define TEST_NUMERICS_MATRIX_TEST_MATRIX_BASE_OPERATIONS_H_

#include <cmath>

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

TEST(SUITENAME, GetData)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat.GetData()[i + j * RowValue]);
        }
    }

    MatrixType const const_mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), const_mat.GetData()[i + j * RowValue]);
        }
    }
}

TEST(SUITENAME, Cast)
{
    MatrixType mat = CreateSequenceMatrix();
    CastMatrixType cast_mat = mat.template Cast<CastScalar>();

    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<CastScalar>(i * ColValue + j), cast_mat.GetData()[i + j * RowValue]);
        }
    }
}

TEST(SUITENAME, GetRows)
{
    MatrixType mat = CreateSequenceMatrix();
    ASSERT_EQ(RowValue, mat.GetRows());
}

TEST(SUITENAME, GetCols)
{
    MatrixType mat = CreateSequenceMatrix();
    ASSERT_EQ(ColValue, mat.GetCols());
}

TEST(SUITENAME, GetSize)
{
    MatrixType mat = CreateSequenceMatrix();
    ASSERT_EQ(RowValue * ColValue, mat.GetSize());
}

TEST(SUITENAME, GetRow)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        RowMatrixType row = mat.GetRow(i);
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(i * ColValue + j, row(j));
        }
    }
}

TEST(SUITENAME, GetCol)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t j = 0; j < ColValue; ++j)
    {
        ColMatrixType col = mat.GetCol(j);
        for(size_t i = 0; i < RowValue; ++i)
        {
            ASSERT_EQ(i * ColValue + j, col(i));
        }
    }
}

TEST(SUITENAME, GetBlock)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            //Get each blocks with matrix(i, j) as top-left corner
            for(size_t rows = 1; rows <= RowValue - i; ++rows)
            {
                for(size_t cols = 1; cols <= ColValue - j; ++cols)
                {
                    DynamicMatrixType submat = mat.GetBlock(i, j, rows, cols);

                    ASSERT_EQ(rows, submat.GetRows());
                    ASSERT_EQ(cols, submat.GetCols());
                    for(size_t row = 0; row < submat.GetRows(); ++row)
                    {
                        for(size_t col = 0; col < submat.GetCols(); ++col)
                        {
                            ASSERT_EQ(mat(i + row, j + col), submat(row, col));
                        }
                    }
                }
            }
        }
    }
}

TEST(SUITENAME, SetBlock)
{
    MatrixType mat = CreateZeroMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            //get each blocks with matrix(i, j) as top-left corner
            for(size_t rows = 1; rows <= RowValue - i; ++rows)
            {
                for(size_t cols = 1; cols <= ColValue - j; ++cols)
                {
                    // initialize mat values
                    for(size_t idx = 0; idx < mat.GetSize(); ++idx)
                    {
                        mat(idx) = static_cast<Scalar>(idx);
                    }

                    // initialize dynamic_block values
                    DynamicMatrixType dyn_block;
                    dyn_block.Resize(rows, cols);
                    for(size_t row = 0; row < dyn_block.GetRows(); ++row)
                    {
                        for(size_t col = 0; col < dyn_block.GetCols(); ++col)
                        {
                            dyn_block(row, col) = static_cast<Scalar>(-1);
                        }
                    }

                    mat.SetBlock(i, j, dyn_block);
                    for(size_t row = 0; row < RowValue; ++row)
                    {
                        for(size_t col = 0; col < ColValue; ++col)
                        {
                            if(row < i || row >= i + rows || col < j || col >= j + cols)
                            {
                                ASSERT_EQ(row + col * RowValue, mat(row, col));
                            }
                            else
                            {
                                ASSERT_EQ(static_cast<Scalar>(-1), mat(row, col));
                            }
                        }
                    }
                }
            }
        }
    }
}

TEST(SUITENAME, BraceOperator)
{
    MatrixType mat = CreateSequenceMatrix();
    MatrixType const const_mat = CreateSequenceMatrix();

    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(i * ColValue + j, mat(i, j));
            ASSERT_EQ(i * ColValue + j, const_mat(i, j));
        }
    }
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ((i % RowValue) * ColValue + (i / RowValue), mat(i));
        ASSERT_EQ((i % RowValue) * ColValue + (i / RowValue), const_mat(i));
    }
}

TEST(SUITENAME, At)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat.At(i, j));
        }
    }

    MatrixType const const_mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), const_mat.At(i, j));
        }
    }
}


TEST(SUITENAME, EqualOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    ASSERT_TRUE(mat1 == mat2);
    ASSERT_TRUE(mat2 == mat1);
    mat2(0) = 100;
    ASSERT_FALSE(mat1 == mat2);
    ASSERT_FALSE(mat2 == mat1);
}

TEST(SUITENAME, AddOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    // C = A + B
    MatrixType mat3 = mat1 + mat2;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 2), mat3(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat2(i, j));
        }
    }

    // B = A + B
    mat2 = mat1 + mat2;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 2), mat2(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
        }
    }

    // A = A + A
    mat1 = mat1 + mat1;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 2), mat1(i, j));
        }
    }
}

TEST(SUITENAME, AddEqualOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    mat2 += mat1;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 2), mat2(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
        }
    }

    mat1 += mat1;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 2), mat1(i, j));
        }
    }
}

TEST(SUITENAME, SubOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    // C = A - B
    MatrixType mat3 = mat1 - mat2;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat3(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat2(i, j));
        }
    }

    // B = A - B
    mat2 = mat1 - mat2;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
        }
    }

    // A = A - A
    mat1 = mat1 - mat1;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat1(i, j));
        }
    }
}

TEST(SUITENAME, SubEqualOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    mat2 -= mat1;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
        }
    }

    mat1 -= mat1;
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat1(i, j));
        }
    }
}

TEST(SUITENAME, MulOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    mat2 = mat1 * static_cast<Scalar>(1);       
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(i * ColValue + j, mat2(i, j));
        }
    }

    mat2 = mat1 * static_cast<Scalar>(10);       
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 10), mat2(i, j));
        }
    }

    mat2 = mat1 * static_cast<Scalar>(0);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
        }
    }

    mat1 = mat1 * static_cast<Scalar>(1);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 1), mat1(i, j));
        }
    }

    mat1 = mat1 * static_cast<Scalar>(10);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 10), mat1(i, j));
        }
    }

    mat1 = mat1 * static_cast<Scalar>(0);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat1(i, j));
        }
    }
}

TEST(SUITENAME, MulEqualOperator)
{
    MatrixType mat = CreateSequenceMatrix();

    mat *= static_cast<Scalar>(1);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 1), mat(i, j));
        }
    }

    mat *= static_cast<Scalar>(10);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>((i * ColValue + j) * 10), mat(i, j));
        }
    }

    mat *= static_cast<Scalar>(0);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(0), mat(i, j));
        }
    }
}

TEST(SUITENAME, OperatorDiv)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();

    mat2 = mat1 / static_cast<Scalar>(1);       
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat2(i, j));
        }
    }

    mat2 = mat1 / static_cast<Scalar>(10);       
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_NEAR(static_cast<Scalar>((i * ColValue + j) / 10.0), mat2(i, j), 1e-5);
        }
    }

    EXPECT_THROW(mat2 = mat1 / static_cast<Scalar>(0), std::runtime_error);

    mat1 = mat1 / static_cast<Scalar>(1);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
        }
    }

    mat1 = mat1 / static_cast<Scalar>(10);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_NEAR(static_cast<Scalar>((i * ColValue + j) / 10.0), mat1(i, j), 1e-5);
        }
    }

    EXPECT_THROW(mat1 = mat1 / static_cast<Scalar>(0), std::runtime_error);
}

TEST(SUITENAME, DivEqualOperator)
{
    MatrixType mat1 = CreateSequenceMatrix();

    mat1 /= static_cast<Scalar>(1);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat1(i, j));
        }
    }

    mat1 /= static_cast<Scalar>(10);
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_NEAR(static_cast<Scalar>((i * ColValue + j) / 10.0), mat1(i, j), 1e-5);
        }
    }

    EXPECT_THROW(mat1 /= static_cast<Scalar>(0), std::runtime_error);
}

TEST(SUITENAME, NegateOperator)
{
    MatrixType mat = CreateSequenceMatrix();
    mat = -mat;
    for(size_t i = 0; i < SizeValue; ++i)
    {
        ASSERT_EQ(-static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), mat(i));
    }
}

TEST(SUITENAME, Transpose)
{
    MatrixType mat = CreateSequenceMatrix();
    TransposeMatrixType mat_t = mat.Transpose();

    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(mat(i, j), mat_t(j, i));
        }
    }
}

TEST(SUITENAME, GetSquaredNorm)
{
    MatrixType mat = CreateSequenceMatrix();

    holo::float64_t norm = 0.0;
    for(size_t i = 0; i < SizeValue; ++i)
    {
        norm += i * i;
    }
    ASSERT_EQ(norm, mat.GetSquaredNorm());

    for(size_t i = 0; i < SizeValue; ++i)
    {
        mat(i) = 0;
    }
    ASSERT_EQ(static_cast<Scalar>(0), mat.GetSquaredNorm());
}

TEST(SUITENAME, GetNorm)
{
    MatrixType mat = CreateSequenceMatrix();

    holo::float64_t norm = 0.0;
    for(size_t i = 0; i < SizeValue; ++i)
    {
        norm += i * i;
    }
    ASSERT_NEAR(sqrt(norm), mat.GetNorm(), mat.GetNorm() * 1e-5);

    for(size_t i = 0; i < SizeValue; ++i)
    {
        mat(i) = 0;
    }
    ASSERT_EQ(static_cast<Scalar>(0), mat.GetNorm());
}

TEST(SUITENAME, IsSquared)
{
    MatrixType mat = CreateSequenceMatrix();

    if(RowValue == ColValue)
    {
        ASSERT_TRUE(mat.IsSquared());
    }
    else
    {
        ASSERT_FALSE(mat.IsSquared());
    }
}

TEST(SUITENAME, IsSymmetric)
{
    MatrixType mat = CreateSequenceMatrix();
    if(RowValue == ColValue)
    {
        if(RowValue == 1)
        {
            ASSERT_TRUE(mat.IsSymmetric());
        }
        else
        {
            ASSERT_FALSE(mat.IsSymmetric());
            for(size_t i = 0; i < RowValue; ++i)
            {
                for(size_t j = 0; j < i; ++j)
                {
                    mat(i, j) = mat(j, i);
                }
            }
            ASSERT_TRUE(mat.IsSymmetric());
        }
    }
    else
    {
        ASSERT_FALSE(mat.IsSymmetric());
    }
}

TEST(SUITENAME, IsApprox)
{
    MatrixType mat1 = CreateSequenceMatrix();
    MatrixType mat2 = CreateSequenceMatrix();
    mat1.Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});
    mat2.Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});
    MatrixType mat3 = mat2 * 1.01;
    
    ASSERT_TRUE(mat1.IsApprox(mat2));
    ASSERT_FALSE(mat1.IsApprox(mat3));
    ASSERT_TRUE(mat1.IsApprox(mat3, 1e-2 + 1e-5));
}

TEST(SUITENAME, Sum)
{
    MatrixType mat = CreateZeroMatrix();
    ASSERT_EQ(static_cast<Scalar>(0), mat.Sum());

    mat = CreateSequenceMatrix();
    holo::float64_t sum = 0.0;
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        sum += i;
    }
    ASSERT_EQ(static_cast<Scalar>(sum), mat.Sum());
}

TEST(SUITENAME, Mean)
{
    MatrixType mat = CreateZeroMatrix();
    ASSERT_EQ(static_cast<Scalar>(0), mat.Mean());

    mat = CreateSequenceMatrix();
    holo::float64_t sum = 0.0;
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        sum += i;
    }
    sum /= mat.GetSize();
    ASSERT_EQ(static_cast<Scalar>(sum), mat.Mean());
}

TEST(SUITENAME, MinCoeff)
{
    MatrixType mat = CreateZeroMatrix();
    ASSERT_EQ(static_cast<Scalar>(0), mat.MinCoeff());

    mat = CreateSequenceMatrix();
    mat = -mat;
    ASSERT_EQ(static_cast<Scalar>(-(mat.GetSize() - 1)), mat.MinCoeff());
}

TEST(SUITENAME, MaxCoeff)
{
    MatrixType mat = CreateZeroMatrix();
    ASSERT_EQ(static_cast<Scalar>(0), mat.MaxCoeff());

    mat = CreateSequenceMatrix();
    ASSERT_EQ(static_cast<Scalar>(mat.GetSize() - 1), mat.MaxCoeff());
}

TEST(SUITENAME, ForeachOperation)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
    mat.Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j + 1), mat(i, j));
        }
    }
}

TEST(SUITENAME, ForeachOperationConst)
{
    MatrixType const mat = CreateSequenceMatrix();
    MatrixType mat2 = CreateZeroMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
            ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
        }
    }
    mat.Foreach([&mat2](Scalar const& value, size_t i, size_t j) mutable->void{mat2(i, j) = value;});
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat2(i, j));
        }
    }
}

TEST(SUITENAME, ForeachOperationCriteria)
{
    MatrixType mat = CreateSequenceMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
    mat.Foreach([](Scalar& value, size_t, size_t)->void{value = -value;}, 
                [](Scalar const&, size_t i, size_t j)->bool{return (i * ColValue + j) % 2 == 0;});
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            if((i * ColValue + j) % 2 == 0)
            {
                ASSERT_EQ(-static_cast<Scalar>(i * ColValue + j), mat(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
            }
        }
    }
}

TEST(SUITENAME, ForeachOperationCriteriaConst)
{
    MatrixType const mat = CreateSequenceMatrix();
    MatrixType mat2 = CreateZeroMatrix();
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
        }
    }
    mat.Foreach([&mat2](Scalar const& value, size_t i, size_t j) mutable->void{mat2(i, j) = -value;}, 
                [](Scalar const&, size_t i, size_t j)->bool{return (i * ColValue + j) % 2 == 0;});
    for(size_t i = 0; i < RowValue; ++i)
    {
        for(size_t j = 0; j < ColValue; ++j)
        {
            ASSERT_EQ(static_cast<Scalar>(i * ColValue + j), mat(i, j));
            if((i * ColValue + j) % 2 == 0)
            {
                ASSERT_EQ(-static_cast<Scalar>(i * ColValue + j), mat2(i, j));
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(0), mat2(i, j));
            }
        }
    }
}

TEST(SUITENAME, CwiseAbs)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseAbs();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_EQ(static_cast<Scalar>(0), mat2(i));
    }
    
    mat = -CreateSequenceMatrix();

    mat2 = mat.CwiseAbs();
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), mat2(i));
    }
}

TEST(SUITENAME, CwiseAbsSquare)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseAbsSquare();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_EQ(static_cast<Scalar>(0), mat2(i));
    }
    
    mat = -CreateSequenceMatrix();

    mat2 = mat.CwiseAbsSquare();
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        size_t value = (i % RowValue) * ColValue + (i / RowValue);
        ASSERT_EQ(static_cast<Scalar>(value * value), mat2(i));
    }
}

TEST(SUITENAME, CwiseCos)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseCos();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(1), mat2(i), 1e-5);
    }
    
    mat = CreateSequenceMatrix();

    mat2 = mat.CwiseCos();
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(std::cos(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue))), mat2(i), 1e-5);
    }
}

TEST(SUITENAME, CwiseExp)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseExp();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(1), mat2(i), 1e-5);
    }
    
    mat = CreateSequenceMatrix();

    mat2 = mat.CwiseExp();
    for(size_t i = 0; i < SizeValue; ++i)
    {
        if(std::isfinite(std::exp(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)))))
        {
            ASSERT_NEAR(std::exp(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue))), 
                        mat2(i), 
                        std::abs(mat2(i) * 1e-5));
        }
        else
        {
            ASSERT_TRUE(std::isinf(mat2(i)));
        }
    }
}

TEST(SUITENAME, CwisePow)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwisePow(static_cast<Scalar>(0));
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(1), mat2(i), std::abs(mat2(i) * 1e-5));
    }
    
    mat = CreateSequenceMatrix();

    mat2 = mat.CwisePow(static_cast<Scalar>(1));
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), mat2(i), std::abs(mat2(i) * 1e-5));
    }

    mat2 = mat.CwisePow(static_cast<Scalar>(2));
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        size_t value = (i % RowValue) * ColValue + (i / RowValue);
        ASSERT_NEAR(static_cast<Scalar>(value * value), mat2(i), std::abs(mat2(i) * 1e-5));
    }

    mat2 = mat.CwisePow(static_cast<Scalar>(2.5));
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(std::pow(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), 2.5), 
                    mat2(i), 
                    std::abs(mat2(i) * 1e-5));
    }
}

TEST(SUITENAME, CwiseProduct)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat_other = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseProduct(mat_other);
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(0), mat2(i), 1e-5);
    }
    
    mat = CreateSequenceMatrix();
    mat_other = CreateSequenceMatrix();

    mat2 = mat.CwiseProduct(mat_other);
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        size_t value = (i % RowValue) * ColValue + (i / RowValue);
        ASSERT_NEAR(static_cast<Scalar>(value * value), mat2(i), 1e-5);
    }
}

TEST(SUITENAME, CwiseQuotient)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat_other = CreateZeroMatrix();
    MatrixType mat2 = CreateZeroMatrix();
    EXPECT_THROW(mat2 = mat.CwiseQuotient(mat_other), std::runtime_error);
    
    mat = CreateSequenceMatrix().Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});
    mat_other = CreateSequenceMatrix().Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});

    mat2 = mat.CwiseQuotient(mat_other);
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(static_cast<Scalar>(1), mat2(i), 1e-5);
    }

    mat_other /= static_cast<Scalar>(2);
    mat2 = mat.CwiseQuotient(mat_other);
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(static_cast<Scalar>(2), mat2(i), 1e-5);
    }
}

TEST(SUITENAME, CwiseSin)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseSin();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(0), mat2(i), 1e-5);
    }
    
    mat = CreateSequenceMatrix();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), mat(i));
    }

    mat2 = mat.CwiseSin();
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(std::sin(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue))), mat2(i), 1e-5);
    }
}

TEST(SUITENAME, CwiseSqrt)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseSqrt();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(0), mat2(i), 1e-5);
    }
    
    mat = CreateSequenceMatrix();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), mat(i));
    }

    mat2 = mat.CwiseSqrt();
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(std::sqrt(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue))), mat2(i), 1e-5);
    }
}

TEST(SUITENAME, CwiseTan)
{
    MatrixType mat = CreateZeroMatrix();
    MatrixType mat2 = mat.CwiseTan();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), mat(i));
        ASSERT_NEAR(static_cast<Scalar>(0), mat2(i), 1e-5);
    }
    
    mat = CreateSequenceMatrix();
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue)), mat(i));
    }

    mat2 = mat.CwiseTan();
    for(size_t i = 0; i < mat2.GetSize(); ++i)
    {
        ASSERT_NEAR(std::tan(static_cast<Scalar>((i % RowValue) * ColValue + (i / RowValue))), mat2(i), 1e-5);
    }
}

TEST(SUITENAME, Fill)
{
    MatrixType mat = CreateSequenceMatrix();
    mat.Fill(static_cast<Scalar>(1.0));
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(1.0), mat(i));
    }
}

TEST(SUITENAME, IsZero)
{
    MatrixType mat = CreateSequenceMatrix();
    mat.Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});
    ASSERT_FALSE(mat.IsZero());
    mat = CreateZeroMatrix();
    ASSERT_TRUE(mat.IsZero());
}

TEST(SUITENAME, IsOne)
{
    MatrixType mat = CreateSequenceMatrix();
    ASSERT_FALSE(mat.IsOne());
    mat.Fill(static_cast<Scalar>(1.0));
    ASSERT_TRUE(mat.IsOne());
}

TEST(SUITENAME, SetZero)
{
    MatrixType mat = CreateSequenceMatrix();
    mat.Foreach([](Scalar& value, size_t, size_t)->void{value += 1;});
    ASSERT_FALSE(mat.IsZero());
    mat.SetZero();
    ASSERT_TRUE(mat.IsZero());
}

TEST(SUITENAME, SetOne)
{
    MatrixType mat = CreateSequenceMatrix();
    ASSERT_FALSE(mat.IsOne());
    mat.SetOne();
    ASSERT_TRUE(mat.IsOne());
}

TEST(SUITENAME, SetConstant)
{
    MatrixType mat = CreateSequenceMatrix();
    mat.SetConstant(static_cast<Scalar>(0));
    ASSERT_TRUE(mat.IsZero());
    mat.SetConstant(static_cast<Scalar>(1));
    ASSERT_TRUE(mat.IsOne());
    mat.SetConstant(static_cast<Scalar>(2));
    for(size_t i = 0; i < mat.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(2), mat(i));
    }
}

TEST(SUITENAME, SetIdentity)
{
    MatrixType mat = CreateSequenceMatrix();
    mat.SetIdentity();
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

