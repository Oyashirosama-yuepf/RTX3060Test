#ifndef HOLO_METADATA_MAP_LINK_INFO_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_LINK_INFO_TYPE_DESCRIPTION_H_

#include <holo/map/link_info.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::LinkInfo, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::LinkInfo");
        (void)desc->SetTemplates({}).SetMembers(
            {{"valid_indicator_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_uint32_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"valid_float32_size", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"indicators", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"uint32_values",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"float32_values",
              TypeDescriptionResolver<holo::metadata::SequenceTag<float32_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()},

             {"link_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_count", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"vec_lanes_info", TypeDescriptionResolver<holo::metadata::SequenceTag<holo::map::LaneInfo, uint32_t>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()},
             {"ref_points",
              TypeDescriptionResolver<holo::metadata::SequenceTag<holo::geometry::Point3T<float64_t>, uint32_t>, ALIGN,
                                      IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
