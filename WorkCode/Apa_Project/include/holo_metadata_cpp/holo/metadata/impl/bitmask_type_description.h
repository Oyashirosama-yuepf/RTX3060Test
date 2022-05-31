#ifndef HOLO_METADATA_IMPL_BITMASK_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_BITMASK_TYPE_DESCRIPTION_H_

#include <string>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionBitmask : public TypeDescription
{
public:
    TypeDescriptionBitmask(uint32_t align, bool big_endian, std::string const& name)
      : TypeDescription(Type::BITMASK, name, align, big_endian), bits_({}), underlying_desc_(nullptr)
    {
    }

    TypeDescriptionBitmask& SetBits(std::vector<std::pair<uint32_t, std::string>> const& bits)
    {
        this->bits_ = bits;
        return *this;
    }

    TypeDescriptionBitmask& SetUnderlyingType(TypeDescription::PtrType const& underlying_desc)
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
        return std::string("bitmask") + '<' + type_name_ + ">";
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

    std::vector<std::pair<uint32_t, std::string>> const& GetBits() const noexcept
    {
        return bits_;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value;
        value = std::string(indent, ' ') + GetName() + "(UnderlyingType: " + underlying_desc_->GetName() + ")\n";
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "Bit values: " + '\n';
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "{" + '\n';
        for (size_t i = 0; i < bits_.size(); ++i)
        {
            value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + std::to_string(bits_[i].first) + " (" +
                     bits_[i].second + ')' + '\n';
        }
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "}" + '\n';
        return value;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node = TypeDescription::ToYaml();
        for (size_t i = 0U; i < bits_.size(); ++i)
        {
            YAML::Node bit;
            bit["offset"] = bits_[i].first;
            bit["name"]   = bits_[i].second;
            node["bits"].push_back(bit);
        }
        node["underlying_description"] = underlying_desc_->ToYaml();
        return node;
    }

private:
    std::vector<std::pair<uint32_t, std::string>> bits_;
    TypeDescription::PtrType                      underlying_desc_;
};

}  // namespace metadata
}  // namespace holo

#endif
