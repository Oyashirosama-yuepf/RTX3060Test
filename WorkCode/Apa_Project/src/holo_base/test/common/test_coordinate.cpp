/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_coordinate.cpp
 * @brief Unit test for Coordinate.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-15
 */

#include <gtest/gtest.h>
#include <holo/common/coordinate.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>

using holo::common::Coordinate;
using holo::common::SensorId;
using holo::common::VehicleLocation;

TEST(Coordinate, DefaultConstructor)
{
    Coordinate coord;
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(0u, coord.GetParam());
}

TEST(Coordinate, ConstructFromUint32)
{
    Coordinate coord(0x12345678);
    ASSERT_EQ(Coordinate::Type::VEHICLE, coord.GetType());
    ASSERT_EQ(0x02345678, coord.GetParam());
}

TEST(Coordinate, SetGetType)
{
    Coordinate coord;
    coord.SetType(Coordinate::Type::VEHICLE);
    ASSERT_EQ(Coordinate::Type::VEHICLE, coord.GetType());
    ASSERT_EQ(0u, coord.GetParam());

    coord.SetType(Coordinate::Type::WGS84);
    ASSERT_EQ(Coordinate::Type::WGS84, coord.GetType());
    ASSERT_EQ(0u, coord.GetParam());

    coord.SetType(Coordinate::Type::UTM6);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(0u, coord.GetParam());
}

TEST(Coordinate, SetGetParam)
{
    Coordinate coord;
    coord.SetParam(0x1234567);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(0x1234567, coord.GetParam());
}

TEST(Coordinate, SetGetVehicleSensorId)
{
    Coordinate coord;
    coord.SetVehicleSensorId(0x02345678);
    ASSERT_TRUE(0x02345678 == coord.GetVehicleSensorId());
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
}

