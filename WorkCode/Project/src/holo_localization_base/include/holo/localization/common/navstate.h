/*!
 * @file navstate.h
 * @brief This header file define navigation state
 * @author lichao@holomatic.com
 * @date Oct 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_LOCALIZATION_COMMON_NAVSTATE_H_
#define HOLO_LOCALIZATION_COMMON_NAVSTATE_H_

#include <holo/common/coordinate.h>
#include <holo/geometry/pose3.h>
#include <holo/numerics/vector.h>

#include <holo/localization/common/stamped.h>
#include <holo/log/hololog.h>

namespace holo
{
namespace localization
{
/**
 * @brief navigation state defines the 3D pose and velocity in navigation frame
 * @tparam T precision type
 *
 */
template <typename T>
class NavstateT
{
public:
    using ScalarType     = T;
    using Pose3Type      = holo::geometry::Pose3T<T>;
    using Vector3Type    = holo::numerics::VectorT<T, 3>;
    using Matrix3Type    = holo::numerics::MatrixT<T, 3, 3>;
    using Matrix6Type    = holo::numerics::MatrixT<T, 6, 6>;
    using CoordinateType = holo::common::Coordinate;

    /**
     * @brief status of navstate
     *
     */
    enum class Status : uint32_t
    {
        ALLGOOD                 = 0x0000,
        SOLUTIONNOGOOD          = 0x0001,
        POSITIONINACTIVE        = 0x0002,
        ORIENTATIONINACTIVE     = 0x0004,
        LINEARVELOCITYINACTIVE  = 0x0008,
        ANGULARVELOCITYINACTIVE = 0x0010,
    };

    /**
     * @brief constructor
     *
     */
    NavstateT()
      : status_(Status::ALLGOOD)
      , parent_coordinate_(CoordinateType())
      , child_coordinate_(CoordinateType())
      , pose_(Pose3Type::Identity())
      , velocity_(Vector3Type::Zero())
      , pose_covariance_(Matrix6Type::Identity())
      , velocity_covariance_(Matrix3Type::Identity())
      , angular_velocity_(Vector3Type::Zero())
    {
    }

    NavstateT(const NavstateT& rhs)
      : status_(rhs.status_)
      , parent_coordinate_(rhs.parent_coordinate_)
      , child_coordinate_(rhs.child_coordinate_)
      , pose_(rhs.pose_)
      , velocity_(rhs.velocity_)
      , pose_covariance_(rhs.pose_covariance_)
      , velocity_covariance_(rhs.velocity_covariance_)
      , angular_velocity_(rhs.angular_velocity_)
    {
    }

    NavstateT& operator=(const NavstateT& rhs)
    {
        status_              = rhs.status_;
        parent_coordinate_   = rhs.parent_coordinate_;
        child_coordinate_    = rhs.child_coordinate_;
        pose_                = rhs.pose_;
        velocity_            = rhs.velocity_;
        pose_covariance_     = rhs.pose_covariance_;
        velocity_covariance_ = rhs.velocity_covariance_;
        angular_velocity_    = rhs.angular_velocity_;
        return *this;
    }

    /**
     * @brief Construct a new Navstate T object from pose and velocity
     *
     * @param p a 3D pose
     * @param v a 3D linear velocity in m/s
     */
    NavstateT(const Pose3Type& p, const Vector3Type& v)
      : status_(Status::ALLGOOD)
      , parent_coordinate_(CoordinateType())
      , child_coordinate_(CoordinateType())
      , pose_(p)
      , velocity_(v)
      , pose_covariance_(Matrix6Type::Identity())
      , velocity_covariance_(Matrix3Type::Identity())
      , angular_velocity_(Vector3Type::Zero())
    {
    }

    /**
     * @brief operator addition overloading, if the coordinate does not satisfy the chain rule, addition will not be
     * applied and it stays the same.
     *
     * @param delta navstate increment
     * @return NavstateT
     */
    NavstateT operator+(const NavstateT& delta) const
    {
        NavstateT navstate;

        if (child_coordinate_.GetParam() != delta.parent_coordinate_.GetParam() ||
            child_coordinate_.GetType() != delta.parent_coordinate_.GetType())
        {
            LOG(WARNING)
                << "coordinate does not satisfy the chain rule, addition will not be applied and it stays the same";

            navstate.SetPose(pose_);
            navstate.SetVelocity(velocity_);
            navstate.SetParentCoordinate(parent_coordinate_);
            navstate.SetChildCoordinate(child_coordinate_);

            return navstate;
        }

        /* T_wj = T_wi * deltaT_ij, V_wj = V_wi + R_wi * deltaV_ij*/
        navstate.SetPose(pose_.operator*(delta.pose_));
        navstate.SetVelocity(velocity_.operator+(pose_.GetRotation().operator*(delta.velocity_)));
        navstate.SetParentCoordinate(parent_coordinate_);
        navstate.SetChildCoordinate(delta.child_coordinate_);

        return navstate;
    }

