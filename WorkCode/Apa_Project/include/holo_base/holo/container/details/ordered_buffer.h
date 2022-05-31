/**
 * @file ordered_buffer.h
 * @brief This header file defines OrderedBuffer object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-10-9
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_COMMON_CONTAINER_ORDERED_BUFFER_H_
#define HOLO_COMMON_CONTAINER_ORDERED_BUFFER_H_

#include <functional>
#include <holo/core/types.h>
#include "deque.h"

namespace holo
{

namespace container
{

namespace details
{

/**
 * @brief A fixed size std::set.
 *
 * @detail Ordered buffer acts like std::set except the capaticy is fixed.
 * Elements in this container is internally sorted in ascending order by Compare method.
 * The container not implemented by red-black tree. It expects the key of each inserted new element is greater than 
 * other elements in the container.
 *
 * @tparam Key The key(value) type.
 * @tparam N Capacity of the container.
 * @tparam Compare A functor to compare Key(value).
 */
template <typename Key, std::size_t N, typename Compare = std::less<Key>, 
          typename Container = holo::container::details::Deque<Key, N> >
class OrderedBuffer
{
public:
    using container_type = Container;
    using key_type = typename Container::value_type;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;
    using key_compare = Compare;
    using value_compare = Compare;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using pointer = typename Container::pointer;
    using const_pointer = typename Container::const_pointer;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using reverse_iterator = typename Container::reverse_iterator;
    using const_reverse_iterator = typename Container::const_reverse_iterator;

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
    OrderedBuffer() noexcept: C()
    {}

    /**
     * @brief Constructs OrderedBuffer container.
     *
     * @detail Constructs a container with as many elements as the range [first, last), with each element 
     * emplace-constructed from its corresponding element in that range.
     *
     * @tparam InputIt Input iterator type.
     * @param first Iterator pointing to the first element.
     * @param last Iterator pointing to the last element.
     */
    template< typename InputIt, typename = typename std::enable_if<!std::is_integral<InputIt>::value>::type>
    OrderedBuffer(InputIt first, InputIt last): C()
    {
        while(first != last)
        {
            emplace(*first++);
        }
    }

    /**
     * @brief Constructs OrderedBuffer container.
     *
     * @detail Constructs a container with a copy of each of the element in x, inthe same order.
     *
     * @param other Another OrderedBuffer container with the same type.
     */
    OrderedBuffer(const OrderedBuffer& other): C(other.C)
    {}

    /**
     * @brief Constructs OrderedBuffer container.
     *
     * @detail Constructs a container that acquires the element of other.
     *
     * @param other Another OrderedBuffer container with the same type.
     */
    OrderedBuffer(OrderedBuffer&& other): C(std::move(other.C))
    {}

    /**
     * @brief Constructs OrderedBuffer container.
     *
     * @detail Constructs a container with a copy of each of the elements in ilist.
     *
     * @param ilist The initailizer list.
     */
    OrderedBuffer(std::initializer_list<value_type> ilist): C()
    {
        for(auto item: ilist)
        {
            emplace(item);
        }
    }

    /**
     * @brief Destructs OrderedBuffer container.
     *
     * @todo comment throws and exception safety.
     */
    ~OrderedBuffer()
    {}

    /**
     * @brief Assigns values to the container.
     *
     * @detail Copy assignment operator. Replaces the contents with a copy of the contents of other.
     *
     * @param other Another container to use as data source.
     *
     * @return The initialized OrderedBuffer container.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    OrderedBuffer& operator= (const OrderedBuffer& other) noexcept
    {
        C = other.C;
        return *this;
    }

    /**
     * @brief Assign content
     *
     * @detail Move assignment operator. Replaces the contents with those of other using move semantics. 
     * other is in a valid but unspecified state afterwards.
     *
     * @param other Another container to use as data source.
     *
     * @return The initialized OrderedBuffer container.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    OrderedBuffer& operator= (OrderedBuffer&& other) noexcept
    {
        C = std::move(other.C);
        return *this;
    }

    /**
     * @brief Assign content
     *
     * @detail Replaces the contents with those identified by initializer list ilist.
     *
     * @param ilist Initializer list to use as data source.
     *
     * @return The initialized OrderedBuffer container.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    OrderedBuffer& operator= (std::initializer_list<value_type> ilist)
    {
        C.clear();
        for(auto item : ilist)
        {
            insert(item);
        }
        return *this;
    }

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
    reference at( size_type pos )
    {
        return C.at(pos);
    }

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
    const_reference at( size_type pos ) const
    {
        return C.at(pos);
    }
    
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
    reference operator[]( size_type pos ) noexcept
    {
        return C[pos];
    }

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
    const_reference operator[]( size_type pos ) const noexcept
    {
        return C[pos];
    }

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
    reference front()
    {
        return C.front();
    }

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
    const_reference front() const
    {
        return C.front();
    }

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
    reference back()
    {
        return C.back();
    }

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
    const_reference back() const
    {
        return C.back();
    }

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
    iterator begin() noexcept
    {
        return C.begin();
    }

    /**
     * @brief Iterator to the beginning.
     *
     * @detail Returns an const iterator to the first element of the container. If the container is empty, the returned 
     * iterator will be equal to end().
     *
     * @return Const iterator to the first element.
     */
    const_iterator begin() const noexcept
    {
        return C.begin();
    }

