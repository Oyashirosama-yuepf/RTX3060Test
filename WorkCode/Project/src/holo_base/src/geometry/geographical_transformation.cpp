/*!
 * @file geographical_transformation.cpp
 * @brief Conversion between lat/lon and UTM
 * @author dz (daizhen@holomatic.com) zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <cassert>
#include <cmath>

#include <holo/geometry/geographical_transformation.h>

namespace holo
{
const ::holo::float64_t GeographicalTransformation::k_PI = 3.14159265358979;

/* Ellipsoid model constants (actual values here are for WGS84) */
const ::holo::float64_t GeographicalTransformation::k_sm_a           = 6378137.0;
const ::holo::float64_t GeographicalTransformation::k_sm_b           = 6356752.314;
const ::holo::float64_t GeographicalTransformation::k_sm_EccSquared  = 6.69437999013e-03;
const ::holo::float64_t GeographicalTransformation::k_UTMScaleFactor = 0.9996;

std::atomic_size_t GeographicalTransformation::zone_id_(50);

::holo::float64_t GeographicalTransformation::DegToRad(const ::holo::float64_t deg)
{
    return (deg / 180.0 * GeographicalTransformation::k_PI);
}

::holo::float64_t GeographicalTransformation::RadToDeg(const ::holo::float64_t rad)
{
    return (rad / GeographicalTransformation::k_PI * 180.0);
}

::holo::bool_t GeographicalTransformation::UTM2LL(const ::holo::geometry::Point2d _xy, ::holo::float64_t& _lon,
                                                  ::holo::float64_t& _lat)
{
    GeographicalTransformation::UTMXYToLatLon(_xy.GetX(), _xy.GetY(), _lat, _lon);
    _lat = RadToDeg(_lat);
    _lon = RadToDeg(_lon);
    return true;
}

::holo::bool_t GeographicalTransformation::LL2UTM(const ::holo::float64_t _lon, const ::holo::float64_t _lat,
                                                  ::holo::geometry::Point2d& _xy)
{
    ::holo::float64_t x = 0.0;
    ::holo::float64_t y = 0.0;
    GeographicalTransformation::LatLonToUTMXY(_lat, _lon, x, y);
    _xy.SetX(x);
    _xy.SetY(y);
    return true;
}

void GeographicalTransformation::SetGlobalZoneId(::std::size_t zone_id)
{
    assert((zone_id >= 1) && (zone_id <= kNUTMZones));
    zone_id_ = zone_id;
}

::std::size_t GeographicalTransformation::GetZoneId()
{
    return zone_id_;
}

void GeographicalTransformation::SetGlobalZoneIdByLatLon(const ::holo::float64_t _lon, const ::holo::float64_t _lat)
{
    const ::std::size_t id = ComputeUTMZoneId(_lon, _lat);
    SetGlobalZoneId(id);
}

::holo::float64_t GeographicalTransformation::ArcLengthOfMeridian(const ::holo::float64_t phi)
{
    ::holo::float64_t alpha, beta, gamma, delta, epsilon, n;
    ::holo::float64_t result;

    using T = GeographicalTransformation;
    /* Precalculate n */
    n = (T::k_sm_a - T::k_sm_b) / (T::k_sm_a + T::k_sm_b);

    /* Precalculate alpha */
    alpha = ((T::k_sm_a + T::k_sm_b) / 2.0) * (1.0 + (std::pow(n, 2.0) / 4.0) + (::std::pow(n, 4.0) / 64.0));

    /* Precalculate beta */
    beta = (-3.0 * n / 2.0) + (9.0 * std::pow(n, 3.0) / 16.0) + (-3.0 * std::pow(n, 5.0) / 32.0);

    /* Precalculate gamma */
    gamma = (15.0 * std::pow(n, 2.0) / 16.0) + (-15.0 * std::pow(n, 4.0) / 32.0);

    /* Precalculate delta */
    delta = (-35.0 * std::pow(n, 3.0) / 48.0) + (105.0 * std::pow(n, 5.0) / 256.0);

    /* Precalculate epsilon */
    epsilon = (315.0 * std::pow(n, 4.0) / 512.0);

    /* Now calculate the sum of the series and return */
    result = alpha * (phi + (beta * std::sin(2.0 * phi)) + (gamma * std::sin(4.0 * phi)) +
                      (delta * std::sin(6.0 * phi)) + (epsilon * std::sin(8.0 * phi)));

    return result;
}

