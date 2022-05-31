#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>

using namespace holo;
using namespace holo::sensors::bosch_mpc;

/* obstacle alias */
using ObjectType   = holo::sensors::bosch_mpc::BoschMpcObstacle;
using ObstacleType = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallback = std::function<void(const ObstaclePtrListType&)>;
/* lane boundary alias */
using MpcBoundaryType   = holo::sensors::bosch_mpc::BoschMpcLaneBoundary;
using LaneboundaryType  = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType     = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallback = std::function<void(const RoadFrameType&)>;

TEST(BoschMpcDriverHoloCan, ConstructObjectPartA)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    (void)std::memset(&raw_data[12], 0, 8);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartA(packet, object);
    ASSERT_FLOAT_EQ(object.GetLongDist(), 0);
    ASSERT_FLOAT_EQ(object.GetAngleCenter(), -0.5);
    ASSERT_EQ(object.GetClassification(), 0);
    ASSERT_TRUE(object.GetPartAValid());
}

TEST(BoschMpcDriverHoloCan, ConstructObjectPartA2)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memset(pdata, 0, 8);
    SET_BV_Obj_01_A_BV1_Obj_01_LongitudinalDist(pdata, BV_Obj_01_A_BV1_Obj_01_LongitudinalDist_Init);
    SET_BV_Obj_01_A_BV1_Obj_01_WnklMitte(pdata, BV_Obj_01_A_BV1_Obj_01_WnklMitte_Init);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartA(packet, object);
    ASSERT_FLOAT_EQ(object.GetLongDist(), 1.0);
    ASSERT_FLOAT_EQ(object.GetAngleCenter(), 0);
    ASSERT_EQ(object.GetClassification(), 0);
    ASSERT_TRUE(object.GetPartAValid());
}

TEST(BoschMpcDriverHoloCan, ConstructObjectPartB)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memset(pdata, 0, 8);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartB(packet, object);
    ASSERT_FLOAT_EQ(object.GetAngleWidth(), 0);
    ASSERT_FLOAT_EQ(object.GetConfidence(), 1.0 / 64);
    ASSERT_FLOAT_EQ(object.GetAngleSpeed(), -1.25);
    ASSERT_TRUE(object.GetPartBValid());
}

TEST(BoschMpcDriverHoloCan, ConstructObjectPartB2)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memset(pdata, 0, 8);
    SET_BV_Obj_01_B_BV1_Obj_01_ExistenzMass(pdata, BV_Obj_01_B_BV1_Obj_01_ExistenzMass_Init);
    SET_BV_Obj_01_B_BV1_Obj_01_WnklGeschw(pdata, BV_Obj_01_B_BV1_Obj_01_WnklGeschw_Init);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartB(packet, object);
    ASSERT_FLOAT_EQ(object.GetAngleWidth(), 0);
    ASSERT_FLOAT_EQ(object.GetConfidence(), 0);
    ASSERT_FLOAT_EQ(object.GetAngleSpeed(), 0);
    ASSERT_TRUE(object.GetPartBValid());
}

TEST(BoschMpcDriverHoloCan, ConstructObjectPartC)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memset(pdata, 0, 8);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartC(packet, object);
    ASSERT_FLOAT_EQ(object.GetInvTTC(), -8);
    ASSERT_FLOAT_EQ(object.GetAngleOverlapEgolaneRight(), -0.25);
    ASSERT_FLOAT_EQ(object.GetAngleOverlapEgolaneLeft(), -0.25);
    ASSERT_EQ(object.GetAge(), 0);
    ASSERT_TRUE(object.GetPartCValid());
}

TEST(BoschMpcDriverHoloCan, ConstructObjectPartD)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memset(pdata, 0, 8);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartD(packet, object);
    ASSERT_FLOAT_EQ(object.GetAngleEdgeRight(), -0.5);
    ASSERT_FLOAT_EQ(object.GetAngleEdgeLeft(), -0.5);
    ASSERT_EQ(object.GetId(), 0);
    ASSERT_TRUE(object.GetPartDValid());
}

TEST(BoschMpcDriverHoloCan, ConstructObjectPartE)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (0 >> 24) & 0xFF;
    raw_data[9]  = (0 >> 16) & 0xFF;
    raw_data[10] = (0 >> 8) & 0xFF;
    raw_data[11] = (0 >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memset(pdata, 0, 8);
    SET_BV_Obj_01_E_BV1_Obj_01_RadialGeschw(pdata, BV_Obj_01_E_BV1_Obj_01_RadialGeschw_Init);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    HoloCanPacket packet;
    packet.Deserialize(raw_data, sizeof(raw_data));
    ObjectType object;
    driver.ConstructObjectPartE(packet, object);
    ASSERT_FLOAT_EQ(object.GetLongVelocity(), 0);
    ASSERT_TRUE(object.GetPartEValid());
    ASSERT_EQ(object.GetTimestamp(), holo::common::Timestamp(123456789, 987654321));
}

