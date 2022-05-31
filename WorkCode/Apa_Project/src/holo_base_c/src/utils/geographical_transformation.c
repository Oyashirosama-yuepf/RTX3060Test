/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geographical_transformation.c
 * @brief Conversion between lat/lon and utm.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-4-3
 */

#include <assert.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/point2.h>
#include <holo_c/geometry/point3.h>
#include <holo_c/utils/geographical_transformation.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

static const float64_t deg2rad = M_PI / 180.0;
static const float64_t rad2deg = 180.0 / M_PI;

// WGS-84 reference system parameters
static const float64_t earth_radius = 6378137;
static const float64_t ecc_squared  = 0.00669438;
static const float64_t k0           = 0.9996;

retcode_t lonlat_to_utm(float64_t lon, float64_t lat, uint8_t zone_id, bool_t south_flag, float64_t* easting,
                        float64_t* northing)
{
    retcode_t rc = RC_SUCCESS;
    float64_t long_origin;
    float64_t ecc_prime_squared;
    float64_t n, t, c, a, m;
    float64_t long_temp;

    float64_t lat_rad;
    float64_t long_rad;
    float64_t long_originRad;

    assert(northing != NULL);
    assert(easting != NULL);
    assert(isnan(lat) == 0);
    assert(isnan(lon) == 0);

    long_temp = (lon + 180) - (int)((lon + 180) / 360) * 360 - 180;  // -180.00 .. 179.9
    lat_rad   = lat * deg2rad;
    long_rad  = long_temp * deg2rad;

    long_origin    = zone_id * 6 - 183;  //*+3 puts origin in middle of zone
    long_originRad = long_origin * deg2rad;

    ecc_prime_squared = (ecc_squared) / (1 - ecc_squared);

    n = earth_radius / sqrt(1 - ecc_squared * sin(lat_rad) * sin(lat_rad));
    t = tan(lat_rad) * tan(lat_rad);
    c = ecc_prime_squared * cos(lat_rad) * cos(lat_rad);
    a = cos(lat_rad) * (long_rad - long_originRad);

    m = earth_radius * ((1 - ecc_squared / 4 - 3 * ecc_squared * ecc_squared / 64 -
                         5 * ecc_squared * ecc_squared * ecc_squared / 256) *
                            lat_rad -
                        (3 * ecc_squared / 8 + 3 * ecc_squared * ecc_squared / 32 +
                         45 * ecc_squared * ecc_squared * ecc_squared / 1024) *
                            sin(2 * lat_rad) +
                        (15 * ecc_squared * ecc_squared / 256 + 45 * ecc_squared * ecc_squared * ecc_squared / 1024) *
                            sin(4 * lat_rad) -
                        (35 * ecc_squared * ecc_squared * ecc_squared / 3072) * sin(6 * lat_rad));

    *easting = (float64_t)(k0 * n *
                               (a + (1 - t + c) * a * a * a / 6 +
                                (5 - 18 * t + t * t + 72 * c - 58 * ecc_prime_squared) * a * a * a * a * a / 120) +
                           500000.0);

    *northing = (float64_t)(
        k0 * (m + n * tan(lat_rad) *
                      (a * a / 2 + (5 - t + 9 * c + 4 * c * c) * a * a * a * a / 24 +
                       (61 - 58 * t + t * t + 600 * c - 330 * ecc_prime_squared) * a * a * a * a * a * a / 720)));
    if (south_flag)
    {
        *northing += 10000000.0;  // 10000000 meter offset for southern hemisphere
    }

    if (isnan(*easting) || isnan(*northing))
    {
        rc = RC_FAIL;
    }

    return rc;
}

