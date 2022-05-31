/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gnss_pvt.cpp
 * @brief Unit test for GnssPvt class.
 * @author Zhang Jiannan(zhangjiannan@holomatic.com)
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2020-12-17
 */

#include <gtest/gtest.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/path.h>
#include <holo/geometry/point3.h>
#include <holo/numerics/vector.h>

#include <array>
#include <tuple>

namespace holo
{
using common::GnssPvt;
using common::Timestamp;

TEST(GnssPvt, Constructor)
{
    GnssPvt pvt;
    ASSERT_EQ(0U, pvt.GetTimestamp().ToNsec());
    ASSERT_EQ(holo::common::Coordinate::Type::WGS84, pvt.GetCoordinate().GetType());

    ASSERT_EQ(false, pvt.IsPositionValid());
    ASSERT_EQ(false, pvt.IsVelocityValid());
    ASSERT_EQ(false, pvt.IsPositionCovValid());
    ASSERT_EQ(false, pvt.IsVelocityCovValid());
    ASSERT_EQ(false, pvt.IsValid());
    ASSERT_EQ(false, pvt.IsCovValid());

    ASSERT_EQ(GnssPvt::Mode::NO_POSITION, pvt.GetMode());

    ASSERT_EQ(0.0, pvt.GetLongitude());
    ASSERT_EQ(0.0, pvt.GetLatitude());
    ASSERT_EQ(0.0, pvt.GetHeight());

    ASSERT_EQ(0.0, pvt.GetVelocityEast());
    ASSERT_EQ(0.0, pvt.GetVelocityNorth());
    ASSERT_EQ(0.0, pvt.GetVelocityUp());

    ASSERT_EQ(0.0, pvt.GetLongitudeCov());
    ASSERT_EQ(0.0, pvt.GetLatitudeCov());
    ASSERT_EQ(0.0, pvt.GetHeightCov());

    ASSERT_EQ(0.0, pvt.GetVelocityEastCov());
    ASSERT_EQ(0.0, pvt.GetVelocityNorthCov());
    ASSERT_EQ(0.0, pvt.GetVelocityUpCov());
}

TEST(GnssPvt, SetGetTimestamp)
{
    Timestamp t{1, 2};
    GnssPvt   pvt;
    GnssPvt&  const_pvt = pvt;
    pvt.SetTimestamp(t);
    ASSERT_EQ(Timestamp(1, 2), pvt.GetTimestamp());
    ASSERT_EQ(Timestamp(1, 2), const_pvt.GetTimestamp());
}

TEST(GnssPvt, SetGetCoordinate)
{
    common::Coordinate coord = common::Coordinate::Gcj02Coordinate();
    GnssPvt            pvt;
    pvt.SetCoordinate(coord);
    ASSERT_EQ(coord, pvt.GetCoordinate());
}

TEST(GnssPvt, SetGetValidFlags)
{
    GnssPvt pvt;
    pvt.SetValidFlags(true, true, true, true);
    ASSERT_EQ(true, pvt.IsPositionValid());
    ASSERT_EQ(true, pvt.IsVelocityValid());
    ASSERT_EQ(true, pvt.IsPositionCovValid());
    ASSERT_EQ(true, pvt.IsVelocityCovValid());
    ASSERT_EQ(true, pvt.IsValid());
    ASSERT_EQ(true, pvt.IsCovValid());

    pvt.SetValidFlags(true, true, true, false);
    ASSERT_EQ(true, pvt.IsPositionValid());
    ASSERT_EQ(true, pvt.IsVelocityValid());
    ASSERT_EQ(true, pvt.IsPositionCovValid());
    ASSERT_EQ(false, pvt.IsVelocityCovValid());
    ASSERT_EQ(true, pvt.IsValid());
    ASSERT_EQ(false, pvt.IsCovValid());

    pvt.SetValidFlags(true, true, false, true);
    ASSERT_EQ(true, pvt.IsPositionValid());
    ASSERT_EQ(true, pvt.IsVelocityValid());
    ASSERT_EQ(false, pvt.IsPositionCovValid());
    ASSERT_EQ(true, pvt.IsVelocityCovValid());
    ASSERT_EQ(true, pvt.IsValid());
    ASSERT_EQ(false, pvt.IsCovValid());

    pvt.SetValidFlags(true, false, true, true);
    ASSERT_EQ(true, pvt.IsPositionValid());
    ASSERT_EQ(false, pvt.IsVelocityValid());
    ASSERT_EQ(true, pvt.IsPositionCovValid());
    ASSERT_EQ(true, pvt.IsVelocityCovValid());
    ASSERT_EQ(false, pvt.IsValid());
    ASSERT_EQ(true, pvt.IsCovValid());

    pvt.SetValidFlags(false, true, true, true);
    ASSERT_EQ(false, pvt.IsPositionValid());
    ASSERT_EQ(true, pvt.IsVelocityValid());
    ASSERT_EQ(true, pvt.IsPositionCovValid());
    ASSERT_EQ(true, pvt.IsVelocityCovValid());
    ASSERT_EQ(false, pvt.IsValid());
    ASSERT_EQ(true, pvt.IsCovValid());
}

TEST(GnssPvt, SetGetMode)
{
    GnssPvt pvt;
    ASSERT_EQ(GnssPvt::Mode::NO_POSITION, pvt.GetMode());

    pvt.SetMode(GnssPvt::Mode::SINGLE_FIX);
    ASSERT_EQ(GnssPvt::Mode::SINGLE_FIX, pvt.GetMode());

    pvt.SetMode(GnssPvt::Mode::DIFF_POSITION);
    ASSERT_EQ(GnssPvt::Mode::DIFF_POSITION, pvt.GetMode());

    pvt.SetMode(GnssPvt::Mode::RTK_FLOAT_FIX);
    ASSERT_EQ(GnssPvt::Mode::RTK_FLOAT_FIX, pvt.GetMode());

    pvt.SetMode(GnssPvt::Mode::RTK_INT_FIX);
    ASSERT_EQ(GnssPvt::Mode::RTK_INT_FIX, pvt.GetMode());
}

TEST(GnssPvt, SetGetLongitude)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetLongitude(value);
    ASSERT_EQ(value, pvt.GetLongitude());
}

