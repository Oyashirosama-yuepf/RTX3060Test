-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : TIMESTAMP
-- Unit(s) Under Test: timestamp
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

-- Unit: timestamp

-- Subprogram: holo::common::details::Duration::Duration()

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:0
TEST.END

-- Subprogram: holo::common::details::Duration::Duration(holo::float64_t)

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::float64_t)
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MAX_NSEC / holo::common::details::Duration::NSEC_PER_SEC + (1)) || t < static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MIN_NSEC / holo::common::details::Duration::NSEC_PER_SEC)) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::float64_t).t:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::Duration(holo::float64_t).<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::float64_t)
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MAX_NSEC / holo::common::details::Duration::NSEC_PER_SEC + (1)) || t < static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MIN_NSEC / holo::common::details::Duration::NSEC_PER_SEC)) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::float64_t).t:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::Duration(holo::float64_t).<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-TEMPLATE
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::float64_t)
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-TEMPLATE
TEST.MCDC_BASIS_PATH:1 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MAX_NSEC / holo::common::details::Duration::NSEC_PER_SEC + (1)) || t < static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MIN_NSEC / holo::common::details::Duration::NSEC_PER_SEC)) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Conflict: Cannot resolve multiple comparisons ( timestamp.holo::common::details::Duration::Duration(holo::float64_t).t ) in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::float64_t).t:900.0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:900
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-TEMPLATE
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::float64_t)
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-TEMPLATE
TEST.MCDC_BASIS_PATH:4 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MAX_NSEC / holo::common::details::Duration::NSEC_PER_SEC + (1)) || t < static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MIN_NSEC / holo::common::details::Duration::NSEC_PER_SEC)) ==> FALSE
      (2) (value > holo::common::details::Duration::DURATION_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable nsec in branch 2
      Conflict: Cannot resolve multiple comparisons ( timestamp.holo::common::details::Duration::Duration(holo::float64_t).t ) in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::float64_t).t:<<MAX>>
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration:<<null>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::Duration(holo::float64_t).<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-TEMPLATE
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::float64_t)
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-TEMPLATE
TEST.MCDC_BASIS_PATH:5 of 5
TEST.NOTES:
This is an automatically generated test case.
   Test Path 5
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MAX_NSEC / holo::common::details::Duration::NSEC_PER_SEC + (1)) || t < static_cast< holo::float64_t>(holo::common::details::Duration::DURATION_MIN_NSEC / holo::common::details::Duration::NSEC_PER_SEC)) ==> FALSE
      (2) (value > holo::common::details::Duration::DURATION_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable nsec in branch 2
      Conflict: Cannot resolve multiple comparisons ( timestamp.holo::common::details::Duration::Duration(holo::float64_t).t ) in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::float64_t).t:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::Duration(holo::float64_t).<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Subprogram: holo::common::details::Duration::Duration(holo::int32_t,holo::int32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::int32_t,holo::int32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::int32_t,holo::int32_t).sec:5
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::int32_t,holo::int32_t).nsec:8
TEST.EXPECTED:timestamp.holo::common::details::Duration::Duration(holo::int32_t,holo::int32_t).sec:5
TEST.EXPECTED:timestamp.holo::common::details::Duration::Duration(holo::int32_t,holo::int32_t).nsec:8
TEST.END

