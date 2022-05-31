/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file reference_buffer.h
 * @brief This header file defines ReferenceBuffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-3-3
 */

#ifndef HOLO_UTILS_INTERNAL_REFERENCE_BUFFER_H_
#define HOLO_UTILS_INTERNAL_REFERENCE_BUFFER_H_

#include <holo/core/exception.h>
#include <holo/serialization/serialization.h>
#include <cstring>
#include <string>
#include <type_traits>

#include "basic_buffer.h"

namespace holo
{
namespace utils
{
class ReferenceBufferBase
{
public:
    ReferenceBufferBase(BasicBuffer& buffer) : data_(buffer.data_), capacity_(buffer.capacity_), size_(buffer.size_)
    {
    }

    ReferenceBufferBase(ReferenceBufferBase& buffer)
      : data_(buffer.data_), capacity_(buffer.capacity_), size_(buffer.size_)
    {
    }

    ReferenceBufferBase(uint8_t* data, size_t& capacity, size_t& size) : data_(data), capacity_(capacity), size_(size)
    {
    }

    ReferenceBufferBase(ReferenceBufferBase const&) = delete;

    ReferenceBufferBase& operator=(ReferenceBufferBase const&) = delete;

    bool_t operator==(ReferenceBufferBase const& other) const noexcept
    {
        return data_ == other.data_;
    }

    bool_t operator!=(ReferenceBufferBase const& other) const noexcept
    {
        return data_ != other.data_;
    }

    uint8_t const& operator[](size_t index) const noexcept
    {
        return data_[index];
    }

    uint8_t const& At(size_t index) const
    {
        if (!(index < size_))
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_[index];
    }

    uint8_t const* GetData() const noexcept
    {
        return data_;
    }

    size_t GetSize() const noexcept
    {
        return size_;
    }

    size_t GetCapacity() const noexcept
    {
        return capacity_;
    }

