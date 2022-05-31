#include <gtest/gtest.h>
#include <holo/sensors/radar/ars408/ars408_holocan.h>
#include <holo_c/sensors/dbc/conti_radar_dbc.h>

using namespace holo;
using namespace holo::sensors::conti_radar;
using ObjectType   = holo::sensors::conti_radar::ContiRadarObstacle;
using ObstacleType = holo::obstacle::ObstacleRadarT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::RADAR_OBSTACLE_LIST_COMMON_CAPACITY>;

static void ConstructCanPacket(uint32_t id, const uint8_t* data, HoloCanPacket& packet)
{
    uint8_t raw_data[28];
    (void)std::memcpy(&raw_data[0], "##@!", 4);
    raw_data[4] = 1;
    raw_data[5] = 2;
    raw_data[6] = 8;
    raw_data[7] = 0;

    raw_data[8]  = (id >> 24) & 0xFF;
    raw_data[9]  = (id >> 16) & 0xFF;
    raw_data[10] = (id >> 8) & 0xFF;
    raw_data[11] = (id >> 0) & 0xFF;

    uint8_t* pdata = &raw_data[12];
    (void)std::memcpy(pdata, data, 8);

    raw_data[20] = (123456789 >> 24) & 0xFF;
    raw_data[21] = (123456789 >> 16) & 0xFF;
    raw_data[22] = (123456789 >> 8) & 0xFF;
    raw_data[23] = (123456789 >> 0) & 0xFF;

    raw_data[24] = (987654321 >> 24) & 0xFF;
    raw_data[25] = (987654321 >> 16) & 0xFF;
    raw_data[26] = (987654321 >> 8) & 0xFF;
    raw_data[27] = (987654321 >> 0) & 0xFF;

    uint32_t des_size = packet.Deserialize(raw_data, sizeof(raw_data));
    ASSERT_EQ(des_size, sizeof(raw_data));
}

static void Callback(const ObstaclePtrListType& input, ObstaclePtrListType& output, bool& called)
{
    output = input;
    called = true;
}

TEST(ContiRadarDriverHoloCan, ParseData0)
{
    Extrinsicf                       extrinsic;
    ContiRadarDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType              output;
    bool                             called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));

    HoloCanPacket packet;
    uint8_t       data[8];
    (void)std::memset(data, 0, sizeof(data));
    ConstructCanPacket(0, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);
}

TEST(ContiRadarDriverHoloCan, ParseData1)
{
    Extrinsicf                       extrinsic;
    ContiRadarDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType              output;
    bool                             called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));

    HoloCanPacket packet;
    uint8_t       data[8];
    (void)std::memset(data, 0, sizeof(data));
    ConstructCanPacket(ID_Object_0_Status, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_TRUE(called);
    ASSERT_EQ(output.GetSize(), 0);
}

TEST(ContiRadarDriverHoloCan, ParseData2)
{
    Extrinsicf                       extrinsic;
    ContiRadarDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType              output;
    bool                             called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));

    HoloCanPacket packet;
    uint8_t       data[8];
    (void)std::memset(data, 0, sizeof(data));

    SET_Object_0_Status_Object_NofObjects(data, 2);
    SET_Object_0_Status_Object_MeasCounter(data, 0);
    SET_Object_0_Status_Object_InterfaceVersion(data, 1);

    ConstructCanPacket(ID_Object_0_Status, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 10);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 11);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 10);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 11);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 10);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    /* absense of 2nd ID_Object_3_Extended */

    (void)std::memset(data, 0, sizeof(data));
    ConstructCanPacket(ID_Object_0_Status, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_TRUE(called);
    ASSERT_EQ(output.GetSize(), 0);
}

TEST(ContiRadarDriverHoloCan, ParseData3)
{
    Extrinsicf                       extrinsic;
    ContiRadarDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType              output;
    bool                             called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));

    HoloCanPacket packet;
    uint8_t       data[8];

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_0_Status_Object_NofObjects(data, 2);
    SET_Object_0_Status_Object_MeasCounter(data, 0);
    SET_Object_0_Status_Object_InterfaceVersion(data, 1);
    ConstructCanPacket(ID_Object_0_Status, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 10);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 11);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 10);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 11);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 10);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 11);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_TRUE(called);
    ASSERT_EQ(output.GetSize(), 2);

    /* for list invalid */
    called = false;
    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 10);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 11);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 10);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 11);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 10);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 11);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_TRUE(called);
    ASSERT_EQ(output.GetSize(), 2);
}

TEST(ContiRadarDriverHoloCan, ParseData4)
{
    Extrinsicf                       extrinsic;
    ContiRadarDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType              output;
    bool                             called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));

    HoloCanPacket packet;
    uint8_t       data[8];
    (void)std::memset(data, 0, sizeof(data));

    SET_Object_0_Status_Object_NofObjects(data, 2);
    SET_Object_0_Status_Object_MeasCounter(data, 0);
    SET_Object_0_Status_Object_InterfaceVersion(data, 1);

    ConstructCanPacket(ID_Object_0_Status, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 10);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 10);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);
}

TEST(ContiRadarDriverHoloCan, ParseData5)
{
    Extrinsicf                       extrinsic;
    ContiRadarDriverT<HoloCanPacket> driver(extrinsic);
    ObstaclePtrListType              output;
    bool                             called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));

    HoloCanPacket packet;
    uint8_t       data[8];
    (void)std::memset(data, 0, sizeof(data));

    SET_Object_0_Status_Object_NofObjects(data, 2);
    SET_Object_0_Status_Object_MeasCounter(data, 0);
    SET_Object_0_Status_Object_InterfaceVersion(data, 1);

    ConstructCanPacket(ID_Object_0_Status, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 10);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_1_General_Object_VrelLong(data, 0);
    SET_Object_1_General_Object_VrelLat(data, 0);
    SET_Object_1_General_Object_RCS(data, 1);
    SET_Object_1_General_Object_ID(data, 11);
    SET_Object_1_General_Object_DynProp(data, 0);
    SET_Object_1_General_Object_DistLong(data, 11);
    SET_Object_1_General_Object_DistLat(data, 12);
    ConstructCanPacket(ID_Object_1_General, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 10);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_2_Quality_Object_VrelLong_rms(data, 0);
    SET_Object_2_Quality_Object_VrelLat_rms(data, 0);
    SET_Object_2_Quality_Object_ProbOfexist(data, 7);
    SET_Object_2_Quality_Object_Orientation_rms(data, 0);
    SET_Object_2_Quality_Object_MeasState(data, 0);
    SET_Object_2_Quality_Object_ID(data, 12);
    SET_Object_2_Quality_Object_DistLong_rms(data, 0);
    SET_Object_2_Quality_Object_DistLat_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLong_rms(data, 0);
    SET_Object_2_Quality_Object_ArelLat_rms(data, 0);
    ConstructCanPacket(ID_Object_2_Quality, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 10);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);

    (void)std::memset(data, 0, sizeof(data));
    SET_Object_3_Extended_Object_Length(data, 0);
    SET_Object_3_Extended_Object_OrientationAngle(data, 0);
    SET_Object_3_Extended_Object_ID(data, 12);
    SET_Object_3_Extended_Object_Width(data, 0);
    SET_Object_3_Extended_Object_Class(data, 0);
    SET_Object_3_Extended_Object_ArelLong(data, 0);
    SET_Object_3_Extended_Object_ArelLat(data, 0);
    ConstructCanPacket(ID_Object_3_Extended, data, packet);
    ASSERT_NO_THROW(driver.ParseData(packet));
    ASSERT_FALSE(called);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
