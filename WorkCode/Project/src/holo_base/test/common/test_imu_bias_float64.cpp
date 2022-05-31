/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for ImuBiasd class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-06
 */

#include <gtest/gtest.h>
#include <holo/common/imu_bias.h>

using Vector3d = holo::numerics::VectorT<holo::float64_t, 3>;
using holo::common::Coordinate;
using holo::common::Timestamp;
using holo::geometry::Point3d;
using holo::common::ImuBiasd;

/**
 * @brief Test ImuBiasd()
 */
TEST(ImuBiasd, DefaultConstructor)
{
    const ImuBiasd imu_bias;

    ASSERT_EQ(Timestamp(), imu_bias.GetTimestamp());
    ASSERT_EQ(Coordinate(Coordinate::UNKNOWN), imu_bias.GetCoordinate());
    const Vector3d actual_angular_velocity_bias    = imu_bias.GetAngularVelocityBias<Vector3d>();
    const Vector3d actual_linear_acceleration_bias = imu_bias.GetLinearAccelerationBias<Vector3d>();
    ASSERT_EQ(Vector3d::Zero(), actual_angular_velocity_bias);
    ASSERT_EQ(Vector3d::Zero(), actual_linear_acceleration_bias);
    ASSERT_EQ(Vector3d::Zero(), actual_angular_velocity_bias);
    ASSERT_EQ(Vector3d::Zero(), actual_linear_acceleration_bias);
}

/**
 * @brief Test ImuBiasd::SetTimestamp() and ImuBiasd::GetTimestamp()
 */
TEST(ImuBiasd, SetAndGetTimestamp)
{
    ImuBiasd imu_bias;
    Timestamp expected_timestamp(5u, 10u);
    imu_bias.SetTimestamp(expected_timestamp);

    ASSERT_EQ(expected_timestamp, imu_bias.GetTimestamp());
}

/**
 * @brief Test ImuBiasd::SetCoordinate() and ImuBiasd::GetCoordinate()
 */
