/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position.h
 * @brief This header file define measurement of generic WGS84 position from GPS
 * @author lichao@holomatic.com
 * @date Sep 02, 2019
 */

#ifndef HOLO_COMMON_GNSS_POSITION_H_
#define HOLO_COMMON_GNSS_POSITION_H_

#include <memory>

#include <holo_c/common/measurement_appendix.h>

#include <holo/common/coordinate.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/point3.h>
#include <holo/serialization/serialization.h>

namespace holo
{
/**
 * @addtogroup common
 * @{
 *
 */

using ::GnssPositionStatus;
using ::holo::common::Coordinate;
using ::holo::common::Timestamp;

/**
 *
 * @brief position measurement class
 * @note longitude and latitude must be float64_t
 */
class GnssPosition
{
public:
    /**
     * @brief constructor
     */
    GnssPosition();

    /**
     * @brief destructor
     */
    ~GnssPosition() noexcept;

    /**
     * @brief Construct a new GnssPosition object by copy another GnssPosition object
     *
     * @param other a GnssPosition
     */
    GnssPosition(const GnssPosition& other);

    /**
     * @brief Construct a new GnssPosition object by move another GnssPosition object
     *
     * @param other a GnssPosition
     */
    GnssPosition(GnssPosition&& other) noexcept;

    /**
     * @brief copy assignment operator overloading
     *
     * @param rhs a GnssPosition
     * @return GnssPosition& the new GnssPosition
     */
    GnssPosition& operator=(const GnssPosition& rhs);

    /**
     * @brief move assignment operator overloading
     *
     * @param rhs a GnssPosition
     * @return GnssPosition& the new GnssPosition
     */
    GnssPosition& operator=(GnssPosition&& rhs) noexcept;

    /**
     * @brief get TImestamp
     *
     * @return Timestamp
     */
    Timestamp GetTimestamp() const;

    /**
     * @brief set Timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(const Timestamp& timestamp);

    /**
     * @brief get coordinate
     *
     * @return  coordinate
     */
    Coordinate GetCoordinate() const;

    /**
     * @brief set coordinate
     *
     * @param coord coordinate of gnss position
     */
    void SetCoordinate(const Coordinate coord);

    /**
     * @brief return gnss position status
     *
     * @return gnss position status
     */
    GnssPositionStatus GetStatus() const;

    /**
     * @brief set gnss position status
     *
     * @param status gnss position status
     */
    void SetStatus(const GnssPositionStatus status);

    /**
     * @brief return latitude
     *
     * @return latitude in the unit of degrees
     */
    float64_t GetLatitude() const;

    /**
     * @brief set latitude
     *
     * @param latitude in the unit of degrees
     */
    void SetLatitude(const float64_t latitude);

    /**
     * @brief return longitude
     *
     * @return longitude in the unit of degrees
     */
    float64_t GetLongitude() const;

    /**
     * @brief set longitude
     *
     * @param longitude in the unit of degrees
     */
    void SetLongitude(const float64_t longitude);

    /**
     * @brief return altitude
     *
     * @return altitude in the unit of meters
     */
    float64_t GetAltitude() const;

    /**
     * @brief set altitude
     *
     * @param altitude in the unit of meters
     */
    void SetAltitude(const float64_t altitude);

    /**
     * @brief return latitude covariance
     *
     * @return latitude covariance in the unit of degree^2
     */
    float64_t GetLatitudeCovariance() const;

    /**
     * @brief set latitude covariance
     *
     * @param latitude_cov covariance in the unit of degree^2
     */
    void SetLatitudeCovariance(const float64_t latitude_cov);

    /**
     * @brief return longitude covariance
     *
     * @return longitude covariance in the unit of degree^2
     */
    float64_t GetLongitudeCovariance() const;

    /**
     * @brief set longitude covariance
     *
     * @param longitude_cov covariance in the unit of degree^2
     */
    void SetLongitudeCovariance(const float64_t longitude_cov);

    /**
     * @brief return altitude covariance
     *
     * @return altitude covariance in the unit of meter^2
     */
    float64_t GetAltitudeCovariance() const;

    /**
     * @brief set altitude covariance
     *
     * @param altitude_cov covariance in the unit of meter^2
     */
    void SetAltitudeCovariance(const float64_t altitude_cov);

    /**
     * @brief Get the Utm Position object
     *
     * @return Point3d Utm Position in meters
     */
    holo::geometry::Point3d GetUtmPosition() const;

    /**
     * @brief Set the Utm Position object
     *
     * @param utm_position the Utm position in meters
     */
    void SetUtmPosition(const holo::geometry::Point3d utm_position);

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return GetTimestamp().GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(GetCoordinate()),
                                                          static_cast<uint32_t>(GetStatus()), GetLatitude(),
                                                          GetLongitude(), GetAltitude(), GetLatitudeCovariance(),
                                                          GetLongitudeCovariance(), GetAltitudeCovariance());
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
        serializer << GetTimestamp() << static_cast<uint32_t>(GetCoordinate()) << static_cast<uint32_t>(GetStatus())
                   << GetLatitude() << GetLongitude() << GetAltitude() << GetLatitudeCovariance()
                   << GetLongitudeCovariance() << GetAltitudeCovariance() << holo::serialization::align;
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
        /* deserialize data */
        float64_t gnss_data[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        uint32_t  coord, status;
        Timestamp timestamp;
        deserializer >> timestamp >> coord >> status;
        for (uint8_t i = 0; i < 6; ++i)
        {
            deserializer >> gnss_data[i];
        }
        /* serialize padding */
        deserializer >> holo::serialization::align;

        SetTimestamp(timestamp);
        SetCoordinate((holo::common::Coordinate)coord);
        SetStatus((holo::GnssPositionStatus)status);
        SetLatitude(gnss_data[0]);
        SetLongitude(gnss_data[1]);
        SetAltitude(gnss_data[2]);
        SetLatitudeCovariance(gnss_data[3]);
        SetLongitudeCovariance(gnss_data[4]);
        SetAltitudeCovariance(gnss_data[5]);
    }

private:
    class Implementation;
    std::unique_ptr<Implementation> impl_;
};

/**
 * @}
 *
 */

}  // namespace holo

#endif /* HOLO_COMMON_GNSS_POSITION_H */
