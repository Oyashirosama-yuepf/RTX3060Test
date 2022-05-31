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
#include <holo_cmw/CMW/CMW.h>
#include <string>

namespace holo_cmw
{
std::string GetStrFromTerminal(const std::string& command);

std::string getTime();

void init_keyboard();
void close_keyboard();
int  keyboard_hit();
bool is_on_playing();
void set_stop_flag();
void set_cmw_spin();

void set_play_flag();

}  // namespace holo_cmw

#endif