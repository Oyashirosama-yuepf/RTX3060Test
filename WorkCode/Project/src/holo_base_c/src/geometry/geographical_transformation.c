/*!
 * * \brief Conversion between lat/lon and UTM
 * * \author Huang Qi
 * * \date Jan 7, 2019
 * * \attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice. */

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <holo_c/geometry/geographical_transformation.h>

static float64_t deg2rad = M_PI / 180.0f;
static float64_t rad2deg = 180.0f / M_PI;

// WGS-84 reference system parameters
static const float64_t a          = 6378137;
static const float64_t eccSquared = 0.00669438;
static const float64_t k0         = 0.9996;

retcode_t LL2UTM(const float64_t Lat, const float64_t Long, 
                 float64_t* UTMNorthing, float64_t* UTMEasting, 
                 int* ZoneID)
{
    retcode_t rc = RC_SUCCESS;
    float64_t LongOrigin;
    float64_t eccPrimeSquared;
    float64_t N, T, C, A, M;

    float64_t LongTemp;

    float64_t LatRad;
    float64_t LongRad;
    float64_t LongOriginRad;
    int       ZoneNumber;

    assert(UTMNorthing != NULL);
    assert(UTMEasting != NULL);
    assert(isnan(Lat) == 0);
    assert(isnan(Long) == 0);

    LongTemp = (Long + 180) - (int)((Long + 180) / 360) * 360 - 180;  // -180.00 .. 179.9
    LatRad   = Lat * deg2rad;
    LongRad  = LongTemp * deg2rad;

    ZoneNumber = (int)((LongTemp + 180) / 6) + 1;

    if (Lat >= 56.0 && Lat < 64.0 && LongTemp >= 3.0 && LongTemp < 12.0)
        ZoneNumber = 32;

    if (Lat >= 72.0 && Lat < 84.0)
    {
        if (LongTemp >= 0.0 && LongTemp < 9.0)
            ZoneNumber = 31;
        else if (LongTemp >= 9.0 && LongTemp < 21.0)
            ZoneNumber = 33;
        else if (LongTemp >= 21.0 && LongTemp < 33.0)
            ZoneNumber = 35;
        else if (LongTemp >= 33.0 && LongTemp < 42.0)
            ZoneNumber = 37;
    }
    LongOrigin    = (ZoneNumber - 1) * 6 - 180 + 3;  //*+3 puts origin in middle of zone
    LongOriginRad = LongOrigin * deg2rad;

    if (ZoneID != NULL)
    {
        *ZoneID = ZoneNumber;
    }

    eccPrimeSquared = (eccSquared) / (1 - eccSquared);

    N = a / sqrt(1 - eccSquared * sin(LatRad) * sin(LatRad));
    T = tan(LatRad) * tan(LatRad);
    C = eccPrimeSquared * cos(LatRad) * cos(LatRad);
    A = cos(LatRad) * (LongRad - LongOriginRad);

    M = a *
        ((1 - eccSquared / 4 - 3 * eccSquared * eccSquared / 64 - 5 * eccSquared * eccSquared * eccSquared / 256) *
             LatRad -
         (3 * eccSquared / 8 + 3 * eccSquared * eccSquared / 32 + 45 * eccSquared * eccSquared * eccSquared / 1024) *
             sin(2 * LatRad) +
         (15 * eccSquared * eccSquared / 256 + 45 * eccSquared * eccSquared * eccSquared / 1024) * sin(4 * LatRad) -
         (35 * eccSquared * eccSquared * eccSquared / 3072) * sin(6 * LatRad));

    *UTMEasting = (float64_t)(k0 * N *
                                  (A + (1 - T + C) * A * A * A / 6 +
                                   (5 - 18 * T + T * T + 72 * C - 58 * eccPrimeSquared) * A * A * A * A * A / 120) +
                              500000.0);

    *UTMNorthing = (float64_t)(
        k0 * (M + N * tan(LatRad) *
                      (A * A / 2 + (5 - T + 9 * C + 4 * C * C) * A * A * A * A / 24 +
                       (61 - 58 * T + T * T + 600 * C - 330 * eccPrimeSquared) * A * A * A * A * A * A / 720)));
    if (Lat < 0)
        *UTMNorthing += 10000000.0;  // 10000000 meter offset for southern hemisphere

    if (isnan(*UTMEasting) || isnan(*UTMNorthing))
    {
        rc = RC_FAIL;
    }

    return rc;
}

retcode_t UTM2LL(const float64_t UTMNorthing, const float64_t UTMEasting, int UTMZone, float64_t* Lat, float64_t* Long)
{
    retcode_t rc = RC_SUCCESS;
    float64_t eccPrimeSquared;
    float64_t e1;
    float64_t N1, T1, C1, R1, D, M;
    float64_t LongOrigin;
    float64_t mu, phi1Rad;
    float64_t x, y;
    int       ZoneNumber;

    assert(Lat != NULL);
    assert(Long != NULL);
    assert(isnan(UTMNorthing) == 0);
    assert(isnan(UTMEasting) == 0);

    e1 = (1 - sqrt(1 - eccSquared)) / (1 + sqrt(1 - eccSquared));

    x = UTMEasting - 500000.0;  // remove 500,000 meter offset for longitude
    y = UTMNorthing;

    ZoneNumber = UTMZone;

    LongOrigin = (ZoneNumber - 1) * 6 - 180 + 3;  // +3 puts origin in middle of zone

    eccPrimeSquared = (eccSquared) / (1 - eccSquared);

    M  = y / k0;
    mu = M /
         (a * (1 - eccSquared / 4 - 3 * eccSquared * eccSquared / 64 - 5 * eccSquared * eccSquared * eccSquared / 256));

    phi1Rad = mu + (3 * e1 / 2 - 27 * e1 * e1 * e1 / 32) * sin(2 * mu) +
              (21 * e1 * e1 / 16 - 55 * e1 * e1 * e1 * e1 / 32) * sin(4 * mu) + (151 * e1 * e1 * e1 / 96) * sin(6 * mu);

    N1 = a / sqrt(1 - eccSquared * sin(phi1Rad) * sin(phi1Rad));
    T1 = tan(phi1Rad) * tan(phi1Rad);
    C1 = eccPrimeSquared * cos(phi1Rad) * cos(phi1Rad);
    R1 = a * (1 - eccSquared) / pow(1 - eccSquared * sin(phi1Rad) * sin(phi1Rad), 1.5);
    D  = x / (N1 * k0);

    *Lat = phi1Rad - (N1 * tan(phi1Rad) / R1) *
                         (D * D / 2 - (5 + 3 * T1 + 10 * C1 - 4 * C1 * C1 - 9 * eccPrimeSquared) * D * D * D * D / 24 +
                          (61 + 90 * T1 + 298 * C1 + 45 * T1 * T1 - 252 * eccPrimeSquared - 3 * C1 * C1) * D * D * D *
                              D * D * D / 720);
    *Lat = *Lat * rad2deg;

    *Long = (D - (1 + 2 * T1 + C1) * D * D * D / 6 +
             (5 - 2 * C1 + 28 * T1 - 3 * C1 * C1 + 8 * eccPrimeSquared + 24 * T1 * T1) * D * D * D * D * D / 120) /
            cos(phi1Rad);
    *Long = LongOrigin + *Long * rad2deg;

    if (isnan(*Lat) || isnan(*Long))
    {
        rc = RC_FAIL;
    }

    return rc;
}