TEST(GnssPvt, SetGetLatitude)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetLatitude(value);
    ASSERT_EQ(value, pvt.GetLatitude());
}

TEST(GnssPvt, SetGetHeight)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetHeight(value);
    ASSERT_EQ(value, pvt.GetHeight());
}

TEST(GnssPvt, SetGetVelocityEast)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetVelocityEast(value);
    ASSERT_EQ(value, pvt.GetVelocityEast());
}

TEST(GnssPvt, SetGetVelocityNorth)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetVelocityNorth(value);
    ASSERT_EQ(value, pvt.GetVelocityNorth());
}

TEST(GnssPvt, SetGetVelocityUp)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetVelocityUp(value);
    ASSERT_EQ(value, pvt.GetVelocityUp());
}

TEST(GnssPvt, SetGetLongitudeCov)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetLongitudeCov(value);
    ASSERT_EQ(value, pvt.GetLongitudeCov());
}

TEST(GnssPvt, SetGetLatitudeCov)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetLatitudeCov(value);
    ASSERT_EQ(value, pvt.GetLatitudeCov());
}

TEST(GnssPvt, SetGetHeightCov)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetHeightCov(value);
    ASSERT_EQ(value, pvt.GetHeightCov());
}

TEST(GnssPvt, SetGetVelocityEastCov)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetVelocityEastCov(value);
    ASSERT_EQ(value, pvt.GetVelocityEastCov());
}

TEST(GnssPvt, SetGetVelocityNorthCov)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetVelocityNorthCov(value);
    ASSERT_EQ(value, pvt.GetVelocityNorthCov());
}

TEST(GnssPvt, SetGetVelocityUpCov)
{
    float64_t value = 1.0;
    GnssPvt   pvt;
    pvt.SetVelocityUpCov(value);
    ASSERT_EQ(value, pvt.GetVelocityUpCov());
}

