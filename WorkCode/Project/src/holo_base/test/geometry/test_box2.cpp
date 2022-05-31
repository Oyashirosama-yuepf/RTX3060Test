/*!
 * \brief box2 unit test
 * \author Evan.Du
 * \date 2017-07-24
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/box2.h>

using namespace holo;

const float32_t tolf = EpsilonT<float32_t>::value;
const float64_t told = EpsilonT<float64_t>::value;

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, Default)
{
    holo::geometry::Box2d box;
    box.SetWidth(10.0);
    box.SetHeight(5.0);
    box.SetPose(holo::geometry::Pose2d(0.1, 1.0, -1.0));

    // check results
    ASSERT_NEAR(box.GetWidth(), 10.0, told);
    ASSERT_NEAR(box.GetHeight(), 5.0, told);
    ASSERT_NEAR(box.GetPose().GetTheta(), 0.1, told);
    ASSERT_NEAR(box.GetPose().GetX(), 1.0, told);
    ASSERT_NEAR(box.GetPose().GetY(), -1.0, told);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, FromCenterPoint)
{
    // construct a box from center point, width, height, and orientation
    holo::geometry::Box2f box(holo::geometry::Point2f(1.0f, 1.0f), std::sqrt(2.0f), std::sqrt(2.0f), M_PI / 4.0f);

    // four corner poitns
    holo::geometry::Point2f pt_bl, pt_br, pt_tr, pt_tl;

    // four boundaries
    holo::geometry::LineSegment2f ls_b, ls_r, ls_t, ls_l;

    // axis-aligned coordinates
    holo::geometry::Point2f pt_min, pt_max;

    box.GetCornerPoints(pt_bl, pt_br, pt_tr, pt_tl);
    box.GetEdges(ls_b, ls_r, ls_t, ls_l);
    box.GetAxisAlignedExternalBox(pt_min, pt_max);

    // check results
    ASSERT_NEAR(box.GetWidth(), std::sqrt(2.0f), tolf);
    ASSERT_NEAR(box.GetHeight(), std::sqrt(2.0f), tolf);

    holo::geometry::Pose2f pose(holo::geometry::Rot2f(M_PI / 4.0f), holo::geometry::Point2f(1.0f, 0.0f));
    ASSERT_TRUE(box.GetPose().IsEqual(pose, 1e-6f));

    ASSERT_TRUE(pt_bl.IsEqual(holo::geometry::Point2f(1.0f, 0.0f), 1e-5f));
    EXPECT_TRUE(pt_br.IsEqual(holo::geometry::Point2f(2.0f, 1.0f), 1e-5f));
    ASSERT_TRUE(pt_tr.IsEqual(holo::geometry::Point2f(1.0f, 2.0f), 1e-5f));
    ASSERT_TRUE(pt_tl.IsEqual(holo::geometry::Point2f(0.0f, 1.0f), 1e-5f));

    ASSERT_TRUE(ls_b.IsEqual(
        holo::geometry::LineSegment2f(holo::geometry::Point2f(1.0f, 0.0f), holo::geometry::Point2f(2.0f, 1.0f)),
        1e-5f));
    ASSERT_TRUE(ls_r.IsEqual(
        holo::geometry::LineSegment2f(holo::geometry::Point2f(2.0f, 1.0f), holo::geometry::Point2f(1.0f, 2.0f)),
        1e-5f));
    ASSERT_TRUE(ls_t.IsEqual(
        holo::geometry::LineSegment2f(holo::geometry::Point2f(1.0f, 2.0f), holo::geometry::Point2f(0.0f, 1.0f)),
        1e-5f));
    ASSERT_TRUE(ls_l.IsEqual(
        holo::geometry::LineSegment2f(holo::geometry::Point2f(0.0f, 1.0f), holo::geometry::Point2f(1.0f, 0.0f)),
        1e-5f));

    ASSERT_TRUE(pt_min.IsEqual(holo::geometry::Point2f(0.0f, 0.0f), 1e-5f));
    ASSERT_TRUE(pt_max.IsEqual(holo::geometry::Point2f(2.0f, 2.0f), 1e-5f));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, Contains1)
{
    holo::geometry::Box2f   box(holo::geometry::Point2f(0.0f, 0.0f), holo::geometry::Point2f(2.0f, 3.0f));
    holo::geometry::Point2f p(1.0f, 2.0f), q(10.0f, 0.0f);

    ASSERT_TRUE(box.Contains(p));
    ASSERT_FALSE(box.Contains(q));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, Contains2)
{
    holo::geometry::Point2d g(-10.0, -20.0);
    holo::geometry::Pose2d  h(holo::geometry::Rot2d(), holo::geometry::Point2d(-10.0, -20.0));
    holo::geometry::Box2d   box(2.0, 3.0,
                              holo::geometry::Pose2d(holo::geometry::Rot2d(), holo::geometry::Point2d(-10.0, -20.0)));
    holo::geometry::Point2d p(0.0, 0.0), q(-9.0, -19.0);

    // check results
    ASSERT_FALSE(box.Contains(p));
    ASSERT_TRUE(box.Contains(q));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, Contains3)
{
    holo::geometry::Box2f         box(holo::geometry::Point2f(0.0f, 0.0f), holo::geometry::Point2f(2.0f, 3.0f));
    holo::geometry::LineSegment2f ls1(holo::geometry::Point2f(0.1f, 0.1f), holo::geometry::Point2f(1.9f, 2.9f)),
        ls2(holo::geometry::Point2f(-0.1f, -0.1f), holo::geometry::Point2f(1.5f, 2.5f));

    // check results
    ASSERT_TRUE(box.Contains(ls1));
    ASSERT_FALSE(box.Contains(ls2));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, Intersect)
{
    holo::geometry::Box2f         box(holo::geometry::Point2f(0.0f, 0.0f), holo::geometry::Point2f(3.0f, 3.0f));
    holo::geometry::LineSegment2f ls1(holo::geometry::Point2f(0.1f, 0.1f), holo::geometry::Point2f(2.9f, 2.9f));
    holo::geometry::LineSegment2f ls2(holo::geometry::Point2f(-0.1f, -0.1f), holo::geometry::Point2f(1.5f, 1.5f));
    holo::geometry::LineSegment2f ls3(holo::geometry::Point2f(-0.1f, -0.1f), holo::geometry::Point2f(3.1f, 3.1f));

    holo::geometry::Point2f p11, p12, p21, p22, p31, p32;
    const uint8_t           num1 = box.Intersect(ls1, p11, p12);
    const uint8_t           num2 = box.Intersect(ls2, p21, p22);
    const uint8_t           num3 = box.Intersect(ls3, p31, p32);

    // check results
    ASSERT_EQ(num1, 0u);
    ASSERT_EQ(num2, 1u);
    ASSERT_EQ(num3, 2u);

    ASSERT_TRUE(p21.IsEqual(holo::geometry::Point2f(0.0f, 0.0f), 1e-5f));
    ASSERT_TRUE(p31.IsEqual(holo::geometry::Point2f(0.0f, 0.0f), 1e-5f));
    ASSERT_TRUE(p32.IsEqual(holo::geometry::Point2f(3.0f, 3.0f), 1e-5f));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, IntersectionOverUnion)
{
    // ground truth box
    holo::geometry::Box2d box(holo::geometry::Point2d(-1.0, -1.0), holo::geometry::Point2d(1.0, 1.0));

    // test boxes
    holo::geometry::Box2d box1(holo::geometry::Point2d(-0.5, -0.5), holo::geometry::Point2d(0.5, 0.5));
    holo::geometry::Box2d box2(holo::geometry::Point2d(-1.5, -1.5), holo::geometry::Point2d(-1.0, -1.0));
    holo::geometry::Box2d box3(holo::geometry::Point2d(1.0, 1.0), holo::geometry::Point2d(1.5, 1.5));
    holo::geometry::Box2d box4(holo::geometry::Point2d(-2.0, -1.0), holo::geometry::Point2d(0.0, 0.0));
    holo::geometry::Box2d box5(holo::geometry::Point2d(-0.5, -1.5), holo::geometry::Point2d(0.5, 1.5));

    // check results
    ASSERT_EQ(box.ComputeIntersectionOverUnion(box), 1.0);
    ASSERT_EQ(box.ComputeIntersectionOverUnion(box1), 0.25);
    ASSERT_EQ(box1.ComputeIntersectionOverUnion(box), 0.25);
    ASSERT_EQ(box.ComputeIntersectionOverUnion(box2), 0.0);
    ASSERT_EQ(box2.ComputeIntersectionOverUnion(box), 0.0);
    ASSERT_EQ(box.ComputeIntersectionOverUnion(box3), 0.0);
    ASSERT_EQ(box3.ComputeIntersectionOverUnion(box), 0.0);
    ASSERT_EQ(box.ComputeIntersectionOverUnion(box4), 0.2);
    ASSERT_EQ(box4.ComputeIntersectionOverUnion(box), 0.2);
    ASSERT_EQ(box.ComputeIntersectionOverUnion(box5), 0.4);
    ASSERT_EQ(box5.ComputeIntersectionOverUnion(box), 0.4);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Box2Test, OutputStream)
{
    holo::geometry::Box2d b1(3.4, 4.5, holo::geometry::Pose2d::Identity());
    std::cout << b1;
}

TEST(Box2Test, Cast)
{
    holo::geometry::Box2d b1(3.4, 4.5, holo::geometry::Pose2d::Identity());
    holo::geometry::Box2f b2 = (holo::geometry::Box2f)b1;
    ASSERT_NEAR(b2.GetWidth(), 3.4f, tolf);
    ASSERT_NEAR(b2.GetHeight(), 4.5f, tolf);
    ASSERT_TRUE(b2.GetPose().IsEqual(holo::geometry::Pose2f::Identity()));
}

TEST(Box2Test, GetSerializedSize)
{
    holo::geometry::Box2d b1(3.4, 4.5, holo::geometry::Pose2d::Identity());
    ASSERT_EQ(48, b1.GetSerializedSize<4U>());
    ASSERT_EQ(48, b1.GetSerializedSize<8U>());
}

TEST(Box2Test, SerializeDeserialize)
{
    holo::geometry::Box2f box2f_input =
        holo::geometry::Box2f(3.0f, 4.0f,
                              holo::geometry::Pose2f(holo::geometry::Rot2f(Matrix2f(0.0f, -1.0f, 1.0f, 0.0f)),
                                                     holo::geometry::Point2f(1.0f, 2.0f)));
    holo::geometry::Box2f box2f_output;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << box2f_input;

    EXPECT_EQ(serializer.GetSize(), box2f_input.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> box2f_output;

    EXPECT_EQ(box2f_input, box2f_output);
}

TEST(Box2Test, GetAxisAlignedExternalBox)
{
    // construct a box from center point, width, height, and orientation
    holo::geometry::Box2f box(holo::geometry::Point2f(1.0f, 1.0f), std::sqrt(2.0f), std::sqrt(2.0f), M_PI / 4.0f);

    // four corner poitns
    holo::geometry::Point2f pt_bl, pt_br, pt_tr, pt_tl;

    // four boundaries
    holo::geometry::LineSegment2f ls_b, ls_r, ls_t, ls_l;

    // axis-aligned coordinates
    holo::geometry::Point2f pt_min, pt_max(-10, -10);
    std::cout << "-----------------------------------"  << std::endl;
    box.GetAxisAlignedExternalBox(pt_min, pt_max);
    std::cout << "-----------------------------------"  << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
