/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_pose_2d.h
 * @brief This header file defines the 2d vehicle pose for project x3v.
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-05-21
 */

#ifndef HOLO_PARKING_LOCALIZATION_VEHICLE_POSE_2D_H_
#define HOLO_PARKING_LOCALIZATION_VEHICLE_POSE_2D_H_

#include <holo/core/types.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace parking
{
namespace localization
{
/**
 * @addtogroup parking
 *
 * @{
 */

/**
 * @brief This class defines the 2d vehicle pose for project x3v.
 *
 * @tparam T float32_t or float64_t
 */

template <typename T>
class VehiclePose2DT
{
public:
    using ScalarType  = T;
    using Vector3Type = holo::Vector3T<ScalarType>;

    /**
     * @brief define map's quality
     * @details Localization in an EXCELLENT map can obtain high accuracy result, while the accuracy when localization
     * in a BAD map can not be guaranteed.
     */
    enum class VehicleStatus : uint8_t
    {
        HIGH_PRECISION = 0,  ///< the pose of vehicle is high precision
        LOW_PRECISION  = 1,  ///< the pose of vehicle is low precision
        NOGOOD         = 2,  ///< the pose of vehicle is not good
        UNKNOWN        = 3,  ///< the pose of vehicle is unknown
    };

    /**
     * @brief Default Constructor
     */
    VehiclePose2DT(const ScalarType curv = 0.0, const Vector3Type& pose = Vector3Type(0.0, 0.0, 0.0),
                   const Vector3Type&   predicted_pose = Vector3Type(0.0, 0.0, 0.0),
                   const VehicleStatus& status         = VehicleStatus::UNKNOWN) noexcept
      : curv_(curv), pose_(pose), predicted_pose_(predicted_pose), status_(status)
    {
    }

    /**
     * @brief copy constructor with params
     *
     * @param other a vehicle pose
     */
    VehiclePose2DT(const VehiclePose2DT& other) noexcept
      : curv_(other.GetCurve())
      , pose_(other.GetPose())
      , predicted_pose_(other.GetPredictedPose())
      , status_(other.GetStatus())
    {
    }

    /**
     * @brief Destroy the vehicle pose
     */
    ~VehiclePose2DT() noexcept
    {
    }

    /**
     * @brief Get curve
     */
    const ScalarType& GetCurve() const
    {
        return curv_;
    }

    /**
     * @brief Set curve
     */
    void SetCurve(const ScalarType& curv)
    {
        curv_ = curv;
    }

    /**
     * @brief Get pose
     */
    const Vector3Type& GetPose() const
    {
        return pose_;
    }

    /**
     * @brief Set pose
     */
    void SetPose(const Vector3Type& pose)
    {
        pose_ = pose;
    }

    /**
     * @brief Get predicted pose
     */
    const Vector3Type GetPredictedPose() const
    {
        return predicted_pose_;
    }

    /**
     * @brief Set predicted_pose
     */
    void SetPredictedPose(const Vector3Type& predicted_pose)
    {
        predicted_pose_ = predicted_pose;
    }

    /**
     * @brief Get status
     */
    const VehicleStatus& GetStatus() const
    {
        return status_;
    }

    /**
     * @brief Set status
     */
    void SetVehicleStatus(const VehicleStatus& status)
    {
        status_ = status;
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << curv_ << pose_ << predicted_pose_ << static_cast<uint8_t>(status_) << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t status;
        deserializer >> curv_ >> pose_ >> predicted_pose_ >> status >> holo::serialization::align;
        status_ = static_cast<VehicleStatus>(status);
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return holo::serialization::SerializedSize<ALIGN>(curv_) * 7 +
               holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(status_));
    }

private:
    ScalarType    curv_;            // curve
    Vector3Type   pose_;            // the vehicle pose in 2d space. [x, y, yaw]
    Vector3Type   predicted_pose_;  // the predicted vehicle pose in 2d space. [x, y, yaw]
    VehicleStatus status_;          // the status of vehcicle pose
};

/**
 * @brief This class represents a vehicle pose with accuracy of float32_t and dimention of descriptor is
 */
using VehiclePose2Df = VehiclePose2DT<float32_t>;

/**
 * @brief This class represents a vehicle pose with accuracy of float64_t and dimention of descriptor is
 */
using VehiclePose2Dd = VehiclePose2DT<float64_t>;

/**
 * @}
 */
}  // namespace localization
}  // namespace parking
}  // namespace holo

#endif  // !HOLO_PARKING_LOCALIZATION_VEHICLE_POSE_2D_H_
