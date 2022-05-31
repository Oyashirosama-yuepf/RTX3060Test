#include <gtest/gtest.h>
#include <holo/log/hololog.h>
#include <holo/point_cloud/point_cloud.h>
#include <holo/point_cloud/point_type.h>
#include <holo/sensors/lidar/pointcloud_ipc.h>
#include <holo/utils/serializer.h>

using namespace holo;
using namespace holo::sensors::lidar;

const uint32_t NORMAL_POINT_NUM = 2500;
const uint32_t ERROR_POINT_NUM  = 250001;

TEST(PointCloudIpc, All)
{
    /* pcd type */
    using PcdPointType   = holo::point_cloud::PointXYZIRSt<float32_t>;
    using PointCloudType = holo::point_cloud::PointCloudT<PcdPointType, std::numeric_limits<size_t>::max(),
                                                          sizeof(PcdPointType), point_cloud::UnorganizedLayoutTag>;
    // using SerializerType   = holo::serialization::Serializer<false, 4>;
    // using DeserializerType = holo::serialization::Deserializer<false, 4>;

    /* server init data */
    SensorId id = 123456;
    /* server */
    std::shared_ptr<PointCloudIpc<PointCloudType>> server;
    ASSERT_NO_THROW(server = std::make_shared<PointCloudIpc<PointCloudType>>(id));
    /* client */
    std::shared_ptr<PointCloudIpc<PointCloudType>> client;
    ASSERT_NO_THROW(client = std::make_shared<PointCloudIpc<PointCloudType>>(id));
    /* client get init data */
    ASSERT_EQ(client->GetSensorId(), id);
    ASSERT_EQ(client->GetShmemSize(), server->GetShmemSize());
    ASSERT_EQ(client->GetCapacity(), server->GetCapacity());
    ASSERT_EQ(client->GetDataSize(), server->GetDataSize());
    /* server set point cloud data (pcd) */
    /* create a pcd */
    PointCloudType pcd;
    /* init pcd data */
    {
        pcd.reserve(NORMAL_POINT_NUM + 10); /* test */
        pcd.resize(NORMAL_POINT_NUM);
        for (uint32_t i = 0u; i < NORMAL_POINT_NUM; i++)
        {
            PcdPointType& point = pcd.at(i);
            point.SetX(12);
            point.SetY(12);
            point.SetZ(12);
            point.SetIntensity(0);
            point.SetTimestamp(Timestamp(10, 20));
        }
    }
    /* set pcd data to shm */
    ASSERT_EQ(server->SetPointCloudData(pcd), true);

    /* client get point cloud data (pcd) */
    PointCloudType pcd2;
    client->GetPointCloudData(pcd2);

    /* check pointcloud data */
    {
        ASSERT_EQ(NORMAL_POINT_NUM, pcd2.size());
        for (uint32_t i = 0; i < pcd2.size(); i++)
        {
            PcdPointType& point = pcd2.at(i);
            ASSERT_EQ(point.GetX(), 12);
            ASSERT_EQ(point.GetY(), 12);
            ASSERT_EQ(point.GetZ(), 12);
            ASSERT_EQ(point.GetIntensity(), 0);
            ASSERT_EQ(point.GetTimestamp(), Timestamp(10, 20));
        }
    }

    /* test pointcloud too big */
    /* init pcd data */
    {
        pcd.reserve(ERROR_POINT_NUM); /* test */
        pcd.resize(ERROR_POINT_NUM);
        for (uint32_t i = 0u; i < ERROR_POINT_NUM; i++)
        {
            PcdPointType& point = pcd.at(i);
            point.SetX(12);
            point.SetY(12);
            point.SetZ(12);
            point.SetIntensity(0);
            point.SetTimestamp(Timestamp(10, 20));
        }
    }
    ASSERT_EQ(server->SetPointCloudData(pcd), false);

    LOG(INFO) << "shm shm_size : " << server->GetShmemSize();
    LOG(INFO) << "shm capacity : " << server->GetCapacity();
    LOG(INFO) << "shm data size: " << server->GetDataSize();
}

TEST(my_test, class_size)
{
    uint32_t size = sizeof(holo::point_cloud::PointXYZIRSt<float32_t>);
    ASSERT_EQ(size, 32);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