-- Subprogram: holo::common::details::Duration::Duration(holo::int64_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::Duration(holo::int64_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Duration::Duration(holo::int64_t).t:2000000001
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:2
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:1
TEST.END

-- Subprogram: holo::common::details::Duration::GetNsec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::GetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nsec < 0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::GetNsec.return:-1147483648
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::GetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nsec < 0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::GetNsec.return:2147483647
TEST.END

-- Subprogram: holo::common::details::Duration::GetSec

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::GetSec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (this->nsec_ < 0) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:-3
TEST.EXPECTED:timestamp.holo::common::details::Duration::GetSec.return:4
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::GetSec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (this->nsec_ < 0) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:3
TEST.EXPECTED:timestamp.holo::common::details::Duration::GetSec.return:5
TEST.END

-- Subprogram: holo::common::details::Duration::IsEqual

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::IsEqual
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (std::abs(this->ToNsec() - rhs.ToNsec()) <= tolerance_nsec) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.rhs.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.rhs.holo::common::details::Duration.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Duration::IsEqual.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::IsEqual
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (std::abs(this->ToNsec() - rhs.ToNsec()) <= tolerance_nsec) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.rhs.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.rhs.holo::common::details::Duration.nsec_:6
TEST.VALUE:timestamp.holo::common::details::Duration::IsEqual.tolerance_nsec:0
TEST.EXPECTED:timestamp.holo::common::details::Duration::IsEqual.return:false
TEST.END

-- Subprogram: holo::common::details::Duration::IsZero

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::IsZero
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() == (0)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:0
TEST.EXPECTED:timestamp.holo::common::details::Duration::IsZero.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::IsZero
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() == (0)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Duration::ToNsec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::ToNsec.return:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::IsZero.return:false
TEST.END

-- Subprogram: holo::common::details::Duration::SetNsec

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::SetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nseconds > holo::common::details::Duration::NSEC_PER_SEC - 1 || nseconds < -holo::common::details::Duration::NSEC_PER_SEC + 1) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::SetNsec.nseconds:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::SetNsec.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::SetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (nseconds > holo::common::details::Duration::NSEC_PER_SEC - 1 || nseconds < -holo::common::details::Duration::NSEC_PER_SEC + 1) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::SetNsec.nseconds:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::SetNsec.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::SetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nseconds > holo::common::details::Duration::NSEC_PER_SEC - 1 || nseconds < -holo::common::details::Duration::NSEC_PER_SEC + 1) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::SetNsec.nseconds:-999999999
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:-999999999
TEST.END

-- Subprogram: holo::common::details::Duration::SetSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::SetSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:0
TEST.VALUE:timestamp.holo::common::details::Duration::SetSec.seconds:4
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:4
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:0
TEST.END

-- Subprogram: holo::common::details::Duration::ToNsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::ToNsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:7
TEST.EXPECTED:timestamp.holo::common::details::Duration::ToNsec.return:4000000007
TEST.END

-- Subprogram: holo::common::details::Duration::ToSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::ToSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:9
TEST.EXPECTED:timestamp.holo::common::details::Duration::ToSec.return:7.0
TEST.END

-- Subprogram: holo::common::details::Duration::ToString

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::ToString
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Duration::ToString.return:"Duration: (1, 2)\n"
TEST.END

-- Subprogram: holo::common::details::Duration::assignFromNsecValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::assignFromNsecValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::assignFromNsecValue.value:2000000001
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:2
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:1
TEST.END

-- Subprogram: holo::common::details::Duration::checkValue

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::checkValue
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > holo::common::details::Duration::DURATION_MAX_NSEC || value < holo::common::details::Duration::DURATION_MIN_NSEC) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::checkValue.value:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::checkValue.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::checkValue
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > holo::common::details::Duration::DURATION_MAX_NSEC || value < holo::common::details::Duration::DURATION_MIN_NSEC) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::checkValue.value:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::checkValue.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::checkValue
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > holo::common::details::Duration::DURATION_MAX_NSEC || value < holo::common::details::Duration::DURATION_MIN_NSEC) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::checkValue.value:2000000001
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:0
TEST.END

-- Subprogram: holo::common::details::Duration::operator!=

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator!=
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
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:6
TEST.VALUE:timestamp.holo::common::details::Duration::operator!=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator!=.rhs.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.holo::common::details::Duration::operator!=.rhs.holo::common::details::Duration.nsec_:8
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator!=.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator!=
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
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:5
TEST.VALUE:timestamp.holo::common::details::Duration::operator!=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator!=.rhs.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.holo::common::details::Duration::operator!=.rhs.holo::common::details::Duration.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator!=.return:false
TEST.END

-- Subprogram: holo::common::details::Duration::operator*

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator*
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator*.rhs:2.0
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator*.return.holo::common::details::Duration.sec_:6
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator*.return.holo::common::details::Duration.nsec_:8
TEST.END

