-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : CLASSIFICATION
-- Unit(s) Under Test: classification
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

-- Unit: classification

-- Subprogram: holo::common::details::Classification::Classification()

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:UNKNOWN
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.END

-- Subprogram: holo::common::details::Classification::Classification(const holo::common::details::Classification::MainType,const holo::common::details::Classification::SubType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification(const holo::common::details::Classification::MainType,const holo::common::details::Classification::SubType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::common::details::Classification::MainType,const holo::common::details::Classification::SubType).main_type:BIKE
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::common::details::Classification::MainType,const holo::common::details::Classification::SubType).sub_type:CAR
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:CAR
TEST.END

-- Subprogram: holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t)

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t)
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (this->IsValidMainType(main_type) == (false)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:classification.holo::common::details::Classification::IsValidMainType
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).main_type:44
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).sub_type:22
TEST.VALUE:classification.holo::common::details::Classification::IsValidMainType.return:false
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t)
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (this->IsValidMainType(main_type) == (false)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:classification.holo::common::details::Classification::IsValidMainType
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).main_type:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).sub_type:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::IsValidMainType.return:true
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t)
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) if (this->IsValidMainType(main_type) == (false)) ==> FALSE
      (2) if (this->IsValidSubType(sub_type) == (false)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:classification.holo::common::details::Classification::IsValidMainType
TEST.STUB:classification.holo::common::details::Classification::IsValidSubType
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).main_type:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).sub_type:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::IsValidMainType.return:true
TEST.VALUE:classification.holo::common::details::Classification::IsValidSubType.return:false
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t)
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (this->IsValidMainType(main_type) == (false)) ==> FALSE
      (2) if (this->IsValidSubType(sub_type) == (false)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.STUB:classification.holo::common::details::Classification::IsValidMainType
TEST.STUB:classification.holo::common::details::Classification::IsValidSubType
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).main_type:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::Classification(const holo::uint16_t,const holo::uint16_t).sub_type:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::IsValidMainType.return:true
TEST.VALUE:classification.holo::common::details::Classification::IsValidSubType.return:true
TEST.END

