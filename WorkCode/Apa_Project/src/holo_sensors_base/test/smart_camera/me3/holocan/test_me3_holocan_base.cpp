#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/me3/me3_holocan.h>

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

TEST(MobileyeDriverT, ConstructorHoloCan)
{
    Extrinsicf                     extrinsic;
    MobileyeDriverT<HoloCanPacket> driver(extrinsic);
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
