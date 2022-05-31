#ifndef HOLO_METADATA_GEOMETRY_LINE2_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_LINE2_TYPE_DESCRIPTION_H_

#include <holo/geometry/line2.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char LINE2_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::Line2T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::Line2T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"a", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE2_SCALAR_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()},
                         {"b", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE2_SCALAR_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()},
                         {"c", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE2_SCALAR_TYPE_NAME>, ALIGN,
                                                       IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
