#ifndef HOLO_METADATA_VISION_IMAGE_OBJECTS_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_VISION_IMAGE_OBJECTS_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/vision/image_objects.h>

namespace holo
{
namespace metadata
{
namespace vision_type
{
static constexpr char IMAGE_OBJECT_OBJECT_TYPE_NAME[] = "ObjectType";
}
template <typename T, size_t SIZE, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::vision::ImageObjectsT<T, SIZE>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::vision::ImageObjectsT");
        (void)desc->SetTemplates({{"ObjectType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"sensor_id", TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"objects",
                  TypeDescriptionResolver<holo::metadata::SequenceTag<
                                              TypeReferenceTag<1U, vision_type::IMAGE_OBJECT_OBJECT_TYPE_NAME>, uint32_t>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
