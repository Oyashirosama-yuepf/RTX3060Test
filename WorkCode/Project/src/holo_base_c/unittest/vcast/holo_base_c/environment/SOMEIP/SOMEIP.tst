-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : SOMEIP
-- Unit(s) Under Test: someip
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

-- Unit: someip

-- Subprogram: someip_packet_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (packet != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (packet != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: someip_packet_deserialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (packet != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (packet != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set return value of function someip_packet_get_serialized_size_4byte_aligned in branch 3
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set return value of function someip_packet_get_serialized_size_4byte_aligned in branch 3
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: someip_packet_deserialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (packet != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (packet != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set return value of function someip_packet_get_serialized_size_8byte_aligned in branch 3
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set return value of function someip_packet_get_serialized_size_8byte_aligned in branch 3
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: someip_packet_get_payload

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_get_payload
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (buffer_size < packet->msg_length - (8)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_get_payload.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_get_payload.packet[0].msg_length:10
TEST.VALUE:someip.someip_packet_get_payload.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_get_payload.buffer_size:<<MIN>>
TEST.EXPECTED:someip.someip_packet_get_payload.return:MACRO=RC_FAIL
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_get_payload
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (buffer_size < packet->msg_length - (8)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_get_payload.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_get_payload.packet[0].msg_length:10
TEST.VALUE:someip.someip_packet_get_payload.packet[0].payload:<<malloc 3>>
TEST.VALUE:someip.someip_packet_get_payload.packet[0].payload:"ab"
TEST.VALUE:someip.someip_packet_get_payload.buffer:<<malloc 2>>
TEST.VALUE:someip.someip_packet_get_payload.buffer_size:2
TEST.EXPECTED:someip.someip_packet_get_payload.buffer[0]:16#61#
TEST.EXPECTED:someip.someip_packet_get_payload.buffer[1]:16#62#
TEST.EXPECTED:someip.someip_packet_get_payload.return:2
TEST.ATTRIBUTES:someip.someip_packet_get_payload.buffer[0]:INPUT_BASE=16
TEST.ATTRIBUTES:someip.someip_packet_get_payload.buffer[1]:INPUT_BASE=16
TEST.END

-- Subprogram: someip_packet_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_get_serialized_size.packet:<<malloc 1>>
TEST.EXPECTED:someip.someip_packet_get_serialized_size.return:8
TEST.END

-- Subprogram: someip_packet_get_serialized_size_4byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_get_serialized_size_4byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_get_serialized_size_4byte_aligned.packet:<<malloc 1>>
TEST.EXPECTED:someip.someip_packet_get_serialized_size_4byte_aligned.return:8
TEST.END

-- Subprogram: someip_packet_get_serialized_size_8byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_get_serialized_size_8byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_get_serialized_size_8byte_aligned.packet:<<malloc 1>>
TEST.EXPECTED:someip.someip_packet_get_serialized_size_8byte_aligned.return:8
TEST.END

-- Subprogram: someip_packet_init_default

-- Test Case: BASIS-PATH-001
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_init_default
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_init_default.packet:<<malloc 1>>
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].service_id:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].method_id:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].msg_length:8
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].client_id:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].session_id:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].proto_ver:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].if_ver:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].msg_type:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].ret_code:0
TEST.EXPECTED:someip.someip_packet_init_default.packet[0].payload:""
TEST.EXPECTED:someip.someip_packet_init_default.return:0
TEST.END

-- Subprogram: someip_packet_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (packet != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (packet != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: someip_packet_serialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (packet != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (packet != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: someip_packet_serialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (packet != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (packet != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (packet != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.packet:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:someip.someip_packet_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: someip_packet_set_payload

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_set_payload
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (len > (1024)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_set_payload.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_set_payload.buffer:<<malloc 1>>
TEST.VALUE:someip.someip_packet_set_payload.len:<<MAX>>
TEST.EXPECTED:someip.someip_packet_set_payload.return:MACRO=RC_FAIL
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:someip
TEST.SUBPROGRAM:someip_packet_set_payload
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (len > (1024)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:someip.someip_packet_set_payload.packet:<<malloc 1>>
TEST.VALUE:someip.someip_packet_set_payload.buffer:<<malloc 2>>
TEST.VALUE:someip.someip_packet_set_payload.buffer[0]:16#61#
TEST.VALUE:someip.someip_packet_set_payload.buffer[1]:16#62#
TEST.VALUE:someip.someip_packet_set_payload.len:2
TEST.EXPECTED:someip.someip_packet_set_payload.packet[0].payload:"ab"
TEST.EXPECTED:someip.someip_packet_set_payload.return:0
TEST.END
