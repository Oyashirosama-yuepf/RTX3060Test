#ifndef HOLO_THREAD_OBJECT_POOL_H_
#define HOLO_THREAD_OBJECT_POOL_H_

#include <assert.h>
#include <holo/core/types.h>
#include <atomic>
#include <iostream>
#include <memory>

#include "exceptions.h"
#include "internal/free_stack.h"

namespace holo
{
namespace thread
{
template <typename T>
class ObjectPool : public std::enable_shared_from_this<ObjectPool<T>>
{
public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = value_type const&;
    using pointer         = value_type*;
    using const_pointer   = value_type const*;

    ObjectPool() noexcept : stack_{}, size_{0U}, used_size_{0U}
    {
    }

    ~ObjectPool() noexcept
    {
        Node* node = stack_.TryGet();
        while (node)
        {
            delete node;
            node = stack_.TryGet();
        }
    }

    ObjectPool(ObjectPool&&) = default;
    ObjectPool& operator=(ObjectPool&&) = default;

    template <typename... Args>
    void Add(Args&&... args)
    {
        stack_.Add(new Node(std::forward<Args>(args)...));
        (void)size_.fetch_add(1);
    }

    std::shared_ptr<T> Get()
    {
        Node* node = alloc();
        if (node)
        {
            T*   object_pointer = &node->data;
            auto self           = this->shared_from_this();

            return std::shared_ptr<T>(object_pointer, [self, node](T* object) {
                (void)object;
                self->free(node);
            });
        }

        return nullptr;
    }

    size_t GetSize() const noexcept
    {
        return size_.load();
    }

    size_t GetUsedSize() const noexcept
    {
        return used_size_.load();
    }

    holo::bool_t IsEmpty() const noexcept
    {
        return size_.load() == used_size_.load();
    }

private:
    ObjectPool(ObjectPool const&) = delete;
    ObjectPool& operator=(ObjectPool const&) = delete;

    struct Node : public internal::FreeStack<Node>::NodeBase
    {
        using Base = typename internal::FreeStack<Node>::NodeBase;

        template <typename... Args>
        Node(Args&&... args) : Base{}, data{std::forward<Args>(args)...}
        {
        }

        T data;
    };

    Node* alloc()
    {
        Node* node = stack_.TryGet();
        if (nullptr == node)
        {
            return nullptr;
        }

        (void)used_size_.fetch_add(1);

        return node;
    }

    holo::bool_t free(Node* node)
    {
        holo::bool_t ret = stack_.Add(node);

        if (ret)
        {
            (void)used_size_.fetch_sub(1);
        }
        else
        {
            DoubleFreeException e{"object pool: double free!"};
            throw e;
        }

        return true;
    }

private:
    internal::FreeStack<Node> stack_;
    std::atomic<size_t>       size_;
    std::atomic<size_t>       used_size_;
};

}  // namespace thread
}  // namespace holo
#endif
