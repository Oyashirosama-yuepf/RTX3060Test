/*!
 * @file test_rot2.cpp
 * @brief unit test for rot2
 * @author duyanwei@holomatic.com
 * @date 2017-07-12
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/rot2.h>

using namespace holo;
using holo::numerics::Vector2;
using holo::numerics::Vector2d;
using holo::numerics::Matrix2;

const float64_t kTol = 1e-8;

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, RotatePoint2d)
{
    holo::geometry::Rot2d   R = holo::geometry::Rot2d::FromDegree(90.0);
    holo::geometry::Point2d p(10.0, 0.0);
    holo::geometry::Point2d q = R.Rotate(p);

    // check results
    ASSERT_NEAR(q.GetX(), 0.0, kTol);
    ASSERT_NEAR(q.GetY(), 10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, UnRotatePoint2d)
{
    holo::geometry::Rot2d   R = holo::geometry::Rot2d::FromDegree(90.0);
    holo::geometry::Point2d p(10.0, 0.0);
    holo::geometry::Point2d q = R.Unrotate(p);

    // check results
    ASSERT_NEAR(q.GetX(), 0.0, kTol);
    ASSERT_NEAR(q.GetY(), -10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, RotateVector2)
{
    holo::geometry::Rot2d   R = holo::geometry::Rot2d::FromDegree(90.0);
    Vector2 p = Vector2d(10.0, 0.0);
    Vector2 q = R.Rotate(p);

    // check results
    ASSERT_NEAR(q(0u), 0.0, kTol);
    ASSERT_NEAR(q(1u), 10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, UnRotateVector2)
{
    holo::geometry::Rot2d   R = holo::geometry::Rot2d::FromDegree(90.0);
    Vector2 p = Vector2d(10.0, 0.0);
    Vector2 q = R.Unrotate(p);

    // check results
    ASSERT_NEAR(q(0u), 0.0, kTol);
    ASSERT_NEAR(q(1u), -10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, OperatorTimesPoint)
{
    holo::geometry::Rot2d   R = holo::geometry::Rot2d::FromDegree(90.0);
    holo::geometry::Point2d p(10.0, 0.0);
    holo::geometry::Point2d q = R * p;

    // check results
    ASSERT_NEAR(q.GetX(), 0.0, kTol);
    ASSERT_NEAR(q.GetY(), 10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, OperatorTimesVector)
{
    holo::geometry::Rot2d    R = holo::geometry::Rot2d::FromDegree(90.0);
    Vector2d p(10.0, 0.0);
    Vector2d q = R * p;

    // check results
    ASSERT_NEAR(q(0u), 0.0, kTol);
    ASSERT_NEAR(q(1u), 10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, OperatorTimesRotation)
{
    const holo::geometry::Rot2d R1 = holo::geometry::Rot2d::FromDegree(45.0);
    const holo::geometry::Rot2d R2 = holo::geometry::Rot2d::FromDegree(45.0);

    // call method
    const holo::geometry::Rot2d actual = R1 * R2;

    // check results
    const holo::geometry::Rot2d expected(Matrix2(0.0, -1.0, 1.0, 0.0));
    ASSERT_EQ(expected, actual);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, Matrix2)
{
    holo::geometry::Rot2d   R = holo::geometry::Rot2d::FromDegree(90.0);
    Matrix2 M = R.ToMatrix();

    // check results
    ASSERT_NEAR(M(0u, 0u), 0.0, kTol);
    ASSERT_NEAR(M(0u, 1u), -1.0, kTol);
    ASSERT_NEAR(M(1u, 0u), 1.0, kTol);
    ASSERT_NEAR(M(1u, 1u), 0.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2dTest, Cast)
{
    holo::geometry::Rot2d r1 = holo::geometry::Rot2d::FromDegree(33.0);
    holo::geometry::Rot2f r2 = (holo::geometry::Rot2f)r1;
    ASSERT_FLOAT_EQ(r2.GetTheta(), holo::geometry::Radian(33.0f));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2fTest, FromMatrix2)
{
    holo::geometry::Rot2f p = holo::geometry::Rot2f::FromDegree(33.0f);
    holo::geometry::Rot2f q(p.ToMatrix());

    ASSERT_TRUE(p.IsEqual(q));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2, SerializeDeserialize)
{
    holo::geometry::Rot2f   src, dst;
    src = Rot2f(Matrix2f(0.0f, -1.0f, 1.0f, 0.0f));
    uint8_t buffer[8];
    holo::serialization::Serializer<> serializer(buffer, 8);
    serializer << src;

    EXPECT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;

    EXPECT_EQ(dst, src);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot2fTest, Normalize)
{
    holo::numerics::Matrix2f matrix(1.0, -2.0, 3.0, -4.0);
    holo::geometry::Rot2f q(matrix);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
