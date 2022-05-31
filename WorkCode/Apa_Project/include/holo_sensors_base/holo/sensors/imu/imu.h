/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file aceinna.h
 * @brief This header file define the function of aceinna driver
 * @author guoguangchao@holomatic.com
 * @date 2020-08-21
 */

#ifndef _HOLO_SENSORS_IMU_IMU_H
#define _HOLO_SENSORS_IMU_IMU_H

#include <holo/common/app_status.h>
#include <holo/common/extrinsic.h>
#include <holo/common/imu.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/angle.h>
#include <holo/os/time.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/common/interface.h>
#include <holo/sensors/utils/sensors_utils.h>
#include <functional>

namespace holo
{
namespace sensors
{
using holo::common::Extrinsicf;
using holo::sensors::common::Device;
static constexpr uint8_t IMU_NODE_ID = 20;
struct ImuOperationParams
{
    float32_t low_freq_lower;
    float32_t low_freq_upper;
    float32_t high_freq_lower;
    float32_t high_freq_upper;
    float32_t temperature_upper;
    float32_t temperature_lower;
    float32_t temperature_diff_max;
    float32_t frame_loss_tolerance;
};
/* imu driver base */
template <typename T>
class ImuDriverT : public Device
{
public:
    using InType                = T;
    using Imud                  = holo::common::Imud;
    using AppStatus             = holo::common::AppStatus;
    using TimestampType         = holo::common::Timestamp;
    using Pose3d                = holo::geometry::Pose3d;
    using Coordinate            = holo::common::Coordinate;
    using CallbackType          = std::function<void(const Imud&)>;
    using AppStatusCallbackType = std::function<void(const AppStatus&)>;

    ImuDriverT(const Extrinsicf& extrinsic)
      : Device(extrinsic.GetSensorId())
      , extrinsic_(extrinsic)
      , imu_callback_(nullptr)
      , app_status_callback_(nullptr)
      , imu_app_status_(TimestampType(), IMU_NODE_ID)
    {
    }

    virtual ~ImuDriverT() = default;

    void InstallCallback(const CallbackType& callback) noexcept
    {
        imu_callback_ = callback;
    }

    void InstallAppStatusCallback(const AppStatusCallbackType& callback) noexcept
    {
        app_status_callback_ = callback;
    }

    void TransformToBody(Imud& imu, const holo::geometry::Pose3d& bTi)
    {
        // const Pose3 bTi = extrinsic.GetPose();

        holo::numerics::Matrix3d const bRi = bTi.GetRotation().ToMatrix();

        holo::numerics::Vector3d const av = bRi * imu.GetAngularVelocity<holo::numerics::Vector3d>();
        holo::numerics::Vector3d       la = bRi * imu.GetLinearAcceleration<holo::numerics::Vector3d>();

        // Centrifugal acceleration
        holo::geometry::Point3d const  t = bTi.GetTranslation();
        holo::numerics::Vector3d const bti(t[0], t[1], t[2]);

        if (!bti.IsZero())
        {
            // Subtract out the the centripetal acceleration from the unbiased one
            // to get linear acceleration vector in the imu frame:
            holo::numerics::Matrix3d const body_Omega_body = av.ToSkewSymmetric();
            holo::numerics::Vector3d const b_velocity_bs   = body_Omega_body * bti;  // magnitude: omega * arm
            la -= body_Omega_body * b_velocity_bs;
        }

        imu.SetAngularVelocity(av.At(0), av.At(1), av.At(2));
        imu.SetLinearAcceleration(la.At(0), la.At(1), la.At(2));
    }

    virtual void ParseData(const T&) = 0;
    virtual void UpdateStatus()
    {
    }
    virtual void SetParamsLimit(holo::sensors::ImuOperationParams& params_limit)
    {
        (void)params_limit;
    }

protected:
    Extrinsicf            extrinsic_;
    CallbackType          imu_callback_;
    AppStatusCallbackType app_status_callback_;

    AppStatus imu_app_status_;
};

}  // namespace sensors
}  // namespace holo

#endif
