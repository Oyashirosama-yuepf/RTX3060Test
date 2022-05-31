#ifndef HOLO_METADATA_COMMON_GNSS_POSITION_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_GNSS_POSITION_TYPE_DESCRIPTION_H_

#include <holo/common/gnss_position.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::GnssPosition, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::GnssPosition");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"status", TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"latitude", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitude", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"altitude", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"latitude_covariance", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitude_covariance", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"altitude_covariance", TypeDescriptionResolver<float64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
