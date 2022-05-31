-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : CHASSIS_STATE
-- Unit(s) Under Test: chassis_state
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

-- Unit: chassis_state

-- Subprogram: chassis_state_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (state != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:1024
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].stamp.sec:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].stamp.nsec:2
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].vehicle_speed:1.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].front_left_wheel_speed:2.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].front_right_wheel_speed:3.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].rear_left_wheel_speed:4.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].rear_right_wheel_speed:5.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].longitudinal_acceleration:6.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].lateral_acceleration:7.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].yaw_rate:8.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].front_wheel_angle:9.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].longitudinal_control_value:10.0
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.rear_fog_light:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.front_fog_light:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.brake_light:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.high_beam:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.low_beam:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.hazard_flasher:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.right_turn_signal:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].light_system_state.left_turn_signal:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.rear_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.front_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.rear_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.front_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.rear_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.rear_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.front_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.front_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.trunk_door:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.rear_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.rear_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.front_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.front_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].cockpit_system_state.driver_seatbelt:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].energy_source_level:5
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].gear_system_state.handbrake:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].gear_system_state.gear_level:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].gear_system_state.gear_position:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].user_operation_state.lateral_takeover:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].user_operation_state.longitudinal_takeover:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].user_operation_state.lateral_activate:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].user_operation_state.longitudinal_activate:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].chassis_actuator_state.gear_actuator_active:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].chassis_actuator_state.lateral_actuator_active:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].chassis_actuator_state.longitudinal_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.state[0].chassis_actuator_state.longitudinal_actuator_active:1
TEST.EXPECTED:chassis_state.chassis_state_deserialize.return:56
TEST.VALUE_USER_CODE:chassis_state.chassis_state_deserialize.buffer
<<chassis_state.chassis_state_deserialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (state != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_deserialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: chassis_state_get_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state[0].chassis_actuator_state.gear_actuator_active:1
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state[0].chassis_actuator_state.lateral_actuator_active:1
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state[0].chassis_actuator_state.longitudinal_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_get_actuator_state.state[0].chassis_actuator_state.longitudinal_actuator_active:1
TEST.EXPECTED:chassis_state.chassis_state_get_actuator_state.return:63
TEST.END

-- Subprogram: chassis_state_get_cockpit_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_cockpit_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.rear_window_defroster:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.front_window_defroster:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.rear_wiper:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.front_wiper:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.rear_right_window:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.rear_left_window:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.front_right_window:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.front_left_window:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.trunk_door:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.rear_right_door:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.rear_left_door:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.front_right_door:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.front_left_door:1
TEST.VALUE:chassis_state.chassis_state_get_cockpit_state.state[0].cockpit_system_state.driver_seatbelt:1
TEST.EXPECTED:chassis_state.chassis_state_get_cockpit_state.return:16383
TEST.END

-- Subprogram: chassis_state_get_energy_source_level

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_energy_source_level
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_energy_source_level.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_energy_source_level.state[0].energy_source_level:5
TEST.EXPECTED:chassis_state.chassis_state_get_energy_source_level.return:5
TEST.END

-- Subprogram: chassis_state_get_front_left_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_front_left_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_front_left_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_front_left_wheel_speed.state[0].front_left_wheel_speed:1.0
TEST.EXPECTED:chassis_state.chassis_state_get_front_left_wheel_speed.return:1.0
TEST.END

-- Subprogram: chassis_state_get_front_right_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_front_right_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_front_right_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_front_right_wheel_speed.state[0].front_right_wheel_speed:1.0
TEST.EXPECTED:chassis_state.chassis_state_get_front_right_wheel_speed.return:1.0
TEST.END

-- Subprogram: chassis_state_get_front_wheel_angle

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_front_wheel_angle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_front_wheel_angle.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_front_wheel_angle.state[0].front_wheel_angle:5.0
TEST.EXPECTED:chassis_state.chassis_state_get_front_wheel_angle.return:5.0
TEST.END

-- Subprogram: chassis_state_get_gear_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_gear_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_gear_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_gear_actuator_state.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_get_gear_actuator_state.state[0].chassis_actuator_state.gear_actuator_active:0
TEST.EXPECTED:chassis_state.chassis_state_get_gear_actuator_state.return:ACTUATOR_STATE_READY
TEST.END

-- Subprogram: chassis_state_get_gear_level

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_gear_level
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_gear_level.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_gear_level.state[0].gear_system_state.gear_level:5
TEST.EXPECTED:chassis_state.chassis_state_get_gear_level.return:5
TEST.END

-- Subprogram: chassis_state_get_gear_position

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_gear_position
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_gear_position.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_gear_position.state[0].gear_system_state.gear_position:5
TEST.EXPECTED:chassis_state.chassis_state_get_gear_position.return:GEAR_POSITION_S
TEST.END

-- Subprogram: chassis_state_get_gear_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_gear_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_gear_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_gear_state.state[0].gear_system_state.handbrake:1
TEST.VALUE:chassis_state.chassis_state_get_gear_state.state[0].gear_system_state.gear_level:1
TEST.VALUE:chassis_state.chassis_state_get_gear_state.state[0].gear_system_state.gear_position:1
TEST.EXPECTED:chassis_state.chassis_state_get_gear_state.return:35
TEST.END

-- Subprogram: chassis_state_get_lateral_acceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_lateral_acceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_lateral_acceleration.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_lateral_acceleration.state[0].lateral_acceleration:5.0
TEST.EXPECTED:chassis_state.chassis_state_get_lateral_acceleration.return:5.0
TEST.END

-- Subprogram: chassis_state_get_lateral_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_lateral_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_lateral_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_lateral_actuator_state.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_get_lateral_actuator_state.state[0].chassis_actuator_state.lateral_actuator_active:0
TEST.EXPECTED:chassis_state.chassis_state_get_lateral_actuator_state.return:ACTUATOR_STATE_READY
TEST.END

-- Subprogram: chassis_state_get_light_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_light_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_light_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.rear_fog_light:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.front_fog_light:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.brake_light:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.high_beam:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.low_beam:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.hazard_flasher:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.right_turn_signal:1
TEST.VALUE:chassis_state.chassis_state_get_light_state.state[0].light_system_state.left_turn_signal:1
TEST.EXPECTED:chassis_state.chassis_state_get_light_state.return:255
TEST.END

-- Subprogram: chassis_state_get_longitudinal_acceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_longitudinal_acceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_acceleration.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_acceleration.state[0].longitudinal_acceleration:1.0
TEST.EXPECTED:chassis_state.chassis_state_get_longitudinal_acceleration.return:1.0
TEST.END

-- Subprogram: chassis_state_get_longitudinal_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_longitudinal_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_actuator_state.state[0].chassis_actuator_state.longitudinal_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_actuator_state.state[0].chassis_actuator_state.longitudinal_actuator_active:0
TEST.EXPECTED:chassis_state.chassis_state_get_longitudinal_actuator_state.return:ACTUATOR_STATE_READY
TEST.END

-- Subprogram: chassis_state_get_longitudinal_control_value

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_longitudinal_control_value
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_control_value.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_longitudinal_control_value.state[0].longitudinal_control_value:5.0
TEST.EXPECTED:chassis_state.chassis_state_get_longitudinal_control_value.return:5.0
TEST.END

-- Subprogram: chassis_state_get_rear_left_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_rear_left_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_rear_left_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_rear_left_wheel_speed.state[0].rear_left_wheel_speed:1.0
TEST.EXPECTED:chassis_state.chassis_state_get_rear_left_wheel_speed.return:1.0
TEST.END

-- Subprogram: chassis_state_get_rear_right_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_rear_right_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_rear_right_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_rear_right_wheel_speed.state[0].rear_right_wheel_speed:1.0
TEST.EXPECTED:chassis_state.chassis_state_get_rear_right_wheel_speed.return:1.0
TEST.END

-- Subprogram: chassis_state_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_serialized_size.state:<<malloc 1>>
TEST.EXPECTED:chassis_state.chassis_state_get_serialized_size.return:56
TEST.END

-- Subprogram: chassis_state_get_timestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_timestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_timestamp.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_timestamp.state[0].stamp.sec:1
TEST.VALUE:chassis_state.chassis_state_get_timestamp.state[0].stamp.nsec:2
TEST.EXPECTED:chassis_state.chassis_state_get_timestamp.return[0].sec:1
TEST.EXPECTED:chassis_state.chassis_state_get_timestamp.return[0].nsec:2
TEST.END

-- Subprogram: chassis_state_get_user_operation_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_user_operation_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_user_operation_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_user_operation_state.state[0].user_operation_state.lateral_takeover:1
TEST.VALUE:chassis_state.chassis_state_get_user_operation_state.state[0].user_operation_state.longitudinal_takeover:1
TEST.VALUE:chassis_state.chassis_state_get_user_operation_state.state[0].user_operation_state.lateral_activate:1
TEST.VALUE:chassis_state.chassis_state_get_user_operation_state.state[0].user_operation_state.longitudinal_activate:1
TEST.EXPECTED:chassis_state.chassis_state_get_user_operation_state.return:15
TEST.END

-- Subprogram: chassis_state_get_vehicle_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_vehicle_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_vehicle_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_vehicle_speed.state[0].vehicle_speed:1.0
TEST.EXPECTED:chassis_state.chassis_state_get_vehicle_speed.return:1.0
TEST.END

-- Subprogram: chassis_state_get_yaw_rate

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_get_yaw_rate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_get_yaw_rate.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_get_yaw_rate.state[0].yaw_rate:5.0
TEST.EXPECTED:chassis_state.chassis_state_get_yaw_rate.return:5.0
TEST.END

-- Subprogram: chassis_state_init_default

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_init_default
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_init_default.state:<<malloc 1>>
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].stamp.sec:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].stamp.nsec:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].vehicle_speed:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].front_left_wheel_speed:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].front_right_wheel_speed:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].rear_left_wheel_speed:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].rear_right_wheel_speed:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].longitudinal_acceleration:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].lateral_acceleration:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].yaw_rate:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].front_wheel_angle:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].longitudinal_control_value:0.0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.rear_fog_light:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.front_fog_light:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.brake_light:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.high_beam:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.low_beam:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.hazard_flasher:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.right_turn_signal:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.left_turn_signal:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].light_system_state.reserved:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.rear_window_defroster:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.front_window_defroster:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.rear_wiper:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.front_wiper:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.rear_right_window:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.rear_left_window:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.front_right_window:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.front_left_window:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.trunk_door:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.rear_right_door:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.rear_left_door:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.front_right_door:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.front_left_door:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.driver_seatbelt:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].cockpit_system_state.reserved:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].energy_source_level:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].gear_system_state.handbrake:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].gear_system_state.gear_level:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].gear_system_state.gear_position:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].user_operation_state.lateral_takeover:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].user_operation_state.longitudinal_takeover:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].user_operation_state.lateral_activate:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].user_operation_state.longitudinal_activate:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].user_operation_state.reserved:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.gear_actuator_ready:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.gear_actuator_active:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.lateral_actuator_ready:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.lateral_actuator_active:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.longitudinal_actuator_ready:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.longitudinal_actuator_active:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.state[0].chassis_actuator_state.reserved:0
TEST.EXPECTED:chassis_state.chassis_state_init_default.return:0
TEST.END

