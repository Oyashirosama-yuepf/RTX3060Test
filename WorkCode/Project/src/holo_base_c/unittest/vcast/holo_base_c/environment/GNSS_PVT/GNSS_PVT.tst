-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : GNSS_PVT
-- Unit(s) Under Test: gnss_pvt
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

-- Unit: gnss_pvt

-- Subprogram: gnss_pvt_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_deserialize
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
      Cannot set local variable expected_size in branch 4
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: gnss_pvt_get_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_coordinate
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_coordinate.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_coordinate.self[0].coordinate:5
TEST.EXPECTED:gnss_pvt.gnss_pvt_get_coordinate.return:5
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_coordinate
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_coordinate.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_height

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_height.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_height.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_height.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_height.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_height_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_height_cov.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_height_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_height_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_height_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_height_cov.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_latitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_latitude_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude_cov.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_latitude_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_latitude_cov.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_longitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude.self[0].longitude:5.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_get_longitude.return:5.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_longitude_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude_cov.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_longitude_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_longitude_cov.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_mode

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_mode
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_mode.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_mode
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_mode.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_position

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.position:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.position:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.position:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.position:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> FALSE
      (3) if point3d_is_valid(position) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.position:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_valid(self) ==> FALSE
      (3) if point3d_is_valid(position) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position.position:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_get_position_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position_cov
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.position_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position_cov
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.position_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.position_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.position_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position_cov
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> FALSE
      (3) if point3d_is_valid(position_cov) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.position_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_position_cov
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_position_cov_valid(self) ==> FALSE
      (3) if point3d_is_valid(position_cov) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_position_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_position_cov.position_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_serialized_size.self:<<malloc 1>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_get_serialized_size.return:112
TEST.END

-- Subprogram: gnss_pvt_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_timestamp
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_timestamp.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_timestamp.self[0].stamp.sec:1
TEST.VALUE:gnss_pvt.gnss_pvt_get_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:gnss_pvt.gnss_pvt_get_timestamp.return[0].sec:1
TEST.EXPECTED:gnss_pvt.gnss_pvt_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_timestamp
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_timestamp.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_velocity

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> FALSE
      (3) if point3d_is_valid(velocity) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.velocity:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> FALSE
      (3) if point3d_is_valid(velocity) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity.velocity:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_get_velocity_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_cov
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (self != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_cov
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (self != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_cov
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> FALSE
      (3) if point3d_is_valid(velocity_cov) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.velocity_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_cov
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> FALSE
      (3) if point3d_is_valid(velocity_cov) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_cov.velocity_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_get_velocity_east

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_velocity_east_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east_cov.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_east_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_east_cov.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_velocity_north

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_velocity_north_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north_cov.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_north_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_north_cov.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_velocity_up

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_get_velocity_up_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up_cov.self:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up_cov.self:<<null>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_get_velocity_up_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if gnss_pvt_is_velocity_cov_valid(self) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function gnss_pvt_is_velocity_cov_valid in branch 2
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_get_velocity_up_cov.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_init

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_init
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
TEST.VALUE:gnss_pvt.gnss_pvt_init.self:<<malloc 1>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].stamp.sec:0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].stamp.nsec:0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].coordinate:0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].status:0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].longitude:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].latitude:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].height:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].velocity_east:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].velocity_north:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].velocity_up:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].longitude_cov:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].latitude_cov:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].height_cov:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].velocity_east_cov:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].velocity_north_cov:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.self[0].velocity_up_cov:0.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_init.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_init
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
TEST.VALUE:gnss_pvt.gnss_pvt_init.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_is_position_cov_valid

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_position_cov_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_position_cov_valid.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_is_position_cov_valid.self[0].status:16#4#
TEST.EXPECTED:gnss_pvt.gnss_pvt_is_position_cov_valid.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_position_cov_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_position_cov_valid.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_is_position_valid

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_position_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_position_valid.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_is_position_valid.self[0].status:1
TEST.EXPECTED:gnss_pvt.gnss_pvt_is_position_valid.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_position_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_position_valid.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_is_velocity_cov_valid

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_velocity_cov_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_velocity_cov_valid.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_is_velocity_cov_valid.self[0].status:16#8#
TEST.EXPECTED:gnss_pvt.gnss_pvt_is_velocity_cov_valid.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_velocity_cov_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_velocity_cov_valid.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_is_velocity_valid

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_velocity_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_velocity_valid.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_is_velocity_valid.self[0].status:2
TEST.EXPECTED:gnss_pvt.gnss_pvt_is_velocity_valid.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_is_velocity_valid
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
TEST.VALUE:gnss_pvt.gnss_pvt_is_velocity_valid.self:<<null>>
TEST.END

