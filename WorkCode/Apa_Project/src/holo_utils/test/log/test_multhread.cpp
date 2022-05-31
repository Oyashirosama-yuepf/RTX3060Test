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
    while (g_running)
    {
        if (n % 2 == 0)
        {
            LOG(INFO) << "Thread " << n;
        }
        else
        {
            LOG(WARNING) << "Thread " << n;
        }
        // std::this_thread::sleep_for(std::chrono::milliseconds(g_num));
    }
}
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (argc < 2)
    {
        std::cout << "input file name" << std::endl;
        return 0;
    }

    std::cout << "start test:" << std::endl;

    ConsoleConfigure     console("console");
    RollingFileConfigure rolling_file("roll_file", argv[1]);

    HoloLogger::Add(console);
    HoloLogger::Add(rolling_file);

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
