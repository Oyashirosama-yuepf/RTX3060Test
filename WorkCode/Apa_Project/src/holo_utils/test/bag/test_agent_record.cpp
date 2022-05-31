#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

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

        port->Write(msg);
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

        port->Write(msg);
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

        port->Write(msg);
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

        port->Write(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    port->Disable();
}

static constexpr holo::int32_t PICTURE_WIDTH{320};
static constexpr holo::int32_t PICTURE_HEIGHT{240};
static constexpr holo::int32_t PICTURE_CHANNELS{3};

void test_thread4(std::shared_ptr<Port> port, std::shared_ptr<cv::VideoCapture> capture)
{
    holo::int32_t fps = capture->get(CV_CAP_PROP_FPS);
    std::cout << "video fps:" << fps << std::endl;
    holo::int32_t delay = 1000 / fps;
    port->Enable();
    cv::Mat      image;
    cv::Mat      out;
    size_t const size = PICTURE_WIDTH * PICTURE_HEIGHT * PICTURE_CHANNELS;
    while (running)
    {
        (*capture) >> image;

        // std::cout << "row:" << image.rows << "  col:" << image.cols << "  ports:" << image.ports() <<
        // std::endl;

        cv::cvtColor(image, out, cv::COLOR_BGR2RGB);

        auto msg = std::make_shared<DataSequenceType>(size);
        std::memcpy(&((*msg)[0]), out.data, size);

        // std::cout << "image size:" << size << std::endl;
        port->Write(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
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
        if (session->IsEstablished())
        {
            session->ProcessWriteEventOnce();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
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

    auto port4 = session->CreatePort("test_video");
    port4->SetInbound(true);
    port4->SetNodeName("node_name_port4");
    port4->SetMetadata("message type metadata4");
    port4->ReportInfo();

    // open video
    std::shared_ptr<cv::VideoCapture> capture = std::make_shared<cv::VideoCapture>();

    // read the default caera
    capture->open(0);

    // check if we succeeded
    if (!capture->isOpened())
    {
        std::cout << "Failed to open video device!" << std::endl;
        exit(-1);
    }

    if (!capture->set(CV_CAP_PROP_FRAME_WIDTH, PICTURE_WIDTH))
    {
        std::cout << "Failed to set video width!" << std::endl;
        exit(-1);
    }

    if (!capture->set(CV_CAP_PROP_FRAME_HEIGHT, PICTURE_HEIGHT))
    {
        std::cout << "Failed to set video height!" << std::endl;
        exit(-1);
    }

    if (PICTURE_WIDTH != capture->get(CV_CAP_PROP_FRAME_WIDTH))
    {
        std::cout << "Failed to check video width!" << std::endl;
        // exit(-1);
    }

    if (PICTURE_HEIGHT != capture->get(CV_CAP_PROP_FRAME_HEIGHT))
    {
        std::cout << "Failed to check video height!" << std::endl;
        // exit(-1);
    }

    std::cout << "video width:" << capture->get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "video height:" << capture->get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;

    std::thread t0(test_thread0, port0);
    std::thread t1(test_thread1, port1);
    std::thread t2(test_thread2, port2);
    std::thread t3(test_thread3, port3);
    std::thread t4(test_thread4, port4, capture);

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
    t4.join();

    t10.join();
    t11.join();
    t12.join();

    session->Destroy();

    std::cout << "exit" << std::endl;
    return 0;
}