TEST(GnssPvt, SetGetPositionWithPointType)
{
    {
        using PointType = std::array<float64_t, 3>;
        GnssPvt pvt;
        ASSERT_EQ((PointType{0.0, 0.0, 0.0}), pvt.GetPosition<PointType>());
        PointType pt1{1.0, 2.0, 3.0};
        pvt.SetPosition(pt1);
        ASSERT_EQ((PointType{1.0, 2.0, 3.0}), pvt.GetPosition<PointType>());
        ASSERT_EQ(1.0, pvt.GetLongitude());
        ASSERT_EQ(2.0, pvt.GetLatitude());
        ASSERT_EQ(3.0, pvt.GetHeight());
    }

    {
        using PointType = std::array<float64_t, 4>;
        GnssPvt pvt;
        ASSERT_EQ((PointType{0.0, 0.0, 0.0}), pvt.GetPosition<PointType>());
        PointType pt1{1.0, 2.0, 3.0};
        pvt.SetPosition(pt1);
        ASSERT_EQ((PointType{1.0, 2.0, 3.0}), pvt.GetPosition<PointType>());
        ASSERT_EQ(1.0, pvt.GetLongitude());
        ASSERT_EQ(2.0, pvt.GetLatitude());
        ASSERT_EQ(3.0, pvt.GetHeight());
    }

    {
        using PointType = std::tuple<float64_t, float64_t, float64_t>;
        GnssPvt pvt;
        ASSERT_EQ((PointType{0.0, 0.0, 0.0}), pvt.GetPosition<PointType>());
        PointType pt1{1.0, 2.0, 3.0};
        pvt.SetPosition(pt1);
        ASSERT_EQ((PointType{1.0, 2.0, 3.0}), pvt.GetPosition<PointType>());
        ASSERT_EQ(1.0, pvt.GetLongitude());
        ASSERT_EQ(2.0, pvt.GetLatitude());
        ASSERT_EQ(3.0, pvt.GetHeight());
    }

    {
        using PointType = holo::geometry::Point3d;
        GnssPvt   pvt;
        ASSERT_EQ((PointType{0.0, 0.0, 0.0}), pvt.GetPosition<PointType>());
        PointType pt1{1.0, 2.0, 3.0};
        pvt.SetPosition(pt1);
        ASSERT_EQ((PointType{1.0, 2.0, 3.0}), pvt.GetPosition<PointType>());
        ASSERT_EQ(1.0, pvt.GetLongitude());
        ASSERT_EQ(2.0, pvt.GetLatitude());
        ASSERT_EQ(3.0, pvt.GetHeight());
    }

    {
        using PointType = holo::numerics::Vector3d;
        GnssPvt pvt;
        ASSERT_EQ((PointType{0.0, 0.0, 0.0}), pvt.GetPosition<PointType>());
        PointType pt1{1.0, 2.0, 3.0};
        pvt.SetPosition(pt1);
        ASSERT_EQ((PointType{1.0, 2.0, 3.0}), pvt.GetPosition<PointType>());
        ASSERT_EQ(1.0, pvt.GetLongitude());
        ASSERT_EQ(2.0, pvt.GetLatitude());
        ASSERT_EQ(3.0, pvt.GetHeight());
    }

    {
        using PointType = holo::numerics::Vector4d;
        GnssPvt pvt;
        ASSERT_EQ((PointType{0.0, 0.0, 0.0}), pvt.GetPosition<PointType>());
        PointType pt1{1.0, 2.0, 3.0};
        pvt.SetPosition(pt1);
        ASSERT_EQ((PointType{1.0, 2.0, 3.0}), pvt.GetPosition<PointType>());
        ASSERT_EQ(1.0, pvt.GetLongitude());
        ASSERT_EQ(2.0, pvt.GetLatitude());
        ASSERT_EQ(3.0, pvt.GetHeight());
    }
}

TEST(GnssPvt, SetGetVelocityWithPointType)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetVelocity<holo::geometry::Point3d>());
    holo::geometry::Point3d pt1{1.0, 2.0, 3.0};
    pvt.SetVelocity(pt1);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetVelocity<holo::geometry::Point3d>());
    ASSERT_EQ(1.0, pvt.GetVelocityEast());
    ASSERT_EQ(2.0, pvt.GetVelocityNorth());
    ASSERT_EQ(3.0, pvt.GetVelocityUp());
}

TEST(GnssPvt, SetGetPositionCovWithPointType)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetPositionCov<holo::geometry::Point3d>());
    holo::geometry::Point3d pt1{1.0, 2.0, 3.0};
    pvt.SetPositionCov(pt1);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetPositionCov<holo::geometry::Point3d>());
    ASSERT_EQ(1.0, pvt.GetLongitudeCov());
    ASSERT_EQ(2.0, pvt.GetLatitudeCov());
    ASSERT_EQ(3.0, pvt.GetHeightCov());
}

