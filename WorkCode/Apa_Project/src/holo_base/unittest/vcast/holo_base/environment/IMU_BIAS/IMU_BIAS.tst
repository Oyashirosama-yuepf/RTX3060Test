-- VectorCAST 21.sp3 (08/04/21)
-- Test Case Script
--
-- Environment    : IMU_BIAS
-- Unit(s) Under Test: imu_bias
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

-- Unit: imu_bias

-- Subprogram: holo::common::details::ImuBiasT<float>::Deserialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::Deserialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetAngularVelocityBias()OutputType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetAngularVelocityBias()OutputType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetAngularVelocityBias()OutputType const.return.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetAngularVelocityBias()OutputType const.return.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetAngularVelocityBias()OutputType const.return.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetAngularVelocityBiasCovariance()OutputType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetAngularVelocityBiasCovariance()OutputType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetAngularVelocityBiasCovariance()OutputType const.return.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetAngularVelocityBiasCovariance()OutputType const.return.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetAngularVelocityBiasCovariance()OutputType const.return.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.coordinate_.holo::common::Coordinate.param_:2
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.coordinate_.holo::common::Coordinate.type_:3
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetCoordinate.return.holo::common::Coordinate.param_:2
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetCoordinate.return.holo::common::Coordinate.type_:3
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetLinearAccelerationBias()OutputType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetLinearAccelerationBias()OutputType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetLinearAccelerationBias()OutputType const.return.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetLinearAccelerationBias()OutputType const.return.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetLinearAccelerationBias()OutputType const.return.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetLinearAccelerationBiasCovariance()OutputType const

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetLinearAccelerationBiasCovariance()OutputType const
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetLinearAccelerationBiasCovariance()OutputType const.return.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetLinearAccelerationBiasCovariance()OutputType const.return.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetLinearAccelerationBiasCovariance()OutputType const.return.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetSerializedSize

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetSerializedSize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetSerializedSize.return:60
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::GetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::GetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetTimestamp.return.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:imu_bias.holo::common::details::ImuBiasT<float>::GetTimestamp.return.holo::common::details::Timestamp.nsec_:2
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::ImuBiasT

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::ImuBiasT
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.timestamp_.holo::common::details::Timestamp.sec_:0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.timestamp_.holo::common::details::Timestamp.nsec_:0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.coordinate_.holo::common::Coordinate.param_:0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.coordinate_.holo::common::Coordinate.type_:0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::Serialize

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::Serialize
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(const holo::common::details::ImuBiasT<float>::Point3Type&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(const holo::common::details::ImuBiasT<float>::Point3Type&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias.holo::geometry::details::Point3T<float>.<<constructor>>.Point3T().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).x:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).y:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).z:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias_covariance.holo::geometry::details::Point3T<float>.<<constructor>>.Point3T().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias_covariance.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias_covariance.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).angular_velocity_bias_covariance.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).x:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).y:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetAngularVelocityBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).z:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.angular_velocity_bias_covariance_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetCoordinate

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetCoordinate
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetCoordinate.coord.holo::common::Coordinate.<<constructor>>.Coordinate().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetCoordinate.coord.holo::common::Coordinate.param_:2
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetCoordinate.coord.holo::common::Coordinate.type_:3
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.coordinate_.holo::common::Coordinate.param_:2
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.coordinate_.holo::common::Coordinate.type_:3
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(const holo::common::details::ImuBiasT<float>::Point3Type&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(const holo::common::details::ImuBiasT<float>::Point3Type&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias.holo::geometry::details::Point3T<float>.<<constructor>>.Point3T().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).x:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).y:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBias(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).z:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias_covariance.holo::geometry::details::Point3T<float>.<<constructor>>.Point3T().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias_covariance.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias_covariance.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(const holo::common::details::ImuBiasT<float>::Point3Type&).linear_acceleration_bias_covariance.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType)
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).x:1.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).y:2.0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetLinearAccelerationBiasCovariance(holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType,holo::common::details::ImuBiasT<float>::ScalarType).z:3.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[0]:1.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[1]:2.0
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.linear_acceleration_bias_covariance_.holo::geometry::details::Point3T<float>.data_[2]:3.0
TEST.END

-- Subprogram: holo::common::details::ImuBiasT<float>::SetTimestamp

-- Test Case: BASIS-PATH-001
TEST.UNIT:imu_bias
TEST.SUBPROGRAM:holo::common::details::ImuBiasT<float>::SetTimestamp
TEST.NEW
TEST.NAME:BASIS-PATH-001
TEST.BASIS_PATH:1 of 1
TEST.NOTES:
   No branches in subprogram
TEST.END_NOTES:
TEST.VALUE:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.<<constructor>>.ImuBiasT().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetTimestamp.timestamp.holo::common::details::Timestamp.<<constructor>>.Timestamp().<<call>>:0
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetTimestamp.timestamp.holo::common::details::Timestamp.sec_:1
TEST.VALUE:imu_bias.holo::common::details::ImuBiasT<float>::SetTimestamp.timestamp.holo::common::details::Timestamp.nsec_:2
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.timestamp_.holo::common::details::Timestamp.sec_:1
TEST.EXPECTED:imu_bias.<<GLOBAL>>.(cl).holo::common::details::ImuBiasT<float>.holo::common::details::ImuBiasT<float>.timestamp_.holo::common::details::Timestamp.nsec_:2
TEST.END
