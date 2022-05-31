/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file coordinate.h
 * @brief This header file defines Coordiante class
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-2-15
 */

#ifndef HOLO_COMMON_COORDINATE_H_
#define HOLO_COMMON_COORDINATE_H_

#include <holo/common/sensor_id.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>
#include <holo/utils/internal/geographical_transformation.h>

namespace holo
{
namespace exception
{
class BadCoordinateConversionException : public std::exception
{
};
}  // namespace exception
namespace common
{
/**
 * @addtogroup common
 * @{
 */

/**
 * @brief Coordinate type represents a coordinate system.
 *
 * @details The Coordinate_t type consists of two parts: @b type and @b param.
 *
 * The @b type part indicates the type of coordinate system. The value should be one of Coordinate::Type.
 * Coordinate types may associate with parameters.
 *
 * The @b param indicates additional information about the coordinate system.
 * The structure of @b param varies from different coordinate types. See @ref page_coordinate_system "Coordinate System"
 * for more details.
 */
class Coordinate
{
public:
    /**
     * @brief Type of coordinate system.
     */
    enum class Type
    {
        UNKNOWN = 0,   ///< Unknown coordinate type.
        VEHICLE = 1,   ///< VEHICLE coordinate.
        WGS84   = 2,   ///< WGS84 coordinate.
        UTM6    = 3,   ///< UTM 6 degree sliced coordinate
        UTM3    = 4,   ///< UTM 3 degree sliced coordinate
        DR      = 5,   ///< Dead reckoning coordinate
        GCJ02   = 11,  ///< GCJ02 coordinate. GuojiaCehuiJu-02

        CUSTOM0 = 12,  ///< User defined coordinate system 0
        CUSTOM1 = 13,  ///< User defined coordinate system 1
        CUSTOM2 = 14,  ///< User defined coordinate system 2
        CUSTOM3 = 15,  ///< User defined coordinate system 3
    };

    static const uint32_t UNKNOWN = 0U;  ///< Unknown coordinate

    static const uint32_t WGS84       = 0x20000000U;  ///< Wgs84
    static const uint32_t GCJ02       = 0xB0000000U;  ///< Gcj02
    static const uint32_t BODY_CENTER = 0x10000C88U;  ///< Body center
    static const uint32_t IMU_MAIN    = 0x12000D88U;  ///< Assume main imu mounted in back trunk center;
    static const uint32_t IMU_VEHICLE = 0x12000C84U;  ///< Assume vehicle imu mounted at chassis rear axle_center;
    static const uint32_t VEHICLE_REAR_AXLE_CENTER = 0x10000C84U;  ///< VEHICLE_REAR_AXLE_CENTER coordinate
    static const uint32_t BODY                     = 0x10000C84U;  ///< Body
    static const uint32_t BODY_GROUND_PROJECTION   = 0x10000F84U;  ///< Body ground-truth projection

    static const uint32_t GRID_WIDTH  = 4096U;
    static const uint32_t GRID_HEIGHT = 4096U;

    /**
     * @brief Default constructor
     */
    Coordinate() noexcept : param_(0), type_(0)
    {
    }

    /**
     * @brief Construct from uint32 value
     *
     * @param value
     */
    Coordinate(uint32_t value) noexcept : param_(value), type_(value >> 28)
    {
    }

    /**
     * @brief Get coordinate type.
     *
     * @return Type of this coordinate.
     */
    Type GetType() const noexcept
    {
        return static_cast<Type>(type_);
    }

    /**
     * @brief Get coordinate parameter.
     *
     * @return Parameter of this coordinate.
     */
    uint32_t GetParam() const noexcept
    {
        return param_;
    }

    /**
     * @brief Get VEHICLE coordinate SensorId parameter.
     *
     * @return The SensorId parameter of this coordinate.
     */
    SensorId GetVehicleSensorId() const noexcept
    {
        return static_cast<SensorId>(param_);
    }

    /**
     * @brief Get UTM zone id(number) parameter.
     *
     * @return Zone id(number) of this coordinate.
     */
    uint32_t GetUtmZoneId() const noexcept
    {
        return param_ & 0x7f;
    }