    uint8_t const& operator*() const
    {
        if (size_ == 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return *data_;
    }

    uint8_t const* operator+(size_t offset) const
    {
        if (offset >= capacity_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_ + offset;
    }

protected:
    ~ReferenceBufferBase() = default;
    uint8_t* data_;
    size_t&  capacity_;
    size_t&  size_;
};

class ReferenceBuffer : public ReferenceBufferBase
{
public:
    ReferenceBuffer(BasicBuffer& buffer) : ReferenceBufferBase(buffer)
    {
    }

    ReferenceBuffer(ReferenceBufferBase& buffer) : ReferenceBufferBase(buffer)
    {
    }

    ReferenceBuffer(uint8_t* data, size_t& capacity, size_t& size) : ReferenceBufferBase(data, capacity, size)
    {
    }

    ReferenceBuffer(ReferenceBuffer const&) = delete;

    ReferenceBuffer& operator=(ReferenceBuffer const&) = delete;

    uint8_t& operator[](size_t index) noexcept
    {
        return data_[index];
    }

    uint8_t& At(size_t index)
    {
        if (!(index < size_))
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_[index];
    }

    uint8_t* GetData() noexcept
    {
        return data_;
    }

    void SetSize(size_t size) noexcept
    {
        size_ = size > capacity_ ? capacity_ : size;
    }

    uint8_t& operator*()
    {
        if (size_ == 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return *data_;
    }

    uint8_t* operator+(size_t offset)
    {
        if (offset >= capacity_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_ + offset;
    }

protected:
    ~ReferenceBuffer() = default;
};

class ConstReferenceBuffer : public ReferenceBufferBase
{
public:
    ConstReferenceBuffer(BasicBuffer& buffer) : ReferenceBufferBase(buffer)
    {
    }

    ConstReferenceBuffer(ReferenceBufferBase& buffer) : ReferenceBufferBase(buffer)
    {
    }

    ConstReferenceBuffer(uint8_t* data, size_t& capacity, size_t& size) : ReferenceBufferBase(data, capacity, size)
    {
    }

    ConstReferenceBuffer(ReferenceBuffer const&) = delete;

    ConstReferenceBuffer& operator=(ReferenceBuffer const&) = delete;

protected:
    ~ConstReferenceBuffer() = default;
};

class BasicSerializer : public ReferenceBuffer
{
public:
    BasicSerializer(BasicBuffer& buffer) : ReferenceBuffer(buffer), put_offset_(size_)
    {
    }

    BasicSerializer(BasicBuffer& buffer, size_t put_offset)
      : ReferenceBuffer(buffer), put_offset_(put_offset > size_ ? size_ : put_offset)
    {
    }

    BasicSerializer(ReferenceBufferBase& buffer) : ReferenceBuffer(buffer), put_offset_(size_)
    {
    }

    BasicSerializer(ReferenceBufferBase& buffer, size_t put_offset)
      : ReferenceBuffer(buffer), put_offset_(put_offset > size_ ? size_ : put_offset)
    {
    }

    BasicSerializer(uint8_t* data, size_t& capacity, size_t& size)
      : ReferenceBuffer(data, capacity, size), put_offset_(size)
    {
    }

    BasicSerializer(uint8_t* data, size_t& capacity, size_t& size, size_t put_offset)
      : ReferenceBuffer(data, capacity, size), put_offset_(put_offset > size ? size : put_offset)
    {
    }

    BasicSerializer(BasicSerializer const&) = delete;

    BasicSerializer& operator=(BasicSerializer const&) = delete;

    /**
     * @brief Insertion operator for arithmetic types
     *
     * @tparam T Type of value to insert to buffer.
     * @param value The value to insert to buffer.
     *
     * @return Reference to output buffer.
     */
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicSerializer& operator<<(T value)
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
    template <typename T, typename std::enable_if<!std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicSerializer& operator<<(T const& value)
    {
        Align();
        value.Serialize(*this);
        return *this;
    }

    BasicSerializer& operator<<(holo::serialization::manipulator::Align)
    {
        Align();
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
    BasicSerializer& operator<<(std::string const& value)
    {
        size_t len = value.size() + 1;
        if (put_offset_ + len > capacity_)
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
    BasicSerializer& operator<<(holo::char_t const* value)
    {
        size_t len = std::strlen(value) + 1;
        if (put_offset_ + len > capacity_)
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
    BasicSerializer& operator<<(BasicSerializer& (*func)(BasicSerializer&))
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
    template <typename InputIterator>
    BasicSerializer& Write(InputIterator start, InputIterator end)
    {
        while (start != end)
        {
            *this << *start++;
        }
        return *this;
    }

    BasicSerializer& Seekp(size_t pos)
    {
        if (pos > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        put_offset_ = pos;
        return *this;
    }

    BasicSerializer& Seekp(ssize_t offset, holo::utils::BasicBuffer::Seekdir dir)
    {
        if (holo::utils::BasicBuffer::beg == dir)
        {
            if ((offset < 0) || (static_cast<size_t>(offset) > size_))
            {
                throw holo::exception::OutOfRangeException("");
            }
            put_offset_ = static_cast<size_t>(offset);
        }
        else if (holo::utils::BasicBuffer::end == dir)
        {
            if ((offset > 0) || (static_cast<size_t>(-offset) > size_))
            {
                throw holo::exception::OutOfRangeException("");
            }
            put_offset_ = static_cast<size_t>(offset) + size_;
        }
        else
        {
            if (((offset >= 0) && (static_cast<size_t>(offset) + put_offset_ > size_)) ||
                ((offset < 0) && (static_cast<size_t>(-offset) > put_offset_)))
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

    /**
     * @brief Sets the position of next charector to put into buffer.
     */
    virtual void Align() noexcept = 0;

protected:
    /**
     * @brief Write bool_t type data to buffer. Write position should be updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(bool_t value) = 0;

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
     * @brief Write int8_t type data to buffer. Write position should be updated
     * after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int8_t value) = 0;

    /**
     * @brief Write uint8_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint8_t value) = 0;

    /**
     * @brief Write int16_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int16_t value) = 0;

    /**
     * @brief Write uint16_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint16_t value) = 0;

    /**
     * @brief Write int32_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int32_t value) = 0;

    /**
     * @brief Write uint32_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint32_t value) = 0;

    /**
     * @brief Write int64_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(int64_t value) = 0;

    /**
     * @brief Write uint64_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(uint64_t value) = 0;

    /**
     * @brief Write float32_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(float32_t value) = 0;

    /**
     * @brief Write float64_t type data to buffer. Write position should be
     * updated after write.
     *
     * @param value value to write.
     *
     * @throws holo::exception::BadAllocException if output buffer overflows.
     *
     * @exceptsafe Strong.
     */
    virtual void write(float64_t value) = 0;

    size_t put_offset_;
};

class BasicDeserializer : public ConstReferenceBuffer
{
public:
    BasicDeserializer(BasicBuffer& buffer, size_t get_offset = 0)
      : ConstReferenceBuffer(buffer), get_offset_(get_offset > size_ ? size_ : get_offset)
    {
    }

    BasicDeserializer(ReferenceBufferBase& buffer, size_t get_offset = 0)
      : ConstReferenceBuffer(buffer), get_offset_(get_offset > size_ ? size_ : get_offset)
    {
    }

    BasicDeserializer(uint8_t* data, size_t& capacity, size_t& size, size_t get_offset = 0)
      : ConstReferenceBuffer(data, capacity, size), get_offset_(get_offset > size_ ? size_ : get_offset)
    {
    }

    BasicDeserializer(BasicDeserializer const&) = delete;

    BasicDeserializer& operator=(BasicDeserializer const&) = delete;

    /**
     * @brief Extraction operator for arithmetic types
     *
     * @tparam T Type of value to extract from buffer.
     * @param value The value to extract from buffer.
     *
     * @return Reference to basic input buffer.
     */
    template <typename T, typename std::enable_if<std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicDeserializer& operator>>(T& value)
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
    template <typename T, typename std::enable_if<!std::is_arithmetic<T>::value, void>::type* = nullptr>
    BasicDeserializer& operator>>(T& value)
    {
        Align();
        value.Deserialize(*this);
        return *this;
    }

    BasicDeserializer& operator>>(holo::serialization::manipulator::Align)
    {
        Align();
        return *this;
    }

    /**
     * @brief Extraction operator for string type
     *
     * @param value The value to extract from buffer.
     *
     * @return Reference to basic input buffer.
     */
    BasicDeserializer& operator>>(std::string& value)
    {
        size_t end = get_offset_;
        while (end < size_)
        {
            if (data_[end] == 0)
            {
                break;
            }
            ++end;
        }
        if (end == size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        value       = std::string(reinterpret_cast<char_t const*>(data_ + get_offset_));
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
    BasicDeserializer& operator>>(BasicDeserializer& (*func)(BasicDeserializer&))
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
    template <typename InputIterator>
    BasicDeserializer& Read(InputIterator first, InputIterator last)
    {
        while (first < last)
        {
            *this >> *first;
            ++first;
        }
        return *this;
    }

    BasicDeserializer& Skip(size_t size)
    {
        if(get_offset_ + size > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        get_offset_ += size;
        return *this;
    }

    /**
     * @brief Sets the position of the next character to be extracted from the
     * input buffer
     *
     * @param pos Absolute position within the buffer.
     *
     * @return Reference to this basic input buffer.
     */
    BasicDeserializer& Seekg(size_t pos)
    {
        if (pos > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        get_offset_ = pos;
        return *this;
    }

    /**
     * @brief Sets the position of the next character to be extracted from the
     * input buffer
     *
     * @param offset Offset value, relative to the dir parameter.
     * @param dir Object of type holo::utils::BasicBuffer::Seekdir. It may take
     * one of following constant: @n holo::utils::BasicBuffer::beg Beginning of
     * the input buffer. @n holo::utils::BasicBuffer::end End of the input
     * buffer. @n holo::utils::BasicBuffer::cur Current position of the input
     * buffer.
     *
     * @return Reference to this input buffer.
     */
    BasicDeserializer& Seekg(ssize_t offset, holo::utils::BasicBuffer::Seekdir dir)
    {
        if (holo::utils::BasicBuffer::beg == dir)
        {
            if ((offset < 0) || (static_cast<size_t>(offset) > size_))
            {
                throw holo::exception::OutOfRangeException("");
            }
            get_offset_ = static_cast<size_t>(offset);
        }
        else if (holo::utils::BasicBuffer::end == dir)
        {
            if ((offset > 0) || (static_cast<size_t>(-offset) > size_))
            {
                throw holo::exception::OutOfRangeException("");
            }
            get_offset_ = static_cast<size_t>(offset) + size_;
        }
        else
        {
            if (((offset >= 0) && (static_cast<size_t>(offset) + get_offset_ > size_)) ||
                ((offset < 0) && (static_cast<size_t>(-offset) > get_offset_)))
            {
                throw holo::exception::OutOfRangeException("");
            }
            get_offset_ = get_offset_ + static_cast<size_t>(offset);
        }
        return *this;
    }

    /**
     * @brief Gets the position of the next character to be extracted from the
     * input buffer
     *
     * @return Absolute position within the buffer.
     */
    size_t Tellg() const
    {
        return get_offset_;
    }

    size_t GetOffset() const
    {
        return get_offset_;
    }

    /**
     * @brief Sets the position of next character to be extracted from the input
     * buffer to next aligned position.
     */
    virtual void Align() noexcept = 0;

protected:
    /**
     * @brief Read bool_t type data from buffer. Read position should be updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(bool_t& value) const = 0;

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
     * @brief Read int8_t type data from buffer. Read position should be updated
     * after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int8_t& value) const = 0;

    /**
     * @brief Read uint8_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint8_t& value) const = 0;

    /**
     * @brief Read int16_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int16_t& value) const = 0;

    /**
     * @brief Read uint16_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint16_t& value) const = 0;

    /**
     * @brief Read int32_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int32_t& value) const = 0;

    /**
     * @brief Read uint32_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint32_t& value) const = 0;

    /**
     * @brief Read int64_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(int64_t& value) const = 0;

    /**
     * @brief Read uint64_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(uint64_t& value) const = 0;

    /**
     * @brief Read float32_t type data from buffer. Read position should be
     * updated after read.
     *
     * @param value Value to store result.
     *
     * @throws holo::exception::OutOfRangeException if input buffer underflows.
     *
     * @exceptsafe Strong
     */
    virtual void read(float32_t& value) const = 0;

    /**
     * @brief Read float64_t type data from buffer. Read position should be
     * updated after read.
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

static inline BasicSerializer& align(BasicSerializer& ser)
{
    ser.Align();
    return ser;
}

static inline BasicDeserializer& align(BasicDeserializer& des)
{
    des.Align();
    return des;
}

}  // namespace utils
}  // namespace holo

#endif
