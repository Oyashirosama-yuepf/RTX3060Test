/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file worker.h
 * @brief This header file defines Worker utility.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-12-03
 */

#ifndef HOLO_PERCEPTION_UTILS_WORKER_H_
#define HOLO_PERCEPTION_UTILS_WORKER_H_

#include <atomic>
#include <thread>

#include <holo/os/timer.h>
#include <holo/core/types.h>

namespace holo
{
namespace perception
{
/**
 * @addtogroup utils
 *
 * @{
 */

/**
 * @brief This class defines a base class of thread wrapper to control the frequence of a program.
 *
 * @details This class is pure virtual base class that all app program should derived this class and implement DoWork
 * function. Just put all your business code in DoWork function.
 */
class Worker
{
public:
    /**
     * @brief Enum defines program state
     */
    enum class WorkerState : uint8_t
    {
        WS_INIT      = 0x01,  ///< INIT state
        WS_RUN       = 0x02,  ///< RUN state
        WS_SUSPEND   = 0x03,  ///< SUSPEND state
        WS_TERMINATE = 0x04,  ///< TERMINATE state
    };

public:
    /**
     * @brief Constructor with params
     *
     * @param hz program frequence to work
     *
     * @throw std::system_error if the thread could not be started
     */
    explicit Worker(const holo::float32_t hz = 20.0f);

    /**
     * @brief Delete copy constructor
     *
     * @param other other Worker object
     */
    Worker(const Worker& other) = delete;

    /**
     * @brief Default destructor
     */
    virtual ~Worker() noexcept;

    /**
     * @brief main function to loop for thread
     *
     * @return true if function runs well
     * @return false if some thing unexpected happen
     */
    virtual bool DoWork() = 0;

    /**
     * @brief Set program state to WS_INIT
     */
    void Init() noexcept
    {
        worker_state_.store(WorkerState::WS_INIT, std::memory_order_acquire);
    }

    /**
     * @brief Set program state to WS_RUN
     */
    void Run() noexcept
    {
        worker_state_.store(WorkerState::WS_RUN, std::memory_order_acquire);
    }

    /**
     * @brief Set program state to WS_SUSPEND
     */
    void Suspend() noexcept
    {
        worker_state_.store(WorkerState::WS_SUSPEND, std::memory_order_acquire);
    }

    /**
     * @brief Set program state to WS_TERMINATE
     */
    void Terminate() noexcept
    {
        worker_state_.store(WorkerState::WS_TERMINATE, std::memory_order_acquire);
    }

    /**
     * @brief Get worker state
     *
     * @return worker state
     */
    WorkerState GetWorkerState() const noexcept
    {
        return worker_state_.load(std::memory_order_release);
    }

protected:
    /**
     * @brief main loop
     */
    void mainThread();

protected:
    std::thread              main_thread_;
    holo::Timer              timer_;
    std::atomic<WorkerState> worker_state_;  // TODO: check the performence with atomic operation
};

/**
 * @}
 */

}  // namespace perception
}  // namespace holo

#endif  // !HOLO_PERCEPTION_UTILS_WORKER_H_
