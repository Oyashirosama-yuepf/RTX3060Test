#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/ifv300/ifv300_someip.h>

using namespace holo;
using namespace holo::sensors;
using namespace holo::sensors::ifv300;

/* obstacle alias */
using ObjectType   = holo::sensors::ifv300::Ifv300Obstacle;
using ObstacleType = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallbackType = std::function<void(const ObstaclePtrListType&)>;
/* lane boundary alias */
using LineType              = holo::sensors::ifv300::Ifv300LaneBoundary;
using LaneboundaryType      = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType         = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallbackType = std::function<void(const RoadFrameType&)>;

template <typename T>
class Ifv300DriverTest : public SmartCameraDriverT<T>, public Ifv300DriverBase
{
public:
    Ifv300DriverTest() : SmartCameraDriverT<T>(), Ifv300DriverBase(Extrinsicf())
    {
    }
    void ParseData(const T&)
    {
    }
};

TEST(Ifv300DriverTest, ConstructorFloat)
{
    Ifv300DriverTest<float> driver;
    ASSERT_EQ(driver.GetSensorId(), 0);
    float fval = 123.456;
    ASSERT_NO_THROW(driver.ParseData(fval));
    ObstacleListCallbackType obstacle_list_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(obstacle_list_callback));
    RoadFrameCallbackType road_frame_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(road_frame_callback));
}

TEST(Ifv300DriverT, ConstructorSomeip)
{
    Extrinsicf                      extrinsic;
    Ifv300DriverT<SomeipPacketType> driver(extrinsic);
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
