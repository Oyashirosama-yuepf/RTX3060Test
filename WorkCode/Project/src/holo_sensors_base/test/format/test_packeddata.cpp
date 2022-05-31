#include <gtest/gtest.h>
#include <holo/log/hololog.h>
#include <holo/sensors/format/packed_data.h>
#include <holo/sensors/utils/sensors_utils.h>

using namespace holo::sensors::format;
using namespace holo::sensors;

TEST(PackedDataTest, All)
{
    /* construct */
    SensorCompressedPacket<1024 * 1024 * 4> packetData1(1, 1, 2, 3, 4, DataCompressAlgorithm::LZ4);
    SensorCompressedPacket<1024 * 1024 * 4> packetData2;

    /* set */
    packetData2.SetHeader(1);
    packetData2.SetVersion(1);
    packetData2.SetSensorId(2);
    packetData2.SetRawDataLen(3);
    packetData2.SetCompressDataLen(4);
    packetData2.SetCompressAlgorithm(DataCompressAlgorithm::LZ4);
    packetData2.SetCompressAlgorithmDesc(0, 0);

    /* get */
    ASSERT_EQ(packetData1.GetHeader(), 1);
    ASSERT_EQ(packetData1.GetVersion(), 1);
    ASSERT_EQ(packetData1.GetSensorsId(), 2);
    ASSERT_EQ(packetData1.GetRawDataLen(), 3);
    ASSERT_EQ(packetData1.GetCompressDataLen(), 4);
    ASSERT_EQ(packetData1.GetCompressAlgorithm(), DataCompressAlgorithm::LZ4);
    for (int i = 0; i < 16; i++)
    {
        ASSERT_EQ(packetData1.GetCompressAlgorithmDesc(i), 0);
    }
    ASSERT_EQ(packetData2.GetHeader(), 1);
    ASSERT_EQ(packetData2.GetVersion(), 1);
    ASSERT_EQ(packetData2.GetSensorsId(), 2);
    ASSERT_EQ(packetData2.GetRawDataLen(), 3);
    ASSERT_EQ(packetData2.GetCompressDataLen(), 4);
    ASSERT_EQ(packetData2.GetCompressAlgorithm(), DataCompressAlgorithm::LZ4);
    ASSERT_EQ(packetData2.GetCompressAlgorithmDesc(0), 0);

    /* set payload */
    uint8_t  input[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint32_t set      = packetData1.SetPayload(0, input, 8);
    ASSERT_EQ(set, 8);
    packetData1.SetCompressDataLen(8u);
    set = packetData2.SetPayload(0, input, 8);
    ASSERT_EQ(set, 8);
    packetData2.SetCompressDataLen(8u);

    /* calculate CRC */
    packetData1.UpdateCrc32();
    packetData2.UpdateCrc32();
    ASSERT_EQ(packetData1.GetCrc32(), packetData1.GetCrc32());
    LOG(INFO) << "GetCrc32: " << packetData1.GetCrc32();

    /* get payload */
    uint8_t        output[8];
    const uint8_t* output2;
    set = packetData1.GetPayload(0, output, 8);
    ASSERT_EQ(set, 8);
    for (int i = 0; i < 8; i++)
    {
        ASSERT_EQ(output[i], input[i]);
    }
    output2 = packetData1.GetPayload();
    ASSERT_TRUE(output2 != nullptr);
    for (int i = 0; i < 8; i++)
    {
        ASSERT_EQ(output2[i], input[i]);
    }

    /* test payload out of range*/
    static const uint32_t NUM             = 1024 * 1024 * 4;
    uint8_t               large_data[NUM] = {0};
    set                                   = packetData2.SetPayload(0, large_data, NUM);
    ASSERT_EQ(set, NUM);
    set = packetData2.SetPayload(1, large_data, NUM);
    ASSERT_EQ(set, 0);
    set = packetData2.SetPayload(0, large_data, NUM + 1);
    ASSERT_EQ(set, 0);
    uint32_t get = packetData2.GetPayload(0, large_data, sizeof(large_data));
    ASSERT_EQ(get, NUM);
    get = packetData2.GetPayload(100, large_data, sizeof(large_data));
    ASSERT_EQ(get, NUM - 100);
    get = packetData2.GetPayload(NUM, large_data, sizeof(large_data));
    ASSERT_EQ(get, 0);

    /* PayloadCapacity */
    uint32_t ret1 = packetData1.GetPayloadCapacity();
    ASSERT_EQ(ret1, NUM);

    /* Serialized */
    const uint8_t s_want[48] = {1, 0, 1, 0, 2, 0, 0, 0, 3, 0, 0, 0, 8, 0, 0, 0, 1, 0, 0, 0, 0,    0,    0,    0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 0xFE, 0xFF, 0xFF, 0xFF};
    uint8_t       s_read[48];
    ASSERT_EQ(packetData1.GetSerializedSize(), 48);
    /* Length too small */
    uint32_t ser = packetData1.Serialize(s_read, 48 - 2);
    ASSERT_EQ(ser, 0);
    ser = packetData1.Serialize(s_read, 48);
    ASSERT_EQ(ser, 48);
    for (int k = 0; k < 44; k++) /* not crc */
    {
        ASSERT_EQ(s_want[k], s_read[k]);
    }

    /* Deserialized */
    SensorCompressedPacket<NUM> packetData3;
    uint32_t                    ret3 = packetData3.Deserialize(s_read, 48);
    ASSERT_EQ(ret3, 48);
    (void)std::memset(&s_read[0], 0, 48);
    ret3 = packetData1.Serialize(s_read, 48);
    ASSERT_EQ(ret3, 48);
    for (int k = 0; k < 44; k++) /* not crc */
    {
        ASSERT_EQ(s_want[k], s_read[k]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
