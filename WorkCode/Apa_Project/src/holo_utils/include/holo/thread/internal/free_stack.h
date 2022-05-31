#ifndef HOLO_THREAD_INTERNAL_FREE_STACK_H_
#define HOLO_THREAD_INTERNAL_FREE_STACK_H_

#include <holo/core/types.h>
#include <atomic>

namespace holo
{
namespace thread
{
namespace internal
{
/**
 * @brief N must inherit NodeBase or have the same fields (and initialization)
 *
 * @tparam N
 */
template <typename N>
class FreeStack
{
public:
    enum class NodeState : holo::uint8_t
    {
        OCCUPIED  = 0U,
        IDLE      = 1U,
        RETURNING = 2U,
        TAKING    = 3U,
    };

    struct NodeBase
    {
        NodeBase() : state{NodeState::OCCUPIED}, next{nullptr}
        {
        }

        std::atomic<NodeState> state;
        std::atomic<N*>        next;
    };

    FreeStack() noexcept : top_{nullptr}
    {
    }

    inline holo::bool_t Add(N* node)
    {
        NodeState old_state = NodeState::OCCUPIED;
        if (node->state.compare_exchange_strong(old_state, NodeState::RETURNING))
        {
            addKnowingStateIsOccupied(node);
            return true;
        }
        return false;
    }

    inline N* TryGet()
    {
        auto top = top_.load(std::memory_order_acquire);
        while (top != nullptr)
        {
            auto      prevTop   = top;
            NodeState old_state = NodeState::IDLE;
            if (!top->state.compare_exchange_strong(old_state, NodeState::TAKING, std::memory_order_acquire,
                                                    std::memory_order_relaxed))
            {
                top = top_.load(std::memory_order_acquire);
                continue;
            }

            auto next = top->next.load(std::memory_order_relaxed);
            if (top_.compare_exchange_strong(top, next, std::memory_order_acquire, std::memory_order_relaxed))
            {
                top->state.store(NodeState::OCCUPIED, std::memory_order_release);
                return top;
            }
            else
            {
                prevTop->state.store(NodeState::IDLE, std::memory_order_release);
            }
        }

        return nullptr;
    }

    // Useful for traversing the list when there's no contention (e.g. to destroy remaining nodes)
    N* GetTopUnsafe() const
    {
        return top_.load(std::memory_order_relaxed);
    }

private:
    inline void addKnowingStateIsOccupied(N* node)
    {
        auto top = top_.load(std::memory_order_relaxed);
        while (true)
        {
            node->next.store(top, std::memory_order_relaxed);
            node->state.store(NodeState::IDLE, std::memory_order_release);

            if (top_.compare_exchange_strong(top, node, std::memory_order_release, std::memory_order_relaxed))
            {
                return;
            }
        }
    }

private:
    std::atomic<N*> top_;
};

}  // namespace internal
}  // namespace thread
}  // namespace holo
#endif
