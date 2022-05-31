#include <gtest/gtest.h>
#include <holo/sensors/radar/ars408/ars408_someip.h>

using namespace holo;
using namespace holo::sensors::conti_radar;
using ObjectType   = holo::sensors::conti_radar::ContiRadarObstacle;
using ObstacleType = holo::obstacle::ObstacleRadarT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::RADAR_OBSTACLE_LIST_COMMON_CAPACITY>;

TEST(ContiRadarDriverInt, All)
{
    Extrinsicf             extrinsic;
    ContiRadarDriverT<int> driver(extrinsic);
    ASSERT_NO_THROW(driver.InstallCallback(nullptr));
    int a = 0;
    ASSERT_NO_THROW(driver.ParseData(a));
}

static void Callback(const ObstaclePtrListType& input, ObstaclePtrListType& output, bool& called)
{
    output = input;
    called = true;
}

TEST(ContiRadarDriverTSomeip, ParseData0)
{
    Extrinsicf                          extrinsic;
    ContiRadarDriverT<SomeipPacketType> driver(extrinsic);
    ObstaclePtrListType                 output;
    bool                                called = false;
    auto h = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(h));
    SomeipPacketType data;
    ASSERT_NO_THROW(driver.ParseData(data));
    ASSERT_FALSE(called);
    data.SetMsgLength(1024);
    ASSERT_NO_THROW(driver.ParseData(data));
    ASSERT_FALSE(called);
}

TEST(ContiRadarDriverTSomeip, ParseData1)
{
    Extrinsicf                          extrinsic;
    ContiRadarDriverT<SomeipPacketType> driver(extrinsic);
    ObstaclePtrListType                 output;
    bool                                called = false;
    auto handler = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(handler));

    struct ContiRadarObjectRawData raw_object = {
        .timestamp         = {.sec = 1, .nsec = 2},
        .id                = 10,  /// -> 10
        .classification    = 1,   /// -> Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR)
        .meas_state        = 2,   /// -> 2
        .prob_of_exist     = 3,   /// -> 0.75
        .rcs               = 128,       /// -> 0
        .length            = 5,         /// -> 1
        .width             = 10,        /// -> 2
        .dyn_prop          = 2,         /// -> MotionStatus::ONCOMING
        .dist_lon          = 2600,      /// -> 2600/5-500=20
        .dist_lat          = 1023 - 5,  /// -> (x-1023)/5=-1
        .vrel_lon          = 512 - 12,  /// -> x/4-128=-3
        .vrel_lat          = 256 + 8,   /// -> x/4-64=2
        .arel_lon          = 1500,      /// -> x/100-10=5
        .arel_lat          = 250,       /// -> x/100-2.5=0
        .orientation_angle = 500,       /// -> x*0.4-180=20
        .dist_lon_rms      = 10,        /// -> 0.063
        .dist_lat_rms      = 11,        /// -> 0.081
        .vrel_lon_rms      = 12,        /// -> 0.105
        .vrel_lat_rms      = 13,        /// -> 0.135
        .arel_lon_rms      = 14,        /// -> 0.174
        .arel_lat_rms      = 15,        /// -> 0.224
        .orientation_angle_rms = 10     /// -> 0.165
    };
    struct ContiRadarObjectListRawData raw_data;
    raw_data.num = 20;
    for (uint32_t k = 0; k < raw_data.num; k++)
    {
        raw_object.id = k + 1;
        memcpy(&raw_data.objects[k], &raw_object, sizeof(struct ContiRadarObjectRawData));
    }
    raw_data.objects[10].prob_of_exist = 0;
    uint8_t data[1024 * 8];
    (void)std::memset(data, 0, sizeof(data));
    uint32_t s = conti_radar_object_list_raw_data_serialize(&raw_data, data, sizeof(data));
    ASSERT_EQ(s, 4 + 52 * 20); /* 1044 */
    SomeipPacketType packet1;
    uint8_t          h  = 0;
    uint8_t          rc = 1;
    uint8_t          pn = 2;
    packet1.SetMsgLength(8 + 4 + 1020);
    packet1.SetPayload(0, &h, 1);
    packet1.SetPayload(1, &rc, 1);
    packet1.SetPayload(2, &pn, 1);
    uint8_t pi = 1;
    packet1.SetPayload(3, &pi, 1);
    packet1.SetPayload(4, data, 1020);
    packet1.SetMsgLength(8 + 4 + 1020 - 4);  // for test
    ASSERT_NO_THROW(driver.ParseData(packet1));
    ASSERT_FALSE(called);
    packet1.SetMsgLength(8 + 4 + 1020);
    ASSERT_NO_THROW(driver.ParseData(packet1));
    ASSERT_FALSE(called);
    h = '#';
    packet1.SetPayload(0, &h, 1);
    ASSERT_NO_THROW(driver.ParseData(packet1));
    ASSERT_FALSE(called);
    SomeipPacketType packet2;
    packet2.SetMsgLength(8 + 4 + 1044 - 1020 - 4);  // for test
    packet2.SetPayload(0, &h, 1);
    packet2.SetPayload(1, &rc, 1);
    packet2.SetPayload(2, &pn, 1);
    pi = 2;
    packet2.SetPayload(3, &pi, 1);
    packet2.SetPayload(4, data, 1044 - 1020);
    ASSERT_NO_THROW(driver.ParseData(packet2));
    ASSERT_FALSE(called);
}

