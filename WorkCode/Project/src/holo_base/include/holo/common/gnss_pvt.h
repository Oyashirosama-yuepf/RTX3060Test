/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_pvt.h
 * @brief This header file defines GnssPvt class.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @date 2020-3-25
 */

#ifndef HOLO_COMMON_GNSS_PVT_H_
#define HOLO_COMMON_GNSS_PVT_H_

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/core/types.h>

#include <array>
#include <cmath>
#include <tuple>

namespace holo
{
namespace common
{
/**
 * @brief This class provide GNSS Position Velocity and Time information.
 */
class GnssPvt
{
public:
    enum class Mode : uint8_t
    {
        NO_POSITION   = 0x00,
        TIMING_ONLY   = 0x01,
        SINGLE_FIX    = 0x02,
        DIFF_POSITION = 0x03,
        RTK_FLOAT_FIX = 0x04,
        RTK_INT_FIX   = 0x05,
    };

    /**
     * @brief Default constructor.
     */
    GnssPvt()
      : stamp_{}
      , coordinate_(Coordinate::Wgs84Coordinate())
      , status_{}
      , longitude_{}
      , latitude_{}
      , height_{}
      , velocity_east_{}
      , velocity_north_{}
      , velocity_up_{}
      , longitude_cov_{}
      , latitude_cov_{}
      , height_cov_{}
      , velocity_east_cov_{}
      , velocity_north_cov_{}
      , velocity_up_cov_{}
    {
    }

    /**
     * @brief Get timestamp
     *
     * @return Reference to timestamp
     */
    Timestamp& GetTimestamp() noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get timestamp
     *
     * @return Reference to timestamp
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Get coordinate
     *
     * @return Coordinate object
     */
    Coordinate GetCoordinate() const noexcept
    {
        return coordinate_;
    }

    /**
     * @brief Test if position is valid.
     *
     * @return true if position is valid otherwise false.
     */
    bool_t IsPositionValid() const noexcept
    {
        return status_ & 0x01;
    }

    /**
     * @brief Test if velocity is valid.
     *
     * @return true if velocity is valid otherwise false.
     */
    bool_t IsVelocityValid() const noexcept
    {
        return status_ & 0x02;
    }

    /**
     * @brief Test if position and velocity are valid.
     *
     * @return true if position and velocity are valid otherwise false.
     */
    bool_t IsValid() const noexcept
    {
        return (status_ & 0x01) && (status_ & 0x02);
    }

    /**
     * @brief Test if position covariance is valid.
     *
     * @return true if position covariance is valid otherwise false.
     */
    bool_t IsPositionCovValid() const noexcept
    {
        return status_ & 0x04;
    }

    /**
     * @brief Test if velocity covariance is valid.
     *
     * @return true if velocity covariance is valid otherwise false.
     */
    bool_t IsVelocityCovValid() const noexcept
    {
        return status_ & 0x08;
    }

    /**
     * @brief Test if position and velocity covariance are valid.
     *
     * @return true if position and velocity covariance are valid otherwise false.
     */
    bool_t IsCovValid() const noexcept
    {
        return (status_ & 0x04) && (status_ & 0x08);
    }

    /**
     * @brief Get gnss positioning mode.
     *
     * @return Positioning mode
     */
    Mode GetMode() const noexcept
    {
        return static_cast<Mode>(status_ >> 8);
    }

    /**
     * @brief Get longitude value. Unit: degree. Range: [-180, 180)
     *
     * @return Longitude
     */
    float64_t GetLongitude() const noexcept
    {
        return longitude_;
    }

    /**
     * @brief Get latitude value. Unit: degree. Range: [-90, 90]
     *
     * @return Latitude
     */
    float64_t GetLatitude() const noexcept
    {
        return latitude_;
    }

    /**
     * @brief Get height value in geodetic height system. Unit: m
     *
     * @return Height
     */
    float64_t GetHeight() const noexcept
    {
        return height_;
    }

    /**
     * @brief Get velocity in east direction. Unit: m/s
     *
     * @return East velocity
     */
    float64_t GetVelocityEast() const noexcept
    {
        return velocity_east_;
    }

    /**
     * @brief Get velocity in north direction. Unit: m/s
     *
     * @return North velocity
     */
    float64_t GetVelocityNorth() const noexcept
    {
        return velocity_north_;
    }

