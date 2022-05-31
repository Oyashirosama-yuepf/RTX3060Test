-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : ODM
-- Unit(s) Under Test: odm
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

-- Unit: odm

-- Subprogram: holo::common::OdmState::Disable

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::Disable
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:1
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:0
TEST.END

-- Subprogram: holo::common::OdmState::Enable

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::Enable
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:1
TEST.END

-- Subprogram: holo::common::OdmState::GetPredictedDistance

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::GetPredictedDistance
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_:5
TEST.EXPECTED:odm.holo::common::OdmState::GetPredictedDistance.return:5
TEST.END

-- Subprogram: holo::common::OdmState::GetPredictedTime

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::GetPredictedTime
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_:5
TEST.EXPECTED:odm.holo::common::OdmState::GetPredictedTime.return:5
TEST.END

-- Subprogram: holo::common::OdmState::IsEnabled

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::IsEnabled
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:1
TEST.EXPECTED:odm.holo::common::OdmState::IsEnabled.return:true
TEST.END

-- Subprogram: holo::common::OdmState::IsPredictedDistanceValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::IsPredictedDistanceValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_valid_:1
TEST.EXPECTED:odm.holo::common::OdmState::IsPredictedDistanceValid.return:true
TEST.END

-- Subprogram: holo::common::OdmState::IsPredictedTimeValid

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::IsPredictedTimeValid
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_valid_:1
TEST.EXPECTED:odm.holo::common::OdmState::IsPredictedTimeValid.return:true
TEST.END

-- Subprogram: holo::common::OdmState::OdmState()

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::OdmState()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_valid_:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_valid_:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.reserved_:0
TEST.END

-- Subprogram: holo::common::OdmState::OdmState(holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::OdmState(holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.holo::common::OdmState::OdmState(holo::uint32_t).value:13582586
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_:250
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_valid_:1
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_:30
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_valid_:1
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:1
TEST.END

-- Subprogram: holo::common::OdmState::SetPredDistance

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::SetPredDistance
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (dist >= 1U << 14U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.holo::common::OdmState::SetPredDistance.dist:<<MAX>>
TEST.EXPECTED:odm.holo::common::OdmState::SetPredDistance.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::SetPredDistance
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (dist >= 1U << 14U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.holo::common::OdmState::SetPredDistance.dist:5
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_:5
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_valid_:1
TEST.END

-- Subprogram: holo::common::OdmState::SetPredTime

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::SetPredTime
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (time >= 1U << 7U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.holo::common::OdmState::SetPredTime.time:<<MAX>>
TEST.EXPECTED:odm.holo::common::OdmState::SetPredTime.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::SetPredTime
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (time >= 1U << 7U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.holo::common::OdmState::SetPredTime.time:5
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_:5
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_valid_:1
TEST.END

-- Subprogram: holo::common::OdmState::operator holo::uint32_t

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmState::operator holo::uint32_t
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.<<constructor>>.OdmState().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_:250
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_dist_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_:30
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.pred_time_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmState.holo::common::OdmState.enable_:1
TEST.EXPECTED:odm.holo::common::OdmState::operator holo::uint32_t.return:13582586
TEST.END

-- Subprogram: holo::common::OdmStates::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmStates::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.<<constructor>>.OdmStates().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.nsec_:1
TEST.EXPECTED:odm.holo::common::OdmStates::GetSerializedSize.return:44
TEST.END

-- Subprogram: holo::common::OdmStates::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmStates::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.<<constructor>>.OdmStates().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.nsec_:1
TEST.EXPECTED:odm.holo::common::OdmStates::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:odm.holo::common::OdmStates::GetTimestamp.return.holo::common::details::Timestamp.nsec_:1
TEST.END

-- Subprogram: holo::common::OdmStates::OdmStates

-- Test Case: holo::common::OdmStates::OdmStates.001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmStates::OdmStates
TEST.NEW
TEST.NAME:holo::common::OdmStates::OdmStates.001
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.END

-- Subprogram: holo::common::OdmStates::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmStates::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.<<constructor>>.OdmStates().<<call>>:0
TEST.VALUE:odm.holo::common::OdmStates::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:odm.holo::common::OdmStates::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:odm.holo::common::OdmStates::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.<<constructor>>.OdmStates().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_dist_:2
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_dist_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_time_:2
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_time_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.enable_:1
TEST.VALUE:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const.ddt:<<MIN>>
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const.return.holo::common::OdmState.pred_dist_:2
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const.return.holo::common::OdmState.pred_dist_valid_:1
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const.return.holo::common::OdmState.pred_time_:2
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const.return.holo::common::OdmState.pred_time_valid_:1
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)const holo::common::OdmState const.return.holo::common::OdmState.enable_:1
TEST.END

-- Subprogram: holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState

-- Test Case: BASIS-PATH-001
TEST.UNIT:odm
TEST.SUBPROGRAM:holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.<<constructor>>.OdmStates().<<call>>:0
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_dist_:2
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_dist_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_time_:2
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.pred_time_valid_:1
TEST.VALUE:odm.<<GLOBAL>>.(cl).holo::common::OdmStates.holo::common::OdmStates.data_[0].holo::common::OdmState.enable_:1
TEST.VALUE:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState.ddt:ICP
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState.return.holo::common::OdmState.pred_dist_:2
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState.return.holo::common::OdmState.pred_dist_valid_:1
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState.return.holo::common::OdmState.pred_time_:2
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState.return.holo::common::OdmState.pred_time_valid_:1
TEST.EXPECTED:odm.holo::common::OdmStates::operator[](holo::common::OdmStates::Ddt)holo::common::OdmState.return.holo::common::OdmState.enable_:1
TEST.END

-- COMPOUND TESTS

TEST.SUBPROGRAM:<<COMPOUND>>
TEST.NEW
TEST.NAME:<<COMPOUND>>.001
TEST.END
--
