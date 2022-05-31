#ifndef HOLO_METADATA_COMMON_SENSOR_ID_TYPE_DESCRIPTION_H_
#define HOLO_METADATA_COMMON_SENSOR_ID_TYPE_DESCRIPTION_H_

#include <holo/common/sensor_id.h>
#include <holo/metadata/common/vehicle_location_type_description.h>
#include <holo/metadata/type_description.h>

namespace holo
{
namespace metadata
{
template <size_t ALIGN, bool IS_BIG_ENDIAN>
struct TypeDescriptionResolver<holo::common::SensorId, ALIGN, IS_BIG_ENDIAN>
{
    static TypeDescription::PtrType Get() noexcept
    {
        auto sensor_id_category =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::SensorId::Category");
        (void)sensor_id_category
            ->SetEnumerates({{0x0, "UNKNOWN"},
                             {0x1, "GNSS"},
                             {0x2, "IMU"},
                             {0x3, "CAMERA"},
                             {0x4, "RADAR"},
                             {0x5, "USS"},
                             {0x6, "LIDAR"},
                             {0x7, "AUDIO"},
                             {0x8, "JOYSTICK"}})
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto sensor_id_model =
            std::make_shared<TypeDescriptionEnumerate>(ALIGN, IS_BIG_ENDIAN, "holo::common::SensorId::Model");
        (void)sensor_id_model
            ->SetEnumerates({
                {0x0, "UNKNOWN"},

                {0x0, "GNSS_UNKNOWN"},
                {0x1, "GNSS_NOVATEL"},
                {0x2, "GNSS_XSENS"},
                {0x3, "GNSS_UBLOX_M8L"},
                {0x4, "GNSS_UBLOX_M8T"},
                {0x5, "GNSS_UBLOX_M8Z"},
                {0x6, "GNSS_UBLOX_F9"},
                {0x7, "GNSS_QIANXU"},
                {0x8, "GNSS_SCT_LANETO"},
                {0x9, "GNSS_SPATIAL"},
                {0xA, "GNSS_UNICORE"},
                {0xB, "GNSS_BDSTAR_NPOS220"},

                {0x0, "IMU_UNKNOWN"},
                {0x1, "IMU_NOVATEL"},
                {0x2, "IMU_XSENS"},
                {0x3, "IMU_UBLOX_M8L"},
                {0x4, "IMU_UBLOX_F9K"},
                {0x5, "IMU_ACEINNA_305"},
                {0x6, "IMU_ACEINNA_330"},
                {0x7, "IMU_MURATA_2230"},

                {0x0, "CAMERA_UNKNOWN"},
                {0x1, "CAMERA_MOBILEYE_EQ3"},
                {0x2, "CAMERA_MOBILEYE_EQ4"},
                {0x3, "CAMERA_BOSCH_MPC"},
                {0x4, "CAMERA_DELPHI_IFV300"},
                {0x5, "CAMERA_CALMCAR"},
                {0x6, "CAMERA_ENTRON_F001R"},
                {0x7, "CAMERA_ENTRON_S001R"},
                {0x8, "CAMERA_LEOPARD_M021"},
                {0x9, "CAMERA_LEOPARD_AR0231"},
                {0xA, "CAMERA_LEOPARD_OV490"},
                {0xB, "CAMERA_LEOPARD_AP020"},

                {0x0, "RADAR_UNKNOWN"},
                {0x1, "RADAR_CONTI_308"},
                {0x2, "RADAR_CONTI_408"},
                {0x3, "RADAR_CONTI_430"},
                {0x4, "RADAR_BOSCH_MRR4"},
                {0x5, "RADAR_DELPHI_ESR"},
                {0x6, "RADAR_DELPHI_RSDS"},

                {0x0, "USS_UNKNOWN"},
                {0x1, "USS_BOSCH"},
                {0x2, "USS_IS"},
                {0x3, "USS_SOFTEC"},

                {0x0, "LIDAR_UNKNOWN"},
                {0x1, "LIDAR_IBEO_SCALA"},
                {0x2, "LIDAR_IBEO_LUX"},
                {0x3, "LIDAR_VLP_16L"},
                {0x4, "LIDAR_VLP_16L_HRS"},
                {0x5, "LIDAR_VLP_32L"},
                {0x6, "LIDAR_PANDAR_40L"},
                {0x7, "LIDAR_LIVOX_MID40"},
                {0x8, "LIDAR_LIVOX_MID100"},
                {0x9, "LIDAR_LEISHEN_8L"},
                {0xA, "LIDAR_LEISHEN_16L"},
                {0xB, "LIDAR_BENEWAKE"},
                {0xC, "LIDAR_OUSTER"},
                {0xD, "LIDAR_SURESTAR"},
                {0xE, "LIDAR_ROBOSENSE"},

                {0x0, "AUDIO_UNKNOWN"},

                {0x0, "JOYSTICK_UNKNOWN"},
                {0x1, "JOYSTICK_BETOP"},
            })
            .SetUnderlyingType(TypeDescriptionResolver<uint8_t, ALIGN, IS_BIG_ENDIAN>::Get());

        auto desc = std::make_shared<TypeDescriptionBitfield>(ALIGN, IS_BIG_ENDIAN, "holo::common::SensorId");
        (void)desc->SetFields({{"category", 24, 4, sensor_id_category},
                         {"model", 16, 8, sensor_id_model},
                         {"location", 0, 16,
                          TypeDescriptionResolver<holo::common::VehicleLocation, ALIGN, IS_BIG_ENDIAN>::Get()}})
            .SetUnderlyingType(TypeDescriptionResolver<uint32_t, ALIGN, IS_BIG_ENDIAN>::Get());
        return desc;
    }
};

}  // namespace metadata
}  // namespace holo

#endif
