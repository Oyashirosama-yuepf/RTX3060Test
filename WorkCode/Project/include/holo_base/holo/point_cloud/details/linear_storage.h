/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file linear_storage.h
 * @brief This header file defines linear storage container type.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2020-11-03
 */

#ifndef HOLO_POINT_CLOUD_DETAILS_LINEAR_STORAGE_H_
#define HOLO_POINT_CLOUD_DETAILS_LINEAR_STORAGE_H_

#include <iterator>
#include <vector>

#include <holo/container/vector.h>
#include <holo/core/types.h>

namespace holo
{
namespace point_cloud
{
namespace details
{
/**
 * @brief Base class for linear storage
 *
 * @tparam T Stored value type
 * @tparam SIZE Size of storage. 0 means dynamic size.
 * @tparam STRIDE Stride of each element
 */
template <typename T, size_t SIZE, size_t STRIDE>
class LinearStorageBase
{
private:
    template <bool_t CONST = false>
    class Iterator;

    struct ElementType;
    using StorageType = holo::container::Vector<ElementType, SIZE>;

public:
    using value_type             = T;
    using allocator_type         = typename StorageType::allocator_type;
    using size_type              = typename StorageType::size_type;
    using difference_type        = typename StorageType::difference_type;
    using reference              = value_type&;
    using const_reference        = value_type const&;
    using pointer                = value_type*;
    using const_pointer          = value_type const*;
    using iterator               = Iterator<false>;
    using const_iterator         = Iterator<true>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /**
     * @brief Default constructor
     */
    LinearStorageBase() = default;

    /**
     * @brief Construct with element number.
     *
     * @detail Constructs a container with n elements. Each element with default value.
     *
     * @param n Number of elements.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe Strong.
     */
    explicit LinearStorageBase(size_type n) : storage_(n)
    {
    }

    /**
     * @brief Construct with element number and value.
     *
     * @detail Constructs a container with n elements. Each element is a copy of value.
     *
     * @param n Number of elements.
     * @param value Element value.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe Strong.
     */
    LinearStorageBase(size_type n, value_type const& value) : storage_(n, value)
    {
    }

    /**
     * @brief Construct with input iterator range.
     *
     * @detail Constructs a container with as many elements as the range [first, last), with each element
     * emplace-constructed from its corresponding element in that range, in the same order.
     *
     * @tparam InputIt Input iterator type.
     * @param first Iterator pointing to the first element.
     * @param last Iterator pointing to the last element.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe Strong
     */
    template <typename InputIt>
    LinearStorageBase(InputIt first, InputIt last) : storage_(first, last)
    {
    }

    /**
     * @brief Default copy constructor
     */
    LinearStorageBase(LinearStorageBase const&) = default;

    /**
     * @brief Default move constructor
     */
    LinearStorageBase(LinearStorageBase&&) = default;

    /**
     * @brief Default copy assign operator
     */
    LinearStorageBase& operator=(LinearStorageBase const&) = default;

    /**
     * @brief Default move assign operator
     */
    LinearStorageBase& operator=(LinearStorageBase&&) = default;

    /**
     * @brief Assign operator with initializer list
     *
     * @param ilist Initializer list
     *
     * @return Reference to this container
     */
    LinearStorageBase& operator=(std::initializer_list<value_type> ilist)
    {
        storage_.assign(ilist.begin(), ilist.end());
    }

    /**
     * @brief Construct with initializer list
     *
     * @param il Initializer list of value type.
     */
    LinearStorageBase(std::initializer_list<value_type> il) : storage_(il.begin(), il.end())
    {
    }

    /**
     * @brief Construct with other LinearStorageBase type of different value type/size/or stride
     *
     * @tparam T_ Value type of the other storage
     * @tparam SIZE_ Size value of the other storage
     * @tparam STRIDE Stride value of the other storage
     * @param other The other storage object
     */
    template <typename T_, size_t SIZE_, size_t STRIDE_,
              typename std::enable_if<!(std::is_same<T, T_>::value && (STRIDE == STRIDE_))>::type* = nullptr>
    LinearStorageBase(LinearStorageBase<T_, SIZE_, STRIDE_> const& other) : storage_(other.begin(), other.end())
    {
    }

    /**
     * @brief Assign container content.
     *
     * @detail The new contents are elements constructed from each of the elements in the range between first and last,
     * in the same order.
     *
     * @tparam InputIt Input iterator type.
     * @param first Iterator pointing to the first element.
     * @param last Iterator pointing to the last element.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe strong
     */
    template <typename InputIt>
    void assign(InputIt first, InputIt last)
    {
        storage_.assign(first, last);
    }

