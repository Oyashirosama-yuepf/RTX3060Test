/**
 * @file deque.h
 * @brief This header file defines Deque object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-22
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_COMMON_CONTAINER_DEQUE_H_
#define HOLO_COMMON_CONTAINER_DEQUE_H_

#include <assert.h>
#include <cstddef>
#include <iterator>
#include <holo/core/types.h>

namespace holo
{

namespace container
{

namespace details
{

/**
 * @brief Deque container.
 *
 * @detail Deque container acts like std::deque except the capacity is fixed. No dynamic allocation will be 
 * performed if container is full.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 */
template <typename T, std::size_t N>
class Deque
{
public:

    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    template<bool_t CONST = false>
    class Iterator;
    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    
    /**
     * @{
     * Constructor/destructor/assign operator API group
     */

    /**
     * @brief Default constructor.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow.
     */
    Deque() noexcept;

    /**
     * @brief Constructs Deque container.
     *
     * @detail Constructs a container with n elements. Each element with default value.
     *
     * @param n Number of elements.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException "BadAllocException"
     *
     * @note Exception safety: Strong.
     */
    explicit Deque(size_type n);

    /**
     * @brief Constructs Deque container.
     *
     * @detail Constructs a container with n elements. Each element is a copy of value.
     *
     * @param n Number of elements.
     * @param value Element value.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException "BadAllocException"
     *
     * @note Exception safety: Strong.
     */
    Deque(size_type n, const value_type& value);

    /**
     * @brief Constructs Deque container.
     *
     * @detail Constructs a container with as many elements as the range [first, last), with each element 
     * emplace-constructed from its corresponding element in that range, in the same order.
     *
     * @tparam InputIt Input iterator type.
     * @param first Iterator pointing to the first element.
     * @param last Iterator pointing to the last element.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException "BadAllocException"
     *
     * @note Exception safety: Strong
     */
    template< typename InputIt, typename = typename std::enable_if<!std::is_integral<InputIt>::value, void>::type>
    Deque(InputIt first, InputIt last);

    /**
     * @brief Constructs Deque container.
     *
     * @detail Constructs a container with a copy of each of the element in x, inthe same order.
     *
     * @param other Another Deque container with the same type.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException BadAllocException
     *
     * @note Exception safety: Strong
     */
    Deque(const Deque& other);

    /**
     * @brief Constructs Deque container.
     *
     * @detail Constructs a container that acquires the element of other.
     *
     * @param other Another Deque container with the same type.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException "BadAllocException"
     *
     * @note Exception safety: Strong
     */
    Deque(Deque&& other);

    /**
     * @brief Constructs Deque container.
     *
     * @detail Constructs a container with a copy of each of the elements in ilist, in the same order.
     *
     * @param ilist The initailizer list.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException "BadAllocException"
     *
     * @note Exception safety: Strong
     */
    Deque(std::initializer_list<value_type> ilist);

    /**
     * @brief Destructs Deque container.
     *
     * @todo comment throws and exception safety.
     */
    ~Deque();

    /**
     * @brief Assigns values to the container.
     *
     * @detail Copy assignment operator. Replaces the contents with a copy of the contents of other.
     *
     * @param other Another container to use as data source.
     *
     * @return The initialized Deque container.
     *
     * @throws noexcept
     *
     * @note Exception safety: No throw
     */
    Deque& operator= (const Deque& other) noexcept;

    /**
     * @brief Assign content
     *
     * @detail Move assignment operator. Replaces the contents with those of other using move semantics. 
     * other is in a valid but unspecified state afterwards.
     *
     * @param other Another container to use as data source.
     *
     * @return The initialized Deque container.
     *
     * @throws noexcept
     *
     * @note Exception safety: No throw
     */
    Deque& operator= (Deque&& other) noexcept;

    /**
     * @brief Assign content
     *
     * @detail Replaces the contents with those identified by initializer list ilist.
     *
     * @param ilist Initializer list to use as data source.
     *
     * @return The initialized Deque container.
     *
     * @throws BadAllocException @ref holo::exception::BadAllocException "BadAllocException"
     *
     * @note Exception safety: Strong
     */
    Deque& operator= (std::initializer_list<value_type> ilist);

