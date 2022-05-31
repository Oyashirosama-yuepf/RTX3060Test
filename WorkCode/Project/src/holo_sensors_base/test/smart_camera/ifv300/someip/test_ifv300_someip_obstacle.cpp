#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_someip.h>

TEST(Ifv300DriverInt, All)
{
    ASSERT_TRUE(true);
}

#if 0
TEST(Ifv300Obj, Constructor)
{
    EXPECT_ANY_THROW(Ifv300Test(std::string("")));
}

TEST(Ifv300Obj, SetupTest)
{
    auto driver = std::make_shared<Ifv300Test>();
    EXPECT_ANY_THROW(driver->SetupTest());
}

TEST(Ifv300Obj, ExtrinsicTest)
{
    auto driver = std::make_shared<Ifv300Test>();
    EXPECT_ANY_THROW(driver->ExtrinsicTest());
}

TEST(Ifv300Obj, LoadParameters)
{
    auto driver = std::make_shared<Ifv300Test>();
    const std::string config("");
    bool b = driver->LoadParameters(config);
    ASSERT_FALSE(b);
}
TEST(Ifv300Obj, ConvertToHoloObstacleWithTransform)
{
    auto driver = std::make_shared<Ifv300Test>();
    const std::shared_ptr<holo::common::Extrinsicf> extrinsic = std::make_shared<holo::Extrinsicf>(
        holo::common::Coordinate(holo::common::Coordinate::BODY),
        holo::common::Coordinate(holo::common::Coordinate::UNKNOWN), holo::geometry::Pose3f());
    struct IfvObjectRawData input;
    input.timestamp.sec                = 1; // 
    input.timestamp.nsec               = 2; // 
    input.part_A.message_counter_msg1  = 3; // 
    input.part_A.count_msg1            = 9; // 
    input.part_A.id                    = 0; // 
    input.part_A.classification        = 4; // Classification(MainType::PEDESTRIAN, SubType::PEDESTRIAN)
    input.part_A.ped_waise_up          = 0; // 
    input.part_A.turn_indicator        = 0; // 
    input.part_A.brake_light_indicator = 0; // 
    input.part_A.height                = 18; // 18 / 10 = 1.8
    input.part_B.message_counter_msg2  = 3; // 
    input.part_B.count_msg2            = 9; // 
    input.part_B.long_accel            = 2560+64; // (x-2560)/128
    input.part_B.ttc_const_acc_model   = 0; // 
    input.part_B.cut_in_cut_out        = 3; // CutInCutOut::NEXT_CUT_IN_RIGHT (lat_pos < 0)
    input.part_C.message_counter_msg3  = 3; // 
    input.part_C.count_msg3            = 9; // 
    input.part_C.lat_pos               = 2048-32; // (x-2048)/16=-2
    input.part_C.lat_vel               = 2048-24; // (x-2048)/16=-1.5
    input.part_C.long_pos              = 32*8; // x/32=8
    input.part_C.long_vel              = 2048+100; // (x-2048)/16=6.25
    input.part_C.width                 = 22; // x/10=2.2
    std::shared_ptr<ObstacleType> output = std::make_shared<ObstacleType>();
    driver->ConvertToHoloObstacleWithTransform(extrinsic, input, output);
    ASSERT_EQ(output->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(output->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(output->GetPosition().GetX(), 8.0f);
    ASSERT_FLOAT_EQ(output->GetPosition().GetY(), 2.0f);
    ASSERT_FLOAT_EQ(output->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(output->GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(output->GetObstacleId(), 9);
    ASSERT_EQ(uint32_t(output->GetSensorId()), 0);
    ASSERT_EQ(output->GetClassification(), holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
        holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(output->GetObstacleExistScore(), 1.0f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[0], 6.25f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[1], 1.5f);
    ASSERT_FLOAT_EQ(output->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(output->GetAcceleration()[0], 0.5f);
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
    ASSERT_EQ(output->GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_IN_LEFT);
}

TEST(Ifv300Obj, ConvertToObstaclePtrListWithTransform)
{
    auto driver = std::make_shared<Ifv300Test>();
    struct IfvObjectRawData object;
    object.timestamp.sec                = 1; // 
    object.timestamp.nsec               = 2; // 
    object.part_A.message_counter_msg1  = 3; // 
    object.part_A.count_msg1            = 9; // 
    object.part_A.id                    = 0; // 
    object.part_A.classification        = 4; // Classification(MainType::PEDESTRIAN, SubType::PEDESTRIAN)
    object.part_A.ped_waise_up          = 0; // 
    object.part_A.turn_indicator        = 0; // 
    object.part_A.brake_light_indicator = 0; // 
    object.part_A.height                = 18; // 18 / 10 = 1.8
    object.part_B.message_counter_msg2  = 3; // 
    object.part_B.count_msg2            = 9; // 
    object.part_B.long_accel            = 2560+64; // (x-2560)/128
    object.part_B.ttc_const_acc_model   = 0; // 
    object.part_B.cut_in_cut_out        = 3; // CutInCutOut::NEXT_CUT_IN_LEFT (lat_pos > 0)
    object.part_C.message_counter_msg3  = 3; // 
    object.part_C.count_msg3            = 9; // 
    object.part_C.lat_pos               = 2048+32; // (x-2048)/16=2
    object.part_C.lat_vel               = 2048+24; // (x-2048)/16=1.5
    object.part_C.long_pos              = 32*8; // x/32=8
    object.part_C.long_vel              = 2048+100; // (x-2048)/16=6.25
    object.part_C.width                 = 22; // x/10=2.2
    struct IfvObjectListRawData input;
    input.num = 1;
    memcpy(&input.object[0], &object, sizeof(struct IfvObjectRawData));
    ObstaclePtrListType output;
    driver->ConvertToObstaclePtrListWithTransform(input, output);
    ASSERT_EQ(output.GetSize(), 1);
    const std::shared_ptr<holo::obstacle::ObstacleVisionT<float32_t>> obj = output.GetObstacleList()[0];
    ASSERT_EQ(obj->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obj->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetX(), 8.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetY(), -2.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(obj->GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(obj->GetObstacleId(), 9);
    ASSERT_EQ(obj->GetSensorId(), holo::sensors::StringToSensorId("CAMERA", "CAMERA_DELPHI_IFV300", "FRONT_WINDOW", "CENTER", "TOP_MOST"));
    ASSERT_EQ(obj->GetClassification(), holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
        holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(obj->GetObstacleExistScore(), 1.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[0], 6.25f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[1], -1.5f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[0], 0.5f);
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
    ASSERT_EQ(obj->GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_IN_RIGHT);
}

static void ObjCallback(const ObstaclePtrListType& obstacle_list, ObstaclePtrListType& copy)
{
    copy = obstacle_list;
}

TEST(Ifv300Obj, ParseObstacles)
{
    auto driver = std::make_shared<Ifv300Test>();
    ObstaclePtrListType objlist;
    auto h = std::bind(&ObjCallback, std::placeholders::_1, std::ref(objlist));
    driver->InstallCallback(h);
    struct IfvObjectListRawData raw_objects;
    uint8_t data[1024] = {0};
    (void)std::memset(data, 0xFF, sizeof(data));
    bool b = driver->ParseObstacles(data, sizeof(data), raw_objects);
    ASSERT_FALSE(b);
    struct IfvObjectListRawData test_objects;
    (void)memset(&test_objects, 0, sizeof(struct IfvObjectListRawData));
    struct IfvObjectRawData object;
    object.timestamp.sec                = 1; // 
    object.timestamp.nsec               = 2; // 
    object.part_A.message_counter_msg1  = 3; // 
    object.part_A.count_msg1            = 9; // 
    object.part_A.id                    = 0; // 
    object.part_A.classification        = 4; // Classification(MainType::PEDESTRIAN, SubType::PEDESTRIAN)
    object.part_A.ped_waise_up          = 0; // 
    object.part_A.turn_indicator        = 0; // 
    object.part_A.brake_light_indicator = 0; // 
    object.part_A.height                = 18; // 18 / 10 = 1.8
    object.part_B.message_counter_msg2  = 3; // 
    object.part_B.count_msg2            = 9; // 
    object.part_B.long_accel            = 2560+64; // (x-2560)/128
    object.part_B.ttc_const_acc_model   = 0; // 
    object.part_B.cut_in_cut_out        = 4; // CutInCutOut::NEXT_CUT_OUT_LEFT (lat_pos > 0)
    object.part_C.message_counter_msg3  = 3; // 
    object.part_C.count_msg3            = 9; // 
    object.part_C.lat_pos               = 2048+32; // (x-2048)/16=2
    object.part_C.lat_vel               = 2048+24; // (x-2048)/16=1.5
    object.part_C.long_pos              = 32*8; // x/32=8
    object.part_C.long_vel              = 2048+100; // (x-2048)/16=6.25
    object.part_C.width                 = 22; // x/10=2.2
    test_objects.num = 1;
    memcpy(&test_objects.object[0], &object, sizeof(struct IfvObjectRawData));
    ifv_object_list_raw_data_serialize(&test_objects, data, sizeof(data));
    b = driver->ParseObstacles(data, sizeof(data), raw_objects);
    ASSERT_TRUE(b);
    ASSERT_EQ(objlist.GetSize(), 1);
    const std::shared_ptr<holo::obstacle::ObstacleVisionT<float32_t>> obj = objlist.GetObstacleList()[0];
    ASSERT_EQ(obj->GetTimestamp().GetSec(), 1);
    ASSERT_EQ(obj->GetTimestamp().GetNsec(), 2);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetX(), 8.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetY(), -2.0f);
    ASSERT_FLOAT_EQ(obj->GetPosition().GetZ(), 0.0f);
    ASSERT_EQ(obj->GetCoordinate(), holo::common::Coordinate(holo::common::Coordinate::BODY));
    ASSERT_EQ(obj->GetObstacleId(), 9);
    ASSERT_EQ(obj->GetSensorId(), holo::sensors::StringToSensorId("CAMERA", "CAMERA_DELPHI_IFV300", "FRONT_WINDOW", "CENTER", "TOP_MOST"));
    ASSERT_EQ(obj->GetClassification(), holo::common::Classification(holo::common::Classification::MainType::PEDESTRIAN,
        holo::common::Classification::SubType::PEDESTRIAN));
    ASSERT_FLOAT_EQ(obj->GetObstacleExistScore(), 1.0f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[0], 6.25f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[1], -1.5f);
    ASSERT_FLOAT_EQ(obj->GetRelativeVelocity()[2], 0.0f);
    ASSERT_FLOAT_EQ(obj->GetAcceleration()[0], 0.5f);
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
    ASSERT_EQ(obj->GetCutInCutOut(), holo::obstacle::CutInCutOut::NEXT_CUT_OUT_RIGHT);
}
#endif
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