::holo::float64_t GeographicalTransformation::UTMCentralMeridian(const ::holo::int32_t zone)
{
    ::holo::float64_t cmeridian;
    cmeridian = GeographicalTransformation::DegToRad(-183.0 + (static_cast<::holo::float64_t>(zone) * 6.0));

    return cmeridian;
}

::holo::float64_t GeographicalTransformation::FootpointLatitude(const ::holo::float64_t y)
{
    ::holo::float64_t y_, alpha_, beta_, gamma_, delta_, epsilon_, n;
    ::holo::float64_t result;

    using T = GeographicalTransformation;

    /* Precalculate n (Eq. 10.18) */
    n = (T::k_sm_a - T::k_sm_b) / (T::k_sm_a + T::k_sm_b);

    /* Precalculate alpha_ (Eq. 10.22) */
    /* (Same as alpha in Eq. 10.17) */
    alpha_ = ((T::k_sm_a + T::k_sm_b) / 2.0) * (1 + (std::pow(n, 2.0) / 4) + (std::pow(n, 4.0) / 64));

    /* Precalculate y_ (Eq. 10.23) */
    y_ = y / alpha_;

    /* Precalculate beta_ (Eq. 10.22) */
    beta_ = (3.0 * n / 2.0) + (-27.0 * std::pow(n, 3.0) / 32.0) + (269.0 * std::pow(n, 5.0) / 512.0);

    /* Precalculate gamma_ (Eq. 10.22) */
    gamma_ = (21.0 * std::pow(n, 2.0) / 16.0) + (-55.0 * std::pow(n, 4.0) / 32.0);

    /* Precalculate delta_ (Eq. 10.22) */
    delta_ = (151.0 * std::pow(n, 3.0) / 96.0) + (-417.0 * std::pow(n, 5.0) / 128.0);

    /* Precalculate epsilon_ (Eq. 10.22) */
    epsilon_ = (1097.0 * std::pow(n, 4.0) / 512.0);

    /* Now calculate the sum of the series (Eq. 10.21) */
    result = y_ + (beta_ * ::std::sin(2.0 * y_)) + (gamma_ * ::std::sin(4.0 * y_)) + (delta_ * ::std::sin(6.0 * y_)) +
             (epsilon_ * ::std::sin(8.0 * y_));

    return result;
}

::holo::int32_t GeographicalTransformation::LatLonToUTMXY(::holo::float64_t lat, ::holo::float64_t lon,
                                                          ::holo::float64_t& x, ::holo::float64_t& y)
{
    MapLatLonToXY(GeographicalTransformation::DegToRad(lat), GeographicalTransformation::DegToRad(lon),
                  UTMCentralMeridian(zone_id_), x, y);

    /* Adjust easting and northing for UTM system. */
    x = x * k_UTMScaleFactor + 500000.0;
    y = y * k_UTMScaleFactor;
    if (y < 0.0)
    {
        y = y + 10000000.0;
    }
    return zone_id_;
}

void GeographicalTransformation::UTMXYToLatLon(::holo::float64_t x, ::holo::float64_t y, ::holo::float64_t& _lat,
                                               ::holo::float64_t& _lon)
{
    _lat                        = 0.0;
    _lon                        = 0.0;
    ::holo::float64_t cmeridian = 0.0;

    x -= 500000.0;
    x /= k_UTMScaleFactor;
    y /= k_UTMScaleFactor;
    cmeridian = UTMCentralMeridian(zone_id_);
    MapXYToLatLon(x, y, cmeridian, _lat, _lon);
}

