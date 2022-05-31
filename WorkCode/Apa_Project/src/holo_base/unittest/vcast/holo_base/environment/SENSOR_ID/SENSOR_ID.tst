-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : SENSOR_ID
-- Unit(s) Under Test: sensor_id
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

-- Unit: sensor_id

-- Subprogram: holo::common::SensorId::GetCategory

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::GetCategory
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.category_:GNSS
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetCategory.return:GNSS
TEST.END

-- Subprogram: holo::common::SensorId::GetLocation()const holo::common::VehicleLocation const

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::GetLocation()const holo::common::VehicleLocation const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetLocation()const holo::common::VehicleLocation const.return.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetLocation()const holo::common::VehicleLocation const.return.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetLocation()const holo::common::VehicleLocation const.return.holo::common::VehicleLocation.plane_:3
TEST.END

-- Subprogram: holo::common::SensorId::GetLocation()holo::common::VehicleLocation

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::GetLocation()holo::common::VehicleLocation
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetLocation()holo::common::VehicleLocation.return.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetLocation()holo::common::VehicleLocation.return.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetLocation()holo::common::VehicleLocation.return.holo::common::VehicleLocation.plane_:3
TEST.END

-- Subprogram: holo::common::SensorId::GetModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::GetModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.model_:GNSS_UBLOX_F9
TEST.EXPECTED:sensor_id.holo::common::SensorId::GetModel.return:GNSS_UBLOX_F9
TEST.END

-- Subprogram: holo::common::SensorId::SensorId()

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::SensorId()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:0
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:0
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:0
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.model_:UNKNOWN
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.category_:UNKNOWN
TEST.END

-- Subprogram: holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).cat:GNSS
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).model:GNSS_UBLOX_F9
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.y_:1
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.x_:2
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).cat:GNSS
TEST.EXPECTED:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).model:GNSS_UBLOX_F9
TEST.EXPECTED:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:sensor_id.holo::common::SensorId::SensorId(holo::common::SensorId::Category,holo::common::SensorId::Model,const holo::common::VehicleLocation&).location.holo::common::VehicleLocation.plane_:3
TEST.END

-- Subprogram: holo::common::SensorId::SensorId(holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::SensorId(holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.holo::common::SensorId::SensorId(holo::uint32_t).value:33752069
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:5
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:0
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:4
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.model_:GNSS_UBLOX_M8L
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.category_:IMU
TEST.END

-- Subprogram: holo::common::SensorId::SetCategory

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::SetCategory
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.holo::common::SensorId::SetCategory.cat:USS
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.category_:USS
TEST.END

-- Subprogram: holo::common::SensorId::SetLocation

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::SetLocation
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.holo::common::SensorId::SetLocation.location.holo::common::VehicleLocation.<<constructor>>.VehicleLocation().<<call>>:0
TEST.VALUE:sensor_id.holo::common::SensorId::SetLocation.location.holo::common::VehicleLocation.y_:1
TEST.VALUE:sensor_id.holo::common::SensorId::SetLocation.location.holo::common::VehicleLocation.x_:2
TEST.VALUE:sensor_id.holo::common::SensorId::SetLocation.location.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.END

-- Subprogram: holo::common::SensorId::SetModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::SetModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.holo::common::SensorId::SetModel.model:GNSS_UBLOX_F9
TEST.EXPECTED:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.model_:GNSS_UBLOX_F9
TEST.END

-- Subprogram: holo::common::SensorId::operator holo::uint32_t

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::operator holo::uint32_t
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:5
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:0
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:4
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.model_:GNSS_UBLOX_M8L
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.category_:IMU
TEST.EXPECTED:sensor_id.holo::common::SensorId::operator holo::uint32_t.return:33752069
TEST.END

-- Subprogram: holo::common::SensorId::operator=

-- Test Case: BASIS-PATH-001
TEST.UNIT:sensor_id
TEST.SUBPROGRAM:holo::common::SensorId::operator=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:sensor_id.<<GLOBAL>>.(cl).holo::common::SensorId.holo::common::SensorId.<<constructor>>.SensorId().<<call>>:0
TEST.VALUE:sensor_id.holo::common::SensorId::operator=.value:33752069
TEST.EXPECTED:sensor_id.holo::common::SensorId::operator=.return.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:5
TEST.EXPECTED:sensor_id.holo::common::SensorId::operator=.return.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:0
TEST.EXPECTED:sensor_id.holo::common::SensorId::operator=.return.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:4
TEST.EXPECTED:sensor_id.holo::common::SensorId::operator=.return.holo::common::SensorId.model_:GNSS_UBLOX_M8L
TEST.EXPECTED:sensor_id.holo::common::SensorId::operator=.return.holo::common::SensorId.category_:IMU
TEST.END
