#ifndef HOLO_METADATA_OBSTACLE_OBSTACLE_GENERAL_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_OBSTACLE_OBSTACLE_GENERAL_TYPE_DESCRIPTION_H_

#include <holo/metadata/geometry/box3_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/numerics/vector_type_description.h>
#include <holo/metadata/obstacle/obstacle_base_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/numerics/vector.h>
#include <holo/obstacle/obstacle_general.h>

namespace holo
{
namespace metadata
{
namespace obstacle_type
{
static constexpr char OBSTACLE_GENERAL_SCALAR_TYPE_NAME[] = "ScalarType";
static constexpr char OBSTACLE_GENERAL_SIZE_FIELD_NAME[] = "num_contour_points";
}

template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::obstacle::ObstacleGeneralT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::details::ObstacleGeneralT");
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
                      holo::geometry::Point3T<TypeReferenceTag<1U, obstacle_type::OBSTACLE_GENERAL_SCALAR_TYPE_NAME>>, ALIGN,
                      IS_BIG_ENDIAN>::Get()},
                 {"relative_velocity",
                  TypeDescriptionResolver<
                      holo::numerics::VectorT<TypeReferenceTag<1U, obstacle_type::OBSTACLE_GENERAL_SCALAR_TYPE_NAME>, 3>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"absolute_velocity",
                  TypeDescriptionResolver<
                      holo::numerics::VectorT<TypeReferenceTag<1U, obstacle_type::OBSTACLE_GENERAL_SCALAR_TYPE_NAME>, 3>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"acceleration",
                  TypeDescriptionResolver<
                      holo::numerics::VectorT<TypeReferenceTag<1U, obstacle_type::OBSTACLE_GENERAL_SCALAR_TYPE_NAME>, 3>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"cut_in_cut_out",
                  TypeDescriptionResolver<holo::obstacle::details::CutInCutOut, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"motion_status",
                  TypeDescriptionResolver<holo::obstacle::details::MotionStatus, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"num_contour_points", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"bounding_box3d", TypeDescriptionResolver<holo::geometry::Box3f, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"contour_points",
                  TypeDescriptionResolver <
                      SequenceTag<
                          holo::geometry::Point3T<TypeReferenceTag<2U, obstacle_type::OBSTACLE_GENERAL_SCALAR_TYPE_NAME>>,
                          ValueReferenceTag<1U, obstacle_type::OBSTACLE_GENERAL_SIZE_FIELD_NAME>>, ALIGN,
                          IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
