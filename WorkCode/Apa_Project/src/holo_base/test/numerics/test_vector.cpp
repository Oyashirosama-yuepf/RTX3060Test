/*!
 * @file test_vector.cpp
 * @brief vector unit test
 * @author Yanwei Du
 * @date July-09-2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/core/types.h>
#include <holo/numerics/vector.h>

using namespace holo::numerics;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ConstructFixedSizeVector)
{
    // create a vector
    const Vector2f vec;

    // check results
    ASSERT_EQ(2u, vec.GetRows());
    ASSERT_EQ(1u, vec.GetCols());
    ASSERT_EQ(2u, vec.GetSize());
}

TEST(Vector2f, CopyAssignment)
{
    Vector2f vec;
    Vector2f::BaseBase matrix;
    matrix(0,0) = 3.0f;
    matrix(1,0) = 4.0f;

    vec = matrix;
    ASSERT_EQ(3.0f, vec(0U));
    ASSERT_EQ(4.0f, vec(1U));

    Vector2f::Base base;
    base[0] = 5.0f;
    base[1] = 6.0f;
    vec = base;
    ASSERT_EQ(5.0f, vec(0U));
    ASSERT_EQ(6.0f, vec(1U));

    // create a vector
    Vector2f vec2(1.0f, 2.f);
    vec = vec2;
    ASSERT_EQ(1.0f, vec(0U));
    ASSERT_EQ(2.0f, vec(1U));
}

TEST(Vector3f, CopyAssignment)
{
    Vector3f vec;
    Vector3f::BaseBase matrix;
    matrix(0,0) = 3.0f;
    matrix(1,0) = 4.0f;
    matrix(2,0) = 5.0f;

    vec = matrix;
    ASSERT_EQ(3.0f, vec(0U));
    ASSERT_EQ(4.0f, vec(1U));
    ASSERT_EQ(5.0f, vec(2U));

    Vector3f::Base base;
    base[0] = 5.0f;
    base[1] = 6.0f;
    base[2] = 7.0f;

    vec = base;
    ASSERT_EQ(5.0f, vec(0U));
    ASSERT_EQ(6.0f, vec(1U));
    ASSERT_EQ(7.0f, vec(2U));

    Vector3f vec2(1.0f, 2.f, 3.0f);
    vec = vec2;
    ASSERT_EQ(1.0f, vec(0U));
    ASSERT_EQ(2.0f, vec(1U));
    ASSERT_EQ(3.0f, vec(2U));
}

TEST(VectorXf, CopyAssignment)
{
    VectorXf vec(5u);
    VectorXf::BaseBase matrix(3u, 1u);
    matrix(0,0) = 3.0f;
    matrix(1,0) = 4.0f;
    matrix(2,0) = 5.0f;

    vec = matrix;
    ASSERT_EQ(3u, vec.GetRows());
    ASSERT_EQ(3.0f, vec(0U));
    ASSERT_EQ(4.0f, vec(1U));
    ASSERT_EQ(5.0f, vec(2U));


    VectorXf::Base base(4u);
    base[0] = 5.0f;
    base[1] = 6.0f;
    base[2] = 7.0f;
    base[3] = 8.0f;

    vec = base;
    ASSERT_EQ(4u, vec.GetRows());
    ASSERT_EQ(5.0f, vec(0U));
    ASSERT_EQ(6.0f, vec(1U));
    ASSERT_EQ(7.0f, vec(2U));
    ASSERT_EQ(8.0f, vec(3U));

    VectorXf vec2(5u);
    vec2(0u) = 11.0f;
    vec2(1u) = 12.0f;
    vec2(2u) = 13.0f;
    vec2(3u) = 14.0f;
    vec2(4u) = 15.0f;
    vec = vec2;
    ASSERT_EQ(5u, vec.GetRows());
    ASSERT_EQ(11.0f, vec(0U));
    ASSERT_EQ(12.0f, vec(1U));
    ASSERT_EQ(13.0f, vec(2U));
    ASSERT_EQ(14.0f, vec(3U));
    ASSERT_EQ(15.0f, vec(4U));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ConstructDynamicVector)
{
    // create a vector
    const VectorX vec(10u);

    // check results
    ASSERT_EQ(10u, vec.GetRows());
    ASSERT_EQ(1u, vec.GetCols());
    ASSERT_EQ(10u, vec.GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ConstructDynamicVectorFromInvalidSize)
{
    ASSERT_THROW(const VectorX m(1000), std::out_of_range);
    ASSERT_THROW(const VectorX m(-1), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ConstructVector3)
{
    // create a vector
    const Vector3 vec(3.0, 2.0, 1.0);

    // check results
    ASSERT_EQ(3.0, vec(0u));
    ASSERT_EQ(2.0, vec(1u));
    ASSERT_EQ(1.0, vec(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ElementAssignment)
{
    // create a vector
    Vector5d vec;

    // assign value to vector
    for (uint8_t i = 0u; i < vec.GetSize(); i++)
    {
        vec[i] = i;
    }

    // check results
    for (uint8_t i = 0u; i < vec.GetSize(); i++)
    {
        ASSERT_EQ(i, vec(i));
        ASSERT_EQ(i, vec[i]);
    }

    const Vector5d vec2(5.0, 4.0, 3.0, 2.0, 1.0);
    for (uint8_t i = 0u; i < vec2.GetSize(); i++)
    {
        ASSERT_EQ(5.0 - i, vec2(i));
        ASSERT_EQ(5.0 - i, vec2[i]);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Transpose)
{
    // create a vector
    const Vector3 vec(1.0, 2.0, 3.0);

    // transpose a vector
    const RowVector3 vec_t = vec.Transpose();

    // check results
    ASSERT_EQ(1u, vec_t.GetRows());
    ASSERT_EQ(3u, vec_t.GetCols());
    for (uint8_t i = 0u; i < vec_t.GetRows(); i++)
    {
        ASSERT_EQ(vec_t(0u, i), vec(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Plus)
{
    // create a vector
    const Vector4f xvec(1.0f, 2.0f, 3.0f, 4.0f);
    const Vector4f yvec(5.0f, 6.0f, 7.0f, 8.0f);

    // call plus
    const Vector4f zvec = xvec + yvec;

    // check results
    ASSERT_EQ(6.0f, zvec(0u));
    ASSERT_EQ(8.0f, zvec(1u));
    ASSERT_EQ(10.0f, zvec(2u));
    ASSERT_EQ(12.0f, zvec(3u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Minus)
{
    // create a vector
    const Vector4f xvec(1.0f, 2.0f, 3.0f, 4.0f);
    const Vector4f yvec(5.0f, 6.0f, 7.0f, 8.0f);

    // call minus
    const Vector4f zvec = xvec - yvec;

    // check results
    ASSERT_EQ(-4.0f, zvec(0u));
    ASSERT_EQ(-4.0f, zvec(1u));
    ASSERT_EQ(-4.0f, zvec(2u));
    ASSERT_EQ(-4.0f, zvec(3u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, MultiplyScalar)
{
    // create a vector
    const holo::float64_t s = 2.0;
    const Vector4         xvec(1.0, 2.0, 3.0, 4.0);

    // call multiply
    const Vector4 yvec = xvec * s;
    const Vector4 zvec = s * xvec;

    // check results
    ASSERT_EQ(2.0, yvec(0u));
    ASSERT_EQ(4.0, yvec(1u));
    ASSERT_EQ(6.0, yvec(2u));
    ASSERT_EQ(8.0, yvec(3u));

    ASSERT_EQ(2.0, zvec(0u));
    ASSERT_EQ(4.0, zvec(1u));
    ASSERT_EQ(6.0, zvec(2u));
    ASSERT_EQ(8.0, zvec(3u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, MultiplyARowVector)
{
    // create a vector and a row vector
    const Vector4 xvec(1.0, 2.0, 3.0, 4.0);
    RowVector4    yvec;
    for (uint8_t i = 0u; i < 4u; i++)
    {
        yvec(i) = i + 1.0;
    }

    // call multiply
    const Matrix4 zmat = xvec * yvec;

    // check results
    for (uint8_t i = 0u; i < xvec.GetRows(); i++)
    {
        for (uint8_t j = 0u; j < yvec.GetCols(); j++)
        {
            const holo::float64_t val = xvec(i) * yvec(j);
            ASSERT_EQ(val, zmat(i, j));
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, NormAndSquaredNorm)
{
    // create a vector
    const Vector6 vec(0.0, 1.0, 2.0, 3.0, 4.0, 5.0);

    // call norm and sq_norm
    const holo::float64_t norm    = vec.GetNorm();
    const holo::float64_t sq_norm = vec.GetSquaredNorm();

    // check results
    ASSERT_NEAR(7.4162, norm, 1e-4);  // 7.416198487
    ASSERT_EQ(55.0, sq_norm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Dot)
{
    // create a vector
    const Vector2 xvec(1.0, 2.0);
    const Vector2 yvec(5.0, 6.0);

    // call dot
    const holo::float64_t result = xvec.Dot(yvec);

    // check results
    ASSERT_EQ(17.0, result);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Cross)
{
    // create two vectors
    const Vector3 xvec(1.0, 2.0, 3.0);
    const Vector3 yvec(3.0, 2.0, 1.0);

    // call cross
    Vector3 zvec = xvec.Cross(yvec);

    // check results
    ASSERT_EQ(-4.0, zvec(0u));
    ASSERT_EQ(8.0, zvec(1u));
    ASSERT_EQ(-4.0, zvec(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, At)
{
    // create vectors
    const Vector3 vec(1.0, 2.0, 3.0);

    // check results
    ASSERT_EQ(1.0, vec.At(0u));
    ASSERT_EQ(2.0, vec.At(1u));
    ASSERT_EQ(3.0, vec.At(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, AtReference)
{
    Vector3 vec(1.0, 2.0, 3.0);
    vec.At(0u) = 2.0;
    vec.At(1u) = 3.0;
    vec.At(2u) = 4.0;

    // check results
    ASSERT_EQ(2.0, vec.At(0u));
    ASSERT_EQ(3.0, vec.At(1u));
    ASSERT_EQ(4.0, vec.At(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, At2)
{
    // create vectors
    const Vector2 vec(1.0, 2.0);

    // check results
    ASSERT_EQ(1.0, vec.At(0u));
    ASSERT_EQ(2.0, vec.At(1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, AtReference2)
{
    Vector2 vec(1.0, 2.0);
    vec.At(0u) = 2.0;
    vec.At(1u) = 3.0;

    // check results
    ASSERT_EQ(2.0, vec.At(0u));
    ASSERT_EQ(3.0, vec.At(1u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, At3)
{
    // create vectors
    const VectorXd vec(4u);

    // check results
    ASSERT_EQ(0.0, vec.At(0u));
    ASSERT_EQ(0.0, vec.At(1u));
    ASSERT_EQ(0.0, vec.At(2u));
    ASSERT_EQ(0.0, vec.At(3u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, AtReference3)
{
    // create vectors
    VectorXd vec(4u);

    // assignment
    vec(0u) = 0.0;
    vec(1u) = -1.0;
    vec(2u) = 2.0;
    vec(3u) = -3.0;

    // check results
    ASSERT_EQ(0.0, vec.At(0u));
    ASSERT_EQ(-1.0, vec.At(1u));
    ASSERT_EQ(2.0, vec.At(2u));
    ASSERT_EQ(-3.0, vec.At(3u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ToSkewSymmetric)
{
    // case 1, fixed size matrix
    const Vector3 xvec(1.0, 2.0, 3.0);

    // call method
    const Matrix3 xmat = xvec.ToSkewSymmetric();

    // check results
    ASSERT_EQ(0.0, xmat(0u, 0u));
    ASSERT_EQ(-3.0, xmat(0u, 1u));
    ASSERT_EQ(2.0, xmat(0u, 2u));
    ASSERT_EQ(3.0, xmat(1u, 0u));
    ASSERT_EQ(0.0, xmat(1u, 1u));
    ASSERT_EQ(-1.0, xmat(1u, 2u));
    ASSERT_EQ(-2.0, xmat(2u, 0u));
    ASSERT_EQ(1.0, xmat(2u, 1u));
    ASSERT_EQ(0.0, xmat(2u, 2u));

    // case 2, dynamic size vector
    VectorX yvec(3u);
    yvec(0) = 3.0;
    yvec(1) = 2.0;
    yvec(2) = 1.0;

    const Matrix3 ymat = yvec.ToSkewSymmetric();
    ASSERT_EQ(0.0, ymat(0u, 0u));
    ASSERT_EQ(-1.0, ymat(0u, 1u));
    ASSERT_EQ(2.0, ymat(0u, 2u));
    ASSERT_EQ(1.0, ymat(1u, 0u));
    ASSERT_EQ(0.0, ymat(1u, 1u));
    ASSERT_EQ(-3.0, ymat(1u, 2u));
    ASSERT_EQ(-2.0, ymat(2u, 0u));
    ASSERT_EQ(3.0, ymat(2u, 1u));
    ASSERT_EQ(0.0, ymat(2u, 2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, AsDiagonal)
{
    // case 1, fixed size matrix
    const Vector3 xvec(1.0, 2.0, 3.0);

    // call method
    const Matrix3 xmat = xvec.AsDiagonal();

    // check results
    ASSERT_EQ(1.0, xmat(0u, 0u));
    ASSERT_EQ(0.0, xmat(0u, 1u));
    ASSERT_EQ(0.0, xmat(0u, 2u));
    ASSERT_EQ(0.0, xmat(1u, 0u));
    ASSERT_EQ(2.0, xmat(1u, 1u));
    ASSERT_EQ(0.0, xmat(1u, 2u));
    ASSERT_EQ(0.0, xmat(2u, 0u));
    ASSERT_EQ(0.0, xmat(2u, 1u));
    ASSERT_EQ(3.0, xmat(2u, 2u));

    // case 2, dynamic size vector
    VectorX yvec(3u);
    yvec(0) = 3.0;
    yvec(1) = 2.0;
    yvec(2) = 1.0;

    const Matrix3 ymat = yvec.AsDiagonal();
    ASSERT_EQ(3.0, ymat(0u, 0u));
    ASSERT_EQ(0.0, ymat(0u, 1u));
    ASSERT_EQ(0.0, ymat(0u, 2u));
    ASSERT_EQ(0.0, ymat(1u, 0u));
    ASSERT_EQ(2.0, ymat(1u, 1u));
    ASSERT_EQ(0.0, ymat(1u, 2u));
    ASSERT_EQ(0.0, ymat(2u, 0u));
    ASSERT_EQ(0.0, ymat(2u, 1u));
    ASSERT_EQ(1.0, ymat(2u, 2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Resize)
{
    // create vector
    VectorX vec(6u);
    vec.Resize(10u);

    // check results
    ASSERT_EQ(10u, vec.GetRows());
    ASSERT_EQ(1u, vec.GetCols());
    ASSERT_EQ(10u, vec.GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ResizeWithInvalidSize)
{
    // create vector
    VectorX vec(6u);

    // check results
    ASSERT_THROW(vec.Resize(1000), std::out_of_range);
    ASSERT_THROW(vec.Resize(-1), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, DynamicSizeSegment)
{
    // create vector
    VectorXd vec(10u);
    for (uint16_t i = 0u; i < vec.GetSize(); i++)
    {
        vec(i) = i;
    }

    // call method and check result
    const uint16_t index   = 6u;
    const uint16_t length  = 4u;
    VectorXd       segment = vec.GetSegment(index, length);
    for (uint16_t i = 0; i < segment.GetSize(); i++)
    {
        const holo::float64_t value = i + index;
        ASSERT_EQ(value, segment(i));
    }

    // call method and check result
    vec.SetSegment(0u, segment);
    for (uint16_t i = 0u; i < vec.GetSize(); i++)
    {
        const holo::float64_t value = (i < segment.GetSize()) ? (i + index) : i;
        ASSERT_EQ(value, vec(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, FixedSizeSegment)
{
    // create vector
    VectorXd vec(10u);
    for (uint16_t i = 0u; i < vec.GetSize(); i++)
    {
        vec(i) = i;
    }

    // call method and check result
    const uint16_t index   = 6u;
    const uint16_t length  = 4u;
    Vector4d       segment = vec.GetSegment(index, length);
    for (uint16_t i = 0u; i < segment.GetSize(); i++)
    {
        const holo::float64_t value = i + index;
        ASSERT_EQ(value, segment(i));
    }

    // call method and check result
    vec.SetSegment(0u, segment);
    for (uint16_t i = 0u; i < vec.GetSize(); i++)
    {
        const holo::float64_t value = (i < segment.GetSize()) ? (i + index) : i;
        ASSERT_EQ(value, vec(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Head)
{
    // create vector
    VectorXd vec(10u);
    for (uint16_t i = 0u; i < vec.GetSize(); i++)
    {
        vec(i) = i;
    }

    // call method and check result
    const uint16_t length = 4u;
    const VectorXd head1  = vec.GetHead(length);
    const Vector4d head2  = vec.GetHead(length);
    for (uint16_t i = 0u; i < head1.GetSize(); i++)
    {
        const holo::float64_t value = i;
        ASSERT_EQ(value, head1(i));
        ASSERT_EQ(value, head2(i));
    }

    // call method and check result
    VectorXd vec2(10u);
    vec2.SetZero();
    vec2.SetHead(head1);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < head1.GetSize()) ? i : 0.0;
        ASSERT_EQ(value, vec2(i));
    }

    vec2.SetZero();
    vec2.SetHead(head2);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < head2.GetSize()) ? i : 0.0;
        ASSERT_EQ(value, vec2(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, FixedSizeHead)
{
    // create vector
    const Vector6d vec(1.0, -2.0, 3.0, -4.0, 5.0, -6.0);

    // call method and check result
    const uint16_t length = 4u;
    const VectorXd head1  = vec.GetHead(length);
    const Vector4d head2  = vec.GetHead(length);
    for (uint16_t i = 0u; i < head1.GetSize(); i++)
    {
        const holo::float64_t value = vec(i);
        ASSERT_EQ(value, head1(i));
        ASSERT_EQ(value, head2(i));
    }

    // call method and check result
    Vector6d vec2;
    vec2.SetHead(head1);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < head1.GetSize()) ? head1(i) : 0.0;
        ASSERT_EQ(value, vec2(i));
    }

    vec2.SetZero();
    vec2.SetHead(head2);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < head2.GetSize()) ? head2(i) : 0.0;
        ASSERT_EQ(value, vec2(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, Tail)
{
    // create vector
    VectorXd vec(10u);
    for (uint16_t i = 0u; i < vec.GetSize(); i++)
    {
        vec(i) = i;
    }

    // call method and check result
    const uint16_t length = 4u;
    const VectorXd tail1  = vec.GetTail(length);
    const Vector4d tail2  = vec.GetTail(length);
    for (uint16_t i = 0u; i < tail1.GetSize(); i++)
    {
        const holo::float64_t value = vec.GetSize() - length + i;
        ASSERT_EQ(value, tail1(i));
        ASSERT_EQ(value, tail2(i));
    }

    // call method and check result
    VectorXd vec2(10u);
    vec2.SetZero();
    vec2.SetTail(tail1);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < (vec2.GetSize() - tail1.GetSize())) ? 0.0 : i;
        ASSERT_EQ(value, vec2(i));
    }

    vec2.SetZero();
    vec2.SetTail(tail2);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < (vec2.GetSize() - tail2.GetSize())) ? 0u : i;
        ASSERT_EQ(value, vec2(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, FixedSizeTail)
{
    // create vector
    const Vector6d vec(1.0, -2.0, 3.0, -4.0, 5.0, -6.0);

    // call method and check result
    const uint16_t length = 4u;
    const VectorXd tail1  = vec.GetTail(length);
    const Vector4d tail2  = vec.GetTail(length);
    for (uint16_t i = 0u; i < tail1.GetSize(); i++)
    {
        const holo::float64_t value = vec(vec.GetSize() - length + i);
        ASSERT_EQ(value, tail1(i));
        ASSERT_EQ(value, tail2(i));
    }

    // call method and check result
    Vector6d vec2;
    vec2.SetTail(tail1);
    const uint16_t diff_length = vec2.GetSize() - tail1.GetSize();
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < diff_length) ? 0.0 : tail1(i - diff_length);
        ASSERT_EQ(value, vec2(i));
    }

    vec2.SetZero();
    vec2.SetTail(tail2);
    for (uint16_t i = 0u; i < vec2.GetSize(); i++)
    {
        const holo::float64_t value = (i < diff_length) ? 0.0 : tail2(i - diff_length);
        ASSERT_EQ(value, vec2(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, DynamicZero)
{
    // create matrix
    const VectorX v = VectorX::Zero(10u);

    // check results
    ASSERT_EQ(10u, v.GetSize());
    for (uint32_t i = 0u; i < v.GetSize(); i++)
    {
        ASSERT_EQ(0.0, v(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, DynamicOne)
{
    // create matrix
    const VectorX v = VectorX::One(5u);

    // check results
    ASSERT_EQ(5u, v.GetSize());
    for (uint32_t i = 0u; i < v.GetSize(); i++)
    {
        ASSERT_EQ(1.0, v(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, DynamicConstant)
{
    // create matrix
    const VectorX v = VectorX::Constant(3u, -1.0);

    // check results
    ASSERT_EQ(3u, v.GetSize());
    for (uint32_t i = 0u; i < v.GetSize(); i++)
    {
        ASSERT_EQ(-1.0, v(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, ConstructSpecialVectorWithInvalidSize)
{
    ASSERT_THROW(VectorX::Zero(-1), std::out_of_range);
    ASSERT_THROW(VectorX::Zero(1000), std::out_of_range);
    ASSERT_THROW(VectorX::One(-1), std::out_of_range);
    ASSERT_THROW(VectorX::One(1000), std::out_of_range);
    ASSERT_THROW(VectorX::Constant(-1, -1), std::out_of_range);
    ASSERT_THROW(VectorX::Constant(1000, -1), std::out_of_range);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, DynamicSizeVectorToFixedSizeVector_1)
{
    VectorXf d_vec(5u);
    {
        d_vec(2u) = 2.0f;
        d_vec(4u) = -4.0f;
    }

    // call methods
    const Vector5f f_vec1 = d_vec;
    Vector5f       f_vec2;
    f_vec2 = d_vec;

    // check results
    ASSERT_EQ(f_vec1.GetSize(), d_vec.GetSize());
    ASSERT_EQ(f_vec2.GetSize(), d_vec.GetSize());
    for (uint16_t index = 0u; index < d_vec.GetSize(); index++)
    {
        ASSERT_EQ(f_vec1(index), d_vec(index));
        ASSERT_EQ(f_vec2(index), d_vec(index));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, DynamicSizeVectorToFixedSizeVector_2)
{
    VectorXf d_vec(3u);
    {
        d_vec(0u) = -0.0f;
        d_vec(1u) = 1.0f;
        d_vec(2u) = -2.0f;
    }

    // call methods
    const Vector3f f_vec1 = d_vec;
    Vector3f       f_vec2;
    f_vec2 = d_vec;

    // check results
    ASSERT_EQ(f_vec1.GetSize(), d_vec.GetSize());
    ASSERT_EQ(f_vec2.GetSize(), d_vec.GetSize());
    for (uint16_t index = 0u; index < d_vec.GetSize(); index++)
    {
        ASSERT_EQ(f_vec1(index), d_vec(index));
        ASSERT_EQ(f_vec2(index), d_vec(index));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Vector, IsSizeValid)
{
    ASSERT_TRUE(VectorX::IsSizeValid(10u));
    ASSERT_FALSE(VectorX::IsSizeValid(256u));
}

TEST(Vector, SerializeDeserialize)
{
    holo::numerics::VectorT<holo::float32_t, 3> src, dst;
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

TEST(Vector, GetSegmentException)
{
    VectorXd vec(1u);
    vec(0) = 1;
    try
    {
        Vector4d segment = vec.GetSegment(3U, 5U);
    }
    catch (...)
    {
    }
}

TEST(Vector, GetAndSetTailException)
{
    VectorXd vec(1u);
    vec(0) = 1;

    try
    {
        const VectorXd tail1 = vec.GetTail(4u);
    }
    catch (...)
    {
    }
    const VectorXd tail1 = vec.GetTail(1u);
    try
    {
        vec.SetTail(tail1);
        vec.SetTail(tail1);
    }
    catch (...)
    {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