retcode_t utm_to_lonlat(uint8_t zone_id, bool_t south_flag, float64_t easting, float64_t northing, float64_t* lon,
                        float64_t* lat)
{
    retcode_t rc = RC_SUCCESS;
    float64_t ecc_prime_squared;
    float64_t e1;
    float64_t n1, t1, c1, r1, d, m;
    float64_t long_origin;
    float64_t mu, phi1_rad;
    float64_t x, y;

    assert(lat != NULL);
    assert(lon != NULL);
    assert(isnan(northing) == 0);
    assert(isnan(easting) == 0);

    e1 = (1 - sqrt(1 - ecc_squared)) / (1 + sqrt(1 - ecc_squared));

    x = easting - 500000.0;  // remove 500,000 meter offset for longitude
    y = northing;
    if (south_flag)
    {
        y -= 10000000.0;
    }

    long_origin = (zone_id - 1) * 6 - 180 + 3;  // +3 puts origin in middle of zone

    ecc_prime_squared = (ecc_squared) / (1 - ecc_squared);

    m  = y / k0;
    mu = m / (earth_radius * (1 - ecc_squared / 4 - 3 * ecc_squared * ecc_squared / 64 -
                              5 * ecc_squared * ecc_squared * ecc_squared / 256));

    phi1_rad = mu + (3 * e1 / 2 - 27 * e1 * e1 * e1 / 32) * sin(2 * mu) +
               (21 * e1 * e1 / 16 - 55 * e1 * e1 * e1 * e1 / 32) * sin(4 * mu) +
               (151 * e1 * e1 * e1 / 96) * sin(6 * mu);

    n1 = earth_radius / sqrt(1 - ecc_squared * sin(phi1_rad) * sin(phi1_rad));
    t1 = tan(phi1_rad) * tan(phi1_rad);
    c1 = ecc_prime_squared * cos(phi1_rad) * cos(phi1_rad);
    r1 = earth_radius * (1 - ecc_squared) / pow(1 - ecc_squared * sin(phi1_rad) * sin(phi1_rad), 1.5);
    d  = x / (n1 * k0);

    *lat =
        phi1_rad - (n1 * tan(phi1_rad) / r1) *
                       (d * d / 2 - (5 + 3 * t1 + 10 * c1 - 4 * c1 * c1 - 9 * ecc_prime_squared) * d * d * d * d / 24 +
                        (61 + 90 * t1 + 298 * c1 + 45 * t1 * t1 - 252 * ecc_prime_squared - 3 * c1 * c1) * d * d * d *
                            d * d * d / 720);
    *lat = *lat * rad2deg;

    *lon = (d - (1 + 2 * t1 + c1) * d * d * d / 6 +
            (5 - 2 * c1 + 28 * t1 - 3 * c1 * c1 + 8 * ecc_prime_squared + 24 * t1 * t1) * d * d * d * d * d / 120) /
           cos(phi1_rad);
    *lon = long_origin + *lon * rad2deg;

    if (isnan(*lat) || isnan(*lon))
    {
        rc = RC_FAIL;
    }

    return rc;
}

uint8_t lonlat_get_utm_zone_id(float64_t lon, float64_t lat)
{
    // http://epsg.io/3857
    // Area of use: World between 85.06°S and 85.06°N.
    assert(lon >= -180.0);
    assert(lon < 180.0);
    assert(lat >= -85.06);
    assert(lat <= 85.06);
    uint8_t zone = (uint8_t)((lon + 180) / 6) + 1;
    // http://www.asprs.org/a/resources/grids/10-99-norway.pdf
    // For that portion of the world where the UTM grid is specified (85.06° south to 85.06° north),
    // the UTM grid zone number is the first element of a Military Grid reference.
    // This number sets the zone longitude limits.
    // Zone 32 has been widened to 9° (at the expense of zone 31) between latitudes 56° and 64° to accommodate
    // southwest Norway. Similarly, between 72° and 84°, zones 33 and 35 have been widened to 12° to accommodate
    // Svalbard. To compensate for these 12° wide zones, zones 31 and 37 are widened to 9° and zones 32, 34, and 36
    // are eliminated.
    if (lat >= 56.0 && lat < 64.0 && lon >= 3.0 && lon < 12.0)
    {
        zone = 32;
    }

    if (lat >= 72.0 && lat < 84.0)
    {
        if (lon >= 0.0 && lon < 9.0)
            zone = 31;
        else if (lon >= 9.0 && lon < 21.0)
            zone = 33;
        else if (lon >= 21.0 && lon < 33.0)
            zone = 35;
        else if (lon >= 33.0 && lon < 42.0)
            zone = 37;
    }
    return zone;
}

