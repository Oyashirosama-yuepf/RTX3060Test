-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : ODOMETRY_FLOAT32
-- Unit(s) Under Test: odometry_float32
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

-- Unit: odometry_float32

-- Subprogram: deserialize_data

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < 3U * 3U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < 3U * 3U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> FALSE
      (5) for (i < 3U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> FALSE
      (5) for (i < 3U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:odometry_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Subprogram: odometryf_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: odometryf_deserialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set const variable TEST.VALUE:      Cannot set local variable expected_size in branch 4
:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set const variable TEST.VALUE:      Cannot set local variable expected_size in branch 4
:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: odometryf_deserialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set const variable TEST.VALUE:      Cannot set local variable expected_size in branch 4
:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (deserialized_size == expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set deserialized_size due to assignment
      Cannot set const variable TEST.VALUE:      Cannot set local variable expected_size in branch 4
:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: odometryf_get_child_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_child_coordinate.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_child_coordinate.self[0].child_coordinate:5
TEST.EXPECTED:odometry_float32.odometryf_get_child_coordinate.return:5
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_child_coordinate.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_coordinate.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_coordinate.self[0].parent_coordinate:5
TEST.EXPECTED:odometry_float32.odometryf_get_coordinate.return:5
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_coordinate.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_linear_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_linear_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self[0].linear_acceleration.rows:1
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self[0].linear_acceleration.cols:2
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self[0].linear_acceleration.size:3
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self[0].linear_acceleration.pitchx:4
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self[0].linear_acceleration.pitchy:5
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self[0].linear_acceleration.capacity:6
TEST.EXPECTED:odometry_float32.odometryf_get_linear_acceleration.return[0].rows:1
TEST.EXPECTED:odometry_float32.odometryf_get_linear_acceleration.return[0].cols:2
TEST.EXPECTED:odometry_float32.odometryf_get_linear_acceleration.return[0].size:3
TEST.EXPECTED:odometry_float32.odometryf_get_linear_acceleration.return[0].pitchx:4
TEST.EXPECTED:odometry_float32.odometryf_get_linear_acceleration.return[0].pitchy:5
TEST.EXPECTED:odometry_float32.odometryf_get_linear_acceleration.return[0].capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_linear_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_linear_acceleration.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_linear_velocity_in_child_coord_orientation

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_linear_velocity_in_child_coord_orientation
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_linear_velocity_in_child_coord_orientation.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_linear_velocity_in_child_coord_orientation.out:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_linear_velocity_in_child_coord_orientation
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_linear_velocity_in_child_coord_orientation.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_get_linear_velocity_in_child_coord_orientation.out:<<malloc 1>>
TEST.END

-- Subprogram: odometryf_get_pose

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_pose
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_pose.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.rotation.m.rows:1
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.rotation.m.cols:2
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.rotation.m.size:3
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.rotation.m.pitchx:4
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.rotation.m.pitchy:5
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.rotation.m.capacity:6
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.translation.x:1.0
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.translation.y:2.0
TEST.VALUE:odometry_float32.odometryf_get_pose.self[0].pose.translation.z:3.0
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].rotation.m.rows:1
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].rotation.m.cols:2
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].rotation.m.size:3
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].rotation.m.pitchx:4
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].rotation.m.pitchy:5
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].rotation.m.capacity:6
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].translation.x:1.0
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].translation.y:2.0
TEST.EXPECTED:odometry_float32.odometryf_get_pose.return[0].translation.z:3.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_pose
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_pose.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_pose_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_pose_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self[0].pose_covariance.rows:1
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self[0].pose_covariance.cols:2
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self[0].pose_covariance.size:3
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self[0].pose_covariance.pitchx:4
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self[0].pose_covariance.pitchy:5
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self[0].pose_covariance.capacity:6
TEST.EXPECTED:odometry_float32.odometryf_get_pose_covariance.return[0].rows:1
TEST.EXPECTED:odometry_float32.odometryf_get_pose_covariance.return[0].cols:2
TEST.EXPECTED:odometry_float32.odometryf_get_pose_covariance.return[0].size:3
TEST.EXPECTED:odometry_float32.odometryf_get_pose_covariance.return[0].pitchx:4
TEST.EXPECTED:odometry_float32.odometryf_get_pose_covariance.return[0].pitchy:5
TEST.EXPECTED:odometry_float32.odometryf_get_pose_covariance.return[0].capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_pose_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_pose_covariance.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_serialized_size.self:<<malloc 1>>
TEST.EXPECTED:odometry_float32.odometryf_get_serialized_size.return:396
TEST.END

-- Subprogram: odometryf_get_serialized_size_4byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_serialized_size_4byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_serialized_size_4byte_aligned.self:<<malloc 1>>
TEST.EXPECTED:odometry_float32.odometryf_get_serialized_size_4byte_aligned.return:396
TEST.END