-- Subprogram: holo::common::details::Duration::operator*=

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator*=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator*=.scale:2.0
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator*=.return.holo::common::details::Duration.sec_:6
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator*=.return.holo::common::details::Duration.nsec_:8
TEST.END

-- Subprogram: holo::common::details::Duration::operator+

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator+
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:2
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:3
TEST.VALUE:timestamp.holo::common::details::Duration::operator+.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator+.rhs.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator+.rhs.holo::common::details::Duration.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator+.return.holo::common::details::Duration.sec_:6
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator+.return.holo::common::details::Duration.nsec_:8
TEST.END

-- Subprogram: holo::common::details::Duration::operator+=

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator+=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator+=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator+=.rhs.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator+=.rhs.holo::common::details::Duration.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator+=.return.holo::common::details::Duration.sec_:7
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator+=.return.holo::common::details::Duration.nsec_:9
TEST.END

-- Subprogram: holo::common::details::Duration::operator-()holo::common::details::Duration const

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator-()holo::common::details::Duration const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:8
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator-()holo::common::details::Duration const.return.holo::common::details::Duration.sec_:-7
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator-()holo::common::details::Duration const.return.holo::common::details::Duration.nsec_:-8
TEST.END

-- Subprogram: holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:6
TEST.VALUE:timestamp.holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const.rhs.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const.rhs.holo::common::details::Duration.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const.return.holo::common::details::Duration.sec_:1
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator-(const holo::common::details::Duration&)holo::common::details::Duration const.return.holo::common::details::Duration.nsec_:1
TEST.END

-- Subprogram: holo::common::details::Duration::operator-=

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator-=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:9
TEST.VALUE:timestamp.holo::common::details::Duration::operator-=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator-=.rhs.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.holo::common::details::Duration::operator-=.rhs.holo::common::details::Duration.nsec_:7
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator-=.return.holo::common::details::Duration.sec_:2
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator-=.return.holo::common::details::Duration.nsec_:2
TEST.END

-- Subprogram: holo::common::details::Duration::operator<

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator<
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() < rhs.ToNsec()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.holo::common::details::Duration::ToNsec.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator<.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator<.rhs.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.holo::common::details::Duration::operator<.rhs.holo::common::details::Duration.nsec_:6
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator<.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator<
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() < rhs.ToNsec()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Duration::ToNsec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator<.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator<.rhs.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.holo::common::details::Duration::operator<.rhs.holo::common::details::Duration.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Duration::ToNsec.return:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator<.return:false
TEST.END

-- Subprogram: holo::common::details::Duration::operator<=

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator<=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this > rhs)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator<=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator<=.rhs.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.holo::common::details::Duration::operator<=.rhs.holo::common::details::Duration.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator<=.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator<=
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this > rhs)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:8
TEST.VALUE:timestamp.holo::common::details::Duration::operator<=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator<=.rhs.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.holo::common::details::Duration::operator<=.rhs.holo::common::details::Duration.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator<=.return:false
TEST.END

-- Subprogram: holo::common::details::Duration::operator==

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() == rhs.ToNsec()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Duration::ToNsec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:6
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:7
TEST.VALUE:timestamp.holo::common::details::Duration::operator==.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator==.rhs.holo::common::details::Duration.sec_:6
TEST.VALUE:timestamp.holo::common::details::Duration::operator==.rhs.holo::common::details::Duration.nsec_:7
TEST.VALUE:timestamp.holo::common::details::Duration::ToNsec.return:-9223372036854775808
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() == rhs.ToNsec()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:6
TEST.VALUE:timestamp.holo::common::details::Duration::operator==.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator==.rhs.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.holo::common::details::Duration::operator==.rhs.holo::common::details::Duration.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator==.return:false
TEST.END

