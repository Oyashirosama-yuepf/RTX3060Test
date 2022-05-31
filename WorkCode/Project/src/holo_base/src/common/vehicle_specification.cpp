/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_specification.cpp
 * @brief the implementation of vehicle parameters.
 * @author lichao@holomatic.com
 * @date Sep 26, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */
#include <iostream>

#include <holo/common/vehicle_specification.h>
#include <holo/core/exception.h>
#include <holo/utils/holo_root.h>
#include <holo/utils/yaml.h>

namespace holo
{
/*****************************************************************************/
VehicleSpecification::VehicleSpecification(const std::string& fn, bool_t verbose)
{
    /*
     * @todo (lichao@holoamtic.com) depend on system related interface
    if (!boost::filesystem::is_regular_file(fn))
    {
        throw std::runtime_error(fn + " does not exist");
    }
    */

    yaml::Node node        = yaml::LoadFile(fn);
    model_                 = node["model"].as<std::string>();
    wheel_base_            = node["wheel_base"].as<Scalar>();
    front_track_gauge_     = node["front_track_gauge"].as<Scalar>();
    rear_track_gauge_      = node["rear_track_gauge"].as<Scalar>();
    steering_ratio_        = node["steering_ratio"].as<Scalar>();
    mass_                  = node["mass"].as<Scalar>();
    mass_front_left_tire_  = node["mass_front_left_tire"].as<Scalar>();
    mass_front_right_tire_ = node["mass_front_right_tire"].as<Scalar>();
    mass_rear_left_tire_   = node["mass_rear_left_tire"].as<Scalar>();
    mass_rear_right_tire_  = node["mass_rear_right_tire"].as<Scalar>();
    front_wheel_stiffness_ = node["front_wheel_stiffness"].as<Scalar>();
    rear_wheel_stiffness_  = node["rear_wheel_stiffness"].as<Scalar>();
    max_wheel_angle_       = node["max_wheel_angle"].as<Scalar>();

    (void)verbose;
    std::cout << "car model: " << model_ << "\twheel base: " << wheel_base_
              << "\tfront_track gauge: " << front_track_gauge_ << "\trear_track gauge: " << rear_track_gauge_
              << "\tsteering_ratio: " << steering_ratio_ << "\tmass: " << mass_ << std::endl;
    std::cout << "mass front left tire: " << mass_front_left_tire_
              << "\tmass front right tire: " << mass_front_right_tire_
              << "\tmass rear left tire: " << mass_rear_left_tire_
              << "\tmass rear right tire: " << mass_rear_right_tire_ << std::endl;
    std::cout << "front wheel stiffness: " << front_wheel_stiffness_
              << "\trear wheel stiffness: " << rear_wheel_stiffness_ << "\tmax wheel angle: " << max_wheel_angle_
              << std::endl;
    std::cout << "Loaded vehicle specification from " << fn << std::endl;
}

/*****************************************************************************/
}  // namespace holo