    /**
     * @brief Get UTM south flag parameter.
     *
     * @return South flag of this coordinate.
     */
    bool_t GetUtmSouthFlag() const noexcept
    {
        return (param_ >> 7) & 0x01;
    }

    /**
     * @brief Get UTM zone parameter.
     * @details UTM zone is consist of two parts: zone_id and south_flag.
     * @f[
     * \begin{bytefield}{8}
     *   \bitheader{0-7} \\
     *   \bitbox{1}{S} & \bitbox{7}{zone\_id}
     * \end{bytefield}
     * @f]
     *
     * @return Zone of this coordinate.
     */
    uint32_t GetUtmZone() const noexcept
    {
        return param_ & 0xff;
    }

    /**
     * @brief Get UTM coordinate offset in easting direction. Unit is GRID_WIDTH.
     *
     * @return Offset in easting direction.
     */
    uint32_t GetUtmOffsetX() const noexcept
    {
        return (param_ >> 20) & 0xff;
    }

    /**
     * @brief Get UTM coordinate offset in northing direction. Unit is GRID_HEIGHT.
     *
     * @return Offset in northing direction.
     */
    uint32_t GetUtmOffsetY() const noexcept
    {
        return (param_ >> 8) & 0x0fff;
    }

    /**
     * @brief Get DR coordinate version.
     *
     * @return DR coordinate version
     */
    uint16_t GetDrVersion() const noexcept
    {
        return static_cast<uint16_t>(param_);
    }

    /**
     * @brief Set coordinate type.
     *
     * @param type Coordinate type.
     */
    void SetType(Type type) noexcept
    {
        type_ = static_cast<uint32_t>(type);
    }

    /**
     * @brief Set Coordinate parameter.
     *
     * @param param Coordinate parameter.
     */
    void SetParam(uint32_t param) noexcept
    {
        param_ = param;
    }

    /**
     * @brief Set SensorId for VEHICLE Coordinate.
     *
     * @param id SensorId.
     */
    void SetVehicleSensorId(SensorId id) noexcept
    {
        param_ = static_cast<uint32_t>(id);
    }

    /**
     * @brief Set UTM Zone ID for UTM Coordinate.
     *
     * @param zone_id Zone ID.
     */
    void SetUtmZoneId(uint8_t zone_id) noexcept
    {
        param_ &= ~(0x7f);
        param_ |= zone_id;
    }

    /**
     * @brief Set South flag for UTM Coordinate.
     *
     * @param south_flag South flag. True for southern semisphere, false for northern semisphere.
     */
    void SetUtmSouthFlag(bool_t south_flag) noexcept
    {
        param_ &= ~(1 << 7);
        param_ |= south_flag << 7;
    }

    /**
     * @brief Set UTM Zone for UTM Coordinate.
     *
     * @param zone Zone.
     */
    void SetUtmZone(uint8_t zone) noexcept
    {
        param_ &= ~(0xff);
        param_ |= zone;
    }

    /**
     * @brief Set offset value in easting direction for UTM Coordinate.
     *
     * @param offset_x Easting direction offset.
     */
    void SetUtmOffsetX(uint32_t offset_x) noexcept
    {
        param_ &= ~(0xff << 20);
        param_ |= offset_x << 20;
    }

    /**
     * @brief Set offset value in northing direction for UTM Coordinate.
     *
     * @param offset_x Northing direction offset.
     */
    void SetUtmOffsetY(uint32_t offset_y) noexcept
    {
        param_ &= ~(0x0fff << 8);
        param_ |= offset_y << 8;
    }

    /**
     * @brief Set version for DR coordinate.
     *
     * @param version DR version
     */
    void SetDrVersion(uint16_t version) noexcept
    {
        param_ &= ~(0xffff);
        param_ |= version;
    }

    /**
     * @brief Assign operator with uint32_t value.
     *
     * @param value Uint32_t coordinate value.
     *
     * @return Reference to this Coordinate.
     */
    Coordinate& operator=(uint32_t value) noexcept
    {
        *reinterpret_cast<uint32_t*>(this) = value;
        return *this;
    }

    /**
     * @brief Cast operator to uint32_t reference type.
     *
     * @return uint32_t reference.
     */
    explicit operator uint32_t&() noexcept
    {
        return *(reinterpret_cast<uint32_t*>(this));
    }

