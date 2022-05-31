#include <gtest/gtest.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/holocan.h>

using namespace holo::sensors::format;

TEST(HoloCanTest, Deserialize)
{
    uint8_t raw_data[28];
    (void)std::memset(&raw_data[0], 0, 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0x456 >> 24) & 0xFF;
    raw_data[9]  = (0x456 >> 16) & 0xFF;
    raw_data[10] = (0x456 >> 8) & 0xFF;
    raw_data[11] = (0x456 >> 0) & 0xFF;

    raw_data[12] = 0;
    raw_data[13] = 1;
    raw_data[14] = 2;
    raw_data[15] = 3;
    raw_data[16] = 4;
    raw_data[17] = 5;
    raw_data[18] = 6;
    raw_data[19] = 7;

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    ASSERT_EQ(packet.GetSerializedSize(), 28);
    uint32_t des_size = packet.Deserialize(raw_data, sizeof(raw_data) - 1);
    ASSERT_TRUE(des_size == 0);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size == 0);
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    ASSERT_TRUE(packet.IsValid());
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

TEST(HoloCanTest, Serialize1)
{
    uint8_t raw_data[28];
    (void)std::memset(&raw_data[0], 0, 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0x456 >> 24) & 0xFF;
    raw_data[9]  = (0x456 >> 16) & 0xFF;
    raw_data[10] = (0x456 >> 8) & 0xFF;
    raw_data[11] = (0x456 >> 0) & 0xFF;

    raw_data[12] = 0;
    raw_data[13] = 1;
    raw_data[14] = 2;
    raw_data[15] = 3;
    raw_data[16] = 4;
    raw_data[17] = 5;
    raw_data[18] = 6;
    raw_data[19] = 7;

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    uint32_t des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    uint8_t  ser_data[28];
    uint32_t ser_size = packet.Serialize(ser_data, sizeof(ser_data) - 1);
    ASSERT_EQ(ser_size, 0);
}

TEST(HoloCanTest, Serialize2)
{
    uint8_t raw_data[28];
    (void)std::memset(&raw_data[0], 0, 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0x456 >> 24) & 0xFF;
    raw_data[9]  = (0x456 >> 16) & 0xFF;
    raw_data[10] = (0x456 >> 8) & 0xFF;
    raw_data[11] = (0x456 >> 0) & 0xFF;

    raw_data[12] = 0;
    raw_data[13] = 1;
    raw_data[14] = 2;
    raw_data[15] = 3;
    raw_data[16] = 4;
    raw_data[17] = 5;
    raw_data[18] = 6;
    raw_data[19] = 7;

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    uint32_t des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    uint8_t  ser_data[28];
    uint32_t ser_size = packet.Serialize(ser_data, sizeof(ser_data));
    ASSERT_EQ(ser_size, sizeof(ser_data));
    for (uint32_t i = 0; i < sizeof(ser_data); i++)
    {
        ASSERT_EQ(ser_data[i], raw_data[i]);
    }
}

TEST(HoloCanTest, Serialize3)
{
    uint8_t raw_data[84];
    (void)std::memset(&raw_data[0], 0, 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 64;
    raw_data[7] = 0;

    raw_data[8]  = (0x456 >> 24) & 0xFF;
    raw_data[9]  = (0x456 >> 16) & 0xFF;
    raw_data[10] = (0x456 >> 8) & 0xFF;
    raw_data[11] = (0x456 >> 0) & 0xFF;

    for (int i = 0; i < 64; ++i)
    {
        raw_data[i + 12] = i;
    }

    raw_data[76] = (123456789 >> 24) & 0xFF;
    raw_data[77] = (123456789 >> 16) & 0xFF;
    raw_data[78] = (123456789 >> 8) & 0xFF;
    raw_data[79] = (123456789 >> 0) & 0xFF;

    raw_data[80] = (987654321 >> 24) & 0xFF;
    raw_data[81] = (987654321 >> 16) & 0xFF;
    raw_data[82] = (987654321 >> 8) & 0xFF;
    raw_data[83] = (987654321 >> 0) & 0xFF;

    HoloCanfdPacket packet;
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    uint32_t des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_TRUE(des_size > 0);
    ASSERT_EQ(packet.GetDlc(), 64);
    for (int i = 0; i < 64; ++i)
    {
        ASSERT_EQ(packet.GetData()[i], i);
    }
    uint8_t  ser_data[84];
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
