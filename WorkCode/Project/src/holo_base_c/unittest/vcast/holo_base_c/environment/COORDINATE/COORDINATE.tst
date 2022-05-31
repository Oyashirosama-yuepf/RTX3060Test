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

-- Subprogram: coordinate_default_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_default_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_default_create.return:0
TEST.END

-- Subprogram: coordinate_dr_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_dr_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_dr_create.version:<<MIN>>
TEST.END

-- Subprogram: coordinate_dr_get_version

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_dr_get_version
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_dr_get_version.return:100
TEST.VALUE_USER_CODE:coordinate.coordinate_dr_get_version.coordinate
<<coordinate.coordinate_dr_get_version.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_dr_set_version

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_dr_set_version
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_dr_set_version.version:100
TEST.VALUE_USER_CODE:coordinate.coordinate_dr_set_version.coordinate
coordinate = coordinate_dr_create(0);
<<coordinate.coordinate_dr_set_version.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_get_param

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_param
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_get_param.return:16#2345678#
TEST.VALUE_USER_CODE:coordinate.coordinate_get_param.coordinate
<<coordinate.coordinate_get_param.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_param_test_for_utm3_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_param
TEST.NEW
TEST.NAME:get_param_test_for_utm3_create
TEST.EXPECTED:coordinate.coordinate_get_param.return:0
TEST.VALUE_USER_CODE:coordinate.coordinate_get_param.coordinate
<<coordinate.coordinate_get_param.coordinate>> = ( &<<coordinate.coordinate_utm3_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_param_test_for_utm6_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_param
TEST.NEW
TEST.NAME:get_param_test_for_utm6_create
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_get_param.return:0
TEST.VALUE_USER_CODE:coordinate.coordinate_get_param.coordinate
<<coordinate.coordinate_get_param.coordinate>> = ( &<<coordinate.coordinate_utm6_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_param_test_for_utm_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_param
TEST.NEW
TEST.NAME:get_param_test_for_utm_create
TEST.EXPECTED:coordinate.coordinate_get_param.return:0
TEST.VALUE_USER_CODE:coordinate.coordinate_get_param.coordinate
<<coordinate.coordinate_get_param.coordinate>> = ( &<<coordinate.coordinate_utm_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_param_test_for_vehicle_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_param
TEST.NEW
TEST.NAME:get_param_test_for_vehicle_create
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_get_param.return:0
TEST.VALUE_USER_CODE:coordinate.coordinate_get_param.coordinate
<<coordinate.coordinate_get_param.coordinate>> = ( &<<coordinate.coordinate_vehicle_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_param_test_for_wgs84_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_param
TEST.NEW
TEST.NAME:get_param_test_for_wgs84_create
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_get_param.return:0
TEST.VALUE_USER_CODE:coordinate.coordinate_get_param.coordinate
<<coordinate.coordinate_get_param.coordinate>> = ( &
<<coordinate.coordinate_wgs84_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_get_type

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_type
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_get_type.coordinate:<<malloc 1>>
TEST.EXPECTED:coordinate.coordinate_get_type.return:COORDINATE_TYPE_VEHICLE
TEST.VALUE_USER_CODE:coordinate.coordinate_get_type.coordinate[0]
<<coordinate.coordinate_get_type.coordinate>>[0] = ( coordinate_vehicle_create(0U) );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_type_test_for_utm3_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_type
TEST.NEW
TEST.NAME:get_type_test_for_utm3_create
TEST.EXPECTED:coordinate.coordinate_get_type.return:COORDINATE_TYPE_UTM3
TEST.VALUE_USER_CODE:coordinate.coordinate_get_type.coordinate
<<coordinate.coordinate_get_type.coordinate>> = ( &<<coordinate.coordinate_utm3_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_type_test_for_utm6_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_type
TEST.NEW
TEST.NAME:get_type_test_for_utm6_create
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_get_type.return:COORDINATE_TYPE_UTM6
TEST.VALUE_USER_CODE:coordinate.coordinate_get_type.coordinate
<<coordinate.coordinate_get_type.coordinate>> = ( &<<coordinate.coordinate_utm6_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_type_test_for_utm_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_type
TEST.NEW
TEST.NAME:get_type_test_for_utm_create
TEST.EXPECTED:coordinate.coordinate_get_type.return:COORDINATE_TYPE_UTM6
TEST.VALUE_USER_CODE:coordinate.coordinate_get_type.coordinate
<<coordinate.coordinate_get_type.coordinate>> = ( &<<coordinate.coordinate_utm_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_type_test_for_vehicle_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_type
TEST.NEW
TEST.NAME:get_type_test_for_vehicle_create
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_get_type.return:COORDINATE_TYPE_VEHICLE
TEST.VALUE_USER_CODE:coordinate.coordinate_get_type.coordinate
<<coordinate.coordinate_get_type.coordinate>> = ( &<<coordinate.coordinate_vehicle_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: get_type_test_for_wgs84_create
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_get_type
TEST.NEW
TEST.NAME:get_type_test_for_wgs84_create
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_get_type.return:COORDINATE_TYPE_WGS84
TEST.VALUE_USER_CODE:coordinate.coordinate_get_type.coordinate
<<coordinate.coordinate_get_type.coordinate>> = ( &<<coordinate.coordinate_wgs84_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_set_param

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_set_param
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_set_param.param:16#12345678#
TEST.ATTRIBUTES:coordinate.coordinate_get_param.return:EXPECTED_BASE=16
TEST.VALUE_USER_CODE:coordinate.coordinate_set_param.coordinate
coordinate = coordinate_default_create();
<<coordinate.coordinate_set_param.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_set_type

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_set_type
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_set_type.coordinate:<<malloc 1>>
TEST.VALUE:coordinate.coordinate_set_type.type:COORDINATE_TYPE_UTM6
TEST.EXPECTED:coordinate.coordinate_set_type.coordinate[0]:805306368
TEST.END

-- Subprogram: coordinate_utm3_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm3_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm3_create.zone_id:0
TEST.VALUE:coordinate.coordinate_utm3_create.south_flag:false
TEST.VALUE:coordinate.coordinate_utm3_create.offset_x:0
TEST.VALUE:coordinate.coordinate_utm3_create.offset_y:0
TEST.EXPECTED_USER_CODE:coordinate.coordinate_utm3_create.return
coordinate = coordinate_utm3_create(0, false, 0, 0);
{{ <<coordinate.coordinate_utm3_create.return>> == ( coordinate ) }}
TEST.END_EXPECTED_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm6_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm6_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm6_create.zone_id:0
TEST.VALUE:coordinate.coordinate_utm6_create.south_flag:false
TEST.VALUE:coordinate.coordinate_utm6_create.offset_x:0
TEST.VALUE:coordinate.coordinate_utm6_create.offset_y:0
TEST.EXPECTED_USER_CODE:coordinate.coordinate_utm6_create.return
coordinate = coordinate_utm6_create(0, false, 0, 0);
{{ <<coordinate.coordinate_utm6_create.return>> == ( coordinate ) }}
TEST.END_EXPECTED_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm_create.zone_id:0
TEST.VALUE:coordinate.coordinate_utm_create.south_flag:false
TEST.VALUE:coordinate.coordinate_utm_create.offset_x:0
TEST.VALUE:coordinate.coordinate_utm_create.offset_y:0
TEST.EXPECTED_USER_CODE:coordinate.coordinate_utm_create.return
coordinate = coordinate_utm_create(0, false, 0, 0);
{{ <<coordinate.coordinate_utm_create.return>> == ( coordinate ) }}
TEST.END_EXPECTED_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_get_offset_x

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_get_offset_x
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_utm_get_offset_x.return:50
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_get_offset_x.coordinate
<<coordinate.coordinate_utm_get_offset_x.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_get_offset_y

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_get_offset_y
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_utm_get_offset_y.return:50
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_get_offset_y.coordinate
<<coordinate.coordinate_utm_get_offset_y.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_get_south_flag

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_get_south_flag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_utm_get_south_flag.return:true
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_get_south_flag.coordinate
<<coordinate.coordinate_utm_get_south_flag.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: coordinate_utm_get_south_flag.001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_get_south_flag
TEST.NEW
TEST.NAME:coordinate_utm_get_south_flag.001
TEST.COMPOUND_ONLY
TEST.EXPECTED:coordinate.coordinate_utm_get_south_flag.return:false
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_get_south_flag.coordinate
<<coordinate.coordinate_utm_get_south_flag.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_get_zone

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_get_zone
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_utm_get_zone.return:50
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_get_zone.coordinate
<<coordinate.coordinate_utm_get_zone.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_get_zone_id

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_get_zone_id
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:coordinate.coordinate_utm_get_zone_id.return:120
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_get_zone_id.coordinate
<<coordinate.coordinate_utm_get_zone_id.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_reset_south_flag

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_reset_south_flag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_reset_south_flag.coordinate
<<coordinate.coordinate_utm_reset_south_flag.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_set_offset_x

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_set_offset_x
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm_set_offset_x.x:50
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_set_offset_x.coordinate
coordinate = coordinate_utm6_create(0, false, 0, 0);
<<coordinate.coordinate_utm_set_offset_x.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: coordinate_utm_set_offset_x.001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_set_offset_x
TEST.NEW
TEST.NAME:coordinate_utm_set_offset_x.001
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_set_offset_x.coordinate
<<coordinate.coordinate_utm_set_offset_x.coordinate>> = ( &<<coordinate.coordinate_utm_create.return>> );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_set_offset_y

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_set_offset_y
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm_set_offset_y.y:50
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_set_offset_y.coordinate
coordinate = coordinate_utm6_create(0, false, 0, 0);
<<coordinate.coordinate_utm_set_offset_y.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_set_south_flag

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_set_south_flag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_set_south_flag.coordinate
coordinate = coordinate_utm6_create(0, false, 0, 0);
<<coordinate.coordinate_utm_set_south_flag.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_set_zone

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_set_zone
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm_set_zone.zone:50
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_set_zone.coordinate
coordinate = coordinate_utm6_create(0, false, 0, 0);
<<coordinate.coordinate_utm_set_zone.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_utm_set_zone_id

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_utm_set_zone_id
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_utm_set_zone_id.zone:120
TEST.VALUE_USER_CODE:coordinate.coordinate_utm_set_zone_id.coordinate
coordinate = coordinate_utm6_create(0, false, 0, 0);
<<coordinate.coordinate_utm_set_zone_id.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_vehicle_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_vehicle_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:coordinate.coordinate_vehicle_create.sensor_id:0
TEST.EXPECTED_USER_CODE:coordinate.coordinate_vehicle_create.return
coordinate = coordinate_vehicle_create(0U);
{{ <<coordinate.coordinate_vehicle_create.return>> == ( coordinate ) }}
TEST.END_EXPECTED_USER_CODE:
TEST.END

-- Subprogram: coordinate_vehicle_get_sensor_id

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_vehicle_get_sensor_id
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE_USER_CODE:coordinate.coordinate_vehicle_get_sensor_id.coordinate
<<coordinate.coordinate_vehicle_get_sensor_id.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.EXPECTED_USER_CODE:coordinate.coordinate_vehicle_get_sensor_id.return
SensorId_t sensor_id = sensor_id_create(SENSOR_CLASS_IMU, SENSOR_MODEL_IMU_NOVATEL, 
                                            vehicle_location_create(VEHICLE_LOCATION_PLANE_TRUNK, 
                                                                    VEHICLE_LOCATION_COORDINATE_CENTER, 
                                                                    VEHICLE_LOCATION_COORDINATE_CENTER));

{{ <<coordinate.coordinate_vehicle_get_sensor_id.return>> == ( sensor_id ) }}
TEST.END_EXPECTED_USER_CODE:
TEST.END

-- Subprogram: coordinate_vehicle_set_sensor_id

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_vehicle_set_sensor_id
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.COMPOUND_ONLY
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE_USER_CODE:coordinate.coordinate_vehicle_set_sensor_id.coordinate
<<coordinate.coordinate_vehicle_set_sensor_id.coordinate>> = ( &coordinate );
TEST.END_VALUE_USER_CODE:
TEST.VALUE_USER_CODE:coordinate.coordinate_vehicle_set_sensor_id.sensor_id
SensorId_t sensor_id = sensor_id_create(SENSOR_CLASS_IMU, SENSOR_MODEL_IMU_NOVATEL, 
                                            vehicle_location_create(VEHICLE_LOCATION_PLANE_TRUNK, 
                                                                    VEHICLE_LOCATION_COORDINATE_CENTER, 
                                                                    VEHICLE_LOCATION_COORDINATE_CENTER));

<<coordinate.coordinate_vehicle_set_sensor_id.sensor_id>> = ( sensor_id );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: coordinate_wgs84_create

-- Test Case: BASIS-PATH-001
TEST.UNIT:coordinate
TEST.SUBPROGRAM:coordinate_wgs84_create
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED_USER_CODE:coordinate.coordinate_wgs84_create.return
coordinate = coordinate_wgs84_create();
{{ <<coordinate.coordinate_wgs84_create.return>> == ( coordinate ) }}
TEST.END_EXPECTED_USER_CODE:
TEST.END

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_dr_set_get_version
TEST.SLOT: "1", "coordinate", "coordinate_dr_set_version", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_dr_get_version", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_set_get_param
TEST.SLOT: "1", "coordinate", "coordinate_set_param", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_get_param", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm3_create
TEST.SLOT: "1", "coordinate", "coordinate_utm3_create", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_get_type", "1", "get_type_test_for_utm3_create"
TEST.SLOT: "3", "coordinate", "coordinate_get_param", "1", "get_param_test_for_utm3_create"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm6_create
TEST.SLOT: "1", "coordinate", "coordinate_utm6_create", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_get_type", "1", "get_type_test_for_utm6_create"
TEST.SLOT: "3", "coordinate", "coordinate_get_param", "1", "get_param_test_for_utm6_create"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm_create
TEST.SLOT: "1", "coordinate", "coordinate_utm_create", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_get_type", "1", "get_type_test_for_utm_create"
TEST.SLOT: "3", "coordinate", "coordinate_get_param", "1", "get_param_test_for_utm_create"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm_set_get_offset_x
TEST.SLOT: "1", "coordinate", "coordinate_utm_set_offset_x", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_utm_get_offset_x", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm_set_get_offset_y
TEST.SLOT: "1", "coordinate", "coordinate_utm_set_offset_y", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_utm_get_offset_y", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm_set_get_zone
TEST.SLOT: "1", "coordinate", "coordinate_utm_set_zone", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_utm_get_zone", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm_set_get_zone_id
TEST.SLOT: "1", "coordinate", "coordinate_utm_set_zone_id", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_utm_get_zone_id", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_utm_set_reset_get_south_flag
TEST.SLOT: "1", "coordinate", "coordinate_utm_set_south_flag", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_utm_get_south_flag", "1", "BASIS-PATH-001"
TEST.SLOT: "3", "coordinate", "coordinate_utm_reset_south_flag", "1", "BASIS-PATH-001"
TEST.SLOT: "4", "coordinate", "coordinate_utm_get_south_flag", "1", "coordinate_utm_get_south_flag.001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_vehicle_create
TEST.SLOT: "1", "coordinate", "coordinate_vehicle_create", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_get_type", "1", "get_type_test_for_vehicle_create"
TEST.SLOT: "3", "coordinate", "coordinate_get_param", "1", "get_param_test_for_vehicle_create"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_vehicle_set_get_sensor_id
TEST.SLOT: "1", "coordinate", "coordinate_vehicle_set_sensor_id", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_vehicle_get_sensor_id", "1", "BASIS-PATH-001"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_wgs84_create
TEST.SLOT: "1", "coordinate", "coordinate_wgs84_create", "1", "BASIS-PATH-001"
TEST.SLOT: "2", "coordinate", "coordinate_get_type", "1", "get_type_test_for_wgs84_create"
TEST.SLOT: "3", "coordinate", "coordinate_get_param", "1", "get_param_test_for_wgs84_create"
TEST.END
--
