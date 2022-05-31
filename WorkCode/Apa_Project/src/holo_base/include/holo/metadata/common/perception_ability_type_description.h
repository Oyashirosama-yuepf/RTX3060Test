#ifndef HOLO_METADATA_COMMON_PERCEPTION_ABILITY_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_PERCEPTION_ABILITY_TYPE_DESCRIPTION_H_

#include <holo/common/perception_ability.h>
#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::PerceptionAbility, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto perception_ability_level = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::PerceptionAbility::PerceptionAbilityLevel");
        (void)perception_ability_level->SetEnumerates({{0x0, "NONE"}, {0x1, "LOW"}, {0x2, "MIDDLE"}, {0x3, "HIGH"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto level_z1_desc = perception_ability_level;
        auto level_z2_desc = perception_ability_level;
        auto level_z3_desc = perception_ability_level;
        auto level_z4_desc = perception_ability_level;
        auto level_z5_desc = perception_ability_level;
        auto level_z6_desc = perception_ability_level;
        auto level_z7_desc = perception_ability_level;
        auto level_z8_desc = perception_ability_level;
        auto level_z9_desc = perception_ability_level;

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::PerceptionAbility");
        (void)desc->SetFields({{"reserved", 18, 14, TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"level_z9", 16, 2, level_z9_desc},
                         {"level_z8", 14, 2, level_z8_desc},
                         {"level_z7", 12, 2, level_z7_desc},
                         {"level_z6", 10, 2, level_z6_desc},
                         {"level_z5", 8, 2, level_z5_desc},
                         {"level_z4", 6, 2, level_z4_desc},
                         {"level_z3", 4, 2, level_z3_desc},
                         {"level_z2", 2, 2, level_z2_desc},
                         {"level_z1", 0, 2, level_z1_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif