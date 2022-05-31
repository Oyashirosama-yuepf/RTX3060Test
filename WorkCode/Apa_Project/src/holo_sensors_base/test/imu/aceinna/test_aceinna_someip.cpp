#include <gtest/gtest.h>
#include <holo/sensors/imu/aceinna/aceinna_someip.h>

using namespace holo;
using namespace holo::sensors::aceinna;

static void Callback0(const holo::common::Imud& input, holo::common::Imud& output, bool& called)
{
    output = input;
    called = true;
}

TEST(AceinnaDriverT, AceinnaDriverT_SomeipPacket)
{
    holo::common::Extrinsicf                       extrinsic;
    AceinnaDriverT<SomeipPacketType>               driver(extrinsic);
    holo::common::Imud                             out;
    bool                                           called = false;
    std::function<void(const holo::common::Imud&)> handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(out), std::ref(called));
    driver.InstallCallback(handler);

    struct ::Imuf imu_f;
    imuf_init(&imu_f);
    ::Timestamp imu_time;
    imu_time.sec  = 12345678;
    imu_time.nsec = 87654321;
    imuf_set_timestamp(&imu_f, &imu_time);
    imuf_set_status(&imu_f, ::IMU_STATUS_ALLGOOD);
    imuf_set_coordinate(&imu_f, 302320712);
    float32_t acc_x = 3.3;
    float32_t acc_y = 4.4;
    float32_t acc_z = 5.5;
    imuf_set_linear_acceleration_value(&imu_f, acc_x, acc_y, acc_z);
    float32_t av_x = 7.7;
    float32_t av_y = 8.8;
    float32_t av_z = 9.9;
    imuf_set_angular_velocity_value(&imu_f, av_x, av_y, av_z);
    uint8_t  ser_data[100];
    uint32_t ser_size = imuf_serialize(&imu_f, &ser_data[0], sizeof(ser_data));
    ASSERT_TRUE(ser_size > 0);

    SomeipPacketType packet;
    packet.SetMsgLength(52);
    packet.SetPayload(4, ser_data, ser_size);
    uint8_t some_ip_data[60];
    ser_size = packet.Serialize(some_ip_data, 60);
    ASSERT_EQ(ser_size, 60);
    driver.ParseData(packet);
    ASSERT_TRUE(called);
    holo::common::Coordinate imu_coord = holo::common::Coordinate::VehicleCoordinate(
        holo::common::SensorId::Category::IMU, holo::common::SensorId::Model::IMU_ACEINNA_305,
        holo::common::VehicleLocation::Plane::CHASSIS, holo::common::VehicleLocation::Location::REAR,
        holo::common::VehicleLocation::Location::CENTER);
    ASSERT_EQ(out.GetCoordinate(), imu_coord);
    ASSERT_EQ(out.GetTimestamp().GetSec(), 12345678);
    ASSERT_EQ(out.GetTimestamp().GetNsec(), 87654321);
    ASSERT_EQ(out.GetStatus(), holo::common::Imud::Status::ALLGOOD);
    ASSERT_FLOAT_EQ(out.GetAngularVelocity<holo::geometry::Point3d>()[0], 7.7);
    ASSERT_FLOAT_EQ(out.GetAngularVelocity<holo::geometry::Point3d>()[1], 8.8);
    ASSERT_FLOAT_EQ(out.GetAngularVelocity<holo::geometry::Point3d>()[2], 9.9);
    ASSERT_FLOAT_EQ(out.GetLinearAcceleration<holo::geometry::Point3d>()[0], 3.3);
    ASSERT_FLOAT_EQ(out.GetLinearAcceleration<holo::geometry::Point3d>()[1], 4.4);
    ASSERT_FLOAT_EQ(out.GetLinearAcceleration<holo::geometry::Point3d>()[2], 5.5);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
