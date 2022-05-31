#ifndef HOLO_METADATA_IMPL_ARRAY2D_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_IMPL_ARRAY2D_TYPE_DESCRIPTION_H_

#include <array>
#include "type_description.h"

namespace holo
{
namespace metadata
{
class TypeDescriptionArray2D : public TypeDescription
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

    TypeDescriptionArray2D(uint32_t align, bool big_endian)
      : TypeDescription(Type::ARRAY2D, "array2d", align, big_endian)
      , element_row_size_(0U)
      , element_col_size_(0U)
      , tag_(0U)
      , element_desc_(nullptr)
    {
    }

    TypeDescriptionArray2D& SetRowColumn(uint32_t row_size, uint32_t col_size, uint32_t tag = RowMajorTag::VALUE)
    {
        this->element_row_size_ = row_size;
        this->element_col_size_ = col_size;
        this->tag_              = tag;
        return *this;
    }

    TypeDescriptionArray2D& SetElementType(TypeDescription::PtrType const& desc)
    {
        this->element_desc_ = desc;
        this->element_desc_->SetParent(this->shared_from_this());
        return *this;
    }

    std::string GetName() const noexcept override
    {
        return std::string(type_name_) + '<' + element_desc_->GetName() + ',' + std::to_string(element_row_size_) +
               ',' + std::to_string(element_col_size_) + ">";
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

    uint32_t GetRowSize() const noexcept
    {
        return element_row_size_;
    }

    uint32_t GetColumnSize() const noexcept
    {
        return element_col_size_;
    }

    uint32_t GetTag() const noexcept
    {
        return tag_;
    }

    uint32_t GetElementPosition(uint32_t x, uint32_t y) const noexcept
    {
        if (tag_ == RowMajorTag::VALUE)
        {
            return (x * element_col_size_ + y);
        }
        else
        {
            return x + y * element_row_size_;
        }
    }

    YAML::Node ToYaml() const noexcept override
    {
        YAML::Node node             = TypeDescription::ToYaml();
        node["element_row_size"]    = element_row_size_;
        node["element_column_size"] = element_col_size_;
        node["tag"]                 = tag_;
        node["element_description"] = element_desc_->ToYaml();
        return node;
    }

private:
    uint32_t                 element_row_size_;
    uint32_t                 element_col_size_;
    uint32_t                 tag_;
    TypeDescription::PtrType element_desc_;
};

template <typename T, size_t R, size_t C, typename LayoutTag = TypeDescriptionArray2D::RowMajorTag>
struct Array2DTag
{
};

template <typename T, size_t R, size_t C, typename LayoutTag, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<Array2DTag<T, R, C, LayoutTag>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionArray2D>(TypeDescriptionArray2D(ALIGN, IS_BIG_ENDIAN));
        desc->SetRowColumn(R, C, LayoutTag::VALUE)
            .SetElementType(TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
