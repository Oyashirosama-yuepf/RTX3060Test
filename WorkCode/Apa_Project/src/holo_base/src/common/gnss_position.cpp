/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file gnss_position.cpp
 * @brief the implementation of class GnssPosition
 * @author lichao@holomatic.com
 * @date Aug 24, 2019
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *  notice.
 */

#include <assert.h>
#include <holo/common/gnss_position.h>
#include <holo/geometry/geographical_transformation.h>
#include <holo_c/common/gnss_position.h>

namespace holo
{
class GnssPosition::Implementation
{
public:
    /**
     * @brief Construct a new Implementation object
     *
     */
    Implementation():gnss_position{}
    {
        (void)gnss_position_init(&gnss_position);
    }

    ::GnssPosition gnss_position;
};

GnssPosition::GnssPosition() : impl_(new Implementation)
{
}

GnssPosition::~GnssPosition()
{
}

GnssPosition::GnssPosition(const GnssPosition& other) : impl_(new Implementation(*other.impl_))
{
}

GnssPosition::GnssPosition(GnssPosition&&) noexcept = default;

GnssPosition& GnssPosition::operator=(const GnssPosition& rhs)
{
    if (this != &rhs)
    {
        this->impl_.reset(new Implementation(*rhs.impl_));
    }
    return *this;
}

GnssPosition& GnssPosition::operator=(GnssPosition&& rhs) noexcept = default;

Timestamp GnssPosition::GetTimestamp() const
{
    int64_t nsec = 0;
    (void)timestamp_to_nsec(gnss_position_get_timestamp(&impl_->gnss_position), &nsec);
    return Timestamp((uint64_t)nsec);
}

void GnssPosition::SetTimestamp(const Timestamp& timestamp)
{
    struct ::Timestamp stamp;
    (void)timestamp_init_from_nsec(&stamp, timestamp.ToNsec());
    (void)gnss_position_set_timestamp(&impl_->gnss_position, &stamp);
}

Coordinate GnssPosition::GetCoordinate() const
{
    return (Coordinate)gnss_position_get_coordinate(&impl_->gnss_position);
}

void GnssPosition::SetCoordinate(const Coordinate coord)
{
    (void)gnss_position_set_coordinate(&impl_->gnss_position, static_cast<uint32_t>(coord));
}

GnssPositionStatus GnssPosition::GetStatus() const
{
    return gnss_position_get_status(&impl_->gnss_position);
}

void GnssPosition::SetStatus(const GnssPositionStatus status)
{
    (void)gnss_position_set_status(&impl_->gnss_position, status);
}

float64_t GnssPosition::GetLatitude() const
{
    return gnss_position_get_latitude(&impl_->gnss_position);
}

void GnssPosition::SetLatitude(const float64_t latitude)
{
    (void)gnss_position_set_latitude(&impl_->gnss_position, latitude);
}

float64_t GnssPosition::GetLongitude() const
{
    return gnss_position_get_longitude(&impl_->gnss_position);
}

void GnssPosition::SetLongitude(const float64_t longitude)
{
    (void)gnss_position_set_longitude(&impl_->gnss_position, longitude);
}

float64_t GnssPosition::GetAltitude() const
{
    return gnss_position_get_altitude(&impl_->gnss_position);
}

void GnssPosition::SetAltitude(const float64_t altitude)
{
    (void)gnss_position_set_altitude(&impl_->gnss_position, altitude);
}

float64_t GnssPosition::GetLatitudeCovariance() const
{
    return gnss_position_get_latitude_covariance(&impl_->gnss_position);
}

void GnssPosition::SetLatitudeCovariance(const float64_t latitude_cov)
{
    (void)gnss_position_set_latitude_covariance(&impl_->gnss_position, latitude_cov);
}

float64_t GnssPosition::GetLongitudeCovariance() const
{
    return gnss_position_get_longitude_covariance(&impl_->gnss_position);
}

void GnssPosition::SetLongitudeCovariance(const float64_t longitude_cov)
{
    (void)gnss_position_set_longitude_covariance(&impl_->gnss_position, longitude_cov);
}

float64_t GnssPosition::GetAltitudeCovariance() const
{
    return gnss_position_get_altitude_covariance(&impl_->gnss_position);
}

void GnssPosition::SetAltitudeCovariance(const float64_t altitude_cov)
{
    (void)gnss_position_set_altitude_covariance(&impl_->gnss_position, altitude_cov);
}

holo::geometry::Point3d GnssPosition::GetUtmPosition() const
{
    /* convert WGS84 to UTM coordinate */
    holo::geometry::Point2d utm_xy;
    (void)GeographicalTransformation::LL2UTM(GetLongitude(), GetLatitude(), utm_xy);

    return holo::geometry::Point3d(utm_xy.GetX(), utm_xy.GetY(), GetAltitude());
}

void GnssPosition::SetUtmPosition(const holo::geometry::Point3d utm_position)
{
    /* convert UTM to WGS84 coordinate */
    float64_t longitude = 0.0;
    float64_t latitude  = 0.0;
    (void)GeographicalTransformation::UTM2LL(utm_position.GetPointXY(), longitude, latitude);

    /* set longitude, latitude and altitude to gnss position */
    SetLongitude(longitude);
    SetLatitude(latitude);
    SetAltitude(utm_position.GetZ());
}

} /* namespace holo */
