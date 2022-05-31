-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : GNSS_POSITION
-- Unit(s) Under Test: gnss_position
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

-- Unit: gnss_position

-- Subprogram: gnss_position_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (position != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize.position:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (position != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: gnss_position_deserialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (position != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (position != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (position != (void *)0) ==> FALSE
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
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (position != (void *)0) ==> FALSE
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
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: gnss_position_deserialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (position != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (position != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (position != (void *)0) ==> FALSE
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
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_deserialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (position != (void *)0) ==> FALSE
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
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: gnss_position_get_altitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_altitude
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
TEST.VALUE:gnss_position.gnss_position_get_altitude.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_altitude.self[0].altitude:5.0
TEST.EXPECTED:gnss_position.gnss_position_get_altitude.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_altitude
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
TEST.VALUE:gnss_position.gnss_position_get_altitude.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_altitude_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_altitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_get_altitude_covariance.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_altitude_covariance.self[0].altitude_cov:5.0
TEST.EXPECTED:gnss_position.gnss_position_get_altitude_covariance.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_altitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_get_altitude_covariance.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_coordinate
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
TEST.VALUE:gnss_position.gnss_position_get_coordinate.self:<<malloc 1>>
TEST.EXPECTED:gnss_position.gnss_position_get_coordinate.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_coordinate
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
TEST.VALUE:gnss_position.gnss_position_get_coordinate.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_latitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_latitude
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
TEST.VALUE:gnss_position.gnss_position_get_latitude.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_latitude.self[0].latitude:5.0
TEST.EXPECTED:gnss_position.gnss_position_get_latitude.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_latitude
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
TEST.VALUE:gnss_position.gnss_position_get_latitude.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_latitude_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_latitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_get_latitude_covariance.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_latitude_covariance.self[0].latitude_cov:5.0
TEST.EXPECTED:gnss_position.gnss_position_get_latitude_covariance.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_latitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_get_latitude_covariance.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_longitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_longitude
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
TEST.VALUE:gnss_position.gnss_position_get_longitude.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_longitude.self[0].longitude:5.0
TEST.EXPECTED:gnss_position.gnss_position_get_longitude.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_longitude
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
TEST.VALUE:gnss_position.gnss_position_get_longitude.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_longitude_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_longitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_get_longitude_covariance.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_longitude_covariance.self[0].longitude_cov:5.0
TEST.EXPECTED:gnss_position.gnss_position_get_longitude_covariance.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_longitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_get_longitude_covariance.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_get_serialized_size.position:<<malloc 1>>
TEST.EXPECTED:gnss_position.gnss_position_get_serialized_size.return:64
TEST.END

-- Subprogram: gnss_position_get_serialized_size_4byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_serialized_size_4byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_get_serialized_size_4byte_aligned.position:<<malloc 1>>
TEST.EXPECTED:gnss_position.gnss_position_get_serialized_size_4byte_aligned.return:64
TEST.END

-- Subprogram: gnss_position_get_serialized_size_8byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_serialized_size_8byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_get_serialized_size_8byte_aligned.position:<<malloc 1>>
TEST.EXPECTED:gnss_position.gnss_position_get_serialized_size_8byte_aligned.return:64
TEST.END

-- Subprogram: gnss_position_get_status

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_status
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
TEST.VALUE:gnss_position.gnss_position_get_status.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_status.self[0].status:GNSS_POSITION_STATUS_UNDEFINEDERROR
TEST.EXPECTED:gnss_position.gnss_position_get_status.return:GNSS_POSITION_STATUS_UNDEFINEDERROR
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_status
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
TEST.VALUE:gnss_position.gnss_position_get_status.self:<<null>>
TEST.END

-- Subprogram: gnss_position_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_timestamp
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
TEST.VALUE:gnss_position.gnss_position_get_timestamp.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_get_timestamp.self[0].stamp.sec:1
TEST.VALUE:gnss_position.gnss_position_get_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:gnss_position.gnss_position_get_timestamp.return[0].sec:1
TEST.EXPECTED:gnss_position.gnss_position_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_get_timestamp
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
TEST.VALUE:gnss_position.gnss_position_get_timestamp.self:<<null>>
TEST.END

-- Subprogram: gnss_position_init

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_init
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
TEST.VALUE:gnss_position.gnss_position_init.self:<<malloc 1>>
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].stamp.sec:0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].stamp.nsec:0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].coordinate:0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].status:GNSS_POSITION_STATUS_ALLGOOD
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].latitude:0.0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].longitude:0.0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].altitude:0.0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].latitude_cov:0.0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].longitude_cov:0.0
TEST.EXPECTED:gnss_position.gnss_position_init.self[0].altitude_cov:0.0
TEST.EXPECTED:gnss_position.gnss_position_init.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_init
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
TEST.VALUE:gnss_position.gnss_position_init.self:<<null>>
TEST.END

