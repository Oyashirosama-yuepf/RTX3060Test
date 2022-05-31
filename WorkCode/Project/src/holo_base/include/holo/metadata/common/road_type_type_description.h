#ifndef HOLO_METADATA_COMMON_ROAD_TYPE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_ROAD_TYPE_TYPE_DESCRIPTION_H_

#include <holo/common/road_type.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
/**
 * @deprecated Use TypeDescriptionResolver<holo::common::RoadCategory, ALIGN, IS_BIG_ENDIAN> instead
 */
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct [[deprecated]] TypeDescriptionResolver<holo::common::RoadType, ALIGN, IS_BIG_ENDIAN> {
    static TypeDescription::PtrType Get() noexcept
    {
        auto type_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadType::Type");
        (void)type_desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "MAINROAD"}, {2U, "RAMP"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto tag_desc = std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadType::Tag");
        (void)tag_desc->SetBits({{0, "TUNNEL"}, {1, "TOLL"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::RoadType");
        (void)desc->SetFields({{"tags", 0, 24, tag_desc}, {"type", 24, 8, type_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

/**
 * @deprecated Use TypeDescriptionResolver<holo::common::LaneCategory, ALIGN, IS_BIG_ENDIAN> instead
 */
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct [[deprecated]] TypeDescriptionResolver<holo::common::LaneType, ALIGN, IS_BIG_ENDIAN> {
    static TypeDescription::PtrType Get() noexcept
    {
        auto type_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneType::Type");
        (void)type_desc
            ->SetEnumerates(
                {{0U, "UNKNOWN"}, {1U, "REGULAR"}, {2U, "ACCELERATION"}, {3U, "DECELERATION"}, {4U, "EMERGENCY"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneType");
        (void)desc->SetFields({{"tags", 0, 24, TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"type", 24, 8, type_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
