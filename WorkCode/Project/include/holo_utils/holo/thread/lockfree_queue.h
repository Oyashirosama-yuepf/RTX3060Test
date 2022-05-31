#ifndef HOLO_THREAD_LOCKFREE_QUEUE_H_
#define HOLO_THREAD_LOCKFREE_QUEUE_H_

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

namespace holo
{
namespace thread
{
template <typename T>
class LockfreeQueue
{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;

    explicit LockfreeQueue(size_t capacity)
      : idle_head_{nullptr}
      , idle_tail_{nullptr}
      , data_head_{nullptr}
      , data_tail_{nullptr}
      , size_{0U}
      , capacity_{capacity}
      , break_{false}
    {
        assert(capacity >= 2U);

        Node* data_node = new Node();
        data_head_.store(data_node);
        data_tail_.store(data_node);

        Node* idle_head_node = new Node();
        idle_head_.store(idle_head_node);

        Node* idle_tail_node = new Node();
        idle_tail_.store(idle_tail_node);

        Node* idle_node = idle_head_node;
        for (size_t i = 2U; i < capacity + 1U; i++)
        {
            idle_node->next.store(new Node());
            idle_node = idle_node->next.load();
        }
        idle_node->next.store(idle_tail_node);
    }

    ~LockfreeQueue()
    {
        Node* node = idle_head_.load();
        Node* tmp  = node;
        while (node)
        {
            tmp  = node;
            node = node->next.load();
            delete tmp;
        }

        node = data_head_.load();
        while (node)
        {
            tmp  = node;
            node = node->next.load();
            delete tmp;
        }
    }

    LockfreeQueue(LockfreeQueue const&) = delete;
    LockfreeQueue& operator=(LockfreeQueue const&) = delete;

    LockfreeQueue(LockfreeQueue&&) = default;
    LockfreeQueue& operator=(LockfreeQueue&&) = default;

    holo::bool_t TryPush(T const& value)
    {
        Node* new_idle_head{nullptr};
        Node* old_idle_head{idle_head_.load()};

        do
        {
            new_idle_head = old_idle_head->next.load();
            // maybe full
            if (new_idle_head == nullptr)
            {
                data_available_condition_.notify_one();
                return false;
            }
        } while (!idle_head_.compare_exchange_weak(old_idle_head, new_idle_head));

        old_idle_head->next.store(nullptr);
        old_idle_head->data = value;
        old_idle_head->refs.store(2U);

        Node* old_data_tail{data_tail_.load()};
        while (!data_tail_.compare_exchange_weak(old_data_tail, old_idle_head))
        {
        }
        (void)size_.fetch_add(1U);
        old_data_tail->next.store(old_idle_head);

        data_available_condition_.notify_one();

        return true;
    }

    holo::bool_t TryPush(T&& value)
    {
        Node* new_idle_head{nullptr};
        Node* old_idle_head{idle_head_.load()};

        do
        {
            new_idle_head = old_idle_head->next.load();
            // maybe full
            if (new_idle_head == nullptr)
            {
                data_available_condition_.notify_one();
                return false;
            }
        } while (!idle_head_.compare_exchange_weak(old_idle_head, new_idle_head));

        old_idle_head->next.store(nullptr);
        old_idle_head->data = std::forward<T>(value);
        old_idle_head->refs.store(2U);

        Node* old_data_tail{data_tail_.load()};
        while (!data_tail_.compare_exchange_weak(old_data_tail, old_idle_head))
        {
        }
        (void)size_.fetch_add(1U);
        old_data_tail->next.store(old_idle_head);

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
        Node* new_data_head{nullptr};
        Node* old_data_head{data_head_.load()};

        do
        {
            new_data_head = old_data_head->next.load();
            // maybe empty
            if (new_data_head == nullptr)
            {
                data_empty_condition_.notify_all();
                return false;
            }
        } while (!data_head_.compare_exchange_weak(old_data_head, new_data_head));

        value                = std::move(new_data_head->data);
        size_t new_head_refs = new_data_head->refs.fetch_sub(1U);
        old_data_head->next.store(nullptr);
        size_t old_head_refs = old_data_head->refs.fetch_sub(1U);

        (void)size_.fetch_sub(1U);

        if (1U == old_head_refs)
        {
            Node* old_idle_tail{idle_tail_.load()};
            while (!idle_tail_.compare_exchange_weak(old_idle_tail, old_data_head))
            {
            }
            old_idle_tail->next.store(old_data_head);
        }

        if (1U == new_head_refs)
        {
            Node* old_idle_tail{idle_tail_.load()};
            while (!idle_tail_.compare_exchange_weak(old_idle_tail, new_data_head))
            {
            }
            old_idle_tail->next.store(new_data_head);
        }

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
    struct Node
    {
        Node() : data{}, next{nullptr}, refs{2U}
        {
        }

        Node(T const& t) : data{t}, next{nullptr}, refs{2U}
        {
        }

        Node(T&& t) : data{std::move(t)}, next{nullptr}, refs{2U}
        {
        }

        T                   data;
        std::atomic<Node*>  next;
        std::atomic<size_t> refs;
    };

private:
    std::atomic<Node*>        idle_head_;
    std::atomic<Node*>        idle_tail_;
    std::atomic<Node*>        data_head_;
    std::atomic<Node*>        data_tail_;
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