-- Subprogram: holo::common::details::Duration::operator>

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator>
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() > rhs.ToNsec()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:8
TEST.VALUE:timestamp.holo::common::details::Duration::operator>.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator>.rhs.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator>.rhs.holo::common::details::Duration.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator>.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator>
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() > rhs.ToNsec()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Duration::operator>.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator>.rhs.holo::common::details::Duration.sec_:5
TEST.VALUE:timestamp.holo::common::details::Duration::operator>.rhs.holo::common::details::Duration.nsec_:6
TEST.END

-- Subprogram: holo::common::details::Duration::operator>=

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator>=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this < rhs)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:6
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:7
TEST.VALUE:timestamp.holo::common::details::Duration::operator>=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator>=.rhs.holo::common::details::Duration.sec_:2
TEST.VALUE:timestamp.holo::common::details::Duration::operator>=.rhs.holo::common::details::Duration.nsec_:3
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator>=.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Duration::operator>=
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this < rhs)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration.holo::common::details::Duration.nsec_:5
TEST.VALUE:timestamp.holo::common::details::Duration::operator>=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Duration::operator>=.rhs.holo::common::details::Duration.sec_:7
TEST.VALUE:timestamp.holo::common::details::Duration::operator>=.rhs.holo::common::details::Duration.nsec_:8
TEST.EXPECTED:timestamp.holo::common::details::Duration::operator>=.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::GetNsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::GetNsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::GetNsec.return:5
TEST.END

-- Subprogram: holo::common::details::Timestamp::GetSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::GetSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:10
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::GetSec.return:10
TEST.END

-- Subprogram: holo::common::details::Timestamp::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::GetSerializedSize.return:8
TEST.END

-- Subprogram: holo::common::details::Timestamp::GpsToUtc

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::GpsToUtc
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (gps.GetSec() > holo::common::details::Timestamp::kLatestLeapSecondGps) ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::GetSec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::GpsToUtc.gps.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::GpsToUtc.utc.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::GetSec.return:<<MIN>>
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::GpsToUtc
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (gps.GetSec() > holo::common::details::Timestamp::kLatestLeapSecondGps) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::GetSec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::GpsToUtc.gps.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::GpsToUtc.utc.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::GetSec.return:<<MAX>>
TEST.END

-- Subprogram: holo::common::details::Timestamp::IsEqual

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::IsEqual
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (std::abs(this->ToNsec() - rhs.ToNsec()) <= tolerance_nsec) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.rhs.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.tolerance_nsec:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::IsEqual.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::IsEqual
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (std::abs(this->ToNsec() - rhs.ToNsec()) <= tolerance_nsec) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.rhs.holo::common::details::Timestamp.sec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.rhs.holo::common::details::Timestamp.nsec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::IsEqual.tolerance_nsec:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::IsEqual.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::IsZero

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::IsZero
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() == (0)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::ToNsec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::ToNsec.return:0
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::IsZero.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::IsZero
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() == (0)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::ToNsec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::ToNsec.return:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::IsZero.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::SetNsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::SetNsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nseconds >= holo::common::details::Timestamp::NSEC_PER_SEC) ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::SetNsec.nseconds:50
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:50
TEST.END

-- Test Case: BASIS-PATH-002
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::SetNsec
TEST.NEW
TEST.NAME:BASIS-PATH-002
TEST.BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nseconds >= holo::common::details::Timestamp::NSEC_PER_SEC) ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::SetNsec.nseconds:1000000000
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::SetNsec.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::SetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (nseconds >= holo::common::details::Timestamp::NSEC_PER_SEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::SetNsec.nseconds:1000000000
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::SetNsec.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::SetNsec
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (nseconds >= holo::common::details::Timestamp::NSEC_PER_SEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::SetNsec.nseconds:5
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::SetNsec.<<throw>>.holo::common::details::OverflowException:<<null>>
TEST.END

-- Subprogram: holo::common::details::Timestamp::SetSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::SetSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::SetSec.seconds:5
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:5
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:0
TEST.END

-- Subprogram: holo::common::details::Timestamp::Timestamp()

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:0
TEST.END

-- Subprogram: holo::common::details::Timestamp::Timestamp(holo::float64_t)

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp(holo::float64_t)
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC / holo::common::details::Timestamp::NSEC_PER_SEC + (1U))) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).t:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp(holo::float64_t)
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC / holo::common::details::Timestamp::NSEC_PER_SEC + (1U))) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).t:5.000006
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Duration:<<null>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).<<throw>>.holo::common::details::OverflowException:<<null>>
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp(holo::float64_t)
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC / holo::common::details::Timestamp::NSEC_PER_SEC + (1U))) ==> FALSE
      (2) (value > holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable nsec in branch 2
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).t:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp(holo::float64_t)
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (t >= static_cast< holo::float64_t>(holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC / holo::common::details::Timestamp::NSEC_PER_SEC + (1U))) ==> FALSE
      (2) (value > holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable nsec in branch 2
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).t:5.000006
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::Timestamp(holo::float64_t).<<throw>>.holo::common::details::OverflowException:<<null>>
TEST.END

