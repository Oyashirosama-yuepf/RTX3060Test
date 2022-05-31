#ifndef TEST_NUMERICS_MATRIX_TEST_VECTOR_BASE_OPERATIONS_H_
#define TEST_NUMERICS_MATRIX_TEST_VECTOR_BASE_OPERATIONS_H_

#include <gtest/gtest.h>
#include <holo/core/types.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

#include <cmath>

TEST(SUITENAME, BracketOperator)
{
    VectorType v = CreateSequenceMatrix();
    for (size_t i = 0; i < SizeValue; ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(i), v[i]);
        v[i] += static_cast<Scalar>(1);
        ASSERT_EQ(static_cast<Scalar>(i + 1), v[i]);
    }

    VectorType const c_v = CreateSequenceMatrix();
    for (size_t i = 0; i < SizeValue; ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(i), c_v[i]);
    }
}

TEST(SUITENAME, At)
{
    VectorType v = CreateSequenceMatrix();
    for (size_t i = 0; i < SizeValue; ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(i), v.At(i));
        v[i] += static_cast<Scalar>(1);
        ASSERT_EQ(static_cast<Scalar>(i + 1), v.At(i));
    }

    VectorType const c_v = CreateSequenceMatrix();
    for (size_t i = 0; i < SizeValue; ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(i), c_v.At(i));
    }
}

TEST(SUITENAME, Get)
{
    VectorType v = CreateSequenceMatrix();
#if RowValue > 0
    ASSERT_EQ(v(0), v.Get<0>());
#endif
#if RowValue > 1
    ASSERT_EQ(v(1), v.Get<1>());
#endif
#if RowValue > 2
    ASSERT_EQ(v(2), v.Get<2>());
#endif
}

TEST(SUITENAME, get)
{
    VectorType v = CreateSequenceMatrix();
#if RowValue > 0
    ASSERT_EQ(v(0), std::get<0>(v));
#endif
#if RowValue > 1
    ASSERT_EQ(v(1), std::get<1>(v));
#endif
#if RowValue > 2
    ASSERT_EQ(v(2), std::get<2>(v));
#endif
}

TEST(SUITENAME, Dot)
{
    VectorType v1  = CreateSequenceMatrix();
    VectorType v2  = CreateSequenceMatrix();
    Scalar     acc = static_cast<Scalar>(0);
    for (size_t i = 0; i < v1.GetSize(); ++i)
    {
        acc += static_cast<Scalar>(i * i);
    }
    ASSERT_EQ(acc, v1.Dot(v2));
}

TEST(SUITENAME, Normalize)
{
    VectorType v = CreateZeroMatrix();
    v.Normalize();
    for (size_t i = 0; i < v.GetSize(); ++i)
    {
        ASSERT_EQ(static_cast<Scalar>(0), v[i]);
    }

    VectorType v2 = CreateSequenceMatrix();
    v2.Foreach([](Scalar& value, size_t, size_t) -> void { value += static_cast<Scalar>(1); });
    v2.Normalize();

    Scalar sum = static_cast<Scalar>(0);
    for (size_t i = 0; i < SizeValue; ++i)
    {
        sum += v2(i) * v2(i);
    }
    ASSERT_NEAR(static_cast<Scalar>(1), sum, 1e-5);

    Scalar acc = static_cast<Scalar>(0);
    for (size_t i = 0; i < SizeValue; ++i)
    {
        acc += static_cast<Scalar>((i + 1) * (i + 1));
    }

    for (size_t i = 0; i < SizeValue; ++i)
    {
        ASSERT_NEAR(static_cast<Scalar>(i + 1) / std::sqrt(acc), v2[i], 1e-5);
    }
}

TEST(SUITENAME, GetSegment)
{
    VectorType v = CreateSequenceMatrix();

    for (size_t i = 0; i < SizeValue; ++i)
    {
        for (size_t j = 1; j < SizeValue + 1 - i; ++j)
        {
            DynamicVectorType dyn_v = v.GetSegment(i, j);
            for (size_t idx = 0; idx < j; ++idx)
            {
                ASSERT_EQ(v[i + idx], dyn_v[idx]);
            }
        }
    }
}

TEST(SUITENAME, SetSegment)
{
    VectorType v = CreateSequenceMatrix();

    for (size_t i = 0; i < SizeValue; ++i)
    {
        for (size_t j = 1; j < SizeValue + 1 - i; ++j)
        {
            v = CreateSequenceMatrix();
            DynamicVectorType dyn_v;
            dyn_v.Resize(j);
            dyn_v.Foreach([](Scalar& value, size_t, size_t) -> void { value = 0; });

            v.SetSegment(i, dyn_v);
            for (size_t idx = 0; idx < SizeValue; ++idx)
            {
                if (idx >= i && idx < i + j)
                {
                    ASSERT_EQ(static_cast<Scalar>(0), v[idx]);
                }
                else
                {
                    ASSERT_EQ(static_cast<Scalar>(idx), v[idx]);
                }
            }
        }
    }
}

TEST(SUITENAME, GetHead)
{
    VectorType v = CreateSequenceMatrix();

    for (size_t j = 1; j < SizeValue + 1; ++j)
    {
        DynamicVectorType dyn_v = v.GetHead(j);
        for (size_t idx = 0; idx < j; ++idx)
        {
            ASSERT_EQ(v[idx], dyn_v[idx]);
        }
    }
}

TEST(SUITENAME, SetHead)
{
    VectorType v = CreateSequenceMatrix();

    for (size_t j = 1; j < SizeValue + 1; ++j)
    {
        v = CreateSequenceMatrix();
        DynamicVectorType dyn_v;
        dyn_v.Resize(j);
        dyn_v.Foreach([](Scalar& value, size_t, size_t) -> void { value = 0; });

        v.SetHead(dyn_v);
        for (size_t idx = 0; idx < SizeValue; ++idx)
        {
            if (idx < j)
            {
                ASSERT_EQ(static_cast<Scalar>(0), v[idx]);
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(idx), v[idx]);
            }
        }
    }
}

TEST(SUITENAME, GetTail)
{
    VectorType v = CreateSequenceMatrix();

    for (size_t j = 1; j < SizeValue + 1; ++j)
    {
        DynamicVectorType dyn_v = v.GetTail(j);
        for (size_t idx = 0; idx < j; ++idx)
        {
            ASSERT_EQ(v[SizeValue - j + idx], dyn_v[idx]);
        }
    }
}

TEST(SUITENAME, SetTail)
{
    VectorType v = CreateSequenceMatrix();

    for (size_t j = 1; j < SizeValue + 1; ++j)
    {
        v = CreateSequenceMatrix();
        DynamicVectorType dyn_v;
        dyn_v.Resize(j);
        dyn_v.Foreach([](Scalar& value, size_t, size_t) -> void { value = 0; });

        v.SetTail(dyn_v);
        for (size_t idx = 0; idx < SizeValue; ++idx)
        {
            if (idx >= SizeValue - j)
            {
                ASSERT_EQ(static_cast<Scalar>(0), v[idx]);
            }
            else
            {
                ASSERT_EQ(static_cast<Scalar>(idx), v[idx]);
            }
        }
    }
}

#endif
