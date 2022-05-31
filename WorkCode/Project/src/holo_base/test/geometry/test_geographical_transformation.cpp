/*!
 * * \brief unit test for geographical transformation
 * * \author Daizhen (daizhen@holomatic.com) zhaofx(zhaofuxing@holomatic.com)
 * * \date Jul 24, 2017
 * * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice. */

#include <gtest/gtest.h>
#include <holo/geometry/geographical_transformation.h>

using namespace std;
using namespace holo;

///////////////////////////////////////////////////////////////////////////////
// Referenced from http://home.hiwaay.net/~taylorc/toolbox/geography/geoutm.
// html
// Beijing
// lat : 39.90421111
// lon : 116.40741111
// with corresponding UTM coordinate as follows:
// x (easting) 449346.01934345544
// y (northing) 4417293.7209900115
// zone id : 50
//
// Latitude of a known test point in Beijing
const float64_t LatitudeBeijing = 39.90421111;
// Longitude of a known test point in Beijing
const float64_t LongitudeBeijing = 116.40741111;
// UTM coordinate X of the known test point in Beijing
const float64_t UTMxBeijing = 449346.01934345544;
// UTM coordinate Y of the known test point in Beijing
const float64_t UTMyBeijing = 4417293.7209900115;
// UTM Zone Id of Beijing
const size_t UTMZoneIdBeijing = 50;

const float64_t LatRadBeijing = ::holo::GeographicalTransformation::DegToRad(LatitudeBeijing);
const float64_t LonRadBeijing = ::holo::GeographicalTransformation::DegToRad(LongitudeBeijing);

///////////////////////////////////////////////////////////////////////////////
// Karlsruhe (for incorporating kitti dataset)
// lat : 49.0069
// lon : 8.4037
// with corresponding UTM coordinate as follows:
// x (easting)  456391.2464264152
// y (northing) 5428394.106300544
// zone id : 32
//
// Latitude of a known test point in Karsruhe
const float64_t LatitudeKarlsruhe = 49.0069;
// Longitude of a known test point in Karlsruhe
const float64_t LongitudeKarlsruhe = 8.4037;
// UTM coordinate X of the known test point in Karlsruhe
const float64_t UTMxKarlsruhe = 456391.2464264152;
// UTM coordinate Y of the known test point in Karlsruhe
const float64_t UTMyKarlsruhe = 5428394.106300544;
// UTM Zone Id of Karlsruhe
const size_t UTMZoneIdKarlsruhe = 32;

TEST(UTM_TRANSFORMATION, TestZoneIdCalculation)
{
    GeographicalTransformation::SetGlobalZoneIdByLatLon(LongitudeBeijing, LatitudeBeijing);

    ASSERT_EQ(GeographicalTransformation::GetZoneId(), UTMZoneIdBeijing);
}

///////////////////////////////////////////////////////////////////////////////
TEST(UTM_TRANSFORMATION, latlon2utm_beijing)
{
    const float64_t tol = 0.1;
    ::holo::geometry::Point2d p;
    GeographicalTransformation::SetGlobalZoneId(50);
    GeographicalTransformation::LL2UTM(LongitudeBeijing, LatitudeBeijing, p);
    ASSERT_NEAR(p.GetX(), UTMxBeijing, tol);
    ASSERT_NEAR(p.GetY(), UTMyBeijing, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(UTM_TRANSFORMATION, utm2latlon_beijing)
{
    const float64_t tol = 0.1;
    float64_t       lat, lon;
    ::holo::geometry::Point2d p(UTMxBeijing, UTMyBeijing);
    GeographicalTransformation::SetGlobalZoneId(50);
    GeographicalTransformation::UTM2LL(p, lon, lat);
    ASSERT_NEAR(lat, LatitudeBeijing, tol);
    ASSERT_NEAR(lon, LongitudeBeijing, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(UTM_TRANSFORMATION, latlon2utm_kalsruhe)
{
    const float64_t tol = 0.1;
    ::holo::geometry::Point2d p;
    GeographicalTransformation::SetGlobalZoneId(32);
    GeographicalTransformation::LL2UTM(LongitudeKarlsruhe, LatitudeKarlsruhe, p);
    ASSERT_NEAR(p.GetX(), UTMxKarlsruhe, tol);
    ASSERT_NEAR(p.GetY(), UTMyKarlsruhe, tol);
}

///////////////////////////////////////////////////////////////////////////////
TEST(UTM_TRANSFORMATION, utm2latlon_karlsruhe)
{
    const float64_t tol = 0.1;
    float64_t       lat, lon;
    ::holo::geometry::Point2d p(UTMxKarlsruhe, UTMyKarlsruhe);
    GeographicalTransformation::SetGlobalZoneId(32);
    GeographicalTransformation::UTM2LL(p, lon, lat);
    ASSERT_NEAR(lat, LatitudeKarlsruhe, tol);
    ASSERT_NEAR(lon, LongitudeKarlsruhe, tol);
}

TEST(UTM_TRANSFORMATION, GetZoneId)
{
    GeographicalTransformation::GetZoneId();
}

TEST(UTM_TRANSFORMATION, SetGlobalZoneIdByLatLon)
{
    // GeographicalTransformation::SetGlobalZoneIdByLatLon(181, 57);
    // GeographicalTransformation::SetGlobalZoneIdByLatLon(4, 100);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(3, 56);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(0, 72);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(9, 72);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(21, 72);
    GeographicalTransformation::SetGlobalZoneIdByLatLon(33, 72);
}

TEST(UTM_TRANSFORMATION, SetGlobalZoneId)
{
    const float64_t tol = 0.1;
    float64_t       lat, lon;
    ::holo::geometry::Point2d p(UTMxKarlsruhe, UTMyKarlsruhe);
    GeographicalTransformation::SetGlobalZoneId(1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    ::holo::GeographicalTransformation ut;
}
