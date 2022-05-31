/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file pose_spline.h
 * @brief PoseSpline class
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @date April 08, 2020
 */

#ifndef HOLO_LOCALIZATION_TOOLS_POSE_SPLINE_H_
#define HOLO_LOCALIZATION_TOOLS_POSE_SPLINE_H_

#include <holo/common/timestamp.h>
#include <holo/geometry/angle_axis.h>
#include <holo/geometry/pose3.h>
#include <holo/localization/tools/spline_fitting.h>

namespace holo
{
namespace localization
{
/**
 * @brief define spline class
 *
 */
class PoseSpline
{
public:
    using Timestamp = holo::common::Timestamp;
    using Pose3d    = holo::geometry::Pose3d;
    using Rot3d     = holo::geometry::Rot3d;
    using Point3d   = holo::geometry::Point3d;
    using Vector3d  = holo::numerics::Vector3d;
    using Vector6d  = holo::numerics::Vector6d;
    using Matrix3d  = holo::numerics::Matrix3d;
    /**
     * @brief Construct a new Spline object
     *
     * @param timestamps timestamps
     * @param poses poses
     * @param offset translation offset
     * @param lambda smoothing coefficient when computing control points
     * @param num_of_time_segments num_of_time_segments
     * @throw std::out_of_range exception if the size of timestamps and poses are not the same
     */
    PoseSpline(const std::vector<Timestamp>& timestamps, const std::vector<Pose3d>& poses,
               const Vector3d& offset = Vector3d(0.0,0.0,0.0), float64_t lambda = 0.0, uint32_t num_of_time_segments = 0u);

    /**
     * @brief Destroy the Spline object
     *
     */
    virtual ~PoseSpline() noexcept;

    /**
     * @brief Get start time
     *
     * @return timestamp
     */
    Timestamp GetStartTime() const;

    /**
     * @brief Get the End Time object
     *
     * @return Timestamp
     */
    Timestamp GetEndTime() const;

    /**
     * @brief Get the Pose object
     *
     * @param t timestamp
     * @param local return local pose when set to true
     * @return Pose3d
     */
    Pose3d GetPose(const Timestamp& t, bool_t local = false) const;

    /**
     * @brief Get the Velocity object [linear_velocity, angular_velocity]
     *
     * @param t timestamp
     * @return Vector6d
     */
    Vector3d GetLinearVelocity(const Timestamp& t) const;

    /**
     * @brief Get the Linear Acceleration object
     *
     * @param t timestamp
     * @return Vector3d
     */
    Vector3d GetLinearAcceleration(const Timestamp& t) const;

    /**
     * @brief Get the Angular Velocity Body Frame object
     *
     * @param t timestamp
     * @return Vector3d
     */
    Vector3d GetAngularVelocityBodyFrame(const Timestamp& t) const;

    /**
     * @brief Get the Offset
     *
     * @return Vector3d const&
     */
    Vector3d const& GetOffset() const;

private:
    /**
     * @brief init spline
     *
     * @param timestamps
     * @param poses
     * @param lambda
     * @param num_of_time_segments
     */
    void initialize(const std::vector<Timestamp>& timestamps, const std::vector<Pose3d>& poses, const float64_t lambda,
                    const uint32_t num_of_time_segments);

    /**
     * @brief convert timestamp to float64_t
     *
     * @param timestamps
     * @return std::vector<float64_t>
     */
    std::vector<float64_t> convertTimestamp(const std::vector<Timestamp>& timestamps) const;

    /**
     * @brief convert pose to vector6d
     *
     * @param poses
     * @return std::vector<Vector6d>
     */
    std::vector<Vector6d> convertPose(const std::vector<Pose3d>& poses) const;

    /**
     * @brief find neareset rotation
     *
     * @details to make rotation trajectory smooth before spline fitting, we "manually" compensate the angle of current
     * rotation (angle-axis representation) by adding constant times of 2*PI, so that it gets "closer" to last rotation.
     * This compensation won't change the physical meaning of rotation itself, but only affects the fitting precision.
     * @param last_rotation last rotation vector
     * @param current_rotation current rotation vector
     * @return Vector3d
     */
    Vector3d findNearestRotation(const Vector3d& last_rotation, const Vector3d& current_rotation) const;

    /**
     * @brief construct s matrix from rotation vector
     *
     * @ref Peter C. Hughes. SpaceCraft Attitude Dynamics. p31
     * @param rotation rotation vector
     * @return Matrix3d S matrix
     */
    Matrix3d constructSMatrix(const Vector3d& rotation) const;

    const Vector3d               offset_;  ///< translation offset
    const SplineFittingT<6u, 3u> spline_;  ///< spline object

};  // class PoseSpline

}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_TOOLS_POSE_SPLINE_H_