-- Subprogram: chassis_state_is_actuators_ready

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_TTT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TTT-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((chassis_state_is_longitudinal_actuator_ready(state) && chassis_state_is_lateral_actuator_ready(state)) && chassis_state_is_gear_actuator_ready(state)) ==> TRUE
      Row number 1 forms a pair with Row 5 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function chassis_state_is_longitudinal_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_lateral_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_gear_actuator_ready in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TTT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TTT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((chassis_state_is_longitudinal_actuator_ready(state) && chassis_state_is_lateral_actuator_ready(state)) && chassis_state_is_gear_actuator_ready(state)) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function chassis_state_is_longitudinal_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_lateral_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_gear_actuator_ready in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_c_TTT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_c_TTT-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) ((chassis_state_is_longitudinal_actuator_ready(state) && chassis_state_is_lateral_actuator_ready(state)) && chassis_state_is_gear_actuator_ready(state)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "c".
         Condition a ==> TRUE
         Condition b ==> TRUE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function chassis_state_is_longitudinal_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_lateral_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_gear_actuator_ready in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_c_TTF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_c_TTF-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) ((chassis_state_is_longitudinal_actuator_ready(state) && chassis_state_is_lateral_actuator_ready(state)) && chassis_state_is_gear_actuator_ready(state)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "c".
         Condition a ==> TRUE
         Condition b ==> TRUE
         Condition c ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function chassis_state_is_longitudinal_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_lateral_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_gear_actuator_ready in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_TFx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_TFx-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((chassis_state_is_longitudinal_actuator_ready(state) && chassis_state_is_lateral_actuator_ready(state)) && chassis_state_is_gear_actuator_ready(state)) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function chassis_state_is_longitudinal_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_lateral_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_gear_actuator_ready in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_5_PAIR_a_Fxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_actuators_ready
TEST.NEW
TEST.NAME:COND_1_ROW_5_PAIR_a_Fxx-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((chassis_state_is_longitudinal_actuator_ready(state) && chassis_state_is_lateral_actuator_ready(state)) && chassis_state_is_gear_actuator_ready(state)) ==> FALSE
      Row number 5 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function chassis_state_is_longitudinal_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_lateral_actuator_ready in branch 1
      Cannot set return value of function chassis_state_is_gear_actuator_ready in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_actuators_ready.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_brake_light_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_brake_light_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_brake_light_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_brake_light_on.state[0].light_system_state.brake_light:1
TEST.EXPECTED:chassis_state.chassis_state_is_brake_light_on.return:true
TEST.END

-- Subprogram: chassis_state_is_door_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_a_Txxxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_a_Txxxx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> TRUE
      Row number 16 forms a pair with Row 32 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_24_PAIR_b_FTxxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_24_PAIR_b_FTxxx-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> TRUE
      Row number 24 forms a pair with Row 32 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_28_PAIR_c_FFTxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_28_PAIR_c_FFTxx-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> TRUE
      Row number 28 forms a pair with Row 32 for Condition #1, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_30_PAIR_d_FFFTx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_30_PAIR_d_FFFTx-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> TRUE
      Row number 30 forms a pair with Row 32 for Condition #1, subcondition "d".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> TRUE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_31_PAIR_e_FFFFT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_31_PAIR_e_FFFFT-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> TRUE
      Row number 31 forms a pair with Row 32 for Condition #1, subcondition "e".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_32_PAIR_a_FFFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_32_PAIR_a_FFFFF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> FALSE
      Row number 32 forms a pair with Row 16 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_32_PAIR_b_FFFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_32_PAIR_b_FFFFF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> FALSE
      Row number 32 forms a pair with Row 24 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_32_PAIR_c_FFFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_32_PAIR_c_FFFFF-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> FALSE
      Row number 32 forms a pair with Row 28 for Condition #1, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_32_PAIR_d_FFFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_32_PAIR_d_FFFFF-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> FALSE
      Row number 32 forms a pair with Row 30 for Condition #1, subcondition "d".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_32_PAIR_e_FFFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_door_open
TEST.NEW
TEST.NAME:COND_1_ROW_32_PAIR_e_FFFFF-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) (((((state->cockpit_system_state).front_left_door || (state->cockpit_system_state).front_right_door) || (state->cockpit_system_state).rear_left_door) || (state->cockpit_system_state).rear_right_door) || (state->cockpit_system_state).trunk_door) ==> FALSE
      Row number 32 forms a pair with Row 31 for Condition #1, subcondition "e".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
         Condition e ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_door in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).trunk_door in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_door_open.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_driver_seatbelt_locked

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_driver_seatbelt_locked
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_driver_seatbelt_locked.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_driver_seatbelt_locked.state[0].cockpit_system_state.driver_seatbelt:1
TEST.EXPECTED:chassis_state.chassis_state_is_driver_seatbelt_locked.return:true
TEST.END

