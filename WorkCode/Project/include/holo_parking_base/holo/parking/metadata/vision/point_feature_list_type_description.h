#ifndef HOLO_PARKING_METADATA_VISION_POINT_FEATURE_LIST_H_
#define HOLO_PARKING_METADATA_VISION_POINT_FEATURE_LIST_H_

#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/parking/vision/point_feature_list.h>

namespace holo
{
namespace metadata
{
namespace vision
{
static constexpr char POINT_FEATURE_LIST_OBSTACLE_TYPE_NAME[] = "ObstacleType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::parking::vision::PointFeaturePtrListT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN,
                                                            "holo::parking::vision::PointFeaturePtrListT");
        desc->SetTemplates({{"ObstacleType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"sensor_id", TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"point_feature_list",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, vision::POINT_FEATURE_LIST_OBSTACLE_TYPE_NAME>,
                                                  uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
