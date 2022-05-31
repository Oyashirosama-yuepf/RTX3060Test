#include <gtest/gtest.h>
#include <holo/log/hololog.h>
#include <holo/sensors/interface/holo_socket/udp_client.h>
#include <holo/sensors/interface/udp_interface.h>
#include <unistd.h>
#include <thread>

static const uint32_t PACKET_SIZE = 1248; /* rsruby */
static const uint32_t COUNT       = PACKET_SIZE / sizeof(uint32_t);

struct TestPacket
{
    uint32_t GetDataU32()
    {
        return (data_[3] << 24) | (data_[2] << 16) | (data_[1] << 8) | data_[0];
    }
    void SetData(uint32_t u32)
    {
        for (uint32_t i = 0; i < COUNT; i++)
        {
            (void)std::memcpy(&data_[i * sizeof(uint32_t)], &u32, sizeof(uint32_t));
        }
    }
    uint32_t Serialize(uint8_t* data, uint32_t size) const noexcept
    {
        if (size < PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(data, &data_[0], PACKET_SIZE);
        return PACKET_SIZE;
    }
    uint32_t Deserialize(const uint8_t* data, uint32_t size)
    {
        if (size > PACKET_SIZE)
        {
            return 0;
        }
        (void)std::memcpy(&data_[0], data, PACKET_SIZE);
        return PACKET_SIZE;
    }

private:
    uint8_t data_[PACKET_SIZE];
};

static uint32_t last_data = 0;
static uint32_t loss_data = 0;
static uint32_t completed = 0;

static bool running = true;

void FuncCallBack(TestPacket packet)
{
    if (packet.GetDataU32() - last_data != 1)
    {
        ++loss_data;
    }
    last_data = packet.GetDataU32();
    completed++;
    usleep(165); /* if don't use queue, time > 160um loss data */
}

void Sender()
{
    holo::sensors::interface::HoloSocketUdpClient client("127.0.0.1", 5800, 1000);
    TestPacket                                    packet;
    uint32_t                                      i = 1;
    uint8_t                                       buffer[PACKET_SIZE];
    while (i < 6500 + 1)
    {
        packet.SetData(i);
        packet.Serialize(&buffer[0], PACKET_SIZE);
        client.Send(&buffer[0], PACKET_SIZE);
        // LOG(INFO) << "Send: " << i - 1; /* too fast */
        i++;
        usleep(160); /* rsruby: 1s >> 6200 Packet (160um * 6200) */
    }
    running = false;
}

TEST(UDP_INTERFACE, All)
{
    holo::sensors::interface::UdpInterfaceParam data_if_param;
    data_if_param.addr.ip   = "127.0.0.1";
    data_if_param.addr.port = 5800;
    data_if_param.timeout   = 10;
    // holo::sensors::interface::UdpInterface<TestPacket> data_interface(data_if_param);
    holo::sensors::interface::UdpInterface<TestPacket> data_interface(data_if_param, true);
    std::function<void(const TestPacket&)>             h1 = std::bind(&FuncCallBack, std::placeholders::_1);
    data_interface.InstallCallback(h1);

    std::thread thr_send(Sender);

    while (1)
    {
        LOG(INFO) << " AllTask : BufferCount : Completed : LossData -> "
                  << data_interface.GetTaskQueueCount() + completed << " : "
                  << data_interface.GetIdleBufferCount() + data_interface.GetTaskQueueCount() << " : " << completed
                  << " : " << loss_data;
        if (!running)
        {
            sleep(1);  // wait task process end
            if (thr_send.joinable())
            {
                thr_send.join();
            }
            break;
        }
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
