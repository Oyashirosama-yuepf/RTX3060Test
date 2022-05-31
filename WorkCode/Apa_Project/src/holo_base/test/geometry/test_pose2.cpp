/*!
 * @file test_pose2.cpp
 * @brief pose2 unit test
 * @author duyanwei@holomatic.com
 * @date 2017-07-11
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/geometry/pose2.h>

using namespace holo;
using holo::numerics::Vector2d;
using holo::numerics::Matrix3;
using holo::geometry::Pose2f;
using holo::geometry::Pose2d;

const float64_t kTol = 1e-9;

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, TransformFrom)
{
    holo::geometry::Pose2d  M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    holo::geometry::Point2d p(10.0, 0.0);
    holo::geometry::Point2d q = M.TransformFrom(p);
    ASSERT_NEAR(q.GetX(), 1.0, kTol);
    ASSERT_NEAR(q.GetY(), 12.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, TransformTo)
{
    holo::geometry::Pose2d  M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    holo::geometry::Point2d p(1.0, 12.0);
    holo::geometry::Point2d q = M.TransformTo(p);
    ASSERT_NEAR(q.GetX(), 10.0, kTol);
    ASSERT_NEAR(q.GetY(), 0.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, TransformFromVector)
{
    holo::geometry::Pose2d M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    Vector2d               p(10.0, 0.0);
    Vector2d               q = M.TransformFrom(p);
    ASSERT_NEAR(q(0u), 0.0, kTol);
    ASSERT_NEAR(q(1u), 10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, TransformToVector)
{
    holo::geometry::Pose2d M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    Vector2d               p(1.0, 12.0);
    Vector2d               q = M.TransformTo(p);
    ASSERT_NEAR(q(0u), 12.0, kTol);
    ASSERT_NEAR(q(1u), -1.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, OperatorTimesPoint)
{
    holo::geometry::Pose2d  M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    holo::geometry::Point2d p(10.0, 0.0);
    holo::geometry::Point2d q = M * p;
    ASSERT_NEAR(q.GetX(), 1.0, kTol);
    ASSERT_NEAR(q.GetY(), 12.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, OperatorTimesVector)
{
    holo::geometry::Pose2d M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    Vector2d               p(10.0, 0.0);
    Vector2d               q = M * p;
    ASSERT_NEAR(q(0u), 0.0, kTol);
    ASSERT_NEAR(q(1u), 10.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, Between)
{
    holo::geometry::Pose2d origin(holo::geometry::Rot2d(holo::geometry::Radian(90.0)),
                                  holo::geometry::Point2d(1.0, 2.0));
    holo::geometry::Pose2d target(holo::geometry::Rot2d(holo::geometry::Radian(180.0)),
                                  holo::geometry::Point2d(3.0, 3.0));

    holo::geometry::Pose2d relative = origin.Between(target);

    ASSERT_NEAR(1.0, relative.GetX(), kTol);
    ASSERT_NEAR(-2.0, relative.GetY(), kTol);
    ASSERT_NEAR(holo::geometry::Radian(90.0), relative.GetTheta(), kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, Matrix3)
{
    holo::geometry::Pose2d M(holo::geometry::Rot2d(holo::geometry::Radian(90.0)), holo::geometry::Point2d(1.0, 2.0));
    Matrix3                A = M.ToMatrix();
    ASSERT_NEAR(A(0u, 0u), 0.0, kTol);
    ASSERT_NEAR(A(0u, 1u), -1.0, kTol);
    ASSERT_NEAR(A(0u, 2u), 1.0, kTol);
    ASSERT_NEAR(A(1u, 0u), 1.0, kTol);
    ASSERT_NEAR(A(1u, 1u), 0.0, kTol);
    ASSERT_NEAR(A(1u, 2u), 2.0, kTol);
    ASSERT_NEAR(A(2u, 0u), 0.0, kTol);
    ASSERT_NEAR(A(2u, 1u), 0.0, kTol);
    ASSERT_NEAR(A(2u, 2u), 1.0, kTol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, Cast)
{
    holo::geometry::Pose2d p1(holo::geometry::Rot2d(holo::geometry::Radian(3.0)), holo::geometry::Point2d(1.3, 2.3));
    holo::geometry::Pose2f p2 = (holo::geometry::Pose2f)p1;
    ASSERT_FLOAT_EQ(p2.GetTheta(), holo::geometry::Radian(3.0f));
    ASSERT_FLOAT_EQ(p2.GetX(), 1.3f);
    ASSERT_FLOAT_EQ(p2.GetY(), 2.3f);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, GetSerializedSize)
{
    holo::geometry::Pose2d p1(holo::geometry::Rot2d(holo::geometry::Radian(3.0)), holo::geometry::Point2d(1.3, 2.3));
    ASSERT_EQ(32, p1.GetSerializedSize<4U>());
    ASSERT_EQ(32, p1.GetSerializedSize<8U>());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose2Test, SerializeAndDeserializeWithFloat32)
{
    Pose2f pose2f_input = Pose2f(Rot2f(Matrix2f(0.0f, -1.0f, 1.0f, 0.0f)), Point2f(1.0f, 2.0f));

    Pose2f pose2f_output;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << pose2f_input;
    ASSERT_EQ(pose2f_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> pose2f_output;

    ASSERT_EQ(pose2f_input.GetRotation().ToMatrix().At(0, 0), pose2f_output.GetRotation().ToMatrix().At(0, 0));
    ASSERT_EQ(pose2f_input.GetRotation().ToMatrix().At(0, 1), pose2f_output.GetRotation().ToMatrix().At(0, 1));
    ASSERT_EQ(pose2f_input.GetRotation().ToMatrix().At(1, 0), pose2f_output.GetRotation().ToMatrix().At(1, 0));
    ASSERT_EQ(pose2f_input.GetRotation().ToMatrix().At(1, 1), pose2f_output.GetRotation().ToMatrix().At(1, 1));
    ASSERT_EQ(pose2f_input.GetTranslation().GetX(), pose2f_output.GetTranslation().GetX());
    ASSERT_EQ(pose2f_input.GetTranslation().GetY(), pose2f_output.GetTranslation().GetY());
    ASSERT_EQ(pose2f_input.GetRotation().GetTheta(), pose2f_output.GetRotation().GetTheta());
}

TEST(Pose2Test, SerializeAndDeserializeWithFloat64)
{
    Pose2d pose2d_input(Rot2d(geometry::Radian((float64_t)(rand() % 3140) / 1000.0)),
                        Point2d((float64_t)(rand() % 1000), (float64_t)(rand() % 1000)));
    Pose2d pose2d_output;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << pose2d_input;
    ASSERT_EQ(pose2d_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> pose2d_output;

    ASSERT_EQ(pose2d_input.GetRotation().ToMatrix().At(0, 0), pose2d_output.GetRotation().ToMatrix().At(0, 0));
    ASSERT_EQ(pose2d_input.GetRotation().ToMatrix().At(0, 1), pose2d_output.GetRotation().ToMatrix().At(0, 1));
    ASSERT_EQ(pose2d_input.GetRotation().ToMatrix().At(1, 0), pose2d_output.GetRotation().ToMatrix().At(1, 0));
    ASSERT_EQ(pose2d_input.GetRotation().ToMatrix().At(1, 1), pose2d_output.GetRotation().ToMatrix().At(1, 1));
    ASSERT_EQ(pose2d_input.GetTranslation().GetX(), pose2d_output.GetTranslation().GetX());
    ASSERT_EQ(pose2d_input.GetTranslation().GetY(), pose2d_output.GetTranslation().GetY());
    ASSERT_EQ(pose2d_input.GetRotation().GetTheta(), pose2d_output.GetRotation().GetTheta());
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
