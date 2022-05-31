-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : LIGHT_SIGNAL_REQUEST
-- Unit(s) Under Test: light_signal_request
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

-- Unit: light_signal_request

-- Subprogram: holo::LightSignalRequest::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.END

-- Subprogram: holo::LightSignalRequest::GetBrakeLight

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetBrakeLight
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.brake_light_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetBrakeLight.return:true
TEST.END

-- Subprogram: holo::LightSignalRequest::GetHazardFlasher

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetHazardFlasher
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.hazard_flasher_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetHazardFlasher.return:true
TEST.END

-- Subprogram: holo::LightSignalRequest::GetLeftTurnSignal

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetLeftTurnSignal
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.left_turn_signal_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetLeftTurnSignal.return:true
TEST.END

-- Subprogram: holo::LightSignalRequest::GetLightCommand

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetLightCommand
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.brake_light_:1
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.hazard_flasher_:1
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.right_turn_signal_:1
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.left_turn_signal_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetLightCommand.return:228
TEST.END

-- Subprogram: holo::LightSignalRequest::GetRightTurnSignal

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetRightTurnSignal
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.right_turn_signal_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetRightTurnSignal.return:true
TEST.END

-- Subprogram: holo::LightSignalRequest::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetSerializedSize.return:16
TEST.END

-- Subprogram: holo::LightSignalRequest::GetTimestamp()const holo::LightSignalRequest::Timestamp const

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetTimestamp()const holo::LightSignalRequest::Timestamp const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetTimestamp()const holo::LightSignalRequest::Timestamp const.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetTimestamp()const holo::LightSignalRequest::Timestamp const.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::LightSignalRequest::GetTimestamp()holo::LightSignalRequest::Timestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::GetTimestamp()holo::LightSignalRequest::Timestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetTimestamp()holo::LightSignalRequest::Timestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:light_signal_request.holo::LightSignalRequest::GetTimestamp()holo::LightSignalRequest::Timestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::LightSignalRequest::LightSignalRequest

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::LightSignalRequest
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.brake_light_:0
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.hazard_flasher_:0
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.right_turn_signal_:0
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.left_turn_signal_:0
TEST.END

-- Subprogram: holo::LightSignalRequest::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.END

-- Subprogram: holo::LightSignalRequest::SetBrakeLight

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::SetBrakeLight
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetBrakeLight.brake_light:true
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.brake_light_:1
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.hazard_flasher_:0
TEST.END

-- Subprogram: holo::LightSignalRequest::SetHazardFlasher

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::SetHazardFlasher
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetHazardFlasher.hazard_flasher:true
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.hazard_flasher_:1
TEST.END

-- Subprogram: holo::LightSignalRequest::SetLeftTurnSignal

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::SetLeftTurnSignal
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetLeftTurnSignal.left_turn_signal:true
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.left_turn_signal_:1
TEST.END

-- Subprogram: holo::LightSignalRequest::SetLightCommand

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::SetLightCommand
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetLightCommand.value:228
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.brake_light_:1
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.hazard_flasher_:1
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.right_turn_signal_:1
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.left_turn_signal_:1
TEST.END

-- Subprogram: holo::LightSignalRequest::SetRightTurnSignal

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::SetRightTurnSignal
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetRightTurnSignal.right_turn_signal:true
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.light_command_.right_turn_signal_:1
TEST.END

-- Subprogram: holo::LightSignalRequest::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:light_signal_request
TEST.SUBPROGRAM:holo::LightSignalRequest::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.<<constructor>>.LightSignalRequest().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:light_signal_request.holo::LightSignalRequest::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:light_signal_request.<<GLOBAL>>.(cl).holo::LightSignalRequest.holo::LightSignalRequest.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END
