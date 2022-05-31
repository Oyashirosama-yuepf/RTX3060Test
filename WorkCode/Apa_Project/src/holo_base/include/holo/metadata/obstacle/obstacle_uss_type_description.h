#ifndef HOLO_METADATA_OBSTACLE_OBSTACLE_USS_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_OBSTACLE_OBSTACLE_USS_TYPE_DESCRIPTION_H_

#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/obstacle/obstacle_base_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/obstacle/obstacle_uss.h>

namespace holo
{
namespace metadata
{
namespace obstacle_type
{
static constexpr char OBSTACLE_USS_SCALAR_TYPE_NAME[] = "ScalarType";
}

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::obstacle::ObstacleUssT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::details::ObstacleUssT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"obstacle_id", TypeDescriptionResolver<holo::uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"sensor_id", TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"classification", TypeDescriptionResolver<holo::common::Classification, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"obstacle_exist_score", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"position",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::OBSTACLE_USS_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"position_sigma",
                  TypeDescriptionResolver<
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::OBSTACLE_USS_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"fov", TypeDescriptionResolver<TypeReferenceTag<0U, obstacle_type::OBSTACLE_USS_SCALAR_TYPE_NAME>, ALIGN,
                      IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
