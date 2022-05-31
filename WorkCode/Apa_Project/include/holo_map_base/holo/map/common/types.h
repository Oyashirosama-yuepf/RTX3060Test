/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file types.h
 * @brief Define common types for map projects
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_COMMON_TYPES_H_
#define HOLO_MAP_COMMON_TYPES_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{

/**
 * @addtogroup map
 * @{
 *
 */

/**
 * @brief Define status for map engine.
 */
enum class MapErrorCode : holo::uint8_t
{
    kOK                 = 0, ///< No error.
    kNONE,                   ///< No target object.
    kFAILED,                 ///< An error occurs in map engine.
    kIMPERFECT,              ///< Half successes and half failures.
    kUNAVAILABLE,            ///< Map engine is unavailable.
    kUNSUPPORTED,            ///< The operation is not supported.
    kENGINE_READY,           ///< Map engine is ready, we can request map data.
    kENGINE_UNREADY,         ///< Map engine is not ready, please wail for a moment.
    kENGINE_UNCONNECTED,     ///< Map engine client disconnect with server.
};

/**
 * @brief Error code for map local server.
 * 
 * @detail This type is used in holo::map::service::Session, define the session status.
 */
enum class MapServiceErrorCode : holo::uint8_t
{
    /// LMS inner error code.
    kNO_ERROR                                   = 0,    ///< No error, a valid session.
    kINNER_ERROR                                = 1,    ///< An unknown error occurs in map local server.
    kSERIALIZATION_ERROR                        = 2,    ///< Session object serialization failed.
    kRETRIEVER_ERROR                            = 3,    ///< No right to access map data.
    kINVALID_REQUEST_ERROR                      = 4,    ///< Request has invalid parameters, please check the request.
    kPERMISSION_REQUEST_ERROR                   = 5,    ///< Invalid token id.
    kLIMITATION_REQUEST_ERROR                   = 6,    ///< Request has been restricted, too frequently.
    kDATA_COMPILING_ERROR                       = 7,    ///< Data complier is error, can't complie the hd-map.
    kINVALID_POSITION_ERROR                     = 8,    ///< Invalid position, it is unavailable.
    /// LMS external error code (Baidu sdk).
    kBD_ENGINE_UNKNOWN_ERROR                    = 100,  ///< Baidu sdk unknown error.
    kBD_ENGINE_SDK_DB_OPEN_FAILED               = 101,  ///< Baidu sdk open db fail,db path error or db breakdown.
    kBD_ENGINE_DB_NOT_COMPATIBLE                = 102,  ///< Baidu db version is wrong.
    kBD_ENGINE_INVALD_POS                       = 103,  ///< Error is input a invalid pos .
    kBD_ENGINE_LOSS_OF_MAP                      = 104,  ///< No used.
    kBD_ENGINE_PARAM_ERROR                      = 105,  ///< Error is input a error param.
    kBD_ENGINE_INNER_ERROR                      = 106,  ///< Baidu sdk inner error.
    kBD_ENGINE_LOAD_MAP_OVERTIME                = 107,  ///< Baidu sdk load db timeout.
    kBD_ENGINE_BUFFER_LOADING                   = 108,  ///< Baidu sdk first load buffer.
    kBD_ENGINE_BUFFER_ENGINE_NOT_INITIALIZE     = 109,  ///< Baidu sdk initialize fail.
    kBD_ENGINE_LICENCE_NOT_INITIALIZE           = 110,  ///< baidu sdk licence not initialized.
    kBD_ENGINE_ACTIVE_FAILED                    = 111,  ///< Baidu sdk active fail,not initialized.
    kBD_ENGINE_LICENCE_NOT_FOUND                = 112,  ///< baidu sdk licence not found.
    kBD_ENGINE_LICENCE_EXPIRED                  = 113,  ///< baidu sdk licence expired.
    kBD_ENGINE_LICENCE_IO_ERROR                 = 114,  ///< baidu sdk licence read fail.
    kBD_ENGINE_NECT_CONNECT_FAILED              = 115,  ///< No used,baidu sdk net connect fail.
    kBD_ENGINE_NECT_TIMEOUT                     = 116,  ///< No used,baidu sdk net connect timeout.
    kBD_ENGINE_UPDATING_BLOCKED                 = 117,  ///< Baidu sdk is updating data.
    kBD_ENGINE_NETWORK_ERROR_MAP_EXPIRED        = 118,  ///< Baidu sdk network error,can't OTA,thensdk can't start.
    kBD_ENGINE_NETWORK_ERROR_MAP_INCONSISTENT   = 119,  ///< Baidu sdk network error,can't OTA,10km mapdata version isn't match sdk,then sdk can't start.
    kBD_ENGINE_OTA_FAILED_MAP_EXPIRED           = 120,  ///< Baidu sdk can't OTA,then sdk can't start.
    kBD_ENGINE_OAT_FAILED_MAP_INCONSISTENT      = 121,  ///< Baidu sdk can't OTA,10km mapdata version isn't match sdk,then sdk can't start.
};

/**
 * @brief Define the direction on the map.
 */
enum class MapDirection : holo::uint8_t
{
    MAP_DIRECTION_UNKNOWN       = 0, ///< Placeholder.
    MAP_DIRECTION_NORTH,             ///< North.
    MAP_DIRECTION_NORTH_EAST,        ///< North east.
    MAP_DIRECTION_EAST,              ///< East.
    MAP_DIRECTION_SOUTH_EAST,        ///< South east.
    MAP_DIRECTION_SOUTH,             ///< South.
    MAP_DIRECTION_SOUTH_WEST,        ///< South west.
    MAP_DIRECTION_WEST,              ///< West.
    MAP_DIRECTION_NORTH_WEST,        ///< North east.
};

/**
 * @}
 *
 */

} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_COMMON_TYPES_H_ */
