#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>

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

TEST(BoschMpcDriverSomeip, ConvertToHoloObstacleWithTransform)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    const struct MpcObjectRawData     input = {
        .timestamp  = {.sec = 1, .nsec = 2},
        .confidence = 62,  // (62+2)/128=0.5
        .id         = 10,  // 10
        .classification =
            3,  // Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN)
        .age                         = 123,   // 123
        .inv_ttc                     = 1024,  // (1024-512)/64=8
        .lon_dist                    = 96,    // 96/16=6
        .lon_velocity                = 1080,  // (1080/72-12)=3
        .angle_center                = 0,     // 0
        .angle_width                 = 0,     // 0/2048=0
        .angle_speed                 = 250,   // (250/200 - 1.25)=0
        .angle_edge_left             = 1024,  // (x-1024)/2048=0
        .angle_edge_right            = 512,   // (x-1024)/2048=-0.25
        .angle_overlap_egolane_right = 0,     // 0
        .angle_overlap_egolane_left  = 0      // 0
    };
    std::shared_ptr<ObstacleType> output = std::make_shared<ObstacleType>();
    driver.ConvertToHoloObstacleWithTransform(input, output);
    ASSERT_EQ(output->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output->GetPosition().GetX(), 6.0f);
    ASSERT_FLOAT_EQ(output->GetPosition().GetY(), -0.753930832f);
    ASSERT_FLOAT_EQ(output->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(output->GetCoordinate(), 0);
    ASSERT_EQ(output->GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(output->GetSensorId()), 0);
    ASSERT_EQ(output->GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(output->GetObstacleExistScore(), 0.50f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[0], 3.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(output->GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(output->GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

TEST(BoschMpcDriverSomeip, ConvertToHoloObstacleWithTransform2)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    const struct MpcObjectRawData     input = {
        .timestamp  = {.sec = 1, .nsec = 2},
        .confidence = 127,  // init val
        .id         = 10,   // 10
        .classification =
            3,  // Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN)
        .age                         = 123,   // 123
        .inv_ttc                     = 1024,  // (1024-512)/64=8
        .lon_dist                    = 4095,  // init val
        .lon_velocity                = 2046,  // init val
        .angle_center                = 2047,  // init val
        .angle_width                 = 0,     // 0/2048=0
        .angle_speed                 = 511,   // init val
        .angle_edge_left             = 1024,  // (x-1024)/2048=0
        .angle_edge_right            = 1024,  // (x-1024)/2048=0
        .angle_overlap_egolane_right = 0,     // 0
        .angle_overlap_egolane_left  = 0      // 0
    };
    std::shared_ptr<ObstacleType> output = std::make_shared<ObstacleType>();
    driver.ConvertToHoloObstacleWithTransform(input, output);
    ASSERT_EQ(output->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output->GetPosition().GetX(), 1.0f);  // default val
    ASSERT_FLOAT_EQ(output->GetPosition().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(output->GetCoordinate(), 0);
    ASSERT_EQ(output->GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(output->GetSensorId()), 0);
    ASSERT_EQ(output->GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(output->GetObstacleExistScore(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(output->GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(output->GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

TEST(BoschMpcDriverSomeip, ConvertToObstaclePtrListWithTransform)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    const struct MpcObjectRawData     object = {
        .timestamp  = {.sec = 1, .nsec = 2},
        .confidence = 62,  // (62+2)/128=0.5
        .id         = 10,  // 10
        .classification =
            3,  // Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN)
        .age                         = 123,   // 123
        .inv_ttc                     = 1024,  // (1024-512)/64=8
        .lon_dist                    = 96,    // 96/16=6
        .lon_velocity                = 1080,  // (1080/72-12)=3
        .angle_center                = 0,     // 0
        .angle_width                 = 0,     // 0/2048=0
        .angle_speed                 = 250,   // (250/200 - 1.25)=0
        .angle_edge_left             = 1024,  // (x-1024)/2048=0
        .angle_edge_right            = 512,   // (x-1024)/2048=-0.25
        .angle_overlap_egolane_right = 0,     // 0
        .angle_overlap_egolane_left  = 0      // 0
    };
    struct MpcObjectListRawData input;
    input.num = 1;
    memcpy(&input.object[0], &object, sizeof(struct MpcObjectRawData));
    ObstaclePtrListType output;
    driver.ConvertToObstaclePtrListWithTransform(input, output);
    ASSERT_EQ(output.GetSize(), 1);
    const std::shared_ptr<holo::obstacle::ObstacleVisionT<float32_t>> obj = output.GetObstacleList()[0];
    ASSERT_EQ(obj->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obj->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetX(), 6.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetY(), -0.753930832f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(obj->GetCoordinate(), 0);
    ASSERT_EQ(obj->GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(obj->GetSensorId()), 0);
    ASSERT_EQ(obj->GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(obj->GetObstacleExistScore(), 0.50f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[0], 3.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(obj->GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(obj->GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

TEST(BoschMpcDriverSomeip, ConvertToObstaclePtrListWithTransform2)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    const struct MpcObjectRawData     object = {
        .timestamp  = {.sec = 1, .nsec = 2},
        .confidence = 127,  // init val
        .id         = 10,   // 10
        .classification =
            3,  // Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN)
        .age                         = 123,   // 123
        .inv_ttc                     = 1024,  // (1024-512)/64=8
        .lon_dist                    = 96,    // 96/16=6
        .lon_velocity                = 1080,  // (1080/72-12)=3
        .angle_center                = 0,     // 0
        .angle_width                 = 0,     // 0/2048=0
        .angle_speed                 = 250,   // (250/200 - 1.25)=0
        .angle_edge_left             = 1024,  // (x-1024)/2048=0
        .angle_edge_right            = 512,   // (x-1024)/2048=-0.25
        .angle_overlap_egolane_right = 0,     // 0
        .angle_overlap_egolane_left  = 0      // 0
    };
    struct MpcObjectListRawData input;
    input.num = 1;
    memcpy(&input.object[0], &object, sizeof(struct MpcObjectRawData));
    ObstaclePtrListType output;
    driver.ConvertToObstaclePtrListWithTransform(input, output);
    ASSERT_EQ(output.GetSize(), 0);
}

static void ObjCallback(const ObstaclePtrListType& obstacle_list, ObstaclePtrListType& copy, bool& called)
{
    copy   = obstacle_list;
    called = true;
}

TEST(BoschMpcDriverSomeip, ParseObstacles)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    ObstaclePtrListType               objlist;
    bool                              called = false;
    auto h = std::bind(&ObjCallback, std::placeholders::_1, std::ref(objlist), std::ref(called));
    driver.InstallCallback(h);
    uint8_t data[1024];
    (void)std::memset(data, 0xFF, sizeof(data));
    bool b = driver.ParseObstacles(data, sizeof(data));
    ASSERT_FALSE(b);
    ASSERT_FALSE(called);
    struct MpcObjectListRawData test_objects;
    (void)memset(&test_objects, 0, sizeof(struct MpcObjectListRawData));
    const struct MpcObjectRawData object = {
        .timestamp  = {.sec = 1, .nsec = 2},
        .confidence = 62,  // (62+2)/128=0.5
        .id         = 10,  // 10
        .classification =
            3,  // Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN)
        .age                         = 123,   // 123
        .inv_ttc                     = 1024,  // (1024-512)/64=8
        .lon_dist                    = 96,    // 96/16=6
        .lon_velocity                = 1080,  // (1080/72-12)=3
        .angle_center                = 0,     // 0
        .angle_width                 = 0,     // 0/2048=0
        .angle_speed                 = 250,   // (250/200 - 1.25)=0
        .angle_edge_left             = 1024,  // (x-1024)/2048=0
        .angle_edge_right            = 512,   // (x-1024)/2048=-0.25
        .angle_overlap_egolane_right = 0,     // 0
        .angle_overlap_egolane_left  = 0      // 0
    };
    test_objects.num = 1;
    memcpy(&test_objects.object[0], &object, sizeof(struct MpcObjectRawData));
    mpc_object_list_raw_data_serialize(&test_objects, data, sizeof(data));
    b = driver.ParseObstacles(data, sizeof(data));
    ASSERT_TRUE(b);
    ASSERT_TRUE(called);
    ASSERT_EQ(objlist.GetSize(), 1);
    const std::shared_ptr<holo::obstacle::ObstacleVisionT<float32_t>> obj = objlist.GetObstacleList()[0];
    ASSERT_EQ(obj->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obj->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetX(), 6.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetY(), -0.753930832f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(obj->GetCoordinate(), 0);
    ASSERT_EQ(obj->GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(obj->GetSensorId()), 0);
    ASSERT_EQ(obj->GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(obj->GetObstacleExistScore(), 0.50f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[0], 3.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(obj->GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(obj->GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

TEST(BoschMpcDriverSomeip, ParseData)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    ObstaclePtrListType               objlist;
    bool                              called = false;
    auto h = std::bind(&ObjCallback, std::placeholders::_1, std::ref(objlist), std::ref(called));
    driver.InstallCallback(h);
    uint8_t data[1024];
    (void)std::memset(data, 0xFF, sizeof(data));
    SomeipPacketType packet;
    packet.SetMethodId(0x21);
    packet.SetMsgLength(8 + sizeof(data));
    packet.SetPayload(0, data, sizeof(data));
    driver.ParseData(packet);
    ASSERT_FALSE(called);
    struct MpcObjectListRawData test_objects;
    (void)memset(&test_objects, 0, sizeof(struct MpcObjectListRawData));
    const struct MpcObjectRawData object = {
        .timestamp  = {.sec = 1, .nsec = 2},
        .confidence = 62,  // (62+2)/128=0.5
        .id         = 10,  // 10
        .classification =
            3,  // Classification(Classification::MainType::PEDESTRIAN, Classification::SubType::PEDESTRIAN)
        .age                         = 123,   // 123
        .inv_ttc                     = 1024,  // (1024-512)/64=8
        .lon_dist                    = 96,    // 96/16=6
        .lon_velocity                = 1080,  // (1080/72-12)=3
        .angle_center                = 0,     // 0
        .angle_width                 = 0,     // 0/2048=0
        .angle_speed                 = 250,   // (250/200 - 1.25)=0
        .angle_edge_left             = 1024,  // (x-1024)/2048=0
        .angle_edge_right            = 512,   // (x-1024)/2048=-0.25
        .angle_overlap_egolane_right = 0,     // 0
        .angle_overlap_egolane_left  = 0      // 0
    };
    test_objects.num = 1;
    memcpy(&test_objects.object[0], &object, sizeof(struct MpcObjectRawData));
    uint32_t ser_size = mpc_object_list_raw_data_serialize(&test_objects, data, sizeof(data));
    ASSERT_TRUE(ser_size > 0);
    packet.SetMethodId(0x21);
    packet.SetMsgLength(8 + 4 + ser_size);
    packet.SetPayload(4, data, ser_size);
    driver.ParseData(packet);
    ASSERT_TRUE(called);
    ASSERT_EQ(objlist.GetSize(), 1);
    const std::shared_ptr<holo::obstacle::ObstacleVisionT<float32_t>> obj = objlist.GetObstacleList()[0];
    ASSERT_EQ(obj->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obj->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetX(), 6.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetY(), -0.753930832f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(obj->GetCoordinate(), 0);
    ASSERT_EQ(obj->GetObstacleId(), 10);
    ASSERT_EQ(uint32_t(obj->GetSensorId()), 0);
    ASSERT_EQ(obj->GetClassification(),
              holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
                                           holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(obj->GetObstacleExistScore(), 0.50f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[0], 3.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetX(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetY(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetPositionSigma().GetZ(), 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocitySigma()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[0], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[1], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAccelerationSigma()[2], 0.0f);
    ASSERT_EQ(obj->GetMotionStatus(), holo::obstacle::MotionStatus::UNKNOWN);
    ASSERT_EQ(obj->GetCutInCutOut(), holo::obstacle::CutInCutOut::UNKNOWN);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