void GeographicalTransformation::MapLatLonToXY(const ::holo::float64_t phi, const ::holo::float64_t lambda,
                                               const ::holo::float64_t lambda0, ::holo::float64_t& x,
                                               ::holo::float64_t& y)
{
    ::holo::float64_t N, nu2, ep2, t, t2, l;
    ::holo::float64_t l3coef, l4coef, l5coef, l6coef, l7coef, l8coef;
    //::holo::float64_t tmp; // Unused

    /* Precalculate ep2 */
    ep2 = (::std::pow(k_sm_a, 2.0) - ::std::pow(k_sm_b, 2.0)) / ::std::pow(k_sm_b, 2.0);

    /* Precalculate nu2 */
    nu2 = ep2 * ::std::pow(::std::cos(phi), 2.0);

    /* Precalculate N */
    N = ::std::pow(k_sm_a, 2.0) / (k_sm_b * ::std::sqrt(1 + nu2));

    /* Precalculate t */
    t  = ::std::tan(phi);
    t2 = t * t;
    // tmp = (t2 * t2 * t2) - ::std::pow(t, 6.0); // Unused

    /* Precalculate l */
    l = lambda - lambda0;

    /* Precalculate coefficients for l**n in the equations below
       so a normal human being can read the expressions for easting
       and northing
       -- l**1 and l**2 have coefficients of 1.0 */
    l3coef = 1.0 - t2 + nu2;

    l4coef = 5.0 - t2 + 9 * nu2 + 4.0 * (nu2 * nu2);

    l5coef = 5.0 - 18.0 * t2 + (t2 * t2) + 14.0 * nu2 - 58.0 * t2 * nu2;

    l6coef = 61.0 - 58.0 * t2 + (t2 * t2) + 270.0 * nu2 - 330.0 * t2 * nu2;

    l7coef = 61.0 - 479.0 * t2 + 179.0 * (t2 * t2) - (t2 * t2 * t2);

    l8coef = 1385.0 - 3111.0 * t2 + 543.0 * (t2 * t2) - (t2 * t2 * t2);

    /* Calculate easting (x) */
    x = N * ::std::cos(phi) * l + (N / 6.0 * ::std::pow(::std::cos(phi), 3.0) * l3coef * ::std::pow(l, 3.0)) +
        (N / 120.0 * ::std::pow(::std::cos(phi), 5.0) * l5coef * ::std::pow(l, 5.0)) +
        (N / 5040.0 * ::std::pow(::std::cos(phi), 7.0) * l7coef * ::std::pow(l, 7.0));

    /* Calculate northing (y) */
    y = ArcLengthOfMeridian(phi) + (t / 2.0 * N * ::std::pow(::std::cos(phi), 2.0) * ::std::pow(l, 2.0)) +
        (t / 24.0 * N * ::std::pow(::std::cos(phi), 4.0) * l4coef * ::std::pow(l, 4.0)) +
        (t / 720.0 * N * ::std::pow(::std::cos(phi), 6.0) * l6coef * ::std::pow(l, 6.0)) +
        (t / 40320.0 * N * ::std::pow(::std::cos(phi), 8.0) * l8coef * ::std::pow(l, 8.0));

    return;
}