-- Subprogram: holo::common::details::Classification::Classification(holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Classification(holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.holo::common::details::Classification::Classification(holo::uint32_t).value:196609
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.END

-- Subprogram: holo::common::details::Classification::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::Classification::GetMainType

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::GetMainType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:PEDESTRIAN
TEST.EXPECTED:classification.holo::common::details::Classification::GetMainType.return:PEDESTRIAN
TEST.END

-- Subprogram: holo::common::details::Classification::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.EXPECTED:classification.holo::common::details::Classification::GetSerializedSize.return:4
TEST.END

-- Subprogram: holo::common::details::Classification::GetSubType

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::GetSubType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:CAR
TEST.EXPECTED:classification.holo::common::details::Classification::GetSubType.return:CAR
TEST.END

-- Subprogram: holo::common::details::Classification::IsValidMainType

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::IsValidMainType
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (it != kMainTypeStringArray.end()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable it in branch 1 since it requires user code.
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.VALUE:classification.holo::common::details::Classification::IsValidMainType.type_code:3
TEST.EXPECTED:classification.holo::common::details::Classification::IsValidMainType.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::IsValidMainType
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (it != kMainTypeStringArray.end()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::IsValidMainType.type_code:8
TEST.EXPECTED:classification.holo::common::details::Classification::IsValidMainType.return:true
TEST.END

-- Subprogram: holo::common::details::Classification::IsValidSubType

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::IsValidSubType
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (it != kSubTypeStringArray.end()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable it in branch 1 since it requires user code.
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::IsValidSubType.type_code:<<MIN>>
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::IsValidSubType
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (it != kSubTypeStringArray.end()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::IsValidSubType.type_code:<<MIN>>
TEST.END

-- Subprogram: holo::common::details::Classification::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::Classification::SetMainType

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::SetMainType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::SetMainType.main_type:BIKE
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.END

-- Subprogram: holo::common::details::Classification::SetSubType

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::SetSubType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::SetSubType.sub_type:CAR
TEST.EXPECTED:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:CAR
TEST.END

-- Subprogram: holo::common::details::Classification::ToMainTypeString

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToMainTypeString
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (it != kMainTypeStringArray.end()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable it in branch 1 since it requires user code.
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToMainTypeString
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (it != kMainTypeStringArray.end()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::Classification::ToString

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToString
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::Classification::ToSubTypeString

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToSubTypeString
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (it != kSubTypeStringArray.end()) ==> TRUE
   Test Case Generation Notes:
      Cannot set variable it in branch 1 since it requires user code.
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToSubTypeString
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (it != kSubTypeStringArray.end()) ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToSubTypeString
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (it != kSubTypeStringArray.end()) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set variable it in branch 1 since it requires user code.
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::ToSubTypeString
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (it != kSubTypeStringArray.end()) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set variable to unknown value in branch 1
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::Classification::Underlying

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::Underlying
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.EXPECTED:classification.holo::common::details::Classification::Underlying.return:196609
TEST.END

-- Subprogram: holo::common::details::Classification::UnderlyingMainType

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::UnderlyingMainType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.EXPECTED:classification.holo::common::details::Classification::UnderlyingMainType.return:3
TEST.END

-- Subprogram: holo::common::details::Classification::UnderlyingSubType

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::UnderlyingSubType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.EXPECTED:classification.holo::common::details::Classification::UnderlyingSubType.return:1
TEST.END

-- Subprogram: holo::common::details::Classification::operator holo::uint32_t

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator holo::uint32_t
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:BIKE
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.EXPECTED:classification.holo::common::details::Classification::operator holo::uint32_t.return:196609
TEST.END

-- Subprogram: holo::common::details::Classification::operator!=

-- Test Case: COND_1_ROW_1_PAIR_a_TT
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator!=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TT
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (!(main_type_ == other.main_type_ && sub_type_ == other.sub_type_)) ==> FALSE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator!=.return:false
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TT
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator!=
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TT
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (!(main_type_ == other.main_type_ && sub_type_ == other.sub_type_)) ==> FALSE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator!=.return:false
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_b_TF
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator!=
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_b_TF
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (!(main_type_ == other.main_type_ && sub_type_ == other.sub_type_)) ==> TRUE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.EXPECTED:classification.holo::common::details::Classification::operator!=.return:true
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_a_Fx
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator!=
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_a_Fx
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (!(main_type_ == other.main_type_ && sub_type_ == other.sub_type_)) ==> TRUE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:UNKNOWN
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.main_type_:PEDESTRIAN
TEST.VALUE:classification.holo::common::details::Classification::operator!=.other.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator!=.return:true
TEST.END

-- Subprogram: holo::common::details::Classification::operator=

-- Test Case: BASIS-PATH-001
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator=
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:PEDESTRIAN
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.VALUE:classification.holo::common::details::Classification::operator=.value:196609
TEST.VALUE:classification.holo::common::details::Classification::operator=.return:<<null>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator=.return.holo::common::details::Classification.main_type_:BIKE
TEST.EXPECTED:classification.holo::common::details::Classification::operator=.return.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.END

-- Subprogram: holo::common::details::Classification::operator==

-- Test Case: COND_1_ROW_1_PAIR_a_TT
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TT
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (main_type_ == other.main_type_ && sub_type_ == other.sub_type_) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TT
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TT
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (main_type_ == other.main_type_ && sub_type_ == other.sub_type_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_b_TF
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_b_TF
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (main_type_ == other.main_type_ && sub_type_ == other.sub_type_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.main_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.sub_type_:UNKNOWN_MOVABLE
TEST.EXPECTED:classification.holo::common::details::Classification::operator==.return:false
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_a_Fx
TEST.UNIT:classification
TEST.SUBPROGRAM:holo::common::details::Classification::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_a_Fx
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (main_type_ == other.main_type_ && sub_type_ == other.sub_type_) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.main_type_:UNKNOWN
TEST.VALUE:classification.<<GLOBAL>>.(cl).holo::common::details::Classification.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.<<constructor>>.Classification().<<call>>:0
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.main_type_:PEDESTRIAN
TEST.VALUE:classification.holo::common::details::Classification::operator==.other.holo::common::details::Classification.sub_type_:<<MIN>>
TEST.EXPECTED:classification.holo::common::details::Classification::operator==.return:false
TEST.END
