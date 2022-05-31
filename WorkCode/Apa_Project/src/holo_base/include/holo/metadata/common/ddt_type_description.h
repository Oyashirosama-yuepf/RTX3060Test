#ifndef HOLO_METADATA_COMMON_DDT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_DDT_TYPE_DESCRIPTION_H_

#include <holo/common/ddt.h>
#include <holo/metadata/common/alarm_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::DdtState, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto flag_desc = std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::DdtState::flag");
        (void)flag_desc->SetBits({{0, "DDT_ENABLE_FLAG"}, {1, "PRED_DISTANCE_VALID_FLAG"}, {2, "PRED_TIME_VALID_FLAG"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::DdtState");
        (void)desc->SetTemplates({}).SetMembers(
            {{"type", TypeDescriptionResolver<holo::uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"flags", flag_desc},
             {"alarm", TypeDescriptionResolver<holo::common::Alarm, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"pred_distance", TypeDescriptionResolver<holo::uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"pred_time", TypeDescriptionResolver<holo::uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::DdtStates<SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::DdtStates");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"ddts", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::common::DdtState, uint8_t>, ALIGN,
                                              IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
