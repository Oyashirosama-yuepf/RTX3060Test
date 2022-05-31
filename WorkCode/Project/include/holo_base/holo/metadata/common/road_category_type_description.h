#ifndef HOLO_METADATA_COMMON_ROAD_CATEGORY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_ROAD_CATEGORY_TYPE_DESCRIPTION_H_

#include <holo/common/road_category.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::RoadCategory, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto category_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadCategory::Category");
        (void)category_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "MAINROAD"}, {2U, "RAMP"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto tag_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadCategory::Tag");
        (void)tag_desc->SetBits({{0, "TUNNEL"}, {1, "TOLL"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadCategory");
        (void)desc->SetFields({{"tags", 0, 24, tag_desc}, {"category", 24, 8, category_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::LaneCategory, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto category_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneCategory::Category");
        (void)category_desc
            ->SetEnumerates(
                {{0U, "UNKNOWN"}, {1U, "REGULAR"}, {2U, "ACCELERATION"}, {3U, "DECELERATION"}, {4U, "EMERGENCY"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneCategory");
        (void)desc->SetFields({{"tags", 0, 24, TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"category", 24, 8, category_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
