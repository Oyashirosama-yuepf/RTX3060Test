/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file constraint_checker.h
 * @brief the header of the constraint checker in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_CONSTRAINT_CHECKER_H_
#define _HOLO_PLANNING_LATTICE_CONSTRAINT_CHECKER_H_

#include <holo/common/path.h>
#include <holo/core/types.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief struct for constraint
 */
struct LatticeConstraint
{
    /**
     * @brief longitudinal speed lower bound
     */
    float64_t lon_speed_lower_bound = -0.001;

    /**
     * @brief longitudinal speed upper bound
     */
    float64_t lon_speed_upper_bound = 140.0 / 3.6;

    /**
     * @brief longitudinal acceleration lower bound
     */
    float64_t lon_acc_lower_bound = -4.0;

    /**
     * @brief longitudinal acceleration upper bound
     */
    float64_t lon_acc_upper_bound = 2.0;

    /**
     * @brief trajectory curvature bound
     */
    float64_t kappa_bound = 0.05;

    /**
     * @brief longitudinal jerk lower bound
     */
    float64_t lon_jerk_lower_bound = -4.0;

    /**
     * @brief longitudinal jerk upper bound
     */
    float64_t lon_jerk_upper_bound = 4.0;

    /**
     * @brief lateral acceleration bound
     */
    float64_t lat_acc_bound = 4.0;

    /**
     * @brief lateral jerk bound
     */
    float64_t lat_jerk_bound = 4.0;
};

/**
 * @brief Class for collision check
 */
class ConstraintChecker
{
public:
    using ConstraintPtr = std::shared_ptr<LatticeConstraint>;
    /**
     * @brief enum to express the result of the check
     */
    enum class Result
    {
        VALID = 0,
        LON_VELOCITY_OUT_OF_BOUND,
        LON_ACCELERATION_OUT_OF_BOUND,
        LON_JERK_OUT_OF_BOUND,
        LAT_VELOCITY_OUT_OF_BOUND,
        LAT_ACCELERATION_OUT_OF_BOUND,
        LAT_JERK_OUT_OF_BOUND,
        CURVATURE_OUT_OF_BOUND,
    };

    /**
     * @brief delete constructor
     */
    ConstraintChecker() = delete;

    /**
     * @brief check physical constraints
     *
     * @param trajectory 2d path need to check
     * @param constraint_ptr pointer of constraint
     *
     * @return VALID trajectory passes check
     * @return LON_VELOCITY_OUT_OF_BOUND trajectory can't pass check because longitudinal velocity is out of bound
     * @return LON_ACCELERATION_OUT_OF_BOUND trajectory can't pass check because longitudinal acc is out of bound
     * @return LON_JERK_OUT_OF_BOUND trajectory can't pass check because longitudinal jerk is out of bound
     * @return LAT_VELOCITY_OUT_OF_BOUND trajectory can't pass check because lateral velocity is out of bound
     * @return LAT_ACCELERATION_OUT_OF_BOUND trajectory can't pass check because lateral acc is out of bound
     * @return LAT_JERK_OUT_OF_BOUND trajectory can't pass check because lateral jerk is out of bound
     * @return CURVATURE_OUT_OF_BOUND trajectory can't pass check because curvature is out of bound
     */
    static Result Check(const common::Path& trajectory, const ConstraintPtr& constraint_ptr);
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif