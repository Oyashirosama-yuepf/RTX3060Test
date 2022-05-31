#ifndef HOLO_METADATA_MAP_LANE_MARK_INFO_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_LANE_MARK_INFO_TYPE_DESCRIPTION_H_

#include <holo/map/lane_mark_info.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::LaneMarkInfo, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::LaneMarkInfo");
        (void)desc->SetTemplates({}).SetMembers(
            {{"valid_indicator_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_uint32_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_float32_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"indicators", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"uint32_values", TypeDescriptionResolver<SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"float32_values", TypeDescriptionResolver<SequenceTag<float32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"mark_type", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"mark_color", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"mark_material", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"mark_rhombus_makring", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"ref_points", TypeDescriptionResolver<SequenceTag<holo::geometry::Point3T<float64_t>, uint32_t>, ALIGN,
                                                    IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};  // namespace metadata

}  // namespace metadata
}  // namespace holo

#endif
