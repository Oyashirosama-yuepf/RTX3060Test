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

using BusType = ros_wrapper::RosBus;

void VehiclePose2DCallback(holo::parking::localization::VehiclePose2Df const& value)
{
    std::cout << "VehiclePose2Df sample received" << std::endl;
    std::cout << "curve: " << value.GetCurve() << std::endl;
    std::cout << "pose: " << value.GetPose().Transpose() << std::endl;
    std::cout << "predictd pose: " << value.GetPredictedPose().Transpose() << std::endl;
    std::cout << "status: " << static_cast<uint8_t>(value.GetStatus()) << std::endl << std::endl;
}

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "vehicle_pose_subscriber");
    BusType bus(0, "Data");

    auto reader = bus.AddReader<holo::parking::localization::VehiclePose2Df,
                                BusType::DefaultConversionTraitsType<holo::parking::localization::VehiclePose2Df> >(
        "vehicle_pose_2d");
    reader.SetOnDataAvailableCallback(VehiclePose2DCallback);

    BusType::AsyncSpin(1);
    while (BusType::IsRunning())
    {
        sleep(1);
    }
    return 0;
}
