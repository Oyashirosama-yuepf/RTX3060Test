#ifndef _HOLO_METADATA_SENSORS_LIDAR_RSBPEARL_RSBPEARL_FORMAT_TYPE_DESCRIPTION_H_
#define _HOLO_METADATA_SENSORS_LIDAR_RSBPEARL_RSBPEARL_FORMAT_TYPE_DESCRIPTION_H_

#include <holo/metadata/type_description.h>
#include <holo/sensors/lidar/rsbpearl/rsbpearl_format.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<::RawRsbpMsopPacket, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto raw_rsbp_msop_header_desc =
            std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawRsbpMsopHeader");
        raw_rsbp_msop_header_desc->SetTemplates({}).SetMembers(
            {{"header", TypeDescriptionResolver<ArrayTag<uint8_t, 8U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved1", TypeDescriptionResolver<ArrayTag<uint8_t, 20U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"timestamp", TypeDescriptionResolver<ArrayTag<uint8_t, 10U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reserved2", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto channel_data_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::ChannelData");
        channel_data_desc->SetTemplates({}).SetMembers(
            {{"distance", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"reflection", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto channel_data_array_desc = std::make_shared<TypeDescriptionArray>(ALIGN, IS_BIG_ENDIAN);
        channel_data_array_desc->SetSize(32U).SetElementType(channel_data_desc);

        auto raw_rsbp_msop_data_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawRsbpMsopData");
        raw_rsbp_msop_data_desc->SetTemplates({}).SetMembers(
            {{"header", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"azimuth", TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"data", channel_data_array_desc}});

        auto raw_rsbp_msop_tail_desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawRsbpMsopTail");
        raw_rsbp_msop_tail_desc->SetTemplates({}).SetMembers(
            {{"header", TypeDescriptionResolver<ArrayTag<uint8_t, 4U>, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"tail", TypeDescriptionResolver<ArrayTag<uint8_t, 2U>, ALIGN, IS_BIG_ENDIAN>::Get()}});

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "::RawRsbpMsopPacket");
        desc->SetTemplates({}).SetMembers({{"header", raw_rsbp_msop_header_desc},
                                           {"data", raw_rsbp_msop_data_desc},
                                           {"tail", raw_rsbp_msop_tail_desc}});

        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
