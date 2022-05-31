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

#ifndef TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_SQUARED_MATRIX_OPERATIONS_H_
#define TEST_NUMERICS_MATRIX_TEST_FIXED_SIZE_SQUARED_MATRIX_OPERATIONS_H_

#include <cmath>

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

TEST(SUITENAME, GetDiagonal)
{
    MatrixType mat = CreateSequenceMatrix();
    ColMatrixType diag;
    if(RowValue != ColValue)
    {
        EXPECT_THROW(diag = mat.GetDiagonal(), std::runtime_error);
    }
    else
    {
        diag = mat.GetDiagonal();
        for(size_t i = 0; i < diag.GetRows(); ++i)
        {
            ASSERT_EQ(mat(i, i), diag(i));
        }
    }
}

#endif

