-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : LIGHT_SIGNAL_REQUEST
-- Unit(s) Under Test: light_signal_request
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

-- Unit: light_signal_request

-- Subprogram: light_signal_request_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> FALSE
      (5) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set local variable expected_size in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_deserialize
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> FALSE
      (5) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set local variable expected_size in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_deserialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: light_signal_request_get_brake_light

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_brake_light
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_brake_light.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_get_brake_light.request[0].light_command.brake_light:1
TEST.EXPECTED:light_signal_request.light_signal_request_get_brake_light.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_brake_light
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_brake_light.request:<<null>>
TEST.END

-- Subprogram: light_signal_request_get_hazard_flasher

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_hazard_flasher
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_hazard_flasher.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_get_hazard_flasher.request[0].light_command.hazard_flasher:1
TEST.EXPECTED:light_signal_request.light_signal_request_get_hazard_flasher.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_hazard_flasher
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_hazard_flasher.request:<<null>>
TEST.END

-- Subprogram: light_signal_request_get_left_turn_signal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_left_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_left_turn_signal.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_get_left_turn_signal.request[0].light_command.left_turn_signal:1
TEST.EXPECTED:light_signal_request.light_signal_request_get_left_turn_signal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_left_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_left_turn_signal.request:<<null>>
TEST.END

-- Subprogram: light_signal_request_get_light_command

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_light_command
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_light_command.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_get_light_command.request[0].light_command.brake_light:1
TEST.VALUE:light_signal_request.light_signal_request_get_light_command.request[0].light_command.hazard_flasher:1
TEST.VALUE:light_signal_request.light_signal_request_get_light_command.request[0].light_command.right_turn_signal:1
TEST.VALUE:light_signal_request.light_signal_request_get_light_command.request[0].light_command.left_turn_signal:1
TEST.EXPECTED:light_signal_request.light_signal_request_get_light_command.return:16#E4#
TEST.END

-- Subprogram: light_signal_request_get_right_turn_signal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_right_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_right_turn_signal.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_get_right_turn_signal.request[0].light_command.right_turn_signal:1
TEST.EXPECTED:light_signal_request.light_signal_request_get_right_turn_signal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_right_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_right_turn_signal.request:<<null>>
TEST.END

-- Subprogram: light_signal_request_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_serialized_size.request:<<malloc 1>>
TEST.EXPECTED:light_signal_request.light_signal_request_get_serialized_size.return:8
TEST.END

-- Subprogram: light_signal_request_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_timestamp.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_get_timestamp.request[0].stamp.sec:1
TEST.VALUE:light_signal_request.light_signal_request_get_timestamp.request[0].stamp.nsec:2
TEST.EXPECTED:light_signal_request.light_signal_request_get_timestamp.return[0].sec:1
TEST.EXPECTED:light_signal_request.light_signal_request_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_get_timestamp.request:<<null>>
TEST.END

-- Subprogram: light_signal_request_init_default

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_init_default.request:<<malloc 1>>
TEST.EXPECTED:light_signal_request.light_signal_request_init_default.request[0].stamp.sec:0
TEST.EXPECTED:light_signal_request.light_signal_request_init_default.request[0].stamp.nsec:0
TEST.EXPECTED:light_signal_request.light_signal_request_init_default.request[0].light_command.brake_light:0
TEST.EXPECTED:light_signal_request.light_signal_request_init_default.request[0].light_command.hazard_flasher:0
TEST.EXPECTED:light_signal_request.light_signal_request_init_default.request[0].light_command.right_turn_signal:0
TEST.EXPECTED:light_signal_request.light_signal_request_init_default.request[0].light_command.left_turn_signal:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_init_default.request:<<null>>
TEST.END

-- Subprogram: light_signal_request_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> FALSE
      (5) if (serialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set serialized_size due to assignment
      Cannot set local variable expected_size in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_serialize
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (request != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < (6)) ==> FALSE
      (5) if (serialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set serialized_size due to assignment
      Cannot set local variable expected_size in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_serialize.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: light_signal_request_set_brake_light

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_brake_light
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_brake_light.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_brake_light.value:true
TEST.EXPECTED:light_signal_request.light_signal_request_set_brake_light.request[0].light_command.brake_light:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_brake_light
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_brake_light.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_brake_light.value:<<MIN>>
TEST.END

-- Subprogram: light_signal_request_set_hazard_flasher

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_hazard_flasher
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_hazard_flasher.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_hazard_flasher.value:true
TEST.EXPECTED:light_signal_request.light_signal_request_set_hazard_flasher.request[0].light_command.hazard_flasher:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_hazard_flasher
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_hazard_flasher.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_hazard_flasher.value:<<MIN>>
TEST.END

-- Subprogram: light_signal_request_set_left_turn_signal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_left_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_left_turn_signal.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_left_turn_signal.value:true
TEST.EXPECTED:light_signal_request.light_signal_request_set_left_turn_signal.request[0].light_command.left_turn_signal:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_left_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_left_turn_signal.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_left_turn_signal.value:<<MIN>>
TEST.END

-- Subprogram: light_signal_request_set_light_command

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_light_command
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_light_command.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_light_command.value:16#E4#
TEST.EXPECTED:light_signal_request.light_signal_request_set_light_command.request[0].light_command.brake_light:1
TEST.EXPECTED:light_signal_request.light_signal_request_set_light_command.request[0].light_command.hazard_flasher:1
TEST.EXPECTED:light_signal_request.light_signal_request_set_light_command.request[0].light_command.right_turn_signal:1
TEST.EXPECTED:light_signal_request.light_signal_request_set_light_command.request[0].light_command.left_turn_signal:1
TEST.END

-- Subprogram: light_signal_request_set_right_turn_signal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_right_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_right_turn_signal.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_right_turn_signal.value:true
TEST.EXPECTED:light_signal_request.light_signal_request_set_right_turn_signal.request[0].light_command.right_turn_signal:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_right_turn_signal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_right_turn_signal.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_right_turn_signal.value:<<MIN>>
TEST.END

-- Subprogram: light_signal_request_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (request != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.request:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.stamp[0].sec:1
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:light_signal_request.light_signal_request_set_timestamp.request[0].stamp.sec:1
TEST.EXPECTED:light_signal_request.light_signal_request_set_timestamp.request[0].stamp.nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (request != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (request != (void *)0) ==> FALSE
      (2) if (stamp != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:light_signal_request_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (request != (void *)0) ==> FALSE
      (2) if (stamp != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.request:<<null>>
TEST.VALUE:light_signal_request.light_signal_request_set_timestamp.stamp:<<null>>
TEST.END
