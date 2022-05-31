-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : ROAD_CATEGORY
-- Unit(s) Under Test: road_category
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

-- Unit: road_category

-- Subprogram: holo::common::LaneCategory::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.END

-- Subprogram: holo::common::LaneCategory::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:road_category.holo::common::LaneCategory::GetSerializedSize.return:4
TEST.END

-- Subprogram: holo::common::LaneCategory::GetValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::GetValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.EXPECTED:road_category.holo::common::LaneCategory::GetValue.return:16777216
TEST.END

-- Subprogram: holo::common::LaneCategory::IsCategoryAcceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryAcceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::ACCELERATION)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:2
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryAcceleration.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryAcceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::ACCELERATION)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryAcceleration.return:false
TEST.END

-- Subprogram: holo::common::LaneCategory::IsCategoryDeceleration

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryDeceleration
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::DECELERATION)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:3
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryDeceleration.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryDeceleration
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::DECELERATION)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryDeceleration.return:false
TEST.END

-- Subprogram: holo::common::LaneCategory::IsCategoryEmergency

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryEmergency
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::EMERGENCY)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:4
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryEmergency.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryEmergency
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::EMERGENCY)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryEmergency.return:false
TEST.END

-- Subprogram: holo::common::LaneCategory::IsCategoryRegular

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryRegular
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::REGULAR)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryRegular.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryRegular
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::REGULAR)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryRegular.return:false
TEST.END

-- Subprogram: holo::common::LaneCategory::IsCategoryUnknown

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryUnknown
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::UNKNOWN)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:0
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryUnknown.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::IsCategoryUnknown
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::UNKNOWN)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.EXPECTED:road_category.holo::common::LaneCategory::IsCategoryUnknown.return:false
TEST.END

-- Subprogram: holo::common::LaneCategory::LaneCategory()

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::LaneCategory()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory:<<null>>
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:0
TEST.END

-- Subprogram: holo::common::LaneCategory::LaneCategory(const holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::LaneCategory(const holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.holo::common::LaneCategory::LaneCategory(const holo::uint32_t).value:16777216
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.END

-- Subprogram: holo::common::LaneCategory::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.END

-- Subprogram: holo::common::LaneCategory::SetCategoryAcceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::SetCategoryAcceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:2
TEST.END

-- Subprogram: holo::common::LaneCategory::SetCategoryDeceleration

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::SetCategoryDeceleration
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:3
TEST.END

-- Subprogram: holo::common::LaneCategory::SetCategoryEmergency

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::SetCategoryEmergency
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:4
TEST.END

-- Subprogram: holo::common::LaneCategory::SetCategoryRegular

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::SetCategoryRegular
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.END

-- Subprogram: holo::common::LaneCategory::SetCategoryUnknown

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::SetCategoryUnknown
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:0
TEST.END

-- Subprogram: holo::common::LaneCategory::SetValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::SetValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::LaneCategory::SetValue.value:16777216
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.END

-- Subprogram: holo::common::LaneCategory::operator holo::uint32_t

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::operator holo::uint32_t
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:1
TEST.EXPECTED:road_category.holo::common::LaneCategory::operator holo::uint32_t.return:16777216
TEST.END

-- Subprogram: holo::common::LaneCategory::operator==

-- Test Case: COND_1_ROW_1_PAIR_a_TT
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TT
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TT
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TT
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_b_TF
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_b_TF
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.category_:1
TEST.EXPECTED:road_category.holo::common::LaneCategory::operator==.return:false
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_a_Fx
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::LaneCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_a_Fx
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::LaneCategory.holo::common::LaneCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.<<constructor>>.LaneCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.tags_:1
TEST.VALUE:road_category.holo::common::LaneCategory::operator==.other.holo::common::LaneCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::LaneCategory::operator==.return:false
TEST.END

-- Subprogram: holo::common::RoadCategory::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.END

-- Subprogram: holo::common::RoadCategory::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.holo::common::RoadCategory::GetSerializedSize.return:4
TEST.END

-- Subprogram: holo::common::RoadCategory::GetValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::GetValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:1
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.EXPECTED:road_category.holo::common::RoadCategory::GetValue.return:16777217
TEST.ATTRIBUTES:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:EXPECTED_BASE=8
TEST.END

-- Subprogram: holo::common::RoadCategory::HasTagToll

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::HasTagToll
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((tags_ & static_cast< holo::uint32_t>(Tag::TOLL)) == static_cast< holo::uint32_t>(Tag::TOLL)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:2
TEST.EXPECTED:road_category.holo::common::RoadCategory::HasTagToll.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::HasTagToll
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((tags_ & static_cast< holo::uint32_t>(Tag::TOLL)) == static_cast< holo::uint32_t>(Tag::TOLL)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.holo::common::RoadCategory::HasTagToll.return:false
TEST.END

-- Subprogram: holo::common::RoadCategory::HasTagTunnel

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::HasTagTunnel
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) ((tags_ & static_cast< holo::uint32_t>(Tag::TUNNEL)) == static_cast< holo::uint32_t>(Tag::TUNNEL)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:1
TEST.EXPECTED:road_category.holo::common::RoadCategory::HasTagTunnel.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::HasTagTunnel
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) ((tags_ & static_cast< holo::uint32_t>(Tag::TUNNEL)) == static_cast< holo::uint32_t>(Tag::TUNNEL)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.holo::common::RoadCategory::HasTagTunnel.return:false
TEST.END

-- Subprogram: holo::common::RoadCategory::IsCategoryMainRoad

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::IsCategoryMainRoad
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::MAINROAD)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.EXPECTED:road_category.holo::common::RoadCategory::IsCategoryMainRoad.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::IsCategoryMainRoad
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::MAINROAD)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::RoadCategory::IsCategoryMainRoad.return:false
TEST.END

-- Subprogram: holo::common::RoadCategory::IsCategoryRamp

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::IsCategoryRamp
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::RAMP)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:2
TEST.EXPECTED:road_category.holo::common::RoadCategory::IsCategoryRamp.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::IsCategoryRamp
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::RAMP)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::RoadCategory::IsCategoryRamp.return:false
TEST.END

