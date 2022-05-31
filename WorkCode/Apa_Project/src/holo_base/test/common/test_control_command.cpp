/**
 * @brief unit test for ControlCommand
 * @author zhangjiannan@holomatic.com
 * @date 2019.11.2
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/common/control_command.h>

using holo::common::ChassisState;
using holo::common::ControlCommand;
using holo::common::Timestamp;

TEST(ControlCommand, Constructor)
{
    ControlCommand cmd;
    ASSERT_EQ(Timestamp(), cmd.GetTimestamp());
    ASSERT_EQ(ControlCommand::LateralControlModel::DISABLE, cmd.GetLateralControlModel());
    ASSERT_EQ(ControlCommand::LongitudinalControlModel::DISABLE, cmd.GetLongitudinalControlModel());

    ASSERT_EQ(ControlCommand::GearControlModel::DISABLE, cmd.GetGearControlModel());
    ASSERT_EQ(cmd.GetLateralControlValue(), 0.0f);
    ASSERT_EQ(cmd.GetLongitudinalControlValue1(), 0.0f);
    ASSERT_EQ(cmd.GetLongitudinalControlValue2(), 0.0f);
    ASSERT_EQ(0x00, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::UNKNOWN, cmd.GetGearPosition());
    ASSERT_EQ(0, cmd.GetGearLevel());
    ASSERT_FALSE(cmd.GetHandbrake());
}

TEST(ControlCommand, GetAndSetTimestamp)
{
    ControlCommand cmd;
    ASSERT_EQ(Timestamp(), cmd.GetTimestamp());

    cmd.SetTimestamp(Timestamp(1, 100));
    ASSERT_EQ(Timestamp(1, 100), cmd.GetTimestamp());
}

TEST(ControlCommand, GetAndSetLateralControlModel)
{
    ControlCommand cmd;
    cmd.SetLateralControlModel(ControlCommand::LateralControlModel::FRONT_WHEEL_ANGLE);
    ASSERT_EQ(ControlCommand::LateralControlModel::FRONT_WHEEL_ANGLE, cmd.GetLateralControlModel());
}

TEST(ControlCommand, GetAndSetLongitudinalControlModel)
{
    ControlCommand cmd;
    cmd.SetLongitudinalControlModel(ControlCommand::LongitudinalControlModel::TORQUE);
    ASSERT_EQ(ControlCommand::LongitudinalControlModel::TORQUE, cmd.GetLongitudinalControlModel());
}

TEST(ControlCommand, GetAndSetGearControlModel)
{
    ControlCommand cmd;
    cmd.SetGearControlModel(ControlCommand::GearControlModel::GEAR_CONTROL);
    ASSERT_EQ(ControlCommand::GearControlModel::GEAR_CONTROL, cmd.GetGearControlModel());
}

TEST(ControlCommand, GetAndSetLateralControlValue)
{
    ControlCommand cmd;
    cmd.SetLateralControlValue(5.5f);
    ASSERT_EQ(5.5f, cmd.GetLateralControlValue());
}

TEST(ControlCommand, GetAndSetLateralTorque)
{
    ControlCommand cmd;
    cmd.SetLateralTorque(15.5f);
    ASSERT_EQ(15.5f, cmd.GetLateralTorque());
}

TEST(ControlCommand, GetAndSetLateralFrontWheelAngle)
{
    ControlCommand cmd;
    cmd.SetLateralFrontWheelAngle(16.5f);
    ASSERT_EQ(16.5f, cmd.GetLateralFrontWheelAngle());
}

TEST(ControlCommand, GetAndSetLateralSteeringAngle)
{
    ControlCommand cmd;
    cmd.SetLateralSteeringAngle(17.5f);
    ASSERT_EQ(17.5f, cmd.GetLateralSteeringAngle());
}

TEST(ControlCommand, GetAndSetLongitudinalControlValue1)
{
    ControlCommand cmd;
    cmd.SetLongitudinalControlValue1(6.5f);
    ASSERT_EQ(6.5f, cmd.GetLongitudinalControlValue1());
}

TEST(ControlCommand, GetAndSetLongitudinalControlValue2)
{
    ControlCommand cmd;
    cmd.SetLongitudinalControlValue2(7.5f);
    ASSERT_EQ(7.5f, cmd.GetLongitudinalControlValue2());
}

TEST(ControlCommand, GetAndSetLongitudinalAcceleration)
{
    ControlCommand cmd;
    cmd.SetLongitudinalAcceleration(17.5f);
    ASSERT_EQ(17.5f, cmd.GetLongitudinalAcceleration());
}

TEST(ControlCommand, GetAndSetLongitudinalDeceleration)
{
    ControlCommand cmd;
    cmd.SetLongitudinalDeceleration(18.5f);
    ASSERT_EQ(18.5f, cmd.GetLongitudinalDeceleration());
}

TEST(ControlCommand, GetAndSetLongitudinalTorque)
{
    ControlCommand cmd;
    cmd.SetLongitudinalTorqueDeceleration(20.5f);
    ASSERT_EQ(20.5f, cmd.GetLongitudinalTorqueDeceleration());
}

TEST(ControlCommand, GetAndSetLongitudinalTorqueDeceleration)
{
    ControlCommand cmd;
    cmd.SetLongitudinalTorqueDeceleration(20.5f);
    ASSERT_EQ(20.5f, cmd.GetLongitudinalTorqueDeceleration());
}

TEST(ControlCommand, GetAndSetLongitudinalSpeedLimit)
{
    ControlCommand cmd;
    cmd.SetLongitudinalSpeedLimit(21.5f);
    ASSERT_EQ(21.5f, cmd.GetLongitudinalSpeedLimit());
}

TEST(ControlCommand, GetAndSetLongitudinalStopDistance)
{
    ControlCommand cmd;
    cmd.SetLongitudinalStopDistance(22.5f);
    ASSERT_EQ(22.5f, cmd.GetLongitudinalStopDistance());
}

TEST(ControlCommand, GetAndSetGearCommand)
{
    ControlCommand cmd;
    ASSERT_EQ(0x00, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::UNKNOWN, cmd.GetGearPosition());
    ASSERT_EQ(0, cmd.GetGearLevel());
    ASSERT_FALSE(cmd.GetHandbrake());

    cmd.SetGearPosition(ChassisState::GearPosition::P);
    ASSERT_EQ(0x20, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::P, cmd.GetGearPosition());
    cmd.SetGearCommand(0x20);
    ASSERT_EQ(ChassisState::GearPosition::P, cmd.GetGearPosition());

    cmd.SetGearPosition(ChassisState::GearPosition::R);
    ASSERT_EQ(0x40, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::R, cmd.GetGearPosition());
    cmd.SetGearCommand(0x40);
    ASSERT_EQ(ChassisState::GearPosition::R, cmd.GetGearPosition());

    cmd.SetGearPosition(ChassisState::GearPosition::N);
    ASSERT_EQ(0x60, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::N, cmd.GetGearPosition());
    cmd.SetGearCommand(0x60);
    ASSERT_EQ(ChassisState::GearPosition::N, cmd.GetGearPosition());

    cmd.SetGearPosition(ChassisState::GearPosition::D);
    ASSERT_EQ(0x80, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::D, cmd.GetGearPosition());
    cmd.SetGearCommand(0x80);
    ASSERT_EQ(ChassisState::GearPosition::D, cmd.GetGearPosition());

    cmd.SetGearPosition(ChassisState::GearPosition::S);
    ASSERT_EQ(0xa0, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::S, cmd.GetGearPosition());
    cmd.SetGearCommand(0xa0);
    ASSERT_EQ(ChassisState::GearPosition::S, cmd.GetGearPosition());

    cmd.SetGearPosition(ChassisState::GearPosition::UNKNOWN);
    ASSERT_EQ(0x00, cmd.GetGearCommand());
    ASSERT_EQ(ChassisState::GearPosition::UNKNOWN, cmd.GetGearPosition());
    cmd.SetGearCommand(0x00);
    ASSERT_EQ(ChassisState::GearPosition::UNKNOWN, cmd.GetGearPosition());

    cmd.SetGearLevel(1);
    ASSERT_EQ(0x02, cmd.GetGearCommand());
    ASSERT_EQ(1, cmd.GetGearLevel());
    cmd.SetGearCommand(0x02);
    ASSERT_EQ(1, cmd.GetGearLevel());

    cmd.SetGearLevel(15);
    ASSERT_EQ(0x1e, cmd.GetGearCommand());
    ASSERT_EQ(15, cmd.GetGearLevel());
    cmd.SetGearCommand(0x1e);
    ASSERT_EQ(15, cmd.GetGearLevel());

    cmd.SetGearLevel(16);
    ASSERT_EQ(0x1e, cmd.GetGearCommand());
    ASSERT_EQ(15, cmd.GetGearLevel());

    cmd.SetGearLevel(255);
    ASSERT_EQ(0x1e, cmd.GetGearCommand());
    ASSERT_EQ(15, cmd.GetGearLevel());

    cmd.SetGearLevel(0);
    ASSERT_EQ(0x00, cmd.GetGearCommand());
    ASSERT_EQ(0, cmd.GetGearLevel());
    cmd.SetGearCommand(0x00);
    ASSERT_EQ(0, cmd.GetGearLevel());

    cmd.SetHandbrake(true);
    ASSERT_EQ(0x01, cmd.GetGearCommand());
    ASSERT_TRUE(cmd.GetHandbrake());
    cmd.SetGearCommand(0x01);
    ASSERT_TRUE(cmd.GetHandbrake());

    cmd.SetHandbrake(false);
    ASSERT_EQ(0x00, cmd.GetGearCommand());
    ASSERT_FALSE(cmd.GetHandbrake());
    cmd.SetGearCommand(0x00);
    ASSERT_FALSE(cmd.GetHandbrake());
}

TEST(ControlCommand, GetSerializedSize)
{
    ControlCommand control_command;
    ASSERT_EQ(24, control_command.GetSerializedSize<4U>());
    ASSERT_EQ(24, control_command.GetSerializedSize<8U>());
}

TEST(ControlCommand, SerializeAndDeserialize)
{
    ControlCommand input_control_command, output_control_command;
    srand(time(0));
    input_control_command.SetTimestamp(holo::common::Timestamp(3, 500));
    input_control_command.SetLateralControlModel(ControlCommand::LateralControlModel::TORQUE);
    input_control_command.SetLongitudinalControlModel(ControlCommand::LongitudinalControlModel::DECELERATE);
    input_control_command.SetGearControlModel(ControlCommand::GearControlModel::GEAR_CONTROL);
    input_control_command.SetLateralControlValue(1.1f);
    input_control_command.SetLongitudinalControlValue1(2.1f);
    input_control_command.SetLongitudinalControlValue2(3.1f);
    input_control_command.SetGearCommand((holo::uint8_t)(rand() % 65536));

    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << input_control_command;
    ASSERT_EQ(input_control_command.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output_control_command;

    ASSERT_EQ(input_control_command.GetTimestamp(), output_control_command.GetTimestamp());
    ASSERT_EQ(input_control_command.GetLateralControlModel(), output_control_command.GetLateralControlModel());
    ASSERT_EQ(input_control_command.GetLongitudinalControlModel(),
              output_control_command.GetLongitudinalControlModel());
    ASSERT_EQ(input_control_command.GetGearControlModel(), output_control_command.GetGearControlModel());
    ASSERT_EQ(input_control_command.GetLateralControlValue(), output_control_command.GetLateralControlValue());
    ASSERT_EQ(input_control_command.GetLongitudinalControlValue1(),
              output_control_command.GetLongitudinalControlValue1());
    ASSERT_EQ(input_control_command.GetLongitudinalControlValue2(),
              output_control_command.GetLongitudinalControlValue2());
    ASSERT_EQ(input_control_command.GetGearCommand(), output_control_command.GetGearCommand());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
