#include <gtest/gtest.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <holo/utils/holo_root.h>

using holo::common::Coordinate;
using holo::common::SensorId;
using holo::common::VehicleLocation;

TEST(TestUtils, SystemPath)
{
    std::string path;
    path = holo::GetHoloConfigRootDirectory() + "/holo_sensors/lib_config/";
    ASSERT_EQ(holo::sensors::GetHoloSensorsLibConfigDirectory(), path);
    path = holo::GetHoloConfigRootDirectory() + "/holo_sensors/extrinsics/";
    ASSERT_EQ(holo::sensors::GetHoloSensorsExtrinsicsDirectory(), path);
}

TEST(TestUtils, SensorId)
{
    auto            x         = VehicleLocation::Location::LEFT_MOST;
    auto            y         = VehicleLocation::Location::TOP_MOST;
    VehicleLocation localtion = holo::sensors::StringToVehicleLocation("FRONT_WINDOW", "LEFT_MOST", "TOP_MOST");
    ASSERT_EQ(localtion, VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, x, y));
    SensorId sid = holo::sensors::StringToSensorId("GNSS", "GNSS_UBLOX_M8T", "FRONT_WINDOW", "LEFT_MOST", "TOP_MOST");
    SensorId sid2(SensorId::Category::GNSS, SensorId::Model::GNSS_UBLOX_M8T, localtion);
    ASSERT_EQ(sid, sid2);
    Coordinate coord =
        holo::sensors::StringToVehicleCoordinate("GNSS", "GNSS_UBLOX_M8T", "FRONT_WINDOW", "LEFT_MOST", "TOP_MOST");
    Coordinate coord2 = Coordinate::VehicleCoordinate(
        SensorId::Category::GNSS, SensorId::Model::GNSS_UBLOX_M8T, VehicleLocation::Plane::FRONT_WINDOW,
        VehicleLocation::Location::LEFT_MOST, VehicleLocation::Location::TOP_MOST);
    ASSERT_EQ(coord, coord2);
}

TEST(TestUtils, Gnss)
{
    double latitude  = -40.00;
    double longitude = 116.123;
    bool   r0        = holo::sensors::ConvertWgs84ToGcj02(latitude, longitude);
    ASSERT_FALSE(r0);
    latitude  = 40.00;
    longitude = -116.123;
    bool r1   = holo::sensors::ConvertWgs84ToGcj02(latitude, longitude);
    ASSERT_FALSE(r1);
    latitude  = 40.00;
    longitude = 116.123;
    bool r3   = holo::sensors::ConvertWgs84ToGcj02(latitude, longitude);
    ASSERT_TRUE(r3);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
