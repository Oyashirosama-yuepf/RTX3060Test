#ifndef HOLO_THREAD_LOCKFREE_CIRCULAR_QUEUE_H_
#define HOLO_THREAD_LOCKFREE_CIRCULAR_QUEUE_H_

#include <assert.h>
#include <holo/core/types.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <vector>

#include "exceptions.h"

namespace holo
{
namespace thread
{
template <typename T>
class LockfreeCircularQueue
{
private:
    enum class State : uint8_t
    {
        IDLE   = 0U,
        WAIT   = 1U,
        READY  = 2U,
        TAKING = 3U,
    };

public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;

    explicit LockfreeCircularQueue(size_t capacity)
      : queue_(capacity), flag_(capacity), head_{0U}, tail_{0U}, size_{0U}, capacity_{capacity}, break_{false}
    {
        assert(capacity >= 32U);

        if (0U != (capacity & (capacity - 1)))
        {
            IllegalParameterException e{"capacity Must be an integer power of 2"};
            throw e;
        }

        for (size_t i = 0U; i < capacity; i++)
        {
            flag_[i].store(State::IDLE);
        }
    }

    holo::bool_t TryPush(T const& value)
    {
        size_t old_tail{0U};
        size_t new_tail{0U};
        State  exp_state{State::IDLE};

        while (!break_.load())
        {
            old_tail = tail_.load();
            new_tail = old_tail + 1U;

            // full
            if (index(new_tail) == index(head_.load()))
            {
                return false;
            }

            exp_state = State::IDLE;
            // exchange success, then +1; or next loop
            // tail_ does not skip non idle nodes
            if (flag_[index(old_tail)].compare_exchange_strong(exp_state, State::WAIT))
            {
                if (!tail_.compare_exchange_strong(old_tail, index(new_tail)))
                {
                    LogicalErrorException e{"TryPush, tail_ is change! unkown error"};
                    throw e;
                }
                break;
            }
            // std::this_thread::yield();
        }

        if (break_.load())
        {
            exp_state = State::WAIT;
            (void)flag_[index(old_tail)].compare_exchange_strong(exp_state, State::IDLE);
            return false;
        }

        queue_[index(old_tail)] = value;
        (void)size_.fetch_add(1);

        exp_state = State::WAIT;
        if (!flag_[index(old_tail)].compare_exchange_strong(exp_state, State::READY))
        {
            LogicalErrorException e{"TryPush, flag_ value NOT State::WAIT! unkown error"};
            throw e;
        }

        data_available_condition_.notify_one();

        return true;
    }

    holo::bool_t TryPush(T&& value)
    {
        size_t old_tail{0U};
        size_t new_tail{0U};
        State  exp_state{State::IDLE};

        while (!break_.load())
        {
            old_tail = tail_.load();
            new_tail = old_tail + 1U;

            // full
            if (index(new_tail) == index(head_.load()))
            {
                return false;
            }

            exp_state = State::IDLE;
            // exchange success, then +1; or next loop
            // tail_ does not skip non idle nodes
            if (flag_[index(old_tail)].compare_exchange_strong(exp_state, State::WAIT))
            {
                if (!tail_.compare_exchange_strong(old_tail, index(new_tail)))
                {
                    LogicalErrorException e{"TryPush, tail_ is change! unkown error"};
                    throw e;
                }
                break;
            }
            // std::this_thread::yield();
        }

        if (break_.load())
        {
            exp_state = State::WAIT;
            (void)flag_[index(old_tail)].compare_exchange_strong(exp_state, State::IDLE);
            return false;
        }

        queue_[index(old_tail)] = std::forward<T>(value);
        (void)size_.fetch_add(1);

        exp_state = State::WAIT;
        if (!flag_[index(old_tail)].compare_exchange_strong(exp_state, State::READY))
        {
            LogicalErrorException e{"TryPush, flag_ value ERROR! unkown error"};
            throw e;
        }

        data_available_condition_.notify_one();

        return true;
    }

    holo::bool_t WaitForTake(std::vector<T>& list)
    {
        (void)list;
        return false;
    }

    holo::bool_t WaitForTake(std::list<T>& list, holo::uint32_t milliseconds)
    {
        (void)list;
        (void)milliseconds;
        return false;
    }

