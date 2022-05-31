-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : VEHICLE_BODY_STATE
-- Unit(s) Under Test: vehicle_body_state
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

-- Unit: vehicle_body_state

-- Subprogram: holo::common::VehicleBodyState::DoDriverSeatbeltNeedFastening

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::DoDriverSeatbeltNeedFastening
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:4096
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::DoDriverSeatbeltNeedFastening.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::DoPassengerSeatbeltNeedFastening

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::DoPassengerSeatbeltNeedFastening
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16384
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::DoPassengerSeatbeltNeedFastening.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetFrontLeftTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetFrontLeftTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_left_tire_pressure_:3.0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetFrontLeftTirePressure.return:3.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetFrontRightTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetFrontRightTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_right_tire_pressure_:6.0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetFrontRightTirePressure.return:6.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetInvalidFlagValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetInvalidFlagValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetRearLeftTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetRearLeftTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_left_tire_pressure_:5.0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetRearLeftTirePressure.return:5.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetRearRightTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetRearRightTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_right_tire_pressure_:6.0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetRearRightTirePressure.return:6.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_left_tire_pressure_:12.0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_right_tire_pressure_:13.0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_left_tire_pressure_:2.0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_right_tire_pressure_:24.0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:3
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:4
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetSerializedSize.return:32
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetStateValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetStateValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:345
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetStateValue.return:345
TEST.END

