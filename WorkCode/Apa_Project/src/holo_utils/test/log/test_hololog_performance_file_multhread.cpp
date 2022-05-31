#include <holo/log/hololog.h>
#include <sys/time.h>
#include <unistd.h>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

using namespace holo;
using namespace log;

static int           g_running    = 0;
static constexpr int g_thread_num = 10;
static constexpr int g_num        = 100 * 10000;

std::mutex              g_mutex;
std::condition_variable g_start_cond;
std::atomic<int>        g_count{0};

std::chrono::milliseconds g_start_ms{0};
std::chrono::milliseconds g_end_ms{0};

void waitForStartTest()
{
    std::unique_lock<std::mutex> looker(g_mutex);
    g_start_cond.wait(looker, [] { return g_running; });
}

void startTest()
{
    {
        std::unique_lock<std::mutex> looker(g_mutex);
        g_running = 1;
    }

    g_start_cond.notify_all();
}

void endTest()
{
    g_running = 0;
    g_start_cond.notify_all();
}

void print(int n)
{
    waitForStartTest();

    // uint32_t count = 0;
    // uint32_t max   = g_num / 10;

    while (g_running && g_count < g_num)
    {
        LOG(INFO) << "Thread " << n << " test log performance " << g_count;
        ++g_count;
    }
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (argc < 2)
    {
        std::cout << "input filename" << std::endl;
        return 0;
    }

    ConsoleConfigure console("console");
    console.SetAsync(true);
    console.SetLevel(LogLevel::OFF);
    SingleFileConfigure file("file", argv[1]);
    file.SetAsync(true);

    HoloLogger::Add(console);
    HoloLogger::Add(file);

    std::cout << "start test:" << std::endl;

    std::thread t[g_thread_num];
    for (int i = 0; i < g_thread_num; i++)
    {
        t[i] = std::thread(print, i);
    }

    std::cout << "threads all OK! press any key to start test" << std::endl;
    std::getchar();

    g_start_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    startTest();

    // std::getchar();
    // endTest();

    for (int i = 0; i < g_thread_num; i++)
    {
        if (t[i].joinable())
        {
            t[i].join();
        }
    }

    g_end_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    std::cout << "start:" << g_start_ms.count() << std::endl;
    std::cout << "end:" << g_end_ms.count() << std::endl;
    std::cout << "end-start:" << g_end_ms.count() - g_start_ms.count() << std::endl;

    std::cout << std::endl << "end test" << std::endl;

    std::getchar();

    return 0;
}
