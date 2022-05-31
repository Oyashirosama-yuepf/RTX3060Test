#ifndef HOLO_METADATA_COMMON_CONTROL_COMMAND_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_CONTROL_COMMAND_TYPE_DESCRIPTION_H_

#include <holo/common/control_command.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::ControlCommand, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto lateral_control_model_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::ControlCommand::LateralControlModel");
        (void)lateral_control_model_desc
            ->SetEnumerates({{0U, "DISABLE"}, {1U, "TORQUE"}, {2U, "FRONT_WHEEL_ANGLE"}, {3U, "STEERING_ANGLE"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto longitudinal_control_model_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::ControlCommand::LongitudinalControlModel");
        (void)longitudinal_control_model_desc
            ->SetEnumerates({{0U, "DISABLE"},
                             {1U, "ACCELERATION"},
                             {2U, "DECELERATION"},
                             {3U, "TORQUE"},
                             {4U, "TORQUE_DECELERATION"},
                             {5U, "PARK"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto gear_control_model_desc = std::make_shared<TypeDescriptionEnumerate>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::ControlCommand::GearControlModel");
        (void)gear_control_model_desc->SetEnumerates({{0U, "DISABLE"}, {1U, "GEAR_CONTROL"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto gear_position_desc = std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "GearPosition");
        (void)gear_position_desc
            ->SetEnumerates({{0, "UNKNOWN"}, {1, "P"}, {2, "R"}, {3, "N"}, {4, "D"}, {5, "S"}, {6, "INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto gear_control_command_desc = std::make_shared<TypeDescriptionBitfield>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::ControlCommand::GearControlCommand");
        (void)gear_control_command_desc
            ->SetFields({{"handbrake", 0, 1, TypeDescriptionResolver<holo::bool_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"gear_level", 1, 4, TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get()},
                         {"gear_position", 5, 3, gear_position_desc}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::ControlCommand");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"lateral_control_model", lateral_control_model_desc},
             {"longitudinal_control_model", longitudinal_control_model_desc},
             {"gear_control_model", gear_control_model_desc},
             {"gear_control_command", gear_control_command_desc},
             {"lateral_control_value", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_control_value1", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"longitudinal_control_value2", TypeDescriptionResolver<::holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
