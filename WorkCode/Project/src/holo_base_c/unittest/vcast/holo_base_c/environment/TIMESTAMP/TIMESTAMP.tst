-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : TIMESTAMP
-- Unit(s) Under Test: serialization timestamp
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

-- Unit: timestamp

-- Subprogram: duration_add

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_add
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_add.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.lhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.duration_add.lhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.duration_add.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.rhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.duration_add.rhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.duration_add.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_add.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_add
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_add.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.lhs[0].sec:1
TEST.VALUE:timestamp.duration_add.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_add.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.rhs[0].sec:2
TEST.VALUE:timestamp.duration_add.rhs[0].nsec:3
TEST.VALUE:timestamp.duration_add.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_add.out[0].sec:3
TEST.EXPECTED:timestamp.duration_add.out[0].nsec:5
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_add
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_add.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.lhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.duration_add.lhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.duration_add.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.rhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.duration_add.rhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.duration_add.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_add.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_add
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_add.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.lhs[0].sec:1
TEST.VALUE:timestamp.duration_add.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_add.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_add.rhs[0].sec:3
TEST.VALUE:timestamp.duration_add.rhs[0].nsec:4
TEST.VALUE:timestamp.duration_add.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_add.out[0].sec:4
TEST.EXPECTED:timestamp.duration_add.out[0].nsec:6
TEST.END