    /**
     * @brief Iterator to the beginning.
     *
     * @detail Returns an const iterator to the first element of the container. If the container is empty, the returned 
     * iterator will be equal to end().
     *
     * @return Const iterator to the first element.
     */
    const_iterator cbegin() const noexcept
    {
        return C.cbegin();
    }

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns an iterator to the element following the last element of the container.
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Iterator to the element following the last element.
     */
    iterator end() noexcept
    {
        return C.end();
    }

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns an const iterator to the element following the last element of the container.
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const iterator to the element following the last element.
     */
    const_iterator end() const noexcept
    {
        return C.end();
    }

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns an const iterator to the element following the last element of the container.
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const iterator to the element following the last element.
     */
    const_iterator cend() const noexcept
    {
        return C.cend();
    }

    /**
     * @brief Reverse iterator to the beginning.
     *
     * @detail Returns a reverse iterator to the first element of the reversed container. 
     * It corresponds to the last element of the non-reversed container. 
     * If the container is empty, the returned iterator is equal to rend().
     *
     * @return Reverse iterator to the first element.
     */
    reverse_iterator rbegin() noexcept
    {
        return C.rbegin();
    }

    /**
     * @brief Reverse iterator to the beginning.
     *
     * @detail Returns a const reverse iterator to the first element of the reversed container. 
     * It corresponds to the last element of the non-reversed container. If the container is empty, 
     * the returned iterator is equal to rend().
     *
     * @return Const everse iterator to the first element.
     */
    const_reverse_iterator rbegin() const noexcept
    {
        return C.rbegin();
    }

    /**
     * @brief Reverse iterator to the beginning.
     *
     * @detail Returns a const reverse iterator to the first element of the reversed container. 
     * It corresponds to the last element of the non-reversed container. If the container is empty, 
     * the returned iterator is equal to rend().
     *
     * @return Const everse iterator to the first element.
     */
    const_reverse_iterator crbegin() const noexcept
    {
        return C.crbegin();
    }

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns a reverse iterator to the element following the last element of the reversed container. 
     * It corresponds to the element preceding the first element of the non-reversed container. 
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Reverse iterator to the element following the last element.
     */
    reverse_iterator rend() noexcept
    {
        return C.rend();
    }

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns a const reverse iterator to the element following the last element of the reversed container. 
     * It corresponds to the element preceding the first element of the non-reversed container. 
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const reverse iterator to the element following the last element.
     */
    const_reverse_iterator rend() const noexcept
    {
        return C.rend();
    }

    /**
     * @brief Iterator to the end.
     *
     * @detail Returns a const reverse iterator to the element following the last element of the reversed container. 
     * It corresponds to the element preceding the first element of the non-reversed container. 
     * This element acts as a placeholder, attempting to access it results in undefined behavior.
     *
     * @return Const reverse iterator to the element following the last element.
     */
    const_reverse_iterator crend() const noexcept
    {
        return C.crend();
    }

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
    bool_t empty() const noexcept
    {
        return C.empty();
    }

    /**
     * @brief Number of elements in the container.
     *
     * @return The number of elements in the container.
     */
    size_type size() const noexcept
    {
        return C.size();
    }

    /**
     * @brief Number of elements the container can hold.
     *
     * @return Capacity of the container.
     */
    size_type max_size() const noexcept
    {
        return C.max_size();
    }

