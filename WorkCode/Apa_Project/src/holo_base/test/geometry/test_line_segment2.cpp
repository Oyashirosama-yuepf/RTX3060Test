/*!
 * @file test_line_segment2.cpp
 * @brief unit test for line segment 2
 * @author Evan.Du
 * @date 2017-07-17
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/line_segment2.h>

using namespace holo;
using holo::numerics::Vector2f;
using holo::numerics::Vector4f;
using holo::numerics::Vector4d;

///////////////////////////////////////////////////////////////////////////////
holo::geometry::Point2f         p11(-1.0f, 0.0f), p12(1.0f, 2.0f);
holo::geometry::Point2f         p21(1.0f, 0.0f), p22(0.0f, 1.0f);
holo::geometry::LineSegment2f   ls1(p11, p12), ls2(p21, p22), ls3(p12, p11);
const float32_t tolf = EpsilonT<float32_t>::value;

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Contains)
{
    // inside
    ASSERT_FALSE(ls1.Contains(p21));
    ASSERT_TRUE(ls1.Contains(p22));

    // outsider
    holo::geometry::Point2f pt(1.1f, 2.1f);
    ASSERT_FALSE(ls1.Contains(pt));
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Dist)
{
    ASSERT_NEAR(ls1.Dist(p21), std::sqrt(2.0f), tolf);
    ASSERT_NEAR(ls1.Dist(p22), 0.0f, tolf);

    holo::geometry::Point2f pt(1.1f, 2.1f);
    ASSERT_NEAR(ls1.Dist(pt), std::sqrt(2.0f) * 0.1f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Project)
{
    holo::geometry::Point2f p21_p = ls1.Project(p21);
    holo::geometry::Point2f p22_p = ls1.Project(p21);

    holo::geometry::Point2f p12_p = ls1.Project(p12);

    holo::geometry::Point2f pt(-2.0f, 0.0f);
    holo::geometry::Point2f pt_p = ls1.Project(pt);

    ASSERT_TRUE(p21_p.IsEqual(holo::geometry::Point2f(0.0f, 1.0f)));
    ASSERT_TRUE(p22_p.IsEqual(holo::geometry::Point2f(0.0f, 1.0f)));
    ASSERT_TRUE(p12_p.IsEqual(holo::geometry::Point2f(1.0f, 2.0f)));
    ASSERT_TRUE(pt_p.IsEqual(holo::geometry::Point2f(-1.0f, 0.0f)));
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, IsEqual)
{
    ASSERT_FALSE(ls1.IsEqual(ls2, 1e-5f));
    ASSERT_FALSE(ls1.IsEqual(ls3, 1e-5f));
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, IsParallel)
{
    ASSERT_FALSE(ls1.IsParallel(ls2, 1e-7f));
    ASSERT_TRUE(ls1.IsParallel(ls3, 1e-7f));
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Intersect)
{
    // construct a line segment that is parallel to ls2
    holo::geometry::LineSegment2f ls4(p21, holo::geometry::Point2f(2.0f, -1.0f));

    holo::geometry::Point2f pt;
    ASSERT_TRUE(ls1.Intersect(ls2, pt));
    ASSERT_NEAR(pt.GetX(), p22.GetX(), tolf);
    ASSERT_NEAR(pt.GetY(), p22.GetY(), tolf);
    ASSERT_FALSE(ls1.Intersect(ls4, pt));
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Normal)
{
    Vector2f n1 = ls1.GetNormal(), n2 = ls2.GetNormal();
    ASSERT_NEAR(n1(0u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(n1(1u), -std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(n2(0u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(n2(1u), std::sqrt(2.0f) / 2.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Direction)
{
    Vector2f d1 = ls1.GetDirection(), d2 = ls2.GetDirection();
    ASSERT_NEAR(d1(0u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(d1(1u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(d2(0u), -std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(d2(1u), std::sqrt(2.0f) / 2.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Length)
{
    ASSERT_NEAR(ls1.GetLength(), std::sqrt(2.0f) * 2.0f, tolf);
    ASSERT_NEAR(ls2.GetLength(), std::sqrt(2.0f), tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Interpolate)
{
    holo::geometry::Point2f pt_0   = ls1.Interpolate(0.0f);
    holo::geometry::Point2f pt_1   = ls1.Interpolate(0.5f);
    holo::geometry::Point2f pt_2   = ls1.Interpolate(1.0f);
    holo::geometry::Point2f pt_min = ls1.GetStartPoint();
    holo::geometry::Point2f pt_max = ls1.GetEndPoint();

    ASSERT_NEAR(pt_0.GetX(), -1.0f, tolf);
    ASSERT_NEAR(pt_0.GetY(), 0.0f, tolf);
    ASSERT_NEAR(pt_1.GetX(), 0.0f, tolf);
    ASSERT_NEAR(pt_1.GetY(), 1.0f, tolf);
    ASSERT_NEAR(pt_2.GetX(), 1.0f, tolf);
    ASSERT_NEAR(pt_2.GetY(), 2.0f, tolf);
    ASSERT_NEAR(pt_min.GetX(), -1.0f, tolf);
    ASSERT_NEAR(pt_min.GetY(), 0.0f, tolf);
    ASSERT_NEAR(pt_max.GetX(), 1.0f, tolf);
    ASSERT_NEAR(pt_max.GetY(), 2.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, Cast)
{
    holo::geometry::LineSegment2d lsd = (holo::geometry::LineSegment2d)ls1;

    Vector4f vf = ls1.GetCoeffs();
    Vector4d vd = lsd.GetCoeffs();

    ASSERT_NEAR(vf(0u), vd(0u), tolf);
    ASSERT_NEAR(vf(1u), vd(1u), tolf);
    ASSERT_NEAR(vf(2u), vd(2u), tolf);
    ASSERT_NEAR(vf(3u), vd(3u), tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, OutputStream)
{
    holo::geometry::LineSegment2d lsd = (holo::geometry::LineSegment2d)ls1;
    std::cout << lsd;
}

///////////////////////////////////////////////////////////////////////////////
TEST(LineSegment2Test, ToString)
{
    holo::geometry::LineSegment2d lsd = (holo::geometry::LineSegment2d)ls1;
    lsd.ToString();
}

TEST(LineSegment2Test, GetSerializedSize)
{
    holo::geometry::LineSegment2d lsd = (holo::geometry::LineSegment2d)ls1;
    ASSERT_EQ(32, lsd.GetSerializedSize<4U>());
    ASSERT_EQ(32, lsd.GetSerializedSize<8U>());
}

/**
 * @brief Test Timestamp::Serialize and Deserialize
 */
TEST(LineSegment2Test, SerializeAndDeserialize)
{
    holo::geometry::LineSegment2d lsd_input = (holo::geometry::LineSegment2d)ls1;
    holo::geometry::LineSegment2d lsd_output;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << lsd_input;
    ASSERT_EQ(lsd_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> lsd_output;

    ASSERT_EQ(lsd_input, lsd_output);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
