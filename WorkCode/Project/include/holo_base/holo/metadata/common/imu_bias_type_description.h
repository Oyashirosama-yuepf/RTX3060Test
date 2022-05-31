#ifndef HOLO_METADATA_COMMON_IMU_BIAS_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_IMU_BIAS_TYPE_DESCRIPTION_H_

#include <holo/common/imu_bias.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/geometry/point3_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
namespace common_type
{
static constexpr char IMU_BIAST_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::ImuBiasT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::ImuBiasT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers({{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"angular_velocity_bias",
                          TypeDescriptionResolver<
                              holo::geometry::Point3T<TypeReferenceTag<1U, common_type::IMU_BIAST_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()},
                         {"linear_acceleration_bias",
                          TypeDescriptionResolver<
                              holo::geometry::Point3T<TypeReferenceTag<1U, common_type::IMU_BIAST_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()},
                         {"angular_velocity_bias_covariance",
                          TypeDescriptionResolver<
                              holo::geometry::Point3T<TypeReferenceTag<1U, common_type::IMU_BIAST_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()},
                         {"linear_acceleration_bias_covariance",
                          TypeDescriptionResolver<
                              holo::geometry::Point3T<TypeReferenceTag<1U, common_type::IMU_BIAST_SCALAR_TYPE_NAME>>, ALIGN,
                              IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};  // namespace metadata
}  // namespace metadata
}  // namespace holo
#endif
