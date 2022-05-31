#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/utils/geographical_transformation.h>
#include <unity.h>

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

static void test_lonlat_to_utm(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t rc = RC_SUCCESS;
        float64_t easting;
        float64_t northing;
        uint8_t   zone_id = lonlat_get_utm_zone_id(utm_data[i].lon, utm_data[i].lat);
        rc = lonlat_to_utm(utm_data[i].lon, utm_data[i].lat, zone_id, (utm_data[i].lat < 0), &easting, &northing);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_EQUAL(utm_data[i].zone_id, zone_id);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].utm_easting, easting);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].utm_northing, northing);
    }
}

static void test_utm_to_lonlat(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t rc         = RC_SUCCESS;
        float64_t easting    = utm_data[i].utm_easting;
        float64_t northing   = utm_data[i].utm_northing;
        uint8_t   zone_id    = utm_data[i].zone_id;
        bool_t    south_flag = utm_data[i].south_flag;

        float64_t lon = 0.0;
        float64_t lat = 0.0;

        rc = utm_to_lonlat(zone_id, south_flag, easting, northing, &lon, &lat);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_DOUBLE_WITHIN(0.00001, utm_data[i].lon, lon);
        TEST_ASSERT_DOUBLE_WITHIN(0.00001, utm_data[i].lat, lat);
    }
}

static void test_point2_convert_lonlat_to_utm(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point2d src_pt;
        struct Point2d dst_pt;
        src_pt.x             = utm_data[i].lon;
        src_pt.y             = utm_data[i].lat;
        uint8_t      zone_id = lonlat_get_utm_zone_id(utm_data[i].lon, utm_data[i].lat);
        Coordinate_t coord   = coordinate_utm_create(zone_id, utm_data[i].south_flag, 0, 0);
        rc                   = point2_convert_lonlat_to_utm(&src_pt, coord, &dst_pt);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_EQUAL(utm_data[i].zone_id, zone_id);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].utm_easting, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].utm_northing, dst_pt.y);
    }
}

static void test_point3_convert_lonlat_to_utm(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point3d src_pt;
        struct Point3d dst_pt;
        src_pt.x             = utm_data[i].lon;
        src_pt.y             = utm_data[i].lat;
        uint8_t      zone_id = lonlat_get_utm_zone_id(utm_data[i].lon, utm_data[i].lat);
        Coordinate_t coord   = coordinate_utm_create(zone_id, utm_data[i].south_flag, 0, 0);
        rc                   = point3_convert_lonlat_to_utm(&src_pt, coord, &dst_pt);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_EQUAL(utm_data[i].zone_id, zone_id);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].utm_easting, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].utm_northing, dst_pt.y);
    }
}

static void test_point2_convert_lonlat_to_utm_and_coord(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point2d src_pt;
        struct Point2d dst_pt;
        Coordinate_t   dst_coord;
        src_pt.x                    = utm_data[i].lon;
        src_pt.y                    = utm_data[i].lat;
        uint32_t const     offset_x = (uint32_t)(utm_data[i].utm_easting / COORDINATE_UTM_GRID_WIDTH);
        uint32_t const     offset_y = (uint32_t)(utm_data[i].utm_northing / COORDINATE_UTM_GRID_HEIGHT);
        Coordinate_t const expected_coord =
            coordinate_utm6_create(utm_data[i].zone_id, utm_data[i].south_flag, offset_x, offset_y);
        float64_t const expected_utm_easting =
            utm_data[i].utm_easting - (float64_t)(offset_x * COORDINATE_UTM_GRID_WIDTH);
        float64_t const expected_utm_northing =
            utm_data[i].utm_northing - (float64_t)(offset_y * COORDINATE_UTM_GRID_HEIGHT);

        rc = point2_convert_lonlat_to_utm_and_coord(&src_pt, &dst_coord, &dst_pt);

        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_EQUAL(expected_coord, dst_coord);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_utm_easting, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_utm_northing, dst_pt.y);
    }
}

static void test_point3_convert_lonlat_to_utm_and_coord(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point3d src_pt;
        struct Point3d dst_pt;
        Coordinate_t   dst_coord;
        src_pt.x                    = utm_data[i].lon;
        src_pt.y                    = utm_data[i].lat;
        uint32_t const     offset_x = (uint32_t)(utm_data[i].utm_easting / COORDINATE_UTM_GRID_WIDTH);
        uint32_t const     offset_y = (uint32_t)(utm_data[i].utm_northing / COORDINATE_UTM_GRID_HEIGHT);
        Coordinate_t const expected_coord =
            coordinate_utm6_create(utm_data[i].zone_id, utm_data[i].south_flag, offset_x, offset_y);
        float64_t const expected_utm_easting =
            utm_data[i].utm_easting - (float64_t)(offset_x * COORDINATE_UTM_GRID_WIDTH);
        float64_t const expected_utm_northing =
            utm_data[i].utm_northing - (float64_t)(offset_y * COORDINATE_UTM_GRID_HEIGHT);

        rc = point3_convert_lonlat_to_utm_and_coord(&src_pt, &dst_coord, &dst_pt);

        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_EQUAL(expected_coord, dst_coord);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_utm_easting, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_utm_northing, dst_pt.y);
    }
}

static void test_point2_convert_utm_to_lonlat(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point2d src_pt;
        struct Point2d dst_pt;
        src_pt.x             = utm_data[i].utm_easting;
        src_pt.y             = utm_data[i].utm_northing;
        uint8_t      zone_id = lonlat_get_utm_zone_id(utm_data[i].lon, utm_data[i].lat);
        Coordinate_t coord   = coordinate_utm_create(zone_id, utm_data[i].south_flag, 0, 0);
        rc                   = point2_convert_utm_to_lonlat(coord, &src_pt, &dst_pt);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].lon, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].lat, dst_pt.y);
    }
}

static void test_point3_convert_utm_to_lonlat(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point3d src_pt;
        struct Point3d dst_pt;
        src_pt.x             = utm_data[i].utm_easting;
        src_pt.y             = utm_data[i].utm_northing;
        uint8_t      zone_id = lonlat_get_utm_zone_id(utm_data[i].lon, utm_data[i].lat);
        Coordinate_t coord   = coordinate_utm_create(zone_id, utm_data[i].south_flag, 0, 0);
        rc                   = point3_convert_utm_to_lonlat(coord, &src_pt, &dst_pt);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].lon, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, utm_data[i].lat, dst_pt.y);
    }
}

static void test_get_distance_to_zone_id(void)
{
    uint8_t zone_id = 49;
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(108, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(109, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(110, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(111, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(112, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(113, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(1.0, 0, lonlat_get_distance_to_zone_id(114, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 13571.76, lonlat_get_distance_to_zone_id(107, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 13571.76, lonlat_get_distance_to_zone_id(115, 40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 17717.04, lonlat_get_distance_to_zone_id(107, 0, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 17717.04, lonlat_get_distance_to_zone_id(115, 0, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 13571.76, lonlat_get_distance_to_zone_id(107, -40, zone_id));
    TEST_ASSERT_DOUBLE_WITHIN(0.1, 13571.76, lonlat_get_distance_to_zone_id(115, -40, zone_id));
}

static void test_point2_convert_utm_with_target_coord(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point2d src_pt;
        struct Point2d dst_pt;
        src_pt.x                     = utm_data[i].utm_easting;
        src_pt.y                     = utm_data[i].utm_northing;
        Coordinate_t const src_coord = coordinate_utm3_create(utm_data[i].zone_id, utm_data[i].south_flag, 0u, 0u);
        Coordinate_t const dst_coord = coordinate_utm3_create(utm_data[i].zone_id - 1u, utm_data[i].south_flag, 2u, 2u);
        struct Point2d     expected_pt;
        struct Point2d     src_pt_lonlat;
        src_pt_lonlat.x = utm_data[i].lon;
        src_pt_lonlat.y = utm_data[i].lat;
        point2_convert_lonlat_to_utm(&src_pt_lonlat, dst_coord, &expected_pt);

        rc = point2_convert_utm_with_target_coord(src_coord, &src_pt, dst_coord, &dst_pt);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_pt.x, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_pt.y, dst_pt.y);
    }
}

static void test_point3_convert_utm_with_target_coord(void)
{
    for (size_t i = 0; i < data_size; ++i)
    {
        retcode_t      rc = RC_SUCCESS;
        struct Point3d src_pt;
        struct Point3d dst_pt;
        src_pt.x                     = utm_data[i].utm_easting;
        src_pt.y                     = utm_data[i].utm_northing;
        Coordinate_t const src_coord = coordinate_utm3_create(utm_data[i].zone_id, utm_data[i].south_flag, 0u, 0u);
        Coordinate_t const dst_coord = coordinate_utm3_create(utm_data[i].zone_id - 1u, utm_data[i].south_flag, 2u, 2u);
        struct Point3d     expected_pt;
        struct Point3d     src_pt_lonlat;
        src_pt_lonlat.x = utm_data[i].lon;
        src_pt_lonlat.y = utm_data[i].lat;
        point3_convert_lonlat_to_utm(&src_pt_lonlat, dst_coord, &expected_pt);

        rc = point3_convert_utm_with_target_coord(src_coord, &src_pt, dst_coord, &dst_pt);
        TEST_ASSERT_EQUAL(RC_SUCCESS, rc);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_pt.x, dst_pt.x);
        TEST_ASSERT_DOUBLE_WITHIN(0.01, expected_pt.y, dst_pt.y);
    }
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_lonlat_to_utm);
    RUN_TEST(test_utm_to_lonlat);
    RUN_TEST(test_get_distance_to_zone_id);
    RUN_TEST(test_point2_convert_lonlat_to_utm_and_coord);
    RUN_TEST(test_point3_convert_lonlat_to_utm_and_coord);
    RUN_TEST(test_point2_convert_utm_with_target_coord);
    RUN_TEST(test_point3_convert_utm_with_target_coord);

    return UNITY_END();
}
