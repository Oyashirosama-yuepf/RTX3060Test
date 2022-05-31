#ifndef HOLO_METADATA_GEOMETRY_BOX2_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_BOX2_TYPE_DESCRIPTION_H_

#include <holo/geometry/box2.h>
#include <holo/metadata/geometry/box2_type_description.h>
#include <holo/metadata/geometry/pose2_type_description.h>
#include <holo/metadata/type_description.h>
#include <memory>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char BOX2T_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::Box2T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::Box2T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"width", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::BOX2T_SCALAR_TYPE_NAME>, ALIGN,
                                                   IS_BIG_ENDIAN>::Get()},
                 {"height", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::BOX2T_SCALAR_TYPE_NAME>, ALIGN,
                                                    IS_BIG_ENDIAN>::Get()},
                 {"pose",
                  TypeDescriptionResolver<holo::geometry::Pose2T<TypeReferenceTag<1U, geometry_type::BOX2T_SCALAR_TYPE_NAME>>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
