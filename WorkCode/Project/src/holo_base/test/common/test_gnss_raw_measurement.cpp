/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @brief unit test for gnss raw measurement class
 * @author houyujian@holomatic.com
 * @date Mar 09, 2019
 */

#include <gtest/gtest.h>
#include <holo/common/gnss_raw_measurement.h>

TEST(GnssRawMeasurementTest, ALLInput)
{
    /* Create a GnssPosition by default constructor */
    holo::common::GnssRawMeasurement gnss_raw_measurement;
    holo::common::GnssRawMeasurement::RawMeasurementBlock raw_block;

    /* Test default constructor */
    ASSERT_FLOAT_EQ(0.0f, gnss_raw_measurement.GetGpsSec());
    ASSERT_EQ(0u, gnss_raw_measurement.GetGpsWeek());
    ASSERT_EQ(0u, gnss_raw_measurement.GetLeapSec());
    ASSERT_EQ(0u, gnss_raw_measurement.GetSatelliteNumber());
    ASSERT_FLOAT_EQ(0.0f, gnss_raw_measurement.GetPDop());
    gnss_raw_measurement.SetSatelliteNumber(2u);
    gnss_raw_measurement.GetRawMeasurementBlock(raw_block, 0u);
    ASSERT_FLOAT_EQ(0.0f, raw_block.pseudorange_measurement);
    ASSERT_FLOAT_EQ(0.0f, raw_block.carrier_phase_measurement);
    ASSERT_FLOAT_EQ(0.0f, raw_block.doppler_measurement);
    ASSERT_EQ(0u, raw_block.gnss_identifier);
    ASSERT_EQ(0u, raw_block.satellite_identifier);
    ASSERT_EQ(0u, raw_block.frequence_identifier);
    ASSERT_EQ(0u, raw_block.carrier_phase_locktime);
    ASSERT_EQ(0u, raw_block.carrier_noise_ratio);
    ASSERT_EQ(0u, raw_block.pseudorange_standard_deviation);
    ASSERT_EQ(0u, raw_block.doppler_standard_deviation);
    ASSERT_EQ(0u, raw_block.carrier_phase_standard_deviation);
    ASSERT_EQ(0u, raw_block.tracking_status);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssRawMeasurementTest, GpsSecInput)
{
    /* Construct a GnssRawData */
    holo::common::GnssRawMeasurement gnss_raw_measurement;

    /* Set gps sec to GnssRawData */
    holo::float64_t expected_gps_sec = 10000.0f;
    gnss_raw_measurement.SetGpsSec(expected_gps_sec);

    /* Test get gps sec function */
    ASSERT_FLOAT_EQ(expected_gps_sec, gnss_raw_measurement.GetGpsSec());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssRawMeasurementTest, GpsWeekInput)
{
    /* Create a GnssRawMeasurement */
    holo::common::GnssRawMeasurement gnss_raw_measurement;

    /* Set gps week to GnssRawData */
    holo::uint16_t expected_gps_week = 2000u;
    gnss_raw_measurement.SetGpsWeek(expected_gps_week);

    /* Test get gps week function */
    ASSERT_EQ(expected_gps_week, gnss_raw_measurement.GetGpsWeek());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssRawMeasurementTest, LeapSecInput)
{
    /* Create a GnssRawMeasurement */
    holo::common::GnssRawMeasurement gnss_raw_measurement;

    /* Generate expected value */
    holo::int8_t expected_leapsec = 18u;
    gnss_raw_measurement.SetLeapSec(expected_leapsec);

    /* Test set and get leapsec function */
    ASSERT_EQ(expected_leapsec, gnss_raw_measurement.GetLeapSec());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssRawMeasurementTest, SatelliteNumberInput)
{
    /* Create a GnssRawMeasurement */
    holo::common::GnssRawMeasurement gnss_raw_measurement;

    /* Generate expected value */
    holo::uint8_t expected_sat_num = 30u;
    gnss_raw_measurement.SetSatelliteNumber(expected_sat_num);

    /* Test set and get satellite numbel function */
    ASSERT_EQ(expected_sat_num, gnss_raw_measurement.GetSatelliteNumber());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssRawMeasurementTest, PdopInput)
{
    /* Create a GnssRawMeasurement */
    holo::common::GnssRawMeasurement gnss_raw_measurement;

    /* Generate expected value */
    holo::float32_t expected_pdop = 1.2f;
    gnss_raw_measurement.SetPDop(expected_pdop);

    /* Test set and get latitude convariance function */
    ASSERT_FLOAT_EQ(expected_pdop, gnss_raw_measurement.GetPDop());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST(GnssRawMeasurementTest, RawBlockInput)
{
    /* Create a GnssRawMeasurement */
    holo::common::GnssRawMeasurement gnss_raw_measurement;

    /* Generate expected value */
    holo::common::GnssRawMeasurement::RawMeasurementBlock expected_raw_block_input, expected_raw_block_output;
    expected_raw_block_input.pseudorange_measurement = 1.1f;
    expected_raw_block_input.carrier_phase_measurement = 2.2f;
    expected_raw_block_input.doppler_measurement = 3.3f;
    expected_raw_block_input.gnss_identifier = 1u;
    expected_raw_block_input.satellite_identifier = 2u;
    expected_raw_block_input.frequence_identifier = 3u;
    expected_raw_block_input.carrier_phase_locktime = 4u;
    expected_raw_block_input.carrier_noise_ratio = 5u;
    expected_raw_block_input.pseudorange_standard_deviation = 6u;
    expected_raw_block_input.carrier_phase_standard_deviation = 7u;
    expected_raw_block_input.doppler_standard_deviation = 8u;
    expected_raw_block_input.tracking_status = 9u;
    gnss_raw_measurement.SetSatelliteNumber(10u);
    gnss_raw_measurement.SetRawMeasurementBlock(expected_raw_block_input, 5u);
    /* Test set and get latitude convariance function */
    gnss_raw_measurement.GetRawMeasurementBlock(expected_raw_block_output, 5u);
    ASSERT_FLOAT_EQ(1.1f, expected_raw_block_output.pseudorange_measurement);
    ASSERT_FLOAT_EQ(2.2f, expected_raw_block_output.carrier_phase_measurement);
    ASSERT_FLOAT_EQ(3.3f, expected_raw_block_output.doppler_measurement);
    ASSERT_EQ(1u, expected_raw_block_output.gnss_identifier);
    ASSERT_EQ(2u, expected_raw_block_output.satellite_identifier);
    ASSERT_EQ(3u, expected_raw_block_output.frequence_identifier);
    ASSERT_EQ(4u, expected_raw_block_output.carrier_phase_locktime);
    ASSERT_EQ(5u, expected_raw_block_output.carrier_noise_ratio);
    ASSERT_EQ(6u, expected_raw_block_output.pseudorange_standard_deviation);
    ASSERT_EQ(7u, expected_raw_block_output.carrier_phase_standard_deviation);
    ASSERT_EQ(8u, expected_raw_block_output.doppler_standard_deviation);
    ASSERT_EQ(9u, expected_raw_block_output.tracking_status);
}

TEST(GnssRawMeasurementTest, GetSerializedSize)
{
    holo::common::GnssRawMeasurement gnss_raw_measurement;
    ASSERT_EQ(16, gnss_raw_measurement.GetSerializedSize<4U>());
    ASSERT_EQ(16, gnss_raw_measurement.GetSerializedSize<8U>());
}

TEST(GnssRawMeasurementTest, SerializeAndDeserialize)
{
    holo::common::GnssRawMeasurement gnss_raw_measurement_input, gnss_raw_measurement_output;

    holo::common::GnssRawMeasurement::RawMeasurementBlock expected_raw_block, expected_raw_block2;
    
    expected_raw_block.pseudorange_measurement = 1.1f;
    expected_raw_block.carrier_phase_measurement = 2.2f;
    expected_raw_block.doppler_measurement = 3.3f;
    expected_raw_block.gnss_identifier = 1u;
    expected_raw_block.satellite_identifier = 2u;
    expected_raw_block.frequence_identifier = 3u;
    expected_raw_block.carrier_phase_locktime = 4u;
    expected_raw_block.carrier_noise_ratio = 5u;
    expected_raw_block.pseudorange_standard_deviation = 6u;
    expected_raw_block.carrier_phase_standard_deviation = 7u;
    expected_raw_block.doppler_standard_deviation = 8u;
    expected_raw_block.tracking_status = 9u;

    gnss_raw_measurement_input.SetSatelliteNumber(2U);
    gnss_raw_measurement_input.SetRawMeasurementBlock(expected_raw_block, 1U);

    gnss_raw_measurement_input.SetGpsSec(2.0f);
    gnss_raw_measurement_input.SetGpsWeek(5U);
    gnss_raw_measurement_input.SetLeapSec(2U);
    gnss_raw_measurement_input.SetPDop(5.5f);

    uint8_t buffer[1024];
    holo::serialization::Serializer<>           serializer(buffer, 1024);
    serializer << gnss_raw_measurement_input;
    ASSERT_EQ(gnss_raw_measurement_input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> gnss_raw_measurement_output;
    gnss_raw_measurement_output.GetRawMeasurementBlock(expected_raw_block2, 1U);

    ASSERT_EQ(gnss_raw_measurement_input.GetTimestamp(), gnss_raw_measurement_output.GetTimestamp());
    ASSERT_EQ(gnss_raw_measurement_input.GetGpsSec(), gnss_raw_measurement_output.GetGpsSec());
    ASSERT_EQ(gnss_raw_measurement_input.GetGpsWeek(), gnss_raw_measurement_output.GetGpsWeek());
    ASSERT_EQ(gnss_raw_measurement_input.GetLeapSec(), gnss_raw_measurement_output.GetLeapSec());
    ASSERT_EQ(gnss_raw_measurement_input.GetSatelliteNumber(), gnss_raw_measurement_output.GetSatelliteNumber());
    ASSERT_EQ(gnss_raw_measurement_input.GetPDop(), gnss_raw_measurement_output.GetPDop());

    ASSERT_EQ(expected_raw_block.pseudorange_measurement, expected_raw_block2.pseudorange_measurement);
    ASSERT_EQ(expected_raw_block.carrier_phase_measurement, expected_raw_block2.carrier_phase_measurement);
    ASSERT_EQ(expected_raw_block.doppler_measurement, expected_raw_block2.doppler_measurement);
    ASSERT_EQ(expected_raw_block.carrier_noise_ratio, expected_raw_block2.carrier_noise_ratio);
    ASSERT_EQ(expected_raw_block.pseudorange_standard_deviation, expected_raw_block2.pseudorange_standard_deviation);
    ASSERT_EQ(expected_raw_block.carrier_phase_standard_deviation, expected_raw_block2.carrier_phase_standard_deviation);
    ASSERT_EQ(expected_raw_block.tracking_status, expected_raw_block2.tracking_status);
    ASSERT_EQ(expected_raw_block.gnss_identifier, expected_raw_block2.gnss_identifier);
    ASSERT_EQ(expected_raw_block.satellite_identifier, expected_raw_block2.satellite_identifier);
    ASSERT_EQ(expected_raw_block.frequence_identifier, expected_raw_block2.frequence_identifier);
    ASSERT_EQ(expected_raw_block.carrier_phase_locktime, expected_raw_block2.carrier_phase_locktime);
    ASSERT_EQ(expected_raw_block.doppler_standard_deviation, expected_raw_block2.doppler_standard_deviation);

}

TEST(GnssRawMeasurementTest, GetAndSetRawMeasurementBlock)
{
    holo::common::GnssRawMeasurement gnss_raw_measurement;
    holo::common::GnssRawMeasurement::RawMeasurementBlock raw_block1, raw_block2;
    try
    {
        gnss_raw_measurement.GetRawMeasurementBlock(raw_block1, 1U);
    }
    catch(...)
    {
    }

    try
    {
        gnss_raw_measurement.SetRawMeasurementBlock(raw_block2, 5u);
    }
    catch(const std::exception& e)
    {
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
