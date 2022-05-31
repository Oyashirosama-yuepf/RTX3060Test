-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : GNSS_RAW_MEASUREMENT
-- Unit(s) Under Test: gnss_raw_measurement
--
-- Script Features
TEST.SCRIPT_FEATURE:C_DIRECT_ARRAY_INDEXING
TEST.SCRIPT_FEATURE:CPP_CLASS_OBJECT_REVISION
TEST.SCRIPT_FEATURE:MULTIPLE_UUT_SUPPORT
TEST.SCRIPT_FEATURE:REMOVED_CL_PREFIX
TEST.SCRIPT_FEATURE:MIXED_CASE_NAMES
TEST.SCRIPT_FEATURE:STANDARD_SPACING_R2
TEST.SCRIPT_FEATURE:OVERLOADED_CONST_SUPPORT
TEST.SCRIPT_FEATURE:UNDERSCORE_NULLPTR
TEST.SCRIPT_FEATURE:FULL_PARAMETER_TYPES
TEST.SCRIPT_FEATURE:STRUCT_DTOR_ADDS_POINTER
TEST.SCRIPT_FEATURE:STRUCT_FIELD_CTOR_ADDS_POINTER
TEST.SCRIPT_FEATURE:STATIC_HEADER_FUNCS_IN_UUTS
TEST.SCRIPT_FEATURE:VCAST_MAIN_NOT_RENAMED
--

-- Unit: gnss_raw_measurement

-- Subprogram: holo::common::GnssRawMeasurement::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < satellite_number_) ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < satellite_number_) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < satellite_number_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < satellite_number_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetGpsSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetGpsSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_second_:5.0
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetGpsSec.return:5.0
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetGpsWeek

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetGpsWeek
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_week_:5
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetGpsWeek.return:5
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetLeapSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetLeapSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.leap_second_:5
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetLeapSec.return:5
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetPDop

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetPDop
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.pdop_:5.0
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetPDop.return:5.0
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetRawMeasurementBlock

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetRawMeasurementBlock
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (index >= this->GetSatelliteNumber()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:5
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.index:6
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetRawMeasurementBlock
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (index >= this->GetSatelliteNumber()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:5
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].pseudorange_measurement:1.0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].carrier_phase_measurement:2.0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].doppler_measurement:3.0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].gnss_identifier:4
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].satellite_identifier:5
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].frequence_identifier:6
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].carrier_phase_locktime:7
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].carrier_noise_ratio:8
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].pseudorange_standard_deviation:9
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].carrier_phase_standard_deviation:11
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].doppler_standard_deviation:12
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[1].tracking_status:13
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.index:1
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.pseudorange_measurement:1.0
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.carrier_phase_measurement:2.0
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.doppler_measurement:3.0
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.gnss_identifier:4
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.satellite_identifier:5
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.frequence_identifier:6
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.carrier_phase_locktime:7
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.carrier_noise_ratio:8
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.pseudorange_standard_deviation:9
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.carrier_phase_standard_deviation:11
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.doppler_standard_deviation:12
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetRawMeasurementBlock.raw_block.tracking_status:13
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetSatelliteNumber

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetSatelliteNumber
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:5
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetSatelliteNumber.return:5
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetSerializedSize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetSerializedSize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (satellite_number_ > 0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MAX>>
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetSerializedSize.return:8176
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetSerializedSize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (satellite_number_ > 0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MIN>>
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetSerializedSize.return:16
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_second_:1.0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_week_:2
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetTimestamp.return.holo::common::details::Timestamp.sec_:1209601
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::GetTimestamp.return.holo::common::details::Timestamp.nsec_:0
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::GnssRawMeasurement

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::GnssRawMeasurement
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_second_:0.0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_week_:0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.leap_second_:0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.pdop_:0.0
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < satellite_number_) ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < satellite_number_) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < satellite_number_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::Serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < satellite_number_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::SetGpsSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetGpsSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetGpsSec.gps_second:5.0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_second_:5.0
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::SetGpsWeek

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetGpsWeek
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetGpsWeek.gps_week:5
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.gps_week_:5
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::SetLeapSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetLeapSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetLeapSec.leap_second:5
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.leap_second_:5
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::SetPDop

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetPDop
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetPDop.pDop:5.0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.pdop_:5.0
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::SetRawMeasurementBlock

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetRawMeasurementBlock
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (index >= this->GetSatelliteNumber()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:5
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.index:<<MAX>>
TEST.EXPECTED:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetRawMeasurementBlock
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (index >= this->GetSatelliteNumber()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:3
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.pseudorange_measurement:1.0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.carrier_phase_measurement:1.0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.doppler_measurement:1.0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.gnss_identifier:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.satellite_identifier:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.frequence_identifier:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.carrier_phase_locktime:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.carrier_noise_ratio:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.pseudorange_standard_deviation:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.carrier_phase_standard_deviation:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.doppler_standard_deviation:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.raw_block.tracking_status:1
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetRawMeasurementBlock.index:0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].pseudorange_measurement:1.0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].carrier_phase_measurement:1.0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].doppler_measurement:1.0
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].gnss_identifier:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].satellite_identifier:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].frequence_identifier:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].carrier_phase_locktime:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].carrier_noise_ratio:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].pseudorange_standard_deviation:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].carrier_phase_standard_deviation:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].doppler_standard_deviation:1
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.raw_block_[0].tracking_status:1
TEST.END

-- Subprogram: holo::common::GnssRawMeasurement::SetSatelliteNumber

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_raw_measurement
TEST.SUBPROGRAM:holo::common::GnssRawMeasurement::SetSatelliteNumber
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.<<constructor>>.GnssRawMeasurement().<<call>>:0
TEST.VALUE:gnss_raw_measurement.holo::common::GnssRawMeasurement::SetSatelliteNumber.satellite_number:5
TEST.EXPECTED:gnss_raw_measurement.<<GLOBAL>>.(cl).holo::common::GnssRawMeasurement.holo::common::GnssRawMeasurement.satellite_number_:5
TEST.END
