/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for ImuBiasf class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#include <gtest/gtest.h>
#include <holo/common/imu_bias.h>

using holo::common::Coordinate;
using holo::common::Timestamp;
using holo::geometry::Point3f;
using holo::common::ImuBiasf;
using holo::numerics::Vector3f;
using holo::numerics::Vector4d;

/**
 * @brief Test ImuBiasf()
 */
TEST(ImuBiasf, DefaultConstructor)
{
    const ImuBiasf imu_bias;

    ASSERT_EQ(Timestamp(), imu_bias.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::UNKNOWN), imu_bias.GetCoordinate());
    const Vector3f actual_angular_velocity_bias    = imu_bias.GetAngularVelocityBias<Vector3f>();
    const Vector3f actual_linear_acceleration_bias = imu_bias.GetLinearAccelerationBias<Vector3f>();
    ASSERT_EQ(Vector3f::Zero(), actual_angular_velocity_bias);
    ASSERT_EQ(Vector3f::Zero(), actual_linear_acceleration_bias);
    ASSERT_EQ(Vector3f::Zero(), actual_angular_velocity_bias);
    ASSERT_EQ(Vector3f::Zero(), actual_linear_acceleration_bias);
}

/**
 * @brief Test ImuBiasf::SetTimestamp() and ImuBiasf::GetTimestamp()
 */
TEST(ImuBiasf, SetAndGetTimestamp)
{
    ImuBiasf imu_bias;
    Timestamp expected_timestamp(5u, 10u);
    imu_bias.SetTimestamp(expected_timestamp);

    ASSERT_EQ(expected_timestamp, imu_bias.GetTimestamp());
}

/**
 * @brief Test ImuBiasf::SetCoordinate() and ImuBiasf::GetCoordinate()
 */
