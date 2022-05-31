/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file calibration_base.hpp
 * @brief define calibration interfaces
 * @author luopei@holomatic.com
 * @author zhaojiaxing@holomatic.com
 * @date 2020-07-16
 */

namespace holo
{
namespace calibration
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CalibrationBaseT<T>::convertContainersToExtrinsics()
{
    uint8_t num = GetContainerNum();
    extrinsics_.resize(num * parameter_dimension_);

    for (uint8_t i = 0u; i < num; ++i)
    {
        Container const& container = GetContainer(i);
        Pose3Type        pose      = container.extrinsic();
        Matrix3Type      rot       = pose.GetRotation().ToMatrix();
        Vector3Type      t         = pose.GetTranslation().ToVector();
        QuaternionType   q(rot);
        extrinsics_[i * parameter_dimension_]      = t(0u);
        extrinsics_[i * parameter_dimension_ + 1u] = t(1u);
        extrinsics_[i * parameter_dimension_ + 2u] = t(2u);
        extrinsics_[i * parameter_dimension_ + 3u] = q.GetX();
        extrinsics_[i * parameter_dimension_ + 4u] = q.GetY();
        extrinsics_[i * parameter_dimension_ + 5u] = q.GetZ();
        extrinsics_[i * parameter_dimension_ + 6u] = q.GetW();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
void CalibrationBaseT<T>::convertExtrinsicsToContainers()
{
    uint8_t num = GetContainerNum();
    extrinsics_.resize(num * parameter_dimension_);

    for (uint8_t i = 0u; i < num; ++i)
    {
        Container&     container = GetContainer(i);
        Scalar         x         = extrinsics_[i * parameter_dimension_];
        Scalar         y         = extrinsics_[i * parameter_dimension_ + 1];
        Scalar         z         = extrinsics_[i * parameter_dimension_ + 2];
        Scalar         qx        = extrinsics_[i * parameter_dimension_ + 3];
        Scalar         qy        = extrinsics_[i * parameter_dimension_ + 4];
        Scalar         qz        = extrinsics_[i * parameter_dimension_ + 5];
        Scalar         qw        = extrinsics_[i * parameter_dimension_ + 6];
        Vector3Type    t(x, y, z);
        QuaternionType q(qw, qx, qy, qz);
        Pose3Type      pose(Rot3(q.ToRotationMatrix()), Point3Type(t));
        container.SetExtrinsic(pose);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}  // namespace calibration

}  // namespace holo
