/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_gnss_raw_measurement_io.cpp
 * @brief unit test io utils for gnss_raw_measurement objects
 * @author Zhou huishuang(zhouhuishuang@holomatic.com)
 * @date 2021-04-12
 */
#include <gtest/gtest.h>
#include <holo/common/gnss_raw_measurement.h>
#include <holo/io/common/gnss_raw_measurement.h>
#include <yaml-cpp/yaml.h>

using GnssRawMeasurement = holo::common::GnssRawMeasurement;

TEST(GnssRawMeasurementIO, EncodeAndDecodeGnssRawMeasurement)
{
    GnssRawMeasurement gnss_raw_measurement, gnss_raw_measurement_expected;

    GnssRawMeasurement::RawMeasurementBlock block1, block2, expected_block1, expected_block2;

    block1.pseudorange_measurement          = 1.1f;
    block1.carrier_phase_measurement        = 2.2f;
    block1.doppler_measurement              = 3.3f;
    block1.gnss_identifier                  = 5u;
    block1.satellite_identifier             = 2u;
    block1.frequence_identifier             = 3u;
    block1.carrier_phase_locktime           = 4u;
    block1.carrier_noise_ratio              = 5u;
    block1.pseudorange_standard_deviation   = 6u;
    block1.carrier_phase_standard_deviation = 7u;
    block1.doppler_standard_deviation       = 8u;
    block1.tracking_status                  = 9u;

    block2.pseudorange_measurement          = 10.1f;
    block2.carrier_phase_measurement        = 20.2f;
    block2.doppler_measurement              = 30.3f;
    block2.gnss_identifier                  = 10u;
    block2.satellite_identifier             = 20u;
    block2.frequence_identifier             = 30u;
    block2.carrier_phase_locktime           = 40u;
    block2.carrier_noise_ratio              = 50u;
    block2.pseudorange_standard_deviation   = 60u;
    block2.carrier_phase_standard_deviation = 70u;
    block2.doppler_standard_deviation       = 80u;
    block2.tracking_status                  = 90u;

    gnss_raw_measurement.SetSatelliteNumber(2U);
    gnss_raw_measurement.SetRawMeasurementBlock(block1, 0U);
    gnss_raw_measurement.SetRawMeasurementBlock(block2, 1U);

    gnss_raw_measurement.SetGpsSec(2.0f);
    gnss_raw_measurement.SetGpsWeek(5U);
    gnss_raw_measurement.SetLeapSec(2U);
    gnss_raw_measurement.SetPDop(5.5f);

    YAML::Node node;
    node["test"]                  = gnss_raw_measurement;
    gnss_raw_measurement_expected = node["test"].as<GnssRawMeasurement>();

    ASSERT_EQ(gnss_raw_measurement.GetTimestamp(), gnss_raw_measurement_expected.GetTimestamp());
    ASSERT_EQ(gnss_raw_measurement.GetGpsSec(), gnss_raw_measurement_expected.GetGpsSec());
    ASSERT_EQ(gnss_raw_measurement.GetGpsWeek(), gnss_raw_measurement_expected.GetGpsWeek());
    ASSERT_EQ(gnss_raw_measurement.GetLeapSec(), gnss_raw_measurement_expected.GetLeapSec());
    ASSERT_EQ(gnss_raw_measurement.GetSatelliteNumber(), gnss_raw_measurement_expected.GetSatelliteNumber());
    ASSERT_EQ(gnss_raw_measurement.GetPDop(), gnss_raw_measurement_expected.GetPDop());
    gnss_raw_measurement_expected.GetRawMeasurementBlock(expected_block1, 0U);
    gnss_raw_measurement_expected.GetRawMeasurementBlock(expected_block2, 1U);

    ASSERT_EQ(block1.pseudorange_measurement, expected_block1.pseudorange_measurement);
    ASSERT_EQ(block1.carrier_phase_measurement, expected_block1.carrier_phase_measurement);
    ASSERT_EQ(block1.doppler_measurement, expected_block1.doppler_measurement);
    ASSERT_EQ(block1.carrier_noise_ratio, expected_block1.carrier_noise_ratio);
    ASSERT_EQ(block1.pseudorange_standard_deviation, expected_block1.pseudorange_standard_deviation);
    ASSERT_EQ(block1.carrier_phase_standard_deviation, expected_block1.carrier_phase_standard_deviation);
    ASSERT_EQ(block1.tracking_status, expected_block1.tracking_status);
    ASSERT_EQ(block1.gnss_identifier, expected_block1.gnss_identifier);
    ASSERT_EQ(block1.satellite_identifier, expected_block1.satellite_identifier);
    ASSERT_EQ(block1.frequence_identifier, expected_block1.frequence_identifier);
    ASSERT_EQ(block1.carrier_phase_locktime, expected_block1.carrier_phase_locktime);
    ASSERT_EQ(block1.doppler_standard_deviation, expected_block1.doppler_standard_deviation);

    ASSERT_NEAR(block2.pseudorange_measurement, expected_block2.pseudorange_measurement, 1e-10);
    ASSERT_NEAR(block2.carrier_phase_measurement, expected_block2.carrier_phase_measurement, 1e-10);
    ASSERT_NEAR(block2.doppler_measurement, expected_block2.doppler_measurement, 1e-10);
    ASSERT_EQ(block2.carrier_noise_ratio, expected_block2.carrier_noise_ratio);
    ASSERT_EQ(block2.pseudorange_standard_deviation, expected_block2.pseudorange_standard_deviation);
    ASSERT_EQ(block2.carrier_phase_standard_deviation, expected_block2.carrier_phase_standard_deviation);
    ASSERT_EQ(block2.tracking_status, expected_block2.tracking_status);
    ASSERT_EQ(block2.gnss_identifier, expected_block2.gnss_identifier);
    ASSERT_EQ(block2.satellite_identifier, expected_block2.satellite_identifier);
    ASSERT_EQ(block2.frequence_identifier, expected_block2.frequence_identifier);
    ASSERT_EQ(block2.carrier_phase_locktime, expected_block2.carrier_phase_locktime);
    ASSERT_EQ(block2.doppler_standard_deviation, expected_block2.doppler_standard_deviation);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
