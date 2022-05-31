#include <holo/log/hololog.h>
#include <gtest/gtest.h>
#include <holo/sensors/format/rawbuf.h>

using namespace holo::sensors::format;

TEST(RawbufferTest, DeserializeOverflow)
{
    uint8_t data[256];
    for (uint32_t i = 0; i < sizeof(data); ++i)
    {
        data[i] = i;
    }

    Rawbuffer<256> buffer;
    buffer.Deserialize(data, sizeof(data) + 1);
    ASSERT_EQ(buffer.size(), 0);
}

TEST(RawbufferTest, DeserializeSuccess)
{
    uint8_t data[256];
    for (uint32_t i = 0; i < sizeof(data); ++i)
    {
        data[i] = i;
    }

    Rawbuffer<256> buffer;
    buffer.Deserialize(data, sizeof(data));
    ASSERT_EQ(buffer.size(), 256);
    for (uint32_t i = 0; i < sizeof(data); ++i)
    {
        ASSERT_EQ(buffer.data()[i], i);
    }
    for (uint32_t i = 0; i < sizeof(data); ++i)
    {
        ASSERT_EQ(buffer[i], i);
    }
    EXPECT_ANY_THROW(buffer.at(256));
}

TEST(RawbufferTest, Serialize)
{
    uint8_t data[256];
    for (uint32_t i = 0; i < sizeof(data); ++i)
    {
        data[i] = i;
    }

    Rawbuffer<256> buffer;
    uint32_t       des_size = buffer.Deserialize(data, sizeof(data));
    ASSERT_TRUE(des_size > 0);
    ASSERT_EQ(buffer.size(), 256);
    uint8_t  ser_data[256];
    uint32_t ser_size = buffer.Serialize(ser_data, sizeof(ser_data) - 1);
    ASSERT_EQ(ser_size, 0);
    ser_size = buffer.Serialize(ser_data, sizeof(ser_data));
    ASSERT_EQ(ser_size, 256);
}

TEST(RawbufferTest, GetSerializedSize)
{
    uint8_t data[128];
    (void)std::memset(data, 0, sizeof(data));
    Rawbuffer<256> buffer;
    uint32_t       des_size = buffer.Deserialize(data, sizeof(data));
    ASSERT_TRUE(des_size > 0);
    ASSERT_EQ(buffer.size(), 128);
    ASSERT_EQ(buffer.GetSerializedSize(), 128);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
