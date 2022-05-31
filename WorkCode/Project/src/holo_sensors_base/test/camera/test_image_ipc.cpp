#include <gtest/gtest.h>
#include <holo/sensors/camera/image_ipc.h>

using namespace holo;
using namespace holo::sensors::camera;

TEST(ImageIpc, Constructor)
{
    SensorId                  id       = 123456;
    uint32_t                  rows     = 720;
    uint32_t                  cols     = 1280;
    holo::Image::Encoding     encoding = holo::Image::Encoding::GRAYSCALE;
    std::shared_ptr<ImageIpc> ipc;
    ASSERT_NO_THROW(ipc = std::make_shared<ImageIpc>(id, rows, cols, encoding));
    ASSERT_EQ(ipc->GetSensorId(), id);
    ASSERT_EQ(ipc->GetCols(), cols);
    ASSERT_EQ(ipc->GetRows(), rows);
    ASSERT_EQ(ipc->GetEncoding(), encoding);
}

TEST(ImageIpc, ConstructorBySensorId0)
{
    SensorId                  id = 123456;
    std::shared_ptr<ImageIpc> client;
    EXPECT_ANY_THROW(client = std::make_shared<ImageIpc>(id));
}

TEST(ImageIpc, ConstructorBySensorId1)
{
    SensorId                  id       = 123456;
    uint32_t                  rows     = 720;
    uint32_t                  cols     = 1280;
    holo::Image::Encoding     encoding = holo::Image::Encoding::NV12;
    std::shared_ptr<ImageIpc> server;
    ASSERT_NO_THROW(server = std::make_shared<ImageIpc>(id, rows, cols, encoding));
    std::shared_ptr<ImageIpc> client;
    ASSERT_NO_THROW(client = std::make_shared<ImageIpc>(id));
    ASSERT_EQ(client->GetSensorId(), id);
    ASSERT_EQ(client->GetCols(), cols);
    ASSERT_EQ(client->GetRows(), rows);
    ASSERT_EQ(client->GetEncoding(), encoding);

    holo::common::Timestamp                          received_stamp;
    holo::common::Timestamp                          trigger_stamp;
    holo::Image::Encoding                            encoding2;
    std::vector<holo::sensors::camera::StreamBuffer> buffers;
    holo::sensors::camera::StreamBuffer              block0;
    block0.init     = false;
    block0.start    = nullptr;
    block0.capacity = 0;
    buffers.push_back(block0);
    bool r = client->GetImageData(received_stamp, trigger_stamp, encoding2, buffers);
    ASSERT_FALSE(r);
    buffers.push_back(block0);
    r = client->GetImageData(received_stamp, trigger_stamp, encoding2, buffers);
    ASSERT_FALSE(r);
    uint8_t data0[1280 * 720 * 2];
    buffers[0].init     = true;
    buffers[0].start    = nullptr;
    buffers[0].capacity = 1280 * 720 - 1;
    buffers[0].size     = 0;
    buffers[1].init     = true;
    buffers[1].start    = data0 + 1280 * 720;
    buffers[1].capacity = 1280 * 720;
    buffers[1].size     = 0;
    r                   = client->GetImageData(received_stamp, trigger_stamp, encoding2, buffers);
    ASSERT_FALSE(r);
    buffers[0].start = data0;
    r                = client->GetImageData(received_stamp, trigger_stamp, encoding2, buffers);
    ASSERT_FALSE(r);
    buffers[0].capacity = 1280 * 720;
    ASSERT_EQ(buffers[0].size, 0);
    ASSERT_EQ(buffers[1].size, 0);
    r = client->GetImageData(received_stamp, trigger_stamp, encoding2, buffers);
    ASSERT_TRUE(r);
    ASSERT_EQ(encoding, holo::Image::Encoding::NV12);
    ASSERT_EQ(buffers[0].size, 1280 * 720);
    ASSERT_EQ(buffers[1].size, 1280 * 720 / 2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
