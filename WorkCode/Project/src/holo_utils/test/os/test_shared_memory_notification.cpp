#include <gtest/gtest.h>
#include <holo/os/shared_memory_block.h>
#include <iostream>

using SharedMemoryNotification = holo::os::SharedMemoryNotification;

/**
 * @brief Test SharedMemoryNotification::GetSerializedSize
 */
TEST(SharedMemoryNotification, GetSerializedSize)
{
    SharedMemoryNotification notification;
    ASSERT_EQ(136, notification.GetSerializedSize<4U>());
    ASSERT_EQ(136, notification.GetSerializedSize<8U>());
}

/**
 * @brief Test SharedMemoryNotification::Serialize and Deserialize
 */
TEST(SharedMemoryNotification, SerializeAndDeserialize)
{
    SharedMemoryNotification          notification1{10U, 100U, "1234567abcdefg"};
    uint8_t                           buffer[1024];
    holo::serialization::Serializer<> serializer(buffer, 1024);
    serializer << notification1;
    ASSERT_EQ(notification1.GetSerializedSize(), serializer.GetSize());

    holo::serialization::Deserializer<> deserializer(buffer, serializer.GetSize());
    SharedMemoryNotification            notification2;
    deserializer >> notification2;

    ASSERT_EQ(notification1.block_index, notification2.block_index);
    ASSERT_EQ(notification1.block_version, notification2.block_version);
    int ret =
        memcmp(notification1.block_name, notification2.block_name, SharedMemoryNotification::BLOCK_NAME_MAX_LENGTH);
    ASSERT_EQ(0, ret);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
