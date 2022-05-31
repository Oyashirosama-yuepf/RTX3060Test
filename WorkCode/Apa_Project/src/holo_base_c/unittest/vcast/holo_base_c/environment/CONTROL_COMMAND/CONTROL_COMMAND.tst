-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : CONTROL_COMMAND
-- Unit(s) Under Test: control_command timestamp
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

-- Unit: control_command

-- Subprogram: control_command_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_deserialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_deserialize.buffer_size:36
TEST.VALUE:uut_prototype_stubs.deserialize_uint8.return:1
TEST.VALUE:uut_prototype_stubs.deserialize_uint32.return:4
TEST.VALUE:uut_prototype_stubs.deserialize_float32.return:4
TEST.EXPECTED:control_command.control_command_deserialize.command[0].stamp.sec:1
TEST.EXPECTED:control_command.control_command_deserialize.command[0].stamp.nsec:2
TEST.EXPECTED:control_command.control_command_deserialize.command[0].lateral_control_model:LATERAL_CONTROL_MODEL_STEERING_ANGLE
TEST.EXPECTED:control_command.control_command_deserialize.command[0].longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_TORQUE_DECELERATION
TEST.EXPECTED:control_command.control_command_deserialize.command[0].gear_control_model:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.EXPECTED:control_command.control_command_deserialize.command[0].lateral_control_value:2.0
TEST.EXPECTED:control_command.control_command_deserialize.command[0].longitudinal_control_value1:3.0
TEST.EXPECTED:control_command.control_command_deserialize.command[0].longitudinal_control_value2:4.0
TEST.EXPECTED:control_command.control_command_deserialize.command[0].gear_control_command.handbrake:1
TEST.EXPECTED:control_command.control_command_deserialize.command[0].gear_control_command.gear_level:1
TEST.EXPECTED:control_command.control_command_deserialize.command[0].gear_control_command.gear_position:1
TEST.EXPECTED:control_command.control_command_deserialize.return:36
TEST.VALUE_USER_CODE:control_command.control_command_deserialize.buffer
<<control_command.control_command_deserialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_deserialize.command:<<null>>
TEST.VALUE:control_command.control_command_deserialize.buffer:<<malloc 1>>
TEST.VALUE:control_command.control_command_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (command != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_deserialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_deserialize.buffer:<<malloc 1>>
TEST.VALUE:control_command.control_command_deserialize.buffer_size:<<MIN>>
TEST.VALUE_USER_CODE:control_command.control_command_deserialize.buffer
<<control_command.control_command_deserialize.buffer>> = ( NULL );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: control_command_deserialize.001
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_deserialize
TEST.NEW
TEST.NAME:control_command_deserialize.001
TEST.VALUE:control_command.control_command_deserialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_deserialize.buffer:<<malloc 4>>
TEST.VALUE:control_command.control_command_deserialize.buffer:"128"
TEST.VALUE:control_command.control_command_deserialize.buffer_size:1
TEST.EXPECTED:control_command.control_command_deserialize.return:MACRO=RC_DESERIALIZATION_BUFFER_UNDERFLOW
TEST.END

-- Test Case: control_command_deserialize.002
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_deserialize
TEST.NEW
TEST.NAME:control_command_deserialize.002
TEST.VALUE:control_command.control_command_deserialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_deserialize.buffer:<<malloc 4>>
TEST.VALUE:control_command.control_command_deserialize.buffer:"128"
TEST.VALUE:control_command.control_command_deserialize.buffer_size:128
TEST.VALUE:uut_prototype_stubs.deserialize_float32.return:64
TEST.END

-- Subprogram: control_command_get_gear_command

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_command
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_command.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_gear_command.command[0].gear_control_command.handbrake:1
TEST.VALUE:control_command.control_command_get_gear_command.command[0].gear_control_command.gear_level:2
TEST.VALUE:control_command.control_command_get_gear_command.command[0].gear_control_command.gear_position:3
TEST.EXPECTED:control_command.control_command_get_gear_command.return:101
TEST.END

-- Subprogram: control_command_get_gear_control_model

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_control_model.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_gear_control_model.command[0].gear_control_model:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.EXPECTED:control_command.control_command_get_gear_control_model.return:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_control_model.command:<<null>>
TEST.END

-- Subprogram: control_command_get_gear_level

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_level
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_level.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_gear_level.command[0].gear_control_command.gear_level:2
TEST.EXPECTED:control_command.control_command_get_gear_level.return:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_level
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_level.command:<<null>>
TEST.END

-- Subprogram: control_command_get_gear_position

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_position
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_position.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_gear_position.command[0].gear_control_command.gear_position:1
TEST.EXPECTED:control_command.control_command_get_gear_position.return:GEAR_POSITION_P
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_gear_position
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_gear_position.command:<<null>>
TEST.END

-- Subprogram: control_command_get_handbrake

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_handbrake
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_handbrake.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_handbrake.command[0].gear_control_command.handbrake:1
TEST.EXPECTED:control_command.control_command_get_handbrake.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_handbrake
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_handbrake.command:<<null>>
TEST.END

-- Subprogram: control_command_get_lateral_control_model

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_control_model.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_lateral_control_model.command[0].lateral_control_model:LATERAL_CONTROL_MODEL_TORQUE
TEST.EXPECTED:control_command.control_command_get_lateral_control_model.return:LATERAL_CONTROL_MODEL_TORQUE
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_control_model.command:<<null>>
TEST.END

-- Subprogram: control_command_get_lateral_control_value

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_control_value
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_control_value.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_lateral_control_value.command[0].lateral_control_value:1.0
TEST.EXPECTED:control_command.control_command_get_lateral_control_value.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_control_value
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_control_value.command:<<null>>
TEST.END

-- Subprogram: control_command_get_lateral_front_wheel_angle

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_front_wheel_angle
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_front_wheel_angle.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_lateral_front_wheel_angle.command[0].lateral_control_value:1.0
TEST.EXPECTED:control_command.control_command_get_lateral_front_wheel_angle.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_front_wheel_angle
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_front_wheel_angle.command:<<null>>
TEST.END

-- Subprogram: control_command_get_lateral_steering_angle

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_steering_angle
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_steering_angle.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_lateral_steering_angle.command[0].lateral_control_value:1.0
TEST.EXPECTED:control_command.control_command_get_lateral_steering_angle.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_steering_angle
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_steering_angle.command:<<null>>
TEST.END

-- Subprogram: control_command_get_lateral_torque

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_torque
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_torque.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_lateral_torque.command[0].lateral_control_value:1.0
TEST.EXPECTED:control_command.control_command_get_lateral_torque.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_lateral_torque
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_lateral_torque.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_acceleration.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_acceleration.command[0].longitudinal_control_value1:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_acceleration.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_acceleration.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_control_model

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_control_model.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_control_model.command[0].longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_ACCELERATE
TEST.EXPECTED:control_command.control_command_get_longitudinal_control_model.return:LONGITUDINAL_CONTROL_MODEL_ACCELERATE
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_control_model.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_control_value1

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_control_value1
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_control_value1.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_control_value1.command[0].longitudinal_control_value1:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_control_value1.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_control_value1
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_control_value1.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_control_value2

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_control_value2
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_control_value2.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_control_value2.command[0].longitudinal_control_value2:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_control_value2.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_control_value2
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_control_value2.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_deceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_deceleration.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_deceleration.command[0].longitudinal_control_value1:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_deceleration.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_deceleration.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_speed_limit

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_speed_limit
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_speed_limit.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_speed_limit.command[0].longitudinal_control_value1:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_speed_limit.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_speed_limit
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_speed_limit.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_stop_distance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_stop_distance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_stop_distance.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_stop_distance.command[0].longitudinal_control_value2:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_stop_distance.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_stop_distance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_stop_distance.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_torque

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_torque
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_torque.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_torque.command[0].longitudinal_control_value1:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_torque.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_torque
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_torque.command:<<null>>
TEST.END

-- Subprogram: control_command_get_longitudinal_torque_deceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_torque_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_torque_deceleration.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_longitudinal_torque_deceleration.command[0].longitudinal_control_value1:1.0
TEST.EXPECTED:control_command.control_command_get_longitudinal_torque_deceleration.return:1.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_longitudinal_torque_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_longitudinal_torque_deceleration.command:<<null>>
TEST.END

-- Subprogram: control_command_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_serialized_size.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].stamp.sec:1
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].stamp.nsec:2
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].lateral_control_model:LATERAL_CONTROL_MODEL_STEERING_ANGLE
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_PARK
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].gear_control_model:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].lateral_control_value:1.0
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].longitudinal_control_value1:2.0
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].longitudinal_control_value2:3.0
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].gear_control_command.handbrake:1
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].gear_control_command.gear_level:1
TEST.VALUE:control_command.control_command_get_serialized_size.command[0].gear_control_command.gear_position:1
TEST.EXPECTED:control_command.control_command_get_serialized_size.return:36
TEST.END

