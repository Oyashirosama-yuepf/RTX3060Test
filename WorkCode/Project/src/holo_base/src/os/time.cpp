/*!
 * @file time.cpp
 * @brief Time wrapper.
 * @author Zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */
#include <holo/os/time.h>

// The reason of place this header file here is the code below needs to use HOLO_PLATEFORM_LINUX\HOLO_PLATEFORM_QNX
#include <holo/os/predefine.h>

#if defined(HOLO_PLATFORM_LINUX)
#include <time.h>
#include <chrono>
#include <thread>
#elif defined(HOLO_PLATFORM_QNX)
#include <time.h>
#include <chrono>
#include <thread>
#else
error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif

namespace holo
{
namespace os
{
bool_t GetLocalTime(::holo::uint32_t& sec, ::holo::uint32_t& n_sec)
{
#if defined(HOLO_PLATFORM_LINUX) || defined(HOLO_PLATFORM_QNX)
    struct timespec t;
    if (0 != clock_gettime(CLOCK_MONOTONIC, &t))
    {
        sec   = 0U;
        n_sec = 0U;
        return false;
    }
    sec   = static_cast<::holo::uint32_t>(t.tv_sec);
    n_sec = static_cast<::holo::uint32_t>(t.tv_nsec);
#else
    error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif
    return true;
}
bool_t GetSystemTime(::holo::uint32_t& sec, ::holo::uint32_t& n_sec)
{
#if defined(HOLO_PLATFORM_LINUX) || defined(HOLO_PLATFORM_QNX)
    struct timespec t;
    if (0 != clock_gettime(CLOCK_REALTIME, &t))
    {
        sec   = 0U;
        n_sec = 0U;
        return false;
    }

    sec   = static_cast<::holo::uint32_t>(t.tv_sec);
    n_sec = static_cast<::holo::uint32_t>(t.tv_nsec);
#else
    error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif
    return true;
}
void Sleep(const ::holo::float32_t duration)
{
    if (duration < 0.0f)
    {
        return;
    }
#if defined(HOLO_PLATFORM_LINUX) || defined(HOLO_PLATFORM_QNX)
    std::this_thread::sleep_for(std::chrono::duration<::holo::float64_t, std::milli>(duration * 1000));
#else
    error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif
}

}  // namespace os

}  // namespace holo
