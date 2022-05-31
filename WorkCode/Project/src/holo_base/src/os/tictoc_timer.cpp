/*!
 * @file tictoc_timer.cpp
 * @brief A tic-toc timer to measure the elapsed time between tic and toc.
 * @author Li Chao (lichao@holomatic.com), zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/os/tictoc_timer.h>
#include <holo/os/time.h>

namespace holo
{
/******************************************************************************/
TicTocTimer::TicTocTimer()
{
    Tic();
}

/******************************************************************************/
void TicTocTimer::Tic()
{
    ::holo::uint32_t second     = 0U;
    ::holo::uint32_t nanosecond = 0U;

    if (::holo::os::GetLocalTime(second, nanosecond))
    {
        last_time_.SetSec(second);
        last_time_.SetNsec(nanosecond);
    }
    else
    {
        last_time_.SetSec(0U);
        last_time_.SetNsec(0U);
    }
}

/******************************************************************************/
::holo::float64_t TicTocTimer::Elapsed() const
{
    ::holo::uint32_t second     = 0U;
    ::holo::uint32_t nanosecond = 0U;

    if (!::holo::os::GetLocalTime(second, nanosecond))
    {
        return 0.0;
    }

    ::holo::common::Duration current(second, nanosecond);

    return (current - last_time_).ToSec();
}

/******************************************************************************/
}  // namespace holo
