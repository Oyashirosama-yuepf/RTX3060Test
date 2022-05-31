/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file input_buffer.h
 * @brief This header file defines InputBuffer object.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-1-15
 */

#ifndef HOLO_UTILS_INPUT_BUFFER_H_
#define HOLO_UTILS_INPUT_BUFFER_H_

#include <cstring>
#include <type_traits>

#include <holo/core/exception.h>
#include <holo/utils/internal/reference_buffer.h>

namespace holo
{
namespace utils
{

/**
 * @brief InputBuffer object is used to access data in BasicBuffer object.
 */
class InputBuffer: public BasicDeserializer
{
public:
    using BasicDeserializer::BasicDeserializer;

    void Align() const override
    {}

protected:

    void read(char_t& value) const override
    {
        readArithmetic(value);
    }

    void read(int8_t& value) const override
    {
        readArithmetic(value);
    }

    void read(uint8_t& value) const override
    {
        readArithmetic(value);
    }

    void read(int16_t& value) const override
    {
        readArithmetic(value);
    }

    void read(uint16_t& value) const override
    {
        readArithmetic(value);
    }

    void read(int32_t& value) const override
    {
        readArithmetic(value);
    }

    void read(uint32_t& value) const override
    {
        readArithmetic(value);
    }

    void read(int64_t& value) const override
    {
        readArithmetic(value);
    }

    void read(uint64_t& value) const override
    {
        readArithmetic(value);
    }

    void read(float32_t& value) const override
    {
        readArithmetic(value);
    }

    void read(float64_t& value) const override
    {
        readArithmetic(value);
    }

private:

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && sizeof(T) != 1, void>::type* = nullptr>
    void readArithmetic(T& value) const
    {
        if(get_offset_ + sizeof(T) > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        std::memcpy(&value, data_ + get_offset_, sizeof(T));
        get_offset_ += sizeof(T);
    }

    template<typename T, typename std::enable_if<std::is_arithmetic<T>::value && sizeof(T) == 1, void>::type* = nullptr>
    void readArithmetic(T& value) const
    {
        if(get_offset_ + sizeof(T) > size_)
        {
            throw holo::exception::OutOfRangeException("");
        }
        value = static_cast<T>(data_[get_offset_++]);
    }
};


} // namespace utils
} // namespace holo

#endif

