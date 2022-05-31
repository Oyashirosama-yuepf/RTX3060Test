#ifndef HOLO_METADATA_COMMON_ALARM_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_ALARM_TYPE_DESCRIPTION_H_

#include <holo/common/alarm.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::Alarm, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto alarm_level =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::Alarm::Level");
        (void)alarm_level->SetEnumerates({{0U, "NORMAL"}, {1U, "MINOR"}, {2U, "MODERATE"}, {3U, "FATAL_1"}, {4U, "FATAL_2"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::Alarm");
        (void)desc->SetFields({{"level", 13, 3, alarm_level},
                         {"code", 0, 13, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif