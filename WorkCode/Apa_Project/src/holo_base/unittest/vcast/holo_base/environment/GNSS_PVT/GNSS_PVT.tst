-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : GNSS_PVT
-- Unit(s) Under Test: gnss_pvt
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

-- Unit: gnss_pvt

-- Subprogram: holo::common::GnssPvt::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetCoordinate
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.coordinate_.holo::common::Coordinate.param_:1
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.coordinate_.holo::common::Coordinate.type_:2
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetCoordinate.return.holo::common::Coordinate.param_:1
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetCoordinate.return.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::GnssPvt::GetHeight

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetHeight
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetHeight
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.height_:3.4
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetHeight.return:3.4
TEST.END

-- Subprogram: holo::common::GnssPvt::GetHeightCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetHeightCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetHeightCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.height_cov_:3.5
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetHeightCov.return:3.5
TEST.END

-- Subprogram: holo::common::GnssPvt::GetLatitude

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetLatitude
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetLatitude
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.latitude_:1.2
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetLatitude.return:1.2
TEST.END

-- Subprogram: holo::common::GnssPvt::GetLatitudeCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetLatitudeCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetLatitudeCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.latitude_cov_:6.7
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetLatitudeCov.return:6.7
TEST.END

-- Subprogram: holo::common::GnssPvt::GetLongitude

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetLongitude
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetLongitude
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.longitude_:3.6
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetLongitude.return:3.6
TEST.END

-- Subprogram: holo::common::GnssPvt::GetLongitudeCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetLongitudeCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetLongitudeCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.longitude_cov_:3.4
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetLongitudeCov.return:3.4
TEST.END

-- Subprogram: holo::common::GnssPvt::GetMode

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetMode
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetMode
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:256
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetMode.return:TIMING_ONLY
TEST.END

-- Subprogram: holo::common::GnssPvt::GetPosition

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetPosition
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetPosition
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.longitude_:1.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.latitude_:2.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.height_:3.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetPosition.return[0]:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetPosition.return[1]:2.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetPosition.return[2]:3.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetPositionCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetPositionCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetPositionCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.longitude_cov_:1.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.latitude_cov_:2.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.height_cov_:3.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetPositionCov.return[0]:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetPositionCov.return[1]:2.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetPositionCov.return[2]:3.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetSerializedSize
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetSerializedSize.return:112
TEST.END

-- Subprogram: holo::common::GnssPvt::GetTimestamp()const holo::common::Timestamp const

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetTimestamp()const holo::common::Timestamp const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetTimestamp()const holo::common::Timestamp const
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.stamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.stamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetTimestamp()const holo::common::Timestamp const.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetTimestamp()const holo::common::Timestamp const.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::GnssPvt::GetTimestamp()holo::common::Timestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetTimestamp()holo::common::Timestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetTimestamp()holo::common::Timestamp
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.stamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.stamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetTimestamp()holo::common::Timestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetTimestamp()holo::common::Timestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocity

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocity
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocity
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_east_:1.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_north_:2.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_up_:3.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocity.return[0]:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocity.return[1]:2.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocity.return[2]:3.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_east_cov_:1.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_north_cov_:2.0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_up_cov_:3.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityCov.return[0]:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityCov.return[1]:2.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityCov.return[2]:3.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityEast

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityEast
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityEast
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_east_:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityEast.return:1.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityEastCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityEastCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityEastCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_east_cov_:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityEastCov.return:1.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityNorth

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityNorth
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityNorth
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_north_:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityNorth.return:1.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityNorthCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityNorthCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityNorthCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_north_cov_:1.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityNorthCov.return:1.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityUp

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityUp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityUp
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_up_:3.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityUp.return:3.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GetVelocityUpCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GetVelocityUpCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::GetVelocityUpCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_up_cov_:3.0
TEST.EXPECTED:gnss_pvt.holo::common::GnssPvt::GetVelocityUpCov.return:3.0
TEST.END

-- Subprogram: holo::common::GnssPvt::GnssPvt

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::GnssPvt
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.stamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.stamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.coordinate_.holo::common::Coordinate.param_:0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.coordinate_.holo::common::Coordinate.type_:2
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.longitude_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.latitude_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.height_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_east_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_north_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_up_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.longitude_cov_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.latitude_cov_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.height_cov_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_east_cov_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_north_cov_:0.0
TEST.EXPECTED:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.velocity_up_cov_:0.0
TEST.END

-- Subprogram: holo::common::GnssPvt::IsCovValid

