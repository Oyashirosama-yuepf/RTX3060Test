#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

using namespace holo::bag::agent;

bool running = true;

void test_thread0(std::shared_ptr<Port> port)
{
    port->Enable();
    while (running)
    {
        auto msg = std::make_shared<DataSequenceType>(32U);
        for (size_t i = 0U; i < 32U; i++)
            (*msg)[i] = 'a';
        (*msg)[31] = '\0';

        port->Write(reinterpret_cast<holo::uint8_t*>(msg->data()), msg->size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    port->Disable();
}

void test_thread1(std::shared_ptr<Port> port)
{
    port->Enable();
    while (running)
    {
        auto msg = std::make_shared<DataSequenceType>(32U);
        for (size_t i = 0U; i < 32U; i++)
            (*msg)[i] = 'b';
        (*msg)[31] = '\0';

        port->Write(reinterpret_cast<holo::uint8_t*>(msg->data()), msg->size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    port->Disable();
}

void test_thread2(std::shared_ptr<Port> port)
{
    port->Enable();
    while (running)
    {
        auto msg = std::make_shared<DataSequenceType>(32U);
        for (size_t i = 0U; i < 32U; i++)
            (*msg)[i] = 'c';
        (*msg)[31] = '\0';

        port->Write(reinterpret_cast<holo::uint8_t*>(msg->data()), msg->size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    port->Disable();
}

void test_thread3(std::shared_ptr<Port> port)
{
    port->Enable();
    while (running)
    {
        auto msg = std::make_shared<DataSequenceType>(32U);
        for (size_t i = 0U; i < 32U; i++)
            (*msg)[i] = 'd';
        (*msg)[31] = '\0';

        port->Write(reinterpret_cast<holo::uint8_t*>(msg->data()), msg->size());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
    std::shared_ptr<Session> session = std::make_shared<Session>("127.0.0.1", 55555);

    session->Init();
    session->SetBusType("test_agent");
    session->SetDomainId(100);

    auto port0 = session->CreatePort("test_topic_0");
    port0->SetInbound(true);
    port0->SetNodeName("node_name_port0");
    port0->SetMetadata("message type metadata0");
    port0->ReportInfo();

    auto port1 = session->CreatePort("test_topic_1");
    port1->SetInbound(true);
    port1->SetNodeName("node_name_port1");
    port1->SetMetadata("message type metadata1");
    port1->ReportInfo();

    auto port2 = session->CreatePort("test_topic_2");
    port2->SetInbound(true);
    port2->SetNodeName("node_name_port2");
    port2->SetMetadata("message type metadata2");
    port2->ReportInfo();

    auto port3 = session->CreatePort("test_topic_3");
    port3->SetInbound(true);
    port3->SetNodeName("node_name_port3");
    port3->SetMetadata("message type metadata3");
    port3->ReportInfo();

    std::thread t0(test_thread0, port0);
    std::thread t1(test_thread1, port1);
    std::thread t2(test_thread2, port2);
    std::thread t3(test_thread3, port3);

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
    t1.join();
    t2.join();
    t3.join();

    t10.join();
    t11.join();
    t12.join();

    session->Destroy();

    std::cout << "exit" << std::endl;
    return 0;
}