    /* @todo (lichao@holomatic.com) add Pose3Type * NavstateT function Pose3Type class */

    /**
     * @brief operator equal overloading
     *
     * @param rhs the other navstate
     * @return bool_t true if equal, otherwise false
     */
    bool_t operator==(const NavstateT& rhs) const
    {
        return (status_ == rhs.status_ && parent_coordinate_ == rhs.parent_coordinate_ &&
                child_coordinate_ == rhs.child_coordinate_ && pose_.operator==(rhs.pose_) &&
                velocity_.operator==(rhs.velocity_) && pose_covariance_.operator==(rhs.pose_covariance_) &&
                velocity_covariance_.                                   operator==(rhs.velocity_covariance_) &&
                angular_velocity_.                                      operator==(rhs.angular_velocity_));
    }

    /**
     * @brief operator addition assignment overloading
     *
     * @param delta navstate increment
     * @return NavstateT
     */
    NavstateT operator+=(const NavstateT& delta)
    {
        NavstateT navstate_next = *this + delta;
        *this                   = navstate_next;
        return *this;
    }

    /**
     * @brief Get the Status object
     *
     * @return Status
     */
    inline Status GetStatus() const
    {
        return status_;
    }

    /**
     * @brief Set the Status object
     *
     * @param status
     */
    inline void SetStatus(const Status status)
    {
        status_ = status;
    }

    /**
     * @brief Get the parent coordinate
     *
     * @return parent coordinate
     */
    inline const CoordinateType& GetParentCoordinate() const
    {
        return parent_coordinate_;
    }

    /**
     * @brief Set the parent coordinate
     *
     * @param coordinate
     */
    inline void SetParentCoordinate(const CoordinateType& coordinate)
    {
        parent_coordinate_ = coordinate;
    }

    /**
     * @brief Get the child coordinate
     *
     * @return child coordinate
     */
    inline const CoordinateType& GetChildCoordinate() const
    {
        return child_coordinate_;
    }

    /**
     * @brief Set the child coordinate
     *
     * @param coordinate
     */
    inline void SetChildCoordinate(const CoordinateType& coordinate)
    {
        child_coordinate_ = coordinate;
    }

    /**
     * @brief Get the Pose object
     *
     * @return const Pose3Type
     */
    inline const Pose3Type& GetPose() const
    {
        return pose_;
    }

    /**
     * @brief Set the Pose object
     *
     * @param pose
     */
    inline void SetPose(const Pose3Type& pose)
    {
        pose_ = pose;
    }

    /**
     * @brief Get the Velocity object
     *
     * @return const Vector3Type
     */
    inline const Vector3Type& GetVelocity() const
    {
        return velocity_;
    }

    /**
     * @brief Set the Velocity object
     *
     * @param velocity
     */
    inline void SetVelocity(const Vector3Type& velocity)
    {
        velocity_ = velocity;
    }

    /**
     * @brief Get the Pose Covariance object
     *
     * @return const Matrix6Type
     */
    inline const Matrix6Type& GetPoseCovariance() const
    {
        return pose_covariance_;
    }

    /**
     * @brief Set the Pose Covariance object
     *
     * @param pose_covariance
     */
    inline void SetPoseCovariance(const Matrix6Type& pose_covariance)
    {
        pose_covariance_ = pose_covariance;
    }

    /**
     * @brief Get the Velocity Covariance object
     *
     * @return const Matrix3Type
     */
    inline const Matrix3Type& GetVelocityCovariance() const
    {
        return velocity_covariance_;
    }

    /**
     * @brief Set the Velocity Covariance object
     *
     * @param velocity_covariance
     */
    inline void SetVelocityCovariance(const Matrix3Type& velocity_covariance)
    {
        velocity_covariance_ = velocity_covariance;
    }

    /**
     * @brief Get the Angular Velocity object
     *
     * @return const Vector3Type
     */
    inline const Vector3Type& GetAngularVelocity() const
    {
        return angular_velocity_;
    }

    /**
     * @brief Set the Angular Velocity object
     *
     * @param angular_velocity
     */
    inline void SetAngularVelocity(const Vector3Type& angular_velocity)
    {
        angular_velocity_ = angular_velocity;
    }

    /**
     * @brief Convert NavstateT to string
     *
     * @return std::string
     */
    std::string ToString() const
    {
        std::stringstream ss;
        ss << "Navstate: (" << pose_.ToString() << ", "
           << "velocity: (" << velocity_.Transpose() << "))" << std::endl;
        return ss.str();
    }

protected:
    Status         status_;              /* status */
    CoordinateType parent_coordinate_;   /* parent coordinate */
    CoordinateType child_coordinate_;    /* child coordinate */
    Pose3Type      pose_;                /* body pose in world/local frame */
    Vector3Type    velocity_;            /* body velocity in world/local frame */
    Matrix6Type    pose_covariance_;     /* position and rotation covariance */
    Matrix3Type    velocity_covariance_; /* linear velocity covariance */
    Vector3Type    angular_velocity_;    /* angular velocity in radian/s */
};