TEST(ImuBiasd, SetAndGetCoord)
{
    ImuBiasd imu_bias;
    Coordinate expected_coord(Coordinate::BODY);  // COORD_BODY
    imu_bias.SetCoordinate(expected_coord);

    ASSERT_EQ(expected_coord, imu_bias.GetCoordinate());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetAngularVelocityBias() with OutputType =
 * holo::geometry::Point3T
 */
TEST(ImuBiasd, GetAngularVelocityBiasPoint3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_angular_velocity_bias(1.0d, 2.0d, 3.0d);
    imu_bias.SetAngularVelocityBias(expected_angular_velocity_bias);

    ASSERT_EQ(expected_angular_velocity_bias, imu_bias.GetAngularVelocityBias<Point3d>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetAngularVelocityBias() with OutputType =
 * holo::Vector3T
 */
TEST(ImuBiasd, GetAngularVelocityBiasVector3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_angular_velocity_bias(1.0d, 2.0d, 3.0d);
    imu_bias.SetAngularVelocityBias(expected_angular_velocity_bias);
    Vector3d value = imu_bias.GetAngularVelocityBias<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetAngularVelocityBias() with OutputType =
 * std::vector
 */
TEST(ImuBiasd, GetAngularVelocityBiasStdVector)
{
    ImuBiasd imu_bias;
    const Point3d expected_angular_velocity_bias(1.0d, 2.0d, 3.0d);
    imu_bias.SetAngularVelocityBias(expected_angular_velocity_bias);
    std::vector<holo::float64_t> value = imu_bias.GetAngularVelocityBias<std::vector<holo::float64_t>>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetAngularVelocityBias(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasd, SetAngularVelocityBiasWithXYZValues)
{
    ImuBiasd imu_bias;
    imu_bias.SetAngularVelocityBias(1.0d, 2.0d, 3.0d);
    Vector3d value = imu_bias.GetAngularVelocityBias<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetAngularVelocityBias(Point3T const& value) 
 */
TEST(ImuBiasd, SetAngularVelocityBiasWithPoint3Type)
{
    ImuBiasd imu_bias;
    Point3d  point_value = {1.0d, 2.0d, 3.0d};
    imu_bias.SetAngularVelocityBias(point_value);
    Vector3d value = imu_bias.GetAngularVelocityBias<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetLinearAccelerationBias() with OutputType =
 * holo::geometry::Point3T
 */
TEST(ImuBiasd, GetLinearAccelerationBiasPoint3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_linear_acceleration_bias(1.0d, 2.0d, 3.0d);
    imu_bias.SetLinearAccelerationBias(expected_linear_acceleration_bias);

    ASSERT_EQ(expected_linear_acceleration_bias, imu_bias.GetLinearAccelerationBias<Point3d>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetLinearAccelerationBias() with OutputType =
 * holo::Vector3T
 */
TEST(ImuBiasd, GetLinearAccelerationBiasVector3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_linear_acceleration_bias(1.0d, 2.0d, 3.0d);
    imu_bias.SetLinearAccelerationBias(expected_linear_acceleration_bias);
    Vector3d value = imu_bias.GetLinearAccelerationBias<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetLinearAccelerationBias() with OutputType =
 * std::vector
 */
TEST(ImuBiasd, GetLinearAccelerationBiasStdVector)
{
    ImuBiasd imu_bias;
    const Point3d expected_linear_acceleration_bias(1.0d, 2.0d, 3.0d);
    imu_bias.SetLinearAccelerationBias(expected_linear_acceleration_bias);
    std::vector<holo::float64_t> value = imu_bias.GetLinearAccelerationBias<std::vector<holo::float64_t>>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetLinearAccelerationBias(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasd, SetLinearAccelerationBiasWithXYZValues)
{
    ImuBiasd imu_bias;
    imu_bias.SetLinearAccelerationBias(1.0d, 2.0d, 3.0d);
    Vector3d value = imu_bias.GetLinearAccelerationBias<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetLinearAccelerationBias(Point3T const& value) 
 */
TEST(ImuBiasd, SetLinearAccelerationBiasWithPoint3Type)
{
    ImuBiasd imu_bias;
    Point3d  point_value = {1.0d, 2.0d, 3.0d};
    imu_bias.SetLinearAccelerationBias(point_value);
    Vector3d value = imu_bias.GetLinearAccelerationBias<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetAngularVelocityBiasCovariance() with OutputType =
 * holo::geometry::Point3T
 */
TEST(ImuBiasd, GetAngularVelocityBiasCovariancePoint3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_angular_velocity_bias_cov(1.0d, 2.0d, 3.0d);
    imu_bias.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_cov);

    ASSERT_EQ(expected_angular_velocity_bias_cov, imu_bias.GetAngularVelocityBiasCovariance<Point3d>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetAngularVelocityBiasCovariance() with OutputType =
 * holo::Vector3T
 */
TEST(ImuBiasd, GetAngularVelocityBiasCovarianceVector3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_angular_velocity_bias_cov(1.0d, 2.0d, 3.0d);
    imu_bias.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_cov);
    Vector3d value = imu_bias.GetAngularVelocityBiasCovariance<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetAngularVelocityBiasCovariance() with OutputType =
 * std::vector
 */
TEST(ImuBiasd, GetAngularVelocityBiasCovarianceStdVector)
{
    ImuBiasd imu_bias;
    const Point3d expected_angular_velocity_bias_cov(1.0d, 2.0d, 3.0d);
    imu_bias.SetAngularVelocityBiasCovariance(expected_angular_velocity_bias_cov);
    std::vector<holo::float64_t> value = imu_bias.GetAngularVelocityBiasCovariance<std::vector<holo::float64_t>>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetAngularVelocityBiasCovariance(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasd, SetAngularVelocityBiasCovarianceWithXYZValues)
{
    ImuBiasd imu_bias;
    imu_bias.SetAngularVelocityBiasCovariance(1.0d, 2.0d, 3.0d);
    Vector3d value = imu_bias.GetAngularVelocityBiasCovariance<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetAngularVelocityBiasCovariance(Point3T const& value) 
 */
TEST(ImuBiasd, SetAngularVelocityBiasCovarianceWithPoint3Type)
{
    ImuBiasd imu_bias;
    Point3d  point_value = {1.0d, 2.0d, 3.0d};
    imu_bias.SetAngularVelocityBiasCovariance(point_value);
    Vector3d value = imu_bias.GetAngularVelocityBiasCovariance<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetLinearAccelerationBiasCovariance() with OutputType
 * = holo::geometry::Point3T
 */
TEST(ImuBiasd, GetLinearAccelerationBiasCovariancePoint3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_linear_acceleration_bias_cov(1.0d, 2.0d, 3.0d);
    imu_bias.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_cov);

    ASSERT_EQ(expected_linear_acceleration_bias_cov, imu_bias.GetLinearAccelerationBiasCovariance<Point3d>());
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetLinearAccelerationBiasCovariance() with OutputType
 * = holo::Vector3T
 */
TEST(ImuBiasd, GetLinearAccelerationBiasCovarianceVector3T)
{
    ImuBiasd imu_bias;
    const Point3d expected_linear_acceleration_bias_cov(1.0d, 2.0d, 3.0d);
    imu_bias.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_cov);
    Vector3d value = imu_bias.GetLinearAccelerationBiasCovariance<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test template <typename OutputType> OutputType ImuBiasd::GetLinearAccelerationBiasCovariance() with OutputType
 * = std::vector
 */
TEST(ImuBiasd, GetLinearAccelerationBiasCovarianceStdVector)
{
    ImuBiasd imu_bias;
    const Point3d expected_linear_acceleration_bias_cov(1.0d, 2.0d, 3.0d);
    imu_bias.SetLinearAccelerationBiasCovariance(expected_linear_acceleration_bias_cov);
    std::vector<holo::float64_t> value = imu_bias.GetLinearAccelerationBiasCovariance<std::vector<holo::float64_t>>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetLinearAccelerationBiasCovariance(ScalarType x, ScalarType y, ScalarType z)
 */
TEST(ImuBiasd, SetLinearAccelerationBiasCovarianceWithXYZValues)
{
    ImuBiasd imu_bias;
    imu_bias.SetLinearAccelerationBiasCovariance(1.0d, 2.0d, 3.0d);
    Vector3d value = imu_bias.GetLinearAccelerationBiasCovariance<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::SetLinearAccelerationBiasCovariance(Point3T const& value) 
 */
TEST(ImuBiasd, SetLinearAccelerationBiasCovarianceWithPoint3Type)
{
    ImuBiasd imu_bias;
    Point3d  point_value = {1.0d, 2.0d, 3.0d};
    imu_bias.SetLinearAccelerationBiasCovariance(point_value);
    Vector3d value = imu_bias.GetLinearAccelerationBiasCovariance<Vector3d>();

    ASSERT_EQ(1.0d, value[0]);
    ASSERT_EQ(2.0d, value[1]);
    ASSERT_EQ(3.0d, value[2]);
}

/**
 * @brief Test ImuBiasd::GetSerializedSize
 */
TEST(ImuBiasd, GetSerializedSize)
{
    ImuBiasd imu_bias;
    ASSERT_EQ(108, imu_bias.GetSerializedSize<4U>());
    ASSERT_EQ(112, imu_bias.GetSerializedSize<8U>());
}

/**
 * @brief Test ImuBiasd::Serialize and Deserialize
 */
TEST(ImuBiasd, SerializeAndDeserialize)
{
    ImuBiasd imu_bias1;
    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << imu_bias1;

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    ImuBiasd                    imu_bias2;
    deserializer >> imu_bias2;

    ASSERT_EQ(imu_bias1.GetTimestamp(), imu_bias2.GetTimestamp());
    ASSERT_EQ(imu_bias1.GetCoordinate(), imu_bias2.GetCoordinate());
    ASSERT_EQ(imu_bias1.GetAngularVelocityBias<Vector3d>(), imu_bias2.GetAngularVelocityBias<Vector3d>());
    ASSERT_EQ(imu_bias1.GetLinearAccelerationBias<Vector3d>(), imu_bias2.GetLinearAccelerationBias<Vector3d>());
    ASSERT_EQ(imu_bias1.GetAngularVelocityBiasCovariance<Vector3d>(), imu_bias2.GetAngularVelocityBiasCovariance<Vector3d>());
    ASSERT_EQ(imu_bias1.GetLinearAccelerationBiasCovariance<Vector3d>(), imu_bias2.GetLinearAccelerationBiasCovariance<Vector3d>());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
