/*!
 * @file test_matrix.cpp
 * @brief matrix unit test
 * @author Yanwei Du
 * @date July-09-2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <cmath>

#include <gtest/gtest.h>

#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

using namespace holo::numerics;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, ConstructFixedSizeMatrix)
{
    const Matrix2f matrix;

    // check results
    ASSERT_EQ(2u, matrix.GetRows());
    ASSERT_EQ(2u, matrix.GetCols());
}

TEST(Matrix2f, CopyAssignment)
{
    Matrix2f matrix;

    const Matrix2f mat_f(0.0f, 1.0f, 2.0f, 3.0f);
    matrix = mat_f;
    ASSERT_EQ(matrix(0,0), 0.0f);
    ASSERT_EQ(matrix(0,1), 1.0f);
    ASSERT_EQ(matrix(1,0), 2.0f);
    ASSERT_EQ(matrix(1,1), 3.0f);

    Matrix2f::Base base(2, 2, {4.0f, 5.0f, 6.0f, 7.0f});
    matrix = base;
    ASSERT_EQ(matrix(0,0), 4.0f);
    ASSERT_EQ(matrix(0,1), 5.0f);
    ASSERT_EQ(matrix(1,0), 6.0f);
    ASSERT_EQ(matrix(1,1), 7.0f);
}

TEST(RowVector2f, CopyAssignment)
{
    RowVector2f matrix;

    const RowVector2f mat_f(0.0f, 1.0f);
    matrix = mat_f;
    ASSERT_EQ(matrix(0,0), 0.0f);
    ASSERT_EQ(matrix(0,1), 1.0f);

    RowVector2f::Base base(1, 2, {4.0f, 5.0f});

    matrix = base;
    ASSERT_EQ(matrix(0,0), 4.0f);
    ASSERT_EQ(matrix(0,1), 5.0f);
}

TEST(MatrixXf, CopyAssignment)
{
    MatrixXf matrix(3u, 2u), mat_f(2u, 2u);
    mat_f(0u, 0u) = 1.0f;
    mat_f(0u, 1u) = 2.0f;
    mat_f(1u, 0u) = 3.0f;
    mat_f(1u, 1u) = 4.0f;

    matrix = mat_f;
    ASSERT_EQ(matrix.GetRows(), 2u);
    ASSERT_EQ(matrix.GetCols(), 2u);
    ASSERT_EQ(matrix(0,1), 2.0f);
    ASSERT_EQ(matrix(1,0), 3.0f);
    ASSERT_EQ(matrix(1,1), 4.0f);


    MatrixXf::Base base(1u, 2u);
    base(0u, 0u) = 4.0f;
    base(0u, 1u) = 5.0f;

    matrix = base;
    ASSERT_EQ(matrix.GetRows(), 1u);
    ASSERT_EQ(matrix.GetCols(), 2u);
    ASSERT_EQ(matrix(0,0), 4.0f);
    ASSERT_EQ(matrix(0,1), 5.0f);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, ConstructDynamicMatrix)
{
    const MatrixX matrix(2u, 10u);

    // check results
    ASSERT_EQ(2u, matrix.GetRows());
    ASSERT_EQ(10u, matrix.GetCols());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, ConstructDynamicMatrixFromInvalidSize)
{
    ASSERT_THROW(const MatrixX m(1000, 2000), std::out_of_range);
    ASSERT_THROW(const MatrixX m(1000, -1), std::out_of_range);
    ASSERT_THROW(const MatrixX m(-1, 1000), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, GetRawData)
{
    const Matrix2d matrix(1.0, -2.0, 3.0, -4.0);

    // check results
    ASSERT_EQ(1.0, matrix.GetData()[0u]);
    ASSERT_EQ(3.0, matrix.GetData()[1u]);
    ASSERT_EQ(-2.0, matrix.GetData()[2u]);
    ASSERT_EQ(-4.0, matrix.GetData()[3u]);

    // use memcpy
    holo::float64_t data[4u];
    memcpy(data, matrix.GetData(), sizeof(holo::float64_t) * matrix.GetSize());

    // check results
    ASSERT_EQ(1.0, data[0u]);
    ASSERT_EQ(3.0, data[1u]);
    ASSERT_EQ(-2.0, data[2u]);
    ASSERT_EQ(-4.0, data[3u]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Cast)
{
    // create matrix
    const Matrix2f mat_f(0.0f, 1.0f, 2.0f, 2.0f);

    // call cast
    const Matrix2d mat_d = mat_f.Cast<holo::float64_t>();

    // check results
    ASSERT_EQ(2u, mat_d.GetRows());
    ASSERT_EQ(2u, mat_d.GetCols());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, ElementAssignmentAndAccess)
{
    Matrix3d mat;

    // assign value to matrix element
    for (uint8_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint8_t j = 0u; j < mat.GetCols(); j++)
        {
            mat(i, j) = i * mat.GetCols() + j;
        }
    }

    // check results
    for (uint8_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint8_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t val = i * mat.GetCols() + j;
            ASSERT_EQ(val, mat(i, j));
            ASSERT_EQ(val, mat.At(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Transpose)
{
    // create new matrix
    const uint8_t rows = 2u;
    const uint8_t cols = 3u;
    MatrixX       mat(rows, cols);

    // assign value to matrix element
    for (uint8_t i = 0u; i < rows; i++)
    {
        for (uint8_t j = 0u; j < cols; j++)
        {
            mat(i, j) = i * cols + j;
        }
    }

    // transpose a matrix
    const MatrixX mat_t = mat.Transpose();

    // check results
    for (uint8_t i = 0u; i < mat_t.GetRows(); i++)
    {
        for (uint8_t j = 0u; j < mat_t.GetCols(); j++)
        {
            ASSERT_EQ(mat(j, i), mat_t(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Equal)
{
    // create matrix
    MatrixX mat(3u, 3u);
    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t value = i * mat.GetCols() + j;
            mat(i, j)                   = value;
        }
    }

    MatrixX other(3u, 3u);

    // check results
    ASSERT_FALSE(mat == other);

    other = mat;
    ASSERT_TRUE(mat == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Plus)
{
    // create matrix
    const Matrix2 xmat(1.0, 2.0, 3.0, 4.0);
    const Matrix2 ymat(5.0, 6.0, 7.0, 8.0);

    // call plus
    const Matrix2 zmat = xmat + ymat;

    // check results
    ASSERT_EQ(6.0, zmat(0u, 0u));
    ASSERT_EQ(8.0, zmat(0u, 1u));
    ASSERT_EQ(10.0, zmat(1u, 0u));
    ASSERT_EQ(12.0, zmat(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, PlusEqual)
{
    // create matrix
    Matrix2       xmat(1.0, 2.0, 3.0, 4.0);
    const Matrix2 ymat(5.0, 6.0, 7.0, 8.0);

    // call plus
    xmat += ymat;

    // check results
    ASSERT_EQ(6.0, xmat(0u, 0u));
    ASSERT_EQ(8.0, xmat(0u, 1u));
    ASSERT_EQ(10.0, xmat(1u, 0u));
    ASSERT_EQ(12.0, xmat(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Minus)
{
    // create matrix
    const Matrix2 xmat(1.0, 2.0, 3.0, 4.0);
    const Matrix2 ymat(5.0, 6.0, 7.0, 8.0);

    // call minus
    const Matrix2 zmat = xmat - ymat;

    // check results
    ASSERT_EQ(-4.0, zmat(0u, 0u));
    ASSERT_EQ(-4.0, zmat(0u, 1u));
    ASSERT_EQ(-4.0, zmat(1u, 0u));
    ASSERT_EQ(-4.0, zmat(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MinusEqual)
{
    // create matrix
    Matrix2       xmat(1.0, 2.0, 3.0, 4.0);
    const Matrix2 ymat(5.0, 6.0, 7.0, 8.0);

    // call minus
    xmat -= ymat;

    // check results
    ASSERT_EQ(-4.0, xmat(0u, 0u));
    ASSERT_EQ(-4.0, xmat(0u, 1u));
    ASSERT_EQ(-4.0, xmat(1u, 0u));
    ASSERT_EQ(-4.0, xmat(1u, 1u));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MultiplyScalar)
{
    // create matrix
    const holo::float64_t s = 2.0;
    const Matrix2         xmat(1.0, 2.0, 3.0, 4.0);

    // call multiply
    const Matrix2 ymat = xmat * s;
    const Matrix2 zmat = s * xmat;

    // check results
    ASSERT_EQ(2.0, ymat(0u, 0u));
    ASSERT_EQ(4.0, ymat(0u, 1u));
    ASSERT_EQ(6.0, ymat(1u, 0u));
    ASSERT_EQ(8.0, ymat(1u, 1u));

    ASSERT_EQ(2.0, zmat(0u, 0u));
    ASSERT_EQ(4.0, zmat(0u, 1u));
    ASSERT_EQ(6.0, zmat(1u, 0u));
    ASSERT_EQ(8.0, zmat(1u, 1u));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MultiplyScalarEqual)
{
    // create matrix
    const holo::float64_t s = 2.0;
    Matrix2               xmat(1.0, 2.0, 3.0, 4.0);

    // call multiply
    xmat *= s;

    // check results
    ASSERT_EQ(2.0, xmat(0u, 0u));
    ASSERT_EQ(4.0, xmat(0u, 1u));
    ASSERT_EQ(6.0, xmat(1u, 0u));
    ASSERT_EQ(8.0, xmat(1u, 1u));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DivideScalar)
{
    // create matrix
    const holo::float64_t s = 2.0;
    const Matrix2         xmat(1.0, 2.0, 3.0, 4.0);

    // call multiply
    const Matrix2 ymat = xmat / s;

    // check results
    ASSERT_EQ(0.5, ymat(0u, 0u));
    ASSERT_EQ(1.0, ymat(0u, 1u));
    ASSERT_EQ(1.5, ymat(1u, 0u));
    ASSERT_EQ(2.0, ymat(1u, 1u));

    const holo::float64_t s_zero = 0.0;

    bool is_exception_catched = false;
    try
    {
        const Matrix2 zmat = xmat / s_zero;
    }
    catch (const std::runtime_error& e)
    {
        is_exception_catched = true;
    }
    catch (...)
    {
        FAIL() << "Caught expected exception!";
    }

    ASSERT_TRUE(is_exception_catched);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DivideScalarEqual)
{
    // create matrix
    const holo::float64_t s = 2.0;
    Matrix2               xmat(1.0, 2.0, 3.0, 4.0);

    // call multiply
    xmat /= s;

    // check results
    ASSERT_EQ(0.5, xmat(0u, 0u));
    ASSERT_EQ(1.0, xmat(0u, 1u));
    ASSERT_EQ(1.5, xmat(1u, 0u));
    ASSERT_EQ(2.0, xmat(1u, 1u));

    const holo::float64_t s_zero = 0.0;

    bool is_exception_catched = false;
    try
    {
        xmat /= s_zero;
    }
    catch (const std::runtime_error& e)
    {
        is_exception_catched = true;
    }

    ASSERT_TRUE(is_exception_catched);
    ASSERT_EQ(0.5, xmat(0u, 0u));
    ASSERT_EQ(1.0, xmat(0u, 1u));
    ASSERT_EQ(1.5, xmat(1u, 0u));
    ASSERT_EQ(2.0, xmat(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MultiplyMatrix)
{
    // create matrix
    const Matrix2 xmat(1.0, 2.0, 3.0, 4.0);
    const Matrix2 ymat(5.0, 6.0, 7.0, 8.0);

    // call multiply
    const Matrix2 zmat = xmat * ymat;

    // check results
    ASSERT_EQ(19.0, zmat(0u, 0u));
    ASSERT_EQ(22.0, zmat(0u, 1u));
    ASSERT_EQ(43.0, zmat(1u, 0u));
    ASSERT_EQ(50.0, zmat(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MultiplyTwoMatrices)
{
    // create matrix
    const Matrix2 xmat(1.0, 2.0, 3.0, 4.0);
    const Matrix2 ymat(5.0, 6.0, 7.0, 8.0);

    // call multiply
    const Matrix2 zmat = xmat * ymat * xmat;

    // check results
    ASSERT_EQ(85.0, zmat(0u, 0u));
    ASSERT_EQ(126.0, zmat(0u, 1u));
    ASSERT_EQ(193.0, zmat(1u, 0u));
    ASSERT_EQ(286.0, zmat(1u, 1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, GetDiagonal)
{
    // create matrix
    const Matrix2f mat(0.0f, 1.0f, 2.0f, 3.0f);
    MatrixXf       mat2(3u, 3u);
    for (uint16_t i = 0u; i < 3u; i++)
    {
        for (uint16_t j = 0u; j < 3u; j++)
        {
            mat2(i, j) = i * 3.0 + j;
        }
    }

    // call method and check results
    const Vector2f actual = mat.GetDiagonal();
    ASSERT_EQ(Vector2f(0.0f, 3.0f), actual);

    const Vector3f actual2 = mat2.GetDiagonal();
    ASSERT_EQ(Vector3f(0.0f, 4.0f, 8.0f), actual2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, NormAndSquaredNorm)
{
    // create matrix
    const Matrix2f mat(0.0f, 1.0f, 2.0f, 2.0f);

    // call norm
    const holo::float32_t norm    = mat.GetNorm();
    const holo::float32_t sq_norm = mat.GetSquaredNorm();

    // check results
    ASSERT_EQ(3.0f, norm);
    ASSERT_EQ(9.0f, sq_norm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, IsSquared)
{
    const Matrix3d mat1;
    const MatrixXd mat2(3u, 3u);
    const MatrixXd mat3(3u, 4u);

    ASSERT_TRUE(mat1.IsSquared());
    ASSERT_TRUE(mat2.IsSquared());
    ASSERT_FALSE(mat3.IsSquared());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, IsSymmetric)
{
    const Matrix3d mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    const MatrixXd mat2(3u, 4u);
    const Matrix3d mat3 = mat1 + mat1.Transpose();

    ASSERT_FALSE(mat1.IsSymmetric());
    ASSERT_FALSE(mat2.IsSymmetric());
    ASSERT_TRUE(mat3.IsSymmetric());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, IsApprox)
{
    const Matrix3d mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    const Matrix3d mat2 = mat1;
    const Matrix3d mat3 = mat1 * 1.01;

    ASSERT_TRUE(mat1.IsApprox(mat2));
    ASSERT_FALSE(mat1.IsApprox(mat3));
    ASSERT_TRUE(mat1.IsApprox(mat3, 1e-1));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Sum)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const holo::float64_t actual = mat.Sum();
    ASSERT_EQ(-5.0, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Mean)
{
    const Matrix2d mat(-1.0, 2.0, -3.0, 4.0);

    // call method and check result
    const holo::float64_t actual = mat.Mean();
    ASSERT_EQ(0.5, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MinCoeff)
{
    const Matrix2d mat(-1.0, 2.0, -3.0, 4.0);

    // call method and check result
    const holo::float64_t actual = mat.MinCoeff();
    ASSERT_EQ(-3.0, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, MaxCoeff)
{
    const Matrix2d mat(-1.0, 2.0, -3.0, 4.0);

    // call method and check result
    const holo::float64_t actual = mat.MaxCoeff();
    ASSERT_EQ(4.0, actual);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseAbs)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseAbs();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::fabs(mat(i, j));
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseAbsSquare)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseAbsSquare();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = mat(i, j) * mat(i, j);
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseCos)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseCos();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::cos(mat(i, j));
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseExp)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseExp();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::exp(mat(i, j));
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwisePow)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const holo::float64_t p      = 3.0;
    const Matrix3d        actual = mat.CwisePow(p);

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::pow(mat(i, j), p);
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseProduct)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d other(9.0, -8.0, 7.0, -6.0, 5.0, -4.0, 3.0, -2.0, 1.0);
    const Matrix3d actual = mat.CwiseProduct(other);

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = mat(i, j) * other(i, j);
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseQuotient)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d other(9.0, -8.0, 7.0, -6.0, 5.0, -4.0, 3.0, -2.0, 1.0);
    const Matrix3d actual = mat.CwiseQuotient(other);

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = mat(i, j) / other(i, j);
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseQuotientInvalid)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d other(0.0, -8.0, 7.0, -6.0, 5.0, -4.0, 3.0, -2.0, 1.0);
    ASSERT_THROW(const Matrix3d actual = mat.CwiseQuotient(other), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseSin)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseSin();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::sin(mat(i, j));
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseSqrt)
{
    const Matrix3d mat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseSqrt();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::sqrt(mat(i, j));
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseSqrtInvalid)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    ASSERT_THROW(const Matrix3d actual = mat.CwiseSqrt(), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseSquare)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseSquare();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = mat(i, j) * mat(i, j);
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, CwiseTan)
{
    const Matrix3d mat(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0, -7.0, 8.0, -9.0);

    // call method and check result
    const Matrix3d actual = mat.CwiseTan();

    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t expected = std::tan(mat(i, j));
            ASSERT_EQ(expected, actual(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Fill)
{
    Matrix2d mat(-1.0, 2.0, -3.0, 4.0);

    // call method and check result
    mat.Fill(10.0);

    for (uint16_t i = 0u; i < 2u; i++)
    {
        for (uint16_t j = 0u; j < 2u; j++)
        {
            ASSERT_EQ(10.0, mat(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, IsZero)
{
    Matrix2d mat(-1.0, 2.0, -3.0, 4.0);

    // call method and check result
    ASSERT_FALSE(mat.IsZero());

    mat.SetZero();
    ASSERT_TRUE(mat.IsZero());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, IsOne)
{
    Matrix2d mat(-1.0, 2.0, -3.0, 4.0);

    // call method and check result
    ASSERT_FALSE(mat.IsOne());

    mat.SetOne();
    ASSERT_TRUE(mat.IsOne());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Zero)
{
    // create matrix
    Matrix3f m1(1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 4.0f);
    MatrixXf m2(2.0f, 3.0f);

    // call zeros
    m1.SetZero();
    m2.SetZero();

    // check results
    for (int32_t i = 0u; i < m1.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m1.GetCols(); j++)
        {
            ASSERT_EQ(0.0f, m1(i, j));
        }
    }

    for (int32_t i = 0u; i < m2.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m2.GetCols(); j++)
        {
            ASSERT_EQ(0.0f, m2(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, One)
{
    // create matrix
    Matrix3f m1(1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 4.0f);
    MatrixXf m2(2.0f, 3.0f);

    // call ones
    m1.SetOne();
    m2.SetOne();

    // check results
    for (int32_t i = 0u; i < m1.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m1.GetCols(); j++)
        {
            ASSERT_EQ(1.0f, m1(i, j));
        }
    }

    for (int32_t i = 0u; i < m2.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m2.GetCols(); j++)
        {
            ASSERT_EQ(1.0f, m2(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Constant)
{
    // create matrix
    Matrix3f m1(1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 4.0f);
    MatrixXf m2(2.0f, 3.0f);

    // call constant
    const holo::float32_t value = 10.5f;
    m1.SetConstant(value);
    m2.SetConstant(value);

    // check results
    for (int32_t i = 0u; i < m1.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m1.GetCols(); j++)
        {
            ASSERT_EQ(value, m1(i, j));
        }
    }

    for (int32_t i = 0u; i < m2.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m2.GetCols(); j++)
        {
            ASSERT_EQ(value, m2(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Identity)
{
    // create matrix
    Matrix3f m1(1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 4.0f);
    MatrixXf m2(2.0f, 3.0f);

    // call identity
    m1.SetIdentity();
    m2.SetIdentity();

    // check results
    for (int32_t i = 0u; i < m1.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m1.GetCols(); j++)
        {
            const holo::float32_t value = (i == j) ? 1.0f : 0.0f;
            ASSERT_EQ(value, m1(i, j));
        }
    }

    for (int32_t i = 0u; i < m2.GetRows(); i++)
    {
        for (int32_t j = 0u; j < m2.GetCols(); j++)
        {
            const holo::float32_t value = (i == j) ? 1.0f : 0.0f;
            ASSERT_EQ(value, m2(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, FixedSizeInverse)
{
    // create matrix
    const Matrix3f mat(1.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 4.0f);

    // call inverse
    const Matrix3f mat_inv = mat.Inverse();
    const Matrix3f expected(1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.25f);

    // check results
    for (uint8_t i = 0u; i < mat_inv.GetRows(); i++)
    {
        for (uint8_t j = 0u; j < mat_inv.GetCols(); j++)
        {
            ASSERT_EQ(expected(i, j), mat_inv(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicSizeInverse)
{
    // create matrix
    MatrixXf mat(3u, 3u);
    {
        mat(0u, 0u) = 1.0f;
        mat(1u, 1u) = 2.0f;
        mat(2u, 2u) = 4.0f;
    }

    // call inverse
    const MatrixXf mat_inv = mat.Inverse();

    // expected result
    MatrixXf expected(3u, 3u);
    {
        expected(0u, 0u) = 1.0f;
        expected(1u, 1u) = 0.5f;
        expected(2u, 2u) = 0.25f;
    }

    // check results
    for (uint8_t i = 0u; i < mat_inv.GetRows(); i++)
    {
        for (uint8_t j = 0u; j < mat_inv.GetCols(); j++)
        {
            ASSERT_EQ(expected(i, j), mat_inv(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, FixedSizeDeterminant)
{
    // create matrix
    const Matrix4 mat(1.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 4.0);

    // call determinant
    const holo::float64_t det = mat.GetDeterminant();

    // check results
    ASSERT_EQ(24.0f, det);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicSizeDeterminant)
{
    // create matrix
    MatrixXd mat(4u, 4u);
    {
        mat(0u, 0u) = 1.0;
        mat(1u, 1u) = 2.0;
        mat(2u, 2u) = 3.0;
        mat(3u, 3u) = 4.0;
    }

    // call determinant
    const holo::float64_t det = mat.GetDeterminant();

    // check results
    ASSERT_EQ(24.0f, det);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Trace)
{
    // create matrix
    const Matrix2 xmat(1.0, 2.0, 3.0, 4.0);
    const MatrixX ymat(2.0, 3.0);

    // call trace
    const holo::float64_t xtrace = xmat.GetTrace();
    const holo::float64_t ytrace = ymat.GetTrace();

    // check results
    ASSERT_EQ(5.0, xtrace);
    ASSERT_EQ(0.0, ytrace);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, Resize)
{
    // create matrix
    MatrixX mat(6u, 6u);
    mat.Resize(4u, 5u);

    // check results
    ASSERT_EQ(4u, mat.GetRows());
    ASSERT_EQ(5u, mat.GetCols());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, ResizeWithInvalidSize)
{
    // create matrix
    MatrixX mat(6u, 6u);

    // check results
    ASSERT_THROW(mat.Resize(1000, 2000), std::out_of_range);
    ASSERT_THROW(mat.Resize(1000, -1), std::out_of_range);
    ASSERT_THROW(mat.Resize(-1, 1000), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicSizeGetRowAndCol)
{
    // create matrix
    MatrixXd mat(3u, 5u);
    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t value = i * mat.GetCols() + j;
            mat(i, j)                   = value;
        }
    }

    // call method and check result
    const uint16_t                        row     = 1u;
    const MatrixT<holo::float64_t, 1, -1> block_r = mat.GetRow(row);

    ASSERT_EQ(1u, block_r.GetRows());
    ASSERT_EQ(5u, block_r.GetCols());
    for (uint16_t j = 0u; j < block_r.GetCols(); j++)
    {
        ASSERT_EQ(mat(row, j), block_r(0u, j));
    }

    // call method and check results
    const uint16_t col     = 3u;
    const VectorXd block_c = mat.GetCol(col);

    ASSERT_EQ(3u, block_c.GetRows());
    ASSERT_EQ(1u, block_c.GetCols());
    for (uint16_t i = 0u; i < block_c.GetRows(); i++)
    {
        ASSERT_EQ(mat(i, col), block_c(i, 0u));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicSizeBlock)
{
    // create matrix
    MatrixXd mat(3u, 3u);
    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t value = i * mat.GetCols() + j;
            mat(i, j)                   = value;
        }
    }

    // call method and check result
    const uint16_t start_row = 0u;
    const uint16_t start_col = 1u;
    const uint16_t rows      = 3u;
    const uint16_t cols      = 2u;
    const MatrixXd block     = mat.GetBlock(start_row, start_col, rows, cols);
    for (uint16_t i = 0u; i < block.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < block.GetCols(); j++)
        {
            const holo::float64_t value = (i + start_row) * mat.GetCols() + j + start_col;
            ASSERT_EQ(value, block(i, j));
        }
    }

    // call method and check results
    mat.SetBlock(0u, 0u, block);
    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            holo::float64_t value = i * mat.GetCols() + j;
            if (i < block.GetRows() && j < block.GetCols())
            {
                value = (i + start_row) * mat.GetCols() + j + start_col;
            }
            ASSERT_EQ(value, mat(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, FixedSizeBlock)
{
    // create matrix
    Matrix3d mat;
    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            const holo::float64_t value = i * mat.GetCols() + j;
            mat(i, j)                   = value;
        }
    }

    // call method and check result
    const uint16_t start_row = 0u;
    const uint16_t start_col = 1u;
    const uint16_t rows      = 2u;
    const uint16_t cols      = 2u;

    const Matrix2d block = mat.GetBlock(start_row, start_col, rows, cols);
    for (uint16_t i = 0u; i < block.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < block.GetCols(); j++)
        {
            const holo::float64_t value = (i + start_row) * mat.GetCols() + j + start_col;
            ASSERT_EQ(value, block(i, j));
        }
    }

    // call method and check results
    mat.SetBlock(0u, 0u, block);
    for (uint16_t i = 0u; i < mat.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < mat.GetCols(); j++)
        {
            holo::float64_t value = i * mat.GetCols() + j;
            if (i < block.GetRows() && j < block.GetCols())
            {
                value = (i + start_row) * mat.GetCols() + j + start_col;
            }
            ASSERT_EQ(value, mat(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicSizeMatrixToFixedSizeMatrix_1)
{
    MatrixXd d_mat(3u, 3u);
    {
        d_mat(0u, 0u) = -1.0;
        d_mat(1u, 1u) = 2.0;
        d_mat(2u, 2u) = -3.0;
    }

    // call methods
    const Matrix3d f_mat1 = d_mat;
    Matrix3d       f_mat2;
    f_mat2 = d_mat;

    // check results
    ASSERT_EQ(f_mat1.GetRows(), d_mat.GetRows());
    ASSERT_EQ(f_mat1.GetCols(), d_mat.GetCols());
    ASSERT_EQ(f_mat2.GetRows(), d_mat.GetRows());
    ASSERT_EQ(f_mat2.GetCols(), d_mat.GetCols());
    for (uint16_t row = 0u; row < d_mat.GetRows(); row++)
    {
        for (uint16_t col = 0u; col < d_mat.GetCols(); col++)
        {
            ASSERT_EQ(f_mat1(row, col), d_mat(row, col));
            ASSERT_EQ(f_mat2(row, col), d_mat(row, col));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicSizeMatrixToFixedSizeMatrix_2)
{
    MatrixXf d_mat(2u, 4u);
    {
        d_mat(0u, 0u) = -1.0f;
        d_mat(0u, 1u) = 2.0f;
        d_mat(1u, 2u) = 3.0f;
        d_mat(1u, 3u) = -4.0f;
    }

    // call methods
    const MatrixT<holo::float32_t, 2, 4> f_mat1 = d_mat;
    MatrixT<holo::float32_t, 2, 4>       f_mat2;
    f_mat2 = d_mat;

    // check results
    ASSERT_EQ(f_mat1.GetRows(), d_mat.GetRows());
    ASSERT_EQ(f_mat1.GetCols(), d_mat.GetCols());
    ASSERT_EQ(f_mat2.GetRows(), d_mat.GetRows());
    ASSERT_EQ(f_mat2.GetCols(), d_mat.GetCols());
    for (uint16_t row = 0u; row < d_mat.GetRows(); row++)
    {
        for (uint16_t col = 0u; col < d_mat.GetCols(); col++)
        {
            ASSERT_EQ(f_mat1(row, col), d_mat(row, col));
            ASSERT_EQ(f_mat2(row, col), d_mat(row, col));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, StaticZero)
{
    // create matrix
    const Matrix6 m = Matrix6::Zero();

    // check results
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            ASSERT_EQ(0.0, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, StaticOne)
{
    // create matrix
    const Matrix5 m = Matrix5::One();

    // check results
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            ASSERT_EQ(1.0, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, StaticConstant)
{
    // create matrix
    const holo::float32_t value = -1.0f;
    const Matrix4f        m     = Matrix4f::Constant(value);

    // check results
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            ASSERT_EQ(value, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, StaticIdentity)
{
    // create matrix
    const Matrix3f m = Matrix3f::Identity();

    // check results
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            const holo::float32_t value = (i == j) ? 1.0f : 0.0f;
            ASSERT_EQ(value, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicZero)
{
    // create matrix
    const MatrixX m = MatrixX::Zero(2u, 3u);

    // check results
    ASSERT_EQ(2u, m.GetRows());
    ASSERT_EQ(3u, m.GetCols());
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            ASSERT_EQ(0.0, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicOne)
{
    // create matrix
    const MatrixX m = MatrixX::One(3u, 4u);

    // check results
    ASSERT_EQ(3u, m.GetRows());
    ASSERT_EQ(4u, m.GetCols());
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            ASSERT_EQ(1.0, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicConstant)
{
    // create matrix
    const MatrixX m = MatrixX::Constant(4u, 5u, -0.5);

    // check results
    ASSERT_EQ(4u, m.GetRows());
    ASSERT_EQ(5u, m.GetCols());
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            ASSERT_EQ(-0.5, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, DynamicIdentity)
{
    // create matrix
    const MatrixX m = MatrixX::Identity(10u);

    // check results
    ASSERT_EQ(10u, m.GetRows());
    ASSERT_EQ(10u, m.GetCols());
    for (uint16_t i = 0u; i < m.GetRows(); i++)
    {
        for (uint16_t j = 0u; j < m.GetCols(); j++)
        {
            const holo::float64_t expected = (i == j) ? 1.0 : 0.0;
            ASSERT_EQ(expected, m(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, ConstructSpecialMatrixWithInvalidSize)
{
    ASSERT_THROW(MatrixX::Zero(1000, 2000), std::out_of_range);
    ASSERT_THROW(MatrixX::Zero(1000, -1), std::out_of_range);
    ASSERT_THROW(MatrixX::One(1000, 2000), std::out_of_range);
    ASSERT_THROW(MatrixX::One(1000, -1), std::out_of_range);
    ASSERT_THROW(MatrixX::Identity(1000), std::out_of_range);
    ASSERT_THROW(MatrixX::Identity(-1), std::out_of_range);
    ASSERT_THROW(MatrixX::Constant(1000, 2000, -1), std::out_of_range);
    ASSERT_THROW(MatrixX::Constant(1000, -1, -1), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, IsSizeValid)
{
    ASSERT_TRUE(MatrixX::IsSizeValid(10u, 5u));
    ASSERT_FALSE(MatrixX::IsSizeValid(256u, 5u));
    ASSERT_FALSE(MatrixX::IsSizeValid(5u, 256u));
    ASSERT_FALSE(MatrixX::IsSizeValid(256u, 256u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Matrix, SerializeDeserialize)
{
    holo::numerics::MatrixT<holo::float32_t, 3, 3> src, dst;
    for (size_t i = 0U; i < src.GetSize(); ++i)
    {
        src(i) = i;
    }

    uint8_t                           buffer[36];
    holo::serialization::Serializer<> serializer(buffer, 36);

    serializer << src;
    EXPECT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());

    deserializer >> dst;

    for (size_t i = 0U; i < src.GetSize(); ++i)
    {
        EXPECT_EQ(src(i), dst(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