TEST(ContiRadarDriverTSomeip, ParseData2)
{
    Extrinsicf                          extrinsic;
    ContiRadarDriverT<SomeipPacketType> driver(extrinsic);
    ObstaclePtrListType                 output;
    bool                                called = false;
    auto handler = std::bind(&Callback, std::placeholders::_1, std::ref(output), std::ref(called));
    ASSERT_NO_THROW(driver.InstallCallback(handler));

    struct ContiRadarObjectRawData raw_object = {
        .timestamp         = {.sec = 1, .nsec = 2},
        .id                = 10,  /// -> 10
        .classification    = 1,   /// -> Classification(Classification::MainType::VEHICLE, Classification::SubType::CAR)
        .meas_state        = 2,   /// -> 2
        .prob_of_exist     = 3,   /// -> 0.75
        .rcs               = 128,       /// -> 0
        .length            = 5,         /// -> 1
        .width             = 10,        /// -> 2
        .dyn_prop          = 2,         /// -> MotionStatus::ONCOMING
        .dist_lon          = 2600,      /// -> 2600/5-500=20
        .dist_lat          = 1023 - 5,  /// -> (x-1023)/5=-1
        .vrel_lon          = 512 - 12,  /// -> x/4-128=-3
        .vrel_lat          = 256 + 8,   /// -> x/4-64=2
        .arel_lon          = 1500,      /// -> x/100-10=5
        .arel_lat          = 250,       /// -> x/100-2.5=0
        .orientation_angle = 500,       /// -> x*0.4-180=20
        .dist_lon_rms      = 10,        /// -> 0.063
        .dist_lat_rms      = 11,        /// -> 0.081
        .vrel_lon_rms      = 12,        /// -> 0.105
        .vrel_lat_rms      = 13,        /// -> 0.135
        .arel_lon_rms      = 14,        /// -> 0.174
        .arel_lat_rms      = 15,        /// -> 0.224
        .orientation_angle_rms = 10     /// -> 0.165
    };
    struct ContiRadarObjectListRawData raw_data;
    raw_data.num = 20;
    for (uint32_t k = 0; k < raw_data.num; k++)
    {
        raw_object.id = k + 1;
        memcpy(&raw_data.objects[k], &raw_object, sizeof(struct ContiRadarObjectRawData));
    }
    raw_data.objects[10].prob_of_exist = 0;
    uint8_t data[1024 * 8];
    (void)std::memset(data, 0, sizeof(data));
    uint32_t s = conti_radar_object_list_raw_data_serialize(&raw_data, data, sizeof(data));
    ASSERT_EQ(s, 4 + 52 * 20); /* 1044 */
    SomeipPacketType packet1;
    uint8_t          h  = 0;
    uint8_t          rc = 1;
    uint8_t          pn = 2;
    packet1.SetMsgLength(8 + 4 + 1020);
    packet1.SetPayload(0, &h, 1);
    packet1.SetPayload(1, &rc, 1);
    packet1.SetPayload(2, &pn, 1);
    uint8_t pi = 1;
    packet1.SetPayload(3, &pi, 1);
    packet1.SetPayload(4, data, 1020);
    packet1.SetMsgLength(8 + 4 + 1020);
    h = '#';
    packet1.SetPayload(0, &h, 1);
    ASSERT_NO_THROW(driver.ParseData(packet1));
    ASSERT_FALSE(called);
    SomeipPacketType packet2;
    packet2.SetMsgLength(8 + 4 + 1044 - 1020);
    packet2.SetPayload(0, &h, 1);
    packet2.SetPayload(1, &rc, 1);
    packet2.SetPayload(2, &pn, 1);
    pi = 2;
    packet2.SetPayload(3, &pi, 1);
    packet2.SetPayload(4, data, 1044 - 1020);
    ASSERT_NO_THROW(driver.ParseData(packet2));
    ASSERT_TRUE(called);

    ASSERT_EQ(output.GetSize(), 20 - 1);
    const std::shared_ptr<holo::obstacle::ObstacleRadarT<float32_t>> obj = output.GetObstacleList()[10];
    ASSERT_TRUE(obj != nullptr);
    ASSERT_EQ(obj->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obj->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetX(), 20.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetY(), -1.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetZ(), 0.0f);
    /// ASSERT_EQ(obj->GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(obj->GetObstacleId(), 10 + 1 + 1);
    /// ASSERT_EQ(uint32_t(obj->GetSensorId()), holo::sensors::StringToSensorId("RADAR", "RADAR_CONTI_408", "UNKNOWN",
    /// "UNKNOWN", "UNKNOWN"));
    ASSERT_EQ(obj->GetClassification(), holo::common::Classification(holo::common::Classification::MainType::VEHICLE,
                                                                     holo::common::Classification::SubType::CAR));
    ASSERT_FLOAT_EQ(obj->GetObstacleExistScore(), 0.75f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[0], -3.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[1], 2.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[0], 5.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetX(), 0.063f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetY(), 0.081f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[0], 0.105f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[1], 0.135f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[0], 0.174f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[1], 0.224f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetObstacleLength(), 1.0f);
    ASSERT_FLOAT_EQ(obj->GetObstacleWidth(), 2.0f);
    ASSERT_EQ(obj->GetMotionStatus(), holo::obstacle::MotionStatus::ONCOMING);
    ASSERT_FLOAT_EQ(obj->GetObstacleRCS(), 0.0f);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
