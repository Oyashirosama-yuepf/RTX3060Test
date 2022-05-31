#ifndef HOLO_METADATA_GEOMETRY_LINE_SEGMENT2_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_LINE_SEGMENT2_TYPE_DESCRIPTION_H_

#include <holo/geometry/line_segment2.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char LINE_SEGMENT2T_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::LineSegment2T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::LineSegment2T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"x", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE_SEGMENT2T_SCALAR_TYPE_NAME>,
                                                       ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"y", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE_SEGMENT2T_SCALAR_TYPE_NAME>,
                                                       ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"v0", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE_SEGMENT2T_SCALAR_TYPE_NAME>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"v1", TypeDescriptionResolver<TypeReferenceTag<0U, geometry_type::LINE_SEGMENT2T_SCALAR_TYPE_NAME>,
                                                        ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
