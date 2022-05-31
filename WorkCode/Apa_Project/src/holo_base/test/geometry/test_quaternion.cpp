/*!
 * \brief quaternion unit test
 * \author Yanwei Du
 * \date Aug-28-2019
 * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <gtest/gtest.h>
#include <holo/core/types.h>
#include <holo/geometry/quaternion.h>
#include <cmath>

using namespace holo;
using holo::numerics::Matrix3d;
using holo::numerics::Matrix3;
using holo::numerics::Vector3f;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, DefaultConstructor)
{
    const holo::geometry::Quaternionf quaternion;

    // check results
    ASSERT_FLOAT_EQ(1.0f, quaternion.GetW());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetX());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetY());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, ConstructFromArray)
{
    const float64_t  data[4u] = {0.1, 0.2, 0.3, 0.4};
    const holo::geometry::Quaternion quaternion(data, 4u);

    // check results
    const float64_t value = std::sqrt(0.1 * 0.1 + 0.2 * 0.2 + 0.3 * 0.3 + 0.4 * 0.4);
    ASSERT_DOUBLE_EQ(0.4 / value, quaternion.GetW());
    ASSERT_DOUBLE_EQ(0.1 / value, quaternion.GetX());
    ASSERT_DOUBLE_EQ(0.2 / value, quaternion.GetY());
    ASSERT_DOUBLE_EQ(0.3 / value, quaternion.GetZ());

    try
    {
        const holo::geometry::Quaternion quaternion2(data, 5u);
    }
    catch(...)
    {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, ConstructFromMatrix)
{
    const float64_t   costheta = std::cos(M_PI / 2.0);
    const float64_t   sintheta = std::sin(M_PI / 2.0);
    const Matrix3d    mat(costheta, -sintheta, 0.0, sintheta, costheta, 0.0, 0.0, 0.0, 1.0);
    const holo::geometry::Quaterniond quaternion(mat);

    // check results
    const float64_t expected = std::sqrt(2.0) / 2.0;
    ASSERT_DOUBLE_EQ(expected, quaternion.GetW());
    ASSERT_DOUBLE_EQ(0.0, quaternion.GetX());
    ASSERT_DOUBLE_EQ(0.0, quaternion.GetY());
    ASSERT_DOUBLE_EQ(expected, quaternion.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, CopyConstructor)
{
    // create quaternion
    const holo::geometry::Quaternion other(0.1, -0.2, 0.3, -0.4);

    // call method
    const holo::geometry::Quaternion quaternion(other);

    // check results
    ASSERT_DOUBLE_EQ(other.GetW(), quaternion.GetW());
    ASSERT_DOUBLE_EQ(other.GetX(), quaternion.GetX());
    ASSERT_DOUBLE_EQ(other.GetY(), quaternion.GetY());
    ASSERT_DOUBLE_EQ(other.GetZ(), quaternion.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, AssignmentOperator)
{
    // create quaternion
    const holo::geometry::Quaternion other(0.1, -0.2, 0.3, -0.4);

    // call method
    const holo::geometry::Quaternion quaternion = other;

    // check results
    ASSERT_DOUBLE_EQ(other.GetW(), quaternion.GetW());
    ASSERT_DOUBLE_EQ(other.GetX(), quaternion.GetX());
    ASSERT_DOUBLE_EQ(other.GetY(), quaternion.GetY());
    ASSERT_DOUBLE_EQ(other.GetZ(), quaternion.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, Cast)
{
    // create quaternion
    const holo::geometry::Quaterniond quat_d(0.1, -0.2, 0.3, -0.4);

    // call cast
    const holo::geometry::Quaternionf quat_f = quat_d.Cast<float32_t>();

    // check results
    const float32_t value = std::sqrt(0.1f * 0.1f + 0.2f * 0.2f + 0.3f * 0.3f + 0.4f * 0.4f);
    ASSERT_FLOAT_EQ(0.1f / value, quat_d.GetW());
    ASSERT_FLOAT_EQ(-0.2f / value, quat_d.GetX());
    ASSERT_FLOAT_EQ(0.3f / value, quat_d.GetY());
    ASSERT_FLOAT_EQ(-0.4f / value, quat_d.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, ToRotationMatrix)
{
    // create quaternion
    const float64_t  value = std::sqrt(2.0) / 2.0;
    const holo::geometry::Quaternion quaternion(value, 0.0, 0.0, value);

    // call method
    const Matrix3 actual = quaternion.ToRotationMatrix();

    // expected matrix
    const float64_t costheta = std::cos(M_PI / 2.0);
    const float64_t sintheta = std::sin(M_PI / 2.0);
    const Matrix3   expected(costheta, -sintheta, 0.0, sintheta, costheta, 0.0, 0.0, 0.0, 1.0);

    // check results
    const Matrix3 diff = expected - actual;
    ASSERT_NEAR(0.0, diff.GetNorm(), 1e-9);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, NormAndSquaredNorm)
{
    // create quaternion
    const holo::geometry::Quaternion quaternion(1.0, 0.0, 2.0, 2.0);

    // call norm
    const float64_t norm    = quaternion.GetNorm();
    const float64_t sq_norm = quaternion.GetSquaredNorm();

    // check results
    ASSERT_DOUBLE_EQ(1.0, norm);
    ASSERT_DOUBLE_EQ(1.0, sq_norm);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, Inverse)
{
    // create quaternion
    const float64_t  value = std::sqrt(2.0) / 2.0;
    const holo::geometry::Quaternion quat(value, 0.0, 0.0, value);

    // call inverse
    const holo::geometry::Quaternion quat_inv = quat.Inverse();

    // check results
    ASSERT_DOUBLE_EQ(value, quat_inv.GetW());
    ASSERT_DOUBLE_EQ(0.0, quat_inv.GetX());
    ASSERT_DOUBLE_EQ(0.0, quat_inv.GetY());
    ASSERT_DOUBLE_EQ(-value, quat_inv.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, Slerp)
{
    // create quaternion
    const holo::geometry::Quaternion left(1.0, 0.0, 0.0, 0.0);
    const holo::geometry::Quaternion right(0.0, 0.0, 0.0, 1.0);
    const float64_t  t = 0.5;

    // call slerp
    const holo::geometry::Quaternion actual = left.Slerp(t, right);

    // check results
    const float64_t value = std::sqrt(2.0) / 2.0;
    ASSERT_DOUBLE_EQ(value, actual.GetW());
    ASSERT_DOUBLE_EQ(0.0, actual.GetX());
    ASSERT_DOUBLE_EQ(0.0, actual.GetY());
    ASSERT_DOUBLE_EQ(value, actual.GetZ());

    try
    {
        const holo::geometry::Quaternion actual = left.Slerp(-1, right);
    }
    catch(...)
    {
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, Conjugate)
{
    // create quaternion
    const float64_t  value = std::sqrt(2.0) / 2.0;
    const holo::geometry::Quaternion quat(value, 0.0, 0.0, value);

    // call inverse
    const holo::geometry::Quaternion quat_conjugate = quat.GetConjugate();

    // check results
    ASSERT_DOUBLE_EQ(value, quat_conjugate.GetW());
    ASSERT_DOUBLE_EQ(0.0, quat_conjugate.GetX());
    ASSERT_DOUBLE_EQ(0.0, quat_conjugate.GetY());
    ASSERT_DOUBLE_EQ(-value, quat_conjugate.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, ElementAccess)
{
    // create quaternion
    const holo::geometry::Quaternionf quaternion(0.1f, -0.2f, 0.3f, -0.4f);

    // call methods and check results
    const float32_t value = std::sqrt(0.1f * 0.1f + 0.2f * 0.2f + 0.3f * 0.3f + 0.4f * 0.4f);
    ASSERT_FLOAT_EQ(0.1f / value, quaternion.GetW());
    ASSERT_FLOAT_EQ(-0.2f / value, quaternion.GetX());
    ASSERT_FLOAT_EQ(0.3f / value, quaternion.GetY());
    ASSERT_FLOAT_EQ(-0.4f / value, quaternion.GetZ());

    const Vector3f vec = quaternion.GetVector();
    ASSERT_FLOAT_EQ(-0.2f / value, vec(0u));
    ASSERT_FLOAT_EQ(0.3f / value, vec(1u));
    ASSERT_FLOAT_EQ(-0.4f / value, vec(2u));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, SetIdentity)
{
    // create quaternion
    holo::geometry::Quaternionf quaternion(0.1f, -0.2f, 0.3f, -0.4f);
    quaternion.SetIdentity();

    // check results
    ASSERT_FLOAT_EQ(1.0f, quaternion.GetW());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetX());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetY());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(Quaternion, Identity)
{
    // create quaternion
    const holo::geometry::Quaternionf quaternion = holo::geometry::Quaternionf::Identity();

    // check results
    ASSERT_FLOAT_EQ(1.0f, quaternion.GetW());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetX());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetY());
    ASSERT_FLOAT_EQ(0.0f, quaternion.GetZ());
}

TEST(Quaternion, GetSerializedSize)
{
    const holo::geometry::Quaternionf quaternion = holo::geometry::Quaternionf::Identity();
    ASSERT_EQ(16, quaternion.GetSerializedSize<4U>());
    ASSERT_EQ(16, quaternion.GetSerializedSize<8U>());
}

TEST(Quaternion, SerializeAndDeserialize)
{
    const holo::geometry::Quaternionf quaternion_input(1.0f, 2.0f, 3.0f, 4.0f);
    holo::geometry::Quaternionf quaternion_output;
    uint8_t buffer[128];
    holo::serialization::Serializer<> serializer(buffer, 128);
    serializer << quaternion_input;
    ASSERT_EQ(quaternion_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> quaternion_output;

    ASSERT_EQ(quaternion_input.GetW(), quaternion_output.GetW());
    ASSERT_EQ(quaternion_input.GetX(), quaternion_output.GetX());
    ASSERT_EQ(quaternion_input.GetY(), quaternion_output.GetY());
    ASSERT_EQ(quaternion_input.GetZ(), quaternion_output.GetZ());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
holo::int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
