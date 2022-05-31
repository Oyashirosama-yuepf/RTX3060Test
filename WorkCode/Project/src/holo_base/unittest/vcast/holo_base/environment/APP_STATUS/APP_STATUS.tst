-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : APP_STATUS
-- Unit(s) Under Test: app_status
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

-- Unit: app_status

-- Subprogram: holo::common::AppStatus::AppStatus()

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::AppStatus()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.node_id_:0
TEST.END

-- Subprogram: holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).sec:1
TEST.VALUE:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).nsec:2
TEST.VALUE:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).<<call>>:0
TEST.VALUE:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).node_id:3
TEST.EXPECTED:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).sec:1
TEST.EXPECTED:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).nsec:2
TEST.EXPECTED:app_status.holo::common::AppStatus::AppStatus(const holo::common::Timestamp&,holo::uint8_t).node_id:3
TEST.END

-- Subprogram: holo::common::AppStatus::GetNodeId

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::GetNodeId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.node_id_:3
TEST.EXPECTED:app_status.holo::common::AppStatus::GetNodeId.return:3
TEST.END

-- Subprogram: holo::common::AppStatus::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.EXPECTED:app_status.holo::common::AppStatus::GetSerializedSize.return:12
TEST.END

-- Subprogram: holo::common::AppStatus::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:app_status.holo::common::AppStatus::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:app_status.holo::common::AppStatus::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::AppStatus::SetNodeId

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::SetNodeId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.holo::common::AppStatus::SetNodeId.node_id:3
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.node_id_:3
TEST.END

-- Subprogram: holo::common::AppStatus::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.holo::common::AppStatus::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:app_status.holo::common::AppStatus::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:app_status.holo::common::AppStatus::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::AppStatus::max_size

-- Test Case: holo::common::AppStatus::max_size.001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::max_size
TEST.NEW
TEST.NAME:holo::common::AppStatus::max_size.001
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_:<<malloc 4>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:1
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:<<function 1>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:2
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:<<function 1>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[2]:3
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[2]:<<function 1>>
TEST.EXPECTED:app_status.holo::common::AppStatus::max_size.return:255
TEST.END

-- Subprogram: holo::common::AppStatus::pop_back

-- Test Case: holo::common::AppStatus::pop_back.001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::pop_back
TEST.NEW
TEST.NAME:holo::common::AppStatus::pop_back.001
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_:<<malloc 3>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:1
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:<<function 1>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:2
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:<<function 1>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[2]:3
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[2]:<<function 1>>
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:1
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:2
TEST.END

-- Subprogram: holo::common::AppStatus::push_back(const holo::uint8_t&)

-- Test Case: holo::common::AppStatus::push_back(constholo::uint8_t&).001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::push_back(const holo::uint8_t&)
TEST.NEW
TEST.NAME:holo::common::AppStatus::push_back(constholo::uint8_t&).001
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.holo::common::AppStatus::push_back(const holo::uint8_t&).value:3
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:3
TEST.END

-- Subprogram: holo::common::AppStatus::push_back(holo::uint8_t&&)

-- Test Case: holo::common::AppStatus::push_back(holo::uint8_t&&).001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::push_back(holo::uint8_t&&)
TEST.NEW
TEST.NAME:holo::common::AppStatus::push_back(holo::uint8_t&&).001
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.holo::common::AppStatus::push_back(holo::uint8_t&&).value:5
TEST.EXPECTED:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:5
TEST.END

-- Subprogram: holo::common::AppStatus::size

-- Test Case: holo::common::AppStatus::size.001
TEST.UNIT:app_status
TEST.SUBPROGRAM:holo::common::AppStatus::size
TEST.NEW
TEST.NAME:holo::common::AppStatus::size.001
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.<<constructor>>.AppStatus().<<call>>:0
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_:<<malloc 3>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:1
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[0]:<<function 1>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:2
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[1]:<<function 1>>
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[2]:3
TEST.VALUE:app_status.<<GLOBAL>>.(cl).holo::common::AppStatus.holo::common::AppStatus.container_[2]:<<function 1>>
TEST.EXPECTED:app_status.holo::common::AppStatus::size.return:3
TEST.END
