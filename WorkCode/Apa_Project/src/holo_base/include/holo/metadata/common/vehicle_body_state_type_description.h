#ifndef HOLO_METADATA_COMMON_VEHICLE_BODY_STATE_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_VEHICLE_BODY_STATE_TYPE_DESCRIPTION_H_

#include <holo/common/vehicle_body_state.h>
#include <holo/metadata/common/timestamp_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::VehicleBodyState, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto state_desc =
            std::make_shared<TypeDescriptionBitmask>(ALIGN, IS_BIG_ENDIAN, "holo::common::VehicleBodyState::State");
        (void)state_desc
            ->SetBits({{1, "LEFT_TURN_SIGNAL_ON"},
                           {2, "RIGHT_TURN_SIGNAL_ON"},
                           {3, "HARZARD_FLASHER_ON"},
                           {4, "LOW_BEAM_ON"},
                           {5, "HIGH_BEAM_ON"},
                           {6, "BRAKE_LIGHT_ON"},
                           {7, "FRONT_FOG_LIGHT_ON"},
                           {8, "REAR_FOG_LIGHT_ON"},
                           {9, "CHARGING_CAP_OPEN"},
                           {10, "FAST_CHARGING_CAP_OPEN"},
                           {11, "LEFT_REARVIEW_MIRROR_FOLD"},
                           {12, "RIGHT_REARVIEW_MIRROR_FOLD"},
                           {13, "DRIVER_SEATBELT_UNLOCK"},
                           {14, "CODRIVER_SEATBELT_UNLOCK"},
                           {15, "PASSENGER_SEATBELT_UNLOCK"},
                           {16, "DRIVER_ABSENT"},
                           {17, "FRONT_WIPER_ON"},
                           {18, "REAR_WIPER_ON"},
                           {19, "FRONT_LEFT_DOOR_OPEN"},
                           {20, "FRONT_RIGHT_DOOR_OPEN"},
                           {21, "REAR_LEFT_DOOR_OPEN"},
                           {22, "REAR_RIGHT_DOOR_OPEN"},
                           {23, "CAR_HOOD_OPEN"},
                           {24, "TRUNK_DOOR_OPEN"},
                           {25, "FRONT_LEFT_WINDOW_OPEN"},
                           {26, "FRONT_RIGHT_WINDOW_OPEN"},
                           {27, "REAR_LEFT_WINDOW_OPEN"},
                           {28, "REAR_RIGHT_WINDOW_OPEN"},
                           {29, "SUNROOF_WINDOW_OPEN"},
                           {30, "POWERTRAIN_NOT_READY"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto invalid_flag_desc = std::make_shared<TypeDescriptionBitmask>(
            ALIGN, IS_BIG_ENDIAN, "holo::common::VehicleBodyState::InvalidFlags");
        (void)invalid_flag_desc
            ->SetBits({{1, "LEFT_TURN_SIGNAL_INVALID"},    {2, "RIGHT_TURN_SIGNAL_INVALID"},
                           {3, "HARZARD_FLASHER_INVALID"},     {4, "LOW_BEAM_INVALID"},
                           {5, "HIGH_BEAM_INVALID"},           {6, "BRAKE_LIGHT_INVALID"},
                           {7, "FRONT_FOG_LIGHT_INVALID"},     {8, "REAR_FOG_LIGHT_INVALID"},
                           {9, "CHARGING_CAP_INVALID"},        {10, "FAST_CHARGING_CAP_INVALID"},
                           {11, "LEFT_REARVIEW_MIRROR_FOLD"},  {12, "RIGHT_REARVIEW_MIRROR_FOLD"},
                           {13, "DRIVER_SEATBELT_INVALID"},    {14, "CODRIVER_SEATBELT_INVALID"},
                           {15, "PASSENGER_SEATBELT_INVALID"}, {16, "DRIVER_ABSENT_INVALID"},
                           {17, "FRONT_WIPER_INVALID"},        {18, "REAR_WIPER_INVALID"},
                           {19, "FRONT_LEFT_DOOR_INVALID"},    {20, "FRONT_RIGHT_DOOR_INVALID"},
                           {21, "REAR_LEFT_DOOR_INVALID"},     {22, "REAR_RIGHT_DOOR_INVALID"},
                           {23, "CAR_HOOD_INVALID"},           {24, "TRUNK_DOOR_INVALID"},
                           {25, "FRONT_LEFT_WINDOW_INVALID"},  {26, "FRONT_RIGHT_WINDOW_INVALID"},
                           {27, "REAR_LEFT_WINDOW_INVALID"},   {28, "REAR_RIGHT_WINDOW_INVALID"},
                           {29, "SUNROOF_WINDOW_INVALID"},     {30, "POWERTRAIN_INVALID"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionStruct>(ALIGN, IS_BIG_ENDIAN, "holo::common::VehicleBodyState");
        (void)desc->SetTemplates({}).SetMembers(
            {{"timestamp", TypeDescriptionResolver<holo::common::Timestamp, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_left_tire_pressure", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"front_right_tire_pressure", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rear_left_tire_pressure", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"rear_right_tire_pressure", TypeDescriptionResolver<holo::float32_t, ALIGN, IS_BIG_ENDIAN>::Get()},
             {"state_flags", state_desc},
             {"invalid_flags", invalid_flag_desc}});
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo
#endif
