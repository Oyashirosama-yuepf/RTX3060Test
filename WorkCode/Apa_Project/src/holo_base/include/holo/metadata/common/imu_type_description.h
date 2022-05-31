#ifndef HOLO_METADATA_COMMON_IMU_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_IMU_TYPE_DESCRIPTION_H_

#include <holo/common/imu.h>
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
static constexpr char IMUT_SCALAR_TYPE_NAME[] = "ScalarType";
}
template <typename T, size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::details::ImuT<T>, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto status_desc = std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::ImuT::Status");
        (void)status_desc
            ->SetBits({{0, "GYROXERROR"},
                       {1, "GYROYERROR"},
                       {2, "GYROZERROR"},
                       {3, "ACCLXERROR"},
                       {4, "ACCLYERROR"},
                       {5, "ACCLZERROR"},
                       {6, "UNDEFINEDERROR"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::ImuT");
        (void)desc->SetTemplates({{"ScalarType", TypeDescriptionResolver<T, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetMembers(
                {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"status", status_desc},
                 {"angular_velocity",
                  TypeDescriptionResolver<holo::geometry::Point3T<TypeReferenceTag<1U, common_type::IMUT_SCALAR_TYPE_NAME>>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"linear_acceleration",
                  TypeDescriptionResolver<holo::geometry::Point3T<TypeReferenceTag<1U, common_type::IMUT_SCALAR_TYPE_NAME>>,
                                          ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo
#endif
