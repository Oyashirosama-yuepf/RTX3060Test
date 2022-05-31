#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/me3/me3_someip.h>

using namespace holo;
using namespace holo::sensors;
using namespace holo::sensors::mobileye;

/* obstacle alias */
using ObjectType   = holo::sensors::mobileye::MobileyeObstacle;
using ObstacleType = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallbackType = std::function<void(const ObstaclePtrListType&)>;
/* lane boundary alias */
using MobileyeBoundaryType  = holo::sensors::mobileye::MobileyeLaneBoundary;
using LaneboundaryType      = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType         = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallbackType = std::function<void(const RoadFrameType&)>;

template <typename T>
class MobileyeDriverTest : public SmartCameraDriverT<T>, public MobileyeDriverBase
{
public:
    MobileyeDriverTest() : SmartCameraDriverT<T>(), MobileyeDriverBase(Extrinsicf())
    {
    }
    void ParseData(const T&)
    {
    }
};

TEST(MobileyeDriverTest, ConstructorFloat)
{
    MobileyeDriverTest<float> driver;
    ASSERT_EQ(driver.GetSensorId(), 0);
    float fval = 123.456;
    ASSERT_NO_THROW(driver.ParseData(fval));
    ObstacleListCallbackType obstacle_list_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(obstacle_list_callback));
    RoadFrameCallbackType road_frame_callback = nullptr;
    ASSERT_NO_THROW(driver.InstallCallback(road_frame_callback));
}

TEST(MobileyeDriverT, ConstructorSomeip)
{
    Extrinsicf                        extrinsic;
    MobileyeDriverT<SomeipPacketType> driver(extrinsic);
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