    /**
     * @brief Cast operator to uint32_t const reference type.
     *
     * @return uint32_t reference.
     */
    explicit operator uint32_t const&() const noexcept
    {
        return *(reinterpret_cast<uint32_t const*>(this));
    }

    /**
     * @brief Check if two coordinates are equal.
     *
     * @param other The other coordinate object.
     *
     * @return true if two coordinates are equal otherwise false.
     */
    bool_t operator==(Coordinate const& other) const noexcept
    {
        return (static_cast<uint32_t>(*this) == static_cast<uint32_t>(other));
    }

    /**
     * @brief Check if coordinate equals to uint32_t value.
     *
     * @param value Uint32_t value.
     *
     * @return true if this coordinate object and uint32_t value are equal otherwise false.
     */
    bool_t operator==(uint32_t value) const noexcept
    {
        return (static_cast<uint32_t>(*this) == value);
    }

    /**
     * @brief Check if uint32_t value equals a coordinate object.
     *
     * @param value Uint32 value.
     * @param coord Coordinate value.
     *
     * @return true if uint32_t value equals coord value otherwise false.
     */
    friend bool_t operator==(uint32_t value, Coordinate coord) noexcept
    {
        return (coord == value);
    }

    /**
     * @brief Check if coordinate and uint32_t value are not equal.
     *
     * @param value Uint32_t value.
     *
     * @return true if this coordinate object and uint32_t value are not equal otherwise false.
     */
    bool_t operator!=(uint32_t value) const noexcept
    {
        return !(*this == value);
    }

    /**
     * @brief Check if uint32_t value and a coordinate object are not equal.
     *
     * @param value Uint32 value.
     * @param coord Coordinate value.
     *
     * @return true if uint32_t value and coord value are not equal otherwise false.
     */
    friend bool_t operator!=(uint32_t value, Coordinate coord) noexcept
    {
        return !(coord == value);
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
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << static_cast<uint32_t>(*this);
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        deserializer >> static_cast<uint32_t&>(*this);
    }

    /**
     * @brief Construct Vehicle coordinate
     *
     * @param cat Sensor category
     * @param model Sensor model
     * @param plane Vehicle plane in which the sensor is mounted.
     * @param x Location in x direction.
     * @param y Location in y direction.
     *
     * @return target Vehicle coordinate
     */
    static Coordinate VehicleCoordinate(SensorId::Category cat, SensorId::Model model, VehicleLocation::Plane plane,
                                        VehicleLocation::Location x, VehicleLocation::Location y)
    {
        return Coordinate(static_cast<uint32_t>(Type::VEHICLE) << 28 | static_cast<uint32_t>(cat) << 24 |
                          static_cast<uint32_t>(model) << 16 | static_cast<uint32_t>(plane) << 8 |
                          static_cast<uint32_t>(x) << 4 | static_cast<uint32_t>(y));
    }

    /**
     * @brief Construct WGS84 coordinate
     *
     * @return target WGS84 coordinate
     */
    static Coordinate Wgs84Coordinate()
    {
        return Coordinate(static_cast<uint32_t>(Type::WGS84) << 28);
    }

    /**
     * @brief Construct UTM6 coordinate by zone_id and south_flag and offsets
     *
     * @param[in] zone_id     The zone identifier
     * @param[in] south_flag  The south flag
     * @param[in] offset_x    The offset x
     * @param[in] offset_y    The offset y
     *
     * @return target UTM6 coordinate
     */
    static Coordinate UtmCoordinate(uint8_t zone_id, bool_t south_flag, uint32_t offset_x = 0, uint32_t offset_y = 0)
    {
        return Coordinate(static_cast<uint32_t>(Type::UTM6) << 28 | (offset_x & 0xff) << 20 | (offset_y & 0xfff) << 8 |
                          (south_flag << 7) | (zone_id & 0x7f));
    }

    /**
     * @brief Construct UTM6 coordinate by zone_id and south_flag and offsets
     *
     * @param[in] zone_id     The zone identifier
     * @param[in] south_flag  The south flag
     * @param[in] offset_x    The offset x
     * @param[in] offset_y    The offset y
     *
     * @return target UTM6 coordinate
     */
    static Coordinate Utm6Coordinate(uint8_t zone_id, bool_t south_flag, uint32_t offset_x = 0, uint32_t offset_y = 0)
    {
        return UtmCoordinate(zone_id, south_flag, offset_x, offset_y);
    }

