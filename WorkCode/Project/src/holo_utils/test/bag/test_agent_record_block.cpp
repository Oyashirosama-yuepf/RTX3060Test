#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <holo/os/shared_memory_block.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using namespace holo::bag::agent;

bool running = true;

void test_thread0(std::shared_ptr<Port> port, std::shared_ptr<holo::os::SharedMemoryBlockWriter> writer)
{
    holo::uint32_t count = 0U;
    port->Enable();
    holo::os::SharedMemoryNotification notification;
    holo::uint32_t                     block_version = 0U;
    holo::uint32_t                     block_index   = 0U;
    holo::uint32_t                     block_count   = writer->GetBlockCount();
    while (running)
    {
        auto        msg = std::make_shared<DataSequenceType>(32U);
        std::string str = std::to_string(count++);
        snprintf(&((*msg)[0]), 32, "%s", str.c_str());

        if (block_index >= block_count)
        {
            block_index = 0U;
        }

        if (msg->size() !=
            writer->Write(block_version, reinterpret_cast<holo::uint8_t*>(msg->data()), msg->size(), block_index))
        {
            std::cout << " write  data to memory error" << std::endl;
        }

        strncpy(notification.block_name, writer->GetName().c_str(),
                holo::os::SharedMemoryNotification::BLOCK_NAME_MAX_LENGTH);
        notification.block_name[holo::os::SharedMemoryNotification::BLOCK_NAME_MAX_LENGTH - 1] = '\0';
        notification.block_version                                                             = block_version;
        notification.block_index                                                               = block_index;

        port->Write(reinterpret_cast<holo::uint8_t*>(&notification), sizeof(notification),
                    holo::bag::protocol::HbpBufferType::NOTIFY);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++block_index;
    }
    port->Disable();
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

void session_write_event(std::shared_ptr<Session> session)
{
    while (running)
    {
        session->ProcessWriteEventOnce();
    }
}

int main()
{
    std::shared_ptr<Session> session      = std::make_shared<Session>("127.0.0.1", 55555);
    auto                     block_writer = std::make_shared<holo::os::SharedMemoryBlockWriter>("test_topic_0");
    block_writer->Init(1024, 10);

    session->Init();
    session->SetBusType("test_agent");
    session->SetDomainId(100);

    auto port0 = session->CreatePort("test_topic_0");
    port0->SetInbound(true);
    port0->SetNodeName("node_name_port0");
    port0->SetMetadata("message type metadata0");
    port0->ReportInfo();

    std::thread t0(test_thread0, port0, block_writer);

    std::cout << "wait for start" << std::endl;

    std::getchar();
    std::cout << "start" << std::endl;

    std::thread t10(session_event, session);
    std::thread t11(session_write_event, session);
    std::thread t12(session_connect_event, session);

    std::cout << "wait for stop" << std::endl;
    std::getchar();

    std::cout << "stop" << std::endl;

    running = false;

    t0.join();

    t10.join();
    t11.join();
    t12.join();

    session->Destroy();

    std::cout << "exit" << std::endl;
    return 0;
}