using Navstatef       = NavstateT<float32_t>;
using Navstated       = NavstateT<float64_t>;
using Navstate        = Navstated;
using StampedNavstate = StampedT<Navstate>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief an advanced navigation state defines the pose, velocity, imu bias and imu bias covariance in the navigation
 * frame
 *
 * @tparam T precision type
 */
template <typename T>
class AdvancedNavstateT : public NavstateT<T>
{
public:
    using Base        = NavstateT<T>;
    using Matrix3Type = typename Base::Matrix3Type;
    using Matrix6Type = typename Base::Matrix6Type;
    using Pose3Type   = typename Base::Pose3Type;
    using Vector3Type = typename Base::Vector3Type;
    using Vector6Type = holo::numerics::VectorT<T, 6>;

    /**
     * @brief define source type of AdvancedNavStateT
     *
     */
    enum class Source : uint32_t
    {
        NONE            = 0x0000,
        PRIOR           = 0x0001,
        GPS             = 0x0002,
        GNSS_PVT        = 0x0004,
        ABS_POSE        = 0x0008,
        ABS_VEL         = 0x0010,
        IMU             = 0x0020,
        IMUBIAS         = 0x0040,
        REL_POSE        = 0x0080,
        REL_VEL         = 0x0100,
        WHEEL           = 0x0200,
        LANE            = 0x0400,
        HD_MAP          = 0x0800,
        VISION_KEYPOINT = 0x1000,
    };

    /**
     * @brief Construct a new Advanced Navstate T object
     *
     */
    AdvancedNavstateT()
      : Base()
      , source_(static_cast<uint32_t>(Source::NONE))
      , angular_velocity_bias_(Vector3Type::Zero())
      , angular_velocity_bias_covariance_(Matrix3Type::Identity())
      , linear_acceleration_bias_(Vector3Type::Zero())
      , linear_acceleration_bias_covariance_(Matrix3Type::Identity())
    {
    }

    AdvancedNavstateT(const AdvancedNavstateT& rhs)
      : Base(rhs)
      , source_(rhs.source_)
      , angular_velocity_bias_(rhs.angular_velocity_bias_)
      , angular_velocity_bias_covariance_(rhs.angular_velocity_bias_covariance_)
      , linear_acceleration_bias_(rhs.linear_acceleration_bias_)
      , linear_acceleration_bias_covariance_(rhs.linear_acceleration_bias_covariance_)
    {
    }

    AdvancedNavstateT& operator=(const AdvancedNavstateT& rhs)
    {
        Base::operator                       =(rhs);
        source_                              = rhs.source_;
        angular_velocity_bias_               = rhs.angular_velocity_bias_;
        angular_velocity_bias_covariance_    = rhs.angular_velocity_bias_covariance_;
        linear_acceleration_bias_            = rhs.linear_acceleration_bias_;
        linear_acceleration_bias_covariance_ = rhs.linear_acceleration_bias_covariance_;
        return *this;
    }

    /**
     * @brief Construct a new Advanced Navstate T object
     *
     * @param p a 3D pose
     * @param v a 3D linear velocity in m/s
     */
    AdvancedNavstateT(const Pose3Type& p, const Vector3Type& v)
      : Base(p, v)
      , source_(static_cast<uint32_t>(Source::NONE))
      , angular_velocity_bias_(Vector3Type::Zero())
      , angular_velocity_bias_covariance_(Matrix3Type::Identity())
      , linear_acceleration_bias_(Vector3Type::Zero())
      , linear_acceleration_bias_covariance_(Matrix3Type::Identity())
    {
    }

    /**
     * @brief Construct a new Advanced Navstate T object
     *
     * @param navstate a navstate
     */
    explicit AdvancedNavstateT(const Base& navstate)
      : Base(navstate)
      , source_(static_cast<uint32_t>(Source::NONE))
      , angular_velocity_bias_(Vector3Type::Zero())
      , angular_velocity_bias_covariance_(Matrix3Type::Identity())
      , linear_acceleration_bias_(Vector3Type::Zero())
      , linear_acceleration_bias_covariance_(Matrix3Type::Identity())
    {
    }

