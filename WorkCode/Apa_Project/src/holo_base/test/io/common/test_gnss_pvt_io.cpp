/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gnss_pvt_io.cpp
 * @brief unit test io utils for gnss_pvt objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */

#include <gtest/gtest.h>
#include <holo/common/gnss_pvt.h>
#include <holo/io/common/gnss_pvt.h>

using GnssPvt = holo::common::GnssPvt;
using Mode    = GnssPvt::Mode;

TEST(GnssPvtIO, EncodeAndDecodeGnssPvt)
{
    GnssPvt gnss_pvt;
    GnssPvt gnss_pvt_expected;

    gnss_pvt.SetTimestamp(holo::common::Timestamp(10, 20));
    gnss_pvt.SetCoordinate(holo::common::Coordinate(30));
    gnss_pvt.SetLongitude(10);
    gnss_pvt.SetLatitude(20);
    gnss_pvt.SetHeight(30);
    gnss_pvt.SetVelocityEast(40);
    gnss_pvt.SetVelocityNorth(50);
    gnss_pvt.SetVelocityUp(60);
    gnss_pvt.SetLongitudeCov(70);
    gnss_pvt.SetLatitudeCov(80);
    gnss_pvt.SetHeightCov(90);
    gnss_pvt.SetVelocityEastCov(100);
    gnss_pvt.SetVelocityNorthCov(110);
    gnss_pvt.SetVelocityUpCov(120);

    gnss_pvt.SetValidFlags(true, true, true, true);
    gnss_pvt.SetMode(Mode::SINGLE_FIX);

    YAML::Node node;
    node["test"]      = gnss_pvt;
    gnss_pvt_expected = node["test"].as<GnssPvt>();

    ASSERT_EQ(gnss_pvt.GetTimestamp(), gnss_pvt_expected.GetTimestamp());
    ASSERT_EQ(gnss_pvt.GetCoordinate(), gnss_pvt_expected.GetCoordinate());
    ASSERT_EQ(gnss_pvt.GetLongitude(), gnss_pvt_expected.GetLongitude());
    ASSERT_EQ(gnss_pvt.GetLatitude(), gnss_pvt_expected.GetLatitude());
    ASSERT_EQ(gnss_pvt.GetHeight(), gnss_pvt_expected.GetHeight());
    ASSERT_EQ(gnss_pvt.GetVelocityEast(), gnss_pvt_expected.GetVelocityEast());
    ASSERT_EQ(gnss_pvt.GetVelocityNorth(), gnss_pvt_expected.GetVelocityNorth());
    ASSERT_EQ(gnss_pvt.GetVelocityUp(), gnss_pvt_expected.GetVelocityUp());
    ASSERT_EQ(gnss_pvt.GetLongitudeCov(), gnss_pvt_expected.GetLongitudeCov());
    ASSERT_EQ(gnss_pvt.GetLatitudeCov(), gnss_pvt_expected.GetLatitudeCov());
    ASSERT_EQ(gnss_pvt.GetHeightCov(), gnss_pvt_expected.GetHeightCov());
    ASSERT_EQ(gnss_pvt.GetVelocityEastCov(), gnss_pvt_expected.GetVelocityEastCov());
    ASSERT_EQ(gnss_pvt.GetVelocityNorthCov(), gnss_pvt_expected.GetVelocityNorthCov());
    ASSERT_EQ(gnss_pvt.GetVelocityUpCov(), gnss_pvt_expected.GetVelocityUpCov());
    ASSERT_EQ(gnss_pvt.IsPositionValid(), gnss_pvt_expected.IsPositionValid());
    ASSERT_EQ(gnss_pvt.IsVelocityValid(), gnss_pvt_expected.IsVelocityValid());
    ASSERT_EQ(gnss_pvt.IsPositionCovValid(), gnss_pvt_expected.IsPositionCovValid());
    ASSERT_EQ(gnss_pvt.IsVelocityCovValid(), gnss_pvt_expected.IsVelocityCovValid());
    ASSERT_EQ(gnss_pvt.GetMode(), gnss_pvt_expected.GetMode());
}

