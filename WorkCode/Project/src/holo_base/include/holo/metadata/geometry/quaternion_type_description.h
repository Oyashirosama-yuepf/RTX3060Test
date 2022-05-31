#ifndef HOLO_METADATA_GEOMETRY_QUATERNION_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_GEOMETRY_QUATERNION_TYPE_DESCRIPTION_H_

#include <holo/geometry/quaternion.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::geometry::QuaternionT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        return TypeDescriptionResolver<ArrayTag<T, 4>, ALIGN, IS_BIG_ENDIAN>::Get();
    }
};
}  // namespace metadata
}  // namespace holo

#endif
