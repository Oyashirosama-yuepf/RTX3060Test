#ifndef HOLO_METADATA_IMPL_ARRAY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_ARRAY_TYPE_DESCRIPTION_H_

#include <array>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionArray : public TypeDescription
{
public:
    TypeDescriptionArray(uint32_t align, bool big_endian)
      : TypeDescription(Type::ARRAY, "array", align, big_endian), element_size_(0U), element_desc_(nullptr)
    {
    }

    TypeDescriptionArray& SetSize(uint32_t element_size)
    {
        this->element_size_ = element_size;
        return *this;
    }

    TypeDescriptionArray& SetElementType(TypeDescription::PtrType const& element_desc)
    {
        this->element_desc_ = element_desc;
        this->element_desc_->SetParent(this->shared_from_this());
        return *this;
    }

    std::string GetName() const noexcept override
    {
        return std::string(type_name_) + '<' + element_desc_->GetName() + ',' + std::to_string(element_size_) + ">";
    }

    std::vector<TypeDescription::MemberPair> GetMembers() const noexcept override
    {
        return {};
    }

    std::vector<TypeDescription::TemplatePair> GetTemplates() const noexcept override
    {
        return {{"", element_desc_}};
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        return std::string(indent, ' ') + GetName();
    }

    uint32_t GetElementSize() const noexcept
    {
        return element_size_;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node             = TypeDescription::ToYaml();
        node["element_size"]        = element_size_;
        node["element_description"] = element_desc_->ToYaml();
        return node;
    }

private:
    uint32_t                 element_size_;
    TypeDescription::PtrType element_desc_;
};

template <typename T, size_t S>
struct ArrayTag
{
};

template <typename T, size_t S, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<ArrayTag<T, S>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionArray>(ALIGN, IS_BIG_ENDIAN);
        desc->SetSize(S).SetElementType(TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
