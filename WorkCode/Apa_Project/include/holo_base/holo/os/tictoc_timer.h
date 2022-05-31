/*!
 * @file tictoc_timer.h
 * @brief A tic-toc timer to measure the elapsed time between tic and toc.
 * @author Li Chao (lichao@holomatic.com), zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_OS_TICTOC_TIMER_H_
#define HOLO_OS_TICTOC_TIMER_H_

#include <string>

#include <holo/core/types.h>
#include <holo/common/timestamp.h>

namespace holo
{
/**
 * \ingroup os
 */
class TicTocTimer
{
public:
    /**
     * @brief Construct
     *
     */
    TicTocTimer();

    /**
     * @brief reset the timer
     *
     */
    void Tic();

    /**
     * @brief return the seconds since the last Tic()
     *
     * @return ::holo::float64_t
     */
    ::holo::float64_t Elapsed() const;

private:
    ::holo::common::Duration last_time_;

};  // class TicTocTimer

}  // namespace holo

#endif  // HOLO_OS_TICTOC_TIMER_H_
