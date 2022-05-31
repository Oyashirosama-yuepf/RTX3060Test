/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_geographical_transformation.cpp
 * @brief Unit test for conversion between lon/lat and utm.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-4-6
 */

#include <gtest/gtest.h>
#include <holo/utils/internal/geographical_transformation.h>
namespace holo
{
struct
{
    float64_t lon;
    float64_t lat;
    uint8_t   zone_id;
    bool_t    south_flag;
    float64_t utm_easting;
    float64_t utm_northing;
} utm_data[] = {{0.0, 0.0, 31, false, 166021.44, 0.0},           {0.0, -0.000001, 31, true, 166021.44, 9999999.89},
                {121.0, 31.0, 51, false, 309049.54, 3431318.84}, {81, 58, 44, false, 500000.00, 6428710.16},
                {5.5, 58, 32, false, 293174.17, 6434070.00},     {5.5, 75.5, 31, false, 569852.73, 8380870.57},
                {15.5, 75.5, 33, false, 513974.27, 8379453.93},  {25.5, 75.5, 35, false, 458080.91, 8379926.17},
                {35.5, 75.5, 37, false, 402232.24, 8382286.94}};

static size_t const data_size = 9;

TEST(GeographicalTransformation, LonLatToUtm)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        float64_t easting;
        float64_t northing;
        uint8_t   zone_id = holo::utils::LonLatGetUtmZoneId(utm_data[i].lon, utm_data[i].lat);
        holo::utils::LonLatToUtm(utm_data[i].lon, utm_data[i].lat, zone_id, (utm_data[i].lat < 0), easting, northing);
        ASSERT_EQ(utm_data[i].zone_id, zone_id);
        ASSERT_NEAR(utm_data[i].utm_easting, easting, 0.01);
        ASSERT_NEAR(utm_data[i].utm_northing, northing, 0.01);
    }
}

TEST(GeographicalTransformation, LonLatToUtmException)
{
        float64_t easting = 402232.24;
        float64_t northing = 8382286.94;
        uint8_t   zone_id = holo::utils::LonLatGetUtmZoneId(utm_data[5].lon, utm_data[5].lat);
        holo::utils::LonLatToUtm(0xffffffffffffffff, 0xffffffffffffffff, zone_id, false, easting, northing);
}

TEST(GeographicalTransformation, UtmToLonLat)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        float64_t easting    = utm_data[i].utm_easting;
        float64_t northing   = utm_data[i].utm_northing;
        uint8_t   zone_id    = utm_data[i].zone_id;
        bool_t    south_flag = utm_data[i].south_flag;

        float64_t lon = 0.0;
        float64_t lat = 0.0;

        holo::utils::UtmToLonLat(zone_id, south_flag, easting, northing, lon, lat);
        ASSERT_NEAR(utm_data[i].lon, lon, 0.0001);
        ASSERT_NEAR(utm_data[i].lat, lat, 0.0001);
    }
}

TEST(GeographicalTransformation, LonLatGetDistanceToZoneId)
{
    uint8_t zone_id = 49;
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(108, 40, zone_id), 0.1);
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(109, 40, zone_id), 0.1);
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(110, 40, zone_id), 0.1);
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(111, 40, zone_id), 0.1);
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(112, 40, zone_id), 0.1);
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(113, 40, zone_id), 0.1);
    EXPECT_NEAR(0, holo::utils::LonLatGetDistanceToZoneId(114, 40, zone_id), 0.1);
    EXPECT_NEAR(13571.76, holo::utils::LonLatGetDistanceToZoneId(107, 40, zone_id), 0.1);
    EXPECT_NEAR(13571.76, holo::utils::LonLatGetDistanceToZoneId(115, 40, zone_id), 0.1);
    EXPECT_NEAR(17717.04, holo::utils::LonLatGetDistanceToZoneId(107, 0, zone_id), 0.1);
    EXPECT_NEAR(17717.04, holo::utils::LonLatGetDistanceToZoneId(115, 0, zone_id), 0.1);
    EXPECT_NEAR(13571.76, holo::utils::LonLatGetDistanceToZoneId(107, -40, zone_id), 0.1);
    EXPECT_NEAR(13571.76, holo::utils::LonLatGetDistanceToZoneId(115, -40, zone_id), 0.1);
}

TEST(GeographicalTransformation, LonLatGetUtmZone)
{
    uint8_t   zone = holo::utils::LonLatGetUtmZone(1.0, 2.0);
}

TEST(GeographicalTransformation, BadGeographicalTransformationException)
{
    try
    {
        throw holo::exception::BadGeographicalTransformationException();
    }
    catch(...)
    {
    }
    
}

}  // namespace holo

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

