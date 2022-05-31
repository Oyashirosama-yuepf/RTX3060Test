#include <holo/log/hololog.h>
#include <gtest/gtest.h>
#include <holo/sensors/format/holosync.h>

using namespace holo::sensors::format;

TEST(HoloSyncTest, Deserialize)
{
    uint8_t raw_data[12];
    raw_data[0] = (123456789 >> 24) & 0xFF;
    raw_data[1] = (123456789 >> 16) & 0xFF;
    raw_data[2] = (123456789 >> 8) & 0xFF;
    raw_data[3] = (123456789 >> 0) & 0xFF;

    raw_data[4] = (987654321 >> 24) & 0xFF;
    raw_data[5] = (987654321 >> 16) & 0xFF;
    raw_data[6] = (987654321 >> 8) & 0xFF;
    raw_data[7] = (987654321 >> 0) & 0xFF;

    raw_data[8]  = (0x12345678 >> 24) & 0xFF;
    raw_data[9]  = (0x12345678 >> 16) & 0xFF;
    raw_data[10] = (0x12345678 >> 8) & 0xFF;
    raw_data[11] = (0x12345678 >> 0) & 0xFF;

    HoloSyncPacket packet;
    ASSERT_EQ(packet.GetSerializedSize(), 12);
    uint32_t des_size = packet.Deserialize(raw_data, sizeof(raw_data) - 1);
    ASSERT_TRUE(des_size == 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    ASSERT_EQ(packet.GetSec(), 123456789);
    ASSERT_EQ(packet.GetNsec(), 987654321);
    ASSERT_EQ(packet.GetCounter(), 0x12345678);
}

TEST(HoloSyncTest, Serialize1)
{
    uint8_t raw_data[12];
    raw_data[0] = (123456789 >> 24) & 0xFF;
    raw_data[1] = (123456789 >> 16) & 0xFF;
    raw_data[2] = (123456789 >> 8) & 0xFF;
    raw_data[3] = (123456789 >> 0) & 0xFF;

    raw_data[4] = (987654321 >> 24) & 0xFF;
    raw_data[5] = (987654321 >> 16) & 0xFF;
    raw_data[6] = (987654321 >> 8) & 0xFF;
    raw_data[7] = (987654321 >> 0) & 0xFF;

    raw_data[8]  = (0x12345678 >> 24) & 0xFF;
    raw_data[9]  = (0x12345678 >> 16) & 0xFF;
    raw_data[10] = (0x12345678 >> 8) & 0xFF;
    raw_data[11] = (0x12345678 >> 0) & 0xFF;

    HoloSyncPacket packet;
    uint32_t       des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    uint8_t  ser_data[12];
    uint32_t ser_size = packet.Serialize(ser_data, sizeof(ser_data) - 1);
    ASSERT_EQ(ser_size, 0);
}

TEST(HoloSyncTest, Serialize2)
{
    uint8_t raw_data[12];
    raw_data[0] = (123456789 >> 24) & 0xFF;
    raw_data[1] = (123456789 >> 16) & 0xFF;
    raw_data[2] = (123456789 >> 8) & 0xFF;
    raw_data[3] = (123456789 >> 0) & 0xFF;

    raw_data[4] = (987654321 >> 24) & 0xFF;
    raw_data[5] = (987654321 >> 16) & 0xFF;
    raw_data[6] = (987654321 >> 8) & 0xFF;
    raw_data[7] = (987654321 >> 0) & 0xFF;

    raw_data[8]  = (0x12345678 >> 24) & 0xFF;
    raw_data[9]  = (0x12345678 >> 16) & 0xFF;
    raw_data[10] = (0x12345678 >> 8) & 0xFF;
    raw_data[11] = (0x12345678 >> 0) & 0xFF;

    HoloSyncPacket packet;
    uint32_t       des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    uint8_t  ser_data[12];
    uint32_t ser_size = packet.Serialize(ser_data, sizeof(ser_data));
    ASSERT_EQ(ser_size, sizeof(ser_data));
    for (uint32_t i = 0; i < sizeof(ser_data); i++)
    {
        ASSERT_EQ(ser_data[i], raw_data[i]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
