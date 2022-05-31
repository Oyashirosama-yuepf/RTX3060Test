/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file boundary_feature.h
 * @brief This header file defines boundary feature.
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2022-04-11
 */

#ifndef HOLO_COMMON_BOUNDARY_FEATURE_H_
#define HOLO_COMMON_BOUNDARY_FEATURE_H_

#include <holo/core/types.h>

namespace holo
{
namespace common
{
/**
 * @brief Style of a lane boundary
 * @details Boundary style is a 8bit data defined as below:
 * @f[
 * \begin{bytefield}{8}
 *   \bitheader{0-7} \\
 *   \bitbox{1}{D} & \bitbox{1}{L} & \bitbox{1}{R} & \bitbox{1}{B} & \bitbox{5}{style}
 * \end{bytefield}
 * @f]
 *
 * - D: Flag indicate this boundary style is a double-line
 * - L: Flag indicate driving from left to right is against traffic regulations
 * - R: Flag indicate driving from right to left is against traffic regulations
 * - B: Flag indicate can't driven across
 * - style: The boundary style code
 */
enum class BoundaryStyle : uint8_t
{
    UNKNOWN              = 0x00U,
    /// See GB 5768.3-2009 table 1
    DASHED               = 0x01U,
    BOTTS_DOT            = 0x02U,
    SOLID                = 0x61U,
    BARRIER              = 0x71U,
    ROAD_EDGE            = 0x72U,
    DOUBLE_SOLID         = 0xE1U,
    DOUBLE_DASHED        = 0x81U,
    LEFT_DOT_RIGHT_SOLID = 0xA1U,
    LEFT_SOLID_RIGHT_DOT = 0xC1U,

    BIT_DOUBLE_LINE              = 7U,
    BIT_CROSS_FROM_LEFT_ILLEGAL  = 6U,
    BIT_CROSS_FROM_RIGHT_ILLEGAL = 5U,
    BIT_BLOCK                    = 4U,
    MASK_DOUBLE_LINE             = 0x80U,
    MASK_LEFT_CROSS_ILLEGAL      = 0x40U,
    MASK_RIGHT_CROSS_ILLEGAL     = 0x20U,
    MASK_BLOCK                   = 0x10U
};

/**
 * @brief Color of the boundary
 */
enum class BoundaryColor : uint8_t
{
    UNKNOWN = 0U,
    WHITE   = 1U,
    YELLOW  = 2U,
    ORANGE  = 3U,
    BLUE    = 4U
};

}  // namespace common
}  // namespace holo

#endif
