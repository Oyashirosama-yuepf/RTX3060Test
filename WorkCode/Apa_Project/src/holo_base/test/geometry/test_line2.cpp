/*!
 * @file test_line2.cpp
 * @brief unit test for line2
 * @author duyanwei@Holomatic.com
 * @date 2017-07-14
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/line2.h>

using namespace holo;
using holo::numerics::Vector2;
using holo::numerics::Vector2f;
using holo::numerics::Vector3;
using holo::numerics::Vector3f;
using holo::numerics::Vector3d;

///////////////////////////////////////////////////////////////////////////////
holo::geometry::Point2f p11(-1.0f, 0.0f), p12(0.0f, 1.0f);
holo::geometry::Point2f p21(1.0f, 0.0f), p22(1.0f, 2.0f);
holo::geometry::Point2f p31(-1.0f, -1.0f), p32(0.0f, 0.0f);
holo::geometry::Line2f  l1(p11, p12), l2(p21, p22), l3(p31, p32), l4(p12, p22);

const float32_t tolf = EpsilonT<float32_t>::value;
const float64_t told = EpsilonT<float64_t>::value;

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Contains)
{
    ASSERT_FALSE(l1.Contains(p21));
    ASSERT_TRUE(l1.Contains(p22));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, ConstructorException)
{
    holo::numerics::Vector3f v3(0.0f, 0.0f, 1.0f);
    holo::geometry::Point2f p51(0.0f, 0.0f), p52(0.0f, 0.0f);

    try
    {
        holo::geometry::Line2f  l5(p51, p52);
    }
    catch(...)
    {
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Dist)
{
    ASSERT_NEAR(l1.Dist(p21), std::sqrt(2.0f), tolf);
    ASSERT_NEAR(l1.Dist(p22), 0.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Project)
{
    holo::geometry::Point2f p21_proj = l1.Project(p21);
    holo::geometry::Point2f p22_proj = l1.Project(p22);

    ASSERT_NEAR(p21_proj.GetX(), 0.0f, tolf);
    ASSERT_NEAR(p21_proj.GetY(), 1.0f, tolf);
    ASSERT_NEAR(p22_proj.GetX(), 1.0f, tolf);
    ASSERT_NEAR(p22_proj.GetY(), 2.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Equals)
{
    ASSERT_FALSE(l1.IsEqual(l2));
    ASSERT_FALSE(l1.IsEqual(l3));
    ASSERT_TRUE(l1.IsEqual(l4));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Parallel)
{
    ASSERT_FALSE(l1.IsParallel(l2));
    ASSERT_TRUE(l1.IsParallel(l3));
    ASSERT_TRUE(l1.IsParallel(l4));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Intersect)
{
    holo::geometry::Point2f pt;
    ASSERT_TRUE(l1.Intersect(l2, pt));
    ASSERT_NEAR(pt.GetX(), 1.0f, tolf);
    ASSERT_NEAR(pt.GetY(), 2.0f, tolf);
    ASSERT_FALSE(l1.Intersect(l3, pt));
    ASSERT_FALSE(l1.Intersect(l4, pt));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Normal)
{
    Vector2f n1 = l1.GetNormal(), n2 = l2.GetNormal();
    ASSERT_NEAR(n1(0u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(n1(1u), -std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(n2(0u), 1.0f, tolf);
    ASSERT_NEAR(n2(1u), 0.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Direction)
{
    Vector2f d1 = l1.GetDirection(), d2 = l2.GetDirection();
    ASSERT_NEAR(d1(0u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(d1(1u), std::sqrt(2.0f) / 2.0f, tolf);
    ASSERT_NEAR(d2(0u), 0.0f, tolf);
    ASSERT_NEAR(d2(1u), 1.0f, tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, FromPointAndVector)
{
    holo::geometry::Point2 pt(1.0, 1.0);
    float64_t              scalar = std::sqrt(2.0);
    Vector2                vec(scalar, scalar);
    holo::geometry::Line2  line(pt, vec);

    // check results
    Vector3 est = line.GetCoeffs();
    ASSERT_NEAR(est(0u), scalar / 2.0, told);
    ASSERT_NEAR(est(1u), -scalar / 2.0, told);
    ASSERT_NEAR(est(2u), 0.0, told);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, Cast)
{
    holo::geometry::Line2d ld = (holo::geometry::Line2d)l1;

    Vector3f vf = l1.GetCoeffs();
    Vector3d vd = ld.GetCoeffs();

    ASSERT_NEAR(vf(0u), vd(0u), tolf);
    ASSERT_NEAR(vf(1u), vd(1u), tolf);
    ASSERT_NEAR(vf(2u), vd(2u), tolf);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, OutputStream)
{
    holo::geometry::Line2d ld = (holo::geometry::Line2d)l1;
    std::cout << ld;
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, ToString)
{
    holo::geometry::Line2d ld = (holo::geometry::Line2d)l1;
    ld.ToString();
}

///////////////////////////////////////////////////////////////////////////////
TEST(Line2Test, BasicSerializeDeserialize)
{
    holo::geometry::Line2f src = {1.0f, 0.0f, 4.0f};
    holo::geometry::Line2f dst;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);

    serializer << src;

    ASSERT_EQ(src.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<>         deserializer(buffer, serializer.GetSize());
    
    deserializer >> dst;

    ASSERT_TRUE(dst.IsEqual(src));
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
