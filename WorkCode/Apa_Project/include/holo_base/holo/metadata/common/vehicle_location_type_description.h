#ifndef HOLO_METADATA_COMMON_VEHICLE_LOCATION_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_VEHICLE_LOCATION_TYPE_DESCRIPTION_H_

#include <holo/common/vehicle_location.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::VehicleLocation, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto plane_desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "Plane");
        (void)plane_desc
            ->SetEnumerates({{0x00, "UNKNOWN"},
                             {0x01, "FRONT"},
                             {0x02, "REAR"},
                             {0x03, "LEFT"},
                             {0x04, "RIGHT"},
                             {0x05, "FRONT_WINDOW"},
                             {0x06, "REAR_WINDOW"},
                             {0x07, "LEFT_WINDOW"},
                             {0x08, "RIGHT_WINDOW"},
                             {0x09, "EIGINE_HOOD"},
                             {0x0A, "ROOF"},
                             {0x0B, "TRUNK_DOOR"},
                             {0x0C, "CHASSIS"},
                             {0x0D, "TRUNK"},
                             {0x0E, "COCKPIT"},
                             {0x0F, "GROUND"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());
        auto x_location_desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "LOCATION");
        (void)x_location_desc
            ->SetEnumerates({{0x00, "UNKNOWN"},
                             {0x01, "BOTTOM_MOST"},
                             {0x01, "REAR_MOST"},
                             {0x01, "LEFT_MOST"},
                             {0x04, "BOTTOM"},
                             {0x04, "REAR"},
                             {0x04, "LEFT"},
                             {0x08, "MIDDLE"},
                             {0x08, "CENTER"},
                             {0x0C, "TOP"},
                             {0x0C, "FRONT"},
                             {0x0C, "RIGHT"},
                             {0x0F, "TOP_MOST"},
                             {0x0F, "FRONT_MOST"},
                             {0x0F, "RIGHT_MOST"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto y_location_desc = x_location_desc;

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::VehicleLocation");
        (void)desc->SetFields({{"plane", 8, 8, plane_desc}, {"x", 4, 4, x_location_desc}, {"y", 0, 4, y_location_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};
}  // namespace metadata
}  // namespace holo

#endif
