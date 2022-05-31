/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file buffer_serializer.h
 * @brief This header file defines the buffer input/output serializer.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-08
 */
#ifndef HOLO_MAP_ADASIS_BUFFER_SERIALIZER_H_
#define HOLO_MAP_ADASIS_BUFFER_SERIALIZER_H_

#include <holo/map/adasis/serialization/serializer.h>
#include <string.h> // memcpy

#include <vector>

namespace holo
{
namespace map
{
namespace adasis
{
namespace serialization
{
/**
 *  Objects that serialize other objects to a memory buffer
 *  using a standard binary encoding
 */
class BufferSerializer : public Serializer
{
protected:
    inline void WriteRaw(const void* ptr, std::size_t sz)
    {
        std::size_t N = buffer_.size();
        buffer_.resize(N + sz);
        memcpy(&(buffer_[N]), ptr, sz);
    }

public:
    BufferSerializer(uint32_t v = 0) : Serializer(v) {}

    virtual ~BufferSerializer() {}

    void Clear() { buffer_.clear(); }

    const std::vector<uint8_t>& Buffer() const { return buffer_; }
    const uint8_t* BufferAddress() const { return &(buffer_[0]); }
    std::size_t BufferSize() const { return buffer_.size(); }

    std::vector<uint8_t>& Buffer() { return buffer_; }

    uint8_t* BufferAddress() { return &(buffer_[0]); }

protected:
    inline void WriteOne(const int64_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const uint64_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const int32_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const uint32_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const int16_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const uint16_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const int8_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const uint8_t x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const float x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const double x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const long double x) { WriteRaw(&x, sizeof(x)); }
    inline void WriteOne(const bool x) { WriteRaw(&x, sizeof(x)); }

    inline void WriteArray(std::size_t n, const int64_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const uint64_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const int32_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const uint32_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const int16_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const uint16_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const int8_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const uint8_t* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const float* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const double* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const long double* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }
    inline void WriteArray(std::size_t n, const bool* x)
    {
        WriteRaw(x, n * sizeof(*x));
    }

protected:
    std::vector<uint8_t> buffer_;
};

/**
 *  Objects that deserialize other objects from a memory buffer
 *  using a standard binary encoding
 */
class BufferDeserializer : public Deserializer
{
protected:
    inline void ReadRaw(void* ptr, std::size_t sz)
    {
        memcpy(ptr, &(buffer_[cursor_]), sz);
        cursor_ += sz;
    }

public:
    BufferDeserializer(uint32_t v = 0) : Deserializer(v), cursor_(0) {}

    virtual ~BufferDeserializer() {}

    void Clear()
    {
        buffer_.clear();
        cursor_ = 0;
    }

    void Reset() { cursor_ = 0; }

    bool Off() const { return cursor_ >= buffer_.size(); }

    const std::vector<uint8_t>& Buffer() const { return buffer_; }

    const uint8_t* BufferAddress() const { return &(buffer_[0]); }

    const uint8_t* NextReadAddress() const { return &(buffer_[cursor_]); }

    std::size_t BufferSize() const { return buffer_.size(); }

    std::vector<uint8_t>& Buffer() { return buffer_; }

    uint8_t* BufferAddress() { return &(buffer_[0]); }

    uint8_t* NextReadAddress() { return &(buffer_[cursor_]); }

protected:
    inline void ReadOne(int64_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(uint64_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(int32_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(uint32_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(int16_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(uint16_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(int8_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(uint8_t& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(float& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(double& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(long double& x) { ReadRaw(&x, sizeof(x)); }
    inline void ReadOne(bool& x) { ReadRaw(&x, sizeof(x)); }

    inline void ReadArray(std::size_t n, int64_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, uint64_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, int32_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, uint32_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, int16_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, uint16_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, int8_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, uint8_t* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, float* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, double* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, long double* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }
    inline void ReadArray(std::size_t n, bool* x)
    {
        ReadRaw(x, n * sizeof(*x));
    }

protected:
    std::vector<uint8_t> buffer_;
    std::size_t cursor_;
};

} // namespace serialization
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_BUFFER_SERIALIZER_H_ */