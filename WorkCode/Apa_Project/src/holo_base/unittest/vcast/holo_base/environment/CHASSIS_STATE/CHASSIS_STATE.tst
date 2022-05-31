-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : CHASSIS_STATE
-- Unit(s) Under Test: chassis_state
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

-- Unit: chassis_state

-- Subprogram: holo::common::details::ChassisState::ChassisState

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::ChassisState
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.vehicle_speed_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_left_wheel_speed_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_right_wheel_speed_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_left_wheel_speed_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_right_wheel_speed_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_left_wheel_pulse_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_right_wheel_pulse_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_left_wheel_pulse_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_right_wheel_pulse_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.longitudinal_acceleration_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.lateral_acceleration_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.yaw_rate_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_wheel_angle_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.longitudinal_control_value_:0.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.energy_source_level_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.gear_pos_:UNKNOWN
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.gear_level_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:0
TEST.END

-- Subprogram: holo::common::details::ChassisState::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetEnergySourceLevel

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetEnergySourceLevel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.energy_source_level_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetEnergySourceLevel.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetFrontLeftWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetFrontLeftWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_left_wheel_pulse_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetFrontLeftWheelPulse.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetFrontLeftWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetFrontLeftWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_left_wheel_speed_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetFrontLeftWheelSpeed.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetFrontRightWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetFrontRightWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_right_wheel_pulse_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetFrontRightWheelPulse.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetFrontRightWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetFrontRightWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_right_wheel_speed_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetFrontRightWheelSpeed.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetFrontWheelAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetFrontWheelAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_wheel_angle_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetFrontWheelAngle.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetGearLevel

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetGearLevel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.gear_level_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetGearLevel.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetGearPosition

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetGearPosition
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.gear_pos_:P
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetGearPosition.return:P
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetInvalidFlagValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetInvalidFlagValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetInvalidFlagValue.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetLateralAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetLateralAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.lateral_acceleration_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetLateralAcceleration.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetLongitudinalAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetLongitudinalAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.longitudinal_acceleration_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetLongitudinalAcceleration.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetLongitudinalControlValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetLongitudinalControlValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.longitudinal_control_value_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetLongitudinalControlValue.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetRearLeftWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetRearLeftWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_left_wheel_pulse_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetRearLeftWheelPulse.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetRearLeftWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetRearLeftWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_left_wheel_speed_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetRearLeftWheelSpeed.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetRearRightWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetRearRightWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_right_wheel_pulse_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetRearRightWheelPulse.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetRearRightWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetRearRightWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_right_wheel_speed_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetRearRightWheelSpeed.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetSerializedSize.return:76
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetStateValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetStateValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:5
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetStateValue.return:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetVehicleSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetVehicleSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.vehicle_speed_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetVehicleSpeed.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::GetYawRate

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::GetYawRate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.yaw_rate_:5.0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::GetYawRate.return:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::IsInvalidFlagSet

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::IsInvalidFlagSet
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
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:1
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::IsInvalidFlagSet.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::IsInvalidFlagSet
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
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::IsInvalidFlagSet.return:false
TEST.END

-- Subprogram: holo::common::details::ChassisState::IsStateSet

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::IsStateSet
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
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:1
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::IsStateSet.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::IsStateSet
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
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:0
TEST.EXPECTED:chassis_state.holo::common::details::ChassisState::IsStateSet.return:false
TEST.END

-- Subprogram: holo::common::details::ChassisState::ResetInvalidFlag

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::ResetInvalidFlag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:0
TEST.END

-- Subprogram: holo::common::details::ChassisState::ResetState

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::ResetState
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:0
TEST.END

-- Subprogram: holo::common::details::ChassisState::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetEnergySourceLevel

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetEnergySourceLevel
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (value > 100) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetEnergySourceLevel.value:<<MAX>>
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.energy_source_level_:100
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetEnergySourceLevel
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (value > 100) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetEnergySourceLevel.value:<<MIN>>
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.energy_source_level_:0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetFrontLeftWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetFrontLeftWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetFrontLeftWheelPulse.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_left_wheel_pulse_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetFrontLeftWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetFrontLeftWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetFrontLeftWheelSpeed.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_left_wheel_speed_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetFrontRightWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetFrontRightWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetFrontRightWheelPulse.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_right_wheel_pulse_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetFrontRightWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetFrontRightWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetFrontRightWheelSpeed.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_right_wheel_speed_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetFrontWheelAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetFrontWheelAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetFrontWheelAngle.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.front_wheel_angle_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetGearLevel

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetGearLevel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetGearLevel.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.gear_level_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetGearPosition

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetGearPosition
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetGearPosition.value:S
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.gear_pos_:S
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetInvalidFlagValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetInvalidFlagValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetInvalidFlagValue.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.invalid_flags_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetLateralAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetLateralAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetLateralAcceleration.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.lateral_acceleration_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetLongitudinalAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetLongitudinalAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetLongitudinalAcceleration.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.longitudinal_acceleration_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetLongitudinalControlValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetLongitudinalControlValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetLongitudinalControlValue.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.longitudinal_control_value_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetRearLeftWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetRearLeftWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetRearLeftWheelPulse.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_left_wheel_pulse_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetRearLeftWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetRearLeftWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetRearLeftWheelSpeed.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_left_wheel_speed_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetRearRightWheelPulse

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetRearRightWheelPulse
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetRearRightWheelPulse.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_right_wheel_pulse_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetRearRightWheelSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetRearRightWheelSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetRearRightWheelSpeed.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.rear_right_wheel_speed_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetStateValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetStateValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetStateValue.value:5
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.state_flags_:5
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetVehicleSpeed

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetVehicleSpeed
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetVehicleSpeed.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.vehicle_speed_:5.0
TEST.END

-- Subprogram: holo::common::details::ChassisState::SetYawRate

-- Test Case: BASIS-PATH-001
TEST.UNIT:chassis_state
TEST.SUBPROGRAM:holo::common::details::ChassisState::SetYawRate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.<<constructor>>.ChassisState().<<call>>:0
TEST.VALUE:chassis_state.holo::common::details::ChassisState::SetYawRate.value:5.0
TEST.EXPECTED:chassis_state.<<GLOBAL>>.(cl).holo::common::details::ChassisState.holo::common::details::ChassisState.yaw_rate_:5.0
TEST.END
