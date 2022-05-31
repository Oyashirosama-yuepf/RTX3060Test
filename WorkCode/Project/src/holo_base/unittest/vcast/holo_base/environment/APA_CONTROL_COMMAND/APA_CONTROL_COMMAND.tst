-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : APA_CONTROL_COMMAND
-- Unit(s) Under Test: apa_control_command
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

-- Unit: apa_control_command

-- Subprogram: holo::common::ApaControlCommand::ApaControlCommand

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::ApaControlCommand
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.lon_auto_mode_:false
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.target_gear_request_:0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.stop_dist_request_:0.0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.speed_limit_request_:0.0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.apafail_brkmode_request_:0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.steer_auto_mode_:false
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.steering_angle_:0.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetApafailBrkmodeRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetApafailBrkmodeRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.apafail_brkmode_request_:5
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetApafailBrkmodeRequest.return:5
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetLonAutoMode

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetLonAutoMode
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.lon_auto_mode_:true
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetLonAutoMode.return:true
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetSerializedSize.return:28
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetSpeedLimitRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetSpeedLimitRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.speed_limit_request_:5.0
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetSpeedLimitRequest.return:5.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetSteerAutoMode

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetSteerAutoMode
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.steer_auto_mode_:true
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetSteerAutoMode.return:true
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetSteeringAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetSteeringAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.steering_angle_:5.0
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetSteeringAngle.return:5.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetStopDistRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetStopDistRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.stop_dist_request_:5.0
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetStopDistRequest.return:5.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetTargetGearRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetTargetGearRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.target_gear_request_:5
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetTargetGearRequest.return:5
TEST.END

-- Subprogram: holo::common::ApaControlCommand::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:apa_control_command.holo::common::ApaControlCommand::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::ApaControlCommand::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetApafailBrkmodeRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetApafailBrkmodeRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetApafailBrkmodeRequest.apafail_brkmode_request:5
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.apafail_brkmode_request_:5
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetLonAutoMode

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetLonAutoMode
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetLonAutoMode.lon_auto_mode:true
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.lon_auto_mode_:true
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetSpeedLimitRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetSpeedLimitRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetSpeedLimitRequest.speed_limit_request:5.0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.speed_limit_request_:5.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetSteerAutoMode

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetSteerAutoMode
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetSteerAutoMode.steer_auto_mode:true
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.steer_auto_mode_:true
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetSteeringAngle

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetSteeringAngle
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetSteeringAngle.steering_angle:5.0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.steering_angle_:5.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetStopDistRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetStopDistRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetStopDistRequest.stop_dist_request:5.0
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.stop_dist_request_:5.0
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetTargetGearRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetTargetGearRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetTargetGearRequest.target_gear_request:5
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.target_gear_request_:5
TEST.END

-- Subprogram: holo::common::ApaControlCommand::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:apa_control_command
TEST.SUBPROGRAM:holo::common::ApaControlCommand::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.<<constructor>>.ApaControlCommand().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:apa_control_command.holo::common::ApaControlCommand::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:apa_control_command.<<GLOBAL>>.(cl).holo::common::ApaControlCommand.holo::common::ApaControlCommand.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END
