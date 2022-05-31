#include <gtest/gtest.h>
#include <holo/sensors/lidar/libply/libply.h>

using namespace holo;
using namespace holo::sensors;
using PointType      = holo::point_cloud::PointXYZIRSt<float64_t>;
using PointCloudType = point_cloud::PointCloudT<PointType, 10>;

TEST(PLYTest, x0)
{
    PointCloudType pcd{
        {{0.0, 0.0, 0.0}, 0, 5, {0, 123456789}},   {{1.1, 1.1, 1.1}, 10, 15, {1, 123456789}},
        {{2.2, 2.2, 2.2}, 20, 25, {2, 123456789}}, {{3.3, 3.3, 3.3}, 30, 35, {3, 123456789}},
        {{4.4, 4.4, 4.4}, 40, 45, {4, 123456789}}, {{5.5, 5.5, 5.5}, 50, 55, {5, 123456789}},
        {{6.6, 6.6, 6.6}, 60, 65, {6, 123456789}}, {{7.7, 7.7, 7.7}, 70, 75, {7, 123456789}},
        {{8.8, 8.8, 8.8}, 80, 85, {8, 123456789}}, {{9.9, 9.9, 9.9}, 90, 95, {9, 123456789}},
    };
    std::string out_name = "0.ply";
    size_t      size     = holo::sensors::PlyConverter<PointCloudType>::Save(pcd, out_name);
    ASSERT_TRUE(size > 0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
