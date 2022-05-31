/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file vehicle_pose_2d_subscriber.cpp
 * @brief an example to publish a VehiclePose2Df message through ROS
 * @author lifeng(lifeng@holomaitc.com)
 * @date 2021-01-08
 */

#include <holo_parking_msg/ros_msg/localization/vehicle_pose_2d_traits.h>
#include <ros_wrapper/ros_bus.h>

using BusType     = ros_wrapper::RosBus;
using Vector3Type = holo::parking::localization::VehiclePose2Df::Vector3Type;

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "vehicle_pose_2d_publisher");
    BusType bus(0, "Data");
    auto    writer = bus.AddWriter<holo::parking::localization::VehiclePose2Df,
                                BusType::DefaultConversionTraitsType<holo::parking::localization::VehiclePose2Df> >(
        "vehicle_pose_2d");

    while (BusType::IsRunning())
    {
        holo::parking::localization::VehiclePose2Df vehicle_pose_2d;
        vehicle_pose_2d.SetCurve(0);
        vehicle_pose_2d.SetVehicleStatus(holo::parking::localization::VehiclePose2Df::VehicleStatus::HIGH_PRECISION);
        vehicle_pose_2d.SetPose(Vector3Type(1, 2, 3));
        vehicle_pose_2d.SetPredictedPose(Vector3Type(1, 2, 3));

        writer.Write(vehicle_pose_2d);
        sleep(1);
    }
    return 0;
}
