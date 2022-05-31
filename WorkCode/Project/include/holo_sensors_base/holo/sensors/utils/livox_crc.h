/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file crc_table.h
 * @brief This header file defines crc table
 * @author huzhiyuan(huzhiyuan@holomaitc.com)
 * @date 2020/10/12
 */

#ifndef HOLO_SENSORS_UTILS_LIVOX_CRC_H_
#define HOLO_SENSORS_UTILS_LIVOX_CRC_H_

#include <holo/core/types.h>

namespace holo
{
namespace sensors
{
static constexpr uint16_t LIVOX_INIT_CRC16 = 0x4C49U;
static constexpr uint32_t LIVOX_INIT_CRC32 = 0x564F580AU;

uint16_t CalcCRC16(const uint8_t* data, uint16_t len, uint16_t seed);
uint32_t CalcCRC32(const uint8_t* data, uint16_t len, uint32_t seed);

}  // namespace sensors
}  // namespace holo

#endif  // HOLO_SENSORS_UTILS_LIVOX_CRC_H_