-- Subprogram: control_command_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 926 TEST.STUB:uut_prototype_stubs.__assert_fail
    >>>     >>> Could not find function __assert_fail
    >>>     >>>    in unit uut_prototype_stubs.
    >>>     >>> Value Line Error - Command Ignored
    >>> (E) @LINE: 926 
    >>>     >>> Could not stub uut_prototype_stubs.__assert_fail
    >>> (E) @LINE: 928 TEST.STUB_VAL_USER_CODE:uut_prototype_stubs.__assert_fail.__function
    >>>     >>> Could not find function __assert_fail
    >>>     >>>    in unit uut_prototype_stubs.
    >>>     >>> Value Line Error - Command Ignored
    >>> (E) @LINE: 928 
    >>>     >>> VectorCast was unable to process this line.
    >>>     >>> Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (controlcommand != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_timestamp.controlcommand:<<null>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (controlcommand != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_get_timestamp.controlcommand:<<malloc 1>>
TEST.VALUE:control_command.control_command_get_timestamp.controlcommand[0].stamp.sec:1
TEST.VALUE:control_command.control_command_get_timestamp.controlcommand[0].stamp.nsec:2
TEST.EXPECTED:control_command.control_command_get_timestamp.return[0].sec:1
TEST.EXPECTED:control_command.control_command_get_timestamp.return[0].nsec:2
TEST.END

-- Subprogram: control_command_init_default

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_init_default.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_init_default.command[0].stamp.sec:1
TEST.VALUE:control_command.control_command_init_default.command[0].stamp.nsec:2
TEST.VALUE:control_command.control_command_init_default.command[0].lateral_control_model:LATERAL_CONTROL_MODEL_STEERING_ANGLE
TEST.VALUE:control_command.control_command_init_default.command[0].longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_PARK
TEST.VALUE:control_command.control_command_init_default.command[0].lateral_control_value:1.0
TEST.VALUE:control_command.control_command_init_default.command[0].longitudinal_control_value1:2.0
TEST.VALUE:control_command.control_command_init_default.command[0].longitudinal_control_value2:3.0
TEST.VALUE:control_command.control_command_init_default.command[0].gear_control_command.handbrake:1
TEST.VALUE:control_command.control_command_init_default.command[0].gear_control_command.gear_level:2
TEST.VALUE:control_command.control_command_init_default.command[0].gear_control_command.gear_position:3
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_init_default.command:<<null>>
TEST.END

-- Subprogram: control_command_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_serialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_serialize.command[0].stamp.sec:1
TEST.VALUE:control_command.control_command_serialize.command[0].stamp.nsec:2
TEST.VALUE:control_command.control_command_serialize.command[0].lateral_control_model:LATERAL_CONTROL_MODEL_STEERING_ANGLE
TEST.VALUE:control_command.control_command_serialize.command[0].longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_PARK
TEST.VALUE:control_command.control_command_serialize.command[0].gear_control_model:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.VALUE:control_command.control_command_serialize.command[0].lateral_control_value:2.0
TEST.VALUE:control_command.control_command_serialize.command[0].longitudinal_control_value1:3.0
TEST.VALUE:control_command.control_command_serialize.command[0].longitudinal_control_value2:4.0
TEST.VALUE:control_command.control_command_serialize.command[0].gear_control_command.handbrake:1
TEST.VALUE:control_command.control_command_serialize.command[0].gear_control_command.gear_level:1
TEST.VALUE:control_command.control_command_serialize.command[0].gear_control_command.gear_position:1
TEST.VALUE:control_command.control_command_serialize.buffer_size:36
TEST.VALUE:uut_prototype_stubs.serialize_uint8.return:1
TEST.VALUE:uut_prototype_stubs.serialize_uint32.return:4
TEST.VALUE:uut_prototype_stubs.serialize_float32.return:4
TEST.EXPECTED:control_command.control_command_serialize.return:36
TEST.VALUE_USER_CODE:control_command.control_command_serialize.buffer
<<control_command.control_command_serialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_serialize.command:<<null>>
TEST.VALUE:control_command.control_command_serialize.buffer:<<malloc 1>>
TEST.VALUE:control_command.control_command_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (command != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_serialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_serialize.buffer:<<malloc 1>>
TEST.VALUE:control_command.control_command_serialize.buffer_size:<<MIN>>
TEST.VALUE_USER_CODE:control_command.control_command_serialize.buffer
<<control_command.control_command_serialize.buffer>> = ( NULL );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: control_command_serialize.001
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_serialize
TEST.NEW
TEST.NAME:control_command_serialize.001
TEST.VALUE:control_command.control_command_serialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_serialize.buffer:<<malloc 4>>
TEST.VALUE:control_command.control_command_serialize.buffer:"128"
TEST.VALUE:control_command.control_command_serialize.buffer_size:1
TEST.EXPECTED:control_command.control_command_serialize.return:MACRO=RC_SERIALIZATION_BUFFER_OVERFLOW
TEST.END

-- Test Case: control_command_serialize.002
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_serialize
TEST.NEW
TEST.NAME:control_command_serialize.002
TEST.VALUE:control_command.control_command_serialize.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_serialize.buffer:<<malloc 4>>
TEST.VALUE:control_command.control_command_serialize.buffer:"128"
TEST.VALUE:control_command.control_command_serialize.buffer_size:128
TEST.VALUE:uut_prototype_stubs.serialize_float32.return:64
TEST.END

-- Subprogram: control_command_set_gear_command

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_command
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_command.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_gear_command.value:101
TEST.EXPECTED:control_command.control_command_set_gear_command.command[0].gear_control_command.handbrake:1
TEST.EXPECTED:control_command.control_command_set_gear_command.command[0].gear_control_command.gear_level:2
TEST.EXPECTED:control_command.control_command_set_gear_command.command[0].gear_control_command.gear_position:3
TEST.END

-- Subprogram: control_command_set_gear_control_model

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_control_model.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_gear_control_model.gear_control_model:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.EXPECTED:control_command.control_command_set_gear_control_model.command[0].gear_control_model:GEAR_CONTROL_MODEL_GEAR_CONTROL
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_control_model.command:<<null>>
TEST.VALUE:control_command.control_command_set_gear_control_model.gear_control_model:<<MIN>>
TEST.END

-- Subprogram: control_command_set_gear_level

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_level
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_level.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_gear_level.value:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_gear_level.command[0].gear_control_command.gear_level:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_level
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_level.command:<<null>>
TEST.VALUE:control_command.control_command_set_gear_level.value:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_level
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (command != (void *)0) ==> FALSE
      (2) (value > 15) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable control_command.control_command_set_gear_level.command 'equal to' and 'not equal to' same value in branches 1/2
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_level.command:<<null>>
TEST.VALUE:control_command.control_command_set_gear_level.value:<<MAX>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_level
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (command != (void *)0) ==> FALSE
      (2) (value > 15) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable control_command.control_command_set_gear_level.command 'equal to' and 'not equal to' same value in branches 1/2
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_level.command:<<null>>
TEST.VALUE:control_command.control_command_set_gear_level.value:<<MIN>>
TEST.END

-- Subprogram: control_command_set_gear_position

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_position
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_position.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_gear_position.value:GEAR_POSITION_N
TEST.EXPECTED:control_command.control_command_set_gear_position.command[0].gear_control_command.gear_position:3
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_gear_position
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_gear_position.command:<<null>>
TEST.VALUE:control_command.control_command_set_gear_position.value:<<MIN>>
TEST.END

-- Subprogram: control_command_set_handbrake

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_handbrake
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_handbrake.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_handbrake.value:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_handbrake.command[0].gear_control_command.handbrake:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_handbrake
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_handbrake.command:<<null>>
TEST.VALUE:control_command.control_command_set_handbrake.value:<<MIN>>
TEST.END

-- Subprogram: control_command_set_lateral_control_model

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_control_model.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_lateral_control_model.lateral_control_model:LATERAL_CONTROL_MODEL_TORQUE
TEST.EXPECTED:control_command.control_command_set_lateral_control_model.command[0].lateral_control_model:LATERAL_CONTROL_MODEL_TORQUE
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_control_model.command:<<null>>
TEST.VALUE:control_command.control_command_set_lateral_control_model.lateral_control_model:<<MIN>>
TEST.END

-- Subprogram: control_command_set_lateral_control_value

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_control_value
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_control_value.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_lateral_control_value.lateral_control_value:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_lateral_control_value.command[0].lateral_control_value:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_control_value
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_control_value.command:<<null>>
TEST.VALUE:control_command.control_command_set_lateral_control_value.lateral_control_value:<<MIN>>
TEST.END

-- Subprogram: control_command_set_lateral_front_wheel_angle

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_front_wheel_angle
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_front_wheel_angle.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_lateral_front_wheel_angle.front_wheel_angle:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_lateral_front_wheel_angle.command[0].lateral_control_value:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_front_wheel_angle
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_front_wheel_angle.command:<<null>>
TEST.VALUE:control_command.control_command_set_lateral_front_wheel_angle.front_wheel_angle:<<MIN>>
TEST.END

-- Subprogram: control_command_set_lateral_steering_angle

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_steering_angle
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_steering_angle.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_lateral_steering_angle.steering_angle:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_lateral_steering_angle.command[0].lateral_control_value:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_steering_angle
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_steering_angle.command:<<null>>
TEST.VALUE:control_command.control_command_set_lateral_steering_angle.steering_angle:<<MIN>>
TEST.END

-- Subprogram: control_command_set_lateral_torque

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_torque
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_torque.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_lateral_torque.lateral_torque:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_lateral_torque.command[0].lateral_control_value:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_lateral_torque
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_lateral_torque.command:<<null>>
TEST.VALUE:control_command.control_command_set_lateral_torque.lateral_torque:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_acceleration.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_acceleration.acceleration:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_acceleration.command[0].longitudinal_control_value1:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_acceleration.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_acceleration.acceleration:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_control_model

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_control_model.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_control_model.longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_ACCELERATE
TEST.EXPECTED:control_command.control_command_set_longitudinal_control_model.command[0].longitudinal_control_model:LONGITUDINAL_CONTROL_MODEL_ACCELERATE
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_control_model
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_control_model.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_control_model.longitudinal_control_model:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_control_value1

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_control_value1
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_control_value1.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_control_value1.longitudinal_control_value:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_control_value1.command[0].longitudinal_control_value1:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_control_value1
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_control_value1.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_control_value1.longitudinal_control_value:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_control_value2

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_control_value2
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_control_value2.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_control_value2.longitudinal_control_value:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_control_value2.command[0].longitudinal_control_value2:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_control_value2
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_control_value2.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_control_value2.longitudinal_control_value:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_deceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_deceleration.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_deceleration.deceleration:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_deceleration.command[0].longitudinal_control_value1:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_deceleration.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_deceleration.deceleration:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_speed_limit

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_speed_limit
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_speed_limit.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_speed_limit.speed_limit:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_speed_limit.command[0].longitudinal_control_value1:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_speed_limit
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_speed_limit.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_speed_limit.speed_limit:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_stop_distance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_stop_distance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_stop_distance.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_stop_distance.stop_distance:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_stop_distance.command[0].longitudinal_control_value2:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_stop_distance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_stop_distance.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_stop_distance.stop_distance:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_torque

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_torque
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_torque.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_torque.torque:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_torque.command[0].longitudinal_control_value1:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_torque
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_torque.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_torque.torque:<<MIN>>
TEST.END

-- Subprogram: control_command_set_longitudinal_torque_deceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_torque_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (command != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_torque_deceleration.command:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_longitudinal_torque_deceleration.torque_deceleration:<<MIN>>
TEST.EXPECTED:control_command.control_command_set_longitudinal_torque_deceleration.command[0].longitudinal_control_value1:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_longitudinal_torque_deceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (command != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_longitudinal_torque_deceleration.command:<<null>>
TEST.VALUE:control_command.control_command_set_longitudinal_torque_deceleration.torque_deceleration:<<MIN>>
TEST.END

-- Subprogram: control_command_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (controlcommand != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_timestamp.controlcommand:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_timestamp.stamp[0].sec:1
TEST.VALUE:control_command.control_command_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:control_command.control_command_set_timestamp.controlcommand[0].stamp.sec:1
TEST.EXPECTED:control_command.control_command_set_timestamp.controlcommand[0].stamp.nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (controlcommand != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_timestamp.controlcommand:<<null>>
TEST.VALUE:control_command.control_command_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (controlcommand != (void *)0) ==> FALSE
      (2) if (stamp != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_timestamp.controlcommand:<<malloc 1>>
TEST.VALUE:control_command.control_command_set_timestamp.stamp:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:control_command_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (controlcommand != (void *)0) ==> FALSE
      (2) if (stamp != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.control_command_set_timestamp.controlcommand:<<null>>
TEST.VALUE:control_command.control_command_set_timestamp.stamp:<<null>>
TEST.END

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_serialize_deserialize
TEST.SLOT: "1", "control_command", "control_command_serialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.SLOT: "2", "control_command", "control_command_deserialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.END
--