    /**
     * @brief Construct a new Advanced Navstate T object
     *
     * @param p a 3D pose
     * @param v a 3D linear velocity
     * @param imu_bias angular velocity bias in rad/s and linear acceleration bias in m/s^2
     */
    AdvancedNavstateT(const Pose3Type& p, const Vector3Type& v, const Vector6Type& imu_bias)
      : Base(p, v)
      , source_(static_cast<uint32_t>(Source::NONE))
      , angular_velocity_bias_(imu_bias(0), imu_bias(1), imu_bias(2))
      , angular_velocity_bias_covariance_(Matrix3Type::Identity())
      , linear_acceleration_bias_(imu_bias(3), imu_bias(4), imu_bias(5))
      , linear_acceleration_bias_covariance_(Matrix3Type::Identity())
    {
    }

    /**
     * @brief Construct a new Advanced Navstate T object
     *
     * @param p a 3D pose
     * @param v a 3D linear velocity in m/s
     * @param _angular_velocity_bias angular velocity bias in rad/s
     * @param _linear_acceleration_bias linear acceleration bias in m/s^2
     */
    AdvancedNavstateT(const Pose3Type& p, const Vector3Type& v, const Vector3Type& _angular_velocity_bias,
                      const Vector3Type& _linear_acceleration_bias)
      : Base(p, v)
      , source_(static_cast<uint32_t>(Source::NONE))
      , angular_velocity_bias_(_angular_velocity_bias)
      , angular_velocity_bias_covariance_(Matrix3Type::Identity())
      , linear_acceleration_bias_(_linear_acceleration_bias)
      , linear_acceleration_bias_covariance_(Matrix3Type::Identity())
    {
    }

    /**
     * @brief Set the Source object
     *
     * @param source
     */
    inline void SetSource(const Source source)
    {
        source_ = static_cast<uint32_t>(source);
    }

    /**
     * @brief Get the Source object
     *
     * @return Source
     */
    inline Source GetSource() const
    {
        return static_cast<Source>(source_);
    }

    /**
     * @brief Get the Source object underlying reference
     *
     * @return Source reference
     */
    inline uint32_t& GetSourceUnderlying()
    {
        return source_;
    }

    /**
     * @brief Set the Angular Velocity Bias object
     *
     * @param angular_velocity_bias
     */
    inline void SetAngularVelocityBias(const Vector3Type& angular_velocity_bias)
    {
        angular_velocity_bias_ = angular_velocity_bias;
    }

    /**
     * @brief Get the Angular Velocity Bias object
     *
     * @return const Vector3Type&
     */
    inline const Vector3Type& GetAngularVelocityBias() const
    {
        return angular_velocity_bias_;
    }

    /**
     * @brief Set the Linear Acceleration Bias object
     *
     * @param linear_acceleration_bias
     */
    inline void SetLinearAccelerationBias(const Vector3Type& linear_acceleration_bias)
    {
        linear_acceleration_bias_ = linear_acceleration_bias;
    }

    /**
     * @brief Get the Linear Acceleration Bias object
     *
     * @return const Vector3Type&
     */
    inline const Vector3Type& GetLinearAccelerationBias() const
    {
        return linear_acceleration_bias_;
    }

    /**
     * @brief Set the Angular Velocity Bias Covariance object
     *
     * @param angular_velocity_bias_covariance
     */
    inline void SetAngularVelocityBiasCovariance(const Matrix3Type& angular_velocity_bias_covariance)
    {
        angular_velocity_bias_covariance_ = angular_velocity_bias_covariance;
    }

    /**
     * @brief Get the Angular Velocity Bias Covariance object
     *
     * @return const Matrix3Type&
     */
    inline const Matrix3Type& GetAngularVelocityBiasCovariance() const
    {
        return angular_velocity_bias_covariance_;
    }

    /**
     * @brief Set the Linear Acceleration Bias Covariance object
     *
     * @param linear_acceleration_bias_covariance
     */
    inline void SetLinearAccelerationBiasCovariance(const Matrix3Type& linear_acceleration_bias_covariance)
    {
        linear_acceleration_bias_covariance_ = linear_acceleration_bias_covariance;
    }

    /**
     * @brief Get the Linear Acceleration Bias Covariance object
     *
     * @return const Matrix3Type&
     */
    inline const Matrix3Type& GetLinearAccelerationBiasCovariance() const
    {
        return linear_acceleration_bias_covariance_;
    }

public:
    uint32_t    source_;                              /* source */
    Vector3Type angular_velocity_bias_;               /* imu angular velocity bias */
    Matrix3Type angular_velocity_bias_covariance_;    /* imu angular velocity bias covariance */
    Vector3Type linear_acceleration_bias_;            /* imu linear acceleration bias */
    Matrix3Type linear_acceleration_bias_covariance_; /* imu linear acceleration bias covariance */
};

using AdvancedNavstatef       = AdvancedNavstateT<float32_t>;
using AdvancedNavstated       = AdvancedNavstateT<float64_t>;
using AdvancedNavstate        = AdvancedNavstated;
using StampedAdvancedNavstate = StampedT<AdvancedNavstate>;

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_COMMON_NAVSTATE_H_
