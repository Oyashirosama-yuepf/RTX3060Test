#ifndef HOLO_METADATA_MAP_GEOFENCE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_GEOFENCE_TYPE_DESCRIPTION_H_

#include <holo/map/geofence.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::Geofences, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto function_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::map::Geofence::Function");
        (void)function_desc
            ->SetEnumerates({{0U, "UNKNOWN"},
                             {1U, "HSA"},
                             {2U, "ICP"},
                             {3U, "TJP"},
                             {4U, "LC"},
                             {5U, "EMSS"},
                             {6U, "FUNCTION_MAX"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto geofence_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::Geofence");
        (void)geofence_desc->SetTemplates({}).SetMembers(
            {{"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"function", function_desc},
             {"start_distance", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"end_distance", TypeDescriptionResolver<int32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto geofence_sequence_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)geofence_sequence_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(geofence_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::Geofences");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"status", geofence_sequence_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