TEST(ImuBiasf, SetAndGetCoord)
{
    ImuBiasf imu_bias;
    Coordinate expected_coord(Coordinate::BODY);  // COORD_BODY
    imu_bias.SetCoordinate(expected_coord);

    ASSERT_EQ(expected_coord, imu_bias.GetCoordinate());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetAngularVelocityBias() with OutputType =
 * holo::geometry::Point3T
 */
TEST(ImuBiasf, GetAngularVelocityBiasPoint3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_angular_velocity_bias(1.0f, 2.0f, 3.0f);
    imu_bias.SetAngularVelocityBias(expected_angular_velocity_bias);

    ASSERT_EQ(expected_angular_velocity_bias, imu_bias.GetAngularVelocityBias<Point3f>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetAngularVelocityBias() with OutputType =
 * holo::Vector3T
 */
TEST(ImuBiasf, GetAngularVelocityBiasVector3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_angular_velocity_bias(1.0f, 2.0f, 3.0f);
    imu_bias.SetAngularVelocityBias(expected_angular_velocity_bias);
    Vector3f value = imu_bias.GetAngularVelocityBias<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetAngularVelocityBias() with OutputType =
 * std::vector
 */
TEST(ImuBiasf, GetAngularVelocityBiasStdVector)
{
    ImuBiasf imu_bias;
    const Point3f expected_angular_velocity_bias(1.0f, 2.0f, 3.0f);
    imu_bias.SetAngularVelocityBias(expected_angular_velocity_bias);
    std::vector<holo::float32_t> value = imu_bias.GetAngularVelocityBias<std::vector<holo::float32_t>>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetAngularVelocityBias(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasf, SetAngularVelocityBiasWithXYZValues)
{
    ImuBiasf imu_bias;
    imu_bias.SetAngularVelocityBias(1.0f, 2.0f, 3.0f);
    Vector3f value = imu_bias.GetAngularVelocityBias<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetAngularVelocityBias(Point3T const& value) 
 */
TEST(ImuBiasf, SetAngularVelocityBiasWithPoint3Type)
{
    ImuBiasf imu_bias;
    Point3f  point_value = {1.0f, 2.0f, 3.0f};
    imu_bias.SetAngularVelocityBias(point_value);
    Vector3f value = imu_bias.GetAngularVelocityBias<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetLinearAccelerationBias() with OutputType =
 * holo::geometry::Point3T
 */
TEST(ImuBiasf, GetLinearAccelerationBiasPoint3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_linear_acceleration_bias(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBias(expected_linear_acceleration_bias);

    ASSERT_EQ(expected_linear_acceleration_bias, imu_bias.GetLinearAccelerationBias<Point3f>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetLinearAccelerationBias() with OutputType =
 * holo::Vector3T
 */
TEST(ImuBiasf, GetLinearAccelerationBiasVector3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_linear_acceleration_bias(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBias(expected_linear_acceleration_bias);
    Vector3f value = imu_bias.GetLinearAccelerationBias<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetLinearAccelerationBias() with OutputType =
 * std::vector
 */
TEST(ImuBiasf, GetLinearAccelerationBiasStdVector)
{
    ImuBiasf imu_bias;
    const Point3f expected_linear_acceleration_bias(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBias(expected_linear_acceleration_bias);
    std::vector<holo::float32_t> value = imu_bias.GetLinearAccelerationBias<std::vector<holo::float32_t>>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetLinearAccelerationBias(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasf, SetLinearAccelerationBiasWithXYZValues)
{
    ImuBiasf imu_bias;
    imu_bias.SetLinearAccelerationBias(1.0f, 2.0f, 3.0f);
    Vector3f value = imu_bias.GetLinearAccelerationBias<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetLinearAccelerationBias(Point3T const& value) 
 */
TEST(ImuBiasf, SetLinearAccelerationBiasWithPoint3Type)
{
    ImuBiasf imu_bias;
    Point3f  point_value = {1.0f, 2.0f, 3.0f};
    imu_bias.SetLinearAccelerationBias(point_value);
    Vector3f value = imu_bias.GetLinearAccelerationBias<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetAngularVelocityBiasCovariance() with OutputType =
 * holo::geometry::Point3T
 */
TEST(ImuBiasf, GetAngularVelocityBiasCovariancePoint3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_angular_velocity_bias_cov(1.0f, 2.0f, 3.0f);
    imu_bias.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_cov);

    ASSERT_EQ(expected_angular_velocity_bias_cov, imu_bias.GetAngularVelocityBiasCovariance<Point3f>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetAngularVelocityBiasCovariance() with OutputType =
 * holo::Vector3T
 */
TEST(ImuBiasf, GetAngularVelocityBiasCovarianceVector3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_angular_velocity_bias_cov(1.0f, 2.0f, 3.0f);
    imu_bias.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_cov);
    Vector3f value = imu_bias.GetAngularVelocityBiasCovariance<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetAngularVelocityBiasCovariance() with OutputType =
 * std::vector
 */
TEST(ImuBiasf, GetAngularVelocityBiasCovarianceStdVector)
{
    ImuBiasf imu_bias;
    const Point3f expected_angular_velocity_bias_cov(1.0f, 2.0f, 3.0f);
    imu_bias.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_cov);
    std::vector<holo::float32_t> value = imu_bias.GetAngularVelocityBiasCovariance<std::vector<holo::float32_t>>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetAngularVelocityBiasCovariance(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasf, SetAngularVelocityBiasCovarianceWithXYZValues)
{
    ImuBiasf imu_bias;
    imu_bias.SetAngularVelocityBiasCovariance(1.0f, 2.0f, 3.0f);
    Vector3f value = imu_bias.GetAngularVelocityBiasCovariance<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetAngularVelocityBiasCovariance(Point3T const& value) 
 */
TEST(ImuBiasf, SetAngularVelocityBiasCovarianceWithPoint3Type)
{
    ImuBiasf imu_bias;
    Point3f  point_value = {1.0f, 2.0f, 3.0f};
    imu_bias.SetAngularVelocityBiasCovariance(point_value);
    Vector3f value = imu_bias.GetAngularVelocityBiasCovariance<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetLinearAccelerationBiasCovariance() with OutputType
 * = holo::geometry::Point3T
 */
TEST(ImuBiasf, GetLinearAccelerationBiasCovariancePoint3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_linear_acceleration_bias_cov(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_cov);

    ASSERT_EQ(expected_linear_acceleration_bias_cov, imu_bias.GetLinearAccelerationBiasCovariance<Point3f>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetLinearAccelerationBiasCovariance() with OutputType
 * = holo::Vector3T
 */
TEST(ImuBiasf, GetLinearAccelerationBiasCovarianceVector3T)
{
    ImuBiasf imu_bias;
    const Point3f expected_linear_acceleration_bias_cov(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_cov);
    Vector3f value = imu_bias.GetLinearAccelerationBiasCovariance<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasf::GetLinearAccelerationBiasCovariance() with OutputType
 * = std::vector
 */
TEST(ImuBiasf, GetLinearAccelerationBiasCovarianceStdVector)
{
    ImuBiasf imu_bias;
    const Point3f expected_linear_acceleration_bias_cov(1.0f, 2.0f, 3.0f);
    imu_bias.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_cov);
    std::vector<holo::float32_t> value = imu_bias.GetLinearAccelerationBiasCovariance<std::vector<holo::float32_t>>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetLinearAccelerationBiasCovariance(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasf, SetLinearAccelerationBiasCovarianceWithXYZValues)
{
    ImuBiasf imu_bias;
    imu_bias.SetLinearAccelerationBiasCovariance(1.0f, 2.0f, 3.0f);
    Vector3f value = imu_bias.GetLinearAccelerationBiasCovariance<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::SetLinearAccelerationBiasCovariance(Point3T const& value) 
 */
TEST(ImuBiasf, SetLinearAccelerationBiasCovarianceWithPoint3Type)
{
    ImuBiasf imu_bias;
    Point3f  point_value = {1.0f, 2.0f, 3.0f};
    imu_bias.SetLinearAccelerationBiasCovariance(point_value);
    Vector3f value = imu_bias.GetLinearAccelerationBiasCovariance<Vector3f>();

    ASSERT_EQ(1.0f, value[0]);
    ASSERT_EQ(2.0f, value[1]);
    ASSERT_EQ(3.0f, value[2]);
}

/**
 * @brief Test ImuBiasf::GetSerializedSize
 */
TEST(ImuBiasf, GetSerializedSize)
{
    ImuBiasf imu_bias;
    ASSERT_EQ(60, imu_bias.GetSerializedSize<4U>());
    ASSERT_EQ(80, imu_bias.GetSerializedSize<8U>());
}

/**
 * @brief Test ImuBiasf::Serialize and Deserialize
 */
TEST(ImuBiasf, SerializeAndDeserialize)
{
    ImuBiasf imu_bias1;
    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << imu_bias1;

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    ImuBiasf                    imu_bias2;
    deserializer >> imu_bias2;

    ASSERT_EQ(imu_bias1.GetTimestamp(), imu_bias2.GetTimestamp());
    ASSERT_EQ(imu_bias1.GetCoordinate(), imu_bias2.GetCoordinate());
    ASSERT_EQ(imu_bias1.GetAngularVelocityBias<Vector3f>(), imu_bias2.GetAngularVelocityBias<Vector3f>());
    ASSERT_EQ(imu_bias1.GetLinearAccelerationBias<Vector3f>(), imu_bias2.GetLinearAccelerationBias<Vector3f>());
    ASSERT_EQ(imu_bias1.GetAngularVelocityBiasCovariance<Vector3f>(), imu_bias2.GetAngularVelocityBiasCovariance<Vector3f>());
    ASSERT_EQ(imu_bias1.GetLinearAccelerationBiasCovariance<Vector3f>(), imu_bias2.GetLinearAccelerationBiasCovariance<Vector3f>());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
