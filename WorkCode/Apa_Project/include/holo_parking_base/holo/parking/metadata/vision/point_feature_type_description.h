#ifndef HOLO_PARKING_METADATA_VISION_POINT_FEATURE_H_
#define HOLO_PARKING_METADATA_VISION_POINT_FEATURE_H_

#include <holo/metadata/geometry/point2_type_description.h>
#include <holo/metadata/type_description.h>
#include <holo/parking/vision/point_feature.h>

namespace holo
{
namespace metadata
{
namespace vision
{
static constexpr char POINT_FEATURE_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::parking::vision::PointFeatureT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::parking::vision::PointFeatureT");
        desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"position", TypeDescriptionResolver<
                                  holo::geometry::Point2T<TypeReferenceTag<1U, vision::POINT_FEATURE_TYPE_NAME>>, ALIGN,
                                  IS_BIG_ENDIAN>::Get()},
                 {"descriptor",
                  TypeDescriptionResolver<
                      holo::metadata::SequenceTag<TypeReferenceTag<1U, vision::POINT_FEATURE_TYPE_NAME>, uint32_t>,
                      ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"confidence", TypeDescriptionResolver<TypeReferenceTag<0U, vision::POINT_FEATURE_TYPE_NAME>, ALIGN,
                                                        IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif