/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sensor_id.h
 * @brief This header file defines SensorId class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2019-12-11
 */

#ifndef HOLO_COMMON_SENSOR_ID_H_
#define HOLO_COMMON_SENSOR_ID_H_

#include <holo/core/types.h>
#include <holo/common/vehicle_location.h>
#include <holo/serialization/serialization.h>

namespace holo
{

namespace common
{

/**
 * @brief SensorId class.
 *
 * @details A sensor-id is consist of three parts: Category, Model and Location.
 *
 * @verbatim
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-------+-------+---------------+-------------------------------+
 * |  RSV  |  CAT  |     MODEL     |           LOCATION            |
 * +-------+-------+---------------+-------------------------------+
 * @endverbatim
 * 
 * RSV: Reserved.
 *
 * CAT: Sensor type category. See SensorId::SensorCategory for possible values.
 *
 * MODEL: Model of the sensor. See SensorId::Model for possible values for each sensor-category.
 *
 * LOCATION: Location of type ::holo::common::VehicleLocation indicating where sensor is mounted.
 */
class SensorId
{
public:

    /**
     * @brief Enumerate sensor Categories.
     * 
     * @note Category is only 4-bit long, value range is [0, 15].
     */
    enum class Category: uint8_t
    {
        UNKNOWN  = 0x0, ///< Unknown category
        GNSS     = 0x1, ///< GNSS
        IMU      = 0x2, ///< IMU
        CAMERA   = 0x3, ///< CAMERA
        RADAR    = 0x4, ///< RADAR
        USS      = 0x5, ///< USS
        LIDAR    = 0x6, ///< LIDAR
        AUDIO    = 0x7, ///< AUDIO
        JOYSTICK = 0x8, ///< JOYSTICK
    };

    /**
     * @brief Enumerate sensor models.
     */
    enum class Model: uint8_t
    {
        UNKNOWN               = 0x00,

        GNSS_UNKNOWN          = 0x00,
        GNSS_NOVATEL          = 0x01,
        GNSS_XSENS            = 0x02,
        GNSS_UBLOX_M8L        = 0x03,
        GNSS_UBLOX_M8T        = 0x04,
        GNSS_UBLOX_M8Z        = 0x05,
        GNSS_UBLOX_F9         = 0x06,
        GNSS_QIANXU           = 0x07,
        GNSS_SCT_LANETO       = 0x08,
        GNSS_SPATIAL          = 0x09,
        GNSS_UNICORE          = 0x0A,
        GNSS_BDSTAR_NPOS220   = 0x0B,

        IMU_UNKNOWN           = 0x00,
        IMU_NOVATEL           = 0x01,
        IMU_XSENS             = 0x02,
        IMU_UBLOX_M8L         = 0x03,
        IMU_UBLOX_F9K         = 0x04,
        IMU_ACEINNA_305       = 0x05,
        IMU_ACEINNA_330       = 0x06,
        IMU_MURATA_2230       = 0x07,

        CAMERA_UNKNOWN        = 0x00,
        CAMERA_MOBILEYE_EQ3   = 0x01,
        CAMERA_MOBILEYE_EQ4   = 0x02,
        CAMERA_BOSCH_MPC      = 0x03,
        CAMERA_DELPHI_IFV300  = 0x04,
        CAMERA_CALMCAR        = 0x05,
        CAMERA_ENTRON_F001R   = 0x06,
        CAMERA_ENTRON_S001R   = 0x07,
        CAMERA_LEOPARD_M021   = 0x08,
        CAMERA_LEOPARD_AR0231 = 0x09,
        CAMERA_LEOPARD_OV490  = 0x0A,
        CAMERA_LEOPARD_AP020  = 0x0B,

        RADAR_UNKNOWN         = 0x00,
        RADAR_CONTI_308       = 0x01,
        RADAR_CONTI_408       = 0x02,
        RADAR_CONTI_430       = 0x03,
        RADAR_BOSCH_MRR4      = 0x04,
        RADAR_DELPHI_ESR      = 0x05,
        RADAR_DELPHI_RSDS     = 0x06,

        USS_UNKNOWN           = 0x00,
        USS_BOSCH             = 0x01,
        USS_IS                = 0x02,
        USS_SOFTEC            = 0x03,