TEST(Coordinate, SetGetUtmZoneId)
{
    Coordinate coord;
    coord.SetUtmZoneId(50U);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(50U, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(50U, coord.GetUtmZone());
    ASSERT_EQ(0, coord.GetUtmOffsetX());
    ASSERT_EQ(0, coord.GetUtmOffsetY());
}

TEST(Coordinate, SetGetUtmSouthFlag)
{
    Coordinate coord;
    coord.SetUtmSouthFlag(true);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(0, coord.GetUtmZoneId());
    ASSERT_EQ(true, coord.GetUtmSouthFlag());
    ASSERT_EQ((1 << 7), coord.GetUtmZone());
    ASSERT_EQ(0, coord.GetUtmOffsetX());
    ASSERT_EQ(0, coord.GetUtmOffsetY());
}

TEST(Coordinate, SetGetUtmZone)
{
    Coordinate coord;
    coord.SetUtmZone(50U);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(50U, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(50U, coord.GetUtmZone());
    ASSERT_EQ(0, coord.GetUtmOffsetX());
    ASSERT_EQ(0, coord.GetUtmOffsetY());

    coord.SetUtmZone(178U);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(50U, coord.GetUtmZoneId());
    ASSERT_EQ(true, coord.GetUtmSouthFlag());
    ASSERT_EQ(178U, coord.GetUtmZone());
    ASSERT_EQ(0, coord.GetUtmOffsetX());
    ASSERT_EQ(0, coord.GetUtmOffsetY());
}

TEST(Coordinate, SetGetUtmOffsetX)
{
    Coordinate coord;
    coord.SetUtmOffsetX(100);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(0, coord.GetUtmZone());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(100, coord.GetUtmOffsetX());
    ASSERT_EQ(0, coord.GetUtmOffsetY());
}

TEST(Coordinate, SetGetUtmOffsetY)
{
    Coordinate coord;
    coord.SetUtmOffsetY(100);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(0, coord.GetUtmZone());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(0, coord.GetUtmOffsetX());
    ASSERT_EQ(100, coord.GetUtmOffsetY());
}

TEST(Coordinate, SetGetDrVersion)
{
    Coordinate coord;
    coord.SetDrVersion(100U);
    ASSERT_EQ(Coordinate::Type::UNKNOWN, coord.GetType());
    ASSERT_EQ(100, coord.GetDrVersion());
}

TEST(Coordinate, AssignOperatorFromUint32)
{
    Coordinate coord;
    coord = 0x12345678u;
    ASSERT_EQ(Coordinate::Type::VEHICLE, coord.GetType());
    ASSERT_EQ(0x02345678u, coord.GetParam());
}

TEST(Coordinate, EqualOperatorWithUint32)
{
    Coordinate coord;
    coord = 0x12345678u;
    ASSERT_TRUE(coord == 0x12345678u);
    ASSERT_TRUE(0x12345678u == coord);
    ASSERT_FALSE(coord == 0u);
    ASSERT_FALSE(0u == coord);
}

TEST(Coordinate, NotEqualOperatorWithUint32)
{
    Coordinate coord;
    coord = 0x12345678u;
    ASSERT_FALSE(coord != 0x12345678u);
    ASSERT_FALSE(0x12345678u != coord);
    ASSERT_TRUE(coord != 0u);
    ASSERT_TRUE(0u != coord);
}

TEST(Coordinate, GetSerializedSize)
{
    Coordinate                        coord;
    ASSERT_EQ(4, coord.GetSerializedSize<4U>());
    ASSERT_EQ(4, coord.GetSerializedSize<8U>());
}

TEST(Coordinate, SerializeAndDeserialize)
{
    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);

    Coordinate coord1 = 0x12345678;
    Coordinate coord2 = 0;
    serializer << coord1;
    ASSERT_EQ(coord1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> coord2;
    ASSERT_EQ(coord1, coord2);
}

TEST(Coordinate, VehicleCoordinate)
{
    Coordinate coord = Coordinate::VehicleCoordinate(
        SensorId::Category::CAMERA, SensorId::Model::CAMERA_MOBILEYE_EQ3, VehicleLocation::Plane::FRONT_WINDOW,
        VehicleLocation::Location::CENTER, VehicleLocation::Location::TOP_MOST);
    ASSERT_EQ(Coordinate::Type::VEHICLE, coord.GetType());
    ASSERT_EQ(SensorId(SensorId::Category::CAMERA, SensorId::Model::CAMERA_MOBILEYE_EQ3,
                       VehicleLocation(VehicleLocation::Plane::FRONT_WINDOW, VehicleLocation::Location::CENTER,
                                       VehicleLocation::Location::TOP_MOST)),
              coord.GetVehicleSensorId());
}

TEST(Coordinate, Wgs84Coordinate)
{
    Coordinate coord = Coordinate::Wgs84Coordinate();
    ASSERT_EQ(Coordinate::Type::WGS84, coord.GetType());
    ASSERT_EQ(0u, coord.GetParam());
}

TEST(Coordinate, UtmCoordinateWithParameters)
{
    Coordinate coord = Coordinate::UtmCoordinate(50, false, 1, 2);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(50u, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(50u, coord.GetUtmZone());
    ASSERT_EQ(1u, coord.GetUtmOffsetX());
    ASSERT_EQ(2u, coord.GetUtmOffsetY());
}

TEST(Coordinate, UtmCoordinateWithLonLat)
{
    Coordinate coord = Coordinate::UtmCoordinate(113.0, 40.0);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(49U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());

    coord = Coordinate::UtmCoordinate(113.0, -40.0);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(true, coord.GetUtmSouthFlag());
    ASSERT_EQ(177U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());
}

TEST(Coordinate, UtmCoordinateWithPointType)
{
    holo::geometry::Point2d pt2(113.0, 40.0);
    Coordinate    coord = Coordinate::UtmCoordinate(pt2);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(49U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());

    pt2.SetY(-40.0);
    coord = Coordinate::UtmCoordinate(pt2);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(true, coord.GetUtmSouthFlag());
    ASSERT_EQ(177U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());

    holo::geometry::Point3d pt3(113.0, 40.0, 100.0);
    coord = Coordinate::UtmCoordinate(pt3);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(49U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());

    pt3.SetY(-40.0);
    coord = Coordinate::UtmCoordinate(pt3);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(true, coord.GetUtmSouthFlag());
    ASSERT_EQ(177U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());

    holo::numerics::Vector3d v3(113.0, 40.0, 100.0);
    coord = Coordinate::UtmCoordinate(v3);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(49U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());

    v3(1) = -40.0;
    coord = Coordinate::UtmCoordinate(v3);
    ASSERT_EQ(Coordinate::Type::UTM6, coord.GetType());
    ASSERT_EQ(49U, coord.GetUtmZoneId());
    ASSERT_EQ(true, coord.GetUtmSouthFlag());
    ASSERT_EQ(177U, coord.GetUtmZone());
    ASSERT_EQ(0U, coord.GetUtmOffsetX());
    ASSERT_EQ(0U, coord.GetUtmOffsetY());
}

TEST(Coordinate, Utm3CoordinateWithParameters)
{
    Coordinate coord = Coordinate::Utm3Coordinate(50, false, 1, 2);
    ASSERT_EQ(Coordinate::Type::UTM3, coord.GetType());
    ASSERT_EQ(50u, coord.GetUtmZone());
    ASSERT_EQ(false, coord.GetUtmSouthFlag());
    ASSERT_EQ(1u, coord.GetUtmOffsetX());
    ASSERT_EQ(2u, coord.GetUtmOffsetY());
}

TEST(Coordinate, GCJ02Coordinate)
{
    Coordinate coord = Coordinate::Gcj02Coordinate();
    ASSERT_EQ(Coordinate::Type::GCJ02, coord.GetType());
    ASSERT_EQ(0u, coord.GetParam());
}

TEST(Coordinate, DrCoordinate)
{
    Coordinate coord = Coordinate::DrCoordinate(0U);
    ASSERT_EQ(Coordinate::Type::DR, coord.GetType());
    ASSERT_EQ(0u, coord.GetDrVersion());
}

TEST(CoordinateConvert, LonLatToUtm)
{
    Coordinate    coord1 = Coordinate::UtmCoordinate(112.9, 40.0);
    Coordinate    coord2 = Coordinate::UtmCoordinate(113.1, 40.0);
    holo::geometry::Point2d pt1(112.9, 39.9);
    holo::geometry::Point2d pt2(113.1, 40.0);
    holo::geometry::Point2d pt3(113.3, 40.1);
    holo::geometry::Point3d utm1_pt1, utm1_pt2, utm1_pt3;
    holo::geometry::Point3d utm2_pt1, utm2_pt2, utm2_pt3;
    Coordinate::PointConvertLonLatToUtm(pt1, coord1, utm1_pt1);
    Coordinate::PointConvertLonLatToUtm(pt2, coord1, utm1_pt2);
    Coordinate::PointConvertLonLatToUtm(pt3, coord1, utm1_pt3);

    Coordinate::PointConvertLonLatToUtm(pt1, coord2, utm2_pt1);
    Coordinate::PointConvertLonLatToUtm(pt2, coord2, utm2_pt2);
    Coordinate::PointConvertLonLatToUtm(pt3, coord2, utm2_pt3);

    ASSERT_TRUE(static_cast<holo::geometry::Point3d>(utm1_pt1 - utm1_pt2)
                    .IsEqual(static_cast<holo::geometry::Point3d>(utm2_pt1 - utm2_pt2), 10e-4));
    ASSERT_TRUE(static_cast<holo::geometry::Point3d>(utm1_pt2 - utm1_pt3)
                    .IsEqual(static_cast<holo::geometry::Point3d>(utm2_pt2 - utm2_pt3), 10e-4));
    ASSERT_TRUE(static_cast<holo::geometry::Point3d>(utm1_pt3 - utm1_pt1)
                    .IsEqual(static_cast<holo::geometry::Point3d>(utm2_pt3 - utm2_pt1), 10e-4));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

