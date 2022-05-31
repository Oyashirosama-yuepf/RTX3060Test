/**
 * @file worker.h
 * @brief The header of the worker.
 * @author sunlei(sunlei@holomatic.com)
 * @date 2017-08-11
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_WORKER_H_
#define _HOLO_PLANNING_WORKER_H_

#include <thread>
#include <vector>

#include <holo/core/types.h>
#include <holo/os/timer.h>

namespace holo
{
namespace planning
{
class Worker
{
public:
    enum WorkerState
    {
        WS_INIT      = 0x001,
        WS_RUN       = 0x002,
        WS_SUSPEND   = 0x003,
        WS_TERMINATE = 0x004,
    };

public:
    explicit Worker(float64_t hz);
    virtual ~Worker();

    void Run();
    void Suspend();
    void Terminate();

    float64_t GetFrequency() const noexcept;
    uint16_t  GetState() const noexcept;

protected:
    virtual bool_t Init();

    virtual bool_t PreWork();
    virtual bool_t DoWork() = 0;

    virtual bool_t PreIdle();
    virtual bool_t Idle();

    void PlanningThread();

private:
    Worker(const Worker& other);
    Worker(Worker&& other);
    Worker& operator=(const Worker& other);
    Worker& operator=(Worker&& other);

protected:
    std::thread thread_;
    Timer       timer_;
    float64_t   hz_;
    uint16_t    worker_state_;
    bool_t      inited_;
};

}  // namespace planning
}  // namespace holo

#endif
