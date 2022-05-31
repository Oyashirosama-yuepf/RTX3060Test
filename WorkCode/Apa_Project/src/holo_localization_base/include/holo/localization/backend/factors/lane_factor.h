/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lane_factor.h
 * @brief A class to define lane factor
 * @author Zhang Yelin (zhangyelin@holomatic.com)
 * @date Dec 13, 2019
 */

#ifndef HOLO_LOCALIZATION_BACKEND_FACTORS_LANE_FACTOR_H_
#define HOLO_LOCALIZATION_BACKEND_FACTORS_LANE_FACTOR_H_

#include <gtest/gtest.h>
#include <holo/geometry/polyfit2.h>
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Lane2Factor
{
public:
    using Vector3                = holo::numerics::Vector3T<Scalar>;
    using Line2                  = holo::geometry::Line2T<Scalar>;
    using LaneCorrespondenceType = holo::localization::LaneCorrespondences::Type;

    /**
     * @brief constructor
     */
    Lane2Factor() = delete;

    /**
     * @brief constructor
     *
     * @param[in] pose_key Key
     * @param[in] point a point belong to the line
     * @param[in] line  line 2d
     * @param[in] sigma standard deviation of measurement
     * @param[in] lane_correspondence_type type of lane correspondence
     * @param[in] disable_rotation_optimization disable rotation optimization flag
     */
    Lane2Factor(const uint64_t& pose_key, const Point3Type& point, const Line2& line, const Scalar& sigma,
                const LaneCorrespondenceType& lane_correspondence_type      = LaneCorrespondenceType::PROJECT_TO_WORLD,
                const bool_t                  disable_rotation_optimization = false);

    /**
     * @brief destructor
     */
    ~Lane2Factor()
    {
    }

    /**
     * @brief get a void pointer of lane factor
     * @details it can be cast to a pointer of base class of holo::localization::internal::Lane2Factor
     * @note whoever calls this method must take care of the allocated memory and release it after using !!!
     *
     * @return void* void pointer to the created lane factor
     * @throw std::bad_alloc if memory allocation fails
     */
    void* GetFactor();

private:
    const uint64_t         pose_index_;                     ///< pose index
    Point3Type             point_;                          ///< 3D point
    Line2                  line_;                           ///< line 2d
    Scalar                 sigma_;                          ///< standard deviation of measurement
    LaneCorrespondenceType lane_correspondence_type_;       ///< type of lane correspondence
    bool_t                 disable_rotation_optimization_;  ///< disable rotation optimization flag

};  // Lane2Factor

/**
 * @}
 *
 */
}  // namespace localization
}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_FACTORS_LANE_FACTOR_H_
