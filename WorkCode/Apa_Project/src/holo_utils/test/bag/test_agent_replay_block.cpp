#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <holo/os/shared_memory_block.h>
#include <holo/thread/thread_pool.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

using namespace holo::bag::agent;

bool running = true;

std::shared_ptr<holo::thread::ThreadPool>          g_task_thread_pool = nullptr;
std::shared_ptr<holo::os::SharedMemoryBlockReader> g_block_reader     = nullptr;
holo::uint32_t                                     g_block_count      = 0U;
holo::uint32_t                                     g_block_capacity   = 0U;

void callback0(holo::uint8_t const* data, holo::uint32_t const size)
{
    (void)size;

    if (nullptr == g_block_reader)
    {
        g_block_reader   = std::make_shared<holo::os::SharedMemoryBlockReader>("test_topic_0");
        g_block_count    = g_block_reader->GetBlockCount();
        g_block_capacity = g_block_reader->GetBlockDataCapacity();
    }

    auto notification = reinterpret_cast<holo::os::SharedMemoryNotification const*>(data);
    if (notification->block_index > g_block_count)
    {
        throw holo::exception::OutOfRangeException{"shared memory block, block_index is out of range!"};
    }

    holo::uint32_t data_size = g_block_reader->GetBlockDataSize(notification->block_index);
    if (0U == data_size || data_size > g_block_capacity)
    {
        throw holo::exception::RuntimeErrorException{"shared memory block, data_size is 0U!"};
    }

    std::vector<holo::uint8_t> sample(data_size);

    g_block_reader->Read(sample.data(), data_size, notification->block_index, notification->block_version);

    std::cout << "this is callback0, msg:" << sample.data() << std::endl;
}

void session_event(std::shared_ptr<Session> session)
{
    while (running)
    {
        session->ProcessEventOnce();
    }
}

void session_connect_event(std::shared_ptr<Session> session)
{
    while (running)
    {
        if (!session->TryConnectOnce())
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            continue;
        }

        holo::int64_t now =
            std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();

        holo::int64_t peer_active_time = session->GetPeerActiveTime();

        if (now > peer_active_time + 10'000'000)
        {
            if (session->IsEstablished())
            {
                session->SendDetectionPackage();
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void task_handler(std::function<void()> const& task)
{
    g_task_thread_pool->AddTask(task);
}

int main()
{
    g_task_thread_pool               = std::make_shared<holo::thread::ThreadPool>(4, 2048);
    std::shared_ptr<Session> session = std::make_shared<Session>("127.0.0.1", 55555);

    session->Init();
    session->SetBusType("test_agent");
    session->SetDomainId(100);
    session->SetTaskHandler(task_handler);

    auto port0 = session->CreatePort("test_topic_0");

    port0->SetMessageHandler(callback0);

    port0->Enable();

    std::cout << "wait for start" << std::endl;

    std::getchar();
    std::cout << "start" << std::endl;

    std::thread t10(session_event, session);
    std::thread t11(session_connect_event, session);

    std::cout << "wait for stop" << std::endl;
    std::getchar();

    std::cout << "stop" << std::endl;

    running = false;

    port0->Disable();

    t10.join();
    t11.join();

    g_task_thread_pool->Destroy();

    session->Destroy();

    std::cout << "exit" << std::endl;

    return 0;
}