-- Test Case: COND_1_ROW_1_PAIR_a_TT-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsCovValid
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TT-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (status_ & (0x4) && status_ & (0x8)) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:4
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TT-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsCovValid
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (status_ & (0x4) && status_ & (0x8)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:4
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_b_TF-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsCovValid
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_b_TF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (status_ & (0x4) && status_ & (0x8)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:4
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_a_Fx-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsCovValid
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_a_Fx-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (status_ & (0x4) && status_ & (0x8)) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:0
TEST.END

-- Subprogram: holo::common::GnssPvt::IsPositionCovValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsPositionCovValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::IsPositionValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsPositionValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::IsValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_TT-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsValid
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TT-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (status_ & (0x1) && status_ & (0x2)) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:1
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TT-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsValid
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (status_ & (0x1) && status_ & (0x2)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_b_TF-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsValid
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_b_TF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (status_ & (0x1) && status_ & (0x2)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:1
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_a_Fx-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsValid
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_a_Fx-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (status_ & (0x1) && status_ & (0x2)) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Multiple equality operators with different values (gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_) in branch 1
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.status_:0
TEST.END

-- Subprogram: holo::common::GnssPvt::IsVelocityCovValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsVelocityCovValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::IsVelocityValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::IsVelocityValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetCoordinate
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetCoordinate.coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetHeight

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetHeight
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetHeight
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetHeight.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetHeightCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetHeightCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetHeightCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetHeightCov.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetLatitude

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetLatitude
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetLatitude
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetLatitude.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetLatitudeCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetLatitudeCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetLatitudeCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetLatitudeCov.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetLongitude

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetLongitude
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetLongitude
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetLongitude.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetLongitudeCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetLongitudeCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetLongitudeCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetLongitudeCov.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetMode

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetMode
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetMode
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetMode.mode:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetPosition(const std::array<float, 3UL>&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetPosition(const std::array<float, 3UL>&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetPosition(holo::float64_t,holo::float64_t,holo::float64_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetPosition(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetPosition(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetPosition(holo::float64_t,holo::float64_t,holo::float64_t).longitude:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetPosition(holo::float64_t,holo::float64_t,holo::float64_t).latitude:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetPosition(holo::float64_t,holo::float64_t,holo::float64_t).height:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetPositionCov(const holo::geometry::Point3f&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetPositionCov(const holo::geometry::Point3f&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetPositionCov(holo::float64_t,holo::float64_t,holo::float64_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetPositionCov(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetPositionCov(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetPositionCov(holo::float64_t,holo::float64_t,holo::float64_t).longitude_cov:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetPositionCov(holo::float64_t,holo::float64_t,holo::float64_t).latitude_cov:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetPositionCov(holo::float64_t,holo::float64_t,holo::float64_t).height_cov:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetTimestamp
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetTimestamp.stamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetValidFlags

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetValidFlags
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetValidFlags
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetValidFlags.position:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetValidFlags.velocity:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetValidFlags.position_cov:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetValidFlags.velocity_cov:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocity(const holo::geometry::Point3f&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocity(const holo::geometry::Point3f&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocity(holo::float64_t,holo::float64_t,holo::float64_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocity(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocity(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocity(holo::float64_t,holo::float64_t,holo::float64_t).velocity_east:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocity(holo::float64_t,holo::float64_t,holo::float64_t).velocity_north:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocity(holo::float64_t,holo::float64_t,holo::float64_t).velocity_up:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityCov(const PointType&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityCov(const PointType&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityCov(holo::float64_t,holo::float64_t,holo::float64_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityCov(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityCov(holo::float64_t,holo::float64_t,holo::float64_t)
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityCov(holo::float64_t,holo::float64_t,holo::float64_t).velocity_east_cov:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityCov(holo::float64_t,holo::float64_t,holo::float64_t).velocity_north_cov:<<MIN>>
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityCov(holo::float64_t,holo::float64_t,holo::float64_t).velocity_up_cov:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityEast

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityEast
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityEast
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityEast.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityEastCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityEastCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityEastCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityEastCov.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityNorth

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityNorth
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityNorth
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityNorth.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityNorthCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityNorthCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityNorthCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityNorthCov.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityUp

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityUp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityUp
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityUp.value:<<MIN>>
TEST.END

-- Subprogram: holo::common::GnssPvt::SetVelocityUpCov

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:holo::common::GnssPvt::SetVelocityUpCov
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.STUB:gnss_pvt.holo::common::GnssPvt::SetVelocityUpCov
TEST.VALUE:gnss_pvt.<<GLOBAL>>.(cl).holo::common::GnssPvt.holo::common::GnssPvt.<<constructor>>.GnssPvt().<<call>>:0
TEST.VALUE:gnss_pvt.holo::common::GnssPvt::SetVelocityUpCov.value:<<MIN>>
TEST.END
