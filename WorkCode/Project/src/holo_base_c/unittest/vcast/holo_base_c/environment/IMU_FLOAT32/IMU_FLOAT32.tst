-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : IMU_FLOAT32
-- Unit(s) Under Test: imu_float32
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

-- Unit: imu_float32

-- Subprogram: deserialize_data

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < 3) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < 3) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (i < 3) ==> FALSE
      (2) for (i < 3) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:deserialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (i < 3) ==> FALSE
      (2) for (i < 3) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.deserialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.deserialize_data.buffer_size:<<MIN>>
TEST.END

-- Subprogram: imuf_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize
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
TEST.VALUE:imu_float32.imuf_deserialize.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize
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
TEST.VALUE:imu_float32.imuf_deserialize.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize
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
TEST.VALUE:imu_float32.imuf_deserialize.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize
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
TEST.VALUE:imu_float32.imuf_deserialize.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: imuf_deserialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: imuf_deserialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_deserialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_deserialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: imuf_get_angular_velocity

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity
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
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self[0].angular_velocity.rows:1
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self[0].angular_velocity.cols:2
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self[0].angular_velocity.size:3
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self[0].angular_velocity.pitchx:4
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self[0].angular_velocity.pitchy:5
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self[0].angular_velocity.capacity:6
TEST.EXPECTED:imu_float32.imuf_get_angular_velocity.return[0].rows:1
TEST.EXPECTED:imu_float32.imuf_get_angular_velocity.return[0].cols:2
TEST.EXPECTED:imu_float32.imuf_get_angular_velocity.return[0].size:3
TEST.EXPECTED:imu_float32.imuf_get_angular_velocity.return[0].pitchx:4
TEST.EXPECTED:imu_float32.imuf_get_angular_velocity.return[0].pitchy:5
TEST.EXPECTED:imu_float32.imuf_get_angular_velocity.return[0].capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity
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
TEST.VALUE:imu_float32.imuf_get_angular_velocity.self:<<null>>
TEST.END