    /**
     * @brief Construct UTM6 coordinate from longitude and latitude
     *
     * @param lon Longitude
     * @param lat Latitude
     *
     * @return UTM6 coordinate the lon/lat point lays in.
     */
    static Coordinate UtmCoordinate(float64_t lon, float64_t lat)
    {
        return Coordinate(static_cast<uint32_t>(Type::UTM6) << 28 | (lat < 0) << 7 |
                          holo::utils::LonLatGetUtmZoneId(lon, lat));
    }

    /**
     * @brief Construct UTM6 coordinate from longitude and latitude
     *
     * @param lon Longitude
     * @param lat Latitude
     *
     * @return UTM6 coordinate the lon/lat point lays in.
     */
    static Coordinate Utm6Coordinate(float64_t lon, float64_t lat)
    {
        return UtmCoordinate(lon, lat);
    }

    /**
     * @brief Construct UTM6 coordinate from a lon/lat point type.
     *
     * @tparam PointType The lon/lat point type
     * @param pt The lon/lat point.
     *
     * @return UTM6 cooridnate the lon/lat point lays in.
     */
    template <typename PointType>
    static Coordinate UtmCoordinate(PointType const& pt)
    {
        return Coordinate(static_cast<uint32_t>(Type::UTM6) << 28 | (pt[1U] < 0) << 7 |
                          holo::utils::LonLatGetUtmZoneId(pt[0U], pt[1U]));
    }

    /**
     * @brief Construct UTM6 coordinate from a lon/lat point type.
     *
     * @tparam PointType The lon/lat point type.
     * @param pt The lon/lat point.
     *
     * @return UTM6 cooridnate the lon/lat point lays in.
     */
    template <typename PointType>
    static Coordinate Utm6Coordinate(PointType const& pt)
    {
        return UtmCoordinate(pt);
    }

    /**
     * @brief Construct UTM3 coordinate by zone_id and south_flag and offsets
     *
     * @param[in] zone_id     The zone identifier
     * @param[in] south_flag  The south flag
     * @param[in] offset_x    The offset x
     * @param[in] offset_y    The offset y
     *
     * @return target UTM3 coordinate
     */
    static Coordinate Utm3Coordinate(uint8_t zone_id, bool_t south_flag, uint32_t offset_x = 0, uint32_t offset_y = 0)
    {
        return Coordinate(static_cast<uint32_t>(Type::UTM3) << 28 | (offset_x & 0xff) << 20 | (offset_y & 0xfff) << 8 |
                          (south_flag << 7) | (zone_id & 0x7f));
    }

    /**
     * @brief Construct DR coordinate
     *
     * @param version DR coordinate version.
     *
     * @return target DR coordiante
     */
    static Coordinate DrCoordinate(uint16_t version)
    {
        return Coordinate(static_cast<uint32_t>(Type::DR) << 28 | version);
    }

    /**
     * @brief Construct GCJ02 coordinate
     *
     * @return target GCJ02 coordinate
     */
    static Coordinate Gcj02Coordinate()
    {
        return Coordinate(static_cast<uint32_t>(Type::GCJ02) << 28);
    }

    /**
     * @brief Convert a point in Lon/Lat coordinate to a point in given UTM coordinate.
     *
     * @tparam InPointType Input point type.
     * @tparam OutPointType Output point type.
     * @param[in] src_pt The point in lon/lat coordinate to be converted.
     * @param[in] dst_coord Destination coordinate to convert src_pt to.
     * @param[out] dst_pt The converted point in dst_coord coordinate.
     */
    template <typename InPointType, typename OutPointType>
    static void PointConvertLonLatToUtm(InPointType const& src_pt, Coordinate const& dst_coord, OutPointType& dst_pt)
    {
        holo::utils::LonLatToUtm(src_pt[0U], src_pt[1U], dst_coord.GetUtmZoneId(),
                                 dst_coord.GetUtmSouthFlag(), dst_pt[0U], dst_pt[1U]);
        dst_pt[0U] -= dst_coord.GetUtmOffsetX() * GRID_WIDTH;
        dst_pt[1U] -= dst_coord.GetUtmOffsetY() * GRID_HEIGHT;
    }

