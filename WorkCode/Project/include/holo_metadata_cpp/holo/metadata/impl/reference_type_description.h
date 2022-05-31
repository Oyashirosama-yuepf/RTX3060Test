#ifndef HOLO_METADATA_IMPL_REFERENCE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_REFERENCE_TYPE_DESCRIPTION_H_

#include <string>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionTypeReference : public TypeDescription
{
public:
    TypeDescriptionTypeReference(uint32_t align, bool big_endian, uint32_t level, std::string const& name)
      : TypeDescription(Type::TYPE_REFERENCE, "type_reference", align, big_endian), level_(level), name_(name)
    {
    }

    // TODO implement type dereference
    TypeDescription::PtrType GetDereferencedType() override
    {
        return this->shared_from_this();
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node = TypeDescription::ToYaml();
        node["level"]   = this->level_;
        node["path"]    = this->name_;
        return node;
    }

private:
    uint32_t    level_;
    std::string name_;
};

template <uint32_t LEVEL, char const* NAME>
struct TypeReferenceTag
{
};

template <uint32_t LEVEL, char const* NAME, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<TypeReferenceTag<LEVEL, NAME>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionTypeReference>(ALIGN, IS_BIG_ENDIAN, LEVEL, NAME);
    }
};

class TypeDescriptionValueReference : public TypeDescription
{
public:
    TypeDescriptionValueReference(uint32_t align, bool big_endian, uint32_t level, std::string const& name)
      : TypeDescription(Type::VALUE_REFERENCE, "value_reference", align, big_endian), level_(level), name_(name)
    {
    }

    // TODO implement type dereference
    TypeDescription::PtrType GetDereferencedType() override
    {
        return this->shared_from_this();
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node = TypeDescription::ToYaml();
        node["level"]   = this->level_;
        node["path"]    = this->name_;
        return node;
    }

private:
    uint32_t    level_;
    std::string name_;
};

template <uint32_t LEVEL, char const* NAME>
struct ValueReferenceTag
{
};

template <uint32_t LEVEL, char const* NAME, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<ValueReferenceTag<LEVEL, NAME>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return std::make_shared<TypeDescriptionValueReference>(ALIGN, IS_BIG_ENDIAN, LEVEL, NAME);
    }
};

}  // namespace metadata
}  // namespace holo

#endif
