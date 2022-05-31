#ifndef HOLO_METADATA_VISION_KEY_POINT3_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_VISION_KEY_POINT3_TYPE_DESCRIPTION_H_

#include <holo/geometry/point3.h>
#include <holo/metadata/type_description.h>
#include <holo/vision/keypoint3.h>

namespace holo
{
namespace metadata
{
namespace vision_type
{
static constexpr char KEY_POINT3_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::vision::KeyPoint3T<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::vision::KeyPoint3T");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"data",
                  TypeDescriptionResolver<ArrayTag<TypeReferenceTag<1U, vision_type::KEY_POINT3_SCALAR_TYPE_NAME>, 2U>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"visibility", TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif