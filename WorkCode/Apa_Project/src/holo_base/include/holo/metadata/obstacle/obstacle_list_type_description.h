#ifndef HOLO_METADATA_OBSTACLE_OBSTACLE_LIST_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_OBSTACLE_OBSTACLE_LIST_TYPE_DESCRIPTION_H_

#include <holo/common/perception_ability.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/perception_ability_type_description.h>
#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/obstacle/obstacle_list_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/obstacle/obstacle_list.h>

namespace holo
{
namespace metadata
{
namespace obstacle_type
{
static constexpr char OBSTACLE_SIZE_FIELD_NAME[] = "size";
static constexpr char OBSTACLE_LIST_OBSTACLE_TYPE_NAME[] = "ObstacleType";
}

template <typename T, size_t CAPACITY, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::obstacle::ObstaclePtrListT<T, CAPACITY>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::obstacle::ObstaclePtrListT");
        (void)desc->SetTemplates({{"ObstacleType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"sensor_id", TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"size", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"perception_ability",
                  TypeDescriptionResolver<holo::common::PerceptionAbility, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"obstacle_list",
                  TypeDescriptionResolver<SequenceTag<TypeReferenceTag<1U, obstacle_type::OBSTACLE_LIST_OBSTACLE_TYPE_NAME>,
                                                      ValueReferenceTag<1U, obstacle_type::OBSTACLE_SIZE_FIELD_NAME>>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
