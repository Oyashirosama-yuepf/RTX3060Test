/*!
 * @file test_point3.cpp
 * @brief Unit test for Point3.h
 * @author Li Chao
 * @date 2017-07-12
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>

using namespace holo;
using holo::numerics::Vector3f;
///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Equal)
{
    holo::geometry::Point3f p, q(1e-10f, 1e-10f, 1e-10f);
    Vector3f                r(0.0f, 0.0f, 0.0f);
    holo::geometry::Point3f s(q), t(r);
    ASSERT_EQ(p.IsEqual(q, 1e-5f), true);
    ASSERT_EQ(p == t, true);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Add)
{
    holo::geometry::Point3d p(1.0, 2.0, 1.0), q(3.0, 4.0, 3.0);
    holo::geometry::Point3d v(5.0, 6.0, 5.0);
    holo::geometry::Point3d r = p + q;
    holo::geometry::Point3d s = p + v;
    p += q;
    q += v;
    ASSERT_EQ(r.GetX(), 4.0);
    ASSERT_EQ(s.GetY(), 8.0);
    ASSERT_EQ(s.GetZ(), 6.0);
    ASSERT_EQ(p.GetX(), 4.0);
    ASSERT_EQ(q.GetY(), 10.0);
    ASSERT_EQ(q.GetZ(), 8.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Sub)
{
    holo::geometry::Point3d p(1.0, 2.0, 1.0), q(3.0, 4.0, 3.0);
    holo::geometry::Point3d v(5.0, 6.0, 5.0);
    holo::geometry::Point3d r = p - q;
    holo::geometry::Point3d s = q - v;
    p -= v;
    holo::geometry::Point3d t = -q;
    ASSERT_EQ(r.GetX(), -2.0);
    ASSERT_EQ(s.GetY(), -2.0);
    ASSERT_EQ(s.GetZ(), -2.0);
    ASSERT_EQ(p.GetX(), -4.0);
    ASSERT_EQ(t.GetY(), -4.0);
    ASSERT_EQ(t.GetZ(), -3.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Mul)
{
    holo::geometry::Point3d p(1.0, 2.0, 1.0);
    float64_t               s = 3.0;
    holo::geometry::Point3d q = s * p;
    ASSERT_EQ(q.GetX(), 3.0);
    ASSERT_EQ(q.GetY(), 6.0);
    ASSERT_EQ(q.GetZ(), 3.0);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Div)
{
    holo::geometry::Point3d p(1.0, 2.0, 1.0);
    float64_t               s = 4.0;
    holo::geometry::Point3d q = p / s;
    ASSERT_EQ(q.GetX(), 0.25);
    ASSERT_EQ(q.GetY(), 0.5);
    ASSERT_EQ(q.GetZ(), 0.25);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, operatorRemainder)
{
    holo::geometry::Point3d p1(1.0, 2.0, 1.0);
    try
    {
        p1 = p1 / 0;
    }
    catch(...)
    {
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Dist)
{
    holo::geometry::Point3d p(1.0, 2.0, 1.0);
    holo::geometry::Point3d q(2.0, 4.0, 2.0);
    float64_t               d1 = p.DistSqr(q);
    float64_t               d2 = p.Dist(q);
    float64_t               c  = std::sqrt(6.0);
    ASSERT_EQ(d1, 6.0);
    ASSERT_EQ(d2, c);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, Prop)
{
    holo::geometry::Point3d p(1.0, 2.0, 1.0);
    uint8_t                 d = 3u;
    ASSERT_EQ(p.IsFinite(), true);
    ASSERT_EQ(p.GetX(), 1.0);
    ASSERT_EQ(p.GetY(), 2.0);
    ASSERT_EQ(p.GetZ(), 1.0);
    ASSERT_EQ(holo::geometry::Point3d::Dim(), d);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, IsZero)
{
    holo::geometry::Point3d p1(0.0, 0.0, 0.0);
    holo::geometry::Point3d p2(1.0, 1.0, 1.0);
    ASSERT_EQ(p1.IsZero(), true);
    ASSERT_EQ(p2.IsZero(), false);
}

///////////////////////////////////////////////////////////////////////////////

TEST(Point3UnitTest, As)
{
    holo::geometry::Point3d p(1.0, 2.0, 3.0);
    holo::numerics::Vector3d v = p.As<holo::numerics::Vector3d>();
    EXPECT_EQ(1.0, v(0));
    EXPECT_EQ(2.0, v(1));
    EXPECT_EQ(3.0, v(2));
    holo::numerics::Vector2d v2 = p.As<holo::numerics::Vector2d>();
    EXPECT_EQ(1.0, v2(0));
    EXPECT_EQ(2.0, v2(1));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Point3UnitTest, AssignmentPoint2d)
{
    holo::geometry::Point3d p1(1.0, 2.0, 0.0);
    holo::geometry::Point2d p2(1.0, 2.0);
    holo::geometry::Point3d p3(p2);
    ASSERT_EQ(p1, p3);
}

TEST(Point3UnitTest, GetSerializedSize)
{
    holo::geometry::Point3d p1(1.0, 2.0, 0.0);
    ASSERT_EQ(24, p1.GetSerializedSize<4U>());
    ASSERT_EQ(24, p1.GetSerializedSize<8U>());
}

TEST(Point3UnitTest, SerializeAndDeserialize)
{
    srand(time(0));

    holo::geometry::Point3f input_pf((float32_t)(rand() % 1000), (float32_t)(rand() % 1000),
                                     (float32_t)(rand() % 1000));

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);

    serializer << input_pf;
    ASSERT_EQ(input_pf.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    holo::geometry::Point3f     output_pf;
    deserializer >> output_pf;

    ASSERT_EQ(input_pf.GetX(), output_pf.GetX());
    ASSERT_EQ(input_pf.GetY(), output_pf.GetY());
    ASSERT_EQ(input_pf.GetZ(), output_pf.GetZ());
}

TEST(Point3, Get)
{
    holo::geometry::Point3d pt(1.0, 2.0, 3.0);
    ASSERT_EQ(1.0, pt.Get<0>());
    ASSERT_EQ(2.0, pt.Get<1>());
    ASSERT_EQ(3.0, pt.Get<2>());
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
