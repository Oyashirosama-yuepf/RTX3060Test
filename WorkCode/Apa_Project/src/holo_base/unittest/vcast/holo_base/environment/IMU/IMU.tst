-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : IMU
-- Unit(s) Under Test: imu
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

-- Unit: imu

-- Subprogram: holo::common::details::ImuT<float>::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::GetAngularVelocity()OutputType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::GetAngularVelocity()OutputType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetAngularVelocity()OutputType const.return.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetAngularVelocity()OutputType const.return.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetAngularVelocity()OutputType const.return.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::GetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::GetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.coordinate_.holo::common::Coordinate.param_:1
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.coordinate_.holo::common::Coordinate.type_:2
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetCoordinate.return.holo::common::Coordinate.param_:1
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetCoordinate.return.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::GetLinearAcceleration()OutputType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::GetLinearAcceleration()OutputType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[0]:3.0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[1]:4.0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[2]:5.0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetLinearAcceleration()OutputType const.return.holo::geometry::details::Point3T<float>.data_[0]:3.0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetLinearAcceleration()OutputType const.return.holo::geometry::details::Point3T<float>.data_[1]:4.0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetLinearAcceleration()OutputType const.return.holo::geometry::details::Point3T<float>.data_[2]:5.0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetSerializedSize.return:40
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::GetStatus

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::GetStatus
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.status_:GYROXERROR
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetStatus.return:GYROXERROR
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:imu.holo::common::details::ImuT<float>::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::ImuT

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::ImuT
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.coordinate_.holo::common::Coordinate.param_:0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.coordinate_.holo::common::Coordinate.type_:0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.status_:ALLGOOD
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetAngularVelocity(const holo::common::details::ImuT<float>::Point3Type&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetAngularVelocity(const holo::common::details::ImuT<float>::Point3Type&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetAngularVelocity(const holo::common::details::ImuT<float>::Point3Type&).angular_velocity.holo::geometry::details::Point3T<float>.<<constructor>>.Point3T().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetAngularVelocity(const holo::common::details::ImuT<float>::Point3Type&).angular_velocity.holo::geometry::details::Point3T<float>.data_[0..1]:2.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetAngularVelocity(const holo::common::details::ImuT<float>::Point3Type&).angular_velocity.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[0..1]:2.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetAngularVelocity(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetAngularVelocity(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetAngularVelocity(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType).x:1.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetAngularVelocity(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType).y:2.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetAngularVelocity(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType).z:3.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.angular_velocity_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetCoordinate.coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetCoordinate.coord.holo::common::Coordinate.param_:1
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetCoordinate.coord.holo::common::Coordinate.type_:2
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.coordinate_.holo::common::Coordinate.param_:1
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.coordinate_.holo::common::Coordinate.type_:2
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetLinearAcceleration(const holo::common::details::ImuT<float>::Point3Type&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetLinearAcceleration(const holo::common::details::ImuT<float>::Point3Type&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(const holo::common::details::ImuT<float>::Point3Type&).linear_acceleration.holo::geometry::details::Point3T<float>.<<constructor>>.Point3T().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(const holo::common::details::ImuT<float>::Point3Type&).linear_acceleration.holo::geometry::details::Point3T<float>.data_[0]:3.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(const holo::common::details::ImuT<float>::Point3Type&).linear_acceleration.holo::geometry::details::Point3T<float>.data_[1]:4.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(const holo::common::details::ImuT<float>::Point3Type&).linear_acceleration.holo::geometry::details::Point3T<float>.data_[2]:5.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[0]:3.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[1]:4.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[2]:5.0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetLinearAcceleration(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetLinearAcceleration(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType).x:3.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType).y:4.0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetLinearAcceleration(holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType,holo::common::details::ImuT<float>::ScalarType).z:5.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[0]:3.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[1]:4.0
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.linear_acceleration_.holo::geometry::details::Point3T<float>.data_[2]:5.0
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetStatus(holo::ImuStatus)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetStatus(holo::ImuStatus)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetStatus(holo::ImuStatus).status:IMU_STATUS_GYROYERROR
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.status_:GYROYERROR
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetStatus(holo::common::details::ImuT<float>::Status)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetStatus(holo::common::details::ImuT<float>::Status)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetStatus(holo::common::details::ImuT<float>::Status).status:UNDEFINEDERROR
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.status_:UNDEFINEDERROR
TEST.END

-- Subprogram: holo::common::details::ImuT<float>::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu
TEST.SUBPROGRAM:holo::common::details::ImuT<float>::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.<<constructor>>.ImuT().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:imu.holo::common::details::ImuT<float>::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:imu.<<GLOBAL>>.(cl).holo::common::details::ImuT<float>.holo::common::details::ImuT<float>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END
