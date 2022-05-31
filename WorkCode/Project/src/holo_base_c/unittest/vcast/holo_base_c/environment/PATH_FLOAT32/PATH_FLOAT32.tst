-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : PATH_FLOAT32
-- Unit(s) Under Test: path_float32
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

-- Unit: path_float32

-- Subprogram: path_pointf_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_deserialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: path_pointf_get_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_acceleration.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_acceleration.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_curvature

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_curvature
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_curvature.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_curvature
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_curvature.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_distance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_distance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_distance.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_distance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_distance.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_point

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_point
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_point.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_point
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_point.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_serialized_size

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_serialized_size
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_serialized_size.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_serialized_size
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_serialized_size.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_speed

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_speed
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_speed.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_speed
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_speed.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_theta

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_theta
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_theta.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_theta
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_theta.point:<<null>>
TEST.END

-- Subprogram: path_pointf_get_time

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_time
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_time.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_get_time
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_get_time.point:<<null>>
TEST.END

-- Subprogram: path_pointf_init_default

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_init_default.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_init_default.point:<<null>>
TEST.END

-- Subprogram: path_pointf_init_from_path_pointf

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_init_from_path_pointf
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.other:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_init_from_path_pointf
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.point:<<null>>
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.other:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_init_from_path_pointf
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (point != (void *)0) ==> FALSE
      (2) if (other != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.point:<<null>>
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.other:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_init_from_path_pointf
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (point != (void *)0) ==> FALSE
      (2) if (other != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.point:<<null>>
TEST.VALUE:path_float32.path_pointf_init_from_path_pointf.other:<<null>>
TEST.END

-- Subprogram: path_pointf_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (serialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set serialized_size due to assignment
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (point != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (serialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set serialized_size due to assignment
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_serialize.point:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.path_pointf_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: path_pointf_set_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_acceleration.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_acceleration.acceleration:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_acceleration.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_acceleration.acceleration:<<MIN>>
TEST.END

-- Subprogram: path_pointf_set_curvature

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_curvature
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_curvature.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_curvature.curvature:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_curvature
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_curvature.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_curvature.curvature:<<MIN>>
TEST.END

-- Subprogram: path_pointf_set_distance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_distance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_distance.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_distance.distance:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_distance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_distance.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_distance.distance:<<MIN>>
TEST.END

-- Subprogram: path_pointf_set_point

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_point
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_point.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_point.pt:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_point
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_point.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_point.pt:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_point
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (point != (void *)0) ==> FALSE
      (2) if (pt != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_point.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_point.pt:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_point
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (point != (void *)0) ==> FALSE
      (2) if (pt != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_point.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_point.pt:<<null>>
TEST.END

-- Subprogram: path_pointf_set_speed

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_speed
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_speed.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_speed.speed:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_speed
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_speed.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_speed.speed:<<MIN>>
TEST.END

-- Subprogram: path_pointf_set_theta

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_theta
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_theta.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_theta.theta:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_theta
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_theta.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_theta.theta:<<MIN>>
TEST.END

-- Subprogram: path_pointf_set_time

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_time
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_time.point:<<malloc 1>>
TEST.VALUE:path_float32.path_pointf_set_time.time:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:path_pointf_set_time
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.path_pointf_set_time.point:<<null>>
TEST.VALUE:path_float32.path_pointf_set_time.time:<<MIN>>
TEST.END

-- Subprogram: pathf_clear_path_list

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_clear_path_list
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_clear_path_list.path:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_clear_path_list
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_clear_path_list.path:<<null>>
TEST.END

-- Subprogram: pathf_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable  'less than' and 'greater than' same value in branches 3/4
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/4
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (expected_size > buffer_size) ==> FALSE
      (5) for (idx < path->point_num) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/5
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_deserialize.path[0].point_num:1
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (expected_size > buffer_size) ==> FALSE
      (5) for (idx < path->point_num) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/5
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_deserialize.path[0].point_num:0
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_6_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_6_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:12 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 12
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (expected_size > buffer_size) ==> FALSE
      (5) for (idx < path->point_num) ==> TRUE
      (6) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #6, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set expected_size due to assignment
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/5
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/6
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.path[0].point_num:1
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_6_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_deserialize
TEST.NEW
TEST.NAME:COND_6_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:11 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 11
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) if (expected_size > buffer_size) ==> FALSE
      (5) for (idx < path->point_num) ==> TRUE
      (6) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #6, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set expected_size due to assignment
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/5
      Conflict: Trying to set variable path_float32.pathf_deserialize.path 'equal to' and 'not equal to' same value in branches 1/6
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_deserialize.path:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.path[0].point_num:1
TEST.VALUE:path_float32.pathf_deserialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: pathf_find_closest_point

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/4
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:0
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/4
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:1
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/5
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MAX>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/5
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_6_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_6_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:12 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 12
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> FALSE
      (6) for (idx < path->point_num) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #6, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/6
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_6_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_6_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:11 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 11
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> FALSE
      (6) for (idx < path->point_num) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #6, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/6
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:1
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_8_ROW_1_PAIR_a_Tx-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_8_ROW_1_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:13 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 13
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> FALSE
      (6) for (idx < path->point_num) ==> TRUE
      (8) if (!find_closest_point && idx != (0)) ==> FALSE
      Row number 1 forms a pair with Row 3 for Condition #8, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable find_closest_point in branch 8
      Cannot set idx due to assignment
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/5
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/6
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/7
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_8_ROW_3_PAIR_a_FT-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_8_ROW_3_PAIR_a_FT-PARTIAL
TEST.MCDC_BASIS_PATH:14 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 14
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> FALSE
      (6) for (idx < path->point_num) ==> TRUE
      (8) if (!find_closest_point && idx != (0)) ==> TRUE
      Row number 3 forms a pair with Row 1 for Condition #8, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable find_closest_point in branch 8
      Cannot set idx due to assignment
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/5
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/6
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/7
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Test Case: COND_8_ROW_4_PAIR_b_FF-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_find_closest_point
TEST.NEW
TEST.NAME:COND_8_ROW_4_PAIR_b_FF-PARTIAL
TEST.MCDC_BASIS_PATH:15 of 15
TEST.NOTES:
This is an automatically generated test case.
   Test Path 15
      (1) if (path != (void *)0) ==> FALSE
      (2) if (target_point != (void *)0) ==> FALSE
      (3) if (closest_idx != (void *)0) ==> FALSE
      (4) if (path->point_num == (0)) ==> FALSE
      (5) if (start_idx >= path->point_num) ==> FALSE
      (6) for (idx < path->point_num) ==> TRUE
      (8) if (!find_closest_point && idx != (0)) ==> FALSE
      Row number 4 forms a pair with Row 3 for Condition #8, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable find_closest_point in branch 8
      Cannot set idx due to assignment
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/5
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/6
      Conflict: Trying to set variable path_float32.pathf_find_closest_point.path 'equal to' and 'not equal to' same value in branches 1/7
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_find_closest_point.path:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_find_closest_point.target_point:<<null>>
TEST.VALUE:path_float32.pathf_find_closest_point.start_idx:<<MIN>>
TEST.VALUE:path_float32.pathf_find_closest_point.closest_idx:<<null>>
TEST.END

-- Subprogram: pathf_get_acceleration_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_acceleration_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_acceleration_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_acceleration_valid.path[0].value_valid.acceleration_valid:1
TEST.EXPECTED:path_float32.pathf_get_acceleration_valid.return:true
TEST.END

-- Subprogram: pathf_get_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_coordinate.path:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_coordinate.path:<<null>>
TEST.END

-- Subprogram: pathf_get_curvature_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_curvature_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_curvature_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_curvature_valid.path[0].value_valid.curvature_valid:1
TEST.EXPECTED:path_float32.pathf_get_curvature_valid.return:true
TEST.END

-- Subprogram: pathf_get_distance_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_distance_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_distance_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_distance_valid.path[0].value_valid.distance_valid:1
TEST.EXPECTED:path_float32.pathf_get_distance_valid.return:true
TEST.END

-- Subprogram: pathf_get_planning_state

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_planning_state
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_planning_state.path:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_planning_state
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_planning_state.path:<<null>>
TEST.END

-- Subprogram: pathf_get_point

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point.index:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point.output_point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point.path:<<null>>
TEST.VALUE:path_float32.pathf_get_point.index:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point.output_point:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (path->point_num <= (50)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_get_point.path 'equal to' and 'not equal to' same value in branches 1/2
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point.path[0].point_num:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point.index:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point.output_point:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (path->point_num <= (50)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_get_point.path 'equal to' and 'not equal to' same value in branches 1/2
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_get_point.index:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point.output_point:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (path != (void *)0) ==> FALSE
      (2) if (path->point_num <= (50)) ==> FALSE
      (3) if (index < path->point_num) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_get_point.path 'equal to' and 'not equal to' same value in branches 1/3
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_get_point.index:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point.output_point:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (path != (void *)0) ==> FALSE
      (2) if (path->point_num <= (50)) ==> FALSE
      (3) if (index < path->point_num) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_get_point.path 'equal to' and 'not equal to' same value in branches 1/3
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point.path[0].point_num:51
TEST.VALUE:path_float32.pathf_get_point.index:<<MAX>>
TEST.VALUE:path_float32.pathf_get_point.output_point:<<malloc 1>>
TEST.END

-- Subprogram: pathf_get_point_list_size

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point_list_size
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point_list_size.path:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point_list_size
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point_list_size.path:<<null>>
TEST.END

-- Subprogram: pathf_get_point_unsafe

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point_unsafe
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point_unsafe.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point_unsafe.index:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point_unsafe
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point_unsafe.path:<<null>>
TEST.VALUE:path_float32.pathf_get_point_unsafe.index:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point_unsafe
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (index < path->point_num) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_get_point_unsafe.path 'equal to' and 'not equal to' same value in branches 1/2
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point_unsafe.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point_unsafe.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_get_point_unsafe.index:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_point_unsafe
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (index < path->point_num) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_get_point_unsafe.path 'equal to' and 'not equal to' same value in branches 1/2
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_point_unsafe.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_point_unsafe.path[0].point_num:<<MIN>>
TEST.VALUE:path_float32.pathf_get_point_unsafe.index:<<MAX>>
TEST.END

-- Subprogram: pathf_get_position_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_position_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_position_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_position_valid.path[0].value_valid.position_valid:1
TEST.EXPECTED:path_float32.pathf_get_position_valid.return:true
TEST.END

-- Subprogram: pathf_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_serialized_size.path:<<malloc 1>>
TEST.EXPECTED:path_float32.pathf_get_serialized_size.return:16
TEST.END

-- Subprogram: pathf_get_speed_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_speed_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_speed_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_speed_valid.path[0].value_valid.speed_valid:1
TEST.EXPECTED:path_float32.pathf_get_speed_valid.return:true
TEST.END

-- Subprogram: pathf_get_theata_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_theata_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_theata_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_theata_valid.path[0].value_valid.theata_valid:1
TEST.EXPECTED:path_float32.pathf_get_theata_valid.return:true
TEST.END

-- Subprogram: pathf_get_time_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_time_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_time_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_time_valid.path[0].value_valid.time_valid:1
TEST.EXPECTED:path_float32.pathf_get_time_valid.return:true
TEST.END

-- Subprogram: pathf_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_timestamp.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_get_timestamp.path[0].stamp.sec:1
TEST.VALUE:path_float32.pathf_get_timestamp.path[0].stamp.nsec:2
TEST.EXPECTED:path_float32.pathf_get_timestamp.return[0].sec:1
TEST.EXPECTED:path_float32.pathf_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_get_timestamp.path:<<null>>
TEST.END

-- Subprogram: pathf_init_default

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_init_default.path:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_init_default
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_init_default.path:<<null>>
TEST.END

-- Subprogram: pathf_push_back_point

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_push_back_point
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_push_back_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_push_back_point.point:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_push_back_point
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_push_back_point.path:<<null>>
TEST.VALUE:path_float32.pathf_push_back_point.point:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_push_back_point
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (point != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_push_back_point.path:<<null>>
TEST.VALUE:path_float32.pathf_push_back_point.point:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_push_back_point
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (point != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_push_back_point.path:<<null>>
TEST.VALUE:path_float32.pathf_push_back_point.point:<<null>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_push_back_point
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (path != (void *)0) ==> FALSE
      (2) if (point != (void *)0) ==> FALSE
      (3) if (path->point_num >= (50)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_push_back_point.path 'equal to' and 'not equal to' same value in branches 1/3
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_push_back_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_push_back_point.path[0].point_num:<<MAX>>
TEST.VALUE:path_float32.pathf_push_back_point.point:<<null>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_push_back_point
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (path != (void *)0) ==> FALSE
      (2) if (point != (void *)0) ==> FALSE
      (3) if (path->point_num >= (50)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_push_back_point.path 'equal to' and 'not equal to' same value in branches 1/3
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_push_back_point.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_push_back_point.path[0].point_num:<<MIN>>
TEST.VALUE:path_float32.pathf_push_back_point.point:<<null>>
TEST.END

-- Subprogram: pathf_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_serialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer:<<malloc 1>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < path->point_num) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_serialize.path 'equal to' and 'not equal to' same value in branches 1/4
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_serialize.path[0].point_num:1
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < path->point_num) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable path_float32.pathf_serialize.path 'equal to' and 'not equal to' same value in branches 1/4
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_serialize.path[0].point_num:0
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < path->point_num) ==> TRUE
      (5) if (serialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set serialized_size due to assignment
      Cannot set local variable expected_size in branch 5
      Conflict: Trying to set variable path_float32.pathf_serialize.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_serialize.path 'equal to' and 'not equal to' same value in branches 1/5
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.path[0].point_num:1
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_serialize
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) if (path != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (expected_size > buffer_size) ==> FALSE
      (4) for (idx < path->point_num) ==> TRUE
      (5) if (serialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set serialized_size due to assignment
      Cannot set local variable expected_size in branch 5
      Conflict: Trying to set variable path_float32.pathf_serialize.path 'equal to' and 'not equal to' same value in branches 1/4
      Conflict: Trying to set variable path_float32.pathf_serialize.path 'equal to' and 'not equal to' same value in branches 1/5
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_serialize.path:<<null>>
TEST.VALUE:path_float32.pathf_serialize.path[0].point_num:1
TEST.VALUE:path_float32.pathf_serialize.buffer:<<null>>
TEST.VALUE:path_float32.pathf_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: pathf_set_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_coordinate.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_coordinate.path:<<null>>
TEST.VALUE:path_float32.pathf_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: pathf_set_path_value_valid

-- Test Case: BASIS-PATH-001
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (8) case value ==> default
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:65
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) case value ==> PATH_VALID_POSITION
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_POSITION
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-003
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-003
TEST.BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (2) case value ==> PATH_VALID_THETA
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_THETA
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-004
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-004
TEST.BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (3) case value ==> PATH_VALID_CURVATURE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_CURVATURE
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-005
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-005
TEST.BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (4) case value ==> PATH_VALID_SPEED
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_SPEED
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-006
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-006
TEST.BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (5) case value ==> PATH_VALID_ACCELERATION
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_ACCELERATION
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-007
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-007
TEST.BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (6) case value ==> PATH_VALID_DISTANCE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_DISTANCE
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-008
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_path_value_valid
TEST.NEW
TEST.NAME:BASIS-PATH-008
TEST.BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (7) case value ==> PATH_VALID_TIME
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_path_value_valid.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_path_value_valid.value:PATH_VALID_TIME
TEST.VALUE:path_float32.pathf_set_path_value_valid.is_valid:<<MIN>>
TEST.END

-- Subprogram: pathf_set_planning_state

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_planning_state
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_planning_state.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_planning_state.planning_state:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_planning_state
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_planning_state.path:<<null>>
TEST.VALUE:path_float32.pathf_set_planning_state.planning_state:<<MIN>>
TEST.END

-- Subprogram: pathf_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (path != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_timestamp.path:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:path_float32.pathf_set_timestamp.stamp[0].sec:1
TEST.VALUE:path_float32.pathf_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:path_float32.pathf_set_timestamp.path[0].stamp.sec:1
TEST.EXPECTED:path_float32.pathf_set_timestamp.path[0].stamp.nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (path != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_timestamp.path:<<null>>
TEST.VALUE:path_float32.pathf_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (path != (void *)0) ==> FALSE
      (2) if (stamp != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_timestamp.path:<<null>>
TEST.VALUE:path_float32.pathf_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:path_float32
TEST.SUBPROGRAM:pathf_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (path != (void *)0) ==> FALSE
      (2) if (stamp != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:path_float32.pathf_set_timestamp.path:<<null>>
TEST.VALUE:path_float32.pathf_set_timestamp.stamp:<<null>>
TEST.END
