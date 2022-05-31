-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : TRAFFIC_LIGHT
-- Unit(s) Under Test: traffic_light
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

-- Unit: traffic_light

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::Deserialize

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < lane_ids_size) ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
      Cannot set local variable lane_ids_size in branch 1
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < lane_ids_size) ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
      Cannot set local variable lane_ids_size in branch 1
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_1_PAIR_a_T-PARTIAL
TEST.MCDC_BASIS_PATH:2 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) for (i < lane_ids_size) ==> TRUE
      Row number 1 forms a pair with Row 2 for Condition #1, subcondition "a".
         Condition a ==> TRUE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
      Cannot set local variable lane_ids_size in branch 1
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.END

-- Test Case: COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::Deserialize
TEST.NEW
TEST.NAME:COND_1_ROW_2_PAIR_a_F-PARTIAL
TEST.MCDC_BASIS_PATH:1 of 2
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) for (i < lane_ids_size) ==> FALSE
      Row number 2 forms a pair with Row 1 for Condition #1, subcondition "a".
         Condition a ==> FALSE
   Test Case Generation Notes:
      Cannot set local variable i in branch 1
      Cannot set local variable lane_ids_size in branch 1
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::GetBoundingBox

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::GetBoundingBox
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.width_:4.0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.height_:5.0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.depth_:6.0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.pose_.holo::geometry::details::Pose3T<double>.translation_.holo::geometry::details::Point3T<double>.data_[0]:1.0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetBoundingBox.return.holo::geometry::details::Box3T<double>.width_:4.0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetBoundingBox.return.holo::geometry::details::Box3T<double>.height_:5.0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetBoundingBox.return.holo::geometry::details::Box3T<double>.depth_:6.0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetBoundingBox.return.holo::geometry::details::Box3T<double>.pose_.holo::geometry::details::Pose3T<double>.translation_.holo::geometry::details::Point3T<double>.data_[0]:1.0
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::GetConfidence

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::GetConfidence
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.confidence_:3.0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetConfidence.return:3.0
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::GetLaneIds

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::GetLaneIds
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_:<<malloc 2>>
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[0]:1
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[0]:<<function 1>>
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[1]:2
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[1]:<<function 1>>
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetLaneIds.return.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[0]:1
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetLaneIds.return.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[1]:2
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetSerializedSize.return:144
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::GetTimer

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::GetTimer
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.timer_:3
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetTimer.return:3
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::GetTrackId

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::GetTrackId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.track_id_:3
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::GetTrackId.return:3
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::IsDetected

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::IsDetected
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.is_detected_:true
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::IsDetected.return:true
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::IsTemporary

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::IsTemporary
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.temporary_:true
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::IsTemporary.return:true
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::Serialize

-- Test Case: BASIS-PATH-001-PARTIAL
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001-PARTIAL
TEST.BASIS_PATH:1 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 1
      (1) range-based for elements in lane_ids_ ==> FALSE
   Test Case Generation Notes:
      Cannot set lane_ids_ in branch 1 to empty.
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.END

-- Test Case: BASIS-PATH-002-PARTIAL
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-002-PARTIAL
TEST.BASIS_PATH:2 of 2 (partial)
TEST.NOTES:
This is an automatically generated test case.
   Test Path 2
      (1) range-based for elements in lane_ids_ ==> TRUE
   Test Case Generation Notes:
      Cannot set lane_ids_ in branch 1 to contain elements.
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::SetConfidence

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::SetConfidence
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetConfidence.confidence:3.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.confidence_:3.0
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::SetDetectFlag

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::SetDetectFlag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.is_detected_:false
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetDetectFlag.flag:true
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.is_detected_:true
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds.lane_ids.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.<<constructor>>.Vector().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds.lane_ids.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_:<<malloc 2>>
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds.lane_ids.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[0]:1
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds.lane_ids.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[0]:<<function 1>>
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds.lane_ids.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[1]:2
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetLaneIds.lane_ids.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[1]:<<function 1>>
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[0]:1
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.lane_ids_.holo::container::details::Vector<unsigned long, 2UL, std::allocator<unsigned long>>.container_[1]:2
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::SetTemporaryFlag

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::SetTemporaryFlag
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.temporary_:false
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetTemporaryFlag.flag:true
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.temporary_:true
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::SetTimer

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::SetTimer
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetTimer.timer:3
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.timer_:3
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::SetTrackId

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::SetTrackId
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.<<constructor>>.TrafficLightT().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::SetTrackId.track_id:3
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.track_id_:3
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT()

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.track_id_:0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.is_detected_:false
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.temporary_:false
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.timer_:-1
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.confidence_:0.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.width_:1.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.height_:1.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.depth_:1.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.pose_.holo::geometry::details::Pose3T<double>.translation_.holo::geometry::details::Point3T<double>.data_[0..2]:0.0
TEST.END

-- Subprogram: holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t)

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t).track_id:1
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t).is_detected:true
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t).temporary:true
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t).timer:3
TEST.VALUE:traffic_light.holo::common::details::TrafficLightT<2UL, 2UL>::TrafficLightT(holo::uint64_t,const holo::bool_t,const holo::bool_t,const holo::int16_t,const holo::float32_t).confidence:4.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.track_id_:1
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.is_detected_:true
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.temporary_:true
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.timer_:3
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.confidence_:4.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.width_:1.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.height_:1.0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>.holo::common::details::TrafficLightT<2UL, 2UL>.bounding_box_.holo::geometry::details::Box3T<double>.depth_:1.0
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.param_:100
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.type_:2
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetCoordinate.return.holo::common::Coordinate.param_:100
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetCoordinate.return.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetSerializedSize.return:16
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetCoordinate.coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetCoordinate.coordinate.holo::common::Coordinate.param_:100
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetCoordinate.coordinate.holo::common::Coordinate.type_:2
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.param_:100
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.<<constructor>>.TrafficLightsT().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT()

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT()
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightT<2UL, 2UL>:<<null>>
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.param_:0
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate)

-- Test Case: BASIS-PATH-001
TEST.UNIT:traffic_light
TEST.SUBPROGRAM:holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate).timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate).timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate).timestamp.holo::common::details::Timestamp.nsec_:2
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate).coordinate.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate).coordinate.holo::common::Coordinate.param_:100
TEST.VALUE:traffic_light.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>::TrafficLightsT(const holo::common::details::Timestamp,const holo::common::Coordinate).coordinate.holo::common::Coordinate.type_:2
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.param_:100
TEST.EXPECTED:traffic_light.<<GLOBAL>>.(cl).holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.holo::common::details::TrafficLightsT<2UL, 2UL, 2UL>.coordinate_.holo::common::Coordinate.type_:2
TEST.END
