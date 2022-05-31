#ifndef HOLO_METADATA_GEOMETRY_ROT3_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_ROT3_TYPE_DESCRIPTION_H_

#include <holo/geometry/rot3.h>
#include <holo/metadata/numerics/matrix_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace geometry_type
{
static constexpr char ROT3T_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::Rot3T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::geometry::Rot3T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"matrix", TypeDescriptionResolver<
                           holo::numerics::MatrixT<TypeReferenceTag<1U, geometry_type::ROT3T_SCALAR_TYPE_NAME>, 3U, 3U>,
                           ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
