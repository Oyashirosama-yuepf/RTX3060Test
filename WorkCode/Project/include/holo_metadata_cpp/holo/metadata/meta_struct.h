#ifndef HOLO_METADATA_METASTRUCT_H_
#define HOLO_METADATA_METASTRUCT_H_

#include <cstdint>
#include <cstring>
#include <exception>
#include <memory>
#include "type_description.h"
#include "utils/endian.h"

namespace holo
{
namespace metadata
{
class Value
{
public:
    Value() : type(Type::INVALID)
    {
    }

    Value(bool value) : type(Type::BOOLEAN), bool_value(value)
    {
    }

    Value(char value) : type(Type::CHAR), char_value(value)
    {
    }

    Value(int8_t value) : type(Type::INT8), int8_value(value)
    {
    }

    Value(int16_t value) : type(Type::INT16), int16_value(value)
    {
    }

    Value(int32_t value) : type(Type::INT32), int32_value(value)
    {
    }

    Value(int64_t value) : type(Type::INT64), int64_value(value)
    {
    }

    Value(uint8_t value) : type(Type::UINT8), uint8_value(value)
    {
    }

    Value(uint16_t value) : type(Type::UINT16), uint16_value(value)
    {
    }

    Value(uint32_t value) : type(Type::UINT32), uint32_value(value)
    {
    }

    Value(uint64_t value) : type(Type::UINT64), uint64_value(value)
    {
    }

    Value(float value) : type(Type::FLOAT32), float32_value(value)
    {
    }

    Value(double value) : type(Type::FLOAT64), float64_value(value)
    {
    }

    Value& operator=(bool value)
    {
        type       = Type::BOOLEAN;
        bool_value = value;
        return *this;
    }

    Value& operator=(char value)
    {
        type       = Type::CHAR;
        char_value = value;
        return *this;
    }

    Value& operator=(int8_t value)
    {
        type       = Type::INT8;
        int8_value = value;
        return *this;
    }

    Value& operator=(int16_t value)
    {
        type        = Type::INT16;
        int16_value = value;
        return *this;
    }

    Value& operator=(int32_t value)
    {
        type        = Type::INT32;
        int32_value = value;
        return *this;
    }

    Value& operator=(int64_t value)
    {
        type        = Type::INT64;
        int64_value = value;
        return *this;
    }

    Value& operator=(uint8_t value)
    {
        type        = Type::UINT8;
        uint8_value = value;
        return *this;
    }

    Value& operator=(uint16_t value)
    {
        type         = Type::UINT16;
        uint16_value = value;
        return *this;
    }

    Value& operator=(uint32_t value)
    {
        type         = Type::UINT32;
        uint32_value = value;
        return *this;
    }

    Value& operator=(uint64_t value)
    {
        type         = Type::UINT64;
        uint64_value = value;
        return *this;
    }

    Value& operator=(float value)
    {
        type          = Type::FLOAT32;
        float32_value = value;
        return *this;
    }

    Value& operator=(double value)
    {
        type          = Type::FLOAT64;
        float64_value = value;
        return *this;
    }

    bool IsValid() const noexcept
    {
        return type != Type::INVALID;
    }

    template <typename T>
    operator T() const
    {
        switch (type)
        {
            case Type::BOOLEAN:
                return static_cast<T>(bool_value);
            case Type::CHAR:
                return static_cast<T>(char_value);
            case Type::INT8:
                return static_cast<T>(int8_value);
            case Type::INT16:
                return static_cast<T>(int16_value);
            case Type::INT32:
                return static_cast<T>(int32_value);
            case Type::INT64:
                return static_cast<T>(int64_value);
            case Type::UINT8:
                return static_cast<T>(uint8_value);
            case Type::UINT16:
                return static_cast<T>(uint16_value);
            case Type::UINT32:
                return static_cast<T>(uint32_value);
            case Type::UINT64:
                return static_cast<T>(uint64_value);
            case Type::FLOAT32:
                return static_cast<T>(float32_value);
            case Type::FLOAT64:
                return static_cast<T>(float64_value);
            default:
                throw std::runtime_error("Type case not supported");
        }
    }

    Type type;
    union
    {
        bool     bool_value;
        char     char_value;
        int8_t   int8_value;
        uint8_t  uint8_value;
        int16_t  int16_value;
        uint16_t uint16_value;
        int32_t  int32_value;
        uint32_t uint32_value;
        int64_t  int64_value;
        uint64_t uint64_value;
        float    float32_value;
        double   float64_value;
    };
};

class MetaStruct
{
public:
    static size_t const TAB_SIZE = 2U;

