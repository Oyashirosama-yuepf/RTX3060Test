/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file basic_output_buffer.h
 * @brief This header file defines BasicOutputBuffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-18
 */

#ifndef HOLO_UTILS_INTERNAL_BASIC_OUTPUT_BUFFER_H_
#define HOLO_UTILS_INTERNAL_BASIC_OUTPUT_BUFFER_H_

#include <cstring>
#include <type_traits>

#include <holo/core/exception.h>
#include <holo/utils/internal/basic_buffer.h>

namespace holo
{
namespace utils
{

class BasicOutputBuffer
{
public:
    /**
     * @brief Construct from BasicBuffer
     *
     * @param buffer The BasicBuffer object.
     */
    BasicOutputBuffer(BasicBuffer& buffer):
        buffer_(buffer),
        put_offset_(buffer.GetSize())
    {}

    BasicOutputBuffer(BasicOutputBuffer const&) = delete;

    /**
     * @brief Destructor
     */
    virtual ~BasicOutputBuffer() noexcept
    {}

    /**
     * @brief Insertion operator for arithmetic types
     *
     * @tparam T Type of value to insert to buffer.
     * @param value The value to insert to buffer.
     *
     * @return Reference to output buffer.
     */
    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicOutputBuffer& operator<<(T value)
    {
        write(value);
        return *this;
    }

    /**
     * @brief Insertion operator for non-arithmetic types
     *
     * @tparam T Type of value to insert to buffer.
     * @param value The value to insert to buffer.
     *
     * @return Reference to output buffer.
     */
    template<typename T, typename std::enable_if<!std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicOutputBuffer& operator<<(T const& value)
    {
        Align();
        value.Serialize(*this);
        return *this;
    }

    /**
     * @brief Insertion operator for string type
     *
     * @tparam T Type of value to insert to buffer.
     * @param value The value to insert to buffer.
     *
     * @return Reference to output buffer.
     */
    BasicOutputBuffer& operator<<(std::string const& value)
    {
        size_t len = value.size() + 1;
        if(put_offset_ + len > capacity_)
        {
            throw holo::exception::BadAllocException();
        }
        std::memcpy(data_ + put_offset_, value.c_str(), len);
        put_offset_ += len;
        size_ = put_offset_ > size_ ? put_offset_ : size_;
        return *this;
    }

    /**
     * @brief Insertion operator for pointer to character type
     *
     * @tparam T Type of value to insert to buffer.
     * @param value The value to insert to buffer.
     *
     * @return Reference to output buffer.
     */
    BasicOutputBuffer& operator<<(holo::char_t const* value)
    {
        size_t len = std::strlen(value) + 1;
        if(put_offset_ + len > capacity_)
        {
            throw holo::exception::BadAllocException();
        }
        std::memcpy(data_ + put_offset_, value, len);
        put_offset_ += len;
        size_ = put_offset_ > size_ ? put_offset_ : size_;
        return *this;
    }

    /**
     * @brief Insertion operator for manipulators
     *
     * @param func function to call
     *
     * @return Reference to *this
     */
    BasicOutputBuffer& operator<<(BasicOutputBuffer& (*func)(BasicOutputBuffer&))
    {
        return func(*this);
    }

    /**
     * @brief Write data from iterator range [start, end);
     *
     * @tparam InputIterator Type of iterator.
     * @param start iterator pointing to first value to insert.
     * @param end iterator pointing to last value to insert.
     *
     * @return Reference to input buffer.
     */
    template<typename InputIterator>
    BasicOutputBuffer& Write(InputIterator start, InputIterator end)
    {
        while(start != end)
        {
            *this << *start++;
        }
        return *this;
    }

    BasicOutputBuffer& Seekp(size_t pos)
    {
        if(pos > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        put_offset_ = pos;
        return *this;
    }

    BasicOutputBuffer& Seekp(ssize_t offset, holo::utils::BasicBuffer::Seekdir dir)
    {
        if(holo::utils::BasicBuffer::beg == dir)
        {
            if( (offset < 0) || (static_cast<size_t>(offset) > size_) )
            {
                throw holo::exception::OutOfRangeException("");
            }
            put_offset_ = static_cast<size_t>(offset);
        }
        else if(holo::utils::BasicBuffer::end == dir)
        {
            if( (offset > 0) || (static_cast<size_t>(-offset) > size_) )
            {
                throw holo::exception::OutOfRangeException("");
            }
            put_offset_ = static_cast<size_t>(offset) + size_;
        }
        else
        {
            if( ((offset >= 0) && (static_cast<size_t>(offset) + put_offset_ > size_)) ||
                ((offset < 0) && (static_cast<size_t>(-offset) > put_offset_)) )
            {
                throw holo::exception::OutOfRangeException("");
            }
            put_offset_ = put_offset_ + static_cast<size_t>(offset);
        }
        return *this;
    }

    size_t Tellp() const
    {
        return put_offset_;
    }

    virtual void Align() = 0;

    size_t GetSize() const noexcept
    {
        return buffer_.GetSize();
    }

protected:
    /**
     * @brief Write char_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(char_t value) = 0;

    /**
     * @brief Write int8_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int8_t value) = 0;

    /**
     * @brief Write uint8_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint8_t value) = 0;

    /**
     * @brief Write int16_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int16_t value) = 0;

    /**
     * @brief Write uint16_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint16_t value) = 0;

    /**
     * @brief Write int32_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int32_t value) = 0;

    /**
     * @brief Write uint32_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint32_t value) = 0;

    /**
     * @brief Write int64_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int64_t value) = 0;

    /**
     * @brief Write uint64_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint64_t value) = 0;

    /**
     * @brief Write float32_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(float32_t value) = 0;

    /**
     * @brief Write float64_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(float64_t value) = 0;

    BasicBuffer& buffer_;

    size_t put_offset_;
};

static inline BasicOutputBuffer& align(BasicOutputBuffer& buf)
{
    buf.Align();
    return buf;
}

} // namespace utils
} // namespace holo

#endif

