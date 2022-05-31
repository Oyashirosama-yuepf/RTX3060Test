/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file projection_line_factor.h
 * @brief A class to define projection line factor
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date June 20, 2020
 */

#ifndef HOLO_LOCALIZATION_BACKEND_FACTORS_PROJECTION_LINE_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_FACTORS_PROJECTION_LINE_FACTOR_H_

#include <gtest/gtest.h>
#include <holo/localization/common/types.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup backend
 * @{
 *
 */

/**
 * @brief This class define ProjectionLineFactor that optimize the pose of body in world frame
 * @details the pose of body in world frame be optimized by reduce error that projection map point to fitted line
 *
 */
class ProjectionLineFactor
{
public:
    /**
     * @brief Disable default constructor
     */
    ProjectionLineFactor() = delete;

    /**
     * @brief Constructor a new ProjectionLineFactor object
     *
     * @param[in] index index of pose that body in world frame
     * @param[in] point map point in world frame
     * @param[in] bTc pose of camera in body frame
     * @param[in] k intrinsic of camera
     * @param[in] line fitted line
     * @param[in] sigma standard deviation of measurement
     * @param[in] huber_threshold threshold of huber loss function, if you don't use huber loss, please enter a negative
     * value
     * @param[in] enable_rotation_constraint enable rotation constraint, if false, the rotation is not optimized
     */
    ProjectionLineFactor(uint64_t const index, Point3Type const& point, Pose3Type const& bTc, Matrix3Type const& K,
                         Line2Type const& line, Scalar const sigma, Scalar const huber_loss_threshold = -1.0,
                         bool_t const enable_rotation_constraint = true) noexcept;

    /**
     * @brief Destructor the ProjectionLineFactor object
     */
    ~ProjectionLineFactor()
    {
    }

    /**
     * @brief Get a void pointer of ProjectionLineFactor
     * @details it can be cast to a pointer of base class of holo::localization::internal::ProjectionLineFactor
     * @note whoever calls this method must take care of the allocated memory and release it after using !!!
     *
     * @return void* void pointer to the created ProjectionLineFactor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor();

private:
    uint64_t    index_;                       ///< index of pose that body in world frame
    Point3Type  point_;                       ///< map point
    Pose3Type   bTc_;                         ///< pose of camera in body frame
    Matrix3Type K_;                           ///< intrinsic of camera
    Line2Type   line_;                        ///< fitted line
    Scalar      sigma_;                       ///< standard deviation of measurement
    Scalar      huber_loss_threshold_;        ///< the threshold of huber loss
    bool_t      enable_rotation_constraint_;  ///< enable rotation constraint

};  // ProjectionLineFactor

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_FACTORS_PROJECTION_LINE_FACTOR_H_
