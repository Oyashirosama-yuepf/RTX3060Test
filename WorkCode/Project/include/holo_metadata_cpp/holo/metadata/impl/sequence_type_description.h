#ifndef HOLO_METADATA_IMPL_SEQUENCE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_SEQUENCE_TYPE_DESCRIPTION_H_

#include <vector>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionSequence : public TypeDescription
{
public:
    TypeDescriptionSequence(uint32_t align, bool big_endian)
      : TypeDescription(Type::SEQUENCE, "sequence", align, big_endian), size_desc_(nullptr), element_desc_(nullptr)
    {
    }

    TypeDescriptionSequence& SetSize(TypeDescription::PtrType const& size_desc)
    {
        this->size_desc_ = size_desc;
        this->size_desc_->SetParent(this->shared_from_this());
        return *this;
    }

    TypeDescriptionSequence& SetElementType(TypeDescription::PtrType const& element_desc)
    {
        this->element_desc_ = element_desc;
        this->element_desc_->SetParent(this->shared_from_this());
        return *this;
    }

    std::string GetName() const noexcept override
    {
        return std::string(type_name_) + '<' + element_desc_->GetName() + ">";
    }

    std::vector<TypeDescription::MemberPair> GetMembers() const noexcept override
    {
        return {};
    }

    std::vector<TypeDescription::TemplatePair> GetTemplates() const noexcept override
    {
        return {{"ElementType", element_desc_}};
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        return std::string(indent, ' ') + GetName();
    }

    TypeDescription::PtrType GetSizeDescription() const noexcept
    {
        return size_desc_;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node             = TypeDescription::ToYaml();
        node["size_description"]    = size_desc_->ToYaml();
        node["element_description"] = element_desc_->ToYaml();
        return node;
    }

protected:
    TypeDescription::PtrType size_desc_;
    TypeDescription::PtrType element_desc_;
};

template <typename T, typename S = uint32_t>
struct SequenceTag
{
};

template <typename T, typename S, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<SequenceTag<T, S>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        desc->SetSize(TypeDescriptionResolver<S, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