    MetaStruct(TypeDescription::PtrType desc, std::string const& name = "")
      : desc(desc), base(nullptr), base_size(0U), offset(0U), members(), name(name)
    {
    }

    virtual size_t Decode(void* base, size_t base_size, size_t offset) = 0;

    virtual std::string GetValueString(size_t indent = 0U) const noexcept = 0;

    virtual std::string PrintToString(size_t indent = 0) const noexcept
    {
        (void)indent;
        return "Not implementated";
    }

    virtual size_t GetElementSize() const noexcept
    {
        return 0U;
    }

    virtual std::shared_ptr<MetaStruct> GetElement(size_t index) const noexcept
    {
        (void)index;
        return nullptr;
    }

    virtual Value GetValue() const noexcept
    {
        return Value();
    }

    std::string GetName() const noexcept
    {
        return name;
    }

    Type GetType() const noexcept
    {
        return desc->GetType();
    }

protected:
    virtual ~MetaStruct()
    {
    }

    size_t align(size_t offset, size_t alignment)
    {
        return (offset + alignment - 1U) & (-alignment);
    }

    TypeDescription::PtrType                 desc;
    void*                                    base;
    size_t                                   base_size;
    size_t                                   offset;
    std::vector<std::shared_ptr<MetaStruct>> members;
    std::string                              name;
};

std::shared_ptr<MetaStruct> CreateMetaStruct(TypeDescription::PtrType desc, std::string const& name = "");

class MetaStructBoolean : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = offset;
        return this->offset + 1U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + (this->getValue() ? "true" : "false") + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    bool getValue() const noexcept
    {
        return *((static_cast<bool*>(this->base) + this->offset));
    }
};

class MetaStructChar : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = offset;
        return this->offset + 1U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::string(1, this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    char getValue() const noexcept
    {
        return *((static_cast<char*>(this->base) + this->offset));
    }
};

class MetaStructInt8 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = offset;
        return this->offset + 1U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    int8_t getValue() const noexcept
    {
        return *((static_cast<int8_t*>(this->base) + this->offset));
    }
};

class MetaStructInt16 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 2U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    int16_t getValue() const noexcept
    {
        int16_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(int16_t));
        return this->desc->IsBigEndian() ? holo::metadata::ntoh16(tmp) : tmp;
    }
};

class MetaStructInt32 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 4U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    int32_t getValue() const noexcept
    {
        int32_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(int32_t));
        return this->desc->IsBigEndian() ? holo::metadata::ntoh32(tmp) : tmp;
    }
};

class MetaStructInt64 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 8U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    int64_t getValue() const noexcept
    {
        int64_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(int64_t));
        return this->desc->IsBigEndian() ? holo::metadata::ntoh64(tmp) : tmp;
    }
};

class MetaStructUint8 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = offset;
        return this->offset + 1U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    int8_t getValue() const noexcept
    {
        return *((static_cast<int8_t*>(this->base) + this->offset));
    }
};

class MetaStructUint16 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 2U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    uint16_t getValue() const noexcept
    {
        uint16_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(uint16_t));
        return this->desc->IsBigEndian() ? holo::metadata::ntoh16(tmp) : tmp;
    }
};

class MetaStructUint32 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 4U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    uint32_t getValue() const noexcept
    {
        uint32_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(uint32_t));
        return this->desc->IsBigEndian() ? holo::metadata::ntoh32(tmp) : tmp;
    }
};

class MetaStructUint64 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 8U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    uint64_t getValue() const noexcept
    {
        uint64_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(uint64_t));
        return this->desc->IsBigEndian() ? holo::metadata::ntoh64(tmp) : tmp;
    }
};

class MetaStructFloat32 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 4U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    float getValue() const noexcept
    {
        uint32_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(uint32_t));
        tmp         = this->desc->IsBigEndian() ? holo::metadata::ntoh32(tmp) : tmp;
        float value = 0;
        std::memcpy(&value, &tmp, sizeof(float));
        return value;
    }
};

class MetaStructFloat64 : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        return this->offset + 8U;
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string("{") + std::to_string(this->getValue()) + std::string("}");
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    Value GetValue() const noexcept override
    {
        return Value(getValue());
    }

private:
    double getValue() const noexcept
    {
        uint64_t tmp = 0;
        std::memcpy(&tmp, static_cast<uint8_t*>(this->base) + this->offset, sizeof(uint64_t));
        tmp          = this->desc->IsBigEndian() ? holo::metadata::ntoh64(tmp) : tmp;
        double value = 0;
        std::memcpy(&value, &tmp, sizeof(double));
        return value;
    }
};

