/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file localization_base.h
 * @brief define localization base
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#ifndef HOLO_LOCALIZATION_COMMON_LOCALIZATION_BASE_H_
#define HOLO_LOCALIZATION_COMMON_LOCALIZATION_BASE_H_

#include <atomic>
#include <memory>

#include <holo/localization/common/types.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief localization base class
 */
class LocalizationBase
{
public:
    /**
     * @brief state
     */
    enum class State
    {
        WAIT  = 0,  ///< wait until enough good measurements arrive to start
        READY = 1,  ///< sufficient measurements manager has been built
        IDLE  = 2,  ///< the core algorithm is idle
        RUN   = 3,  ///< the core algorithm is running
    };

    /**
     * @brief status
     */
    enum class Status
    {
        PAUSE = 0,  ///< main loop is paused
        SPIN  = 1,  ///< main loop is spin
        STOP  = 2,  ///< main loop has stopped
    };

    /**
     * @brief constructor
     */
    LocalizationBase() noexcept;

    /**
     * @brief destructor
     */
    virtual ~LocalizationBase() noexcept;

    /**
     * @brief get status
     */
    virtual Status GetStatus() const
    {
        return status_;
    }

    /**
     * @brief set status to spin
     */
    virtual void Spin();

    /**
     * @brief set status to pause
     */
    virtual void Pause();

    /**
     * @brief set status to stop
     */
    virtual void Stop();

protected:
    /**
     * @brief check internal state
     */
    virtual bool_t checkState() const;

    /**
     * @brief main thread function
     *
     * @param frequency main loop frequency
     */
    virtual void threadFunc(const Scalar frequency);

    /**
     * @brief check pre condition
     */
    virtual bool_t checkPreCondition();

    /**
     * @brief core algorithm happens here
     */
    virtual void run() = 0;

    /**
     * @brief post process
     */
    virtual bool_t postProcess();

    /**
     * @brief diagnostics system and publish diagnostic message
     */
    virtual void diagnosticSystem();

    std::atomic<State>  state_;   ///< algorithm state
    std::atomic<Status> status_;  ///< algorithm status

private:
};  // class LocalizationBase

/**
 * @}
 *
 */

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_LOCALIZATION_BASE_H_
