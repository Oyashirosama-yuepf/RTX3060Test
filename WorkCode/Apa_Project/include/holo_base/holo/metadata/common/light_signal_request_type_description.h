#ifndef HOLO_METADATA_COMMON_LIGHT_SIGNAL_REQUEST_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_LIGHT_SIGNAL_REQUEST_TYPE_DESCRIPTION_H_

#include <holo/common/light_signal_request.h>
#include <holo/metadata/common/light_signal_request_type_description.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::LightSignalRequest, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto light_command_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::PathPointT::ValidValue");
        (void)light_command_desc
            ->SetBits({{0, "rear_fog_light"},
                       {1, "front_fog_light"},
                       {2, "brake_light_signal"},
                       {3, "high_beam_light"},
                       {4, "low_beam_light"},
                       {5, "hazard_flasher"},
                       {6, "right_turn_signal"},
                       {7, "left_turn_signal"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint16_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::LightSignalRequest");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"light_command", light_command_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