    /**
     * @}
     * End constructor/destructor/assign operator API group
     */

    /**
     * @{
     * Element access API group
     */

    /**
     * @brief Access specified element with bounds checking.
     *
     * @detail Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the container, exception holo::exception::OutOfRangeException will be thrown.
     *
     * @param pos Position of the element to return.
     *
     * @return Reference to requredted element.
     *
     * @throws OutOfRangeException @ref holo::exception::OutOfRangeException "OutOfRangeException"
     *
     * @note Exception safety: Strong
     *
     * @see @ref operator[]
     */
    reference at( size_type pos );

    /**
     * @brief Access specified element with bounds checking.
     *
     * @detail Returns a reference to the element at specified location pos, with bounds checking.
     * If pos is not within the range of the container, exception std::out_of_range will be thrown.
     *
     * @param pos Position of the element to return.
     *
     * @return Reference to requredted element.
     *
     * @throws OutOfRangeException @ref holo::exception::OutOfRangeException "OutOfRangeException"
     *
     * @note Exception safety: Strong
     *
     * @see @ref operator[]
     */
    const_reference at( size_type pos ) const;
    
    /**
     * @brief Access specified element.
     *
     * @detail Returns a reference to the element at specified location pos. No bounds checking is performed.
     *
     * @param pos Position of the element to return.
     *
     * @return Reference to the requested element.
     *
     * @pre pos < container.size()
     *
     * @see @ref at.
     */
    reference operator[]( size_type pos ) noexcept;

    /**
     * @brief Access specified element.
     *
     * @detail Returns a reference to the element at specified location pos. No bounds checking is performed.
     *
     * @param pos Position of the element to return.
     *
     * @return Reference to the requested element.
     *
     * @pre pos < container.size()
     *
     * @see @ref at.
     */
    const_reference operator[]( size_type pos ) const noexcept;

    /**
     * @brief Access the first element.
     *
     * @detail Returns a reference to the first element in the container. Calling front on an empty container will 
     * raise holo::exception::OutOfRangeException.
     *
     * @return Reference to the first element.
     *
     * @throws holo::exception::OutOfRangeException if container is empty.
     *
     * @note Exception safety: strong
     *
     * @see back()
     */
    reference front();

    /**
     * @brief Access the first element.
     *
     * @detail Returns a reference to the first element in the container. Calling front on an empty container will 
     * raise holo::exception::OutOfRangeException.
     *
     * @return Reference to the first element.
     *
     * @throws holo::exception::OutOfRangeException if container is empty.
     *
     * @note Exception safety: strong
     *
     * @see back()
     */
    const_reference front() const;

    /**
     * @brief Access the last element.
     *
     * @detail Returns reference to the last element in the container. Calling back on an empty container will raise
     * holo::exception::OutOfRangeException.
     *
     * @return Reference to the last element.
     *
     * @throws holo::exception::OutOfRangeException if container is empty.
     *
     * @note Exception safety: strong
     *
     * @see front()
     */
    reference back();

    /**
     * @brief Access the last element.
     *
     * @detail Returns reference to the last element in the container. Calling back on an empty container will raise
     * holo::exception::OutOfRangeException.
     *
     * @return Reference to the last element.
     *
     * @throws holo::exception::OutOfRangeException if container is empty.
     *
     * @note Exception safety: strong
     *
     * @see front()
     */
    const_reference back() const;

    /**
     * @}
     * End element access API group
     */

    /**
     * @{
     * Iterators API group
     */
    
    /**
     * @brief Iterator to the beginning.
     *
     * @detail Returns an iterator to the first element of the container. If the container is empty, the returned 
     * iterator will be equal to end().
     *
     * @return Iterator to the first element.
     */
    iterator begin() noexcept;

    /**
     * @brief Iterator to the beginning.
     *
     * @detail Returns an const iterator to the first element of the container. If the container is empty, the returned 
     * iterator will be equal to end().
     *
     * @return Const iterator to the first element.
     */
    const_iterator begin() const noexcept;