class MetaStructString : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());
        size_t size     = std::strlen(static_cast<char*>(this->base) + this->offset) + 1U;
        return this->align(this->offset + size, this->desc->GetAlignment());
    }

    std::string GetValueString(size_t) const noexcept override
    {
        return std::string(static_cast<char*>(this->base) + this->offset);
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }
};

class MetaStructEnumerate : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        size_t underlying_size = this->desc->GetSize();
        this->base             = base;
        this->base_size        = base_size;
        this->offset           = this->align(offset, this->desc->GetAlignment());
        return this->offset + underlying_size;
    }

    std::string GetValueString(size_t indent) const noexcept override
    {
        std::shared_ptr<MetaStruct> pmeta = CreateMetaStruct(this->desc->GetTemplates()[0].second);
        pmeta->Decode(this->base, this->base_size, this->offset);
        std::string value = pmeta->GetValueString(indent);
        value += "(" + this->getEnumerateString() + ")";
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);

        return value;
    }

private:
    std::string getEnumerateString() const noexcept
    {
        std::shared_ptr<TypeDescriptionEnumerate> enum_desc =
            std::dynamic_pointer_cast<TypeDescriptionEnumerate>(this->desc);
        TypeDescription::PtrType underlying_desc = this->desc->GetTemplates()[0].second;

        auto underlying_meta = CreateMetaStruct(underlying_desc);
        underlying_meta->Decode(this->base, this->base_size, this->offset);
        uint64_t value = underlying_meta->GetValue();

        auto const& enumerates = enum_desc->GetEnumerates();
        for (size_t i = 0; i < enumerates.size(); ++i)
        {
            if (value == enumerates[i].first)
            {
                return enumerates[i].second;
            }
        }
        return "<Unresolved enumerate>";
    }
};

class MetaStructBitmask : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        size_t underlying_size = this->desc->GetSize();
        this->base             = base;
        this->base_size        = base_size;
        this->offset           = this->align(offset, this->desc->GetAlignment());
        return this->offset + underlying_size;
    }

    std::string GetValueString(size_t indent) const noexcept override
    {
        std::shared_ptr<MetaStruct> pmeta = CreateMetaStruct(this->desc->GetTemplates()[0].second);
        pmeta->Decode(this->base, this->base_size, this->offset);
        std::string value        = pmeta->GetValueString(indent);
        auto        flag_strings = this->getBitmaskStrings();
        if (!flag_strings.empty())
        {
            value += "\n";
            value += std::string(indent, ' ') + std::string("{\n");
            for (size_t i = 0; i < flag_strings.size(); ++i)
            {
                value += std::string(indent + MetaStruct::TAB_SIZE, ' ') + flag_strings[i] + "\n";
            }
            value += std::string(indent, ' ') + std::string("}");
        }
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

    std::vector<std::string> getBitmaskStrings() const noexcept
    {
        std::vector<std::string>                flag_strings;
        std::shared_ptr<TypeDescriptionBitmask> bits_desc =
            std::dynamic_pointer_cast<TypeDescriptionBitmask>(this->desc);
        TypeDescription::PtrType underlying_desc = this->desc->GetTemplates()[0].second;

        auto underlying_meta = CreateMetaStruct(underlying_desc);
        underlying_meta->Decode(this->base, this->base_size, this->offset);
        uint64_t value = underlying_meta->GetValue();

        auto const& bits = bits_desc->GetBits();
        for (size_t i = 0; i < bits.size(); ++i)
        {
            if (static_cast<uint64_t>(value) & (1U << bits[i].first))
            {
                flag_strings.push_back(bits[i].second);
            }
        }
        return flag_strings;
    }
};

class MetaStructArray : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base                                     = base;
        this->base_size                                = base_size;
        this->offset                                   = this->align(offset, this->desc->GetAlignment());
        std::shared_ptr<TypeDescriptionArray> arr_desc = std::dynamic_pointer_cast<TypeDescriptionArray>(this->desc);
        size_t                                member_offset = this->offset;
        for (size_t i = 0; i < arr_desc->GetElementSize(); ++i)
        {
            this->members.push_back(CreateMetaStruct(arr_desc->GetTemplates()[0].second));
            member_offset = this->members.back()->Decode(base, base_size, member_offset);
        }
        return this->align(member_offset, this->desc->GetAlignment());
    }
    std::string GetValueString(size_t indent) const noexcept override
    {
        std::string value = "\n";
        value += std::string(indent, ' ') + "{\n";
        for (size_t i = 0U; i < this->members.size(); ++i)
        {
            value += std::string(indent, ' ') + "[" + std::to_string(i) + "]: ";
            value += this->members[i]->GetValueString(indent + MetaStruct::TAB_SIZE) + "\n";
        }
        value += std::string(indent, ' ') + "}";
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }
};

