/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-10-30
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_FRAME_CONVERTER_H_
#define _HOLO_PLANNING_FRAME_CONVERTER_H_

#include <array>

#include <holo/common/path.h>
#include <holo/core/types.h>
#include <holo/geometry/pose2.h>
#include <holo/planning/common/curve_point.h>

namespace holo
{
namespace planning
{
class FrameConverter
{
public:
    FrameConverter() = delete;

    static bool_t Cartesian2Frenet(const float64_t                 rs,
                                   const float64_t                 rx,
                                   const float64_t                 ry,
                                   const float64_t                 rtheta,
                                   const float64_t                 rkappa,
                                   const float64_t                 rdkappa,
                                   const float64_t                 x,
                                   const float64_t                 y,
                                   const float64_t                 v,
                                   const float64_t                 a,
                                   const float64_t                 theta,
                                   const float64_t                 kappa,
                                   std::array<float64_t, 3>* const ptr_s_condition,
                                   std::array<float64_t, 3>* const ptr_d_condition);

    static bool_t Frenet2Cartesian(const float64_t                 rs,
                                   const float64_t                 rx,
                                   const float64_t                 ry,
                                   const float64_t                 rtheta,
                                   const float64_t                 rkappa,
                                   const float64_t                 rdkappa,
                                   const std::array<float64_t, 3>& s_condition,
                                   const std::array<float64_t, 3>& d_condition,
                                   float64_t* const                ptr_x,
                                   float64_t* const                ptr_y,
                                   float64_t* const                ptr_theta,
                                   float64_t* const                ptr_kappa,
                                   float64_t* const                ptr_v,
                                   float64_t* const                ptr_a);

    static void Global2Body(const geometry::Pose2d& global_obj_pos,
                            const geometry::Pose2d& global_car_pos,
                            common::PathPoint&      local_obj_pose);

    static void Body2Global(const geometry::Pose2d& local_obj_pos,
                            const geometry::Pose2d& global_car_pos,
                            common::PathPoint&      global_obj_pos);

    static void Global2Body(const CurvePoint&       global_obj_point,
                            const geometry::Pose2d& global_car_pos,
                            CurvePoint&             local_obj_point);

    static void Body2Global(const CurvePoint&       local_obj_point,
                            const geometry::Pose2d& global_car_pos,
                            CurvePoint&             global_obj_point);
};

}  // namespace planning
}  // namespace holo

#endif