-- Subprogram: holo::common::details::Timestamp::Timestamp(holo::uint32_t,holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp(holo::uint32_t,holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::uint32_t,holo::uint32_t).sec:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::uint32_t,holo::uint32_t).nsec:4
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::Timestamp(holo::uint32_t,holo::uint32_t).sec:3
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::Timestamp(holo::uint32_t,holo::uint32_t).nsec:4
TEST.END

-- Subprogram: holo::common::details::Timestamp::Timestamp(holo::uint64_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::Timestamp(holo::uint64_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::Timestamp::Timestamp(holo::uint64_t).t:5
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:5
TEST.END

-- Subprogram: holo::common::details::Timestamp::ToNsec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::ToNsec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:3
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::ToNsec.return:3
TEST.END

-- Subprogram: holo::common::details::Timestamp::ToSec

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::ToSec
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::ToSec.return:3.0
TEST.END

-- Subprogram: holo::common::details::Timestamp::ToString

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::ToString
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::ToString.return:"Timestamp: (1, 2)\n"
TEST.END

-- Subprogram: holo::common::details::Timestamp::UtcToGps

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::UtcToGps
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (utc.GetSec() > holo::common::details::Timestamp::kLatestLeapSecondUtc) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::GetSec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.utc.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.utc.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.utc.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.gps.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.gps.holo::common::details::Timestamp.sec_:4
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.gps.holo::common::details::Timestamp.nsec_:5
TEST.VALUE:timestamp.holo::common::details::Timestamp::GetSec.return:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::UtcToGps.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::UtcToGps
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (utc.GetSec() > holo::common::details::Timestamp::kLatestLeapSecondUtc) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::GetSec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.utc.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.utc.holo::common::details::Timestamp.sec_:1000000
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.utc.holo::common::details::Timestamp.nsec_:1000000
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.gps.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.gps.holo::common::details::Timestamp.sec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::UtcToGps.gps.holo::common::details::Timestamp.nsec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::GetSec.return:<<MIN>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::UtcToGps.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::assignFromNsecValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::assignFromNsecValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::assignFromNsecValue.value:2000000001
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:2
TEST.EXPECTED:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:1
TEST.END

-- Subprogram: holo::common::details::Timestamp::checkValue

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::checkValue
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (value > holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC || value < holo::common::details::Timestamp::TIMESTAMP_MIN_NSEC) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::checkValue.value:9223372036854775807
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::checkValue.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::checkValue
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (value > holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC || value < holo::common::details::Timestamp::TIMESTAMP_MIN_NSEC) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::checkValue.value:-9223372036854775808
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::checkValue.<<throw>>.holo::common::details::OverflowException.holo::common::details::OverflowException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::checkValue
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (value > holo::common::details::Timestamp::TIMESTAMP_MAX_NSEC || value < holo::common::details::Timestamp::TIMESTAMP_MIN_NSEC) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::checkValue.value:5
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::checkValue.value:5
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator!=

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator!=
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
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator!=.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator!=.rhs.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator!=.rhs.holo::common::details::Timestamp.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator!=.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator!=
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
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator!=.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator!=.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator!=.rhs.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator!=.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator+

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator+
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator+.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator+.rhs.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator+.rhs.holo::common::details::Duration.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator+.return.holo::common::details::Timestamp.sec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator+.return.holo::common::details::Timestamp.nsec_:4
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator+=

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator+=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator+=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator+=.rhs.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator+=.rhs.holo::common::details::Duration.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator+=.return.holo::common::details::Timestamp.sec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator+=.return.holo::common::details::Timestamp.nsec_:4
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:4
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:5
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const.rhs.holo::common::details::Duration.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const.rhs.holo::common::details::Duration.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const.return.holo::common::details::Timestamp.sec_:3
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Duration&)holo::common::details::Timestamp const.return.holo::common::details::Timestamp.nsec_:3
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:4
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:5
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const.rhs.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const.rhs.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const.return:<<null>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const.return.holo::common::details::Duration.sec_:1
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator-(const holo::common::details::Timestamp&)holo::common::details::Duration const.return.holo::common::details::Duration.nsec_:3
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator-=

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator-=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-=.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-=.rhs.holo::common::details::Duration.sec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator-=.rhs.holo::common::details::Duration.nsec_:3
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator-=.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator-=.return.holo::common::details::Timestamp.nsec_:1
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator<

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator<
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:2
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.sec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator<.return:true
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator<
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() < rhs.ToNsec()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Conflict: Trying to set variable timestamp.holo::common::details::Timestamp::ToNsec.return 'less than' and 'greater than' same value in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.sec_:20
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.nsec_:40
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator<.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator<
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() < rhs.ToNsec()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:timestamp.holo::common::details::Timestamp::ToNsec
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<.rhs.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::ToNsec.return:<<MAX>>
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator<.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator<=

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator<=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this > rhs)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<=.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<=.rhs.holo::common::details::Timestamp.sec_:4
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<=.rhs.holo::common::details::Timestamp.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator<=.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator<=
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this > rhs)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:4
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:5
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<=.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<=.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator<=.rhs.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator<=.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator==

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() == rhs.ToNsec()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator==.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator==.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator==.rhs.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() == rhs.ToNsec()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator==.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator==.rhs.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator==.rhs.holo::common::details::Timestamp.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator==.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator>

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator>
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->ToNsec() > rhs.ToNsec()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set a value greater than the maximum in branch 1
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:4
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>.rhs.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator>.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator>
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->ToNsec() > rhs.ToNsec()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>.rhs.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>.rhs.holo::common::details::Timestamp.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator>.return:false
TEST.END

