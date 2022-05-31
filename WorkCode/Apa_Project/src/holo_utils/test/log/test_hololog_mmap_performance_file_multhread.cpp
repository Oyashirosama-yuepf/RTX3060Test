#include <holo/log/hololog.h>
#include <holo/log/log4cplus/buffer/block.h>
#include <holo/log/log4cplus/buffer/buffer.h>
#include <holo/log/log4cplus/ostream.h>
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
namespace log4 = ::holo::log::log4cplus;

static int           g_running    = 0;
static constexpr int g_thread_num = 10;
static constexpr int g_num        = 100 * 10000;

std::mutex              g_mutex;
std::condition_variable g_start_cond;
std::atomic<int>        g_count{0};

std::chrono::milliseconds g_start_ms{0};
std::chrono::milliseconds g_end_ms{0};

std::mutex                    g_buffer_mutex;
std::shared_ptr<log4::Buffer> g_buffer{nullptr};
std::string                   g_file;

static constexpr holo::uint32_t MAX_STREAM_BUFFER_SIZE = 20 * 1024;

thread_local holo::char_t  g_ostream_buffer[MAX_STREAM_BUFFER_SIZE]{};
thread_local log4::OStream tls_ostream{g_ostream_buffer, MAX_STREAM_BUFFER_SIZE};

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

std::shared_ptr<log4::Buffer> createBuffer(std::string const& file)
{
    std::unique_lock<std::mutex> looker(g_buffer_mutex);
    if (g_buffer == nullptr || g_buffer->IsBackup())
    {
        g_buffer = log4::Buffer::Create(file, 10 * 1024 * 1024, log4::BackupStrategy::INDEX);
    }
    return g_buffer;
}

void appendTime(std::ostream& output)
{
    struct timeval tv;
    struct ::tm    tm_time;

    gettimeofday(&tv, NULL);
    localtime_r(&tv.tv_sec, &tm_time);

    output << std::setw(4) << 1900 + tm_time.tm_year << std::setw(2) << 1 + tm_time.tm_mon << std::setw(2)
           << tm_time.tm_mday << ' ' << std::setw(2) << tm_time.tm_hour << ':' << std::setw(2) << tm_time.tm_min << ':'
           << std::setw(2) << tm_time.tm_sec << '.' << std::setw(6) << tv.tv_usec << ' ';
}

void print(int n)
{
    waitForStartTest();

    std::shared_ptr<log4::Buffer> buffer = createBuffer(g_file);
    while (g_running && g_count < g_num)
    {
        appendTime(tls_ostream);
        tls_ostream << "test_hololog_performance_multhread.cpp 55 INFO ";
        tls_ostream << "Thread " << n << " test log performance " << g_count << '\n';
        tls_ostream.Trunc();

        log4::Block block = buffer->RequestBlock(tls_ostream.Count());
        if (0 == block.Write(g_ostream_buffer, tls_ostream.Count()))
        {
            buffer->Backup();
            buffer            = createBuffer(g_file);
            log4::Block block = buffer->RequestBlock(tls_ostream.Count());
            if (0 == block.Write(g_ostream_buffer, tls_ostream.Count()))
            {
                std::cout << "create buffer error!" << std::endl;
            }
        }
        ++g_count;
        tls_ostream.Reset();
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

    g_file = argv[1];
    createBuffer(g_file);
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
