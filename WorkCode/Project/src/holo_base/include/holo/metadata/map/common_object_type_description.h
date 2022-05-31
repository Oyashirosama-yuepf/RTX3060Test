#ifndef HOLO_METADATA_MAP_COMMON_OBJECT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_COMMON_OBJECT_TYPE_DESCRIPTION_H_

#include <holo/map/common_object.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace map_type
{
static constexpr char COMMON_OBJECT_POINT_SIZE_FIELD_NAME[] = "point_count";
}
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::CommonObject, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::CommonObject");
        (void)desc->SetTemplates({}).SetMembers(
            {{"object_id", TypeDescriptionResolver<uint64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"object_type", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"point_count", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"bottom_point", TypeDescriptionResolver<holo::geometry::Point3T<float64_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"out_line",
              TypeDescriptionResolver<SequenceTag<holo::geometry::Point3T<float64_t>,
                                                  ValueReferenceTag<2U, map_type::COMMON_OBJECT_POINT_SIZE_FIELD_NAME>>,
                                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