-- Subprogram: chassis_state_is_driver_takeover

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_driver_takeover
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_driver_takeover.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_driver_takeover
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state->user_operation_state).longitudinal_takeover || (state->user_operation_state).lateral_takeover) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_takeover in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_takeover in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_driver_takeover.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_driver_takeover
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((state->user_operation_state).longitudinal_takeover || (state->user_operation_state).lateral_takeover) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_takeover in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_takeover in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_driver_takeover.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_driver_takeover
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state->user_operation_state).longitudinal_takeover || (state->user_operation_state).lateral_takeover) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_takeover in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_takeover in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_driver_takeover.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_driver_takeover
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((state->user_operation_state).longitudinal_takeover || (state->user_operation_state).lateral_takeover) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_takeover in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_takeover in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_driver_takeover.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_fog_light_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_fog_light_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_fog_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_fog_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state->light_system_state).front_fog_light || (state->light_system_state).rear_fog_light) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).front_fog_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).rear_fog_light in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_fog_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_fog_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((state->light_system_state).front_fog_light || (state->light_system_state).rear_fog_light) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).front_fog_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).rear_fog_light in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_fog_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_fog_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state->light_system_state).front_fog_light || (state->light_system_state).rear_fog_light) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).front_fog_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).rear_fog_light in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_fog_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_fog_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((state->light_system_state).front_fog_light || (state->light_system_state).rear_fog_light) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).front_fog_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).rear_fog_light in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_fog_light_on.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_front_fog_light_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_fog_light_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_fog_light_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_fog_light_on.state[0].light_system_state.front_fog_light:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_fog_light_on.return:true
TEST.END

-- Subprogram: chassis_state_is_front_left_door_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_left_door_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_left_door_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_left_door_open.state[0].cockpit_system_state.front_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_left_door_open.return:true
TEST.END

-- Subprogram: chassis_state_is_front_left_window_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_left_window_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_left_window_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_left_window_open.state[0].cockpit_system_state.front_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_left_window_open.return:true
TEST.END

