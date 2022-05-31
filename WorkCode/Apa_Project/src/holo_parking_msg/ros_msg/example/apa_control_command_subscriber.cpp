/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file apa_control_command_subscriber.cpp
 * @brief an example to subscribe a ApaControlCommand message through ROS
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-01-11
 */

#include <holo_parking_msg/ros_msg/control/apa_control_command_traits.h>
#include <ros_wrapper/ros_bus.h>

using BusType = ros_wrapper::RosBus;

void CommandCallback(holo::parking::control::ApaControlCommand const& value)
{
    std::cout << value.GetTargetGearRequest() << std::endl;
}

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "apa_control_command_subscriber");
    BusType bus(0, "Data");

    auto reader = bus.AddReader<holo::parking::control::ApaControlCommand,
                                BusType::DefaultConversionTraitsType<holo::parking::control::ApaControlCommand> >(
        "apa_control_command");
    reader.SetOnDataAvailableCallback(CommandCallback);

    BusType::AsyncSpin(1);
    while (BusType::IsRunning())
    {
        sleep(1);
    }
    return 0;
}
