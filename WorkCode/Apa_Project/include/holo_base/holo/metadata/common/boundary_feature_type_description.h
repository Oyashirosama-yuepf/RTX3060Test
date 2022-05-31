#ifndef HOLO_METADATA_COMMON_BOUNDARY_FEATURE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_BOUNDARY_FEATURE_TYPE_DESCRIPTION_H_

#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::BoundaryColor, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::BoundaryColor");
        (void)desc->SetEnumerates({{0U, "UNKNOWN"}, {1U, "WHITE"}, {2U, "YELLOW"}, {3U, "ORANGE"}, {4U, "BLUE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::BoundaryStyle, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::BoundaryStyle");
        (void)desc->SetEnumerates({{0U, "UNKNOWN"},
                             {0x01U, "DASHED"},
                             {0x02U, "BOTTS_DOT"},
                             {0x61U, "SOLID"},
                             {0x62U, "ROAD_EDGE"},
                             {0x63U, "BARRIER_BLOCK"},
                             {0x64U, "FISHBONE"},
                             {0x65U, "ROAD_BOUNDARY"},
                             {0xE1U, "DOUBLE_SOLID"},
                             {0xE2U, "DOUBLE_DASHED"},
                             {0xA1U, "LEFT_DOT_RIGHT_SOLID"},
                             {0xC1U, "LEFT_SOLID_RIGHT_DOT"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo
#endif