-- Subprogram: chassis_state_is_front_right_door_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_right_door_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_right_door_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_right_door_open.state[0].cockpit_system_state.front_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_right_door_open.return:true
TEST.END

-- Subprogram: chassis_state_is_front_right_window_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_right_window_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_right_window_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_right_window_open.state[0].cockpit_system_state.front_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_right_window_open.return:true
TEST.END

-- Subprogram: chassis_state_is_front_window_defroster_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_window_defroster_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_window_defroster_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_window_defroster_on.state[0].cockpit_system_state.front_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_window_defroster_on.return:true
TEST.END

-- Subprogram: chassis_state_is_front_wiper_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_front_wiper_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_front_wiper_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_front_wiper_on.state[0].cockpit_system_state.front_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_is_front_wiper_on.return:true
TEST.END

-- Subprogram: chassis_state_is_gear_actuator_ready

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_gear_actuator_ready
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_gear_actuator_ready.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_gear_actuator_ready.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_is_gear_actuator_ready.return:true
TEST.END

-- Subprogram: chassis_state_is_handbrake_hold

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_handbrake_hold
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_handbrake_hold.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_handbrake_hold.state[0].gear_system_state.handbrake:1
TEST.EXPECTED:chassis_state.chassis_state_is_handbrake_hold.return:true
TEST.END

-- Subprogram: chassis_state_is_hazard_flasher_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_hazard_flasher_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_hazard_flasher_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_hazard_flasher_on.state[0].light_system_state.hazard_flasher:1
TEST.EXPECTED:chassis_state.chassis_state_is_hazard_flasher_on.return:true
TEST.END

-- Subprogram: chassis_state_is_head_light_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_head_light_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_head_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_head_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state->light_system_state).high_beam || (state->light_system_state).low_beam) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).high_beam in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).low_beam in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_head_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_head_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((state->light_system_state).high_beam || (state->light_system_state).low_beam) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).high_beam in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).low_beam in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_head_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_head_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state->light_system_state).high_beam || (state->light_system_state).low_beam) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).high_beam in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).low_beam in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_head_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_head_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((state->light_system_state).high_beam || (state->light_system_state).low_beam) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).high_beam in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).low_beam in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_head_light_on.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_high_beam_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_high_beam_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_high_beam_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_high_beam_on.state[0].light_system_state.high_beam:1
TEST.EXPECTED:chassis_state.chassis_state_is_high_beam_on.return:true
TEST.END

-- Subprogram: chassis_state_is_lateral_activated

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_lateral_activated
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_lateral_activated.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_lateral_activated.state[0].user_operation_state.lateral_activate:1
TEST.EXPECTED:chassis_state.chassis_state_is_lateral_activated.return:true
TEST.END

-- Subprogram: chassis_state_is_lateral_actuator_ready

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_lateral_actuator_ready
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_lateral_actuator_ready.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_lateral_actuator_ready.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_is_lateral_actuator_ready.return:true
TEST.END

-- Subprogram: chassis_state_is_lateral_takeover

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_lateral_takeover
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_lateral_takeover.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_lateral_takeover.state[0].user_operation_state.lateral_takeover:1
TEST.EXPECTED:chassis_state.chassis_state_is_lateral_takeover.return:true
TEST.END

-- Subprogram: chassis_state_is_left_turn_signal_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_left_turn_signal_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_left_turn_signal_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_left_turn_signal_on.state[0].light_system_state.left_turn_signal:1
TEST.EXPECTED:chassis_state.chassis_state_is_left_turn_signal_on.return:true
TEST.END

-- Subprogram: chassis_state_is_longitudinal_activated

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_longitudinal_activated
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_longitudinal_activated.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_longitudinal_activated.state[0].user_operation_state.longitudinal_activate:1
TEST.EXPECTED:chassis_state.chassis_state_is_longitudinal_activated.return:true
TEST.END

-- Subprogram: chassis_state_is_longitudinal_actuator_ready

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_longitudinal_actuator_ready
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_longitudinal_actuator_ready.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_longitudinal_actuator_ready.state[0].chassis_actuator_state.longitudinal_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_is_longitudinal_actuator_ready.return:true
TEST.END

-- Subprogram: chassis_state_is_longitudinal_takeover

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_longitudinal_takeover
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_longitudinal_takeover.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_longitudinal_takeover.state[0].user_operation_state.longitudinal_takeover:1
TEST.EXPECTED:chassis_state.chassis_state_is_longitudinal_takeover.return:true
TEST.END

-- Subprogram: chassis_state_is_low_beam_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_low_beam_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_low_beam_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_low_beam_on.state[0].light_system_state.low_beam:1
TEST.EXPECTED:chassis_state.chassis_state_is_low_beam_on.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_fog_light_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_fog_light_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_fog_light_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_fog_light_on.state[0].light_system_state.rear_fog_light:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_fog_light_on.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_left_door_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_left_door_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_left_door_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_left_door_open.state[0].cockpit_system_state.rear_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_left_door_open.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_left_window_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_left_window_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_left_window_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_left_window_open.state[0].cockpit_system_state.rear_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_left_window_open.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_right_door_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_right_door_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_right_door_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_right_door_open.state[0].cockpit_system_state.rear_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_right_door_open.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_right_window_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_right_window_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_right_window_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_right_window_open.state[0].cockpit_system_state.rear_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_right_window_open.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_window_defroster_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_window_defroster_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_window_defroster_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_window_defroster_on.state[0].cockpit_system_state.rear_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_window_defroster_on.return:true
TEST.END

-- Subprogram: chassis_state_is_rear_wiper_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_rear_wiper_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_rear_wiper_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_rear_wiper_on.state[0].cockpit_system_state.rear_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_is_rear_wiper_on.return:true
TEST.END

-- Subprogram: chassis_state_is_right_turn_signal_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_right_turn_signal_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_right_turn_signal_on.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_right_turn_signal_on.state[0].light_system_state.right_turn_signal:1
TEST.EXPECTED:chassis_state.chassis_state_is_right_turn_signal_on.return:true
TEST.END

