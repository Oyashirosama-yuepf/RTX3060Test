#ifndef HOLO_METADATA_IMPL_PRIMITIVE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_PRIMITIVE_TYPE_DESCRIPTION_H_

#include "sequence_type_description.h"

namespace holo
{
namespace metadata
{
struct TypeDescriptionBoolean : TypeDescription
{
    TypeDescriptionBoolean(uint32_t align, bool big_endian)
      : TypeDescription(Type::BOOLEAN, "bool", align > sizeof(bool) ? sizeof(bool) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(bool);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<bool, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionBoolean>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionChar : TypeDescription
{
    TypeDescriptionChar(uint32_t align, bool big_endian)
      : TypeDescription(Type::CHAR, "char", align > sizeof(char) ? sizeof(char) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(char);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<char, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionChar>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionInt8 : TypeDescription
{
    TypeDescriptionInt8(uint32_t align, bool big_endian)
      : TypeDescription(Type::INT8, "int8", align > sizeof(int8_t) ? sizeof(int8_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(int8_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<int8_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionInt8>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionInt16 : TypeDescription
{
    TypeDescriptionInt16(uint32_t align, bool big_endian)
      : TypeDescription(Type::INT16, "int16", align > sizeof(int16_t) ? sizeof(int16_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(int16_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<int16_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionInt16>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionInt32 : TypeDescription
{
    TypeDescriptionInt32(uint32_t align, bool big_endian)
      : TypeDescription(Type::INT32, "int32", align > sizeof(int32_t) ? sizeof(int32_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(int32_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionInt32>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionInt64 : TypeDescription
{
    TypeDescriptionInt64(uint32_t align, bool big_endian)
      : TypeDescription(Type::INT64, "int64", align > sizeof(int64_t) ? sizeof(int64_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(int64_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<int64_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionInt64>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionUint8 : TypeDescription
{
    TypeDescriptionUint8(uint32_t align, bool big_endian)
      : TypeDescription(Type::UINT8, "uint8", align > sizeof(uint8_t) ? sizeof(uint8_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(uint8_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionUint8>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionUint16 : TypeDescription
{
    TypeDescriptionUint16(uint32_t align, bool big_endian)
      : TypeDescription(Type::UINT16, "uint16", align > sizeof(uint16_t) ? sizeof(uint16_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(uint16_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionUint16>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionUint32 : TypeDescription
{
    TypeDescriptionUint32(uint32_t align, bool big_endian)
      : TypeDescription(Type::UINT32, "uint32", align > sizeof(uint32_t) ? sizeof(uint32_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(uint32_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionUint32>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionUint64 : TypeDescription
{
    TypeDescriptionUint64(uint32_t align, bool big_endian)
      : TypeDescription(Type::UINT64, "uint64", align > sizeof(uint64_t) ? sizeof(uint64_t) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(uint64_t);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionUint64>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionFloat32 : TypeDescription
{
    TypeDescriptionFloat32(uint32_t align, bool big_endian)
      : TypeDescription(Type::FLOAT32, "float32", align > sizeof(float) ? sizeof(float) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(float);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<float, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionFloat32>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionFloat64 : TypeDescription
{
    TypeDescriptionFloat64(uint32_t align, bool big_endian)
      : TypeDescription(Type::FLOAT64, "float64", align > sizeof(double) ? sizeof(float) : align, big_endian)
    {
    }

    uint32_t GetSize() const noexcept override
    {
        return sizeof(double);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<double, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionFloat64>(ALIGN, IS_BIG_ENDIAN);
    }
};

struct TypeDescriptionString : TypeDescription
{
    TypeDescriptionString(uint32_t align, bool big_endian) : TypeDescription(Type::STRING, "string", align, big_endian)
    {
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<std::string, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionString>(ALIGN, IS_BIG_ENDIAN);
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<uint8_t*, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return TypeDescriptionResolver<SequenceTag<uint8_t, uint32_t>>::Get();
    }
};

}  // namespace metadata
}  // namespace holo

#endif
