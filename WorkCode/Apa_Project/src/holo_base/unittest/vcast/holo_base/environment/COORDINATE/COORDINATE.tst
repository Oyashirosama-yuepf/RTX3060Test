-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : COORDINATE
-- Unit(s) Under Test: coordinate
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

-- Unit: coordinate

-- Subprogram: holo::common::Coordinate::Coordinate()

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Coordinate()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::Coordinate(holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Coordinate(holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.holo::common::Coordinate::Coordinate(holo::uint32_t).value:16#12345678#
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:16#2345678#
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:1
TEST.END

-- Subprogram: holo::common::Coordinate::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::DrCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::DrCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::DrCoordinate.version:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::DrCoordinate.return.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::DrCoordinate.return.holo::common::Coordinate.type_:5
TEST.END

-- Subprogram: holo::common::Coordinate::Gcj02Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Gcj02Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Gcj02Coordinate.return.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Gcj02Coordinate.return.holo::common::Coordinate.type_:11
TEST.END

-- Subprogram: holo::common::Coordinate::GetDrVersion

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetDrVersion
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:1
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetDrVersion.return:50
TEST.END

-- Subprogram: holo::common::Coordinate::GetParam

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetParam
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:16#2345678#
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetParam.return:16#2345678#
TEST.END

-- Subprogram: holo::common::Coordinate::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::GetType

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:2
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetType.return:WGS84
TEST.END

-- Subprogram: holo::common::Coordinate::GetUtmOffsetX

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetUtmOffsetX
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:1
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetUtmOffsetX.return:0
TEST.END

-- Subprogram: holo::common::Coordinate::GetUtmOffsetY

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetUtmOffsetY
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetUtmOffsetY.return:0
TEST.END

-- Subprogram: holo::common::Coordinate::GetUtmSouthFlag

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetUtmSouthFlag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetUtmSouthFlag.return:false
TEST.END

-- Subprogram: holo::common::Coordinate::GetUtmZone

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetUtmZone
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetUtmZone.return:50
TEST.END

-- Subprogram: holo::common::Coordinate::GetUtmZoneId

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetUtmZoneId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetUtmZoneId.return:50
TEST.END

-- Subprogram: holo::common::Coordinate::GetVehicleSensorId

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::GetVehicleSensorId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:1234
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetVehicleSensorId.return.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:2
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetVehicleSensorId.return.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:13
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetVehicleSensorId.return.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:4
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetVehicleSensorId.return.holo::common::SensorId.model_:UNKNOWN
TEST.EXPECTED:coordinate.holo::common::Coordinate::GetVehicleSensorId.return.holo::common::SensorId.category_:UNKNOWN
TEST.END

-- Subprogram: holo::common::Coordinate::PointConvert

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 5 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
      Cannot set return value of function holo::common::Coordinate::GetType in branch 4
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 5 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
      Cannot set return value of function holo::common::Coordinate::GetType in branch 4
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-003
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-003
TEST.BASIS_PATH:3 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-003-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-003-PARTIAL
TEST.BASIS_PATH:3 of 5 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-004
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-004
TEST.BASIS_PATH:4 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-004-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-004-PARTIAL
TEST.BASIS_PATH:4 of 5 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-005
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-005
TEST.BASIS_PATH:5 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (src_coord == dst_coord) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-005-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:BASIS-PATH-005-PARTIAL
TEST.BASIS_PATH:5 of 5 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (src_coord == dst_coord) ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord == dst_coord) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord == dst_coord) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord == dst_coord) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord == dst_coord) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_TT
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_TT
TEST.MCDC_BASIS_PATH:4 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #2, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_TT-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_TT-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #2, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_b_TF
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_b_TF
TEST.MCDC_BASIS_PATH:5 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_b_TF-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_b_TF-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_2_ROW_3_PAIR_a_Fx
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_2_ROW_3_PAIR_a_Fx
TEST.MCDC_BASIS_PATH:3 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_2_ROW_3_PAIR_a_Fx-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_2_ROW_3_PAIR_a_Fx-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_3_ROW_3_PAIR_a_TxT
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_3_PAIR_a_TxT
TEST.MCDC_BASIS_PATH:7 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> TRUE
      Row number 3 forms a pair with Row 7 for Condition #3, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_3_ROW_3_PAIR_a_TxT-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_3_PAIR_a_TxT-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> TRUE
      Row number 3 forms a pair with Row 7 for Condition #3, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_3_ROW_5_PAIR_b_FTT
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_5_PAIR_b_FTT
TEST.MCDC_BASIS_PATH:8 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> TRUE
      Row number 5 forms a pair with Row 7 for Condition #3, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_3_ROW_5_PAIR_b_FTT-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_5_PAIR_b_FTT-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> TRUE
      Row number 5 forms a pair with Row 7 for Condition #3, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_3_ROW_6_PAIR_c_FTF
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_6_PAIR_c_FTF
TEST.MCDC_BASIS_PATH:9 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 6 forms a pair with Row 5 for Condition #3, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_3_ROW_6_PAIR_c_FTF-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_6_PAIR_c_FTF-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 6 forms a pair with Row 5 for Condition #3, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_3_ROW_7_PAIR_a_FFx
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_7_PAIR_a_FFx
TEST.MCDC_BASIS_PATH:6 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 7 forms a pair with Row 3 for Condition #3, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_3_ROW_7_PAIR_a_FFx-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_3_ROW_7_PAIR_a_FFx-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      Row number 7 forms a pair with Row 3 for Condition #3, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_b_TTx
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_b_TTx
TEST.MCDC_BASIS_PATH:13 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 13
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #4, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
         Condition c ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_b_TTx-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_b_TTx-PARTIAL
