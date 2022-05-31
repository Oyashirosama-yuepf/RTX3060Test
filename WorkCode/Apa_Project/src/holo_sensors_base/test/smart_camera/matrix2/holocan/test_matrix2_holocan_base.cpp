#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/matrix2/matrix2_holocan.h>

using namespace holo;
using namespace holo::sensors;
using namespace holo::sensors::horizon_matrix2;

//! obstacle typedefs
using ObjectType     = holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle;
using ObjectListType = std::array<ObjectType, HORIZON_MATRIX2_OBJECTS_NUM>;
using ObstacleType   = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallbackType = std::function<void(const ObstaclePtrListType&)>;
//! road frame typedefs
using LineType              = holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary;
using LineListType          = std::array<LineType, HORIZON_MATRIX2_LINES_NUM>;
using LaneboundaryType      = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType         = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallbackType = std::function<void(const RoadFrameType&)>;

template <typename T>
class HorizonMatrix2DriverTest : public SmartCameraDriverT<T>, public HorizonMatrix2DriverBase
{
public:
    HorizonMatrix2DriverTest() : SmartCameraDriverT<T>(), HorizonMatrix2DriverBase(Extrinsicf())
    {
    }
    void ParseData(const T&)
    {
    }
};

TEST(HorizonMatrix2DriverTest, ConstructorFloat)
{
    HorizonMatrix2DriverTest<float> driver;
    ASSERT_EQ(driver.GetSensorId(), 0);
    float fval = 123.456;
    ASSERT_NO_THROW(driver.ParseData(fval));
    ObstacleListCallbackType obstacle_list_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(obstacle_list_callback));
    RoadFrameCallbackType road_frame_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(road_frame_callback));
}

TEST(HorizonMatrix2DriverT, ConstructorHoloCan)
{
    Extrinsicf                           extrinsic;
    HorizonMatrix2DriverT<HoloCanPacket> driver(extrinsic);
    ASSERT_EQ(driver.GetSensorId(), 0);
    ObstacleListCallbackType obstacle_list_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(obstacle_list_callback));
    RoadFrameCallbackType road_frame_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(road_frame_callback));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
