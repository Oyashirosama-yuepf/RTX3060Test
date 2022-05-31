/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sliding_window.h
 * @brief Define a sliding window.
 * @author wanghaiyang@holomatic.com
 * @date "2021-10-28"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_SLIDING_WINDOW_H_
#define HOLO_MAP_SERVICE_SESSION_SLIDING_WINDOW_H_

#include <holo/core/types.h>
#include <holo/log/hololog.h>
#include <holo/os/tictoc_timer.h>

namespace holo
{
namespace map
{
namespace service
{
namespace session
{
/**
 * @addtogroup session
 * @{
 *
 */

/**
 * @brief A sliding window that manages work thread active/idle status for improve
 *        map data transmission efficiency between LMS server and clients.
 */
class SlidingWindow
{
public:
    /// Redefine types for inner members.
    using TimerType             = holo::TicTocTimer;
    using TimeValueType         = holo::float64_t;
    using DecelerationLevelType = holo::uint8_t;

    /**
     * @brief Access verbose flag.
     * 
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept
    {
        return this->verbose_;
    }

    /**
     * @brief Assign verbose flag.
     * 
     * @param[in] v true: Turn on debugging info flag;
     *              false: Turn off debugging info flag.
     */
    void SetVerbose(holo::bool_t const v)
    {
        this->verbose_ = v;
    }

    /**
     * @brief Access decelerating state.
     * 
     * @return true: Data transmission is decelerating or has been stoped;
     *         false: Data transmission is being protected.
     */
    holo::bool_t GetDeceleratingFlag() const noexcept
    {
        return this->is_decelerating_;
    }

    /**
     * @brief Access protecting state.
     * 
     * @return true: Data transmission is being protected;
     *         false: Data transmission has been stoped or is decelerating,
     */
    holo::bool_t GetProtectingFlag() const noexcept
    {
        return this->is_protecting_;
    }

    /**
     * @brief Access max idle time.
     * 
     * @return Max idle time, unit: millisecond, default 1000 millisecond.
     */
    TimeValueType GetMaxIdleInterval() const noexcept
    {
        return this->max_idle_interval_;
    }

    /**
     * @brief Assign max idle time.
     * 
     * @param[in] v unit: millisecond.
     */
    void SetMaxIdleInterval(TimeValueType const& v)
    {
        this->max_idle_interval_ = v;
    }

    /**
     * @brief Access min idle time.
     * 
     * 
     * @return Min idle time, unit: millisecond, default 1 millisecond.
     */
    TimeValueType GetMinIdleInterval() const noexcept
    {
        return this->min_idle_interval_;
    }

    /**
     * @brief Assign min idle time.
     * 
     * @param[in] v unit: millisecond.
     */
    void SetMinIdleInterval(TimeValueType const& v)
    {
        this->min_idle_interval_ = v;
    }

    /**
     * @brief Access current idle time.
     * 
     * @return Current idle time, unit: millisecond.
     */
    TimeValueType GetCurrentIdleInterval() const noexcept
    {
        return this->current_idle_interval_;
    }

    /**
     * @brief Access protected time.
     * 
     * @return Protected time, unit: millisecond, default 3000 millisecond.
     */
    TimeValueType GetProtectedInterval() const noexcept
    {
        return this->protected_interval_;
    }

    /**
     * @brief Assign protected time.
     * 
     * @param[in] v Protected time, uint: millisecond.
     */
    void SetProtectedInterval(TimeValueType const v)
    {
        this->protected_interval_ = v;
    }

    /**
     * @brief Access max deceleration time.
     * 
     * @return Max deceleration time, unit: millisecond, default 3000 millisecond.
     */
    TimeValueType GetMaxDecelerationDuration() const noexcept
    {
        return this->max_deceleration_duration_;
    }

    /**
     * @brief Assign max deceleration time.
     * 
     * @param[in] v Max deceleration time, unit: millisecond.
     */
    void SetMaxDecelerationDuration(TimeValueType const v)
    {
        this->max_deceleration_duration_ = v;
    }

    /**
     * @brief Access max deceleration level.
     * 
     * @return Max deceleration level, default level 3.
     */
    DecelerationLevelType GetMaxDecelerationLevel() const noexcept
    {
        return this->max_deceleration_level_;
    }

    /**
     * @brief Assign max deceleration level.
     * 
     * @param[in] Max deceleration.
     */
    void SetMaxDecelerationLevel(DecelerationLevelType const l)
    {
        this->max_deceleration_level_ = l;
    }

    /**
     * @brief Access current deceleration level.
     * 
     * @return Current deceleration level.
     */
    holo::bool_t GetCurrentDecelerationLevel() const noexcept
    {
        return this->current_deceleration_level_;
    }

    /**
     * @brief Reset sliding window.
     */
    void Reset()
    {
        this->verbose_          = false;
        this->is_protecting_    = false;
        this->is_decelerating_  = false;

        this->max_idle_interval_        = 1000.0;
        this->min_idle_interval_        = 1.0;
        this->protected_interval_       = 3000.0;
        this->current_idle_interval_    = 1.0;

        this->max_deceleration_duration_    = 3000.0;
        this->max_deceleration_level_       = 3;
        this->current_deceleration_level_   = 0;
    }

