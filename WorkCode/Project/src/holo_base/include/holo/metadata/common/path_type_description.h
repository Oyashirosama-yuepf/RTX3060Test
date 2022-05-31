#ifndef HOLO_METADATA_COMMON_PATH_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_PATH_TYPE_DESCRIPTION_H_

#include <holo/common/path.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char PATH_POINTT_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::PathT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto valid_value_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::PathT::ValidValue");
        (void)valid_value_desc
            ->SetBits({{0, "POSITION"},
                       {1, "THETA"},
                       {2, "CURVATURE"},
                       {3, "SPEED"},
                       {4, "ACCELERATION"},
                       {5, "DISTANCE"},
                       {6, "TIME"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto planning_state_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::PathT::PlanningState");
        (void)planning_state_desc
            ->SetEnumerates({{0U, "UNKNOWN"}, {1U, "FORWARD"}, {2U, "BACKWARD"}, {3U, "HOLD"}, {4U, "PARK"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto path_point_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::PathPointT");
        (void)path_point_desc->SetTemplates({}).SetMembers(
            {{"point", TypeDescriptionResolver<
                           holo::geometry::Point3T<TypeReferenceTag<3U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>>, ALIGN,
                           IS_BIG_ENDIAN>::Get()},
             {"theta", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>, ALIGN,
                                               IS_BIG_ENDIAN>::Get()},
             {"curvature", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>, ALIGN,
                                                   IS_BIG_ENDIAN>::Get()},
             {"speed", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>, ALIGN,
                                               IS_BIG_ENDIAN>::Get()},
             {"acceleration", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>, ALIGN,
                                                      IS_BIG_ENDIAN>::Get()},
             {"distance", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>, ALIGN,
                                                  IS_BIG_ENDIAN>::Get()},
             {"time", TypeDescriptionResolver<TypeReferenceTag<2U, common_type::PATH_POINTT_SCALAR_TYPE_NAME>, ALIGN,
                                              IS_BIG_ENDIAN>::Get()}});

        auto path_points_desc = std::make_shared<TypeDescriptionSequence>(ALIGN, IS_BIG_ENDIAN);
        (void)path_points_desc->SetSize(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get())
            .SetElementType(path_point_desc);

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::PathT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"valid_value", valid_value_desc},
                         {"planning_state", planning_state_desc},
                         {"path_point", path_points_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