TEST(GnssPvtIO, DecodeGnssPvt_1)
{
    GnssPvt gnss_pvt;
    GnssPvt gnss_pvt_expected;

    gnss_pvt.SetTimestamp(holo::common::Timestamp(10, 20));
    gnss_pvt.SetCoordinate(holo::common::Coordinate(30));
    gnss_pvt.SetLongitude(10);
    gnss_pvt.SetLatitude(20);
    gnss_pvt.SetHeight(30);
    gnss_pvt.SetVelocityEast(40);
    gnss_pvt.SetVelocityNorth(50);
    gnss_pvt.SetVelocityUp(60);
    gnss_pvt.SetLongitudeCov(70);
    gnss_pvt.SetLatitudeCov(80);
    gnss_pvt.SetHeightCov(90);
    gnss_pvt.SetVelocityEastCov(100);
    gnss_pvt.SetVelocityNorthCov(110);
    gnss_pvt.SetVelocityUpCov(120);

    gnss_pvt.SetValidFlags(true, true, true, true);
    gnss_pvt.SetMode(Mode::SINGLE_FIX);

    YAML::Node node =
        YAML::Load("{'timestamp':{'sec':10,'nsec':20},'coordinate':30,'longitude':10.0,'latitude':20,'height':30,'"
                   "velocity_east':40,'velocity_north':50,'velocity_up':60,'longitude_cov':70,'latitude_cov':80,'"
                   "height_cov':90,'velocity_east_cov':100,'velocity_north_cov':110,'velocity_up_cov':120,'status':{'"
                   "position_valid_flag':true, 'velocity_valid_flag':true, "
                   "'position_cov_valid_flag':true,'velocity_cov_valid_flag':true,'mode':'SINGLE_FIX'}}");
    gnss_pvt_expected = node.as<GnssPvt>();

    ASSERT_EQ(gnss_pvt.GetTimestamp(), gnss_pvt_expected.GetTimestamp());
    ASSERT_EQ(gnss_pvt.GetCoordinate(), gnss_pvt_expected.GetCoordinate());
    ASSERT_EQ(gnss_pvt.GetLongitude(), gnss_pvt_expected.GetLongitude());
    ASSERT_EQ(gnss_pvt.GetLatitude(), gnss_pvt_expected.GetLatitude());
    ASSERT_EQ(gnss_pvt.GetHeight(), gnss_pvt_expected.GetHeight());
    ASSERT_EQ(gnss_pvt.GetVelocityEast(), gnss_pvt_expected.GetVelocityEast());
    ASSERT_EQ(gnss_pvt.GetVelocityNorth(), gnss_pvt_expected.GetVelocityNorth());
    ASSERT_EQ(gnss_pvt.GetVelocityUp(), gnss_pvt_expected.GetVelocityUp());
    ASSERT_EQ(gnss_pvt.GetLongitudeCov(), gnss_pvt_expected.GetLongitudeCov());
    ASSERT_EQ(gnss_pvt.GetLatitudeCov(), gnss_pvt_expected.GetLatitudeCov());
    ASSERT_EQ(gnss_pvt.GetHeightCov(), gnss_pvt_expected.GetHeightCov());
    ASSERT_EQ(gnss_pvt.GetVelocityEastCov(), gnss_pvt_expected.GetVelocityEastCov());
    ASSERT_EQ(gnss_pvt.GetVelocityNorthCov(), gnss_pvt_expected.GetVelocityNorthCov());
    ASSERT_EQ(gnss_pvt.GetVelocityUpCov(), gnss_pvt_expected.GetVelocityUpCov());
    ASSERT_EQ(gnss_pvt.IsPositionValid(), gnss_pvt_expected.IsPositionValid());
    ASSERT_EQ(gnss_pvt.IsVelocityValid(), gnss_pvt_expected.IsVelocityValid());
    ASSERT_EQ(gnss_pvt.IsPositionCovValid(), gnss_pvt_expected.IsPositionCovValid());
    ASSERT_EQ(gnss_pvt.IsVelocityCovValid(), gnss_pvt_expected.IsVelocityCovValid());
    ASSERT_EQ(gnss_pvt.GetMode(), gnss_pvt_expected.GetMode());
}

