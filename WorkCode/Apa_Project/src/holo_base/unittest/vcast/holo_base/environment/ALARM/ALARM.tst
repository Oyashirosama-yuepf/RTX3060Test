-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : ALARM
-- Unit(s) Under Test: alarm
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

-- Unit: alarm

-- Subprogram: holo::common::Alarm::Alarm()

-- Test Case: BASIS-PATH-001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::Alarm()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:0
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:0
TEST.END

-- Subprogram: holo::common::Alarm::Alarm(holo::common::Alarm::UnderlyingType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::Alarm(holo::common::Alarm::UnderlyingType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:alarm.holo::common::Alarm::Alarm(holo::common::Alarm::UnderlyingType).value:24588
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:12
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.END

-- Subprogram: holo::common::Alarm::GetLevel

-- Test Case: BASIS-PATH-001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::GetLevel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:3
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:4
TEST.EXPECTED:alarm.holo::common::Alarm::GetLevel.return:FATAL_2
TEST.END

-- Subprogram: holo::common::Alarm::operator holo::uint16_t

-- Test Case: holo::common::Alarm::operatorholo::uint16_t.001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator holo::uint16_t
TEST.NEW
TEST.NAME:holo::common::Alarm::operatorholo::uint16_t.001
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:12
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.EXPECTED:alarm.holo::common::Alarm::operator holo::uint16_t.return:24588
TEST.END

-- Subprogram: holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this == rhs)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:1
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:2
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.code_:3
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.level_:4
TEST.EXPECTED:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this == rhs)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:1
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:2
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.code_:1
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.level_:2
TEST.EXPECTED:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this == rhs)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:5
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const.rhs:24589
TEST.EXPECTED:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this == rhs)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:12
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.VALUE:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const.rhs:24588
TEST.EXPECTED:alarm.holo::common::Alarm::operator!=(const holo::common::Alarm::UnderlyingType)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::Alarm::operator=

-- Test Case: BASIS-PATH-001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:0
TEST.VALUE:alarm.holo::common::Alarm::operator=.value:24588
TEST.VALUE:alarm.holo::common::Alarm::operator=.return.holo::common::Alarm.<<constructor>>.Alarm(holo::common::Alarm::UnderlyingType).value:24588
TEST.VALUE:alarm.holo::common::Alarm::operator=.return.holo::common::Alarm.<<constructor>>.Alarm(holo::common::Alarm::UnderlyingType).<<call>>:0
TEST.VALUE:alarm.holo::common::Alarm::operator=.return.holo::common::Alarm.code_:0
TEST.VALUE:alarm.holo::common::Alarm::operator=.return.holo::common::Alarm.level_:0
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:12
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.EXPECTED:alarm.holo::common::Alarm::operator=.return.holo::common::Alarm.code_:12
TEST.EXPECTED:alarm.holo::common::Alarm::operator=.return.holo::common::Alarm.level_:3
TEST.END

-- Subprogram: holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (static_cast< holo::common::Alarm::UnderlyingType>((*this)) == static_cast< holo::common::Alarm::UnderlyingType>(rhs)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Alarm::operator holo::common::Alarm::UnderlyingType in branch 1
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:3
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:4
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.code_:3
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.level_:4
TEST.EXPECTED:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (static_cast< holo::common::Alarm::UnderlyingType>((*this)) == static_cast< holo::common::Alarm::UnderlyingType>(rhs)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set return value of function holo::common::Alarm::operator holo::common::Alarm::UnderlyingType in branch 1
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:3
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:4
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.code_:5
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.rhs.holo::common::Alarm.level_:6
TEST.EXPECTED:alarm.holo::common::Alarm::operator==(const holo::common::Alarm)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (static_cast< holo::common::Alarm::UnderlyingType>((*this)) == rhs) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:12
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const.rhs:24588
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:12
TEST.EXPECTED:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.EXPECTED:alarm.holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (static_cast< holo::common::Alarm::UnderlyingType>((*this)) == rhs) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.code_:20
TEST.VALUE:alarm.<<GLOBAL>>.(cl).holo::common::Alarm.holo::common::Alarm.level_:3
TEST.VALUE:alarm.holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const.rhs:24588
TEST.EXPECTED:alarm.holo::common::Alarm::operator==(const holo::common::Alarm::UnderlyingType)holo::bool_t const.return:false
TEST.END

-- Subprogram: holo::common::operator!=

-- Test Case: holo::common::operator!=.001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::operator!=
TEST.NEW
TEST.NAME:holo::common::operator!=.001
TEST.VALUE:alarm.holo::common::operator!=.lhs:24588
TEST.VALUE:alarm.holo::common::operator!=.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::operator!=.rhs.holo::common::Alarm.code_:12
TEST.VALUE:alarm.holo::common::operator!=.rhs.holo::common::Alarm.level_:4
TEST.EXPECTED:alarm.holo::common::operator!=.return:true
TEST.END

-- Test Case: holo::common::operator!=.002
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::operator!=
TEST.NEW
TEST.NAME:holo::common::operator!=.002
TEST.VALUE:alarm.holo::common::operator!=.lhs:24588
TEST.VALUE:alarm.holo::common::operator!=.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::operator!=.rhs.holo::common::Alarm.code_:12
TEST.VALUE:alarm.holo::common::operator!=.rhs.holo::common::Alarm.level_:3
TEST.EXPECTED:alarm.holo::common::operator!=.return:false
TEST.END

-- Subprogram: holo::common::operator==

-- Test Case: holo::common::operator==.001
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::operator==
TEST.NEW
TEST.NAME:holo::common::operator==.001
TEST.VALUE:alarm.holo::common::operator==.lhs:24588
TEST.VALUE:alarm.holo::common::operator==.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::operator==.rhs.holo::common::Alarm.code_:12
TEST.VALUE:alarm.holo::common::operator==.rhs.holo::common::Alarm.level_:3
TEST.EXPECTED:alarm.holo::common::operator==.return:true
TEST.END

-- Test Case: holo::common::operator==.002
TEST.UNIT:alarm
TEST.SUBPROGRAM:holo::common::operator==
TEST.NEW
TEST.NAME:holo::common::operator==.002
TEST.VALUE:alarm.holo::common::operator==.lhs:24589
TEST.VALUE:alarm.holo::common::operator==.rhs.holo::common::Alarm.<<constructor>>.Alarm().<<call>>:0
TEST.VALUE:alarm.holo::common::operator==.rhs.holo::common::Alarm.code_:12
TEST.VALUE:alarm.holo::common::operator==.rhs.holo::common::Alarm.level_:3
TEST.EXPECTED:alarm.holo::common::operator==.return:false
TEST.END