class MetaStructArray2D : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;

    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());

        std::shared_ptr<TypeDescriptionArray2D> arr_desc_ =
            std::dynamic_pointer_cast<TypeDescriptionArray2D>(this->desc);
        size_t member_offset = this->offset;
        for (size_t i = 0; i < arr_desc_->GetRowSize() * arr_desc_->GetColumnSize(); ++i)
        {
            this->members.push_back(CreateMetaStruct(arr_desc_->GetTemplates()[0].second));
            member_offset = this->members.back()->Decode(base, base_size, member_offset);
        }
        return this->align(member_offset, this->desc->GetAlignment());
    }

    std::string GetValueString(size_t indent) const noexcept override
    {
        std::shared_ptr<TypeDescriptionArray2D> arr_desc_ =
            std::dynamic_pointer_cast<TypeDescriptionArray2D>(this->desc);
        std::string value = "\n";
        value += std::string(indent, ' ') + "{\n";

        for (size_t row = 0U; row < arr_desc_->GetRowSize(); ++row)
        {
            for (size_t column = 0U; column < arr_desc_->GetColumnSize(); ++column)
            {
                value +=
                    std::string(indent, ' ') + "[" + std::to_string(row) + "]" + "[" + std::to_string(column) + "]: ";
                value += this->members[arr_desc_->GetElementPosition(row, column)]->GetValueString(
                             indent + MetaStruct::TAB_SIZE) +
                         "\n";
            }
        }

        value += std::string(indent, ' ') + "}";
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }
};

class MetaStructSequence : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());

        std::shared_ptr<TypeDescriptionSequence> seq_desc =
            std::dynamic_pointer_cast<TypeDescriptionSequence>(this->desc);

        size_t element_size = 0U;

        auto size_meta = CreateMetaStruct(seq_desc->GetSizeDescription());

        size_t member_offset = size_meta->Decode(base, base_size, this->offset);
        member_offset        = this->align(member_offset, this->desc->GetAlignment());
        element_size         = size_meta->GetValue();

        for (size_t i = 0; i < element_size; ++i)
        {
            this->members.push_back(CreateMetaStruct(seq_desc->GetTemplates()[0U].second));
            member_offset = this->members.back()->Decode(base, base_size, member_offset);
        }
        return this->align(member_offset, this->desc->GetAlignment());
    }

    std::string GetValueString(size_t indent) const noexcept override
    {
        std::string value = "\n";
        value += std::string(indent, ' ') + "{\n";
        value += std::string(indent, ' ') + "size: " + std::to_string(this->members.size()) + "\n";
        for (size_t i = 0U; i < this->members.size(); ++i)
        {
            value += std::string(indent, ' ') + "[" + std::to_string(i) + "]: ";
            value += this->members[i]->GetValueString(indent + MetaStruct::TAB_SIZE) + "\n";
        }
        value += std::string(indent, ' ') + "}";
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }
};

class MetaStructSequence2D : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());

        std::shared_ptr<TypeDescriptionSequence2D> seq_desc =
            std::dynamic_pointer_cast<TypeDescriptionSequence2D>(this->desc);
        tag_ = seq_desc->GetTag();

        size_t element_row_size = 0U;
        auto   row_size_meta    = CreateMetaStruct(seq_desc->GetRowSizeDescription());
        size_t member_offset    = row_size_meta->Decode(base, base_size, this->offset);
        member_offset           = this->align(member_offset, this->desc->GetAlignment());
        element_row_size        = row_size_meta->GetValue();
        size_record_.push_back(element_row_size);

        for (size_t i = 0; i < element_row_size; ++i)
        {
            size_t element_column_size = 0U;
            auto   column_size_meta    = CreateMetaStruct(seq_desc->GetColumnSizeDescription());
            member_offset              = column_size_meta->Decode(base, base_size, member_offset);
            member_offset              = this->align(member_offset, this->desc->GetAlignment());
            element_column_size        = column_size_meta->GetValue();
            size_record_.push_back(element_column_size);

            for (size_t i = 0; i < element_column_size; ++i)
            {
                this->members.push_back(CreateMetaStruct(seq_desc->GetTemplates()[0U].second));
                member_offset = this->members.back()->Decode(base, base_size, member_offset);
            }
        }
        return this->align(member_offset, this->desc->GetAlignment());
    }

    std::string GetValueString(size_t indent) const noexcept override
    {
        std::string value = "\n";
        value += std::string(indent, ' ') + "{\n";

        for (size_t i = 0; i < size_record_.size() - 1; i++)
        {
            value += std::string(indent, ' ') + "size: " + std::to_string(size_record_.at(i + 1)) + "\n";
            for (size_t j = 0U; j < size_record_.at(i + 1); j++)
            {
                if (tag_ == TypeDescriptionSequence2D::RowMajorTag::VALUE)
                {
                    value += std::string(indent, ' ') + "[" + std::to_string(i) + "]" + "[" + std::to_string(j) + "]: ";
                    value +=
                        this->members[this->GetElementPosition(i, j)]->GetValueString(indent + MetaStruct::TAB_SIZE) +
                        "\n";
                }
                else
                {
                    value += std::string(indent, ' ') + "[" + std::to_string(j) + "]" + "[" + std::to_string(i) + "]: ";
                    value +=
                        this->members[this->GetElementPosition(i, j)]->GetValueString(indent + MetaStruct::TAB_SIZE) +
                        "\n";
                }
            }
        }

        value += std::string(indent, ' ') + "}";
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }

