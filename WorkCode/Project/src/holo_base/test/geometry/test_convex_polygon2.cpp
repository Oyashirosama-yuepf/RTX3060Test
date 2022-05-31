/*!
 * @file test_eonvex_polygon2.cpp
 * @brief unit test for polygon2
 * @author duyanwei@holomatic.com
 * @date 2017-07-12
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/convex_polygon2.h>

using namespace holo;

const float64_t tol = EpsilonT<float64_t>::value;

///////////////////////////////////////////////////////////////////////////////
class TestFixture : public ::testing::Test
{
public:
    TestFixture()
    {
    }

    virtual ~TestFixture()
    {
    }

    virtual void SetUp()
    {
        // construct polygon vertices
        // counter-clockwise
        vertices1_[0] = holo::geometry::Point2d(3.0, 3.0);
        vertices1_[1] = holo::geometry::Point2d(-6.0, 3.0);
        vertices1_[2] = holo::geometry::Point2d(-6.0, -3.0);
        vertices1_[3] = holo::geometry::Point2d(3.0, -3.0);

        // clockwise
        vertices2_[0] = holo::geometry::Point2d(3.0, 3.0);
        vertices2_[1] = holo::geometry::Point2d(3.0, -3.0);
        vertices2_[2] = holo::geometry::Point2d(-6.0, -3.0);
        vertices2_[3] = holo::geometry::Point2d(-6.0, 3.0);

        for (uint8_t i = 0u; i < 4u; i++)
        {
            polygon1_.AppendVertex(vertices1_[i]);
            polygon2_.AppendVertex(vertices2_[i]);
        }
    }

    virtual void TearDown()
    {
    }

protected:
    std::array<holo::geometry::Point2d, 4u> vertices1_;
    std::array<holo::geometry::Point2d, 4u> vertices2_;
    holo::geometry::ConvexPolygon2d         polygon1_;
    holo::geometry::ConvexPolygon2d         polygon2_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, AppendVertex)
{
    holo::geometry::ConvexPolygon2d p;

    // valid vertex
    for (uint8_t i = 0u; i < polygon1_.GetSize(); i++)
    {
        ASSERT_TRUE(p.AppendVertex(polygon1_.GetVertex(i)));
        ASSERT_EQ(i + 1u, p.GetSize());
    }

    // invalid vertex
    const uint8_t expected_size = p.GetSize();
    ASSERT_FALSE(p.AppendVertex(holo::geometry::Point2d(0.0, 0.0)));
    ASSERT_EQ(expected_size, p.GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, GetSize)
{
    ASSERT_TRUE(4u == polygon1_.GetSize());
    ASSERT_TRUE(4u == polygon2_.GetSize());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, GetVertex)
{
    for (uint8_t i = 0u; i < polygon1_.GetSize(); i++)
    {
        ASSERT_NEAR(polygon1_.GetVertex(i).GetX(), vertices1_[i].GetX(), tol);
        ASSERT_NEAR(polygon1_.GetVertex(i).GetY(), vertices1_[i].GetY(), tol);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, GetEdge)
{
    for (uint8_t i = 0u; i < polygon1_.GetSize(); i++)
    {
        uint8_t j = i + 1u;
        if (i == polygon1_.GetSize() - 1u)
        {
            j = 0u;
        }

        holo::geometry::LineSegment2d ls(vertices1_[i], vertices1_[j]);
        ASSERT_TRUE(polygon1_.GetEdge(i).IsEqual(ls));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, Contains)
{
    holo::geometry::Point2d inside(1.0, -1.0);
    ASSERT_TRUE(polygon1_.Contains(inside));

    holo::geometry::Point2d inside2(2.9, 2.9);
    ASSERT_TRUE(polygon1_.Contains(inside2));

    holo::geometry::Point2d outside(10.0, -10.0);
    ASSERT_FALSE(polygon1_.Contains(outside));

    holo::geometry::Point2d edge(0.0, 3.0);
    ASSERT_FALSE(polygon1_.Contains(outside));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, Contains2)
{
    holo::geometry::Point2d inside(1.0, -1.0);
    ASSERT_TRUE(polygon2_.Contains(inside));

    holo::geometry::Point2d inside2(2.9, 2.9);
    ASSERT_TRUE(polygon2_.Contains(inside2));

    holo::geometry::Point2d outside(10.0, -10.0);
    ASSERT_FALSE(polygon2_.Contains(outside));

    holo::geometry::Point2d edge(0.0, 3.0);
    ASSERT_FALSE(polygon2_.Contains(outside));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, IsEqual)
{
    ASSERT_FALSE(polygon1_.IsEqual(polygon2_));
    ASSERT_TRUE(polygon2_.IsEqual(polygon2_));
    ASSERT_FALSE(polygon1_ == polygon2_);
    ASSERT_TRUE(polygon2_ == polygon2_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_F(TestFixture, Cast)
{
    holo::geometry::ConvexPolygon2f pf = (holo::geometry::ConvexPolygon2f)polygon1_;

    for (uint8_t i = 0u; i < polygon1_.GetSize(); i++)
    {
        ASSERT_NEAR(polygon1_.GetVertex(i).GetX(), pf.GetVertex(i).GetX(), tol);
        ASSERT_NEAR(polygon1_.GetVertex(i).GetY(), pf.GetVertex(i).GetY(), tol);
    }
}

TEST_F(TestFixture, GetSerializedSize)
{
    holo::geometry::ConvexPolygon2f convf;
    ASSERT_EQ(4, convf.GetSerializedSize<4U>());
    ASSERT_EQ(8, convf.GetSerializedSize<8U>());
}

TEST_F(TestFixture, SerializeAndDeserialize)
{
    holo::geometry::ConvexPolygon2f input_pf, output_pf;

    srand(time(0));

    int32_t point_cnt0 = 2;
    int32_t point_cnt1 = 2;
    int32_t i          = 0;
    for (i = 0; i < point_cnt0; ++i)
    {
        input_pf.AppendVertex(holo::geometry::Point2f((float32_t)(rand() % 100), (float32_t)(rand() % 1000)));
    }

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << input_pf;
    ASSERT_EQ(input_pf.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_pf;


    ASSERT_EQ(input_pf.GetSize(), output_pf.GetSize());
    for (i = 0; i < input_pf.GetSize(); ++i)
    {
        ASSERT_EQ(input_pf.GetVertex(i).GetX(), output_pf.GetVertex(i).GetX());
        ASSERT_EQ(input_pf.GetVertex(i).GetY(), output_pf.GetVertex(i).GetY());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
