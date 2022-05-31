/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file structs.h
 * @brief Common struct definitions
 * @author zhengshulei@holomatic.com
 * @date "2022-4-12"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_COMMON_STRUCTS_H_
#define HOLO_MAP_SERVICE_CLIENT_COMMON_STRUCTS_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace common
{ 
    
struct BackgroundStatus
{
    struct NavigationStatus
    {
        enum class NavigationMode : holo::uint8_t
        {
            INVALID    = 0U,
            NAVIGATION = 1U,
            CRUISER    = 2U,
            YAWING     = 3U
        };

        enum class RoutingMode : holo::uint8_t
        {
            OUT_ROUTE      = 0U,
            ON_HD_ROUTE    = 1U,
            ON_SD_ROUTE    = 2U,
            ON_SD_HD_ROUTE = 3U
        };

        static holo::float64_t constexpr DEFAULT_INVALID_DISTANCE_VALUE = -999999.999999;

        holo::bool_t    near_sd_map_destination           = false;
        holo::bool_t    near_hd_map_destination           = false;
        holo::float64_t near_sd_map_destination_threshold = 3000; ///< default threshold set to 3km
        holo::float64_t near_hd_map_destination_threshold = 3000; ///< default threshold set to 3km
        holo::float64_t distance_to_sd_map_destination    = DEFAULT_INVALID_DISTANCE_VALUE;
        holo::float64_t distance_to_hd_map_destination    = DEFAULT_INVALID_DISTANCE_VALUE;

        NavigationMode navigation_mode = NavigationMode::INVALID;
        RoutingMode    routint_mode    = RoutingMode::OUT_ROUTE;

    };

    NavigationStatus navigation_status;
    
};

} ///< namespace common
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_COMMON_STRUCTS_H_ */