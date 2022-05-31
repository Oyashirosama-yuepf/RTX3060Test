-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : EXTRINSIC_FLOAT32
-- Unit(s) Under Test: extrinsic_float32
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

-- Unit: extrinsic_float32

-- Subprogram: extrinsicf_deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:8 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == deserialized_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set deserialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_deserialize
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:7 of 8
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (1) if (self != (void *)0) ==> FALSE
      (2) if (buffer != (void *)0) ==> FALSE
      (3) if (buffer_size < expected_size) ==> FALSE
      (4) if (expected_size == deserialized_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable expected_size in branch 4
      Cannot set deserialized_size due to assignment
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_deserialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: extrinsicf_get_child_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_child_coordinate.extrinsic:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_get_child_coordinate.extrinsic[0].child_coordinate:5
TEST.EXPECTED:extrinsic_float32.extrinsicf_get_child_coordinate.return:5
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_child_coordinate.extrinsic:<<null>>
TEST.END

-- Subprogram: extrinsicf_get_parent_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_parent_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_parent_coordinate.extrinsic:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_get_parent_coordinate.extrinsic[0].parent_coordinate:5
TEST.EXPECTED:extrinsic_float32.extrinsicf_get_parent_coordinate.return:5
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_parent_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_parent_coordinate.extrinsic:<<null>>
TEST.END

-- Subprogram: extrinsicf_get_pose

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_pose
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_pose.extrinsic:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_pose
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_pose.extrinsic:<<null>>
TEST.END

-- Subprogram: extrinsicf_get_serialized_size

-- Test Case: BASIS-PATH-001
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_get_serialized_size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_get_serialized_size.self:<<malloc 1>>
TEST.EXPECTED:extrinsic_float32.extrinsicf_get_serialized_size.return:8
TEST.END

-- Subprogram: extrinsicf_init

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_init
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:uut_prototype_stubs.__assert_fail
TEST.VALUE:extrinsic_float32.extrinsicf_init.extrinsic:<<malloc 1>>
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].parent_coordinate:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].child_coordinate:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.rotation.m.rows:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.rotation.m.cols:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.rotation.m.size:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.rotation.m.pitchx:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.rotation.m.pitchy:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.rotation.m.capacity:0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.translation.x:0.0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.translation.y:0.0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.extrinsic[0].pose.translation.z:0.0
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_init
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:uut_prototype_stubs.__assert_fail
TEST.VALUE:extrinsic_float32.extrinsicf_init.extrinsic:<<null>>
TEST.VALUE:uut_prototype_stubs.__assert_fail.__file:"/home/holo/test_workspace5/src/holo_base_c/src/common/extrinsic_float32.c"
TEST.VALUE:uut_prototype_stubs.__assert_fail.__line:16
TEST.EXPECTED:extrinsic_float32.extrinsicf_init.return:1
TEST.EXPECTED:uut_prototype_stubs.__assert_fail.__assertion:"8"
TEST.STUB_VAL_USER_CODE:uut_prototype_stubs.__assert_fail.__assertion
void test()
{
    return 8;
};

<<uut_prototype_stubs.__assert_fail.__assertion>> = ( test );
TEST.END_STUB_VAL_USER_CODE:
TEST.STUB_VAL_USER_CODE:uut_prototype_stubs.__assert_fail.__function
void print()
{
    return "stub succeed";
};
<<uut_prototype_stubs.__assert_fail.__function>> = ( print );
TEST.END_STUB_VAL_USER_CODE:
TEST.END

-- Subprogram: extrinsicf_serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MIN>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MAX>>
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_serialize
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
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.self:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_serialize.buffer_size:<<MAX>>
TEST.END

-- Subprogram: extrinsicf_set_child_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_set_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_set_child_coordinate.extrinsic:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_set_child_coordinate.child_coordinate:<<MIN>>
TEST.EXPECTED:extrinsic_float32.extrinsicf_set_child_coordinate.extrinsic[0].child_coordinate:<<MIN>>
TEST.EXPECTED:extrinsic_float32.extrinsicf_set_child_coordinate.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_set_child_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_set_child_coordinate.extrinsic:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_set_child_coordinate.child_coordinate:<<MIN>>
TEST.END

-- Subprogram: extrinsicf_set_parent_coordinate

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_set_parent_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_set_parent_coordinate.extrinsic:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_set_parent_coordinate.parent_coordinate:<<MIN>>
TEST.EXPECTED:extrinsic_float32.extrinsicf_set_parent_coordinate.extrinsic[0].parent_coordinate:<<MIN>>
TEST.EXPECTED:extrinsic_float32.extrinsicf_set_parent_coordinate.return:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_set_parent_coordinate
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_set_parent_coordinate.extrinsic:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_set_parent_coordinate.parent_coordinate:<<MIN>>
TEST.END

-- Subprogram: extrinsicf_set_pose

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_set_pose
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (extrinsic != (void *)0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_set_pose.extrinsic:<<malloc 1>>
TEST.VALUE:extrinsic_float32.extrinsicf_set_pose.pose:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:extrinsic_float32
TEST.SUBPROGRAM:extrinsicf_set_pose
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (extrinsic != (void *)0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:extrinsic_float32.extrinsicf_set_pose.extrinsic:<<null>>
TEST.VALUE:extrinsic_float32.extrinsicf_set_pose.pose:<<malloc 1>>
TEST.END