-- Subprogram: holo::common::VehicleBodyState::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsAutoSunroofOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsAutoSunroofOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:268435456
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsAutoSunroofOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsBrakeLightOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsBrakeLightOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:32
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsBrakeLightOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsCarHoodOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsCarHoodOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:4194304
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsCarHoodOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsDoorOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsDoorOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:655360
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsDoorOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsFrontFogLightOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsFrontFogLightOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:64
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsFrontFogLightOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsFrontLeftDoorOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsFrontLeftDoorOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:262144
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsFrontLeftDoorOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsFrontLeftWindowOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsFrontLeftWindowOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16777216
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsFrontLeftWindowOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsFrontRightDoorOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsFrontRightDoorOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:524288
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsFrontRightDoorOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsFrontRightWindowOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsFrontRightWindowOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:33554432
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsFrontRightWindowOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsFrontWiperOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsFrontWiperOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:65536
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsFrontWiperOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsHazardFlasherOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsHazardFlasherOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:4
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsHazardFlasherOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsHighBeamOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsHighBeamOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsHighBeamOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsInvalidFlagSet()holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsInvalidFlagSet()holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (invalid_flags_ != 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:1
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet()holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsInvalidFlagSet()holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (invalid_flags_ != 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet()holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 24 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((invalid_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State &> (__VAR1__args))) == this->getFlags(std::forward< holo::common::VehicleBodyState::State &> (__VAR1__args))) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.STUB:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:2
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const.__VAR1__args:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 44 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((invalid_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State &> (__VAR1__args))) == this->getFlags(std::forward< holo::common::VehicleBodyState::State &> (__VAR1__args))) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const.__VAR1__args:LEFT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSet(holo::common::VehicleBodyState::State&)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsInvalidFlagSetAny

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsInvalidFlagSetAny
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 26 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSetAny.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((invalid_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State &> (__VAR1__args))) != 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:1
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const.return:1
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSetAny.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsInvalidFlagSetAny
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 47 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSetAny.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((invalid_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State &> (__VAR1__args))) != 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const.return:0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsInvalidFlagSetAny.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsLeftTurnSignalOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsLeftTurnSignalOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsLeftTurnSignalOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsLowBeamOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsLowBeamOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:8
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsLowBeamOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRearFogLightOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRearFogLightOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:128
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRearFogLightOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRearLeftDoorOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRearLeftDoorOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1048576
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRearLeftDoorOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRearLeftWindowOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRearLeftWindowOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:67108864
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRearLeftWindowOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRearRightDoorOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRearRightDoorOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:2097152
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRearRightDoorOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRearRightWindowOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRearRightWindowOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:134217728
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRearRightWindowOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRearWiperOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRearWiperOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:131072
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRearWiperOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsRightTurnSignalOn

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsRightTurnSignalOn
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:2
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsRightTurnSignalOn.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsStateSet()holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSet()holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (state_flags_ != 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet()holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSet()holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (state_flags_ != 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet()holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1032 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) == this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.STUB:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR1__args:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1052 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) == this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR1__args:HIGH_BEAM_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSet(holo::common::VehicleBodyState::State&&)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1118 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR5__args), std::forward< holo::common::VehicleBodyState::State> (__VAR4__args), std::forward< holo::common::VehicleBodyState::State> (__VAR3__args), std::forward< holo::common::VehicleBodyState::State> (__VAR2__args
), std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) != 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:3
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR5__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR4__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR3__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR2__args:LOW_BEAM_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR1__args:HIGH_BEAM_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1140 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR5__args), std::forward< holo::common::VehicleBodyState::State> (__VAR4__args), std::forward< holo::common::VehicleBodyState::State> (__VAR3__args), std::forward< holo::common::VehicleBodyState::State> (__VAR2__args
), std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) != 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR5__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR4__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR3__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR2__args:LOW_BEAM_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1074 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((state_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR6__args), std::forward< holo::common::VehicleBodyState::State> (__VAR5__args), std::forward< holo::common::VehicleBodyState::State> (__VAR4__args), std::forward< holo::common::VehicleBodyState::State> (__VAR3__args
), std::forward< holo::common::VehicleBodyState::State> (__VAR2__args), std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) != 0U) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR6__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR5__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR4__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR3__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR2__args:HIGH_BEAM_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR1__args:BRAKE_LIGHT_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1096 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((state_flags_ & this->getFlags(std::forward< holo::common::VehicleBodyState::State> (__VAR6__args), std::forward< holo::common::VehicleBodyState::State> (__VAR5__args), std::forward< holo::common::VehicleBodyState::State> (__VAR4__args), std::forward< holo::common::VehicleBodyState::State> (__VAR3__args
), std::forward< holo::common::VehicleBodyState::State> (__VAR2__args), std::forward< holo::common::VehicleBodyState::State> (__VAR1__args))) != 0U) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR6__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR5__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR4__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR3__args:LOW_BEAM_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR2__args:FRONT_FOG_LIGHT_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.__VAR1__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.return:0
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsStateSetAny(holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsTrunkDoorOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsTrunkDoorOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:8388608
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsTrunkDoorOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::IsWindowOpen

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::IsWindowOpen
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16777216
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::IsWindowOpen.return:true
TEST.END

-- Subprogram: holo::common::VehicleBodyState::ResetInvalidFlag()

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::ResetInvalidFlag()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:16777216
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::ResetInvalidFlag(holo::common::VehicleBodyState::State&&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::ResetInvalidFlag(holo::common::VehicleBodyState::State&&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 23 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::ResetInvalidFlag(holo::common::VehicleBodyState::State&&).args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:2
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::ResetInvalidFlag(holo::common::VehicleBodyState::State&&).__VAR1__args:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::ResetState()

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::ResetState()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:3
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::ResetState(holo::common::VehicleBodyState::State&&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::ResetState(holo::common::VehicleBodyState::State&&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1367 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::ResetState(holo::common::VehicleBodyState::State&&).args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:3
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::ResetState(holo::common::VehicleBodyState::State&&).__VAR1__args:LEFT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:2
TEST.END

-- Subprogram: holo::common::VehicleBodyState::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetBrakeLight

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetBrakeLight
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetBrakeLight.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:32
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetBrakeLight
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetBrakeLight.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetDoorState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) fl ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:262144
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) fl ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:3 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (2) fr ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:524288
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:4 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (2) fr ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:5 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (3) rl ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1048576
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:6 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (3) rl ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:7 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (4) rr ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:2097152
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:8 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (4) rr ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:9 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (5) trunk ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:8388608
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:10 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (5) trunk ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_6_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_6_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:11 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 11
      (6) hood ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #6, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:4194304
TEST.END

-- Test Case: COND_6_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetDoorState
TEST.NEW
TEST.NAME:COND_6_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:12 of 12
TEST.NOTES:
This is an automatically generated test case.
   Test Path 12
      (6) hood ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #6, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.trunk:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetDoorState.hood:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetFrontFogLight

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetFrontFogLight
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetFrontFogLight.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:64
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetFrontFogLight
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetFrontFogLight.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetFrontLeftTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetFrontLeftTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetFrontLeftTirePressure.value:6.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_left_tire_pressure_:6.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetFrontRightTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetFrontRightTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetFrontRightTirePressure.value:4.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_right_tire_pressure_:4.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetHazardFlasher

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetHazardFlasher
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetHazardFlasher.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:4
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetHazardFlasher
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetHazardFlasher.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetHighBeam

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetHighBeam
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetHighBeam.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetHighBeam
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetHighBeam.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetInvalidFlag

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetInvalidFlag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 23 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetInvalidFlag.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetInvalidFlag.__VAR1__args:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:2
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetInvalidFlagValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetInvalidFlagValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetInvalidFlagValue.value:32
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:32
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetLeftTurnSignal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetLeftTurnSignal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetLeftTurnSignal.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:1
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetLeftTurnSignal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetLeftTurnSignal.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetLowBeam

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetLowBeam
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetLowBeam.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:8
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetLowBeam
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetLowBeam.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetNeedFasteningSeatbelt

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetNeedFasteningSeatbelt
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) driver ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.driver:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.passenger:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:4096
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetNeedFasteningSeatbelt
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) driver ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.driver:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.passenger:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetNeedFasteningSeatbelt
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (2) passenger ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.driver:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.passenger:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16384
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetNeedFasteningSeatbelt
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (2) passenger ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.driver:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetNeedFasteningSeatbelt.passenger:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetRearFogLight

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetRearFogLight
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetRearFogLight.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:128
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetRearFogLight
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetRearFogLight.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetRearLeftTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetRearLeftTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetRearLeftTirePressure.value:3.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_left_tire_pressure_:3.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetRearRightTirePressure

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetRearRightTirePressure
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetRearRightTirePressure.value:4.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_right_tire_pressure_:4.0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetRightTurnSignal

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetRightTurnSignal
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) value ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetRightTurnSignal.value:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:2
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetRightTurnSignal
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) value ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetRightTurnSignal.value:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetState

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetState
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1354 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetState.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetState.__VAR1__args:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:2
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetStateValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetStateValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetStateValue.value:43
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:43
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetWindowState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) fl ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:16777216
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) fl ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:3 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (2) fr ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:33554432
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:4 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (2) fr ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_3_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_3_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:5 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (3) rl ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #3, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:67108864
TEST.END

