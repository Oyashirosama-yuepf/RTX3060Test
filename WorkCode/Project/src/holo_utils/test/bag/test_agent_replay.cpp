#include <holo/bag/agent/port.h>
#include <holo/bag/agent/session.h>
#include <holo/thread/thread_pool.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace holo::bag::agent;

bool running = true;

std::shared_ptr<holo::thread::ThreadPool> g_task_thread_pool = nullptr;

void callback0(holo::uint8_t const* data, holo::uint32_t const size)
{
    (void)size;
    std::cout << "this is callback0, msg:" << data << std::endl;
}

void callback1(holo::uint8_t const* data, holo::uint32_t const size)
{
    (void)size;
    std::cout << "this is callback1, msg:" << data << std::endl;
}

void callback2(holo::uint8_t const* data, holo::uint32_t const size)
{
    (void)size;
    std::cout << "this is callback2, msg:" << data << std::endl;
}

void callback3(holo::uint8_t const* data, holo::uint32_t const size)
{
    (void)size;
    std::cout << "this is callback3, msg:" << data << std::endl;
}

static constexpr holo::int32_t       PICTURE_WIDTH{320};
static constexpr holo::int32_t       PICTURE_HEIGHT{240};
static constexpr holo::int32_t       PICTURE_CHANNELS{3};
static constexpr holo::char_t const* WINDOW_NAME{"test_video"};

static cv::Mat out_image;

void callback4(holo::uint8_t const* data, holo::uint32_t const size)
{
    (void)size;
    // std::cout << "msg size:" << msg->size() << std::endl;
    // std::cout << "this is callback4, msg:" << &((*msg)[0]) << std::endl;

    // std::memcpy(in_image.data, &((*msg)[0]), msg->size());
    cv::Mat in_image(PICTURE_HEIGHT, PICTURE_WIDTH, CV_8UC3, (void*)data);

    cv::cvtColor(in_image, out_image, cv::COLOR_RGB2BGR);

    cv::imshow(WINDOW_NAME, out_image);

    if (cv::waitKey(30) == 'q')
    {
        cv::destroyWindow(WINDOW_NAME);
        exit(0);
    }
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
            std::cout << "connect failure! wait for 5 seconds " << std::endl;
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

    cv::namedWindow(WINDOW_NAME, 0);
    // cv::resizeWindow(WINDOW_NAME, PICTURE_WIDTH, PICTURE_HEIGHT);

    auto port0 = session->CreatePort("test_topic_0");
    auto port1 = session->CreatePort("test_topic_1");
    auto port2 = session->CreatePort("test_topic_2");
    auto port3 = session->CreatePort("test_topic_3");
    auto port4 = session->CreatePort(WINDOW_NAME);

    port0->SetMessageHandler(callback0);
    port1->SetMessageHandler(callback1);
    port2->SetMessageHandler(callback2);
    port3->SetMessageHandler(callback3);
    port4->SetMessageHandler(callback4);

    port0->Enable();
    port1->Enable();
    port2->Enable();
    port3->Enable();
    port4->Enable();

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
    port1->Disable();
    port2->Disable();
    port3->Disable();
    port4->Disable();

    t10.join();
    t11.join();

    g_task_thread_pool->Destroy();

    session->Destroy();

    std::cout << "exit" << std::endl;

    return 0;
}
