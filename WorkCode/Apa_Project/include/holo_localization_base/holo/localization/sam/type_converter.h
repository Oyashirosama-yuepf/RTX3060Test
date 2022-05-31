/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file type_converter.h
 * @brief this class provides functions to convert between holo type and gtsam type
 * @author Shuaijie Li(lishuaijie@holomatic.com)
 * @date "2021-03-13"
 */

#ifndef HOLO_LOCALIZATION_SAM_TYPE_CONVERTER_H_
#define HOLO_LOCALIZATION_SAM_TYPE_CONVERTER_H_

#include <holo/localization/common/types.h>
#include <holo/localization/sam/sam.h>

namespace holo
{
namespace localization
{
class TypeConverter
{
public:
    /**
     * @brief convert gtsam::Vector3 to holo::numerics::Vector3
     *
     * @param[in] src gtsam::Vector3
     * @param[in][out] tgt holo::numerics::Vector3
     */
    template <typename Scalar>
    static void Convert(GTVector3 const& src, holo::numerics::Vector3T<Scalar>& tgt)
    {
        for (uint16_t i = 0u; i < 3u; i++)
        {
            tgt[i] = src[i];
        }
    }

    /**
     * @brief convert holo::numerics::Vector3 to gtsam::Vector3
     *
     * @param[in] src holo::numerics::Vector3
     * @param[in][out] tgt gtsam::Vector3
     */
    template <typename Scalar>
    static void Convert(holo::numerics::Vector3T<Scalar> const& src, GTVector3& tgt)
    {
        for (uint16_t i = 0u; i < 3u; i++)
        {
            tgt[i] = src[i];
        }
    }

    /**
     * @brief convert holo::numerics::Matrix3 to gtsam::Matrix3
     *
     * @param[in] src holo::numerics::Matrix3
     * @param[in][out] tgt gtsam::Matrix3
     */
    template <typename Scalar>
    static void Convert(holo::numerics::Matrix3T<Scalar> const& src, GTMatrix3& tgt)
    {
        for (uint16_t i = 0u; i < 3u; i++)
        {
            for (uint16_t j = 0u; j < 3u; j++)
            {
                tgt(i, j) = src(i, j);
            }
        }
    }

    /**
     * @brief convert gtsam::Matrix3 to holo::numerics::Matrix3
     *
     * @param[in] src gtsam::Matrix3
     * @param[in][out] tgt holo::numerics::Matrix3
     */
    template <typename Scalar>
    static void Convert(GTMatrix3 const& src, holo::numerics::Matrix3T<Scalar>& tgt)
    {
        for (uint16_t i = 0u; i < 3u; i++)
        {
            for (uint16_t j = 0u; j < 3u; j++)
            {
                tgt(i, j) = src(i, j);
            }
        }
    }

    /**
     * @brief convert holo::numerics::Matrix6 to gtsam::Matrix6
     *
     * @param[in] src holo::numerics::Matrix6
     * @param[in][out] tgt gtsam::Matrix6
     */
    template <typename Scalar>
    static void Convert(holo::numerics::Matrix6T<Scalar> const& src, GTMatrix6& tgt)
    {
        for (uint16_t i = 0u; i < 6u; i++)
        {
            for (uint16_t j = 0u; j < 6u; j++)
            {
                tgt(i, j) = src(i, j);
            }
        }
    }

    /**
     * @brief convert gtsam::Matrix6 to holo::numerics::Matrix6
     *
     * @param[in] src gtsam::Matrix6
     * @param[in][out] tgt holo::numerics::Matrix6
     */
    template <typename Scalar>
    static void Convert(GTMatrix6 const& src, holo::numerics::Matrix6T<Scalar>& tgt)
    {
        for (uint16_t i = 0u; i < 6u; i++)
        {
            for (uint16_t j = 0u; j < 6u; j++)
            {
                tgt(i, j) = src(i, j);
            }
        }
    }

    /**
     * @brief convert gtsam::Point3 to holo::geometry::Point3
     *
     * @param[in] src gtsam::Point3
     * @param[in][out] tgt holo::geometry::Point3
     */
    template <typename Scalar>
    static void Convert(GTPoint3 const& src, holo::geometry::Point3T<Scalar>& tgt)
    {
        tgt.Set(src[0u], src[1u], src[2u]);
    }

    /**
     * @brief convert holo::geometry::Point3 to gtsam::Point3
     *
     * @param[in] src holo::geometry::Point3
     * @param[in][out] tgt gtsam::Point3
     */
    template <typename Scalar>
    static void Convert(holo::geometry::Point3T<Scalar> const& src, GTPoint3& tgt)
    {
        tgt[0u] = src.GetX();
        tgt[1u] = src.GetY();
        tgt[2u] = src.GetZ();
    }

