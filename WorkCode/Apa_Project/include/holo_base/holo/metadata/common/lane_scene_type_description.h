#ifndef HOLO_METADATA_COMMON_LANE_SCENE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_LANE_SCENE_TYPE_DESCRIPTION_H_

#include <holo/common/lane_scene.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::LaneScene, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::LaneScene");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lane_status", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
