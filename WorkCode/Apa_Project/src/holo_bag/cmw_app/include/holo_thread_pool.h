/**
 * @file holo_thread_pool.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the holo_thread_pool
 * @version 0.1
 * @date 2021-04-23
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_THREAD_POOL_H_
#define _HOLO_THREAD_POOL_H_

#include <holo/bag/interface/sequential_writer.h>
#include <holo/log/hololog.h>

#include <atomic>
#include <functional>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

namespace holo_cmw
{
class HoloThreadPool
{
    using Task = std::function<void()>;

public:
    HoloThreadPool(std::size_t threads);
    ~HoloThreadPool();

    template <class F, class... Args>
    auto EnQueue(F &&f, Args &&...args) -> std::future<decltype(f(args...))>;
    int IdleCount();

private:
    std::vector<std::thread>    pool_;
    std::queue<Task>            tasks_;
    ::holo::bag::MutexCondition mc_thread_pool_;
    std::atomic<bool>           stoped_;
    std::atomic<int>            idle_thread_num_;
};

inline HoloThreadPool::HoloThreadPool(std::size_t threads): stoped_{false}
{
    idle_thread_num_ = threads < 1 ? 1 : threads;
    for (int size = 0; size < idle_thread_num_; ++size)
    {
        pool_.emplace_back
        (
            [this]
            {
                while (!this->stoped_)
                {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock{this->mc_thread_pool_.mt_};
                        this->mc_thread_pool_.cv_.wait
                        (
                            lock,
                            [this]
                            {
                                return this->stoped_.load() || !this->tasks_.empty();
                            }
                        );
                        if (this->stoped_ && this->tasks_.empty())
                        {
                            return;
                        }
                        task = std::move(this->tasks_.front());
                        this->tasks_.pop();
                    }
                    idle_thread_num_--;
                    task();
                    idle_thread_num_++;
                }                
            }
        );
    }

};

inline HoloThreadPool::~HoloThreadPool()
{
    stoped_.store(true);
    mc_thread_pool_.cv_.notify_all();
    for(std::thread &thread : pool_)
    {
        if(thread.joinable())
        {
            thread.join();
        }
    }
};

template <class F, class... Args>
auto HoloThreadPool::EnQueue(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
{
    if(stoped_.load())
    {
        LOG(ERROR)<<"EnQueue on ThreadTool is stoped";
    }

    using ReturnType = decltype(f(args...));
    auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<ReturnType> future = task->get_future();
    {
        std::lock_guard<std::mutex> lock(mc_thread_pool_.mt_);
        tasks_.emplace([task](){(*task)();});
    }
    mc_thread_pool_.cv_.notify_one();
    return future;
};

inline int HoloThreadPool::IdleCount()
{
    return idle_thread_num_;
};

}

#endif // _HOLO_THREAD_POOL_H_