-- Subprogram: holo::common::RoadCategory::IsCategoryUnknown

-- Test Case: COND_1_ROW_1_PAIR_a_T
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::IsCategoryUnknown
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (category_ == static_cast< holo::uint32_t>(Category::UNKNOWN)) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.EXPECTED:road_category.holo::common::RoadCategory::IsCategoryUnknown.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::IsCategoryUnknown
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (category_ == static_cast< holo::uint32_t>(Category::UNKNOWN)) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.EXPECTED:road_category.holo::common::RoadCategory::IsCategoryUnknown.return:false
TEST.END

-- Subprogram: holo::common::RoadCategory::ResetTagToll

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::ResetTagToll
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.END

-- Subprogram: holo::common::RoadCategory::ResetTagTunnel

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::ResetTagTunnel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.END

-- Subprogram: holo::common::RoadCategory::RoadCategory()

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::RoadCategory()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.END

-- Subprogram: holo::common::RoadCategory::RoadCategory(const holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::RoadCategory(const holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.holo::common::RoadCategory::RoadCategory(const holo::uint32_t).value:16777219
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:3
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.END

-- Subprogram: holo::common::RoadCategory::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.END

-- Subprogram: holo::common::RoadCategory::SetCategoryMainRoad

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::SetCategoryMainRoad
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.END

-- Subprogram: holo::common::RoadCategory::SetCategoryRamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::SetCategoryRamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:2
TEST.END

-- Subprogram: holo::common::RoadCategory::SetCategoryUnknown

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::SetCategoryUnknown
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.END

-- Subprogram: holo::common::RoadCategory::SetTagToll

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::SetTagToll
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:2
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.END

-- Subprogram: holo::common::RoadCategory::SetTagTunnel

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::SetTagTunnel
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:1
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:0
TEST.END

-- Subprogram: holo::common::RoadCategory::SetValue

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::SetValue
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::RoadCategory::SetValue.value:16777217
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:1
TEST.EXPECTED:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.END

-- Subprogram: holo::common::RoadCategory::operator holo::uint32_t

-- Test Case: BASIS-PATH-001
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::operator holo::uint32_t
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:1
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:1
TEST.EXPECTED:road_category.holo::common::RoadCategory::operator holo::uint32_t.return:16777217
TEST.END

-- Subprogram: holo::common::RoadCategory::operator==

-- Test Case: COND_1_ROW_1_PAIR_a_TT
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_TT
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> TRUE
      Row number 1 forms a pair with Row 3 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::RoadCategory::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_b_TT
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_b_TT
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::RoadCategory::operator==.return:true
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_b_TF
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_b_TF
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "b".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.category_:1
TEST.EXPECTED:road_category.holo::common::RoadCategory::operator==.return:false
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_a_Fx
TEST.UNIT:road_category
TEST.SUBPROGRAM:holo::common::RoadCategory::operator==
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_a_Fx
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) (this->tags_ == other.tags_ && this->category_ == other.category_) ==> FALSE
      Row number 3 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.tags_:<<MIN>>
TEST.VALUE:road_category.<<GLOBAL>>.(cl).holo::common::RoadCategory.holo::common::RoadCategory.category_:<<MIN>>
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.<<constructor>>.RoadCategory().<<call>>:0
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.tags_:1
TEST.VALUE:road_category.holo::common::RoadCategory::operator==.other.holo::common::RoadCategory.category_:<<MIN>>
TEST.EXPECTED:road_category.holo::common::RoadCategory::operator==.return:false
TEST.END
