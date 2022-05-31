-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : SEGMENTATION_2D
-- Unit(s) Under Test: segmentation_2d
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

-- Unit: segmentation_2d

-- Subprogram: holo::Segmentation2DT<float>::GetTimestamp()const holo::Segmentation2DT<float>::Timestamp const

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::GetTimestamp()const holo::Segmentation2DT<float>::Timestamp const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::GetTimestamp()const holo::Segmentation2DT<float>::Timestamp const.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::GetTimestamp()const holo::Segmentation2DT<float>::Timestamp const.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::GetTimestamp()holo::Segmentation2DT<float>::Timestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::GetTimestamp()holo::Segmentation2DT<float>::Timestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::GetTimestamp()holo::Segmentation2DT<float>::Timestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::GetTimestamp()holo::Segmentation2DT<float>::Timestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::Segmentation2DT()

-- Test Case: holo::Segmentation2DT<float>::Segmentation2DT().001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::Segmentation2DT()
TEST.NEW
TEST.NAME:holo::Segmentation2DT<float>::Segmentation2DT().001
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:UNKNOWN
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:UNKNOWN
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.num_classes:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.height:0
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.width:0
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::SetTimestamp.stamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::SetTimestamp.stamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::SetTimestamp.stamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.stamp_.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.height:2
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.width:3
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_:<<malloc 1>>
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.<<constructor>>.SemanticSegment().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.contours:<<malloc 1>>
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0]:<<function 1>>
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.height:2
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()const holo::Segmentation2DT<float>::Info const.return.holo::Segmentation2DT<float>::Info.width:3
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.height:2
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.width:3
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.height:2
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::info()holo::Segmentation2DT<float>::Info.return.holo::Segmentation2DT<float>::Info.width:3
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.<<constructor>>.Info().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.height:2
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(const holo::Segmentation2DT<float>::Info&).info.holo::Segmentation2DT<float>::Info.width:3
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.height:2
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.width:3
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.<<constructor>>.Info().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.height:2
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::info(holo::Segmentation2DT<float>::Info&&).info.holo::Segmentation2DT<float>::Info.width:3
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.y_:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.x_:2
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.location_.holo::common::VehicleLocation.plane_:3
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.model_:GNSS_QIANXU
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.sensor_id.holo::common::SensorId.category_:JOYSTICK
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.num_classes:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.height:2
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.info_.holo::Segmentation2DT<float>::Info.width:3
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::semantic_segments()const holo::Segmentation2DT<float>::SemanticSegments const

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::semantic_segments()const holo::Segmentation2DT<float>::SemanticSegments const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_:<<malloc 1>>
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.<<constructor>>.SemanticSegment().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0]:<<function 1>>
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments()const holo::Segmentation2DT<float>::SemanticSegments const.return[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments()const holo::Segmentation2DT<float>::SemanticSegments const.return[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments()const holo::Segmentation2DT<float>::SemanticSegments const.return[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::semantic_segments()holo::Segmentation2DT<float>::SemanticSegments

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::semantic_segments()holo::Segmentation2DT<float>::SemanticSegments
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_:<<malloc 1>>
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.<<constructor>>.SemanticSegment().<<call>>:0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0]:<<function 1>>
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments()holo::Segmentation2DT<float>::SemanticSegments.return[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments()holo::Segmentation2DT<float>::SemanticSegments.return[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.EXPECTED:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments()holo::Segmentation2DT<float>::SemanticSegments.return[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&).semantic_segments:<<malloc 1>>
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.<<constructor>>.SemanticSegment().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(const holo::Segmentation2DT<float>::SemanticSegments&).semantic_segments[0]:<<function 1>>
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.END

-- Subprogram: holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:segmentation_2d
TEST.SUBPROGRAM:holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.<<constructor>>.Segmentation2DT().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&).semantic_segments:<<malloc 1>>
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.<<constructor>>.SemanticSegment().<<call>>:0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&).semantic_segments[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.VALUE:segmentation_2d.holo::Segmentation2DT<float>::semantic_segments(holo::Segmentation2DT<float>::SemanticSegments&&).semantic_segments[0]:<<function 1>>
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.category_id:TRAFFIC_BOARD
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.instance_id:1
TEST.EXPECTED:segmentation_2d.<<GLOBAL>>.(cl).holo::Segmentation2DT<float>.holo::Segmentation2DT<float>.semantic_segments_[0].holo::Segmentation2DT<float>::SemanticSegment.confidence:2.0
TEST.END
