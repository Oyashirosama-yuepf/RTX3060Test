/*!
 * @file test_eigen_solver.cpp
 * @brief eigen solver unit test
 * @author Yanwei Du
 * @date 2019-Sep-09
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/numerics/eigen_solver.h>

using namespace holo;
using holo::numerics::MatrixX;
using holo::numerics::VectorX;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(EigenSolver, ComputeEigenValuesAndVectors)
{
    MatrixX matrix(2u, 2u);
    {
        matrix(0u, 0u) = 1.0;
        matrix(0u, 1u) = 2.0;
        matrix(1u, 0u) = 2.0;
        matrix(1u, 1u) = 3.0;
    }

    // call method and check results
    VectorX expected_values(2u);
    {
        expected_values(0u) = -0.236068;
        expected_values(1u) = 4.23607;
    }

    MatrixX expected_vectors(2, 2);
    {
        expected_vectors(0u, 0u) = -0.850651;
        expected_vectors(0u, 1u) = -0.525731;
        expected_vectors(1u, 0u) = 0.525731;
        expected_vectors(1u, 1u) = -0.850651;
    }

    VectorX      actual_values;
    MatrixX      actual_vectors;
    const bool_t flag = eigen_solver::ComputeEigenValuesAndVectors(matrix, actual_values, actual_vectors);

    ASSERT_TRUE(flag);
    ASSERT_NEAR(expected_values(0u), actual_values(0u), 1e-3);
    ASSERT_NEAR(expected_values(1u), actual_values(1u), 1e-3);
    ASSERT_NEAR(expected_vectors(0u, 0u), actual_vectors(0u, 0u), 1e-3);
    ASSERT_NEAR(expected_vectors(0u, 1u), actual_vectors(0u, 1u), 1e-3);
    ASSERT_NEAR(expected_vectors(1u, 0u), actual_vectors(1u, 0u), 1e-3);
    ASSERT_NEAR(expected_vectors(1u, 1u), actual_vectors(1u, 1u), 1e-3);

    const MatrixX matrix2(3u, 4u);
    const bool_t flag2 = eigen_solver::ComputeEigenValuesAndVectors(matrix2, actual_values, actual_vectors);
    ASSERT_FALSE(flag2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(EigenSolver, SVD)
{
    MatrixX matrix(3u, 4u);
    {
        matrix(0u, 0u) = 1.0;
        matrix(1u, 1u) = 2.0;
        matrix(2u, 2u) = 3.0;
    }

    // check results
    MatrixX U;
    VectorX S;
    MatrixX V;

    const bool_t flag = eigen_solver::SVD(matrix, U, S, V);
    ASSERT_TRUE(flag);
    ASSERT_DOUBLE_EQ(3.0, S(0u));
    ASSERT_DOUBLE_EQ(2.0, S(1u));
    ASSERT_DOUBLE_EQ(1.0, S(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(EigenSolver, SovleLinearSystem)
{
    // matrix
    MatrixX matrix(3u, 3u);
    {
        for (uint8_t i = 0u; i < matrix.GetRows(); i++)
        {
            for (uint8_t j = 0u; j < matrix.GetCols(); j++)
            {
                matrix(i, j) = i * matrix.GetCols() + j + 1.0;
            }
        }
        matrix(2u, 2u) = 10u;
    }

    // expected results
    VectorX expected(3u);
    {
        expected(0u) = -2.0;
        expected(1u) = 1.0;
        expected(2u) = 1.0;
    }

    // construct b
    const VectorX b = matrix * expected;

    // call method and check results
    const VectorX actual = eigen_solver::SolveLinearSystem(matrix, b);
    ASSERT_NEAR(expected(0u), actual(0u), 1e-8);
    ASSERT_NEAR(expected(1u), actual(1u), 1e-8);
    ASSERT_NEAR(expected(2u), actual(2u), 1e-8);

    VectorX actual2 = eigen_solver::SolveLinearSystem(matrix, b, holo::eigen_solver::Type::FULL_PIV_LU);
    actual2 = eigen_solver::SolveLinearSystem(matrix, b, holo::eigen_solver::Type::LLT);
    actual2 = eigen_solver::SolveLinearSystem(matrix, b, holo::eigen_solver::Type::LDLT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