    holo::bool_t WaitForTake(T& value)
    {
        do
        {
            if (TryTake(value))
            {
                return true;
            }

            waitForDataVailable();
        } while (!break_.load());

        return false;
    }

    holo::bool_t WaitForTake(T& value, holo::uint32_t milliseconds)
    {
        do
        {
            if (TryTake(value))
            {
                return true;
            }

            if (!waitForDataVailable(milliseconds))
            {
                return false;
            }
        }while (!break_.load());

        return false;
    }

    holo::bool_t TryTake(T& value)
    {
        size_t old_head{head_.load()};
        size_t new_head{0U};
        State  exp_state{State::READY};

        do
        {
            new_head = old_head + 1U;
            // empty
            if (index(old_head) == index(tail_.load()))
            {
                data_empty_condition_.notify_all();
                return false;
            }
        } while (!head_.compare_exchange_strong(old_head, index(new_head)));

        exp_state = State::READY;
        while (!break_.load() && !flag_[index(old_head)].compare_exchange_strong(exp_state, State::TAKING))
        {
            // never happen
            if (State::IDLE == exp_state)
            {
                if (break_.load())
                {
                    return false;
                }
                else
                {
                    exp_state = State::READY;
                    LogicalErrorException e{"TryTake, flag_ value IS State::IDLE! unkown error"};
                    throw e;
                }
            }
            else if (State::WAIT == exp_state)
            {
                // always happen
                exp_state = State::READY;
                continue;
            }
            else if (State::READY == exp_state)
            {
                // never happen
                exp_state = State::READY;
                LogicalErrorException e{"TryTake, flag_ value IS State::READY! unkown error"};
                throw e;
            }
            else
            {
                // some one taking. never happen. Because tail_ does not skip non idle nodes
                return false;
            }
        }

        if (break_.load())
        {
            return false;
        }

        value = std::move(queue_[index(old_head)]);
        (void)size_.fetch_sub(1);
        if (0 == size_.load())
        {
            data_empty_condition_.notify_all();
        }

        exp_state = State::TAKING;
        if (!flag_[index(old_head)].compare_exchange_strong(exp_state, State::IDLE))
        {
            LogicalErrorException e{"TryTake, flag_ value ERROR! unkown error"};
            throw e;
        }

        return true;
    }

    holo::bool_t WaitForEmpty()
    {
        std::unique_lock<std::mutex> locker(mutex_);
        data_empty_condition_.wait(locker, [this] { return break_.load() || IsEmpty(); });

        return true;
    }

    holo::bool_t WaitForEmpty(holo::uint32_t milliseconds)
    {
        std::unique_lock<std::mutex> locker(mutex_);

        holo::bool_t ret = data_empty_condition_.wait_for(locker, std::chrono::milliseconds(milliseconds),
                                                          [this] { return break_.load() || IsEmpty(); });

        if (true == ret || break_.load())
        {
            return true;
        }

        return false;
    }

    void BreakWait()
    {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            break_.store(true);
        }
        data_available_condition_.notify_all();
        data_empty_condition_.notify_all();
    }

    holo::bool_t IsEmpty()
    {
        return 0U == size_.load();
    }

    holo::bool_t IsFull()
    {
        return tail_ + 1 == head_;
    }

    size_t Size()
    {
        return size_.load();
    }

private:
    size_t index(size_t idx)
    {
        return idx & (capacity_ - 1U);
    }

    holo::bool_t waitForDataVailable()
    {
        std::unique_lock<std::mutex> locker(mutex_);

        data_available_condition_.wait(locker, [this] { return break_.load() || !IsEmpty(); });

        return true;
    }

    holo::bool_t waitForDataVailable(holo::uint32_t milliseconds)
    {
        std::unique_lock<std::mutex> locker(mutex_);

        return data_available_condition_.wait_for(locker, std::chrono::milliseconds(milliseconds),
                                                  [this] { return break_.load() || !IsEmpty(); });
    }

private:
    std::vector<T>                  queue_;
    std::vector<std::atomic<State>> flag_;
    std::atomic<size_t>             head_;
    std::atomic<size_t>             tail_;
    std::atomic<size_t>             size_;
    mutable std::mutex              mutex_;
    std::condition_variable         data_available_condition_;
    std::condition_variable         data_empty_condition_;
    size_t                          capacity_;
    std::atomic<holo::bool_t>       break_;
};  // namespace thread
}  // namespace thread
}  // namespace holo
#endif
