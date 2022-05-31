#include <holo/log/hololog.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace holo;
using namespace log;

static int           g_running = 1;
static constexpr int g_num     = 10;

void print(int n)
{
    uint32_t i = 0;
    while (g_running)
    {
        LOG_IF_EVERY_N(INFO, i < 11, 10) << "MultiThread id=" << n << " test LOG_IF_EVERY_N:" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        i++;
    }
}
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "start test:" << std::endl;

    std::thread t[g_num];
    for (int i = 0; i < g_num; i++)
    {
        t[i] = std::thread(print, i);
    }

    std::getchar();

    g_running = 0;

    for (int i = 0; i < g_num; i++)
    {
        if (t[i].joinable())
        {
            t[i].join();
        }
    }

    std::cout << std::endl << "end test" << std::endl;

    return 0;
}
