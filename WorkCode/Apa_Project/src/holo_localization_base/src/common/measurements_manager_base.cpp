/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file measurements_manager_base.cpp
 * @brief define measurements_manager class
 * @author duyanwei@holomatic.com
 * @date 2019-12-04
 */

#include <holo/localization/common/measurements_manager_base.h>

namespace holo
{
namespace localization
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeasurementsManagerBase::MeasurementsManagerBase()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeasurementsManagerBase::~MeasurementsManagerBase()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MeasurementsManagerBase::Reset()
{
    // lock buffer
    std::unique_lock<std::mutex> lock1(ground_truth_buffer_mutex_);
    std::unique_lock<std::mutex> lock2(imu_buffer_mutex_);
    std::unique_lock<std::mutex> lock3(odometry_buffer_mutex_);
    std::unique_lock<std::mutex> lock4(position_buffer_mutex_);
    std::unique_lock<std::mutex> lock5(road_frame_buffer_mutex_);
    std::unique_lock<std::mutex> lock6(chassis_state_buffer_mutex_);
    std::unique_lock<std::mutex> lock7(image_buffer_mutex_);
    std::unique_lock<std::mutex> lock8(gnss_pvt_mutex_);

    // clear all the buffers
    ground_truth_buffer_.clear();
    imu_buffer_.clear();
    odometry_buffer_.clear();
    position_buffer_.clear();
    road_frame_buffer_.clear();
    chassis_state_buffer_.clear();
    image_buffer_.clear();
    gnss_pvt_buffer_.clear();

    // @todo reset anything else if necessary
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddGroundTruth(const OdometryType& m)
{
    std::unique_lock<std::mutex> lock(ground_truth_buffer_mutex_);
    return insertMeasurementT<OdometryType, kOdometryBufferSize>(m, ground_truth_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const ImuType& m)
{
    std::unique_lock<std::mutex> lock(imu_buffer_mutex_);
    return insertMeasurementT<ImuType, kImuBufferSize>(m, imu_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const OdometryType& m)
{
    std::unique_lock<std::mutex> lock(odometry_buffer_mutex_);
    return insertMeasurementT<OdometryType, kOdometryBufferSize>(m, odometry_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const GnssPosition& m)
{
    std::unique_lock<std::mutex> lock(position_buffer_mutex_);
    return insertMeasurementT<GnssPosition, kPositionBufferSize>(m, position_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const GnssPvtType& m)
{
    std::unique_lock<std::mutex> lock(gnss_pvt_mutex_);
    return insertMeasurementT<GnssPvtType, kGnssPvtBufferSize>(m, gnss_pvt_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const RoadFrame& m)
{
    std::unique_lock<std::mutex> lock(road_frame_buffer_mutex_);
    return insertMeasurementT<RoadFrame, kRoadFrameBufferSize>(m, road_frame_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const StampedRouteInfoType& m)
{
    std::unique_lock<std::mutex> lock(stamped_route_info_buffer_mutex_);
    return insertMeasurementT<StampedRouteInfoType, kStampedRouteInfoBufferSize>(m, stamped_route_info_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const ChassisState& m)
{
    std::unique_lock<std::mutex> lock(chassis_state_buffer_mutex_);
    return insertMeasurementT<ChassisState, kChassisStateBufferSize>(m, chassis_state_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::AddMeasurement(const ImageType& m)
{
    std::unique_lock<std::mutex> lock(image_buffer_mutex_);
    return insertMeasurementT<ImageType, kImageBufferSize>(m, image_buffer_);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestGroundTruth(OdometryType& m)
{
    std::unique_lock<std::mutex> lock(ground_truth_buffer_mutex_);
    return getLatestMeasurementT<OdometryType, kOdometryBufferSize>(ground_truth_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(ImuType& m)
{
    std::unique_lock<std::mutex> lock(imu_buffer_mutex_);
    return getLatestMeasurementT<ImuType, kImuBufferSize>(imu_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(OdometryType& m)
{
    std::unique_lock<std::mutex> lock(odometry_buffer_mutex_);
    return getLatestMeasurementT<OdometryType, kOdometryBufferSize>(odometry_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(GnssPosition& m)
{
    std::unique_lock<std::mutex> lock(position_buffer_mutex_);
    return getLatestMeasurementT<GnssPosition, kPositionBufferSize>(position_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(GnssPvtType& m)
{
    std::unique_lock<std::mutex> lock(gnss_pvt_mutex_);
    return getLatestMeasurementT<GnssPvtType, kGnssPvtBufferSize>(gnss_pvt_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(RoadFrame& m)
{
    std::unique_lock<std::mutex> lock(road_frame_buffer_mutex_);
    return getLatestMeasurementT<RoadFrame, kRoadFrameBufferSize>(road_frame_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(ChassisState& m)
{
    std::unique_lock<std::mutex> lock(chassis_state_buffer_mutex_);
    return getLatestMeasurementT<ChassisState, kChassisStateBufferSize>(chassis_state_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetLatestMeasurement(ImageType& m)
{
    std::unique_lock<std::mutex> lock(image_buffer_mutex_);
    return getLatestMeasurementT<ImageType, kImageBufferSize>(image_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetAndPopOldestMeasurement(RoadFrame& m)
{
    std::unique_lock<std::mutex> lock(road_frame_buffer_mutex_);
    if (road_frame_buffer_.empty())
    {
        return false;
    }
    m = road_frame_buffer_.front();
    road_frame_buffer_.pop_front();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestGroundTruth(const Timestamp& t, OdometryType& m)
{
    std::unique_lock<std::mutex> lock(ground_truth_buffer_mutex_);
    return getNearestMeasurementT<OdometryType, kOdometryBufferSize>(t, ground_truth_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestMeasurement(const Timestamp& t, ImuType& m)
{
    std::unique_lock<std::mutex> lock(imu_buffer_mutex_);
    return getNearestMeasurementT<ImuType, kImuBufferSize>(t, imu_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestMeasurement(const Timestamp& t, OdometryType& m)
{
    std::unique_lock<std::mutex> lock(odometry_buffer_mutex_);
    return getNearestMeasurementT<OdometryType, kOdometryBufferSize>(t, odometry_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestMeasurement(const Timestamp& t, StampedRouteInfoType& m)
{
    std::unique_lock<std::mutex> lock(stamped_route_info_buffer_mutex_);
    return getNearestMeasurementT<StampedRouteInfoType, kStampedRouteInfoBufferSize>(t, stamped_route_info_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestMeasurement(const Timestamp& t, ChassisState& m)
{
    std::unique_lock<std::mutex> lock(chassis_state_buffer_mutex_);
    return getNearestMeasurementT<ChassisState, kChassisStateBufferSize>(t, chassis_state_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestMeasurement(const Timestamp& t, ImageType& m)
{
    std::unique_lock<std::mutex> lock(image_buffer_mutex_);
    return getNearestMeasurementT<ImageType, kImageBufferSize>(t, image_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetNearestMeasurement(const Timestamp& t, GnssPvtType& m)
{
    std::unique_lock<std::mutex> lock(gnss_pvt_mutex_);
    return getNearestMeasurementT<GnssPvtType, kGnssPvtBufferSize>(t, gnss_pvt_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetCurrentGroundTruth(const Timestamp& t, OdometryType& m)
{
    std::unique_lock<std::mutex> lock(ground_truth_buffer_mutex_);
    return getCurrentMeasurementT<OdometryType, kOdometryBufferSize>(t, ground_truth_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetCurrentMeasurement(const Timestamp& t, OdometryType& m)
{
    std::unique_lock<std::mutex> lock(odometry_buffer_mutex_);
    return getCurrentMeasurementT<OdometryType, kOdometryBufferSize>(t, odometry_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetCurrentMeasurement(const Timestamp& t, ChassisState& m)
{
    std::unique_lock<std::mutex> lock(chassis_state_buffer_mutex_);
    return getCurrentMeasurementT<ChassisState, kChassisStateBufferSize>(t, chassis_state_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetCurrentMeasurement(const Timestamp& t, GnssPvtType& m)
{
    std::unique_lock<std::mutex> lock(gnss_pvt_mutex_);
    return getCurrentMeasurementT<GnssPvtType, kGnssPvtBufferSize>(t, gnss_pvt_buffer_, m);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                       std::vector<ImuType>& imus)
{
    std::unique_lock<std::mutex> lock(imu_buffer_mutex_);
    return getMeasurementsBetweenT<ImuType, kImuBufferSize>(left, right, imu_buffer_, imus);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                       std::vector<OdometryType>& odometries)
{
    std::unique_lock<std::mutex> lock(odometry_buffer_mutex_);
    return getMeasurementsBetweenT<OdometryType, kOdometryBufferSize>(left, right, odometry_buffer_, odometries);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                       std::vector<GnssPosition>& positions)
{
    std::unique_lock<std::mutex> lock(position_buffer_mutex_);
    return getMeasurementsBetweenT<GnssPosition, kPositionBufferSize>(left, right, position_buffer_, positions);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                       std::vector<GnssPvtType>& gnss_pvts)
{
    std::unique_lock<std::mutex> lock(gnss_pvt_mutex_);
    return getMeasurementsBetweenT<GnssPvtType, kGnssPvtBufferSize>(left, right, gnss_pvt_buffer_, gnss_pvts);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                       std::vector<RoadFrame>& road_frames)
{
    std::unique_lock<std::mutex> lock(road_frame_buffer_mutex_);
    return getMeasurementsBetweenT<RoadFrame, kRoadFrameBufferSize>(left, right, road_frame_buffer_, road_frames);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                       std::vector<ChassisState>& chassis_states)
{
    std::unique_lock<std::mutex> lock(chassis_state_buffer_mutex_);
    return getMeasurementsBetweenT<ChassisState, kChassisStateBufferSize>(left, right, chassis_state_buffer_,
                                                                          chassis_states);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                              std::vector<ImuType>& imus)
{
    std::unique_lock<std::mutex> lock(imu_buffer_mutex_);
    return getAlignedMeasurementsBetweenT<ImuType, kImuBufferSize>(left, right, imu_buffer_, imus);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                              std::vector<OdometryType>& odometries)
{
    std::unique_lock<std::mutex> lock(odometry_buffer_mutex_);
    return getAlignedMeasurementsBetweenT<OdometryType, kOdometryBufferSize>(left, right, odometry_buffer_, odometries);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                              std::vector<GnssPvtType>& gnss_pvts)
{
    std::unique_lock<std::mutex> lock(gnss_pvt_mutex_);
    return getAlignedMeasurementsBetweenT<GnssPvtType, kGnssPvtBufferSize>(left, right, gnss_pvt_buffer_, gnss_pvts);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool_t MeasurementsManagerBase::GetAlignedMeasurementsBetween(const Timestamp& left, const Timestamp& right,
                                                              std::vector<ChassisState>& chassis_states)
{
    std::unique_lock<std::mutex> lock(chassis_state_buffer_mutex_);
    return getAlignedMeasurementsBetweenT<ChassisState, kChassisStateBufferSize>(left, right, chassis_state_buffer_,
                                                                                 chassis_states);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
ImuType MeasurementsManagerBase::interpolateT<ImuType>(const ImuType& left, const ImuType& right,
                                                       const Timestamp& stamp)
{
    if (stamp == left.GetTimestamp())
    {
        return left;
    }

    if (stamp == right.GetTimestamp())
    {
        return right;
    }

    const float64_t lt    = left.GetTimestamp().ToSec();
    const float64_t rt    = right.GetTimestamp().ToSec();
    const float64_t mt    = stamp.ToSec();
    const float64_t ratio = (mt - lt) / (rt - lt);

    if (ratio < 0.0 || ratio > 1.0)
    {
        const std::string s = "interpolate need the ratio be in range [0, 1], ratio: ";
        LOG(ERROR) << s << ratio;
        return ImuType();
    }

    /// fabricate a new imu
    ImuType imu(left);
    imu.SetTimestamp(stamp);
    // @todo compiling error
    // imu.SetStatus(left.GetStatus() | right.GetStatus());

    const ImuType::Vector3Type gyro_diff =
        right.GetAngularVelocity<ImuType::Vector3Type>() - left.GetAngularVelocity<ImuType::Vector3Type>();
    const ImuType::Vector3Type acc_diff =
        right.GetLinearAcceleration<ImuType::Vector3Type>() - left.GetLinearAcceleration<ImuType::Vector3Type>();

    imu.SetAngularVelocity(ImuType::Point3Type(left.GetAngularVelocity<ImuType::Vector3Type>() +
                                               static_cast<ImuType::ScalarType>(ratio) * gyro_diff));
    imu.SetLinearAcceleration(ImuType::Point3Type(left.GetLinearAcceleration<ImuType::Vector3Type>() +
                                                  static_cast<ImuType::ScalarType>(ratio) * acc_diff));

    DLOG(INFO) << "Interpolate finished";
    return imu;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
OdometryType MeasurementsManagerBase::interpolateT<OdometryType>(const OdometryType& left, const OdometryType& right,
                                                                 const Timestamp& stamp)
{
    OdometryType odometry(left);
    odometry.SetTimestamp(stamp);

    // compute ratio
    const Timestamp t1    = left.GetTimestamp();
    const Timestamp t2    = right.GetTimestamp();
    const float64_t ratio = (stamp - t1).ToSec() / (t2 - t1).ToSec();

    if (ratio < 0.0 || ratio > 1.0)
    {
        std::stringstream ss;
        ss << "interpolation needs the ratio be in range [0, 1], ratio: " << ratio;
        LOG(ERROR) << ss.str();
        return OdometryType();
    }

    // pose interpolation
    odometry.SetPose(Pose3Type::Interpolate(left.GetPose(), right.GetPose(), static_cast<Scalar>(ratio)));

    // velocity interpolation
    odometry.SetVelocity(
        linearInterpolationT<Vector6Type>(left.GetVelocity(), right.GetVelocity(), static_cast<Scalar>(ratio)));

    // @todo leave other variables to future, e.g. covariance
    // duyanwei@holomatic.com

    return odometry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
ChassisState MeasurementsManagerBase::interpolateT<ChassisState>(const ChassisState& left, const ChassisState& right,
                                                                 const Timestamp& stamp)
{
    ChassisState chassis_state(left);
    chassis_state.SetTimestamp(stamp);

    // compute ratio
    const Timestamp t1    = left.GetTimestamp();
    const Timestamp t2    = right.GetTimestamp();
    const float64_t ratio = (stamp - t1).ToSec() / (t2 - t1).ToSec();

    if (ratio < 0.0 || ratio > 1.0)
    {
        std::stringstream ss;
        ss << "interpolation needs the ratio be in range [0, 1], ratio: " << ratio;
        LOG(ERROR) << ss.str();
        return ChassisState();
    }

    // wheel speed
    chassis_state.SetFrontLeftWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetFrontLeftWheelSpeed(), right.GetFrontLeftWheelSpeed(), ratio));
    chassis_state.SetFrontRightWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetFrontRightWheelSpeed(), right.GetFrontRightWheelSpeed(), ratio));
    chassis_state.SetRearLeftWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetRearLeftWheelSpeed(), right.GetRearLeftWheelSpeed(), ratio));
    chassis_state.SetRearRightWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetRearRightWheelSpeed(), right.GetRearRightWheelSpeed(), ratio));

    // front wheel angle
    chassis_state.SetFrontWheelAngle(
        linearInterpolationT<holo::float32_t>(left.GetFrontWheelAngle(), right.GetFrontWheelAngle(), ratio));

    // yaw rate
    chassis_state.SetYawRate(linearInterpolationT<holo::float32_t>(left.GetYawRate(), right.GetYawRate(), ratio));

    // vehicle speed
    chassis_state.SetVehicleSpeed(
        linearInterpolationT<holo::float32_t>(left.GetVehicleSpeed(), right.GetVehicleSpeed(), ratio));

    // longitudinal acceleration
    chassis_state.SetLongitudinalAcceleration(linearInterpolationT<holo::float32_t>(
        left.GetLongitudinalAcceleration(), right.GetLongitudinalAcceleration(), ratio));

    // lateral acceleration
    chassis_state.SetLateralAcceleration(
        linearInterpolationT<holo::float32_t>(left.GetLateralAcceleration(), right.GetLateralAcceleration(), ratio));

    // @todo add other components if needs
    // lishuaijie@holomatic.com

    return chassis_state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
GnssPvtType MeasurementsManagerBase::interpolateT<GnssPvtType>(const GnssPvtType& left, const GnssPvtType& right,
                                                               const Timestamp& stamp)
{
    GnssPvtType gnss_pvt(left);
    gnss_pvt.SetTimestamp(stamp);

    /// Step 1: Compute ratio
    const Timestamp t1    = left.GetTimestamp();
    const Timestamp t2    = right.GetTimestamp();
    const float64_t ratio = (stamp - t1).ToSec() / (t2 - t1).ToSec();

    if (ratio < 0.0 || ratio > 1.0)
    {
        std::stringstream ss;
        ss << "interpolation needs the ratio be in range [0, 1], ratio: " << ratio;
        LOG(ERROR) << ss.str();
        return GnssPvtType();
    }

    /// Step 2: Position interpolation
    gnss_pvt.SetPosition<Vector3Type>(linearInterpolationT<Vector3Type>(
        left.GetPosition<Vector3Type>(), right.GetPosition<Vector3Type>(), static_cast<Scalar>(ratio)));

    /// Step 3: Velocity interpolation
    gnss_pvt.SetVelocity<Vector3Type>(linearInterpolationT<Vector3Type>(
        left.GetVelocity<Vector3Type>(), right.GetVelocity<Vector3Type>(), static_cast<Scalar>(ratio)));

    /// @todo leave other variables to future, e.g. covariance (leigehang@holomatic.com)

    return gnss_pvt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
ImuType MeasurementsManagerBase::extrapolateT<ImuType>(const ImuType& left, const ImuType& right,
                                                       const Timestamp& stamp)
{
    if (stamp == left.GetTimestamp())
    {
        return left;
    }

    if (stamp == right.GetTimestamp())
    {
        return right;
    }

    const float64_t lt = left.GetTimestamp().ToSec();
    const float64_t rt = right.GetTimestamp().ToSec();
    const float64_t et = stamp.ToSec();

    if (lt < et && et < rt)
    {
        std::string s = "the stamp is in the middle of two imu, so do nothing";
        LOG(ERROR) << s;
        return ImuType();
    }

    const bool_t is_left = et < lt ? true : false;

    /// fabricate a new imu
    ImuType imu(left);
    imu.SetTimestamp(stamp);
    // @todo compiling error
    // imu.SetStatus(left.GetStatus() | right.GetStatus());

    const ImuType::Vector3Type gyro_diff =
        right.GetAngularVelocity<ImuType::Vector3Type>() - left.GetAngularVelocity<ImuType::Vector3Type>();
    const ImuType::Vector3Type acc_diff =
        right.GetLinearAcceleration<ImuType::Vector3Type>() - left.GetLinearAcceleration<ImuType::Vector3Type>();

    if (is_left)
    {
        const float64_t ratio = (rt - et) / (rt - lt);
        imu.SetAngularVelocity(ImuType::Point3Type(right.GetAngularVelocity<ImuType::Vector3Type>() -
                                                   static_cast<ImuType::ScalarType>(ratio) * gyro_diff));
        imu.SetLinearAcceleration(ImuType::Point3Type(right.GetLinearAcceleration<ImuType::Vector3Type>() -
                                                      static_cast<ImuType::ScalarType>(ratio) * acc_diff));
    }
    else
    {
        const float64_t ratio = (et - lt) / (rt - lt);
        imu.SetAngularVelocity(ImuType::Point3Type(left.GetAngularVelocity<ImuType::Vector3Type>() +
                                                   static_cast<ImuType::ScalarType>(ratio) * gyro_diff));
        imu.SetLinearAcceleration(ImuType::Point3Type(left.GetLinearAcceleration<ImuType::Vector3Type>() +
                                                      static_cast<ImuType::ScalarType>(ratio) * acc_diff));
    }
    DLOG(INFO) << "Extrapolate finished";
    return imu;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
OdometryType MeasurementsManagerBase::extrapolateT<OdometryType>(const OdometryType& left, const OdometryType& right,
                                                                 const Timestamp& stamp)
{
    OdometryType odometry(left);
    odometry.SetTimestamp(stamp);

    // compute ratio
    const Timestamp t1    = left.GetTimestamp();
    const Timestamp t2    = right.GetTimestamp();
    const float64_t ratio = (stamp - t1).ToSec() / (t2 - t1).ToSec();

    if (ratio > 0.0 && ratio < 1.0)
    {
        std::stringstream ss;
        ss << "extrapolation needs the ratio be out of range [0, 1], ratio: " << ratio;
        LOG(ERROR) << ss.str();
        return OdometryType();
    }

    // pose interpolation
    odometry.SetPose(Pose3Type::Interpolate(left.GetPose(), right.GetPose(), static_cast<Scalar>(ratio)));

    // velocity interpolation
    odometry.SetVelocity(linearInterpolationT<Vector6Type>(left.GetVelocity(), right.GetVelocity(), ratio));

    // @todo leave other variables to future, e.g. covariance
    // duyanwei@holomatic.com

    return odometry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
ChassisState MeasurementsManagerBase::extrapolateT<ChassisState>(const ChassisState& left, const ChassisState& right,
                                                                 const Timestamp& stamp)
{
    ChassisState chassis_state(left);
    chassis_state.SetTimestamp(stamp);

    // compute ratio
    const Timestamp t1    = left.GetTimestamp();
    const Timestamp t2    = right.GetTimestamp();
    const float64_t ratio = (stamp - t1).ToSec() / (t2 - t1).ToSec();

    if (ratio > 0.0 && ratio < 1.0)
    {
        std::stringstream ss;
        ss << "extrapolation needs the ratio be out of range [0, 1], ratio: " << ratio;
        LOG(ERROR) << ss.str();
        return ChassisState();
    }

    // wheel speed
    chassis_state.SetFrontLeftWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetFrontLeftWheelSpeed(), right.GetFrontLeftWheelSpeed(), ratio));
    chassis_state.SetFrontRightWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetFrontRightWheelSpeed(), right.GetFrontRightWheelSpeed(), ratio));
    chassis_state.SetRearLeftWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetRearLeftWheelSpeed(), right.GetRearLeftWheelSpeed(), ratio));
    chassis_state.SetRearRightWheelSpeed(
        linearInterpolationT<holo::float32_t>(left.GetRearRightWheelSpeed(), right.GetRearRightWheelSpeed(), ratio));

    // front wheel angle
    chassis_state.SetFrontWheelAngle(
        linearInterpolationT<holo::float32_t>(left.GetFrontWheelAngle(), right.GetFrontWheelAngle(), ratio));

    // yaw rate
    chassis_state.SetYawRate(linearInterpolationT<holo::float32_t>(left.GetYawRate(), right.GetYawRate(), ratio));

    // vehicle speed
    chassis_state.SetVehicleSpeed(
        linearInterpolationT<holo::float32_t>(left.GetVehicleSpeed(), right.GetVehicleSpeed(), ratio));

    // longitudinal acceleration
    chassis_state.SetLongitudinalAcceleration(linearInterpolationT<holo::float32_t>(
        left.GetLongitudinalAcceleration(), right.GetLongitudinalAcceleration(), ratio));

    // lateral acceleration
    chassis_state.SetLateralAcceleration(
        linearInterpolationT<holo::float32_t>(left.GetLateralAcceleration(), right.GetLateralAcceleration(), ratio));

    // @todo other components

    return chassis_state;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <>
GnssPvtType MeasurementsManagerBase::extrapolateT<GnssPvtType>(const GnssPvtType& left, const GnssPvtType& right,
                                                               const Timestamp& stamp)
{
    GnssPvtType gnss_pvt(left);
    gnss_pvt.SetTimestamp(stamp);

    /// Step 1: Compute ratio
    const Timestamp t1    = left.GetTimestamp();
    const Timestamp t2    = right.GetTimestamp();
    const float64_t ratio = (stamp - t1).ToSec() / (t2 - t1).ToSec();

    if (ratio > 0.0 && ratio < 1.0)
    {
        std::stringstream ss;
        ss << "extrapolation needs the ratio be out of range [0, 1], ratio: " << ratio;
        LOG(ERROR) << ss.str();
        return GnssPvtType();
    }

    /// Step 2: Position interpolation
    gnss_pvt.SetPosition<Vector3Type>(linearInterpolationT<Vector3Type>(
        left.GetPosition<Vector3Type>(), right.GetPosition<Vector3Type>(), static_cast<Scalar>(ratio)));

    /// Step 3: Velocity interpolation
    gnss_pvt.SetVelocity<Vector3Type>(linearInterpolationT<Vector3Type>(
        left.GetVelocity<Vector3Type>(), right.GetVelocity<Vector3Type>(), static_cast<Scalar>(ratio)));

    /// @todo leave other variables to future, e.g. covariance (leigehang@holomatic.com)

    return gnss_pvt;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}  // namespace localization
}  // namespace holo