-- Test Case: COND_3_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_3_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:6 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 6
      (3) rl ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #3, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_4_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_4_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:7 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 7
      (4) rr ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #4, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:134217728
TEST.END

-- Test Case: COND_4_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_4_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:8 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 8
      (4) rr ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #4, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_5_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_5_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:9 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 9
      (5) sunroof ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #5, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:268435456
TEST.END

-- Test Case: COND_5_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWindowState
TEST.NEW
TEST.NAME:COND_5_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:10 of 10
TEST.NOTES:
This is an automatically generated test case.
   Test Path 10
      (5) sunroof ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #5, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.fr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rl:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.rr:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWindowState.sunroof:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::SetWiperState

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWiperState
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) fw ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.fw:true
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.rw:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:65536
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWiperState
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) fw ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.fw:false
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.rw:<<MIN>>
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWiperState
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (2) rw ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.fw:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.rw:true
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:131072
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::SetWiperState
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (2) rw ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.fw:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::SetWiperState.rw:false
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::VehicleBodyState

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::VehicleBodyState
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_left_tire_pressure_:0.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.front_right_tire_pressure_:0.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_left_tire_pressure_:0.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.rear_right_tire_pressure_:0.0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.state_flags_:0
TEST.EXPECTED:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.invalid_flags_:0
TEST.END

-- Subprogram: holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const.value:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State)holo::uint32_t const.return:2
TEST.END

-- Subprogram: holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&)holo::uint32_t const

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&)holo::uint32_t const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1486 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&)holo::uint32_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&)holo::uint32_t const.value:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR1__args:LEFT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&)holo::uint32_t const.return:1
TEST.END

-- Subprogram: holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1472 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.value:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR2__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR1__args:RIGHT_TURN_SIGNAL_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.return:3
TEST.END

-- Subprogram: holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1458 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.value:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR3__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR2__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR1__args:HARZARD_FLASHER_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.return:7
TEST.END

-- Subprogram: holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1444 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.value:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR4__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR3__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR2__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR1__args:LOW_BEAM_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.return:15
TEST.END

-- Subprogram: holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const

-- Test Case: BASIS-PATH-001
TEST.UNIT:vehicle_body_state
TEST.SUBPROGRAM:holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.IMPORT_FAILURES:
(E) Errors from previous script import(s)
    >>> (E) @LINE: 1430 TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.args:<<MIN>>
    >>>     >>> Unknown parameter/object name args
    >>>     >>> Value Line Error - Command Ignored
TEST.END_IMPORT_FAILURES:
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:vehicle_body_state.<<GLOBAL>>.(cl).holo::common::VehicleBodyState.holo::common::VehicleBodyState.<<constructor>>.VehicleBodyState().<<call>>:0
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.value:<<MIN>>
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR5__args:LEFT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR4__args:RIGHT_TURN_SIGNAL_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR3__args:HARZARD_FLASHER_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR2__args:LOW_BEAM_ON
TEST.VALUE:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.__VAR1__args:HIGH_BEAM_ON
TEST.EXPECTED:vehicle_body_state.holo::common::VehicleBodyState::getFlags(holo::common::VehicleBodyState::State,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&,holo::common::VehicleBodyState::State&&)holo::uint32_t const.return:31
TEST.END
