#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_someip.h>

using namespace holo;
using namespace holo::sensors;
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

template <typename T>
class BoschMpcDriverTest : public SmartCameraDriverT<T>, public BoschMpcDriverBase
{
public:
    BoschMpcDriverTest() : SmartCameraDriverT<T>(), BoschMpcDriverBase(Extrinsicf())
    {
    }
    void ParseData(const T&)
    {
    }
};

TEST(BoschMpcDriverTest, ConstructorFloat)
{
    BoschMpcDriverTest<float> driver;
    ASSERT_EQ(driver.GetSensorId(), 0);
    float fval = 123.456;
    ASSERT_NO_THROW(driver.ParseData(fval));
    ObstacleListCallback obstacle_list_callback = nullptr;
    driver.InstallCallback(obstacle_list_callback);
    RoadFrameCallback road_frame_callback = nullptr;
    driver.InstallCallback(road_frame_callback);
    MpcBoundaryType b1;
    b1.SetDy(1.2);
    MpcBoundaryType b2;
    b2.SetDy(-1.2);
    bool b = driver.CompareLaneBoundaryLeft(&b1, &b2);
    ASSERT_FALSE(b);
    b = driver.CompareLaneBoundaryRight(&b1, &b2);
    ASSERT_TRUE(b);
}

TEST(BoschMpcDriverBase, ConstructorSomeip)
{
    Extrinsicf                        extrinsic;
    BoschMpcDriverT<SomeipPacketType> driver(extrinsic);
    ASSERT_EQ(driver.GetSensorId(), 0);
    ObstacleListCallback obstacle_list_callback = nullptr;
    driver.InstallCallback(obstacle_list_callback);
    RoadFrameCallback road_frame_callback = nullptr;
    driver.InstallCallback(road_frame_callback);
    MpcBoundaryType b1;
    b1.SetDy(1.2);
    MpcBoundaryType b2;
    b2.SetDy(-1.2);
    bool b = driver.CompareLaneBoundaryLeft(&b1, &b2);
    ASSERT_FALSE(b);
    b = driver.CompareLaneBoundaryRight(&b1, &b2);
    ASSERT_TRUE(b);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
