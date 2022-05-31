/*!
 * @file timer.h
 * @brief Use to control the thread execution, control a minimum execution time.
 * @author liwenjun (liwenjun@holomatic.ai), zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_OS_TIMER_H_
#define _HOLO_OS_TIMER_H_

#include <holo/os/tictoc_timer.h>
#include <holo/core/types.h>

namespace holo
{
/**
 * \ingroup os
 * @detail The thread will sleeps when (Stop - Start) < (1 / frequency) until the duration more than (1 / frequency).
 */
class Timer
{
public:
    /**
     * @brief Constructor
     * @detail The "duration" member variable will be reset 1.0 if frequency < zero or frequency near to zero.
     *          frequency in units of seconds
     *
     * @param frequency
     */
    Timer(const ::holo::float32_t frequency);

    /**
     * @brief Start the timer.
     *
     */
    void Start();

    /**
     * @brief Sleep the thread if the elapsed between last start less than the agreed time.
     *
     */
    void Stop();

private:
    // duration : 1 / input hz
    ::holo::float64_t duration_;

    // use to calculate elapsed time
    ::holo::TicTocTimer tictoc_;
};

}  // namespace holo

#endif
