/**
 * @brief unit test for LightSignalRequest
 * @author lijiawen(lijiawen@holomatic.com)
 * @date 2019-11-29
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <gtest/gtest.h>
#include <holo/common/light_signal_request.h>

namespace holo
{
using holo::common::Timestamp;

TEST(LightSignalRequest, Constructor)
{
    LightSignalRequest request;
    ASSERT_EQ(Timestamp(), request.GetTimestamp());

    ASSERT_EQ(0x0000, request.GetLightCommand());
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());

    const LightSignalRequest request2(request);
    ASSERT_EQ(Timestamp(), request2.GetTimestamp());

    ASSERT_EQ(0x0000, request2.GetLightCommand());
    ASSERT_FALSE(request2.GetLeftTurnSignal());
    ASSERT_FALSE(request2.GetRightTurnSignal());
    ASSERT_FALSE(request2.GetHazardFlasher());
    ASSERT_FALSE(request2.GetBrakeLight());

    LightSignalRequest request3 = request2;
    ASSERT_EQ(Timestamp(), request3.GetTimestamp());

    ASSERT_EQ(0x0000, request3.GetLightCommand());
    ASSERT_FALSE(request3.GetLeftTurnSignal());
    ASSERT_FALSE(request3.GetRightTurnSignal());
    ASSERT_FALSE(request3.GetHazardFlasher());
    ASSERT_FALSE(request3.GetBrakeLight());
}

TEST(LightSignalRequest, Timestamp)
{
    LightSignalRequest request;
    ASSERT_EQ(Timestamp(), request.GetTimestamp());

    request.SetTimestamp(Timestamp(1, 100));
    ASSERT_EQ(Timestamp(1, 100), request.GetTimestamp());

    request.GetTimestamp().SetSec(2);
    request.GetTimestamp().SetNsec(200);
    ASSERT_EQ(Timestamp(2, 200), request.GetTimestamp());
}

TEST(LightSignalRequest, LightCommand)
{
    LightSignalRequest request;
    ASSERT_EQ(0x0000, request.GetLightCommand());
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());

    request.SetLeftTurnSignal(true);
    ASSERT_EQ(0x0080, request.GetLightCommand());
    ASSERT_TRUE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());
    request.SetLightCommand(0x0080);
    ASSERT_TRUE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());

    request.SetLeftTurnSignal(false);
    request.SetRightTurnSignal(true);
    ASSERT_EQ(0x0040, request.GetLightCommand());
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_TRUE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());
    request.SetLightCommand(0x0040);
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_TRUE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());

    request.SetRightTurnSignal(false);
    request.SetHazardFlasher(true);
    ASSERT_EQ(0x0020, request.GetLightCommand());
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_TRUE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());
    request.SetLightCommand(0x0020);
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_TRUE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());

    request.SetHazardFlasher(false);
    request.SetBrakeLight(true);
    ASSERT_EQ(0x0004, request.GetLightCommand());
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_TRUE(request.GetBrakeLight());
    request.SetLightCommand(0x0004);
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_TRUE(request.GetBrakeLight());

    request.SetBrakeLight(false);
    ASSERT_EQ(0x0000, request.GetLightCommand());
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());
    request.SetLightCommand(0x0000);
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());

    request.SetLightCommand(0x00e4);
    ASSERT_TRUE(request.GetLeftTurnSignal());
    ASSERT_TRUE(request.GetRightTurnSignal());
    ASSERT_TRUE(request.GetHazardFlasher());
    ASSERT_TRUE(request.GetBrakeLight());

    request.SetLightCommand(0x0000);
    ASSERT_FALSE(request.GetLeftTurnSignal());
    ASSERT_FALSE(request.GetRightTurnSignal());
    ASSERT_FALSE(request.GetHazardFlasher());
    ASSERT_FALSE(request.GetBrakeLight());
}

TEST(LightSignalRequest, GetSerializedSize)
{
    LightSignalRequest light;    
    ASSERT_EQ(16, light.GetSerializedSize<4U>());
    ASSERT_EQ(16, light.GetSerializedSize<8U>());
}

TEST(LightSignalRequest, SerializeAndDeserialize)
{
    LightSignalRequest input, output;

    holo::Timestamp timestamp(1234, 5678);
    input.SetTimestamp(timestamp);
    input.SetLightCommand(0xABCD);

    uint8_t buffer[128];
    holo::serialization::Serializer<>          serializer(buffer, 128);
    serializer << input;
    ASSERT_EQ(input.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> output;

    ASSERT_EQ(input.GetTimestamp(), output.GetTimestamp());
    ASSERT_EQ(input.GetLightCommand(), output.GetLightCommand());}

} /* namespace holo */

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
