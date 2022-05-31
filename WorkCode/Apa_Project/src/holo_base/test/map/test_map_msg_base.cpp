#include <gtest/gtest.h>
#include <holo/map/map_msg_base.h>
#include <iostream>

class TestMapMsgBase : public holo::map::MapMsgBase
{
public:
    TestMapMsgBase() : holo::map::MapMsgBase(4U, 4U, 4U)
    {
    }
};

TEST(TestMapMsgBase, Test_MapMsgBase_Valid)
{
    ::holo::map::MapMsgBase map_message(10, 11, 12);
    ASSERT_TRUE(map_message.IsValid());

    auto indicator_size = map_message.GetValidIndicatorSize();
    map_message.SetValidIndicatorSize(100);
    ASSERT_FALSE(map_message.IsValid());
    map_message.SetValidIndicatorSize(indicator_size);
    ASSERT_TRUE(map_message.IsValid());

    auto uint32_size = map_message.GetValidUint32Size();
    map_message.SetValidUint32Size(100);
    ASSERT_FALSE(map_message.IsValid());
    map_message.SetValidUint32Size(uint32_size);
    ASSERT_TRUE(map_message.IsValid());

    auto float32_size = map_message.GetValidFloat32Size();
    map_message.SetValidFloat32Size(100);
    ASSERT_FALSE(map_message.IsValid());
    map_message.SetValidFloat32Size(float32_size);
    ASSERT_TRUE(map_message.IsValid());
}

TEST(TestMapMsgBase, Test_MapMsgBase_Constructor)
{
    ::holo::map::MapMsgBase map_message(10, 11, 12);
    ASSERT_TRUE(map_message.IsValid());

    auto indicator_size = map_message.GetValidIndicatorSize();
    ASSERT_EQ(10, indicator_size);
    map_message.SetValidIndicatorSize(100);
    ASSERT_FALSE(map_message.IsValid());
    map_message.SetValidIndicatorSize(indicator_size);
    ASSERT_TRUE(map_message.IsValid());

    auto uint32_size = map_message.GetValidUint32Size();
    ASSERT_EQ(11, uint32_size);
    map_message.SetValidUint32Size(100);
    ASSERT_FALSE(map_message.IsValid());
    map_message.SetValidUint32Size(uint32_size);
    ASSERT_TRUE(map_message.IsValid());

    auto float32_size = map_message.GetValidFloat32Size();
    ASSERT_EQ(12, float32_size);
    map_message.SetValidFloat32Size(100);
    ASSERT_FALSE(map_message.IsValid());
    map_message.SetValidFloat32Size(float32_size);
    ASSERT_TRUE(map_message.IsValid());
}

TEST(TestMapMsgBase, Test_MapMsgBase_CopyConstructor)
{
    ::holo::map::MapMsgBase map_message(10, 11, 12);
    ASSERT_TRUE(map_message.IsValid());
    map_message.SetValidIndicatorSize(100);

    ::holo::map::MapMsgBase map_message_copy(map_message);
    ASSERT_FALSE(map_message_copy.IsValid());
}

TEST(TestMapMsgBase, Test_MapMsgBase_assignmentOperator)
{
    ::holo::map::MapMsgBase map_message_1(10, 11, 12);
    ::holo::map::MapMsgBase map_message_2(11, 12, 13);
    ASSERT_TRUE(map_message_1.IsValid());
    ASSERT_TRUE(map_message_2.IsValid());
    map_message_1 = map_message_2;
    ASSERT_FALSE(map_message_1.IsValid());
}

TEST(TestMapMsgBase, BasicSerializeDeserialize)
{
    TestMapMsgBase msg, dst;
    msg.SetValuesFloat32({1.0f, 2.0f, 3.0f, 4.0f});
    msg.SetValuesUint32({1, 2, 3, 4});
    ASSERT_TRUE(msg.IsValid());

    uint8_t buffer[64];
    holo::serialization::Serializer<> serializer(buffer, 64U);
    serializer << msg;
    
    ASSERT_EQ(msg.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    deserializer >> dst;

    ASSERT_EQ(msg.GetValuesFloat32(), dst.GetValuesFloat32());
    ASSERT_EQ(msg.GetValuesUint32(), dst.GetValuesUint32());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
