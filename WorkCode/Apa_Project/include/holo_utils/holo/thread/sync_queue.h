#ifndef HOLO_THREAD_SYNC_QUEUE_H_
#define HOLO_THREAD_SYNC_QUEUE_H_

#include <holo/core/types.h>
#include <chrono>
#include <condition_variable>
#include <list>
#include <mutex>

namespace holo
{
namespace thread
{
template <typename T>
class SyncQueue
{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;

    explicit SyncQueue(size_t capacity) : capacity_(capacity), break_(false)
    {
    }

    holo::bool_t TryPush(T const& value)
    {
        std::unique_lock<std::mutex> locker(mutex_);
        if (!break_ && notFull())
        {
            queue_.emplace_back(value);
            data_available_condition_.notify_one();
            return true;
        }
        else
        {
            return false;
        }
    }

    holo::bool_t TryPush(T&& value)
    {
        std::unique_lock<std::mutex> locker(mutex_);
        if (!break_ && notFull())
        {
            queue_.emplace_back(std::forward<T>(value));
            data_available_condition_.notify_one();
            return true;
        }
        else
        {
            return false;
        }
    }

    holo::bool_t WaitForTake(std::list<T>& list)
    {
        std::unique_lock<std::mutex> locker(mutex_);
        data_available_condition_.wait(locker, [this] { return break_ || notEmpty(); });

        if (break_)
        {
            return false;
        }

        list = std::move(queue_);
        data_empty_condition_.notify_all();
        return true;
    }

    holo::bool_t WaitForTake(std::list<T>& list, holo::uint32_t milliseconds)
    {
        std::unique_lock<std::mutex> locker(mutex_);

        holo::bool_t ret = data_available_condition_.wait_for(locker, std::chrono::milliseconds(milliseconds),
                                                              [this] { return break_ || notEmpty(); });

        if (false == ret || break_)
        {
            return false;
        }

        list = std::move(queue_);
        data_empty_condition_.notify_all();
        return true;
    }

    holo::bool_t WaitForTake(T& value)
    {
        std::unique_lock<std::mutex> locker(mutex_);
        data_available_condition_.wait(locker, [this] { return break_ || notEmpty(); });

        if (break_)
        {
            return false;
        }

        value = queue_.front();
        queue_.pop_front();
        data_empty_condition_.notify_all();
        return true;
    }

    holo::bool_t WaitForTake(T& value, holo::uint32_t milliseconds)
    {
        std::unique_lock<std::mutex> locker(mutex_);

        holo::bool_t ret = data_available_condition_.wait_for(locker, std::chrono::milliseconds(milliseconds),
                                                              [this] { return break_ || notEmpty(); });

        if (false == ret || break_)
        {
            return false;
        }

        value = queue_.front();
        queue_.pop_front();
        data_empty_condition_.notify_all();
        return true;
    }

    holo::bool_t TryTake(T& value)
    {
        std::unique_lock<std::mutex> locker(mutex_);
        if (break_ || !notEmpty())
        {
            return false;
        }

        value = queue_.front();
        queue_.pop_front();
        data_empty_condition_.notify_all();
        return true;
    }

    holo::bool_t WaitForEmpty()
    {
        std::unique_lock<std::mutex> locker(mutex_);
        data_empty_condition_.wait(locker, [this] { return break_ || queue_.empty(); });

        return true;
    }

    holo::bool_t WaitForEmpty(holo::uint32_t milliseconds)
    {
        std::unique_lock<std::mutex> locker(mutex_);

        holo::bool_t ret = data_empty_condition_.wait_for(locker, std::chrono::milliseconds(milliseconds),
                                                          [this] { return break_ || queue_.empty(); });

        if (true == ret || break_)
        {
            return true;
        }

        return false;
    }

    void BreakWait()
    {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            break_ = true;
        }
        data_available_condition_.notify_all();
        data_empty_condition_.notify_all();
    }

    holo::bool_t IsEmpty()
    {
        std::lock_guard<std::mutex> locker(mutex_);
        return queue_.empty();
    }

    holo::bool_t IsFull()
    {
        std::lock_guard<std::mutex> locker(mutex_);
        return queue_.size() == capacity_;
    }

    size_t Size()
    {
        std::lock_guard<std::mutex> locker(mutex_);
        return queue_.size();
    }

private:
    holo::bool_t notFull()
    {
        holo::bool_t full = (queue_.size() >= capacity_);
        return !full;
    }

    holo::bool_t notEmpty()
    {
        holo::bool_t empty = queue_.empty();
        return !empty;
    }

private:
    std::list<T>            queue_;
    mutable std::mutex      mutex_;
    std::condition_variable data_available_condition_;
    std::condition_variable data_empty_condition_;
    size_t                  capacity_;
    holo::bool_t            break_;
};

}  // namespace thread
}  // namespace holo
#endif
