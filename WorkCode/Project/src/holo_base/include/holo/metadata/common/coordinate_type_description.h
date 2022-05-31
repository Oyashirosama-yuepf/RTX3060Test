#ifndef HOLO_METADATA_COMMON_COORDINATE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_COORDINATE_TYPE_DESCRIPTION_H_

#include <holo/common/coordinate.h>
#include <holo/metadata/common/sensor_id_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::Coordinate, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto type_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::Coordinate::Type");
        (void)type_desc
            ->SetEnumerates({{0, "UNKNOWN"},
                             {1, "VEHICLE"},
                             {2, "WGS84"},
                             {3, "UTM6"},
                             {4, "UTM3"},
                             {5, "DR"},
                             {11, "GCJ02"},
                             {12, "CUSTOM0"},
                             {13, "CUSTOM1"},
                             {14, "CUSTOM2"},
                             {15, "CUSTOM3"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::Coordinate");
        (void)desc->SetFields(
                {{"type", 28, 4, type_desc},
                 {"param", 0, 28, TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get()},

                 {"sensor_id", 0, 28, TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>::Get()},

                 {"offset_x", 20, 8, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"offset_y", 8, 12, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"S", 7, 1, TypeDescriptionResolver<bool, ALIGN, IS_BIG_ENDIAN>::Get()},
                 {"zone_id", 0, 7, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},

                 {"version", 0, 16, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