void GeographicalTransformation::MapXYToLatLon(const ::holo::float64_t x, const ::holo::float64_t y,
                                               const ::holo::float64_t lambda0, ::holo::float64_t& phi,
                                               ::holo::float64_t& lambda)
{
    ::holo::float64_t phif, Nf, Nfpow, nuf2, ep2, tf, tf2, tf4, cf;
    ::holo::float64_t x1frac, x2frac, x3frac, x4frac, x5frac, x6frac, x7frac;
    ::holo::float64_t x8frac;
    ::holo::float64_t x2poly, x3poly, x4poly, x5poly, x6poly, x7poly, x8poly;

    /* Get the value of phif, the footpoint latitude. */
    phif = FootpointLatitude(y);

    /* Precalculate ep2 */
    ep2 = (::std::pow(k_sm_a, 2.0) - ::std::pow(k_sm_b, 2.0)) / ::std::pow(k_sm_b, 2.0);

    /* Precalculate cos (phif) */
    cf = ::std::cos(phif);

    /* Precalculate nuf2 */
    nuf2 = ep2 * ::std::pow(cf, 2.0);

    /* Precalculate Nf and initialize Nfpow */
    Nf    = ::std::pow(k_sm_a, 2.0) / (k_sm_b * ::std::sqrt(1 + nuf2));
    Nfpow = Nf;

    /* Precalculate tf */
    tf  = ::std::tan(phif);
    tf2 = tf * tf;
    tf4 = tf2 * tf2;

    /* Precalculate fractional coefficients for x**n in the equations
     below to simplify the expressions for latitude and longitude. */
    x1frac = 1.0 / (Nfpow * cf);

    Nfpow *= Nf; /* now equals Nf**2) */
    x2frac = tf / (2.0 * Nfpow);

    Nfpow *= Nf; /* now equals Nf**3) */
    x3frac = 1.0 / (6.0 * Nfpow * cf);

    Nfpow *= Nf; /* now equals Nf**4) */
    x4frac = tf / (24.0 * Nfpow);

    Nfpow *= Nf; /* now equals Nf**5) */
    x5frac = 1.0 / (120.0 * Nfpow * cf);

    Nfpow *= Nf; /* now equals Nf**6) */
    x6frac = tf / (720.0 * Nfpow);

    Nfpow *= Nf; /* now equals Nf**7) */
    x7frac = 1.0 / (5040.0 * Nfpow * cf);

    Nfpow *= Nf; /* now equals Nf**8) */
    x8frac = tf / (40320.0 * Nfpow);

    /* Precalculate polynomial coefficients for x**n.
     -- x**1 does not have a polynomial coefficient. */
    x2poly = -1.0 - nuf2;

    x3poly = -1.0 - 2 * tf2 - nuf2;

    x4poly = 5.0 + 3.0 * tf2 + 6.0 * nuf2 - 6.0 * tf2 * nuf2 - 3.0 * (nuf2 * nuf2) - 9.0 * tf2 * (nuf2 * nuf2);

    x5poly = 5.0 + 28.0 * tf2 + 24.0 * tf4 + 6.0 * nuf2 + 8.0 * tf2 * nuf2;

    x6poly = -61.0 - 90.0 * tf2 - 45.0 * tf4 - 107.0 * nuf2 + 162.0 * tf2 * nuf2;

    x7poly = -61.0 - 662.0 * tf2 - 1320.0 * tf4 - 720.0 * (tf4 * tf2);

    x8poly = 1385.0 + 3633.0 * tf2 + 4095.0 * tf4 + 1575 * (tf4 * tf2);

    /* Calculate latitude */
    phi = phif + x2frac * x2poly * (x * x) + x4frac * x4poly * ::std::pow(x, 4.0) +
          x6frac * x6poly * ::std::pow(x, 6.0) + x8frac * x8poly * ::std::pow(x, 8.0);

    /* Calculate longitude */
    lambda = lambda0 + x1frac * x + x3frac * x3poly * ::std::pow(x, 3.0) + x5frac * x5poly * ::std::pow(x, 5.0) +
             x7frac * x7poly * ::std::pow(x, 7.0);

    return;
}

::std::size_t GeographicalTransformation::ComputeUTMZoneId(::holo::float64_t lon, ::holo::float64_t lat)
{
    /**************************************************************
     *             Compute UTM Zone ID
     *
     * Step 1: make sure the angles are within the expected range
     *         longitude (-180, 180]
     *         latitude  (-90, 90]
     * Step 2: calculate the zone id depending on the lat/lon
     *         reference:
     * https://en.wikipedia.org/wiki/Universal_Transverse_Mercator_coordinate_
     * system
     *
     ***************************************************************/

    /* --------------------------- STEP 1 ------------------------ */
    /* not sure if this check is needed. Lat/Lon shall be guaranteed to be
     * within the range at the input
     * It may be better to deny the processing of out-of-range data, but
     * there must be some feedback from constructor, so put this handling here
     * it is more or less a quick check
     * */
    if (lon < -180 || lon >= 180)
    {
        ::holo::int32_t dir = lon < 0 ? -1 : 1;
        while (lon < -180 || lon >= 180)
        {
            lon -= 360.0 * (dir);
        }
    }

    if (lat <= -90 || lat >= 90)
    {
        ::holo::int32_t dir = lat < 0 ? -1 : 1;
        while (lat <= -90 || lat >= 90)
        {
            lat -= 360.0 * (dir);
        }
    }

    /* --------------------------- STEP 2 ------------------------ */
    /* Calculate the zone id, especially those special areas */
    uint8_t zone = static_cast<uint8_t>((lon + 186) / 6);

    if (lat >= 56.0 && lat < 64.0 && lon >= 3.0 && lon < 12.0)
    {
        zone = 32;
    }
    else if (lat >= 72.0 && lat < 84.0)
    {
        if (lon >= 0.0 && lon < 9.0)
        {
            zone = 31;
        }
        else if (lon >= 9.0 && lon < 21.0)
        {
            zone = 33;
        }
        else if (lon >= 21.0 && lon < 33.0)
        {
            zone = 35;
        }
        else if (lon >= 33.0 && lon < 42.0)
        {
            zone = 37;
        }
    }

    return zone;
}

}  // namespace holo
