#ifndef HOLO_METADATA_IMPL_SEQUENCE2D_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_SEQUENCE2D_TYPE_DESCRIPTION_H_

#include <vector>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionSequence2D : public TypeDescription
{
public:
    struct RowMajorTag
    {
        static uint32_t const VALUE = 0U;
    };

    struct ColumnMajorTag
    {
        static uint32_t const VALUE = 1U;
    };

    TypeDescriptionSequence2D(uint32_t align, bool big_endian)
      : TypeDescription(Type::SEQUENCE2D, "sequence2d", align, big_endian)
      , row_size_desc_(0U)
      , col_size_desc_(0U)
      , tag_(0U)
      , element_desc_(nullptr)
    {
    }

    TypeDescriptionSequence2D& SetRowColumn(TypeDescription::PtrType const& row_size_desc,
                                            TypeDescription::PtrType const& col_size_desc,
                                            uint32_t                        tag = RowMajorTag::VALUE)
    {
        this->row_size_desc_ = row_size_desc;
        this->row_size_desc_->SetParent(this->shared_from_this());
        this->col_size_desc_ = col_size_desc;
        this->col_size_desc_->SetParent(this->shared_from_this());
        this->tag_ = tag;
        return *this;
    }

    TypeDescriptionSequence2D& SetElementType(TypeDescription::PtrType const& desc)
    {
        this->element_desc_ = desc;
        this->element_desc_->SetParent(this->shared_from_this());
        return *this;
    }

    std::string GetName() const noexcept override
    {
        return std::string(type_name_) + '<' + element_desc_->GetName() + "," + row_size_desc_->GetName() + "," +
               col_size_desc_->GetName() + ">";
    }

    std::vector<TypeDescription::MemberPair> GetMembers() const noexcept override
    {
        return {};
    }

    std::vector<TypeDescription::MemberPair> GetTemplates() const noexcept override
    {
        return {{"ElementType", element_desc_}};
    }

    std::string PrintToString(size_t indent) const noexcept override
    {
        return std::string(indent, ' ') + GetName();
    }

    TypeDescription::PtrType GetRowSizeDescription() const noexcept
    {
        return row_size_desc_;
    }

    TypeDescription::PtrType GetColumnSizeDescription() const noexcept
    {
        return col_size_desc_;
    }

    uint32_t GetTag() const noexcept
    {
        return tag_;
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node                 = TypeDescription::ToYaml();
        node["row_size_description"]    = row_size_desc_->ToYaml();
        node["column_size_description"] = col_size_desc_->ToYaml();
        node["element_description"]     = element_desc_->ToYaml();
        node["tag"]                     = tag_;
        return node;
    }

protected:
    TypeDescription::PtrType row_size_desc_;
    TypeDescription::PtrType col_size_desc_;
    uint32_t                 tag_;
    TypeDescription::PtrType element_desc_;
};

template <typename T, typename R, typename C, typename LayoutTag = TypeDescriptionSequence2D::RowMajorTag>
struct Sequence2DTag
{
};

template <typename T, typename R, typename C, typename LayoutTag, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<Sequence2DTag<T, R, C, LayoutTag>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionSequence2D>(TypeDescriptionSequence2D(ALIGN, IS_BIG_ENDIAN));
        desc->SetRowColumn(TypeDescriptionResolver<R, ALIGN, IS_BIG_ENDIAN>::Get(),
                           TypeDescriptionResolver<C, ALIGN, IS_BIG_ENDIAN>::Get(), LayoutTag::VALUE)
            .SetElementType(TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
