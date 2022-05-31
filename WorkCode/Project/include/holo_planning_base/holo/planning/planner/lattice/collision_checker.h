/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file collision_checker.h
 * @brief the header of the collision checker in lattice
 * @author zhangyuchen(zhangyuchen@holomatic.com)
 * @date 2019-12-25
 */

#ifndef _HOLO_PLANNING_LATTICE_COLLISION_CHECKER_H_
#define _HOLO_PLANNING_LATTICE_COLLISION_CHECKER_H_

#include <holo/core/types.h>

#include <holo/planning/common/box/normal_box.h>
#include <holo/planning/math/curve/curve_1d.h>

namespace holo
{
namespace planning
{
namespace lattice
{
/**
 * @brief Class for collision check
 */
class CollisionChecker
{
public:
    using predicted_boxes_trajectory_ptr = std::shared_ptr<std::vector<std::vector<NormalBox>>>;
    /**
     * @brief Construct a new Collision Checker object
     *
     * @param boxes_trajectory_ptr pointer of predicted obstacles trajectory boxs
     */
    CollisionChecker(const predicted_boxes_trajectory_ptr& boxes_trajectory_ptr);

    /**
     * @brief Destroy the Collision Checker object
     */
    ~CollisionChecker() = default;

    /**
     * @brief collision check
     *
     * @param lon_curve longitudinal curve
     * @param lat_curve lateral curve
     * @param ego_box box of ego car
     *
     * @return bool_t true if pass check, false otherwise
     */
    bool_t Check(const std::shared_ptr<math::Curve1d>& lon_curve,
                 const std::shared_ptr<math::Curve1d>& lat_curve,
                 NormalBox&                            ego_box) const;

private:
    /**
     * @brief pointer of predicted obstacles' trajectory
     */
    predicted_boxes_trajectory_ptr boxes_trajectory_ptr_;
};

}  // namespace lattice
}  // namespace planning
}  // namespace holo

#endif