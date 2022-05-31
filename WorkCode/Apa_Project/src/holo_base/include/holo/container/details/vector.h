/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vector.h
 * @brief Wrapper for std::vector with limited max size.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-12-20
 */

#ifndef HOLO_CONTAINER_DETAILS_VECTOR_BASE_H_
#define HOLO_CONTAINER_DETAILS_VECTOR_BASE_H_

#include <holo/core/exception.h>
#include <holo/serialization/serialization.h>

#include <type_traits>
#include <vector>
#include <limits>

#include "traits.h"

namespace holo
{
namespace container
{
namespace details
{
/**
 * @brief VectorBase is base class for sequence container with predefined maximum element size.
 *
 * @tparam T Type of the elements
 * @tparam SIZE Max size of the vector
 * @tparam Allocator An allocator that is used to acquire/release memory and construct/destroy the elements.
 */
template <typename T, size_t SIZE, typename Allocator = std::allocator<T>>
class VectorBase
{
public:
    using ContainerType = std::vector<T, Allocator>;  ///< The underlying container type.

    static size_t const SIZE_VALUE = SIZE;

    using value_type             = typename ContainerType::value_type;
    using allocator_type         = typename ContainerType::allocator_type;
    using size_type              = typename ContainerType::size_type;
    using difference_type        = typename ContainerType::difference_type;
    using reference              = typename ContainerType::reference;
    using const_reference        = typename ContainerType::const_reference;
    using pointer                = typename ContainerType::pointer;
    using const_pointer          = typename ContainerType::const_pointer;
    using iterator               = typename ContainerType::iterator;
    using const_iterator         = typename ContainerType::const_iterator;
    using reverse_iterator       = typename ContainerType::reverse_iterator;
    using const_reverse_iterator = typename ContainerType::const_reverse_iterator;

    /**
     * @brief Default constructor
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase() : container_()
    {
        container_.reserve(SIZE);
    }

    /**
     * @brief Constructs an empty container with given allocator.
     *
     * @param alloc The allocator
     *
     * @throws Calls to Allocator::allocate may throw
     */
    explicit VectorBase(Allocator const& alloc) : container_(alloc)
    {
        container_.reserve(SIZE);
    }

