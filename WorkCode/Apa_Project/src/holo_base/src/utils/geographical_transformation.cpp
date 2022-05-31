/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file geographical_transformation.h
 * @brief Conversion between lon/lat and utm.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-4-3
 */

#include <holo/utils/internal/geographical_transformation.h>
#include <holo_c/utils/geographical_transformation.h>
#include <holo_c/core/retcode.h>

namespace holo
{
namespace utils
{
void LonLatToUtm(float64_t lon, float64_t lat, uint8_t zone_id, bool_t south_flag, float64_t& easting,
                 float64_t& northing)
{
    if(RC_SUCCESS != lonlat_to_utm(lon, lat, zone_id, south_flag, &easting, &northing))
    {
        throw holo::exception::BadGeographicalTransformationException();
    }
}

void UtmToLonLat(uint8_t zone_id, bool_t south_flag, float64_t easting, float64_t northing, float64_t& lon,
                 float64_t& lat)
{
    if(RC_SUCCESS != utm_to_lonlat(zone_id, south_flag, easting, northing, &lon, &lat))
    {
        throw holo::exception::BadGeographicalTransformationException();
    }
}

uint8_t LonLatGetUtmZoneId(float64_t lon, float64_t lat)
{
    return lonlat_get_utm_zone_id(lon, lat);
}

uint8_t LonLatGetUtmZone(float64_t lon, float64_t lat)
{
    return lonlat_get_utm_zone(lon, lat);
}

float64_t LonLatGetDistanceToZoneId(float64_t lon, float64_t lat, uint8_t zone_id)
{
    return lonlat_get_distance_to_zone_id(lon, lat, zone_id);
}

}  // namespace utils
}  // namespace holo