uint8_t lonlat_get_utm_zone(float64_t lon, float64_t lat)
{
    assert(lon >= -180.0);
    assert(lon < 180.0);
    assert(lat >= -85.06);
    assert(lat <= 85.06);

    uint8_t zone = (uint8_t)((lon + 180) / 6) + 1;

    if (lat < 0)
    {
        zone |= (1 << 7);
    }
    else
    {
        // http://www.asprs.org/a/resources/grids/10-99-norway.pdf
        // For that portion of the world where the UTM grid is specified (85.06° south to 85.06° north),
        // the UTM grid zone number is the first element of a Military Grid reference.
        // This number sets the zone longitude limits.
        // Zone 32 has been widened to 9° (at the expense of zone 31) between latitudes 56° and 64° to accommodate
        // southwest Norway. Similarly, between 72° and 84°, zones 33 and 35 have been widened to 12° to accommodate
        // Svalbard. To compensate for these 12° wide zones, zones 31 and 37 are widened to 9° and zones 32, 34, and 36
        // are eliminated.
        if (lat >= 56.0 && lat < 64.0 && lon >= 3.0 && lon < 12.0)
        {
            zone = 32;
        }

        if (lat >= 72.0 && lat < 84.0)
        {
            if (lon >= 0.0 && lon < 9.0)
                zone = 31;
            else if (lon >= 9.0 && lon < 21.0)
                zone = 33;
            else if (lon >= 21.0 && lon < 33.0)
                zone = 35;
            else if (lon >= 33.0 && lon < 42.0)
                zone = 37;
        }
    }
    return zone;
}

static float64_t lonlat_get_distance_in_same_lat(float64_t delta_lon, float64_t lat)
{
    float64_t delta_angle = acos(1 - cos(lat * deg2rad) * cos(lat * deg2rad) * (1 - cos(delta_lon * deg2rad)));
    if ((delta_lon > M_PI) || (delta_lon < -M_PI))
    {
        delta_angle = 2 * M_PI - delta_angle;
    }
    return delta_angle / (4 * M_PI) * earth_radius;
}

float64_t lonlat_get_distance_to_zone_id(float64_t lon, float64_t lat, uint8_t zone_id)
{
    float64_t lon_west       = zone_id * 6.0 - 186.0;
    float64_t lon_east       = zone_id * 6.0 - 180;
    float64_t delta_lon_west = lon - lon_west;
    float64_t delta_lon_east = lon - lon_east;
    float64_t distance       = 0.0;
    if (((delta_lon_west < 0.0) && (delta_lon_west >= -177.0)) || (delta_lon_west >= 183.0))
    {
        distance = lonlat_get_distance_in_same_lat(2 * delta_lon_west, lat);
    }
    else if (((delta_lon_east > 0.0) && (delta_lon_east < 177.0)) || (delta_lon_east <= -183.0))
    {
        distance = lonlat_get_distance_in_same_lat(2 * delta_lon_east, lat);
    }
    else
    {
        distance = 0.0;
    }
    return distance;
}

retcode_t point2_convert_lonlat_to_utm(struct Point2d const* src_pt, Coordinate_t dst_coord, struct Point2d* dst_pt)
{
    retcode_t rc = lonlat_to_utm(src_pt->x, src_pt->y, coordinate_utm_get_zone_id(&dst_coord),
                                 coordinate_utm_get_south_flag(&dst_coord), &(dst_pt->x), &(dst_pt->y));
    if (RC_SUCCESS == rc)
    {
        dst_pt->x -= coordinate_utm_get_offset_x(&dst_coord) * COORDINATE_UTM_GRID_WIDTH;
        dst_pt->y -= coordinate_utm_get_offset_y(&dst_coord) * COORDINATE_UTM_GRID_HEIGHT;
    }
    return rc;
}

retcode_t point3_convert_lonlat_to_utm(struct Point3d const* src_pt, Coordinate_t dst_coord, struct Point3d* dst_pt)
{
    retcode_t rc = lonlat_to_utm(src_pt->x, src_pt->y, coordinate_utm_get_zone_id(&dst_coord),
                                 coordinate_utm_get_south_flag(&dst_coord), &(dst_pt->x), &(dst_pt->y));
    if (RC_SUCCESS == rc)
    {
        dst_pt->x -= coordinate_utm_get_offset_x(&dst_coord) * COORDINATE_UTM_GRID_WIDTH;
        dst_pt->y -= coordinate_utm_get_offset_y(&dst_coord) * COORDINATE_UTM_GRID_HEIGHT;
    }
    return rc;
}

retcode_t point2_convert_lonlat_to_utm_and_coord(struct Point2d const* src_pt, Coordinate_t* dst_coord,
                                                 struct Point2d* dst_pt)
{
    uint8_t const zone       = lonlat_get_utm_zone(src_pt->x, src_pt->y);
    uint8_t const zone_id    = (zone & ~(1 << 7u));
    bool_t const  south_flag = zone >> 7u;

