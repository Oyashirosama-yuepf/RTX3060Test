/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for imud class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#include <gtest/gtest.h>
#include <holo/common/imu.h>
#include <holo/geometry/point3.h>

using Vector3d = holo::numerics::VectorT<holo::float64_t, 3>;
using holo::common::Coordinate;
using holo::geometry::Point3d;
using holo::common::Imud;

/**
 * @brief Test Imud()
 */
TEST(Imud, DefaultConstructor)
{
    const Imud imu;

    ASSERT_EQ(holo::common::Timestamp(), imu.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::UNKNOWN), imu.GetCoordinate());
    const Vector3d actual_angular_velocity    = imu.GetAngularVelocity<Vector3d>();
    const Vector3d actual_linear_acceleration = imu.GetLinearAcceleration<Vector3d>();
    ASSERT_EQ(Vector3d::Zero(), actual_angular_velocity);
    ASSERT_EQ(Vector3d::Zero(), actual_linear_acceleration);
    ASSERT_EQ(Imud::Status::ALLGOOD, imu.GetStatus());
}

/**
 * @brief Test Imud::SetTimestamp() and Imud:GetTimestamp()
 */
TEST(Imud, SetAndGetTimestamp)
{
    Imud imu;
    holo::common::Timestamp expected_timestamp(5u, 10u);
    imu.SetTimestamp(expected_timestamp);

    ASSERT_EQ(expected_timestamp, imu.GetTimestamp());
}

/**
 * @brief Test Imud::SetCoordinate() and Imud::GetCoordinate()
 */
TEST(Imud, SetAndGetCoordinate)
{
    Imud imu;
    Coordinate expected_coord(Coordinate::BODY);  // COORD_BODY
    imu.SetCoordinate(expected_coord);

    ASSERT_EQ(expected_coord, imu.GetCoordinate());
}

/**
 * @brief Test Imud::SetStatus(Status status) and Imud::GetStatus()
 */
TEST(Imud, SetAndGetStatus)
{
    Imud imu;
    const Imud::Status expected_status = Imud::Status::ACCLZERROR;
    imu.SetStatus(expected_status);

    ASSERT_EQ(expected_status, imu.GetStatus());
}

/**
 * @brief Test template <typename OutputType> OutputType Imud::GetAngularVelocity() with OutputType =
 * holo::geometry::Point3T
 */
TEST(Imud, GetAngularVelocityPoint3T)
{
    Imud imu;
    const Point3d expected_angular_velocity(1.0d, 2.0d, 3.0d);
    imu.SetAngularVelocity(expected_angular_velocity);

    ASSERT_EQ(expected_angular_velocity, imu.GetAngularVelocity<Point3d>());
}

/**
 * @brief Test template <typename OutputType> OutputType Imud::GetAngularVelocity() with OutputType = holo::Vector3T
 */
TEST(Imud, GetAngularVelocityVector3T)
{
    Imud imu;
    const Point3d expected_angular_velocity(1.0d, 2.0d, 3.0d);
    imu.SetAngularVelocity(expected_angular_velocity);
    Vector3d value = imu.GetAngularVelocity<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType Imud::GetAngularVelocity() with OutputType = std::vector
 */
TEST(Imud, GetAngularVelocityStdVector)
{
    Imud imu;
    const Point3d expected_angular_velocity(1.0d, 2.0d, 3.0d);
    imu.SetAngularVelocity(expected_angular_velocity);
    std::vector<holo::float64_t> value = imu.GetAngularVelocity<std::vector<holo::float64_t>>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test Imud::SetAngularVelocity(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(Imud, SetAngularVelocityWithXYZValues)
{
    Imud imu;
    imu.SetAngularVelocity(1.0d, 2.0d, 3.0d);
    Vector3d value = imu.GetAngularVelocity<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test Imud::SetAngularVelocity(Point3T const& value) 
 */
TEST(Imud, SetAngularVelocityWithPoint3Type)
{
    Imud imu;
    Point3d point_value = {1.0d, 2.0d, 3.0d};
    imu.SetAngularVelocity(point_value);
    Vector3d value = imu.GetAngularVelocity<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType Imud::GetLinearAcceleration() with OutputType =
 * holo::geometry::Point3T
 */
TEST(Imud, GetLinearAccelerationPoint3T)
{
    Imud imu;
    const Point3d expected_angular_velocity(1.0d, 2.0d, 3.0d);
    imu.SetLinearAcceleration(expected_angular_velocity);

    ASSERT_EQ(expected_angular_velocity, imu.GetLinearAcceleration<Point3d>());
}

/**
 * @brief Test template <typename OutputType> OutputType Imud::GetLinearAcceleration() with OutputType = holo::Vector3T
 */
TEST(Imud, GetLinearAccelerationVector3T)
{
    Imud imu;
    const Point3d expected_angular_velocity(1.0d, 2.0d, 3.0d);
    imu.SetLinearAcceleration(expected_angular_velocity);
    Vector3d value = imu.GetLinearAcceleration<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType Imud::GetLinearAcceleration() with OutputType = std::vector
 */
TEST(Imud, GetLinearAccelerationStdVector)
{
    Imud imu;
    const Point3d expected_angular_velocity(1.0d, 2.0d, 3.0d);
    imu.SetLinearAcceleration(expected_angular_velocity);
    std::vector<holo::float64_t> value = imu.GetLinearAcceleration<std::vector<holo::float64_t>>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test Imud::SetLinearAcceleration(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(Imud, SetLinearAccelerationWithXYZValues)
{
    Imud imu;
    imu.SetLinearAcceleration(1.0d, 2.0d, 3.0d);
    Vector3d value = imu.GetLinearAcceleration<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test Imud::SetLinearAcceleration(Point3T const& value) 
 */
TEST(Imud, SetLinearAccelerationWithPoint3Type)
{
    Imud imu;
    Point3d point_value = {1.0d, 2.0d, 3.0d};
    imu.SetLinearAcceleration(point_value);
    Vector3d value = imu.GetLinearAcceleration<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test Imud::GetSerializedSize
 */
TEST(Imud, GetSerializedSize)
{
    Imud imu;
    ASSERT_EQ(64, imu.GetSerializedSize<4U>());
    ASSERT_EQ(64, imu.GetSerializedSize<8U>());
}

/**
 * @brief Test Imud::Serialize and Deserialize
 */
TEST(Imud, SerializeAndDeserialize)
{
    Imud imu1;
    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << imu1;
    ASSERT_EQ(imu1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    Imud                        imu2;
    deserializer >> imu2;

    ASSERT_EQ(imu1.GetTimestamp(), imu2.GetTimestamp());
    ASSERT_EQ(imu1.GetCoordinate(), imu2.GetCoordinate());
    ASSERT_EQ(imu1.GetStatus(), imu2.GetStatus());
    ASSERT_EQ(imu1.GetAngularVelocity<Vector3d>(), imu2.GetAngularVelocity<Vector3d>());
    ASSERT_EQ(imu1.GetLinearAcceleration<Vector3d>(), imu2.GetLinearAcceleration<Vector3d>());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