-- Subprogram: holo::common::details::Timestamp::operator>=

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator>=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(*this < rhs)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:5
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:6
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>=.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>=.rhs.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>=.rhs.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator>=.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::Timestamp::operator>=
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(*this < rhs)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:timestamp.<<GLOBAL>>.(cl).holo::common::details::Timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>=.rhs.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>=.rhs.holo::common::details::Timestamp.sec_:3
TEST.VALUE:timestamp.holo::common::details::Timestamp::operator>=.rhs.holo::common::details::Timestamp.nsec_:4
TEST.EXPECTED:timestamp.holo::common::details::Timestamp::operator>=.return:false
TEST.END

-- Subprogram: holo::common::details::operator*

-- Test Case: BASIS-PATH-001
TEST.UNIT:timestamp
TEST.SUBPROGRAM:holo::common::details::operator*
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:timestamp.holo::common::details::operator*.lhs:3.0
TEST.VALUE:timestamp.holo::common::details::operator*.rhs.holo::common::details::Duration.<<constructor>>.Duration().<<call>>:0
TEST.VALUE:timestamp.holo::common::details::operator*.rhs.holo::common::details::Duration.sec_:4
TEST.VALUE:timestamp.holo::common::details::operator*.rhs.holo::common::details::Duration.nsec_:5
TEST.EXPECTED:timestamp.holo::common::details::operator*.return.holo::common::details::Duration.sec_:12
TEST.EXPECTED:timestamp.holo::common::details::operator*.return.holo::common::details::Duration.nsec_:15
TEST.END