    /**
     * @brief If worker thread is busy, it should active Accelerate().
     * 
     */
    void Accelerate()
    {
        // Protecting mode timer, within 3000.0 ms (Default value, defined by [protected_interval_])
        // the decelerating mode will not be turned on even though no tasks to do. As long as there is
        // task, it will always be in protecting mode.
        this->acceleration_timer_.Tic();

        this->is_protecting_            = true;
        this->is_decelerating_          = false;

        // As long as there is a task, worker therad should not be idle until no task to do.
        this->current_idle_interval_        = 0.0;
        // Reset deceleration level when worker thread work in accelartion status.
        this->current_deceleration_level_   = 0;
    }

    /**
     * @brief If worker thread is idle, it should active Decelerate().
     */
    void Decelerate()
    {
        if (this->isProtected())
        {
            // There is no task to do, but sliding window still in protecting mode, worker thread
            // should idle 1 ms(Default value) in order to save computing resource.
            this->current_idle_interval_ = this->min_idle_interval_;
            return;
        }

        // If sliding window out of protecting mode, it should in decelerating mode immediately.
        if (!this->is_decelerating_)
        {
            // Start deceleration timer, in 3000ms(Default interval) the idle time will increase
            // to 1000ms from 1ms.
            this->deceleration_timer_.Tic();
            this->is_decelerating_ = true;
            this->current_deceleration_level_ = 0;
        }

        // To milliseconds.
        TimeValueType const duration = this->deceleration_timer_.Elapsed() * 1000.0;
        if (duration > this->max_deceleration_duration_)
        {
            this->current_deceleration_level_ = this->max_deceleration_level_;
        }
        else
        {
            if (duration > this->current_deceleration_level_*this->max_idle_interval_)
            {
                this->current_deceleration_level_ = (this->current_deceleration_level_ >= this->max_deceleration_level_)
                    ? this->max_deceleration_level_ : (this->current_deceleration_level_ + 1);
            }
        }
        
        // Idle time will be changed step by step.
        DecelerationLevelType const delta = this->max_deceleration_level_ - this->current_deceleration_level_ + 1;
        TimeValueType const idle_duration = this->max_deceleration_duration_ / this->max_deceleration_level_;
        TimeValueType const idle_step = idle_duration / (delta * 10.0);
        this->current_idle_interval_ = idle_step;

        if (this->verbose_)
        {
            LOG(INFO) << "Decelerate debug, duration=" << duration << " level=" << this->current_deceleration_level_
                      << " delta=" << delta << " idle_step=" << idle_step << " idle_duration=" << idle_duration;
        }
    }

private:
    /**
     * @brief Check if the sliding window is protected.
     * 
     * @return true: Be protected;
     *         false: Otherwise.
     */
    holo::bool_t isProtected()
    {
        // Before turn on protecting mode, must start [acceleration_timer_].
        if (!this->is_protecting_)
        {
            return false;
        }

        // To milliseconds
        TimeValueType const duration = this->acceleration_timer_.Elapsed() * 1000.0;
        if (duration > this->protected_interval_)
        {
            this->is_protecting_ = false;
            return false;
        }

        return true;
    }

private:
    /// If true, print debugging info for current class object.
    holo::bool_t verbose_           = false;
    /// If true, current work will not be decelerated, even though no job to do,
    /// current idle at the most 1ms(Defined by min_idle_interval_).
    holo::bool_t is_protecting_     = false;
    /// If true, current work will be decelerated, the decelerating will last for
    /// xxx milliseconds(Defined by [max_deceleration_duration_]).
    /// When the decelerating stop, the current idle will be 1000 milliseconds(
    /// Defined by [max_idle_interval_], default 1000 milliseconds).
    holo::bool_t is_decelerating_   = false;

    /// Max idle interval, unit: millisecond, default 1000 millisecond.
    /// Only when the worker thread is completely slowed down, the idle interval will
    /// reach the maximum.
    TimeValueType max_idle_interval_        = 1000.0;
    /// Min idle interval, if the [is_protecting] is true, there is no jon to do,
    /// the current idle time will be minimum, otherwise it's will be 0.0.
    /// unit: millisecond, default 1 millisecond.
    TimeValueType min_idle_interval_        = 1.0;
    /// Current idle time, when the worker thread is accelerating, this value will toward
    /// [min_idle_interval], when the worker thread is decelerating, this value will
    /// toward [max_idle_interval_]. unit: millisecond, default 1 millisecond.
    TimeValueType current_idle_interval_    = 1.0; //Uint: millisecond, 1ms.
    /// Protected time, even though there is no job to do, within the protected interval,
    /// the current idle time will not increase. unit: millisecond, default 3000 millisecond.
    TimeValueType protected_interval_       = 3000.0;

    /// Max deceleration duration, within this duration, current idle interval will increase
    /// to [max_idle_interval_] from [min_idle_interval_]. unit: millisecond, default 3000
    /// millisecond.
    TimeValueType max_deceleration_duration_ = 3000.0;

    /// Max deceleration level, work with [max_deceleration_duration_].
    DecelerationLevelType max_deceleration_level_           = 3;
    /// Current deceleration level,  work  with [max_deceleration_duration_], it is used
    /// to adjust the speed reduction ration.
    DecelerationLevelType current_deceleration_level_       = 0;

    /// Timer for acceleration.
    TimerType acceleration_timer_;
    /// Timer for deceleration.
    TimerType deceleration_timer_;
}; ///< End of class SlidingWindow.

/**
 * @}
 *
 */

} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_SLIDING_WINDOW_H_ */