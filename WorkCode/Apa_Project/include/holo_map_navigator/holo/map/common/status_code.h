/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file status_code.h
 * @brief This header file defines .
 * @author jiangdianqin(jiangdianqin@holomaitc.com)
 * @date "2020-12-28"
 */
#ifndef HOLO_MAP_CORE_STATUS_CODE_H_
#define HOLO_MAP_CORE_STATUS_CODE_H_

#include <holo/core/types.h>

namespace holo
{
namespace map
{
typedef holo::uint8_t MapCodeType;
enum class MapModuleCode : MapCodeType
{
    PER_LOCAL_MAP_FUSION = 12,
    MAP_NAVIGATOR        = 21
};
enum class NavigatorStatusCode
{
    OK                          = 0,
    No_Odometry                 = 1,
    No_HDMap                    = 2,
    HDMap_Exception             = 3,
    Map_Match_Fail              = 4,
    Router_Detection_Fail       = 5,
    Navigator_Command_Exception = 6,
    Lane_Seq_Exception          = 7,
    Speed_Limit_Exception       = 8,
    Road_Attribute_Exception    = 9,
    Geo_Fence_Exception         = 10,
    Road_Type_Exception         = 11
};
}  // namespace map
}  // namespace holo

#endif