TEST(BoschMpcDriverHoloCan, ConvertToObstaclePtrListWithTransform)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);
    std::array<ObjectType, 16>     input;
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[0].SetPartCValid(true);
    input[0].SetPartDValid(true);
    input[0].SetPartEValid(true);
    input[0].SetConfidence(0.1);
    input[0].SetPartAValid(true);
    input[0].SetPartBValid(true);
    input[0].SetPartCValid(true);
    input[0].SetPartDValid(true);
    input[0].SetPartEValid(true);
    input[0].SetConfidence(0.0);
    ObstaclePtrListType output;
    driver.ConvertToObstaclePtrListWithTransform(input, output);
}

static void ObjCallback(const ObstaclePtrListType& obstacle_list, ObstaclePtrListType& copy, bool& called)
{
    copy   = obstacle_list;
    called = true;
}

TEST(BoschMpcDriverHoloCan, ParseData)
{
    Extrinsicf                     extrinsic;
    BoschMpcDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType            objlist;
    bool                           called = false;
    auto h = std::bind(&ObjCallback, std::placeholders::_1, std::ref(objlist), std::ref(called));
    driver.InstallCallback(h);

    const uint32_t id_list[80] = {
        ID_BV_Obj_01_A, ID_BV_Obj_01_B, ID_BV_Obj_01_C, ID_BV_Obj_01_D, ID_BV_Obj_01_E, ID_BV_Obj_02_A, ID_BV_Obj_02_B,
        ID_BV_Obj_02_C, ID_BV_Obj_02_D, ID_BV_Obj_02_E, ID_BV_Obj_03_A, ID_BV_Obj_03_B, ID_BV_Obj_03_C, ID_BV_Obj_03_D,
        ID_BV_Obj_03_E, ID_BV_Obj_04_A, ID_BV_Obj_04_B, ID_BV_Obj_04_C, ID_BV_Obj_04_D, ID_BV_Obj_04_E, ID_BV_Obj_05_A,
        ID_BV_Obj_05_B, ID_BV_Obj_05_C, ID_BV_Obj_05_D, ID_BV_Obj_05_E, ID_BV_Obj_06_A, ID_BV_Obj_06_B, ID_BV_Obj_06_C,
        ID_BV_Obj_06_D, ID_BV_Obj_06_E, ID_BV_Obj_07_A, ID_BV_Obj_07_B, ID_BV_Obj_07_C, ID_BV_Obj_07_D, ID_BV_Obj_07_E,
        ID_BV_Obj_08_A, ID_BV_Obj_08_B, ID_BV_Obj_08_C, ID_BV_Obj_08_D, ID_BV_Obj_08_E, ID_BV_Obj_09_A, ID_BV_Obj_09_B,
        ID_BV_Obj_09_C, ID_BV_Obj_09_D, ID_BV_Obj_09_E, ID_BV_Obj_10_A, ID_BV_Obj_10_B, ID_BV_Obj_10_C, ID_BV_Obj_10_D,
        ID_BV_Obj_10_E, ID_BV_Obj_11_A, ID_BV_Obj_11_B, ID_BV_Obj_11_C, ID_BV_Obj_11_D, ID_BV_Obj_11_E, ID_BV_Obj_12_A,
        ID_BV_Obj_12_B, ID_BV_Obj_12_C, ID_BV_Obj_12_D, ID_BV_Obj_12_E, ID_BV_Obj_13_A, ID_BV_Obj_13_B, ID_BV_Obj_13_C,
        ID_BV_Obj_13_D, ID_BV_Obj_13_E, ID_BV_Obj_14_A, ID_BV_Obj_14_B, ID_BV_Obj_14_C, ID_BV_Obj_14_D, ID_BV_Obj_14_E,
        ID_BV_Obj_15_A, ID_BV_Obj_15_B, ID_BV_Obj_15_C, ID_BV_Obj_15_D, ID_BV_Obj_15_E, ID_BV_Obj_16_A, ID_BV_Obj_16_B,
        ID_BV_Obj_16_C, ID_BV_Obj_16_D, ID_BV_Obj_16_E,
    };

    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    for (int i = 0; i < 80; ++i)
    {
        raw_data[8]  = (id_list[i] >> 24) & 0xFF;
        raw_data[9]  = (id_list[i] >> 16) & 0xFF;
        raw_data[10] = (id_list[i] >> 8) & 0xFF;
        raw_data[11] = (id_list[i] >> 0) & 0xFF;
        HoloCanPacket packet;
        packet.Deserialize(raw_data, sizeof(raw_data));
        ASSERT_NO_THROW(driver.ParseData(packet));
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
