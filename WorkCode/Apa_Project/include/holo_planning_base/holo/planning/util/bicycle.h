/**
 * @file bicycle.h
 * @brief the header of the bicycle
 * @author sunlei(sunlei@holomatic.com)
 * @date 2017-11-20
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_BICYCLE_H_
#define _HOLO_PLANNING_BICYCLE_H_

#include <string>

#include <holo/core/types.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace planning
{
/**
 * @brief Class for bicycle.
 *
 * @details A bicycle model, which is to simulate vechicle.
 */
class Bicycle
{
public:
    /**
     * @brief Constructor.
     *
     * @param pos The position
     * @param heading The heading
     * @param velocity The velocity
     * @param wheelbase The wheelbase
     * @param wheelangle The wheelangle
     * @param acc The acceleration
     * @param max_velocity The maximum velocity
     */
    Bicycle(const geometry::Point3d&         pos,
            float64_t                        heading,
            float64_t                        velocity,
            float64_t                        wheelbase,
            float64_t                        wheelangle,
            float64_t                        acc,
            std::pair<float64_t, float64_t>& max_velocity);

    /**
     * @brief Destroys the object.
     */
    ~Bicycle();

    /**
     * @brief Gets the position.
     *
     * @return The position.
     */
    const geometry::Point3d& GetPosition() const;

    /**
     * @brief Gets the heading.
     *
     * @return The heading.
     */
    float64_t GetHeading() const;

    /**
     * @brief Gets the velocity.
     *
     * @return The velocity.
     */
    float64_t GetVelocity() const;

    /**
     * @brief Gets the wheelbase.
     *
     * @return The wheelbase.
     */
    float64_t GetWheelbase() const;

    /**
     * @brief Sets the wheel angle.
     *
     * @param angle The angle
     */
    void SetWheelAngle(float64_t angle);

    /**
     * @brief Gets the wheel angle.
     *
     * @return The wheel angle.
     */
    float64_t GetWheelAngle() const;

    /**
     * @brief Gets the input acc.
     *
     * @return The input acc.
     */
    float64_t GetAcc() const;

    /**
     * @brief Set max velocity.
     *
     * @param v The new max velocity
     */
    void SetMaxVelocity(const std::pair<float64_t, float64_t>& v);

    /**
     * @brief Get max velocity.
     *
     * @return The max velocity
     */
    const std::pair<float64_t, float64_t>& GetMaxVelocity() const;

    /**
     * @brief Gets the total distance.
     *
     * @return The total distance.
     */
    float64_t GetTotalDistance() const;

    /**
     * @brief Gets the current acceleration.
     *
     * @return The velocity.
     */
    float64_t GetCurrentAcceleration() const;

    /**
     * @brief Move one step.
     *
     * @param delta_t The step time
     */
    void Step(float64_t delta_t);

    /**
     * @brief Move one step.
     *
     * @param dist The step distance
     */
    void StepDistance(float64_t dist);

private:
    /**
     * @brief The vehicle's positon
     */
    geometry::Point3d position_;

    /**
     * @brief The vehicle's heading
     */
    float64_t heading_;

    /**
     * @brief The vehicle's velocity
     */
    float64_t velocity_;

    /**
     * @brief The vehicle's current acceleration
     */
    float64_t current_acc_;

    /**
     * @brief The vehicle's wheelbase
     */
    float64_t wheelbase_;

    /**
     * @brief The vehicle's wheelangle
     */
    float64_t wheelangle_;

    /**
     * @brief The vehicle's acceleration
     */
    float64_t acc_;

    /**
     * @brief The vehicle's maximum velocity
     */
    std::pair<float64_t, float64_t> max_velocity_;

    /**
     * @brief The total distance of vehicle moved
     */
    float64_t total_distance_;
};

}  // namespace planning
}  // namespace holo

#endif