-- Subprogram: gnss_pvt_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_serialize
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
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: gnss_pvt_set_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_coordinate
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_coordinate.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_coordinate.coordinate:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_coordinate.self[0].coordinate:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_coordinate
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_coordinate.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_height

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_height
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_height.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_height.height:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_height.self[0].height:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_height.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_height
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_height.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_height.height:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_height_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_height_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_height_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_height_cov.height_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_height_cov.self[0].height_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_height_cov.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_height_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_height_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_height_cov.height_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_latitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_latitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude.latitude:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_latitude.self[0].latitude:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_latitude.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_latitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude.latitude:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_latitude_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_latitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude_cov.latitude_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_latitude_cov.self[0].latitude_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_latitude_cov.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_latitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_latitude_cov.latitude_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_longitude

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_longitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude.longitude:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_longitude.self[0].longitude:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_longitude
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude.longitude:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_longitude_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_longitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude_cov.longitude_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_longitude_cov.self[0].longitude_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_longitude_cov.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_longitude_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_longitude_cov.longitude_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_mode

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_mode
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_mode.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_mode.mode:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_mode
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_mode.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_mode.mode:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_position

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position[0].x:1.0
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position[0].y:2.0
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position[0].z:3.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position.self[0].longitude:1.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position.self[0].latitude:2.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position.self[0].height:3.0
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(position) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(position) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position.position:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_set_position_by_values

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.longitude:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.latitude:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.height:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_by_values.self[0].longitude:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_by_values.self[0].latitude:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_by_values.self[0].height:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_by_values.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.longitude:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.latitude:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_by_values.height:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_position_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.position_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.position_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(position_cov) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.position_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(position_cov) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov.position_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_set_position_cov_by_values

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_cov_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.longitude_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.latitude_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.height_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_cov_by_values.self[0].longitude_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_cov_by_values.self[0].latitude_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_cov_by_values.self[0].height_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_position_cov_by_values.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_position_cov_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.longitude_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.latitude_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_position_cov_by_values.height_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_timestamp
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.timestamp:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.timestamp[0].sec:1
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.timestamp[0].nsec:2
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_timestamp.self[0].stamp.sec:1
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_timestamp.self[0].stamp.nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_timestamp
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.timestamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if (timestamp != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.timestamp:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_timestamp
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if (timestamp != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_timestamp.timestamp:<<null>>
TEST.END

-- Subprogram: gnss_pvt_set_valid_flags

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_valid_flags
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.position:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.velocity:true
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.position_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.velocity_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_valid_flags.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_valid_flags
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.position:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.velocity:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.position_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_valid_flags.velocity_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.velocity:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(velocity) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.velocity:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(velocity) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity.velocity:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_set_velocity_by_values

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.velocity_east:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.velocity_north:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.velocity_up:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_by_values.self[0].velocity_east:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_by_values.self[0].velocity_north:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_by_values.self[0].velocity_up:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_by_values.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.velocity_east:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.velocity_north:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_by_values.velocity_up:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.velocity_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_cov
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(velocity_cov) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.velocity_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:true
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_cov
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (self != (void *)0) ==> FALSE
      (2) if point3d_is_valid(velocity_cov) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov.velocity_cov:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.point3d_is_valid.return:false
TEST.END

-- Subprogram: gnss_pvt_set_velocity_cov_by_values

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_cov_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.velocity_east_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.velocity_north_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.velocity_up_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.self[0].velocity_east_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.self[0].velocity_north_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.self[0].velocity_up_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_cov_by_values
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.velocity_east_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.velocity_north_cov:<<MIN>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_cov_by_values.velocity_up_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_east

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_east
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east.velocity_east:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_east.self[0].velocity_east:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_east.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_east
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east.velocity_east:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_east_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_east_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east_cov.velocity_east_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_east_cov.self[0].velocity_east_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_east_cov.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_east_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_east_cov.velocity_east_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_north

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_north
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north.velocity_north:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_north.self[0].velocity_north:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_north.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_north
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north.velocity_north:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_north_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_north_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north_cov.velocity_north_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_north_cov.self[0].velocity_north_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_north_cov.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_north_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_north_cov.velocity_north_cov:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_up

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_up
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up.velocity_up:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_up.self[0].velocity_up:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_up.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_up
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up.velocity_up:<<MIN>>
TEST.END

-- Subprogram: gnss_pvt_set_velocity_up_cov

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_up_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up_cov.self:<<malloc 1>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up_cov.velocity_up_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_up_cov.self[0].velocity_up_cov:<<MIN>>
TEST.EXPECTED:gnss_pvt.gnss_pvt_set_velocity_up_cov.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:gnss_pvt
TEST.SUBPROGRAM:gnss_pvt_set_velocity_up_cov
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
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up_cov.self:<<null>>
TEST.VALUE:gnss_pvt.gnss_pvt_set_velocity_up_cov.velocity_up_cov:<<MIN>>
TEST.END
