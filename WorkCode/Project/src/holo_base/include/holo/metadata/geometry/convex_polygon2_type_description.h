#ifndef HOLO_METADATA_GEOMETRY_CONVEX_POLYGON2_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_CONVEX_POLYGON2_TYPE_DESCRIPTION_H_

#include <holo/geometry/convex_polygon2.h>
#include <holo/metadata/geometry/point2_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char CONVEX_POLYGEN2_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::ConvexPolygon2T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::ConvexPolygon2T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"vertices",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<
                          holo::geometry::Point2T<TypeReferenceTag<2U, geometry_type::CONVEX_POLYGEN2_SCALAR_TYPE_NAME>>,
                          holo::uint8_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
