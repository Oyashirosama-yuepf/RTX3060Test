#include <gtest/gtest.h>
#include <holo/sensors/smart_camera/matrix2/matrix2_holocan.h>

using namespace holo;
using namespace holo::sensors::horizon_matrix2;

//! obstacle typedefs
using ObjectTyoe     = holo::sensors::horizon_matrix2::HorizonMatrix2Obstacle;
using ObjectListTyoe = std::array<ObjectTyoe, HORIZON_MATRIX2_OBJECTS_NUM>;
using ObstacleType   = holo::obstacle::ObstacleVisionT<float32_t>;
using ObstaclePtrListType =
    holo::obstacle::ObstaclePtrListT<ObstacleType, holo::obstacle::VISION_OBSTACLE_LIST_COMMON_CAPACITY>;
using ObstacleListCallback = std::function<void(const ObstaclePtrListType&)>;
//! road frame typedefs
using LineType          = holo::sensors::horizon_matrix2::HorizonMatrix2LaneBoundary;
using LineListType      = std::array<LineType, HORIZON_MATRIX2_LINES_NUM>;
using LaneboundaryType  = holo::common::LaneBoundary<holo::numerics::Polynomial<float32_t, 3>>;
using RoadFrameType     = holo::common::RoadFrame<holo::numerics::Polynomial<float32_t, 3>, 8>;
using RoadFrameCallback = std::function<void(const RoadFrameType&)>;

TEST(HorizonMatrix2DriverT, All)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
