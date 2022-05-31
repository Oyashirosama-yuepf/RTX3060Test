/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file calibration_base.h
 * @brief define calibration interfaces
 * @author luopei@holomatic.com
 * @author zhaojiaxing@holomatic.com
 * @date 2020-07-16
 */

#ifndef HOLO_CALIBRATION_COMMON_CALIBRATION_BASE_H_
#define HOLO_CALIBRATION_COMMON_CALIBRATION_BASE_H_

#include <holo/common/coordinate.h>
#include <holo/common/extrinsic.h>
#include <holo/common/gnss_pvt.h>
#include <holo/common/intrinsic.h>
#include <holo/common/odometry.h>
#include <holo/common/road_frame.h>
#include <holo/core/epsilon.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/line2.h>
#include <holo/geometry/line_segment2.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/quaternion.h>
#include <holo/geometry/rot2.h>
#include <holo/geometry/rot3.h>
#include <holo/numerics/matrix.h>
#include <holo/numerics/vector.h>

namespace holo
{
namespace calibration
{
/**
 * @addtogroup calibration
 * @{
 *
 */

/**
 * @brief calibration base class, define calibration interfaces
 *
 * @tparam ContainerT
 */
template <typename ContainerT>
class CalibrationBaseT
{
public:
    /**
     * @brief define calibration basic geometry types
     */
    using Scalar         = holo::float64_t;
    using Point2Type     = holo::geometry::Point2T<Scalar>;
    using Point3Type     = holo::geometry::Point3T<Scalar>;
    using Pose2Type      = holo::geometry::Pose2T<Scalar>;
    using Pose3Type      = holo::geometry::Pose3T<Scalar>;
    using QuaternionType = holo::geometry::QuaternionT<Scalar>;
    using Rot2Type       = holo::geometry::Rot2T<Scalar>;
    using Rot3Type       = holo::geometry::Rot3T<Scalar>;

    /**
     * @brief define calibration basic numerics types
     */
    using Matrix3Type = holo::numerics::Matrix3T<Scalar>;
    using MatrixXType = holo::numerics::MatrixXT<Scalar>;
    using Vector2Type = holo::numerics::Vector2T<Scalar>;
    using Vector3Type = holo::numerics::Vector3T<Scalar>;
    using Vector4Type = holo::numerics::Vector4T<Scalar>;
    using Vector5Type = holo::numerics::Vector5T<Scalar>;
    using Vector6Type = holo::numerics::Vector6T<Scalar>;
    using Vector9Type = holo::numerics::VectorT<Scalar, 9>;
    using VectorXType = holo::numerics::VectorXT<Scalar>;

    using Container = ContainerT;

    /**
     * @brief Construct a new Calibration Base T object
     *
     */
    CalibrationBaseT()
    {
    }

    /**
     * @brief Destroy the Calibration Base T object
     *
     */
    virtual ~CalibrationBaseT()
    {
    }

    /**
     * @brief core function compute the desired extrinsic[s] at each container,
     *        each container compute the transformation matrix between source,
     *        and target frame.
     *
     * @return true
     * @return false
     */
    virtual bool_t Compute() = 0;

    /**
     * @brief return the size of containers
     *
     * @return uint8_t
     */
    virtual uint8_t GetContainerNum() const = 0;

    /**
     * @brief function to get container in case we just have one container
     *
     * @return const ContainerT&
     */
    virtual ContainerT const& GetContainer() const = 0;

    /**
     * @brief Get the Container object
     *
     * @return ContainerT&
     */
    virtual ContainerT& GetContainer() = 0;

    /**
     * @brief function to get the ith container in case we have multiple containers
     *
     * @return const ContainerT&
     */
    virtual ContainerT const& GetContainer(uint8_t const) const = 0;

    /**
     * @brief Get the Container object
     *
     * @return ContainerT&
     */
    virtual ContainerT& GetContainer(uint8_t const) = 0;

    /**
     * @brief Get the Extrinsic object
     *
     * @return Pose3Type
     */
    virtual Pose3Type GetExtrinsic()
    {
        return GetContainer().GetExtrinsic();
    }

    /**
     * @brief get the extrinsic
     *
     * @return Pose3Type
     */
    virtual Pose3Type GetExtrinsic() const
    {
        return GetContainer().GetExtrinsic();
    }

    /**
     * @brief get the ith extrinsic
     *
     * @param i
     * @return Pose3Type
     */
    virtual Pose3Type GetExtrinsic(uint8_t const i)
    {
        return GetContainer(i).GetExtrinsic();
    }

    /**
     * @brief get the ith extrinsic
     *
     * @param i
     * @return Pose3Type
     */
    virtual Pose3Type GetExtrinsic(uint8_t const i) const
    {
        return GetContainer(i).GetExtrinsic();
    }

protected:
    /**
     * @brief convert extrinsic [Pose3] in container to optimize variable extrinsics_
     *
     */
    void convertContainersToExtrinsics();

    /**
     * @brief back convert optimize variable extrinsics_ to container extrinsic [Pose3]
     *
     */
    void convertExtrinsicsToContainers();

    /**
     * @brief extrinsic parameters for optimize
     *        format [xyz qxqyqzqw]
     *
     */
    std::vector<Scalar> extrinsics_;

    /**
     * @brief extrinsic dimension
     *
     */
    const uint8_t parameter_dimension_ = 7u;

private:
};

/**
 * @}
 *
 */

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_COMMON_CALIBRATION_BASE_H_  ----- */