private:
    uint32_t GetElementPosition(uint32_t x, uint32_t y) const noexcept
    {
        uint32_t value = 0U;
        for (size_t i = 0; i < x; i++)
        {
            value += size_record_[i + 1];
        }
        value += y;
        return value;
    }

    std::vector<size_t> size_record_;
    uint32_t            tag_;
};

class MetaStructStruct : public MetaStruct
{
public:
    using MetaStruct::MetaStruct;
    size_t Decode(void* base, size_t base_size, size_t offset) override
    {
        this->base      = base;
        this->base_size = base_size;
        this->offset    = this->align(offset, this->desc->GetAlignment());

        size_t member_offset = this->offset;

        auto struct_members = this->desc->GetMembers();

        for (size_t i = 0; i < struct_members.size(); ++i)
        {
            this->members.push_back(CreateMetaStruct(struct_members[i].second, struct_members[i].first));
            member_offset = this->members.back()->Decode(base, base_size, member_offset);
        }
        return this->align(member_offset, this->desc->GetAlignment());
    }

    std::string GetValueString(size_t indent) const noexcept override
    {
        std::string value = "\n";
        value += std::string(indent, ' ') + "{\n";
        auto members_desc = this->desc->GetMembers();
        for (size_t i = 0U; i < this->members.size(); ++i)
        {
            value += std::string(indent + MetaStruct::TAB_SIZE, ' ') + members_desc[i].first + ": ";
            value += members_desc[i].second->GetName();
            value += this->members[i]->GetValueString(indent + MetaStruct::TAB_SIZE);
            value += "\n";
        }
        value += std::string(indent, ' ') + "}\n";
        return value;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value = std::string(indent, ' ') + this->desc->GetName();
        value += this->GetValueString(indent);
        return value;
    }
};

std::shared_ptr<MetaStruct> CreateMetaStruct(TypeDescription::PtrType desc, std::string const& name)
{
    switch (desc->GetType())
    {
        case Type::BOOLEAN:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructBoolean>(desc, name));
        case Type::CHAR:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructChar>(desc, name));
        case Type::INT8:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructInt8>(desc, name));
        case Type::INT16:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructInt16>(desc, name));
        case Type::INT32:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructInt32>(desc, name));
        case Type::INT64:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructInt64>(desc, name));
        case Type::UINT8:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructUint8>(desc, name));
        case Type::UINT16:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructUint16>(desc, name));
        case Type::UINT32:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructUint32>(desc, name));
        case Type::UINT64:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructUint64>(desc, name));
        case Type::FLOAT32:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructFloat32>(desc, name));
        case Type::FLOAT64:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructFloat64>(desc, name));
        case Type::ENUMERATE:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructEnumerate>(desc, name));
        case Type::BITMASK:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructBitmask>(desc, name));
        case Type::ARRAY:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructArray>(desc, name));
        case Type::ARRAY2D:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructArray2D>(desc, name));
        case Type::SEQUENCE:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructSequence>(desc, name));
        case Type::SEQUENCE2D:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructSequence2D>(desc, name));
        case Type::STRUCT:
            return std::static_pointer_cast<MetaStruct>(std::make_shared<MetaStructStruct>(desc, name));
        default:
            throw std::runtime_error("Unrecognized type description type");
    }
}
}  // namespace metadata
}  // namespace holo

#endif
