#ifndef HOLO_METADATA_COMMON_APA_CONTROL_COMMAND_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_APA_CONTROL_COMMAND_TYPE_DESCRIPTION_H_

#include <holo/common/apa_control_command.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::ApaControlCommand, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::ApaControlCommand");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lon_auto_mode", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"target_gear_request", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"stop_dist_request", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"speed_limit_request", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"apafail_brkmode_request", TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"steer_auto_mode", TypeDescriptionResolver<bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"steering_angle", TypeDescriptionResolver<float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
