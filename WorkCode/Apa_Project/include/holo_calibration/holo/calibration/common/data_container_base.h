/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file data_container_base.h
 * @brief define data container interfaces
 * @author luopei@holomatic.com
 * @author zhaojiaxing@holomatic.com
 * @date 2020-07-28
 */

#ifndef HOLO_CALIBRATION_COMMON_DATA_CONTAINER_BASE_H_
#define HOLO_CALIBRATION_COMMON_DATA_CONTAINER_BASE_H_

#include <holo/geometry/pose3.h>

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
 * @brief base class for data container
 *
 * @tparam SourceType
 * @tparam TargetType
 */
template <typename SourceType, typename TargetType>
class DataContainerBaseT
{
public:
    /**
     * @brief define data container basic geometry types
     */
    using Scalar    = holo::float64_t;
    using Pose3Type = holo::geometry::Pose3T<Scalar>;

    /**
     * @brief Construct a new Data Container BaseT object
     *
     */
    DataContainerBaseT()
    {
    }

    /**
     * @brief Destroy the Data Container BaseT object
     *
     */
    virtual ~DataContainerBaseT()
    {
    }

    /**
     * @brief Get data size
     *
     * @return uint16_t
     */
    virtual uint16_t GetDataSize() const = 0;

    /**
     * @brief Get the ith element in Source object
     *
     * @return SourceType const&
     */
    virtual SourceType const& GetSource(uint16_t const) const = 0;

    /**
     * @brief Get the ith element in Source object
     *
     * @return SourceType&
     */
    virtual SourceType& GetSource(uint16_t const) = 0;

    /**
     * @brief Get the ith element in Targets object
     *
     * @return SourceType const&
     */
    virtual TargetType const& GetTarget(uint16_t const) const = 0;

    /**
     * @brief Get the ith element in Targets object
     *
     * @return SourceType&
     */
    virtual TargetType& GetTarget(uint16_t const) = 0;

    /**
     * @brief update data status based on extrinsic
     *
     */
    virtual void UpdateStatus() = 0;

    /**
     * @brief Get the Extrinsic object
     *
     * @return const Pose3Type&
     */
    const Pose3Type& GetExtrinsic() const
    {
        return extrinsic_;
    }

    /**
     * @brief Get the Extrinsic object
     *
     * @return Pose3Type&
     */
    Pose3Type& GetExtrinsic()
    {
        return extrinsic_;
    }

    /**
     * @brief Set the Extrinsic object
     *
     * @param extrinsic
     */
    void SetExtrinsic(Pose3Type const& extrinsic)
    {
        extrinsic_ = extrinsic;
    }

    /**
     * @brief Set the initial extrinsic parameter
     *
     * @param pose
     */
    void SetInitExtrinsic(Pose3Type const& extrinsic)
    {
        extrinsic_ = extrinsic;
    }

protected:
    Pose3Type extrinsic_;
};

}  // namespace calibration

}  // namespace holo

#endif /* ----- #ifndef HOLO_CALIBRATION_COMMON_DATA_CONTAINER_BASE_H_  ----- */
