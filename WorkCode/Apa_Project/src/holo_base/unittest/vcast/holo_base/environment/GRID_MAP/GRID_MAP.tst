-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : GRID_MAP
-- Unit(s) Under Test: grid_map
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

-- Unit: grid_map

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.x:<<MAX>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.y:<<MIN>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return:<<null>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.x:<<MIN>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.y:<<MAX>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.x:<<MIN>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.y:<<MIN>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.relative_velocity_.holo::geometry::details::Point2T<float>.data_[0..1]:0.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.main_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.obstacle_id_:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.is_occupied_:false
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.motion_status_:UNKNOWN
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.x:<<MAX>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.y:<<MIN>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.x:<<MIN>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.y:<<MAX>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.x:<<MIN>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.y:<<MIN>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.obstacle_id_:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.is_occupied_:false
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::At(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.motion_status_:UNKNOWN
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (x_index < 0 || y_index < 0) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.data_[0]:-5000.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.data_[1]:4.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.data_[0]:3.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.data_[1]:-50000.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.data_[0]:-2.5
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.coor.holo::geometry::details::Point2T<float>.data_[1]:-7.5
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.return[0]:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const std::pair<unsigned, unsigned> const.return[1]:0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.data_[0]:<<MIN>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.data_[1]:3.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:<<MIN>>
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.data_[0]:3.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.data_[1]:<<MIN>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (x_index < 0 || y_index < 0) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:<<MIN>>
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.coor.holo::geometry::details::Point2T<float>.data_[0..1]:-7.5
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.return[0]:1
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellIndex(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)std::pair<unsigned, unsigned>.return[1]:2
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Deserialize

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.data_[0]:-1000.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.data_[1]:5.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return:<<null>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return:<<null>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.data_[0]:3.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.data_[1]:-1000.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (x_index < 0 || y_index < 0) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.data_[0]:7.2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.coor.holo::geometry::details::Point2T<float>.data_[1]:-7.2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.<<constructor>>.GridMapCell().<<call>>:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.main_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.obstacle_id_:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.is_occupied_:false
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.motion_status_:UNKNOWN
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType

-- Test Case: COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.data_[0]:5.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.data_[1]:-1000.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (x_index < 0 || y_index < 0) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:4.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.data_[0]:7.2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.data_[1]:-7.2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.main_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.obstacle_id_:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.is_occupied_:false
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.motion_status_:UNKNOWN
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (x_index < 0 || y_index < 0) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x_index in branch 1
      Cannot set local variable y_index in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.<<constructor>>.Point2T().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.data_[0]:-1000.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.coor.holo::geometry::details::Point2T<float>.data_[1]:3.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetCell(const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Point2Type&)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetOriginX

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetOriginX
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetOriginX.return:1
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetOriginY

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetOriginY
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetOriginY.return:2
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetResolution

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetResolution
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:3.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetResolution.return:3.0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetSerializedSize.return:860
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap()

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:0
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).sec:1
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).nsec:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).resolution:3.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).origin_x:4
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).origin_y:5
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).sec:1
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp(holo::uint32_t,holo::uint32_t).nsec:2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).resolution:3.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).origin_x:4
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::GridMap(holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::TimestampType,holo::float32_t,holo::uint32_t,holo::uint32_t).origin_y:5
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Serialize

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Serialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::Serialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE * holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin

-- Test Case: COND_1_ROW_2_PAIR_a_Tx
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_Tx
TEST.MCDC_BASIS_PATH:2 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) if (origin_x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || origin_y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 2 forms a pair with Row 4 for Condition #1, subcondition "a".
         Condition a ==> TRUE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.origin_x:100
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.origin_y:<<MIN>>
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_3_PAIR_b_FT
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin
TEST.NEW
TEST.NAME:COND_1_ROW_3_PAIR_b_FT
TEST.MCDC_BASIS_PATH:3 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) if (origin_x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || origin_y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 3 forms a pair with Row 4 for Condition #1, subcondition "b".
         Condition a ==> FALSE
         Condition b ==> TRUE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.origin_x:3
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.origin_y:100
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.<<throw>>.holo::exception::OutOfRangeException.holo::exception::OutOfRangeException.<<exists>>:<<exists>>
TEST.END

-- Test Case: COND_1_ROW_4_PAIR_a_FF
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin
TEST.NEW
TEST.NAME:COND_1_ROW_4_PAIR_a_FF
TEST.MCDC_BASIS_PATH:1 of 3
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) if (origin_x >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE || origin_y >= holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> FALSE
      Row number 4 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> FALSE
         Condition b ==> FALSE
   Test Case Generation Notes:
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.origin_x:2
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetOrigin.origin_y:3
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:2
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:3
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetResolution

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetResolution
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:0.0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetResolution.resolution:5.0
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::initialize

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::initialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (x < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable x in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::initialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (x < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable x in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::initialize
TEST.NEW
TEST.NAME:COND_2_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:4 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 4
      (1) for (x < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
      (2) for (y < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #2, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable y in branch 2
      Cannot set local variable x in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Test Case: COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::initialize
TEST.NEW
TEST.NAME:COND_2_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:3 of 4
TEST.NOTES:
This is an automatically generated test case.
   Test Path 3
      (1) for (x < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::HEIGHT_VALUE) ==> TRUE
      (2) for (y < holo::common::GridMap< holo::common::GridMapCell, 5UL, 6UL> ::WIDTH_VALUE) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #2, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable y in branch 2
      Cannot set local variable x in branch 1
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.x:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.y:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.<<constructor>>.GridMapCell().<<call>>:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.relative_velocity_.holo::geometry::details::Point2T<float>.data_[0..1]:0.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.main_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.obstacle_id_:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.is_occupied_:false
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)const holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType const.return.holo::common::GridMapCell.motion_status_:UNKNOWN
TEST.END

-- Subprogram: holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType

-- Test Case: BASIS-PATH-001
TEST.UNIT:grid_map
TEST.SUBPROGRAM:holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.<<constructor>>.GridMap().<<call>>:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.resolution_:5.0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_x_:0
TEST.VALUE:grid_map.<<GLOBAL>>.(cl).holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>.origin_y_:0
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.x:1
TEST.VALUE:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.y:2
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.relative_velocity_.holo::geometry::details::Point2T<float>.data_[0..1]:0.0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.main_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.classification_.holo::common::details::Classification.sub_type_:UNKNOWN
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.obstacle_id_:0
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.is_occupied_:false
TEST.EXPECTED:grid_map.holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::operator()(const holo::uint32_t,const holo::uint32_t)holo::common::GridMap<holo::common::GridMapCell, 5UL, 6UL>::CellType.return.holo::common::GridMapCell.motion_status_:UNKNOWN
TEST.END