    /**
     * @brief Iterator to the beginning.
     *
     * @detail Returns an const iterator to the first element of the container. If the container is empty, the returned 
     * iterator will be equal to end().
     *
     * @return Const iterator to the first element.
     */
    const_iterator cbegin() const noexcept;

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns an iterator to the element following the last element of the container.
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Iterator to the element following the last element.
     */
    iterator end() noexcept;

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns an const iterator to the element following the last element of the container.
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const iterator to the element following the last element.
     */
    const_iterator end() const noexcept;

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns an const iterator to the element following the last element of the container.
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const iterator to the element following the last element.
     */
    const_iterator cend() const noexcept;

    /**
     * @brief Reverse iterator to the beginning.
     *
     * @detail Returns a reverse iterator to the first element of the reversed container. 
     * It corresponds to the last element of the non-reversed container. 
     * If the container is empty, the returned iterator is equal to rend().
     *
     * @return Reverse iterator to the first element.
     */
    reverse_iterator rbegin() noexcept;

    /**
     * @brief Reverse iterator to the beginning.
     *
     * @detail Returns a const reverse iterator to the first element of the reversed container. 
     * It corresponds to the last element of the non-reversed container. If the container is empty, 
     * the returned iterator is equal to rend().
     *
     * @return Const everse iterator to the first element.
     */
    const_reverse_iterator rbegin() const noexcept;

    /**
     * @brief Reverse iterator to the beginning.
     *
     * @detail Returns a const reverse iterator to the first element of the reversed container. 
     * It corresponds to the last element of the non-reversed container. If the container is empty, 
     * the returned iterator is equal to rend().
     *
     * @return Const everse iterator to the first element.
     */
    const_reverse_iterator crbegin() const noexcept;

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns a reverse iterator to the element following the last element of the reversed container. 
     * It corresponds to the element preceding the first element of the non-reversed container. 
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Reverse iterator to the element following the last element.
     */
    reverse_iterator rend() noexcept;

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns a const reverse iterator to the element following the last element of the reversed container. 
     * It corresponds to the element preceding the first element of the non-reversed container. 
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const reverse iterator to the element following the last element.
     */
    const_reverse_iterator rend() const noexcept;

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns a const reverse iterator to the element following the last element of the reversed container. 
     * It corresponds to the element preceding the first element of the non-reversed container. 
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const reverse iterator to the element following the last element.
     */
    const_reverse_iterator crend() const noexcept;

    /**
     * @}
     * End iterators API group
     */

    /**
     * @{
     * Capacity API group
     */
    
    /**
     * @brief Checks whether the container is empty.
     *
     * @return 
     */
    bool_t empty() const noexcept;

    /**
     * @brief Number of elements in the container.
     *
     * @return The number of elements in the container.
     */
    size_type size() const noexcept;

    /**
     * @brief Number of elements the container can hold.
     *
     * @return Capacity of the container.
     */
    size_type max_size() const noexcept;

    /**
     * @brief Change size
     *
     * @detail Resize the container so that it contains n elements. Deque is a fixed size container. if n <= N,
     * Will do nothing. if n > N, will throw exception.
     *
     * @param n New container size in number of elements.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if n > N.
     *
     * @note Exception safety: strong
     */
    void resize(size_type n);

    /**
     * @brief Shrink to fit.
     *
     * @detail Requests the container to reduce its memory usage to fit its size. This function will do nothing.
     */
    void shrink_to_fit() noexcept;

    /**
     * @}
     * End Capacity API group
     */


    /**
     * @{
     * Begin modifiers API group
     */

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
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + (last - first) > N.
     *
     * @note Exception safety: strong
     */
    template <class InputIt, typename = typename std::enable_if<!std::is_integral<InputIt>::value >::type >
    void assign(InputIt first, InputIt last);

    /**
     * @brief Assign container content.
     *
     * @detail The new contents are n elements, each initialized to a copy of value.
     *
     * @param n Number of elements.
     * @param value Value of each element.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + n > N.
     *
     * @note Exception safety: strong
     */
    void assign(size_type n, const value_type& value);

