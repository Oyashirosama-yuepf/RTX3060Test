/*!
 * @file time.h
 * @brief Time wrapper.
 * @author Zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_OS_TIME_H_
#define HOLO_OS_TIME_H_

#include <holo/core/types.h>

namespace holo
{
namespace os
{
/**
 * @brief Get local time. It has nothing to do with system time
 * @detail Timing starts when the system starts.
 *
 * @param[in,out] sec second, invalid value is 0
 * @param[in,out] n_sec nanosecond, invalid value is 0
 * @return true success otherwise false
 */
bool_t GetLocalTime(::holo::uint32_t& sec, ::holo::uint32_t& n_sec);
/**
 * @brief Get system time, it means current time of day, starts from 1970.1.1.
 *
 * @param[in,out] sec second, invalid value is 0
 * @param[in,out] n_sec nanosecond, invalid value is 0
 * @return true success otherwise false
 */
bool_t GetSystemTime(::holo::uint32_t& sec, ::holo::uint32_t& n_sec);
/**
 * @brief Make thread sleep, return cpu to system.
 *
 * @param duration in units of second.
 */
void Sleep(const ::holo::float32_t duration);

}  // namespace os
}  // namespace holo
#endif  // OS_TIME_H_
