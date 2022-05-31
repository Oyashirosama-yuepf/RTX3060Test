/**
 * @brief This header file defines exceptions for serialization and deserialization operations.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date Oct 30, 2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <stdexcept>

#ifndef HOLO_UTILS_SERIALIZATION_EXCEPTION_H_
#define HOLO_UTILS_SERIALIZATION_EXCEPTION_H_

namespace holo
{

namespace exception
{

class SerializationBufferOverflowException: public std::exception
{
public:
    SerializationBufferOverflowException(uint32_t serialized_size) noexcept : serialized_size_(serialized_size)
    {}

    uint32_t GetSize() const noexcept
    {
        return serialized_size_;
    }

    void SetSize(uint32_t size) noexcept
    {
        serialized_size_ = size;
    }

private:
    uint32_t serialized_size_;
};

class DeserializationBufferUnderflowException: public std::exception
{
public:
    DeserializationBufferUnderflowException(uint32_t deserialized_size) noexcept: deserialized_size_(deserialized_size)
    {}

    uint32_t GetSize() const noexcept
    {
        return deserialized_size_;
    }

    void SetSize(uint32_t size) noexcept
    {
        deserialized_size_ = size;
    }

private:
    uint32_t deserialized_size_;
};


} /* namespace exception */

} /* namespace holo */

#endif