    /**
     * @brief Assign container content.
     *
     * @detail The new contents are copies of the values passed as initializer list, in the same order.
     *
     * @param ilist The initializer list.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + ilist.size() > N.
     *
     * @note Exception safety: strong
     */
    void assign(std::initializer_list<value_type> ilist);

    /**
     * @brief Clears the contents.
     *
     * @detail Erases all elements from the container. After this call, size() returns zero.
     */
    void clear() noexcept;

    /**
     * @brief Inserts value before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param value Element value to insert.
     *
     * @return Iterator pointing to the inserted value.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + 1 > N.
     *
     * @note Exception safety: strong
     */
    iterator insert( const_iterator pos, const value_type& value );

    /**
     * @brief Inserts value before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param value Element value to insert.
     *
     * @return Iterator pointing to the inserted value.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + 1 > N.
     *
     * @note Exception safety: strong
     */
    iterator insert( const_iterator pos, value_type&& value );

    /**
     * @brief Inserts count copies of the value before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param count Number of elements to insert.
     * @param value Element value to insert.
     *
     * @return Iterator pointing to the first element inserted, or pos if count == 0.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + n > N.
     *
     * @note Exception safety: strong
     */
    iterator insert( const_iterator pos, size_type count, const value_type& value );

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
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + (last - first) > N.
     *
     * @note Exception safety: strong
     * @note The behavior is undefined if first and last are iterators into *this.
     */
    template< class InputIt >
    iterator insert( const_iterator pos, InputIt first, InputIt last );

    /**
     * @brief Inserts elements from initializer list before pos.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param ilist
     *
     * @return Iterator pointing to the first element inserted, or pos if ilist is empty.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if size() + ilist.size() > N.
     *
     * @note Exception safety: strong
     */
    iterator insert( const_iterator pos, std::initializer_list<value_type> ilist );

    /**
     * @brief Constructs element in-place
     *
     * @tparam Args Constructor argument types.
     * @param pos Iterator before which the new element will be constructed.
     * @param args Arguments to forward to the constructor of the element.
     *
     * @return Iterator pointing to the emplaced element.
     */
    template< class... Args >
    iterator emplace( const_iterator pos, Args&&... args );

    /**
     * @brief Removes the element at pos.
     *
     * @param pos Iterator to the element to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase( const_iterator pos );

    /**
     * @brief Removes the elements in the range [first, last).
     *
     * @param first Iterator pointing to the beginning of elements to remove.
     * @param last Iterator pointing to the end of elements to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase( const_iterator first, const_iterator last );

    /**
     * @brief Adds an element to the end.
     *
     * @detail Appends the given element value to the end of the container. 
     * The new element is initialized as a copy of value.
     *
     * @param value The value of the element to append.
     */
    void push_back( const value_type& value );

    /**
     * @brief Adds an element to the end.
     *
     * @detail Appends the given element value to the end of the container. 
     * Value is moved into the new element.
     *
     * @param value The value of the element to append.
     */
    void push_back( value_type&& value );

    /**
     * @brief Constructs element in-place at the end.
     *
     * @tparam Args Constructor argument types.
     * @param args Arguments to forward to the constructor of the element.
     */
    template< class... Args >
    void emplace_back( Args&&... args );

    /**
     * @brief Removes the last element.
     * @todo pop_back on an empty container?
     */
    void pop_back();

    /**
     * @brief Inserts an element to the beginning.
     *
     * @param value The value of the element to prepend.
     */
    void push_front( const value_type& value );

    /**
     * @brief Inserts an element to the beginning.
     *
     * @param value The value of the element to prepend.
     */
    void push_front( value_type&& value );

    /**
     * @brief Inserts an element to the beginning.
     *
     * @param value The value of the element to prepend.
     */
    void push_fornt( value_type&& value );

    /**
     * @brief Constructs an element in-place at the beginning.
     *
     * @tparam Args Constructor argument types.
     * @param args Arguments to forward to the constructor of the element.
     */
    template< class... Args >
    void emplace_front( Args&&... args );

