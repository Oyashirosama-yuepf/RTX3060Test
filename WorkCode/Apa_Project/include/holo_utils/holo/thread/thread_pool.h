#ifndef HOLO_THREAD_THREAD_POOL_H_
#define HOLO_THREAD_THREAD_POOL_H_

#include <assert.h>
#include <holo/core/types.h>
#include <atomic>
#include <exception>
#include <functional>
#include <future>
#include <memory>
#include <thread>

#include "exceptions.h"
#include "lockfree_queue.h"
#include "sync_queue.h"

namespace holo
{
namespace thread
{
class ThreadPool final
{
public:
    static constexpr size_t DEFAULT_TASKS_NUMBER{1024U};

    explicit ThreadPool(size_t threads_num, size_t tasks_num = DEFAULT_TASKS_NUMBER)
      : run_flag_{true}, pause_flag_{false}, task_queue_{tasks_num}, thread_list_{}
    {
        assert(threads_num > 0U && tasks_num > 0U);

        for (size_t i = 0U; i < threads_num; ++i)
        {
            thread_list_.emplace_back(&ThreadPool::run, this);
        }
    }

    ~ThreadPool() noexcept
    {
        Destroy();
    }

    ThreadPool(ThreadPool const&) = delete;
    ThreadPool(ThreadPool&&)      = delete;
    ThreadPool& operator=(ThreadPool const&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    template <typename Function, typename... Args>
    std::future<typename std::result_of<Function(Args...)>::type> AddTask(Function&& f, Args&&... args)
    {
        using return_type = typename std::result_of<Function(Args...)>::type;

        if (!pause_flag_.load())
        {
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<Function>(f), std::forward<Args>(args)...));

            if (!task_queue_.TryPush([task]() { (*task)(); }))
            {
                TaskQueueIsFullException e{"task queue is Full!"};
                throw e;
            }
            return task->get_future();
        }

        ThreadPoolPauseStatusException e{"thread pool is pause! can not add task!"};
        throw e;
        // return std::future<void>;
    }

    void Resume()
    {
        pause_flag_.store(false);
    }

    void Pause()
    {
        pause_flag_.store(true);
    }

    void WaitAndDestroy()
    {
        pause_flag_.store(true);
        task_queue_.WaitForEmpty();
        Destroy();
    }

    void Destroy()
    {
        pause_flag_.store(true);
        run_flag_.store(false);
        task_queue_.BreakWait();

        for (auto& thread : thread_list_)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
    }

private:
    void run()
    {
        while (run_flag_.load())
        {
            std::function<void()> task{};
            holo::uint32_t        milliseconds{1000U};
            if (!task_queue_.WaitForTake(task, milliseconds))
            {
                continue;
            }
            task();
        }
    }

private:
    std::atomic<holo::bool_t>            run_flag_;
    std::atomic<holo::bool_t>            pause_flag_;
    LockfreeQueue<std::function<void()>> task_queue_;
    std::list<std::thread>               thread_list_;
};

}  // namespace thread
}  // namespace holo
#endif
