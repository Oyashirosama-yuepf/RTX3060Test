#include <gtest/gtest.h>
#include <holo/sensors/common/device.h>
#include <holo/sensors/common/interface.h>
#include <holo/sensors/format/holocan.h>
#include <holo/sensors/format/rawbuf.h>
#include <holo/sensors/format/someip.h>
#include <thread>

using namespace holo::sensors::common;
using namespace holo::sensors::format;

TEST(InterfaceT, ConstructorHoloCanPacket)
{
    uint8_t data[28];
    (void)std::memcpy(&data[0], "##@!", 4);
    data[4] = 1;
    data[5] = 2;
    data[6] = 8;
    data[7] = 0;

    data[8]  = (0x456 >> 24) & 0xFF;
    data[9]  = (0x456 >> 16) & 0xFF;
    data[10] = (0x456 >> 8) & 0xFF;
    data[11] = (0x456 >> 0) & 0xFF;

    data[12] = 0;
    data[13] = 1;
    data[14] = 2;
    data[15] = 3;
    data[16] = 4;
    data[17] = 5;
    data[18] = 6;
    data[19] = 7;

    data[20] = (123456789 >> 24) & 0xFF;
    data[21] = (123456789 >> 16) & 0xFF;
    data[22] = (123456789 >> 8) & 0xFF;
    data[23] = (123456789 >> 0) & 0xFF;

    data[24]     = (987654321 >> 24) & 0xFF;
    data[25]     = (987654321 >> 16) & 0xFF;
    data[26]     = (987654321 >> 8) & 0xFF;
    data[27]     = (987654321 >> 0) & 0xFF;
    int32_t size = 28 - 1;

    InterfaceT<HoloCanPacket> driver;
    driver.InstallCallback(nullptr);
    bool r = driver.ParseData(data, size);
    ASSERT_TRUE(r);
}

static void callback0(const HoloCanPacket& input, HoloCanPacket& output)
{
    output = input;
}

TEST(DeviceDriver, ConstructorHoloCanPacket2)
{
    uint8_t data[28];
    (void)std::memcpy(&data[0], "##@!", 4);
    data[4] = 1;
    data[5] = 2;
    data[6] = 8;
    data[7] = 0;

    data[8]  = (0x456 >> 24) & 0xFF;
    data[9]  = (0x456 >> 16) & 0xFF;
    data[10] = (0x456 >> 8) & 0xFF;
    data[11] = (0x456 >> 0) & 0xFF;

    data[12] = 0;
    data[13] = 1;
    data[14] = 2;
    data[15] = 3;
    data[16] = 4;
    data[17] = 5;
    data[18] = 6;
    data[19] = 7;

    data[20] = (123456789 >> 24) & 0xFF;
    data[21] = (123456789 >> 16) & 0xFF;
    data[22] = (123456789 >> 8) & 0xFF;
    data[23] = (123456789 >> 0) & 0xFF;

    data[24]     = (987654321 >> 24) & 0xFF;
    data[25]     = (987654321 >> 16) & 0xFF;
    data[26]     = (987654321 >> 8) & 0xFF;
    data[27]     = (987654321 >> 0) & 0xFF;
    int32_t size = 28;

    InterfaceT<HoloCanPacket>                 driver;
    HoloCanPacket                             packet;
    std::function<void(const HoloCanPacket&)> h = std::bind(&callback0, std::placeholders::_1, std::ref(packet));
    driver.InstallCallback(h);
    bool r = driver.ParseData(data, size);
    ASSERT_TRUE(r);
    ASSERT_EQ(packet.GetSec(), 123456789);
    ASSERT_EQ(packet.GetNsec(), 987654321);
    ASSERT_EQ(packet.GetChannel(), 1);
    ASSERT_EQ(packet.GetSource(), 2);
    ASSERT_EQ(packet.GetId(), 0x456);
    ASSERT_EQ(packet.GetDlc(), 8);
    ASSERT_EQ(packet.GetData()[0], 0);
    ASSERT_EQ(packet.GetData()[1], 1);
    ASSERT_EQ(packet.GetData()[2], 2);
    ASSERT_EQ(packet.GetData()[3], 3);
    ASSERT_EQ(packet.GetData()[4], 4);
    ASSERT_EQ(packet.GetData()[5], 5);
    ASSERT_EQ(packet.GetData()[6], 6);
    ASSERT_EQ(packet.GetData()[7], 7);
}

TEST(DeviceDriver, ConstructorSomeIpPacket)
{
    const uint8_t                  data[24] = {0, 1, 0, 2, 0, 0, 0, 16, 0, 3, 0, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
    InterfaceT<SomeipPacket<1024>> driver;
    driver.InstallCallback((std::function<void(const SomeipPacket<1024>&)>)nullptr);
    bool r = driver.ParseData(data, sizeof(data) - 1);
    ASSERT_FALSE(r);
}

static void callback1(const SomeipPacket<1024>& input, SomeipPacket<1024>& output)
{
    uint32_t size = input.GetSerializedSize();
    uint8_t  data[size];
    input.Serialize(data, sizeof(data));
    output.Deserialize(data, sizeof(data));
}

TEST(DeviceDriver, ConstructorSomeIpPacket2)
{
    const uint8_t                  data[24] = {0, 1, 0, 2, 0, 0, 0, 16, 0, 3, 0, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
    InterfaceT<SomeipPacket<1024>> driver;
    SomeipPacket<1024>             packet;
    std::function<void(const SomeipPacket<1024>&)> h = std::bind(&callback1, std::placeholders::_1, std::ref(packet));
    driver.InstallCallback(h);
    bool r = driver.ParseData(data, sizeof(data));
    ASSERT_TRUE(r);
    ASSERT_EQ(packet.GetMsgId(), 0x00010002);
    ASSERT_EQ(packet.GetServiceId(), 1);
    ASSERT_EQ(packet.GetMethodId(), 2);
    ASSERT_EQ(packet.GetMsgLength(), 16);
    ASSERT_EQ(packet.GetReqId(), 0x00030004);
    ASSERT_EQ(packet.GetClientId(), 3);
    ASSERT_EQ(packet.GetSessionId(), 4);
    ASSERT_EQ(packet.GetProtoVerison(), 5);
    ASSERT_EQ(packet.GetIfVersion(), 6);
    ASSERT_EQ(packet.GetMsgType(), 7);
    ASSERT_EQ(packet.GetReturnCode(), 8);
    for (int k = 0; k < 8; k++)
    {
        uint8_t  byte;
        uint32_t get = packet.GetPayload(k, &byte, 1);
        ASSERT_EQ(get, 1);
        ASSERT_EQ(byte, k + 1);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
