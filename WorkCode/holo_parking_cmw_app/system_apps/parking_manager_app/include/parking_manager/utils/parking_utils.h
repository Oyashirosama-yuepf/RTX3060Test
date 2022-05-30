/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_utils.h
 * @brief This header file defines general parking utils functions
 * @author yangzhongtao<yangzhongtao@holomatic.com>
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_PARKING_UTILS_H
#define HOLO_PARKING_PARKING_UTILS_H

#include <cstring>
#include <iostream>
#include <sys/socket.h>

#include <holo/core/types.h>
#include <holo/utils/holo_root.h>
#include <parking_manager/utils/parking_structure.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

bool_t IsAbsolutePath(const std::string& yaml_file);

std::string GetHoloParkingLibConfigDirectory();

void GenerateMsg(const ParkingMsgId& msg_id, const uint8_t* input, const uint32_t& data_len, std::vector<uint8_t>& output);

void GenerateMsgInfo(const ParkingMsgId& msg_id, const uint32_t& msg_len, std::vector<uint8_t>& output);

uint8_t GetUINT8(const uint8_t* msg, size_t& offset);

uint16_t GetUINT16(const uint8_t* msg, size_t& offset);

uint32_t GetUINT32(const uint8_t* msg, size_t& offset);

uint64_t GetUINT64(const uint8_t* msg, size_t& offset);

float32_t GetFLOAT(const uint8_t* msg, size_t& offset);

uint16_t GetUint16(const uint8_t* msg, size_t& offset);

uint32_t GetUint32(const uint8_t* msg, size_t& offset);

uint64_t GetUint64(const uint8_t* msg, size_t& offset);

float32_t GetFloat(const uint8_t* msg, size_t& offset);

ssize_t SendNoSignal(int _socket, const void *_buf, size_t _size);

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif  //HOLO_PARKING_PARKING_UTILS_H