    /**
     * @brief Removes the first element.
     */
    void pop_front();

    /**
     * @brief Swap the contents.
     *
     * @param other Container to exchange the contents with.
     */
    void swap( Deque& other );

    /**
     * @}
     * End modifiers API group
     */
    
private:
    value_type* data_;
    uint8_t buffer_[sizeof(value_type) * N];
    size_type start_;
    size_type size_;
};

template<typename T, size_t N>
template<bool_t CONST>
class Deque<T, N>::Iterator
{
public:
    using difference_type = typename Deque<T, N>::difference_type;
    using value_type = typename Deque<T, N>::value_type;
    using reference =  typename std::conditional<CONST, 
                                                 typename Deque<T,N>::const_reference, 
                                                 typename Deque<T, N>::reference
                                                 >::type;
    using pointer = typename std::conditional<CONST,
                                              typename Deque<T, N>::const_pointer,
                                              typename Deque<T, N>::pointer
                                     >::type;
    using iterator_category = std::random_access_iterator_tag;

    Iterator(): base_(nullptr), start_(0), offset_(0)
    {}

    Iterator(value_type* base, size_type start, difference_type offset):
        base_(base),
        start_(start),
        offset_(offset)
    {}

    Iterator(const Iterator& other):
        base_(other.base_),
        start_(other.start_),
        offset_(other.offset_)
    {}

    template<bool_t CONST_ = CONST, typename = typename std::enable_if<CONST_, void>::type >
    Iterator(const Iterator<false>& other):
        base_(other.base_),
        start_(other.start_),
        offset_(other.offset_)
    {
    }

    ~Iterator()
    {
    }

    Iterator& operator=(const Iterator& other)
    {
        base_ = other.base_;
        start_ = other.start_;
        offset_ = other.offset_;
        return *this;
    }

    template<bool_t InputConst>
    bool_t operator==(const Iterator<InputConst>& other) const
    {
        return (base_ == other.base_) && (start_ == other.start_) && (offset_ == other.offset_);
    }

    template<bool_t InputConst>
    bool_t operator!=(const Iterator<InputConst>& other) const
    {
        return !this->operator==(other);
    }

    template<bool_t InputConst>
    bool_t operator<(const Iterator<InputConst>& other) const
    {
        assert(base_ == other.base_);
        assert(start_ == other.start_);
        return offset_ < other.offset_;
    }

    template<bool_t InputConst>
    bool_t operator>(const Iterator<InputConst>& other) const
    {
        assert(base_ == other.base_);
        assert(start_ == other.start_);
        return offset_ > other.offset_;
    }

    template<bool_t InputConst>
    bool_t operator<=(const Iterator<InputConst>& other) const
    {
        return !this->operator>(other);
    }

    template<bool_t InputConst>
    bool_t operator>=(const Iterator<InputConst>& other) const
    {
        return !this->operator<(other);
    }

    Iterator& operator++()
    {
        ++(this->offset_);
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator tmp(*this);
        ++(this->offset_);
        return tmp;
    }

    Iterator& operator--()
    {
        /// @todo Handle underflow?
        --(this->offset_);
        return *this;
    }

    Iterator operator--(int)
    {
        /// @todo Handle underflow?
        Iterator tmp(*this);
        --(this->offset_);
        return tmp;

    }

    Iterator& operator+=(difference_type rhs)
    {
        this->offset_ += rhs;
        return *this;
    }

    Iterator operator+(difference_type rhs) const
    {
        Iterator tmp(*this);
        tmp.offset_ += rhs;
        return tmp;
    }

    friend Iterator operator+(difference_type lhs, const Iterator& rhs)
    {
        Iterator tmp(rhs);
        tmp.offset_ += lhs;
        return tmp;
    }

    Iterator& operator-=(difference_type rhs)
    {
        /// @todo Handle underflow?
        this->offset_ -= rhs;
        return *this;
    }

    Iterator operator-(difference_type rhs) const
    {
        /// @todo Handle underflow?
        Iterator tmp(*this);
        tmp.offset_ -= rhs;
        return tmp;
    }

