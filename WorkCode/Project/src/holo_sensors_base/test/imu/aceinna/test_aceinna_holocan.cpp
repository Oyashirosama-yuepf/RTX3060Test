#include <gtest/gtest.h>
#include <holo/sensors/imu/aceinna/aceinna_holocan.h>

using namespace holo;
using namespace holo::sensors::aceinna;

static void Callback0(const holo::common::Imud& input, holo::common::Imud& output, bool& called)
{
    output = input;
    called = true;
}

TEST(AceinnaDriverT, AceinnaDriverT_HoloCanPacket1)
{
    Extrinsicf                                     extrinsic;
    AceinnaDriverT<HoloCanPacket>                  driver(extrinsic);
    holo::common::Imud                             out;
    bool                                           called = false;
    std::function<void(const holo::common::Imud&)> handler =
        std::bind(&Callback0, std::placeholders::_1, std::ref(out), std::ref(called));
    driver.InstallCallback(handler);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0xcf02980 >> 24) & 0xFF;
    raw_data[9]  = (0xcf02980 >> 16) & 0xFF;
    raw_data[10] = (0xcf02980 >> 8) & 0xFF;
    raw_data[11] = (0xcf02980 >> 0) & 0xFF;

    raw_data[12] = 0;
    raw_data[13] = 0;
    raw_data[14] = 0;
    raw_data[15] = 0;
    raw_data[16] = 0;
    raw_data[17] = 0;
    raw_data[18] = 0;
    raw_data[19] = 0;

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    uint32_t      des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    driver.ParseData(packet);

    raw_data[8]  = (0x8f02d80 >> 24) & 0xFF;
    raw_data[9]  = (0x8f02d80 >> 16) & 0xFF;
    raw_data[10] = (0x8f02d80 >> 8) & 0xFF;
    raw_data[11] = (0x8f02d80 >> 0) & 0xFF;

    raw_data[12] = (1000 >> 0) & 0xFF;
    raw_data[13] = (1000 >> 8) & 0xFF;
    raw_data[14] = (2000 >> 0) & 0xFF;
    raw_data[15] = (2000 >> 8) & 0xFF;
    raw_data[16] = (3000 >> 0) & 0xFF;
    raw_data[17] = (3000 >> 8) & 0xFF;
    raw_data[18] = 0;
    raw_data[19] = 0;
    packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);

    raw_data[8]  = (0xcf02a80 >> 24) & 0xFF;
    raw_data[9]  = (0xcf02a80 >> 16) & 0xFF;
    raw_data[10] = (0xcf02a80 >> 8) & 0xFF;
    raw_data[11] = (0xcf02a80 >> 0) & 0xFF;

    raw_data[12] = (4000 >> 0) & 0xFF;
    raw_data[13] = (4000 >> 8) & 0xFF;
    raw_data[14] = (5000 >> 0) & 0xFF;
    raw_data[15] = (5000 >> 8) & 0xFF;
    raw_data[16] = (6000 >> 0) & 0xFF;
    raw_data[17] = (6000 >> 8) & 0xFF;
    packet.Deserialize(raw_data, sizeof(raw_data));
    driver.ParseData(packet);
    ASSERT_TRUE(called);
    holo::common::Coordinate imu_coord = holo::common::Coordinate::VehicleCoordinate(
        holo::common::SensorId::Category::IMU, holo::common::SensorId::Model::IMU_ACEINNA_305,
        holo::common::VehicleLocation::Plane::CHASSIS, holo::common::VehicleLocation::Location::REAR,
        holo::common::VehicleLocation::Location::CENTER);
    ASSERT_EQ(out.GetCoordinate(), imu_coord);
    ASSERT_EQ(out.GetTimestamp().GetSec(), 123456789);
    ASSERT_EQ(out.GetTimestamp().GetNsec(), 987654321);
    ASSERT_EQ(out.GetStatus(), holo::common::Imud::Status::ALLGOOD);
    ASSERT_FLOAT_EQ(out.GetAngularVelocity<holo::geometry::Point3d>()[0], -3.8179078);
    ASSERT_FLOAT_EQ(out.GetAngularVelocity<holo::geometry::Point3d>()[1], 3.6815538);
    ASSERT_FLOAT_EQ(out.GetAngularVelocity<holo::geometry::Point3d>()[2], 3.5452001);
    ASSERT_FLOAT_EQ(out.GetLinearAcceleration<holo::geometry::Point3d>()[0], -310);
    ASSERT_FLOAT_EQ(out.GetLinearAcceleration<holo::geometry::Point3d>()[1], 300);
    ASSERT_FLOAT_EQ(out.GetLinearAcceleration<holo::geometry::Point3d>()[2], 290);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
