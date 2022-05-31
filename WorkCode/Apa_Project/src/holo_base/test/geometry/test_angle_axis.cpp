/*!
 * @file test_angle_axis.cpp
 * @brief angle unit test
 * @author duyanwei@holomatic.com
 * @date 2017-07-11
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>

#include <holo/geometry/angle_axis.h>

using namespace holo;
using holo::numerics::Vector3;
using holo::numerics::Matrix3;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, DefaultConstructor)
{
    // call method
    const holo::geometry::AngleAxis aa;

    // check results
    ASSERT_EQ(0.0, aa.GetAngle());
    ASSERT_EQ(Vector3::One() / std::sqrt(3.0), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ConstructFromAngleAndAxis)
{
    const float64_t angle = 0.5;
    const Vector3   axis(0.1, -0.2, 0.3);

    // call method
    const holo::geometry::AngleAxis aa(angle, axis);

    // check results
    ASSERT_EQ(angle, aa.GetAngle());
    ASSERT_EQ(axis / axis.GetNorm(), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ConstructFromAngleAndAxisException)
{
    const float64_t angle = 0.5;
    const Vector3   axis  = Vector3::Zero();

    // call method and check result
    ASSERT_THROW(const holo::geometry::AngleAxis aa(angle, axis), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ConstructFromQuaternion)
{
    const holo::geometry::Quaternion q(std::sqrt(2.0) / 2.0, 0.0, 0.0, std::sqrt(2.0) / 2.0);

    // call method
    const holo::geometry::AngleAxis aa(q);

    // check results
    ASSERT_EQ(M_PI / 2.0, aa.GetAngle());
    ASSERT_EQ(Vector3(0.0, 0.0, 1.0), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ConstructFromMatrix)
{
    const float64_t cos90 = std::cos(M_PI / 2.0);
    const float64_t sin90 = std::sin(M_PI / 2.0);
    const Matrix3   mat(cos90, 0.0, sin90, 0.0, 1.0, 0.0, -sin90, 0.0, cos90);

    // call method
    const holo::geometry::AngleAxis aa(mat);

    // check results
    ASSERT_EQ(M_PI / 2.0, aa.GetAngle());
    ASSERT_EQ(Vector3(0.0, 1.0, 0.0), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ConstructFromMatrixException)
{
    const Matrix3 mat = Matrix3::One();

    // call method and check result
    ASSERT_THROW(const holo::geometry::AngleAxis aa(mat), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ConstructFromRotationMatrix)
{
    const holo::geometry::Rot3 rot = holo::geometry::Rot3::Rx(M_PI / 2.0);

    // call method
    const holo::geometry::AngleAxis aa(rot);

    // check results
    ASSERT_EQ(M_PI / 2.0, aa.GetAngle());
    ASSERT_EQ(Vector3(1.0, 0.0, 0.0), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, CopyConstructor)
{
    const holo::geometry::Rot3      rot = holo::geometry::Rot3::Rx(M_PI / 2.0);
    const holo::geometry::AngleAxis aa(rot);

    // call method
    const holo::geometry::AngleAxis other(aa);

    // check results
    ASSERT_EQ(aa.GetAngle(), other.GetAngle());
    ASSERT_EQ(aa.GetAxis(), other.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, AssignmentOperator)
{
    const holo::geometry::Rot3      rot = holo::geometry::Rot3::Rx(M_PI / 2.0);
    const holo::geometry::AngleAxis aa(rot);

    // call method
    holo::geometry::AngleAxis other;
    other = aa;

    // check results
    ASSERT_EQ(aa.GetAngle(), other.GetAngle());
    ASSERT_EQ(aa.GetAxis(), other.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, AssignmentOperatorFromQuaternion)
{
    const holo::geometry::Rot3 rot = holo::geometry::Rot3::Rx(M_PI / 2.0);
    holo::geometry::AngleAxis  aa(rot);

    // call method
    const holo::geometry::Quaternion q(std::sqrt(2.0) / 2.0, 0.0, 0.0, std::sqrt(2.0) / 2.0);
    aa = q;

    // check results
    ASSERT_EQ(M_PI / 2.0, aa.GetAngle());
    ASSERT_EQ(Vector3(0.0, 0.0, 1.0), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, AssignmentOperatorFromMatrix)
{
    holo::geometry::AngleAxis aa;

    // call method
    const float64_t cos90 = std::cos(M_PI / 2.0);
    const float64_t sin90 = std::sin(M_PI / 2.0);
    const Matrix3   mat(cos90, 0.0, sin90, 0.0, 1.0, 0.0, -sin90, 0.0, cos90);
    aa = mat;

    // check results
    ASSERT_EQ(M_PI / 2.0, aa.GetAngle());
    ASSERT_EQ(Vector3(0.0, 1.0, 0.0), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, AssignmentOperatorFromMatrixException)
{
    holo::geometry::AngleAxis aa;

    // call method and check result
    ASSERT_THROW(aa = Matrix3::One(), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, GetterAndSetter)
{
    holo::geometry::AngleAxis       aa;
    const float64_t angle = 0.5;
    const Vector3   axis(0.1, -0.2, 0.3);

    // call method
    aa.SetAngle(angle);
    aa.SetAxis(axis);

    // check results
    ASSERT_EQ(angle, aa.GetAngle());
    ASSERT_EQ(axis / axis.GetNorm(), aa.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, SetAxisException)
{
    holo::geometry::AngleAxis     aa;
    const Vector3 axis = Vector3::Zero();

    // call method and check result
    ASSERT_THROW(aa.SetAxis(axis), std::runtime_error);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, Inverse)
{
    const float64_t angle = 0.5;
    const Vector3   axis(0.0, -1.0, 0.0);
    const holo::geometry::AngleAxis aa(angle, axis);

    // call method
    const holo::geometry::AngleAxis aa_inv = aa.Inverse();

    // check results
    ASSERT_EQ(-angle, aa_inv.GetAngle());
    ASSERT_EQ(axis / axis.GetNorm(), aa_inv.GetAxis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, IsApprox)
{
    const float64_t angle = 0.5;
    const Vector3   axis(0.1, -0.2, 0.3);
    const holo::geometry::AngleAxis aa(angle, axis);

    // call method
    const holo::geometry::AngleAxis other(aa);
    const holo::geometry::AngleAxis other2(0.6, axis);

    // check results
    ASSERT_TRUE(aa.IsApprox(other));
    ASSERT_FALSE(aa.IsApprox(other2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(AngleAxis, ToRotationMatrix)
{
    const float64_t cos90 = std::cos(M_PI / 2.0);
    const float64_t sin90 = std::sin(M_PI / 2.0);
    const Matrix3   mat(cos90, 0.0, sin90, 0.0, 1.0, 0.0, -sin90, 0.0, cos90);

    // call method
    const holo::geometry::AngleAxis aa(mat);

    // check results
    ASSERT_EQ(mat, aa.ToRotationMatrix());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t main(int32_t argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
