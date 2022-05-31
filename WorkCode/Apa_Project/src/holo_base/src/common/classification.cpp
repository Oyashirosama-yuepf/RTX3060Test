/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file classification.cpp
 * @brief This src file implements Classification.
 * @author lisongze(lisongze@holomaitc.com)
 * @date 2019-09-04
 */

#include <holo/common/classification.h>

namespace holo
{
namespace common 
{
const std::array<std::pair<Classification::MainType, std::string>, Classification::kClassificationMainTypeNum>
    Classification::kMainTypeStringArray = {
        std::make_pair(Classification::MainType::UNKNOWN, std::string("UNKNOWN")),
        std::make_pair(Classification::MainType::PEDESTRIAN, std::string("PEDESTRIAN")),
        std::make_pair(Classification::MainType::VEHICLE, std::string("VEHICLE")),
        std::make_pair(Classification::MainType::BIKE, std::string("BIKE")),
        std::make_pair(Classification::MainType::TRAFFIC_SIGN, std::string("TRAFFIC_SIGN")),
        std::make_pair(Classification::MainType::ANIMAL, std::string("ANIMAL")),
        std::make_pair(Classification::MainType::SPEED_HUMP, std::string("SPEED_HUMP"))
};

const std::array<std::pair<Classification::SubType, std::string>, Classification::kClassificationSubTypeNum>
    Classification::kSubTypeStringArray = {
        std::make_pair(Classification::SubType::UNKNOWN, std::string("UNKNOWN")),
        std::make_pair(Classification::SubType::UNKNOWN_MOVABLE, std::string("UNKNOWN_MOVABLE")),
        std::make_pair(Classification::SubType::UNKNOWN_UNMOVABLE, std::string("UNKNOWN_UNMOVABLE")),

        std::make_pair(Classification::SubType::PEDESTRIAN, std::string("PEDESTRIAN")),

        std::make_pair(Classification::SubType::CAR, std::string("CAR")),
        std::make_pair(Classification::SubType::TRUCK, std::string("TRUCK")),
        std::make_pair(Classification::SubType::VAN, std::string("VAN")),
        std::make_pair(Classification::SubType::BUS, std::string("BUS")),

        std::make_pair(Classification::SubType::BICYCLE, std::string("BICYCLE")),
        std::make_pair(Classification::SubType::TRICYCLE, std::string("TRICYCLE")),
        std::make_pair(Classification::SubType::MOTOBIKE, std::string("MOTOBIKE")),
        
        std::make_pair(Classification::SubType::TRAFFIC_LED_BOARD, std::string("TRAFFIC_LED_BOARD")),
        std::make_pair(Classification::SubType::TRAFFIC_SIGN_BOARD, std::string("TRAFFIC_SIGN_BOARD")),
        std::make_pair(Classification::SubType::TRAFFIC_CONE, std::string("TRAFFIC_CONE")),
        std::make_pair(Classification::SubType::TRAFFIC_POLE, std::string("TRAFFIC_POLE")),
        std::make_pair(Classification::SubType::TRAFFIC_LANE, std::string("TRAFFIC_LANE")),
        std::make_pair(Classification::SubType::TRAFFIC_CURB, std::string("TRAFFIC_CURB")),
        std::make_pair(Classification::SubType::TRAFFIC_LIGHT, std::string("TRAFFIC_LIGHT")),
        std::make_pair(Classification::SubType::TRAFFIC_CROSSING, std::string("TRAFFIC_CROSSING")),
        std::make_pair(Classification::SubType::TRAFFIC_MARKER, std::string("TRAFFIC_MARKER")),
        std::make_pair(Classification::SubType::WATER_HORSE, std::string("WATER_HORSE")),
        std::make_pair(Classification::SubType::COLLISION_SPHERE, std::string("COLLISION_SPHERE")),
        std::make_pair(Classification::SubType::COLLISION_POST, std::string("COLLISION_POST")),
        std::make_pair(Classification::SubType::COLLISION_BAR, std::string("COLLISION_BAR")),
        std::make_pair(Classification::SubType::GROUND_LOCK, std::string("GROUND_LOCK")),
        std::make_pair(Classification::SubType::AUTO_GATE, std::string("AUTO_GATE")),
        std::make_pair(Classification::SubType::NO_PARKING, std::string("NO_PARKING")),
        std::make_pair(Classification::SubType::SPEED_HUMP, std::string("SPEED_HUMP")),

        std::make_pair(Classification::SubType::ANIMAL_DOG, std::string("ANIMAL_DOG")),
        std::make_pair(Classification::SubType::ANIMAL_CAT, std::string("ANIMAL_CAT")),
        std::make_pair(Classification::SubType::ANIMAL_COW, std::string("ANIMAL_COW")),
        std::make_pair(Classification::SubType::ANIMAL_SHEEP, std::string("ANIMAL_SHEEP"))
};
}  // namespace common
}  // namespace holo
