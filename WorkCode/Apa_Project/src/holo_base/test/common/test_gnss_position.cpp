/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for gnss position class
 * @author lichao@holomatic.com
 * @date Sep 13, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/gnss_position.h>

using holo::common::Coordinate;

/* Latitude of a known test point in Beijing */
static const holo::float64_t gLatitudeBeijing = 39.90421111;
/* Longitude of a known test point in Beijing */
static const holo::float64_t gLongitudeBeijing = 116.40741111;
/* UTM coordinate X of the known test point in Beijing */
static const holo::float64_t gUtmXBeijing = 449346.01934345544;
/* UTM coordinate Y of the known test point in Beijing */
static const holo::float64_t gUtmYBeijing = 4417293.7209900115;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructorDefaultTest, NormalInput)
{
    /* Create a GnssPosition by default constructor */
    const holo::GnssPosition gnss_position;

    /* Test default constructor */
    ASSERT_TRUE(holo::Timestamp() == gnss_position.GetTimestamp());
    ASSERT_TRUE(Coordinate(Coordinate::WGS84) == gnss_position.GetCoordinate()); // COORD_WGS84
    ASSERT_FLOAT_EQ(0.0f, gnss_position.GetLatitude());
    ASSERT_FLOAT_EQ(0.0f, gnss_position.GetLongitude());
    ASSERT_FLOAT_EQ(0.0f, gnss_position.GetAltitude());
    ASSERT_FLOAT_EQ(0.0f, gnss_position.GetLatitudeCovariance());
    ASSERT_FLOAT_EQ(0.0f, gnss_position.GetLongitudeCovariance());
    ASSERT_FLOAT_EQ(0.0f, gnss_position.GetAltitudeCovariance());
    ASSERT_TRUE(GnssPositionStatus::GNSS_POSITION_STATUS_ALLGOOD == gnss_position.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////l
TEST(ConstructByCopyTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position_other;
    gnss_position_other.SetTimestamp(holo::Timestamp(5u, 8u));
    gnss_position_other.SetCoordinate(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    gnss_position_other.SetLatitude(gLatitudeBeijing);
    gnss_position_other.SetLongitude(gLongitudeBeijing);
    gnss_position_other.SetAltitude(10.9f);
    gnss_position_other.SetLatitudeCovariance(1.2f);
    gnss_position_other.SetLongitudeCovariance(3.4f);
    gnss_position_other.SetAltitudeCovariance(5.6f);

    /* Create another GnssPosition from this GnssPosition */
    const holo::GnssPosition gnss_position(gnss_position_other);

    /* Test copy constructor */
    ASSERT_TRUE(gnss_position.GetTimestamp() == gnss_position_other.GetTimestamp());
    ASSERT_TRUE(gnss_position.GetCoordinate() == gnss_position_other.GetCoordinate());
    ASSERT_FLOAT_EQ(gnss_position.GetLatitude(), gnss_position_other.GetLatitude());
    ASSERT_FLOAT_EQ(gnss_position.GetLongitude(), gnss_position_other.GetLongitude());
    ASSERT_FLOAT_EQ(gnss_position.GetAltitude(), gnss_position_other.GetAltitude());
    ASSERT_FLOAT_EQ(gnss_position.GetLatitudeCovariance(), gnss_position_other.GetLatitudeCovariance());
    ASSERT_FLOAT_EQ(gnss_position.GetLongitudeCovariance(), gnss_position_other.GetLongitudeCovariance());
    ASSERT_FLOAT_EQ(gnss_position.GetAltitudeCovariance(), gnss_position_other.GetAltitudeCovariance());
    ASSERT_TRUE(gnss_position.GetStatus() == gnss_position_other.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(ConstructByMoveTest, NormalInput)
{
    /* Generate expected value */
    const holo::Timestamp         expected_timestamp(5u, 8u);
    const Coordinate              expected_coord                = Coordinate::Utm6Coordinate(50U, false); // COORD_WORLD
    const holo::float64_t         expected_latitude             = gLatitudeBeijing;
    const holo::float64_t         expected_longitude            = gLongitudeBeijing;
    const holo::float64_t         expected_altitude             = 10.9f;
    const holo::float64_t         expected_latitude_covariance  = 1.2f;
    const holo::float64_t         expected_longitude_covariance = 2.4f;
    const holo::float64_t         expected_altitude_covariance  = 3.6f;
    const enum GnssPositionStatus expected_status               = GnssPositionStatus::GNSS_POSITION_STATUS_ALLGOOD;

    /* Create a GnssPosition */
    holo::GnssPosition gnss_position_other;
    gnss_position_other.SetTimestamp(expected_timestamp);
    gnss_position_other.SetCoordinate(expected_coord);
    gnss_position_other.SetLatitude(expected_latitude);
    gnss_position_other.SetLongitude(expected_longitude);
    gnss_position_other.SetAltitude(expected_altitude);
    gnss_position_other.SetLatitudeCovariance(expected_latitude_covariance);
    gnss_position_other.SetLongitudeCovariance(expected_longitude_covariance);
    gnss_position_other.SetAltitudeCovariance(expected_altitude_covariance);
    gnss_position_other.SetStatus(expected_status);

    /* Create another GnssPosition from this GnssPosition */
    const holo::GnssPosition gnss_position = std::move(gnss_position_other);

    /* Test copy constructor */
    ASSERT_TRUE(expected_timestamp == gnss_position.GetTimestamp());
    ASSERT_TRUE(expected_coord == gnss_position.GetCoordinate());
    ASSERT_FLOAT_EQ(expected_latitude, gnss_position.GetLatitude());
    ASSERT_FLOAT_EQ(expected_longitude, gnss_position.GetLongitude());
    ASSERT_FLOAT_EQ(expected_altitude, gnss_position.GetAltitude());
    ASSERT_FLOAT_EQ(expected_latitude_covariance, gnss_position.GetLatitudeCovariance());
    ASSERT_FLOAT_EQ(expected_longitude_covariance, gnss_position.GetLongitudeCovariance());
    ASSERT_FLOAT_EQ(expected_altitude_covariance, gnss_position.GetAltitudeCovariance());
    ASSERT_TRUE(expected_status == gnss_position.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(CopyAssignmentOperatorTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position_other;
    gnss_position_other.SetTimestamp(holo::Timestamp(5u, 8u));
    gnss_position_other.SetCoordinate(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    gnss_position_other.SetLatitude(gLatitudeBeijing);
    gnss_position_other.SetLongitude(gLongitudeBeijing);
    gnss_position_other.SetAltitude(10.9f);
    gnss_position_other.SetLatitudeCovariance(1.2f);
    gnss_position_other.SetLongitudeCovariance(3.4f);
    gnss_position_other.SetAltitudeCovariance(5.6f);

    /* Create another GnssPosition from this GnssPosition */
    holo::GnssPosition gnss_position;
    gnss_position = gnss_position_other;

    /* Test copy constructor */
    ASSERT_TRUE(gnss_position.GetTimestamp() == gnss_position_other.GetTimestamp());
    ASSERT_TRUE(gnss_position.GetCoordinate() == gnss_position_other.GetCoordinate());
    ASSERT_FLOAT_EQ(gnss_position.GetLatitude(), gnss_position_other.GetLatitude());
    ASSERT_FLOAT_EQ(gnss_position.GetLongitude(), gnss_position_other.GetLongitude());
    ASSERT_FLOAT_EQ(gnss_position.GetAltitude(), gnss_position_other.GetAltitude());
    ASSERT_FLOAT_EQ(gnss_position.GetLatitudeCovariance(), gnss_position_other.GetLatitudeCovariance());
    ASSERT_FLOAT_EQ(gnss_position.GetLongitudeCovariance(), gnss_position_other.GetLongitudeCovariance());
    ASSERT_FLOAT_EQ(gnss_position.GetAltitudeCovariance(), gnss_position_other.GetAltitudeCovariance());
    ASSERT_TRUE(gnss_position.GetStatus() == gnss_position_other.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(MoveAssignmentOperatorTest, NormalInput)
{
    /* @todo(lichao@holoamtic.com) complete unit test */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetTimestampTest, NormalInput)
{
    /* Construct a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    holo::Timestamp expected_timestamp(5u, 10u);
    gnss_position.SetTimestamp(expected_timestamp);

    /* Test get timestamp function */
    ASSERT_TRUE(expected_timestamp == gnss_position.GetTimestamp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetCoordTest, NormalInput)
{
    /* Construct a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected coordinate id */
    Coordinate expected_coord(Coordinate(Coordinate::BODY)); // COORD_BODY

    /* Set coord id to GnssPosition */
    gnss_position.SetCoordinate(expected_coord);

    /* test result */
    ASSERT_TRUE(expected_coord == gnss_position.GetCoordinate());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetStatusTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const enum GnssPositionStatus expected_status = GnssPositionStatus::GNSS_POSITION_STATUS_ALLGOOD;
    gnss_position.SetStatus(expected_status);

    /* Test get status function */
    ASSERT_TRUE(expected_status == gnss_position.GetStatus());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLatitudeTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const holo::float64_t expected_latitude = gLatitudeBeijing;
    gnss_position.SetLatitude(expected_latitude);

    /* Test set and get latitude function */
    ASSERT_FLOAT_EQ(expected_latitude, gnss_position.GetLatitude());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLongitudeTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const holo::float64_t expected_longitude = gLongitudeBeijing;
    gnss_position.SetLongitude(expected_longitude);

    /* Test set and get longitude function */
    ASSERT_FLOAT_EQ(expected_longitude, gnss_position.GetLongitude());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetAltitudeTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const holo::float64_t expected_altitude = 10.9f;
    gnss_position.SetAltitude(expected_altitude);

    /* Test set and get altitude function */
    ASSERT_FLOAT_EQ(expected_altitude, gnss_position.GetAltitude());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLatitudeCovarianceTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const holo::float64_t expected_latitude_covariance = 1.2f;
    gnss_position.SetLatitudeCovariance(expected_latitude_covariance);

    /* Test set and get latitude convariance function */
    ASSERT_FLOAT_EQ(expected_latitude_covariance, gnss_position.GetLatitudeCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetLongitudeCovarianceTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const holo::float64_t expected_longitude_covariance = 2.4f;
    gnss_position.SetLongitudeCovariance(expected_longitude_covariance);

    /* Test set and get longitude covariance function */
    ASSERT_FLOAT_EQ(expected_longitude_covariance, gnss_position.GetLongitudeCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetAndGetAltitudeCovarianceTest, NormalInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition gnss_position;

    /* Generate expected value */
    const holo::float64_t expected_altitude_covariance = 3.6f;
    gnss_position.SetAltitudeCovariance(expected_altitude_covariance);

    /* Test set and get altitude covariance function */
    ASSERT_FLOAT_EQ(expected_altitude_covariance, gnss_position.GetAltitudeCovariance());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GetUtmPositionTest, BeijingInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition    gnss_position;
    const holo::float64_t expected_altitude(10.9);
    gnss_position.SetTimestamp(holo::Timestamp(5u, 8u));
    gnss_position.SetCoordinate(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD
    gnss_position.SetLatitude(gLatitudeBeijing);
    gnss_position.SetLongitude(gLongitudeBeijing);
    gnss_position.SetAltitude(expected_altitude);

    /* Generate expected values */
    const holo::geometry::Point3d expected_utm_position(gUtmXBeijing, gUtmYBeijing, expected_altitude);

    /* Test get utm position function */
    ASSERT_TRUE(expected_utm_position == gnss_position.GetUtmPosition());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(SetUtmPositionTest, BeijingInput)
{
    /* Create a GnssPosition */
    holo::GnssPosition    gnss_position;
    const holo::float64_t expected_altitude(10.9);
    gnss_position.SetTimestamp(holo::Timestamp(5u, 8u));
    gnss_position.SetCoordinate(Coordinate::Utm6Coordinate(50U, false)); // COORD_WORLD

    /* Set Utm position to gnss position */
    const holo::geometry::Point3d utm_position(gUtmXBeijing, gUtmYBeijing, expected_altitude);
    gnss_position.SetUtmPosition(utm_position);

    /* Test set Utm position function */
    const holo::float64_t tol = 1e-9;
    ASSERT_NEAR(gLongitudeBeijing, gnss_position.GetLongitude(), tol);
    ASSERT_NEAR(gLatitudeBeijing, gnss_position.GetLatitude(), tol);
    ASSERT_EQ(expected_altitude, gnss_position.GetAltitude());
}

TEST(Gnss_Position, GetSerializedSize)
{
    holo::GnssPosition    gnss_position;
    ASSERT_EQ(64, gnss_position.GetSerializedSize<4U>());
    ASSERT_EQ(64, gnss_position.GetSerializedSize<8U>());
}

TEST(Gnss_Position, SerializeAndDeserialize)
{
   holo::GnssPosition input_gnss_pos, output_gnss_pos;

    input_gnss_pos.SetTimestamp(holo::Timestamp(20, 30));
    input_gnss_pos.SetCoordinate(Coordinate(Coordinate::BODY));
    input_gnss_pos.SetStatus(holo::GnssPositionStatus::GNSS_POSITION_STATUS_INSUFFICIENT_OBS);

    input_gnss_pos.SetLatitude(1.0);
    input_gnss_pos.SetLongitude(2.0);
    input_gnss_pos.SetAltitude(3.0);
    input_gnss_pos.SetLatitudeCovariance(4.0);
    input_gnss_pos.SetLongitudeCovariance(5.0);
    input_gnss_pos.SetAltitudeCovariance(6.0);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>          serializer(buffer, 1024);
    serializer << input_gnss_pos;
    ASSERT_EQ(input_gnss_pos.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_gnss_pos;

    ASSERT_EQ(input_gnss_pos.GetTimestamp(), output_gnss_pos.GetTimestamp());
    ASSERT_EQ(input_gnss_pos.GetCoordinate(), output_gnss_pos.GetCoordinate());
    ASSERT_EQ(input_gnss_pos.GetStatus(), output_gnss_pos.GetStatus());
    ASSERT_EQ(input_gnss_pos.GetLatitude(), output_gnss_pos.GetLatitude());
    ASSERT_EQ(input_gnss_pos.GetLongitude(), output_gnss_pos.GetLongitude());
    ASSERT_EQ(input_gnss_pos.GetAltitude(), output_gnss_pos.GetAltitude());
    ASSERT_EQ(input_gnss_pos.GetLatitudeCovariance(), output_gnss_pos.GetLatitudeCovariance());
    ASSERT_EQ(input_gnss_pos.GetLongitudeCovariance(), output_gnss_pos.GetLongitudeCovariance());
    ASSERT_EQ(input_gnss_pos.GetAltitudeCovariance(), output_gnss_pos.GetAltitudeCovariance());
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
