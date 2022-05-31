#include <holo/log/hololog.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace holo;
using namespace log;

static int                   g_running   = 1;
static constexpr int         g_num       = 10;
static constexpr char const* g_warn_msg  = "This is a warning message";
static constexpr char const* g_error_msg = "This is a error message";

void print(int n)
{
    while (g_running)
    {
        if (n % 2 == 0)
        {
            LOG(INFO) << "Thread " << n;
        }
        else
        {
            LOG(DEBUG) << "Thread " << n;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(g_num));
    }
}
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "start test:" << std::endl;

    HoloLogger::SetLogLevel(LogLevel::FATAL);

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

    LOG(WARNING) << g_warn_msg;
    LOG(ERROR) << g_error_msg;

    std::cout << std::endl << "end test" << std::endl;

    return 0;
}
