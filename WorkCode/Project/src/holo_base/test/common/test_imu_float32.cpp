/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for imuf class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#include <gtest/gtest.h>
#include <holo/common/imu.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>

using Vector3f = holo::numerics::VectorT<holo::float32_t, 3>;
using holo::common::Coordinate;
using holo::geometry::Point3f;
using holo::common::Imuf;

/**
 * @brief Test Imuf()
 */
TEST(Imuf, DefaultConstructor)
{
    const Imuf imu;

    ASSERT_EQ(holo::common::Timestamp(), imu.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::UNKNOWN), imu.GetCoordinate());
    const Vector3f actual_angular_velocity    = imu.GetAngularVelocity<Vector3f>();
    const Vector3f actual_linear_acceleration = imu.GetLinearAcceleration<Vector3f>();
    ASSERT_EQ(Vector3f::Zero(), actual_angular_velocity);
    ASSERT_EQ(Vector3f::Zero(), actual_linear_acceleration);
    ASSERT_EQ(Imuf::Status::ALLGOOD, imu.GetStatus());
}

/**
 * @brief Test Imuf::SetTimestamp() and Imuf::GetTimestamp()
 */
TEST(Imuf, SetAndGetTimestamp)
{
    Imuf imu;
    holo::common::Timestamp expected_timestamp(5u, 10u);
    imu.SetTimestamp(expected_timestamp);

    ASSERT_EQ(expected_timestamp, imu.GetTimestamp());
}

/**
 * @brief Test Imuf::SetCoordinate() and Imuf::GetCoordinate()
 */
TEST(Imuf, SetAndGetCoordinate)
{
    Imuf imu;
    Coordinate expected_coord(Coordinate::BODY);  // COORD_BODY
    imu.SetCoordinate(expected_coord);

    ASSERT_EQ(expected_coord, imu.GetCoordinate());
}

/**
 * @brief Test Imuf::SetStatus(Status status) and Imuf::GetStatus()
 */
TEST(Imuf, SetAndGetStatus)
{
    Imuf imu;
    const Imuf::Status expected_status = Imuf::Status::ACCLZERROR;
    imu.SetStatus(expected_status);

    ASSERT_EQ(expected_status, imu.GetStatus());
}

/**
 * @brief Test template <typename OutputType> OutputType Imuf::GetAngularVelocity() with OutputType =
 * holo::geometry::Point3T
 */
TEST(Imuf, GetAngularVelocityPoint3T)
{
    Imuf imu;
    const Point3f expected_angular_velocity(1.0f, 2.0f, 3.0f);
    imu.SetAngularVelocity(expected_angular_velocity);

    ASSERT_EQ(expected_angular_velocity, imu.GetAngularVelocity<Point3f>());
}

/**
 * @brief Test template <typename OutputType> OutputType Imuf::GetAngularVelocity() with OutputType = holo::Vector3T
 */
TEST(Imuf, GetAngularVelocityVector3T)
{
    Imuf imu;
    const Point3f expected_angular_velocity(1.0f, 2.0f, 3.0f);
    imu.SetAngularVelocity(expected_angular_velocity);
    Vector3f value = imu.GetAngularVelocity<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType Imuf::GetAngularVelocity() with OutputType = std::vector
 */
TEST(Imuf, GetAngularVelocityStdVector)
{
    Imuf imu;
    const Point3f expected_angular_velocity(1.0f, 2.0f, 3.0f);
    imu.SetAngularVelocity(expected_angular_velocity);
    std::vector<holo::float32_t> value = imu.GetAngularVelocity<std::vector<holo::float32_t>>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test Imuf::SetAngularVelocity(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(Imuf, SetAngularVelocityWithXYZValues)
{
    Imuf imu;
    imu.SetAngularVelocity(1.0f, 2.0f, 3.0f);
    Vector3f value = imu.GetAngularVelocity<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test Imuf::SetAngularVelocity(Point3T const& value) 
 */
TEST(Imuf, SetAngularVelocityWithPoint3Type)
{
    Imuf imu;
    Point3f point_value = {1.0f, 2.0f, 3.0f};
    imu.SetAngularVelocity(point_value);
    Vector3f value = imu.GetAngularVelocity<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType Imuf::GetLinearAcceleration() with OutputType =
 * holo::geometry::Point3T
 */
TEST(Imuf, GetLinearAccelerationPoint3T)
{
    Imuf imu;
    const Point3f expected_angular_velocity(1.0f, 2.0f, 3.0f);
    imu.SetLinearAcceleration(expected_angular_velocity);

    ASSERT_EQ(expected_angular_velocity, imu.GetLinearAcceleration<Point3f>());
}

/**
 * @brief Test template <typename OutputType> OutputType Imuf::GetLinearAcceleration() with OutputType = holo::Vector3T
 */
TEST(Imuf, GetLinearAccelerationVector3T)
{
    Imuf imu;
    const Point3f expected_angular_velocity(1.0f, 2.0f, 3.0f);
    imu.SetLinearAcceleration(expected_angular_velocity);
    Vector3f value = imu.GetLinearAcceleration<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType Imuf::GetLinearAcceleration() with OutputType = std::vector
 */
TEST(Imuf, GetLinearAccelerationStdVector)
{
    Imuf imu;
    const Point3f expected_angular_velocity(1.0f, 2.0f, 3.0f);
    imu.SetLinearAcceleration(expected_angular_velocity);
    std::vector<holo::float32_t> value = imu.GetLinearAcceleration<std::vector<holo::float32_t>>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test Imuf::SetLinearAcceleration(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(Imuf, SetLinearAccelerationWithXYZValues)
{
    Imuf imu;
    imu.SetLinearAcceleration(1.0f, 2.0f, 3.0f);
    Vector3f value = imu.GetLinearAcceleration<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test Imuf::SetLinearAcceleration(Point3T const& value) 
 */
TEST(Imuf, SetLinearAccelerationWithPoint3Type)
{
    Imuf imu;
    Point3f point_value = {1.0f, 2.0f, 3.0f};
    imu.SetLinearAcceleration(point_value);
    Vector3f value = imu.GetLinearAcceleration<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test Imuf::GetSerializedSize
 */
TEST(Imuf, GetSerializedSize)
{
    Imuf imu;
    ASSERT_EQ(40, imu.GetSerializedSize<4U>());
    ASSERT_EQ(48, imu.GetSerializedSize<8U>());
}

/**
 * @brief Test Imuf::Serialize and Deserialize
 */
TEST(Imuf, SerializeAndDeserialize)
{
    Imuf imu1;
    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << imu1;
    ASSERT_EQ(imu1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    Imuf                        imu2;
    deserializer >> imu2;

    ASSERT_EQ(imu1.GetTimestamp(), imu2.GetTimestamp());
    ASSERT_EQ(imu1.GetCoordinate(), imu2.GetCoordinate());
    ASSERT_EQ(imu1.GetStatus(), imu2.GetStatus());
    ASSERT_EQ(imu1.GetAngularVelocity<Vector3f>(), imu2.GetAngularVelocity<Vector3f>());
    ASSERT_EQ(imu1.GetLinearAcceleration<Vector3f>(), imu2.GetLinearAcceleration<Vector3f>());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