    /**
     * @brief convert gtsam::Rot3 to holo::geometry::Rot3
     *
     * @param[in] src gtsam::Rot3
     * @param[in][out] tgt holo::geometry::Rot3
     */
    template <typename Scalar>
    static void Convert(GTRot3 const& src, holo::geometry::Rot3T<Scalar>& tgt)
    {
        GTMatrix3 rot = src.matrix();
        new (&tgt) holo::geometry::Rot3T<Scalar>(rot(0u, 0u), rot(0u, 1u), rot(0u, 2u), rot(1u, 0u), rot(1u, 1u),
                                                 rot(1u, 2u), rot(2u, 0u), rot(2u, 1u), rot(2u, 2u));
    }

    /**
     * @brief convert holo::geometry::Rot3 to gtsam::Rot3
     *
     * @param[in] src holo::geometry::Rot3
     * @param[in][out] tgt gtsam::Rot3
     */
    template <typename Scalar>
    static void Convert(holo::geometry::Rot3T<Scalar> const& src, GTRot3& tgt)
    {
        new (&tgt)
            GTRot3(src.R00(), src.R01(), src.R02(), src.R10(), src.R11(), src.R12(), src.R20(), src.R21(), src.R22());
    }

    /**
     * @brief convert gtsam::Pose3 to holo::geometry::Pose3
     *
     * @param[in] src gtsam::Pose3
     * @param[in][out] tgt holo::geometry::Pose3
     */
    template <typename Scalar>
    static void Convert(GTPose3 const& src, holo::geometry::Pose3T<Scalar>& tgt)
    {
        typename holo::geometry::Pose3T<Scalar>::Rot3Type rot;
        Convert(src.rotation(), rot);

        typename holo::geometry::Pose3T<Scalar>::Point3Type trans;
        Convert(src.translation(), trans);

        new (&tgt) holo::geometry::Pose3T<Scalar>(rot, trans);
    }

    /**
     * @brief convert holo::geometry::Pose3 to gtsam::Pose3
     *
     * @param[in] src holo::geometry::Pose3
     * @param[in][out] tgt gtsam::Pose3
     */
    template <typename Scalar>
    static void Convert(holo::geometry::Pose3T<Scalar> const& src, GTPose3& tgt)
    {
        GTRot3 rot;
        Convert(src.GetRotation(), rot);

        GTPoint3 trans;
        Convert(src.GetTranslation(), trans);

        new (&tgt) GTPose3(rot, trans);
    }

    /**
     * @brief convert gtsam::NavState to holo::localization::Navstate
     *
     * @param[in] src gtsam::NavState
     * @param[in][out] tgt holo::localization::Navstate
     */
    template <typename Scalar>
    static void Convert(GTNavState const& src, holo::localization::NavstateT<Scalar>& tgt)
    {
        typename holo::localization::NavstateT<Scalar>::Pose3Type pose;
        Convert(src.pose(), pose);

        typename holo::localization::NavstateT<Scalar>::Vector3Type velocity;
        Convert(src.v(), velocity);

        tgt.SetPose(pose);
        tgt.SetVelocity(velocity);
    }

    /**
     * @brief convert holo::localization::Navstate to gtsam::NavState
     *
     * @param[in] src holo::localization::Navstate
     * @param[in][out] tgt gtsam::NavState
     */
    template <typename Scalar>
    static void Convert(holo::localization::NavstateT<Scalar> const& src, GTNavState& tgt)
    {
        GTPose3 pose;
        Convert(src.GetPose(), pose);

        GTVector3 velocity;
        Convert(src.GetVelocity(), velocity);

        new (&tgt) GTNavState(pose, velocity);
    }

    /**
     * @brief convert gtsam::ConstantBias to holo::common::ImuBias
     *
     * @param[in] src gtsam::ConstantBias
     * @param[in][out] tgt holo::common::ImuBias
     */
    template <typename Scalar>
    static void Convert(GTConstantBias const& src, holo::common::ImuBiasT<Scalar>& tgt)
    {
        GTVector3 const& acc  = src.accelerometer();
        GTVector3 const& gyro = src.gyroscope();

        tgt.SetLinearAccelerationBias(acc[0u], acc[1u], acc[2u]);
        tgt.SetAngularVelocityBias(gyro[0u], gyro[1u], gyro[2u]);
    }

    /**
     * @brief convert holo::common::ImuBias to gtsam::ConstantBias
     *
     * @param[in] src holo::common::ImuBias
     * @param[in][out] tgt gtsam::ConstantBias
     */
    template <typename Scalar>
    static void Convert(holo::common::ImuBiasT<Scalar> const& src, GTConstantBias& tgt)
    {
        GTVector3 const acc  = src.template GetLinearAccelerationBias<GTVector3>();
        GTVector3 const gyro = src.template GetAngularVelocityBias<GTVector3>();
        new (&tgt) GTConstantBias(acc, gyro);
    }

};  // class TypeConverter
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_SAM_TYPE_CONVERTER_H_