TEST(GnssPvtIO, DecodeGnssPvt_2)
{
    GnssPvt gnss_pvt;
    GnssPvt gnss_pvt_expected;

    gnss_pvt.SetTimestamp(holo::common::Timestamp(10, 20));
    gnss_pvt.SetCoordinate(holo::common::Coordinate(30));
    gnss_pvt.SetLongitude(10);
    gnss_pvt.SetLatitude(20);
    gnss_pvt.SetHeight(30);
    gnss_pvt.SetVelocityEast(40);
    gnss_pvt.SetVelocityNorth(50);
    gnss_pvt.SetVelocityUp(60);
    gnss_pvt.SetLongitudeCov(70);
    gnss_pvt.SetLatitudeCov(80);
    gnss_pvt.SetHeightCov(90);
    gnss_pvt.SetVelocityEastCov(100);
    gnss_pvt.SetVelocityNorthCov(110);
    gnss_pvt.SetVelocityUpCov(120);

    gnss_pvt.SetValidFlags(true, true, true, true);
    gnss_pvt.SetMode(Mode::SINGLE_FIX);

    YAML::Node node = YAML::Load(
        "{'timestamp':{'sec':10,'nsec':20},'coordinate':30,'longitude':10.0,'latitude':20,'height':30,'velocity_east':"
        "40,'velocity_north':50,'velocity_up':60,'longitude_cov':70,'latitude_cov':80,'height_cov':90,'velocity_east_"
        "cov':100,'velocity_north_cov':110,'velocity_up_cov':120,'status':{'position_valid_flag':true, "
        "'velocity_valid_flag':true, 'position_cov_valid_flag':true,'velocity_cov_valid_flag':true,'mode':2}}");
    gnss_pvt_expected = node.as<GnssPvt>();

    ASSERT_EQ(gnss_pvt.GetTimestamp(), gnss_pvt_expected.GetTimestamp());
    ASSERT_EQ(gnss_pvt.GetCoordinate(), gnss_pvt_expected.GetCoordinate());
    ASSERT_EQ(gnss_pvt.GetLongitude(), gnss_pvt_expected.GetLongitude());
    ASSERT_EQ(gnss_pvt.GetLatitude(), gnss_pvt_expected.GetLatitude());
    ASSERT_EQ(gnss_pvt.GetHeight(), gnss_pvt_expected.GetHeight());
    ASSERT_EQ(gnss_pvt.GetVelocityEast(), gnss_pvt_expected.GetVelocityEast());
    ASSERT_EQ(gnss_pvt.GetVelocityNorth(), gnss_pvt_expected.GetVelocityNorth());
    ASSERT_EQ(gnss_pvt.GetVelocityUp(), gnss_pvt_expected.GetVelocityUp());
    ASSERT_EQ(gnss_pvt.GetLongitudeCov(), gnss_pvt_expected.GetLongitudeCov());
    ASSERT_EQ(gnss_pvt.GetLatitudeCov(), gnss_pvt_expected.GetLatitudeCov());
    ASSERT_EQ(gnss_pvt.GetHeightCov(), gnss_pvt_expected.GetHeightCov());
    ASSERT_EQ(gnss_pvt.GetVelocityEastCov(), gnss_pvt_expected.GetVelocityEastCov());
    ASSERT_EQ(gnss_pvt.GetVelocityNorthCov(), gnss_pvt_expected.GetVelocityNorthCov());
    ASSERT_EQ(gnss_pvt.GetVelocityUpCov(), gnss_pvt_expected.GetVelocityUpCov());
    ASSERT_EQ(gnss_pvt.IsPositionValid(), gnss_pvt_expected.IsPositionValid());
    ASSERT_EQ(gnss_pvt.IsVelocityValid(), gnss_pvt_expected.IsVelocityValid());
    ASSERT_EQ(gnss_pvt.IsPositionCovValid(), gnss_pvt_expected.IsPositionCovValid());
    ASSERT_EQ(gnss_pvt.IsVelocityCovValid(), gnss_pvt_expected.IsVelocityCovValid());
    ASSERT_EQ(gnss_pvt.GetMode(), gnss_pvt_expected.GetMode());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