-- Subprogram: odometryf_get_serialized_size_8byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_serialized_size_8byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_serialized_size_8byte_aligned.self:<<malloc 1>>
TEST.EXPECTED:odometry_float32.odometryf_get_serialized_size_8byte_aligned.return:400
TEST.END

-- Subprogram: odometryf_get_source

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_source
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_source.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_source.self[0].source:ODOMETRY_SOURCE_IMU
TEST.EXPECTED:odometry_float32.odometryf_get_source.return:ODOMETRY_SOURCE_IMU
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_source
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_source.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_status

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_status
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_status.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_status.self[0].status:ODOMETRY_STATUS_SOLUTIONNOGOOD
TEST.EXPECTED:odometry_float32.odometryf_get_status.return:ODOMETRY_STATUS_SOLUTIONNOGOOD
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_status
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_status.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_timestamp.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_timestamp.self[0].stamp.sec:1
TEST.VALUE:odometry_float32.odometryf_get_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:odometry_float32.odometryf_get_timestamp.return[0].sec:1
TEST.EXPECTED:odometry_float32.odometryf_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_timestamp.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_translation

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_translation
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_translation.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_translation
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_translation.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_velocity

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_velocity
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_velocity.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_velocity.self[0].velocity.rows:1
TEST.VALUE:odometry_float32.odometryf_get_velocity.self[0].velocity.cols:2
TEST.VALUE:odometry_float32.odometryf_get_velocity.self[0].velocity.size:3
TEST.VALUE:odometry_float32.odometryf_get_velocity.self[0].velocity.pitchx:4
TEST.VALUE:odometry_float32.odometryf_get_velocity.self[0].velocity.pitchy:5
TEST.VALUE:odometry_float32.odometryf_get_velocity.self[0].velocity.capacity:6
TEST.EXPECTED:odometry_float32.odometryf_get_velocity.return[0].rows:1
TEST.EXPECTED:odometry_float32.odometryf_get_velocity.return[0].cols:2
TEST.EXPECTED:odometry_float32.odometryf_get_velocity.return[0].size:3
TEST.EXPECTED:odometry_float32.odometryf_get_velocity.return[0].pitchx:4
TEST.EXPECTED:odometry_float32.odometryf_get_velocity.return[0].pitchy:5
TEST.EXPECTED:odometry_float32.odometryf_get_velocity.return[0].capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_velocity
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_velocity.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_velocity_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_velocity_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self[0].velocity_covariance.rows:1
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self[0].velocity_covariance.cols:2
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self[0].velocity_covariance.size:3
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self[0].velocity_covariance.pitchx:4
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self[0].velocity_covariance.pitchy:5
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self[0].velocity_covariance.capacity:6
TEST.EXPECTED:odometry_float32.odometryf_get_velocity_covariance.return[0].rows:1
TEST.EXPECTED:odometry_float32.odometryf_get_velocity_covariance.return[0].cols:2
TEST.EXPECTED:odometry_float32.odometryf_get_velocity_covariance.return[0].size:3
TEST.EXPECTED:odometry_float32.odometryf_get_velocity_covariance.return[0].pitchx:4
TEST.EXPECTED:odometry_float32.odometryf_get_velocity_covariance.return[0].pitchy:5
TEST.EXPECTED:odometry_float32.odometryf_get_velocity_covariance.return[0].capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_velocity_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_velocity_covariance.self:<<null>>
TEST.END

-- Subprogram: odometryf_get_yaw

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_yaw
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_yaw.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_get_yaw
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_get_yaw.self:<<null>>
TEST.END

-- Subprogram: odometryf_init

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_init
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_init.self:<<malloc 1>>
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].stamp.sec:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].stamp.nsec:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].parent_coordinate:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].child_coordinate:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].source:ODOMETRY_SOURCE_UNKNOWN
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].status:ODOMETRY_STATUS_ALLGOOD
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.rotation.m.rows:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.rotation.m.cols:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.rotation.m.size:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.rotation.m.pitchx:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.rotation.m.pitchy:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.rotation.m.capacity:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.translation.x:0.0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.translation.y:0.0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose.translation.z:0.0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity.rows:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity.cols:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity.size:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity.pitchx:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity.pitchy:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity.capacity:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose_covariance.rows:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose_covariance.cols:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose_covariance.size:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose_covariance.pitchx:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose_covariance.pitchy:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].pose_covariance.capacity:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity_covariance.rows:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity_covariance.cols:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity_covariance.size:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity_covariance.pitchx:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity_covariance.pitchy:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].velocity_covariance.capacity:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].linear_acceleration.rows:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].linear_acceleration.cols:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].linear_acceleration.size:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].linear_acceleration.pitchx:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].linear_acceleration.pitchy:0
TEST.EXPECTED:odometry_float32.odometryf_init.self[0].linear_acceleration.capacity:0
TEST.EXPECTED:odometry_float32.odometryf_init.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_init
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_init.self:<<null>>
TEST.END

