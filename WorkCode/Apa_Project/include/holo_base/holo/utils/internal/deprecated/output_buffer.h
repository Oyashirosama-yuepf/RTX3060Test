/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file output_buffer.h
 * @brief This header file defines OutputBuffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-7
 */

#ifndef HOLO_UTILS_OUTPUT_BUFFER_H_
#define HOLO_UTILS_OUTPUT_BUFFER_H_

#include <cstring>
#include <type_traits>

#include <holo/core/exception.h>
#include <holo/utils/internal/reference_buffer.h>

namespace holo
{
namespace utils
{

/**
 * @brief The OutputBuffer object is used to modify the content of a BasicBuffer.
 */
class OutputBuffer: public BasicSerializer
{
public:
    using BasicSerializer::BasicSerializer

    void Align() override
    {}

protected:

    void write(char_t value) override
    {
        writeInternal(value);
    }

    void write(int8_t value) override
    {
        writeInternal(value);
    }

    void write(uint8_t value) override
    {
        writeInternal(value);
    }

    void write(int16_t value) override
    {
        writeInternal(value);
    }

    void write(uint16_t value) override
    {
        writeInternal(value);
    }

    void write(int32_t value) override
    {
        writeInternal(value);
    }

    void write(uint32_t value) override
    {
        writeInternal(value);
    }

    void write(int64_t value) override
    {
        writeInternal(value);
    }

    void write(uint64_t value) override
    {
        writeInternal(value);
    }

    void write(float32_t value) override
    {
        writeInternal(value);
    }

    void write(float64_t value) override
    {
        writeInternal(value);
    }

private:
    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && sizeof(T) != 1, void>::type* = nullptr>
    void writeInternal(T value)
    {
        if(put_offset_ + sizeof(T) > capacity_)
        {
            throw holo::exception::BadAllocException();
        }
        std::memcpy(data_ + put_offset_, &value, sizeof(T));
        put_offset_ += sizeof(T);
        size_ = put_offset_ > size_ ? put_offset_ : size_;
    }

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && sizeof(T) == 1, void>::type* = nullptr>
    void writeInternal(T value)
    {
        if(put_offset_ + sizeof(T) > capacity_)
        {
            throw holo::exception::BadAllocException();
        }
        data_[put_offset_++] = static_cast<uint8_t>(value);
        size_ = put_offset_ > size_ ? put_offset_ : size_;
    }
};

} // namespace utils
} // namespace holo

#endif

