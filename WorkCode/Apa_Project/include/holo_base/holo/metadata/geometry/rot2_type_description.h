#ifndef HOLO_METADATA_GEOMETRY_ROT2_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_ROT2_TYPE_DESCRIPTION_H_

#include <holo/geometry/rot2.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char ROT2T_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::Rot2T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::Rot2T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"cos", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::ROT2T_SCALAR_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()},
                         {"sin", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::ROT2T_SCALAR_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