-- Subprogram: imuf_get_angular_velocity_value

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:3
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      (2) if (angle_rate_x != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      (2) if (angle_rate_x != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      (2) if (angle_rate_x != (void *)0) ==> FALSE
      (3) if (angle_rate_y != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      (2) if (angle_rate_x != (void *)0) ==> FALSE
      (3) if (angle_rate_y != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      (2) if (angle_rate_x != (void *)0) ==> FALSE
      (3) if (angle_rate_y != (void *)0) ==> FALSE
      (4) if (angle_rate_z != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_angular_velocity_value
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (3 == vectorf_get_size(&(self->angular_velocity))) ==> FALSE
      (2) if (angle_rate_x != (void *)0) ==> FALSE
      (3) if (angle_rate_y != (void *)0) ==> FALSE
      (4) if (angle_rate_z != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_y:<<null>>
TEST.VALUE:imu_float32.imuf_get_angular_velocity_value.angle_rate_z:<<null>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Subprogram: imuf_get_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_coordinate
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
TEST.VALUE:imu_float32.imuf_get_coordinate.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_coordinate.self[0].coordinate:1
TEST.EXPECTED:imu_float32.imuf_get_coordinate.return:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_coordinate
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
TEST.VALUE:imu_float32.imuf_get_coordinate.self:<<null>>
TEST.END

-- Subprogram: imuf_get_linear_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration
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
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self[0].linear_acceleration.rows:1
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self[0].linear_acceleration.cols:2
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self[0].linear_acceleration.size:3
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self[0].linear_acceleration.pitchx:4
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self[0].linear_acceleration.pitchy:5
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self[0].linear_acceleration.capacity:6
TEST.EXPECTED:imu_float32.imuf_get_linear_acceleration.return[0].rows:1
TEST.EXPECTED:imu_float32.imuf_get_linear_acceleration.return[0].cols:2
TEST.EXPECTED:imu_float32.imuf_get_linear_acceleration.return[0].size:3
TEST.EXPECTED:imu_float32.imuf_get_linear_acceleration.return[0].pitchx:4
TEST.EXPECTED:imu_float32.imuf_get_linear_acceleration.return[0].pitchy:5
TEST.EXPECTED:imu_float32.imuf_get_linear_acceleration.return[0].capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration
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
TEST.VALUE:imu_float32.imuf_get_linear_acceleration.self:<<null>>
TEST.END

-- Subprogram: imuf_get_linear_acceleration_value

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:3
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      (2) if (acc_x != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      (2) if (acc_x != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:6 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      (2) if (acc_x != (void *)0) ==> FALSE
      (3) if (acc_y != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:5 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      (2) if (acc_x != (void *)0) ==> FALSE
      (3) if (acc_y != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      (2) if (acc_x != (void *)0) ==> FALSE
      (3) if (acc_y != (void *)0) ==> FALSE
      (4) if (acc_z != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<malloc 1>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_linear_acceleration_value
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (3 == vectorf_get_size(&(self->linear_acceleration))) ==> FALSE
      (2) if (acc_x != (void *)0) ==> FALSE
      (3) if (acc_y != (void *)0) ==> FALSE
      (4) if (acc_z != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_x:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_y:<<null>>
TEST.VALUE:imu_float32.imuf_get_linear_acceleration_value.acc_z:<<null>>
TEST.VALUE:uut_prototype_stubs.vectorf_get_size.return:<<MIN>>
TEST.END

-- Subprogram: imuf_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_serialized_size.self:<<malloc 1>>
TEST.EXPECTED:imu_float32.imuf_get_serialized_size.return:40
TEST.END

-- Subprogram: imuf_get_serialized_size_4byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_serialized_size_4byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_serialized_size_4byte_aligned.self:<<malloc 1>>
TEST.EXPECTED:imu_float32.imuf_get_serialized_size_4byte_aligned.return:40
TEST.END

-- Subprogram: imuf_get_serialized_size_8byte_aligned

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_serialized_size_8byte_aligned
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_float32.imuf_get_serialized_size_8byte_aligned.self:<<malloc 1>>
TEST.EXPECTED:imu_float32.imuf_get_serialized_size_8byte_aligned.return:40
TEST.END

-- Subprogram: imuf_get_status

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_status
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
TEST.VALUE:imu_float32.imuf_get_status.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_status.self[0].status:IMU_STATUS_UNDEFINEDERROR
TEST.EXPECTED:imu_float32.imuf_get_status.return:IMU_STATUS_UNDEFINEDERROR
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_status
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
TEST.VALUE:imu_float32.imuf_get_status.self:<<null>>
TEST.END

-- Subprogram: imuf_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_timestamp
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
TEST.VALUE:imu_float32.imuf_get_timestamp.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_get_timestamp.self[0].stamp.sec:1
TEST.VALUE:imu_float32.imuf_get_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:imu_float32.imuf_get_timestamp.return[0].sec:1
TEST.EXPECTED:imu_float32.imuf_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_get_timestamp
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
TEST.VALUE:imu_float32.imuf_get_timestamp.self:<<null>>
TEST.END

-- Subprogram: imuf_init

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_init
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
TEST.VALUE:imu_float32.imuf_init.self:<<malloc 1>>
TEST.EXPECTED:imu_float32.imuf_init.self[0].stamp.sec:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].stamp.nsec:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].coordinate:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].status:IMU_STATUS_ALLGOOD
TEST.EXPECTED:imu_float32.imuf_init.self[0].angular_velocity.rows:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].angular_velocity.cols:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].angular_velocity.size:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].angular_velocity.pitchx:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].angular_velocity.pitchy:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].angular_velocity.capacity:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].linear_acceleration.rows:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].linear_acceleration.cols:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].linear_acceleration.size:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].linear_acceleration.pitchx:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].linear_acceleration.pitchy:0
TEST.EXPECTED:imu_float32.imuf_init.self[0].linear_acceleration.capacity:0
TEST.EXPECTED:imu_float32.imuf_init.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_init
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
TEST.VALUE:imu_float32.imuf_init.self:<<null>>
TEST.END

-- Subprogram: imuf_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize
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
TEST.VALUE:imu_float32.imuf_serialize.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize
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
TEST.VALUE:imu_float32.imuf_serialize.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize
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
TEST.VALUE:imu_float32.imuf_serialize.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize
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
TEST.VALUE:imu_float32.imuf_serialize.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize.buffer_size:<<MIN>>
TEST.END

-- Subprogram: imuf_serialize_4byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_4byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_4byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: imuf_serialize_8byte_aligned

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_serialize_8byte_aligned
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
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.self:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer:<<null>>
TEST.VALUE:imu_float32.imuf_serialize_8byte_aligned.buffer_size:<<MAX>>
TEST.END