    /**
     * @brief Convert a point in UTM coordinate to Lon/Lat coordinate.
     *
     * @tparam InPointType Input point type.
     * @tparam OutPointType Output point type.
     * @param[in] src_coord The UTM coordinate src_pt is in.
     * @param[in] src_pt The point in UTM coordinate to be converted.
     * @param[out] dst_pt The converted point in Lon/Lat coordinate.
     */
    template <typename InPointType, typename OutPointType>
    static void PointConvertUtmToLonLat(Coordinate const& src_coord, InPointType const& src_pt, OutPointType& dst_pt)
    {
        float64_t utm_easting  = src_pt[0U] + src_coord.GetUtmOffsetX() * GRID_WIDTH;
        float64_t utm_northing = src_pt[1U] + src_coord.GetUtmOffsetY() * GRID_HEIGHT;
        holo::utils::UtmToLonLat(src_coord.GetUtmZoneId(), src_coord.GetUtmSouthFlag(), utm_easting, utm_northing,
                                 dst_pt[0U], dst_pt[1U]);
    }

    /**
     * @brief Convert a point in UTM coordinate to a point in another UTM coordinate.
     *
     * @tparam InPointType Input point type.
     * @tparam OutPointType Output point type.
     * @param[in] src_coord The UTM coordinate src_pt is in.
     * @param[in] src_pt The point in UTM coordinate to be converted.
     * @param[in] dst_coord The UTM coordinate src_pt is converted to.
     * @param[out] dst_pt The converted point in dst_coord coordinate.
     */
    template <typename InPointType, typename OutPointType>
    static void PointConvertUtmToUtm(Coordinate const& src_coord, InPointType const& src_pt,
                                     Coordinate const& dst_coord, OutPointType& dst_pt)
    {
        if (src_coord.GetUtmZone() == dst_coord.GetUtmZone())
        {
            dst_pt[0U] =
                src_pt[0U] +
                static_cast<int32_t>(src_coord.GetUtmOffsetX() - dst_coord.GetUtmOffsetX()) * GRID_WIDTH;
            dst_pt[1U] =
                src_pt[1U] +
                static_cast<int32_t>(src_coord.GetUtmOffsetY() - dst_coord.GetUtmOffsetY()) * GRID_HEIGHT;
        }
        else
        {
            PointConvertUtmToLonLat(src_coord, src_pt, dst_pt);
            PointConvertLonLatToUtm(dst_pt, dst_coord, dst_pt);
        }
    }

    /**
     * @brief Convert a point from one coordinate to another coordinate
     *
     * @tparam InPointType Input point type.
     * @tparam OutPointType Output point type.
     * @param[in] src_coord The coordinate src_pt is in.
     * @param[in] src_pt The point to be converted.
     * @param[in] dst_coord The coordinate src_pt is converted to.
     * @param[out] dst_pt The converted point in dst_coord coordinate.
     */
    template <typename InPointType, typename OutPointType>
    static void PointConvert(Coordinate const& src_coord, InPointType& src_pt, Coordinate const& dst_coord,
                             OutPointType& dst_pt)
    {
        if (src_coord == dst_coord)
        {
            dst_pt[0U] = src_pt[0U];
            dst_pt[1U] = src_pt[1U];
        }
        else
        {
            if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType())
            {
                PointConvertUtmToUtm(src_coord, src_pt, dst_coord, dst_pt);
            }
            else if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) &&
                     (Type::UTM6 == dst_coord.GetType()))
            {
                PointConvertLonLatToUtm(src_pt, dst_coord, dst_pt);
            }
            else if ((Type::UTM6 == src_coord.GetType()) &&
                     (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType()))
            {
                PointConvertUtmToLonLat(src_coord, src_pt, dst_pt);
            }
            else
            {
                throw holo::exception::BadCoordinateConversionException();
            }
        }
    }

private:
    uint32_t param_ : 28;  ///< Coordinate parameter.
    uint32_t type_ : 4;    ///< Coordinate type.
};

/**
 * @}
 */

}  // namespace common
}  // namespace holo

#endif

