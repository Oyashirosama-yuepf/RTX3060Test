#ifndef HOLO_METADATA_COMMON_WEATHER_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_WEATHER_TYPE_DESCRIPTION_H_

#include <holo/common/weather.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::Weather, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto cloudy_desc =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::Weather::Category::Cloudy");
        (void)cloudy_desc->SetEnumerates({{0, "sunny"}, {1, "cloudy"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto category_desc =
            std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::Weather::Category");
        (void)category_desc
            ->SetFields({{"cloudy", 0, 1, cloudy_desc},
                         {"rainfall", 1, 5, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"snowfall", 6, 5, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"foggy_vis", 11, 5, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"sandy_vis", 16, 5, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"reserved", 21, 11, TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::Weather");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"weather_category", category_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
