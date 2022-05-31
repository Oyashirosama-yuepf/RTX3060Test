#ifndef HOLO_METADATA_SENSORS_CAMERA_IMAGE_STRUCTURE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_SENSORS_CAMERA_IMAGE_STRUCTURE_TYPE_DESCRIPTION_H_

#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

#include <holo/sensors/camera/image_structure.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::sensors::camera::FrameType, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::sensors::camera::FrameType");
        desc->SetEnumerates({{0, "UNKNOWN"}, {1, "P"}, {19, "I"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::sensors::camera::ImageType, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::sensors::camera::ImageType");
        desc->SetEnumerates({{0, "JPEG"}, {1, "H264"}, {2, "H265"}, {3, "RAW_YUYV"}, {255, "INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::sensors::camera::ImagePacket, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::sensors::camera::ImagePacket");
        desc->SetTemplates({}).SetMembers(
            {{"seq", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"received_stemp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"trigger_stamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"frame_type", TypeDescriptionResolver<holo::sensors::camera::FrameType, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"cols", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rows", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"image_type", TypeDescriptionResolver<holo::sensors::camera::ImageType, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data",
              TypeDescriptionResolver<holo::metadata::SequenceTag<uint8_t, uint32_t>, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo
#endif