    /**
     * @brief Assign container content.
     *
     * @detail The new contents are n elements, each initialized to a copy of value.
     *
     * @param n Number of elements.
     * @param value Value of each element.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe strong
     */
    void assign(size_type n, const value_type& value)
    {
        storage_.assign(n, value);
    }

    /**
     * @brief Assign container content.
     *
     * @detail The new contents are copies of the values passed as initializer list, in the same order.
     *
     * @param ilist The initializer list.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe strong
     */
    void assign(std::initializer_list<value_type> ilist)
    {
        storage_.assign(ilist.begin(), ilist.end());
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
        return storage_.at(pos).value;
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
        return storage_.at(pos).value;
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
        return storage_[pos].value;
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
        return storage_[pos].value;
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    reference front()
    {
        return storage_.front().value;
    }

    /**
     * @brief Access the first element
     *
     * @return Reference to first element
     */
    const_reference front() const
    {
        return storage_.front().value;
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    reference back()
    {
        return storage_.back().value;
    }

    /**
     * @brief Access the last element
     *
     * @return Reference to last element
     */
    const_reference back() const
    {
        return storage_.back().value;
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    iterator begin()
    {
        return storage_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator begin() const
    {
        return storage_.begin();
    }

    /**
     * @brief Get iterator to the beginning
     *
     * @return Iterator to beginning
     */
    const_iterator cbegin() const
    {
        return storage_.cbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    reverse_iterator rbegin()
    {
        return storage_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator rbegin() const
    {
        return storage_.rbegin();
    }

    /**
     * @brief Get reverse iterator to the beginning
     *
     * @return Reverse iterator to beginning
     */
    const_reverse_iterator crbegin() const
    {
        return storage_.crbegin();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    iterator end()
    {
        return storage_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator end() const
    {
        return storage_.end();
    }

    /**
     * @brief Get iterator to the end
     *
     * @return Iterator to end
     */
    const_iterator cend() const
    {
        return storage_.cend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    reverse_iterator rend()
    {
        return storage_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator rend() const
    {
        return storage_.rend();
    }

    /**
     * @brief Get reverse iterator to the end
     *
     * @return Reverse iterator to end
     */
    const_reverse_iterator crend() const
    {
        return storage_.crend();
    }

    /**
     * @brief Checks whether the storage is empty
     *
     * @return true if storage is empty otherwise false
     */
    bool empty() const noexcept
    {
        return storage_.empty();
    }

    /**
     * @brief Get number of elements in storage
     *
     * @return Number of elements.
     */
    size_type size() const noexcept
    {
        return storage_.size();
    }

    /**
     * @brief Get maximum possible number of elements
     *
     * @return Maximum possible number of elements
     */
    size_type max_size() const noexcept
    {
        return storage_.max_size();
    }

    /**
     * @brief Change size
     *
     * @detail Resize the container so that it contains n elements.
     *
     * @param n New container size in number of elements.
     *
     * @throws std::bad_alloc exception.
     *
     * @exceptsafe strong
     */
    void resize(size_type n)
    {
        storage_.resize(n);
    }

    /**
     * @brief Change size
     *
     * @detail Resize the container so that it contains n elements. If current size is less than n, additional copies of
     * value are appended
     *
     * @param n New container size in number of elements.
     *
     * @throws std::bad_alloc exception.
     *
     * @exceptsafe strong
     */
    void resize(size_type n, value_type const& value)
    {
        storage_.resize(n, value);
    }

    /**
     * @brief Reserve storage to hold new_cap elements
     *
     * @param new_cap new element capacity
     */
    void reserve(size_type new_cap)
    {
        storage_.reserve(new_cap);
    }

    /**
     * @brief Get number of elements that can be held in currently allocated storage
     *
     * @return Number of elements
     */
    size_t capacity() const noexcept
    {
        return storage_.capacity();
    }

    /**
     * @brief This function does nothing. Only to keep consistance with STL vector
     */
    void shrink_to_fit()
    {
        storage_.shrink_to_fit();
    }

    /**
     * @brief Clears the content
     */
    void clear() noexcept
    {
        storage_.clear();
    }

    /**
     * @brief Inserts value before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param value Element value to insert.
     *
     * @return Iterator pointing to the inserted value.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe strong
     */
    iterator insert(const_iterator pos, value_type const& value)
    {
        return iterator(storage_.insert(pos.iter_, value));
    }

    /**
     * @brief Inserts value before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param value Element value to insert.
     *
     * @return Iterator pointing to the inserted value.
     *
     * @throws std::bad_alloc
     *
     * @exceptsafe strong
     */
    iterator insert(const_iterator pos, value_type&& value)
    {
        return iterator(storage_.insert(pos.iter_, std::move(value)));
    }

    /**
     * @brief Inserts count copies of the value before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param count Number of elements to insert.
     * @param value Element value to insert.
     *
     * @return Iterator pointing to the first element inserted, or pos if count == 0.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe String
     */
    iterator insert(const_iterator pos, size_type count, value_type const& value)
    {
        return iterator(storage_.insert(pos.iter_, count, value));
    }

    /**
     * @brief Inserts elements from range [first, last) before pos.
     *
     * @tparam InputIt Input iterator type. InputIt must qualifies as C++ named requiredments "LegacyInputIterator" to
     * avoid ambiguity with insert(const_iterator, size_type, const value_type&).
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param first Iterator pointing to the beginning of elements to insert.
     * @param last Iterator pointing to the end of elements to insert.
     *
     * @return Iterator pointing to the first element inserted, or pos if first == last.
     *
     * @pre first and last point to same container and last >= first.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe strong
     * @note The behavior is undefined if first and last are iterators into *this.
     */
    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        return iterator(storage_.insert(pos.iter_, first, last));
    }

    /**
     * @brief Inserts elements from initializer list before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param ilist
     *
     * @return Iterator pointing to the first element inserted, or pos if ilist is empty.
     *
     * @throws std::bad_alloc exception
     *
     * @exceptsafe strong
     */
    iterator insert(const_iterator pos, std::initializer_list<value_type> ilist)
    {
        return iterator(storage_.insert(pos.iter_, ilist.begin(), ilist.end()));
    }

    /**
     * @brief Constructs element in-place
     *
     * @tparam Args Constructor argument types.
     * @param pos Iterator before which the new element will be constructed.
     * @param args Arguments to forward to the constructor of the element.
     *
     * @return Iterator pointing to the emplaced element.
     */
    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args)
    {
        return iterator(storage_.emplace(pos.iter_, std::forward<Args>(args)...));
    }

    /**
     * @brief Removes the element at pos.
     *
     * @param pos Iterator to the element to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase(const_iterator pos)
    {
        return iterator(storage_.erase(pos.iter_));
    }

    /**
     * @brief Removes the elements in the range [first, last).
     *
     * @param first Iterator pointing to the beginning of elements to remove.
     * @param last Iterator pointing to the end of elements to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase(const_iterator first, const_iterator last)
    {
        return iterator(storage_.erase(first.iter_, last.iter_));
    }

    /**
     * @brief Adds an element to the end.
     *
     * @detail Appends the given element value to the end of the container.
     * The new element is initialized as a copy of value.
     *
     * @param value The value of the element to append.
     */
    void push_back(value_type const& value)
    {
        storage_.push_back(value);
    }

    /**
     * @brief Adds an element to the end.
     *
     * @detail Appends the given element value to the end of the container.
     * Value is moved into the new element.
     *
     * @param value The value of the element to append.
     */
    void push_back(value_type&& value)
    {
        storage_.push_back(std::move(value));
    }

    /**
     * @brief Constructs element in-place at the end.
     *
     * @tparam Args Constructor argument types.
     * @param args Arguments to forward to the constructor of the element.
     */
    template <class... Args>
    void emplace_back(Args&&... args)
    {
        storage_.emplace_back(std::forward<Args>(args)...);
    }

    /**
     * @brief Removes the last element.
     */
    void pop_back()
    {
        storage_.pop_back();
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return storage_.template GetSerializedSize<ALIGN, ElementType>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << storage_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> storage_;
    }

    template <typename T_, size_t SIZE_, size_t STRIDE_>
    friend class LinearStorageBase;

protected:
    /**
     * @brief Default destructor
     */
    ~LinearStorageBase() = default;

private:
    template <bool_t CONST>
    class Iterator
    {
    public:
        using IteratorType      = typename std::conditional<CONST, typename StorageType::const_iterator,
                                                       typename StorageType::iterator>::type;
        using difference_type   = typename LinearStorageBase::difference_type;
        using value_type        = typename LinearStorageBase::value_type;
        using reference [[deprecated]]        = typename std::conditional<CONST, typename LinearStorageBase::const_reference,
                                                    typename LinearStorageBase::reference>::type;
        using pointer [[deprecated]]          = typename std::conditional<CONST, typename LinearStorageBase::const_pointer,
                                                  typename LinearStorageBase::pointer>::type;
        using reference_type         = typename std::conditional<CONST, typename LinearStorageBase::const_reference,
                                                    typename LinearStorageBase::reference>::type;
        using pointer_type           = typename std::conditional<CONST, typename LinearStorageBase::const_pointer,
                                                  typename LinearStorageBase::pointer>::type;
        using iterator_category = std::random_access_iterator_tag;

        Iterator() noexcept : iter_{}
        {
        }

        template <bool_t CONST_ = CONST, typename = typename std::enable_if<CONST_, void>::type>
        Iterator(Iterator<false> const& other) noexcept : iter_(other.iter_)
        {
        }

        Iterator(IteratorType const& iter) noexcept : iter_(iter)
        {
        }

        template <bool_t InputConst>
        bool_t operator==(Iterator<InputConst> const& rhs) const
        {
            return iter_ == rhs.iter_;
        }

        template <bool_t InputConst>
        bool_t operator!=(Iterator<InputConst> const& rhs) const
        {
            return iter_ != rhs.iter_;
        }

        template <bool_t InputConst>
        bool_t operator<(Iterator<InputConst> const& rhs) const
        {
            return iter_ < rhs.iter_;
        }

        template <bool_t InputConst>
        bool_t operator>(Iterator<InputConst> const& rhs) const
        {
            return iter_ > rhs.iter_;
        }

        template <bool_t InputConst>
        bool_t operator<=(Iterator<InputConst> const& rhs) const
        {
            return iter_ <= rhs.iter_;
        }

        template <bool_t InputConst>
        bool_t operator>=(Iterator<InputConst> const& rhs) const
        {
            return iter_ > rhs.iter_;
        }

        Iterator& operator++()
        {
            ++iter_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp(*this);
            ++iter_;
            return tmp;
        }

        Iterator& operator--()
        {
            --iter_;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator tmp(*this);
            --iter_;
            return tmp;
        }

        Iterator& operator+=(difference_type rhs)
        {
            iter_ += rhs;
            return *this;
        }

        Iterator operator+(difference_type rhs) const
        {
            Iterator tmp(*this);
            tmp += rhs;
            return tmp;
        }

        friend Iterator operator+(difference_type lhs, const Iterator& rhs)
        {
            return rhs + lhs;
        }

        Iterator& operator-=(difference_type rhs)
        {
            iter_ -= rhs;
            return *this;
        }

        Iterator operator-(difference_type rhs) const
        {
            Iterator tmp(*this);
            tmp -= rhs;
            return tmp;
        }

        difference_type operator-(Iterator rhs) const
        {
            return iter_ - rhs.iter_;
        }

        reference_type operator*() const
        {
            return (*iter_).value;
        }

        pointer_type operator->() const
        {
            return &((*iter_).value);
        }

        reference_type operator[](difference_type idx) const
        {
            return iter_[idx].value;
        }

        friend class Iterator<!CONST>;
        friend class LinearStorageBase;

    private:
        IteratorType iter_;
    };

    /**
     * @brief Stored element type of underlying storage
     */
    struct ElementType
    {
        value_type value;
        uint8_t    padding[STRIDE - (sizeof(value_type) % STRIDE)];

        template <typename... Args>
        ElementType(Args&&... args) : value(std::forward<Args>(args)...), padding{}
        {
        }

        ElementType()                   = default;
        ElementType(ElementType const&) = default;
        /// @todo Will cause compile error without declare non-const type copy constructor. Need to figure out why!
        ElementType(ElementType&)  = default;
        ElementType(ElementType&&) = default;
        ElementType& operator=(ElementType const&) = default;
        ElementType& operator=(ElementType&&) = default;
        ~ElementType()                        = default;

        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return value.template GetSerializedSize<ALIGN>();
        }

        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << value;
        }

        template <typename D>
        void Deserialize(D& deserializer)
        {
            deserializer >> value;
        }
    };

    StorageType storage_;  ///< Underlying storage wrapper
};

/**
 * @brief Linear storage class acts like a vector, but each element is aligned with STRIDE value.
 *
 * @tparam T Type of element.
 * @tparam SIZE Maximum size of elements. 0U means dynamic size.
 * @tparam STRIDE Stride of each element.
 */
template <typename T, size_t SIZE, size_t STRIDE>
class LinearStorage : public LinearStorageBase<T, SIZE, STRIDE>
{
public:
    using Base = holo::point_cloud::details::LinearStorageBase<T, SIZE, STRIDE>;
    using Base::Base;

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
};

}  // namespace details
}  // namespace point_cloud
}  // namespace holo

#endif
