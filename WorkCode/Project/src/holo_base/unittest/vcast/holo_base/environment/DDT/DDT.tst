-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : DDT
-- Unit(s) Under Test: ddt
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

-- Unit: ddt

-- Subprogram: holo::common::DdtStates<2UL>::DdtStates

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::DdtStates
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:0
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::Deserialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MIN>>
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::GetSerializedSize.return:12
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::HasDdtState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::HasDdtState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::HasDdtState.ddt:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::HasDdtState.return:false
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::HasDdtState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:2
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::HasDdtState.ddt:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::HasDdtState.return:true
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::HasDdtState
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::HasDdtState.ddt:<<MIN>>
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::HasDdtState.return:true
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::HasDdtState
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::HasDdtState.ddt:<<MIN>>
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::HasDdtState.return:true
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::RemoveDdtState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::RemoveDdtState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::RemoveDdtState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.ddt:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.return:false
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::RemoveDdtState
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:3
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.ddt:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.return:true
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::RemoveDdtState
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.ddt:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::RemoveDdtState.return:false
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::Serialize

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::Serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::Serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MIN>>
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:6
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.<<throw>>.holo::exception::OutOfRangeException:<<null>>
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.flags_:6
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MIN>>
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.ddt:<<MIN>>
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.ddt:7
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:6
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.<<throw>>.holo::exception::OutOfRangeException:<<null>>
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.flags_:6
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:6
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.flags_:6
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.ddt:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:7
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:8
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.ddt:7
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.<<throw>>.holo::exception::OutOfRangeException:<<null>>
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.type_:7
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.flags_:8
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::at(holo::uint8_t)holo::common::DdtState.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_time_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_time_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::begin()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::capacity

-- Test Case: holo::common::DdtStates<2UL>::capacity.001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::capacity
TEST.NEW
TEST.NAME:holo::common::DdtStates<2UL>::capacity.001
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::capacity.return:2
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::cbegin

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::cbegin
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_time_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cbegin.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cbegin.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cbegin.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cbegin.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cbegin.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cbegin.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::cend

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::cend
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cend.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cend.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cend.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cend.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cend.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::cend.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::clear

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::clear
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:1
TEST.EXPECTED:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:0
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::const_iterator const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::end()holo::common::DdtStates<2UL>::iterator.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.ddt:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.type_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.flags_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:6
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.flags_:6
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (index < ddt_total_num_) ==> TRUE
      (2) if (ddt == (ddts_[index]).GetType()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 2
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.type_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.flags_:4
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_distance_:3
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[0].holo::common::DdtState.pred_time_:4
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.ddt:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.type_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.flags_:4
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_distance_:3
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)const holo::common::DdtState const.return.holo::common::DdtState.pred_time_:4
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (index < ddt_total_num_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:<<MAX>>
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:6
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:7
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:8
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.flags_:6
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_distance_:7
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_time_:8
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 6
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (index < ddt_total_num_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.type_:5
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.flags_:6
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_distance_:7
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddts_[1].holo::common::DdtState.pred_time_:8
TEST.VALUE:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.ddt:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.type_:5
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.flags_:6
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.alarm_.holo::common::Alarm.code_:1
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.alarm_.holo::common::Alarm.level_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_distance_:7
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::operator[](holo::uint8_t)holo::common::DdtState.return.holo::common::DdtState.pred_time_:8
TEST.END

-- Subprogram: holo::common::DdtStates<2UL>::size

-- Test Case: BASIS-PATH-001
TEST.UNIT:ddt
TEST.SUBPROGRAM:holo::common::DdtStates<2UL>::size
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.<<constructor>>.DdtStates().<<call>>:0
TEST.VALUE:ddt.<<GLOBAL>>.(cl).holo::common::DdtStates<2UL>.holo::common::DdtStates<2UL>.ddt_total_num_:2
TEST.EXPECTED:ddt.holo::common::DdtStates<2UL>::size.return:2
TEST.END