    /**
     * @brief Change size
     *
     * @detail Resize the container so that it contains n elements. OrderedBuffer is a fixed size container. if n <= N,
     * Will do nothing. if n > N, will throw exception.
     *
     * @param n New container size in number of elements.
     *
     * @throws BadAllocException throws @ref holo::exception::BadAllocException if n > N.
     *
     * @note Exception safety: strong
     */
    void resize(size_type n)
    {
        C.resize(n);
    }

    /**
     * @brief Shrink to fit.
     *
     * @detail Requests the container to reduce its memory usage to fit its size. This function will do nothing.
     */
    void shrink_to_fit() noexcept
    {
        C.shrink_to_fit();
    }

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
     * @detail The new contents are elements constructed from each of the elements in the range between first and last.
     *
     * @tparam InputIt Input iterator type.
     * @param first Iterator pointing to the first element.
     * @param last Iterator pointing to the last element.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    template <class InputIt, typename = typename std::enable_if<!std::is_integral<InputIt>::value >::type >
    void assign(InputIt first, InputIt last) noexcept
    {
        C.clear();
        while(first != last)
        {
            emplace(*first++);
        }
    }

    /**
     * @brief Assign container content.
     *
     * @detail The new contents are copies of the values passed as initializer list, in the same order.
     *
     * @param ilist The initializer list.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    void assign(std::initializer_list<value_type> ilist)
    {
        C.clear();
        for (auto item : ilist)
        {
            emplace(item);
        }
    }

    /**
     * @brief Clears the contents.
     *
     * @detail Erases all elements from the container. After this call, size() returns zero.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    void clear() noexcept
    {
        C.clear();
    }

    /**
     * @brief Inserts value.
     *
     * @detail if container is full, element with smallest key will be replaced.
     *
     * @param value Element value to insert.
     *
     * @return Returns a pair consisting of an iterator to the inserted element 
     * (or to the element that prevented the insertion) and a bool value set to true if the insertion took place.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    std::pair<iterator, holo::bool_t> insert( const value_type& value ) noexcept
    {
        iterator it = C.begin();
        holo::bool_t insertion = false;
        difference_type offset = -1;

        for(auto rit = C.rbegin(); rit != C.rend(); ++rit)
        {
            if( key_compare()(*rit, value) )
            {
                insertion = true;
                offset = rit.base() - begin();
                break;
            }
            else
            {
                if ( !key_compare()(value, *rit) )
                {
                    offset = rit.base() - begin() - 1;
                    break;
                }
            }
        }

        if(offset == -1 && size() < N)
        {
            insertion = true;
            offset = 0;
        }

        if (insertion)
        {
            if(size() == N)
            {
                C.pop_front();
                offset--;
            }
            it = C.insert(C.begin() + offset, value);
        }
        else
        {
            if(offset == -1)
            {
                it = C.end();
            }
            else
            {
                it = C.begin() + offset;
            }
        }
        return std::pair<iterator, holo::bool_t>(it, insertion);
    }

    /**
     * @brief Inserts value.
     *
     * @detail if container is full, element with smallest key will be replaced.
     *
     * @param value Element value to insert.
     *
     * @return Returns a pair consisting of an iterator to the inserted element 
     * (or to the element that prevented the insertion) and a bool value set to true if the insertion took place.
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    std::pair<iterator, holo::bool_t> insert( value_type&& value ) noexcept
    {
        iterator it = C.begin();
        holo::bool_t insertion = false;
        difference_type offset = -1;

        for(auto rit = C.rbegin(); rit != C.rend(); ++rit)
        {
            if( key_compare()(*rit, value) )
            {
                insertion = true;
                offset = rit.base() - begin();
                break;
            }
            else
            {
                if ( !key_compare()(value, *rit) )
                {
                    offset = rit.base() - begin() - 1;
                    break;
                }
            }
        }

        if(offset == -1 && size() < N)
        {
            insertion = true;
            offset = 0;
        }

        if (insertion)
        {
            if(size() == N)
            {
                C.pop_front();
                offset--;
            }
            it = C.insert(C.begin() + offset, std::move(value));
        }
        else
        {
            if(offset == -1)
            {
                it = C.end();
            }
            else
            {
                it = C.begin() + offset;
            }
        }
        return std::pair<iterator, holo::bool_t>(it, insertion);
    }

    /**
     * @brief Inserts elements from range [first, last) before pos.
     *
     * @detail if container is full, element with smallest key will be replaced.
     *
     * @tparam InputIt Input iterator type. InputIt must qualifies as C++ named requiredments "LegacyInputIterator" to 
     * avoid ambiguity with insert(const_iterator, size_type, const value_type&).
     *
     * @param first Iterator pointing to the beginning of elements to insert.
     * @param last Iterator pointing to the end of elements to insert.
     *
     * @pre first and last point to same container and last >= first.
     *
     * @note The behavior is undefined if first and last are iterators into *this.
     *
     * @throws noexcept
     */
    template< class InputIt >
    void insert( InputIt first, InputIt last ) noexcept
    {
        while(first != last)
        {
            emplace(*first++);
        }
    }

