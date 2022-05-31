/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2017-10-18
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_ROAD_PARAM_H_
#define _HOLO_PLANNING_ROAD_PARAM_H_

#include <holo/core/types.h>
#include <holo/planning/common/macro.h>

namespace holo
{
namespace planning
{
class RoadParam
{
public:
    RoadParam();
    float64_t GetLaneWidth() const;
    void      SetLaneWidth(float64_t width);

    void      SetRoadMaxVelocity(float64_t velocity);
    float64_t GetRoadMaxVelocity() const;

    void      SetAheadDistanceAndSpeed(float64_t dis, float64_t v);
    void      SetTargetSpeedToCurrentLimit(float64_t v);
    float64_t GetDistanceAhead();
    float64_t GetTargetSpeedAhead();

    void Reset();

    /**
     * @brief set current lane curvature
     */
    void SetLaneCurvature(float64_t curv);

    /**
     * @brief get current lane curvature
     *
     * @return the curvature
     */
    float64_t GetLaneCurvature() const;

private:
    float64_t lane_width_;

    /**
     * @brief       the max velocity of car in current road
     */
    float64_t road_max_velocity_;

    /**
     * @brief       distance ahead param
     *              (>=0: approach to entrance of highway)
     *              (< 0: normal driving)
     */
    float64_t distance_ahead_;

    /**
     * @brief       target speed ahead param
     */
    float64_t target_speed_ahead_;

    /**
     * @brief lane curvature
     */
    float64_t lane_curvature_;
};

}  // namespace planning
}  // namespace holo

#endif
