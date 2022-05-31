/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file basic_input_buffer.h
 * @brief This header file defines BasicInputBuffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-15
 */

#ifndef HOLO_UTILS_INTERNAL_BASIC_INPUT_BUFFER_H_
#define HOLO_UTILS_INTERNAL_BASIC_INPUT_BUFFER_H_

#include <cstring>
#include <type_traits>

#include <holo/utils/internal/basic_buffer.h>
#include <holo/core/exception.h>

namespace holo
{
namespace utils
{

/**
 * @brief BasicInputBuffer object is base class for all readonly buffers.
 */
class BasicInputBuffer: public BasicBuffer
{
public:

    /**
     * @brief Construct from BasicBuffer
     *
     * @param buffer A BasicBuffer object to reference.
     * @param offset Read offset.
     */
    BasicInputBuffer(BasicBuffer const& buffer, size_t offset = 0) noexcept:
        BasicBuffer(buffer),
        get_offset_(offset)
    {}

    /**
     * @brief Copy constructor
     *
     * @param other The other BasicInputBuffer object.
     */
    BasicInputBuffer(BasicInputBuffer const& other) noexcept:
        BasicBuffer(other),
        get_offset_(other.get_offset_)
    {}

    virtual ~BasicInputBuffer() noexcept
    {}

    /**
     * @brief Extraction operator for arithmetic types
     *
     * @tparam T Type of value to extract from buffer.
     * @param value The value to extract from buffer.
     *
     * @return Reference to basic input buffer.
     */
    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicInputBuffer& operator>>(T& value)
    {
        read(value);
        return *this;
    }

    /**
     * @brief Extraction operator for non-arithmetic types
     *
     * @tparam T Type of value to extract from buffer.
     * @param value The value to extract from buffer.
     *
     * @return Reference to basic input buffer.
     */
    template<typename T, typename std::enable_if<!std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicInputBuffer& operator>>(T& value)
    {
        Align();
        value.Deserialize(*this);
        return *this;
    }

    /**
     * @brief Extraction operator for string type
     *
     * @param value The value to extract from buffer.
     *
     * @return Reference to basic input buffer.
     */
    BasicInputBuffer& operator>>(std::string& value)
    {
        size_t end = get_offset_;
        while(end < size_)
        {
            if(data_[end] == 0)
            {
                break;
            }
            ++end;
        }
        if(end == size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        value = std::string(reinterpret_cast<char_t const*>(data_ + get_offset_));
        get_offset_ = end + 1;
        return *this;
    }

    /**
     * @brief Extraction operator for manipulators
     *
     * @param func function to call
     *
     * @return Reference to basic input buffer
     */
    BasicInputBuffer& operator>>(BasicInputBuffer& (*func)(BasicInputBuffer&))
    {
        return func(*this);
    }

    /**
     * @brief Read data to iterator range [first, last);
     *
     * @tparam InputIterator Type of iterator.
     * @param first iterator pointing to first value to extract.
     * @param last iterator pointing to last value to extract.
     *
     * @return Reference to input buffer.
     */
    template<typename InputIterator>
    BasicInputBuffer& Read(InputIterator first, InputIterator last)
    {
        while(first < last)
        {
            *this >> *first;
            ++first;
        }
        return *this;
    }

    /**
     * @brief Sets the position of the next character to be extracted from the input buffer
     *
     * @param pos Absolute position within the buffer.
     *
     * @return Reference to this basic input buffer.
     */
    BasicInputBuffer& Seekg(size_t pos)
    {
        if(pos > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        get_offset_ = pos;
        return *this;
    }

    /**
     * @brief Sets the position of the next character to be extracted from the input buffer
     *
     * @param offset Offset value, relative to the dir parameter.
     * @param dir Object of type holo::utils::BasicBuffer::Seekdir. It may take one of following constant: @n
     * holo::utils::BasicBuffer::beg Beginning of the input buffer. @n
     * holo::utils::BasicBuffer::end End of the input buffer. @n
     * holo::utils::BasicBuffer::cur Current position of the input buffer.
     *
     * @return Reference to this input buffer.
     */
    BasicInputBuffer& Seekg(ssize_t offset, holo::utils::BasicBuffer::Seekdir dir)
    {
        if(holo::utils::BasicBuffer::beg == dir)
        {
            if( (offset < 0) || (static_cast<size_t>(offset) > size_) )
            {
                throw holo::exception::OutOfRangeException("");
            }
            get_offset_ = static_cast<size_t>(offset);
        }
        else if(holo::utils::BasicBuffer::end == dir)
        {
            if( (offset > 0) || (static_cast<size_t>(-offset) > size_) )
            {
                throw holo::exception::OutOfRangeException("");
            }
            get_offset_ = static_cast<size_t>(offset) + size_;
        }
        else
        {
            if( ((offset >= 0) && (static_cast<size_t>(offset) + get_offset_ > size_)) ||
                ((offset < 0) && (static_cast<size_t>(-offset) > get_offset_)) )
            {
                throw holo::exception::OutOfRangeException("");
            }
            get_offset_ = get_offset_ + static_cast<size_t>(offset);
        }
        return *this;
    }

    /**
     * @brief Gets the position of the next character to be extracted from the input buffer
     *
     * @return Absolute position within the buffer.
     */
    size_t Tellg() const
    {
        return get_offset_;
    }

    /**
     * @brief Sets the position of next character to be extracted from the input buffer to next aligned position.
     */
    virtual void Align() const = 0;

protected:
    /**
     * @brief Read char_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(char_t& value) const = 0;

    /**
     * @brief Read int8_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int8_t& value) const = 0;

    /**
     * @brief Read uint8_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint8_t& value) const = 0;

    /**
     * @brief Read int16_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int16_t& value) const = 0;

    /**
     * @brief Read uint16_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint16_t& value) const = 0;

    /**
     * @brief Read int32_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int32_t& value) const = 0;

    /**
     * @brief Read uint32_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint32_t& value) const = 0;

    /**
     * @brief Read int64_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int64_t& value) const = 0;

    /**
     * @brief Read uint64_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint64_t& value) const = 0;

    /**
     * @brief Read float32_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(float32_t& value) const = 0;

    /**
     * @brief Read float64_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(float64_t& value) const = 0;

    size_t mutable get_offset_;
    
};

static inline BasicInputBuffer& align(BasicInputBuffer& buf)
{
    buf.Align();
    return buf;
}

} // namespace utils
} // namespace holo

#endif