    /**
     * @brief Inserts elements from initializer list before pos.
     *
     * @detail if container is full, element with smallest key will be replaced.
     *
     * @param pos Iterator before which the content will be inserted. pos may be the end() iterator.
     * @param ilist
     *
     * @throws noexcept
     *
     * @note Exception safety: Nothrow
     */
    void insert( std::initializer_list<value_type> ilist ) noexcept
    {
        for(auto item : ilist)
        {
            emplace(item);
        }
    }

    /**
     * @brief Constructs element in-place
     *
     * @detail if container is full, element with smallest key will be replaced.
     *
     * @tparam Args Constructor argument types.
     * @param pos Iterator before which the new element will be constructed.
     * @param args Arguments to forward to the constructor of the element.
     *
     * @return Iterator pointing to the emplaced element.
     */
    template< class... Args >
    std::pair<iterator, holo::bool_t> emplace( Args&&... args )
    {
        iterator it = C.begin();
        holo::bool_t insertion = false;
        difference_type offset = -1;

        value_type value(std::forward<Args>(args)...);

        for(auto rit = C.rbegin(); rit != C.rend(); ++rit)
        {
            if( key_compare()(*rit, value) )
            {
                insertion = true;
                offset = rit.base() - begin();
                break;
            }
            else
            {
                if ( !key_compare()(value, *rit) )
                {
                    offset = rit.base() - begin() - 1;
                    break;
                }
            }
        }

        if(offset == -1 && size() < N)
        {
            insertion = true;
            offset = 0;
        }

        if (insertion)
        {
            if(size() == N)
            {
                C.pop_front();
                offset--;
            }
            it = C.emplace(C.begin() + offset, std::move(value));
        }
        else
        {
            if(offset == -1)
            {
                it = C.end();
            }
            else
            {
                it = C.begin() + offset;
            }
        }
        return std::pair<iterator, holo::bool_t>(it, insertion);
    }

    /**
     * @brief Removes the element at pos.
     *
     * @param pos Iterator to the element to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase( const_iterator pos )
    {
        return C.erase(pos);
    }

    /**
     * @brief Removes the elements in the range [first, last).
     *
     * @param first Iterator pointing to the beginning of elements to remove.
     * @param last Iterator pointing to the end of elements to remove.
     *
     * @return Iterator following the last removed element.
     */
    iterator erase( const_iterator first, const_iterator last )
    {
        return C.erase(first, last);
    }

    /**
     * @brief Removes the last element.
     * @todo pop_back on an empty container?
     */
    void pop_back()
    {
        C.pop_back();
    }

    /**
     * @brief Removes the first element.
     */
    void pop_front()
    {
        C.pop_front();
    }

    /**
     * @brief Swap the contents.
     *
     * @param other Container to exchange the contents with.
     */
    void swap( OrderedBuffer& other )
    {
        C.swap(other.C);
    }

    /**
     * @}
     * End modifiers API group
     */
    
    bool_t operator==(const OrderedBuffer rhs) const
    {
        return C == rhs.C;
    }

    bool_t operator!=(const OrderedBuffer rhs) const
    {
        return C != rhs.C;
    }

    bool_t operator<(const OrderedBuffer rhs) const
    {
        return C < rhs.C;
    }

    bool_t operator>(const OrderedBuffer rhs) const
    {
        return C > rhs.C;
    }

    bool_t operator<=(const OrderedBuffer rhs) const
    {
        return C <= rhs.C;
    }

    bool_t operator>=(const OrderedBuffer rhs) const
    {
        return C >= rhs.C;
    }

private:
    Container C;
};

} // namespace details

} // namespace container

} // namespace holo

#endif
