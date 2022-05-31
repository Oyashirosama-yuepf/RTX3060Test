/**
 * @file utils.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief 
 * @date 2020-09-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _HOLO_CMW_APP_UTILS_H_
#define _HOLO_CMW_APP_UTILS_H_
#include <string>
#include <holo/core/types.h>
#include <holo/common/timestamp.h>

namespace holo_cmw
{
std::string GetStrFromTerminal(const std::string& command);

std::string getTime(int64_t timestamp = 0);

void init_keyboard();
void close_keyboard();
int  keyboard_hit();
bool is_on_playing();
void set_stop_flag();
void set_cmw_spin();
int  charToIntBig(holo::uint8_t const* src, int offset);
int  charToIntLittle(holo::uint8_t const* src, int offset);
holo::common::Timestamp GetCurrentUtcTime();
::holo::uint32_t uint32_t_to_big_endian(::holo::uint32_t data);
::holo::uint64_t uint8_t_to_uint64_t(::holo::uint8_t const* buffer, std::size_t size);
}  // namespace holo_cmw

#endif