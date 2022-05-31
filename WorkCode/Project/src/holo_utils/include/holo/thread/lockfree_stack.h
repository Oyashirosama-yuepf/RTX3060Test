#ifndef HOLO_THREAD_LOCKFREE_STACK_H_
#define HOLO_THREAD_LOCKFREE_STACK_H_

#include <assert.h>
#include <holo/core/types.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <vector>

#include "exceptions.h"
#include "internal/free_stack.h"

namespace holo
{
namespace thread
{
template <typename T>
class LockfreeStack
{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;

    explicit LockfreeStack(size_t capacity)
      : idle_stack_{}, data_stack_{}, size_{0U}, capacity_{capacity}, break_{false}
    {
        for (size_t i = 0U; i < capacity_; i++)
        {
            idle_stack_.Add(new Node());
        }
    }

    ~LockfreeStack()
    {
        for (size_t i = 0U; i < capacity_; ++i)
        {
            Node* node = idle_stack_.TryGet();
            if (node)
            {
                delete node;
                node = nullptr;
            }

            node = data_stack_.TryGet();
            if (node)
            {
                delete node;
                node = nullptr;
            }
        }
    }

    LockfreeStack(LockfreeStack const&) = delete;
    LockfreeStack& operator=(LockfreeStack const&) = delete;

    LockfreeStack(LockfreeStack&&) = default;
    LockfreeStack& operator=(LockfreeStack&&) = default;

    holo::bool_t TryPush(T const& value)
    {
        Node* idle_node = idle_stack_.TryGet();
        if (nullptr == idle_node)
        {
            return false;
        }

        idle_node->data = value;

        data_stack_.Add(idle_node);

        (void)size_.fetch_add(1U);

        data_available_condition_.notify_one();

        return true;
    }

    holo::bool_t TryPush(T&& value)
    {
        Node* idle_node = idle_stack_.TryGet();
        if (nullptr == idle_node)
        {
            return false;
        }

        idle_node->data = std::forward<T>(value);

        data_stack_.Add(idle_node);

        (void)size_.fetch_add(1U);

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
        }while (!break_.load());

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
        Node* data_node = data_stack_.TryGet();
        if (data_node == nullptr)
        {
            data_empty_condition_.notify_all();
            return false;
        }

        value = std::move(data_node->data);
        (void)size_.fetch_sub(1U);

        idle_stack_.Add(data_node);

        if (0 == size_.load())
        {
            data_empty_condition_.notify_all();
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
        return size_.load() == capacity_;
    }

    size_t Size()
    {
        return size_.load();
    }

private:
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
    struct Node : public internal::FreeStack<Node>::NodeBase
    {
        using Base = typename internal::FreeStack<Node>::NodeBase;

        Node() : Base{}, data{}
        {
        }

        T data;
    };

private:
    internal::FreeStack<Node> idle_stack_;
    internal::FreeStack<Node> data_stack_;
    mutable std::mutex        mutex_;
    std::condition_variable   data_available_condition_;
    std::condition_variable   data_empty_condition_;
    std::atomic<size_t>       size_;
    size_t                    capacity_;
    std::atomic<holo::bool_t> break_;
};

}  // namespace thread
}  // namespace holo
#endif
