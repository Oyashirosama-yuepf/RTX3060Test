/*!
 *  \brief Convert latitude longitude to x y.
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */
#ifndef HOLO_MAP_COMMON_CLASSES_LATLON_H_
#define HOLO_MAP_COMMON_CLASSES_LATLON_H_
#include <holo/geometry/geographical_transformation.h>
#include <holo/map/common/across_zone_conversion.h>
#include <holo/map/common/across_zone_utility.h>
#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{
class LatLon
{
    typedef float64_t DegreeType;

public:
    /// Default constructor
    LatLon();

    /// Constructor with individual parameter input
    LatLon(const DegreeType&, const DegreeType&);

    /// Constructor with point2d
    LatLon(const MapPoint&);

    /// Copy constructor
    LatLon(const LatLon&);

    /// Destructor
    ~LatLon() noexcept;

    /**
     * Transform LatLon coordinates to XY coordinates
     * @return XY coordinates given in Point type
     */
    MapPoint ToXY() const;

    /// Copy assignment
    LatLon& operator=(const LatLon& other);

    /**
     * Setter by given latitude and longitude values
     * @param[in] _lat latitude value
     * @param[in] _lon longitude value
     */
    void SetByLatLon(const DegreeType& _lat, const DegreeType& _lon);

    /**
     * Setter by given XY coordinates
     * @param[in] point_xy Coordinate given as XY point
     */
    void SetByXY(const MapPoint& point_xy);

        /**
     * @brief Convert utm point to wgs84 point.
     * 
     * @param[in] point_xy Coordinate given as XY point
     * @param[in] zone Zone id in utm coordinate system with 6 longitude wide.
     * @param[in] south true: point in the southern hemisphere, false: point in the northern hemisphere.
     * 
     * @return Nothing.
    */
    void SetByXY(MapPoint const& xy, holo::uint8_t const zone, bool const south = false);

    /// Get latitude
    DegreeType Latitude() const;

    /// Get longitude
    DegreeType Longitude() const;

    /// Set latitude
    void SetLat(const DegreeType& lat);

    /// Set longitude
    void SetLon(const DegreeType& lon);

private:
    /// latitude in units of meters
    DegreeType lat_ = 0.0;
    /// longitude in units of meters
    DegreeType lon_ = 0.0;
};

typedef LatLon          LL;
typedef std::vector<LL> VecLL;

inline LatLon::LatLon() : lat_(0.0), lon_(0.0)
{
}

inline LatLon::LatLon(const DegreeType& _lat, const DegreeType& _lon) : lat_(_lat), lon_(_lon)
{
}

inline LatLon::LatLon(const LatLon& _other) : lat_(_other.Latitude()), lon_(_other.Longitude())
{
}

inline LatLon::LatLon(const MapPoint& _point)
{
    SetByXY(_point);
}

inline LatLon::~LatLon()
{
}

inline MapPoint LatLon::ToXY() const
{
    MapPoint          point;
    ::holo::float64_t x = 0.0;
    ::holo::float64_t y = 0.0;
    
    ::holo::uint8_t global_zone_id    = 0;
    ::holo::bool_t  global_south_flag = false;
    across_zone::utility::GlobalCoordinate::GetUtmZone(global_zone_id, global_south_flag);

    if (lonlat_to_utm(lon_, lat_, global_zone_id, global_south_flag, &x, &y) == RC_SUCCESS)
    {
        point.SetX(x);
        point.SetY(y);
    }
    return point;
}

/// Copy assignment

inline LatLon& LatLon::operator=(const LatLon& other)
{
    if (this != &other)
    {
        this->lat_ = other.lat_;
        this->lon_ = other.lon_;
    }
    return *this;
}

/**
 * Setter by given latitude and longitude values
 * @param[in] _lat latitude value
 * @param[in] _lon longitude value
 */

inline void LatLon::SetByLatLon(const DegreeType& _lat, const DegreeType& _lon)
{
    lat_ = _lat;
    lon_ = _lon;
}

/**
 * Setter by given XY coordinates
 * @param[in] point_xy Coordinate given as XY point
 */

inline void LatLon::SetByXY(const MapPoint& point_xy)
{
    this->lat_ = 0.0;
    this->lon_ = 0.0;

    ::holo::uint8_t global_zone_id    = 0;
    ::holo::bool_t  global_south_flag = false;
    across_zone::utility::GlobalCoordinate::GetUtmZone(global_zone_id, global_south_flag);

    utm_to_lonlat(global_zone_id, global_south_flag, point_xy.GetX(), point_xy.GetY(), &this->lon_, &this->lat_);
}

/**
 * @brief Convert utm point to wgs84 point.
 * 
 * @param[in] point_xy Coordinate given as XY point
 * @param[in] zone Zone id in utm coordinate system with 6 longitude wide.
 * @param[in] south true: point in the southern hemisphere, false: point in the northern hemisphere.
 * 
 * @return Nothing.
 */
inline void LatLon::SetByXY(MapPoint const& xy, holo::uint8_t const zone, bool const south)
{
    this->lat_ = 0.0;
    this->lon_ = 0.0;
    utm_to_lonlat(zone, south, xy.GetX(), xy.GetY(), &this->lon_, &this->lat_);
}

/// Get latitude

inline LatLon::DegreeType LatLon::Latitude() const
{
    return lat_;
}

/// Get longitude

inline LatLon::DegreeType LatLon::Longitude() const
{
    return lon_;
}

/// Set latitude

inline void LatLon::SetLat(const DegreeType& lat)
{
    lat_ = lat;
}

/// Set longitude

inline void LatLon::SetLon(const DegreeType& lon)
{
    lon_ = lon;
}

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_COMMON_CLASSES_LATLON_H_ */
