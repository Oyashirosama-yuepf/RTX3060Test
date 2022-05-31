-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : VEHICLE_LOCATION
-- Unit(s) Under Test: vehicle_location
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

-- Unit: vehicle_location

-- Subprogram: holo::common::VehicleLocation::GetLocationX

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::GetLocationX
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:1
TEST.EXPECTED:vehicle_location.holo::common::VehicleLocation::GetLocationX.return:BOTTOM_MOST
TEST.END

-- Subprogram: holo::common::VehicleLocation::GetLocationY

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::GetLocationY
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:vehicle_location.holo::common::VehicleLocation::GetLocationY.return:BOTTOM_MOST
TEST.END

-- Subprogram: holo::common::VehicleLocation::GetPlane

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::GetPlane
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:5
TEST.EXPECTED:vehicle_location.holo::common::VehicleLocation::GetPlane.return:FRONT_WINDOW
TEST.ATTRIBUTES:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:EXPECTED_BASE=16
TEST.END

-- Subprogram: holo::common::VehicleLocation::SetLocation

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::SetLocation
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::SetLocation.x:BOTTOM_MOST
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::SetLocation.y:BOTTOM
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:16#4#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:16#1#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:0
TEST.END

-- Subprogram: holo::common::VehicleLocation::SetLocationX

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::SetLocationX
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::SetLocationX.x:BOTTOM_MOST
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:1
TEST.END

-- Subprogram: holo::common::VehicleLocation::SetLocationY

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::SetLocationY
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::SetLocationY.y:BOTTOM_MOST
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:1
TEST.END

-- Subprogram: holo::common::VehicleLocation::SetPlane

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::SetPlane
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::SetPlane.value:FRONT_WINDOW
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:16#5#
TEST.END

-- Subprogram: holo::common::VehicleLocation::VehicleLocation()

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::VehicleLocation()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:0
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:0
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:0
TEST.END

-- Subprogram: holo::common::VehicleLocation::VehicleLocation(holo::common::VehicleLocation::Plane,holo::common::VehicleLocation::Location,holo::common::VehicleLocation::Location)

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::VehicleLocation(holo::common::VehicleLocation::Plane,holo::common::VehicleLocation::Location,holo::common::VehicleLocation::Location)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::VehicleLocation(holo::common::VehicleLocation::Plane,holo::common::VehicleLocation::Location,holo::common::VehicleLocation::Location).plane:REAR
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::VehicleLocation(holo::common::VehicleLocation::Plane,holo::common::VehicleLocation::Location,holo::common::VehicleLocation::Location).x:BOTTOM_MOST
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::VehicleLocation(holo::common::VehicleLocation::Plane,holo::common::VehicleLocation::Location,holo::common::VehicleLocation::Location).y:MIDDLE
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:16#8#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:16#1#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:16#2#
TEST.END

-- Subprogram: holo::common::VehicleLocation::VehicleLocation(holo::uint16_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::VehicleLocation(holo::uint16_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::VehicleLocation(holo::uint16_t).value:16#1CC#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:16#C#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:16#C#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:16#1#
TEST.END

-- Subprogram: holo::common::VehicleLocation::operator=

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_location
TEST.SUBPROGRAM:holo::common::VehicleLocation::operator=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:vehicle_location.holo::common::VehicleLocation::operator=.value:16#1CC#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.y_:16#C#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.x_:16#C#
TEST.EXPECTED:vehicle_location.<<GLOBAL>>.(cl).holo::common::VehicleLocation.holo::common::VehicleLocation.plane_:16#1#
TEST.ATTRIBUTES:vehicle_location.holo::common::VehicleLocation::operator=.return.holo::common::VehicleLocation.y_:INPUT_BASE=16,EXPECTED_BASE=16
TEST.ATTRIBUTES:vehicle_location.holo::common::VehicleLocation::operator=.return.holo::common::VehicleLocation.x_:INPUT_BASE=16,EXPECTED_BASE=16
TEST.ATTRIBUTES:vehicle_location.holo::common::VehicleLocation::operator=.return.holo::common::VehicleLocation.plane_:INPUT_BASE=16,EXPECTED_BASE=16
TEST.END
