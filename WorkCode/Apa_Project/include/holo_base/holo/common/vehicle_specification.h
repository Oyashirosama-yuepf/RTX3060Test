/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_specification.h
 * @brief This header file define vehicle parameters.
 * @author lichao@holomatic.com
 * @date Sep 24, 2019
 */

#ifndef HOLO_COMMON_VEHICLE_SPECIFICATION_H_
#define HOLO_COMMON_VEHICLE_SPECIFICATION_H_

#include <string>

#include <holo/core/types.h>

namespace holo
{
/**
 * @addtogroup common
 * @{
 *
 */

/**
 * @brief This class defines vehicle specification.
 *
 * @details this class mainly aims at holding the type and the size of components
 * in vehicle
 */
class VehicleSpecification
{
public:
    using Scalar = float32_t;
    /**
     * @brief construtor
     */
    VehicleSpecification() = delete;

    /**
     * @brief construtor
     * @param[in] fn file directory
     * @param[in] verbose verbosity
     * @throws the file directory does not exist
     */
    explicit VehicleSpecification(const std::string& fn, bool_t verbose = false);

    /**
     * @brief destrutor
     */
    ~VehicleSpecification() noexcept
    {
    }

    /**
     * @brief Get the Model object
     *
     * @return const std::string& vehicle model
     */
    const std::string& GetModel() const noexcept
    {
        return model_;
    }

    /**
     * @brief Get the Wheel Base object
     *
     * @return Scalar wheel base of vehicle in the unit of meters
     */
    Scalar GetWheelBase() const noexcept
    {
        return wheel_base_;
    }

    /**
     * @brief Get the Front Track Gauge object
     *
     * @return Scalar front track gauge of vehicle in the unit of meters
     */
    Scalar GetFrontTrackGauge() const noexcept
    {
        return front_track_gauge_;
    }

    /**
     * @brief Get the Rear Track Gauge object
     *
     * @return Scalar rear track gauge of vehicle in the unit of meters
     */
    Scalar GetRearTrackGauge() const noexcept
    {
        return rear_track_gauge_;
    }

    /**
     * @brief Get the Steering Ratio object
     *
     * @return Scalar steering ratio of vehicle in the unit of %
     */
    Scalar GetSteeringRatio() const noexcept
    {
        return steering_ratio_;
    }

    /**
     * @brief Get the Mass object
     *
     * @return Scalar mass of vehicle in the unit of kg
     */
    Scalar GetMass() const noexcept
    {
        return mass_;
    }

    /**
     * @brief Get the Mass Front Left Tire object
     *
     * @return Scalar mass of front left tire in kg
     */
    Scalar GetMassFrontLeftTire() const noexcept
    {
        return mass_front_left_tire_;
    }

    /**
     * @brief Get the Mass Front Right Tire object
     *
     * @return Scalar mass of front right tire in kg
     */
    Scalar GetMassFrontRightTire() const noexcept
    {
        return mass_front_right_tire_;
    }

    /**
     * @brief Get the Mass Rear Left Tire object
     *
     * @return Scalar mass of rear left tire in kg
     */
    Scalar GetMassRearLeftTire() const noexcept
    {
        return mass_rear_left_tire_;
    }

    /**
     * @brief Get the Mass Rear Right Tire object
     *
     * @return Scalar mass of rear right tire in kg
     */
    Scalar GetMassRearRightTire() const noexcept
    {
        return mass_rear_right_tire_;
    }

    /**
     * @brief Get the Front Wheel Stiffness object
     *
     * @return Scalar the front wheel lateral stiffness in N/rad
     */
    Scalar GetFrontWheelStiffness() const noexcept
    {
        return front_wheel_stiffness_;
    }

    /**
     * @brief Get the Rear Wheel Stiffness object
     *
     * @return Scalar the rear wheel lateral stiffness in N/rad
     */
    Scalar GetRearWheelStiffness() const noexcept
    {
        return rear_wheel_stiffness_;
    }

    /**
     * @brief Get the Max Wheel Angle object
     *
     * @return Scalar the maximum turning angle of front wheel in degree
     */
    Scalar GetMaxWheelAngle() const noexcept
    {
        return max_wheel_angle_;
    }

private:
    std::string model_;        /* vehicle model name */
    Scalar      wheel_base_;   /* the distance between the center of vehicle front wheel
                                   and the rear axis [meter] */
    Scalar front_track_gauge_; /* the distance between the front left wheel and the front right
                                  wheel [meter] */
    Scalar rear_track_gauge_;  /* the distance between the rear left wheel and the rear right
                                  wheel [meter] */
    Scalar steering_ratio_; /* steering angle divide by front wheel angle [%]. this parameter maybe variable in some car
                               model */
    Scalar mass_;           /* mass of vehicle */
    Scalar mass_front_left_tire_;  /* mass of front left tire [kg] */
    Scalar mass_front_right_tire_; /* mass of front right tire [kg] */
    Scalar mass_rear_left_tire_;   /* mass of rear left tire [kg] */
    Scalar mass_rear_right_tire_;  /* mass of rear right tire [kg] */
    Scalar front_wheel_stiffness_; /* the front wheel lateral stiffness [N/rad] */
    Scalar rear_wheel_stiffness_;  /* the rear wheel lateral stiffness [N/rad] */
    Scalar max_wheel_angle_;       /* the maximum turning angle of front wheel [degree] */

};  // class VehicleSpecification

/**
 * @}
 *
 */

}  // namespace holo

#endif  // HOLO_COMMON_VEHICLE_SPECIFICATION_H_
