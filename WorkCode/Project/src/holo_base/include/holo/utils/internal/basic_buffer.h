/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file basic_buffer.h
 * @brief This header file defines BasicBuffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-15
 */

#ifndef HOLO_UTILS_INTERNAL_BASIC_BUFFER_H_
#define HOLO_UTILS_INTERNAL_BASIC_BUFFER_H_

#include <holo/container/list.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>

#include <cstring>

namespace holo
{
namespace utils
{
/**
 * @brief The BasicBuffer object is the base class for all buffers. It defines basic operations to a buffer.
 *
 * @details Basic buffer object stores basic information about a memory block.
 * Including the start address of a memory block, capacity of the memory block and size of data stored in the memory
 * block.
 *
 * Basic buffer object acts like a read-only raw pointer. It shall not modify the content of a memory block.
 * Memory block can only be modified through OutputBuffer.
 *
 * Basic buffer can only be created through its derived classes because the constructors are not public.
 */
class BasicBuffer
{
public:
    enum class Seekdir
    {
        BEG = 0x01,
        END = 0x02,
        CUR = 0x03,
    };

    static Seekdir constexpr beg = Seekdir::BEG;
    static Seekdir constexpr end = Seekdir::END;
    static Seekdir constexpr cur = Seekdir::CUR;

    /**
     * @brief Check if the content of two buffers are same.
     *
     * @param other The other buffer.
     *
     * @return true if the contents are the same. Otherwise false.
     *
     * @exceptsafe No throw.
     */
    bool_t operator==(BasicBuffer const& other) const noexcept
    {
        if (other.size_ != size_)
        {
            return false;
        }
        return std::memcmp(data_, other.data_, size_) == 0;
    }

    /**
     * @brief Check if the content of two buffers are different.
     *
     * @param other The other buffer.
     *
     * @return true if the contents are different. Otherwise false.
     *
     * @exceptsafe No throw.
     */
    bool_t operator!=(BasicBuffer const& other) const noexcept
    {
        return !(*this == other);
    }

    /**
     * @brief Get reference to the byte at specific position without bounds check.
     *
     * @param index position of the byte.
     *
     * @return Reference to the byte.
     *
     * @exceptsafe No throw.
     *
     * @note The behaviour is undefined if index out of buffer capacity range.
     */
    uint8_t const& operator[](size_t index) const noexcept
    {
        return data_[index];
    }

    uint8_t& operator[](size_t index) noexcept
    {
        return data_[index];
    }

    /**
     * @brief Get reference to the byte at specific position with bounds check.
     *
     * @param index position of the byte.
     *
     * @return Reference to the byte.
     *
     * @throws holo::exception::OutOfRangeException if index >= buffer size.
     *
     * @exceptsafe Strong.
     */
    uint8_t const& At(size_t index) const
    {
        if (!(index < size_))
        {
            throw holo::exception::OutOfRangeException("");
        }
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

    /**
     * @brief Get start address of underlying memory block.
     *
     * @return Start address of memory block.
     *
     * @exceptsafe No throw.
     */
    uint8_t const* GetData() const noexcept
    {
        return data_;
    }

    uint8_t* GetData() noexcept
    {
        return data_;
    }

    /**
     * @brief Get number of bytes store in this memory block.
     *
     * @return Number of bytes store in this memory block.
     *
     * @exceptsafe No throw.
     */
    size_t GetSize() const noexcept
    {
        return size_;
    }

    void SetSize(size_t size) noexcept
    {
        size_ = size > capacity_ ? capacity_ : size;
    }

    /**
     * @brief Get max number of bytes this memory block can store.
     *
     * @return Max number of bytes this memory block can store.
     *
     * @exceptsafe No throw.
     */
    size_t GetCapacity() const noexcept
    {
        return capacity_;
    }

    /**
     * @brief Get reference to the first byte of this memory block.
     *
     * @details This overloaded operator will make BasicBuffer acts like a raw pointer.
     *
     * @return Reference to the first byte.
     *
     * @throws holo::exception::OutofRangeException is the memory block is empty.
     *
     * @exceptsafe Strong.
     */
    uint8_t const& operator*() const
    {
        if (size_ == 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return *data_;
    }

    uint8_t& operator*()
    {
        if (size_ == 0)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return *data_;
    }

    /**
     * @brief Get a new buffer from this buffer + offset.
     *
     * @details This overloaded operator will make BasicBuffer acts like a raw pointer.
     *
     * @param offset offset from this buffer.
     *
     * @return A new buffer.
     *
     * @throws holo::exception::BadAllocException if offset >= buffer capacity.
     */
    uint8_t const* operator+(size_t offset) const
    {
        if (offset >= capacity_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_ + offset;
    }

    uint8_t* operator+(size_t offset)
    {
        if (offset >= capacity_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        return data_ + offset;
    }

    friend class ReferenceBufferBase;

protected:
    /**
     * @brief Construct from raw memory block
     *
     * @param data The start address of the memory block.
     * @param capacity The max size of the memory block.
     * @param size Number of bytes store in the memory block.
     *
     * @exceptsafe Strong.
     */
    BasicBuffer(uint8_t* data, size_t capacity, size_t size = 0)
      : data_(data), capacity_(capacity), size_(size > capacity ? capacity : size)
    {
    }

    BasicBuffer(BasicBuffer const&) = delete;

    BasicBuffer& operator=(BasicBuffer&) = delete;

    ~BasicBuffer() noexcept = default;

    uint8_t* data_;      ///< start address of raw memory block.
    size_t   capacity_;  ///< max number of bytes of memory block.
    size_t   size_;      ///< number of bytes store in the memory block.
};

}  // namespace utils
}  // namespace holo

#endif