TEST.MCDC_BASIS_PATH:13 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 13
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #4, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
         Condition c ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 4
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_4_ROW_3_PAIR_a_TFT
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_3_PAIR_a_TFT
TEST.MCDC_BASIS_PATH:11 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 11
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> TRUE
      Row number 3 forms a pair with Row 7 for Condition #4, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_4_ROW_3_PAIR_a_TFT-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_3_PAIR_a_TFT-PARTIAL
TEST.MCDC_BASIS_PATH:11 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 11
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> TRUE
      Row number 3 forms a pair with Row 7 for Condition #4, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 4
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_4_ROW_4_PAIR_b_TFF
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_4_PAIR_b_TFF
TEST.MCDC_BASIS_PATH:12 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 12
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #4, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_4_ROW_4_PAIR_b_TFF-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_4_PAIR_b_TFF-PARTIAL
TEST.MCDC_BASIS_PATH:12 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 12
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #4, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 4
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_4_ROW_7_PAIR_a_Fxx
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_7_PAIR_a_Fxx
TEST.MCDC_BASIS_PATH:10 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> FALSE
      Row number 7 forms a pair with Row 3 for Condition #4, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_4_ROW_7_PAIR_a_Fxx-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvert
TEST.NEW
TEST.NAME:COND_4_ROW_7_PAIR_a_Fxx-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 13
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (src_coord == dst_coord) ==> FALSE
      (2) if (Type::UTM6 == src_coord.GetType() && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (3) if ((Type::WGS84 == src_coord.GetType() || Type::GCJ02 == src_coord.GetType()) && Type::UTM6 == dst_coord.GetType()) ==> FALSE
      (4) if (Type::UTM6 == src_coord.GetType() && (Type::WGS84 == dst_coord.GetType() || Type::GCJ02 == dst_coord.GetType())) ==> FALSE
      Row number 7 forms a pair with Row 3 for Condition #4, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetType in branch 4
      Cannot set return value of function holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const in branch 1
      Cannot set return value of function holo::common::Coordinate::GetType in branch 2
      Cannot set return value of function holo::common::Coordinate::GetType in branch 3
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvert.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::PointConvertLonLatToUtm

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertLonLatToUtm
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertLonLatToUtm.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::PointConvertUtmToLonLat

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToLonLat
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToLonLat.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::PointConvertUtmToUtm

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetUtmZone in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetUtmZone in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetUtmZone in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::PointConvertUtmToUtm
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (src_coord.GetUtmZone() == dst_coord.GetUtmZone()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::GetUtmZone in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.src_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::PointConvertUtmToUtm.dst_coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetDrVersion

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetDrVersion
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetDrVersion.version:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetParam

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetParam
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetParam.param:50
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:50
TEST.END

-- Subprogram: holo::common::Coordinate::SetType

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetType.type:VEHICLE
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:1
TEST.END

-- Subprogram: holo::common::Coordinate::SetUtmOffsetX

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetUtmOffsetX
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetUtmOffsetX.offset_x:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:5242880
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetUtmOffsetY

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetUtmOffsetY
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetUtmOffsetY.offset_y:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:1280
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetUtmSouthFlag

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetUtmSouthFlag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetUtmSouthFlag.south_flag:true
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:128
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetUtmZone

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetUtmZone
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetUtmZone.zone:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetUtmZoneId

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetUtmZoneId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetUtmZoneId.zone_id:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::SetVehicleSensorId

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::SetVehicleSensorId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetVehicleSensorId.id.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::SetVehicleSensorId.id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:coordinate.holo::common::Coordinate::SetVehicleSensorId.id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:coordinate.holo::common::Coordinate::SetVehicleSensorId.id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.VALUE:coordinate.holo::common::Coordinate::SetVehicleSensorId.id.holo::common::SensorId.model_:UNKNOWN
TEST.VALUE:coordinate.holo::common::Coordinate::SetVehicleSensorId.id.holo::common::SensorId.category_:GNSS
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:16778017
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::Utm3Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Utm3Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::Utm3Coordinate.zone_id:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm3Coordinate.south_flag:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm3Coordinate.offset_x:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm3Coordinate.offset_y:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm3Coordinate.return.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm3Coordinate.return.holo::common::Coordinate.type_:4
TEST.END

-- Subprogram: holo::common::Coordinate::Utm6Coordinate(const PointType&)holo::common::Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Utm6Coordinate(const PointType&)holo::common::Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm6Coordinate(const PointType&)holo::common::Coordinate.return.holo::common::Coordinate.param_:1
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm6Coordinate(const PointType&)holo::common::Coordinate.return.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::Coordinate::Utm6Coordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Utm6Coordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.lon:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.lat:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.return.holo::common::Coordinate.param_:128
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.return.holo::common::Coordinate.type_:3
TEST.END

-- Subprogram: holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.zone_id:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.south_flag:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.offset_x:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.offset_y:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.return.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Utm6Coordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.return.holo::common::Coordinate.type_:3
TEST.END

-- Subprogram: holo::common::Coordinate::UtmCoordinate(const PointType&)holo::common::Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::UtmCoordinate(const PointType&)holo::common::Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.END

-- Subprogram: holo::common::Coordinate::UtmCoordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::UtmCoordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::UtmCoordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.lon:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::UtmCoordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.lat:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::UtmCoordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.return.holo::common::Coordinate.param_:128
TEST.EXPECTED:coordinate.holo::common::Coordinate::UtmCoordinate(holo::float64_t,holo::float64_t)holo::common::Coordinate.return.holo::common::Coordinate.type_:3
TEST.END

-- Subprogram: holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.zone_id:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.south_flag:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.offset_x:<<MIN>>
TEST.VALUE:coordinate.holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.offset_y:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.return.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::UtmCoordinate(holo::uint8_t,holo::bool_t,holo::uint32_t,holo::uint32_t)holo::common::Coordinate.return.holo::common::Coordinate.type_:3
TEST.END

-- Subprogram: holo::common::Coordinate::VehicleCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::VehicleCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::VehicleCoordinate.cat:USS
TEST.VALUE:coordinate.holo::common::Coordinate::VehicleCoordinate.model:GNSS_UBLOX_M8T
TEST.VALUE:coordinate.holo::common::Coordinate::VehicleCoordinate.plane:FRONT_WINDOW
TEST.VALUE:coordinate.holo::common::Coordinate::VehicleCoordinate.x:BOTTOM
TEST.VALUE:coordinate.holo::common::Coordinate::VehicleCoordinate.y:BOTTOM
TEST.VALUE:coordinate.holo::common::Coordinate::VehicleCoordinate.return:<<null>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::VehicleCoordinate.return.holo::common::Coordinate.param_:84149572
TEST.EXPECTED:coordinate.holo::common::Coordinate::VehicleCoordinate.return.holo::common::Coordinate.type_:1
TEST.END

-- Subprogram: holo::common::Coordinate::Wgs84Coordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::Wgs84Coordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Wgs84Coordinate.return.holo::common::Coordinate.param_:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::Wgs84Coordinate.return.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::Coordinate::operator const holo::uint32_t &

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator const holo::uint32_t &
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:1
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:2
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator const holo::uint32_t &.return:536870913
TEST.END

-- Subprogram: holo::common::Coordinate::operator holo::uint32_t &

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator holo::uint32_t &
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:1
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:2
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator holo::uint32_t &.return:536870913
TEST.END

-- Subprogram: holo::common::Coordinate::operator!=

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator!=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this == value)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator!=.value:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator!=.return:false
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator!=
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this == value)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator!=.value:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator!=.return:false
TEST.END

-- Subprogram: holo::common::Coordinate::operator=

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator=.value:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.param_:5
TEST.EXPECTED:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (static_cast< holo::uint32_t>((*this)) == static_cast< holo::uint32_t>(other)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator const holo::uint32_t & in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const.other.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (static_cast< holo::uint32_t>((*this)) == static_cast< holo::uint32_t>(other)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Coordinate::operator const holo::uint32_t & in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const.other.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator==(const holo::common::Coordinate&)holo::bool_t const.return:true
TEST.END

-- Subprogram: holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (static_cast< holo::uint32_t>((*this)) == value) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const.value:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:coordinate
TEST.SUBPROGRAM:holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (static_cast< holo::uint32_t>((*this)) == value) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:coordinate.<<GLOBAL>>.(cl).holo::common::Coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:coordinate.holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const.value:<<MIN>>
TEST.EXPECTED:coordinate.holo::common::Coordinate::operator==(holo::uint32_t)holo::bool_t const.return:true
TEST.END