-- Subprogram: odometryf_init_from_odometryf

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_init_from_odometryf
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.other:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_init_from_odometryf
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.other:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_init_from_odometryf
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (other != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.other:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_init_from_odometryf
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (other != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_init_from_odometryf.other:<<null>>
TEST.END

-- Subprogram: odometryf_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: odometryf_serialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: odometryf_serialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:odometry_float32.odometryf_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: odometryf_set_child_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_child_coordinate.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_child_coordinate.coordinate:<<MIN>>
TEST.EXPECTED:odometry_float32.odometryf_set_child_coordinate.self[0].child_coordinate:<<MIN>>
TEST.EXPECTED:odometry_float32.odometryf_set_child_coordinate.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_child_coordinate.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_child_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: odometryf_set_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_coordinate.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_coordinate.coordinate:<<MIN>>
TEST.EXPECTED:odometry_float32.odometryf_set_coordinate.self[0].parent_coordinate:<<MIN>>
TEST.EXPECTED:odometry_float32.odometryf_set_coordinate.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_coordinate.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: odometryf_set_linear_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_linear_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_linear_acceleration.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_linear_acceleration.linear_acceleration:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_linear_acceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_linear_acceleration.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_linear_acceleration.linear_acceleration:<<malloc 1>>
TEST.END

-- Subprogram: odometryf_set_pose

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_pose
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_pose.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_pose.pose:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.rows:1
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.cols:2
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.size:3
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.pitchx:4
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.pitchy:5
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.capacity:2
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.base:<<malloc 2>>
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.base[0]:1.0
TEST.VALUE:odometry_float32.odometryf_set_pose.pose[0].rotation.m.base[1]:2.0
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.rows:1
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.cols:2
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.size:3
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.pitchx:4
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.pitchy:5
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.capacity:2
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.base[0]:1.0
TEST.EXPECTED:odometry_float32.odometryf_set_pose.self[0].pose.rotation.m.base[1]:2.0
TEST.EXPECTED:odometry_float32.odometryf_set_pose.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_pose
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_pose.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_pose.pose:<<malloc 1>>
TEST.END

-- Subprogram: odometryf_set_pose_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_pose_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_pose_covariance.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_pose_covariance.pose_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_pose_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_pose_covariance.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_pose_covariance.pose_cov:<<malloc 1>>
TEST.END

-- Subprogram: odometryf_set_source

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_source
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_source.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_source.source:ODOMETRY_SOURCE_HD_MAP
TEST.EXPECTED:odometry_float32.odometryf_set_source.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_source
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_source.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_source.source:<<MIN>>
TEST.END

-- Subprogram: odometryf_set_status

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_status
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_status.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_status.status:ODOMETRY_STATUS_LINEARACCELERATIONINACTIVE
TEST.EXPECTED:odometry_float32.odometryf_set_status.self[0].status:ODOMETRY_STATUS_LINEARACCELERATIONINACTIVE
TEST.EXPECTED:odometry_float32.odometryf_set_status.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_status
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_status.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_status.status:<<MIN>>
TEST.END

-- Subprogram: odometryf_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_timestamp.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_timestamp.stamp[0].sec:1
TEST.VALUE:odometry_float32.odometryf_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:odometry_float32.odometryf_set_timestamp.self[0].stamp.sec:1
TEST.EXPECTED:odometry_float32.odometryf_set_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:odometry_float32.odometryf_set_timestamp.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_timestamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_timestamp.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Subprogram: odometryf_set_velocity

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_velocity
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_velocity.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_velocity
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_velocity.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_velocity.velocity:<<malloc 1>>
TEST.END

-- Subprogram: odometryf_set_velocity_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_velocity_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_velocity_covariance.self:<<malloc 1>>
TEST.VALUE:odometry_float32.odometryf_set_velocity_covariance.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:odometryf_set_velocity_covariance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odometry_float32.odometryf_set_velocity_covariance.self:<<null>>
TEST.VALUE:odometry_float32.odometryf_set_velocity_covariance.velocity_cov:<<malloc 1>>
TEST.END

-- Subprogram: serialize_data

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < 3U * 3U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < 3U * 3U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 4
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> FALSE
      (5) for (i < 3U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:odometry_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (1) for (i < 3U * 3U) ==> FALSE
      (2) for (i < 6U) ==> FALSE
      (3) for (i < 6U * 6U) ==> FALSE
      (4) for (i < 6U * 6U) ==> FALSE
      (5) for (i < 3U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 5
      Conflict: Unable to control expression-to-expression comparison in branch 1
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 3
      Conflict: Unable to control expression-to-expression comparison in branch 4
TEST.END_NOTES:
TEST.VALUE:odometry_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:odometry_float32.serialize_data.buffer_size:<<MIN>>
TEST.END