TEST(GnssPvt, SetGetVelocityCovWithPointType)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetVelocityCov<holo::geometry::Point3d>());
    holo::geometry::Point3d pt1{1.0, 2.0, 3.0};
    pvt.SetVelocityCov(pt1);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetVelocityCov<holo::geometry::Point3d>());
    ASSERT_EQ(1.0, pvt.GetVelocityEastCov());
    ASSERT_EQ(2.0, pvt.GetVelocityNorthCov());
    ASSERT_EQ(3.0, pvt.GetVelocityUpCov());
}

TEST(GnssPvt, SetPositionWithValues)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetPosition<holo::geometry::Point3d>());
    pvt.SetPosition(1.0, 2.0, 3.0);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetPosition<holo::geometry::Point3d>());
}

TEST(GnssPvt, SetVelocityWithValues)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetVelocity<holo::geometry::Point3d>());
    pvt.SetVelocity(1.0, 2.0, 3.0);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetVelocity<holo::geometry::Point3d>());
}

TEST(GnssPvt, SetPositionCovWithValues)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetPositionCov<holo::geometry::Point3d>());
    pvt.SetPositionCov(1.0, 2.0, 3.0);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetPositionCov<holo::geometry::Point3d>());
}

TEST(GnssPvt, SetVelocityCovWithValues)
{
    GnssPvt pvt;
    ASSERT_EQ((holo::geometry::Point3d{0.0, 0.0, 0.0}), pvt.GetVelocityCov<holo::geometry::Point3d>());
    pvt.SetVelocityCov(1.0, 2.0, 3.0);
    ASSERT_EQ((holo::geometry::Point3d{1.0, 2.0, 3.0}), pvt.GetVelocityCov<holo::geometry::Point3d>());
}

/**
 * @brief Test GnssPvt::GetSerializedSize
 */
TEST(GnssPvt, GetSerializedSize)
{
    GnssPvt pvt;
    ASSERT_EQ(112, pvt.GetSerializedSize<4U>());
    ASSERT_EQ(112, pvt.GetSerializedSize<8U>());
}

TEST(GnssPvt, SerializeDeserialize)
{
    GnssPvt                           pvt;
    GnssPvt                           pvt2;

    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);

    pvt.SetPosition(1, 2, 3);
    pvt.SetVelocity(4, 5, 6);
    pvt.SetPositionCov(7, 8, 9);
    pvt.SetVelocityCov(10, 11, 12);
    serializer << pvt;
    ASSERT_EQ(pvt.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<true, 4> deserializer(buffer, serializer.GetSize());
    deserializer >> pvt2;
    
    ASSERT_EQ(pvt2.GetTimestamp(), pvt.GetTimestamp());
    ASSERT_EQ(pvt2.GetCoordinate(), pvt.GetCoordinate());
    ASSERT_EQ(pvt2.GetLongitude(), pvt.GetLongitude());
    ASSERT_EQ(pvt2.GetLatitude(), pvt.GetLatitude());
    ASSERT_EQ(pvt2.GetHeight(), pvt.GetHeight());
    ASSERT_EQ(pvt2.GetVelocityEast(), pvt.GetVelocityEast());
    ASSERT_EQ(pvt2.GetVelocityNorth(), pvt.GetVelocityNorth());
    ASSERT_EQ(pvt2.GetVelocityUp(), pvt.GetVelocityUp());
    ASSERT_EQ(pvt2.GetLongitudeCov(), pvt.GetLongitudeCov());
    ASSERT_EQ(pvt2.GetLatitudeCov(), pvt.GetLatitudeCov());
    ASSERT_EQ(pvt2.GetHeightCov(), pvt.GetHeightCov());
    ASSERT_EQ(pvt2.GetVelocityEastCov(), pvt.GetVelocityEastCov());
    ASSERT_EQ(pvt2.GetVelocityNorthCov(), pvt.GetVelocityNorthCov());
    ASSERT_EQ(pvt2.GetVelocityUpCov(), pvt.GetVelocityUpCov());
}

}  // namespace holo

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
