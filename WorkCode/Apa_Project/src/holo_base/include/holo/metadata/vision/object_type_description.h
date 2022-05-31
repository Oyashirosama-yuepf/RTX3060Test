#ifndef HOLO_METADATA_VISION_OBJECT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_VISION_OBJECT_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/classification_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/vision/object.h>

namespace holo
{
namespace metadata
{
namespace vision_type
{
static constexpr char OBJECT_POINT_TYPE_NAME[] = "PointType";
}
template <typename T, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::vision::ObjectT<T, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::vision::ObjectT");
        (void)desc->SetTemplates({{"PointType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"category", TypeDescriptionResolver<holo::common::Classification, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"points",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, vision_type::OBJECT_POINT_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
