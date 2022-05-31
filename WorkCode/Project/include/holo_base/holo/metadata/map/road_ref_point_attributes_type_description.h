#ifndef HOLO_METADATA_MAP_ROAD_REF_POINT_ATTRIBUTES_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_MAP_ROAD_REF_POINT_ATTRIBUTES_TYPE_DESCRIPTION_H_

#include <holo/map/road_ref_point_attributes.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace map_type
{
static constexpr char ROAD_REF_POINT_ATTRIBUTES_TYPE_NAME[] = "RoadAttributeType";
}

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::RoadScs, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoadScs");
        (void)desc->SetTemplates({}).SetMembers(
            {{"distance", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"slope", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"curvature_radius", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"superelevation", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::RoadTypeInterval, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoadTypeInterval");
        (void)desc->SetTemplates({}).SetMembers(
            {{"interval_first", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"interval_second", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"road_category", TypeDescriptionResolver<holo::common::RoadCategory, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

template <typename T, std::size_t MAX_SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::map::RoadRefPointAttributes<T, MAX_SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::map::RoadRefPointAttributes");
        (void)desc->SetTemplates({{"RoadAttributeType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"ref_point",
                  TypeDescriptionResolver<holo::geometry::Point3T<float64_t>, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"attributes",
                  TypeDescriptionResolver<holo::metadata::SequenceTag<
                                              TypeReferenceTag<1U, map_type::ROAD_REF_POINT_ATTRIBUTES_TYPE_NAME>, uint32_t>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
