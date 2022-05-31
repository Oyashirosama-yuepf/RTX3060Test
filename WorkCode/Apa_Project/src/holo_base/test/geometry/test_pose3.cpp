/*!
 * @brief Unit test for pose3.h
 * @author Li Chao (lichao@holomatic.ai)
 * @date Jul 18, 2017
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/geometry/angle.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/matrix.h>

using namespace holo;
using holo::numerics::Vector3f;
using holo::numerics::Vector6;
using holo::numerics::Matrix4;
using holo::geometry::Pose3d;
using holo::geometry::Pose3f;
using holo::geometry::Point3;

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, TransformFrom)
{
    float64_t              tol = 1e-8;
    holo::geometry::Pose3  M(holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0)), holo::geometry::Point3(1, 2, 3));
    holo::geometry::Point3 p(1.0, 0.0, 0.0);
    holo::geometry::Point3 q = M.TransformFrom(p);
    ASSERT_NEAR(q.GetX(), 1.0, tol);
    ASSERT_NEAR(q.GetY(), 3.0, tol);
    ASSERT_NEAR(q.GetZ(), 3.0, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, TransformTo)
{
    float64_t              tol = 1e-8;
    holo::geometry::Pose3  M(holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0)), holo::geometry::Point3(1, 2, 3));
    holo::geometry::Point3 p(1.0, 3.0, 3.0);
    holo::geometry::Point3 q = M.TransformTo(p);
    ASSERT_NEAR(q.GetX(), 1.0, tol);
    ASSERT_NEAR(q.GetY(), 0.0, tol);
    ASSERT_NEAR(q.GetZ(), 0.0, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, TransformFromVector)
{
    float32_t              tol = 1e-5f;
    holo::geometry::Pose3f M(holo::geometry::Rot3f::Rz(holo::geometry::Radian(90.0f)),
                             holo::geometry::Point3f(1.0f, 2.0f, 3.0f));
    Vector3f               p(1.0f, 0.0f, 0.0f);
    Vector3f               q = M.TransformFrom(p);
    ASSERT_NEAR(q(0u), 0.0f, tol);
    ASSERT_NEAR(q(1u), 1.0f, tol);
    ASSERT_NEAR(q(2u), 0.0f, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, TransformToVector)
{
    float32_t              tol = 1e-5f;
    holo::geometry::Pose3f M(holo::geometry::Rot3f::Rz(holo::geometry::Radian(90.0f)),
                             holo::geometry::Point3f(1.0f, 2.0f, 3.0f));
    Vector3f               p(0.0f, 1.0f, 0.0f);
    Vector3f               q = M.TransformTo(p);
    ASSERT_NEAR(q(0u), 1.0f, tol);
    ASSERT_NEAR(q(1u), 0.0f, tol);
    ASSERT_NEAR(q(2u), 0.0f, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, OperatorTimesPoint)
{
    float64_t              tol = 1e-8;
    holo::geometry::Pose3  M(holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0)), holo::geometry::Point3(1, 2, 3));
    holo::geometry::Point3 p(1.0, 0.0, 0.0);
    holo::geometry::Point3 q = M * p;
    ASSERT_NEAR(q.GetX(), 1.0, tol);
    ASSERT_NEAR(q.GetY(), 3.0, tol);
    ASSERT_NEAR(q.GetZ(), 3.0, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, OperatorTimesVector)
{
    float32_t              tol = 1e-5f;
    holo::geometry::Pose3f M(holo::geometry::Rot3f::Rz(holo::geometry::Radian(90.0f)),
                             holo::geometry::Point3f(1.0f, 2.0f, 3.0f));
    Vector3f               p(1.0f, 0.0f, 0.0f);
    Vector3f               q = M * p;
    ASSERT_NEAR(q(0u), 0.0f, tol);
    ASSERT_NEAR(q(1u), 1.0f, tol);
    ASSERT_NEAR(q(2u), 0.0f, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, OperatorTimesPose)
{
    const holo::geometry::Pose3 p1(holo::geometry::Rot3::Rz(holo::geometry::Radian(45.0)), holo::geometry::Point3());
    const holo::geometry::Pose3 p2(holo::geometry::Rot3::Rz(holo::geometry::Radian(45.0)), holo::geometry::Point3());

    // call method
    const holo::geometry::Pose3 actual = p1 * p2;

    // check results
    const holo::geometry::Pose3 expected(
        Matrix4(0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0));
    ASSERT_EQ(expected, actual);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, Compose)
{
    const holo::geometry::Pose3 p1(holo::geometry::Rot3::Rz(holo::geometry::Radian(45.0)), holo::geometry::Point3());
    const holo::geometry::Pose3 p2(holo::geometry::Rot3::Rz(holo::geometry::Radian(45.0)), holo::geometry::Point3());

    // call method
    const holo::geometry::Pose3 actual = p1.Compose(p2);

    // check results
    const holo::geometry::Pose3 expected(
        Matrix4(0.0, -1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0));
    ASSERT_EQ(expected, actual);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, Matrix)
{
    float64_t             tol = 1e-8;
    holo::geometry::Pose3 M(holo::geometry::Rot3::Rz(holo::geometry::Radian(90.0)), holo::geometry::Point3(1, 2, 3));
    Matrix4               A = M.ToMatrix();
    ASSERT_NEAR(A(0u, 0u), 0.0, tol);
    ASSERT_NEAR(A(0u, 1u), -1.0, tol);
    ASSERT_NEAR(A(0u, 2u), 0.0, tol);
    ASSERT_NEAR(A(0u, 3u), 1.0, tol);

    ASSERT_NEAR(A(1u, 0u), 1.0, tol);
    ASSERT_NEAR(A(1u, 1u), 0.0, tol);
    ASSERT_NEAR(A(1u, 2u), 0.0, tol);
    ASSERT_NEAR(A(1u, 3u), 2.0, tol);

    ASSERT_NEAR(A(2u, 0u), 0.0, tol);
    ASSERT_NEAR(A(2u, 1u), 0.0, tol);
    ASSERT_NEAR(A(2u, 2u), 1.0, tol);
    ASSERT_NEAR(A(2u, 3u), 3.0, tol);

    ASSERT_NEAR(A(3u, 0u), 0.0, tol);
    ASSERT_NEAR(A(3u, 1u), 0.0, tol);
    ASSERT_NEAR(A(3u, 2u), 0.0, tol);
    ASSERT_NEAR(A(3u, 3u), 1.0, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, LieAlgebra)
{
    holo::geometry::Pose3 M(holo::geometry::Rot3::RzRyRx(-0.2, 0.3, 0.2), holo::geometry::Point3(2.0, 3.0, 4.0));
    Vector6               vec = holo::geometry::Pose3::Logmap(M);
    holo::geometry::Pose3 N   = holo::geometry::Pose3::Expmap(vec);
    ASSERT_EQ(M.IsEqual(N), true);
}

///////////////////////////////////////////////////////////////////////////////
TEST(Pose3UnitTest, Cast)
{
    holo::geometry::Pose3d p1(holo::geometry::Rot3::RzRyRx(-0.2, 0.3, 0.2), holo::geometry::Point3(2.0, 3.0, 4.0));
    holo::geometry::Pose3f p2 = (holo::geometry::Pose3f)p1;

    for (uint8_t i = 0u; i < 3u; ++i)
    {
        for (uint8_t j = 0u; j < 3u; ++j)
        {
            ASSERT_FLOAT_EQ(p1.GetRotation().ToMatrix()(i, j), p2.GetRotation().ToMatrix()(i, j));
        }
    }

    ASSERT_FLOAT_EQ(p1.GetX(), p2.GetX());
    ASSERT_FLOAT_EQ(p1.GetY(), p2.GetY());
    ASSERT_FLOAT_EQ(p1.GetZ(), p2.GetZ());
}

TEST(Pose3UnitTest, GetSerializedSize)
{
    Pose3d p1(Rot3::RzRyRx(-0.2, 0.3, 0.2), Point3(2.0, 3.0, 4.0));
    ASSERT_EQ(96, p1.GetSerializedSize<4U>());
    ASSERT_EQ(96, p1.GetSerializedSize<8U>());
}

TEST(Pose3UnitTest, SerializeAndDeserializeWithFloat32)
{
    srand(time(0));

    float32_t xf = ((float32_t)(rand() % 1000)) * 0.001f;
    float32_t yf = ((float32_t)(rand() % 1000)) * 0.001f;
    float32_t zf = ((float32_t)(rand() % 1000)) * 0.001f;

    Pose3f    input_p3f(Rot3f::RzRyRx(xf, yf, zf),
                     Point3f((float32_t)(rand() % 1000), (float32_t)(rand() % 1000), (float32_t)(rand() % 1000)));
    Pose3f    output_p3f;

    uint8_t buf[128];
    holo::serialization::Serializer<> serializer(buf, 128);
    serializer << input_p3f;
    ASSERT_EQ(input_p3f.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<>      deserializerf(buf, serializer.GetSize());
    deserializerf >> output_p3f;

    ASSERT_EQ(input_p3f.GetX(), output_p3f.GetX());
    ASSERT_EQ(input_p3f.GetY(), output_p3f.GetY());
    ASSERT_EQ(input_p3f.GetZ(), output_p3f.GetZ());
    ASSERT_EQ(input_p3f.GetRotation().R00(), output_p3f.GetRotation().R00());
    ASSERT_EQ(input_p3f.GetRotation().R01(), output_p3f.GetRotation().R01());
    ASSERT_EQ(input_p3f.GetRotation().R02(), output_p3f.GetRotation().R02());
    ASSERT_EQ(input_p3f.GetRotation().R10(), output_p3f.GetRotation().R10());
    ASSERT_EQ(input_p3f.GetRotation().R11(), output_p3f.GetRotation().R11());
    ASSERT_EQ(input_p3f.GetRotation().R12(), output_p3f.GetRotation().R12());
    ASSERT_EQ(input_p3f.GetRotation().R20(), output_p3f.GetRotation().R20());
    ASSERT_EQ(input_p3f.GetRotation().R21(), output_p3f.GetRotation().R21());
    ASSERT_EQ(input_p3f.GetRotation().R22(), output_p3f.GetRotation().R22());
}

TEST(Pose3UnitTest, SerializeAndDeserializeWithFloat64)
{
    Pose3d  input_p3d = Pose3d(Rot3d(0.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0), Point3d(0.0, 0.0, 0.0));
    Pose3d  output_p3d;

    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << input_p3d;
    ASSERT_EQ(input_p3d.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<>      deserializer(buffer, serializer.GetSize());
    deserializer >> output_p3d;

    ASSERT_EQ(input_p3d.GetRotation().R00(), output_p3d.GetRotation().R00());
    ASSERT_EQ(input_p3d.GetRotation().R01(), output_p3d.GetRotation().R01());
    ASSERT_EQ(input_p3d.GetRotation().R02(), output_p3d.GetRotation().R02());
    ASSERT_EQ(input_p3d.GetRotation().R10(), output_p3d.GetRotation().R10());
    ASSERT_EQ(input_p3d.GetRotation().R11(), output_p3d.GetRotation().R11());
    ASSERT_EQ(input_p3d.GetRotation().R12(), output_p3d.GetRotation().R12());
    ASSERT_EQ(input_p3d.GetRotation().R20(), output_p3d.GetRotation().R20());
    ASSERT_EQ(input_p3d.GetRotation().R21(), output_p3d.GetRotation().R21());
    ASSERT_EQ(input_p3d.GetRotation().R22(), output_p3d.GetRotation().R22());
    ASSERT_EQ(input_p3d.GetTranslation().GetX(), output_p3d.GetTranslation().GetX());
    ASSERT_EQ(input_p3d.GetTranslation().GetY(), output_p3d.GetTranslation().GetY());
    ASSERT_EQ(input_p3d.GetTranslation().GetZ(), output_p3d.GetTranslation().GetZ());
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
