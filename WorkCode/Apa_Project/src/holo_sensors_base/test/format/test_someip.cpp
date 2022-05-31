#include <holo/log/hololog.h>
#include <gtest/gtest.h>
#include <holo/sensors/format/someip.h>

using namespace holo::sensors::format;

TEST(SomeIpTest, All)
{
    SomeipPacket<1400> packet1(1,      // service_id
                               2,      // method_id
                               8 + 8,  // msg_length
                               3,      // client_id
                               4,      // session_id
                               5,      // proto_ver
                               6,      // if_ver
                               7,      // msg_type
                               8       // ret_code
    );
    /* basic */
    ASSERT_EQ(packet1.GetMsgId(), 0x00010002);
    ASSERT_EQ(packet1.GetServiceId(), 1);
    ASSERT_EQ(packet1.GetMethodId(), 2);
    ASSERT_EQ(packet1.GetMsgLength(), 16);
    ASSERT_EQ(packet1.GetReqId(), 0x00030004);
    ASSERT_EQ(packet1.GetClientId(), 3);
    ASSERT_EQ(packet1.GetSessionId(), 4);
    ASSERT_EQ(packet1.GetProtoVerison(), 5);
    ASSERT_EQ(packet1.GetIfVersion(), 6);
    ASSERT_EQ(packet1.GetMsgType(), 7);
    ASSERT_EQ(packet1.GetReturnCode(), 8);
    uint8_t  input[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint32_t set      = packet1.SetPayload(0, input, 8);
    ASSERT_EQ(set, 8);
    uint8_t  output[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint32_t get       = packet1.GetPayload(0, output, 8);
    ASSERT_EQ(get, 8);
    for (int k = 0; k < 8; k++)
    {
        ASSERT_EQ(input[k], output[k]);
    }
    /* serialize and deserialize */
    const uint8_t s_want[24] = {0, 1, 0, 2, 0, 0, 0, 16, 0, 3, 0, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
    uint8_t       s_read[24];
    ASSERT_EQ(packet1.GetSerializedSize(), 24);
    uint32_t ser = packet1.Serialize(s_read, 24 - 1);
    ASSERT_EQ(ser, 0);
    ser = packet1.Serialize(s_read, 24);
    ASSERT_EQ(ser, 24);
    for (int k = 0; k < 24; k++)
    {
        ASSERT_EQ(s_want[k], s_read[k]);
    }
    SomeipPacket<1400> packet2;
    uint32_t           des = packet2.Deserialize(s_read, 24 - 1);
    ASSERT_EQ(des, 0);
    des = packet2.Deserialize(s_read, 24);
    ASSERT_EQ(des, 24);
    ASSERT_EQ(packet1.GetMsgId(), packet2.GetMsgId());
    ASSERT_EQ(packet1.GetServiceId(), packet2.GetServiceId());
    ASSERT_EQ(packet1.GetMethodId(), packet2.GetMethodId());
    ASSERT_EQ(packet1.GetMsgLength(), packet2.GetMsgLength());
    ASSERT_EQ(packet1.GetReqId(), packet2.GetReqId());
    ASSERT_EQ(packet1.GetClientId(), packet2.GetClientId());
    ASSERT_EQ(packet1.GetSessionId(), packet2.GetSessionId());
    ASSERT_EQ(packet1.GetProtoVerison(), packet2.GetProtoVerison());
    ASSERT_EQ(packet1.GetIfVersion(), packet2.GetIfVersion());
    ASSERT_EQ(packet1.GetMsgType(), packet2.GetMsgType());
    ASSERT_EQ(packet1.GetReturnCode(), packet2.GetReturnCode());
    /* set */
    packet2.SetServiceId(10001);
    packet2.SetMethodId(10002);
    packet2.SetClientId(10003);
    packet2.SetSessionId(10004);
    packet2.SetProtoVerison(201);
    packet2.SetIfVersion(202);
    packet2.SetMsgType(203);
    packet2.SetReturnCode(204);
    ASSERT_EQ(packet2.GetMsgId(), (uint32_t(10001) << 16) + 10002);
    ASSERT_EQ(packet2.GetServiceId(), 10001);
    ASSERT_EQ(packet2.GetMethodId(), 10002);
    ASSERT_EQ(packet2.GetReqId(), (uint32_t(10003) << 16) + 10004);
    ASSERT_EQ(packet2.GetClientId(), 10003);
    ASSERT_EQ(packet2.GetSessionId(), 10004);
    ASSERT_EQ(packet2.GetProtoVerison(), 201);
    ASSERT_EQ(packet2.GetIfVersion(), 202);
    ASSERT_EQ(packet2.GetMsgType(), 203);
    ASSERT_EQ(packet2.GetReturnCode(), 204);
    /* set msglength and set payload */
    uint8_t large_data[1500] = {0};
    bool    setlen           = packet1.SetMsgLength(1400 + 8 + 1);
    ASSERT_FALSE(setlen);
    setlen = packet1.SetMsgLength(1400 + 8);
    ASSERT_TRUE(setlen);
    set = packet1.SetPayload(0, large_data, 1400);
    ASSERT_EQ(set, 1400);
    set = packet1.SetPayload(1, large_data, 1400);
    ASSERT_EQ(set, 0);
    set = packet1.SetPayload(0, large_data, 1401);
    ASSERT_EQ(set, 0);
    get = packet1.GetPayload(0, large_data, sizeof(large_data));
    ASSERT_EQ(get, 1400);
    get = packet1.GetPayload(100, large_data, sizeof(large_data));
    ASSERT_EQ(get, 1300);
    get = packet1.GetPayload(1401, large_data, sizeof(large_data));
    ASSERT_EQ(get, 0);
    uint8_t* payload = packet1.GetPayload();
    ASSERT_TRUE(payload != nullptr);
    uint32_t payload_length = packet1.GetPayloadLength();
    ASSERT_EQ(payload_length, 1400);
    uint32_t payload_capacity = packet1.GetPayloadCapacity();
    ASSERT_EQ(payload_capacity, 1400);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
