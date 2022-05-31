#include <gtest/gtest.h>
#include <holo/sensors/lidar/livox/livox_hap_driver.h>

using namespace holo;
using namespace holo::sensors::livox;
using namespace holo::sensors::format;

TEST(LivoxHapDriverTest, All)
{
    /* LivoxHapKeyValueParam */
    uint8_t             data0[21];
    uint8_t             req_len = 0;
    LivoxHapControlInfo info1(NORMAL_MODE, 11, 30, 0xff);
    /* work mode */
    LivoxHapKeyValueParam<uint8_t>* kv8 = reinterpret_cast<LivoxHapKeyValueParam<uint8_t>*>(&data0[0]);
    kv8->SetValue(KEY_WORK_MODE, info1.WorkMode());
    req_len += sizeof(LivoxHapKeyValueParam<uint8_t>);  // 5
    ASSERT_EQ(kv8->Key(), KEY_WORK_MODE);
    ASSERT_EQ(kv8->ValLength(), sizeof(uint8_t));
    ASSERT_EQ(kv8->Value(), info1.WorkMode());
    /* vehicle speed */
    LivoxHapKeyValueParam<uint32_t>* kv32 = reinterpret_cast<LivoxHapKeyValueParam<uint32_t>*>(&data0[req_len]);
    kv32->SetValue(KEY_VEHICLE_SPEED, info1.VehicleSpeed());
    req_len += sizeof(LivoxHapKeyValueParam<uint32_t>);  // 5+ 8
    ASSERT_EQ(kv32->Key(), KEY_VEHICLE_SPEED);
    ASSERT_EQ(kv32->ValLength(), sizeof(uint32_t));
    ASSERT_EQ(kv32->Value(), info1.VehicleSpeed());
    /* ev temp */
    kv32 = reinterpret_cast<LivoxHapKeyValueParam<uint32_t>*>(&data0[req_len]);
    kv32->SetValue(KEY_ENVIRONMENT_TEMP, info1.EvTemp());  // 5 + 8 + 8
    ASSERT_EQ(kv32->Key(), KEY_ENVIRONMENT_TEMP);
    ASSERT_EQ(kv32->ValLength(), sizeof(uint32_t));
    ASSERT_EQ(kv32->Value(), info1.EvTemp());

    /* LivoxHapControlInfo */
    LivoxHapControlInfo info2(NORMAL_MODE, 11, 30, 0xff);
    ASSERT_EQ(info2.WorkMode(), NORMAL_MODE);
    ASSERT_EQ(info2.VehicleSpeed(), 11);
    ASSERT_EQ(info2.EvTemp(), 30);
    ASSERT_EQ(info2.Slot(), 0xff);

    /* Driver  Constructor */
    LivoxHapDriver<LivoxHapPacket<1440>> driver(1234, 313, 10);
    LivoxHapPacket<1440>                 packet;
    EXPECT_NO_THROW(driver.PushPacket(packet));

    /* broadcast discovery packet content */
    uint8_t  data[50] = {0};
    uint32_t len      = 50;
    driver.generateBroadcastDiscoveryPacket(0x0d, data, len);
    ASSERT_EQ(data[0], 0xAA);
    ASSERT_EQ(data[1], 2);
    ASSERT_EQ((uint16_t)data[2], 21);
    ASSERT_EQ((uint16_t)data[4], 0x00);
    ASSERT_EQ((uint16_t)data[6], 0x00);
    ASSERT_EQ((uint16_t)data[8], 0x0d);
    ASSERT_EQ((uint16_t)data[10], 0x10);
    ASSERT_EQ((uint16_t)data[12], 0x00);
    ASSERT_EQ((uint16_t)data[16], NULL);

    /* lidar work control packet content */
    uint8_t data1[41] = {0xaa, 0x02, 0x29, 0x00, 0x00, 0x00, 0x02, 0x00, 0x0d, 0x00, 0x10, 0x00, 0x00, 0x00,
                         0xff, 0xe9, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x04, 0x00, 0x0b, 0x00, 0x00,
                         0x00, 0x02, 0x00, 0x04, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x73, 0xf2, 0x17, 0x35};
    uint8_t data2[50] = {0};
    len               = 50;
    LivoxHapControlInfo info(NORMAL_MODE, 11, 30, 0xff);
    driver.generateWorkControlPacket(0x0d, data2, len, info);
    ASSERT_EQ(data2[0], 0xAA);
    ASSERT_EQ(data2[1], 2);
    ASSERT_EQ((uint16_t)data2[2], 41);
    ASSERT_EQ((uint16_t)data2[4], 0x00);
    ASSERT_EQ((uint16_t)data2[6], 0x02);
    ASSERT_EQ((uint16_t)data2[8], 0x0d);
    ASSERT_EQ((uint16_t)data2[10], 0x10);
    ASSERT_EQ((uint16_t)data2[12], 0x00);
    for (int i = 14; i < 41; i++)
    {
        ASSERT_EQ(data1[i], data2[i]);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
