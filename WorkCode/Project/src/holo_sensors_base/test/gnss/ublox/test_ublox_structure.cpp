#include <gtest/gtest.h>
#include <holo/sensors/gnss/ublox/ublox_structure.h>

using namespace holo;
using namespace holo::sensors::ublox;

TEST(UbxNavPvtMessage, Deserialize)
{
    struct UbxNavPvtMessage data;
    uint8_t                 buffer[sizeof(data)];
    (void)std::memset(&buffer, 0, sizeof(buffer));
    uint32_t des_size0 = data.Deserialize(buffer, sizeof(buffer) - 1);
    ASSERT_EQ(des_size0, 0);
    uint32_t des_size = data.Deserialize(buffer, sizeof(buffer));
    ASSERT_EQ(des_size, sizeof(buffer));
    ASSERT_EQ(data.itow, 0);
    ASSERT_EQ(data.year, 0);
    ASSERT_EQ(data.month, 0);
    ASSERT_EQ(data.day, 0);
    ASSERT_EQ(data.hour, 0);
    ASSERT_EQ(data.min, 0);
    ASSERT_EQ(data.sec, 0);
    ASSERT_EQ(data.valid, 0);
    ASSERT_EQ(data.tAcc, 0);
    ASSERT_EQ(data.nano, 0);
    ASSERT_EQ(data.fixType, 0);
    ASSERT_EQ(data.flags, 0);
    ASSERT_EQ(data.flags2, 0);
    ASSERT_EQ(data.numSV, 0);
    ASSERT_EQ(data.lon, 0);
    ASSERT_EQ(data.lat, 0);
    ASSERT_EQ(data.height, 0);
    ASSERT_EQ(data.hMSL, 0);
    ASSERT_EQ(data.hAcc, 0);
    ASSERT_EQ(data.vAcc, 0);
    ASSERT_EQ(data.velN, 0);
    ASSERT_EQ(data.velE, 0);
    ASSERT_EQ(data.velD, 0);
    ASSERT_EQ(data.gSpeed, 0);
    ASSERT_EQ(data.headMot, 0);
    ASSERT_EQ(data.sAcc, 0);
    ASSERT_EQ(data.headAcc, 0);
    ASSERT_EQ(data.pDop, 0);
    ASSERT_EQ(data.headVeh, 0);
    ASSERT_EQ(data.magDec, 0);
    ASSERT_EQ(data.magAcc, 0);
}

TEST(UbxRxmRawxMessageHeader, Deserialize)
{
    struct UbxRxmRawxMessageHeader data;
    uint8_t                        buffer[sizeof(data)];
    (void)std::memset(&buffer, 0, sizeof(buffer));
    uint32_t des_size0 = data.Deserialize(buffer, sizeof(buffer) - 1);
    ASSERT_EQ(des_size0, 0);
    uint32_t des_size = data.Deserialize(buffer, sizeof(buffer));
    ASSERT_EQ(des_size, sizeof(buffer));
    ASSERT_EQ(data.rcvTow, 0);
    ASSERT_EQ(data.week, 0);
    ASSERT_EQ(data.leapS, 0);
    ASSERT_EQ(data.numMeas, 0);
    ASSERT_EQ(data.recStat, 0);
    ASSERT_EQ(data.reserved1[0], 0);
    ASSERT_EQ(data.reserved1[1], 0);
    ASSERT_EQ(data.reserved1[2], 0);
}

TEST(UbxRxmRawxMessageBlock, Deserialize)
{
    struct UbxRxmRawxMessageBlock data;
    uint8_t                       buffer[sizeof(data)];
    (void)std::memset(&buffer, 0, sizeof(buffer));
    uint32_t des_size0 = data.Deserialize(buffer, sizeof(buffer) - 1);
    ASSERT_EQ(des_size0, 0);
    uint32_t des_size = data.Deserialize(buffer, sizeof(buffer));
    ASSERT_EQ(des_size, sizeof(buffer));
    ASSERT_EQ(data.pr_mes, 0);
    ASSERT_EQ(data.cp_mes, 0);
    ASSERT_EQ(data.do_mes, 0);
    ASSERT_EQ(data.gnss_id, 0);
    ASSERT_EQ(data.sv_id, 0);
    ASSERT_EQ(data.reserved2, 0);
    ASSERT_EQ(data.freq_id, 0);
    ASSERT_EQ(data.locktime, 0);
    ASSERT_EQ(data.cno, 0);
    ASSERT_EQ(data.pr_stdev, 0);
    ASSERT_EQ(data.cp_stdev, 0);
    ASSERT_EQ(data.do_stdev, 0);
    ASSERT_EQ(data.trk_stat, 0);
    ASSERT_EQ(data.reserved3, 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
