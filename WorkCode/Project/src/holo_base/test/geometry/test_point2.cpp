/*!
 * @file test_point2.h
 * @brief Unit test for Point2.h
 * @author Li Chao
 * @date 2017-07-07
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/point2.h>
#include <holo/numerics/vector.h>

#include <cmath>

using namespace holo;
using holo::numerics::Vector2f;

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Equal)
{
    holo::geometry::Point2f  p, q(0.0f, 0.0f);
    Vector2f r(0.0f, 0.0f);
    holo::geometry::Point2f  s(q), t(r);
    ASSERT_EQ(p.IsEqual(q, 1e-5f), true);
    ASSERT_EQ(q.IsEqual(s, 1e-5f), true);
    ASSERT_EQ(q.IsEqual(t, 1e-5f), true);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Add)
{
    holo::geometry::Point2d p(1.0, 2.0), q(3.0, 4.0);
    holo::geometry::Point2d v(5.0, 6.0);
    holo::geometry::Point2d r = p + q;
    holo::geometry::Point2d s = p + v;
    p += q;
    q += v;
    ASSERT_EQ(r.GetX(), 4.0);
    ASSERT_EQ(s.GetY(), 8.0);
    ASSERT_EQ(p.GetX(), 4.0);
    ASSERT_EQ(q.GetY(), 10.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Sub)
{
    holo::geometry::Point2d p(1.0, 2.0), q(3.0, 4.0);
    holo::geometry::Point2d v(5.0, 6.0);
    holo::geometry::Point2d r = p - q;
    holo::geometry::Point2d s = q - v;
    p -= v;
    holo::geometry::Point2d t = -q;
    ASSERT_EQ(r.GetX(), -2.0);
    ASSERT_EQ(s.GetY(), -2.0);
    ASSERT_EQ(p.GetX(), -4.0);
    ASSERT_EQ(t.GetY(), -4.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Mul)
{
    holo::geometry::Point2d   p(1.0, 2.0);
    float64_t s = 3.0;
    holo::geometry::Point2d   q = s * p;
    ASSERT_EQ(q.GetX(), 3.0);
    ASSERT_EQ(q.GetY(), 6.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Div)
{
    holo::geometry::Point2d   p(1.0, 2.0);
    float64_t s = 4.0;
    holo::geometry::Point2d   q = p / s;
    ASSERT_EQ(q.GetX(), 0.25);
    ASSERT_EQ(q.GetY(), 0.5);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Dist)
{
    holo::geometry::Point2d   p(1.0, 2.0);
    holo::geometry::Point2d   q(2.0, 4.0);
    float64_t d1 = p.DistSqr(q);
    float64_t d2 = p.Dist(q);
    float64_t c  = std::sqrt(5.0);
    ASSERT_EQ(d1, 5.0);
    ASSERT_EQ(d2, c);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, Prop)
{
    holo::geometry::Point2d p(1.0, 2.0);
    uint8_t d = 2u;
    ASSERT_EQ(p.IsFinite(), true);
    ASSERT_EQ(p.GetX(), 1.0);
    ASSERT_EQ(p.GetY(), 2.0);
    ASSERT_EQ(holo::geometry::Point2d::Dim(), d);
}

TEST(Point2UnitTest, As)
{
    holo::geometry::Point2d p1(1.0, 2.0);
    holo::numerics::Vector2d v = p1.As<holo::numerics::Vector2d>();
    EXPECT_EQ(1.0, v(0));
    EXPECT_EQ(2.0, v(1));
    holo::numerics::Vector3d v2 = p1.As<holo::numerics::Vector3d>();
    EXPECT_EQ(1.0, v2(0));
    EXPECT_EQ(2.0, v2(1));
    EXPECT_EQ(0.0, v2(2));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, PoinxXY)
{
    holo::geometry::Point2d p(1.0, 2.0);
    ASSERT_TRUE(p == p.GetPointXY());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, ZValue)
{
    holo::geometry::Point2d p1(1.0, 2.0);
    holo::geometry::Point2d p2(1.0, 2.0, 3.0);
    ASSERT_TRUE(p1 == p2);
    ASSERT_FLOAT_EQ(p1.GetZ(), 0.0);
    ASSERT_FLOAT_EQ(p2.GetZ(), 0.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, OutputOperator)
{
    holo::geometry::Point2d p1(1.0, 2.0);
    std::cout << p1;
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, operatorRemainder)
{
    holo::geometry::Point2d p1(1.0, 2.0);
    try
    {
        p1 = p1 / 0;
    }
    catch(...)
    {
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point2UnitTest, ToString)
{
    holo::geometry::Point2d p1(1.0, 2.0);
    p1.ToString();
}

TEST(Point2, SerializeDeserialize)
{
    holo::geometry::Point2f src{1.0f, 2.0f};
    holo::geometry::Point2f dst;
    uint8_t buffer[128];
    holo::serialization::Serializer<>          ser(buffer, 128);

    ser << src;
    ASSERT_EQ(src.GetSerializedSize(), ser.GetSize());

    holo::serialization::Deserializer<> des(buffer, ser.GetSize());
    des >> dst;

    EXPECT_EQ(dst[0U], src[0U]);
    EXPECT_EQ(dst[1U], src[1U]);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
