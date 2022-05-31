/*!
 * @file geographical_transformation.h
 * @brief conversion between lat/lon and UTM
 * @author dz (daizhen@holomatic.com) zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_GEOMETRY_GEOGRAPHICAL_TRANSFORMATION_H_
#define HOLO_GEOMETRY_GEOGRAPHICAL_TRANSFORMATION_H_

#include <atomic>
#include <mutex>
#include <string>

#include <holo/core/types.h>
#include <holo/geometry/angle.h>
#include <holo/geometry/point2.h>

namespace holo
{
class GeographicalTransformation
{
    static const ::holo::float64_t k_PI;

    /* Ellipsoid model constants (actual values here are for WGS84) */
    static const ::holo::float64_t k_sm_a;
    static const ::holo::float64_t k_sm_b;
    static const ::holo::float64_t k_sm_EccSquared;
    static const ::holo::float64_t k_UTMScaleFactor;

public:
    /**
     * @brief Construct, the zone id default is China area!
     *
     */
    GeographicalTransformation() = default;

    /**
     * @brief Destroy
     *
     */
    ~GeographicalTransformation() = default;

    /**
     * @brief Converts degrees to radians.
     *
     * @param deg degrees
     * @return ::holo::float64_t
     */
    static ::holo::float64_t DegToRad(const ::holo::float64_t deg);

    /**
     * @brief Converts radians to degrees
     *
     * @param rad radians
     * @return ::holo::float64_t
     */
    static ::holo::float64_t RadToDeg(const ::holo::float64_t rad);

    /* @brief convert a point in UTM coordinate to the longitude and latitude
     * @param xy known 2D point given in units of meters
     * @param lon longitude to be calculated in units of degrees
     * @prams lat latitude to be calculated in units of degrees
     * */
    static ::holo::bool_t UTM2LL(const ::holo::geometry::Point2d xy, ::holo::float64_t& lon, ::holo::float64_t& lat);

    /* @brief convert the longitude and latitude to a point in UTM coordinate,
     * this version will bypass the zone id lookup and use the default zone id
     * @param lon longitude in units of degrees
     * @param lat latitude in units of degrees
     * @param xy 2D point to be calculated, given in units of meters
     * */
    static ::holo::bool_t LL2UTM(const ::holo::float64_t lon, const ::holo::float64_t lat, ::holo::geometry::Point2d& xy);

    /* @brief setup the zone id
     * @note  we can inherit this class in order to invoke this function.
     * @param[in] zone_id UTM zone id
     * */
    static void SetGlobalZoneId(const ::std::size_t zone_id);

    /* @brief Set zone id by given latitude and longitude
     * @note  we can inherit this class in order to invoke this function.
     * @param[in] _lon longitude in WGS84 in degrees
     * @param[in] _lat latitude in WGS84 in degrees
     * */
    static void SetGlobalZoneIdByLatLon(const ::holo::float64_t _lon, const ::holo::float64_t _lat);

    /**
     * @brief Get current zone id
     * @return current zone id
     */
    static ::std::size_t GetZoneId();

protected:
    /// zone id for faster conversion
    static ::std::atomic_size_t zone_id_;

    /* the number of UTM zones */
    static const ::std::size_t kNUTMZones = 60;

    /**
     * @brief set if the position is in southsemi
     * @param[in] _is_sourthsemi true for southsemi
     */
    static void SetSouthSemiIndicator(const ::holo::bool_t _is_sourthsemi);

    /* @brief calculate zone id depending on the lat/lon
     * @note  we can inherit this class in order to invoke this function.
     * @param[in] lon longitude in units of degrees
     * @param[in] lat latitude in units of degrees
     * */
    static ::std::size_t ComputeUTMZoneId(::holo::float64_t lon, ::holo::float64_t lat);

    /**
     * @brief Computes the ellipsoidal distance from the equator to a point at
     * a given latitude
     * @param[in] phi latitude of the point, in radians.
     * @return  Ellipsoidal distance of the point from the equator, in meters.
     */
    static ::holo::float64_t ArcLengthOfMeridian(::holo::float64_t phi);

    /**
     * @brief Determines the central meridian for the given UTM zone.
     * @param[in] zone id
     * @return The central meridian for the given UTM zone, in radians
       Range of the central meridian is the radian equivalent of [-177,+177].
     */
    static ::holo::float64_t UTMCentralMeridian(const ::holo::int32_t zone);

    /**
     * @brief Computes the footpoint latitude for use in converting transverse
       Mercator coordinates to ellipsoidal coordinates.
     * @param y UTM northing coordinate, in meters
     * @return footpoint latitude, in radians.
     */
    static ::holo::float64_t FootpointLatitude(::holo::float64_t y);

    /**
     * @brief Converts a latitude/longitude pair to x and y coordinates in the
       Universal Transverse Mercator projection.
     * @param[in] lat Latitude of the point, in radians.
     * @param[in] lon Longitude of the point, in radians.
     * @param[out] x UTM coordinate x in meters
     * @param[out] y UTM coordinate y in meters
     * @return The UTM zone used for calculating the values of x and y.
     */
    static ::holo::int32_t LatLonToUTMXY(const ::holo::float64_t lat, const ::holo::float64_t lon, ::holo::float64_t& x,
                                         ::holo::float64_t& y);

    /**
     * @brief Converts x and y coordinates in the Universal Transverse Mercator
     * @param[in] x The easting of the point, in meters.
     * @param[in] y The northing of the point, in meters.
     * @param[out] lat The latitude of the point, in radians.
     * @param[out] lon The longitude of the point, in radians.
     */
    static void UTMXYToLatLon(const ::holo::float64_t x, const ::holo::float64_t y, ::holo::float64_t& lat,
                              ::holo::float64_t& lon);

    /**
     * @brief Converts a latitude/longitude pair to x and y coordinates in the
       Transverse Mercator projection. Note that Transverse Mercator is not
       the same as UTM; a scale factor is required to convert between them.
     * @param[in] phi Latitude of the point, in radians.
     * @param[in] lambda Longitude of the point, in radians.
     * @param[in] lambda0 Longitude of the central meridian, in radians.
     * @param[out] x The x coordinate of the computed point.
     * @param[out] y The y coordinate of the computed point.
     */
    static void MapLatLonToXY(const ::holo::float64_t phi, const ::holo::float64_t lambda,
                              const ::holo::float64_t lambda0, ::holo::float64_t& x, ::holo::float64_t& y);

    /**
     * @brief Converts x and y coordinates in the Transverse Mercator projection
     * to a latitude/longitude pair.  Note that Transverse Mercator is not
       the same as UTM; a scale factor is required to convert between them.
     * @param[in] x The easting of the point, in meters.
     * @param[in] y The northing of the point, in meters.
     * @param[in] lambda0 Longitude of the central meridian, in radians.
     * @param[out] phi Latitude in radians.
     * @param[out] lambda Longitude in radians.
     */
    static void MapXYToLatLon(const ::holo::float64_t x, const ::holo::float64_t y, const ::holo::float64_t lambda0,
                              ::holo::float64_t& phi, ::holo::float64_t& lambda);

};  // GeographicalTransformation

}  // namespace holo

#endif  // HOLO_GEOMETRY_GEOGRAPHICAL_TRANSFORMATION_H_
