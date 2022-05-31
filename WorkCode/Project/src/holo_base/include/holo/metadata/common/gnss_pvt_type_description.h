#ifndef HOLO_METADATA_COMMON_GNSS_PVT_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_GNSS_PVT_TYPE_DESCRIPTION_H_

#include <holo/common/gnss_pvt.h>
#include <holo/metadata/common/coordinate_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::GnssPvt, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto mode_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::GnssPvt::Mode");
        (void)mode_desc
            ->SetEnumerates({{0x00, "NO_POSITION"},
                             {0x01, "TIMING_ONLY"},
                             {0x02, "SINGLE_FIX"},
                             {0x03, "DIFF_POSITION"},
                             {0x04, "RTK_FLOAT_FIX"},
                             {0x05, "RTK_INT_FIX"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto status_desc =
            std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::GnssPvt::Status");
        (void)status_desc
            ->SetFields({{"PositionValid", 0, 1, TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"VelocityValid", 1, 1, TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"PositionCovValid", 2, 1, TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"VelocityCovValid", 3, 1, TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"Mode", 8, 8, mode_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::GnssPvt");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"coordinate", TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"status", status_desc},
             {"longitude", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"latitude", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"height", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity_east", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity_north", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity_up", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitude_cov", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"latitude_cov", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"height_cov", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity_east_cov", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity_north_cov", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"velocity_up_cov", TypeDescriptionResolver<holo::float64_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