-- Subprogram: chassis_state_is_signal_light_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_12_PAIR_b_FTxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_12_PAIR_b_FTxx-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> TRUE
      Row number 12 forms a pair with Row 16 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_14_PAIR_c_FFTx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_14_PAIR_c_FFTx-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> TRUE
      Row number 14 forms a pair with Row 16 for Condition #1, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_15_PAIR_d_FFFT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_15_PAIR_d_FFFT-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> TRUE
      Row number 15 forms a pair with Row 16 for Condition #1, subcondition "d".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_a_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_a_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> FALSE
      Row number 16 forms a pair with Row 8 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_b_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_b_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> FALSE
      Row number 16 forms a pair with Row 12 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_c_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_c_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> FALSE
      Row number 16 forms a pair with Row 14 for Condition #1, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_d_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_d_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> FALSE
      Row number 16 forms a pair with Row 15 for Condition #1, subcondition "d".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_8_PAIR_a_Txxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_signal_light_on
TEST.NEW
TEST.NAME:COND_1_ROW_8_PAIR_a_Txxx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((((state->light_system_state).brake_light || (state->light_system_state).hazard_flasher) || (state->light_system_state).right_turn_signal) || (state->light_system_state).left_turn_signal) ==> TRUE
      Row number 8 forms a pair with Row 16 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->light_system_state).brake_light in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).hazard_flasher in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).right_turn_signal in branch 1
            Cannot set value of field for a const class/struct/union for (state->light_system_state).left_turn_signal in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_signal_light_on.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_system_activated

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_system_activated
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_system_activated.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_system_activated
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state->user_operation_state).longitudinal_activate || (state->user_operation_state).lateral_activate) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_activate in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_activate in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_system_activated.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_system_activated
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((state->user_operation_state).longitudinal_activate || (state->user_operation_state).lateral_activate) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_activate in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_activate in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_system_activated.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_system_activated
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state->user_operation_state).longitudinal_activate || (state->user_operation_state).lateral_activate) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_activate in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_activate in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_system_activated.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_system_activated
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((state->user_operation_state).longitudinal_activate || (state->user_operation_state).lateral_activate) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).longitudinal_activate in branch 1
            Cannot set value of field for a const class/struct/union for (state->user_operation_state).lateral_activate in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_system_activated.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_trunk_door_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_trunk_door_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_trunk_door_open.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_is_trunk_door_open.state[0].cockpit_system_state.trunk_door:1
TEST.EXPECTED:chassis_state.chassis_state_is_trunk_door_open.return:true
TEST.END

-- Subprogram: chassis_state_is_window_defroster_on

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_defroster_on
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_defroster_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_defroster_on
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state->cockpit_system_state).front_window_defroster || (state->cockpit_system_state).rear_window_defroster) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_window_defroster in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_window_defroster in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_defroster_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_defroster_on
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((state->cockpit_system_state).front_window_defroster || (state->cockpit_system_state).rear_window_defroster) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_window_defroster in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_window_defroster in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_defroster_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_defroster_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state->cockpit_system_state).front_window_defroster || (state->cockpit_system_state).rear_window_defroster) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_window_defroster in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_window_defroster in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_defroster_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_defroster_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((state->cockpit_system_state).front_window_defroster || (state->cockpit_system_state).rear_window_defroster) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_window_defroster in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_window_defroster in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_defroster_on.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_window_open

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_12_PAIR_b_FTxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_12_PAIR_b_FTxx-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> TRUE
      Row number 12 forms a pair with Row 16 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_14_PAIR_c_FFTx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_14_PAIR_c_FFTx-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> TRUE
      Row number 14 forms a pair with Row 16 for Condition #1, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> TRUE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_15_PAIR_d_FFFT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_15_PAIR_d_FFFT-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> TRUE
      Row number 15 forms a pair with Row 16 for Condition #1, subcondition "d".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_a_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_a_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> FALSE
      Row number 16 forms a pair with Row 8 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_b_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_b_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> FALSE
      Row number 16 forms a pair with Row 12 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_c_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_c_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> FALSE
      Row number 16 forms a pair with Row 14 for Condition #1, subcondition "c".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_16_PAIR_d_FFFF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_16_PAIR_d_FFFF-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> FALSE
      Row number 16 forms a pair with Row 15 for Condition #1, subcondition "d".
         Condition a ==> FALSE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_8_PAIR_a_Txxx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_window_open
TEST.NEW
TEST.NAME:COND_1_ROW_8_PAIR_a_Txxx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((((state->cockpit_system_state).front_left_window || (state->cockpit_system_state).front_right_window) || (state->cockpit_system_state).rear_left_window) || (state->cockpit_system_state).rear_right_window) ==> TRUE
      Row number 8 forms a pair with Row 16 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
         Condition c ==> FALSE
         Condition d ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_right_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_left_window in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_right_window in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_window_open.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_is_wiper_on

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_wiper_on
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state->cockpit_system_state).front_wiper || (state->cockpit_system_state).rear_wiper) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_wiper in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_wiper in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_wiper_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_wiper_on
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) ((state->cockpit_system_state).front_wiper || (state->cockpit_system_state).rear_wiper) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_wiper in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_wiper in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_wiper_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_wiper_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state->cockpit_system_state).front_wiper || (state->cockpit_system_state).rear_wiper) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_wiper in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_wiper in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_wiper_on.state:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_is_wiper_on
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) ((state->cockpit_system_state).front_wiper || (state->cockpit_system_state).rear_wiper) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).front_wiper in branch 1
            Cannot set value of field for a const class/struct/union for (state->cockpit_system_state).rear_wiper in branch 1
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_is_wiper_on.state:<<malloc 1>>
TEST.END

