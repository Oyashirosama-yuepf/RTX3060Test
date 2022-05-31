#ifndef HOLO_METADATA_GEOMETRY_POINT3_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_POINT3_TYPE_DESCRIPTION_H_

#include <holo/geometry/point3.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char POINT3T_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::Point3T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "Point3T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data",
                  TypeDescriptionResolver<ArrayTag<TypeReferenceTag<1U, geometry_type::POINT3T_SCALAR_TYPE_NAME>, 3U>, ALIGN,
                                          IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
