-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : CONTROL_COMMAND
-- Unit(s) Under Test: control_command
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

-- Unit: control_command

-- Subprogram: holo::common::ControlCommand::ControlCommand

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::ControlCommand
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_model_:DISABLE
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_model_:DISABLE
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_model_:DISABLE
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.handbrake_:0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_level_:0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_position_:0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:0.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:0.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value2_:0.0
TEST.END

-- Subprogram: holo::common::ControlCommand::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetGearCommand

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetGearCommand
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.handbrake_:1
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_level_:3
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_position_:3
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetGearCommand.return:103
TEST.END

-- Subprogram: holo::common::ControlCommand::GetGearControlModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetGearControlModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_model_:GEAR_CONTROL
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetGearControlModel.return:GEAR_CONTROL
TEST.END

-- Subprogram: holo::common::ControlCommand::GetGearLevel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetGearLevel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_level_:3
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetGearLevel.return:3
TEST.END

-- Subprogram: holo::common::ControlCommand::GetGearPosition

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetGearPosition
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_position_:5
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetGearPosition.return:S
TEST.END

-- Subprogram: holo::common::ControlCommand::GetHandbrake

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetHandbrake
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.handbrake_:1
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetHandbrake.return:true
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLateralControlModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLateralControlModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_model_:FRONT_WHEEL_ANGLE
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLateralControlModel.return:FRONT_WHEEL_ANGLE
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLateralControlValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLateralControlValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:3.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLateralControlValue.return:3.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLateralFrontWheelAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLateralFrontWheelAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_model_:FRONT_WHEEL_ANGLE
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:5.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLateralFrontWheelAngle.return:5.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLateralSteeringAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLateralSteeringAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:6.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLateralSteeringAngle.return:6.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLateralTorque

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLateralTorque
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:8.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLateralTorque.return:8.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:8.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalAcceleration.return:8.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalControlModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalControlModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_model_:PARK
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalControlModel.return:PARK
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalControlValue1

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalControlValue1
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:4.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalControlValue1.return:4.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalControlValue2

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalControlValue2
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value2_:5.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalControlValue2.return:5.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalDeceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalDeceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:8.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalDeceleration.return:8.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalSpeedLimit

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalSpeedLimit
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:9.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalSpeedLimit.return:9.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalStopDistance

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalStopDistance
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value2_:5.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalStopDistance.return:5.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalTorque

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalTorque
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:8.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalTorque.return:8.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetLongitudinalTorqueDeceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetLongitudinalTorqueDeceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:5.0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetLongitudinalTorqueDeceleration.return:5.0
TEST.END

-- Subprogram: holo::common::ControlCommand::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetSerializedSize.return:24
TEST.END

-- Subprogram: holo::common::ControlCommand::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:control_command.holo::common::ControlCommand::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::ControlCommand::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetGearCommand

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetGearCommand
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetGearCommand.value:103
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.handbrake_:1
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_level_:3
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_position_:3
TEST.END

-- Subprogram: holo::common::ControlCommand::SetGearControlModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetGearControlModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetGearControlModel.gear_control_model:GEAR_CONTROL
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_model_:GEAR_CONTROL
TEST.END

-- Subprogram: holo::common::ControlCommand::SetGearLevel

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetGearLevel
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (gear_level > 15) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetGearLevel.gear_level:<<MAX>>
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_level_:15
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetGearLevel
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (gear_level > 15) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetGearLevel.gear_level:<<MIN>>
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_level_:0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetGearPosition

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetGearPosition
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetGearPosition.gear_position:N
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.gear_position_:3
TEST.END

-- Subprogram: holo::common::ControlCommand::SetHandbrake

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetHandbrake
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetHandbrake.handbrake:true
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.gear_control_command_.handbrake_:1
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLateralControlModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLateralControlModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLateralControlModel.lateral_control_model:TORQUE
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_model_:TORQUE
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLateralControlValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLateralControlValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLateralControlValue.lateral_control_value:56.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:56.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLateralFrontWheelAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLateralFrontWheelAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLateralFrontWheelAngle.front_wheel_angle:56.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:56.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLateralSteeringAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLateralSteeringAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLateralSteeringAngle.steering_angle:45.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:45.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLateralTorque

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLateralTorque
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLateralTorque.lateral_torque:32.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.lateral_control_value_:32.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalAcceleration.acceleration:21.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:21.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalControlModel

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalControlModel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalControlModel.longitudinal_control_model:ACCELERATE
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_model_:ACCELERATE
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalControlValue1

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalControlValue1
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalControlValue1.longitudinal_control_value1:43.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:43.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalControlValue2

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalControlValue2
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalControlValue2.longitudinal_control_value2:54.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value2_:54.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalDeceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalDeceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalDeceleration.deceleration:54.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:54.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalSpeedLimit

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalSpeedLimit
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalSpeedLimit.speed_limit:32.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:32.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalStopDistance

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalStopDistance
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalStopDistance.stop_distance:12.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value2_:12.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalTorque

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalTorque
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalTorque.torque:34.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:34.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetLongitudinalTorqueDeceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetLongitudinalTorqueDeceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetLongitudinalTorqueDeceleration.torque_deceleration:45.0
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.longitudinal_control_value1_:45.0
TEST.END

-- Subprogram: holo::common::ControlCommand::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:control_command
TEST.SUBPROGRAM:holo::common::ControlCommand::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.<<constructor>>.ControlCommand().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:control_command.holo::common::ControlCommand::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:3
TEST.VALUE:control_command.holo::common::ControlCommand::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:4
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.timestamp_.holo::common::details::Timestamp.sec_:3
TEST.EXPECTED:control_command.<<GLOBAL>>.(cl).holo::common::ControlCommand.holo::common::ControlCommand.timestamp_.holo::common::details::Timestamp.nsec_:4
TEST.END
