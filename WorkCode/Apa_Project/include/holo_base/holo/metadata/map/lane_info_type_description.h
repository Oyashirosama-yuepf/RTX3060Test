#ifndef HOLO_METADATA_MAP_LANE_INFO_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_LANE_INFO_TYPE_DESCRIPTION_H_

#include <holo/map/lane_info.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::LaneInfo, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::LaneInfo");
        (void)desc->SetTemplates({}).SetMembers(
            {{"valid_indicator_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_uint32_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_float32_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"indicators", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"uint32_values",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"float32_values",
              TypeDescriptionResolver<holo::metadata::SequenceTag<float32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"seq", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"type", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"left_mark_info", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"right_mark_info", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"vec_succ_ids",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint64_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"vec_pre_ids",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint64_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"vec_points",
              TypeDescriptionResolver<holo::metadata::SequenceTag<holo::geometry::Point3T<float64_t>, uint32_t>, ALIGN,
                                      IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};  // namespace metadata

}  // namespace metadata
}  // namespace holo

#endif
