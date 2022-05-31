-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : DEQUEUE
-- Unit(s) Under Test: dequeue
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

-- Unit: dequeue

-- Subprogram: dequeuef_get_capacity

-- Test Case: BASIS-PATH-001
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_capacity
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_capacity.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_capacity.dequeue[0].capacity:5
TEST.EXPECTED:dequeue.dequeuef_get_capacity.return:5
TEST.END

-- Subprogram: dequeuef_get_data_by_index

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_data_by_index
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue)) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_data_by_index.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_get_data_by_index.index:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_data_by_index
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue)) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_data_by_index.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.index:<<MAX>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_data_by_index
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue)) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_data_by_index.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.index:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_index.data:<<malloc 1>>
TEST.END

-- Subprogram: dequeuef_get_data_by_reverse_index

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_data_by_reverse_index
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue)) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.index:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_data_by_reverse_index
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue)) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.index:<<MAX>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_data_by_reverse_index
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head || index >= dequeuef_get_size(dequeue)) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.index:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_data_by_reverse_index.data:<<malloc 1>>
TEST.END

-- Subprogram: dequeuef_get_size

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_size
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_size.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_size.dequeue[0].head:4294967295
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_size
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_size.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_size.dequeue[0].head:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_size
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) (dequeue->tail <= dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Cannot resolve multiple comparisons ( dequeue.dequeuef_get_size.dequeue.head ) in branches 1/2
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_size.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_size.dequeue[0].head:<<MAX>>
TEST.VALUE:dequeue.dequeuef_get_size.dequeue[0].tail:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_get_size
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) (dequeue->tail <= dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_get_size.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_get_size.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_get_size.dequeue[0].tail:<<MAX>>
TEST.END

-- Subprogram: dequeuef_init

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_init
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if ((0) == buffer_size || DEQUEUEF_MAX_BUFFER_SIZE == buffer_size) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_init.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_init.buffer:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_init.buffer_size:0
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_init
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if ((0) == buffer_size || DEQUEUEF_MAX_BUFFER_SIZE == buffer_size) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable dequeue.dequeuef_init.buffer_size 'equal to' and 'not equal to' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_init.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_init.buffer:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_init.buffer_size:1
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_init
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if ((0) == buffer_size || DEQUEUEF_MAX_BUFFER_SIZE == buffer_size) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_init.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_init.buffer:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_init.buffer_size:1
TEST.END

-- Subprogram: dequeuef_is_empty

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_is_empty
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (dequeue->head == DEQUEUEF_MAX_BUFFER_SIZE) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_is_empty.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_is_empty.dequeue[0].head:4294967295
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_is_empty
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (dequeue->head == DEQUEUEF_MAX_BUFFER_SIZE) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_is_empty.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_is_empty.dequeue[0].head:<<MIN>>
TEST.END

-- Subprogram: dequeuef_is_full

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_is_full
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (dequeue->head == dequeue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_is_full.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_is_full.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_is_full.dequeue[0].tail:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_is_full
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (dequeue->head == dequeue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_is_full.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_is_full.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_is_full.dequeue[0].tail:1
TEST.END

-- Subprogram: dequeuef_peek_back

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_peek_back
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_peek_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_peek_back.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_peek_back.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_peek_back
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_peek_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_peek_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_peek_back.data:<<malloc 1>>
TEST.END

-- Subprogram: dequeuef_peek_front

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_peek_front
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_peek_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_peek_front.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_peek_front.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_peek_front
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_peek_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_peek_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_peek_front.data:<<malloc 1>>
TEST.END

-- Subprogram: dequeuef_pop_back

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_back
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_pop_back.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_back
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_back.data:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_back
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_back.data:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_back
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_back.data:<<null>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_back
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      (3) if (dequeue->head == dequeue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 3
      Cannot set dequeue->tail due to assignment
      Conflict: Trying to set variable dequeue.dequeuef_pop_back.data 'equal to' and 'not equal to' same value in branches 2/3
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].base:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_back.data:<<malloc 1>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_back
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      (3) if (dequeue->head == dequeue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set dequeue->tail due to assignment
      Conflict: Trying to set variable dequeue.dequeuef_pop_back.data 'equal to' and 'not equal to' same value in branches 2/3
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].base:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_back.dequeue[0].head:1
TEST.VALUE:dequeue.dequeuef_pop_back.data:<<malloc 1>>
TEST.END

-- Subprogram: dequeuef_pop_front

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_front
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_pop_front.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_front
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_front.data:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_front
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_front.data:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_front
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_front.data:<<null>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_front
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      (3) if (dequeue->head == dequeue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set dequeue->head due to assignment
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_front.data:<<null>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_pop_front
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      (3) if (dequeue->head == dequeue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set dequeue->head due to assignment
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_pop_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_pop_front.data:<<null>>
TEST.END

-- Subprogram: dequeuef_push_back

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_back
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (dequeue->head == dequeue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].tail:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_back.data:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_back
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (dequeue->head == dequeue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].tail:1
TEST.VALUE:dequeue.dequeuef_push_back.data:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_back
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (dequeue->head == dequeue->tail) ==> FALSE
      (2) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].tail:<<MAX>>
TEST.VALUE:dequeue.dequeuef_push_back.data:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_back
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (dequeue->head == dequeue->tail) ==> FALSE
      (2) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_back.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_back.dequeue[0].tail:1
TEST.VALUE:dequeue.dequeuef_push_back.data:<<MIN>>
TEST.END

-- Subprogram: dequeuef_push_front

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_front
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (dequeue->head == dequeue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].tail:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_front.data:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_front
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (dequeue->head == dequeue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].tail:1
TEST.VALUE:dequeue.dequeuef_push_front.data:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_front
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (dequeue->head == dequeue->tail) ==> FALSE
      (2) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].head:4294967295
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].tail:<<MAX>>
TEST.VALUE:dequeue.dequeuef_push_front.data:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:dequeue
TEST.SUBPROGRAM:dequeuef_push_front
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (dequeue->head == dequeue->tail) ==> FALSE
      (2) if (DEQUEUEF_MAX_BUFFER_SIZE == dequeue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:dequeue.dequeuef_push_front.dequeue:<<malloc 1>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].head:<<MIN>>
TEST.VALUE:dequeue.dequeuef_push_front.dequeue[0].tail:1
TEST.VALUE:dequeue.dequeuef_push_front.data:<<MIN>>
TEST.END
