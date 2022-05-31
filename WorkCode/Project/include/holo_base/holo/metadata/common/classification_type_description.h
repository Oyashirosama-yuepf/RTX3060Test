#ifndef HOLO_METADATA_COMMON_CLASSIFICATION_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_CLASSIFICATION_TYPE_DESCRIPTION_H_

#include <holo/common/classification.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::Classification, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto main_type =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::Classification::MainType");
        (void)main_type
            ->SetEnumerates({{0x00U, "UNKNOWN"},
                             {0x01U, "PEDESTRIAN"},
                             {0x02U, "VEHICLE"},
                             {0x03U, "BIKE"},
                             {0x04U, "TRAFFIC_SIGN"},
                             {0x05U, "ANIMAL"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto sub_type =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::Classification::MainType");
        (void)sub_type
            ->SetEnumerates({{0x0000U, "UNKNOWN"},
                             {0x0001U, "UNKNOWN_MOVABLE"},
                             {0x0002U, "UNKNOWN_UNMOVABLE"},

                             {0x0100U, "PEDESTRIAN"},

                             {0x0200U, "CAR"},
                             {0x0201U, "TRUCK"},
                             {0x0202U, "VAN"},
                             {0x0203U, "BUS"},

                             {0x0300U, "BICYCLE"},
                             {0x0301U, "TRICYCLE"},
                             {0x0302U, "MOTOBIKE"},

                             {0x0400U, "TRAFFIC_LED_BOARD"},
                             {0x0401U, "TRAFFIC_SIGN_BOARD"},
                             {0x0402U, "TRAFFIC_CONE"},

                             {0x0403U, "TRAFFIC_POLE"},
                             {0x0404U, "TRAFFIC_LANE"},
                             {0x0405U, "TRAFFIC_CURB"},
                             {0x0406U, "TRAFFIC_LIGHT"},
                             {0x0407U, "TRAFFIC_CROSSING"},
                             {0x0408U, "TRAFFIC_MARKER"},
                             {0x0500U, "ANIMAL_DOG"},
                             {0x0501U, "ANIMAL_CAT"},
                             {0x0502U, "ANIMAL_COW"},
                             {0x0503U, "ANIMAL_SHEEP"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::Classification");
        (void)desc->SetFields({{"main_type", 16, 16, main_type}, {"sub_type", 0, 16, sub_type}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