    retcode_t rc = lonlat_to_utm(src_pt->x, src_pt->y, zone_id, south_flag, &(dst_pt->x), &(dst_pt->y));
    if (RC_SUCCESS == rc)
    {
        uint32_t const offset_x = (uint32_t)(dst_pt->x / COORDINATE_UTM_GRID_WIDTH);
        uint32_t const offset_y = (uint32_t)(dst_pt->y / COORDINATE_UTM_GRID_HEIGHT);
        dst_pt->x -= (float64_t)(offset_x * COORDINATE_UTM_GRID_WIDTH);
        dst_pt->y -= (float64_t)(offset_y * COORDINATE_UTM_GRID_HEIGHT);
        *dst_coord = coordinate_utm6_create(zone_id, south_flag, offset_x, offset_y);
    }
    return rc;
}

retcode_t point3_convert_lonlat_to_utm_and_coord(struct Point3d const* src_pt, Coordinate_t* dst_coord,
                                                 struct Point3d* dst_pt)
{
    uint8_t const zone       = lonlat_get_utm_zone(src_pt->x, src_pt->y);
    uint8_t const zone_id    = (zone & ~(1 << 7u));
    bool_t const  south_flag = zone >> 7u;

    retcode_t rc = lonlat_to_utm(src_pt->x, src_pt->y, zone_id, south_flag, &(dst_pt->x), &(dst_pt->y));
    if (RC_SUCCESS == rc)
    {
        uint32_t const offset_x = (uint32_t)(dst_pt->x / COORDINATE_UTM_GRID_WIDTH);
        uint32_t const offset_y = (uint32_t)(dst_pt->y / COORDINATE_UTM_GRID_HEIGHT);
        dst_pt->x -= (float64_t)(offset_x * COORDINATE_UTM_GRID_WIDTH);
        dst_pt->y -= (float64_t)(offset_y * COORDINATE_UTM_GRID_HEIGHT);
        *dst_coord = coordinate_utm6_create(zone_id, south_flag, offset_x, offset_y);
    }
    return rc;
}

retcode_t point2_convert_utm_to_lonlat(Coordinate_t src_coord, struct Point2d const* src_pt, struct Point2d* dst_pt)
{
    float64_t utm_easting  = src_pt->x + coordinate_utm_get_offset_x(&src_coord) * COORDINATE_UTM_GRID_WIDTH;
    float64_t utm_northing = src_pt->y + coordinate_utm_get_offset_y(&src_coord) * COORDINATE_UTM_GRID_HEIGHT;
    retcode_t rc = utm_to_lonlat(coordinate_utm_get_zone_id(&src_coord), coordinate_utm_get_south_flag(&src_coord),
                                 utm_easting, utm_northing, &(dst_pt->x), &(dst_pt->y));
    return rc;
}

retcode_t point3_convert_utm_to_lonlat(Coordinate_t src_coord, struct Point3d const* src_pt, struct Point3d* dst_pt)
{
    float64_t utm_easting  = src_pt->x + coordinate_utm_get_offset_x(&src_coord) * COORDINATE_UTM_GRID_WIDTH;
    float64_t utm_northing = src_pt->y + coordinate_utm_get_offset_y(&src_coord) * COORDINATE_UTM_GRID_HEIGHT;
    retcode_t rc = utm_to_lonlat(coordinate_utm_get_zone_id(&src_coord), coordinate_utm_get_south_flag(&src_coord),
                                 utm_easting, utm_northing, &(dst_pt->x), &(dst_pt->y));
    return rc;
}

retcode_t point2_convert_utm_with_target_coord(Coordinate_t src_coord, struct Point2d const* src_pt,
                                               Coordinate_t dst_coord, struct Point2d* dst_pt)
{
    retcode_t rc = point2_convert_utm_to_lonlat(src_coord, src_pt, dst_pt);
    if (rc != RC_SUCCESS)
    {
        return rc;
    }
    rc = point2_convert_lonlat_to_utm(dst_pt, dst_coord, dst_pt);
    return rc;
}

retcode_t point3_convert_utm_with_target_coord(Coordinate_t src_coord, struct Point3d const* src_pt,
                                               Coordinate_t dst_coord, struct Point3d* dst_pt)
{
    retcode_t rc = point3_convert_utm_to_lonlat(src_coord, src_pt, dst_pt);
    if (rc != RC_SUCCESS)
    {
        return rc;
    }
    rc = point3_convert_lonlat_to_utm(dst_pt, dst_coord, dst_pt);
    return rc;
}
