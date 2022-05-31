#ifndef HOLO_METADATA_GEOMETRY_POSE3_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_POSE3_TYPE_DESCRIPTION_H_

#include <holo/geometry/pose3.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/geometry/rot3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char POSE3T_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::Pose3T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::Pose3T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"rotation", TypeDescriptionResolver<
                                  holo::geometry::Rot3T<TypeReferenceTag<1U, geometry_type::POSE3T_SCALAR_TYPE_NAME>>, ALIGN,
                                  IS_BIG_ENDIAN>::Get()},
                 {"translation", TypeDescriptionResolver<
                                     holo::geometry::Point3T<TypeReferenceTag<1U, geometry_type::POSE3T_SCALAR_TYPE_NAME>>,
                                     ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
