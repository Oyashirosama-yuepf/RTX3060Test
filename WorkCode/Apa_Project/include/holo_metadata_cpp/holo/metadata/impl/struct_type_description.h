#ifndef HOLO_METADATA_IMPL_STRUCT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_STRUCT_TYPE_DESCRIPTION_H_

#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionStruct : public TypeDescription
{
public:
    TypeDescriptionStruct(uint32_t align, bool big_endian, std::string const& name)
      : TypeDescription(Type::STRUCT, name, align, big_endian), templates_(), members_()
    {
    }

    TypeDescriptionStruct& SetTemplates(std::vector<TypeDescription::TemplatePair> templates)
    {
        this->templates_ = templates;
        for (auto& t : this->templates_)
        {
            t.second->SetParent(this->shared_from_this());
        }
        return *this;
    }

    TypeDescriptionStruct& SetMembers(std::vector<TypeDescription::MemberPair> members)
    {
        this->members_ = members;
        for (auto& m : this->members_)
        {
            m.second->SetParent(this->shared_from_this());
        }
        return *this;
    }

    std::string GetName() const noexcept override
    {
        std::string name = std::string(type_name_);
        if (!templates_.empty())
        {
            name += "<";
        }
        for (size_t i = 0; i < templates_.size(); ++i)
        {
            name += templates_[i].first;
            if (i < templates_.size() - 1)
            {
                name += ",";
            }
        }
        if (!templates_.empty())
        {
            name += ">";
        }
        return name;
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        std::string value;
        value = std::string(indent, ' ') + GetName() + '\n';
        value += std::string(indent, ' ') + "{" + '\n';
        for (size_t i = 0; i < members_.size(); ++i)
        {
            Type t = members_[i].second->GetType();
            if (t == Type::STRUCT || t == Type::ENUMERATE || t == Type::BITMASK)
            {
                value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + members_[i].first + ":\n";
                value += members_[i].second->PrintToString(indent + 2 * TypeDescription::TAB_SIZE) + '\n';
            }
            else
            {
                value += std::string(indent + TypeDescription::TAB_SIZE, ' ') + members_[i].first + '(' +
                         members_[i].second->GetName() + ')' + '\n';
            }
        }
        value += std::string(indent, ' ') + "}" + '\n';
        return value;
    }

    std::vector<TypeDescription::MemberPair> GetMembers() const noexcept override
    {
        return members_;
    }

    std::vector<TypeDescription::TemplatePair> GetTemplates() const noexcept override
    {
        return templates_;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node = TypeDescription::ToYaml();
        for (size_t i = 0; i < members_.size(); ++i)
        {
            YAML::Node member;
            member["name"]        = members_[i].first;
            member["description"] = members_[i].second->ToYaml();
            node["members"].push_back(member);
        }
        for(size_t i = 0; i < templates_.size(); ++i)
        {
            YAML::Node temp;
            temp["name"] = templates_[i].first;
            temp["description"] = templates_[i].second->ToYaml();
            node["templates"].push_back(temp);
        }
        return node;
    }

private:
    std::vector<TypeDescription::TemplatePair> templates_;
    std::vector<TypeDescription::MemberPair>   members_;
};

}  // namespace metadata
}  // namespace holo

#endif
