/*!
 * @file test_box3.cpp
 * @brief unit test for box3
 * @author jiaxing.zhao
 * @date 2017-07-25
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notic.
 */

#include <gtest/gtest.h>
#include <holo/geometry/box3.h>

using namespace holo;
using holo::geometry::Point3f;

const float32_t tolf = EpsilonT<float32_t>::value;

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, ConstructFromCenter)
{
    float32_t const             width  = 1.0f;
    float32_t const             height = 2.0f;
    float32_t const             depth  = 4.0f;
    Point3f const               center(10.0f, -11.0f, 12.0f);
    holo::geometry::Box3f const box(width, height, depth, center);

    ASSERT_EQ(width, box.GetWidth());
    ASSERT_EQ(height, box.GetHeight());
    ASSERT_EQ(depth, box.GetDepth());
    ASSERT_EQ(center, box.GetCenter());
    ASSERT_EQ(Pose3f(Rot3f::Identity(), Point3f(8.0f, -11.5f, 11.0f)), box.GetPose());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, ConstructFromCenter_Rotated)
{
    float32_t const             width  = 1.0f;
    float32_t const             height = 2.0f;
    float32_t const             depth  = 4.0f;
    Point3f const               center(10.0f, -11.0f, 12.0f);
    float32_t const             roll  = 0.0f;
    float32_t const             pitch = 0.0f;
    float32_t const             yaw   = static_cast<float32_t>(M_PI / 2.0);
    holo::geometry::Box3f const box(width, height, depth, center, roll, pitch, yaw);

    ASSERT_EQ(width, box.GetWidth());
    ASSERT_EQ(height, box.GetHeight());
    ASSERT_EQ(depth, box.GetDepth());
    ASSERT_EQ(center, box.GetCenter());
    ASSERT_EQ(Pose3f(Rot3f::RzRyRx(roll, pitch, yaw), Point3f(10.5f, -13.0f, 11.0f)), box.GetPose());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Contains)
{
    holo::geometry::Box3f   box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(2.0f, 3.0f, 4.0f));
    holo::geometry::Point3f p(1.0f, 2.0f, 3.0f), q(10.0f, 0.0f, 0.0f);
    ASSERT_TRUE(box.Contains(p));
    ASSERT_FALSE(box.Contains(q));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Contains2)
{
    holo::geometry::Box3d box(
        Vector3d(2.0, 3.0, 4.0),
        holo::geometry::Pose3d(holo::geometry::Rot3d(), holo::geometry::Point3d(-10.0, -20.0, -30.0)));
    holo::geometry::Point3d p(0.0, 0.0, 0.0), q(-9.0, -19.0, -29.0);

    ASSERT_TRUE(box.Contains(q));
    ASSERT_FALSE(box.Contains(p));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Contains3)
{
    holo::geometry::Box3f   box(holo::geometry::Point3f(1.0f, 4.0f, 1.0f), holo::geometry::Point3f(3.0f, 2.0f, 3.0f));
    holo::geometry::Point3f p(2.0f, 3.0f, 2.0f), q(10.0f, 0.0f, 0.0f);
    holo::geometry::Point3f center = box.GetCenter();

    ASSERT_TRUE(box.Contains(p));
    ASSERT_FALSE(box.Contains(q));
    ASSERT_TRUE(center.IsEqual(holo::geometry::Point3f(2.0f, 3.0f, 2.0f)));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Contains4)
{
    holo::geometry::Box3f   box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(2.0f, -3.0f, -4.0f));
    holo::geometry::Point3f p(1.0f, -2.0f, -2.0f), q(0.0f, 0.0f, 1.0f);

    ASSERT_TRUE(box.Contains(p));
    ASSERT_FALSE(box.Contains(q));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, AxisAlignedCoordinates)
{
    holo::geometry::Box3f   box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(2.0f, 2.0f, 2.0f));
    holo::geometry::Point3f min_pt, max_pt;
    float32_t               tol = 1e-3f;
    holo::geometry::Point3f p(0.0f, 0.0f, 0.0f), q(2.0f, 2.0f, 2.0f);
    box.GetAxisAlignedExternalBox(min_pt, max_pt);
    ASSERT_NEAR(min_pt.GetX(), p.GetX(), tol);
    ASSERT_NEAR(min_pt.GetY(), p.GetY(), tol);
    ASSERT_NEAR(min_pt.GetZ(), p.GetZ(), tol);
    ASSERT_NEAR(max_pt.GetX(), q.GetX(), tol);
    ASSERT_NEAR(max_pt.GetY(), q.GetY(), tol);
    ASSERT_NEAR(max_pt.GetZ(), q.GetZ(), tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, CornerPoints)
{
    holo::geometry::Box3f box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(1.0f, 2.0f, 3.0f));

    std::vector<holo::geometry::Point3f> corners = box.GetCornerPoints();

    std::vector<holo::geometry::Point3f> expected{
        holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(1.0f, 0.0f, 0.0f),
        holo::geometry::Point3f(1.0f, 2.0f, 0.0f), holo::geometry::Point3f(0.0f, 2.0f, 0.0f),
        holo::geometry::Point3f(0.0f, 2.0f, 3.0f), holo::geometry::Point3f(0.0f, 0.0f, 3.0f),
        holo::geometry::Point3f(1.0f, 0.0f, 3.0f), holo::geometry::Point3f(1.0f, 2.0f, 3.0f)};

    ASSERT_EQ(8u, corners.size());
    for (uint8_t i = 0u; i < corners.size(); i++)
    {
        ASSERT_EQ(expected.at(i), corners.at(i));
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Center)
{
    holo::geometry::Box3f   box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(1.0f, 2.0f, 3.0f));
    holo::geometry::Point3f expected(0.5f, 1.0f, 1.5f);
    ASSERT_EQ(expected, box.GetCenter());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Dimension)
{
    holo::geometry::Box3f box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(1.0f, box.GetDepth());
    ASSERT_EQ(2.0f, box.GetWidth());
    ASSERT_EQ(3.0f, box.GetHeight());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Volume)
{
    holo::geometry::Box3f box(holo::geometry::Point3f(0.0f, 0.0f, 0.0f), holo::geometry::Point3f(1.0f, 2.0f, 3.0f));
    ASSERT_EQ(6.0f, box.GetVolume());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, Cast)
{
    holo::geometry::Box3d b1(3.4, 4.5, 6.7, holo::geometry::Pose3d::Identity());
    holo::geometry::Box3f b2 = (holo::geometry::Box3f)b1;
    ASSERT_NEAR(b2.GetWidth(), 3.4, tolf);
    ASSERT_NEAR(b2.GetHeight(), 4.5, tolf);
    ASSERT_NEAR(b2.GetDepth(), 6.7, tolf);
    ASSERT_TRUE(b2.GetPose().IsEqual(holo::geometry::Pose3f::Identity()));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, OutputStream)
{
    holo::geometry::Box3d b1(3.4, 4.5, 6.7, holo::geometry::Pose3d::Identity());
    std::cout << b1;
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, GetSerializedSize)
{
    holo::geometry::Box3d b1(3.4, 4.5, 6.7, holo::geometry::Pose3d::Identity());
    ASSERT_EQ(120, b1.GetSerializedSize<4U>());
    ASSERT_EQ(120, b1.GetSerializedSize<8U>());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box3Test, SerializeDeserialize)
{
    holo::geometry::Box3f box3f_input = holo::geometry::Box3f(
        4.0f, 5.0f, 6.0f,
        holo::geometry::Pose3f(holo::geometry::Rot3f(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
                               holo::geometry::Point3f(1.0f, 2.0f, 3.0f)));
    holo::geometry::Box3f box3f_output;

    uint8_t                           buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << box3f_input;

    EXPECT_EQ(serializer.GetSize(), box3f_input.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> box3f_output;

    EXPECT_EQ(box3f_input, box3f_output);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