    /**
     * @brief Get velocity in up dirction. Unit: m/s
     *
     * @return Up velocity
     */
    float64_t GetVelocityUp() const noexcept
    {
        return velocity_up_;
    }

    /**
     * @brief Get longitude covariance. Unit: m^2.
     *
     * @return Longitude covariance.
     */
    float64_t GetLongitudeCov() const noexcept
    {
        return longitude_cov_;
    }

    /**
     * @brief Get latitude covariance. Unit: m^2.
     *
     * @return Latitude covariance.
     */
    float64_t GetLatitudeCov() const noexcept
    {
        return latitude_cov_;
    }

    /**
     * @brief Get height covariance. Unit: m^2.
     *
     * @return Height covariance.
     */
    float64_t GetHeightCov() const noexcept
    {
        return height_cov_;
    }

    /**
     * @brief Get velocity covariance in east direction. Unit: (m/s)^2.
     *
     * @return East velocity covariance.
     */
    float64_t GetVelocityEastCov() const noexcept
    {
        return velocity_east_cov_;
    }

    /**
     * @brief Get velocity covariance in north direction. Unit: (m/s)^2.
     *
     * @return North velocity covariance.
     */
    float64_t GetVelocityNorthCov() const noexcept
    {
        return velocity_north_cov_;
    }

    /**
     * @brief Get velocity covariance in up direction. Unit: (m/s)^2.
     *
     * @return Up velocity covariance.
     */
    float64_t GetVelocityUpCov() const noexcept
    {
        return velocity_up_cov_;
    }

    /**
     * @brief Set timestamp value.
     *
     * @param stamp Timestamp value.
     */
    void SetTimestamp(Timestamp const& stamp) noexcept
    {
        stamp_ = stamp;
    }

    /**
     * @brief Set coordinate value.
     *
     * @param coordinate Coordinate value.
     */
    void SetCoordinate(Coordinate coordinate) noexcept
    {
        coordinate_ = coordinate;
    }

    /**
     * @brief Set flags to indicate which part of GnssPvt is valid.
     *
     * @param position Position is valid.
     * @param velocity Velocity is valid.
     * @param position_cov Position covariance is valid.
     * @param velocity_cov Velocity covariance is valid.
     */
    void SetValidFlags(bool_t position, bool_t velocity, bool_t position_cov, bool_t velocity_cov) noexcept
    {
        status_ &= ~0x0f;
        status_ |= (position << 0) | (velocity << 1) | (position_cov << 2) | (velocity_cov << 3);
    }

    /**
     * @brief Set gnss positioning mode.
     *
     * @param mode Positioning mode.
     */
    void SetMode(Mode mode) noexcept
    {
        status_ &= ~(0xff << 8);
        status_ |= static_cast<uint32_t>(mode) << 8;
    }

    /**
     * @brief Set longitude value. Unit: degree. Range: [-180, 180).
     *
     * @param value Longitude value.
     */
    void SetLongitude(float64_t value) noexcept
    {
        longitude_ = value;
    }

    /**
     * @brief Set latitude value. Unit: degree. Range: [-90, 90]
     *
     * @param value Latitude value.
     */
    void SetLatitude(float64_t value) noexcept

    {
        latitude_ = value;
    }

    /**
     * @brief Set height value in geodetic height system.
     *
     * @param value Height value.
     */
    void SetHeight(float64_t value) noexcept
    {
        height_ = value;
    }

    /**
     * @brief Set velocity in east direction. Unit: m/s.
     *
     * @param value East velocity value.
     */
    void SetVelocityEast(float64_t value) noexcept
    {
        velocity_east_ = value;
    }

    /**
     * @brief Set velocity in north direction. Unit: m/s.
     *
     * @param value North velocity value.
     */
    void SetVelocityNorth(float64_t value) noexcept
    {
        velocity_north_ = value;
    }

    /**
     * @brief Set velocity in up direction. Unit: m/s.
     *
     * @param value Up velocity value.
     */
    void SetVelocityUp(float64_t value) noexcept
    {
        velocity_up_ = value;
    }

    /**
     * @brief Set longitude covariance value. Unit: m^2
     *
     * @param value Longitude covariance value.
     */
    void SetLongitudeCov(float64_t value) noexcept
    {
        longitude_cov_ = value;
    }