-- Subprogram: imuf_set_angular_velocity

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_angular_velocity
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
TEST.VALUE:imu_float32.imuf_set_angular_velocity.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity[0].rows:1
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity[0].cols:2
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity[0].size:3
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity[0].pitchx:4
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity[0].pitchy:5
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity[0].capacity:6
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.self[0].angular_velocity.rows:1
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.self[0].angular_velocity.cols:2
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.self[0].angular_velocity.size:3
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.self[0].angular_velocity.pitchx:4
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.self[0].angular_velocity.pitchy:5
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.self[0].angular_velocity.capacity:6
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_angular_velocity
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
TEST.VALUE:imu_float32.imuf_set_angular_velocity.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity.angular_velocity:<<malloc 1>>
TEST.END

-- Subprogram: imuf_set_angular_velocity_value

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_angular_velocity_value
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
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.angle_rate_x:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.angle_rate_y:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.angle_rate_z:<<MIN>>
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity_value.self[0].angular_velocity_data[0..2]:<<MIN>>
TEST.EXPECTED:imu_float32.imuf_set_angular_velocity_value.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_angular_velocity_value
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
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.angle_rate_x:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.angle_rate_y:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_angular_velocity_value.angle_rate_z:<<MIN>>
TEST.END

-- Subprogram: imuf_set_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_coordinate
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
TEST.VALUE:imu_float32.imuf_set_coordinate.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_coordinate.coordinate:<<MIN>>
TEST.EXPECTED:imu_float32.imuf_set_coordinate.self[0].coordinate:<<MIN>>
TEST.EXPECTED:imu_float32.imuf_set_coordinate.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_coordinate
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
TEST.VALUE:imu_float32.imuf_set_coordinate.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: imuf_set_linear_acceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_linear_acceleration
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
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration[0].rows:1
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration[0].cols:2
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration[0].size:3
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration[0].pitchx:4
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration[0].pitchy:5
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration[0].capacity:6
TEST.EXPECTED:imu_float32.imuf_set_linear_acceleration.self[0].linear_acceleration.rows:1
TEST.EXPECTED:imu_float32.imuf_set_linear_acceleration.self[0].linear_acceleration.cols:2
TEST.EXPECTED:imu_float32.imuf_set_linear_acceleration.self[0].linear_acceleration.size:3
TEST.EXPECTED:imu_float32.imuf_set_linear_acceleration.self[0].linear_acceleration.pitchx:4
TEST.EXPECTED:imu_float32.imuf_set_linear_acceleration.self[0].linear_acceleration.pitchy:5
TEST.EXPECTED:imu_float32.imuf_set_linear_acceleration.self[0].linear_acceleration.capacity:6
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_linear_acceleration
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
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration.linear_acceleration:<<malloc 1>>
TEST.END

-- Subprogram: imuf_set_linear_acceleration_value

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_linear_acceleration_value
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
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.acc_x:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.acc_y:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.acc_z:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_linear_acceleration_value
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
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.acc_x:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.acc_y:<<MIN>>
TEST.VALUE:imu_float32.imuf_set_linear_acceleration_value.acc_z:<<MIN>>
TEST.END

-- Subprogram: imuf_set_status

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_status
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
TEST.VALUE:imu_float32.imuf_set_status.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_status.status:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_status
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
TEST.VALUE:imu_float32.imuf_set_status.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_status.status:<<MIN>>
TEST.END

-- Subprogram: imuf_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_timestamp
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
TEST.VALUE:imu_float32.imuf_set_timestamp.self:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:imu_float32.imuf_set_timestamp.stamp[0].sec:1
TEST.VALUE:imu_float32.imuf_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:imu_float32.imuf_set_timestamp.self[0].stamp.sec:1
TEST.EXPECTED:imu_float32.imuf_set_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:imu_float32.imuf_set_timestamp.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:imuf_set_timestamp
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
TEST.VALUE:imu_float32.imuf_set_timestamp.self:<<null>>
TEST.VALUE:imu_float32.imuf_set_timestamp.stamp:<<malloc 1>>
TEST.END

-- Subprogram: serialize_data

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < 3) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < 3) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (i < 3) ==> FALSE
      (2) for (i < 3) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_float32
TEST.SUBPROGRAM:serialize_data
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (i < 3) ==> FALSE
      (2) for (i < 3) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Unable to control expression-to-expression comparison in branch 2
      Conflict: Unable to control expression-to-expression comparison in branch 1
TEST.END_NOTES:
TEST.VALUE:imu_float32.serialize_data.self:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer:<<malloc 1>>
TEST.VALUE:imu_float32.serialize_data.buffer_size:<<MIN>>
TEST.END
