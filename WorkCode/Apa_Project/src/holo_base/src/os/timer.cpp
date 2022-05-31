/*!
 * @file timer.cpp
 * @brief Use to control the thread execution, control a minimum execution time.
 * @author liwenjun (liwenjun@holomatic.ai), zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <holo/os/timer.h>

#include <holo/os/time.h>

namespace holo
{
Timer::Timer(const ::holo::float32_t frequency)
{
    duration_ = (frequency < 0.0001f) ? static_cast<float64_t>(1.0) : static_cast<float64_t>(1.0f) / frequency;
}

void Timer::Start()
{
    tictoc_.Tic();
}

void Timer::Stop()
{
    ::holo::float64_t elapsed = tictoc_.Elapsed();

    if (elapsed < duration_)
    {
        float64_t value = duration_ - elapsed;
        ::holo::os::Sleep(static_cast<float32_t>(value));
    }
}

}  // namespace holo