-- Subprogram: chassis_state_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (state != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].stamp.sec:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].stamp.nsec:2
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].vehicle_speed:1.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].front_left_wheel_speed:2.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].front_right_wheel_speed:3.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].rear_left_wheel_speed:4.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].rear_right_wheel_speed:5.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].longitudinal_acceleration:6.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].lateral_acceleration:7.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].yaw_rate:8.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].front_wheel_angle:9.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].longitudinal_control_value:10.0
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.rear_fog_light:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.front_fog_light:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.brake_light:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.high_beam:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.low_beam:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.hazard_flasher:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.right_turn_signal:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].light_system_state.left_turn_signal:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.rear_window_defroster:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.front_window_defroster:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.rear_wiper:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.front_wiper:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.rear_right_window:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.rear_left_window:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.front_right_window:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.front_left_window:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.trunk_door:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.rear_right_door:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.rear_left_door:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.front_right_door:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.front_left_door:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].cockpit_system_state.driver_seatbelt:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].energy_source_level:5
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].gear_system_state.handbrake:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].gear_system_state.gear_level:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].gear_system_state.gear_position:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].user_operation_state.lateral_takeover:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].user_operation_state.longitudinal_takeover:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].user_operation_state.lateral_activate:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].user_operation_state.longitudinal_activate:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].chassis_actuator_state.gear_actuator_active:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].chassis_actuator_state.lateral_actuator_active:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].chassis_actuator_state.longitudinal_actuator_ready:1
TEST.VALUE:chassis_state.chassis_state_serialize.state[0].chassis_actuator_state.longitudinal_actuator_active:1
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:1024
TEST.VALUE:uut_prototype_stubs.timestamp_serialize.return:8
TEST.VALUE:uut_prototype_stubs.timestamp_deserialize.return:8
TEST.VALUE:uut_prototype_stubs.serialize_uint8.return:1
TEST.VALUE:uut_prototype_stubs.serialize_uint16.obj:<<null>>
TEST.VALUE:uut_prototype_stubs.serialize_uint16.return:2
TEST.VALUE:uut_prototype_stubs.serialize_float32.return:4
TEST.VALUE:uut_prototype_stubs.deserialize_uint8.return:1
TEST.VALUE:uut_prototype_stubs.deserialize_uint16.return:2
TEST.VALUE:uut_prototype_stubs.deserialize_float32.return:4
TEST.EXPECTED:chassis_state.chassis_state_serialize.return:56
TEST.VALUE_USER_CODE:chassis_state.chassis_state_serialize.buffer
<<chassis_state.chassis_state_serialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (state != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_serialize.return:12
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (state != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_serialize.state:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer:<<null>>
TEST.VALUE:chassis_state.chassis_state_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: chassis_state_set_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_actuator_state.value:<<MAX>>
TEST.EXPECTED:chassis_state.chassis_state_set_actuator_state.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_set_actuator_state.state[0].chassis_actuator_state.gear_actuator_active:1
TEST.EXPECTED:chassis_state.chassis_state_set_actuator_state.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_set_actuator_state.state[0].chassis_actuator_state.lateral_actuator_active:1
TEST.EXPECTED:chassis_state.chassis_state_set_actuator_state.state[0].chassis_actuator_state.longitudinal_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_set_actuator_state.state[0].chassis_actuator_state.longitudinal_actuator_active:1
TEST.END

-- Subprogram: chassis_state_set_brake_light

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_brake_light
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_brake_light.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_brake_light.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_brake_light.state[0].light_system_state.brake_light:1
TEST.END

-- Subprogram: chassis_state_set_cockpit_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_cockpit_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_cockpit_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_cockpit_state.value:16383
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.rear_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.front_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.rear_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.front_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.rear_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.rear_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.front_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.front_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.trunk_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.rear_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.rear_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.front_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.front_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_cockpit_state.state[0].cockpit_system_state.driver_seatbelt:1
TEST.END

-- Subprogram: chassis_state_set_door_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_door_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_door_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_door_state.fl:true
TEST.VALUE:chassis_state.chassis_state_set_door_state.fr:true
TEST.VALUE:chassis_state.chassis_state_set_door_state.rl:true
TEST.VALUE:chassis_state.chassis_state_set_door_state.rr:true
TEST.VALUE:chassis_state.chassis_state_set_door_state.trunk:true
TEST.EXPECTED:chassis_state.chassis_state_set_door_state.state[0].cockpit_system_state.trunk_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_door_state.state[0].cockpit_system_state.rear_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_door_state.state[0].cockpit_system_state.rear_left_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_door_state.state[0].cockpit_system_state.front_right_door:1
TEST.EXPECTED:chassis_state.chassis_state_set_door_state.state[0].cockpit_system_state.front_left_door:1
TEST.END

-- Subprogram: chassis_state_set_driver_seatbelt

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_driver_seatbelt
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_driver_seatbelt.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_driver_seatbelt.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_driver_seatbelt.state[0].cockpit_system_state.driver_seatbelt:1
TEST.END

-- Subprogram: chassis_state_set_energy_source_level

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_energy_source_level
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value > 100U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_energy_source_level.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_energy_source_level.value:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_energy_source_level
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value > 100U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_energy_source_level.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_energy_source_level.value:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_front_fog_light

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_fog_light
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_fog_light.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_fog_light.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_fog_light.state[0].light_system_state.front_fog_light:1
TEST.END

-- Subprogram: chassis_state_set_front_left_door

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_left_door
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_left_door.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_left_door.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_left_door.state[0].cockpit_system_state.front_left_door:1
TEST.END

-- Subprogram: chassis_state_set_front_left_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_left_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_left_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_left_wheel_speed.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_front_left_wheel_speed.state[0].front_left_wheel_speed:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_front_left_window

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_left_window
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_left_window.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_left_window.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_left_window.state[0].cockpit_system_state.front_left_window:1
TEST.END

-- Subprogram: chassis_state_set_front_right_door

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_right_door
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_right_door.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_right_door.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_right_door.state[0].cockpit_system_state.front_right_door:1
TEST.END

-- Subprogram: chassis_state_set_front_right_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_right_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_right_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_right_wheel_speed.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_front_right_wheel_speed.state[0].front_right_wheel_speed:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_front_right_window

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_right_window
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_right_window.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_right_window.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_right_window.state[0].cockpit_system_state.front_right_window:1
TEST.END

-- Subprogram: chassis_state_set_front_wheel_angle

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_wheel_angle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_wheel_angle.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_wheel_angle.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_front_wheel_angle.state[0].front_wheel_angle:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_front_window_defroster

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_window_defroster
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_window_defroster.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_window_defroster.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_window_defroster.state[0].cockpit_system_state.front_window_defroster:1
TEST.END

-- Subprogram: chassis_state_set_front_wiper

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_front_wiper
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_front_wiper.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_front_wiper.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_front_wiper.state[0].cockpit_system_state.front_wiper:1
TEST.END

-- Subprogram: chassis_state_set_gear_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_gear_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_gear_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_gear_actuator_state.value:ACTUATOR_STATE_ACTIVE
TEST.EXPECTED:chassis_state.chassis_state_set_gear_actuator_state.state[0].chassis_actuator_state.gear_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_set_gear_actuator_state.state[0].chassis_actuator_state.gear_actuator_active:1
TEST.END

-- Subprogram: chassis_state_set_gear_level

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_gear_level
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value > 15U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_gear_level.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_gear_level.value:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_gear_level
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value > 15U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_gear_level.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_gear_level.value:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_gear_position

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_gear_position
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_gear_position.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_gear_position.value:GEAR_POSITION_P
TEST.EXPECTED:chassis_state.chassis_state_set_gear_position.state[0].gear_system_state.gear_position:1
TEST.END

-- Subprogram: chassis_state_set_gear_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_gear_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_gear_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_gear_state.value:35
TEST.EXPECTED:chassis_state.chassis_state_set_gear_state.state[0].gear_system_state.handbrake:1
TEST.EXPECTED:chassis_state.chassis_state_set_gear_state.state[0].gear_system_state.gear_level:1
TEST.EXPECTED:chassis_state.chassis_state_set_gear_state.state[0].gear_system_state.gear_position:1
TEST.END

-- Subprogram: chassis_state_set_handbrake

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_handbrake
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_handbrake.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_handbrake.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_handbrake.state[0].gear_system_state.handbrake:1
TEST.END

-- Subprogram: chassis_state_set_hazard_flasher

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_hazard_flasher
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_hazard_flasher.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_hazard_flasher.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_hazard_flasher.state[0].light_system_state.hazard_flasher:1
TEST.END

-- Subprogram: chassis_state_set_high_beam

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_high_beam
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_high_beam.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_high_beam.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_high_beam.state[0].light_system_state.high_beam:1
TEST.END

-- Subprogram: chassis_state_set_lateral_acceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_lateral_acceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_lateral_acceleration.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_lateral_acceleration.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_lateral_acceleration.state[0].lateral_acceleration:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_lateral_activated

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_lateral_activated
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_lateral_activated.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_lateral_activated.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_lateral_activated.state[0].user_operation_state.lateral_activate:1
TEST.END

-- Subprogram: chassis_state_set_lateral_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_lateral_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_lateral_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_lateral_actuator_state.value:ACTUATOR_STATE_ACTIVE
TEST.EXPECTED:chassis_state.chassis_state_set_lateral_actuator_state.state[0].chassis_actuator_state.lateral_actuator_ready:1
TEST.EXPECTED:chassis_state.chassis_state_set_lateral_actuator_state.state[0].chassis_actuator_state.lateral_actuator_active:1
TEST.END

-- Subprogram: chassis_state_set_lateral_takeover

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_lateral_takeover
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_lateral_takeover.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_lateral_takeover.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_lateral_takeover.state[0].user_operation_state.lateral_takeover:1
TEST.END

-- Subprogram: chassis_state_set_left_turn_signal

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_left_turn_signal
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_left_turn_signal.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_left_turn_signal.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_left_turn_signal.state[0].light_system_state.left_turn_signal:1
TEST.END

-- Subprogram: chassis_state_set_light_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_light_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_light_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_light_state.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.rear_fog_light:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.front_fog_light:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.brake_light:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.high_beam:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.low_beam:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.hazard_flasher:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.right_turn_signal:0
TEST.EXPECTED:chassis_state.chassis_state_set_light_state.state[0].light_system_state.left_turn_signal:0
TEST.END

-- Subprogram: chassis_state_set_longitudinal_acceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_longitudinal_acceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_acceleration.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_acceleration.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_longitudinal_acceleration.state[0].longitudinal_acceleration:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_longitudinal_activated

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_longitudinal_activated
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_activated.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_activated.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_longitudinal_activated.state[0].user_operation_state.longitudinal_activate:1
TEST.END

-- Subprogram: chassis_state_set_longitudinal_actuator_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_longitudinal_actuator_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_actuator_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_actuator_state.value:ACTUATOR_STATE_ACTIVE
TEST.EXPECTED:chassis_state.chassis_state_set_longitudinal_actuator_state.value:ACTUATOR_STATE_ACTIVE
TEST.END

-- Subprogram: chassis_state_set_longitudinal_control_value

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_longitudinal_control_value
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_control_value.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_control_value.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_longitudinal_control_value.state[0].longitudinal_control_value:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_longitudinal_takeover

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_longitudinal_takeover
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_takeover.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_longitudinal_takeover.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_longitudinal_takeover.state[0].user_operation_state.longitudinal_takeover:1
TEST.END

-- Subprogram: chassis_state_set_low_beam

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_low_beam
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_low_beam.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_low_beam.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_low_beam.state[0].light_system_state.low_beam:1
TEST.END

-- Subprogram: chassis_state_set_rear_fog_light

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_fog_light
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_fog_light.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_fog_light.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_fog_light.state[0].light_system_state.rear_fog_light:1
TEST.EXPECTED:chassis_state.chassis_state_set_rear_fog_light.state[0].light_system_state.front_fog_light:0
TEST.END

-- Subprogram: chassis_state_set_rear_left_door

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_left_door
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_left_door.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_left_door.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_left_door.state[0].cockpit_system_state.rear_left_door:1
TEST.END

-- Subprogram: chassis_state_set_rear_left_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_left_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_left_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_left_wheel_speed.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_rear_left_wheel_speed.state[0].rear_left_wheel_speed:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_rear_left_window

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_left_window
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_left_window.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_left_window.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_left_window.state[0].cockpit_system_state.rear_left_window:1
TEST.END

-- Subprogram: chassis_state_set_rear_right_door

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_right_door
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_right_door.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_right_door.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_right_door.state[0].cockpit_system_state.rear_right_door:1
TEST.END

-- Subprogram: chassis_state_set_rear_right_wheel_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_right_wheel_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_right_wheel_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_right_wheel_speed.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_rear_right_wheel_speed.state[0].rear_right_wheel_speed:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_rear_right_window

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_right_window
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_right_window.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_right_window.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_right_window.state[0].cockpit_system_state.rear_right_window:1
TEST.END

-- Subprogram: chassis_state_set_rear_window_defroster

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_window_defroster
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_window_defroster.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_window_defroster.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_window_defroster.state[0].cockpit_system_state.rear_window_defroster:1
TEST.END

-- Subprogram: chassis_state_set_rear_wiper

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_rear_wiper
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_rear_wiper.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_rear_wiper.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_rear_wiper.state[0].cockpit_system_state.rear_wiper:1
TEST.END

-- Subprogram: chassis_state_set_right_turn_signal

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_right_turn_signal
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_right_turn_signal.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_right_turn_signal.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_right_turn_signal.state[0].light_system_state.right_turn_signal:1
TEST.END

-- Subprogram: chassis_state_set_signal_light_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_signal_light_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_signal_light_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_signal_light_state.left:true
TEST.VALUE:chassis_state.chassis_state_set_signal_light_state.right:true
TEST.VALUE:chassis_state.chassis_state_set_signal_light_state.warn:true
TEST.VALUE:chassis_state.chassis_state_set_signal_light_state.brake:true
TEST.EXPECTED:chassis_state.chassis_state_set_signal_light_state.state[0].light_system_state.brake_light:1
TEST.EXPECTED:chassis_state.chassis_state_set_signal_light_state.state[0].light_system_state.hazard_flasher:1
TEST.EXPECTED:chassis_state.chassis_state_set_signal_light_state.state[0].light_system_state.right_turn_signal:1
TEST.EXPECTED:chassis_state.chassis_state_set_signal_light_state.state[0].light_system_state.left_turn_signal:1
TEST.END

-- Subprogram: chassis_state_set_timestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_timestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_timestamp.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_timestamp.stamp[0].sec:1
TEST.VALUE:chassis_state.chassis_state_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:chassis_state.chassis_state_set_timestamp.state[0].stamp.sec:1
TEST.EXPECTED:chassis_state.chassis_state_set_timestamp.state[0].stamp.nsec:2
TEST.END

-- Subprogram: chassis_state_set_trunk_door

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_trunk_door
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_trunk_door.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_trunk_door.value:true
TEST.EXPECTED:chassis_state.chassis_state_set_trunk_door.state[0].cockpit_system_state.trunk_door:1
TEST.END

-- Subprogram: chassis_state_set_user_operation_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_user_operation_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_user_operation_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_user_operation_state.value:<<MAX>>
TEST.EXPECTED:chassis_state.chassis_state_set_user_operation_state.state[0].user_operation_state.lateral_takeover:1
TEST.EXPECTED:chassis_state.chassis_state_set_user_operation_state.state[0].user_operation_state.longitudinal_takeover:1
TEST.EXPECTED:chassis_state.chassis_state_set_user_operation_state.state[0].user_operation_state.lateral_activate:1
TEST.EXPECTED:chassis_state.chassis_state_set_user_operation_state.state[0].user_operation_state.longitudinal_activate:1
TEST.END

-- Subprogram: chassis_state_set_vehicle_speed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_vehicle_speed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_vehicle_speed.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_vehicle_speed.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_vehicle_speed.state[0].vehicle_speed:<<MIN>>
TEST.END

-- Subprogram: chassis_state_set_window_defroster_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_window_defroster_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_window_defroster_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_window_defroster_state.front:true
TEST.VALUE:chassis_state.chassis_state_set_window_defroster_state.rear:true
TEST.EXPECTED:chassis_state.chassis_state_set_window_defroster_state.state[0].cockpit_system_state.rear_window_defroster:1
TEST.EXPECTED:chassis_state.chassis_state_set_window_defroster_state.state[0].cockpit_system_state.front_window_defroster:1
TEST.END

-- Subprogram: chassis_state_set_window_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_window_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_window_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_window_state.fl:true
TEST.VALUE:chassis_state.chassis_state_set_window_state.fr:true
TEST.VALUE:chassis_state.chassis_state_set_window_state.rl:true
TEST.VALUE:chassis_state.chassis_state_set_window_state.rr:true
TEST.EXPECTED:chassis_state.chassis_state_set_window_state.state[0].cockpit_system_state.rear_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_window_state.state[0].cockpit_system_state.rear_left_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_window_state.state[0].cockpit_system_state.front_right_window:1
TEST.EXPECTED:chassis_state.chassis_state_set_window_state.state[0].cockpit_system_state.front_left_window:1
TEST.END

-- Subprogram: chassis_state_set_wiper_state

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_wiper_state
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_wiper_state.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_wiper_state.front:true
TEST.VALUE:chassis_state.chassis_state_set_wiper_state.rear:true
TEST.EXPECTED:chassis_state.chassis_state_set_wiper_state.state[0].cockpit_system_state.rear_wiper:1
TEST.EXPECTED:chassis_state.chassis_state_set_wiper_state.state[0].cockpit_system_state.front_wiper:1
TEST.END

-- Subprogram: chassis_state_set_yaw_rate

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:chassis_state_set_yaw_rate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.chassis_state_set_yaw_rate.state:<<malloc 1>>
TEST.VALUE:chassis_state.chassis_state_set_yaw_rate.value:<<MIN>>
TEST.EXPECTED:chassis_state.chassis_state_set_yaw_rate.state[0].yaw_rate:<<MIN>>
TEST.END

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_serialize_deserialize
TEST.SLOT: "1", "chassis_state", "chassis_state_serialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.SLOT: "2", "chassis_state", "chassis_state_deserialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.END
--