    /**
     * @brief Set latitude covariance value. Unit: m^2
     *
     * @param value Latitude covariance value.
     */
    void SetLatitudeCov(float64_t value) noexcept
    {
        latitude_cov_ = value;
    }

    /**
     * @brief Set height covariance value. Unit: m^2
     *
     * @param value Height covariance value.
     */
    void SetHeightCov(float64_t value) noexcept
    {
        height_cov_ = value;
    }

    /**
     * @brief Set velocity in east direction covariance value. Unit: (m/s)^2
     *
     * @param value East velocity covariance value.
     */
    void SetVelocityEastCov(float64_t value) noexcept
    {
        velocity_east_cov_ = value;
    }

    /**
     * @brief Set velocity in north direction covariance value. Unit: (m/s)^2
     *
     * @param value North velocity covariance value.
     */
    void SetVelocityNorthCov(float64_t value) noexcept
    {
        velocity_north_cov_ = value;
    }

    /**
     * @brief Set velocity in up direction covariance value. Unit: (m/s)^2
     *
     * @param value Up velocity covariance value.
     */
    void SetVelocityUpCov(float64_t value) noexcept
    {
        velocity_up_cov_ = value;
    }

    /**
     * @brief Get gnss position in PointType format.
     *
     * @tparam PointType Position format. PointType should provide following constructors: @n
     * PointType(float64_t, float64_t, float64_t) or @n
     * PointType(std::initializer_list<float64_t>)
     *
     * @return PointType gnss position.
     */
    template <typename PointType>
    PointType GetPosition() const noexcept
    {
        return PointType{longitude_, latitude_, height_};
    }

    /**
     * @brief Get velocity in PointType format.
     *
     * @tparam PointType velocity format. PointType should provide following constructors: @n
     * PointType(float64_t, float64_t, float64_t) or @n
     * PointType(std::initializer_list<float64_t>)
     *
     * @return PointType velocity.
     */
    template <typename PointType>
    PointType GetVelocity() const noexcept
    {
        return PointType{velocity_east_, velocity_north_, velocity_up_};
    }

    /**
     * @brief Get position covariance in PointType format.
     *
     * @tparam PointType position covariance format. PointType should provide following constructors: @n
     * PointType(float64_t, float64_t, float64_t) or @n
     * PointType(std::initializer_list<float64_t>)
     *
     * @return PointType position covariance.
     */
    template <typename PointType>
    PointType GetPositionCov() const noexcept
    {
        return PointType{longitude_cov_, latitude_cov_, height_cov_};
    }

    /**
     * @brief Get velocity covariance in PointType format.
     *
     * @tparam PointType velocity covariance format. PointType should provide following constructors: @n
     * PointType(float64_t, float64_t, float64_t) or @n
     * PointType(std::initializer_list<float64_t>)
     *
     * @return PointType velocity covariance.
     */
    template <typename PointType>
    PointType GetVelocityCov() const noexcept
    {
        return PointType{velocity_east_cov_, velocity_north_cov_, velocity_up_cov_};
    }

    /**
     * @brief Set position from std::array value.
     *
     * @param pt PointType position value.
     */
    template <typename T, size_t S>
    void SetPosition(std::array<T, S> const& value) noexcept
    {
        longitude_ = std::get<0>(value);
        latitude_  = std::get<1>(value);
        height_    = std::get<2>(value);
    }

    /**
     * @brief Set position from std::tuple.
     *
     * @param pt PointType position value.
     */
    template <typename... Args>
    void SetPosition(std::tuple<Args...> const& value) noexcept
    {
        longitude_ = std::get<0>(value);
        latitude_  = std::get<1>(value);
        height_    = std::get<2>(value);
    }

    /**
     * @brief Set position from PointType value.
     *
     * @tparam PointType PointType position format.
     *
     * @param pt PointType position value.
     */
    template <typename PointType>
    void SetPosition(PointType const& pt) noexcept
    {
        longitude_ = pt[0];
        latitude_  = pt[1];
        height_    = pt[2];
    }

    /**
     * @brief Set velocity from PointType value.
     *
     * @tparam PointType PointType velocity format.
     *
     *
     * @param pt PointType velocity value.
     */
    template <typename PointType>
    void SetVelocity(PointType const& pt) noexcept
    {
        velocity_east_  = pt[0];
        velocity_north_ = pt[1];
        velocity_up_    = pt[2];
    }

