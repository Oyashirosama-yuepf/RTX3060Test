/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file allocator.h
 * @brief This header file defines byte swap functions
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2022-2-22
 */

#ifndef HOLO_CORE_ALLOCATOR_H_
#define HOLO_CORE_ALLOCATOR_H_

#include <memory>
#include <limits>

namespace holo
{
namespace core
{
/**
 * @brief Allocator with expected maximum allocated object size
 *
 * @tparam T Allocated object type. Maybe rebind to other types.
 * @tparam M Maximum allocated size.
 */
template <typename T, size_t M = std::numeric_limits<size_t>::max()>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = T const*;
    using reference = T&;
    using const_reference = T const&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    using propagate_on_container_copy_assignment = std::false_type; // Do not copy allocator instance when container is copied.
    using propagate_on_container_move_assignment = std::true_type; // Copy allocator instance when container is moved
    using propagate_on_container_swap = std::true_type; // Swap allocator instance when swapping two containers

    static size_t const MAX_SIZE_VALUE = M;

    /**
     * @brief Rebind allocator to new type
     *
     * @tparam U Rebind element type
     */
    template <typename U>
    struct rebind
    {
        typedef Allocator<U, M> other;
    };

    /**
     * @brief return address of value
     */
    pointer address(reference value) const
    {
        return &value;
    }

    const_pointer address(const_reference value) const
    {
        return &value;
    }

    /**
     * @brief default constructor. 
     */
    Allocator() noexcept : p_allocated_size_(std::make_shared<size_t>(0))
    {
    }

    Allocator(const Allocator& other) noexcept = default;

    template <typename U, size_t N>
    Allocator(const Allocator<U, N>& other) noexcept : p_allocated_size_(other.p_allocated_size_)
    {
    }

    ~Allocator() noexcept = default;

    // return maximum number of elements that can be allocated
    size_type max_size() const noexcept
    {
        return M;
    }

    // allocate but don't initialize num elements of type T
    pointer allocate(size_type num, const void* = 0)
    {
        if (*p_allocated_size_ + num > M)
        {
            throw std::bad_alloc();
        }
        pointer ret = (pointer)(::operator new (num * sizeof(T)));
        *p_allocated_size_ += num;
        return ret;
    }

    // initialize elements of allocated storage p with value value
    void construct(pointer p, const T& value)
    {
        new ((void*)p) T(value);
    }

    // destroy elements of initialized storage p
    void destroy(pointer p)
    {
        p->~T();
    }

    // deallocate storage p of deleted elements
    void deallocate(pointer p, size_type num)
    {
        ::operator delete ((void*)p);
        *p_allocated_size_ -= num;
    }

    std::shared_ptr<size_t> p_allocated_size_; // TODO Use static memory allocation
};
}  // namespace core
}  // namespace holo

namespace std
{
// return that all specializations of this allocator are interchangeable
template <typename T1, size_t N1, typename T2, size_t N2>
bool operator==(holo::core::Allocator<T1, N1> const&, holo::core::Allocator<T2, N2> const&) noexcept
{
    return true;
}

template <typename T1, size_t N1, typename T2, size_t N2>
bool operator!=(holo::core::Allocator<T1, N1> const&, holo::core::Allocator<T2, N2> const&) noexcept
{
    return false;
}
}  // namespace std

#endif
