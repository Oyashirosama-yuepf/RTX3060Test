#ifndef HOLO_METADATA_IMPL_BITFIELD_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_BITFIELD_TYPE_DESCRIPTION_H_

#include <string>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionBitfield : public TypeDescription
{
public:
    /**
     * @brief Describe a bit field
     * @details first = (field offset, field width), second = field description
     */
    struct FieldDescription
    {
        FieldDescription(std::string const& name, uint32_t offset, uint32_t width, TypeDescription::PtrType desc)
          : name(name), offset(offset), width(width), desc(desc)
        {
        }

        std::string              name;
        uint32_t                 offset;
        uint32_t                 width;
        TypeDescription::PtrType desc;
    };

    TypeDescriptionBitfield(uint32_t align, bool big_endian, std::string const& name)
      : TypeDescription(Type::BITFIELD, name, align, big_endian), fields_(), underlying_desc_(nullptr)
    {
    }

    TypeDescriptionBitfield& SetFields(std::vector<FieldDescription> const& fields)
    {
        this->fields_ = fields;
        for (auto& f : this->fields_)
        {
            f.desc->SetParent(this->shared_from_this());
        }
        return *this;
    }

    TypeDescriptionBitfield& SetUnderlyingType(TypeDescription::PtrType const& underlying_desc)
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
        return std::string("bitfield") + '<' + type_name_ + ">";
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

    std::vector<FieldDescription> const& GetFields() const noexcept
    {
        return fields_;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value;
        value = std::string(indent, ' ') + GetName() + "(UnderlyingType: " + underlying_desc_->GetName() + ")\n";
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "Field values: " + '\n';
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "{" + '\n';
        for (size_t i = 0; i < fields_.size(); ++i)
        {
            value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + fields_[i].name + " (" +
                     "offset: " + std::to_string(fields_[i].offset) + ", width: " + std::to_string(fields_[i].width) +
                     ')' + '\n';
            value += std::string(indent + TypeDescription::TAB_SIZE * 2, ' ') +
                     fields_[i].desc->PrintToString(indent + TypeDescription::TAB_SIZE * 2);
        }
        value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + "}" + '\n';
        return value;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node = TypeDescription::ToYaml();
        for (size_t i = 0U; i < fields_.size(); ++i)
        {
            YAML::Node field;
            field["name"]        = fields_[i].name;
            field["offset"]      = fields_[i].offset;
            field["width"]       = fields_[i].width;
            field["description"] = fields_[i].desc->ToYaml();
            node["fields"].push_back(field);
        }
        node["underlying_description"] = underlying_desc_->ToYaml();
        return node;
    }

private:
    std::vector<FieldDescription> fields_;
    TypeDescription::PtrType      underlying_desc_;
};

}  // namespace metadata
}  // namespace holo

#endif
