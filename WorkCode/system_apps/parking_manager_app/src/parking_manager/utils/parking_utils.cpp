/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_utils.cpp
 * @brief This cpp file defines general parking utils functions
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#include <parking_manager/utils/parking_utils.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

bool_t IsAbsolutePath(const std::string& yaml_file)
{
    if (yaml_file.length() >= 1 && yaml_file[0] == '/')
    {
        return true;
    }
    return false;
}

std::string GetHoloParkingLibConfigDirectory()
{
	return GetHoloConfigRootDirectory() + "/holo_parking_cmw_app/lib_config/";
}

void GenerateMsg(const ParkingMsgId& msg_id, const uint8_t* input, const uint32_t& data_len, std::vector<uint8_t>& output)
{
	output.resize(data_len + MSG_INFO_LEN);
  memcpy(&output.at(HEADER_OFFSET), &PARKING_TCP_HEADER, sizeof(PARKING_TCP_HEADER));
	uint16_t id = static_cast<uint16_t>(msg_id);
	memcpy(&output.at(MSG_ID_OFFSET), &id, sizeof(id));
	memcpy(&output.at(MSG_LEN_OFFSET), &data_len, sizeof(data_len));
	memcpy(&output.at(DATA_OFFSET), input, data_len);
}

void GenerateMsgInfo(const ParkingMsgId& msg_id, const uint32_t& msg_len, std::vector<uint8_t>& output)
{
  output.resize(DATA_OFFSET + msg_len);
  memcpy(&output.at(HEADER_OFFSET), &PARKING_TCP_HEADER, sizeof(PARKING_TCP_HEADER));
  uint16_t id = static_cast<uint16_t>(msg_id);
  memcpy(&output.at(MSG_ID_OFFSET), &id, sizeof(id));
  memcpy(&output.at(MSG_LEN_OFFSET), &msg_len, sizeof(msg_len));
}

void HPPGenerateMsg(const HPPParkingMsgId& msg_id, const uint8_t* input, const uint32_t& data_len, std::vector<uint8_t>& output)
{
	output.resize(data_len + MSG_INFO_LEN);
  memcpy(&output.at(HEADER_OFFSET), &HPP_PARKING_TCP_HEADER, sizeof(HPP_PARKING_TCP_HEADER));
	uint16_t id = static_cast<uint16_t>(msg_id);
	memcpy(&output.at(MSG_ID_OFFSET), &id, sizeof(id));
	memcpy(&output.at(MSG_LEN_OFFSET), &data_len, sizeof(data_len));
	memcpy(&output.at(DATA_OFFSET), input, data_len);
}

void HPPGenerateMsgInfo(const HPPParkingMsgId& msg_id, const uint32_t& msg_len, std::vector<uint8_t>& output)
{
  output.resize(DATA_OFFSET + msg_len);
  memcpy(&output.at(HEADER_OFFSET), &HPP_PARKING_TCP_HEADER, sizeof(HPP_PARKING_TCP_HEADER));
  uint16_t id = static_cast<uint16_t>(msg_id);
  memcpy(&output.at(MSG_ID_OFFSET), &id, sizeof(id));
  memcpy(&output.at(MSG_LEN_OFFSET), &msg_len, sizeof(msg_len));
}

uint8_t GetUINT8(const uint8_t* msg, size_t& offset)
{
  uint8_t ret = msg[offset];
  offset++;
  return ret;
}

uint16_t GetUINT16(const uint8_t* msg, size_t& offset)
{
  uint16_t ret = (msg[offset]<<8) + msg[offset+1];
  offset += 2;
  return ret;
}

uint32_t GetUINT32(const uint8_t* msg, size_t& offset)
{
  uint32_t ret = (msg[offset]<<24) + (msg[offset+1]<<16) + (msg[offset+2]<<8) + msg[offset+3];
  offset += 4;
  return ret;
}

uint64_t GetUINT64(const uint8_t* msg, size_t& offset)
{
  uint64_t ret = (static_cast<uint64_t>(msg[offset+0])<<(7*8)) +
                 (static_cast<uint64_t>(msg[offset+1])<<(6*8)) +
                 (static_cast<uint64_t>(msg[offset+2])<<(5*8)) +
                 (static_cast<uint64_t>(msg[offset+3])<<(4*8)) +
                 (static_cast<uint64_t>(msg[offset+4])<<(3*8)) +
                 (static_cast<uint64_t>(msg[offset+5])<<(2*8)) +
                 (static_cast<uint64_t>(msg[offset+6])<<(1*8)) +
                 msg[offset+7];
  offset += 8;
  return ret;
}

float32_t GetFLOAT(const uint8_t* msg, size_t& offset)
{
  uint32_t test = GetUINT32(msg, offset);
  float32_t ans;
  memcpy(&ans, &test, 4);
  return ans;
}


uint16_t GetUint16(const uint8_t* msg, size_t& offset)
{
  uint16_t ret;
  memcpy(&ret, msg+offset, 2);
  offset += 2;
  return ret;
}

uint32_t GetUint32(const uint8_t* msg, size_t& offset)
{
  uint32_t ret;
  memcpy(&ret, msg+offset, 4);
  offset += 4;
  return ret;
}

uint64_t GetUint64(const uint8_t* msg, size_t& offset)
{
  uint64_t ret;
  memcpy(&ret, msg+offset, 8);
  offset += 8;
  return ret;
}

float32_t GetFloat(const uint8_t* msg, size_t& offset)
{
  float32_t ans;
  memcpy(&ans, msg+offset, 4);
  offset += 4;
  return ans;
}

ssize_t SendNoSignal(int _socket, const void *_buf, size_t _size)
{
  return send(_socket, _buf, _size, MSG_NOSIGNAL);
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
