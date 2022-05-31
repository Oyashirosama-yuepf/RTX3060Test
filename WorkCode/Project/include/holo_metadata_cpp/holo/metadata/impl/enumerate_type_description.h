#ifndef HOLO_METADATA_IMPL_ENUMERATE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_ENUMERATE_TYPE_DESCRIPTION_H_

#include <string>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionEnumerate : public TypeDescription
{
public:
    TypeDescriptionEnumerate(uint32_t align, bool big_endian, std::string const& name)
      : TypeDescription(Type::ENUMERATE, name, align, big_endian)
      , enumerates_()
      , underlying_desc_(nullptr)
    {
    }

    TypeDescriptionEnumerate& SetEnumerates(std::vector<std::pair<uint64_t, std::string>> const& enumerates)
    {
        this->enumerates_ = enumerates;
        return *this;
    }

    TypeDescriptionEnumerate& SetUnderlyingType(TypeDescription::PtrType const& underlying_desc)
    {
        this->underlying_desc_ = underlying_desc;
        this->underlying_desc_->SetParent(this->shared_from_this());
        return *this;
    }

    uint32_t GetSize() const noexcept override
    {
        return this->underlying_desc_->GetSize();
    }

    std::string GetName() const noexcept override
    {
        return std::string("enum") + '<' + type_name_ + ">";
    }

    uint32_t GetAlignment() const noexcept override
    {
        return this->underlying_desc_->GetAlignment();
    }

    std::vector<TypeDescription::MemberPair> GetMembers() const noexcept override
    {
        return {};
    }

    std::vector<TypeDescription::TemplatePair> GetTemplates() const noexcept override
    {
        return {{"", underlying_desc_}};
    }

    std::vector<std::pair<uint64_t, std::string>> const& GetEnumerates() const noexcept
    {
        return enumerates_;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value;
        value = std::string(indent, ' ') + GetName() + "(UnderlyingType: " + underlying_desc_->GetName() + ")\n";
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "Valid values: " + '\n';
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "{" + '\n';
        for (size_t i = 0; i < enumerates_.size(); ++i)
        {
            value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + std::to_string(enumerates_[i].first) +
                     " (" + enumerates_[i].second + ')' + '\n';
        }
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "}" + '\n';
        return value;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node = TypeDescription::ToYaml();
        for (size_t i = 0U; i < enumerates_.size(); ++i)
        {
            YAML::Node enumerate;
            enumerate["value"] = enumerates_[i].first;
            enumerate["name"]  = enumerates_[i].second;
            node["enumerates"].push_back(enumerate);
        }
        node["underlying_description"] = underlying_desc_->ToYaml();
        return node;
    }

protected:
    std::vector<std::pair<uint64_t, std::string>> enumerates_;
    TypeDescription::PtrType                      underlying_desc_;
};

}  // namespace metadata
}  // namespace holo

#endif
