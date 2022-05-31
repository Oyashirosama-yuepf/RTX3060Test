/*!
 * @file test_rot3.cpp
 * @brief Unit test for Rot3.h
 * @author Li Chao (lichao@holomatic.ai)
 * @date Jul 14, 2017
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/geometry/angle.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>

using namespace holo;
using holo::numerics::Vector3;

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, ConstructFromVectors)
{
    const Vector3 v1(0.0, 1.0, 0.0);
    const Vector3 v2(-1.0, 0.0, 0.0);
    const Vector3 v3(0.0, 0.0, 1.0);

    // construct rot3
    const holo::geometry::Rot3 rot(v1, v2, v3);

    // check results
    const holo::geometry::Rot3 expected(holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0)));
    ASSERT_EQ(expected, rot);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, ConstructFromPoints)
{
    const holo::geometry::Point3 p1(0.0, 1.0, 0.0);
    const holo::geometry::Point3 p2(-1.0, 0.0, 0.0);
    const holo::geometry::Point3 p3(0.0, 0.0, 1.0);

    // construct rot3
    const holo::geometry::Rot3 rot(p1, p2, p3);

    // check results
    const holo::geometry::Rot3 expected(holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0)));
    ASSERT_EQ(expected, rot);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, RotatePoint3)
{
    const holo::geometry::Rot3   R = holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0));
    const holo::geometry::Point3 p(1.0, 0.0, 0.0);

    // call methods
    const holo::geometry::Point3 q1 = R.Rotate(p);
    const holo::geometry::Point3 q2 = R * p;

    // check results
    const holo::geometry::Point3 expected(0.0, 1.0, 0.0);
    ASSERT_EQ(expected, q1);
    ASSERT_EQ(expected, q2);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, UnrotatePoint3)
{
    const float64_t              tol = 1e-8;
    const holo::geometry::Rot3   R   = holo::geometry::Rot3::Ry(holo::geometry::Radian(90.0));
    const holo::geometry::Point3 p(0.0, 0.0, 1.0);
    const holo::geometry::Point3 q = R.Unrotate(p);
    ASSERT_NEAR(q.GetX(), -1.0, tol);
    ASSERT_NEAR(q.GetY(), 0.0, tol);
    ASSERT_NEAR(q.GetZ(), 0.0, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, RotateVector3)
{
    const holo::geometry::Rot3 R = holo::geometry::Rot3::Rz(holo::geometry::Radian(180.0));
    const Vector3              v(0.0, 1.0, 3.0);

    // call methods
    const Vector3 v1 = R.Rotate(v);
    const Vector3 v2 = R * v;

    // check results
    const Vector3 expected(0.0, -1.0, 3.0);
    ASSERT_TRUE(expected.IsApprox(v1, 1e-15));
    ASSERT_TRUE(expected.IsApprox(v2, 1e-15));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, UnrotateVector3)
{
    const float64_t            tol = 1e-8;
    const holo::geometry::Rot3 R   = holo::geometry::Rot3::Rx(holo::geometry::Radian(90.0));
    const Vector3              p   = Vector3d(1.0, 2.0, 3.0);
    const Vector3              q   = R.Unrotate(p);
    ASSERT_NEAR(q(0u), 1.0, tol);
    ASSERT_NEAR(q(1u), 3.0, tol);
    ASSERT_NEAR(q(2u), -2.0, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, AngleBetween)
{
    // create two rot3
    const holo::geometry::Rot3 R1 = holo::geometry::Rot3::Rx(holo::geometry::Radian(45.0));
    const holo::geometry::Rot3 R2 = holo::geometry::Rot3::Rx(holo::geometry::Radian(-45.0));

    // call methods
    const float64_t angle = R1.ComputeAngle(R2);

    // check results
    const float64_t expected = 90.0;
    ASSERT_NEAR(expected, angle, 1e-10);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, ToQuaternion)
{
    // create rot3
    const holo::geometry::Rot3 R = holo::geometry::Rot3::Rx(holo::geometry::Radian(180.0));

    // call methods
    const holo::geometry::Quaternion q = R.ToQuaternion();

    // check results
    ASSERT_NEAR(0.0, q.GetW(), 1e-15);
    ASSERT_NEAR(1.0, q.GetX(), 1e-15);
    ASSERT_NEAR(0.0, q.GetY(), 1e-15);
    ASSERT_NEAR(0.0, q.GetZ(), 1e-15);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, Inverse)
{
    // create rot3
    const holo::geometry::Rot3 R = holo::geometry::Rot3::Rx(holo::geometry::Radian(45.0));

    // check results
    const holo::geometry::Rot3 expected = holo::geometry::Rot3::Rx(holo::geometry::Radian(-45.0));
    ASSERT_EQ(expected, R.Inverse());
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, GetRow)
{
    // create rot3
    const holo::geometry::Rot3 R = holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0));

    // call method
    const Vector3 r0 = R.GetRow(0u);
    const Vector3 r1 = R.GetRow(1u);
    const Vector3 r2 = R.GetRow(2u);

    // check results
    ASSERT_TRUE(Vector3(0.0, -1.0, 0.0).IsApprox(r0, 1e-15));
    ASSERT_TRUE(Vector3(1.0, 0.0, 0.0).IsApprox(r1, 1e-15));
    ASSERT_TRUE(Vector3(0.0, 0.0, 1.0).IsApprox(r2, 1e-15));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, GetCol)
{
    // create rot3
    const holo::geometry::Rot3 R = holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0));

    // call method
    const Vector3 c0 = R.GetCol(0u);
    const Vector3 c1 = R.GetCol(1u);
    const Vector3 c2 = R.GetCol(2u);

    // check results
    ASSERT_TRUE(Vector3(0.0, 1.0, 0.0).IsApprox(c0, 1e-15));
    ASSERT_TRUE(Vector3(-1.0, 0.0, 0.0).IsApprox(c1, 1e-15));
    ASSERT_TRUE(Vector3(0.0, 0.0, 1.0).IsApprox(c2, 1e-15));
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, AngleAxis2Rot3)
{
    const float64_t            pi = M_PI;
    const holo::geometry::Rot3 R  = holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0));
    const Vector3              w  = Vector3d(0.0, 0.0, pi / 2.0);
    const holo::geometry::Rot3 Q  = holo::geometry::Rot3::Rodriguez(w);
    const holo::geometry::Rot3 S  = holo::geometry::Rot3::Expmap(w);
    const Vector3              v  = holo::geometry::Rot3::Logmap(S);
    ASSERT_EQ(R.IsEqual(Q), true);
    ASSERT_EQ(R.IsEqual(S), true);
    ASSERT_EQ(v(0u) == w(0u), true);
    ASSERT_EQ(v(1u) == w(1u), true);
    ASSERT_EQ(v(2u) == w(2u), true);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, LogmapBoundaryConditions)
{
    const float64_t            theta1 = 0.0;
    const float64_t            theta2 = 5e-11;
    const float64_t            theta3 = M_PI;
    const holo::geometry::Rot3 R1     = holo::geometry::Rot3::Rz(theta1);
    const holo::geometry::Rot3 R2     = holo::geometry::Rot3::Rz(theta2);
    const holo::geometry::Rot3 R3     = holo::geometry::Rot3::Rz(theta3);
    const Vector3              v1     = holo::geometry::Rot3::Logmap(R1);
    const Vector3              v2     = holo::geometry::Rot3::Logmap(R2);
    const Vector3              v3     = holo::geometry::Rot3::Logmap(R3);
    ASSERT_EQ(v1(2u) == theta1, true);
    ASSERT_EQ(v2(2u) == theta2, true);
    ASSERT_EQ(v3(2u) == theta3, true);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, RQ)
{
    const float64_t            roll  = holo::geometry::Radian(45.0);
    const float64_t            pitch = holo::geometry::Radian(75.0);
    const float64_t            yaw   = holo::geometry::Radian(-135.0);
    const holo::geometry::Rot3 R     = holo::geometry::Rot3::RzRyRx(roll, pitch, yaw);
    const holo::geometry::Rot3 Q =
        holo::geometry::Rot3::Rz(yaw) * (holo::geometry::Rot3::Ry(pitch) * holo::geometry::Rot3::Rx(roll));
    ASSERT_EQ(R.IsEqual(Q), true);
    const Vector3 v = R.YPR();
    ASSERT_NEAR(holo::geometry::Degree(v(0u)), holo::geometry::Degree(yaw), 1e-9);
    ASSERT_NEAR(holo::geometry::Degree(v(1u)), holo::geometry::Degree(pitch), 1e-9);
    ASSERT_NEAR(holo::geometry::Degree(v(2u)), holo::geometry::Degree(roll), 1e-9);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, RQ_2)
{
    const float64_t            roll  = holo::geometry::Radian(45.0);
    const float64_t            pitch = holo::geometry::Radian(75.0);
    const float64_t            yaw   = holo::geometry::Radian(-135.0);
    const float64_t            yaw2   = holo::geometry::Radian(-15.0);

    const holo::geometry::Rot3 R     = holo::geometry::Rot3::RzRyRx(roll, pitch, yaw);
    const holo::geometry::Rot3 Q =
        holo::geometry::Rot3::Rz(yaw2) * (holo::geometry::Rot3::Ry(pitch) * holo::geometry::Rot3::Rx(roll));
    ASSERT_EQ(R.IsEqual(Q), false);
}


///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, Cast)
{
    const float64_t             roll  = holo::geometry::Radian(45.0);
    const float64_t             pitch = holo::geometry::Radian(75.0);
    const float64_t             yaw   = holo::geometry::Radian(-135.0);
    const holo::geometry::Rot3d r1    = holo::geometry::Rot3d::RzRyRx(roll, pitch, yaw);
    const holo::geometry::Rot3f r2    = (holo::geometry::Rot3f)r1;

    for (uint8_t i = 0u; i < 3u; ++i)
    {
        for (uint8_t j = 0u; j < 3u; ++j)
        {
            ASSERT_FLOAT_EQ(r1.ToMatrix()(i, j), r2.ToMatrix()(i, j));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
TEST(Rot3UnitTest, FromMatrix3)
{
    const holo::geometry::Rot3f p = holo::geometry::Rot3f::RzRyRx(33.0f, 44.0f, 55.0f);
    const holo::geometry::Rot3f q(p.ToMatrix());

    ASSERT_TRUE(p.IsEqual(q));
}

TEST(Rot3, SerializeDeserialize)
{
    holo::geometry::Rot3f   src, dst;
    src = Rot3f(holo::geometry::Rot3f::RzRyRx(1, 2, 3));
    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << src;

    EXPECT_EQ(serializer.GetSize(), src.GetSerializedSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;

    EXPECT_EQ(dst, src);
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
