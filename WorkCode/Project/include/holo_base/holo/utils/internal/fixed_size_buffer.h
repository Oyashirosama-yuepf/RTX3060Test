/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file buffer.h
 * @brief This header file defines buffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-7
 */

#ifndef HOLO_UTILS_INTERNAL_FIXED_SIZE_BUFFER_H_
#define HOLO_UTILS_INTERNAL_FIXED_SIZE_BUFFER_H_

#include <algorithm>

#include <holo/core/types.h>
#include <holo/core/exception.h>
#include "basic_buffer.h"

namespace holo
{
namespace utils
{

/**
 * @brief FixedSizeBuffer object.
 *
 * @tparam N Capacity of the buffer
 * @tparam Alignment Alignment of memory block.
 */
template<size_t N, size_t Alignment = 1U>
class FixedSizeBuffer: public BasicBuffer
{
public:
    /**
     * @brief Default contructor.
     */
    FixedSizeBuffer() noexcept:
        BasicBuffer{nullptr, N, 0},
        raw_ptr_{new uint8_t[N + Alignment - 1]}
    {
        data_ = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(raw_ptr_) - 1 + Alignment) & (-Alignment));
    }

    /**
     * @brief Copy constructor. Will copy the content from the other FixedSizeBuffer object.
     *
     * @param other The other FixedSizeBuffer object.
     *
     * @throws holo::exception::BadAllocException if number of existing buffer exceeded BasicBuffer::MAX_BUFFER_NUMBER
     *
     * @exceptsafe Strong.
     */
    FixedSizeBuffer(FixedSizeBuffer const& other):
        BasicBuffer{nullptr, N, other.size_},
        raw_ptr_{new uint8_t[N + Alignment - 1]}
    {
        data_ = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(raw_ptr_) - 1 + Alignment) & (-Alignment));
        std::memcpy(data_, other.data_, size_);
    }

    FixedSizeBuffer(FixedSizeBuffer&& other):
        BasicBuffer{other.data_, N, other.size_},
        raw_ptr_{other.raw_ptr_}
    {
        other.raw_ptr_ = nullptr;
    }

    FixedSizeBuffer operator=(FixedSizeBuffer const& other)
    {
        size_ = other.size_;
        memcpy(data_, other.data_, other.size_);
        return *this;
    }

    FixedSizeBuffer operator=(FixedSizeBuffer&& other)
    {
        uint8_t* tmp = raw_ptr_;
        raw_ptr_ = other.raw_ptr_;
        other.raw_ptr_ = tmp;

        tmp = data_;
        data_ = other.data_;
        other.data_ = tmp;

        size_ = other.size_;
        other.size_ = 0;
        return *this;
    }

    ~FixedSizeBuffer()
    {
        if(raw_ptr_)
        {
            delete[] raw_ptr_;
        }
    }

    /**
     * @brief Construct from other type of FixedSizeBuffer object.
     *
     * @details If size of other FixedSizeBuffer is greater than the capacity of this buffer. Data will be truncated.
     *
     * @tparam InputCapacity Input FixedSizeBuffer capacity value.
     * @param other The other FixedSizeBuffer object.
     *
     * @throws holo::exception::BadAllocException if number of existing buffer exceeded BasicBuffer::MAX_BUFFER_NUMBER
     *
     * @exceptsafe Strong.
     */
    template<size_t InputCapacity>
    FixedSizeBuffer(FixedSizeBuffer<InputCapacity> const& other) noexcept:
        BasicBuffer{nullptr, N, other.GetSize() > N ? N : other.GetSize()},
        raw_ptr_(new uint8_t[N - 1 + Alignment])
    {
        data_ = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(raw_ptr_) - 1 + Alignment) & (-Alignment));
        std::memcpy(data_, other.GetData(), size_);
    }

    /**
     * @brief Construct from initializer list
     *
     * @param iList initializer_list
     *
     * @throws holo::exception::BadAllocException if number of existing buffer exceeded BasicBuffer::MAX_BUFFER_NUMBER
     *
     * @exceptsafe Strong.
     */
    FixedSizeBuffer(std::initializer_list<uint8_t> iList):
        BasicBuffer{nullptr, N, iList.size() > N ? N : iList.size()},
        raw_ptr_(new uint8_t[N - 1 + Alignment])
    {
        data_ = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(raw_ptr_) - 1 + Alignment) & (-Alignment));
        std::copy(iList.begin(), iList.begin() + size_, data_);
    }

private:
    uint8_t* raw_ptr_;
};

} // namespace utils
} // namespace holo

#endif