    difference_type operator-(Iterator rhs) const
    {
        /// @todo Handle rhs and this pointing to different container.
        return this->offset_ - rhs.offset_;
    }

    reference operator*() const
    {
        return base_[(start_ + offset_ + N ) % N];
    }

    pointer operator->() const
    {
        return base_ + ((start_ + N + offset_) % N);
    }

    reference operator[](difference_type idx) const
    {
        return base_[(start_ + N + offset_ + idx) % N];
    }

    friend class Iterator<!CONST>;
    friend class Deque<T, N>;

private:
    value_type* base_;
    typename Deque<T, N>::size_type start_;
    difference_type offset_;
};

/**
 * @{
 * Non-member function group.
 */

/**
 * @brief Checks if two Deques are equal
 *
 * @detail Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each 
 * element in lhs compares equal with the element in rhs at the same position.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 * @param lhs Left hand side operand.
 * @param rhs Right hand side operand.
 *
 * @return @b true if the contents of the containers are equal, @b false otherwise.
 * 
 * @relates Deque
 */
template<typename T, std::size_t N>
bool_t operator==( const Deque<T, N> lhs, const Deque<T, N> rhs);

/**
 * @brief Checks if two Deques are equal
 *
 * @detail Checks if the contents of lhs and rhs are equal, that is, they have the same number of elements and each 
 * element in lhs compares equal with the element in rhs at the same position.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 * @param lhs Left hand side operand.
 * @param rhs Right hand side operand.
 *
 * @return @b true if the contents of the containers are not equal, @b false otherwise.
 * 
 * @relates Deque
 */
template<typename T, std::size_t N>
bool_t operator!=( const Deque<T, N> lhs, const Deque<T, N> rhs);

/**
 * @brief Compares the contents.
 *
 * @detail Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent 
 * to std::lexicographical_compare.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 * @param lhs Left hand side operand.
 * @param rhs Right hand side operand.
 *
 * @return @b true if the contents of the lhs are lexicographically @a less than the contents of rhs, @b false otherwise.
 * 
 * @relates Deque
 */
template<typename T, std::size_t N>
bool_t operator<( const Deque<T, N> lhs, const Deque<T, N> rhs);

/**
 * @brief Compares the contents.
 *
 * @detail Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent 
 * to std::lexicographical_compare.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 * @param lhs Left hand side operand.
 * @param rhs Right hand side operand.
 *
 * @return @b true if the contents of the lhs are lexicographically @a less than or @a equal the contents of rhs, 
 * @b false otherwise.
 * 
 * @relates Deque
 */
template<typename T, std::size_t N>
bool_t operator<=( const Deque<T, N> lhs, const Deque<T, N> rhs);

/**
 * @brief Compares the contents.
 *
 * @detail Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent 
 * to std::lexicographical_compare.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 * @param lhs Left hand side operand.
 * @param rhs Right hand side operand.
 *
 * @return @b true if the contents of the lhs are lexicographically @a greater than or equal the contents of rhs, 
 * @b false otherwise.
 * 
 * @relates Deque
 */
template<typename T, std::size_t N>
bool_t operator>( const Deque<T, N> lhs, const Deque<T, N> rhs);

/**
 * @brief Compares the contents.
 *
 * @detail Compares the contents of lhs and rhs lexicographically. The comparison is performed by a function equivalent 
 * to std::lexicographical_compare.
 *
 * @tparam T Container data type.
 * @tparam N Capacity of this container.
 * @param lhs Left hand side operand.
 * @param rhs Right hand side operand.
 *
 * @return @b true if the contents of the lhs are lexicographically @a greater than or @a equal the contents of rhs, 
 * @b false otherwise.
 * 
 * @relates Deque
 */
template<typename T, std::size_t N>
bool_t operator>=( const Deque<T, N> lhs, const Deque<T, N> rhs);

/**
 * @}
 * End non-member function group.
 */

} //namespace details

} //namespace container

} // namespace holo

#include "impl/deque.hpp"

#endif