-- Subprogram: duration_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (duration != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_deserialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_deserialize.duration[0].sec:0
TEST.VALUE:timestamp.duration_deserialize.duration[0].nsec:0
TEST.VALUE:timestamp.duration_deserialize.buffer_size:8
TEST.EXPECTED:timestamp.duration_deserialize.duration[0].sec:1
TEST.EXPECTED:timestamp.duration_deserialize.duration[0].nsec:2
TEST.EXPECTED:timestamp.duration_deserialize.return:8
TEST.VALUE_USER_CODE:timestamp.duration_deserialize.buffer
<<timestamp.duration_deserialize.buffer>> = ( &buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (duration != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_deserialize.duration:<<null>>
TEST.VALUE:timestamp.duration_deserialize.buffer:<<malloc 1>>
TEST.VALUE:timestamp.duration_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (duration != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_deserialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_deserialize.duration[0].sec:1
TEST.VALUE:timestamp.duration_deserialize.duration[0].nsec:2
TEST.VALUE:timestamp.duration_deserialize.buffer_size:8
TEST.EXPECTED:timestamp.duration_deserialize.return:0
TEST.VALUE_USER_CODE:timestamp.duration_deserialize.buffer
<<timestamp.duration_deserialize.buffer>> = ( NULL );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: duration_deserialize.001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_deserialize
TEST.NEW
TEST.NAME:duration_deserialize.001
TEST.STUB:timestamp.duration_get_serialized_size
TEST.VALUE:timestamp.duration_get_serialized_size.return:16
TEST.VALUE:timestamp.duration_deserialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_deserialize.duration[0].sec:1
TEST.VALUE:timestamp.duration_deserialize.duration[0].nsec:2
TEST.VALUE:timestamp.duration_deserialize.buffer:<<malloc 2>>
TEST.VALUE:timestamp.duration_deserialize.buffer:"8"
TEST.VALUE:timestamp.duration_deserialize.buffer_size:8
TEST.EXPECTED:timestamp.duration_deserialize.return:MACRO=RC_DESERIALIZATION_BUFFER_UNDERFLOW
TEST.END

-- Test Case: duration_deserialize.002
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_deserialize
TEST.NEW
TEST.NAME:duration_deserialize.002
TEST.STUB:serialization.deserialize_int32
TEST.VALUE:timestamp.duration_deserialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_deserialize.duration[0].sec:1
TEST.VALUE:timestamp.duration_deserialize.duration[0].nsec:2
TEST.VALUE:timestamp.duration_deserialize.buffer:<<malloc 2>>
TEST.VALUE:timestamp.duration_deserialize.buffer:"8"
TEST.VALUE:timestamp.duration_deserialize.buffer_size:9
TEST.VALUE:serialization.deserialize_int32.return:0
TEST.EXPECTED:timestamp.duration_deserialize.return:8
TEST.END

-- Subprogram: duration_divide_int32

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_divide_int32
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (0 == rhs) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_divide_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_divide_int32.rhs:0
TEST.VALUE:timestamp.duration_divide_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_divide_int32.return:MACRO=RC_DURATION_INVALID_PARAMETER
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_divide_int32
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (0 == rhs) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_divide_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_divide_int32.rhs:<<MIN>>
TEST.VALUE:timestamp.duration_divide_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_divide_int32.out[0].sec:0
TEST.EXPECTED:timestamp.duration_divide_int32.out[0].nsec:0
TEST.EXPECTED:timestamp.duration_divide_int32.return:0
TEST.END

-- Subprogram: duration_get_nsec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_get_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nsec < 0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_get_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_get_nsec.duration[0].sec:2
TEST.VALUE:timestamp.duration_get_nsec.duration[0].nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_get_nsec.return:-1147483648
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_get_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nsec < 0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_get_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_get_nsec.duration[0].nsec:<<MAX>>
TEST.EXPECTED:timestamp.duration_get_nsec.return:<<MAX>>
TEST.END

-- Subprogram: duration_get_sec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_get_sec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (duration->nsec < 0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_get_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_get_sec.duration[0].sec:2
TEST.VALUE:timestamp.duration_get_sec.duration[0].nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_get_sec.return:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_get_sec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (duration->nsec < 0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_get_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_get_sec.duration[0].sec:1
TEST.VALUE:timestamp.duration_get_sec.duration[0].nsec:<<MAX>>
TEST.EXPECTED:timestamp.duration_get_sec.return:1
TEST.END

-- Subprogram: duration_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_get_serialized_size.duration:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_get_serialized_size.return:8
TEST.END

-- Subprogram: duration_init

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init.duration:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_init.duration[0].sec:0
TEST.EXPECTED:timestamp.duration_init.duration[0].nsec:0
TEST.END

-- Subprogram: duration_init_from_duration

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_duration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_duration.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_duration.other:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_duration.other[0].sec:1
TEST.VALUE:timestamp.duration_init_from_duration.other[0].nsec:2
TEST.EXPECTED:timestamp.duration_init_from_duration.duration[0].sec:1
TEST.EXPECTED:timestamp.duration_init_from_duration.duration[0].nsec:2
TEST.EXPECTED:timestamp.duration_init_from_duration.return:0
TEST.END

-- Subprogram: duration_init_from_nsec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nsec > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_nsec.nsec:1
TEST.EXPECTED:timestamp.duration_init_from_nsec.duration[0].sec:0
TEST.EXPECTED:timestamp.duration_init_from_nsec.duration[0].nsec:1
TEST.EXPECTED:timestamp.duration_init_from_nsec.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nsec > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_init_from_nsec.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_nsec
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (nsec > DURATION_MAX_NSEC) ==> FALSE
      (2) if (nsec < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_init_from_nsec.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_nsec
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (nsec > DURATION_MAX_NSEC) ==> FALSE
      (2) if (nsec < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_nsec.nsec:-2147483648000000000
TEST.EXPECTED:timestamp.duration_init_from_nsec.duration[0].sec:-2147483648
TEST.EXPECTED:timestamp.duration_init_from_nsec.duration[0].nsec:0
TEST.EXPECTED:timestamp.duration_init_from_nsec.return:0
TEST.END

-- Test Case: duration_init_from_nsec.001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_nsec
TEST.NEW
TEST.NAME:duration_init_from_nsec.001
TEST.EXPECTED:timestamp.duration_init_from_nsec.return:MACRO=RC_DURATION_OVERFLOW
TEST.VALUE_USER_CODE:timestamp.duration_init_from_nsec.nsec
<<timestamp.duration_init_from_nsec.nsec>> = ( DURATION_MAX_NSEC + 1 );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: duration_init_from_sec

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec.sec:1.0
TEST.EXPECTED:timestamp.duration_init_from_sec.duration[0].sec:1
TEST.EXPECTED:timestamp.duration_init_from_sec.duration[0].nsec:0
TEST.EXPECTED:timestamp.duration_init_from_sec.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec.sec:2.0
TEST.EXPECTED:timestamp.duration_init_from_sec.duration[0].sec:2
TEST.EXPECTED:timestamp.duration_init_from_sec.duration[0].nsec:0
TEST.EXPECTED:timestamp.duration_init_from_sec.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec.sec:<<MIN>>
TEST.EXPECTED:timestamp.duration_init_from_sec.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec.sec:2.0
TEST.EXPECTED:timestamp.duration_init_from_sec.duration[0].sec:2
TEST.EXPECTED:timestamp.duration_init_from_sec.duration[0].nsec:0
TEST.EXPECTED:timestamp.duration_init_from_sec.return:0
TEST.END

-- Subprogram: duration_init_from_sec_nsec

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.sec:1
TEST.VALUE:timestamp.duration_init_from_sec_nsec.nsec:2
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.duration[0].sec:1
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.duration[0].nsec:2
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.sec:<<MIN>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.sec:<<MIN>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_init_from_sec_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.sec:1
TEST.VALUE:timestamp.duration_init_from_sec_nsec.nsec:2
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.duration[0].sec:1
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.duration[0].nsec:2
TEST.END

-- Test Case: duration_init_from_sec_nsec.001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_init_from_sec_nsec
TEST.NEW
TEST.NAME:duration_init_from_sec_nsec.001
TEST.VALUE:timestamp.duration_init_from_sec_nsec.sec:<<MAX>>
TEST.VALUE:timestamp.duration_init_from_sec_nsec.nsec:<<MAX>>
TEST.EXPECTED:timestamp.duration_init_from_sec_nsec.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Subprogram: duration_is_equal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_equal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (duration_to_int64(lhs) == duration_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.duration_to_int64
TEST.VALUE:timestamp.duration_to_int64.return:-9223372036854775808
TEST.VALUE:timestamp.duration_is_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_equal.lhs[0].sec:1
TEST.VALUE:timestamp.duration_is_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_is_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_equal.rhs[0].sec:1
TEST.VALUE:timestamp.duration_is_equal.rhs[0].nsec:2
TEST.EXPECTED:timestamp.duration_is_equal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_equal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (duration_to_int64(lhs) == duration_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_is_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_equal.lhs[0].sec:1
TEST.VALUE:timestamp.duration_is_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_is_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_equal.rhs[0].sec:3
TEST.VALUE:timestamp.duration_is_equal.rhs[0].nsec:4
TEST.EXPECTED:timestamp.duration_is_equal.return:false
TEST.END

-- Subprogram: duration_is_greater

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_greater
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (duration_to_int64(lhs) > duration_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_is_greater.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater.lhs[0].sec:5
TEST.VALUE:timestamp.duration_is_greater.lhs[0].nsec:6
TEST.VALUE:timestamp.duration_is_greater.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater.rhs[0].sec:1
TEST.VALUE:timestamp.duration_is_greater.rhs[0].nsec:2
TEST.EXPECTED:timestamp.duration_is_greater.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_greater
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (duration_to_int64(lhs) > duration_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.duration_to_int64
TEST.VALUE:timestamp.duration_to_int64.return:-9223372036854775808
TEST.VALUE:timestamp.duration_is_greater.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater.lhs[0].sec:3
TEST.VALUE:timestamp.duration_is_greater.lhs[0].nsec:4
TEST.VALUE:timestamp.duration_is_greater.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater.rhs[0].sec:7
TEST.VALUE:timestamp.duration_is_greater.rhs[0].nsec:8
TEST.EXPECTED:timestamp.duration_is_greater.return:false
TEST.END

-- Subprogram: duration_is_greater_equal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_greater_equal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (duration_to_int64(lhs) >= duration_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.duration_to_int64
TEST.VALUE:timestamp.duration_to_int64.return:<<MAX>>
TEST.VALUE:timestamp.duration_is_greater_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater_equal.lhs[0].sec:3
TEST.VALUE:timestamp.duration_is_greater_equal.lhs[0].nsec:4
TEST.VALUE:timestamp.duration_is_greater_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater_equal.rhs[0].sec:1
TEST.VALUE:timestamp.duration_is_greater_equal.rhs[0].nsec:2
TEST.EXPECTED:timestamp.duration_is_greater_equal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_greater_equal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (duration_to_int64(lhs) >= duration_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.duration_to_int64.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_is_greater_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater_equal.lhs[0].sec:1
TEST.VALUE:timestamp.duration_is_greater_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_is_greater_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_greater_equal.rhs[0].sec:2
TEST.VALUE:timestamp.duration_is_greater_equal.rhs[0].nsec:3
TEST.EXPECTED:timestamp.duration_is_greater_equal.return:false
TEST.END

-- Subprogram: duration_is_less

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_less
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (duration_to_int64(lhs) < duration_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.duration_to_int64.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_is_less.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less.lhs[0].sec:1
TEST.VALUE:timestamp.duration_is_less.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_is_less.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less.rhs[0].sec:3
TEST.VALUE:timestamp.duration_is_less.rhs[0].nsec:4
TEST.EXPECTED:timestamp.duration_is_less.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_less
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (duration_to_int64(lhs) < duration_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_is_less.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less.lhs[0].sec:3
TEST.VALUE:timestamp.duration_is_less.lhs[0].nsec:4
TEST.VALUE:timestamp.duration_is_less.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less.rhs[0].sec:1
TEST.VALUE:timestamp.duration_is_less.rhs[0].nsec:2
TEST.EXPECTED:timestamp.duration_is_less.return:false
TEST.END

-- Subprogram: duration_is_less_equal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_less_equal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (duration_to_int64(lhs) <= duration_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.duration_to_int64
TEST.VALUE:timestamp.duration_to_int64.return:<<MIN>>
TEST.VALUE:timestamp.duration_is_less_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less_equal.lhs[0].sec:1
TEST.VALUE:timestamp.duration_is_less_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_is_less_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less_equal.rhs[0].sec:2
TEST.VALUE:timestamp.duration_is_less_equal.rhs[0].nsec:3
TEST.EXPECTED:timestamp.duration_is_less_equal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_is_less_equal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (duration_to_int64(lhs) <= duration_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.duration_to_int64.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_is_less_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less_equal.lhs[0].sec:3
TEST.VALUE:timestamp.duration_is_less_equal.lhs[0].nsec:4
TEST.VALUE:timestamp.duration_is_less_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_is_less_equal.rhs[0].sec:1
TEST.VALUE:timestamp.duration_is_less_equal.rhs[0].nsec:2
TEST.EXPECTED:timestamp.duration_is_less_equal.return:false
TEST.END

-- Subprogram: duration_multiply_float64

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_float64
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_float64.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.duration_multiply_float64.rhs:<<MAX>>
TEST.VALUE:timestamp.duration_multiply_float64.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_float64.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_float64
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_float64.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].sec:1
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_multiply_float64.rhs:2.0
TEST.VALUE:timestamp.duration_multiply_float64.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_float64.out[0].sec:2
TEST.EXPECTED:timestamp.duration_multiply_float64.out[0].nsec:4
TEST.EXPECTED:timestamp.duration_multiply_float64.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_float64
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_float64.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.duration_multiply_float64.rhs:2.0
TEST.VALUE:timestamp.duration_multiply_float64.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_float64.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_float64
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_float64.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].sec:1
TEST.VALUE:timestamp.duration_multiply_float64.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_multiply_float64.rhs:2.0
TEST.VALUE:timestamp.duration_multiply_float64.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_float64.out[0].sec:2
TEST.EXPECTED:timestamp.duration_multiply_float64.out[0].nsec:4
TEST.END

-- Subprogram: duration_multiply_int32

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_int32
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 6 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (0 == rhs) ==> FALSE
      (2) if (value / rhs != nsec) ==> FALSE
      (4) if (value > DURATION_MAX_NSEC) ==> FALSE
      (5) if (value < DURATION_MIN_NSEC) ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
      Cannot set local variable value in branch 4
      Cannot set local variable value in branch 5
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].sec:1
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].nsec:2
TEST.VALUE:timestamp.duration_multiply_int32.rhs:3
TEST.VALUE:timestamp.duration_multiply_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_int32.out[0].sec:3
TEST.EXPECTED:timestamp.duration_multiply_int32.out[0].nsec:6
TEST.EXPECTED:timestamp.duration_multiply_int32.return:0
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_int32
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 6 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (0 == rhs) ==> FALSE
      (2) if (value / rhs != nsec) ==> FALSE
      (4) if (value > DURATION_MAX_NSEC) ==> FALSE
      (5) if (value < DURATION_MIN_NSEC) ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
      Cannot set local variable value in branch 4
      Cannot set local variable value in branch 5
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].sec:9
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].nsec:9
TEST.VALUE:timestamp.duration_multiply_int32.rhs:9
TEST.VALUE:timestamp.duration_multiply_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_int32.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: BASIS-PATH-003-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_int32
TEST.NEW
TEST.NAME:BASIS-PATH-003-PARTIAL
TEST.BASIS_PATH:3 of 6 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (0 == rhs) ==> FALSE
      (2) if (value / rhs != nsec) ==> FALSE
      (4) if (value > DURATION_MAX_NSEC) ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
      Cannot set local variable value in branch 4
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].sec:1000
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].nsec:1000000
TEST.VALUE:timestamp.duration_multiply_int32.rhs:100000
TEST.VALUE:timestamp.duration_multiply_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_int32.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Test Case: BASIS-PATH-004-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_int32
TEST.NEW
TEST.NAME:BASIS-PATH-004-PARTIAL
TEST.BASIS_PATH:4 of 6 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (0 == rhs) ==> FALSE
      (2) if (value / rhs != nsec) ==> TRUE
      (3) if (value < (0)) ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
      Cannot set local variable value in branch 3
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].sec:7
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].nsec:8
TEST.VALUE:timestamp.duration_multiply_int32.rhs:<<MIN>>
TEST.VALUE:timestamp.duration_multiply_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_int32.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Test Case: BASIS-PATH-005-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_int32
TEST.NEW
TEST.NAME:BASIS-PATH-005-PARTIAL
TEST.BASIS_PATH:5 of 6 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (0 == rhs) ==> FALSE
      (2) if (value / rhs != nsec) ==> TRUE
      (3) if (value < (0)) ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
      Cannot set local variable value in branch 3
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].sec:-7
TEST.VALUE:timestamp.duration_multiply_int32.lhs[0].nsec:-8
TEST.VALUE:timestamp.duration_multiply_int32.rhs:<<MIN>>
TEST.VALUE:timestamp.duration_multiply_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_int32.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: BASIS-PATH-006
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_multiply_int32
TEST.NEW
TEST.NAME:BASIS-PATH-006
TEST.BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (0 == rhs) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_multiply_int32.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_multiply_int32.rhs:0
TEST.VALUE:timestamp.duration_multiply_int32.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_multiply_int32.out[0].sec:0
TEST.EXPECTED:timestamp.duration_multiply_int32.out[0].nsec:0
TEST.EXPECTED:timestamp.duration_multiply_int32.return:0
TEST.END

-- Subprogram: duration_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (duration != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_serialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_serialize.duration[0].sec:1
TEST.VALUE:timestamp.duration_serialize.duration[0].nsec:2
TEST.VALUE:timestamp.duration_serialize.buffer_size:8
TEST.EXPECTED:timestamp.duration_serialize.return:8
TEST.VALUE_USER_CODE:timestamp.duration_serialize.buffer
<<timestamp.duration_serialize.buffer>> = ( &buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (duration != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_serialize.duration:<<null>>
TEST.VALUE:timestamp.duration_serialize.buffer:<<malloc 1>>
TEST.VALUE:timestamp.duration_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (duration != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_serialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_serialize.duration[0].sec:1
TEST.VALUE:timestamp.duration_serialize.duration[0].nsec:2
TEST.VALUE:timestamp.duration_serialize.buffer:<<null>>
TEST.VALUE:timestamp.duration_serialize.buffer_size:0
TEST.END

-- Test Case: duration_serialize.001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_serialize
TEST.NEW
TEST.NAME:duration_serialize.001
TEST.STUB:timestamp.duration_get_serialized_size
TEST.VALUE:timestamp.duration_get_serialized_size.return:16
TEST.VALUE:timestamp.duration_serialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_serialize.duration[0].sec:1
TEST.VALUE:timestamp.duration_serialize.duration[0].nsec:2
TEST.VALUE:timestamp.duration_serialize.buffer_size:8
TEST.EXPECTED:timestamp.duration_serialize.return:MACRO=RC_SERIALIZATION_BUFFER_OVERFLOW
TEST.VALUE_USER_CODE:timestamp.duration_serialize.buffer
unsigned char buffer[8] = {0};
<<timestamp.duration_serialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: duration_serialize.002
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_serialize
TEST.NEW
TEST.NAME:duration_serialize.002
TEST.STUB:serialization.serialize_int32
TEST.VALUE:timestamp.duration_serialize.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_serialize.buffer_size:8
TEST.VALUE:serialization.serialize_int32.return:1
TEST.VALUE_USER_CODE:timestamp.duration_serialize.buffer
unsigned char buffer[8] = {0};
<<timestamp.duration_serialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Subprogram: duration_set_nsec

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_set_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nsec > NSEC_PER_SEC - 1 || nsec < 0) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_set_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_set_nsec.nsec:<<MAX>>
TEST.EXPECTED:timestamp.duration_set_nsec.return:MACRO=RC_DURATION_INVALID_PARAMETER
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_set_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (nsec > NSEC_PER_SEC - 1 || nsec < 0) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_set_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_set_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.duration_set_nsec.return:MACRO=RC_DURATION_INVALID_PARAMETER
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_set_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nsec > NSEC_PER_SEC - 1 || nsec < 0) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_set_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_set_nsec.nsec:5
TEST.EXPECTED:timestamp.duration_set_nsec.duration[0].sec:0
TEST.EXPECTED:timestamp.duration_set_nsec.duration[0].nsec:5
TEST.EXPECTED:timestamp.duration_set_nsec.return:0
TEST.END

-- Subprogram: duration_set_sec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_set_sec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (duration->nsec < 0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_set_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_set_sec.duration[0].nsec:<<MIN>>
TEST.VALUE:timestamp.duration_set_sec.sec:<<MIN>>
TEST.EXPECTED:timestamp.duration_set_sec.duration[0].sec:-2147483648
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_set_sec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (duration->nsec < 0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_set_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_set_sec.duration[0].nsec:<<MAX>>
TEST.VALUE:timestamp.duration_set_sec.sec:<<MIN>>
TEST.EXPECTED:timestamp.duration_set_sec.duration[0].sec:-2147483648
TEST.END

-- Subprogram: duration_sub

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_sub
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.lhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.duration_sub.lhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.duration_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.rhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.duration_sub.rhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.duration_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_sub.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_sub
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.lhs[0].sec:3
TEST.VALUE:timestamp.duration_sub.lhs[0].nsec:4
TEST.VALUE:timestamp.duration_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.rhs[0].sec:1
TEST.VALUE:timestamp.duration_sub.rhs[0].nsec:2
TEST.VALUE:timestamp.duration_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_sub.out[0].sec:2
TEST.EXPECTED:timestamp.duration_sub.out[0].nsec:2
TEST.EXPECTED:timestamp.duration_sub.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_sub
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.lhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.duration_sub.lhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.duration_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.rhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.duration_sub.rhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.duration_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_sub.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_sub
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.lhs[0].sec:3
TEST.VALUE:timestamp.duration_sub.lhs[0].nsec:4
TEST.VALUE:timestamp.duration_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.duration_sub.rhs[0].sec:1
TEST.VALUE:timestamp.duration_sub.rhs[0].nsec:2
TEST.VALUE:timestamp.duration_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_sub.out[0].sec:2
TEST.EXPECTED:timestamp.duration_sub.out[0].nsec:2
TEST.END

-- Subprogram: duration_to_int64

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_to_int64
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_to_int64.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_to_int64.duration[0].sec:3
TEST.VALUE:timestamp.duration_to_int64.duration[0].nsec:4
TEST.EXPECTED:timestamp.duration_to_int64.return:3000000004
TEST.END

-- Subprogram: duration_to_nsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_to_nsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_to_nsec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_to_nsec.duration[0].sec:1
TEST.VALUE:timestamp.duration_to_nsec.duration[0].nsec:2
TEST.VALUE:timestamp.duration_to_nsec.nsec:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_to_nsec.nsec[0]:1000000002
TEST.EXPECTED:timestamp.duration_to_nsec.return:0
TEST.END

-- Subprogram: duration_to_sec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:duration_to_sec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.duration_to_sec.duration:<<malloc 1>>
TEST.VALUE:timestamp.duration_to_sec.duration[0].sec:1
TEST.VALUE:timestamp.duration_to_sec.duration[0].nsec:100000001
TEST.VALUE:timestamp.duration_to_sec.sec:<<malloc 1>>
TEST.EXPECTED:timestamp.duration_to_sec.sec[0]:1.1
TEST.EXPECTED:timestamp.duration_to_sec.return:0
TEST.END

-- Subprogram: timestamp_add_duration

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_add_duration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_add_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.timestamp_add_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_add_duration.return:MACRO=RC_TIMESTAMP_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_add_duration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_add_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_add_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].sec:2
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].nsec:3
TEST.VALUE:timestamp.timestamp_add_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_add_duration.out[0].sec:3
TEST.EXPECTED:timestamp.timestamp_add_duration.out[0].nsec:5
TEST.EXPECTED:timestamp.timestamp_add_duration.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_add_duration
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      (2) if (value < TIMESTAMP_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_add_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.timestamp_add_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_add_duration.return:MACRO=RC_TIMESTAMP_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_add_duration
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      (2) if (value < TIMESTAMP_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_add_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_add_duration.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_add_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].sec:3
TEST.VALUE:timestamp.timestamp_add_duration.rhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_add_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_add_duration.out[0].sec:4
TEST.EXPECTED:timestamp.timestamp_add_duration.out[0].nsec:6
TEST.EXPECTED:timestamp.timestamp_add_duration.return:0
TEST.END

-- Subprogram: timestamp_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (timestamp != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_deserialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.timestamp[0].sec:0
TEST.VALUE:timestamp.timestamp_deserialize.timestamp[0].nsec:0
TEST.VALUE:timestamp.timestamp_deserialize.buffer:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer_size:8
TEST.EXPECTED:timestamp.timestamp_deserialize.timestamp[0].sec:1
TEST.EXPECTED:timestamp.timestamp_deserialize.timestamp[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_deserialize.return:8
TEST.VALUE_USER_CODE:timestamp.timestamp_deserialize.buffer
<<timestamp.timestamp_deserialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (timestamp != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_deserialize.timestamp:<<null>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_deserialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (timestamp != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_deserialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer_size:8
TEST.VALUE_USER_CODE:timestamp.timestamp_deserialize.buffer
<<timestamp.timestamp_deserialize.buffer>> = ( NULL );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: timestamp_deserialize.001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_deserialize
TEST.NEW
TEST.NAME:timestamp_deserialize.001
TEST.STUB:timestamp.timestamp_get_serialized_size
TEST.VALUE:timestamp.timestamp_get_serialized_size.return:16
TEST.VALUE:timestamp.timestamp_deserialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_deserialize.timestamp[0].nsec:2
TEST.VALUE:timestamp.timestamp_deserialize.buffer:<<malloc 2>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer:"8"
TEST.VALUE:timestamp.timestamp_deserialize.buffer_size:8
TEST.EXPECTED:timestamp.timestamp_deserialize.return:MACRO=RC_DESERIALIZATION_BUFFER_UNDERFLOW
TEST.END

-- Test Case: timestamp_deserialize.002
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_deserialize
TEST.NEW
TEST.NAME:timestamp_deserialize.002
TEST.STUB:serialization.deserialize_uint32
TEST.VALUE:timestamp.timestamp_deserialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_deserialize.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_deserialize.timestamp[0].nsec:2
TEST.VALUE:timestamp.timestamp_deserialize.buffer:<<malloc 2>>
TEST.VALUE:timestamp.timestamp_deserialize.buffer:"8"
TEST.VALUE:timestamp.timestamp_deserialize.buffer_size:8
TEST.VALUE:serialization.deserialize_uint32.return:16
TEST.END

-- Subprogram: timestamp_get_nsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_get_nsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_get_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_get_nsec.timestamp[0].nsec:1
TEST.EXPECTED:timestamp.timestamp_get_nsec.return:1
TEST.END

-- Subprogram: timestamp_get_sec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_get_sec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_get_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_get_sec.timestamp[0].sec:1
TEST.EXPECTED:timestamp.timestamp_get_sec.return:1
TEST.END

-- Subprogram: timestamp_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_get_serialized_size.timestamp:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_get_serialized_size.return:8
TEST.END

-- Subprogram: timestamp_init

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init.timestamp:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_init.timestamp[0].sec:0
TEST.EXPECTED:timestamp.timestamp_init.timestamp[0].nsec:0
TEST.EXPECTED:timestamp.timestamp_init.return:0
TEST.END

-- Subprogram: timestamp_init_from_nsec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nsec > TIMESTAMP_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_nsec.nsec:<<MAX>>
TEST.EXPECTED:timestamp.timestamp_init_from_nsec.return:MACRO=RC_TIMESTAMP_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nsec > TIMESTAMP_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_nsec.nsec:3
TEST.EXPECTED:timestamp.timestamp_init_from_nsec.timestamp[0].sec:0
TEST.EXPECTED:timestamp.timestamp_init_from_nsec.timestamp[0].nsec:3
TEST.END

-- Subprogram: timestamp_init_from_sec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (sec > (float64_t)4294967295U + (0.9999900000000000455)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec.sec:<<MAX>>
TEST.EXPECTED:timestamp.timestamp_init_from_sec.return:MACRO=RC_TIMESTAMP_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (sec > (float64_t)4294967295U + (0.9999900000000000455)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec.sec:2.0
TEST.EXPECTED:timestamp.timestamp_init_from_sec.timestamp[0].sec:2
TEST.EXPECTED:timestamp.timestamp_init_from_sec.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (sec > (float64_t)4294967295U + (0.9999900000000000455)) ==> FALSE
      (2) if (sec < (float64_t)TIMESTAMP_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec.sec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_init_from_sec.return:MACRO=RC_TIMESTAMP_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (sec > (float64_t)4294967295U + (0.9999900000000000455)) ==> FALSE
      (2) if (sec < (float64_t)TIMESTAMP_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec.sec:2.0
TEST.EXPECTED:timestamp.timestamp_init_from_sec.timestamp[0].sec:2
TEST.EXPECTED:timestamp.timestamp_init_from_sec.timestamp[0].nsec:0
TEST.EXPECTED:timestamp.timestamp_init_from_sec.return:0
TEST.END

-- Subprogram: timestamp_init_from_sec_nsec

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.nsec:<<MAX>>
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.timestamp[0].sec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.timestamp[0].nsec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.return:MACRO=RC_TIMESTAMP_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.sec:1
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.nsec:2
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.timestamp[0].sec:1
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.timestamp[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      (2) if (value < TIMESTAMP_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.return:MACRO=RC_TIMESTAMP_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_sec_nsec
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      (2) if (value < TIMESTAMP_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.sec:1
TEST.VALUE:timestamp.timestamp_init_from_sec_nsec.nsec:2
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.timestamp[0].sec:1
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.timestamp[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_init_from_sec_nsec.return:0
TEST.END

-- Subprogram: timestamp_init_from_timestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_init_from_timestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_init_from_timestamp.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_timestamp.other:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_init_from_timestamp.other[0].sec:1
TEST.VALUE:timestamp.timestamp_init_from_timestamp.other[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_init_from_timestamp.timestamp[0].sec:1
TEST.EXPECTED:timestamp.timestamp_init_from_timestamp.timestamp[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_init_from_timestamp.return:0
TEST.END

-- Subprogram: timestamp_is_equal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_equal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (timestamp_to_int64(lhs) == timestamp_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_is_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_equal.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_equal.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_equal.rhs[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_is_equal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_equal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (timestamp_to_int64(lhs) == timestamp_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_is_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_equal.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_equal.rhs[0].sec:3
TEST.VALUE:timestamp.timestamp_is_equal.rhs[0].nsec:4
TEST.EXPECTED:timestamp.timestamp_is_equal.return:false
TEST.END

-- Subprogram: timestamp_is_greater

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_greater
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (timestamp_to_int64(lhs) > timestamp_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_is_greater.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater.lhs[0].sec:3
TEST.VALUE:timestamp.timestamp_is_greater.lhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_is_greater.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_greater.rhs[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_is_greater.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_greater
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (timestamp_to_int64(lhs) > timestamp_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.timestamp_to_int64
TEST.VALUE:timestamp.timestamp_to_int64.return:-9223372036854775808
TEST.VALUE:timestamp.timestamp_is_greater.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_greater.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_greater.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater.rhs[0].sec:2
TEST.VALUE:timestamp.timestamp_is_greater.rhs[0].nsec:3
TEST.EXPECTED:timestamp.timestamp_is_greater.return:false
TEST.END

-- Subprogram: timestamp_is_greater_equal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_greater_equal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (timestamp_to_int64(lhs) >= timestamp_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.timestamp_to_int64
TEST.VALUE:timestamp.timestamp_to_int64.return:<<MAX>>
TEST.VALUE:timestamp.timestamp_is_greater_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater_equal.lhs[0].sec:4
TEST.VALUE:timestamp.timestamp_is_greater_equal.lhs[0].nsec:5
TEST.VALUE:timestamp.timestamp_is_greater_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater_equal.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_greater_equal.rhs[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_is_greater_equal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_greater_equal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (timestamp_to_int64(lhs) >= timestamp_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.timestamp_to_int64.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_is_greater_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater_equal.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_greater_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_greater_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_greater_equal.rhs[0].sec:3
TEST.VALUE:timestamp.timestamp_is_greater_equal.rhs[0].nsec:4
TEST.EXPECTED:timestamp.timestamp_is_greater_equal.return:false
TEST.END

-- Subprogram: timestamp_is_less

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_less
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (timestamp_to_int64(lhs) < timestamp_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.timestamp_to_int64.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_is_less.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_less.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_less.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less.rhs[0].sec:5
TEST.VALUE:timestamp.timestamp_is_less.rhs[0].nsec:6
TEST.EXPECTED:timestamp.timestamp_is_less.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_less
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (timestamp_to_int64(lhs) < timestamp_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.timestamp_to_int64
TEST.VALUE:timestamp.timestamp_to_int64.return:<<MAX>>
TEST.VALUE:timestamp.timestamp_is_less.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_less.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_less.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less.rhs[0].sec:2
TEST.VALUE:timestamp.timestamp_is_less.rhs[0].nsec:3
TEST.EXPECTED:timestamp.timestamp_is_less.return:false
TEST.END

-- Subprogram: timestamp_is_less_equal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_less_equal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (timestamp_to_int64(lhs) <= timestamp_to_int64(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.timestamp_to_int64
TEST.VALUE:timestamp.timestamp_to_int64.return:<<MIN>>
TEST.VALUE:timestamp.timestamp_is_less_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less_equal.lhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_less_equal.lhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_is_less_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less_equal.rhs[0].sec:3
TEST.VALUE:timestamp.timestamp_is_less_equal.rhs[0].nsec:4
TEST.EXPECTED:timestamp.timestamp_is_less_equal.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_is_less_equal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (timestamp_to_int64(lhs) <= timestamp_to_int64(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.timestamp_to_int64.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_is_less_equal.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less_equal.lhs[0].sec:3
TEST.VALUE:timestamp.timestamp_is_less_equal.lhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_is_less_equal.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_is_less_equal.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_is_less_equal.rhs[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_is_less_equal.return:false
TEST.END

-- Subprogram: timestamp_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.COMPOUND_ONLY
TEST.MCDC_BASIS_PATH:2 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (timestamp != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_serialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_serialize.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_serialize.timestamp[0].nsec:2
TEST.VALUE:timestamp.timestamp_serialize.buffer_size:8
TEST.EXPECTED:timestamp.timestamp_serialize.return:8
TEST.VALUE_USER_CODE:timestamp.timestamp_serialize.buffer
<<timestamp.timestamp_serialize.buffer>> = ( buffer );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (timestamp != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_serialize.timestamp:<<null>>
TEST.VALUE:timestamp.timestamp_serialize.buffer:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_serialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.IMPORT_FAILURES:
(E) @LINE: 2413 TEST.VALUE_USER_CODE:timestamp.timestamp_serialize.buffer
    >>> Warning: Value already set
    >>> The previous expected value will be ignored.
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:4 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (timestamp != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_serialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_serialize.buffer_size:<<MIN>>
TEST.VALUE_USER_CODE:timestamp.timestamp_serialize.buffer
<<timestamp.timestamp_serialize.buffer>> = ( NULL );
TEST.END_VALUE_USER_CODE:
TEST.END

-- Test Case: timestamp_serialize.001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_serialize
TEST.NEW
TEST.NAME:timestamp_serialize.001
TEST.STUB:timestamp.timestamp_get_serialized_size
TEST.VALUE:timestamp.timestamp_get_serialized_size.return:16
TEST.VALUE:timestamp.timestamp_serialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_serialize.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_serialize.timestamp[0].nsec:2
TEST.VALUE:timestamp.timestamp_serialize.buffer:<<malloc 2>>
TEST.VALUE:timestamp.timestamp_serialize.buffer:"8"
TEST.VALUE:timestamp.timestamp_serialize.buffer_size:8
TEST.EXPECTED:timestamp.timestamp_serialize.return:MACRO=RC_SERIALIZATION_BUFFER_OVERFLOW
TEST.END

-- Test Case: timestamp_serialize.002
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_serialize
TEST.NEW
TEST.NAME:timestamp_serialize.002
TEST.STUB:serialization.serialize_uint32
TEST.VALUE:timestamp.timestamp_serialize.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_serialize.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_serialize.timestamp[0].nsec:2
TEST.VALUE:timestamp.timestamp_serialize.buffer:<<malloc 2>>
TEST.VALUE:timestamp.timestamp_serialize.buffer:"8"
TEST.VALUE:timestamp.timestamp_serialize.buffer_size:8
TEST.VALUE:timestamp.timestamp_serialize.return:8
TEST.VALUE:serialization.serialize_uint32.return:0
TEST.END

-- Subprogram: timestamp_set_nsec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_set_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nsec >= (uint32_t)NSEC_PER_SEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_set_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_set_nsec.nsec:<<MAX>>
TEST.EXPECTED:timestamp.timestamp_set_nsec.return:MACRO=RC_TIMESTAMP_INVALID_PARAMETER
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_set_nsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nsec >= (uint32_t)NSEC_PER_SEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_set_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_set_nsec.nsec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_set_nsec.timestamp[0].sec:0
TEST.EXPECTED:timestamp.timestamp_set_nsec.timestamp[0].nsec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_set_nsec.return:0
TEST.END

-- Subprogram: timestamp_set_sec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_set_sec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_set_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_set_sec.sec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_set_sec.timestamp[0].sec:<<MIN>>
TEST.EXPECTED:timestamp.timestamp_set_sec.return:0
TEST.END

-- Subprogram: timestamp_sub

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.lhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub.lhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.rhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub.rhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub.return:MACRO=RC_DURATION_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.lhs[0].sec:3
TEST.VALUE:timestamp.timestamp_sub.lhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_sub.rhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub.out[0].sec:2
TEST.EXPECTED:timestamp.timestamp_sub.out[0].nsec:2
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.lhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub.lhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.rhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub.rhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub.return:MACRO=RC_DURATION_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > DURATION_MAX_NSEC) ==> FALSE
      (2) if (value < DURATION_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.lhs[0].sec:3
TEST.VALUE:timestamp.timestamp_sub.lhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_sub.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_sub.rhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_sub.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub.out[0].sec:2
TEST.EXPECTED:timestamp.timestamp_sub.out[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_sub.return:0
TEST.END

-- Subprogram: timestamp_sub_duration

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub_duration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub_duration.return:MACRO=RC_TIMESTAMP_OVERFLOW
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub_duration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].sec:3
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_sub_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_sub_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub_duration.out[0].sec:2
TEST.EXPECTED:timestamp.timestamp_sub_duration.out[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_sub_duration.return:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub_duration
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      (2) if (value < TIMESTAMP_MIN_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].sec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].nsec:<<MIN>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].sec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].nsec:<<MAX>>
TEST.VALUE:timestamp.timestamp_sub_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub_duration.return:MACRO=RC_TIMESTAMP_UNDERFLOW
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_sub_duration
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > TIMESTAMP_MAX_NSEC) ==> FALSE
      (2) if (value < TIMESTAMP_MIN_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable value in branch 2
      Cannot set local variable value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_sub_duration.lhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].sec:3
TEST.VALUE:timestamp.timestamp_sub_duration.lhs[0].nsec:4
TEST.VALUE:timestamp.timestamp_sub_duration.rhs:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].sec:1
TEST.VALUE:timestamp.timestamp_sub_duration.rhs[0].nsec:2
TEST.VALUE:timestamp.timestamp_sub_duration.out:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_sub_duration.out[0].sec:2
TEST.EXPECTED:timestamp.timestamp_sub_duration.out[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_sub_duration.return:0
TEST.END

-- Subprogram: timestamp_to_int64

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_to_int64
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_to_int64.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_to_int64.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_to_int64.timestamp[0].nsec:2
TEST.EXPECTED:timestamp.timestamp_to_int64.return:1000000002
TEST.END

-- Subprogram: timestamp_to_nsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_to_nsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_to_nsec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_to_nsec.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_to_nsec.timestamp[0].nsec:2
TEST.VALUE:timestamp.timestamp_to_nsec.nsec:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_to_nsec.nsec[0]:1000000002
TEST.EXPECTED:timestamp.timestamp_to_nsec.return:0
TEST.END

-- Subprogram: timestamp_to_sec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:timestamp_to_sec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.timestamp_to_sec.timestamp:<<malloc 1>>
TEST.VALUE:timestamp.timestamp_to_sec.timestamp[0].sec:1
TEST.VALUE:timestamp.timestamp_to_sec.timestamp[0].nsec:200000000
TEST.VALUE:timestamp.timestamp_to_sec.sec:<<malloc 1>>
TEST.EXPECTED:timestamp.timestamp_to_sec.sec[0]:1.2
TEST.EXPECTED:timestamp.timestamp_to_sec.return:0
TEST.END

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_duration_serialize_deserialize
TEST.SLOT: "1", "timestamp", "duration_serialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.SLOT: "2", "timestamp", "duration_deserialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.END
--

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.test_timestamp_serialize_deserialize
TEST.SLOT: "1", "timestamp", "timestamp_serialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.SLOT: "2", "timestamp", "timestamp_deserialize", "1", "COND_1_ROW_1_PAIR_a_T"
TEST.END
--