        LIDAR_UNKNOWN         = 0x00,
        LIDAR_IBEO_SCALA      = 0x01,
        LIDAR_IBEO_LUX        = 0x02,
        LIDAR_VLP_16L         = 0x03,
        LIDAR_VLP_16L_HRS     = 0x04,
        LIDAR_VLP_32L         = 0x05,
        LIDAR_PANDAR_40L      = 0x06,
        LIDAR_LIVOX_MID40     = 0x07,
        LIDAR_LIVOX_MID100    = 0x08,
        LIDAR_LEISHEN_8L      = 0x09,
        LIDAR_LEISHEN_16L     = 0x0A,
        LIDAR_BENEWAKE        = 0x0B,
        LIDAR_OUSTER          = 0x0C,
        LIDAR_SURESTAR        = 0x0D,
        LIDAR_ROBOSENSE       = 0x0E,

        AUDIO_UNKNOWN         = 0x00,

        JOYSTICK_UNKNOWN      = 0x00,
        JOYSTICK_BETOP        = 0x01,
    };

    /**
     * @brief Default constructor.
     *
     * @exceptsafe: No throw.
     */
    SensorId() noexcept: 
        location_(VehicleLocation()),
        model_(Model::UNKNOWN),
        category_(Category::UNKNOWN)
    {}

    /**
     * @brief Construct from uint32_t value.
     *
     * @param value Value to initialize SensorId.
     *
     * @exceptsafe: No throw.
     *
     * @note The high 4-bit of value will be ignored.
     */
    SensorId(uint32_t value) noexcept:
        location_(static_cast<uint16_t>(value)),
        model_(static_cast<Model>(value >> 16)),
        category_(static_cast<Category>((value >> 24) & 0x0f))
    {}

    /**
     * @brief Construct from category, model and location.
     *
     * @param cat Category of the sensor.
     * @param model Model of the sensor.
     * @param location Mount location of the sensor.
     * 
     * @exceptsafe No throw.
     */
    SensorId(Category cat, Model model = Model::UNKNOWN, VehicleLocation const& location = VehicleLocation()) noexcept:
        location_(location),
        model_(model),
        category_(cat)
    {}

    /**
     * @brief Assign operator. Enable initialize from uint32_t.
     *
     * @param value Value to initialize SensorId.
     *
     * @return Reference to sensor_id object.
     *
     * @exceptsafe No throw.
     */
    SensorId& operator=(uint32_t value) noexcept
    {
        location_ = static_cast<uint16_t>(value);
        model_ = static_cast<Model>(value >> 16);
        category_ = static_cast<Category>((value >> 24) & 0x0f);
        return *this;
    }

    /**
     * @brief Cast operator. Enable cast to uint32_t type.
     *
     * @return uint32_t type value.
     *
     * @exceptsafe No throw.
     */
    operator uint32_t() const noexcept
    {
        return static_cast<uint32_t>(category_) << 24 | 
               static_cast<uint32_t>(model_) << 16 | 
               static_cast<uint32_t>(location_);
    }

    /**
     * @brief Set sensor location
     *
     * @param location Location of the sensor.
     *
     * @exceptsafe No throw.
     */
    void SetLocation(VehicleLocation const& location) noexcept
    {
        location_ = location;
    }

    /**
     * @brief Get sensor location
     *
     * @return Location of the sensor.
     *
     * @exceptsafe No throw.
     */
    VehicleLocation const& GetLocation() const noexcept
    {
        return location_;
    }

    /**
     * @brief Get sensor location
     *
     * @return Location of the sensor.
     *
     * @exceptsafe No throw.
     */
    VehicleLocation& GetLocation() noexcept
    {
        return location_;
    }

    /**
     * @brief Set sensor model
     *
     * @param model Model of the sensor.
     *
     * @exceptsafe No throw.
     */
    void SetModel(Model model) noexcept
    {
        model_ = model;
    }

    /**
     * @brief Get sensor model
     *
     * @return Model of the sensor.
     *
     * @exceptsafe No throw.
     */
    Model GetModel() const noexcept
    {
        return model_;
    }

    /**
     * @brief Set sensor category
     *
     * @param cat Category of the sensor.
     *
     * @exceptsafe No throw.
     */
    void SetCategory(Category cat) noexcept
    {
        category_ = cat;
    }

    /**
     * @brief Get sensor category
     *
     * @return Category of the sensor.
     *
     * @exceptsafe No throw.
     */
    Category GetCategory() const noexcept
    {
        return category_;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return sizeof(uint32_t);
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << (uint32_t)(*this);
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t value = 0;
        deserializer >> value;
        *this = value;
    }

private:

    template<uint8_t Alignment>
    uint32_t getSerializedSize() const noexcept;
    template<uint8_t Alignment>
    uint32_t serialize(uint8_t* buffer, uint32_t buffer_size) const;
    template<uint8_t Alignment>
    uint32_t deserialize(const uint8_t* buffer, uint32_t buffer_size);

    VehicleLocation location_;
    Model model_;
    Category category_;
};

} // namespace common
} // namespace holo

#endif
