/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file across_zone_utility.h
 * @brief utm flag and utility function
 * @author Jiangdianqin(jiangdianqin@holomaitc.com)
 * @date 2020-03-30
 */

#ifndef HOLO_MAP_COMMON_ACROSS_ZONE_UTILITY_H_
#define HOLO_MAP_COMMON_ACROSS_ZONE_UTILITY_H_

#include <holo/common/coordinate.h>
#include <holo/core/types.h>
#include <holo/map/common/common_type_define.h>
#include <holo_c/core/retcode.h>
#include <holo_c/utils/geographical_transformation.h>

#include <atomic>
#include <cmath>
#include <cstdlib>
#include <map>

namespace holo
{
namespace map
{
/**
 * @addtogroup across_zone
 *
 * @{
 */
namespace across_zone
{
/**
 * @addtogroup utility
 *
 * @{
 */

namespace utility
{

class GlobalCoordinate
{
public:
    GlobalCoordinate()                              = delete;
    GlobalCoordinate(const GlobalCoordinate& other) = delete;
    GlobalCoordinate(GlobalCoordinate&& other)      = delete;

    ~GlobalCoordinate() = delete;

    GlobalCoordinate& operator=(const GlobalCoordinate& other) = delete;
    GlobalCoordinate& operator=(GlobalCoordinate&& other)      = delete;

public:
    /**
     * @brief Set the global UtmZoneId
     * 
     * @param[in] zone_id 
     */
    static void SetUtmZoneId(const ::holo::uint8_t& zone_id) noexcept
    {
        global_coordinate_.SetUtmZoneId(zone_id);
    }

    /**
     * @brief Set the global UtmSouthFlag
     * 
     * @param[in] south_flag 
     */
    static void SetUtmSouthFlag(const ::holo::bool_t& south_flag) noexcept
    {
        global_coordinate_.SetUtmSouthFlag(south_flag);
    }

    /**
     * @brief Set the global UtmZone
     * 
     * @param[in] zone_id 
     * @param[in] south_flag 
     */
    static void SetUtmZone(const ::holo::uint8_t& zone_id, const ::holo::bool_t& south_flag) noexcept
    {
        global_coordinate_.SetUtmZoneId(zone_id);
        global_coordinate_.SetUtmSouthFlag(south_flag);
    }

    /**
     * @brief Set the global Coordinate
     * 
     * @param coordinate 
     */
    static void SetCoordinate(const ::holo::common::Coordinate& coordinate) noexcept
    {
        global_coordinate_ = coordinate;
    }

    /**
     * @brief Get the global UtmZoneId
     * 
     * @return ::holo::uint8_t 
     */
    static ::holo::uint8_t GetUtmZoneId() noexcept
    {
        return global_coordinate_.GetUtmZoneId();      
    }

    /**
     * @brief Get the global UtmSouthFlag
     * 
     * @return ::holo::uint8_t 
     */
    static ::holo::bool_t GetUTMTag() noexcept
    {
        return global_coordinate_.GetUtmSouthFlag();
    }

    /**
     * @brief Get the UtmZone
     * 
     * @param[out] zone_id 
     * @param[out] south_flag 
     */
    static void GetUtmZone(::holo::uint8_t& zone_id, ::holo::bool_t& south_flag) noexcept
    {
        zone_id                               = global_coordinate_.GetUtmZoneId();
        south_flag                            = global_coordinate_.GetUtmSouthFlag();
    }

    /**
     * @brief Get the global Coordinate
     * 
     * @return ::holo::common::Coordinate 
     */
    static ::holo::common::Coordinate GetCoordinate() noexcept
    {
        return global_coordinate_;
    }

private:
    /// global coordinate
    static ::holo::common::Coordinate global_coordinate_;
};

/*
    UTMTag is an enum to describe the relationship between odometry utm coordinate saved in utm_flags and data,
    utm coordinate saved in utm_flags is same with odometry from mlc, and utm_flags in data followed by original data.
    we use UTMTag to describe the location between them.
    for example:
    zone 50     |   zone 51
                |
      coincide  |   neighbour
    ---------------------------
      opposite  |   symmetry
                |
                |
 */
enum class UTMTag
{
    Coincide  = 0,
    Neighbour = 1,
    Opposite  = 2,
    Symmetry  = 3,
    Unknown   = 4
};

/**
 * @brief Get utm tag
 * @param[in] zone_id origin zone id
 * @param[in] extra_zone_id extra zone id
 * @param[in] south_flag if it is in south hemisphere
 * @return tag UTMTag
 */
UTMTag GetUTMTag(const holo::uint8_t zone_id, const holo::uint8_t extra_zone_id, const bool south_flag);

/**
 * @brief if it is close to the zone border
 *
 * @param[in] lat latitude in unit of degree
 * @param[in] lon longitude in unit of degree
 * @return near zone id, if the difference in longditude between current point and zone border is less
 *                       0.1 degree under lat 30
 *                       0.2 degree under lat 60
 *                       0.3 degree under lat 85.06
 *@return INVALID_ZONE_ID, if lat or lon overflows.
 */
::holo::uint8_t GetClosestZoneId(const ::holo::float64_t lat, const ::holo::float64_t lon);

/**
 * @brief calculate plan distance by spherical point
 *
 * @param[in] start point
 * @param[in] end point
 * @return ::holo::float64_t distance between two point
 */
::holo::float64_t CalculateDistance(const holo::geometry::Point2d start_point, const holo::geometry::Point2d end_point);

/**
 * @brief if it is close to the equator
 *
 * @param lat latitude in unit of degree
 * @return true, if the difference in longitude between current point and equator is less 0.1 degree
 * @return false,if lat overflows.
 */
::holo::bool_t IsCloseToEquator(const ::holo::float64_t lat);

}  /// namespace utility

/**
 * @}
 */

}  /// namespace across_zone

/**
 * @}
 */
}  /// namespace map
}  /// namespace holo

#endif /* HOLO_MAP_COMMON_ACROSS_ZONE_UTILITY_H_ */