/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file apa_control_command_publisher.cpp
 * @brief an example to publish a ApaControlCommand message through ROS
 * @author zhangchun(zhangchun@holomaitc.com)
 * @date 2021-01-11
 */

#include <holo_parking_msg/ros_msg/control/apa_control_command_traits.h>
#include <ros_wrapper/ros_bus.h>

using BusType = ros_wrapper::RosBus;

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "apa_control_command_publisher");
    BusType bus(0, "Data");
    auto    writer = bus.AddWriter<holo::parking::control::ApaControlCommand,
                                BusType::DefaultConversionTraitsType<holo::parking::control::ApaControlCommand> >(
        "apa_control_command");

    uint8_t i = 0;
    while (BusType::IsRunning())
    {
        holo::parking::control::ApaControlCommand command;
        command.SetTargetGearRequest(i);
        writer.Write(command);
        sleep(1);
        ++i;
    }
    return 0;
}