-- Subprogram: gnss_position_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (position != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize.position:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (position != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: gnss_position_serialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (position != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (position != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_4byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: gnss_position_serialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (position != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (position != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_serialize_8byte_aligned
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (position != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == serialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set serialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.position:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:gnss_position.gnss_position_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: gnss_position_set_altitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_altitude
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
TEST.VALUE:gnss_position.gnss_position_set_altitude.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_altitude.alt:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_altitude.self[0].altitude:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_altitude
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
TEST.VALUE:gnss_position.gnss_position_set_altitude.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_altitude.alt:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_altitude_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_altitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_set_altitude_covariance.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_altitude_covariance.alt_cov:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_altitude_covariance.self[0].altitude_cov:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_altitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_set_altitude_covariance.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_altitude_covariance.alt_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_coordinate
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
TEST.VALUE:gnss_position.gnss_position_set_coordinate.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_coordinate.coordinate:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_coordinate.self[0].coordinate:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_coordinate
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
TEST.VALUE:gnss_position.gnss_position_set_coordinate.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_latitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_latitude
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
TEST.VALUE:gnss_position.gnss_position_set_latitude.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_latitude.lat:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_latitude.self[0].latitude:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_latitude
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
TEST.VALUE:gnss_position.gnss_position_set_latitude.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_latitude.lat:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_latitude_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_latitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_set_latitude_covariance.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_latitude_covariance.lat_cov:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_latitude_covariance.self[0].latitude_cov:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_latitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_set_latitude_covariance.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_latitude_covariance.lat_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_longitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_longitude
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
TEST.VALUE:gnss_position.gnss_position_set_longitude.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_longitude.lon:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_longitude.self[0].longitude:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_longitude
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
TEST.VALUE:gnss_position.gnss_position_set_longitude.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_longitude.lon:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_longitude_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_longitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_set_longitude_covariance.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_longitude_covariance.lon_cov:<<MIN>>
TEST.EXPECTED:gnss_position.gnss_position_set_longitude_covariance.self[0].longitude_cov:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_longitude_covariance
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
TEST.VALUE:gnss_position.gnss_position_set_longitude_covariance.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_longitude_covariance.lon_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_status

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_status
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
TEST.VALUE:gnss_position.gnss_position_set_status.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_status.status:GNSS_POSITION_STATUS_UNDEFINEDERROR
TEST.EXPECTED:gnss_position.gnss_position_set_status.self[0].status:GNSS_POSITION_STATUS_UNDEFINEDERROR
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_status
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
TEST.VALUE:gnss_position.gnss_position_set_status.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_status.status:<<MIN>>
TEST.END

-- Subprogram: gnss_position_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_timestamp
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
TEST.VALUE:gnss_position.gnss_position_set_timestamp.self:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:gnss_position.gnss_position_set_timestamp.stamp[0].sec:1
TEST.VALUE:gnss_position.gnss_position_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:gnss_position.gnss_position_set_timestamp.self[0].stamp.sec:1
TEST.EXPECTED:gnss_position.gnss_position_set_timestamp.self[0].stamp.nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_position
TEST.SUBPROGRAM:gnss_position_set_timestamp
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
TEST.VALUE:gnss_position.gnss_position_set_timestamp.self:<<null>>
TEST.VALUE:gnss_position.gnss_position_set_timestamp.stamp:<<malloc 1>>
TEST.END