    /**
     * @brief Constructs the container with count default-inserted instance of T.
     *
     * @param count Number of elements.
     *
     * @throws std::bad_alloc if count > SIZE.
     * @throws Calls to Allocator::allocate may throw
     */
    explicit VectorBase(size_type count)
    {
        if (count > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.reserve(SIZE);
        container_.assign(count, T());
    }

    /**
     * @brief Constructs the container with count copies of elements with value
     *
     * @param count Number of elements
     * @param value value to initialize elements of the container
     * @param alloc allocator to use for all memory allocations of this container.
     *
     * @throws std::bad_alloc if count > SIZE
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(size_type count, T const& value, Allocator const& alloc = Allocator()) : container_(alloc)
    {
        if (count > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.reserve(SIZE);
        container_.assign(count, value);
    }

    /**
     * @brief Constructs the container with the contents of the range [first, last)
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param first Start of range to copy elements
     * @param last End of range to copy elements
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws std::bad_alloc if std::distance(first, last) > SIZE
     * @throws Calls to Allocator::allocate may throw
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    VectorBase(InputIt first, InputIt last, Allocator const& alloc = Allocator()) : container_(alloc)
    {
        if (static_cast<size_t>(std::distance(first, last)) > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.reserve(SIZE);
        container_.assign(first, last);
    }

    /**
     * @brief Copy constructor
     *
     * @param other The other container.
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase const& other) : container_(other.container_)
    {
        container_.reserve(SIZE);
    }

    /**
     * @brief Copy constructor
     *
     * @param other The other container
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase const& other, Allocator const& alloc) : container_(other.container_, alloc)
    {
        container_.reserve(SIZE);
    }

    /**
     * @brief Move constructor
     *
     * @param other The other container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase&& other) : container_(std::move(other.container_))
    {
        container_.reserve(SIZE);
    }

    /**
     * @brief Allocator-extended move constructor
     *
     * @param other The other container
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase&& other, Allocator const& alloc) : container_(std::move(other.container_), alloc)
    {
        container_.reserve(SIZE);
    }

    /**
     * @brief Constructs with the contents of the initializer list
     *
     * @param init The initializer list
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws std::bad_alloc if initializer size > SIZE
     */
    VectorBase(std::initializer_list<T> init, Allocator const& alloc = Allocator()) : container_(alloc)
    {
        if (init.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.reserve(SIZE);
        container_.assign(init);
    }

    /**
     * @brief Construct with other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase(VectorBase<T, SIZE_, Allocator_> const& other)
      : container_(std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.get_allocator()))
    {
        if (other.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.reserve(SIZE);
        container_ = other.container_;
    }

    /**
     * @brief Construct with other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase(VectorBase<T, SIZE_, Allocator_>&& other)
      : container_(std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.get_allocator()))
    {
        if (other.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_ = std::move(other.container_);
        if (SIZE_ < SIZE)
        {
            container_.reserve(SIZE);
        }
    }

    /**
     * @brief Copy assign operator
     *
     * @param other The other container
     *
     * @return Reference to this container
     */
    VectorBase& operator=(VectorBase const& other) = default;

    /**
     * @brief Move assign operator
     *
     * @param other The other container
     *
     * @return Reference to this container
     */
    VectorBase& operator=(VectorBase&& other) = default;

    /**
     * @brief Replace the contents with those identified by initializer list
     *
     * @param ilist initializer list
     *
     * @return Reference to this container
     */
    VectorBase& operator=(std::initializer_list<T> ilist)
    {
        if (ilist.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_ = ilist;
        return *this;
    }

    /**
     * @brief Assign from other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase& operator=(VectorBase<T, SIZE_, Allocator_> const& other)
    {
        if (other.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_ = other.container_;
        return *this;
    }

    /**
     * @brief Assign from other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase& operator=(VectorBase<T, SIZE_, Allocator_>&& other)
    {
        if (other.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_ = std::move(other.container_);
        if (SIZE_ < SIZE)
        {
            container_.reserve(SIZE);
        }
        return *this;
    }

    /**
     * @brief Replace the contents with count copies of value
     *
     * @param count Number of elements
     * @param value Element value
     *
     * @throws std::bad_alloc if count > SIZE
     */
    void assign(size_type count, T const& value)
    {
        if (count > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.assign(count, value);
    }

    /**
     * @brief Replace the contents with copies of those in the range [first, last)
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param first Start of range to copy elements
     * @param last End of range to copy elements
     *
     * @throws std::bad_alloc if std::distance(first, last) > SIZE
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    void assign(InputIt first, InputIt last)
    {
        if (static_cast<size_t>(std::distance(first, last)) > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.assign(first, last);
    }

    /**
     * @brief Replace the contents with the those identified by initializer list
     *
     * @param ilist The initailizer list
     */
    void assign(std::initializer_list<T> ilist)
    {
        if (ilist.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.assign(ilist);
    }

    /**
     * @brief Return the associated allocator
     *
     * @return The associated allocator
     */
    allocator_type get_allocator() const
    {
        return container_.get_allocator();
    }

    /**
     * @brief Access specified element with bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     *
     * @throws std::out_of_range if pos > size()
     */
    reference at(size_type pos)
    {
        return container_.at(pos);
    }

    /**
     * @brief Access specified element with bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     *
     * @throws std::out_of_range if pos > size()
     */
    const_reference at(size_type pos) const
    {
        return container_.at(pos);
    }

    /**
     * @brief Access specified element without bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     */
    reference operator[](size_type pos)
    {
        return container_[pos];
    }

    /**
     * @brief Access specified element without bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     */
    const_reference operator[](size_type pos) const
    {
        return container_[pos];
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    reference front()
    {
        return container_.front();
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    const_reference front() const
    {
        return container_.front();
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    reference back()
    {
        return container_.back();
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    const_reference back() const
    {
        return container_.back();
    }

    /**
     * @brief Direct access to the underlying array.
     *
     * @return Pointer to underlying array
     */
    T* data() noexcept
    {
        return container_.data();
    }

    /**
     * @brief Direct access to the underlying array.
     *
     * @return Pointer to underlying array
     */
    T const* data() const noexcept
    {
        return container_.data();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    iterator begin()
    {
        return container_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator begin() const
    {
        return container_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator cbegin() const
    {
        return container_.cbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    reverse_iterator rbegin()
    {
        return container_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator rbegin() const
    {
        return container_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator crbegin() const
    {
        return container_.crbegin();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    iterator end()
    {
        return container_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator end() const
    {
        return container_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator cend() const
    {
        return container_.cend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    reverse_iterator rend()
    {
        return container_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator rend() const
    {
        return container_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator crend() const
    {
        return container_.crend();
    }

    /**
     * @brief Checks whether the container is empty
     *
     * @return true if container is empty otherwise false
     */
    bool empty() const noexcept
    {
        return container_.empty();
    }

    /**
     * @brief Get number of elements in container
     *
     * @return Number of elements.
     */
    size_type size() const noexcept
    {
        return container_.size();
    }

    /**
     * @brief Get maximum possible number of elements
     *
     * @return Maximum possible number of elements
     */
    size_type max_size() const noexcept
    {
        return SIZE;
    }

    /**
     * @brief Reserve storage to hold new_cap elements
     *
     * @param new_cap new element capacity
     */
    void reserve(size_type new_cap)
    {
        if (new_cap > SIZE)
        {
            throw std::bad_alloc();
        }
    }

    /**
     * @brief Get number of elements that can be held in currently allocated storage
     *
     * @return Number of elements
     */
    size_t capacity() const noexcept
    {
        return container_.capacity() > SIZE ? SIZE : container_.capacity();
    }

    /**
     * @brief This function does nothing. Only to keep consistance with STL vector
     */
    void shrink_to_fit()
    {
    }

    /**
     * @brief Clears the content
     */
    void clear() noexcept
    {
        container_.clear();
    }

    /**
     * @brief Insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if container size exceeded the maximum size.
     */
    iterator insert(const_iterator pos, T const& value)
    {
        if (container_.size() + 1 > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, value);
    }

    /**
     * @brief Insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if container size exceeded the maximum size.
     */
    iterator insert(const_iterator pos, T&& value)
    {
        if (container_.size() + 1 > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, std::move(value));
    }

    /**
     * @brief Insert count copies of the value before pos
     *
     * @param pos Iterator to insert value before
     * @param count Number of elements
     * @param value The value to insert
     *
     * @return iterator pointing to the first element inserted or pos if count == 0
     *
     * @throws std::bad_alloc if container size + count > SIZE.
     */
    iterator insert(const_iterator pos, size_type count, T const& value)
    {
        if (container_.size() + count > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, count, value);
    }

    /**
     * @brief Inserts elements from range [first, last) before pos
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param pos Iterator to insert value before
     * @param first Start of range to inserted elements
     * @param last End of range to inserted elements
     *
     * @return iterator pointing to the first element inserted or pos if first == last
     *
     * @throws std::bad_alloc if container size + std::distance(first, last) > SIZE.
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        if (container_.size() + static_cast<size_t>(std::distance(first, last)) > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, first, last);
    }

    /**
     * @brief Inserts elements from initializer list before pos
     *
     * @param pos Iterator to insert value before
     * @param ilist The initailizer list
     *
     * @return iterator pointing to the first element inserted or pos if ilist is empty
     *
     * @throws std::bad_alloc if container size + ilist.size() > SIZE.
     */
    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        if (container_.size() + ilist.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, ilist);
    }

    /**
     * @brief Construct element in-place
     *
     * @tparam Args Types of arguments
     * @param pos Iterator to insert value before
     * @param args arguments to forward to the constructor of the element
     *
     * @return iterator pointing to the emplaced element
     */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        if (container_.size() + 1 > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.emplace(pos, std::forward<Args>(args)...);
    }

    /**
     * @brief Remove element at pos
     *
     * @param pos Iterator pointing to the element to remove
     *
     * @return Iterator following the last removed element. if pos refers to last element, then the end() iterator is
     * returned.
     */
    iterator erase(const_iterator pos)
    {
        return container_.erase(pos);
    }

    /**
     * @brief Remove elements in the range [first, last)
     *
     * @param first Start of range to remove elements
     * @param last End of range to remove elements
     *
     * @return Iterator following the last removed element. If last == end(), then the updated end() iterator is
     * returned. If [first, last) is an empty range, then last is returned.
     */
    iterator erase(const_iterator first, const_iterator last)
    {
        return container_.erase(first, last);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @param value The element to add at the end.
     */
    void push_back(T const& value)
    {
        if (container_.size() + 1 > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.push_back(value);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @param value The element to add at the end.
     */
    void push_back(T&& value)
    {
        if (container_.size() + 1 > SIZE)
        {
            throw std::bad_alloc();
        }
        return container_.push_back(std::move(value));
    }

    /**
     * @brief Construct an element in-place at the end
     *
     * @tparam Args Types of arguments
     * @param args arguments to forward to the constructor of the element
     */
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (container_.size() + 1 > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Removes the last element.
     */
    void pop_back()
    {
        container_.pop_back();
    }

    /**
     * @brief Change the number of elements stored
     *
     * @param count Number of elements
     */
    void resize(size_type count)
    {
        if (count > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.resize(count);
    }

    /**
     * @brief Change the number of elements stored
     *
     * @param count Number of elements
     * @param value The value to initialize the new elements
     */
    void resize(size_type count, value_type const& value)
    {
        if (count > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.resize(count, value);
    }

    /**
     * @brief Swaps the contents
     *
     * @param other The other container
     */
    void swap(VectorBase& other) noexcept
    {
        container_.swap(other.container_);
    }

    /**
     * @brief Swaps the contents with VectorBase of different size.
     *
     * @tparam SIZE_ Size of the other VectorBase
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if size() > SIZE_.
     * @throws std::bad_alloc if other.size() > SIZE.
     */
    template <size_t SIZE_, typename = typename std::enable_if<(SIZE_ > SIZE)>::type>
    void swap(VectorBase<T, SIZE_, Allocator>& other)
    {
        if ((this->size() > SIZE_) || other.size() > SIZE)
        {
            throw std::bad_alloc();
        }
        container_.swap(other.container_);
        if (SIZE_ > SIZE)
        {
            other.container_.reserve(SIZE_);
        }
        else
        {
            container_.reserve(SIZE);
        }
    }

    template <size_t ALIGN = 4U, typename T_ = value_type,
              typename std::enable_if<std::is_arithmetic<T_>::value || std::is_enum<T_>::value>::type* = nullptr>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t)) +
               holo::serialization::AlignedSize<ALIGN>(this->size() * sizeof(value_type));
    }

    template <size_t ALIGN = 4U, typename T_ = value_type,
              typename std::enable_if<!(std::is_arithmetic<T_>::value || std::is_enum<T_>::value)>::type* = nullptr>
    size_t GetSerializedSize() const noexcept
    {
        size_t size = holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        for (size_t i = 0U; i < this->size(); ++i)
        {
            size += (*this)[i].template GetSerializedSize<ALIGN>();
        }
        return size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << static_cast<uint32_t>(size()) << holo::serialization::align;
        for (size_t i = 0U; i < this->size(); ++i)
        {
            serializer << (*this)[i];
        }
        serializer << holo::serialization::align;
    }

    template <typename S>
    void Deserialize(S& deserializer)
    {
        uint32_t size = 0U;
        deserializer >> size >> holo::serialization::align;
        this->resize(size);
        for (size_t i = 0U; i < this->size(); ++i)
        {
            deserializer >> (*this)[i];
        }
        deserializer >> holo::serialization::align;
    }

    template <typename T_, size_t SIZE_, typename Allocator_>
    friend class VectorBase;

protected:
    ~VectorBase() = default;

private:
    ContainerType container_;
};

/**
 * @brief Partial specialization for semi-automatic vector type.
 *
 * @tparam T Type of the elements
 * @tparam Allocator An allocator that is used to acquire/release memory and construct/destroy the elements.
 */
template <typename T, typename Allocator>
class VectorBase<T, 0U, Allocator>
{
public:
    using ContainerType = std::vector<T, Allocator>;  ///< The underlying container type.

    using value_type             = typename ContainerType::value_type;
    using allocator_type         = typename ContainerType::allocator_type;
    using size_type              = typename ContainerType::size_type;
    using difference_type        = typename ContainerType::difference_type;
    using reference              = typename ContainerType::reference;
    using const_reference        = typename ContainerType::const_reference;
    using pointer                = typename ContainerType::pointer;
    using const_pointer          = typename ContainerType::const_pointer;
    using iterator               = typename ContainerType::iterator;
    using const_iterator         = typename ContainerType::const_iterator;
    using reverse_iterator       = typename ContainerType::reverse_iterator;
    using const_reverse_iterator = typename ContainerType::const_reverse_iterator;

    /**
     * @brief Default constructor
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase() : container_()
    {
    }

    /**
     * @brief Constructs an empty container with given allocator.
     *
     * @param alloc The allocator
     *
     * @throws Calls to Allocator::allocate may throw
     */
    explicit VectorBase(Allocator const& alloc) : container_(alloc)
    {
    }

    /**
     * @brief Constructs the container with count default-inserted instance of T.
     *
     * @param count Number of elements.
     *
     * @throws std::bad_alloc if count > SIZE.
     * @throws Calls to Allocator::allocate may throw
     */
    explicit VectorBase(size_type count) : container_(count)
    {
    }

    /**
     * @brief Constructs the container with count copies of elements with value
     *
     * @param count Number of elements
     * @param value value to initialize elements of the container
     * @param alloc allocator to use for all memory allocations of this container.
     *
     * @throws std::bad_alloc if count > SIZE
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(size_type count, T const& value, Allocator const& alloc = Allocator()) : container_(count, value, alloc)
    {
    }

    /**
     * @brief Constructs the container with the contents of the range [first, last)
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param first Start of range to copy elements
     * @param last End of range to copy elements
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws std::bad_alloc if std::distance(first, last) > SIZE
     * @throws Calls to Allocator::allocate may throw
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    VectorBase(InputIt first, InputIt last, Allocator const& alloc = Allocator()) : container_(first, last, alloc)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other The other container.
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase const& other) : container_(other.container_)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other The other container
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase const& other, Allocator const& alloc) : container_(other.container_, alloc)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other The other container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase&& other) : container_(std::move(other.container_))
    {
    }

    /**
     * @brief Allocator-extended move constructor
     *
     * @param other The other container
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase&& other, Allocator const& alloc) : container_(std::move(other.container_), alloc)
    {
    }

    /**
     * @brief Constructs with the contents of the initializer list
     *
     * @param init The initializer list
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws std::bad_alloc if initializer size > SIZE
     */
    VectorBase(std::initializer_list<T> init, Allocator const& alloc = Allocator()) : container_(init, alloc)
    {
    }

    /**
     * @brief Construct with other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase(VectorBase<T, SIZE_, Allocator_> const& other) : container_(other.container_)
    {
    }

    /**
     * @brief Construct with other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase(VectorBase<T, SIZE_, Allocator_>&& other) : container_(std::move(other.container_))
    {
    }

    /**
     * @brief Copy assign operator
     *
     * @param other The other container
     *
     * @return Reference to this container
     */
    VectorBase& operator=(VectorBase const& other)
    {
        if (other.size() > capacity())
        {
            throw std::bad_alloc();
        }
        container_ = other.container_;
        return *this;
    }

    /**
     * @brief Move assign operator
     *
     * @param other The other container
     *
     * @return Reference to this container
     */
    VectorBase& operator=(VectorBase&& other)
    {
        if (other.size() > capacity())
        {
            throw std::bad_alloc();
        }
        container_ = std::move(other.container_);
        return *this;
    }

    /**
     * @brief Replace the contents with those identified by initializer list
     *
     * @param ilist initializer list
     *
     * @return Reference to this container
     */
    VectorBase& operator=(std::initializer_list<T> ilist)
    {
        if (ilist.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.assign(ilist.begin(), ilist.end());
        return *this;
    }

    /**
     * @brief Assign from other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase& operator=(VectorBase<T, SIZE_, Allocator_> const& other)
    {
        if (other.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_ = other.container_;
        return *this;
    }

    /**
     * @brief Assign from other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase& operator=(VectorBase<T, SIZE_, Allocator_>&& other)
    {
        if (other.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_ = std::move(other.container_);
        return *this;
    }

    /**
     * @brief Replace the contents with count copies of value
     *
     * @param count Number of elements
     * @param value Element value
     *
     * @throws std::bad_alloc if count > SIZE
     */
    void assign(size_type count, T const& value)
    {
        if (count > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.assign(count, value);
    }

    /**
     * @brief Replace the contents with copies of those in the range [first, last)
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param first Start of range to copy elements
     * @param last End of range to copy elements
     *
     * @throws std::bad_alloc if std::distance(first, last) > SIZE
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    void assign(InputIt first, InputIt last)
    {
        if (static_cast<size_t>(std::distance(first, last)) > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.assign(first, last);
    }

    /**
     * @brief Replace the contents with the those identified by initializer list
     *
     * @param ilist The initailizer list
     */
    void assign(std::initializer_list<T> ilist)
    {
        if (ilist.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.assign(ilist.begin(), ilist.end());
    }

    /**
     * @brief Return the associated allocator
     *
     * @return The associated allocator
     */
    allocator_type get_allocator() const
    {
        return container_.get_allocator();
    }

    /**
     * @brief Access specified element with bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     *
     * @throws std::out_of_range if pos > size()
     */
    reference at(size_type pos)
    {
        return container_.at(pos);
    }

    /**
     * @brief Access specified element with bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     *
     * @throws std::out_of_range if pos > size()
     */
    const_reference at(size_type pos) const
    {
        return container_.at(pos);
    }

    /**
     * @brief Access specified element without bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     */
    reference operator[](size_type pos)
    {
        return container_[pos];
    }

    /**
     * @brief Access specified element without bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     */
    const_reference operator[](size_type pos) const
    {
        return container_[pos];
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    reference front()
    {
        return container_.front();
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    const_reference front() const
    {
        return container_.front();
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    reference back()
    {
        return container_.back();
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    const_reference back() const
    {
        return container_.back();
    }

    /**
     * @brief Direct access to the underlying array.
     *
     * @return Pointer to underlying array
     */
    T* data() noexcept
    {
        return container_.data();
    }

    /**
     * @brief Direct access to the underlying array.
     *
     * @return Pointer to underlying array
     */
    T const* data() const noexcept
    {
        return container_.data();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    iterator begin()
    {
        return container_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator begin() const
    {
        return container_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator cbegin() const
    {
        return container_.cbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    reverse_iterator rbegin()
    {
        return container_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator rbegin() const
    {
        return container_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator crbegin() const
    {
        return container_.crbegin();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    iterator end()
    {
        return container_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator end() const
    {
        return container_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator cend() const
    {
        return container_.cend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    reverse_iterator rend()
    {
        return container_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator rend() const
    {
        return container_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator crend() const
    {
        return container_.crend();
    }

    /**
     * @brief Checks whether the container is empty
     *
     * @return true if container is empty otherwise false
     */
    bool empty() const noexcept
    {
        return container_.empty();
    }

    /**
     * @brief Get number of elements in container
     *
     * @return Number of elements.
     */
    size_type size() const noexcept
    {
        return container_.size();
    }

    /**
     * @brief Get maximum possible number of elements
     *
     * @return Maximum possible number of elements
     */
    size_type max_size() const noexcept
    {
        return container_.capacity();
    }

    /**
     * @brief Reserve storage to hold new_cap elements
     *
     * @param new_cap new element capacity
     */
    void reserve(size_type new_cap)
    {
        container_.reserve(new_cap);
    }

    /**
     * @brief Get number of elements that can be held in currently allocated storage
     *
     * @return Number of elements
     */
    size_t capacity() const noexcept
    {
        return container_.capacity();
    }

    /**
     * @brief This function does nothing. Only to keep consistance with STL vector
     */
    void shrink_to_fit()
    {
        container_.shrink_to_fit();
    }

    /**
     * @brief Clears the content
     */
    void clear() noexcept
    {
        container_.clear();
    }

    /**
     * @brief Insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if container size exceeded the maximum size.
     */
    iterator insert(const_iterator pos, T const& value)
    {
        if (container_.size() + 1 > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, value);
    }

    /**
     * @brief Insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if container size exceeded the maximum size.
     */
    iterator insert(const_iterator pos, T&& value)
    {
        if (container_.size() + 1 > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, std::move(value));
    }

    /**
     * @brief Insert count copies of the value before pos
     *
     * @param pos Iterator to insert value before
     * @param count Number of elements
     * @param value The value to insert
     *
     * @return iterator pointing to the first element inserted or pos if count == 0
     *
     * @throws std::bad_alloc if container size + count > SIZE.
     */
    iterator insert(const_iterator pos, size_type count, T const& value)
    {
        if (container_.size() + count > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, count, value);
    }

    /**
     * @brief Inserts elements from range [first, last) before pos
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param pos Iterator to insert value before
     * @param first Start of range to inserted elements
     * @param last End of range to inserted elements
     *
     * @return iterator pointing to the first element inserted or pos if first == last
     *
     * @throws std::bad_alloc if container size + std::distance(first, last) > SIZE.
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        if (container_.size() + static_cast<size_t>(std::distance(first, last)) > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, first, last);
    }

    /**
     * @brief Inserts elements from initializer list before pos
     *
     * @param pos Iterator to insert value before
     * @param ilist The initailizer list
     *
     * @return iterator pointing to the first element inserted or pos if ilist is empty
     *
     * @throws std::bad_alloc if container size + ilist.size() > SIZE.
     */
    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        if (container_.size() + ilist.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.insert(pos, ilist);
    }

    /**
     * @brief Construct element in-place
     *
     * @tparam Args Types of arguments
     * @param pos Iterator to insert value before
     * @param args arguments to forward to the constructor of the element
     *
     * @return iterator pointing to the emplaced element
     */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        if (container_.size() + 1 > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.emplace(pos, std::forward<Args>(args)...);
    }

    /**
     * @brief Remove element at pos
     *
     * @param pos Iterator pointing to the element to remove
     *
     * @return Iterator following the last removed element. if pos refers to last element, then the end() iterator is
     * returned.
     */
    iterator erase(const_iterator pos)
    {
        return container_.erase(pos);
    }

    /**
     * @brief Remove elements in the range [first, last)
     *
     * @param first Start of range to remove elements
     * @param last End of range to remove elements
     *
     * @return Iterator following the last removed element. If last == end(), then the updated end() iterator is
     * returned. If [first, last) is an empty range, then last is returned.
     */
    iterator erase(const_iterator first, const_iterator last)
    {
        return container_.erase(first, last);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @param value The element to add at the end.
     */
    void push_back(T const& value)
    {
        if (container_.size() + 1 > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.push_back(value);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @param value The element to add at the end.
     */
    void push_back(T&& value)
    {
        if (container_.size() + 1 > this->capacity())
        {
            throw std::bad_alloc();
        }
        return container_.push_back(std::move(value));
    }

    /**
     * @brief Construct an element in-place at the end
     *
     * @tparam Args Types of arguments
     * @param args arguments to forward to the constructor of the element
     */
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        if (container_.size() + 1 > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Removes the last element.
     */
    void pop_back()
    {
        container_.pop_back();
    }

    /**
     * @brief Change the number of elements stored
     *
     * @param count Number of elements
     */
    void resize(size_type count)
    {
        if (count > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.resize(count);
    }

    /**
     * @brief Change the number of elements stored
     *
     * @param count Number of elements
     * @param value The value to initialize the new elements
     */
    void resize(size_type count, value_type const& value)
    {
        if (count > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.resize(count, value);
    }

    /**
     * @brief Swaps the contents
     *
     * @param other The other container
     */
    void swap(VectorBase& other) noexcept
    {
        container_.swap(other.container_);
    }

    /**
     * @brief Swaps the contents with VectorBase of different size.
     *
     * @tparam SIZE_ Size of the other VectorBase
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if size() > SIZE_.
     * @throws std::bad_alloc if other.size() > SIZE.
     */
    template <size_t SIZE_>
    void swap(VectorBase<T, SIZE_, Allocator>& other)
    {
        if ((this->size() > SIZE_) || other.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.swap(other.container_);
        if (SIZE_ > this->capacity())
        {
            other.container_.reserve(SIZE_);
        }
    }

    template <size_t ALIGN = 4U, typename T_ = value_type,
              typename std::enable_if<std::is_arithmetic<T_>::value || std::is_enum<T_>::value>::type* = nullptr>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t)) +
               holo::serialization::AlignedSize<ALIGN>(this->size() * sizeof(value_type));
    }

    template <size_t ALIGN = 4U, typename T_ = value_type,
              typename std::enable_if<!(std::is_arithmetic<T_>::value || std::is_enum<T_>::value)>::type* = nullptr>
    size_t GetSerializedSize() const noexcept
    {
        size_t size = holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        for (size_t i = 0U; i < this->size(); ++i)
        {
            size += (*this)[i].template GetSerializedSize<ALIGN>();
        }
        return size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << static_cast<uint32_t>(size()) << holo::serialization::align;
        for (size_t i = 0U; i < this->size(); ++i)
        {
            serializer << (*this)[i];
        }
        serializer << holo::serialization::align;
    }

    template <typename S>
    void Deserialize(S& deserializer)
    {
        uint32_t size = 0U;
        deserializer >> size >> holo::serialization::align;
        this->resize(size);
        for (size_t i = 0U; i < this->size(); ++i)
        {
            deserializer >> (*this)[i];
        }
        deserializer >> holo::serialization::align;
    }

    template <typename T_, size_t SIZE_, typename Allocator_>
    friend class VectorBase;

protected:
    ~VectorBase() = default;

private:
    ContainerType container_;
};

/**
 * @brief Partial specialization for automatic vector type.
 *
 * @tparam T Type of the elements
 * @tparam Allocator An allocator that is used to acquire/release memory and construct/destroy the elements.
 */
template <typename T, typename Allocator>
class VectorBase<T, std::numeric_limits<size_t>::max(), Allocator>
{
public:
    using ContainerType = std::vector<T, Allocator>;  ///< The underlying container type.

    using value_type             = typename ContainerType::value_type;
    using allocator_type         = typename ContainerType::allocator_type;
    using size_type              = typename ContainerType::size_type;
    using difference_type        = typename ContainerType::difference_type;
    using reference              = typename ContainerType::reference;
    using const_reference        = typename ContainerType::const_reference;
    using pointer                = typename ContainerType::pointer;
    using const_pointer          = typename ContainerType::const_pointer;
    using iterator               = typename ContainerType::iterator;
    using const_iterator         = typename ContainerType::const_iterator;
    using reverse_iterator       = typename ContainerType::reverse_iterator;
    using const_reverse_iterator = typename ContainerType::const_reverse_iterator;

    /**
     * @brief Default constructor
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase() : container_()
    {
    }

    /**
     * @brief Constructs an empty container with given allocator.
     *
     * @param alloc The allocator
     *
     * @throws Calls to Allocator::allocate may throw
     */
    explicit VectorBase(Allocator const& alloc) : container_(alloc)
    {
    }

    /**
     * @brief Constructs the container with count default-inserted instance of T.
     *
     * @param count Number of elements.
     *
     * @throws std::bad_alloc if count > SIZE.
     * @throws Calls to Allocator::allocate may throw
     */
    explicit VectorBase(size_type count) : container_(count)
    {
    }

    /**
     * @brief Constructs the container with count copies of elements with value
     *
     * @param count Number of elements
     * @param value value to initialize elements of the container
     * @param alloc allocator to use for all memory allocations of this container.
     *
     * @throws std::bad_alloc if count > SIZE
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(size_type count, T const& value, Allocator const& alloc = Allocator()) : container_(count, value, alloc)
    {
    }

    /**
     * @brief Constructs the container with the contents of the range [first, last)
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param first Start of range to copy elements
     * @param last End of range to copy elements
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws std::bad_alloc if std::distance(first, last) > SIZE
     * @throws Calls to Allocator::allocate may throw
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    VectorBase(InputIt first, InputIt last, Allocator const& alloc = Allocator()) : container_(first, last, alloc)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other The other container.
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase const& other) : container_(other.container_)
    {
    }

    /**
     * @brief Copy constructor
     *
     * @param other The other container
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase const& other, Allocator const& alloc) : container_(other.container_, alloc)
    {
    }

    /**
     * @brief Move constructor
     *
     * @param other The other container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase&& other) : container_(std::move(other.container_))
    {
    }

    /**
     * @brief Allocator-extended move constructor
     *
     * @param other The other container
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws Calls to Allocator::allocate may throw
     */
    VectorBase(VectorBase&& other, Allocator const& alloc) : container_(std::move(other.container_), alloc)
    {
    }

    /**
     * @brief Constructs with the contents of the initializer list
     *
     * @param init The initializer list
     * @param alloc allocator to use for all memory allocations of this container
     *
     * @throws std::bad_alloc if initializer size > SIZE
     */
    VectorBase(std::initializer_list<T> init, Allocator const& alloc = Allocator()) : container_(init, alloc)
    {
    }

    /**
     * @brief Construct with other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase(VectorBase<T, SIZE_, Allocator_> const& other) : container_(other.container_)
    {
    }

    /**
     * @brief Construct with other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase(VectorBase<T, SIZE_, Allocator_>&& other) : container_(std::move(other.container_))
    {
    }

    /**
     * @brief Copy assign operator
     *
     * @param other The other container
     *
     * @return Reference to this container
     */
    VectorBase& operator=(VectorBase const& other) = default;

    /**
     * @brief Move assign operator
     *
     * @param other The other container
     *
     * @return Reference to this container
     */
    VectorBase& operator=(VectorBase&& other) = default;

    /**
     * @brief Replace the contents with those identified by initializer list
     *
     * @param ilist initializer list
     *
     * @return Reference to this container
     *
     * @throws std::bad_alloc
     */
    VectorBase& operator=(std::initializer_list<T> ilist)
    {
        container_ = ilist;
        return *this;
    }

    /**
     * @brief Assign from other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase& operator=(VectorBase<T, SIZE_, Allocator_> const& other)
    {
        container_ = other.container_;
        return *this;
    }

    /**
     * @brief Assign from other Vector of different SIZE
     *
     * @tparam SIZE_ Size of the other VectorBase object.
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if other.size() > SIZE
     */
    template <size_t SIZE_, typename Allocator_>
    VectorBase& operator=(VectorBase<T, SIZE_, Allocator_>&& other)
    {
        container_ = std::move(other.container_);
        return *this;
    }

    /**
     * @brief Replace the contents with count copies of value
     *
     * @param count Number of elements
     * @param value Element value
     *
     * @throws std::bad_alloc if count > SIZE
     */
    void assign(size_type count, T const& value)
    {
        container_.assign(count, value);
    }

    /**
     * @brief Replace the contents with copies of those in the range [first, last)
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param first Start of range to copy elements
     * @param last End of range to copy elements
     *
     * @throws std::bad_alloc if std::distance(first, last) > SIZE
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    void assign(InputIt first, InputIt last)
    {
        container_.assign(first, last);
    }

    /**
     * @brief Replace the contents with the those identified by initializer list
     *
     * @param ilist The initailizer list
     */
    void assign(std::initializer_list<T> ilist)
    {
        container_.assign(ilist);
    }

    /**
     * @brief Return the associated allocator
     *
     * @return The associated allocator
     */
    allocator_type get_allocator() const
    {
        return container_.get_allocator();
    }

    /**
     * @brief Access specified element with bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     *
     * @throws std::out_of_range if pos > size()
     */
    reference at(size_type pos)
    {
        return container_.at(pos);
    }

    /**
     * @brief Access specified element with bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     *
     * @throws std::out_of_range if pos > size()
     */
    const_reference at(size_type pos) const
    {
        return container_.at(pos);
    }

    /**
     * @brief Access specified element without bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     */
    reference operator[](size_type pos)
    {
        return container_[pos];
    }

    /**
     * @brief Access specified element without bounds check.
     *
     * @param pos Element index
     *
     * @return reference to the element
     */
    const_reference operator[](size_type pos) const
    {
        return container_[pos];
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    reference front()
    {
        return container_.front();
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    const_reference front() const
    {
        return container_.front();
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    reference back()
    {
        return container_.back();
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    const_reference back() const
    {
        return container_.back();
    }

    /**
     * @brief Direct access to the underlying array.
     *
     * @return Pointer to underlying array
     */
    T* data() noexcept
    {
        return container_.data();
    }

    /**
     * @brief Direct access to the underlying array.
     *
     * @return Pointer to underlying array
     */
    T const* data() const noexcept
    {
        return container_.data();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    iterator begin()
    {
        return container_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator begin() const
    {
        return container_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator cbegin() const
    {
        return container_.cbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    reverse_iterator rbegin()
    {
        return container_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator rbegin() const
    {
        return container_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator crbegin() const
    {
        return container_.crbegin();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    iterator end()
    {
        return container_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator end() const
    {
        return container_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator cend() const
    {
        return container_.cend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    reverse_iterator rend()
    {
        return container_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator rend() const
    {
        return container_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator crend() const
    {
        return container_.crend();
    }

    /**
     * @brief Checks whether the container is empty
     *
     * @return true if container is empty otherwise false
     */
    bool empty() const noexcept
    {
        return container_.empty();
    }

    /**
     * @brief Get number of elements in container
     *
     * @return Number of elements.
     */
    size_type size() const noexcept
    {
        return container_.size();
    }

    /**
     * @brief Get maximum possible number of elements
     *
     * @return Maximum possible number of elements
     */
    size_type max_size() const noexcept
    {
        return container_.max_size();
    }

    /**
     * @brief Reserve storage to hold new_cap elements
     *
     * @param new_cap new element capacity
     */
    void reserve(size_type new_cap)
    {
        container_.reserve(new_cap);
    }

    /**
     * @brief Get number of elements that can be held in currently allocated storage
     *
     * @return Number of elements
     */
    size_t capacity() const noexcept
    {
        return container_.capacity();
    }

    /**
     * @brief This function does nothing. Only to keep consistance with STL vector
     */
    void shrink_to_fit()
    {
        container_.shrink_to_fit();
    }

    /**
     * @brief Clears the content
     */
    void clear() noexcept
    {
        container_.clear();
    }

    /**
     * @brief Insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if container size exceeded the maximum size.
     */
    iterator insert(const_iterator pos, T const& value)
    {
        return container_.insert(pos, value);
    }

    /**
     * @brief Insert value before pos
     *
     * @param pos Iterator to insert value before
     * @param value The value to insert
     *
     * @return iterator to inserted element
     *
     * @throws std::bad_alloc if container size exceeded the maximum size.
     */
    iterator insert(const_iterator pos, T&& value)
    {
        return container_.insert(pos, std::move(value));
    }

    /**
     * @brief Insert count copies of the value before pos
     *
     * @param pos Iterator to insert value before
     * @param count Number of elements
     * @param value The value to insert
     *
     * @return iterator pointing to the first element inserted or pos if count == 0
     *
     * @throws std::bad_alloc if container size + count > SIZE.
     */
    iterator insert(const_iterator pos, size_type count, T const& value)
    {
        return container_.insert(pos, count, value);
    }

    /**
     * @brief Inserts elements from range [first, last) before pos
     *
     * @tparam InputIt Input iterator type. Must satisfy c++ named requirements: LegacyInputIterator
     * @param pos Iterator to insert value before
     * @param first Start of range to inserted elements
     * @param last End of range to inserted elements
     *
     * @return iterator pointing to the first element inserted or pos if first == last
     *
     * @throws std::bad_alloc if container size + std::distance(first, last) > SIZE.
     */
    template <typename InputIt, typename = typename std::enable_if<IsInputIterator<InputIt>::value>::type>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        return container_.insert(pos, first, last);
    }

    /**
     * @brief Inserts elements from initializer list before pos
     *
     * @param pos Iterator to insert value before
     * @param ilist The initailizer list
     *
     * @return iterator pointing to the first element inserted or pos if ilist is empty
     *
     * @throws std::bad_alloc if container size + ilist.size() > SIZE.
     */
    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        return container_.insert(pos, ilist);
    }

    /**
     * @brief Construct element in-place
     *
     * @tparam Args Types of arguments
     * @param pos Iterator to insert value before
     * @param args arguments to forward to the constructor of the element
     *
     * @return iterator pointing to the emplaced element
     */
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        return container_.emplace(pos, std::forward<Args>(args)...);
    }

    /**
     * @brief Remove element at pos
     *
     * @param pos Iterator pointing to the element to remove
     *
     * @return Iterator following the last removed element. if pos refers to last element, then the end() iterator is
     * returned.
     */
    iterator erase(const_iterator pos)
    {
        return container_.erase(pos);
    }

    /**
     * @brief Remove elements in the range [first, last)
     *
     * @param first Start of range to remove elements
     * @param last End of range to remove elements
     *
     * @return Iterator following the last removed element. If last == end(), then the updated end() iterator is
     * returned. If [first, last) is an empty range, then last is returned.
     */
    iterator erase(const_iterator first, const_iterator last)
    {
        return container_.erase(first, last);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @param value The element to add at the end.
     */
    void push_back(T const& value)
    {
        return container_.push_back(value);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @param value The element to add at the end.
     */
    void push_back(T&& value)
    {
        return container_.push_back(std::move(value));
    }

    /**
     * @brief Construct an element in-place at the end
     *
     * @tparam Args Types of arguments
     * @param args arguments to forward to the constructor of the element
     */
    template <typename... Args>
    void emplace_back(Args&&... args)
    {
        container_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Removes the last element.
     */
    void pop_back()
    {
        container_.pop_back();
    }

    /**
     * @brief Change the number of elements stored
     *
     * @param count Number of elements
     */
    void resize(size_type count)
    {
        container_.resize(count);
    }

    /**
     * @brief Change the number of elements stored
     *
     * @param count Number of elements
     * @param value The value to initialize the new elements
     */
    void resize(size_type count, value_type const& value)
    {
        container_.resize(count, value);
    }

    /**
     * @brief Swaps the contents
     *
     * @param other The other container
     */
    void swap(VectorBase& other) noexcept
    {
        container_.swap(other.container_);
    }

    /**
     * @brief Swaps the contents with VectorBase of different size.
     *
     * @tparam SIZE_ Size of the other VectorBase
     * @param other The other VectorBase object.
     *
     * @throws std::bad_alloc if size() > SIZE_.
     * @throws std::bad_alloc if other.size() > SIZE.
     */
    template <size_t SIZE_>
    void swap(VectorBase<T, SIZE_, Allocator>& other)
    {
        if ((this->size() > SIZE_) || other.size() > this->capacity())
        {
            throw std::bad_alloc();
        }
        container_.swap(other.container_);
        if (SIZE_ > this->capacity())
        {
            other.container_.reserve(SIZE_);
        }
    }

    template <size_t ALIGN = 4U, typename T_ = value_type,
              typename std::enable_if<std::is_arithmetic<T_>::value || std::is_enum<T_>::value>::type* = nullptr>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t)) +
               holo::serialization::AlignedSize(this->size() * sizeof(value_type));
    }

    template <size_t ALIGN = 4U, typename T_ = value_type,
              typename std::enable_if<!(std::is_arithmetic<T_>::value || std::is_enum<T_>::value)>::type* = nullptr>
    size_t GetSerializedSize() const noexcept
    {
        size_t size = holo::serialization::AlignedSize<ALIGN>(sizeof(uint32_t));
        for (size_t i = 0U; i < this->size(); ++i)
        {
            size += (*this)[i].template GetSerializedSize<ALIGN>();
        }
        return size;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << static_cast<uint32_t>(size()) << holo::serialization::align;
        for (size_t i = 0U; i < this->size(); ++i)
        {
            serializer << (*this)[i];
        }
        serializer << holo::serialization::align;
    }

    template <typename S>
    void Deserialize(S& deserializer)
    {
        uint32_t size = 0U;
        deserializer >> size >> holo::serialization::align;
        this->resize(size);
        for (size_t i = 0U; i < this->size(); ++i)
        {
            deserializer >> (*this)[i];
        }
        deserializer >> holo::serialization::align;
    }

    template <typename T_, size_t SIZE_, typename Allocator_>
    friend class VectorBase;

protected:
    ~VectorBase() = default;

private:
    ContainerType container_;
};

/**
 * @brief Checks if the contents of lhs and rhs are equal.
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of lhs
 * @tparam Alloc Allocator type of lhs
 * @tparam SIZE Maximum size of rhs
 * @tparam Alloc Allocator type of rhs
 * @param lhs Left hand side
 * @param rhs Right hand side
 *
 * @return true if lhs and rhs are equal otherwise false.
 */
template <typename T, size_t SIZE, typename Alloc, size_t SIZE_, typename Alloc_>
inline bool operator==(VectorBase<T, SIZE, Alloc> const& lhs, VectorBase<T, SIZE_, Alloc_> const& rhs)
{
    return (lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

/**
 * @brief Checks if the contents of lhs and rhs are not equal.
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of lhs
 * @tparam Alloc Allocator type of lhs
 * @tparam SIZE Maximum size of rhs
 * @tparam Alloc Allocator type of rhs
 * @param lhs Left hand side
 * @param rhs Right hand side
 *
 * @return true if lhs and rhs are not equal otherwise false.
 */
template <typename T, size_t SIZE, typename Alloc, size_t SIZE_, typename Alloc_>
inline bool operator!=(VectorBase<T, SIZE, Alloc> const& lhs, VectorBase<T, SIZE_, Alloc_> const& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Compares the contents of lhs and rhs lexicographically
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of lhs
 * @tparam Alloc Allocator type of lhs
 * @tparam SIZE Maximum size of rhs
 * @tparam Alloc Allocator type of rhs
 * @param lhs Left hand side
 * @param rhs Right hand side
 *
 * @return true if lhs < rhs otherwise false
 */
template <typename T, size_t SIZE, typename Alloc, size_t SIZE_, typename Alloc_>
inline bool operator<(VectorBase<T, SIZE, Alloc> const& lhs, VectorBase<T, SIZE_, Alloc_> const& rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * @brief Compares the contents of lhs and rhs lexicographically
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of lhs
 * @tparam Alloc Allocator type of lhs
 * @tparam SIZE Maximum size of rhs
 * @tparam Alloc Allocator type of rhs
 * @param lhs Left hand side
 * @param rhs Right hand side
 *
 * @return true if lhs > rhs otherwise false
 */
template <typename T, size_t SIZE, typename Alloc, size_t SIZE_, typename Alloc_>
inline bool operator>(VectorBase<T, SIZE, Alloc> const& lhs, VectorBase<T, SIZE_, Alloc_> const& rhs)
{
    return rhs < lhs;
}

/**
 * @brief Compares the contents of lhs and rhs lexicographically
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of lhs
 * @tparam Alloc Allocator type of lhs
 * @tparam SIZE Maximum size of rhs
 * @tparam Alloc Allocator type of rhs
 * @param lhs Left hand side
 * @param rhs Right hand side
 *
 * @return true if lhs <= rhs otherwise false
 */
template <typename T, size_t SIZE, typename Alloc, size_t SIZE_, typename Alloc_>
inline bool operator<=(VectorBase<T, SIZE, Alloc> const& lhs, VectorBase<T, SIZE_, Alloc_> const& rhs)
{
    return !(rhs < lhs);
}

/**
 * @brief Compares the contents of lhs and rhs lexicographically
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of lhs
 * @tparam Alloc Allocator type of lhs
 * @tparam SIZE Maximum size of rhs
 * @tparam Alloc Allocator type of rhs
 * @param lhs Left hand side
 * @param rhs Right hand side
 *
 * @return true if lhs >= rhs otherwise false
 */
template <typename T, size_t SIZE, typename Alloc, size_t SIZE_, typename Alloc_>
inline bool operator>=(VectorBase<T, SIZE, Alloc> const& lhs, VectorBase<T, SIZE_, Alloc_> const& rhs)
{
    return !(lhs < rhs);
}

template <typename T, size_t SIZE, typename Alloc>
class Vector : public VectorBase<T, SIZE, Alloc>
{
public:
    using Base = VectorBase<T, SIZE, Alloc>;

    static size_t const SIZE_VALUE = SIZE;

    using value_type             = typename Base::value_type;
    using allocator_type         = typename Base::allocator_type;
    using size_type              = typename Base::size_type;
    using difference_type        = typename Base::difference_type;
    using reference              = typename Base::reference;
    using const_reference        = typename Base::const_reference;
    using pointer                = typename Base::pointer;
    using const_pointer          = typename Base::const_pointer;
    using iterator               = typename Base::iterator;
    using const_iterator         = typename Base::const_iterator;
    using reverse_iterator       = typename Base::reverse_iterator;
    using const_reverse_iterator = typename Base::const_reverse_iterator;

    using Base::Base;

    Vector& operator=(std::initializer_list<T> ilist)
    {
        Base::operator=(ilist);
        return *this;
    }
};

}  // namespace details
}  // namespace container
}  // namespace holo

namespace std
{
/**
 * @brief specializes the std::swap algorithm
 *
 * @tparam T Type of elements
 * @tparam SIZE Maximum size of container
 * @tparam Alloc Allocator type
 * @param lhs Left hand side
 * @param rhs Right hand side
 */
template <typename T, size_t SIZE, typename Alloc>
inline void swap(holo::container::details::VectorBase<T, SIZE, Alloc> const& lhs,
                 holo::container::details::VectorBase<T, SIZE, Alloc> const& rhs)
{
    lhs.swap(rhs);
}

}  // namespace std

#endif