    /**
     * @brief Set position covariance from PointType value.
     *
     * @tparam PointType PointType position covariance format.
     *
     *
     * @param pt PointType position covariance value.
     */
    template <typename PointType>
    void SetPositionCov(PointType const& pt) noexcept
    {
        longitude_cov_ = pt[0];
        latitude_cov_  = pt[1];
        height_cov_    = pt[2];
    }

    /**
     * @brief Set velocity covariance from PointType value.
     *
     * @tparam PointType PointType velocity covariance format.
     *
     *
     * @param pt PointType velocity covariance value.
     */
    template <typename PointType>
    void SetVelocityCov(PointType const& pt) noexcept
    {
        velocity_east_cov_  = pt[0];
        velocity_north_cov_ = pt[1];
        velocity_up_cov_    = pt[2];
    }

    /**
     * @brief Set position values
     *
     * @param longitude Longitude value
     * @param latitude Latitude value
     * @param height Height value
     */
    void SetPosition(float64_t longitude, float64_t latitude, float64_t height) noexcept
    {
        longitude_ = longitude;
        latitude_  = latitude;
        height_    = height;
    }

    /**
     * @brief Set velocity values
     *
     * @param velocity_east East velocity value.
     * @param velocity_north North velocity value.
     * @param velocity_up Height velocity value.
     */
    void SetVelocity(float64_t velocity_east, float64_t velocity_north, float64_t velocity_up) noexcept
    {
        velocity_east_  = velocity_east;
        velocity_north_ = velocity_north;
        velocity_up_    = velocity_up;
    }

    /**
     * @brief Set position covariance values.
     *
     * @param longitude_cov Longitude covariance value.
     * @param latitude_cov Latitude covariance value.
     * @param height_cov Height covariance value.
     */
    void SetPositionCov(float64_t longitude_cov, float64_t latitude_cov, float64_t height_cov) noexcept
    {
        longitude_cov_ = longitude_cov;
        latitude_cov_  = latitude_cov;
        height_cov_    = height_cov;
    }

    /**
     * @brief Set velocity covariance values.
     *
     * @param velocity_east_cov East velocity covariance value.
     * @param velocity_north_cov North velocity covariance value.
     * @param velocity_up_cov Height velocity covariance value.
     */
    void SetVelocityCov(float64_t velocity_east_cov, float64_t velocity_north_cov, float64_t velocity_up_cov) noexcept
    {
        velocity_east_cov_  = velocity_east_cov;
        velocity_north_cov_ = velocity_north_cov;
        velocity_up_cov_    = velocity_up_cov;
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
        return stamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(coordinate_), status_, longitude_, latitude_, height_,
                                     velocity_east_, velocity_north_, velocity_up_, longitude_cov_, latitude_cov_,
                                     height_cov_, velocity_east_cov_, velocity_north_cov_, velocity_up_cov_);
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
        serializer << stamp_ << coordinate_ << status_ << longitude_ << latitude_ << height_ << velocity_east_
                   << velocity_north_ << velocity_up_ << longitude_cov_ << latitude_cov_ << height_cov_
                   << velocity_east_cov_ << velocity_north_cov_ << velocity_up_cov_ << holo::serialization::align;
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
        deserializer >> stamp_ >> coordinate_ >> status_ >> longitude_ >> latitude_ >> height_ >> velocity_east_ >>
            velocity_north_ >> velocity_up_ >> longitude_cov_ >> latitude_cov_ >> height_cov_ >> velocity_east_cov_ >>
            velocity_north_cov_ >> velocity_up_cov_ >> holo::serialization::align;
    }

private:
    Timestamp  stamp_;
    Coordinate coordinate_;
    uint32_t   status_;

    float64_t longitude_;
    float64_t latitude_;
    float64_t height_;

    float64_t velocity_east_;
    float64_t velocity_north_;
    float64_t velocity_up_;

    float64_t longitude_cov_;
    float64_t latitude_cov_;
    float64_t height_cov_;

    float64_t velocity_east_cov_;
    float64_t velocity_north_cov_;
    float64_t velocity_up_cov_;
};

static_assert(sizeof(GnssPvt) == 112, "");

}  // namespace common
}  // namespace holo

#endif
