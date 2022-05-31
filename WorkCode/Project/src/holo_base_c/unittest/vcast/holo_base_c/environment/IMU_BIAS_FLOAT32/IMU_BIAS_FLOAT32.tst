-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : IMU_BIAS_FLOAT32
-- Unit(s) Under Test: imu_bias_float32
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

-- Unit: imu_bias_float32

-- Subprogram: imu_biasf_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_deserialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: imu_biasf_get_angular_velocity_bias

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_angular_velocity_bias
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.rows:1
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.cols:2
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.size:3
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.pitchx:4
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.pitchy:5
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.capacity:6
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.base:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias.self[0].angular_velocity_bias.base[0]:3.0
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].rows:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].cols:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].size:3
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].pitchx:4
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].pitchy:5
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].capacity:6
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias.return[0].base[0]:3.0
TEST.END

-- Subprogram: imu_biasf_get_angular_velocity_bias_covariance

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_angular_velocity_bias_covariance
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.rows:1
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.cols:2
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.size:3
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.pitchx:4
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.pitchy:5
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.capacity:6
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.base:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.self[0].linear_acceleration_bias_cov.base[0]:2.0
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].rows:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].cols:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].size:3
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].pitchx:4
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].pitchy:5
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].capacity:6
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_angular_velocity_bias_covariance.return[0].base[0]:2.0
TEST.END

-- Subprogram: imu_biasf_get_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_coordinate
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
TEST.VALUE:imu_bias_float32.imu_biasf_get_coordinate.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_coordinate.self[0].coordinate:5
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_coordinate.return:5
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_coordinate
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
TEST.VALUE:imu_bias_float32.imu_biasf_get_coordinate.self:<<null>>
TEST.END

-- Subprogram: imu_biasf_get_linear_acceleration_bias

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_linear_acceleration_bias
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.rows:1
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.cols:2
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.size:3
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.pitchx:4
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.pitchy:5
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.capacity:6
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.base:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.self[0].linear_acceleration_bias.base[0]:2.0
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].rows:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].cols:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].size:3
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].pitchx:4
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].pitchy:5
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].capacity:6
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_linear_acceleration_bias.return[0].base[0]:2.0
TEST.END

-- Subprogram: imu_biasf_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias_float32.imu_biasf_get_serialized_size.self:<<malloc 1>>
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_serialized_size.return:4
TEST.END

-- Subprogram: imu_biasf_get_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_timestamp
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
TEST.VALUE:imu_bias_float32.imu_biasf_get_timestamp.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_get_timestamp.self[0].stamp.sec:1
TEST.VALUE:imu_bias_float32.imu_biasf_get_timestamp.self[0].stamp.nsec:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_timestamp.return[0].sec:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_get_timestamp.return[0].nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_get_timestamp
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
TEST.VALUE:imu_bias_float32.imu_biasf_get_timestamp.self:<<null>>
TEST.END

-- Subprogram: imu_biasf_init

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_init
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
TEST.VALUE:imu_bias_float32.imu_biasf_init.self:<<malloc 1>>
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias.rows:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias.cols:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias.size:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias.pitchx:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias.pitchy:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias.capacity:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias.rows:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias.cols:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias.size:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias.pitchx:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias.pitchy:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias.capacity:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias_cov.rows:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias_cov.cols:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias_cov.size:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias_cov.pitchx:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias_cov.pitchy:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].angular_velocity_bias_cov.capacity:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias_cov.rows:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias_cov.cols:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias_cov.size:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias_cov.pitchx:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias_cov.pitchy:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].linear_acceleration_bias_cov.capacity:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].stamp.sec:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.self[0].stamp.nsec:0
TEST.EXPECTED:imu_bias_float32.imu_biasf_init.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_init
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
TEST.VALUE:imu_bias_float32.imu_biasf_init.self:<<null>>
TEST.END

-- Subprogram: imu_biasf_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_serialize
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
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: imu_biasf_set_angular_velocity_bias

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_angular_velocity_bias
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].rows:1
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].cols:2
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].size:3
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].pitchx:4
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].pitchy:5
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].capacity:6
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].base:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias[0].base[0]:2.0
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.rows:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.cols:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.size:3
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.pitchx:4
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.pitchy:5
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.capacity:6
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self[0].angular_velocity_bias.base[0]:2.0
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_angular_velocity_bias.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_angular_velocity_bias
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias.angular_velocity_bias:<<malloc 1>>
TEST.END

-- Subprogram: imu_biasf_set_angular_velocity_bias_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_angular_velocity_bias_covariance
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias_covariance.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias_covariance.angular_velocity_bias_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_angular_velocity_bias_covariance
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias_covariance.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_angular_velocity_bias_covariance.angular_velocity_bias_cov:<<malloc 1>>
TEST.END

-- Subprogram: imu_biasf_set_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_coordinate
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_coordinate.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_coordinate.coordinate:<<MIN>>
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_coordinate.self[0].coordinate:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_coordinate
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_coordinate.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_coordinate.coordinate:<<MIN>>
TEST.END

-- Subprogram: imu_biasf_set_linear_acceleration_bias

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_linear_acceleration_bias
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].rows:1
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].cols:2
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].size:3
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].pitchx:4
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].pitchy:5
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].capacity:6
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].base:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias[0].base[0]:2.0
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.rows:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.cols:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.size:3
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.pitchx:4
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.pitchy:5
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.capacity:6
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self[0].linear_acceleration_bias.base[0]:2.0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_linear_acceleration_bias
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias.linear_acceleration_bias:<<malloc 1>>
TEST.END

-- Subprogram: imu_biasf_set_linear_acceleration_bias_covariance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_linear_acceleration_bias_covariance
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias_covariance.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias_covariance.linear_acceleration_bias_cov:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_linear_acceleration_bias_covariance
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias_covariance.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_linear_acceleration_bias_covariance.linear_acceleration_bias_cov:<<malloc 1>>
TEST.END

-- Subprogram: imu_biasf_set_timestamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_timestamp
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_timestamp.self:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_timestamp.stamp:<<malloc 1>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_timestamp.stamp[0].sec:1
TEST.VALUE:imu_bias_float32.imu_biasf_set_timestamp.stamp[0].nsec:2
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_timestamp.self[0].stamp.sec:1
TEST.EXPECTED:imu_bias_float32.imu_biasf_set_timestamp.self[0].stamp.nsec:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:imu_bias_float32
TEST.SUBPROGRAM:imu_biasf_set_timestamp
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
TEST.VALUE:imu_bias_float32.imu_biasf_set_timestamp.self:<<null>>
TEST.VALUE:imu_bias_float32.imu_biasf_set_timestamp.stamp:<<malloc 1>>
TEST.END
