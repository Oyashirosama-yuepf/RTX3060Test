/**
 * @file deque.hpp
 * @brief This file implements Deque object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-23
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 *
 * @todo Contructor of value_type may throw exception, garentee exception safety!
 * @todo There are lots of code duplication, reduce code duplication later!
 *
 */

#include <algorithm>
#include <new>
#include <type_traits>
#include <holo/core/types.h>
#include <holo/core/exception.h>
#include "../deque.h"

namespace holo
{

namespace container
{

namespace details
{

template<typename T, std::size_t N>
Deque<T, N>::Deque() noexcept:
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(0)
{
}

template<typename T, std::size_t N>
Deque<T, N>::Deque(size_type n):
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(n)
{
    if(n <= N)
    {
        for(size_type i = 0; i < n; ++i)
        {
            (void)new(&data_[i]) value_type();
        }
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
Deque<T, N>::Deque(size_type n, const value_type& value):
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(n)
{
    if(n <= N)
    {
        for(size_type i = 0; i < n; ++i)
        {
            (void)new(&data_[i]) value_type(value);
        }
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
template< typename InputIt, typename>
Deque<T, N>::Deque(InputIt first, InputIt last):
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(0)
{
    if (last - first <= (difference_type)N)
    {
        size_type count = (size_type)(last - first) > N ? N : (size_type)(last - first);
        for(size_type i = 0; i < count; ++i)
        {
            (void)new(&data_[i]) value_type(*first++);
        }
        size_ = count;
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
Deque<T, N>::Deque(const Deque& other):
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(other.size_)
{
    for(size_type i = 0; i < other.size_; ++i)
    {
        (void)new(&data_[i]) value_type(other[i]);
    }
}

template<typename T, std::size_t N>
Deque<T, N>::Deque(Deque&& other):
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(other.size_)
{
    for(size_type i = 0; i < other.size_; ++i)
    {
        (void)new(&data_[i]) value_type(std::move(other[i]));
    }
}

template<typename T, std::size_t N>
Deque<T, N>::Deque(std::initializer_list<value_type> ilist):
    data_(reinterpret_cast<value_type*>(buffer_)), start_(0), size_(0)
{
    if (ilist.size() <= N)
    {
        size_type i = 0;
        for(auto v : ilist)
        {
            (void)new(&data_[i++]) value_type(v);
        }
        size_ = ilist.size();
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
Deque<T, N>::~Deque()
{
    for(size_type i = 0; i < size_; ++i)
    {
        data_[ (start_ + i) % N ].~value_type();
    }
}

template<typename T, std::size_t N>
Deque<T, N>& Deque<T, N>::operator= (const Deque& other) noexcept
{
    clear();
    for(size_type i = 0; i < other.size_; ++i)
    {
        (void)new(&data_[ (start_ + i) % N ]) value_type(other[i]);
    }
    size_ = other.size_;
    return *this;
}

template<typename T, std::size_t N>
Deque<T, N>& Deque<T, N>::operator= (Deque&& other) noexcept
{
    clear();
    for(size_type i = 0; i < other.size_; ++i)
    {
        (void)new(&data_[ (start_ + i) % N ]) value_type(std::move(other[i]));
    }
    size_ = other.size_;
    return *this;
}

template<typename T, std::size_t N>
Deque<T, N>& Deque<T, N>::operator= (std::initializer_list<value_type> ilist)
{
    clear();
    if (ilist.size() <= N)
    {
        size_type i = 0;
        for(auto v : ilist)
        {
            (void)new(&data_[i++]) value_type(v);
        }
        size_ = ilist.size();
        return *this;
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
typename Deque<T, N>::reference Deque<T, N>::at( size_type pos )
{
    if ( pos >= size_ )
    {
        throw holo::exception::OutOfRangeException("Deque visit index out of range!");
    }
    return data_[ (start_ + pos) % N ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reference Deque<T, N>::at( size_type pos ) const
{
    if ( pos >= size_ )
    {
        throw holo::exception::OutOfRangeException("Deque visit index out of range!");
    }
    return data_[ (start_ + pos) % N ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::reference Deque<T, N>::operator[]( size_type pos) noexcept
{
    return data_[ (start_ + pos) % N ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reference Deque<T, N>::operator[]( size_type pos) const noexcept
{
    return data_[ (start_ + pos) % N ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::reference Deque<T, N>::front()
{
    if (size_ == 0)
    {
        throw holo::exception::OutOfRangeException("Call front() on empty Deque");
    }
    return data_[ start_ ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reference Deque<T, N>::front() const
{
    if (size_ == 0)
    {
        throw holo::exception::OutOfRangeException("Call front() on empty Deque");
    }
    return data_[ start_ ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::reference Deque<T, N>::back()
{
    if (size_ == 0)
    {
        throw holo::exception::OutOfRangeException("Call back() on empty Deque");
    }
    return data_[ (start_ + size_ + N - 1) % N ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reference Deque<T, N>::back() const
{
    if (size_ == 0)
    {
        throw holo::exception::OutOfRangeException("Call back() on empty Deque");
    }
    return data_[ (start_ + size_ + N - 1) % N ];
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::begin() noexcept
{
    return iterator( data_, start_, (difference_type)(0) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_iterator Deque<T, N>::begin() const noexcept
{
    return const_iterator( data_, start_, (difference_type)(0) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_iterator Deque<T, N>::cbegin() const noexcept
{
    return const_iterator( data_, start_, (difference_type)(0) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::end() noexcept
{
    return iterator( data_, start_, (difference_type)(size_) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_iterator Deque<T, N>::end() const noexcept
{
    return const_iterator( data_, start_, (difference_type)(size_) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_iterator Deque<T, N>::cend() const noexcept
{
    return const_iterator( data_, start_, (difference_type)(size_) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::reverse_iterator Deque<T, N>::rbegin() noexcept
{
    return reverse_iterator( iterator( data_, start_, (difference_type)(size_) ) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reverse_iterator Deque<T, N>::rbegin() const noexcept
{
    return const_reverse_iterator( const_iterator( data_, start_, (difference_type)(size_) ) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reverse_iterator Deque<T, N>::crbegin() const noexcept
{
    return const_reverse_iterator( const_iterator( data_, start_, (difference_type)(size_) ) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::reverse_iterator Deque<T, N>::rend() noexcept
{
    return reverse_iterator( iterator( data_, start_, (difference_type)(0) ) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reverse_iterator Deque<T, N>::rend() const noexcept
{
    return const_reverse_iterator( const_iterator( data_, start_, (difference_type)(0) ) );
}

template<typename T, std::size_t N>
typename Deque<T, N>::const_reverse_iterator Deque<T, N>::crend() const noexcept
{
    return const_reverse_iterator( const_iterator( data_, start_, (difference_type)(0) ) );
}

template<typename T, std::size_t N>
bool_t Deque<T, N>::empty() const noexcept
{
    return size_ == 0;
}

template<typename T, std::size_t N>
typename Deque<T, N>::size_type Deque<T, N>::size() const noexcept
{
    return size_;
}

template<typename T, std::size_t N>
typename Deque<T, N>::size_type Deque<T, N>::max_size() const noexcept
{
    return N;
}

template<typename T, std::size_t N>
void Deque<T, N>::resize(size_type n)
{
    if(n > N)
    {
        throw holo::exception::BadAllocException();
    }
    return;
}

template<typename T, std::size_t N>
void Deque<T, N>::shrink_to_fit() noexcept
{
    // Do nothing, just make this container compatible with std::deque.
    return;
}


template<typename T, std::size_t N>
template <class InputIt, typename>
void Deque<T, N>::assign(InputIt first, InputIt last)
{
    size_type count = (size_type)(last - first);
    if (count <= N)
    {
        clear();
        for(size_type i = 0; i < count; ++i)
        {
            (void)new(&data_[i]) value_type(*first++);
        }
        size_ = count;
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
void Deque<T, N>::assign(size_type n, const value_type& value)
{
    if (n <= N)
    {
        clear();
        for(size_type i = 0; i < n; ++i)
        {
            (void)new(&data_[i]) value_type(value);
        }
        size_ = n;
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
void Deque<T, N>::assign(std::initializer_list<value_type> ilist)
{
    if (ilist.size() <= N)
    {
        clear();
        auto it = ilist.begin();
        for(size_type i = 0; i < ilist.size(); ++i)
        {
            (void)new(&data_[i]) value_type(*it++);
        }
        size_ = ilist.size();
    }
    else
    {
        throw holo::exception::BadAllocException();
    }
}

template<typename T, std::size_t N>
void Deque<T, N>::clear() noexcept
{
    for(size_type idx = start_; idx < start_ + size_; ++idx)
    {
        data_[ idx % N ].~value_type();
    }
    start_ = 0;
    size_ = 0;
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::insert( const_iterator pos, const value_type& value )
{
    if( size_ >= N )
    {
        throw holo::exception::BadAllocException();
    }

    // value could be an element in this container, make a copy before moving container elements.
    value_type tmp(value);

    iterator insert_pos(pos.base_, pos.start_, pos.offset_);

    if( insert_pos != cbegin() )
    {
        // Move [ insert_pos, cend() ) to [ insert_pos + 1, cend() + 1 )
        // std::move_backward(insert_pos, end(), end() + 1);
        iterator from = end();
        iterator to = end() + 1;
        while(from != insert_pos)
        {
            (void)new(&(*--to)) value_type(std::move(*--from));
            from->~value_type();
        }
        (void)new(&(*insert_pos)) value_type(std::move(tmp));
    }
    else
    {
        // Insert at beginning
        start_ = (start_ + N - 1) % N;
        insert_pos.start_ = start_;
        (void)new(&(*insert_pos)) value_type(std::move(tmp));
    }
    size_ += 1;
    return insert_pos;
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::insert( const_iterator pos, value_type&& value )
{
    if( size_ >= N )
    {
        throw holo::exception::BadAllocException();
    }

    // value could be an element in this container, make a copy before moving container elements.
    value_type tmp(std::move(value));

    iterator insert_pos(pos.base_, pos.start_, pos.offset_);

    if( insert_pos != cbegin() )
    {
        // Move [ insert_pos, cend() ) to [ insert_pos + 1, cend() + 1 )
        // std::move_backward(insert_pos, end(), end() + 1);
        iterator from = end();
        iterator to = end() + 1;
        while(from != insert_pos)
        {
            (void)new(&(*--to)) value_type(std::move(*--from));
            from->~value_type();
        }
        (void)new(&(*insert_pos)) value_type(std::move(tmp));
    }
    else
    {
        // Insert at beginning
        start_ = (start_ + N - 1) % N;
        insert_pos.start_ = start_;
        (void)new(&(*insert_pos)) value_type(std::move(tmp));
    }
    size_ += 1;
    return insert_pos;
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::insert( const_iterator pos,
                                                                      size_type count,
                                                                      const value_type& value )
{
    if( size_ + count > N )
    {
        throw holo::exception::BadAllocException();
    }

    // value could be an element in this container, make a copy before moving container elements.
    value_type tmp(value);

    iterator insert_pos(pos.base_, pos.start_, pos.offset_);

    if (count == 0)
    {
        return insert_pos;
    }

    if( insert_pos != cbegin() )
    {
        // Move [ pos, cend() ) to [ pos + count, cend() + count )
        // std::move_backward( pos, cend(), cend() + count );
        iterator from = end();
        iterator to = end() + count;
        while(from != insert_pos)
        {
            (void)new(&(*--to)) value_type(std::move(*--from));
            from->~value_type();
        }
        for( size_type idx = 0; idx < count; ++idx)
        {
            (void)new(&insert_pos[idx]) value_type(tmp);
        }
    }
    else
    {
        // Insert at beginning
        start_ = (start_ + N - count) % N;
        insert_pos.start_ = start_;
        for( size_type idx = 0; idx < count; ++idx)
        {
            (void)new(&insert_pos[idx]) value_type(tmp);
        }
    }
    size_ += count;
    return insert_pos;
}

template<typename T, std::size_t N>
template< class InputIt >
typename Deque<T, N>::iterator Deque<T, N>::insert( const_iterator pos, InputIt first, InputIt last )
{
    assert(last >= first);
    size_type count = (size_type)(last - first);
    if( size_ + count > N )
    {
        throw holo::exception::BadAllocException();
    }

    iterator insert_pos(pos.base_, pos.start_, pos.offset_);

    if (count == 0)
    {
        return insert_pos;
    }

    if( insert_pos != cbegin() )
    {
        iterator from = end();
        iterator to = end() + count;
        while(from != insert_pos)
        {
            (void)new(&(*--to)) value_type(std::move(*--from));
            from->~value_type();
        }
        insert_pos += count;
    }
    else
    {
        start_ = (start_ + N - count) % N;
        insert_pos.start_ = start_;
        insert_pos.offset_ = count;
    }
    while( first != last )
    {
        (void)new(&(*(--insert_pos))) value_type(*(--last));
    }
    size_ += count;
    return insert_pos;
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::insert( const_iterator pos,
                                                                      std::initializer_list<value_type> ilist )
{
    return insert(pos, ilist.begin(), ilist.end());
}

template<typename T, std::size_t N>
template< class... Args >
typename Deque<T, N>::iterator Deque<T, N>::emplace( const_iterator pos, Args&&... args )
{
    if( size_ >= N )
    {
        throw holo::exception::BadAllocException();
    }

    iterator insert_pos(pos.base_, pos.start_, pos.offset_);

    if( insert_pos != cbegin() )
    {
        // Move [ pos, cend() ) to [ pos + 1, cend() + 1 )
        // std::move_backward(pos, cend(), cend() + 1);
        iterator from = end();
        iterator to = end() + 1;
        while(from != insert_pos)
        {
            (void)new(&(*--to)) value_type(std::move(*--from));
            from->~value_type();
        }
        (void)new(&(*insert_pos)) value_type(std::forward<Args>(args)...);
    }
    else
    {
        // Insert at beginning
        start_ = (start_ + N - 1) % N;
        insert_pos.start_ = start_;
        (void)new(&(*insert_pos)) value_type(std::forward<Args>(args)...);
    }
    size_ += 1;
    return insert_pos;
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::erase( const_iterator pos )
{
    auto erase_pos = iterator(pos.base_, pos.start_, pos.offset_);
    if(erase_pos != cbegin())
    {
        std::move(erase_pos + 1, end(), erase_pos);
        data_[ (start_ + size_ - 1) % N ].~value_type();
    }
    else
    {
        data_[ start_ ].~value_type();
        start_ = (start_ + 1) % N;
        erase_pos.start_ = start_;
    }
    size_ -= 1;
    return erase_pos;
}

template<typename T, std::size_t N>
typename Deque<T, N>::iterator Deque<T, N>::erase( const_iterator first, const_iterator last )
{
    assert(last >= first);

    auto erase_pos = iterator(first.base_, first.start_, first.offset_);
    auto erase_first = iterator(first.base_, first.start_, first.offset_);
    auto erase_last = iterator(last.base_, last.start_, last.offset_);
    size_type count = (size_type)(last - first);

    if( first == cbegin() )
    {
        while(first != last)
        {
            first++->~value_type();
        }
        start_ = (start_ + count) % N;
        erase_pos.start_ = start_;
    }
    else
    {
        std::move(erase_last, end(), erase_first);
        for(erase_pos = end() - (last - first); erase_pos != end(); ++erase_pos)
        {
            (*erase_pos).~value_type();
        }
        erase_pos = iterator(first.base_, first.start_, first.offset_);
    }
    size_ -= count;
    return erase_pos;
}

template<typename T, std::size_t N>
void Deque<T, N>::push_back( const value_type& value )
{
    if (size_ >= N)
    {
        throw holo::exception::BadAllocException();
    }
    (void)new(&data_[ (start_ + size_) % N ]) value_type(value);
    ++size_;
}

template<typename T, std::size_t N>
void Deque<T, N>::push_back( value_type&& value )
{
    if (size_ >= N)
    {
        throw holo::exception::BadAllocException();
    }
    (void)new(&data_[ (start_ + size_) % N ]) value_type(std::move(value));
    ++size_;
}

template<typename T, std::size_t N>
template< class... Args >
void Deque<T, N>::emplace_back( Args&&... args )
{
    if (size_ >= N)
    {
        throw holo::exception::BadAllocException();
    }
    (void)new(&data_[ (start_ + size_) % N ]) value_type(std::forward<Args>(args)...);
    ++size_;
}

template<typename T, std::size_t N>
void Deque<T, N>::pop_back()
{
    data_[ (start_ + size_ + N - 1) % N ].~value_type();
    --size_;
}

template<typename T, std::size_t N>
void Deque<T, N>::push_front( const value_type& value )
{
    if (size_ >= N)
    {
        throw holo::exception::BadAllocException();
    }
    start_ = (start_ + N - 1) % N;
    (void)new(&data_[ start_ ]) value_type(value);
    ++size_;
}

template<typename T, std::size_t N>
void Deque<T, N>::push_front( value_type&& value )
{
    if (size_ >= N)
    {
        throw holo::exception::BadAllocException();
    }
    start_ = (start_ + N - 1) % N;
    (void)new(&data_[ start_ ]) value_type(std::move(value));
    ++size_;
}

template<typename T, std::size_t N>
template< class... Args >
void Deque<T, N>::emplace_front( Args&&... args )
{
    if (size_ >= N)
    {
        throw holo::exception::BadAllocException();
    }
    start_ = (start_ + N - 1) % N;
    (void)new(&data_[ start_ ]) value_type(std::forward<Args>(args)...);
    ++size_;
}

template<typename T, std::size_t N>
void Deque<T, N>::pop_front()
{
    data_[ start_ ].~value_type();
    start_ = (start_ + 1) % N;
    --size_;
}

template<typename T, std::size_t N>
void Deque<T, N>::swap( Deque& other )
{
    std::swap(data_, other.data_);
    std::swap(start_, other.start_);
    std::swap(size_, other.size_);
}

template<typename T, std::size_t N>
bool_t operator==( const Deque<T, N> lhs, const Deque<T, N> rhs)
{
    if(lhs.size() != rhs.size())
    {
        return false;
    }
    for(typename Deque<T, N>::size_type i = 0; i < lhs.size(); ++i)
    {
        if(!(lhs[i] == rhs[i]))
        {
            return false;
        }
    }
    return true;
}

template<typename T, std::size_t N>
bool_t operator!=( const Deque<T, N> lhs, const Deque<T, N> rhs)
{
    return !(lhs == rhs);
}

template<typename T, std::size_t N>
bool_t operator<( const Deque<T, N> lhs, const Deque<T, N> rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, std::size_t N>
bool_t operator>( const Deque<T, N> lhs, const Deque<T, N> rhs)
{
    return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template<typename T, std::size_t N>
bool_t operator<=( const Deque<T, N> lhs, const Deque<T, N> rhs)
{
    return !(rhs < lhs);
}

template<typename T, std::size_t N>
bool_t operator>=( const Deque<T, N> lhs, const Deque<T, N> rhs)
{
    return !(lhs < rhs);
}

} // namespace details

} //namespace container

} //namespace holo

