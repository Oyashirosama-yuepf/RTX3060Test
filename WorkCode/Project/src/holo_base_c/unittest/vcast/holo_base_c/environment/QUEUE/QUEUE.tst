-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : QUEUE
-- Unit(s) Under Test: queue
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

-- Unit: queue

-- Subprogram: queuef_get_capacity

-- Test Case: BASIS-PATH-001
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_capacity
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_capacity.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_capacity.queue[0].capacity:5
TEST.EXPECTED:queue.queuef_get_capacity.return:5
TEST.END

-- Subprogram: queuef_get_data_by_index

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_data_by_index
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue)) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_data_by_index.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_data_by_index.queue[0].head:4294967295
TEST.VALUE:queue.queuef_get_data_by_index.index:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_data_by_index
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue)) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_data_by_index.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_data_by_index.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_index.index:<<MAX>>
TEST.VALUE:queue.queuef_get_data_by_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_data_by_index
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue)) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_data_by_index.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_data_by_index.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_index.index:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_index.data:<<malloc 1>>
TEST.END

-- Subprogram: queuef_get_data_by_reverse_index

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_data_by_reverse_index
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue)) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_data_by_reverse_index.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.queue[0].head:4294967295
TEST.VALUE:queue.queuef_get_data_by_reverse_index.index:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_data_by_reverse_index
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue)) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_data_by_reverse_index.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.index:<<MAX>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_data_by_reverse_index
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head || index >= queuef_get_size(queue)) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_data_by_reverse_index.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.index:<<MIN>>
TEST.VALUE:queue.queuef_get_data_by_reverse_index.data:<<malloc 1>>
TEST.END

-- Subprogram: queuef_get_size

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_size
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_size.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_size.queue[0].head:4294967295
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_size
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_size.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_size.queue[0].head:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_size
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      (2) (queue->tail <= queue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Cannot resolve multiple comparisons ( queue.queuef_get_size.queue.head ) in branches 1/2
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_size.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_size.queue[0].head:<<MAX>>
TEST.VALUE:queue.queuef_get_size.queue[0].tail:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_get_size
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      (2) (queue->tail <= queue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_get_size.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_get_size.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_get_size.queue[0].tail:<<MAX>>
TEST.END

-- Subprogram: queuef_init

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_init
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if ((0) == buffer_size || QUEUEF_MAX_BUFFER_SIZE == buffer_size) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_init.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_init.buffer:<<malloc 1>>
TEST.VALUE:queue.queuef_init.buffer_size:0
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_init
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if ((0) == buffer_size || QUEUEF_MAX_BUFFER_SIZE == buffer_size) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable queue.queuef_init.buffer_size 'equal to' and 'not equal to' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:queue.queuef_init.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_init.buffer:<<malloc 1>>
TEST.VALUE:queue.queuef_init.buffer_size:1
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_init
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if ((0) == buffer_size || QUEUEF_MAX_BUFFER_SIZE == buffer_size) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_init.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_init.buffer:<<malloc 1>>
TEST.VALUE:queue.queuef_init.buffer_size:1
TEST.END

-- Subprogram: queuef_is_empty

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_is_empty
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (queue->head == QUEUEF_MAX_BUFFER_SIZE) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_is_empty.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_is_empty.queue[0].head:4294967295
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_is_empty
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (queue->head == QUEUEF_MAX_BUFFER_SIZE) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_is_empty.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_is_empty.queue[0].head:<<MIN>>
TEST.END

-- Subprogram: queuef_is_full

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_is_full
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (queue->head == queue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_is_full.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_is_full.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_is_full.queue[0].tail:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_is_full
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (queue->head == queue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_is_full.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_is_full.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_is_full.queue[0].tail:1
TEST.END

-- Subprogram: queuef_peek

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_peek
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_peek.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_peek.queue[0].head:4294967295
TEST.VALUE:queue.queuef_peek.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_peek
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_peek.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_peek.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_peek.data:<<malloc 1>>
TEST.END

-- Subprogram: queuef_pop

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_pop
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_pop.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_pop.queue[0].head:4294967295
TEST.VALUE:queue.queuef_pop.data:<<malloc 1>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_pop
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_pop.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_pop.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_pop.data:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_pop
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_pop.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_pop.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_pop.data:<<malloc 1>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_pop
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_pop.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_pop.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_pop.data:<<null>>
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_pop
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:6 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      (3) if (queue->head == queue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set queue->head due to assignment
TEST.END_NOTES:
TEST.VALUE:queue.queuef_pop.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_pop.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_pop.data:<<null>>
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_pop
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:5 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      (2) if ((void *)0 != data) ==> FALSE
      (3) if (queue->head == queue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set queue->head due to assignment
TEST.END_NOTES:
TEST.VALUE:queue.queuef_pop.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_pop.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_pop.data:<<null>>
TEST.END

-- Subprogram: queuef_push

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_push
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (queue->head == queue->tail) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_push.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_push.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_push.queue[0].tail:<<MIN>>
TEST.VALUE:queue.queuef_push.data:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_push
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (queue->head == queue->tail) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_push.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_push.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_push.queue[0].tail:1
TEST.VALUE:queue.queuef_push.data:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_push
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (queue->head == queue->tail) ==> FALSE
      (2) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_push.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_push.queue[0].head:4294967295
TEST.VALUE:queue.queuef_push.queue[0].tail:<<MAX>>
TEST.VALUE:queue.queuef_push.data:<<MIN>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:queue
TEST.SUBPROGRAM:queuef_push
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (queue->head == queue->tail) ==> FALSE
      (2) if (QUEUEF_MAX_BUFFER_SIZE == queue->head) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:queue.queuef_push.queue:<<malloc 1>>
TEST.VALUE:queue.queuef_push.queue[0].head:<<MIN>>
TEST.VALUE:queue.queuef_push.queue[0].tail:1
TEST.VALUE:queue.queuef_push.data:<<MIN>>
TEST.END
